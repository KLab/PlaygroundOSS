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
#include "TextureManagement.h"
#include "RenderingFramework.h"
#include "mem.h"
#include "zlib.h"
#include "CKLBUtility.h"
#include "CKLBDrawTask.h"
#include "KLBPlatformMetrics.h"

/*
 * Here is the header of the ETC1 decoder part taken out from the 
 * rg_etc1 library, we took only the decoder part out.
 *
 * The original project code can be found at :
 * http://code.google.com/p/rg-etc1/
 * The implementation and license detail is at the end of the file.
 *
// Fast, high quality ETC1 block packer/unpacker - Rich Geldreich <richgel99@gmail.com>
// Please see ZLIB license at the end of this file.
 */

namespace rg_etc1
{
   // Unpacks an 8-byte ETC1 compressed block to a block of 4x4 32bpp RGBA pixels.
   // Returns false if the block is invalid. Invalid blocks will still be unpacked with clamping.
   // This function is thread safe, and does not dynamically allocate any memory.
   // If preserve_alpha is true, the alpha channel of the destination pixels will not be overwritten. Otherwise, alpha will be set to 255.
   bool unpack_etc1_block(const void *pETC1_block, unsigned int* pDst_pixels_rgba, bool preserve_alpha = false);
} // namespace rg_etc1

u32 gTextureAllocSW = 0;
u32 gTextureAllocHW = 0;

// Prototypes
void processImage8888(u32 /*pixelCount*/, u32 lineWidth, u32 height, u8* buffer);
void processImage565(u32 pixelCount, u32 lineWidth, u32 height, u8* buffer);
void processImage4444(u32 pixelCount, u32 lineWidth, u32 height, u8* buffer);
void processImage5551(u32 pixelCount, u32 lineWidth, u32 height, u8* buffer);
CKLBAbstractAsset* createTexture(u32 orgWidthI, u32 orgHeightI, const char* name);

CKLBTextureAsset::CKLBTextureAsset()
: CKLBAbstractAsset ()
, m_indexBufferTotal(NULL)
, m_floatBufferTotal(NULL)
, m_pTexture        (NULL)
, m_pTextureUsage   (NULL)
, m_pImages         (NULL)
, m_softTexture     (NULL)
, m_imageCount      (0)
, m_bytePerPix		(0)
, m_width			(0)
, m_height			(0)
{
}

CKLBTextureAsset::~CKLBTextureAsset()
{
	if (m_pImages) { 
		for (u32 n = 0; n < m_imageCount; n++) {
			if (m_pImages[n]) {
				KLBDELETE(m_pImages[n]);
			}
		}
		KLBDELETEA(m_pImages);
	}

	if (m_indexBufferTotal)	{ KLBDELETE(m_indexBufferTotal); }
	if (m_floatBufferTotal)	{ KLBDELETE(m_floatBufferTotal); }

	CKLBOGLWrapper& pMgr = CKLBOGLWrapper::getInstance();

	if (m_pTexture) {
		gTextureAllocHW -= this->m_width * this->m_height * m_bytePerPix;
		if (m_pTextureUsage) {
			m_pTexture->releaseUsage	(m_pTextureUsage);
		}
		pMgr.releaseTexture		(m_pTexture);
		m_pTexture = NULL;
	}

	if (m_softTexture) {
		KLBDELETEA(m_softTexture);
		gTextureAllocSW -= this->m_width * this->m_height * 4;
		m_softTexture = NULL;
	}
}

void
CKLBTextureAsset::unloadRessource() {
	if (m_pTexture) {
		m_pTexture->makeEmptyShell();
	}

	gTextureAllocHW -= this->m_width * this->m_height * m_bytePerPix;

	// Release software texture.
	if (m_softTexture) {
		KLBDELETEA(m_softTexture);
		gTextureAllocSW -= this->m_width * this->m_height * 4;
		m_softTexture = NULL;
	}
}

CKLBImageAsset* 
CKLBTextureAsset::getImage(const char* fileName) 
{
	// TODO OPTIMIZE : binary search instead of stupid search.
	// Tool will garantee that image are ordered correctly.
	if (fileName) {
		for (u32 n = 0; n < m_imageCount; n++) {
			if (strcmp(fileName,m_pImages[n]->getName()) == 0) {
				return m_pImages[n];
			}
		}
	}
	return NULL;
}

void 
CKLBTextureAsset::onRegisterSubAsset() 
{ 
	//
	// Register all sub images as asset search.
	//
	CKLBAssetManager& pAMgr = CKLBAssetManager::getInstance();
	for (u32 n = 0; n < m_imageCount; n++) {
		pAMgr.addSearchSubEntry(this, m_pImages[n]->getName());
	}
}

void 
CKLBAssetManager::dump() 
{
	if (m_assetRecord) {
		FILE* pFile = CPFInterface::getInstance().client().getShellOutput();

		int totalSize = 0;
		for (u32 n = 0; n < this->m_maxAssetEntry; n++) {
			
			if (!m_assetRecord[n].m_isFree) {
				CKLBAbstractAsset* pAsset = m_assetRecord[n].m_pAsset;

				// Display self name
				fprintf(pFile, "[%4i] %s",n, pAsset->getName());
				
				// display type
				switch (pAsset->getClassID()) {
				case CLS_ASSETBASE:
					fprintf(pFile, " Base Asset?");
					break;
				case CLS_ASSETTEXTURE:
					fprintf(pFile, " Texture Asset");
					break;
				case CLS_ASSETIMAGE:
					fprintf(pFile, " Image Asset");
					break;
				case CLS_ASSETAUDIO:
					fprintf(pFile, " Audio Asset");
					break;
				case CLS_ASSETFLASH:
					fprintf(pFile, " Flash Asset");
					break;
				case CLS_ASSETANIMSPLINE:
					fprintf(pFile, " Spline Asset");
					break;
				case CLS_ASSETMAP:
					fprintf(pFile, " Map Asset");
					break;
				case CLS_ASSETCELLANIM:
					fprintf(pFile, " Cell Anim Asset");
					break;
				case CLS_ASSETCOMPOSITE:
					fprintf(pFile, " UI Form");
					break;
				case CLS_ASSETNODEANIM:
					fprintf(pFile, " Node Anim");
					break;
				default:
					fprintf(pFile, " Unknown");
					break;
				}

				if (pAsset->getClassID() == CLS_ASSETTEXTURE) {
					CKLBTextureAsset* p = (CKLBTextureAsset*)pAsset;

					int size = (p->m_bytePerPix * p->m_width * p->m_height) >> 10;
					totalSize += size;
					fprintf(pFile, " @%p W:%4i H:%4i MEM:%4iKB\n",pAsset, p->m_width, p->m_height, size);
					for (int m = 0; m < p->m_imageCount; m++) {
						fprintf(pFile, "\t%s\n", p->m_pImages[m]->getName());
					}
				} else {
					fprintf(pFile, " @%p\n",pAsset);
				}
			}
		}
		fprintf(pFile, "TOTAL TEXTURE SIZE : %08i KB\n", totalSize);
	}
}

void 
CKLBTextureAsset::onUnregisterSubAsset() 
{
	//
	// Register all sub images as asset search.
	//
	CKLBAssetManager& pAMgr = CKLBAssetManager::getInstance();
	for (u32 n = 0; n < m_imageCount; n++) {
		pAMgr.removeSearchEntry(m_pImages[n]->getName());
	}
}

/* NO DICO
bool CKLBTextureAsset::include(const char* name) {
	if (!CKLBAbstractAsset::include(name)) {
		return (getImage(name) != NULL);
	}
	return true;
}*/

CKLBImageAsset::CKLBImageAsset()
: CKLBAsset         ()
, m_pUVCoord        (NULL)
, m_pXYCoord        (NULL)
, m_pIndex          (NULL)
, m_pTextureAsset   (NULL)
, m_subIndex        (-1)
, m_subTiles        (NULL)
, m_nextSubTile     (NULL)
, m_attribList      (NULL)
, m_attribCount     (0)
, m_usageType       (0)
, m_topLeftImage    (NULL)
, m_renderOffset    (0)
, m_bAllocatedOutsideTexture(false)
{
}

CKLBImageAsset::~CKLBImageAsset() 
{
	if (m_subTiles) {
		CKLBImageAsset* pImgParse = m_subTiles;
		while (pImgParse) {
			CKLBImageAsset* pImgParseNext = pImgParse->m_nextSubTile;
			KLBDELETE(pImgParse);
			pImgParse = pImgParseNext;
		}
	}

	if (m_attribCount) {
		for (int n = 0; n < m_attribCount;n++) {
			if (m_attribList[n].type == ASSET_ATTRIB::zATTRIB_STRING) {
				KLBDELETEA(m_attribList[n].v.str);
			}
		}
		m_attribCount = 0;
	}

	KLBDELETEA(m_attribList);

	KLBDELETE(m_topLeftImage);

	if (m_bAllocatedOutsideTexture) {
		KLBDELETEA(m_pXYCoord);
		// Use the same array with offset from beginning, NEVER DELETE
		// KLBDELETEA(m_pUVCoord);
		// KLBDELETEA(m_pIndex	);
	}
}

void 
CKLBImageAsset::getCenter(s32& cx, s32& cy) 
{
	cx = this->m_iCenterX;
	cy = this->m_iCenterY;
}

CKLBImageAsset* 
CKLBImageAsset::getAsTopLeftImage(s32 offX, s32 offY) 
{
	if ((offX == 0) && (offY == 0)) {
		return this;
	} else {
		if (!this->m_topLeftImage) {
			m_topLeftImage	= KLBNEW(CKLBImageAsset); // Fake for now.
			float* pArrayXY	= KLBNEWA(float, this->getVertexCount()*2);
			if (m_topLeftImage && pArrayXY) {
				
				// Avoid double delete.
				m_topLeftImage->m_subTiles		= NULL;
				m_topLeftImage->m_attribCount	= 0;
				m_topLeftImage->m_attribList	= NULL;
				m_topLeftImage->m_topLeftImage	= NULL;
				m_topLeftImage->m_iCenterX		= 0;
				m_topLeftImage->m_iCenterY		= 0;

				// Setup new XY coordinate.
				m_topLeftImage->m_bAllocatedOutsideTexture = true;
				m_topLeftImage->m_pXYCoord		= pArrayXY;
				
				m_topLeftImage->m_pUVCoord		= this->m_pUVCoord;
				m_topLeftImage->m_pIndex		= this->m_pIndex;
				m_topLeftImage->m_pTextureAsset	= this->m_pTextureAsset;
				m_topLeftImage->m_subIndex		= this->m_subIndex;
				m_topLeftImage->m_subTiles		= this->m_subTiles;
				m_topLeftImage->m_nextSubTile	= this->m_nextSubTile;
				m_topLeftImage->m_uiVertexCount	= this->m_uiVertexCount;
				m_topLeftImage->m_uiIndexCount	= this->m_uiIndexCount;
				m_topLeftImage->m_imageSize		= this->m_imageSize;	// Original image size
				m_topLeftImage->m_boundWidth	= this->m_boundWidth;
				m_topLeftImage->m_boundHeight	= this->m_boundHeight;

				for (u32 n=0; n < this->getVertexCount()*2; n += 2) {
					pArrayXY[n  ]	= this->m_pXYCoord[n  ] + offX;
					pArrayXY[n+1]	= this->m_pXYCoord[n+1] + offY;
				}
			} else {
				KLBDELETE(m_topLeftImage);
				m_topLeftImage = NULL;
				KLBDELETEA(pArrayXY);
			}
		}
		return m_topLeftImage;
	}
}

bool 
CKLBImageAsset::getAttribute(u8 attribID, s32& attribValue) 
{
	for (int n = 0; n < m_attribCount; n++) {
		if (this->m_attribList[n].attribID == attribID) {
			if (this->m_attribList[n].type == ASSET_ATTRIB::zATTRIB_INT) {
				attribValue = m_attribList[n].v.value;
				return true;
			}
		}
	}
	return false;
}

bool 
CKLBImageAsset::getAttribute(u8 attribID, float& attribValue) 
{
	for (int n = 0; n < m_attribCount; n++) {
		if (this->m_attribList[n].attribID == attribID) {
			if (this->m_attribList[n].type == ASSET_ATTRIB::zATTRIB_FLOAT) {
				attribValue = m_attribList[n].v.fvalue;
				return true;
			}
		}
	}
	return false;
}

bool 
CKLBImageAsset::getAttribute(u8 attribID, const char*& attribValue) 
{
	for (int n = 0; n < m_attribCount; n++) {
		if (this->m_attribList[n].attribID == attribID) {
			if (this->m_attribList[n].type == ASSET_ATTRIB::zATTRIB_STRING) {
				attribValue = m_attribList[n].v.str;
				return true;
			}
		}
	}
	return false;
}

