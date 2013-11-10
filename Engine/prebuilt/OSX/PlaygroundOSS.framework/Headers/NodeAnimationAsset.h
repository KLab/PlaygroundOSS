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
#ifndef __SPLINEANIM_ASSET__
#define __SPLINEANIM_ASSET__

#include "CKLBSplineNode.h"
class KLBBlendAnimationAssetPlugin;

class CKLBNodeAnimationAsset : public CKLBAsset {
	friend class CKLBAnimationNode;
	friend class KLBBlendAnimationAssetPlugin;
public:
	CKLBNodeAnimationAsset();
	~CKLBNodeAnimationAsset();

	virtual CKLBNode*	createSubTree	(u32 priority = 0);
	virtual u32			getClassID		()		{ return CLS_ASSETNODEANIM;	}
	virtual	ASSET_TYPE	getAssetType	()		{ return ASSET_NODEANIM;	}
protected:
	CKLBNodeAnimationAsset* load(u8* stream, u32 streamSize);

	s32					m_length;
	s32					m_timeShift;
	u16					m_type;
	u32					m_mask;
	float				m_param[16];
};

/*!
* \class KLBBlendAnimationAssetPlugin
* \brief Blend Animation Asset Plugin
* 
* KLBBlendAnimationAssetPlugin is in charge of loading CKLBNodeAnimationAsset.
*/
class KLBBlendAnimationAssetPlugin : public IKLBAssetPlugin {
public:
	KLBBlendAnimationAssetPlugin();
	~KLBBlendAnimationAssetPlugin();

	virtual u32					getChunkID		()			{ return CHUNK_TAG('A','N','I','M');	}
	virtual	u8					charHeader		()			{ return 'a';							}
	virtual const char*			fileExtension	()			{ return ".anim";						}

	virtual CKLBAbstractAsset*	loadAsset		(u8* stream, u32 streamSize);
};

#endif
