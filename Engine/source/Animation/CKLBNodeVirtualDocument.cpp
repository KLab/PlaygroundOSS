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
#include "CKLBNodeVirtualDocument.h"

#include "CKLBTexturePacker.h"
TexturePacker& mgrPacker = TexturePacker::getInstance();

static u32 convertARGB32_RGBA8(u32 argb) {
	u32 dst;
	u8* pDst = (u8*)&dst;
	pDst[0]  = argb>>16;    // R
	pDst[1]  = argb>>8;     // G
	pDst[2]  = argb;        // B
	pDst[3]  = argb>>24;    // A
	return dst;
}

// RGBA8 32 bit encoded
u16 getTo4444(u32 color) {
	u8* pCol = (u8*)&color;

	// Base color.
	u16 col	= 	      ((pCol[2]     ) & 0x00F0)		// Blue
					| ((pCol[1] << 4) & 0x0F00)		// Green
					| ((pCol[0] << 8) & 0xF000)		// Red
					| ((pCol[3] >> 4))				// Alpha
					;
	return col;
}

void RenderContext::setClip	(s32 x0, s32 y0, s32 x1, s32 y1) {
	if (x0 < 0)				{ x0 = 0; }
	if (y0 < 0)				{ y0 = 0; }
	if (x1 > targetWidth)	{ x1 = targetWidth;		}
	if (y1 > targetHeight)	{ y1 = targetHeight;	}

	clipX0 = x0;
	clipY0 = y0;
	clipX1 = x1;
	clipY1 = y1;
}

void RenderContext::setPixelClip(s32 x1, s32 y1, u32 color) {
	if ((x1 < clipX0) || (y1 < clipY0) || (x1 >= clipX1) || (y1 >= clipY1)) {
		return;
	}

	u8* pCol = (u8*)&color;
	if (pCol[3] != 255) {
		int alpha	= pCol[3]; alpha += alpha>>7;		// 0..256
		int nalpha	= 256 - alpha;						// 256..0

		int cb		= alpha * pCol[0];
		int cg		= alpha * pCol[1];
		int cr		= alpha * pCol[2];
		int ca		= alpha * pCol[3];

		u32* pBuf = &pBuffer[x1 + (stride * y1)];
		u8* p8Buf = (u8*)pBuf;

		int b = ((p8Buf[0] * nalpha) + cb)>>8;
		int g = ((p8Buf[1] * nalpha) + cg)>>8;
		int r = ((p8Buf[2] * nalpha) + cr)>>8;
		int ar= ((p8Buf[3] * nalpha) + ca)>>8; // Do NOT use scale (255 vs 256)

		p8Buf	[0] = b;  // B
		p8Buf	[1] = g;  // G
		p8Buf	[2] = r;  // R
		p8Buf	[3] = ar; // A
	} else {
		pBuffer[x1 + (stride * y1)] = color;
	}
}

void RenderContext::setPixelClip4444(s32 x1, s32 y1, u16 color) {
	if ((x1 < clipX0) || (y1 < clipY0) || (x1 >= clipX1) || (y1 >= clipY1)) {
		return;
	}

	int alpha = color >> 12;
	if (alpha != 0xF) {
			alpha  += alpha>>3;							// 0..16
		int nalpha	= 16 - alpha;						// 16..0

		// 4.4 precision
		int cb		= alpha * (color & 0x00F0);
		int cg		= alpha * (color & 0x0F00);
		int cr		= alpha * (color & 0xF000);
		int ca		= alpha * (color & 0x000F);

		u16* pBuf = &((u16*)pBuffer)[x1 + (stride * y1)];
		u16  col = *pBuf;

		int b = (((col & 0x00F0) * nalpha) + cb)>>4;
		int g = (((col & 0x0F00) * nalpha) + cg)>>4;
		int r = (((col & 0xF000) * nalpha) + cr)>>4;
		int ar= (((col & 0x000F) * nalpha) + ca)>>4; // Do NOT use scale (255 vs 256)

		*pBuf++ = (r & 0xF000) | (g & 0x0F00) | (b & 0x00F0) | (ar & 0x000F);
	} else {
		((u16*)pBuffer)[x1 + (stride * y1)] = color;
	}
}

void RenderContext::drawLine(s32 x1, s32 y1, s32 x2, s32 y2, u32 color) {
	x2 -= offsetX;
	x1 -= offsetX;
	y2 -= offsetY;
	y1 -= offsetY;

	s32 d, dx, dy, delta, xincr, x, y;

	dx = x2 - x1; if (dx < 0) { dx = -dx; }
	dy = y2 - y1; if (dy < 0) { dy = -dy; }

	s32 inv = (dx >= dy);
	if (inv) {
		// Swap X and Y
		x = x1; x1 = y1; y1 = x;
		x = x2; x2 = y2; y2 = x;
	}
	
	if (y1 > y2) {
		x = x1; x1 = x2; x2 = x;
		y = y1; y1 = y2; y2 = y;
	}

	xincr = x2 > x1 ? 1 : -1;
	dy = y2 - y1;
	dx = x2 - x1;
	if (dx < 0) { dx = -dx; }
	delta = 2 * dx;
	d = delta - dy;

	x = x1;

	if (format == 4) {
		for (y = y1; y <= y2; ++y) {
			if (inv) {
				setPixelClip(y, x, color);
			} else {
				setPixelClip(x, y, color);
			}
		
			d += delta;
			if (d >= 0) {
				x += xincr;
				d -= (dy<<1);
			}
		}
	} else {
		u16 color16 = getTo4444(color);

		for (y = y1; y <= y2; ++y) {
			if (inv) {
				setPixelClip4444(y, x, color16);
			} else {
				setPixelClip4444(x, y, color16);
			}
		
			d += delta;
			if (d >= 0) {
				x += xincr;
				d -= (dy<<1);
			}
		}
	}
}

void RenderContext::drawRect(s32 x0, s32 y0, s32 x1, s32 y1, u32 color) {
	// Offset done internally.
	drawLine(x0,y0,x1,y0,color);
	drawLine(x1,y0,x1,y1,color);
	drawLine(x1,y1,x0,y1,color);
	drawLine(x0,y1,x0,y0,color);
}

