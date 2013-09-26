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
// PlayerCPP.cpp : Defines the entry point for the console application.
//
#include "CKLBSWFPlayer.h"
#include "CKLBObject.h"
#include "CKLBRendering.h"
#include "mem.h"
#include "Message.h"
#include "CKLBUtility.h"

// ================================================================================
//   Asset Plugin.
// ================================================================================

KLBFlashAssetPlugin::KLBFlashAssetPlugin()
: IKLBAssetPlugin()
{
}

KLBFlashAssetPlugin::~KLBFlashAssetPlugin() {
}

/*virtual*/
CKLBAbstractAsset* KLBFlashAssetPlugin::loadAsset(u8* stream, u32 /*streamSize*/) {
	//
	// Create asset and forward to loader.
	//
	CKLBSWFAsset* pNewAsset = KLBNEW(CKLBSWFAsset);

	if (pNewAsset) {
		if( pNewAsset->LoadData(stream) ) {
    		return pNewAsset;
        } else {
            KLBDELETE( pNewAsset );
        }
	}
	return NULL;
}


// ================================================================================
// Class Construction / Destruction.
// ================================================================================

struct SShape {
	u16 shapeID;
	u16 styleCount;
	u16	indexCount;
	u16 vertexCount;
	u8	styleType;

	u32	indexBuffer;
	u32	XYBuffer;
	u32 UVBuffer;
	u32 fillColor;
	CTexture*       texture;
	CTextureUsage*  textureUsage;
};

struct SSound {
	void*			handle;
	u32				nameIdx;
	const char*		name;

};

CKLBSWFAsset::CKLBSWFAsset()
:CKLBAsset()
,m_aConstants			(NULL)
,m_aChars				(NULL)
,m_aMatrixData			(NULL)
,m_aMatrixType			(NULL)
,m_aMatrixDataIndex		(NULL)
,m_aStreamInstruction	(NULL)
,m_aMovieInfo			(NULL)
,m_alistCacheEntries	(NULL)
,m_parentSWF			(NULL)
,m_aBitmapLoaded		(NULL)
,m_subAssets			(NULL)
,m_pIndex				(NULL)
,m_shapes				(NULL)
,m_sounds				(NULL)
,m_isMaster				(false)
,m_msPerFrame			(41)	// around 24 fps default.
,m_uiMovieCount			(0)	
,m_uiShapeCount			(0)
,m_uiSoundCount			(0)
{
}

CKLBSWFAsset::~CKLBSWFAsset() {
	if (m_aConstants)			{	KLBDELETEA(m_aConstants);			m_aConstants			= NULL;	}
	if (m_aChars)				{	KLBDELETEA(m_aChars);				m_aChars				= NULL;	}
	if (m_aMatrixData)			{	KLBDELETEA(m_aMatrixData);			m_aMatrixData			= NULL;	}
	if (m_aMatrixType)			{	KLBDELETEA(m_aMatrixType);			m_aMatrixType			= NULL;	}
	if (m_aMatrixDataIndex)		{	KLBDELETEA(m_aMatrixDataIndex);	    m_aMatrixDataIndex		= NULL;	}
	if (m_aStreamInstruction)	{	KLBDELETEA(m_aStreamInstruction);	m_aStreamInstruction	= NULL;	}
	if (m_alistCacheEntries)	{	
		for (u32 n=0; n < m_uiMovieCount; n++) {
			SCacheEntry* pList = m_alistCacheEntries[n];
			while (pList) {
				SCacheEntry* pNext = pList->m_next;
				// Kill subtree
				KLBDELETE(pList->m_cacheNode);
				// Kill Entry
				KLBDELETE(pList);
				pList = pNext;
			}
		}
		KLBDELETEA(m_alistCacheEntries);	m_alistCacheEntries		= NULL; 
	}
	if (m_aMovieInfo)			{	KLBDELETEA(m_aMovieInfo);			m_aMovieInfo			= NULL;	}
	if (m_pIndex)				{	KLBDELETEA(m_pIndex);				m_pIndex				= NULL; }
	if (m_shapes)				{
		CKLBOGLWrapper& pMgr	= CKLBOGLWrapper::getInstance();

		for (u32 n = 0; n < this->m_uiShapeCount; n++) {
			if (m_shapes[n].textureUsage) {
				m_shapes[n].texture->releaseUsage(m_shapes[n].textureUsage);
			}

			if (m_shapes[n].texture) {
				pMgr.releaseTexture(m_shapes[n].texture);
			}
		}
		KLBDELETEA(m_shapes);				
		m_shapes = NULL; 
	}
	
	if (m_sounds) {
		for (u32 n = 0; n < this->m_uiSoundCount; n++) {
			CPFInterface::getInstance().platform().releaseAudio(m_sounds[n].handle);
		}
		KLBDELETEA(m_sounds);
	}
	
	if (m_isMaster) {
		CKLBSWFAsset* pList = m_subAssets;
		while (pList) {
			CKLBSWFAsset* pListNext = pList->m_subAssets;
			KLBDELETE(pList);
			pList = pListNext;
		}
	}

	if (m_aBitmapLoaded) {
		for (u32 n = 0; n < m_uiMovieCount; n++) {
			if (m_aBitmapLoaded[n]) {
				m_aBitmapLoaded[n]->getTexture()->decrementRefCount();
				m_aBitmapLoaded[n] = NULL;
			}
		}
		KLBDELETEA(m_aBitmapLoaded);
		m_aBitmapLoaded = NULL;
	}
}

// ================================================================================
// Player Implementation
// ================================================================================

// ##########################################
//
//   Player
//
// ##########################################


#define READU8P(p)	(*p++)
#define READU16P(p)	((p[0]<<8)   | p[1]); p += 2
#define READU32P(p)	((p[0]<<24)  | (p[1]<<16) | (p[2]<<8) | p[3]); p += 4
#define READFLP(p)	(((p[0]<<24) | (p[1]<<16) | (p[2]<<8) | p[3])/65536.0f); p += 4


u32 globalTmpTable[64*64];
u32 globalPalette[64];

