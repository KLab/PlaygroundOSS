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
#include "AudioAsset.h"
#include "CPFInterface.h"

// #######################################################
//   Asset Instance
// #######################################################

CKLBAudioAsset::CKLBAudioAsset()
: CKLBAbstractAsset ()
, m_resName         (NULL)
, m_handle          (NULL)
{
}

CKLBAudioAsset::~CKLBAudioAsset()
{
	if (m_handle) {
		release();
		m_handle = NULL;
	}
}

bool CKLBAudioAsset::init(const char* url) {
	m_handle = CPFInterface::getInstance().platform().loadAudio(url, true);
	return m_handle != NULL;
}

bool CKLBAudioAsset::preLoad() {
	klb_assert(m_handle, "Audio data is not init()");
	return CPFInterface::getInstance().platform().preLoad(m_handle);
}

void CKLBAudioAsset::play(float volume) {
	klb_assert(m_handle, "Audio data is not init()");
	CPFInterface::getInstance().platform().playAudio(m_handle,10000000,volume,volume);
}

void CKLBAudioAsset::stop() {
	klb_assert(m_handle, "Audio data is not init()");
	CPFInterface::getInstance().platform().stopAudio(m_handle);
}

void CKLBAudioAsset::release() {
	klb_assert(m_handle, "Audio data is not init()");
	CPFInterface::getInstance().platform().releaseAudio(m_handle);
}

// #######################################################
//   Asset Manager
// #######################################################

KLBAudioAssetPlugin::KLBAudioAssetPlugin():
	IKLBAssetPlugin	()
{
}

KLBAudioAssetPlugin::~KLBAudioAssetPlugin()
{
}

/*virtual*/
CKLBAbstractAsset*	KLBAudioAssetPlugin::loadAsset(u8* /*stream*/, u32 /*streamSize*/) {
	klb_assertAlways("loadAsset not support with KLBAudioAssetPlugin, please use loadByFileName instead.");
	return NULL;
}

/*virtual*/
CKLBAbstractAsset*	KLBAudioAssetPlugin::loadByFileName(const char* url) {
	CKLBAudioAsset* pAudioAsset = KLBNEW(CKLBAudioAsset);
	if (pAudioAsset) {
		if (pAudioAsset->init(url)) {
			return pAudioAsset;
		}
		KLBDELETE(pAudioAsset);
	}
	return NULL;
}