void RenderContext::fillRect(s32 x0, s32 y0, s32 x1, s32 y1, u32 color, bool forceFill) {
	x0 -= offsetX;
	x1 -= offsetX;
	y0 -= offsetY;
	y1 -= offsetY;

	if (x0 < clipX0)	{ x0 = clipX0; }
	if (y0 < clipY0)	{ y0 = clipY0; }
	if (x1 > clipX1)	{ x1 = clipX1; }
	if (y1 > clipY1)	{ y1 = clipY1; }

	if (((color>>24) == 255) || (forceFill)) {
		//
		// OPTIMIZE : use fully ptr, avoid x,y increment, use memcpy32.
		//
		if (format == 4) {
			u32* pBuf = &pBuffer[x0 + (stride * y0)];

			s32 startX0 = x0;
			while (y0 < y1) {
				x0 = startX0;
				while (x0 < x1) {
					*pBuf++ = color;
					x0++;
				}
				pBuf += stride - (x1 - startX0);	// Delta Stride.
				y0++;
			}
		} else {
			u16* pBuf = (u16*)&(((u8*)pBuffer)[x0 + (stride * format * y0)]);

			u16 color16 = getTo4444(color);

			s32 startX0 = x0;
			while (y0 < y1) {
				x0 = startX0;
				while (x0 < x1) {
					*pBuf++ = color16;
					x0++;
				}
				pBuf += stride - (x1 - startX0);	// Delta Stride.
				y0++;
			}
		}
	} else {

		//
		// color is 8 Bit RGBA
		//
		u8* pCol	= (u8*)&color;

		//
		// PreAlpha
		//
		int alpha	= pCol[3]; alpha += alpha>>7;		// 0..256
		int nalpha	= 256 - alpha;						// 256..0

		int cb		= alpha * pCol[0];
		int cg		= alpha * pCol[1];
		int cr		= alpha * pCol[2];
		int ca		= alpha * pCol[3];

		//
		// Dst is also RGBA
		//
		if (format == 4) {
			u32* pBuf = &pBuffer[x0 + (stride * y0)];

			s32 startX0 = x0;
			while (y0 < y1) {
				x0 = startX0;
				while (x0 < x1) {
					u8* p8Buf = (u8*)pBuf;

					int b = ((p8Buf[0] * nalpha) + cb)>>8;
					int g = ((p8Buf[1] * nalpha) + cg)>>8;
					int r = ((p8Buf[2] * nalpha) + cr)>>8;
					int ar= ((p8Buf[3] * nalpha) + ca)>>8; // Do NOT use scale (255 vs 256)

					p8Buf	[0] = b;  // B
					p8Buf	[1] = g;  // G
					p8Buf	[2] = r;  // R
					p8Buf	[3] = ar; // A

					pBuf++;
					x0++;
				}
				pBuf += stride - (x1 - startX0);	// Delta Stride.
				y0++;
			}
		} else {
			u16* pBuf = (u16*)&(((u8*)pBuffer)[x0 + (stride * format * y0)]);

			// 8.8 -> 4.8 precision, then at correct place for addition
			cb >>= 4; cb <<= 4;
			cg >>= 4; cg <<= 8;
			cr >>= 4; cr <<= 12;
			ca >>= 4; // ca <<= 0;

			s32 startX0 = x0;
			while (y0 < y1) {
				x0 = startX0;
				while (x0 < x1) {
					u16  col = *pBuf;

					int b = (((col & 0x00F0) * nalpha) + cb)>>8;
					int g = (((col & 0x0F00) * nalpha) + cg)>>8;
					int r = (((col & 0xF000) * nalpha) + cr)>>8;
					int ar= (((col & 0x000F) * nalpha) + ca)>>8; // Do NOT use scale (255 vs 256)

					*pBuf++ = (r & 0xF000) | (g & 0x0F00) | (b & 0x00F0) | (ar & 0x000F);
					x0++;
				}
				pBuf += stride - (x1 - startX0);	// Delta Stride in pixel
				y0++;
			}
		}
	}
}

#include "CKLBTextTempBuffer.h"

// #define INTERNAL_FILL_WITH_COLOR_TEXPACKER
#ifdef INTERNAL_FILL_WITH_COLOR_TEXPACKER

static u32 colorcount = 0;
u32 getTestColor() {
	colorcount = (colorcount+1) & 0xF;

	u32 colorFill = 0x80FFFFFF;

	switch (colorcount) {
	case 0:	colorFill = 0xFF00FF00; // Green
		break;
	case 1:	colorFill = 0xFFFF0000; // Red
		break;
	case 2:	colorFill = 0xFF0000FF; // Blue
		break;
	case 3:	colorFill = 0xFFFF00FF; // Magenta
		break;
	case 4:	colorFill = 0xFF00FFFF; // Yellow
		break;
	case 5:	colorFill = 0xFFFFFF00; // Cyan
		break;

	case 6:	colorFill = 0xFF80FF80;
		break;
	case 7:	colorFill = 0xFFFF8080;
		break;
	case 8:	colorFill = 0xFF8080FF;
		break;
	case 9:	colorFill = 0xFFFF80FF;
		break;
	case 10:colorFill = 0xFF80FFFF;
		break;
	case 11:colorFill = 0xFFFFFF80;
		break;

	case 12:colorFill = 0xFF80FF00;
		break;
	case 13:colorFill = 0xFFFF8000;
		break;
	case 14:colorFill = 0xFF0080FF;
		break;
	case 15:colorFill = 0xFFFF0080;
		break;
	}

	return colorFill;
}
#endif

void RenderContext::drawText(s32 x , s32 y , char* string  , u32 color, void* font, bool docMode) {
	IPlatformRequest& platform = CPFInterface::getInstance().platform();

	x -= offsetX;
	y -= offsetY;

	//
	// 1. Reset Tmp Buffer
	//
	if (!docMode) {
		memset(pBuffer, 0, this->stride * format * this->targetHeight);
	}

	//
	// 2. Render text
	//
	platform.renderText(	string,
							font,
							color,
							this->targetWidth,
							this->targetHeight,
							(u8*)pBuffer,
							this->stride * format,	// Byte stride
							x,
							y,
							(format != 4));
}

