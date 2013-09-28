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
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "KLBOpenSLAudioPlayer.h"
#include "CAndroidRequest.h"

KLBOpenSLSoundHandle::KLBOpenSLSoundHandle() :
is_initiated(false),
is_loop_requested(false),
cur_mbel(-1)
{
	buf_fill_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

KLBOpenSLSoundHandle::~KLBOpenSLSoundHandle()
{
	// performing lock for sure (dtor could be called under playing status)
	pthread_mutex_lock(&buf_fill_lock);
	DEBUG_PRINT("AUDIO; destroying sound-handle");
	destroyOpenSLObjects();
	is_destroyed = true;
	pthread_mutex_unlock(&buf_fill_lock);
	pthread_mutex_destroy(&buf_fill_lock);
}

void KLBOpenSLSoundHandle::initInternalResources() {
	consumed_pos = 0;
	head_bufsize = 0;
	is_playing = false;
	is_initiated = false;
	is_destroyed = false;
	state = 0;
	volume = 1.0f;
	m_interruptionType = KLBOpenSLEngine::eINTERRUPTION_TYPE_NONE;
	fade_param.m_fadeCnt = 0;
	fade_param.m_startVol = 1.0f;
	fade_param.m_endVol = 1.0f;
	fade_param.m_fadeRatio = 1.0f;
	fade_param.m_fadeMiliSec = 0;
	fade_param.m_nowFadeInterType = INTER_TYPE_NONE;
	fade_param.m_nowFadeType = FADE_TYPE_NONE;
	fade_param.m_bfade = false;
	fade_param.m_prevmseq = 0;
	last_error = 0;
}

void KLBOpenSLSoundHandle::destroyOpenSLObjects() {
	if (bqPlayerObject != NULL)
	{
		if (bqPlayerPlay != NULL) {
			stop();
		}
		(*bqPlayerObject)->Destroy(bqPlayerObject);
		bqPlayerObject = NULL;
		bqPlayerPlay = NULL;
		bqPlayerBufferQueue = NULL;
		bqPlayerVol = NULL;
	}
}

void KLBOpenSLSoundHandle::play(int _msec, float _tgtVol, float _startVol)
{
	SLresult result;
	time_elapsed = 0;
	consumed_pos = 0;
	assert(bqPlayerPlay != NULL);
	result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
	assert(SL_RESULT_SUCCESS == result);
	fade_param.m_fadeRatio = (_startVol < 0.0f) ? (0.0f) : ((_startVol > 1.0f) ? 1.0f : _startVol);
	if( _msec > 0 ) {
		setFadeParam(FADE_TYPE_PLAY, _tgtVol, _msec, INTER_TYPE_LINEAR, _startVol);
	}
	refreshVolume();
	fillPcmBuffer(bqPlayerBufferQueue, true);
    state = IClientRequest::E_SOUND_STATE_PLAY;
	if (KLBOpenSLEngine::getInstance()->isSoundPaused()) {
		this->pause();
		this->setInterruptionType(KLBOpenSLEngine::eINTERRUPTION_TYPE_RESIGN_ACTIVE);
	}
}

void KLBOpenSLSoundHandle::stop(int _msec, float _tgtVol)
{
	SLresult result;
	if( _msec <= 0 ) {
		if (state == IClientRequest::E_SOUND_STATE_PLAY) {
			DEBUG_PRINT("stop sound handle");
			assert(bqPlayerPlay != NULL);
			result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_STOPPED);
			assert(SL_RESULT_SUCCESS == result);
		}
		if (bqPlayerBufferQueue != NULL) {
			result = (*bqPlayerBufferQueue)->Clear(bqPlayerBufferQueue);
			assert(SL_RESULT_SUCCESS == result);
		}
		time_elapsed = 0;
		consumed_pos = 0;
		state = IClientRequest::E_SOUND_STATE_STOP;
	} else {
   		setFadeParam(FADE_TYPE_STOP, _tgtVol, _msec, INTER_TYPE_LINEAR, 0.0f);
	}
}