static const u8 ROMCircleLookup[64*64] = {
	63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,62,62,62,62,62,61,61,62,62,62,62,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,62,62,61,61,60,60,60,60,60,59,59,60,60,60,60,60,61,61,62,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,62,61,61,60,59,59,58,58,58,58,57,57,57,57,58,58,58,58,59,59,60,61,61,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,62,61,60,59,59,58,57,57,56,56,56,56,55,55,55,55,56,56,56,56,57,57,58,59,59,60,61,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,62,61,60,59,58,57,57,56,55,55,54,54,54,54,53,53,53,53,54,54,54,54,55,55,56,57,57,58,59,60,61,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,63,62,61,60,59,58,57,56,56,55,54,54,53,53,52,52,52,51,51,51,51,52,52,52,53,53,54,54,55,56,56,57,58,59,60,61,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,62,61,60,58,57,56,55,54,54,53,52,52,51,51,50,50,50,49,49,49,49,50,50,50,51,51,52,52,53,54,54,55,56,57,58,60,61,62,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,62,60,59,58,57,56,55,54,53,52,51,50,50,49,49,48,48,48,47,47,47,47,48,48,48,49,49,50,50,51,52,53,54,55,56,57,58,59,60,62,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,61,60,59,57,56,55,54,53,52,51,50,49,48,48,47,47,46,46,45,45,45,45,45,45,46,46,47,47,48,48,49,50,51,52,53,54,55,56,57,59,60,61,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,61,60,58,57,56,55,53,52,51,50,49,48,47,46,46,45,45,44,44,43,43,43,43,43,43,44,44,45,45,46,46,47,48,49,50,51,52,53,55,56,57,58,60,61,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,61,60,58,57,56,54,53,52,51,49,48,47,46,45,45,44,43,43,42,42,41,41,41,41,41,41,42,42,43,43,44,45,45,46,47,48,49,51,52,53,54,56,57,58,60,61,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,62,60,58,57,56,54,53,51,50,49,48,47,45,44,44,43,42,41,41,40,40,39,39,39,39,39,39,40,40,41,41,42,43,44,44,45,47,48,49,50,51,53,54,56,57,58,60,62,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,62,60,59,57,56,54,53,51,50,49,47,46,45,44,43,42,41,40,39,39,38,38,37,37,37,37,37,37,38,38,39,39,40,41,42,43,44,45,46,47,49,50,51,53,54,56,57,59,60,62,63,63,63,63,63,63,63,
	63,63,63,63,63,63,62,61,59,57,56,54,53,51,50,48,47,46,44,43,42,41,40,39,38,37,37,36,36,35,35,35,35,35,35,36,36,37,37,38,39,40,41,42,43,44,46,47,48,50,51,53,54,56,57,59,61,62,63,63,63,63,63,63,
	63,63,63,63,63,63,61,60,58,56,55,53,51,50,48,47,45,44,43,42,40,39,38,37,36,36,35,34,34,33,33,33,33,33,33,34,34,35,36,36,37,38,39,40,42,43,44,45,47,48,50,51,53,55,56,58,60,61,63,63,63,63,63,63,
	63,63,63,63,63,62,60,58,57,55,53,52,50,49,47,45,44,43,41,40,39,38,36,35,34,34,33,32,32,31,31,31,31,31,31,32,32,33,34,34,35,36,38,39,40,41,43,44,45,47,49,50,52,53,55,57,58,60,62,63,63,63,63,63,
	63,63,63,63,63,61,59,57,56,54,52,51,49,47,46,44,43,41,40,38,37,36,35,34,33,32,31,30,30,29,29,29,29,29,29,30,30,31,32,33,34,35,36,37,38,40,41,43,44,46,47,49,51,52,54,56,57,59,61,63,63,63,63,63,
	63,63,63,63,62,60,58,56,55,53,51,49,48,46,44,43,41,40,38,37,36,34,33,32,31,30,29,28,28,27,27,27,27,27,27,28,28,29,30,31,32,33,34,36,37,38,40,41,43,44,46,48,49,51,53,55,56,58,60,62,63,63,63,63,
	63,63,63,63,61,59,57,55,54,52,50,48,47,45,43,42,40,38,37,35,34,33,31,30,29,28,27,26,26,25,25,25,25,25,25,26,26,27,28,29,30,31,33,34,35,37,38,40,42,43,45,47,48,50,52,54,55,57,59,61,63,63,63,63,
	63,63,63,62,60,58,56,54,53,51,49,47,45,44,42,40,39,37,36,34,33,31,30,29,27,26,25,25,24,23,23,23,23,23,23,24,25,25,26,27,29,30,31,33,34,36,37,39,40,42,44,45,47,49,51,53,54,56,58,60,62,63,63,63,
	63,63,63,61,59,57,56,54,52,50,48,46,44,43,41,39,38,36,34,33,31,30,28,27,26,25,24,23,22,21,21,21,21,21,21,22,23,24,25,26,27,28,30,31,33,34,36,38,39,41,43,44,46,48,50,52,54,56,57,59,61,63,63,63,
	63,63,62,61,59,57,55,53,51,49,47,45,44,42,40,38,36,35,33,31,30,28,27,25,24,23,22,21,20,19,19,19,19,19,19,20,21,22,23,24,25,27,28,30,31,33,35,36,38,40,42,44,45,47,49,51,53,55,57,59,61,62,63,63,
	63,63,62,60,58,56,54,52,50,48,46,45,43,41,39,37,35,34,32,30,29,27,25,24,23,21,20,19,18,18,17,17,17,17,18,18,19,20,21,23,24,25,27,29,30,32,34,35,37,39,41,43,45,46,48,50,52,54,56,58,60,62,63,63,
	63,63,61,59,57,55,54,52,50,48,46,44,42,40,38,36,34,33,31,29,27,26,24,23,21,20,18,17,16,16,15,15,15,15,16,16,17,18,20,21,23,24,26,27,29,31,33,34,36,38,40,42,44,46,48,50,52,54,55,57,59,61,63,63,
	63,63,61,59,57,55,53,51,49,47,45,43,41,39,37,36,34,32,30,28,26,25,23,21,20,18,17,16,14,14,13,13,13,13,14,14,16,17,18,20,21,23,25,26,28,30,32,34,36,37,39,41,43,45,47,49,51,53,55,57,59,61,63,63,
	63,62,60,58,56,54,53,51,49,47,45,43,41,39,37,35,33,31,29,27,25,24,22,20,18,17,15,14,13,12,11,11,11,11,12,13,14,15,17,18,20,22,24,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,54,56,58,60,62,63,
	63,62,60,58,56,54,52,50,48,46,44,42,40,38,36,34,32,30,28,26,25,23,21,19,17,16,14,12,11,10, 9, 9, 9, 9,10,11,12,14,16,17,19,21,23,25,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,63,
	63,62,60,58,56,54,52,50,48,46,44,42,40,38,36,34,32,30,28,26,24,22,20,18,16,14,13,11,10, 8, 7, 7, 7, 7, 8,10,11,13,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,63,
	63,62,60,58,56,54,52,50,48,45,43,41,39,37,35,33,31,29,27,25,23,21,19,18,16,14,12,10, 8, 7, 5, 5, 5, 5, 7, 8,10,12,14,16,18,19,21,23,25,27,29,31,33,35,37,39,41,43,45,48,50,52,54,56,58,60,62,63,
	63,62,60,57,55,53,51,49,47,45,43,41,39,37,35,33,31,29,27,25,23,21,19,17,15,13,11, 9, 7, 5, 4, 3, 3, 4, 5, 7, 9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,60,62,63,
	63,61,59,57,55,53,51,49,47,45,43,41,39,37,35,33,31,29,27,25,23,21,19,17,15,13,11, 9, 7, 5, 3, 1, 1, 3, 5, 7, 9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,
	63,61,59,57,55,53,51,49,47,45,43,41,39,37,35,33,31,29,27,25,23,21,19,17,15,13,11, 9, 7, 5, 3, 1, 1, 3, 5, 7, 9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,
	63,62,60,57,55,53,51,49,47,45,43,41,39,37,35,33,31,29,27,25,23,21,19,17,15,13,11, 9, 7, 5, 4, 3, 3, 4, 5, 7, 9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,60,62,63,
	63,62,60,58,56,54,52,50,48,45,43,41,39,37,35,33,31,29,27,25,23,21,19,18,16,14,12,10, 8, 7, 5, 5, 5, 5, 7, 8,10,12,14,16,18,19,21,23,25,27,29,31,33,35,37,39,41,43,45,48,50,52,54,56,58,60,62,63,
	63,62,60,58,56,54,52,50,48,46,44,42,40,38,36,34,32,30,28,26,24,22,20,18,16,14,13,11,10, 8, 7, 7, 7, 7, 8,10,11,13,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,63,
	63,62,60,58,56,54,52,50,48,46,44,42,40,38,36,34,32,30,28,26,25,23,21,19,17,16,14,12,11,10, 9, 9, 9, 9,10,11,12,14,16,17,19,21,23,25,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,63,
	63,62,60,58,56,54,53,51,49,47,45,43,41,39,37,35,33,31,29,27,25,24,22,20,18,17,15,14,13,12,11,11,11,11,12,13,14,15,17,18,20,22,24,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,54,56,58,60,62,63,
	63,63,61,59,57,55,53,51,49,47,45,43,41,39,37,36,34,32,30,28,26,25,23,21,20,18,17,16,14,14,13,13,13,13,14,14,16,17,18,20,21,23,25,26,28,30,32,34,36,37,39,41,43,45,47,49,51,53,55,57,59,61,63,63,
	63,63,61,59,57,55,54,52,50,48,46,44,42,40,38,36,34,33,31,29,27,26,24,23,21,20,18,17,16,16,15,15,15,15,16,16,17,18,20,21,23,24,26,27,29,31,33,34,36,38,40,42,44,46,48,50,52,54,55,57,59,61,63,63,
	63,63,62,60,58,56,54,52,50,48,46,45,43,41,39,37,35,34,32,30,29,27,25,24,23,21,20,19,18,18,17,17,17,17,18,18,19,20,21,23,24,25,27,29,30,32,34,35,37,39,41,43,45,46,48,50,52,54,56,58,60,62,63,63,
	63,63,62,61,59,57,55,53,51,49,47,45,44,42,40,38,36,35,33,31,30,28,27,25,24,23,22,21,20,19,19,19,19,19,19,20,21,22,23,24,25,27,28,30,31,33,35,36,38,40,42,44,45,47,49,51,53,55,57,59,61,62,63,63,
	63,63,63,61,59,57,56,54,52,50,48,46,44,43,41,39,38,36,34,33,31,30,28,27,26,25,24,23,22,21,21,21,21,21,21,22,23,24,25,26,27,28,30,31,33,34,36,38,39,41,43,44,46,48,50,52,54,56,57,59,61,63,63,63,
	63,63,63,62,60,58,56,54,53,51,49,47,45,44,42,40,39,37,36,34,33,31,30,29,27,26,25,25,24,23,23,23,23,23,23,24,25,25,26,27,29,30,31,33,34,36,37,39,40,42,44,45,47,49,51,53,54,56,58,60,62,63,63,63,
	63,63,63,63,61,59,57,55,54,52,50,48,47,45,43,42,40,38,37,35,34,33,31,30,29,28,27,26,26,25,25,25,25,25,25,26,26,27,28,29,30,31,33,34,35,37,38,40,42,43,45,47,48,50,52,54,55,57,59,61,63,63,63,63,
	63,63,63,63,62,60,58,56,55,53,51,49,48,46,44,43,41,40,38,37,36,34,33,32,31,30,29,28,28,27,27,27,27,27,27,28,28,29,30,31,32,33,34,36,37,38,40,41,43,44,46,48,49,51,53,55,56,58,60,62,63,63,63,63,
	63,63,63,63,63,61,59,57,56,54,52,51,49,47,46,44,43,41,40,38,37,36,35,34,33,32,31,30,30,29,29,29,29,29,29,30,30,31,32,33,34,35,36,37,38,40,41,43,44,46,47,49,51,52,54,56,57,59,61,63,63,63,63,63,
	63,63,63,63,63,62,60,58,57,55,53,52,50,49,47,45,44,43,41,40,39,38,36,35,34,34,33,32,32,31,31,31,31,31,31,32,32,33,34,34,35,36,38,39,40,41,43,44,45,47,49,50,52,53,55,57,58,60,62,63,63,63,63,63,
	63,63,63,63,63,63,61,60,58,56,55,53,51,50,48,47,45,44,43,42,40,39,38,37,36,36,35,34,34,33,33,33,33,33,33,34,34,35,36,36,37,38,39,40,42,43,44,45,47,48,50,51,53,55,56,58,60,61,63,63,63,63,63,63,
	63,63,63,63,63,63,62,61,59,57,56,54,53,51,50,48,47,46,44,43,42,41,40,39,38,37,37,36,36,35,35,35,35,35,35,36,36,37,37,38,39,40,41,42,43,44,46,47,48,50,51,53,54,56,57,59,61,62,63,63,63,63,63,63,
	63,63,63,63,63,63,63,62,60,59,57,56,54,53,51,50,49,47,46,45,44,43,42,41,40,39,39,38,38,37,37,37,37,37,37,38,38,39,39,40,41,42,43,44,45,46,47,49,50,51,53,54,56,57,59,60,62,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,62,60,58,57,56,54,53,51,50,49,48,47,45,44,44,43,42,41,41,40,40,39,39,39,39,39,39,40,40,41,41,42,43,44,44,45,47,48,49,50,51,53,54,56,57,58,60,62,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,61,60,58,57,56,54,53,52,51,49,48,47,46,45,45,44,43,43,42,42,41,41,41,41,41,41,42,42,43,43,44,45,45,46,47,48,49,51,52,53,54,56,57,58,60,61,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,61,60,58,57,56,55,53,52,51,50,49,48,47,46,46,45,45,44,44,43,43,43,43,43,43,44,44,45,45,46,46,47,48,49,50,51,52,53,55,56,57,58,60,61,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,61,60,59,57,56,55,54,53,52,51,50,49,48,48,47,47,46,46,45,45,45,45,45,45,46,46,47,47,48,48,49,50,51,52,53,54,55,56,57,59,60,61,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,62,60,59,58,57,56,55,54,53,52,51,50,50,49,49,48,48,48,47,47,47,47,48,48,48,49,49,50,50,51,52,53,54,55,56,57,58,59,60,62,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,62,61,60,58,57,56,55,54,54,53,52,52,51,51,50,50,50,49,49,49,49,50,50,50,51,51,52,52,53,54,54,55,56,57,58,60,61,62,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,63,62,61,60,59,58,57,56,56,55,54,54,53,53,52,52,52,51,51,51,51,52,52,52,53,53,54,54,55,56,56,57,58,59,60,61,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,62,61,60,59,58,57,57,56,55,55,54,54,54,54,53,53,53,53,54,54,54,54,55,55,56,57,57,58,59,60,61,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,62,61,60,59,59,58,57,57,56,56,56,56,55,55,55,55,56,56,56,56,57,57,58,59,59,60,61,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,62,61,61,60,59,59,58,58,58,58,57,57,57,57,58,58,58,58,59,59,60,61,61,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,62,62,61,61,60,60,60,60,60,59,59,60,60,60,60,60,61,61,62,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,62,62,62,62,62,61,61,62,62,62,62,62,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
	63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,
};