void 
CKLBImageAsset::getXY(u32 vertexIndex, float* pX, float* pY) 
{
	klb_assert(pX && pY, "null pointer");
	klb_assert(vertexIndex < m_uiVertexCount , "invalid index");
	if (vertexIndex < m_uiVertexCount) {
		vertexIndex *= 2;
		*pX = m_pXYCoord[vertexIndex++];
		*pY = m_pXYCoord[vertexIndex  ];
	}
}

void 
CKLBImageAsset::getUV(u32 vertexIndex, float* pU, float* pV) 
{
	klb_assert(pU && pV, "null pointer");
	klb_assert(vertexIndex < m_uiVertexCount , "invalid index");
	if (vertexIndex < m_uiVertexCount) {
		vertexIndex *= 2;
		*pU = m_pUVCoord[vertexIndex++];
		*pV = m_pUVCoord[vertexIndex  ];
	}
}

void 
CKLBImageAsset::setSubImage(u32 width, u32 height, u32 offX, u32 offY) 
{
	this->m_tileWidth	= width;
	this->m_tileHeight	= height;
	this->m_tileOffX	= offX;
	this->m_tileOffY	= offY;
	this->m_tileCount	= this->m_imageSize.getWidth() / m_tileWidth;
	if (m_tileCount == 0) {
		m_tileCount = 1;
	}
}

CKLBImageAsset* 
CKLBImageAsset::findSub(u32 index) 
{
	CKLBImageAsset* pAsset = this->m_subTiles;
	while (pAsset) {
		if (pAsset->m_subIndex == index) {
			return pAsset;
		}
		pAsset = pAsset->m_nextSubTile;
	}
	return NULL;
}

void 
CKLBImageAsset::addSubImage(CKLBImageAsset* pImage) 
{
	// add to link list.
	pImage->m_nextSubTile = this->m_subTiles;
	this->m_subTiles	= pImage;
}

CKLBImageAsset*	CKLBImageAsset::getSubImage(u32 index, CKLBImageAsset* pAsset) {
	if (m_uiSubTileCount != 1) {
		klb_assertAlways("TODO implement");
	} else {
		if (m_uiIndexCount == 6 && m_uiVertexCount == 4) {
			bool doAlloc = (!pAsset);
			if (doAlloc) {
				pAsset = findSub(index); 
				if (!pAsset) {
					pAsset = KLBNEW(CKLBImageAsset);
				} else {
					return pAsset;
				}
			} else {
				klb_assertAlways("FORBIDDEN FOR NOW");
				return NULL;
			}

			if (pAsset) {
				this->addSubImage(pAsset);
				// pAsset->m_assetID		= CKLBAssetManager::getInstance()->allocateAssetSlot(pAsset);
				pAsset->m_pTextureAsset	= this->m_pTextureAsset;
				pAsset->m_pName			= this->m_pName;
				pAsset->m_subIndex		= index;


				pAsset->m_bAllocatedOutsideTexture	= true;

				if (doAlloc) {
					pAsset->m_pXYCoord	= KLBNEWA(float,(8*2) + 3);
					pAsset->m_pUVCoord	= &pAsset->m_pXYCoord[8]; 
					pAsset->m_pIndex	= (u16*)(&pAsset->m_pUVCoord[8]);
				}

				if (pAsset->m_pXYCoord) {
					u32 tY = index / m_tileCount;
					u32 tX = index - (tY * m_tileCount);
					float fWidth	= this->m_pXYCoord[2] - this->m_pXYCoord[0];
					float fHeight	= this->m_pXYCoord[5] - this->m_pXYCoord[1];

					//
					// Index
					//
					pAsset->m_pIndex[0]	= 0;
					pAsset->m_pIndex[1]	= 1;
					pAsset->m_pIndex[2]	= 3;
					pAsset->m_pIndex[3]	= 1;
					pAsset->m_pIndex[4]	= 2;
					pAsset->m_pIndex[5]	= 3;

					//
					// Coordinate subtile.
					//
					pAsset->m_pXYCoord[0] = (float)m_tileOffX;
					pAsset->m_pXYCoord[1] = (float)m_tileOffY;

					pAsset->m_pXYCoord[2] = (float)(m_tileOffX + m_tileWidth);
					pAsset->m_pXYCoord[3] = (float)m_tileOffY;

					pAsset->m_pXYCoord[4] = pAsset->m_pXYCoord[2];
					pAsset->m_pXYCoord[5] = (float)(m_tileOffY + m_tileHeight);

					pAsset->m_pXYCoord[6] = (float)m_tileOffX;
					pAsset->m_pXYCoord[7] = pAsset->m_pXYCoord[5];

					//
					// UV SubTile
					//
					float UPixStep	    = (this->m_pUVCoord[2] - this->m_pUVCoord[0]) / fWidth;
					float VPixStep	    = (this->m_pUVCoord[5] - this->m_pUVCoord[1]) / fHeight;
					float UStep		    = UPixStep * m_tileWidth ;
					float VStep		    = VPixStep * m_tileHeight;
					float UStepOffset   = UStep * m_tileOffX;
					float VStepOffset   = VStep * m_tileOffY;
					float U0            = this->m_pUVCoord[0] + (UStep * tX) + UStepOffset;
					float V0            = this->m_pUVCoord[1] + (VStep * tY) + VStepOffset;
					float U1            = U0 + UStep;
					float V1            = V0 + VStep;

					pAsset->m_pUVCoord[0] = U0;
					pAsset->m_pUVCoord[1] = V0;
					pAsset->m_pUVCoord[2] = U1;
					pAsset->m_pUVCoord[3] = V0;
					pAsset->m_pUVCoord[4] = U1;
					pAsset->m_pUVCoord[5] = V1;
					pAsset->m_pUVCoord[6] = U0;
					pAsset->m_pUVCoord[7] = V1;

					pAsset->m_iCenterX = 0;
					pAsset->m_iCenterY = 0;
					pAsset->m_uiVertexCount	= 4;
					pAsset->m_uiIndexCount  = 6;

					pAsset->m_imageSize.m_iTop		= 0;
					pAsset->m_imageSize.m_iBottom	= m_tileHeight;
					pAsset->m_imageSize.m_iLeft		= 0;
					pAsset->m_imageSize.m_iRight	= m_tileWidth;
					pAsset->m_boundWidth			= m_tileWidth;
					pAsset->m_boundHeight			= m_tileHeight;
				} else {
					// Delete all sub systems too.
					KLBDELETE(pAsset);
					pAsset = NULL;
				}
			}
			return pAsset;
		}
	}
	return NULL;
}

CKLBImageAsset* 
KLBTextureAssetPlugin::loadImage(u8* stream, u32 /*streamSize*/, CKLBImageAsset* pReload) 
{
	//
	// u8  Vertex Count
	// u8  Index  Count
	// u16	center X
	// u16	center Y
	//
	// Vertex Count	--> Convert into UV and XY
	// u32 X		
	// u32 Y
	// Index Count
	// u8  Index
	CKLBImageAsset* pNewAssetI = m_pReloadAsset ? pReload : KLBNEW(CKLBImageAsset);
	if (pNewAssetI) {
		// Str Length including zero and padding.
		u16 length = (stream[0] << 8) | stream[1];
		stream += 2;
	
		// Name
		// + [pad]
		if (!m_pReloadAsset)
		pNewAssetI->m_pName	= pNewAssetI->allocateName(stream, length);

		if (!pNewAssetI->m_pName) {
			return NULL;
		}
		stream += length;

		pNewAssetI->m_uiSubTileCount	= (stream[0] << 8) | stream[1];
		stream += 2;

		bool is3dModel		= false;
		bool loadUVIndex	= true;
		bool compactUV		= false;
		if (pNewAssetI->m_uiSubTileCount == 0xFFFE) {
			compactUV = true;
		}

		u32 patchCoordinateModeFromAttribute = 0;
		if (pNewAssetI->m_uiSubTileCount == 0xFFFF) {
			// Extension with attribute.

			// Attribute count.
			u32 attribCount = (stream[0]<<8) | stream[1]; stream += 2;
			pNewAssetI->m_attribCount = attribCount;
			
			if (!m_pReloadAsset)
			pNewAssetI->m_attribList = KLBNEWA(ASSET_ATTRIB,attribCount);

			if (pNewAssetI->m_attribList) {
				ASSET_ATTRIB* pAtt = pNewAssetI->m_attribList;
				for (u32 n=0; n<attribCount; n++) {
					pAtt[n].type		= ASSET_ATTRIB::zATTRIB_INT;	// Default in case of error.
				}

				for (u32 n=0; n<attribCount; n++) {
					// Key ID + Type + Value
					u8 key	= *stream++;
					u8 type = *stream++;
					pAtt[n].attribID	= key;
					pAtt[n].type		= type;

					if (key == ASSET_ATTRIB::zK0_RECT) {
						// Standard Rect
						pNewAssetI->m_usageType |= CKLBImageAsset::IS_STANDARD_RECT;
					}
					if (key == ASSET_ATTRIB::zK1_SC_LEFT) {
						// Scroll Bar
						pNewAssetI->m_usageType |= CKLBImageAsset::IS_SCROLLBARTYPE;
					}
					if (key == ASSET_ATTRIB::zK2_S9_LEFT) {
						// Slice 9
						pNewAssetI->m_usageType |= CKLBImageAsset::IS_SCALE9;
					}
					if (key == ASSET_ATTRIB::z3DMODEL) {
						pNewAssetI->m_usageType |= CKLBImageAsset::IS_3DMODEL;
						is3dModel = true;
					}

					switch (type) {
					case ASSET_ATTRIB::zATTRIB_INT:
					case ASSET_ATTRIB::zATTRIB_FLOAT:
						pAtt[n].v.value	= (stream[0]<<24) | (stream[1]<<16) | (stream[2]<<8) | (stream[3]);
						if (is3dModel) {
							loadUVIndex = (pAtt[n].v.value & 0x80000000) ? true : false;
						}
						if (key == ASSET_ATTRIB::zK4_STRETCH_OR_SCALE) {
							patchCoordinateModeFromAttribute = pAtt[n].v.value;
						}
						stream += 4;
						break;
					case ASSET_ATTRIB::zATTRIB_STRING:
						{
							u8 argLen = (stream[0]<<8) | stream[1];
							stream += 2;
							if (argLen) {
								char* p	= KLBNEWA(char,argLen);
								if (p) {
									pAtt[n].v.str = p;
									memcpy(p, stream, argLen);
									stream += argLen;
								} else {
									klb_assertAlways("Memory alloc fail.");
									return NULL;
								}
							} else {
								pAtt[n].v.str	= NULL;
							}
						}
						break;
					default:
						klb_assertAlways("Invalid Image Attribute Type");
						break;
					}

					if (key == ASSET_ATTRIB::zK3_OFFSET) {
						pNewAssetI->m_renderOffset = pAtt[n].v.value;					
					}
				}
			} else {
				return NULL;
			}

			pNewAssetI->m_uiSubTileCount = (stream[0] << 8) | stream[1];
			stream += 2;
		}

		for (u32 n=0; n < pNewAssetI->m_uiSubTileCount; n++) {
			CKLBImageAsset* pNewAsset;
			if (pNewAssetI->m_uiSubTileCount == 1) {
				pNewAsset = pNewAssetI;
			} else {
				pNewAsset = KLBNEW(CKLBImageAsset);
			}

			if (!pNewAsset) {
				return NULL;
			}

			if (is3dModel) {
				pNewAsset->m_uiVertexCount  = (stream[0] << 8) | stream[1]; stream += 2;
				pNewAsset->m_uiIndexCount	= (stream[0] << 8) | stream[1]; stream += 2;
			} else {
				pNewAsset->m_uiVertexCount	= *stream++;
				pNewAsset->m_uiIndexCount	= *stream++;
			}

			pNewAsset->m_imageSize.m_iRight	 = (stream[0] << 8) | stream[1]; stream += 2;
			pNewAsset->m_imageSize.m_iBottom = (stream[0] << 8) | stream[1]; stream += 2;

			// Decide to use information from image info (tool) when standard rect AND borderless mode.
			u32 patchCoordinateMode = 0;
			if (pNewAssetI->m_usageType & CKLBImageAsset::IS_STANDARD_RECT) {
				if (CKLBDrawResource::getInstance().hasBorder() == false) {
					patchCoordinateMode = patchCoordinateModeFromAttribute;
				}
			}

			pNewAsset->m_imageSize.m_iLeft	= 0;
			pNewAsset->m_imageSize.m_iTop	= 0;

			pNewAsset->m_iCenterX	= (s16)((stream[0] << 8) | stream[1]); stream += 2;
			pNewAsset->m_iCenterY	= (s16)((stream[0] << 8) | stream[1]); stream += 2;

			float cx = pNewAsset->m_iCenterX;
			float cy = pNewAsset->m_iCenterY;

			if (m_pUVBuffer && m_pXYBuffer && m_pIndexBuffer) {
				pNewAsset->m_pUVCoord	= this->m_pUVBuffer;
				pNewAsset->m_pXYCoord	= this->m_pXYBuffer;
				pNewAsset->m_pIndex		= this->m_pIndexBuffer;
			} else {
				// find a way to get this->m_pTextureAsset if to implement.
				klb_assertAlways( "stand alone loading not implemented : should create array and implement asset destructor.");
			}

			if (pNewAsset->m_pUVCoord	&&
				pNewAsset->m_pXYCoord	&&
				pNewAsset->m_pIndex	 	&&
				this->m_pTextureAsset) {

				pNewAsset->m_pTextureAsset	= this->m_pTextureAsset;	// For Rendering.

				float minX = 9999.0f;
				float minY = 9999.0f;
				float maxX = -9999.0f;
				float maxY = -9999.0f;

				int idxVert = 0;
				int stepVert;
				if (is3dModel) {
					stepVert = 3;
				} else {
					stepVert = 2;
				}

				for (int n=0; n < pNewAsset->m_uiVertexCount; n++) {
					// XY Coordinates in screen space.
					u32 val	= (stream[0] << 24) | (stream[1] << 16) | (stream[2] << 8) | stream[3];
					float x = (val / 65536.0f) - cx;
					pNewAsset->m_pXYCoord[idxVert  ] = x;
					stream	+= 4;

					val		= (stream[0] << 24) | (stream[1] << 16) | (stream[2] << 8) | stream[3];
					float y = (val / 65536.0f) - cy;
					pNewAsset->m_pXYCoord[idxVert+1] = y;
					stream	+= 4;

					if (is3dModel) {
						val		= (stream[0] << 24) | (stream[1] << 16) | (stream[2] << 8) | stream[3];
						float z = (val / 65536.0f);
						pNewAsset->m_pXYCoord[idxVert+2] = z;
						stream	+= 4;
					} else {
						if (x < minX) { minX = x; }
						if (x > maxX) { maxX = x; }

						if (y < minY) { minY = y; }
						if (y > maxY) { maxY = y; }
					}

					idxVert	+= stepVert;

					if (loadUVIndex) {
						if (compactUV) {
							// UV Coordinates in texture
							val		= (stream[0] << 8) | (stream[1]);
							pNewAsset->m_pUVCoord[(n * 2)  ] = (val / 32768.0f);
							stream	+= 2;

							val		= (stream[0] << 8) | (stream[1]);
							pNewAsset->m_pUVCoord[(n * 2)+1] = (val / 32768.0f);
							stream	+= 2;
						} else {
							// UV Coordinates in texture
							val		= (stream[0] << 24) | (stream[1] << 16) | (stream[2] << 8) | stream[3];
							pNewAsset->m_pUVCoord[(n * 2)  ] = (val / 65536.0f);
							stream	+= 4;

							val		= (stream[0] << 24) | (stream[1] << 16) | (stream[2] << 8) | stream[3];
							pNewAsset->m_pUVCoord[(n * 2)+1] = (val / 65536.0f);
							stream	+= 4;
						}
					}
				}

				if (patchCoordinateMode == 1) {
					int deltaX = CKLBDrawResource::getInstance().ox();
					int deltaY = CKLBDrawResource::getInstance().oy();

					pNewAsset->m_pXYCoord[0] -= deltaX;
					pNewAsset->m_pXYCoord[1] -= deltaY;

					pNewAsset->m_pXYCoord[2] += deltaX;
					pNewAsset->m_pXYCoord[3] -= deltaY;

					pNewAsset->m_pXYCoord[4] += deltaX;
					pNewAsset->m_pXYCoord[5] += deltaY;

					pNewAsset->m_pXYCoord[6] -= deltaX;
					pNewAsset->m_pXYCoord[7] += deltaY;
				} else if (patchCoordinateMode == 2) {
					int deltaX = CKLBDrawResource::getInstance().ox();
					int deltaY = CKLBDrawResource::getInstance().oy();
					if (deltaX) {
						float purcX = deltaX / (float)CKLBDrawResource::getInstance().width();
						deltaY = purcX * CKLBDrawResource::getInstance().height();
					} else {
						float purcY = deltaY / (float)CKLBDrawResource::getInstance().height();
						deltaX = purcY * CKLBDrawResource::getInstance().width();
					}

					pNewAsset->m_pXYCoord[0] -= deltaX;
					pNewAsset->m_pXYCoord[1] -= deltaY;

					pNewAsset->m_pXYCoord[2] += deltaX;
					pNewAsset->m_pXYCoord[3] -= deltaY;

					pNewAsset->m_pXYCoord[4] += deltaX;
					pNewAsset->m_pXYCoord[5] += deltaY;

					pNewAsset->m_pXYCoord[6] -= deltaX;
					pNewAsset->m_pXYCoord[7] += deltaY;
				}

				if (loadUVIndex) {
					for (int n = 0; n < pNewAsset->m_uiIndexCount; n++) {
						pNewAsset->m_pIndex[n] = *stream++;
					}

					this->m_pLastLoadedUV		= pNewAsset->m_pUVCoord;
					this->m_pLastLoadedIndex	= pNewAsset->m_pIndex;
					this->m_pUVBuffer			+= (pNewAsset->m_uiVertexCount * 2);
					this->m_pIndexBuffer		+= pNewAsset->m_uiIndexCount;
				} else {
					this->m_pUVBuffer			= this->m_pLastLoadedUV;
					this->m_pIndexBuffer		= this->m_pLastLoadedIndex;
				}
				this->m_pXYBuffer			+= (pNewAsset->m_uiVertexCount * stepVert);

				pNewAsset->m_boundWidth		= maxX - minX;
				pNewAsset->m_boundHeight	= maxY - minY;
				return pNewAsset;
			}
		}
	}

	klb_assertNull(0,"allocation failure.");
	return NULL;
}