void KLBOpenSLSoundHandle::pause(int _msec, float _tgtVol)
{
    if (state == IClientRequest::E_SOUND_STATE_PLAY) {
    	if( _msec <= 0 ) {
			SLresult result;
			assert(bqPlayerPlay != NULL);
			result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PAUSED);
			assert(SL_RESULT_SUCCESS == result);
			time_elapsed += CAndroidRequest::getInstance()->nanotime() - time_started;
			state = IClientRequest::E_SOUND_STATE_PAUSE;
    	} else {
    		setFadeParam(FADE_TYPE_PAUSE, _tgtVol, _msec, INTER_TYPE_LINEAR, 0.0f);
    	}
	}
}

void KLBOpenSLSoundHandle::resume(int _msec, float _tgtVol)
{
    if (state == IClientRequest::E_SOUND_STATE_PAUSE) {
		SLresult result;
		assert(bqPlayerPlay != NULL);
		result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
		assert(SL_RESULT_SUCCESS == result);
		state = IClientRequest::E_SOUND_STATE_PLAY;
		if( _msec > 0 ) {
			setFadeParam(FADE_TYPE_RESUME, _tgtVol, _msec, INTER_TYPE_LINEAR, 0.0f);
		}
		refreshVolume();
		updateTimeStarted();
	}
}

s32 KLBOpenSLSoundHandle::tellAudio()
{
	s32 elapsed_sysclock_ms = 0;
	if (isPlaying()) {
		elapsed_sysclock_ms = (s32)((CAndroidRequest::getInstance()->nanotime() - time_started + time_elapsed) / 1000000);
	}
	else {
		elapsed_sysclock_ms = (s32)((time_elapsed) / 1000000);
	}
	SLresult result;
	SLmillisecond msec;
	// DEBUG_PRINT("before GetPosition");
	result = (*bqPlayerPlay)->GetPosition(bqPlayerPlay, &msec);
	assert(SL_RESULT_SUCCESS == result);
	// DEBUG_PRINT("after GetPosition");
	s32 ts_error = msec - elapsed_sysclock_ms;
	s32 ts_adj = (ts_error - last_error) >> 2;
	// DEBUG_PRINT("tellAudio ts_error=%d. diff delta=%d, adj=%d", ts_error, ts_error - last_error, ts_adj);
	last_error += ts_adj;
	return elapsed_sysclock_ms + last_error;
}

void KLBOpenSLSoundHandle::closeAudio()
{

}

void KLBOpenSLSoundHandle::setVolume(float volume)
{
	KLBOpenSLSoundHandle::volume = volume;
	refreshVolume();
}

void KLBOpenSLSoundHandle::refreshVolume() {
	if (bqPlayerVol != NULL) {
		float actual_volume = KLBOpenSLEngine::getInstance()->GetMasterVolume(this->asset->isSE()) * fade_param.m_fadeRatio * volume;
		SLmillibel max_mbel = 0;
		int res = (*bqPlayerVol)->GetMaxVolumeLevel(bqPlayerVol, &max_mbel);
		assert(SL_RESULT_SUCCESS == res);
		SLmillibel mbel = gain_to_attenuation(actual_volume, max_mbel);
		if (mbel != cur_mbel) {
			DEBUG_PRINT("AUDIO; setting new volume: %f(%x), isSE=%d, masterVolume=%f, fadeRatio=%f, volume=%f",
				actual_volume, mbel, this->asset->isSE(),
				KLBOpenSLEngine::getInstance()->GetMasterVolume(this->asset->isSE()), fade_param.m_fadeRatio, volume);
			res = (*bqPlayerVol)->SetVolumeLevel(bqPlayerVol, mbel);
			assert(SL_RESULT_SUCCESS == res);
			cur_mbel = mbel;
		}
	}
}

