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
#ifndef CKLBUIVariableItem_h
#define CKLBUIVariableItem_h

#include "CKLBUITask.h"

/*!
* \class CKLBUIVariableItem
* \brief Variable Item Task Class
* 
* CKLBUIVariableItem is nearly similar to CKLBUISimpleItem.
* However, it is possible to modify the UV on the texture 
* or to change the asset associated to an instance of CKLBUIVariableItem.
* It also support multitexturing using the second texture as a mask (multiply)
*/
class CKLBUIVariableItem : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIVariableItem>;
private:
	CKLBUIVariableItem();
	virtual ~CKLBUIVariableItem();

public:
	virtual u32 getClassID();

	static CKLBUIVariableItem * create(CKLBUITask * pParent, CKLBNode * pNode,
									   u32 order, float x, float y, float width, float height,
									   const char * asset);

	bool init(CKLBUITask * pParent, CKLBNode * pNode,
			  u32 order, float x, float y, float width, float height, const char * asset);
	bool initUI  (CLuaState& lua);
	int commandUI(CLuaState& lua, int argc, int cmd);

	void execute(u32 deltaT);
	void dieUI  ();

	inline u32  getOrder() { return m_order; }
	inline void setOrder(u32 order) { 
		if(m_order != order) {
			m_order = order;
			m_pDynSprite->changeOrder(CKLBRenderingManager::getInstance(), m_order);
		}
	}

	inline const char* getAsset() { return m_asset; }

	inline float getWidth() { return m_width; }
	inline void  setWidth(float width) {
		if(m_width != width) {
			m_width = width;
			REFRESH_A;
		}
	}

	inline float getHeight() { return m_height; }
	inline void  setHeight(float height) {
		if(m_height != height) {
			m_height = height; 
			REFRESH_A;
		}
	}

	void changeUV(float x, float y, float width, float height);

	inline bool changeAsset(const char* asset) {
		bool bResult = setAsset(asset);
		m_pNode->markUpMatrix();
		return bResult;
	}

	bool setMaskAsset(const char* asset);

private:
	bool initCore(u32 order, float x, float y, float width, float height, const char * asset);

	void createArrVert(float width, float height);
	
	void getUV      (CKLBImageAsset * pTex);		// テクスチャからUV値を取り込んでおく
	void getSize    (CKLBImageAsset * pTex);	    // テクスチャからオリジナルサイズを取得する。
	bool setAsset   (const char * asset);
private:
	CKLBImageAsset	*	m_pTex;
	u32					m_handle;
	CKLBImageAsset	*	m_pMaskTex;
	u32					m_Maskhandle;

	const char		*	m_asset;

	CKLBDynSprite	*	m_pDynSprite;
	CKLBNode		*	m_pNode;

	float				m_width;
	float				m_height;

	float				m_arrUV_intern[8];
	float				m_arrOriginalUV_intern[8];
	float				m_arrVert_intern[8];

	// 元画像のサイズ
	float				m_org_width;
	float				m_org_height;

	u32					m_order;
	u32					m_vCount;

	static PROP_V2		ms_propItems[];

	// プロパティのインデックス
};


#endif // CKLBUIVariableItem_h