void RenderContext::drawImage(s32 x , s32 y , SDrawCommand* pCommand  , u8 alpha) {
	CKLBImageAsset* pImg = (CKLBImageAsset*)pCommand->ptr;

	x -= offsetX;
	y -= offsetY;

	// Screen Space size
	s32 sdx = pCommand->x1 - pCommand->x0;
	s32 sdy = pCommand->y1 - pCommand->y0;
	// Screen Image Corner
	s32 x0 = x;
	s32 y0 = y;
	s32 x1 = x+sdx;
	s32 y1 = y+sdy;
	// Texture Space Top Left
	s32 texX	= pCommand->sx0;
	s32 texY	= pCommand->sy0;

	// Completly outside : skip
	if ((pImg == NULL) || (x1 <= clipX0) || (y1 <= clipY0) || (x0 >= clipX1) || (y0 >= clipY1)) {
		return;
	}

	// Fully inside or partially clipped.
	s32 delta;

	//
	// Top Left Corner Test
	//

	delta = x0 - clipX0;
	// Shorten width  ?
	if (delta < 0)	{	sdx += delta;
						// Left corner in texture space
						if (pCommand->swap) { texY -= delta; } else { texX -= delta; }
						x0 = clipX0;
					}
	// Shorten height ?
	delta = y0 - clipY0;
	if (delta < 0)	{	sdy += delta;	x0 = clipX0;	
						// Left corner in texture space
						if (pCommand->swap) { texX -= delta; } else { texY -= delta; }
					}

	//
	// Bottom Right Corner Test
	//

	delta = clipX1 - x1;
	// Shorten width  ?
	if (delta < 0) { sdx += delta; }
	// Shorten height ?
	delta = clipY1 - y1;
	if (delta < 0) { sdy += delta; }

	u8* pix		= pImg->m_pTextureAsset->m_softTexture;
	s32 lstride	= pImg->m_pTextureAsset->m_width;

	pix = &pix[(texX + (texY * lstride)) * 4];

	lstride *= 4;

	//
	// === Draw ===
	//
	u8* pBuf = (u8*)&pBuffer[x0 + (stride * y0)];

	s32 jmpStrideBuf = (stride - sdx) * 4;
	s32 jmpStrideHoriz;
	s32 jmpStrideVert;

	if (pCommand->swap) {
		jmpStrideHoriz	= lstride;
		jmpStrideVert	= (lstride * (-sdx)) + 4; // Roll back Y pixel in texture space, advance +1 pixel
	} else {
		jmpStrideHoriz	= 4;
		jmpStrideVert	= lstride - (sdx * 4);
	}

	int galpha		= alpha + (alpha>>7);		// 0..256
	// int gnalpha		= 256 - galpha;				// 256..0

	if (format == 4) {
		for (int y=0; y < sdy; y++) {
			for (int x=0; x < sdx; x++) {
				// 0..255 Alpha
				int ca		= (galpha * pix[3] >> 8);	// Pixel Alpha * Global Alpha
				int alpha	= ca + (ca >> 7);
				int nAlpha  = 256 - alpha;

				pBuf[0] = ((pBuf[0] * nAlpha) + (alpha * pix[0])) >> 8; // R
				pBuf[1] = ((pBuf[1] * nAlpha) + (alpha * pix[1])) >> 8; // G
				pBuf[2] = ((pBuf[2] * nAlpha) + (alpha * pix[2])) >> 8; // B
				pBuf[3] = ((pBuf[3] * nAlpha) + (alpha * pix[3])) >> 8; // A

				pBuf+=4;
				pix += jmpStrideHoriz;
			}
			pBuf += jmpStrideBuf;
			pix  += jmpStrideVert;
		}
	} else {
		klb_assertAlways("IMAGE RENDER NOT SUPPORTED in 4444 for virtual doc");
	}
}

#ifdef DEBUG_TEXTURE_PACKER

struct VirtualDocElement {
	static VirtualDocElement* getDocElement(CKLBNodeVirtualDocument* pDoc);
	VirtualDocElement*			pNext;
	CKLBNodeVirtualDocument*	pDoc;
};

VirtualDocElement*	gDocumentList = NULL;
CKLBNodeVirtualDocument*	pIgnore	= NULL;

void setIgnoreVirtualDoc(CKLBNodeVirtualDocument* pDoc) {
	pIgnore = pDoc;	
}

VirtualDocElement* VirtualDocElement::getDocElement(CKLBNodeVirtualDocument* pDoc) {
	VirtualDocElement* pElem = new VirtualDocElement();
	pElem->pDoc = pDoc;
	pElem->pNext= NULL;
	return pElem;
}

void registerVirtualDoc(CKLBNodeVirtualDocument* pDoc) {
	VirtualDocElement* pNewElem = VirtualDocElement::getDocElement(pDoc);
	if (pNewElem) {
		pNewElem->pNext	= gDocumentList;
		gDocumentList	= pNewElem;
	} else {
		klb_assertAlways("allo failure");
	}
}

void unregisterVirtualDoc(CKLBNodeVirtualDocument* pDoc) {
	VirtualDocElement* pElem = gDocumentList;
	VirtualDocElement* pPrev = NULL;

	while (pElem) {
		if (pElem->pDoc == pDoc) {
			break;
		}
		pPrev = pElem;
		pElem = pElem->pNext;
	}

	if (pElem) {
		if (pPrev == NULL) {
			gDocumentList = pElem->pNext;
		} else {
			pPrev->pNext  = pElem->pNext;
		}
		delete pElem;
	} else {
		klb_assertAlways("Item not found : already removed from list");
	}
}

void checkVirtualDocState() {
	VirtualDocElement* pElem = gDocumentList;
	while (pElem) {
		if (pElem->pDoc != pIgnore) {
			pElem->pDoc->check();
		}
		pElem = pElem->pNext;
	}
}

void dumpVirtualDocState(void* pDoc) {
	printf("=== Dump Virtual Doc List ===\n");
	VirtualDocElement* pElem = gDocumentList;
	while (pElem) {
		if (pElem->pDoc == pDoc) {
			printf("Obj : %8X FOUND !!! \n", pElem->pDoc);
		} else {
			printf("Obj : %8X\n", pElem->pDoc);
		}
		pElem = pElem->pNext;
	}
	printf("=== End Dump ===\n");
}

#endif

CKLBNodeVirtualDocument::CKLBNodeVirtualDocument()
:m_commandArray		(NULL)
,m_commandMaxCount	(0)
,m_CurrentCommand	(0)
,m_isVertical		(false)
,m_bgColor			(0x00000000)
,m_viewPortHeight	(0)
,m_viewPortWidth	(0)
,m_currTile			(0)
,m_prevTile			(0x7FFF)
,m_scroll			(0)
,m_prevScroll		(1)
,m_bDisplay			(true)
,m_tileXStart		(0)
,m_tileYStart		(0)
,m_tileXEnd			(0)
,m_tileYEnd			(0)
,m_documentWidth	(0)
,m_documentHeight	(0)
,m_posX				(0)
,m_posY				(0)
,m_bScroll			(false)
//,m_surfA			(NULL_IDX)
//,m_surfB			(NULL_IDX)
,m_bHasChanged		(false)
{
	m_deleteRender = false; // Force own management of sprite on destruction.
	for(int i = 0; i < 2; i++) {
		m_drawarea[i].tile = NULL;
		m_drawarea[i].softwareBufTile = NULL;
		m_drawarea[i].surf_handle = NULL_IDX;
	}
	/*
	m_softwareBufferTile[0] = NULL;
	m_softwareBufferTile[1] = NULL;
	m_tile				[0] = NULL;
	m_tile				[1] = NULL;
	*/
	for (int n = 0; n < 5; n++) {
		font[n] = NULL;
	}

	m_format = TexturePacker::getCurrentModeTexture();
#ifdef DEBUG_TEXTURE_PACKER
	registerVirtualDoc(this);
#endif
}

CKLBNodeVirtualDocument::~CKLBNodeVirtualDocument() {
	clearRessources(true, true);
	freeDocument();
#ifdef DEBUG_TEXTURE_PACKER
	unregisterVirtualDoc(this);
	mgrPacker.scan(this);
#endif
}