bool CKLBSWFAsset::LoadData(u8* pData) {
	// Asset Name
	int offset = READU16P(pData);
	this->m_pName = allocateName(pData, offset);

	// Skip Name
	pData += offset;

	this->m_msPerFrame			= READU16P(pData);

	//
	// Create String Constant Pool.
	//
	this->m_uiStringCount		= READU16P(pData);
	this->m_uiTotalCharsCount	= READU16P(pData);

	if (this->m_uiStringCount == 0xFFFF) {
		m_uiSoundCount	= READU16P(pData);
		if (m_uiSoundCount != 0) {
			m_sounds = KLBNEWA(SSound, m_uiSoundCount);
			if (m_sounds) {
				memset(m_sounds, 0, m_uiSoundCount * sizeof(SSound));
				for (u32 n=0; n < m_uiSoundCount; n++) {
					m_sounds[n].nameIdx = READU16P(pData);
				}
			} else {
				return false;
			}
		}
		
		// Total Index Buffer
		m_uiIndexTotal	= READU32P(pData);
		m_pIndex		= KLBNEWA(u16, m_uiIndexTotal);
		m_uiShapeCount	= READU16P(pData);

		if (m_pIndex) {
			// Shape Extension
//			m_uiShapeCount	= READU16P(pData);  // 2012.12.19 
			m_shapes		= KLBNEWA(SShape,m_uiShapeCount);
			if (m_shapes) {
				CKLBOGLWrapper& pMgr	= CKLBOGLWrapper::getInstance();

				for (u16 n = 0; n < m_uiShapeCount; n++) {
					m_shapes[n].texture			= NULL;
					m_shapes[n].textureUsage	= NULL;
				}

				for (u16 n = 0; n < m_uiShapeCount; n++) {
					m_shapes[n].shapeID		= READU16P(pData);
					m_shapes[n].styleCount	= READU16P(pData);
					klb_assert(m_shapes[n].styleCount == 1, "Multiple style not supported yet");
					for (int m=0; m < m_shapes[n].styleCount; m++) {
						//
						// Support only one style for now.
						//
						u32 idx = READU32P(pData);
						m_shapes[n].indexBuffer	= idx;
						m_shapes[n].indexCount	= READU16P(pData);

						u32 end = idx + m_shapes[n].indexCount;
						while (idx < end) {
							m_pIndex[idx++] = READU16P(pData);
						}

						m_shapes[n].vertexCount	= READU16P(pData);
						m_shapes[n].XYBuffer	= READU32P(pData);
						m_shapes[n].UVBuffer	= READU32P(pData);

						m_shapes[n].styleType	= READU8P(pData);
						m_shapes[n].texture		= NULL;

						CTexture* pTexture;
						/*
							public const uint TYPE_FILL_COLOR = 1;
							public const uint  = 2;
							public const uint TYPE_RADIAL_GRAD = 3;
						 */
						#define TYPE_BITMAP				(0)
						#define TYPE_FILL_COLOR			(1)
						#define TYPE_LINEAR_GRAD		(2)
						#define TYPE_RADIAL_GRAD		(3)

						switch (m_shapes[n].styleType) {
						case TYPE_LINEAR_GRAD:
							// Linear Gradient.
							pTexture = pMgr.createTexture(	64, 1, 
														GL_UNSIGNED_BYTE, CKLBOGLWrapper::RGBA, 
														pData, 256,
														CKLBOGLWrapper::TEX_NONE);
							pData += 256;
							break;
						case TYPE_RADIAL_GRAD:
							{
								u32* colPtr = globalPalette;
								memcpy(colPtr, pData, 64*4);	// Make sure that colPtr is 32 bit aligned. (casting to pData is dangerous -> unaligned)

								const u8*  src = ROMCircleLookup;
								u32* dst = globalTmpTable;
								u32* end = &globalTmpTable[64*64];
								while (dst < end) {
									*dst++ = colPtr[*src++];
								}

								// Radial Gradient.
								pTexture = pMgr.createTexture(	64, 64, 
															GL_UNSIGNED_BYTE, CKLBOGLWrapper::RGBA, 
															globalTmpTable, 64*64*4,
															CKLBOGLWrapper::TEX_NONE);
								pData += 256;
							}
							break;
						case TYPE_FILL_COLOR:
							pTexture = NULL;
							m_shapes[n].fillColor = READU32P(pData);
							break;
						default:
						case TYPE_BITMAP:
							pTexture = NULL;
							m_shapes[n].fillColor = 0xFFFFFFFF;
						}

						if (pTexture) {
							m_shapes[n].texture = pTexture;

							CTextureUsage*	pUsage = pTexture->createUsage();
							if (pUsage) {
								m_shapes[n].textureUsage = pUsage;
								pUsage->setWrapping(CTextureUsage::CLAMP_TO_EDGE, CTextureUsage::CLAMP_TO_EDGE);
							}
						} else {
							// Do nothing.
						}
					}
				}
			} else {
//				return false;   // 2012.12.19  malloc(0)でNULLを返すと(m_uiIndexTotalが0)の場合ここでfalseを返すと動かないFlashが出てくる
			}
		} else {
//			return false;       // 2012.12.19  malloc(0)でNULLを返すと(m_uiIndexTotalが0)の場合ここでfalseを返すと動かないFlashが出てくる
		}
		
		this->m_uiStringCount = READU16P(pData);
	}

	this->m_aConstants  = KLBNEWA(char*,m_uiStringCount);
	this->m_aChars      = KLBNEWA(char,m_uiTotalCharsCount + m_uiStringCount);

	this->m_isMaster    = true;

	offset = 0;
	if (m_aConstants && m_aChars) {
		//
		// Load String Constant Pool
		//
		for (int n=0; n < m_uiStringCount; n++) {
			this->m_aConstants[n] = &m_aChars[offset];	// C Style unicode string, but size is coded before as pascal style.
			u16 length = READU16P(pData);
			// m_aChars[offset++] = length;
			for (int m = 0; m < length; m++) {
				m_aChars[offset++] = READU8P(pData);
			}
		}

		//
		// Matrix Array Stream
		//
		m_uiMatrixCount = READU32P(pData);
		u32 floatCount  = READU32P(pData);

		m_aMatrixData = KLBNEWA(float,floatCount);

		if (m_aMatrixData) {
			//
			// Load all floats	(Used not only for matrices, but also shape XYUV)
			//
			for (u32 n = 0; n < floatCount; n++) {
				this->m_aMatrixData[n] = READFLP(pData);
			}

			//
			// Matrix Array Indexes.
			//
			this->m_aMatrixType         = KLBNEWA(u8,m_uiMatrixCount);
			this->m_aMatrixDataIndex    = KLBNEWA(u32,m_uiMatrixCount);

			// Matrix Transform Type.
			if (m_aMatrixType && m_aMatrixDataIndex) {
				for (u32 n = 0; n < m_uiMatrixCount; n++) {
					this->m_aMatrixType[n]      = READU8P(pData);
					this->m_aMatrixDataIndex[n] = READU32P(pData);
				}
			}

			//
			// Instruction Stream
			//
			this->m_aStreamSize	        = READU32P(pData);
			this->m_aStreamInstruction  = KLBNEWA(u32,m_aStreamSize);

			if (m_aStreamInstruction) {
				for (u32 n = 0; n < m_aStreamSize; n++) {
					this->m_aStreamInstruction[n] = READU32P(pData);
				}

				//
				// Movie Stream
				//
				m_uiMovieCount = READU16P(pData);
				int size = m_uiMovieCount * SIZE_MOVIE_INFO;
				m_aMovieInfo	= KLBNEWA(u32,size);
				m_aBitmapLoaded	= KLBNEWA(CKLBImageAsset*,m_uiMovieCount);
				m_alistCacheEntries	= KLBNEWA(SCacheEntry*, m_aStreamSize);

				if (m_aMovieInfo && m_aBitmapLoaded && m_alistCacheEntries) {
					for (int n = 0; n < size; n++) {
						m_aMovieInfo[n] = READU32P(pData);
					}

					// Faster than init in loop.
					memset32(m_aBitmapLoaded,		0, m_uiMovieCount * sizeof(CKLBImageAsset*  )	);
					memset32(m_alistCacheEntries,	0, m_uiMovieCount * sizeof(SCacheEntry*		)	);

					//
					// Create sub movies ressource automatically.
					//
					for (int n = 0; n < m_uiMovieCount; n++) {

						// For each movie, check against name in constant pool.
						int idx = m_aMovieInfo[(n * SIZE_MOVIE_INFO) + CODE_NAMEINDEX];
						if (idx != NULL_IDX) {
							if (m_aMovieInfo[(n * SIZE_MOVIE_INFO) + CODE_FRAMECOUNT] != NULL_IDX)
							{
								//
								CKLBSWFAsset* pLinkAsset = KLBNEW(CKLBSWFAsset);
								if (pLinkAsset) {
									pLinkAsset->m_subAssets		= m_subAssets;
									m_subAssets					= pLinkAsset;
									pLinkAsset->m_pName			= m_aConstants[idx];
									pLinkAsset->m_refMovieID	= (u16)n; // Direct linking.
									pLinkAsset->m_uiMovieCount	= 0;	// Force replace asset to skip this sub asset.
								}
							}
						}
					}

					// Resolve all Audio Asset.
					IPlatformRequest& plt = CPFInterface::getInstance().platform();
					for (u32 n = 0; n < m_uiSoundCount; n++) {
						m_sounds[n].handle = plt.loadAudio(m_aConstants[m_sounds[n].nameIdx], true);
						plt.preLoad(m_sounds[n].handle);
					}
					return true;
				}
			}
		}
	}
	return false;
}

