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
#ifndef __CKLB_CANVAS_SPRITE__
#define __CKLB_CANVAS_SPRITE__

#include "CKLBRendering.h"

class CKLBCanvasSprite : public CKLBSprite {
public:
	CKLBCanvasSprite();
	~CKLBCanvasSprite();

	bool setupCanvas	(u32 vertexCount, u32 indexCount);
	void setupTexture	(CKLBTextureAsset* pTexture);

	inline
	bool isFreeze		()	{ return m_freeze; }
	void freeze			(bool freeze);
	bool clear			();
	bool drawImage		(float x, float y, CKLBImageAsset* pImage, u32 color);
	bool drawScale		(float x, float y, float scale, CKLBImageAsset* pImage, u32 color);
	bool drawImageClip	(float x, float y, CKLBImageAsset* pImage, float percW, float percH, u32 color);
	bool fillRect		(float x, float y, float w, float h, u32 color);

	void startDynamicSection	(u32 section);
	void endDynamicSection		(u32 section);
	void dynamicSectionTranslate(u32 section, float x, float y);
	void dynamicSectionColor	(u32 section, u32 color);

	void setFillUV				(float u, float v);
protected:
	#define MAX_SECTION		(10)
	struct SECTION {
		u16		lengthFloat;
		u16		start;
		bool	started;
	};

	SECTION	m_dynSection[10];
	void doUVAndColor	(CKLBImageAsset* pImage, u32 color, u16 vCount, u16 iCount);

	CKLBImageAsset _internalImg;
	u32*	m_pLocalColors;

	float	m_fillU;
	float	m_fillV;
	u32*	m_pFillColors;
	float*	m_pFillVertex;
	float*	m_pFillUV;
	u16*	m_pFillIndex;
	bool	m_freeze;
};

#endif // __CKLB_CANVAS_SPRITE__