void KLBOpenSLSoundHandle::updateFadeParam() {
	s64 nowSeq = 0;

	if ((fade_param.m_bfade == false) && (fade_param.m_nowFadeType != FADE_TYPE_NONE))
	{
		fade_param.m_bfade = true;
		fade_param.m_prevmseq = tellAudio();
		// DEBUG_PRINT("[sound] fade start!");
	}
	if (fade_param.m_bfade)
	{
		nowSeq = tellAudio();

		// フェードカウントインクリメント
		fade_param.m_fadeCnt += (nowSeq - fade_param.m_prevmseq);
		if (fade_param.m_fadeCnt >= fade_param.m_fadeMiliSec) {
			fade_param.m_fadeCnt = fade_param.m_fadeMiliSec;
		} else if (fade_param.m_fadeCnt < 0) {
			fade_param.m_fadeCnt = 0;
		}

		// 係数計算
		if (fade_param.m_fadeCnt >= 0 && fade_param.m_fadeMiliSec > 0)
		{
			fade_param.m_fadeRatio = fade_param.m_startVol + ((fade_param.m_endVol - fade_param.m_startVol) * ((float)fade_param.m_fadeCnt / (float)fade_param.m_fadeMiliSec));
			if (fade_param.m_fadeRatio < 0.0f) {
				fade_param.m_fadeRatio = 0.0f;
			} else if (fade_param.m_fadeRatio > 1.0f) {
				fade_param.m_fadeRatio = 1.0f;
			}
		}

		// サウンドに大して設定
		refreshVolume();

		// フェード終了の確認
		if (fade_param.m_fadeCnt >= fade_param.m_fadeMiliSec)
		{
			fade_param.m_fadeCnt = fade_param.m_fadeMiliSec;
			fade_param.m_bfade = false;

			if (fade_param.m_nowFadeType == FADE_TYPE_STOP)
			{
				DEBUG_PRINT("[sound] fade -> stopped");
				stop();
			}
			else if (fade_param.m_nowFadeType == FADE_TYPE_PAUSE)
			{
				DEBUG_PRINT("[sound] fade -> paused");
				pause();
			}
			fade_param.m_nowFadeType = FADE_TYPE_NONE;
		}

		fade_param.m_prevmseq = tellAudio();
	}
}

bool KLBOpenSLSoundHandle::setFadeParam(s16 _fadeType, float _tgtVol, u32 _msec, s16 _interType, float _startVolume)
{
	if (_startVolume < 0.0f) {
		_startVolume = 0.0f;
	}
	else if (1.0f < _startVolume) {
		_startVolume = 1.0f;
	}
	if (_msec <= 0 || _fadeType >= FADE_TYPE_NUM || _fadeType <= FADE_TYPE_NONE) {
		// フェードしないため初期化
		fade_param.m_nowFadeType = INTER_TYPE_NONE;
		fade_param.m_nowFadeType = FADE_TYPE_NONE;
		fade_param.m_endVol = 0.0f;
		fade_param.m_fadeCnt = 0;
		fade_param.m_fadeRatio = 1.0f;
		fade_param.m_fadeMiliSec = 0;
		fade_param.m_bfade = false;
		fade_param.m_prevmseq = 0;
		return true;
	}

	fade_param.m_fadeCnt = 0;
	fade_param.m_endVol = _tgtVol;
	fade_param.m_nowFadeType = _fadeType;
	fade_param.m_nowFadeInterType = _interType;
	switch (_fadeType) {
		case FADE_TYPE_PLAY:
		case FADE_TYPE_RESUME:
			fade_param.m_startVol = _startVolume;
			fade_param.m_fadeRatio = _startVolume;
			break;

		case FADE_TYPE_STOP:
		case FADE_TYPE_PAUSE:
		case FADE_TYPE_PLAYING:
			fade_param.m_startVol = 1.0f;
			break;
	}
	fade_param.m_fadeMiliSec = _msec;
	fade_param.m_bfade = false;
	fade_param.m_prevmseq = 0;
	return true;
}

void KLBOpenSLSoundHandle::setPan(float pan)
{

}