/**
	Trick function to allow sharing buffer for all images into texture
	and not using multiple allocation.
 */
void 
KLBTextureAssetPlugin::setBuffers(CKLBTextureAsset*	pTextureAsset, float* uvBuffer, float* xyBuffer, u16* indexBuffer) 
{
	m_pUVBuffer		= uvBuffer;
	m_pXYBuffer		= xyBuffer;
	m_pIndexBuffer	= indexBuffer;
	m_pTextureAsset	= pTextureAsset;
}

// ---------------------------------------------------------------------------------------------
//   Texture.
// ---------------------------------------------------------------------------------------------

KLBTextureAssetPlugin::KLBTextureAssetPlugin()
: IKLBAssetPlugin   ()
, m_pUVBuffer       (NULL)
, m_pXYBuffer       (NULL)
, m_pIndexBuffer    (NULL)
, m_pTextureAsset   (NULL)
, m_loadHardware    (true)
, m_loadSoftware    (false)
, m_useQuarterTexture(false)
{
}

KLBTextureAssetPlugin::~KLBTextureAssetPlugin() 
{
}

void
KLBTextureAssetPlugin::setLoadingMode(E_TEXTURELOADINGMODE mode) 
{
	switch (mode) {
	case TEX_LOAD_GPU:
		m_loadHardware = true;
		m_loadSoftware = false;
		break;
	case TEX_LOAD_CPU:
		m_loadHardware = false;
		m_loadSoftware = true;
		break;
	case TEX_LOAD_GPUCPU:
		m_loadHardware = true;
		m_loadSoftware = true;
		break;
	}
}

u8* 
KLBTextureAssetPlugin::createSoftTexture(s32 width, s32 height, u32 pixelFormat, u8 channelCount, void* data) 
{
	u8* buffer = KLBNEWA(u8, width * height * 4);
	u8* retBuf = buffer;

	if (buffer) {
		// Setup default alpha
		u8 alpha = 255;

		switch (pixelFormat) {
		case GL_UNSIGNED_SHORT_5_6_5:
			{
				// GL_RGB
				u16* src = (u16*)data;
				for (int y = 0 ; y < height; y++) {
					for (int x = 0 ; x < width ; x++) {
						// RGBA
						u8 tmp = (*src & 0xF800)>>8;
						*buffer++ = tmp | (tmp >> 5);	// Full 5->8 Bit conv
						tmp = (*src & 0x07E0) >> 3;
						*buffer++ = tmp | (tmp >> 6);	// Full 6->8 Bit conv
						tmp = (*src & 0x001F) << 3;
						*buffer++ = tmp | (tmp >> 5);	// Full 5->8 Bit conv
						*buffer++ = alpha;
						src++;
					}
				}
			}
			break;
		case GL_UNSIGNED_SHORT_5_5_5_1:
			{
				u16* src = (u16*)data;
				for (int y = 0 ; y < height; y++) {
					for (int x = 0 ; x < width ; x++) {
						// RGBA
						u8 tmp = (*src & 0xF800)>>8;
						*buffer++ = tmp | (tmp >> 5);	// Full 5->8 Bit conv
						tmp = (*src & 0x07C0) >> 3;
						*buffer++ = tmp | (tmp >> 5);	// Full 5->8 Bit conv
						tmp = (*src & 0x003E) << 2;
						*buffer++ = tmp | (tmp >> 5);	// Full 5->8 Bit conv
						*buffer++ = ((s8)((*src & 1)<<7))>>7;	// Full 1->8 Bit conv
						src++;
					}
				}
			}
			break;
		case GL_UNSIGNED_SHORT_4_4_4_4:
			{
				u16* src = (u16*)data;
				for (int y = 0 ; y < height; y++) {
					for (int x = 0 ; x < width ; x++) {
						// RGBA
						u8 tmp = (*src & 0xF000)>>8;
						*buffer++ = tmp | (tmp >> 4);	// Full 4->8 Bit conv
						tmp = (*src & 0x0F00) >> 4;
						*buffer++ = tmp | (tmp >> 4);	// Full 4->8 Bit conv
						tmp = (*src & 0x00F0);
						*buffer++ = tmp | (tmp >> 4);	// Full 4->8 Bit conv
						tmp = (*src & 0x000F);
						*buffer++ = tmp | (tmp << 4);	// Full 4->8 Bit conv
						src++;
					}
				}
			}
			break;
		default:	// Byte
			switch (channelCount) {
			case 1:
			case 2:
				klb_assertAlways("Those texture mode are not supported");
				break;
			case 3:
				{
					u8* src = (u8*)data;
					for (int y = 0 ; y < height; y++) {
						for (int x = 0 ; x < width ; x++) {
							*buffer++ = *src++;
							*buffer++ = *src++;
							*buffer++ = *src++;
							*buffer++ = 255;
						}
					}
				}
				break;
			case 4:
				{
					memcpy(buffer, data, width * height * 4);
				}
				break;
			}
			break;
		}
	}

	return retBuf;
}

void 
processImage8888(u32 /*pixelCount*/, u32 lineWidth, u32 height, u8* buffer) 
{
	u32* line1 = (u32*)buffer;
	u32* line2 = &(((u32*)buffer)[lineWidth]);
	u8* dst = buffer;
	for (u32 y = 0; y < (height >> 1); y++) {
		u8* pix1 = (u8*)line1;
		u8* pix2 = (u8*)line2;
		for (u32 x=0; x < (lineWidth >> 1); x++) {
			u32 sum;
			sum = (pix1[0] + pix1[4] + pix2[0] + pix2[4])>>2;
			*dst++ = sum;
			sum = (pix1[1] + pix1[5] + pix2[1] + pix2[5])>>2;
			*dst++ = sum;
			sum = (pix1[2] + pix1[6] + pix2[2] + pix2[6])>>2;
			*dst++ = sum;
			sum = (pix1[3] + pix1[7] + pix2[3] + pix2[7])>>2;
			*dst++ = sum;

			pix1 += 8;
			pix2 += 8;
		}
		// Skip 2 lines.
		line1 += lineWidth << 1;
		line2 += lineWidth << 1;
	}	
}

void 
processImage565(u32 pixelCount, u32 lineWidth, u32 height, u8* buffer) 
{
	u16* pSrc	= (u16*)buffer;
	u32* pDst	= (u32*)pSrc;
	u16* pDst16	= pSrc;

	//
	// Horizontal pass.
	//
#define R_B		(0xF81F)
#define _G_		(0x07E0)
#define SHIFTNEXT	(16)
	for (u32 n = 0; n < (pixelCount>>1); n++) {
		u32 pix1	= *pSrc++;
		u32 pix2	= *pSrc++;
		*pDst++ = (((pix1 & _G_) << SHIFTNEXT) | (pix1 & R_B)) + (((pix2 & _G_) << SHIFTNEXT) | (pix2 & R_B));
	}

	//
	// Vertical Pass + Mixing into correct.
	//
	u32* line1 = (u32*)buffer;
	u32* line2 = &(((u32*)buffer)[lineWidth>>1]);
	pDst16 = (u16*)buffer;
	for (u32 y = 0; y < (height >> 1); y++) {
		for (u32 x=0; x < (lineWidth >> 1); x++) {
			u32 pix		= (((*line1++) + (*line2++))) >> 2;
			*pDst16++	= ((pix & (_G_ << SHIFTNEXT)) >> SHIFTNEXT) | (pix & R_B);
		}
		// Skip 2 lines.
		line1 += lineWidth>>1;
		line2 += lineWidth>>1;
	}
#undef	R_B
#undef  _G_
#undef SHIFTNEXT
}

