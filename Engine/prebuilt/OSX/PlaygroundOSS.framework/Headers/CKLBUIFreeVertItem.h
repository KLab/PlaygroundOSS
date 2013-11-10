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
#ifndef CKLBUIFreeVertItem_h
#define CKLBUIFreeVertItem_h

#include "CKLBUITask.h"
#include "CKLBDrawTask.h"

/*!
* \class CKLBUIFreeVertItem
* \brief Free Vertex Item Task Class
* 
* CKLBUIFreeVertItem can display image like CKLBUISimpleItem.
* However, it is possible to modify the UV, Colors and coordinate for each vertex.
* It is usefull also to just display a filled area with a given RGBA color, or gradient display 
* without texture at all.
*/
class CKLBUIFreeVertItem : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIFreeVertItem>;
private:
	CKLBUIFreeVertItem();
	virtual ~CKLBUIFreeVertItem();

	bool init(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, const char* asset, float* vertices);
	bool initCore(u32 order, float x, float y, const char* asset, float* vertices);
public:
	u32 getClassID();
	static CKLBUIFreeVertItem* create(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, const char* asset, float* vertices);

	bool initUI  (CLuaState& lua);
	int commandUI(CLuaState& lua, int argc, int cmd);

	void execute(u32 deltaT);
	void dieUI  ();

	inline virtual u32 getOrder() {	return m_order; }

	inline virtual void setOrder(u32 order) {
		if (m_order != order) {
			getNode()->setPriority(order);
			m_order = order;
		}
	}

	inline const char* getAsset() { return m_asset; }

	inline void setVertCol(int idx, u32 argb) {
		m_arrColor[idx] = argb;
		assignVertColors();
	}

	void setVertColors	(u32* colors);
	void setVertUV		(float* uv);
	void setVertXY		(float* coord);

private:
	u32         m_order;
	const char* m_asset;

	bool setVertColors  (CLuaState& lua);
	bool setVertices    (CLuaState& lua, float* tmpDest = NULL);	// Lua配列から頂点座標値を取り込んでおく
	void setUV          (CKLBImageAsset * pTex);	                // テクスチャからUV値を取り込んでおく
	bool setArrUV       (CLuaState& lua);		                    // Lua配列からUV値を取り込んでおく

	void setVertColors  ();
	void setVertices    ();     // 頂点座標値配列から、座標値を設定する
	void setUV          ();	    // UV値配列から、UV値を設定する。

private:
	inline void assignVertColors() {
		for(int i = 0; i < 4; i++) {
			u32 col;
			u32 color = m_arrColor[i];
			u8* pCol = (u8*)&col;
			// Memory order cast to 'col'
			pCol[0] = color >> 16;	// R
			pCol[1] = color >> 8;	// G
			pCol[2] = color;		// B
			pCol[3] = color >> 24;  // A

			m_pDynSprite->setVertexColor(getNode(),i, col);
		}
	}

	inline void assignVertices() {
		// 4頂点分の座標値が頂点配列に格納されているので、
		// それをDynSpriteに設定する。

		//
		// Patch coordinate to fit screen if we are in bordeless mode.
		//
		int w = CKLBDrawResource::getInstance().width ();
		int h = CKLBDrawResource::getInstance().height();

		if (
			(((int)m_arrVert[0]) == 0) &&
			(((int)m_arrVert[1]) == 0) &&
			(((int)m_arrVert[2]) == w) &&
			(((int)m_arrVert[3]) == 0) &&
			(((int)m_arrVert[4]) == w) &&
			(((int)m_arrVert[5]) == h) &&
			(((int)m_arrVert[6]) == 0) &&
			(((int)m_arrVert[7]) == h)
		   )
		{
			float oxf = CKLBDrawResource::getInstance().ox();
			float oyf = CKLBDrawResource::getInstance().oy();
			m_arrVert[0] -= oxf;
			m_arrVert[1] -= oyf;
			m_arrVert[2] += oxf;
			m_arrVert[3] -= oyf;
			m_arrVert[4] += oxf;
			m_arrVert[5] += oyf;
			m_arrVert[6] -= oxf;
			m_arrVert[7] += oyf;
		}

		for(int i = 0; i < 4; i++) {
			m_pDynSprite->setVertexXY(i, m_arrVert[i*2], m_arrVert[(i*2) + 1]);
		}
	}

	inline void assignUV()
	{
		// 4頂点分の座標値が頂点配列に格納されているので、
		// それをDynSpriteに設定する。
		for(int i = 0; i < 4; i++) {
			m_pDynSprite->setVertexUV(i, m_arrUV[i*2], m_arrUV[(i*2) + 1]);
		}
		getNode()->markUpMatrix();
	}


	CKLBImageAsset	*	m_pTex;

	CKLBDynSprite	*	m_pDynSprite;

	u32					m_handle;

	float				m_arrVert[8];
	float				m_arrUV[8];
	float				m_arrOriginalUV[8];
	u32					m_arrColor[4];

	static PROP_V2		ms_propItems[];
	static const u16	ms_indices[];

	// プロパティのインデックス
};

#endif // CKLBUIFormVertItem_h
