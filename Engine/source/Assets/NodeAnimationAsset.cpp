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
#include "NodeAnimationAsset.h"

CKLBNodeAnimationAsset::CKLBNodeAnimationAsset()
:CKLBAsset		()
{
	// Nothing to do.
}

CKLBNodeAnimationAsset::~CKLBNodeAnimationAsset() {
	// Nothing to do.
}

CKLBNode* CKLBNodeAnimationAsset::createSubTree(u32 /*priority*/) {
	CKLBSplineNode* pNode = KLBNEW(CKLBSplineNode);
	if (pNode) {
		pNode->setAnimation(this->m_length,
							this->m_timeShift,
							this->m_type ? this->m_type : 1,
							NULL,
							0,
							this->m_mask,
							this->m_param);
	}
	return pNode;
}

KLBBlendAnimationAssetPlugin::KLBBlendAnimationAssetPlugin() {
	// Do nothing.
}

KLBBlendAnimationAssetPlugin::~KLBBlendAnimationAssetPlugin() {
	// Do nothing.
}

CKLBNodeAnimationAsset* CKLBNodeAnimationAsset::load(u8* stream, u32 /*streamSize*/) {
	m_type		= (stream[0]<<8) + stream[1];
	m_length	= (stream[2]<<24) | (stream[3] << 16) | (stream[4] << 8) | (stream[5]);
	m_timeShift	= (stream[6]<<24) | (stream[7] << 16) | (stream[8] << 8) | (stream[9]);
	stream += 10;
	m_mask		= (stream[0]<<24) | (stream[1] << 16) | (stream[2] << 8) | (stream[3]);
	stream += 4;
	int count = *stream++;
	for (int n = 0; n<count; n++) {
		// 16.16 fixed -> float
		m_param[n] = ((stream[0]<<24) | (stream[1] << 16) | (stream[2] << 8) | (stream[3])) / 65536.0f;
		stream += 4;
	}
	return this;
}

CKLBAbstractAsset* KLBBlendAnimationAssetPlugin::loadAsset(u8* stream, u32 streamSize) {
	CKLBNodeAnimationAsset* pNewAsset = KLBNEW(CKLBNodeAnimationAsset);
	if (pNewAsset) {
		if (pNewAsset->load(stream, streamSize)) {
			// OK
			return pNewAsset;
		}
		KLBDELETE(pNewAsset); // Fail
	}
	return NULL;
}
