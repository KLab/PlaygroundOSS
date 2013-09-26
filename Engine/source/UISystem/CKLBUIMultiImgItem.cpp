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
#include "CKLBUIMultiImgItem.h"
#include "CKLBUtility.h"
;
// Command Values
enum {
	UI_MULTIIMG_SET_INDEX = 0,
};

static IFactory::DEFCMD cmd[] = {
	{"UI_MULTIIMG_SET_INDEX", UI_MULTIIMG_SET_INDEX },
	{0, 0}
};

static CKLBTaskFactory<CKLBUIMultiImgItem> factory("UI_MultiImgItem", CLS_KLBUIMULTIIMGITEM, cmd);

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUIMultiImgItem::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",	UINTEGER,	(setBoolT)&CKLBUIMultiImgItem::setOrder,	(getBoolT)&CKLBUIMultiImgItem::getOrder,	0	},
	{	"index",	UINTEGER,	(setBoolT)&CKLBUIMultiImgItem::setIndex,	(getBoolT)&CKLBUIMultiImgItem::getIndex,	0	},
	{	"idxmax",	UINTEGER,	(setBoolT)&CKLBUIMultiImgItem::setIndexMax,	(getBoolT)&CKLBUIMultiImgItem::getIndexMax,	0	}
	// TODO : Useless property -> Does not exist, isnt used !
};

enum {
	ARG_PARENT = 1,

	ARG_ORDER,
	ARG_X,
	ARG_Y,

	ARG_ASSET_LIST,

	ARG_INDEX,

	ARG_REQUIRE = ARG_ASSET_LIST,
	ARG_NUMS = ARG_INDEX
};

CKLBUIMultiImgItem::CKLBUIMultiImgItem()
: CKLBUITask    ()
, m_items       (NULL)
{
	setNotAlwaysActive();
	m_newScriptModel = true;
}

CKLBUIMultiImgItem::~CKLBUIMultiImgItem() 
{
}

CKLBUIMultiImgItem* 
CKLBUIMultiImgItem::create(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, u32 idx, const char** pArrayAsset, u32* pArrayIndexes, u32 assetCount) 
{
	CKLBUIMultiImgItem* pTask = KLBNEW(CKLBUIMultiImgItem);
    if(!pTask) { return NULL; }

	if(!pTask->init(pParent, pNode, order, x,y,idx,pArrayAsset, pArrayIndexes, assetCount)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool CKLBUIMultiImgItem::init(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, u32 idx, const char** pArrayAsset, u32* pArrayIndexes, u32 assetCount) {
	if(!setupNode()) return false;

	//
	// Create array and load resources.
	//
	u32 max = 0;
	for(u32 i = 0; i < assetCount; i++) {
		u32 idxImg = pArrayIndexes[i];
        if(max < idxImg) { max = idxImg; }
	}
	
	max++;

	IMGITEM* items = KLBNEWA(IMGITEM, max);
	if(!items) { return false; }

	// Reset all handle to NULL
	for(u32 i=0; i < max; i++) {
		items[i].handle	= 0;
		items[i].sprite = NULL;
	}

	CKLBRenderingManager& rdr = CKLBRenderingManager::getInstance();
	for(u32 i = 0; i < assetCount; i++) {
		const char* name = pArrayAsset[i];
		u32 idxImg = pArrayIndexes[i];
		u32 handle;
		CKLBAsset * pAsset = CKLBUtility::loadAsset(name, &handle, NULL);
		if(pAsset->getAssetType() == ASSET_IMAGE) {
			CKLBSprite*	pRender	= rdr.allocateCommandSprite((CKLBImageAsset*)pAsset,order);

			items[idxImg].handle = handle;
			items[idxImg].sprite = pRender;
		}
	}

	bool bResult = initCore(order,x,y,idx,items,max);
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}
	return bResult;
}

bool 
CKLBUIMultiImgItem::initCore(u32 order,float x,float y, u32 index, IMGITEM* pIndexes, u32 max)
{
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	setInitPos(x, y);

	// 領域を確保
	m_cntImg    = max;
	m_items     = pIndexes;
    if(!m_items) { return false; }
	m_idxMax    = m_cntImg - 1;	// 最大index値を追加する

	REFRESH_A;
	REFRESH_B;

	klb_assert((((s32)order) >= 0), "Order Problem");

	m_order     = order;
	setIndex(index);

	return true;
}

bool
CKLBUIMultiImgItem::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < ARG_REQUIRE || argc > ARG_NUMS) return false;

	float x     = lua.getFloat(ARG_X);
	float y     = lua.getFloat(ARG_Y);
	u32 order   = lua.getInt(ARG_ORDER);
	u32 idxImg  = (argc >= ARG_INDEX) ? lua.getInt(ARG_INDEX) : 0;
	
	// asset list を取得
	lua.retValue(ARG_ASSET_LIST);

	// 要素の数を数える
	int max = 0;
	lua.retNil();

	// Read indexes and count entries.
	while(lua.tableNext()) {
		lua.retValue(-2);
		int idx = lua.getInt(-1);
		if(max < idx) max = idx;
		lua.pop(2);
	}

	IMGITEM* items = KLBNEWA(IMGITEM, max);

    if(!items) { return false; }

	// Reset all handle to NULL
	for(int idx = 0; idx < max; idx++) {
		items[idx].handle = 0;
		items[idx].sprite = NULL;
	}

	m_order = order; // Needed for getImgList
    if(!getImgList(lua,items,max)) { return false; }
	return initCore(order, x,y,idxImg,items,max);
}

