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
#ifndef __KLB_AUDIO_ASSET__
#define __KLB_AUDIO_ASSET__

#include "CKLBAsset.h"

/*!
* \class CKLBAudioAsset
* \brief Audio Asset Class
* 
* Wrapper for audio object given by porting layer.
*/
class CKLBAudioAsset : public CKLBAbstractAsset {
public:
	virtual u32			getClassID	()		{ return CLS_ASSETAUDIO; }
	virtual	ASSET_TYPE	getAssetType()		{ return ASSET_AUDIO;    }

	CKLBAudioAsset();
	~CKLBAudioAsset();

	bool init	(const char* url);
	bool preLoad();
	void play	(float volume = 1.0f);
	void stop	();
	void release();
private:
	char*	m_resName;
	void*	m_handle;
};

/*!
* \class KLBAudioAssetPlugin
* \brief Audio Asset Plugin Class
* 
* KLBAudioAssetPlugin is in charge of loading CKLBAudioAsset.
*/
class KLBAudioAssetPlugin : public IKLBAssetPlugin {
public:
	KLBAudioAssetPlugin();
	~KLBAudioAssetPlugin();

	virtual u32					getChunkID		()				{ return CHUNK_TAG('A','U','D','I'); }
	virtual	u8					charHeader		()				{ return 'A';			}
	virtual const char*			fileExtension	()				{ return ".audio"; }

	virtual CKLBAbstractAsset*	loadAsset		(u8* stream, u32 streamSize);
	virtual CKLBAbstractAsset*	loadByFileName	(const char* fileName);
};

#endif