void CKLBNodeVirtualDocument::clearRessources(bool freeSurface, bool freeFonts) {
	if (freeSurface) {
#ifdef DEBUG_TEXTURE_PACKER
		mgrPacker.setCurrentDelete(this);
#endif
		for(int i = 0; i < 2; i++) {
			if(m_drawarea[i].surf_handle != NULL_IDX) {
				mgrPacker.releaseSurface(m_drawarea[i].surf_handle);
			}
			m_drawarea[i].surf_handle = NULL_IDX;
			m_drawarea[i].softwareBufTile = NULL;
		}
		/*
		if (m_surfA != NULL_IDX) {
			mgrPacker.releaseSurface(m_surfA);
		}

		if (m_surfB != NULL_IDX) {
			mgrPacker.releaseSurface(m_surfB);
		}
#ifdef DEBUG_TEXTURE_PACKER
		mgrPacker.setCurrentDelete(NULL);
#endif

		m_surfA = NULL_IDX;
		m_surfB = NULL_IDX;

		m_softwareBufferTile[0] = NULL;
		m_softwareBufferTile[1] = NULL;
		*/
	}

	CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();

	if(m_drawarea[0].tile) {
		setRender(NULL, 0);
		pRdrMgr.releaseCommand(m_drawarea[0].tile);
		if(m_drawarea[1].tile != m_drawarea[0].tile) {
			setRender(NULL,1);
			pRdrMgr.releaseCommand(m_drawarea[1].tile);
		}
	}
	m_drawarea[0].tile = NULL;
	m_drawarea[1].tile = NULL;
/*
	if (m_tile[0]) {
		this->setRender(NULL,0);
		pRdrMgr.releaseCommand(m_tile[0]);
	}

	if (m_tile[1] && m_tile[0] && (m_tile[1] != m_tile[0])) {
		this->setRender(NULL,1);
		pRdrMgr.releaseCommand(m_tile[1]);
	}

	m_tile[1] = NULL;
	m_tile[0] = NULL;
*/
	if(freeFonts) {
		freeFont();
	}
}

void CKLBNodeVirtualDocument::check() {
	klb_assert(m_drawarea[0].softwareBufTile, "VIRTUAL DOC NOT FREED BUT SET TO NULL");
	klb_assert(m_drawarea[0].tile,            "VIRTUAL DOC NOT FREED BUT SET TO NULL");

/*
	if (m_softwareBufferTile[0] == 0) {
		klb_assertAlways("VIRTUAL DOC NOT FREED BUT SET TO NULL");
	}
	if (m_tile[0]==0) {
		klb_assertAlways("VIRTUAL DOC NOT FREED BUT SET TO NULL");
	}
*/
}

void CKLBNodeVirtualDocument::docTextureCompaction(void* ctx, u16 oldsurface, u16 newSurface) {
	CKLBNodeVirtualDocument* pObj = (CKLBNodeVirtualDocument*)ctx;

	// klb_assert((_CrtCheckMemory() != 0), "Heap Error !");
	for(int i = 0; i < 2; i++) {
		if(pObj->m_drawarea[i].surf_handle == oldsurface) {
			VDOCDRAW * pDraw = &(pObj->m_drawarea[i]);
			pDraw->surf_handle = newSurface;

			float u0;
			float v0;
			float u1;
			float v1;
			float stepU;
			float stepV;
			u32*  swBuff;
			mgrPacker.getSurfaceInfo(newSurface, swBuff, u0,v0,u1,v1,stepU,stepV);

			klb_assert(swBuff == pDraw->softwareBufTile, "Consistency of the buffer cannot be taken. ");

			pDraw->leftU	= u0;
			pDraw->upV		= v0;
			pDraw->rightU	= u1;
			pDraw->bottomV	= v1;
			pDraw->stepU	= stepU;
			pDraw->stepV	= stepV;

			pDraw->tile->m_pTexture = mgrPacker.getTextureUsage(newSurface);

			pObj->updateDynSprites(i);

			pObj->markUpMatrix();

			break;
		}
	}
/*
	if (oldsurface == pObj->m_surfA) {
		// Update Object.
		pObj->m_surfA = newSurface;
	} else
	if (oldsurface == pObj->m_surfB) {
		pObj->m_surfB = newSurface;
	}

	// Get UV info
	float u0;
	float v0;
	float u1;
	float v1;
	float stepU;
	float stepV;
	u32*  swBuff;

	mgrPacker.getSurfaceInfo(newSurface, swBuff, u0,v0,u1,v1,stepU,stepV);

	int idx;
	if (pObj->m_softwareBufferTile[0] == swBuff) {
		idx = 0;
	} else if (pObj->m_softwareBufferTile[1] == swBuff) {
		idx = 1;
	} else {
		idx = 0;
		klb_assertAlways("Error");
	}

	// pObj->m_softwareBufferTile[idx] = swBuff; <-- Buffer not reallocated
	pObj->leftU		[idx] = u0;
	pObj->upV		[idx] = v0;
	pObj->rightU	[idx] = u1;
	pObj->bottomV	[idx] = v1;
	pObj->stepU		[idx] = stepU;
	pObj->stepV		[idx] = stepV;

	// Update Vertex
	pObj->m_tile[idx]->m_pTexture = mgrPacker.getTextureUsage(newSurface);
	pObj->updateDynSprites(idx);
	pObj->markUpMatrix();
	*/
	
}