u16 CKLBSWFAsset::findMovie(char* name) {
	for (u16 n = 0; n < this->m_uiMovieCount; n++) {
		// For each movie, check against name in constant pool.
		int idx = m_aMovieInfo[(n * SIZE_MOVIE_INFO) + CODE_NAMEINDEX];
		if (idx != NULL_IDX) {
			if (strcmp(name, &(m_aConstants[idx][1])) == 0) { // [1] : Skip Plugin ID.
				return n;
			}
		}
	}
	return NULL_IDX;
}

CKLBSWFAsset* CKLBSWFAsset::findMovieAsset(char* name) {
	klb_assert(m_isMaster, "Can not using findMovieAsset on a sub asset");
	// OPTIMIZE : registration could register VALID name before EMPTY NAME to fasten up search (2 pass register)
	CKLBSWFAsset* pLinkAsset = m_subAssets;
	while (pLinkAsset) {
		if (strcmp(name, pLinkAsset->m_pName) == 0) {
			return pLinkAsset;
		}
	}
	return NULL;
}

void CKLBSWFAsset::setVolumeSE(float volume) {
	if (m_sounds) {
		for (u32 n = 0; n< this->m_uiSoundCount; n++) {
			CPFInterface::getInstance().platform().setAudioVolume(m_sounds[n].handle, volume);
		}
	}
}

static char* copyStr(const char* str) {
	u32 len = strlen(str);
	char* buff = KLBNEWA(char, len+1);
	memcpy(buff, str, len + 1);
	return buff;
}

s8 CKLBSWFMovie::replaceAsTemplate(const char** pArrayString, u32 entryCount) {
	u32 stringCount = entryCount << 1;
	u32 movieCount	= this->m_player->m_uiMovieCount;
	s8  res         = 0;
	freeTables();

	m_aBitmapLoaded = KLBNEWA(CKLBImageAsset*, movieCount);
	m_convTable		= KLBNEWA(s32, movieCount);
	m_nameTable		= KLBNEWA(const char*, movieCount);

	if (m_aBitmapLoaded && m_convTable && m_nameTable) {
		for (u32 n = 0; n < movieCount; n++) {
			m_convTable[n]		= -1;	// Unmapped
			m_nameTable[n]		= NULL;
			m_aBitmapLoaded[n]	= NULL;
		}

		for (u32 n=0; n < movieCount; n++) {
			int cteId = m_player->m_aMovieInfo[ (n * SIZE_MOVIE_INFO) + CODE_NAMEINDEX];
			if (cteId != 0xFFFF) {
				char* origStr = &m_player->m_aConstants[cteId][1];
				for (u32 m = 0; m < stringCount; m += 2) {
					if (CKLBUtility::safe_strcmp(origStr,pArrayString[m])==0) {
						m_nameTable[n] = copyStr(pArrayString[m+1]);
						if (m_nameTable[n]) {	// Protect in case of allocation failure.
							m_convTable[n] = 0;
							res++;
						} else {
							klb_assertAlways("Allocation Failure");
						}
					}
				}
			}
		}
	} else {
		res = -1;
	}

	return res;
}

u32 CKLBSWFAsset::getResourceList(u32 arraySize, const char** arrayOfString) {
	u32 res     = 0;
	u32 fill    = 0;

	for (int n=0; n < this->m_uiMovieCount; n++) {
		int cteId = m_aMovieInfo[ (n * SIZE_MOVIE_INFO) + CODE_NAMEINDEX];
		if (cteId != NULL_IDX) {
			const char* name;
			name = &(m_aConstants[cteId][1]);
			if (fill < arraySize) {
				arrayOfString[fill++] = name;
			}
			res++;
		}
	}
	return res;
}

CKLBImageAsset* CKLBSWFMovie::getImage(u16 movieID) {
	CKLBImageAsset** pBmpLoaded = m_aBitmapLoaded;
	if (pBmpLoaded == NULL) {
		pBmpLoaded = m_player->m_aBitmapLoaded;
	}
	
	if (pBmpLoaded[movieID] == NULL) {
		int cteId = m_player->m_aMovieInfo[ (movieID * SIZE_MOVIE_INFO) + CODE_NAMEINDEX];
		if (cteId != NULL_IDX) {
			CKLBAssetManager& pAssetMgr = CKLBAssetManager::getInstance();
			const char* name;
			
			s32 offX = 0;
			s32 offY = 0;

			bool replace;

			const char* origName = &(m_player->m_aConstants[cteId][1]);
			if (m_convTable && (m_convTable[movieID] != -1)) {
				name = m_nameTable[movieID];
				if (name == NULL) {
					name = origName;
					replace = false;
				} else {
					// Original Texture & Image -> Center coordinate.
					// If the original filename starts with a percent,
					// that means it's a template image that does not
					// exist on disk.
					if (origName[0] != '%') {
						u16 assetID = pAssetMgr.getAssetIDFromName(origName ,m_player->m_aConstants[cteId][0]); // char 0 = 'I'
						CKLBAbstractAsset* pAsset = pAssetMgr.getAsset(assetID);
						if (pAsset) {
							CKLBImageAsset* pImgOrig = ((CKLBTextureAsset*)pAsset)->getImage(origName);
							pImgOrig->getCenter(offX, offY);
						}
					}
					replace = true;
				}
			} else {
				name    = &(m_player->m_aConstants[cteId][1]);
				replace = false;
			}

			u16 assetID = pAssetMgr.getAssetIDFromName(name,m_player->m_aConstants[cteId][0]); // char 0 = 'I'
			CKLBAbstractAsset* pAsset = pAssetMgr.getAsset(assetID);
			if (pAsset) {
				if (pAsset->getAssetType() == ASSET_TEXTURE) {
					CKLBImageAsset* pImgUsed = ((CKLBTextureAsset*)pAsset)->getImage(name);
					if (!replace) {
						pImgUsed->getCenter(offX, offY);
					}
					pBmpLoaded[movieID] = pImgUsed->getAsTopLeftImage(offX, offY);
					if (pBmpLoaded[movieID]) {
						pBmpLoaded[movieID]->getTexture()->incrementRefCount();
					}
				} else {
					klb_assertAlways( "invalid resource type");
				}
			} else {
				DEBUG_PRINT("[Flash] Asset %s not found !!!!!", name);
			}
		}
	}
	return pBmpLoaded[movieID];
}