void 
processImage4444(u32 pixelCount, u32 lineWidth, u32 height, u8* buffer) 
{
	// 8 Bit
	u16* pSrc	= (u16*)buffer;
	u32* pDst	= (u32*)pSrc;
	u16* pDst16	= pSrc;

	//
	// Horizontal pass.
	//
#define _R_B	(0x0F0F)
#define A_G_	(0xF0F0)
#define SHIFTNEXT	(16 - 2)
	for (u32 n = 0; n < (pixelCount>>1); n++) {
		u32 pix1	= *pSrc++;
		u32 pix2	= *pSrc++;
		*pDst++ = (((pix1 & A_G_) << SHIFTNEXT) | (pix1 & _R_B)) + (((pix2 & A_G_) << SHIFTNEXT) | (pix2 & _R_B));
	}

	//
	// Vertical Pass + Mixing into correct.
	//
	u32* line1 = (u32*)buffer;
	u32* line2 = &(((u32*)buffer)[lineWidth>>1]);
	pDst16 = (u16*)buffer;
	for (u32 y = 0; y < (height >> 1); y++) {
		for (u32 x=0; x < (lineWidth >> 1); x++) {
			u32 pix		= (((*line1++) + (*line2++))) >> 2;
			*pDst16++	= ((pix & (A_G_ << SHIFTNEXT)) >> SHIFTNEXT) | (pix & _R_B);
		}
		// Skip 2 lines.
		line1 += lineWidth>>1;
		line2 += lineWidth>>1;
	}
#undef	_R_B
#undef  A_G_
#undef  SHIFTNEXT
}

void 
processImage5551(u32 pixelCount, u32 lineWidth, u32 height, u8* buffer) 
{
	// 8 Bit
	u16* pSrc	= (u16*)buffer;
	u32* pDst	= (u32*)pSrc;
	u16* pDst16	= pSrc;

	//
	// Horizontal pass.
	//
	// rrrrr ggggg bbbbb a
	// 00000 11111 00000 1
	// 0000.0111.1100.0001	0x07C1

	// 11111 00000 11111 0
	// 1111.1000.0011.1110

	//	1111.1000.0011.1110|0000.0111.1100.0001

#define _R_B	(0x07C1)
#define A_G_	(0xF83E)
#define SHIFTNEXT	(16 - 2)
	for (u32 n = 0; n < (pixelCount>>1); n++) {
		u32 pix1	= *pSrc++;
		u32 pix2	= *pSrc++;
		*pDst++ = (((pix1 & A_G_) << SHIFTNEXT) | (pix1 & _R_B)) + (((pix2 & A_G_) << SHIFTNEXT) | (pix2 & _R_B));
	}

	//
	// Vertical Pass + Mixing into correct.
	//
	u32* line1 = (u32*)buffer;
	u32* line2 = &(((u32*)buffer)[lineWidth>>1]);
	pDst16 = (u16*)buffer;
	for (u32 y = 0; y < (height >> 1); y++) {
		for (u32 x=0; x < (lineWidth >> 1); x++) {
			u32 pix		= (((*line1++) + (*line2++))) >> 2;
			*pDst16++	= ((pix & (A_G_ << SHIFTNEXT)) >> SHIFTNEXT) | (pix & _R_B);
		}
		// Skip 2 lines.
		line1 += lineWidth>>1;
		line2 += lineWidth>>1;
	}
#undef	_R_B
#undef  A_G_
#undef  SHIFTNEXT
}