bool
CKLBUIMultiImgItem::getImgList(CLuaState& lua, IMGITEM* items, u32 /*max*/)
{
	CKLBRenderingManager& rdr = CKLBRenderingManager::getInstance();

	lua.retNil();
	while(lua.tableNext()) {
		lua.retValue(-2);
		int idx = lua.getInt(-1) - 1;
		const char * name = lua.getString(-2);
		lua.pop(2);

		u32 handle;
		CKLBAsset * pAsset = CKLBUtility::loadAsset(name, &handle, NULL);
		if(pAsset->getAssetType() == ASSET_IMAGE) {
			CKLBSprite*	pRender	= rdr.allocateCommandSprite((CKLBImageAsset*)pAsset,m_order);

			items[idx].handle = handle;
			items[idx].sprite = pRender;
		}

	}

	return true;
}

int
CKLBUIMultiImgItem::commandUI(CLuaState& lua, int argc, int cmd)
{
	int ret = 0;
	switch(cmd)
	{
	default:
		{
			lua.retBoolean(false);
			ret = 1;
		}
		break;
	case UI_MULTIIMG_SET_INDEX:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			int idx = lua.getInt(3);
			// 指定されたindexが有効な範囲に収まらなければ、何もせずfalseを返す
			int max = m_idxMax;
			if(idx > max || idx < 0) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			setIndex(idx);
			lua.retBoolean(true);
			ret = 1;
		}
		break;
	}
	return ret;
}

void
CKLBUIMultiImgItem::execute(u32 /* deltaT */)
{
	if(CHANGE_A) {
		CKLBNode* pNode = getNode();
		pNode->setRender(m_items[m_idxImg].sprite,0);
		pNode->markUpMatrix();
		RESET_A;
	}

	if(CHANGE_B) {
		u32 max = m_idxMax;

		// 最大値の書き換えは是正する
		if(max >= m_cntImg) {
			max = m_cntImg - 1;
			m_idxMax = max;
		}

		if(m_idxImg <= max) {  /* && m_idxImg >= 0 : m_idxImg is unsigned */
			CKLBNode* pNode = getNode();
			CKLBRenderingManager& rdr = CKLBRenderingManager::getInstance();
			m_items[m_idxImg].sprite->changeOrder(rdr,m_order);
			if(m_items[m_idxImg].sprite != pNode->getRender(0)) {
				pNode->setRender(m_items[m_idxImg].sprite,0);
				pNode->markUpMatrix();
			}
		}

		RESET_B;
	}
}

void
CKLBUIMultiImgItem::dieUI()
{
	getNode()->setRender(NULL,0);
	CKLBRenderingManager& rdr = CKLBRenderingManager::getInstance();
	for(u32 i = 0; i < m_cntImg; i++) {
		CKLBDataHandler::releaseHandle(m_items[i].handle);
		rdr.releaseCommand(m_items[i].sprite);
	}
	KLBDELETEA(m_items);
}

u32
CKLBUIMultiImgItem::getClassID()
{
	return CLS_KLBUIMULTIIMGITEM;
}

// TODO C# - check this method.
bool 
CKLBUIMultiImgItem::changeAssets(const char** pArrayAsset, u32* pArrayIndexes, u32 assetCount)
{
	getNode()->setRender(NULL,0);
	CKLBRenderingManager& rdr = CKLBRenderingManager::getInstance();
	for(u32 i = 0; i < m_cntImg; i++) {
		CKLBDataHandler::releaseHandle(m_items[i].handle);
		rdr.releaseCommand(m_items[i].sprite);
	}
	KLBDELETEA(m_items);

	u32 max = 0;
	for(u32 idx = 0; idx < assetCount; idx++) {
		u32 idxImg = pArrayIndexes[idx];
		if (max < idxImg) max = idxImg;
	}
	
	max++;

	IMGITEM* items = KLBNEWA(IMGITEM, max);
	if(!items) { return false; }

	// Reset all handle to 0
	for(u32 idx = 0; idx < max; idx++) {
		items[idx].handle = 0;
		items[idx].sprite = NULL;
	}

	for(u32 i=0; i < assetCount; i++) {
		const char* name = pArrayAsset[i];
		u32 idxImg = pArrayIndexes[i];
		u32 handle;
		CKLBAsset * pAsset = CKLBUtility::loadAsset(name, &handle, NULL);
		if (pAsset->getAssetType() == ASSET_IMAGE) {
			CKLBSprite*	pRender	= rdr.allocateCommandSprite((CKLBImageAsset*)pAsset,m_order);

			items[idxImg].handle = handle;
			items[idxImg].sprite = pRender;
		}
	}

	m_cntImg    = max;
	m_items     = items;
	m_idxMax    = m_cntImg - 1;	// 最大index値を追加する

	REFRESH_A;
	REFRESH_B;

	return true;
}