CKLBNode* CKLBSWFAsset::addMovieA(char* name, u16 layer, SMatrix2D* m, CKLBNode* root, const char** templateTable, u32 pairCount) {
	u16 index;
	if (name == NULL) {
		index = this->m_uiMovieCount-1;
	} else {
		index = findMovie(name);
	}

	CKLBNode* newMovie = NULL;
	if (index != NULL_IDX) {
		newMovie = addMovieB(index, layer, m, root, templateTable, pairCount);	// Only called from UI SWF Player.
	}
	return newMovie;
}

CKLBNode* CKLBSWFAsset::addMovieB(u16 movieID, u16 layer, SMatrix2D* m, CKLBNode* root, const char** convTable, u32 convCount) {
	CKLBNode* newMovie = NULL; // Fail by default.
	int movieIndex = movieID * SIZE_MOVIE_INFO;
	int type = m_aMovieInfo[ movieIndex + CODE_FRAMECOUNT];

	if (type < 32768) {
		CKLBSWFMovie* lMovie = KLBNEWC(CKLBSWFMovie,(this, root, layer));

		if (lMovie) {
			// Propagate link to top node (MUST BE SET JUST AFTER CONSTRUCTION)
			if (root) {
				lMovie->m_flashRoot = ((CKLBSWFMovie*)root)->m_flashRoot;
			} else {
				lMovie->setFlashRoot();
			}

			lMovie->m_movieStartCode= m_aMovieInfo[ movieIndex + CODE_STARTINDEX];
			lMovie->m_movieEndCode	= m_aMovieInfo[ movieIndex + CODE_ENDINDEX];
			lMovie->m_movieCode		= lMovie->m_movieStartCode + SKIP_SHOW; // Skip custom show frame "0"
			lMovie->m_uiFrame		= 1;
			lMovie->m_isPlaying			= PLAYING;
			lMovie->m_isPlayingBackup	= PLAYING;
			lMovie->m_msPerFrame	= m_msPerFrame;

			if (convTable) {
				lMovie->replaceAsTemplate(convTable, convCount);
			}

			// Force execution first frame.
			lMovie->nextFrame(1);


		}

		newMovie = lMovie;
	} else {
		// 0xFFFF
		if (type == NULL_IDX) {
			CKLBImageAsset* pImg = ((CKLBSWFMovie*)root)->m_flashRoot->getImage(movieID);
			if (pImg) {
				CKLBSprite* pSpr;

				s32 ioffX		= (s16)m_aMovieInfo[movieIndex + CODE_OFFSETX];
				s32 ioffY		= (s16)m_aMovieInfo[movieIndex + CODE_OFFSETY];

				// Any value different from 0.
				if (ioffX || ioffY) {
					//
					// Include offset in dynamic sprite.
					//
					CKLBDynSprite* pSprite = CKLBRenderingManager::getInstance().allocateCommandDynSprite(pImg->getVertexCount(), pImg->getIndexCount());

					// Assign texture reference.
					pSprite->setTexture(pImg->getTexture()->m_pTextureUsage);

					// Copy UV.
					memcpy(pSprite->getSrcUVBuffer(),pImg->getUVBuffer(), pImg->getVertexCount() * 2 * sizeof(float));

					// Copy Indexes.
					u16* pIdx = pSprite->getSrcIndexBuffer();
					memcpy(pSprite->getSrcIndexBuffer(), pImg->getIndexBuffer(), pImg->getIndexCount() * sizeof(u16));


					//
					// Add translation directly in sprite information, avoiding intermediate nodes.
					//
					float* coords	= pSprite->getSrcXYBuffer();
					float offX		= (float)((s16)m_aMovieInfo[movieIndex + CODE_OFFSETX]);
					float offY		= (float)((s16)m_aMovieInfo[movieIndex + CODE_OFFSETY]);
					float* srcXY	= pImg->getXYBuffer();

					for (u32 n=0; n < pImg->getVertexCount(); n++) {
						*coords++ = *srcXY++ + offX;
						*coords++ = *srcXY++ + offY;
					}

					pSpr = pSprite;
				} else {
					pSpr = CKLBRenderingManager::getInstance().allocateCommandSprite(pImg);
				}

				CKLBNode* pMovie	= KLBNEW(CKLBNode);
				if (pMovie) {
					pMovie->setRender(pSpr);
					pMovie->setRenderOnDestroy(true);
					newMovie = pMovie;

					root->addNode(pMovie, layer);

					pMovie->markUpMatrix();

					// Force top node to refresh.
					// OPTIMIZE : replacement from to another image could be done, no need to mark rebuild.
					((CKLBSWFMovie*)root)->m_flashRoot->m_rebuildSort = true;
				}
			}
		} else {
			// 0x8xxx : Shape	(4096 shape max)
			if ((type & 0xF000) == 0x8000) {
				SShape* pShp = &m_shapes[type & 0xFFF];
				if (pShp) {
					CKLBNode* pMovie	= KLBNEW(CKLBNode);
					CKLBDynSprite*	pSprite = CKLBRenderingManager::getInstance().allocateCommandDynSprite(pShp->vertexCount, pShp->indexCount);
					if (pSprite && pMovie) {
						root->addNode(pMovie,layer);
						pMovie->setRenderOnDestroy(true);

						// Transfer Index Buffer
						u16* dst = pSprite->getSrcIndexBuffer();
						memcpy(dst,&m_pIndex[pShp->indexBuffer],pShp->indexCount * sizeof(u16));
						// Transfer XY Coordinate
						memcpy(pSprite->getSrcXYBuffer(), &m_aMatrixData[pShp->XYBuffer], pShp->vertexCount * 2 * sizeof(float));
						// Transfer UV Coordinate
						memcpy(pSprite->getSrcUVBuffer(), &m_aMatrixData[pShp->UVBuffer], pShp->vertexCount * 2 * sizeof(float));
						pMovie->setRender(pSprite);
						pSprite->setTexture(pShp->textureUsage); // Use CTextureUsage directly !
						if (pShp->styleType == TYPE_FILL_COLOR) {
							// Optimize u32 -> float -> u32 color conv.
							u8* pCol = (u8*)&pShp->fillColor;
							float vec4[4];
							vec4[0]	= (pCol[0] / 255.0f);
							vec4[1]	= (pCol[1] / 255.0f);
							vec4[2]	= (pCol[2] / 255.0f);
							vec4[3]	= (pCol[3] / 255.0f);

							pSprite->setColor(vec4);
						}
						pSprite->mark(CKLBDynSprite::MARK_CHANGE_UV | CKLBDynSprite::MARK_CHANGE_XY);
						((CKLBSWFMovie*)root)->m_flashRoot->m_rebuildSort = true;
						newMovie = pMovie;
					}
				} else {
					klb_assertAlways("Flash content refer to a shape undefined : most likely bitmap used directly without movie clip.");
				}
			} else {
			}
		// 0xFFFE : End Clip.
			//
			// Support other type of shape : End Clip / Shape
			//
		}
	}

	if (newMovie != NULL) {
		newMovie->m_movieID = movieID;
		if (m != NULL) {
			for (int n = 0; n < 5; n++) {
				newMovie->m_matrix.m_matrix[n] = m->m_matrix[n];    // copy Array
            }
			newMovie->m_matrix.m_type = m->m_type;                  // copy type.
			newMovie->markUpMatrix();
		}

		// Node added at construction already.
		
		newMovie->m_useParentColor	= true;
	}
	return newMovie;
}

CKLBNode* CKLBSWFAsset::createSubTree(u32 priorityBase) {
	CKLBSWFMovie* pMov;
	if (this->m_parentSWF) {
		// Submovies.
		pMov = (CKLBSWFMovie*)m_parentSWF->addMovieB(this->m_refMovieID, 0, NULL, NULL, NULL, 0);
	} else {
		// Main timeline.
		pMov = (CKLBSWFMovie*)addMovieB(this->m_uiMovieCount-1, 0, NULL, NULL, NULL, 0);
	}
	if (pMov) { pMov->setPriority(priorityBase); }
	return pMov;
}

// ##########################################
//
// --- Instance ---
//
// ##########################################

CKLBSWFMovie::CKLBSWFMovie(CKLBSWFAsset* pPlayer, CKLBNode* pParent, u16 layer)
: CKLBNode          ()
, m_player          (pPlayer)
, m_movieStartCode  (NULL_IDX)
, m_movieCode       (NULL_IDX)
, m_movieEndCode    (NULL_IDX)
, m_uiFrame         (0)
, m_localTime       (0)
, m_renderOffset    (0)
, m_isPlaying       (false)
, m_firstFrame      (true)
, m_updateFrame     (0)
, m_isFlashRoot     (false)
, m_flashRoot       (NULL)
, m_rebuildSort     (true)
, m_disableJump     (false)
, m_aBitmapLoaded   (NULL)
, m_convTable       (NULL)
, m_nameTable       (NULL)
, m_playMode        (true)
, m_volume          (1.0f)
, m_supportCaching	(false)
{
	// Is animated by factory design BEFORE ANY OPERATION.
	this->m_status |= ANIMATED;

	CKLBSystem::addToAnimation(this);

	// Add to the scene graph tree.
	if (pParent != NULL) {
		pParent->addNode(this,layer);
	}
}