/*virtual*/
CKLBAbstractAsset* 
KLBTextureAssetPlugin::loadAsset(u8* stream, u32 streamSize) 
{
	CKLBTextureAsset* pNewAsset = m_pReloadAsset ? ((CKLBTextureAsset*)m_pReloadAsset) : KLBNEW(CKLBTextureAsset);

	if (pNewAsset) {
		u8* streamStart = stream;

		// Str Length including zero and padding.
		u16 length = (stream[0] << 8) | stream[1];
		stream += 2;
	
		if (!m_pReloadAsset)
		pNewAsset->m_fileSource = CKLBUtility::copyString(this->m_currentFile);

		// + [pad]
		if (!m_pReloadAsset)
		pNewAsset->m_pName		= pNewAsset->allocateName(stream, length);
		stream += length;

		//
		// Width		2 byte
		// Height		2 byte
		// Type			2 byte
		// totalVertexCount 2/6 byte
		// totalIndexCount	2/6 byte
		// ImageCount	2 byte
		//

		pNewAsset->m_width				= (stream[0]<<8) | stream[1]; stream += 2;
		pNewAsset->m_height				= (stream[0]<<8) | stream[1]; stream += 2;
		pNewAsset->m_type				= (stream[0]<<8) | stream[1]; stream += 2;
		pNewAsset->m_totalVertexCount	= (stream[0]<<8) | stream[1]; stream += 2;

		if (pNewAsset->m_totalVertexCount == 0xFFFF) {
			pNewAsset->m_totalVertexCount	= (stream[0]<<24) | (stream[1]<<16) | (stream[2]<<8) | stream[3]; stream += 4;
		}
		pNewAsset->m_totalIndexCount	= (stream[0]<<8) | stream[1]; stream += 2;
		if (pNewAsset->m_totalIndexCount == 0xFFFF) {
			pNewAsset->m_totalIndexCount	= (stream[0]<<24) | (stream[1]<<16) | (stream[2]<<8) | stream[3]; stream += 4;
		}
		pNewAsset->m_imageCount			= (stream[0]<<8) | stream[1]; stream += 2;

		int uvOffset;
		if (pNewAsset->m_type & 0x8000) {
			uvOffset = (stream[0]<<24) | (stream[1]<<16) | (stream[2]<<8) | stream[3]; stream += 4;
		} else {
			uvOffset = pNewAsset->m_totalVertexCount * 2;
			pNewAsset->m_totalVertexCount *= 4;
		}

		if (!m_pReloadAsset) {
		pNewAsset->m_floatBufferTotal	= KLBNEWA(float				,pNewAsset->m_totalVertexCount		);
		pNewAsset->m_indexBufferTotal	= KLBNEWA(u16				,pNewAsset->m_totalIndexCount		);	// UV and X,Y
		pNewAsset->m_pImages			= KLBNEWA(CKLBImageAsset*	,pNewAsset->m_imageCount			);
		}

		if (pNewAsset->m_floatBufferTotal && pNewAsset->m_indexBufferTotal && pNewAsset->m_pImages && pNewAsset->m_pName) {
			//
			// Trick here : texture loader directly embed the image loading process
			// and allocate the buffers for the image objects.
			// --> Special API are added to the Image plugin to do so.
			//
			
			setBuffers(
				pNewAsset,
				pNewAsset->m_floatBufferTotal,										// UV Storage
				&pNewAsset->m_floatBufferTotal[uvOffset],	// XY Storage
				pNewAsset->m_indexBufferTotal);

			for (u16 n = 0; n < pNewAsset->m_imageCount; n++) {
				//
				// Stream size
				//
				stream += 4;	// Skip [TIMG]/[3DM_]
				u32 size = (stream[0]<<8) | stream[1]; stream += 2;
				if (size == 0xFFFF) {
					size = (stream[0]<<24) | (stream[1]<<16) | (stream[2]<<8) | stream[3]; stream += 4;
				}
		
				CKLBImageAsset* pImg = loadImage(stream, size, pNewAsset->m_pImages[n]);
				pNewAsset->m_pImages[n] = pImg;

				if (pNewAsset->m_pImages[n] == NULL) {
					return NULL;
				}
				stream += size;
			}

			// + [pad] : 4 byte aligned texture.
			// Default for uncompressed stream.
			pNewAsset->m_bitmap				= &stream[0];
			
			// Texture size is all the data remaining (FullDataSize - AlreadyReadDataSize )
			u32 textureSize = streamSize - (stream - streamStart);
			bool hardCompression = false;

			GLenum pixelFormat;
			CKLBOGLWrapper::TEX_CHANNEL channelCount;

			// 0 ALPHA | 1 LUMA | 2 LUMALPHA | 3 RGB | 4 RGBA	// Bit 0..2
			// COMPRESS (3) | DOUBLE_BUFF (5) | MIPMAP (4)		// Bit 3,4,5
			// 0 565 | 1 5551 | 2 4444 | 3 8					// Bit 6..7

			switch (pNewAsset->m_type & 0x7) {
			case 0:
				channelCount = CKLBOGLWrapper::ALPHA;
				break;
			case 1:
				channelCount = CKLBOGLWrapper::LUMINANCE;
				break;
			case 2:
				channelCount = CKLBOGLWrapper::LUMINANCE_ALPHA;
				break;
			case 3:
				channelCount = CKLBOGLWrapper::RGB;
				break;
			case 4:
			default:
				channelCount = CKLBOGLWrapper::RGBA;
				break;
			}

			int bytePerPix;
			int hasClick;

			switch ((pNewAsset->m_type>>6) & 0x3) {
			case 0:
				pixelFormat = GL_UNSIGNED_SHORT_5_6_5;
				bytePerPix	= 2;
				hasClick	= 0;
				break;
			case 1:
				pixelFormat = GL_UNSIGNED_SHORT_5_5_5_1;
				bytePerPix	= 2;
				hasClick	= 1;
				break;
			case 2:
				pixelFormat = GL_UNSIGNED_SHORT_4_4_4_4;
				bytePerPix	= 2;
				hasClick	= 1;
				break;
			case 3:
			default:	// Avoid warning.
				pixelFormat = GL_UNSIGNED_BYTE;
				bytePerPix	= 1 * (channelCount ? channelCount : 1); // Luminance is 1 byte.
				hasClick	= 1;
				break;
			}

			u32 opt = CKLBOGLWrapper::TEX_NONE;
			u32 compressType = 0;
			if (pNewAsset->m_type & (1<<3)) {
				compressType = (stream[0]<<24) | (stream[1]<<16) | (stream[2]<<8) | stream[3]; stream += 4;

				// Extension to be supported, read 4 more byte to find out.
				if (compressType == 0) {
					/* textureSize = zlib stream */
					u32 outputSize = bytePerPix * pNewAsset->m_width * pNewAsset->m_height;
					pNewAsset->m_bitmap				= KLBNEWA(u8, outputSize);

					if (pNewAsset->m_bitmap) {
						u8* in = &stream[0];
						// textureSize = compressed stream Size.
						int ret;
						z_stream strm;

						/* allocate deflate state */
						strm.zalloc     = Z_NULL;
						strm.zfree      = Z_NULL;
						strm.opaque     = Z_NULL;
						strm.avail_in   = 0;
						strm.next_in    = Z_NULL;
						ret = inflateInit(&strm);
						if (ret != Z_OK) {
							KLBDELETEA((u8*)pNewAsset->m_bitmap);
							pNewAsset->m_bitmap = NULL;
						}

						// Number of byte available in the stream for decompression.
						strm.avail_in = textureSize; 
						// Input stream setup
						strm.next_in  = in;

						// Number of byte available in the output buffer for decompression.
						strm.avail_out = outputSize;
						// Target Buffer for decompression.
						strm.next_out  = (u8*)pNewAsset->m_bitmap;

						//---------------------------------
						// Decompress me !
						MEASURE_THREAD_CPU_BEGIN(TASKTYPE_TEX_LOAD_INFLATE);
						ret = inflate(&strm, Z_NO_FLUSH);
						MEASURE_THREAD_CPU_END(TASKTYPE_TEX_LOAD_INFLATE);
						if ((ret != Z_OK) && (ret != Z_STREAM_END)) {
							KLBDELETEA((u8*)pNewAsset->m_bitmap);
							pNewAsset->m_bitmap = NULL;
						}
						//---------------------------------
					
						// Job complete, end.
						// do not care about end result 
						// because all the free possible have been made.
						ret = inflateEnd(&strm);
					}
				} else {
					//
					// Support for later extension PVRTC, ETC1, ETC2, ...
					//
					hardCompression = true;
					opt |= CKLBOGLWrapper::TEX_OPT_COMPRESSED_BIT;
					// pixelFormat	setup
					// channelCount	setup
					// Stream shifted by 4 byte (compress type)

					char *exts = (char *)glGetString(GL_EXTENSIONS);

					// Prefer to put the strcmp AFTER the equality check to avoid useless string compare.
					//
					// === GL_IMG_texture_compression_pvrtc group ===
					//
					#ifdef GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG
					if ((compressType == GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG) && strstr(exts, "GL_IMG_texture_compression_pvrtc")) {
						// OK.
					} else
					#endif
					#ifdef GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG
					if ((compressType == GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG) && strstr(exts, "GL_IMG_texture_compression_pvrtc")) {
						// OK.
					} else
					#endif
					#ifdef GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG
					if ((compressType == GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG) && strstr(exts, "GL_IMG_texture_compression_pvrtc")) {
						// OK.
					} else
					#endif
					#ifdef GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG
					if ((compressType == GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG) && strstr(exts, "GL_IMG_texture_compression_pvrtc")) {
						// OK.
					} else
					#endif
					//
					// === GL_IMG_texture_compression_pvrtc2 group ===
					//
					#ifdef GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG
					if ((compressType == GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG) && strstr(exts, "GL_IMG_texture_compression_pvrtc2")) {
						// OK.
					} else
					#endif
					#ifdef GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG
					if ((compressType == GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG) && strstr(exts, "GL_IMG_texture_compression_pvrtc2")) {
						// OK.
					} else
					#endif
					//
					// === GL_OES_compressed_ETC1_RGB8_texture group ===
					//
					#ifdef GL_ETC1_RGB8_OES
					if ((compressType == GL_ETC1_RGB8_OES) && strstr(exts, "GL_OES_compressed_ETC1_RGB8_texture")) {
						// OK.
					} else
					#endif
					//
					// === ETC2 is mandatory and there is not EXTENSIONS ===
					//
					#ifdef GL_COMPRESSED_RGB8_ETC2
					if (compressType == GL_COMPRESSED_RGB8_ETC2) {
						// OK.
					} else
					#endif
					#ifdef GL_COMPRESSED_RGBA8_ETC2_EAC
					if (compressType == GL_COMPRESSED_RGBA8_ETC2_EAC) {
						// OK.
					} else
					#endif

					if (true) {
						if (compressType == 0x8D64 /*GL_ETC1_RGB8_OES*/) {
							//
							// SW decoder called.
							//

							// Reset HW compression bits
							hardCompression = false;
							compressType = 0;
							
							pixelFormat = GL_UNSIGNED_BYTE;
							bytePerPix  = 4;

							opt &= ~CKLBOGLWrapper::TEX_OPT_COMPRESSED_BIT;
							u32 outputSize = bytePerPix * pNewAsset->m_width * pNewAsset->m_height;
							pNewAsset->m_bitmap				= KLBNEWA(u8, outputSize);

							if (pNewAsset->m_bitmap) {

								/* From Khronos Specs
									First block in mem  Second block in mem
									 ---- ---- ---- ---- .... .... .... ....  --> u direction
									|a1  |e1  |i1  |m1  |a2  :e2  :i2  :m2  :
									|    |    |    |    |    :    :    :    : 
									 ---- ---- ---- ---- .... .... .... ....
									|b1  |f1  |j1  |n1  |b2  :f2  :j2  :n2  : 
									|    |    |    |    |    :    :    :    : 
									 ---- ---- ---- ---- .... .... .... ....
									|c1  |g1  |k1  |o1  |c2  :g2  :k2  :o2  : 
									|    |    |    |    |    :    :    :    : 
									 ---- ---- ---- ---- .... .... .... ....
									|d1  |h1  |l1  |p1  |d2  :h2  :l2  :p2  : 
									|    |    |    |    |    :    :    :    : 
									 ---- ---- ---- ---- ---- ---- ---- ---- 
									:a3  :e3  :i3  :m3  |a4  |e4  |i4  |m4  |
									:    :    :    :    |    |    |    |    |
									 .... .... .... .... ---- ---- ---- ---- 
									:b3  :f3  :j3  :n3  |b4  |f4  |j4  |n4  |
									:    :    :    :    |    |    |    |    |
									 .... .... .... .... ---- ---- ---- ---- 
									:c3  :g3  :k3  :o3  |c4  |g4  |k4  |o4  |
									:    :    :    :    |    |    |    |    |
									 .... .... .... .... ---- ---- ---- ---- 
									:d3  :h3  :l3  :p3  |d4  |h4  |l4  |p4  |
									:    :    :    :    |    |    |    |    |
									 .... .... .... .... ---- ---- ---- ---- 
									| Third block in mem  Fourth block in mem
									v
									v direction

									Add figure 3.9.1: Pixel layout for a ETC1 compressed block:

									 ---- ---- ---- ---- 
									|a   |e   |i   |m   |
									|    |    |    |    |
									 ---- ---- ---- ---- 
									|b   |f   |j   |n   |
									|    |    |    |    |
									 ---- ---- ---- ---- 
									|c   |g   |k   |o   |
									|    |    |    |    |
									 ---- ---- ---- ---- 
									|d   |h   |l   |p   |
									|    |    |    |    |
									 ---- ---- ---- ---- 
								*/

								// Horizontal block first then vertical lines
								u8* pSrcStream = &stream[0];
								u8* pDstStream = (u8*)pNewAsset->m_bitmap;
								u32 rgbaOut[16];
								for (int y=0; y < pNewAsset->m_height>>2; y++) {
									u32* writePix = (u32*)pDstStream; 
									for (int x=0; x < pNewAsset->m_width>>2; x++) {
										rg_etc1::unpack_etc1_block(pSrcStream, (u32*)rgbaOut,false);
										pSrcStream += 8; // Next 64 bit chunk.

										writePix[0] = rgbaOut[0];
										writePix[1] = rgbaOut[1];
										writePix[2] = rgbaOut[2];
										writePix[3] = rgbaOut[3];

										writePix += pNewAsset->m_width;

										writePix[0] = rgbaOut[4];
										writePix[1] = rgbaOut[5];
										writePix[2] = rgbaOut[6];
										writePix[3] = rgbaOut[7];

										writePix += pNewAsset->m_width;

										writePix[0] = rgbaOut[8];
										writePix[1] = rgbaOut[9];
										writePix[2] = rgbaOut[10];
										writePix[3] = rgbaOut[11];
										writePix += pNewAsset->m_width;

										writePix[0] = rgbaOut[12];
										writePix[1] = rgbaOut[13];
										writePix[2] = rgbaOut[14];
										writePix[3] = rgbaOut[15];

										writePix -= pNewAsset->m_width * 3; // Rollback at top
										writePix += 4;						// Next block on the line
									}
									pDstStream += 4 * 4 * pNewAsset->m_width; // RGBA * Width * 4 pixel height
								}
							}
						} else {
							klb_assertAlways("COMPRESSED TEXTURE FORMAT %8X NOT SUPPORTED ON THIS PLATFORM",compressType);
						}
					}

					if (compressType != 0) {
						pixelFormat = compressType;
						pNewAsset->m_bitmap				= &stream[0];
					}
				}
			}

			if (pNewAsset->m_type & (1<<4)) {
				opt |= CKLBOGLWrapper::TEX_OPT_MIPMAP_BIT;
			}

			if (pNewAsset->m_type & (1<<5)) {
				opt |= CKLBOGLWrapper::TEX_OPT_DOUBLEBUFFERED_BIT;
			}

			CKLBOGLWrapper& pMgr = CKLBOGLWrapper::getInstance();

			if (pNewAsset->m_bitmap) {
				//
				// Texture creation may fail, but asset is considered as loaded
				//
				MEASURE_THREAD_CPU_BEGIN(TASKTYPE_TEX_LOAD_LOWCONV);
				bool lowRes = (CPFInterface::getInstance().client().getPhysicalScreenHeight() < 480) || m_useQuarterTexture;
				if (lowRes && (compressType == 0)) {
					switch (pixelFormat) {
					case GL_UNSIGNED_SHORT_5_6_5:
						processImage565(
							pNewAsset->m_width * pNewAsset->m_height,
							pNewAsset->m_width,
							pNewAsset->m_height,
							(u8*)pNewAsset->m_bitmap);
						break;
					case GL_UNSIGNED_SHORT_5_5_5_1:
						processImage5551(
							pNewAsset->m_width * pNewAsset->m_height,
							pNewAsset->m_width,
							pNewAsset->m_height,
							(u8*)pNewAsset->m_bitmap);
						break;
					case GL_UNSIGNED_SHORT_4_4_4_4:
						processImage4444(
							pNewAsset->m_width * pNewAsset->m_height,
							pNewAsset->m_width,
							pNewAsset->m_height,
							(u8*)pNewAsset->m_bitmap);
						break;
					case GL_UNSIGNED_BYTE:
						processImage8888(
							pNewAsset->m_width * pNewAsset->m_height,
							pNewAsset->m_width,
							pNewAsset->m_height,
							(u8*)pNewAsset->m_bitmap);
						break;
					}

					pNewAsset->m_width  >>= 1;
					pNewAsset->m_height >>= 1;
					textureSize >>= 2;
				}
				MEASURE_THREAD_CPU_END(TASKTYPE_TEX_LOAD_LOWCONV);

				if (this->m_loadHardware) {
					MEASURE_THREAD_CPU_BEGIN(TASKTYPE_TEX_LOAD_OGL);
					if (CKLBAssetManager::getInstance().isAsyncLoading() == false) {
						pNewAsset->m_bytePerPix	= bytePerPix;
						pNewAsset->m_pTexture	= pMgr.createTexture(pNewAsset->m_width,
																	 pNewAsset->m_height,
																	 pixelFormat,
																	 channelCount,
																	 pNewAsset->m_bitmap,
																	 textureSize,
																	 (CKLBOGLWrapper::TEX_OPTION)opt,0,
																	 (!m_pReloadAsset) ? NULL : pNewAsset->m_pTexture);
						// Sync loading.
					} else {
						// Async loading, but main thread need to perform the openGL call.
						CKLBAssetManager::getInstance().setMainThreadTexture(pNewAsset, pixelFormat, channelCount, opt, textureSize);
					}
					if (pNewAsset->m_pTexture) {
						gTextureAllocHW += pNewAsset->m_width * pNewAsset->m_height * bytePerPix;
					}
					MEASURE_THREAD_CPU_END(TASKTYPE_TEX_LOAD_OGL);
				} else {
					pNewAsset->m_pTexture = NULL;
				}

				//
				// Compute Mip Map for clicking alpha info.
				//
				if (hasClick) {
					#define TILE_WIDTH_BIT		(3)
					#define TILE_WIDTH			(1<<TILE_WIDTH_BIT)

					// 1 Bit bitmap of Width/8, Height/8
					int size		= ((pNewAsset->m_width>>TILE_WIDTH_BIT) * (pNewAsset->m_height>>TILE_WIDTH_BIT)) >> 3;

					u8* clickMap	= m_pReloadAsset ? pNewAsset->m_pTexture->getSWAlphaBuffer() : KLBNEWA(u8, size);
					int bit;
					int shift;
					int byte;
					if (clickMap) {
					memset(clickMap, 0, size);

					u16 fakeNum = 0x00FF;
					u8* tstPtr	= (u8*)&fakeNum;
					int byteVal	= (tstPtr[0] == 0xFF) ? 0 : 1;	// Support for big-endian/little-endian portability.

					switch ((pNewAsset->m_type>>6) & 0x3) {
					case 1:
						// GL_UNSIGNED_SHORT_5_5_5_1;
						bit   = 1;
						shift = 0;
						byte  = byteVal;
						break;
					case 2:
						// GL_UNSIGNED_SHORT_4_4_4_4;
						bit   = 0x08;
						shift = 3;
						byte  = byteVal;
						break;
					case 3:
					default:	// Avoid warning.
						// 8888
						bit   = 0x80;
						shift = 7;
						byte  = 3;
						break;
					}

					// Shift ptr to point to correct alpha byte right away.
					u8* ptr = &(((u8*)pNewAsset->m_bitmap)[byte]);

					// Shift ptr sampling to point at 4, 4
					ptr += (pNewAsset->m_width * bytePerPix * (TILE_WIDTH>>1)) + (bytePerPix * (TILE_WIDTH>>1));

					u8* clickPtr = clickMap;

					int posBit = 0;
					int stepTile  = (bytePerPix * TILE_WIDTH);
					// cheap trick : read pixel 4,4 of each 8x8 tile
					for (int y=0; y < pNewAsset->m_height; y+=TILE_WIDTH) {
						u8* ptrScan		= ptr;
						u8* ptrScanEnd	= ptrScan + (pNewAsset->m_width * bytePerPix);
						u8  val			= 0;
						while (ptrScan < ptrScanEnd) {
							// Read Alpha -> put at bit 0 -> put at correct bit in current byte of target buffer.
							u8 streamBit = ((posBit++)&7);
							val   |= ((*ptrScan & bit)>>shift) << streamBit;
							if (streamBit == 7) {
								*clickPtr++ = val;
							}
							ptrScan		+= stepTile;
						}
						ptr += (pNewAsset->m_width * stepTile);	// Skip 8 lines
					}
					}

					pNewAsset->m_pTexture->assignSWAlphaBuffer(clickMap);
				}

				if (this->m_loadSoftware) {
					pNewAsset->m_softTexture = createSoftTexture(
						pNewAsset->m_width,
						pNewAsset->m_height,
						pixelFormat,
						channelCount,
						pNewAsset->m_bitmap);
					if (pNewAsset->m_softTexture) {
						gTextureAllocSW += pNewAsset->m_width * pNewAsset->m_height * 4;
					}
				} else {
					pNewAsset->m_softTexture = NULL;
				}

				if (pNewAsset->m_pTexture) {
					pNewAsset->m_pTextureUsage = pNewAsset->m_pTexture->createUsage();				
					// pNewAsset->m_pTextureUsage->setSampling(
				} else {
					pNewAsset->m_pTextureUsage = NULL;
				}
			}

			//
			// Stream was compressed ?
			//
			if (pNewAsset->m_type & (1<<3)) {
				// Free Uncompressed source buffer.
				if (pNewAsset->m_bitmap) {
					if (hardCompression == false) {
						KLBDELETEA((u8*)pNewAsset->m_bitmap);
						pNewAsset->m_bitmap = NULL;
					}
				} else {
					// Allocation error, failure.
					KLBDELETE(pNewAsset);
					pNewAsset = NULL;
				}
			}
			return pNewAsset;
		}

		klb_assertNull(0, "Allocation issue");
		KLBDELETE(pNewAsset);
	}
	return NULL;
}