void KLBOpenSLSoundHandle::setSoundAsset(KLBOpenSLSoundAsset *asset) {
	// destroy current OpenSL related objects if nb-channel or sampling-rate is not equal to prior sample
	if (is_initiated) {
		if (asset->getChannels() == this->pcm_channels && asset->getPcmSamplingRate() == this->pcm_sampling_rate) {
			// shortcut. simply change asset reference and initialize sound handle internal data
			DEBUG_PRINT("reusing most OpenSL stuff");
			updateAsset(asset);
			initInternalResources();
			is_initiated = true;
			return;
		}
		else {
			destroyOpenSLObjects();
		}
	}

	initInternalResources();
	updateAsset(asset);
	SLEngineItf engine = KLBOpenSLEngine::getInstance()->engineEngine;
	SLresult result;
	SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
	SLDataFormat_PCM format_pcm = {
			SL_DATAFORMAT_PCM, this->getPcmChannels(), this->getSlSamplingRate(),
			this->getSlSampleFormat(), this->getSlSampleFormat(),
			this->getSlChannelMask(), SL_BYTEORDER_LITTLEENDIAN};
	SLDataSource audioSrc = {&loc_bufq, &format_pcm};

	// configure audio sink
	SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, KLBOpenSLEngine::getInstance()->outputMixObject};
	SLDataSink audioSnk = {&loc_outmix, NULL};

	// create audio player
	const SLInterfaceID ids[2] = {SL_IID_VOLUME, SL_IID_BUFFERQUEUE};
	const SLboolean req[2] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
	result = (*engine)->CreateAudioPlayer(engine, &bqPlayerObject, &audioSrc, &audioSnk, 2, ids, req);
	assert(SL_RESULT_SUCCESS == result);

	// realize the player
	result = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
	assert(SL_RESULT_SUCCESS == result);

	// get the play interface
	result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerPlay);
	assert(SL_RESULT_SUCCESS == result);

	// get the buffer queue interface
	result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE,
			&bqPlayerBufferQueue);
	assert(SL_RESULT_SUCCESS == result);

	// register callback on the buffer queue
	result = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, KLBOpenSLSoundHandle::bqPlayerCallback, this);
	assert(SL_RESULT_SUCCESS == result);

	// get the volume interface
	result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_VOLUME, &bqPlayerVol);
	assert(SL_RESULT_SUCCESS == result);

	is_initiated = true;
}

void KLBOpenSLSoundHandle::bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context)
{
	KLBOpenSLSoundHandle* soundHandle = (KLBOpenSLSoundHandle*)context;
	if (soundHandle != NULL) {
		soundHandle->fillPcmBuffer(bq, false);
	}
}

void KLBOpenSLSoundHandle::fillPcmBuffer(SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue, bool is_starting) {
	pthread_mutex_lock(&buf_fill_lock);
	if (is_destroyed) {
		DEBUG_PRINT("called after object discarded");
		pthread_mutex_unlock(&buf_fill_lock);
		return;
	}
	SLresult result;
	asset->fetchNextPcmBuffer(this);
	if (head_bufsize == 0)
	{
		DEBUG_PRINT("AUDIO; playback finished");
		// set the player's state to playing
		if (!asset->isSE())
		{
			if (!is_loop_requested) {
				DEBUG_PRINT("requesting loop");
				is_loop_requested = true;
				pthread_mutex_unlock(&buf_fill_lock);
				return;
			}
			else {
				DEBUG_PRINT("AUDIO; BGM loop detected. rebuffering");
				asset->resetBuffer();
				asset->readVorbisSamples(-1);
				consumed_pos = 0;
				asset->fetchNextPcmBuffer(this);
			}
		}
		else if (repeatMode == KLBOpenSLSoundAsset::ONCE || true)
		{
			this->stop();
			pthread_mutex_unlock(&buf_fill_lock);
			return;
		}
		else
		{
			consumed_pos = 0;
			pthread_mutex_unlock(&buf_fill_lock);
			return;
		}
	}
	// DEBUG_PRINT("AUDIO; enqueue PCM buffer (addr=%d, size=%d)", (int)current_head, head_bufsize);
	// enqueue another buffer
	int bufsize_former = head_bufsize, bufsize_latter = 0;
	if ((is_starting || is_loop_requested) && !asset->isSE()) {
		DEBUG_PRINT("AUDIO; separating buffer queue");
		// separate bufqueue
		bufsize_former >>= 1;
		bufsize_latter = head_bufsize - bufsize_former;
	}
	result = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, current_head, bufsize_former);
	assert(SL_RESULT_SUCCESS == result);
	if (bufsize_latter != 0) {
		DEBUG_PRINT("AUDIO; enqueuing second buffer");
		result = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, (short*)((int)current_head + bufsize_former), bufsize_latter);
		assert(SL_RESULT_SUCCESS == result);
	}
    if (is_starting) {
    	updateTimeStarted();
    }

	if (!asset->isFullyBuffered())
	{
		// DEBUG_PRINT("AUDIO; not a full buffer");
		KLBOpenSLEngine::getInstance()->registerAssetForRefilling(asset);
	}
	if (is_loop_requested) {
		is_loop_requested = false;
	}
	pthread_mutex_unlock(&buf_fill_lock);
	return;
}