CKLBSWFMovie::~CKLBSWFMovie() {
	freeTables();
}

void CKLBSWFMovie::freeTables() {
	if (m_aBitmapLoaded) {
		for (u32 n = 0; n < m_player->m_uiMovieCount; n++) {
			if (m_aBitmapLoaded[n]) {
				m_aBitmapLoaded[n]->getTexture()->decrementRefCount();
				m_aBitmapLoaded[n] = NULL;
			}
		}
		KLBDELETEA(m_aBitmapLoaded);
		m_aBitmapLoaded = NULL;
	}


	if (m_convTable) {
		KLBDELETEA(m_convTable);
		m_convTable = NULL;
	}

	if (m_nameTable) {
		for (u32 n = 0; n < m_player->m_uiMovieCount; n++) {
			KLBDELETEA(m_nameTable[n]);
		}
		KLBDELETEA(m_nameTable);
		m_nameTable = NULL;
	}
}

void CKLBSWFMovie::setVolumeSE(float volume) {
	m_volume = volume;
	m_player->setVolumeSE(volume);
}

void CKLBSWFMovie::setFlashRoot() {
	m_isFlashRoot	= true;
	m_flashRoot		= this;
	m_rebuildSort	= true;		
}

void CKLBSWFMovie::gotoFrame(u16 frame) {
	if (frame != NULL_IDX) {
		// m_movieCode = this->findCodeFrame(frame);
		m_disableJump = true;


		// Reset any stop instruction from the flash player state.
		// If player is still active : force to play
		if (m_playMode) {
			m_isPlaying = PLAYING;
		} else {
		// If player is inactive : force to play when the play() function is called.
			m_isPlayingBackup = PLAYING;
		}

		nextFrame(frame);
		m_disableJump = false;
	}
}

u16 CKLBSWFMovie::findCodeFrame(char* label, u16* pFrameNum) {
	u16 uiFrame     = 0;
	u32 movieCode   = m_movieStartCode;

	if (label) {
		//
		// 
		// search failure return start frame : always a valid frame => Avoid a lot of test within the player runtime.
		//
		while (movieCode < m_movieEndCode) {
			u16 val = m_player->m_aStreamInstruction[movieCode++];
			switch (val) {
			case SHOW_FRAME:
				{
					u16 lblIdx = m_player->m_aStreamInstruction[movieCode++]; // Label
					if (lblIdx != NULL_IDX) {
						if (CKLBUtility::safe_strcmp(this->m_player->m_aConstants[lblIdx], label) == 0) {
							if (pFrameNum) {
								*pFrameNum = uiFrame + 1;
							}
							return movieCode-2;
						}
					}
				}
				movieCode++;
				movieCode++;
				
				uiFrame++;

				break;
			case PLACE_OBJECT_CLIP:
				{
					movieCode += 5;
				}
				break;
			case PLACE_OBJECT:
				{
					movieCode += 4;
				}
				break;
			case REMOVE_OBJECT:
			case PLAY_SOUND:
				{
					movieCode++;
				}
				break;
			default:
				if (val & 0x8000) {
					klb_assertAlways("Future Extension Invalid code");
					if (val & 0x4000) {
						movieCode += ((val >> 4) & 0x1F);
					} else {
						// Do nothing : remove encode everything.
					}
				} else {
					klb_assertAlways("Invalid code");
				}
			}
		}
	} else {
		klb_assertAlways( "empty label search");
	}

	if (pFrameNum) {
		*pFrameNum = NULL_IDX;
	}
	return NULL_IDX;
}

u16 CKLBSWFMovie::findCodeFrame(u16 frame) {
	u16 uiFrame	    = 0;
	u32 movieCode   = m_movieStartCode;

	//
	// 
	// search failure return start frame : always a valid frame => Avoid a lot of test within the player runtime.
	//
	while (uiFrame != frame) {
		if (movieCode < m_movieEndCode) {
			u16 val = m_player->m_aStreamInstruction[movieCode++];
			switch (val) {
			case SHOW_FRAME:
				movieCode++;	// Skip label
				movieCode++;
				movieCode++;
				
				uiFrame++;

				break;
			case PLACE_OBJECT_CLIP:
				{
					movieCode += 5;
				}
				break;
			case PLACE_OBJECT:
				{
					movieCode += 4;
				}
				break;
			case REMOVE_OBJECT:
			case PLAY_SOUND:
				{
					movieCode++;
				}
				break;
			default:
				if (val & 0x8000) {
					klb_assertAlways("Future Extension Invalid code");
					if (val & 0x4000) {
						movieCode += ((val >> 4) & 0x1F);
					} else {
						// Do nothing : remove encode everything.
					}
				} else {
					klb_assertAlways("Invalid code");
				}
			}
		} else {
			return m_movieStartCode + 4;
			break;
		}
	}

	return movieCode - 4;
}

// Normal mode
#define SWF_NORMAL			(0)
// Delay of one frame the object destruction (set m_firstFrame)
#define SWF_GOTO_AND_PLAY	(1)

void CKLBSWFMovie::InitBits(void)
{
	// Reset the bit position and buffer.
	m_bitPos = 0;
	m_bitBuf = 0;
}

s32 CKLBSWFMovie::GetSBits(s32 n)
// Get n bits from the string with sign extension.
{
	// Get the number as an unsigned value.
	s32 v = (s32) GetBits(n);

	// Is the number negative?
	if (v & (1L << (n - 1)))
	{
		// Yes. Extend the sign.
		v |= -1L << n;
	}

	return v;
}

u32 CKLBSWFMovie::GetBits (s32 n)
// Get n bits from the stream.
{
	u32 v = 0;

	while (true)
	{
		s32 s = n - m_bitPos;
		if (s > 0)
		{
			// Consume the entire buffer
			v |= m_bitBuf << s;
			n -= m_bitPos;

			// Get the next buffer
			m_bitBuf = m_player->m_aStreamInstruction[m_movieCode++];
			m_bitPos = 16;
		}
		else
		{
			// Consume a portion of the buffer
			v |= m_bitBuf >> -s;
			m_bitPos -= n;
			m_bitBuf &= 0xffff >> (16 - m_bitPos); // mask off the consumed bits

			return v;
		}
	}
}

void CKLBSWFAsset::cacheSceneGraph(CKLBSWFMovie* node, u16 frame) {
	u16 movieID = node->m_movieID;

	if (hasCache(node, frame) == false) {
		// Add new entry.
		SCacheEntry* pNewEntry = KLBNEW(SCacheEntry);
		if (pNewEntry) {
			pNewEntry->m_next		= m_alistCacheEntries[movieID];
			pNewEntry->m_cacheFrame	= frame;
			m_alistCacheEntries[movieID] = pNewEntry;

			// Copy
			pNewEntry->m_cacheNode = (CKLBSWFMovie*)node->clone(NULL, NULL, NULL, true);
		}

		/*
		// Original
		node->dump(0,0xFFFFFFFF);
		// Copy
		m_alistCacheEntries[movieID]->m_cacheNode->dump(0,0xFFFFFFFF);
		*/
	} // else already cached.
}


bool CKLBSWFAsset::hasCache(CKLBSWFMovie* node, u16 frame) {
	u16 movieID = node->m_movieID;
	
	SCacheEntry* pEntries = m_alistCacheEntries[movieID];
	while (pEntries) {
		if (pEntries->m_cacheFrame == frame) {
			return true;
		}
		pEntries = pEntries->m_next;
	}

	return false;
}

void CKLBSWFAsset::restoreSceneGraph(CKLBSWFMovie* node, u16 frame) {
	u16 movieID = node->m_movieID;

	SCacheEntry* pEntries = m_alistCacheEntries[movieID];
	while (pEntries) {
		if (pEntries->m_cacheFrame == frame) {
			// CKLBNode* parent = node->getParent();
			CKLBNode* pNewTree = (CKLBSWFMovie*)pEntries->m_cacheNode->clone(NULL, NULL, NULL, false);

			// Remove old child and destroy
			CKLBNode* pChildren = node->getChild();
			while (pChildren) {
				CKLBNode* pNextChild = pChildren->getBrother();
				node->removeNode(pChildren);
				KLBDELETE(pChildren);		// removeNode happens automatically.
				pChildren = pNextChild;
			}

			// Add each child
			pChildren = pNewTree->getChild();
			while (pChildren) {
				CKLBNode* pNextChild = pChildren->getBrother();
				pNewTree->removeNode(pChildren);
				node->addNode(pChildren,pChildren->getLayer());
				pChildren = pNextChild;
			}

			//
			//
			//

			// Destroy cloned pNewTree emptied.
			CKLBSWFMovie* newMovie = (CKLBSWFMovie*)pNewTree;
			node->m_flashRoot		=	newMovie->m_flashRoot;
			node->m_volume			=	newMovie->m_volume;
			node->m_renderOffset	=	newMovie->m_renderOffset;
			node->m_localTime		=	newMovie->m_localTime;
			node->m_movieStartCode	=	newMovie->m_movieStartCode;
			node->m_movieCode		=	newMovie->m_movieCode;
			node->m_movieEndCode	=	newMovie->m_movieEndCode;
			node->m_uiFrame			=	newMovie->m_uiFrame;
			node->m_msPerFrame		=	newMovie->m_msPerFrame;
			node->m_updateFrame		=	newMovie->m_updateFrame;
			node->m_isPlaying		=	newMovie->m_isPlaying;
			node->m_isPlayingBackup =	newMovie->m_isPlayingBackup;

			KLBDELETE(pNewTree);
			return;
		}
		pEntries = pEntries->m_next;
	}
}