bool CKLBNodeVirtualDocument::setViewPortSize(u32 width, u32 height, float alignOffsetX, float alignOffsetY, u32 priority, bool doScroll) {
	/* TODO : This optimization was buggy, rolled back to old code, but should be looked at.
	if (!((width > m_viewPortWidth) || (height > m_viewPortHeight))) { 
		return true;
	}*/

	bool success = true;
	clearRessources(false,false);
#ifdef DEBUG_TEXTURE_PACKER
	setIgnoreVirtualDoc(this);
#endif

	m_viewPortHeight	= height;
	m_viewPortWidth		= width;
	if ((width == 0) || (height == 0)) {
		//m_bDisplay = true;
		return false;
	}

	m_alignOffsetX = alignOffsetX;
	m_alignOffsetY = alignOffsetY;

	//
	// Allocate Dynamic sprite.
	//
	CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();
	CKLBDynSprite* pSprA = pRdrMgr.allocateCommandDynSprite(2*3,2*3);
	CKLBDynSprite* pSprB = doScroll ? pRdrMgr.allocateCommandDynSprite(2*3,2*3) : pSprA;

	if (pSprA && pSprB) {
		m_drawarea[0].tile = pSprA;
		m_drawarea[1].tile = pSprB;
		if (this->setRenderSlotCount(2)) {
			this->setRender(pSprA,0);
			pSprA->changeOrder(pRdrMgr, priority);
			if (doScroll) {
				this->setRender(pSprB,1);
				pSprB->changeOrder(pRdrMgr, priority);
			}
		} else {
			success = false;
		}
	} else {
		success = false;
		if (pSprA) {	pRdrMgr.releaseCommand(pSprA);	}
		if (pSprB) {	pRdrMgr.releaseCommand(pSprB);	}
	}

	u32 texW = width;
	u32 texH = height;
	
	mgrPacker.setFormat(m_format);

	if (m_drawarea[0].surf_handle == NULL_IDX) {
		m_drawarea[0].surf_handle = mgrPacker.allocateSurface(pSprA, texW, texH, this, docTextureCompaction);
		/* Special render state associated to text, not needed now.
		if (m_format == VDFORMAT_8) {
			pSprA->setRenderState(pRdrMgr->getTextState());
		} */
	} else {
		m_drawarea[0].surf_handle = mgrPacker.reallocateSurface(m_drawarea[0].surf_handle, texW, texH);
	}

	if (m_drawarea[0].surf_handle != NULL_IDX) {
		// Success.
		mgrPacker.getSurfaceInfo(m_drawarea[0].surf_handle,
								 m_drawarea[0].softwareBufTile,
								 m_drawarea[0].leftU,
								 m_drawarea[0].upV,
								 m_drawarea[0].rightU,
								 m_drawarea[0].bottomV,
								 m_drawarea[0].stepU,
								 m_drawarea[0].stepV);
		m_drawarea[0].format = m_format;
	}

	m_bScroll = doScroll;

	if (doScroll) {
		if (m_drawarea[1].surf_handle == NULL_IDX) {
			m_drawarea[1].surf_handle = mgrPacker.allocateSurface(pSprB, texW, texH, this, docTextureCompaction);
			/* Special render state associated to text, not needed now.
			if (m_format == VDFORMAT_8) {
				 pSprB->setRenderState(pRdrMgr->getTextState());
			} */
		} else {
			m_drawarea[1].surf_handle = mgrPacker.reallocateSurface(m_drawarea[1].surf_handle, texW, texH);
		}
		m_drawarea[1].format = m_format;

		if (width < height) {
			texW *= 2;
		} else {
			texH *= 2;
		}

		if (m_drawarea[1].surf_handle == NULL_IDX) {
			success = false;
		}
	} else {
		m_drawarea[1].surf_handle = NULL_IDX;
	}

	success = success && (m_drawarea[0].surf_handle != NULL_IDX);

	if (success) {
		if (doScroll) {
			mgrPacker.getSurfaceInfo(m_drawarea[1].surf_handle,
									 m_drawarea[1].softwareBufTile,
									 m_drawarea[1].leftU,
									 m_drawarea[1].upV,
									 m_drawarea[1].rightU,
									 m_drawarea[1].bottomV,
									 m_drawarea[1].stepU,
									 m_drawarea[1].stepV);

		} else {
			m_drawarea[1].softwareBufTile = m_drawarea[0].softwareBufTile;
			m_drawarea[1].stepU			= m_drawarea[0].stepU;
			m_drawarea[1].stepV			= m_drawarea[0].stepV;
			m_drawarea[1].leftU			= m_drawarea[0].leftU;
			m_drawarea[1].upV			= m_drawarea[0].upV;
			m_drawarea[1].rightU		= m_drawarea[0].rightU;
			m_drawarea[1].bottomV		= m_drawarea[0].bottomV;
		}

		//
		// For now we allocate a seperate texture
		// But we could later on write a texture chunk allocator.
		//
		/*
		u32 realTexW = nearest2Pow(texW);
		u32 realTexH = nearest2Pow(texH);
		
		stepUPix = 1.0f / realTexW;
		stepVPix = 1.0f / realTexH;

		*/

		// this->m_textureX[0] = 0;
		// this->m_textureY[0] = 0;

		
		pSprA->m_pTexture = mgrPacker.getTextureUsage(m_drawarea[0].surf_handle);
		if (doScroll) {
			pSprB->m_pTexture = mgrPacker.getTextureUsage(m_drawarea[1].surf_handle);
		}
	}

#ifdef DEBUG_TEXTURE_PACKER
	// Failed : free everything.
	setIgnoreVirtualDoc(NULL);
#endif

	if (!success) {
		clearRessources(true, false);
	}

	this->renderContext.stride			= m_viewPortWidth; // in pixel
	this->renderContext.targetWidth		= m_viewPortWidth;
	this->renderContext.targetHeight	= m_viewPortHeight;

	m_bHasChanged = true;

	return success;
}

void CKLBNodeVirtualDocument::setViewPortPos(s32 x, s32 y) {
	if ((m_viewPortWidth == 0) || (m_viewPortHeight == 0)) {
		return;
	}

	if (x < 0) {
		x = 0;
	}

	if (y < 0) {
		y = 0;
	}

	// Non scrollable type -> Force no scroll.
	if (!m_bScroll) {
		x = 0;
		y = 0;
	}

	if (m_bDisplay) {
		if (!m_isVertical) {
			m_currTile	= x / m_viewPortWidth;
			m_scroll	= (x % m_viewPortWidth);
		} else {
			m_currTile	= y / m_viewPortHeight;
			m_scroll	= (y % m_viewPortHeight);
		}
		int currIdx = m_currTile & 1;
		m_up = currIdx;

		//printf("tile:%i pos:%i\n", m_currTile, m_scroll);

		m_posX = x;
		m_posY = y;

		if ((m_currTile != m_prevTile) || m_bHasChanged /* || (m_prevScroll != m_scroll) || (!m_bScroll) */) {
			if(m_bHasChanged) {
				m_bHasChanged = false;
			}

			if (m_bScroll) {

				if (m_currTile == m_prevTile + 1) {
					// Copy Next Tile to Curr Tile
					if (!m_isVertical) {
						setTargetSurface(1-currIdx, (m_currTile + 1) * m_viewPortWidth, 0);
					} else {
						setTargetSurface(1-currIdx, 0, (m_currTile + 1) * m_viewPortHeight);
					}
					renderDocument();
				} else
				if (m_currTile == m_prevTile - 1) {
					// Copy Curr Tile to Next Tile
					if (!m_isVertical) {
						setTargetSurface(currIdx, m_currTile * m_viewPortWidth, 0);
					} else {
						setTargetSurface(currIdx, 0, m_currTile * m_viewPortHeight);
					}
					renderDocument();
				} else /*if (m_currTile != m_prevTile)*/	// Complete refresh both.
				{
					// Redraw Both tile.
					if (!m_isVertical) {
						setTargetSurface(currIdx,  m_currTile      * m_viewPortWidth, 0);
						renderDocument();
						setTargetSurface(1 - currIdx, (m_currTile + 1) * m_viewPortWidth, 0);
						renderDocument();
					} else {
						setTargetSurface(currIdx, 0, m_currTile       * m_viewPortHeight);
						renderDocument();
						setTargetSurface(1 - currIdx, 0, (m_currTile + 1) * m_viewPortHeight);
						renderDocument();
					}
				}
			} else {
				setTargetSurface(currIdx, 0, m_currTile       * m_viewPortHeight);
				renderDocument();
			}
		}
		// Refresh only the XY and UV. Texture may NOT be updated.
		updateDynSprites(currIdx);
		if (m_bScroll) {
			updateDynSprites(1 - currIdx);
		}
		markUpMatrix();			// Recompute geometry.

		m_prevTile		= m_currTile;
		m_prevScroll	= m_scroll;
	} else {
		klb_assertAlways( "create document, CKLBNodeVirtualDocument::lock()/unlockDocument()");
	}
}

void CKLBNodeVirtualDocument::setDocumentSize	(u32 width, u32 height, bool scrollVertical) {
	m_documentWidth		= width;
	m_documentHeight	= height;
	m_isVertical		= scrollVertical;
	m_prevTile			= 0x7fff;
}

bool CKLBNodeVirtualDocument::createDocument	(u16 maxCommandCount, u8 format) {
	freeDocument();

	m_commandArray		= KLBNEWA(SDrawCommand,maxCommandCount);
	m_CurrentCommand	= 0;
	m_format			= format;
	if (m_commandArray) {
		m_commandMaxCount = maxCommandCount;
		return true;
	} else {
		m_commandMaxCount = 0;
		return false;
	}
}

