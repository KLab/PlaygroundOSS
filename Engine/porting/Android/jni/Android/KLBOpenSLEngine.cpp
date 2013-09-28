/* 
   Copyright 2013 KLab Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include <pthread.h>
#include <unistd.h>
#include "KLBOpenSLAudioPlayer.h"
#include "ivorbisfile.h"

KLBOpenSLEngine::KLBOpenSLEngine() :
engineObject(NULL),
asset_waiting_refill(NULL),
master_volume_bgm(1),
master_volume_se(1),
is_bgm_off(false),
is_se_off(false),
is_sound_paused(false),
m_multiProcessType(IClientRequest::E_SOUND_MULTIPROCESS_MUSIC_CUT)
{
    // DEBUG_PRINT("AUDIO; construct KLBOpenSLEngine");
	SLresult result;
    // DEBUG_PRINT("AUDIO; slCreateEngine");
	result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
    assert(SL_RESULT_SUCCESS == result);

    // DEBUG_PRINT("AUDIO; realizing engineObject");
	result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);

    // get the engine interface, which is needed in order to create other objects
    result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
    assert(SL_RESULT_SUCCESS == result);

    // DEBUG_PRINT("AUDIO; creating output mix");
	result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 0, NULL, NULL);
    assert(SL_RESULT_SUCCESS == result);

    // DEBUG_PRINT("AUDIO; realizing output mix");
	result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    assert(SL_RESULT_SUCCESS == result);

    // DEBUG_PRINT("AUDIO; allocating memories for handlers");
	soundHandles = (KLBOpenSLSoundHandle**)calloc(KLBOpenSLEngine::MAX_SOUND_HANDLE, sizeof(KLBOpenSLSoundHandle*));
	soundAssets = (KLBOpenSLSoundAsset**)calloc(KLBOpenSLEngine::MAX_SOUND_ASSETS, sizeof(KLBOpenSLSoundAsset*));

    // DEBUG_PRINT("AUDIO; creating KLBOpenSLSoundAssetLoader");
	assetLoader = new KLBOpenSLSoundAssetLoader();
	assetLoader->startObservation();

	cs_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	asset_refill_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

	observingThread = CPFInterface::getInstance().platform().createThread(ThreadSoundEngineParam, this);
}

KLBOpenSLEngine::~KLBOpenSLEngine()
{
	if (outputMixObject != NULL)
	{
		(*outputMixObject)->Destroy(outputMixObject);
	}
	if (engineObject != NULL)
	{
		(*engineObject)->Destroy(engineObject);
		engineObject = NULL;
		engineEngine = NULL;
	}
	for (int i = 0; i < MAX_SOUND_HANDLE; ++i)
	{
		KLBOpenSLSoundHandle* soundHandle = *(soundHandles + i);
		if (soundHandle != NULL)
		{
			delete soundHandle;
		}
	}
	free(soundHandles);
	free(soundAssets);
	delete assetLoader;
    if(observingThread != NULL)
    {
        CPFInterface::getInstance().platform().deleteThread(observingThread);
        observingThread = NULL;
    }
	pthread_mutex_destroy(&cs_mutex);
	pthread_mutex_destroy(&asset_refill_mutex);
}

KLBOpenSLEngine* KLBOpenSLEngine::getInstance()
{
	static KLBOpenSLEngine engine;
	return &engine;
}

void KLBOpenSLEngine::registerAssetForRefilling(KLBOpenSLSoundAsset* asset) {
	// DEBUG_PRINT("AUDIO; registering asset for vorbis samples refilling.");
	pthread_mutex_lock(&asset_refill_mutex);
	asset_waiting_refill = asset;
	pthread_mutex_unlock(&asset_refill_mutex);
}

void KLBOpenSLEngine::updateFadeRatio() {
	pthread_mutex_lock(&cs_mutex);
	for (int i = 0; i < MAX_SOUND_HANDLE; ++i) {
		KLBOpenSLSoundHandle** handle = soundHandles + i;
		if (*handle != NULL && (*handle)->isInitiated() && (*handle)->isPlaying()) {
			(*handle)->updateFadeParam();
		}
	}
	pthread_mutex_unlock(&cs_mutex);
}

void KLBOpenSLEngine::performRefillOnCurrentAsset() {
	pthread_mutex_lock(&asset_refill_mutex);
	if (asset_waiting_refill != NULL) {
		asset_waiting_refill->readVorbisSamples(-1);
		asset_waiting_refill = NULL;
	}
	pthread_mutex_unlock(&asset_refill_mutex);
}

s32 KLBOpenSLEngine::ThreadSoundEngineParam(void * hThread, void * data)
{
	KLBOpenSLEngine* engine = (KLBOpenSLEngine*)data;
	DEBUG_PRINT("AUDIO; sound engine observation thread started.");
    while(1)
    {
		engine->performRefillOnCurrentAsset();
		engine->updateFadeRatio();
        usleep(16000);
    }
    return 0; // 終了
}

KLBOpenSLSoundAsset *KLBOpenSLEngine::load(char const *path, bool is_se)
{
	if (strlen(path) == 8 && !strncmp(path, "asset://", 8)) {
		DEBUG_PRINT("skipping load() due to empty asset is specified.");
		return NULL;
	}
	DEBUG_PRINT("AUDIO; loading %s, bufmode=%d", path, is_se);
	// TODO: load beginning frames, then associate with assetLoader (if any)
	// search for vacant asset first
	KLBOpenSLSoundAsset* currentAsset = NULL;
	for (int i = 0; i < MAX_SOUND_ASSETS; ++i)
	{
		if (soundAssets[i] == NULL)
		{
			DEBUG_PRINT("AUDIO; opening file");
			soundAssets[i] = currentAsset = assetLoader->openFile(path, is_se);
			if (currentAsset == NULL) {
				DEBUG_PRINT("AUDIO; failed to open file: %s (file not found?)", path);
			}
			break;
		}
	}
	if (currentAsset == NULL) {
		return NULL;
	}
	if (is_se)
	{
		currentAsset->prepare(-1);
	}
	else
	{
		currentAsset->prepare(KLBOpenSLSoundAsset::DEFAULT_LOAD_SAMPLES);
		if (!currentAsset->isFullyBuffered())
		{
			assetLoader->registerAsset(currentAsset);
		}
	}
	return currentAsset;
}

s32 KLBOpenSLEngine::tellCorrespondingSoundHandle(KLBOpenSLSoundAsset *asset) {
	pthread_mutex_lock(&cs_mutex);
	s32 ret_val = 0;
	for (int i = 0; i < MAX_SOUND_HANDLE; ++i)
	{
		KLBOpenSLSoundHandle** handle = soundHandles + i;
		if (*handle != NULL && (*handle)->isInitiated() && (*handle)->getSoundAsset() == asset)
		{
			// DEBUG_PRINT("found tellAudio()");
			// return result of first one
			ret_val = (*handle)->tellAudio();
			break;
		}
	}
	pthread_mutex_unlock(&cs_mutex);
	return ret_val;
}

s32 KLBOpenSLEngine::getStateOfCorrespondingSoundHandle(KLBOpenSLSoundAsset *asset) {
	for (int i = 0; i < MAX_SOUND_HANDLE; ++i)
	{
		KLBOpenSLSoundHandle** handle = soundHandles + i;
		if (*handle != NULL && (*handle)->isInitiated() && (*handle)->getSoundAsset() == asset)
		{
			return (*handle)->getState();
		}
	}
	return 0;
}

void KLBOpenSLEngine::stopCorrespondingSoundHandles(KLBOpenSLSoundAsset *asset, bool isLockGained, float _tgtVol, u32 _millisec) {
	if (!isLockGained) {
		pthread_mutex_lock(&cs_mutex);
	}
	for (int i = 0; i < MAX_SOUND_HANDLE; ++i)
	{
		KLBOpenSLSoundHandle** handle = soundHandles + i;
		if (*handle != NULL && (*handle)->isInitiated() && (*handle)->getSoundAsset() == asset)
		{
			(*handle)->stop(_millisec, _tgtVol);
		}
	}
	if (!isLockGained) {
		pthread_mutex_unlock(&cs_mutex);
	}
}

void KLBOpenSLEngine::pauseCorrespondingSoundHandles(KLBOpenSLSoundAsset *asset, bool isLockGained, float _tgtVol, u32 _millisec) {
	if (!isLockGained) {
		pthread_mutex_lock(&cs_mutex);
	}
	for (int i = 0; i < MAX_SOUND_HANDLE; ++i)
	{
		KLBOpenSLSoundHandle** handle = soundHandles + i;
		if (*handle != NULL && (*handle)->isInitiated() && (*handle)->getSoundAsset() == asset)
		{
			(*handle)->pause(_millisec, _tgtVol);
		}
	}
	if (!isLockGained) {
		pthread_mutex_unlock(&cs_mutex);
	}
}

void KLBOpenSLEngine::resumeCorrespondingSoundHandles(KLBOpenSLSoundAsset *asset, bool isLockGained, float _tgtVol, u32 _millisec) {
	if (!isLockGained) {
		pthread_mutex_lock(&cs_mutex);
	}
	for (int i = 0; i < MAX_SOUND_HANDLE; ++i)
	{
		KLBOpenSLSoundHandle** handle = soundHandles + i;
		if (*handle != NULL && (*handle)->isInitiated() && (*handle)->getSoundAsset() == asset)
		{
			(*handle)->resume(_millisec, _tgtVol);
		}
	}
	if (!isLockGained) {
		pthread_mutex_unlock(&cs_mutex);
	}
}

void KLBOpenSLEngine::setMasterVolume(float volume, bool is_se) {
	if (is_se) {
		master_volume_se = volume;
	}
	else {
		master_volume_bgm = volume;
	}
}

void KLBOpenSLEngine::setFadeParamOnCorrespondingSoundHandles(KLBOpenSLSoundAsset *asset, float _tgtVol, u32 _millisec) {
	pthread_mutex_lock(&cs_mutex);
	for (int i = 0; i < MAX_SOUND_HANDLE; ++i)
	{
		KLBOpenSLSoundHandle** handle = soundHandles + i;
		if (*handle != NULL && (*handle)->isInitiated() && (*handle)->getSoundAsset() == asset)
		{
			(*handle)->setFadeParam(KLBOpenSLSoundHandle::FADE_TYPE_PLAYING, _tgtVol, _millisec);
		}
	}
	pthread_mutex_unlock(&cs_mutex);
}

void KLBOpenSLEngine::setVolumeOnCorrespondingSoundHandles(KLBOpenSLSoundAsset *asset, float volume, bool isLockGained) {
	if (!isLockGained) {
		pthread_mutex_lock(&cs_mutex);
	}
	DEBUG_PRINT("AUDIO; setting new volume(%f) for %s", volume, asset->getSrcFullPath());
	for (int i = 0; i < MAX_SOUND_HANDLE; ++i)
	{
		KLBOpenSLSoundHandle** handle = soundHandles + i;
		if (*handle != NULL && (*handle)->isInitiated() && (*handle)->getSoundAsset() == asset)
		{
			(*handle)->setVolume(volume);
		}
	}
	if (!isLockGained) {
		pthread_mutex_unlock(&cs_mutex);
	}
}

void KLBOpenSLEngine::discardCorrespondingSoundHandles(KLBOpenSLSoundAsset *asset, bool isLockGained) {
	if (!isLockGained) {
		pthread_mutex_lock(&cs_mutex);
	}
	// DEBUG_PRINT("AUDIO; discarding sound handle...(searching %d)", (int)asset);
	for (int i = 0; i < MAX_SOUND_HANDLE; ++i)
	{
		KLBOpenSLSoundHandle** handle = soundHandles + i;
		// DEBUG_PRINT("AUDIO; - candidate: %d at %d", (int)*handle, handle);
		if (*handle != NULL && (*handle)->isInitiated() && (*handle)->getSoundAsset() == asset)
		{
			delete *handle;
			*handle = NULL;
		}
	}
	if (!isLockGained) {
		pthread_mutex_unlock(&cs_mutex);
	}
}

void KLBOpenSLEngine::onActivityPause() {
	DEBUG_PRINT("AUDIO; performing pause on all playing sounds");
	is_sound_paused = true;
	for (int i = 0; i < MAX_SOUND_HANDLE; ++i) {
		KLBOpenSLSoundHandle** handle = soundHandles + i;
		if (*handle != NULL) {
			DEBUG_PRINT("AUDIO; pause target: initd: %d, isPlaying: %d, intruType: %d", (*handle)->isInitiated(), (*handle)->isPlaying(), (*handle)->getInterruptionType());
			if ((*handle)->isInitiated() && (*handle)->isPlaying() && ((*handle)->getInterruptionType() == eINTERRUPTION_TYPE_NONE)) {
				// サウンドを停止し割り込みフラグをたてる
				(*handle)->pause();
				(*handle)->setInterruptionType(eINTERRUPTION_TYPE_RESIGN_ACTIVE);
			}
		}
	}
}

void KLBOpenSLEngine::onActivityResume() {
	// DEBUG_PRINT("AUDIO; performing resume on all playing sounds");
	is_sound_paused = false;
	for (int i = 0; i < MAX_SOUND_HANDLE; ++i) {
		KLBOpenSLSoundHandle** handle = soundHandles + i;
		if (*handle != NULL) {
			DEBUG_PRINT("AUDIO; resume target: initd: %d, isPlaying: %d, intruType: %d", (*handle)->isInitiated(), (*handle)->isPlaying(), (*handle)->getInterruptionType());
			if ((*handle)->isInitiated() && !(*handle)->isPlaying() && ((*handle)->getInterruptionType() == eINTERRUPTION_TYPE_RESIGN_ACTIVE)) {
				// 割り込みフラグがたっている物に限り再生を再開
				(*handle)->resume();
				(*handle)->setInterruptionType(eINTERRUPTION_TYPE_NONE);
			}
		}
	}
}

void KLBOpenSLEngine::chackAudioMasterVolume() {
	switch (m_multiProcessType) {
		case IClientRequest::E_SOUND_MULTIPROCESS_MUSIC_CUT:    // ミュージックを無効
		    is_se_off  = false;
		    is_bgm_off = false;
		    break;
		case IClientRequest::E_SOUND_MULTIPROCESS_SOUND_CUT:    // ゲームサウンドを無効
		    is_se_off  = true;
		    is_bgm_off = false;
		    break;
		case IClientRequest::E_SOUND_MULTIPROCESS_SOUND_BGM_CUT: // ゲームのBGMサウンドのみ無効
		    is_se_off  = false;
		    is_bgm_off = true;
			/*
		    if(!isMusicPlayerPlaying()) {
		    	is_bgm_off = false;
		    }
			*/
		    break;
	}
	for (int i = 0; i < MAX_SOUND_HANDLE; ++i)
	{
		KLBOpenSLSoundHandle** handle = soundHandles + i;
		if (*handle != NULL && (*handle)->isInitiated() && (*handle)->isPlaying())
		{
			(*handle)->refreshVolume();
		}
	}
}