/*virtual*/
CKLBNode* CKLBSWFMovie::clone(CKLBNode* newItem, CKLBNode* parent, CKLBNode* brother, bool transferSpriteOwnership) {
	if (newItem == NULL) {
		newItem = KLBNEWC(CKLBSWFMovie,(this->m_player, parent, this->m_layer));
	}

	if (newItem != NULL) {
		// We want the clone template to stay NON animated.
		if (transferSpriteOwnership) {
			CKLBSystem::removeFromAnimation(newItem);
		}

		CKLBNode::clone(newItem, parent, brother, transferSpriteOwnership);

		CKLBSWFMovie* newMovie = (CKLBSWFMovie*)newItem;

		newMovie->m_flashRoot		= m_flashRoot;
		newMovie->m_volume			= m_volume;
		newMovie->m_renderOffset	= m_renderOffset;
		newMovie->m_localTime		= m_localTime;
		newMovie->m_movieStartCode	= m_movieStartCode;
		newMovie->m_movieCode		= m_movieCode;
		newMovie->m_movieEndCode	= m_movieEndCode;
		newMovie->m_uiFrame			= m_uiFrame;
		newMovie->m_msPerFrame		= m_msPerFrame;
		newMovie->m_updateFrame		= m_updateFrame;
		newMovie->m_isPlaying		= m_isPlaying;
		newMovie->m_isPlayingBackup = m_isPlayingBackup;

		// Flash root is the only one to own the arrays
		// And flash root is never going to be destroyed.
		// newMovie->m_aBitmapLoaded	= m_aBitmapLoaded;
		// newMovie->m_convTable		= m_convTable;
		// newMovie->m_nameTable		= m_nameTable;

		newMovie->m_firstFrame		= m_firstFrame;
		newMovie->m_rebuildSort		= m_rebuildSort;
		// False always.
		// newMovie->m_isFlashRoot		= m_isFlashRoot;
		newMovie->m_disableJump		= false;
		newMovie->m_playMode		= m_playMode;
	}

	return newItem;
}