void CKLBNodeVirtualDocument::freeDocument		() {
	if (m_commandArray) {
		for (u32 n = 0; n < m_CurrentCommand; n++) {
			if (m_commandArray[n].command == DRAWTEXT) {
				if (m_commandArray[n].ptr) {
					KLBDELETEA((char *)(m_commandArray[n].ptr));
				}
			}
		}
		KLBDELETEA(m_commandArray);
		m_commandArray = NULL;
	}
	m_CurrentCommand	= 0;
	m_bDisplay			= true;
}

void CKLBNodeVirtualDocument::freeFont() {
	IPlatformRequest& platform = CPFInterface::getInstance().platform();
	for (int n=0; n<5; n++) {
		if (font[n]) {
			platform.deleteFont(font[n]);
		}
		font[n] = NULL;
	}
}

void CKLBNodeVirtualDocument::lockDocument() {
	klb_assert(m_bDisplay,		"Document is already locked");
	klb_assert(m_commandArray,	"CKLBNodeVirtualDocument::createDocument not called.");

	// Do nothing in our implementation.
	m_bDisplay = false;
}

void CKLBNodeVirtualDocument::emptyDocument() {
/*
	2012.11.29  
	m_CurrentCommand	= 0;
*/
	if (m_commandArray) {
		for (u32 n = 0; n < m_CurrentCommand; n++) {
			if (m_commandArray[n].command == DRAWTEXT) {
				if (m_commandArray[n].ptr) {
					KLBDELETEA((char *)(m_commandArray[n].ptr));
				}
			}
		}
	}
	m_CurrentCommand = 0;
}

void CKLBNodeVirtualDocument::unlockDocument() {
	// --> Optimize data structure in optimized version.
	m_bDisplay      = true;
	m_bHasChanged   = true;
}

void CKLBNodeVirtualDocument::clear		(u32 fillColor) {
	m_bgColor		= convertARGB32_RGBA8(fillColor);
	m_bHasChanged   = true;
}

void CKLBNodeVirtualDocument::drawLine		(s16 x0, s16 y0, s16 x1,    s16 y1,     u32 color) {
	if (m_CurrentCommand < m_commandMaxCount) {
		SDrawCommand* drw = &m_commandArray[m_CurrentCommand++];
		drw->x0			= x0;
		drw->x1			= x1;
		drw->y0			= y0;
		drw->y1			= y1;
		drw->color		= convertARGB32_RGBA8(color);
		drw->command	= DRAWLINE;
	} else {
		klb_assertAlways("Reached max command in virtual document");
	}
}

void CKLBNodeVirtualDocument::drawRect		(s16 x0, s16 y0, u16 width, u16 height, u32 color) {
	if (m_CurrentCommand < m_commandMaxCount) {
		SDrawCommand* drw = &m_commandArray[m_CurrentCommand++];
		drw->x0			= x0;
		drw->x1			= x0 + width - 1;
		drw->y0			= y0;
		drw->y1			= y0 + height - 1;
		drw->color		= convertARGB32_RGBA8(color);
		drw->command	= DRAWRECT;
	} else {
		klb_assertAlways("Reached max command in virtual document");
	}
}

void CKLBNodeVirtualDocument::fillRect		(s16 x0, s16 y0, u16 width, u16 height, u32 color, bool fill) {
	if (m_CurrentCommand < m_commandMaxCount) {
		SDrawCommand* drw = &m_commandArray[m_CurrentCommand++];
		drw->x0			= x0;
		drw->x1			= x0 + width;
		drw->y0			= y0;
		drw->y1			= y0 + height;
		drw->color		= convertARGB32_RGBA8(color);
		if (fill) {
			drw->command = FILLRECTFORCE;	// Fill
		} else {
			drw->command = FILLRECT;			// Blend
		}
	} else {
		klb_assertAlways("Reached max command in virtual document");
	}
}

void CKLBNodeVirtualDocument::drawImage	(s16 x0, s16 y0, CKLBImageAsset* img, u8 Alpha) {
	if (img->getVertexCount() == 4) {
		if (m_CurrentCommand < m_commandMaxCount) {
			SDrawCommand* drw = &m_commandArray[m_CurrentCommand++];
			drw->x0			= x0;
			drw->y0			= y0;
			drw->ptr		= img;

			//
			// Preprocess image once to extract all information for
			// software rasterization process.
			//
			CKLBTextureAsset* pAsset = img->getTexture();
			float fx0; float fy0;
			float fx1; float fy1;
			img->getXY(0,&fx0,&fy0);
			img->getXY(2,&fx1,&fy1);
			for (int n=0; n < 4; n+=2) {
				float u; float v;
				img->getUV(n,&u,&v);			// Read UV vertex 0 and vertex 2
				s32 px = pAsset->m_width  * u;		// Get X,Y from UV
				s32 py = pAsset->m_height * v;

				if (n == 0) {
					drw->sx0		= px;
					drw->sy0		= py;
				} else {
					s32 dx = (s32)(fx1-fx0);
					s32 dy = (s32)(fy1-fy0);
					drw->x1			= x0 + dx;
					drw->y1			= y0 + dy;
					drw->sdx		= px - drw->sx0;
					drw->sdy		= py - drw->sy0;

					if ((drw->sdx == dx) || (drw->sdy == dy)) {
						// Normal
						drw->swap = false;
					} else if ((drw->sdy == dx) || (drw->sdx == dy)) {
						// Swap X,Y
						drw->swap = true;
					} else {
						// Error
						klb_assertAlways("Imcompatible Bitmap with 4 vertex");
					}
				}
			}

			drw->ptr		= img;
			drw->color		= Alpha;
			drw->command	= DRAWIMAGE; 
		} else {
			klb_assertAlways("Reached max command in virtual document");
		}
	} else {
		klb_assertAlways("Image has more than 4 vertex");
	}
}

void CKLBNodeVirtualDocument::drawTileImage(s16 x0, s16 y0, u16 width, u16 height, CKLBImageAsset* img, u8 Alpha) {
	if (m_CurrentCommand < m_commandMaxCount) {
		SDrawCommand* drw = &m_commandArray[m_CurrentCommand++];
		drw->x0			= x0;
		drw->x1			= x0 + width;		// NO -1
		drw->y0			= y0;
		drw->y1			= y0 + height;		// NO -1
		drw->ptr		= img;
		drw->color		= Alpha;
		drw->command	= DRAWIMAGETILED;
	} else {
		klb_assertAlways("Reached max command in virtual document");
	}
}

