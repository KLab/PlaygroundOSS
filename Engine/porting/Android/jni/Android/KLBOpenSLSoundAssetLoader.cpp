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
#include "KLBOpenSLAudioPlayer.h"
#include "CAndroidPathConv.h"
#include "ivorbisfile.h"
#include <unistd.h>

KLBOpenSLSoundAssetLoader::KLBOpenSLSoundAssetLoader()
{
	assets = (KLBOpenSLSoundAsset**) calloc(KLBOpenSLEngine::MAX_SOUND_ASSETS, sizeof(KLBOpenSLSoundAsset**));
}

KLBOpenSLSoundAssetLoader::~KLBOpenSLSoundAssetLoader()
{
	stopObservation();
	free(assets);
}

KLBOpenSLSoundAsset* KLBOpenSLSoundAssetLoader::openFile(char const *path, bool isFullBuffered)
{
    // DEBUG_PRINT("AUDIO; openFile");
    // DEBUG_PRINT("path: %s", path);
    const char* target_path = CAndroidPathConv::getInstance().fullpath(path, ".ogg");
	KLBOpenSLSoundAsset* asset = NULL;
	if (access(target_path, F_OK) != -1) {
		asset = new KLBOpenSLSoundAsset(path, isFullBuffered);
	}
	delete [] target_path;
	return asset;
}

void KLBOpenSLSoundAssetLoader::startObservation() {
	if (observationThread == NULL)
	{
		observationThread = CPFInterface::getInstance().platform().createThread(KLBOpenSLSoundAssetLoader::FileObservationThreadParam, this);
	}
}

int KLBOpenSLSoundAssetLoader::FileObservationThreadParam(void * hThread, void * data)
{
	KLBOpenSLSoundAssetLoader* me = (KLBOpenSLSoundAssetLoader*)data;
	while( 1 )
	{
		for (int i = 0; i < KLBOpenSLEngine::MAX_SOUND_ASSETS; ++i)
		{
			// TODO: reuse unregistered assets
			KLBOpenSLSoundAsset* targetPtr = *(me->assets + i);
			if (targetPtr != NULL)
			{
				// DEBUG_PRINT("targetPtr: %d", targetPtr);
			}
		}

		usleep(30000); // sleep for 30ms
	}

	return 0; // exit
}

void KLBOpenSLSoundAssetLoader::registerAsset(KLBOpenSLSoundAsset *pAsset) {
	for (int i = 0; i < KLBOpenSLEngine::MAX_SOUND_ASSETS; ++i)
	{
		// TODO: reuse unregistered assets
		KLBOpenSLSoundAsset* targetPtr = *(assets + i);
		if (targetPtr == NULL)
		{
			targetPtr = pAsset;
			return;
		}
	}
	// buffer queue is full
	// TODO: remove unused asset from memory and retry
}

void KLBOpenSLSoundAssetLoader::stopObservation() {
	if (observationThread != NULL)
	{
		CPFInterface::getInstance().platform().deleteThread(observationThread);
		observationThread = NULL;
	}
}

void KLBOpenSLSoundAssetLoader::unregisterAsset(KLBOpenSLSoundAsset *pAsset) {
	for (int i = 0; i < KLBOpenSLEngine::MAX_SOUND_ASSETS; ++i)
	{
		// TODO: reuse unregistered assets
		KLBOpenSLSoundAsset* targetPtr = *(assets + i);
		if (targetPtr != NULL && targetPtr == pAsset)
		{
			targetPtr = NULL;
			return;
		}
	}
	// pointer not found
	// TODO: error handling
}

