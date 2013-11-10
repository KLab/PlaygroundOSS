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
#ifndef CKLBUIMultiImgItem_h
#define CKLBUIMultiImgItem_h

#include "CKLBUITask.h"

struct IMGITEM {
	u32				handle;
	CKLBSprite*		sprite;
};

/*!
* \class CKLBUIMultiImgItem
* \brief Multi Images Item Task Class
* 
* CKLBUIMultiImgItem is used to regroup some images into one Task.
* One image only is displayed every frame, but the active image can be changed
* at any moment through provided APIs.
*/
class CKLBUIMultiImgItem : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIMultiImgItem>;
private:
	CKLBUIMultiImgItem();
	virtual ~CKLBUIMultiImgItem();

	bool init(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, u32 idx, const char** pArrayAsset, u32* pArrayIndexes, u32 assetCount);
	bool initCore(u32 order,float x,float y, u32 index, IMGITEM* pIndexes, u32 max);
public:
	u32 getClassID();
	static CKLBUIMultiImgItem* create(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, u32 idx, const char** pArrayAsset, u32* pArrayIndexes, u32 assetCount);
	bool initUI  (CLuaState& lua);
	int commandUI(CLuaState& lua, int argc, int cmd);

	void execute(u32 deltaT);
	void dieUI  ();

	inline u32  getIndexMax() { return m_idxMax; }
	inline void setIndexMax(u32 index) {
		if (index != m_idxMax) {
			m_idxMax = index;
			if(m_idxImg > m_idxMax) {
				m_idxImg = m_idxMax;
			}
			REFRESH_B;
		}
	}

	inline virtual u32 getOrder() { return m_order; }
	inline virtual void setOrder(u32 order) {
		if(order != m_order) {
			m_order = order;
			REFRESH_B;
		}
	}

	inline u32  getIndex() { return m_idxImg; }
	inline void setIndex(u32 index) {
		if(index != m_idxImg) {
			m_idxImg = (index <= m_idxMax) ? index : m_idxMax;
			REFRESH_B;
		}
	}

	bool changeAssets(const char** pArrayAsset, u32* pArrayIndexes, u32 assetCount);

protected:
	IMGITEM		*	m_items;	// イメージの情報

	bool getImgList(CLuaState& lua, IMGITEM* items, u32 max);
private:

	u32				m_idxMax;
	u32				m_cntImg;	// 与えられたイメージの数
	u32				m_idxImg;	// 現在表示されているイメージのindex
	u32				m_order;

	static	PROP_V2		ms_propItems[];
};

#endif // CKLBMultiImgItem_h
