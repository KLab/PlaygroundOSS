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
#include "CKLBCanvasSprite.h"
#include "mem.h"

CKLBCanvasSprite* CKLBRenderingManager::allocateCommandCanvasSprite(
	u32 vertexCount, 
	u32 indexCount, 
	u32 priority)
{
	CKLBCanvasSprite* pSpr = KLBNEW(CKLBCanvasSprite);
	if (pSpr) {
		if (pSpr->setupCanvas(vertexCount, indexCount)) {
			pSpr->m_pAllocNext			= m_pAllocatedSpriteList;
			if (m_pAllocatedSpriteList) {
				m_pAllocatedSpriteList->m_pAllocPrev = pSpr;
			}
			m_pAllocatedSpriteList		= pSpr;
			pSpr->m_uiOrder				= priority;
			return pSpr;
		}
		KLBDELETE(pSpr);
	}
	return NULL;
}

CKLBCanvasSprite::CKLBCanvasSprite()
:CKLBSprite()
,m_freeze	(false)
{
}

CKLBCanvasSprite::~CKLBCanvasSprite() {
}

void CKLBCanvasSprite::setupTexture(CKLBTextureAsset* pTexture) {
	_internalImg.m_pTextureAsset	= pTexture;
	m_pTexture			= pTexture->m_pTextureUsage;
}

bool CKLBCanvasSprite::setupCanvas(u32 vertexCount, u32 indexCount) {
	_internalImg.m_bAllocatedOutsideTexture = true;

	// Vertex & index count
	_internalImg.m_pTextureAsset	= NULL; //pTexture;

	float* buf	=	KLBNEWA(float, (vertexCount*VERTEX_SIZE) + indexCount);

	_internalImg.m_pXYCoord			= buf;
	_internalImg.m_pUVCoord			= &buf[vertexCount*(VERTEX_SIZE-2)];
	_internalImg.m_pIndex			= (u16*)&buf[vertexCount*VERTEX_SIZE];

	// Pos Transform
	float*	arr						= KLBNEWA(float,vertexCount* (VERTEX_SIZE+2));
	u32* arrCol						= (u32*)&arr[vertexCount * VERTEX_SIZE];

	bool res = (_internalImg.m_pXYCoord && arr);
	if (res) {
		for (int n=0; n < MAX_SECTION; n++) {
			m_dynSection[n].lengthFloat	= 0;
			m_dynSection[n].start		= 0;
			m_dynSection[n].started		= false;
		}

		m_pImageAsset		= &_internalImg;
		m_pVertex			= arr;
		m_pColors			= arrCol;
		m_pIndex			= _internalImg.m_pIndex;	// Cache
		m_uiMaxVertexCount	= (u16)vertexCount;
		m_uiMaxIndexCount	= (u16)indexCount;

		m_uiStatus			= FLAG_XYUPDATE | FLAG_COLORUPDATE | FLAG_UVUPDATE;

		
		m_uiIndexCount = 1; // Force clear()
		clear();

		this->switchImage(&_internalImg);
	} else {
		if	(arr)		{ KLBDELETEA(arr);		}		
		// Other arrays destroyed when this object is destroyed.

	}
	return res;
}

void CKLBCanvasSprite::freeze(bool freeze) {
	m_freeze = freeze;
}

bool CKLBCanvasSprite::clear() {
	if (m_uiIndexCount != 0) {
		m_uiVertexCount		= 0;
		m_uiIndexCount		= 0;
		_internalImg.m_uiIndexCount		= 0;
		_internalImg.m_uiVertexCount	= 0;
		m_uiStatus						|= FLAG_BUFFERSHIFT;
		m_pFillColors		= m_pColors;
		m_pFillVertex		= _internalImg.m_pXYCoord;
		m_pFillUV			= _internalImg.m_pUVCoord;
		m_pFillIndex		= m_pIndex;
		return true;
	} else {
		return false;
	}
}

void CKLBCanvasSprite::startDynamicSection(u32 section) {
	if ((section < MAX_SECTION) && (!m_dynSection[section].started)) {
		m_dynSection[section].lengthFloat	= 0;
		m_dynSection[section].start			= _internalImg.m_uiVertexCount<<1;
		m_dynSection[section].started		= true;
	} else {
		klb_assertAlways("Canvas section out of range or not ended");
	}
}

void CKLBCanvasSprite::endDynamicSection(u32 section) {
	if ((section < MAX_SECTION) && (m_dynSection[section].started)) {
		m_dynSection[section].started		= false;
		m_dynSection[section].lengthFloat	= (_internalImg.m_uiVertexCount<<1) - m_dynSection[section].start;
	} else {
		klb_assertAlways("Canvas section out of range or not started");
	}
}

