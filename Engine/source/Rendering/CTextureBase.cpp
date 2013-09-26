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
#include "RenderingFramework.h"

CTextureBase::CTextureBase()
:pSWAlphaMap	(NULL)
{
	// Do nothing.
}

CTextureBase::~CTextureBase() {
	KLBDELETEA(pSWAlphaMap);
}

void CTextureBase::assignSWAlphaBuffer(u8* pBuffer) {
	pSWAlphaMap = pBuffer;
}

u32	CTextureBase::isAlpha	(float u,float v) {
	klb_assert(((u >= 0.0f) && (u <= 1.0f)),"Out of range UV");
	klb_assert(((v >= 0.0f) && (v <= 1.0f)),"Out of range UV");
	// Optimize : have (width/tile)  (height/tile) as float already.
	int x		= ((int)(u * (this->getWidth ())))>>3;
	int y		= ((int)(v * (this->getHeight())))>>3;
	int adr		= (x+(y*(this->getWidth()>>3)));
	int adrByte = adr>>3;
	int adrBit	= adr&7; // 0..7 order
	return (pSWAlphaMap[adrByte] >> adrBit) & 1;
}

//
// Texture base.
//

CTextureUsage*	CTextureBase::createUsage() {
	usageCount++;
	if (usageCount == 1) {
		return &this->usageList;
	} else {
		CTextureUsage* pItem = KLBNEW(CTextureUsage);
		if (pItem) {
			pItem->init(this);
			pItem->pNext = this->usageList.pNext;
			this->usageList.pNext = pItem;
		}
		return pItem;
	}
}

void CTextureBase::releaseUsage(CTextureUsage* pUsage) {
	if (pUsage) { return; }

	CTextureUsage* parse = this->usageList.pNext;
	CTextureUsage* prev = null;
	while (parse != pUsage) {
		prev = parse;
		parse = parse->pNext;
	}

	if (parse == pUsage) {
		if (prev == null) {
			this->usageList.pNext = parse->pNext;
		} else {
			prev->pNext = parse->pNext;
		}
	}

	KLBDELETE(pUsage);
}

void CTextureBase::releaseSubTextures() {
	if (pChild) {
		CTextureBase* pBase = this->pChild;
		while (pBase) {
			CTextureBase* pNext = pBase->pBrother;
			pBase->releaseSubTextures();
			KLBDELETE(pBase);
			pBase = pNext;
		}
	}
}

void CTexture::makeEmptyShell() {
	if (texture) {
		dglDeleteTextures(1, &texture);
		texture = 0;
	}
	if (textureDoubleBuff) {
		dglDeleteTextures(1, &textureDoubleBuff);
		textureDoubleBuff = 0;
	}
}

CSubTexture*	CTextureBase::setSubAtlas(bool asFont, s32 x, s32 y, s32 width, s32 height) {
	CSubTexture* pSub = asFont ? KLBNEW(CFontTexture) : KLBNEW(CSubTexture);
	if (pSub) {
		pSub->width = width;
		pSub->height = height;
		pSub->x = x + this->x;
		pSub->y = y + this->y;

		pSub->pChild	= null;
		pSub->pMaster	= this->pMaster;
		pSub->pMgr		= this->pMgr;
		pSub->pParent	= pMaster;
		pSub->usageList.init(this);
		pSub->usageCount	= 0;

		pSub->pBrother	= this->pChild;
		if (this->pChild == null) {
			this->pChild = (CTextureBase*)pSub;
		}
	}
	return pSub;
}

void	CTextureBase::releaseSubTexture(CSubTexture* /*pSubTex*/) {
	// ### NOT IMPLEMENTED
	/*
	if (pChild) {
		CTextureBase* pParse = pChild;
		while (pParse) {
			CTextureBase* pParseNext = pParse->pBrother;
			pParse->releaseSubTextures();
			KLBDELETE(pParse);
			pParse = pParseNext;
		}
		pChild = null;
	}*/
}

void CTextureBase::updateTextureFromFrame(u32 mipLevel, s32 dstX, s32 dstY, s32 srcX, s32 srcY, s32 srcW, s32 srcH) {
	dglBindTexture(GL_TEXTURE_2D,pMaster->getWorkingTexture());

	dstX += this->x;
	dstY += this->y;

	dglCopyTexSubImage2D (GL_TEXTURE_2D, mipLevel, dstX, dstY, srcX, srcY, srcW, srcH);
}

bool	CTextureBase::updateTexture(s32 x, s32 y, s32 width, s32 height, void* data, s32 dataSize) {
	x = this->x + x;
	y = this->y + y;

	dglBindTexture(GL_TEXTURE_2D,pMaster->getWorkingTexture());

	dglPixelStorei(GL_PACK_ALIGNMENT,	1);
	dglPixelStorei(GL_UNPACK_ALIGNMENT,	1);
	if (pMaster->isCompressed) {
		#ifdef STD_OPENGL
			#pragma message ("Warning : feature not supported with standard OpenGL for now")
		#else
			dglCompressedTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height,
					pMaster->format,
					dataSize,
					data);
		#endif
	} else {
		dglTexSubImage2D (GL_TEXTURE_2D, 0, x, y, width, height,
				pMaster->channels,
				pMaster->format,
				data);
	}

	if (dglGetError()) {
		klb_assertAlways("Invalid texture update");
		return false;
	} else {
		return true;
	}
}

void CTextureBase::convertPixelToRenderUV(s32 x, s32 y, UVCOMPUTE_MODE sampling, float* u, float* v) {
	float offU = 0.0f;
	float offV = 0.0f;

	// Absolute coordinate in top parent.
	x = this->x + x;
	y = this->y + y;

	if (sampling == CENTROID) {				// Can optimize.
		offU = pMaster->UPerPixel * 0.5f;
		offV = pMaster->VPerPixel * 0.5f;
	}

	*u = (x * pMaster->UPerPixel) + offU;
	*v = (y * pMaster->VPerPixel) + offV;
}

void 	CTextureBase::releaseUsage() {
	//
	// Parse the atlas tree of texture.
	//
	if (pChild) {
		CTextureBase* pParse = pChild;
		while (pParse) {
			pParse->releaseUsage();
			pParse = pParse->pBrother;
		}
	}

	// Release usage.
	CTextureUsage* pUsage = this->usageList.pNext;
	while (pUsage) {
		CTextureUsage* pNextUsage = pUsage->pNext;
		KLBDELETE(pUsage);
		pUsage = pNextUsage;
	}
}