#include "CKLBNode.h"

/*virtual*/
CKLBNode* 
CKLBImageAsset::createSubTree(u32 priorityBase) 
{
	CKLBNode*	pNode	= KLBNEW(CKLBNode);
	CKLBSprite*	pRender	= CKLBRenderingManager::getInstance().allocateCommandSprite(this,priorityBase);
	if (pNode && pRender) {
		pNode->setRender(pRender);
		return pNode;
	}
	if (pNode) { KLBDELETE(pNode); }
	return NULL;
}

#include "CKLBDataHandler.h"

/*static*/ 
CKLBNode* 
CKLBImageAsset::createSprite(	u32 textureHandle,
								const char* imageName,
								CKLBNode* pParentNode,
								u32 renderPriority) 
{
	klb_assert(textureHandle,	"Valid Handle is required");
	klb_assert(pParentNode,		"Requires valid parent node");

	CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();
	CKLBNode* pNode = KLBNEW(CKLBNode);

	if (pNode) {
		klb_assert(pParentNode,		"Requires valid parent node");

		CKLBImageAsset* pImg = ((CKLBTextureAsset*)CKLBDataHandler::getPointer(textureHandle))->getImage(imageName);
		if (pImg) {
			CKLBSprite*	pRender	= pRdrMgr.allocateCommandSprite(pImg);
			if (pRender) {
				pRender->changeOrder(pRdrMgr, renderPriority);
				pNode->setRender(pRender);
				pNode->setRenderOnDestroy(true);
				pParentNode->addNode(pNode, 0);
				pParentNode->markUpMatrix();
				return pNode;
			}
		}
		KLBDELETE(pNode);
	}
	return NULL;
}

// 1. createTexture.
// 2. Register Asset. (Name in dictionnary, slot, etc...)
// 3. Do screenshot feature
CKLBAbstractAsset* 
createTexture(u32 orgWidthI, u32 orgHeightI, const char* name) 
{
	CKLBTextureAsset* pNewAsset = KLBNEW(CKLBTextureAsset);

	if (pNewAsset && name) {
		u32 widthI	= CKLBUtility::nearest2Pow(orgWidthI );
		u32 heightI = CKLBUtility::nearest2Pow(orgHeightI);

		// Name
		// + [pad]
		if (pNewAsset) {
			pNewAsset->setNameDirect(name);

			pNewAsset->m_width				= orgWidthI;
			pNewAsset->m_height				= orgHeightI;
			pNewAsset->m_type				= 3;
			pNewAsset->m_totalVertexCount	= 4;
			pNewAsset->m_totalIndexCount	= 6;
			pNewAsset->m_imageCount			= 1;

			pNewAsset->m_floatBufferTotal	= KLBNEWA(float				, pNewAsset->m_totalVertexCount*4	);  // XYUV
			pNewAsset->m_indexBufferTotal	= KLBNEWA(u16				, pNewAsset->m_totalIndexCount		);
			pNewAsset->m_pImages			= KLBNEWA(CKLBImageAsset*	, pNewAsset->m_imageCount			);

			GLenum pixelFormat;
			CKLBOGLWrapper::TEX_CHANNEL channelCount;
			channelCount					= CKLBOGLWrapper::RGB;
			pixelFormat						= GL_UNSIGNED_BYTE;

			int bytePerPix;
			bytePerPix						= 1 * (channelCount ? channelCount : 1); // Luminance is 1 byte.
			CKLBOGLWrapper& pMgr			= CKLBOGLWrapper::getInstance();
			int textureSize					= widthI * heightI * bytePerPix;

			//
			// Texture creation may fail, but asset is considered as loaded
			//
			pNewAsset->m_bytePerPix			= bytePerPix;
			pNewAsset->m_pTexture			= pMgr.createTexture(	pNewAsset->m_width,
																	pNewAsset->m_height,
																	pixelFormat,
																	channelCount,
																	NULL,
																	textureSize,
																	(CKLBOGLWrapper::TEX_OPTION)0);

			if (pNewAsset->m_pTexture) {
				gTextureAllocHW += textureSize;
			}

			if (pNewAsset->m_floatBufferTotal && pNewAsset->m_indexBufferTotal && pNewAsset->m_pImages && pNewAsset->getName()) {
				CKLBImageAsset* pNewAssetI = KLBNEW(CKLBImageAsset);
				pNewAsset->m_pImages[0] = pNewAssetI;
				if (pNewAssetI) {
					klb_assert(strlen(name) < 250, "Name for screenshot name is too long");

					// + [pad]
					char buff[256];
					sprintf(buff,"%s.imag",name);

					pNewAssetI->setNameDirect(buff);
					pNewAssetI->m_uiSubTileCount		= 1;
					pNewAssetI->m_usageType             |= CKLBImageAsset::IS_STANDARD_RECT;

					pNewAssetI->m_uiVertexCount			= 4;
					pNewAssetI->m_uiIndexCount			= 6;

					pNewAssetI->m_imageSize.m_iRight	= orgWidthI;
					pNewAssetI->m_imageSize.m_iBottom	= orgHeightI;
					pNewAssetI->m_imageSize.m_iLeft		= 0;
					pNewAssetI->m_imageSize.m_iTop		= 0;

					pNewAssetI->m_iCenterX				= 0;
					pNewAssetI->m_iCenterY				= 0;

					pNewAssetI->m_pUVCoord				= pNewAsset->m_floatBufferTotal;
					pNewAssetI->m_pXYCoord				= &pNewAsset->m_floatBufferTotal[8];
					pNewAssetI->m_pIndex				= pNewAsset->m_indexBufferTotal;

					pNewAssetI->m_pTextureAsset			= pNewAsset;

					float orgWidth	= orgWidthI;
					float orgHeight	= orgHeightI;
					/*
					float ratioU	= orgWidth  / widthI;
					float ratioV	= orgHeight / heightI;
					*/
					float startV	= 1.0f;
					float endV		= 0.0f;

					float startU	= 0.0f;
					float endU		= 1.0f;

					pNewAssetI->m_pXYCoord[0]			= 0.0f;
					pNewAssetI->m_pXYCoord[1]			= 0.0f;

					pNewAssetI->m_pXYCoord[2]			= orgWidth;
					pNewAssetI->m_pXYCoord[3]			= 0.0f;

					pNewAssetI->m_pXYCoord[4]			= orgWidth;
					pNewAssetI->m_pXYCoord[5]			= orgHeight;

					pNewAssetI->m_pXYCoord[6]			= 0.0f;
					pNewAssetI->m_pXYCoord[7]			= orgHeight;

					pNewAssetI->m_pUVCoord[0]			= startU;
					pNewAssetI->m_pUVCoord[1]			= startV;

					pNewAssetI->m_pUVCoord[2]			= endU;
					pNewAssetI->m_pUVCoord[3]			= startV;

					pNewAssetI->m_pUVCoord[4]			= endU;
					pNewAssetI->m_pUVCoord[5]			= endV;

					pNewAssetI->m_pUVCoord[6]			= startU;
					pNewAssetI->m_pUVCoord[7]			= endV;


					pNewAssetI->m_pIndex[0]				= 0;
					pNewAssetI->m_pIndex[1]				= 1;
					pNewAssetI->m_pIndex[2]				= 3;

					pNewAssetI->m_pIndex[3]				= 1;
					pNewAssetI->m_pIndex[4]				= 2;
					pNewAssetI->m_pIndex[5]				= 3;

					pNewAssetI->m_boundWidth			= orgWidthI;
					pNewAssetI->m_boundHeight			= orgHeightI;

					pNewAsset->m_pTextureUsage			= pNewAsset->m_pTexture->createUsage();

					return pNewAsset;
				}
			}
		}
		KLBDELETE(pNewAsset);
	}

	klb_assertNull(0, "allocation failure.");
	return NULL;
}

bool 
createScreenAsset(const char* name, u32 orgWidthI, u32 orgHeightI) 
{
	CKLBAbstractAsset* pAsset = createTexture(orgWidthI, orgHeightI, name);
	if (pAsset) {
		CKLBAssetManager::getInstance().registerAsset(pAsset);
		if (pAsset->getAssetID() != NULL_IDX) {
			pAsset->incrementRefCount();
			return true;
		}
		KLBDELETE(pAsset);
	}
	return false;
}

bool 
doScreenShot(const char* name, u32 srcx, u32 srcy, u32 width, u32 height, u32 dstx, u32 dsty) 
{
	CKLBAssetManager& mgr = CKLBAssetManager::getInstance();
	u16 idx = mgr.getAssetIDFromName(name,(char)NULL,1);
	if (idx != NULL_IDX) {
		CKLBTextureAsset* pNewAsset	= (CKLBTextureAsset*)mgr.getAsset(idx);
		u8* buffer					= NULL;
		u32 bufferSize				= width * height * 3;	// RGB888 per pixel
		CKLBOGLWrapper& pMgr		= CKLBOGLWrapper::getInstance();

		buffer = KLBNEWA(u8, bufferSize);
		if (buffer) {
			if (pMgr.copyScreenRGB888(srcx,srcy,width,height,buffer)) {
				if (pNewAsset->m_pTexture->updateTexture(dstx,dsty,width,height,buffer,bufferSize)) {
					KLBDELETEA(buffer);
					return true;
				}
			}
			KLBDELETEA(buffer);
		}
	}
	return false;
}

void 
freeScreenAsset(const char* name) 
{
	CKLBAssetManager& mgr = CKLBAssetManager::getInstance();
	u16 idx = mgr.getAssetIDFromName(name,(char)NULL,1);
	if (idx != NULL_IDX) {
		CKLBTextureAsset* pNewAsset	= (CKLBTextureAsset*)mgr.getAsset(idx);
		pNewAsset->decrementRefCount();
	}
}

/*
 * Here is the implementation of the ETC1 decoder part taken out from the 
 * rg_etc1 library, we took only the decoder part out.
 *
 * The original project code can be found at :
 * http://code.google.com/p/rg-etc1/
 */
//------------------------------------------------------------------------------
//
// rg_etc1 uses the ZLIB license:
// http://opensource.org/licenses/Zlib
//
// Copyright (c) 2012 Rich Geldreich
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
//------------------------------------------------------------------------------

// File: rg_etc1.cpp - Fast, high quality ETC1 block packer/unpacker - Rich Geldreich <richgel99@gmail.com>
// Please see ZLIB license at the end of rg_etc1.h.
//
// For more information Ericsson Texture Compression (ETC/ETC1), see:
// http://www.khronos.org/registry/gles/extensions/OES/OES_compressed_ETC1_RGB8_texture.txt
//
// v1.04 - 5/15/14 - Fix signed vs. unsigned subtraction problem (noticed when compiled with gcc) in pack_etc1_block_init(). 
//         This issue would cause an assert when this func. was called in debug. (Note this module was developed/testing with MSVC, 
//         I still need to test it throughly when compiled with gcc.)
//
// v1.03 - 5/12/13 - Initial public release
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
//#include <stdio.h>
#include <math.h>

#pragma warning (disable: 4201) //  nonstandard extension used : nameless struct/union

#if defined(_DEBUG) || defined(DEBUG)
#define RG_ETC1_BUILD_DEBUG
#endif

