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
#ifndef __TEXTURE_MGT__
#define __TEXTURE_MGT__

#include "CKLBAsset.h"

class KLBTextureAssetPlugin;

class CTexture;
class CTextureUsage;
class CKLBImageAsset;

/*!
* \class CKLBTextureAsset
* \brief Texture Asset Class
* 
* Texture asset is a texture that describes a 2D texture uploaded to the GPU.
* Inside a texture asset file, we also store a list of 2D models.
* A 2D model is a list vertices and related indexes for rendering triangles. 
*/
class CKLBTextureAsset : public CKLBAbstractAsset {
	friend class KLBTextureAssetPlugin;
public:

	CKLBTextureAsset();
	~CKLBTextureAsset();

	virtual	ASSET_TYPE	getAssetType()	{ return ASSET_TEXTURE;		}
	virtual u32			getClassID	()	{ return CLS_ASSETTEXTURE;  }

	/* NO DICO
	virtual bool	include				(const char* name);*/
	virtual void unloadRessource();

	virtual void onRegisterSubAsset		();
	virtual void onUnregisterSubAsset	();

	CKLBImageAsset*		getImage		(const char* fileName);

	u16					m_width;
	u16					m_height;
	u16					m_type;
	u32					m_totalVertexCount;
	u32					m_totalIndexCount;
	u16					m_imageCount;
	void*				m_bitmap;
	u16*				m_indexBufferTotal;
	float*				m_floatBufferTotal;
	CTexture*			m_pTexture;
	CTextureUsage*		m_pTextureUsage;
	CKLBImageAsset**	m_pImages;
	u8*					m_softTexture;
	u8					m_bytePerPix;
};

struct SKLBRect {
public:
	s16	m_iLeft;
	s16 m_iRight;
	s16 m_iTop;
	s16 m_iBottom;

	inline
	s32 getWidth() {	return m_iRight - m_iLeft; }

	inline
	s32 getHeight() {	return m_iBottom - m_iTop; }
};

/*!
* \class CKLBImageAsset
* \brief Image Asset Class
* 
* CKLBImageAsset is a basic asset for image rendering.
* It uses a CKLBTextureAsset.
* There are also various attributes that are stored within an image asset.
*/
class CKLBImageAsset : public CKLBAsset {
	friend class KLBTextureAssetPlugin;
public:
	static const u8		IS_STANDARD_RECT	= 0x1;
	static const u8		IS_SCALE9			= 0x2;
	static const u8		IS_SCROLLBARTYPE	= 0x4;
	static const u8		IS_3DMODEL			= 0x8;

	static CKLBNode*	createSprite	(	u32 textureHandle,
											const char* imageName,
											CKLBNode* pParentNode,
											u32 renderPriority);

	CKLBImageAsset();
	~CKLBImageAsset();

	virtual CKLBNode*	createSubTree	(u32 priorityBase = 0);
	virtual u32			getClassID		()		{ return CLS_ASSETIMAGE;	}
	virtual	ASSET_TYPE	getAssetType	()		{ return ASSET_IMAGE;		}

	inline
	u32					getVertexCount	()		{ return m_uiVertexCount;	}

	inline
	u32					getIndexCount	()		{ return m_uiIndexCount;	}

	CKLBTextureAsset*	getTexture		()		{ return m_pTextureAsset;	}	

	inline
	SKLBRect*			getSize			()		{ return &m_imageSize;		}

	void				setSubImage		(u32 width, u32 height, u32 offX, u32 offY);
	CKLBImageAsset*		findSub			(u32 index);

	void				addSubImage		(CKLBImageAsset* pImage);

	/** Warning : the asset pointer is not managed and becomes the responsability of the owner. */
	CKLBImageAsset*		getSubImage		(u32 index, CKLBImageAsset* replaceAsset = NULL);

	void				getCenter		(s32& cx, s32& cy);
	CKLBImageAsset*		getAsTopLeftImage(s32 offX, s32 offY);

	inline
	u16*				getIndexBuffer	()	{ return m_pIndex;		}

