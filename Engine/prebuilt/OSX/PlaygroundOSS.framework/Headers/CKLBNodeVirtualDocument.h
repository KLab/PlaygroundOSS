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
#ifndef __CKLBVIRTUALDOCUMENTNODE__
#define __CKLBVIRTUALDOCUMENTNODE__

#include "CKLBNode.h"
#include "string.h"

enum ECOMMAND {
	DRAWLINE,
	DRAWRECT,
	FILLRECT,
	FILLRECTFORCE,
	DRAWIMAGE,
	DRAWIMAGETILED,
	DRAWTEXT,
};

struct SDrawCommand {
	// SDrawCommand*	next; /* Not used for now */
	// Can add other pointer later on to more optimized data structure.
	void*			ptr;	// Image or string buffer
	void*			txt;	// text to display inside string buffer
	s16				y0;
	s16 			x0;
	s16 			y1;
	s16 			x1;
	s16				sdx;
	s16				sdy;
	s16				sx0;
	s16				sy0;
	u32				color;
	ECOMMAND		command;
	u8				fntIdx;
	bool			swap;
};

struct RenderContext {
	u32* pBuffer;
	s32  stride;
	s32	clipX0;
	s32	clipY0;
	s32 clipX1;
	s32 clipY1;
	s32 offsetX;
	s32 offsetY;
	s32 targetWidth;
	s32 targetHeight;
	u8	format;

	void translate	(s32 offsetX, s32 offsetY) {
		this->offsetX = offsetX;
		this->offsetY = offsetY;
	}

	void setClip	(s32 x0, s32 y0, s32 x1, s32 y1);				//Only command in buffer space (no translate)
	void drawLine	(s32 x0, s32 y0, s32 x1, s32 y1, u32 color);
	void drawRect	(s32 x0, s32 y0, s32 x1, s32 y1, u32 color);
	void fillRect	(s32 x0, s32 y0, s32 x1, s32 y1, u32 color, bool forceFill);
	void drawText	(s32 x , s32 y , char* string  , u32 color, void* font, bool docMode);
	void drawImage	(s32 x , s32 y , SDrawCommand* img  , u8  alpha);
private:
	void setPixelClip		(s32 x1, s32 y1, u32 color);
	void setPixelClip4444	(s32 x1, s32 y1, u16 color);
};

// Just for FORMAT_8 / FORMAT_8888 constant.
#include "CKLBTexturePacker.h"

/*!
* \class CKLBNodeVirtualDocument
* \brief Virtual Doument Specilized Node Class
* 
* CKLBNodeVirtualDocumentis in charge of the graphic operations
* on a Virtual Document.
*/
class CKLBNodeVirtualDocument : public CKLBNode {
public:
	/*
	static const int	VDFORMAT_8			= FORMAT_8;		// Not supported yet.
	static const int	VDFORMAT_8888		= FORMAT_8888;
	static const int	VDFORMAT_4444		= FORMAT_4444;
	*/

	CKLBNodeVirtualDocument();
	~CKLBNodeVirtualDocument();

	u32 getClassID() { return CLS_KLBNODEVIRTUALDOC; }

	void	setFont			(u8 index, const char* fontName, u16 fontSize);
	void	setDocumentSize	(u32 width, u32 height, bool scrollVertical = true);
	bool	setViewPortSize	(u32 width, u32 height, float alignOffsetX, float alignOffsetY, u32 priority, bool doScroll);
	void	setViewPortPos	(s32 x,     s32 y);
	bool	createDocument	(u16 maxCommandCount, u8 format);
	void	freeDocument	();
	void	freeFont		();

	void	lockDocument	();
	void	unlockDocument	();
	void	emptyDocument	();

	void	clear			(u32 fillColor);
	void	drawLine		(s16 x0, s16 y0, s16 x1,    s16 y1,     u32 color);
	void	drawRect		(s16 x0, s16 y0, u16 width, u16 height, u32 color);
	void	fillRect		(s16 x0, s16 y0, u16 width, u16 height, u32 color, bool fill = false);
	void	drawImage		(s16 x0, s16 y0, CKLBImageAsset* img, u8 alpha);
	void	drawTileImage	(s16 x0, s16 y0, u16 width, u16 height, CKLBImageAsset* img, u8 alpha);
	void	drawText		(s16 x0, s16 y0, const char* string, u32 color, u8 fontIndex,
							 u8 align_mode = 0, s16 align_width = 0	// addhook parameters.
							 );

	s32		getViewPortPosX	()	{ return m_posX; }
	s32		getViewPortPosY	()	{ return m_posY; }

	void	check();

	void	setPriority(u32 renderPriority);

	void	forceRefresh	();
protected:
	static
	void	docTextureCompaction(void* ctx, u16 oldsurface, u16 newSurface);

	void	clearRessources	(bool freeSurface, bool freeFonts);
	void	renderDocument	();
	void	setVertex		(CKLBDynSprite* pSpr, u32 idx4, float x0, float y0, float u, float v);
	void	setTargetSurface(u8 index, s32 offsetX, s32 offsetY);
	void	updateDynSprites(u8 index);


	float			m_alignOffsetX;
	float			m_alignOffsetY;
	s32				m_posX;
	s32				m_posY;
	SDrawCommand*	m_commandArray;
	u16				m_commandMaxCount;
	u16				m_CurrentCommand;

	struct VDOCDRAW {
		CKLBDynSprite	*	tile;				// 描画用スプライト
		float				upV;
		float				bottomV;
		float				leftU;
		float				rightU;

		float				stepU;
		float				stepV;
		u32				*	softwareBufTile;	// 対応するソフトウェアバッファ
		u16					surf_handle;		// 対応するsurfaceのハンドル
		u8					format;
	};

	VDOCDRAW		m_drawarea[2];

	/*
	// m_drawarea[] は、以前のバージョンにおける下記メンバを置き換えるものとなる。

	u16				m_surfA;
	u16				m_surfB;
	u32*			m_softwareBufferTile[2];	// ViewPort x 2
	CKLBDynSprite*	m_tile		[2];
	float			upV			[2];
	float			bottomV		[2];
	float			leftU		[2];
	float			rightU		[2];
	// u32			m_textureX	[2];
	// u32			m_textureY	[2];

	// 2 tiles inside SAME texture : u v step are the same.
	float			stepU		[2];
	float			stepV		[2];
	*/
	bool			m_isVertical;
	bool			m_bScroll;

	CTexture*		m_texture;
	
	u32				m_bgColor;

	STextInfo		fontInfo	[5];
	void*			font		[5];

	// 2 tiles inside SAME texture : u v step are the same.

	u32				m_viewPortHeight;
	u32				m_viewPortWidth;
	s16				m_currTile;
	s16				m_prevTile;
	s16				m_scroll;
	s16				m_prevScroll;
	u8				m_currBuff;
	u8				m_up;
	u8				m_format;
	bool			m_bDisplay;

	bool			m_bHasChanged;

	s32				m_tileXStart;
	s32				m_tileYStart;
	s32				m_tileXEnd;
	s32				m_tileYEnd;
	s32				m_documentWidth;
	s32				m_documentHeight;

	RenderContext	renderContext;
};

#endif