void KLBOpenSLEngine::unload(KLBOpenSLSoundAsset *asset) {
	// DEBUG_PRINT("unloading asset: %s", asset->getSrcFullPath());
	KLBOpenSLSoundHandle** handle;
	pthread_mutex_lock(&cs_mutex);

	// wait for refilling if in process
	pthread_mutex_lock(&asset_refill_mutex);
	// remove from refilling list immediately
	if (asset == asset_waiting_refill) {
		asset_waiting_refill = NULL;
	}
	pthread_mutex_unlock(&asset_refill_mutex);

	this->discardCorrespondingSoundHandles(asset, true);
	assetLoader->unregisterAsset(asset);
	KLBOpenSLSoundAsset* asset_candidate = NULL;
	for (int i = 0; i < MAX_SOUND_ASSETS; ++i)
	{
		if (soundAssets[i] == asset)
		{
			DEBUG_PRINT("discarded asset idx=%d", i);
			soundAssets[i] = NULL;
			break;
		}
	}
	pthread_mutex_unlock(&cs_mutex);
}

KLBOpenSLSoundHandle* KLBOpenSLEngine::assignSoundHandle(KLBOpenSLSoundAsset *pAsset) {
	int dequeue_candidate = -1;
	s64 dequeue_candidate_start_at = 9223372036854775807LL;
	pthread_mutex_lock(&cs_mutex);
	KLBOpenSLSoundHandle** handle;
	if (!pAsset->isSE()) {
		// try to reuse sound-handle for BGM
		for (int i = 0; i < MAX_SOUND_HANDLE; ++i)
		{
			handle = soundHandles + i;
			if (*handle != NULL && (*handle)->isInitiated() && (*handle)->getSoundAsset() == pAsset) {
				return *handle;
			}
		}
	}
	for (int i = 0; i < MAX_SOUND_HANDLE; ++i)
	{
		handle = soundHandles + i;
		if (*handle == NULL)
		{
			// DEBUG_PRINT("assigning new sound handle: %d", i);
			*handle = new KLBOpenSLSoundHandle();
			dequeue_candidate = -1;
			break;
		}
		else if ((*handle)->isInitiated() && (*handle)->getSoundAsset()->isFullyBuffered() && !(*handle)->isPlaying())
		{
			// DEBUG_PRINT("reusing handle pointer: %d", i);
			dequeue_candidate = -1;
			break;
		}
		else
		{
			// TODO: prioritize. BGM > single SE > multi SE
			if ((*handle)->getSoundAsset()->isFullyBuffered() && (*handle)->getTimeStarted() < dequeue_candidate_start_at) {
				dequeue_candidate_start_at = (*handle)->getTimeStarted();
				dequeue_candidate = i;
				// DEBUG_PRINT("deque candidate updated: %d", dequeue_candidate);
			}
		}
	}
	if (dequeue_candidate != -1) {
		// DEBUG_PRINT("deque&reassign: %d", dequeue_candidate);
		handle = soundHandles + dequeue_candidate;
		(*handle)->stop();
	}

	(*handle)->setSoundAsset(pAsset);
	pthread_mutex_unlock(&cs_mutex);
	return *handle;
}