void CKLBNodeVirtualDocument::drawText		(s16 x0, s16 y0, const char* string, u32 color, u8 fontIndex,
								u8 align_mode, s16 align_width	// addhook parameters.
								) {
	klb_assert(fontIndex < 5, "Maximum 5 fonts per document");
	if (font[fontIndex]) {
		char* start;
		const char* origString = string;
		if (string != NULL) {
			u32 length = strlen(string) + 1;
			char* newString = KLBNEWA(char, length);
			if (newString) {
				memcpy(newString, string, length);
				string = newString;
				start  = newString;

				#define	CR	(0x0D)
				#define LF	(0x0A)

				bool first = true;

				STextInfo textInfo;
				CPFInterface::getInstance().platform().getTextInfo(string, font[fontIndex], &textInfo);

				// 1 line size.
				int heightF = textInfo.ascent - textInfo.descent;

				int lineY	= 0;
				bool hadCR	= false;

				while (*start) {
					//
					//
					//
					if(*start == CR) {
						*start++ = 0;
						lineY += heightF;
						hadCR = true;
						continue;
					} else if(*start == LF) {
						*start++ = 0;
						if(!hadCR) lineY += heightF;
						hadCR = false;
						continue;
					} else if ((*start == '\\') && (start[1] == 'n')) {
						*start++ = 0;
						*start++ = 0;
						lineY += heightF;
						hadCR = false;
						continue;
					} else if(*start) {

						char * term;
						char code = 0;
						for(term = start; *term; term++) {
							if ((*term == CR) || (*term == LF) || ((*term=='\\') && (term[1]=='n'))) {
								code	= *term;
								*term	= 0;
								break;
							}

							if ((term[0]=='\\') && (term[1]=='\\')) {
								int strLen = strlen(term);		// Number of char
								memcpy(term, term+1, strLen);	// convert \ + \ into a single \ for display
								term++;							// skip \ char
							}
						}


						if (m_CurrentCommand < m_commandMaxCount) {
							SDrawCommand* drw = &m_commandArray[m_CurrentCommand++];
							CPFInterface::getInstance().platform().getTextInfo(start, font[fontIndex], &textInfo);

                            //行末コードを書き戻
							// Because the processing of the CR/LF is needed once we process this block.
							*term = code;

							switch(align_mode) {
							default:	drw->x0 = x0;	break;
							case 1:		drw->x0 = x0 + (align_width - (int)textInfo.width) / 2;	break;
							case 2:		drw->x0 = x0 + (align_width - (int)textInfo.width);		break;
							}
							drw->y0			= y0 - (int)textInfo.ascent  + lineY;
							drw->x1			= x0 + (int)textInfo.width;
							drw->y1			= y0 - (int)textInfo.descent + lineY;
							drw->ptr		= first ? (void*)string : NULL;
							drw->txt		= start;

							drw->color		= color;
							drw->command	= DRAWTEXT;
							drw->fntIdx		= fontIndex;
							hadCR = false;
							first = false;
						} else {
							DEBUG_PRINT("With text : '%s', Reached max command in virtual document (done by multiline text, if using Label, please use only one line.", origString);
							break;
						}

						// Jump at the end of display char.
						start = term;
					}
				}

				// No draw instruction was generated.
				if (first) {
					KLBDELETEA(string);
				}
			}
		}
	} else {
		DEBUG_PRINT("Font undefined");
	}
}

void CKLBNodeVirtualDocument::setFont(u8 index, const char* fontName, u16 fontSize) {
	klb_assert(index < 5, "Maximum 5 fonts per document");
	IPlatformRequest& platform = CPFInterface::getInstance().platform();
	if(font[index]) {
		platform.deleteFont(font[index]);
		font[index] = NULL;
	}
	font[index] = platform.getFont(fontSize, fontName,&fontInfo[index].ascent);
	m_bHasChanged = true;
}

void CKLBNodeVirtualDocument::setTargetSurface(u8 index, s32 offsetX, s32 offsetY) {
	m_currBuff		= index;
	m_tileXStart	= offsetX;
	m_tileYStart	= offsetY;
	m_tileXEnd		= offsetX + m_viewPortWidth;
	m_tileYEnd		= offsetY + m_viewPortHeight;
}

void CKLBNodeVirtualDocument::setVertex(CKLBDynSprite* pSpr, u32 idx4, float x0, float y0, float u, float v) {
	x0 += m_alignOffsetX;
	y0 += m_alignOffsetY;

	// 012 345
	switch (idx4) {
	case 0:
		pSpr->setVertexXY(0, x0,y0);
		pSpr->setVertexUV(0, u ,v );
		break;
	case 1:
		pSpr->setVertexXY(1, x0,y0);
		pSpr->setVertexUV(1, u ,v );
		pSpr->setVertexXY(3, x0,y0);
		pSpr->setVertexUV(3, u ,v );
		break;
	case 2:
		pSpr->setVertexXY(4, x0,y0);
		pSpr->setVertexUV(4, u ,v );
		break;
	case 3:
		pSpr->setVertexXY(2, x0,y0);
		pSpr->setVertexUV(2, u ,v );
		pSpr->setVertexXY(5, x0,y0);
		pSpr->setVertexUV(5, u ,v );
		break;
	}
}

void CKLBNodeVirtualDocument::forceRefresh() {
	if (m_drawarea[0].surf_handle != NULL_IDX) {
		// Success.
		mgrPacker.getSurfaceInfo(m_drawarea[0].surf_handle,
								 m_drawarea[0].softwareBufTile,
								 m_drawarea[0].leftU,
								 m_drawarea[0].upV,
								 m_drawarea[0].rightU,
								 m_drawarea[0].bottomV,
								 m_drawarea[0].stepU,
								 m_drawarea[0].stepV);
		updateDynSprites(0);
		mgrPacker.updateTexture(m_drawarea[0].surf_handle);
	}
	
	if (m_drawarea[1].surf_handle != NULL_IDX) {
		mgrPacker.getSurfaceInfo(m_drawarea[1].surf_handle,
									m_drawarea[1].softwareBufTile,
									m_drawarea[1].leftU,
									m_drawarea[1].upV,
									m_drawarea[1].rightU,
									m_drawarea[1].bottomV,
									m_drawarea[1].stepU,
									m_drawarea[1].stepV);

		updateDynSprites(1);
		mgrPacker.updateTexture(m_drawarea[1].surf_handle);
	}
	
	markUpMatrixAndColor();
}