#define RG_ETC1_ASSERT assert

namespace rg_etc1
{
   typedef unsigned char uint8;
   typedef unsigned short uint16;
   typedef unsigned int uint;
   typedef unsigned int uint32;
   typedef long long int64;
   typedef unsigned long long uint64;

   const uint32 cUINT32_MAX = 0xFFFFFFFFU;
   const uint64 cUINT64_MAX = 0xFFFFFFFFFFFFFFFFULL; //0xFFFFFFFFFFFFFFFFui64;
   
   template<typename T> inline T minimum(T a, T b) { return (a < b) ? a : b; }
   template<typename T> inline T clamp(T value, T low, T high) { return (value < low) ? low : ((value > high) ? high : value); }

   enum eNoClamp { cNoClamp };

   struct color_quad_u8
   {
      static inline int clamp(int v) { if (v & 0xFFFFFF00U) v = (~(static_cast<int>(v) >> 31)) & 0xFF; return v; }

      struct component_traits { enum { cSigned = false, cFloat = false, cMin = 0U, cMax = 255U }; };

   public:
      typedef unsigned char component_t;
      typedef int parameter_t;

      enum { cNumComps = 4 };

      union
      {
         struct
         {
            component_t r;
            component_t g;
            component_t b;
            component_t a;
         };

         component_t c[cNumComps];

         uint32 m_u32;
      };

      inline color_quad_u8()
      {
      }

      inline color_quad_u8(const color_quad_u8& other) : m_u32(other.m_u32)
      {
      }

      explicit inline color_quad_u8(parameter_t y, parameter_t alpha = component_traits::cMax)
      {
         set(y, alpha);
      }

      inline color_quad_u8(parameter_t red, parameter_t green, parameter_t blue, parameter_t alpha = component_traits::cMax)
      {
         set(red, green, blue, alpha);
      }

      explicit inline color_quad_u8(eNoClamp, parameter_t y, parameter_t alpha = component_traits::cMax)
      {
         set_noclamp_y_alpha(y, alpha);
      }

      inline color_quad_u8(eNoClamp, parameter_t red, parameter_t green, parameter_t blue, parameter_t alpha = component_traits::cMax)
      {
         set_noclamp_rgba(red, green, blue, alpha);
      }

      inline void clear()
      {
         m_u32 = 0;
      }

      inline color_quad_u8& operator= (const color_quad_u8& other)
      {
         m_u32 = other.m_u32;
         return *this;
      }

      inline color_quad_u8& set_rgb(const color_quad_u8& other)
      {
         r = other.r;
         g = other.g;
         b = other.b;
         return *this;
      }

      inline color_quad_u8& operator= (parameter_t y)
      {
         set(y, component_traits::cMax);
         return *this;
      }

      inline color_quad_u8& set(parameter_t y, parameter_t alpha = component_traits::cMax)
      {
         y = clamp(y);
         alpha = clamp(alpha);
         r = static_cast<component_t>(y);
         g = static_cast<component_t>(y);
         b = static_cast<component_t>(y);
         a = static_cast<component_t>(alpha);
         return *this;
      }

      inline color_quad_u8& set_noclamp_y_alpha(parameter_t y, parameter_t alpha = component_traits::cMax)
      {
         RG_ETC1_ASSERT( (y >= component_traits::cMin) && (y <= component_traits::cMax) );
         RG_ETC1_ASSERT( (alpha >= component_traits::cMin) && (alpha <= component_traits::cMax) );

         r = static_cast<component_t>(y);
         g = static_cast<component_t>(y);
         b = static_cast<component_t>(y);
         a = static_cast<component_t>(alpha);
         return *this;
      }

      inline color_quad_u8& set(parameter_t red, parameter_t green, parameter_t blue, parameter_t alpha = component_traits::cMax)
      {
         r = static_cast<component_t>(clamp(red));
         g = static_cast<component_t>(clamp(green));
         b = static_cast<component_t>(clamp(blue));
         a = static_cast<component_t>(clamp(alpha));
         return *this;
      }

      inline color_quad_u8& set_noclamp_rgba(parameter_t red, parameter_t green, parameter_t blue, parameter_t alpha)
      {
         RG_ETC1_ASSERT( (red >= component_traits::cMin) && (red <= component_traits::cMax) );
         RG_ETC1_ASSERT( (green >= component_traits::cMin) && (green <= component_traits::cMax) );
         RG_ETC1_ASSERT( (blue >= component_traits::cMin) && (blue <= component_traits::cMax) );
         RG_ETC1_ASSERT( (alpha >= component_traits::cMin) && (alpha <= component_traits::cMax) );

         r = static_cast<component_t>(red);
         g = static_cast<component_t>(green);
         b = static_cast<component_t>(blue);
         a = static_cast<component_t>(alpha);
         return *this;
      }

      inline color_quad_u8& set_noclamp_rgb(parameter_t red, parameter_t green, parameter_t blue)
      {
         RG_ETC1_ASSERT( (red >= component_traits::cMin) && (red <= component_traits::cMax) );
         RG_ETC1_ASSERT( (green >= component_traits::cMin) && (green <= component_traits::cMax) );
         RG_ETC1_ASSERT( (blue >= component_traits::cMin) && (blue <= component_traits::cMax) );

         r = static_cast<component_t>(red);
         g = static_cast<component_t>(green);
         b = static_cast<component_t>(blue);
         return *this;
      }

      static inline parameter_t get_min_comp() { return component_traits::cMin; }
      static inline parameter_t get_max_comp() { return component_traits::cMax; }
      static inline bool get_comps_are_signed() { return component_traits::cSigned; }

      inline component_t operator[] (uint i) const { RG_ETC1_ASSERT(i < cNumComps); return c[i]; }
      inline component_t& operator[] (uint i) { RG_ETC1_ASSERT(i < cNumComps); return c[i]; }

      inline color_quad_u8& set_component(uint i, parameter_t f)
      {
         RG_ETC1_ASSERT(i < cNumComps);

         c[i] = static_cast<component_t>(clamp(f));

         return *this;
      }

      inline color_quad_u8& clamp(const color_quad_u8& l, const color_quad_u8& h)
      {
         for (uint i = 0; i < cNumComps; i++)
            c[i] = static_cast<component_t>(rg_etc1::clamp<parameter_t>(c[i], l[i], h[i]));
         return *this;
      }

      inline color_quad_u8& clamp(parameter_t l, parameter_t h)
      {
         for (uint i = 0; i < cNumComps; i++)
            c[i] = static_cast<component_t>(rg_etc1::clamp<parameter_t>(c[i], l, h));
         return *this;
      }

   }; // class color_quad_u8

   enum etc_constants
   {
      cETC1BytesPerBlock = 8U,

      cETC1SelectorBits = 2U,
      cETC1SelectorValues = 1U << cETC1SelectorBits,
      cETC1SelectorMask = cETC1SelectorValues - 1U,

      cETC1BlockShift = 2U,
      cETC1BlockSize = 1U << cETC1BlockShift,

      cETC1LSBSelectorIndicesBitOffset = 0,
      cETC1MSBSelectorIndicesBitOffset = 16,

      cETC1FlipBitOffset = 32,
      cETC1DiffBitOffset = 33,

      cETC1IntenModifierNumBits = 3,
      cETC1IntenModifierValues = 1 << cETC1IntenModifierNumBits,
      cETC1RightIntenModifierTableBitOffset = 34,
      cETC1LeftIntenModifierTableBitOffset = 37,

      // Base+Delta encoding (5 bit bases, 3 bit delta)
      cETC1BaseColorCompNumBits = 5,
      cETC1BaseColorCompMax = 1 << cETC1BaseColorCompNumBits,

      cETC1DeltaColorCompNumBits = 3,
      cETC1DeltaColorComp = 1 << cETC1DeltaColorCompNumBits,
      cETC1DeltaColorCompMax = 1 << cETC1DeltaColorCompNumBits,

      cETC1BaseColor5RBitOffset = 59,
      cETC1BaseColor5GBitOffset = 51,
      cETC1BaseColor5BBitOffset = 43,

      cETC1DeltaColor3RBitOffset = 56,
      cETC1DeltaColor3GBitOffset = 48,
      cETC1DeltaColor3BBitOffset = 40,

      cETC1AbsColor4R1BitOffset = 60,
      cETC1AbsColor4G1BitOffset = 52,
      cETC1AbsColor4B1BitOffset = 44,

      cETC1AbsColor4R2BitOffset = 56,
      cETC1AbsColor4G2BitOffset = 48,
      cETC1AbsColor4B2BitOffset = 40,

      // Delta3:
      // 0   1   2   3   4   5   6   7
      // 000 001 010 011 100 101 110 111
      // 0   1   2   3   -4  -3  -2  -1
   };
   
   static uint8 g_quant5_tab[256+16];

   static const int g_etc1_inten_tables[cETC1IntenModifierValues][cETC1SelectorValues] = 
   { 
      { -8,  -2,   2,   8 }, { -17,  -5,  5,  17 }, { -29,  -9,   9,  29 }, {  -42, -13, 13,  42 }, 
      { -60, -18, 18,  60 }, { -80, -24, 24,  80 }, { -106, -33, 33, 106 }, { -183, -47, 47, 183 } 
   };

   static const uint8 g_etc1_to_selector_index[cETC1SelectorValues] = { 2, 3, 1, 0 };
      
   struct etc1_block
   {
      // big endian uint64:
      // bit ofs:  56  48  40  32  24  16   8   0
      // byte ofs: b0, b1, b2, b3, b4, b5, b6, b7 
      union 
      {
         uint64 m_uint64;
         uint8 m_bytes[8];
      };

      uint8 m_low_color[2];
      uint8 m_high_color[2];

      enum { cNumSelectorBytes = 4 };
      uint8 m_selectors[cNumSelectorBytes];

      inline uint get_byte_bits(uint ofs, uint num) const
      {
         RG_ETC1_ASSERT((ofs + num) <= 64U);
         RG_ETC1_ASSERT(num && (num <= 8U));
         RG_ETC1_ASSERT((ofs >> 3) == ((ofs + num - 1) >> 3));
         const uint byte_ofs = 7 - (ofs >> 3);
         const uint byte_bit_ofs = ofs & 7;
         return (m_bytes[byte_ofs] >> byte_bit_ofs) & ((1 << num) - 1);
      }

      // false = left/right subblocks
      // true = upper/lower subblocks
      inline bool get_flip_bit() const 
      {
         return (m_bytes[3] & 1) != 0;
      }   

      inline bool get_diff_bit() const
      {
         return (m_bytes[3] & 2) != 0;
      }

      // Returns intensity modifier table (0-7) used by subblock subblock_id.
      // subblock_id=0 left/top (CW 1), 1=right/bottom (CW 2)
      inline uint get_inten_table(uint subblock_id) const
      {
         RG_ETC1_ASSERT(subblock_id < 2);
         const uint ofs = subblock_id ? 2 : 5;
         return (m_bytes[3] >> ofs) & 7;
      }

      // Returned selector value ranges from 0-3 and is a direct index into g_etc1_inten_tables.
      inline uint get_selector(uint x, uint y) const
      {
         RG_ETC1_ASSERT((x | y) < 4);

         const uint bit_index = x * 4 + y;
         const uint byte_bit_ofs = bit_index & 7;
         const uint8 *p = &m_bytes[7 - (bit_index >> 3)];
         const uint lsb = (p[0] >> byte_bit_ofs) & 1;
         const uint msb = (p[-2] >> byte_bit_ofs) & 1;
         const uint val = lsb | (msb << 1);

         return g_etc1_to_selector_index[val];
      }

      inline uint16 get_base4_color(uint idx) const
      {
         uint r, g, b;
         if (idx)
         {
            r = get_byte_bits(cETC1AbsColor4R2BitOffset, 4);
            g = get_byte_bits(cETC1AbsColor4G2BitOffset, 4);
            b = get_byte_bits(cETC1AbsColor4B2BitOffset, 4);
         }
         else
         {
            r = get_byte_bits(cETC1AbsColor4R1BitOffset, 4);
            g = get_byte_bits(cETC1AbsColor4G1BitOffset, 4);
            b = get_byte_bits(cETC1AbsColor4B1BitOffset, 4);
         }
         return static_cast<uint16>(b | (g << 4U) | (r << 8U));
      }

      inline uint16 get_base5_color() const
      {
         const uint r = get_byte_bits(cETC1BaseColor5RBitOffset, 5);
         const uint g = get_byte_bits(cETC1BaseColor5GBitOffset, 5);
         const uint b = get_byte_bits(cETC1BaseColor5BBitOffset, 5);
         return static_cast<uint16>(b | (g << 5U) | (r << 10U));
      }