void CKLBCanvasSprite::dynamicSectionTranslate(u32 section, float x, float y) {
	klb_assert(((section < MAX_SECTION) && (!m_dynSection[section].started)),"Canvas section out of range or not defined completly");

	int fCount = m_dynSection[section].lengthFloat;

	float* pFillVertex	= &_internalImg.m_pXYCoord[m_dynSection[section].start];
	// Apply Translation.
	for (int n=0; n < (fCount>>1); n++) {
		pFillVertex[0] = x + pFillVertex[0];	// X
		pFillVertex[1] = y + pFillVertex[1];	// Y
		pFillVertex += 2;
	}
	m_uiStatus |= FLAG_XYUPDATE;
}

void CKLBCanvasSprite::dynamicSectionColor(u32 section, u32 color) {
	klb_assert(((section < MAX_SECTION) && (!m_dynSection[section].started)),"Canvas section out of range or not defined completly");

	int cCount			= m_dynSection[section].lengthFloat>>1;
	u32* pFillColors	= &m_pColors[m_dynSection[section].start>>1];
	memset32(pFillColors,	color, cCount * sizeof(u32));
	m_uiStatus |= FLAG_COLORUPDATE;
}

void CKLBCanvasSprite::doUVAndColor(CKLBImageAsset* pImage, u32 color, u16 fCount, u16 iCount) {
	// Apply UV
	memcpy32(m_pFillUV,		pImage->getUVBuffer(), fCount * sizeof(float));

	// Apply Color
	memset32(m_pFillColors,	color, (fCount>>1) * sizeof(u32));

	// Update All Coord / UV counter
	m_pFillUV	  += fCount;
	m_pFillColors += (fCount>>1);

	u16  start	= _internalImg.m_uiVertexCount;
	_internalImg.m_uiVertexCount	+= (fCount>>1);
	m_uiVertexCount					 = _internalImg.m_uiVertexCount;

	// Apply Indexes
	u16* ptrIdx = m_pFillIndex;
	u16* srcIdx = pImage->getIndexBuffer();
	for (int n=0; n < iCount; n++) {
		ptrIdx[n] = start + srcIdx[n]; 
	}

	// Update Index Counter
	m_pFillIndex					+= iCount;
	_internalImg.m_uiIndexCount		+= iCount;
	m_uiIndexCount					= _internalImg.m_uiIndexCount;
	m_uiStatus						|= FLAG_BUFFERSHIFT | FLAG_XYUPDATE | FLAG_COLORUPDATE | FLAG_UVUPDATE;
}

bool CKLBCanvasSprite::drawImage(float x, float y, CKLBImageAsset* pImage, u32 color) {
	u16 vCount = (u16)pImage->getVertexCount() * 2;
	u16 iCount = (u16)pImage->getIndexCount();

	// Apply Translation.
	float* pSrcCoord = pImage->getXYBuffer();
	for (u16 n=0; n < (vCount>>1); n++) {
		*m_pFillVertex++ = x + *pSrcCoord++;	// X
		*m_pFillVertex++ = y + *pSrcCoord++;	// Y
	}

	doUVAndColor(pImage, color, vCount, iCount);
	
	klb_assert(_internalImg.m_uiIndexCount  <= m_uiMaxIndexCount,  "Reached Limit");
	klb_assert(_internalImg.m_uiVertexCount <= m_uiMaxVertexCount, "Reached Limit");
	return true;
}