void CKLBNodeVirtualDocument::renderDocument() {
	// klb_assert((_CrtCheckMemory() != 0), "Heap Error !");

	if (!m_bDisplay)	{ return; }


	RenderContext* pCtx = &renderContext;
	// pCtx->pBuffer		= m_softwareBufferTile[m_currBuff];
	pCtx->pBuffer		= m_drawarea[m_currBuff].softwareBufTile;
	pCtx->offsetX		= m_tileXStart;
	pCtx->offsetY		= m_tileYStart;
	pCtx->format		= m_drawarea[m_currBuff].format;

	// Clipping absolute buffer coordinate.
	pCtx->setClip	(0, 0, m_viewPortWidth, m_viewPortHeight);

	// Force tile fill at current coordinate. (relative coordinate fill, different from absolute instruction)
	pCtx->fillRect	(	m_tileXStart,
						m_tileYStart,
						m_viewPortWidth  + m_tileXStart,
						m_viewPortHeight + m_tileYStart, m_bgColor, true);

	// Render at absolute coordinate.
	for (u32 n = 0; n < m_CurrentCommand; n++) {
		SDrawCommand* pDCom = &m_commandArray[n];
		s16 x0, x1, y0, y1;
		if(pDCom->x0 <= pDCom->x1) { x0 = pDCom->x0; x1 = pDCom->x1; } else { x0 = pDCom->x1; x1 = pDCom->x0; }
		if(pDCom->y0 <= pDCom->y1) { y0 = pDCom->y0; y1 = pDCom->y1; } else { y0 = pDCom->y1; y1 = pDCom->y0; }
	
		// x0 <= x1, y0 < y1
		if (
			 (x1 <=  m_tileXStart) || (x0 >= m_tileXEnd  )
			 ||
			 (y1 <=  m_tileYStart) || (y0 >= m_tileYEnd  )
		   )
		{
			// skip instruction.
			continue;
		}
		switch (m_commandArray[n].command) {
		default:
			klb_assertAlways("Unknow draw command.");
			break;
		case DRAWLINE:	pCtx->drawLine	(pDCom->x0,pDCom->y0, pDCom->x1, pDCom->y1, pDCom->color);	break;
		case DRAWRECT:	pCtx->drawRect	(pDCom->x0,pDCom->y0, pDCom->x1, pDCom->y1, pDCom->color);	break;
		case FILLRECT:	pCtx->fillRect	(pDCom->x0,pDCom->y0, pDCom->x1, pDCom->y1, pDCom->color, false); break;
		case FILLRECTFORCE
					:	pCtx->fillRect	(pDCom->x0,pDCom->y0, pDCom->x1, pDCom->y1, pDCom->color, true); break;
		case DRAWIMAGE: pCtx->drawImage	(pDCom->x0,pDCom->y0, pDCom, pDCom->color);	break;
		case DRAWTEXT:	{
				s32 ascent = (s32)this->fontInfo[pDCom->fntIdx].ascent;
				pCtx->drawText	(pDCom->x0,pDCom->y0 + ascent, (char*)pDCom->txt   , pDCom->color, font[pDCom->fntIdx], m_bScroll);
			}
			break;
		case DRAWIMAGETILED:
			{
				// Set clip.
				pCtx->setClip(pDCom->x0, pDCom->y0, pDCom->x1, pDCom->y1);
				
				// Draw Images
				for (s32 y = 0; y < pDCom->y1; y += (pDCom->y1 - pDCom->y0)) {
					for (s32 x = 0; x < pDCom->x1; x += (pDCom->x1 - pDCom->x0)) {
						pCtx->drawImage	(x, y, pDCom, pDCom->color);
					}
				}

				// Restore clip
				pCtx->setClip(0,0,this->m_viewPortWidth,this->m_viewPortHeight);
			}
			break;
		}
	}

	updateDynSprites(0);
	updateDynSprites(1);
	mgrPacker.updateTexture(m_drawarea[0].surf_handle);
	mgrPacker.updateTexture(m_drawarea[1].surf_handle);
}

void CKLBNodeVirtualDocument::updateDynSprites(u8 currBuff) {
	VDOCDRAW * pDraw = &m_drawarea[currBuff];
	CKLBDynSprite* pSpr = pDraw->tile;

	if (pSpr) {
		if (m_up == currBuff) {
			//
			// Up clipping.
			//

			//
			// 4 Vertex numbering
			//
			// 0--1 /////////////////////
			// |  | <----- Top is clipped
			// 3--2
			//
			if (m_isVertical) {
				s32		remainV		= m_viewPortHeight - m_scroll;
				float	remainVF	= (float)remainV;
				float	vpWidthF	= (float)m_viewPortWidth;
				//
				// Dyn Sprite has 6 vertex. which are equiv to :
				//
				// 0---1/3 /////////////////////
				// |    | <----- Top is clipped
				//5/2---4

				float clipV = pDraw->upV + (m_scroll * pDraw->stepV);
				setVertex(pSpr,0, 0,		0,			pDraw->leftU,		clipV);
				setVertex(pSpr,1, vpWidthF,	0,			pDraw->rightU,		clipV);
				setVertex(pSpr,2, vpWidthF,	remainVF,	pDraw->rightU,		pDraw->bottomV);
				setVertex(pSpr,3, 0,		remainVF,	pDraw->leftU,		pDraw->bottomV);
			} else {
				// 0----1.3
				// |//|  |
				// |//|  |
				//5.2----4
				//   /|
				//   /|
				s32		remainH		= m_viewPortWidth - m_scroll;
				float	remainHF	= (float)remainH;
				float	vpHeightF	= (float)m_viewPortHeight;

				float clipU = pDraw->leftU + (m_scroll * pDraw->stepU);

				setVertex(pSpr,0, 0,		0,			clipU,					pDraw->upV);
				setVertex(pSpr,1, remainHF,	0,			pDraw->rightU,			pDraw->upV);
				setVertex(pSpr,2, remainHF,	vpHeightF,	pDraw->rightU,			pDraw->bottomV);
				setVertex(pSpr,3, 0,		vpHeightF,	clipU,					pDraw->bottomV);
			}
		} else {
			float	vpWidthF	= (float)m_viewPortWidth;
			float	vpHeightF	= (float)m_viewPortHeight;
			//
			// 0--1
			// |  | <----- Top is clipped
			// 3--2 /////////////////////
			//
			if (m_isVertical) {
				float	vOffsetF	= (float)(m_viewPortHeight - m_scroll);
				s32		remainV		= m_scroll;
				float	remainVF	= (float)remainV;

				float clipV = pDraw->upV + (remainVF * pDraw->stepV);

				setVertex(pSpr,0, 0,		vOffsetF,			  pDraw->leftU,		pDraw->upV);
				setVertex(pSpr,1, vpWidthF,	vOffsetF,			  pDraw->rightU,	pDraw->upV);
				setVertex(pSpr,2, vpWidthF,	vOffsetF + remainVF,  pDraw->rightU,	clipV);
				setVertex(pSpr,3, 0,		vOffsetF + remainVF,  pDraw->leftU,		clipV);
			} else {
				float	hOffsetF	= (float)(m_viewPortWidth - m_scroll);
				s32		remainH		= m_scroll;
				float	remainHF	= (float)remainH;

				float clipU = pDraw->leftU + (remainH * pDraw->stepU);

				setVertex(pSpr, 0, hOffsetF,			0,			pDraw->leftU,	pDraw->upV);
				setVertex(pSpr, 1, hOffsetF + remainHF,	0,			clipU,			pDraw->upV);
				setVertex(pSpr, 2, hOffsetF + remainHF,	vpHeightF,	clipU,			pDraw->bottomV);
				setVertex(pSpr, 3, hOffsetF,			vpHeightF,	pDraw->leftU,	pDraw->bottomV);
			}
		}

		pSpr->mark(CKLBDynSprite::MARK_CHANGE_UV | CKLBDynSprite::MARK_CHANGE_XY | FLAG_BUFFERSHIFT);
	}
}

void CKLBNodeVirtualDocument::setPriority(u32 renderPriority)
{
	CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();
	m_drawarea[0].tile->changeOrder(pRdrMgr, renderPriority);
	m_drawarea[1].tile->changeOrder(pRdrMgr, renderPriority);
}