      inline uint16 get_delta3_color() const
      {
         const uint r = get_byte_bits(cETC1DeltaColor3RBitOffset, 3);
         const uint g = get_byte_bits(cETC1DeltaColor3GBitOffset, 3);
         const uint b = get_byte_bits(cETC1DeltaColor3BBitOffset, 3);
         return static_cast<uint16>(b | (g << 3U) | (r << 6U));
      }

      static color_quad_u8 unpack_color5(uint16 packed_color5, bool scaled, uint alpha = 255U);
      static void unpack_color5(uint& r, uint& g, uint& b, uint16 packed_color, bool scaled);

      static bool unpack_color5(color_quad_u8& result, uint16 packed_color5, uint16 packed_delta3, bool scaled, uint alpha = 255U);
      static bool unpack_color5(uint& r, uint& g, uint& b, uint16 packed_color5, uint16 packed_delta3, bool scaled, uint alpha = 255U);

      // Results range from -4 to 3 (cETC1ColorDeltaMin to cETC1ColorDeltaMax)
      static void unpack_delta3(int& r, int& g, int& b, uint16 packed_delta3);

      static color_quad_u8 unpack_color4(uint16 packed_color4, bool scaled, uint alpha = 255U);
      static void unpack_color4(uint& r, uint& g, uint& b, uint16 packed_color4, bool scaled);

      // subblock colors
      static void get_diff_subblock_colors(color_quad_u8* pDst, uint16 packed_color5, uint table_idx);
      static bool get_diff_subblock_colors(color_quad_u8* pDst, uint16 packed_color5, uint16 packed_delta3, uint table_idx);
      static void get_abs_subblock_colors(color_quad_u8* pDst, uint16 packed_color4, uint table_idx);

      static inline void unscaled_to_scaled_color(color_quad_u8& dst, const color_quad_u8& src, bool color4)
      {
         if (color4)
         {
            dst.r = src.r | (src.r << 4);
            dst.g = src.g | (src.g << 4);
            dst.b = src.b | (src.b << 4);
         }
         else
         {
            dst.r = (src.r >> 2) | (src.r << 3);
            dst.g = (src.g >> 2) | (src.g << 3);
            dst.b = (src.b >> 2) | (src.b << 3);
         }
         dst.a = src.a;
      }
   };

#undef RG_ETC1_GET_KEY
#undef RG_ETC1_GET_KEY_FROM_INDEX

   color_quad_u8 etc1_block::unpack_color5(uint16 packed_color5, bool scaled, uint alpha)
   {
      uint b = packed_color5 & 31U;
      uint g = (packed_color5 >> 5U) & 31U;
      uint r = (packed_color5 >> 10U) & 31U;

      if (scaled)
      {
         b = (b << 3U) | (b >> 2U);
         g = (g << 3U) | (g >> 2U);
         r = (r << 3U) | (r >> 2U);
      }

      return color_quad_u8(cNoClamp, r, g, b, rg_etc1::minimum(alpha, 255U));
   }

   void etc1_block::unpack_color5(uint& r, uint& g, uint& b, uint16 packed_color5, bool scaled)
   {
      color_quad_u8 c(unpack_color5(packed_color5, scaled, 0));
      r = c.r;
      g = c.g;
      b = c.b;
   }

   bool etc1_block::unpack_color5(color_quad_u8& result, uint16 packed_color5, uint16 packed_delta3, bool scaled, uint alpha)
   {
      int dc_r, dc_g, dc_b;
      unpack_delta3(dc_r, dc_g, dc_b, packed_delta3);
      
      int b = (packed_color5 & 31U) + dc_b;
      int g = ((packed_color5 >> 5U) & 31U) + dc_g;
      int r = ((packed_color5 >> 10U) & 31U) + dc_r;

      bool success = true;
      if (static_cast<uint>(r | g | b) > 31U)
      {
         success = false;
         r = rg_etc1::clamp<int>(r, 0, 31);
         g = rg_etc1::clamp<int>(g, 0, 31);
         b = rg_etc1::clamp<int>(b, 0, 31);
      }

      if (scaled)
      {
         b = (b << 3U) | (b >> 2U);
         g = (g << 3U) | (g >> 2U);
         r = (r << 3U) | (r >> 2U);
      }

      result.set_noclamp_rgba(r, g, b, rg_etc1::minimum(alpha, 255U));
      return success;
   }

   bool etc1_block::unpack_color5(uint& r, uint& g, uint& b, uint16 packed_color5, uint16 packed_delta3, bool scaled, uint alpha)
   {
      color_quad_u8 result;
      const bool success = unpack_color5(result, packed_color5, packed_delta3, scaled, alpha);
      r = result.r;
      g = result.g;
      b = result.b;
      return success;
   }
     
   void etc1_block::unpack_delta3(int& r, int& g, int& b, uint16 packed_delta3)
   {
      r = (packed_delta3 >> 6) & 7;
      g = (packed_delta3 >> 3) & 7;
      b = packed_delta3 & 7;
      if (r >= 4) r -= 8;
      if (g >= 4) g -= 8;
      if (b >= 4) b -= 8;
   }

   color_quad_u8 etc1_block::unpack_color4(uint16 packed_color4, bool scaled, uint alpha)
   {
      uint b = packed_color4 & 15U;
      uint g = (packed_color4 >> 4U) & 15U;
      uint r = (packed_color4 >> 8U) & 15U;

      if (scaled)
      {
         b = (b << 4U) | b;
         g = (g << 4U) | g;
         r = (r << 4U) | r;
      }

      return color_quad_u8(cNoClamp, r, g, b, rg_etc1::minimum(alpha, 255U));
   }
   
   void etc1_block::unpack_color4(uint& r, uint& g, uint& b, uint16 packed_color4, bool scaled)
   {
      color_quad_u8 c(unpack_color4(packed_color4, scaled, 0));
      r = c.r;
      g = c.g;
      b = c.b;
   }

   void etc1_block::get_diff_subblock_colors(color_quad_u8* pDst, uint16 packed_color5, uint table_idx)
   {
      RG_ETC1_ASSERT(table_idx < cETC1IntenModifierValues);
      const int *pInten_modifer_table = &g_etc1_inten_tables[table_idx][0];

      uint r, g, b;
      unpack_color5(r, g, b, packed_color5, true);

      const int ir = static_cast<int>(r), ig = static_cast<int>(g), ib = static_cast<int>(b);

      const int y0 = pInten_modifer_table[0];
      pDst[0].set(ir + y0, ig + y0, ib + y0);

      const int y1 = pInten_modifer_table[1];
      pDst[1].set(ir + y1, ig + y1, ib + y1);

      const int y2 = pInten_modifer_table[2];
      pDst[2].set(ir + y2, ig + y2, ib + y2);

      const int y3 = pInten_modifer_table[3];
      pDst[3].set(ir + y3, ig + y3, ib + y3);
   }
   
   bool etc1_block::get_diff_subblock_colors(color_quad_u8* pDst, uint16 packed_color5, uint16 packed_delta3, uint table_idx)
   {
      RG_ETC1_ASSERT(table_idx < cETC1IntenModifierValues);
      const int *pInten_modifer_table = &g_etc1_inten_tables[table_idx][0];

      uint r, g, b;
      bool success = unpack_color5(r, g, b, packed_color5, packed_delta3, true);

      const int ir = static_cast<int>(r), ig = static_cast<int>(g), ib = static_cast<int>(b);

      const int y0 = pInten_modifer_table[0];
      pDst[0].set(ir + y0, ig + y0, ib + y0);

      const int y1 = pInten_modifer_table[1];
      pDst[1].set(ir + y1, ig + y1, ib + y1);

      const int y2 = pInten_modifer_table[2];
      pDst[2].set(ir + y2, ig + y2, ib + y2);

      const int y3 = pInten_modifer_table[3];
      pDst[3].set(ir + y3, ig + y3, ib + y3);

      return success;
   }
   
   void etc1_block::get_abs_subblock_colors(color_quad_u8* pDst, uint16 packed_color4, uint table_idx)
   {
      RG_ETC1_ASSERT(table_idx < cETC1IntenModifierValues);
      const int *pInten_modifer_table = &g_etc1_inten_tables[table_idx][0];

      uint r, g, b;
      unpack_color4(r, g, b, packed_color4, true);
      
      const int ir = static_cast<int>(r), ig = static_cast<int>(g), ib = static_cast<int>(b);

      const int y0 = pInten_modifer_table[0];
      pDst[0].set(ir + y0, ig + y0, ib + y0);
      
      const int y1 = pInten_modifer_table[1];
      pDst[1].set(ir + y1, ig + y1, ib + y1);

      const int y2 = pInten_modifer_table[2];
      pDst[2].set(ir + y2, ig + y2, ib + y2);

      const int y3 = pInten_modifer_table[3];
      pDst[3].set(ir + y3, ig + y3, ib + y3);
   }
      
   bool unpack_etc1_block(const void* pETC1_block, unsigned int* pDst_pixels_rgba, bool preserve_alpha)
   {
      color_quad_u8* pDst = reinterpret_cast<color_quad_u8*>(pDst_pixels_rgba);
      const etc1_block& block = *static_cast<const etc1_block*>(pETC1_block);

      const bool diff_flag = block.get_diff_bit();
      const bool flip_flag = block.get_flip_bit();
      const uint table_index0 = block.get_inten_table(0);
      const uint table_index1 = block.get_inten_table(1);

      color_quad_u8 subblock_colors0[4];
      color_quad_u8 subblock_colors1[4];
      bool success = true;

      if (diff_flag)
      {
         const uint16 base_color5 = block.get_base5_color();
         const uint16 delta_color3 = block.get_delta3_color();
         etc1_block::get_diff_subblock_colors(subblock_colors0, base_color5, table_index0);
            
         if (!etc1_block::get_diff_subblock_colors(subblock_colors1, base_color5, delta_color3, table_index1))
            success = false;
      }
      else
      {
         const uint16 base_color4_0 = block.get_base4_color(0);
         etc1_block::get_abs_subblock_colors(subblock_colors0, base_color4_0, table_index0);

         const uint16 base_color4_1 = block.get_base4_color(1);
         etc1_block::get_abs_subblock_colors(subblock_colors1, base_color4_1, table_index1);
      }

      if (preserve_alpha)
      {
         if (flip_flag)
         {
            for (uint y = 0; y < 2; y++)
            {
               pDst[0].set_rgb(subblock_colors0[block.get_selector(0, y)]);
               pDst[1].set_rgb(subblock_colors0[block.get_selector(1, y)]);
               pDst[2].set_rgb(subblock_colors0[block.get_selector(2, y)]);
               pDst[3].set_rgb(subblock_colors0[block.get_selector(3, y)]);
               pDst += 4;
            }

            for (uint y = 2; y < 4; y++)
            {
               pDst[0].set_rgb(subblock_colors1[block.get_selector(0, y)]);
               pDst[1].set_rgb(subblock_colors1[block.get_selector(1, y)]);
               pDst[2].set_rgb(subblock_colors1[block.get_selector(2, y)]);
               pDst[3].set_rgb(subblock_colors1[block.get_selector(3, y)]);
               pDst += 4;
            }
         }
         else
         {
            for (uint y = 0; y < 4; y++)
            {
               pDst[0].set_rgb(subblock_colors0[block.get_selector(0, y)]);
               pDst[1].set_rgb(subblock_colors0[block.get_selector(1, y)]);
               pDst[2].set_rgb(subblock_colors1[block.get_selector(2, y)]);
               pDst[3].set_rgb(subblock_colors1[block.get_selector(3, y)]);
               pDst += 4;
            }
         }
      }
      else 
      {
         if (flip_flag)
         {
            // 0000
            // 0000
            // 1111
            // 1111
            for (uint y = 0; y < 2; y++)
            {
               pDst[0] = subblock_colors0[block.get_selector(0, y)];
               pDst[1] = subblock_colors0[block.get_selector(1, y)];
               pDst[2] = subblock_colors0[block.get_selector(2, y)];
               pDst[3] = subblock_colors0[block.get_selector(3, y)];
               pDst += 4;
            }

            for (uint y = 2; y < 4; y++)
            {
               pDst[0] = subblock_colors1[block.get_selector(0, y)];
               pDst[1] = subblock_colors1[block.get_selector(1, y)];
               pDst[2] = subblock_colors1[block.get_selector(2, y)];
               pDst[3] = subblock_colors1[block.get_selector(3, y)];
               pDst += 4;
            }
         }
         else
         {
            // 0011
            // 0011
            // 0011
            // 0011
            for (uint y = 0; y < 4; y++)
            {
               pDst[0] = subblock_colors0[block.get_selector(0, y)];
               pDst[1] = subblock_colors0[block.get_selector(1, y)];
               pDst[2] = subblock_colors1[block.get_selector(2, y)];
               pDst[3] = subblock_colors1[block.get_selector(3, y)];
               pDst += 4;
            }
         }
      }
      
      return success;
   }
         
} // namespace rg_etc1