void CKLBSWFMovie::nextFrame(u16 frame) {
	int mode = SWF_NORMAL;
	if (m_isPlaying != STOPPED) {
		if ((frame < this->m_uiFrame) || (m_uiFrame == NULL_IDX)) {	// May be able to optimize condition.
			m_uiFrame = 1;
			// clearSubTree();
			m_movieCode = this->m_movieStartCode + SKIP_SHOW;
			m_firstFrame = true;
		}

		// Just next frame
		if (frame == NULL_IDX) {
			frame = m_uiFrame+1;
		} else {
			frame++; // = Exit when we reach the beginning of the NEXT FRAME.
		}

		u16 lblCode = NULL_IDX;

		while (m_uiFrame < frame) {
nextInstruction:
			u16 val = m_player->m_aStreamInstruction[m_movieCode++];
			if (val & 0x8000) {								// Bit 15
				klb_assertAlways("Future Extension Invalid code");
				if (val & 0x4000) {							// Bit 14
					// 8..4

					InitBits();
			
					bool has8BitLayer	= (val & 0x0002) != 0;		// Bit  1
					u32 layer = GetBits((has8BitLayer) ? 8 : 16);

					CKLBNode* movie;
					movie = getNode(layer);
			
					// 
					bool hasObject		= (val & 0x0008) != 0;		// Bit  3
					if (hasObject) {
						bool has8BitID	= (val & 0x0004) != 0;	    // Bit  2
						u32 objId = GetBits((has8BitID) ? 8 : 16);
						if (movie != NULL) {
							if (movie->m_movieID != objId) {
								removeMovie(movie);
								KLBDELETE(movie);
								movie = NULL;
							}
						}

						if (movie == NULL) {
							movie = addMovie(objId, layer); // Default matrix is set, update by place.
						}
					}
			
					bool hasClipping	= val & 0x0001;		// Bit  0
					if (hasClipping) {
						// TODO Future clipping support.
						// u32 clipID = GetBits(16);
					}
			
					if (movie) {
						int read;
						bool hasTranslation = (val & 0x2000) != 0;		// Bit 13
						bool hasScale       = (val & 0x1000) != 0;		// Bit 12
						bool hasSkew		= (val & 0x0800) != 0;		// Bit 11
						if (hasTranslation | hasScale | hasSkew) {
							u8 type     = MATRIX_ID;
					
							#define A			(0)
							#define B			(1)
							#define C			(2)
							#define D			(3)
							#define TX			(4)
							#define TY			(5)
					
							float* p = movie->m_matrix.m_matrix;
					
							p[A]		= 1.0f;
							p[B]		= 0.0f;
							p[C]		= 0.0f;
							p[D]		= 1.0f;
							p[TX]		= 0.0f;
							p[TY]		= 0.0f;
					
							if (hasTranslation) {
								read = GetBits(5);
								p[TX]	= GetSBits(read) / 64.0f;
								p[TY]	= GetSBits(read) / 64.0f;
								type = MATRIX_T;
							}
					
							if (hasScale) {
								read = GetBits(5);
								p[A]	= GetSBits(read) / 65536.0f;
								p[D]	= GetSBits(read) / 65536.0f;
								type = MATRIX_TS;
							}
					
							if (hasSkew) {
								read = GetBits(5);
								p[B]	= GetSBits(read) / 65536.0f;
								p[C]	= GetSBits(read) / 65536.0f;
								type = MATRIX_TG;
							}
					
							movie->m_matrix.m_type = type;
							movie->markUpMatrix();
						}
				
						bool hasColorAlpha	= (val & 0x0400) != 0;		// Bit 10
						bool hasColorRGB	= (val & 0x0200) != 0;		// Bit  9
						if (GetBits(1)) {
							float* p = movie->m_localColorMatrix.m_vector;

							read = GetBits(4);

							// RGB First
							if (hasColorRGB) {
								p[0]	= GetBits(read) / 256.0f;
								p[1]	= GetBits(read) / 256.0f;
								p[2]	= GetBits(read) / 256.0f;
							} else {
								p[0]    = 1.0f;
								p[1]    = 1.0f;
								p[2]    = 1.0f;
							}
					
							p[3] = (hasColorAlpha) ? (GetBits(read) / 256.0f) : 1.0f;
					
							movie->m_pColorMatrix	= &movie->m_colorMatrix;
							movie->m_useParentColor	= false;
							movie->markUpColor();
						}
				
						movie->m_updateFrame = m_uiFrame;
					} else {
						klb_assertAlways("Can not create / access movie.");
					}
				} else {
					// Remove
					// 
					// bool fit = val & 0x2000;		// Bit 13
					u16 layer = val & 0x1FFF;
					CKLBNode*	pNode	= getNode(layer);
					removeMovie(pNode);
					KLBDELETE(pNode);
				}
				goto nextInstruction;
			} else {
				switch (val) {
				case SHOW_FRAME:

					//
					// Delay of ONE frame to destroy all movies.
					//
					if ((mode == SWF_GOTO_AND_PLAY) && (m_uiFrame == frame)) {
						m_firstFrame	= true;
						mode = SWF_NORMAL;
					}

					// Do nothing, end.
					lblCode = m_player->m_aStreamInstruction[m_movieCode++];	// Label

					if (m_isPlaying == STOP_TARGET) {
						m_isPlaying = STOPPED;
					}

					{
						u16 type = m_player->m_aStreamInstruction[m_movieCode++];
						if (!m_disableJump) {
							// Stop instruction on this frame.
							if (type == STOP_INSTRUCTION) {
								this->m_isPlaying = STOPPED;
								m_movieCode++;
							} else {
								if ((type == GOTO_AND_STOP) || (type == GOTO_AND_PLAY)) {
									u16 frameTarget = m_player->m_aStreamInstruction[m_movieCode++] + 2;
									
									if (m_supportCaching && m_player->hasCache(this, frameTarget)) {
										m_player->restoreSceneGraph(this, frameTarget);
										frame		= frameTarget;
										m_uiFrame	= frameTarget;
									} else {
										u16 newMovieCode = this->findCodeFrame(frameTarget);

										if (newMovieCode < m_movieCode) {
											// For now, movie loops.
											m_movieCode		= m_movieStartCode + SKIP_SHOW;
											m_uiFrame		= 0;
										}

										frame			= frameTarget;
										mode			= SWF_GOTO_AND_PLAY;
										m_disableJump	= true;
									}
									// Freeze player once reached.
									if (type == GOTO_AND_STOP) {
										m_isPlaying = STOPPED;
									}
								} else {
									m_movieCode++;
								}
							}
						} else {
							m_movieCode++;
						}
					}
					break;
				case PLACE_OBJECT_CLIP:
				case PLACE_OBJECT:
					{
						u16 movieID			= m_player->m_aStreamInstruction[m_movieCode++];
						u16 matrixIdx		= m_player->m_aStreamInstruction[m_movieCode++];
						u16 matrixColIdx	= m_player->m_aStreamInstruction[m_movieCode++];
						u16 layer			= m_player->m_aStreamInstruction[m_movieCode++];
						u16 clipLayer;

						if (m_player->m_aStreamInstruction[m_movieCode-5] == PLACE_OBJECT_CLIP) {
							clipLayer		= m_player->m_aStreamInstruction[m_movieCode++];
						}
						CKLBNode* movie;

						//
						// Remove movie if replace
						//
						movie = getNode(layer);
						if (movieID != NULL_IDX) {
							if (movie != NULL) {
								if (movie->m_movieID != movieID) {
									removeMovie(movie);
									KLBDELETE(movie);
									movie = NULL;
								}
							}

							if (movie == NULL) {
								movie = addMovie(movieID, layer); // Default matrix is set, update by place.
							}
						}

						klb_assertNull(movie, "Null pointer");

						if (movie) {
							//
							// Setup matrix / color matrix, movie play etc...
							//

							#define A			(0)
							#define B			(1)
							#define C			(2)
							#define D			(3)
							#define TX			(4)
							#define TY			(5)

							// Marking for object destruction when owner movie loop.
							movie->m_updateFrame = m_uiFrame;
							if (matrixIdx != NULL_IDX) {
								int idx = m_player->m_aMatrixDataIndex[matrixIdx];
								float* pFL = movie->m_matrix.m_matrix;
								switch (m_player->m_aMatrixType[matrixIdx]) {
								case MATRIX_TG:
									// Thru. no break.
									pFL[A]  = m_player->m_aMatrixData[idx++];
									pFL[D]  = m_player->m_aMatrixData[idx++];
									pFL[B]  = m_player->m_aMatrixData[idx++];
									pFL[C]  = m_player->m_aMatrixData[idx++];
								case MATRIX_T:
									pFL[TX] = m_player->m_aMatrixData[idx++];
									pFL[TY] = m_player->m_aMatrixData[idx++];
									break;
								case MATRIX_TS:
									pFL[A]  = m_player->m_aMatrixData[idx++];
									pFL[D]  = m_player->m_aMatrixData[idx++];
									pFL[TX] = m_player->m_aMatrixData[idx++];
									pFL[TY] = m_player->m_aMatrixData[idx++];
									pFL[B]  = 0.0f;
									pFL[C]  = 0.0f;
									break;
								case MATRIX_COL:
									// N/A Here
									break;
								case MATRIX_ID:
									pFL[A]  = 1.0f;
									pFL[D]  = 1.0f;
									pFL[TX] = 0.0f;
									pFL[TY] = 0.0f;
									pFL[B]  = 0.0f;
									pFL[C]  = 0.0f;
									break;
								}

								// Update type of local matrix.
								movie->m_matrix.m_type = m_player->m_aMatrixType[matrixIdx];

								#undef A
								#undef B
								#undef C
								#undef D
								#undef TX
								#undef TY

								movie->markUpMatrix();
							}

							if (matrixColIdx != NULL_IDX) {
								float* pFL = movie->m_localColorMatrix.m_vector;
								if (m_player->m_aMatrixType[matrixColIdx] == 0) {
									*pFL++  = 1.0f;
									*pFL++  = 1.0f;
									*pFL++  = 1.0f;
									*pFL++  = 1.0f;
								} else {
									int idx = m_player->m_aMatrixDataIndex[matrixColIdx];
									*pFL++	= m_player->m_aMatrixData[idx++];	// R
									*pFL++	= m_player->m_aMatrixData[idx++];	// G
									*pFL++	= m_player->m_aMatrixData[idx++];	// B
									*pFL	= m_player->m_aMatrixData[idx];		// A
								}
								movie->m_pColorMatrix	= &movie->m_colorMatrix;
								movie->m_useParentColor	= false;
								movie->markUpColor();
							}
						}
					}
			
					goto nextInstruction;
				case REMOVE_OBJECT:
					{
						u16 layer			= m_player->m_aStreamInstruction[m_movieCode++];
						CKLBNode*	pNode	= getNode(layer);
						removeMovie(pNode);
						KLBDELETE(pNode);
					}

					goto nextInstruction;
				case PLAY_SOUND:
					{
						u8 sndId = (u8)m_player->m_aStreamInstruction[m_movieCode++];
						if (mode != SWF_GOTO_AND_PLAY) {
							CPFInterface::getInstance().platform().playAudio(m_player->m_sounds[sndId].handle);
						}
					}
					goto nextInstruction;
				default:
					klb_assertAlways("Invalid code");
					break;
				}
			}

			if (m_firstFrame) {
				m_firstFrame = false;
			
				//
				// Clean like crazy.
				//
				CKLBNode* pChild = m_pChild;
				while (pChild) {
					CKLBNode* pChildNext = ((CKLBSWFMovie*)pChild)->m_pBrother;
					if (pChild->m_updateFrame != m_uiFrame) {
						this->removeNode(pChild);
						KLBDELETE(pChild);
					}
					pChild = pChildNext;
				}
			}

			m_uiFrame++;
		}


		if (m_movieCode == m_movieEndCode) {
			u32 frameLast = m_uiFrame;

			// For now, movie loops.
			m_movieCode = m_movieStartCode + SKIP_SHOW;
			m_firstFrame = true;

			// Change value AFTER call back for user (may read the frame if API allows it)
			m_uiFrame	= NULL_IDX; // Force player to restart from frame 0.

			if (m_msgListener) {
				m_msgListener->receiveMsg(this, ANIMATION_COMPLETE, frameLast);
			}
		} else {
			if (m_msgListener && (lblCode != NULL_IDX)) {
				m_msgListener->receiveMsg(this, LABEL_REACHED, lblCode);
			}
		}

		if (m_disableJump == true && m_supportCaching) {
			m_player->cacheSceneGraph(this, m_uiFrame);
		}

		m_disableJump = false;
	}
}

// -----------------------------------------------------------------
//   Tree marking and update.
/*virtual*/
void CKLBSWFMovie::animate(u32 deltaTimeMilli) {
	//
	// 1. Execute movie
	// Note : same behavior as flash : all sub movies continue to "play".
	//
	if (m_movieCode != NULL_IDX) {
		m_localTime += deltaTimeMilli;
		if (m_localTime >= m_msPerFrame) {
			// m_localTime -= m_msPerFrame;  <-- Best Effort method, try to get back lost time.
			m_localTime = 0;	// Do not accelerate if late, but no frame skip.
			nextFrame(NULL_IDX);
		}
	} else {
		// Movie is stopped, remove from animation.
		CKLBSystem::removeFromAnimation(this);
	}

	if (m_isFlashRoot && m_rebuildSort) {
		rebuildSort();
	}
}

void CKLBSWFMovie::setPriority(u32 baseOrder) {
	this->m_renderOffset = baseOrder;
	m_rebuildSort		 = true;
}

void CKLBSWFMovie::rebuildSort() {
	CKLBRenderingManager& pRdr = CKLBRenderingManager::getInstance();

	u32 renderOffset = this->m_renderOffset;
	rebuildRecurse(this, &renderOffset, pRdr);

	// Sort finished.
	m_rebuildSort = false;
}

void CKLBSWFMovie::rebuildRecurse(CKLBNode* pNode, u32* pIndex, CKLBRenderingManager& pRdr) {
	CKLBSWFMovie* pBrother = (CKLBSWFMovie*)pNode;
	while (pBrother) {
		//
		// Child first.
		//
		if (pBrother->m_pChild) {
			rebuildRecurse(pBrother->m_pChild, pIndex, pRdr);
		}

		//
		// Process node itself
		//
		for (u32 n=0; n<pBrother->m_renderCount; n++) {
			CKLBRenderCommand* pRCommand = pBrother->m_pRender[n];
			if (pRCommand) {
				*pIndex = *pIndex + 1; // Increment global pointer.
				if (pRCommand->getOrder() != *pIndex) {	// Optimization : if order did not change.
					pRCommand->changeOrder(pRdr, *pIndex);
				}
			}
		}

		pBrother = (CKLBSWFMovie*)pBrother->m_pBrother;	// Cast to access ancestor protected.
	}
}

CKLBNode* CKLBSWFMovie::addMovie(u16 movieID, u16 layer) {
	return m_player->addMovieB(movieID, layer, NULL, this, NULL, 0);
}

void CKLBSWFMovie::removeMovie(CKLBNode* pMovie) {
	this->removeNode(pMovie);
}

// -----------------------------------------------------------------
//   Perform Rendering.

// ##########################################
//
//   Test Porting Layer Implementation.
//
// ##########################################

// LATER RP : may need some API extension to free all sub movies also ?
// LATER RP : may need some API to replace bitmaps already loaded, ...