bool CKLBCanvasSprite::drawImageClip(float x, float y, CKLBImageAsset* pImage, float percW, float percH, u32 color) {
	u16 vCount = (u16)pImage->getVertexCount() * 2;
	u16 iCount = (u16)pImage->getIndexCount();

	// Apply Translation.
	float* pSrcCoord = pImage->getXYBuffer();
	for (u16 n=0; n < (vCount>>1); n++) {
		*m_pFillVertex++ = x + ((*pSrcCoord++) * percW);	// X
		*m_pFillVertex++ = y + ((*pSrcCoord++) * percH);	// Y
	}

	// UV
	float* pSrcUV = pImage->getUVBuffer();

	m_pFillUV[0] = pSrcUV[0];
	m_pFillUV[1] = pSrcUV[1];

	m_pFillUV[2] = pSrcUV[0] + (percW * (pSrcUV[2] - pSrcUV[0]));
	m_pFillUV[3] = pSrcUV[1] + (percH * (pSrcUV[3] - pSrcUV[1]));

	m_pFillUV[4] = pSrcUV[0] + (percW * (pSrcUV[4] - pSrcUV[0]));
	m_pFillUV[5] = pSrcUV[1] + (percH * (pSrcUV[5] - pSrcUV[1]));

	m_pFillUV[6] = pSrcUV[0] + (percW * (pSrcUV[6] - pSrcUV[0]));
	m_pFillUV[7] = pSrcUV[1] + (percH * (pSrcUV[7] - pSrcUV[1]));

	m_pFillUV += 8;

	// Update Vertex count.
	u16  start	= _internalImg.m_uiVertexCount;
	_internalImg.m_uiVertexCount	+= (vCount>>1);
	m_uiVertexCount					 = _internalImg.m_uiVertexCount;

	// Apply Indexes
	u16* ptrIdx = m_pFillIndex;
	u16* srcIdx = pImage->getIndexBuffer();
	for (int n=0; n < iCount; n++) {
		ptrIdx[n] = start + srcIdx[n]; 
	}

	// Color
	memset32(m_pFillColors,	color, (vCount>>1) * sizeof(u32));
	m_pFillIndex					+= iCount;
	_internalImg.m_uiIndexCount		+= iCount;
	m_uiIndexCount					= _internalImg.m_uiIndexCount;
	m_uiStatus						|= FLAG_BUFFERSHIFT | FLAG_XYUPDATE | FLAG_COLORUPDATE | FLAG_UVUPDATE;
	return true;
}

bool CKLBCanvasSprite::drawScale(float x, float y, float scale, CKLBImageAsset* pImage, u32 color) {
	u16 vCount = (u16)pImage->getVertexCount() * 2;
	u16 iCount = (u16)pImage->getIndexCount();

	// Apply Translation.
	float* pSrcCoord = pImage->getXYBuffer();
	for (u16 n=0; n < (vCount>>1); n++) {
		*m_pFillVertex++ = x + (*pSrcCoord++) * scale;	// X
		*m_pFillVertex++ = y + (*pSrcCoord++) * scale;	// Y
	}

	doUVAndColor(pImage, color, vCount, iCount);

	klb_assert(_internalImg.m_uiIndexCount  <= m_uiMaxIndexCount,  "Reached Limit");
	klb_assert(_internalImg.m_uiVertexCount <= m_uiMaxVertexCount, "Reached Limit");
	return true;
}

void CKLBCanvasSprite::setFillUV(float u, float v) 
{
	m_fillU = u;
	m_fillV = v;
}

bool CKLBCanvasSprite::fillRect(float x, float y, float w, float h, u32 color) {
	//
	// Coordinate
	//
	*m_pFillVertex++ = x;
	*m_pFillVertex++ = y;

	float x1 = x + w;
	*m_pFillVertex++ = x1;
	*m_pFillVertex++ = y;

	float y1 = y + h;
	*m_pFillVertex++ = x1;
	*m_pFillVertex++ = y1;

	*m_pFillVertex++ = x;
	*m_pFillVertex++ = y1;

	//
	// U,V : 0.0f, 0.0f
	//
	*m_pFillUV++ = m_fillU;
	*m_pFillUV++ = m_fillV;
	*m_pFillUV++ = m_fillU;
	*m_pFillUV++ = m_fillV;
	*m_pFillUV++ = m_fillU;
	*m_pFillUV++ = m_fillV;
	*m_pFillUV++ = m_fillU;
	*m_pFillUV++ = m_fillV;

	memset32(m_pFillColors, color, 4);
	m_pFillColors += 4;


	// Apply Indexes
	u16  start	= _internalImg.m_uiVertexCount;
	_internalImg.m_uiVertexCount	+= 4;
	m_uiVertexCount					= _internalImg.m_uiVertexCount;

	u16* ptrIdx = m_pFillIndex;

	*ptrIdx++ = start;		// 0 
	*ptrIdx++ = start+1;	// 1 
	*ptrIdx++ = start+3;	// 3
	
	*ptrIdx++ = start+1;	// 1
	*ptrIdx++ = start+2;	// 2
	*ptrIdx++ = start+3;	// 3

	// Update Index Counter
	m_pFillIndex					= ptrIdx;
	_internalImg.m_uiIndexCount	   += 6;
	m_uiIndexCount					= _internalImg.m_uiIndexCount;

	m_uiStatus						|= FLAG_BUFFERSHIFT | FLAG_XYUPDATE | FLAG_COLORUPDATE | FLAG_UVUPDATE;

	klb_assert(_internalImg.m_uiIndexCount  <= m_uiMaxIndexCount,  "Reached Limit");
	klb_assert(_internalImg.m_uiVertexCount <= m_uiMaxVertexCount, "Reached Limit");
	return true;
}