	inline
	float*				getUVBuffer		()	{ return m_pUVCoord;	}

	inline
	float*				getXYBuffer		()	{ return m_pXYCoord;	}

	void				getXY(u32 vertexIndex, float* pX, float* pY);
	void				getUV(u32 vertexIndex, float* pU, float* pV);

	bool				getAttribute(u8 attribID, s32& attribValue);
	bool				getAttribute(u8 attribID, float& attribValue);
	bool				getAttribute(u8 attribID, const char*& attribValue);

	inline u8			hasStandardAttribute(u8 mask)	{ return m_usageType & mask; }
public:
	ASSET_ATTRIB*		m_attribList;

	u16*				m_pIndex;
	float*				m_pUVCoord;
	float*				m_pXYCoord;

	CKLBTextureAsset*	m_pTextureAsset;

	CKLBImageAsset*		m_subTiles;
	CKLBImageAsset*		m_nextSubTile;

	SKLBRect			m_imageSize;	// Original image size
	float				m_boundWidth;
	float				m_boundHeight;
	s32					m_renderOffset;

	s16					m_subIndex;

	s16					m_iCenterX;
	s16					m_iCenterY;

	u16					m_uiVertexCount;
	u16					m_uiIndexCount;


	u16					m_attribMask;
	u16					m_attribCount;
	u16					m_tileWidth;
	u16					m_tileHeight;
	u16					m_tileOffX;
	u16					m_tileOffY;
	u16					m_tileCount;
	u16					m_uiSubTileCount;
	u8					m_usageType;
	bool				m_bAllocatedOutsideTexture;
private:
	CKLBImageAsset*		m_topLeftImage;
};

enum E_TEXTURELOADINGMODE {
	TEX_LOAD_GPU,
	TEX_LOAD_CPU,
	TEX_LOAD_GPUCPU
};

/*!
* \class KLBTextureAssetPlugin
* \brief Texture Asset Plugin Class
* 
* Plugin responsible for loading texture and images inside texture.
* See CKLBTextureAsset and CKLBImageAsset.
*/
class KLBTextureAssetPlugin : public IKLBAssetPlugin {
public:
	KLBTextureAssetPlugin();
	~KLBTextureAssetPlugin();

	void	setLoadingMode(E_TEXTURELOADINGMODE mode);
	u8*		createSoftTexture	(	s32 width, 
									s32 height, 
									u32 pixelFormat, 
									u8 channelCount, 
									void* data );

	virtual u32					getChunkID		()			{ return CHUNK_TAG('T','E','X','B'); }
	virtual	u8					charHeader		()			{ return 'T';			}
	virtual const char*			fileExtension	()			{ return ".texb"; }

	virtual CKLBAbstractAsset*	loadAsset(u8* stream, u32 streamSize);
	virtual void				setCurrentFileName(const char* currentFileName) {
		m_currentFile = currentFileName;
	}

	void				setBuffers		(CKLBTextureAsset*	pTextureAsset, float* uvBuffer, float* xyBuffer, u16* indexBuffer);
	CKLBImageAsset*		loadImage		(u8* stream, u32 streamSize, CKLBImageAsset* pReload);
	void				setQuarterTexture(bool activate) {
		m_useQuarterTexture = activate;
	}
private:
	float*				m_pUVBuffer;
	float*				m_pXYBuffer;
	float*				m_pLastLoadedUV;
	u16*				m_pLastLoadedIndex;
	u16*				m_pIndexBuffer;
	CKLBTextureAsset*	m_pTextureAsset;
	const char*			m_currentFile;
	bool				m_loadHardware;
	bool				m_loadSoftware;
	bool				m_useQuarterTexture;
};

bool createScreenAsset	(const char* name, u32 orgWidthI, u32 orgHeightI);
bool doScreenShot		(const char* name, u32 srcx, u32 srcy, u32 width, u32 height, u32 dstx, u32 dsty);
void freeScreenAsset	(const char* name);

#endif
