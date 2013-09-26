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
#include "CKLBUIScale9.h"
#include "CKLBUtility.h"
#include "CKLBLuaEnv.h"
;
// Command Values
enum {
	UI_SCALE9_SETRESOURCE	= 0,
	UI_SCALE9_SETWIDTH		= 1,
	UI_SCALE9_SETHEIGHT		= 2,
	UI_SCALE9_SETSIZE		= 3
};

static IFactory::DEFCMD cmd[] = {
	{"UI_SCALE9_SETRESOURCE",		UI_SCALE9_SETRESOURCE		},
	{"UI_SCALE9_SETWIDTH",			UI_SCALE9_SETWIDTH			},
	{"UI_SCALE9_SETHEIGHT",			UI_SCALE9_SETHEIGHT			},
	{"UI_SCALE9_SETSIZE",			UI_SCALE9_SETSIZE			},
	{0, 0}
};

static CKLBTaskFactory<CKLBUIScale9> factory("UI_Scale9", CLS_KLBUISCALE9, cmd);

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUIScale9::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",	UINTEGER,	(setBoolT)&CKLBUIScale9::setOrder,	(getBoolT)&CKLBUIScale9::getOrder,	0	},
	{	"width",	INTEGER,	(setBoolT)&CKLBUIScale9::setWidth,	(getBoolT)&CKLBUIScale9::getWidth,	0	},
	{	"height",	INTEGER,	(setBoolT)&CKLBUIScale9::setHeight,	(getBoolT)&CKLBUIScale9::getHeight,	0	},
	{	"asset",	R_STRING,	NULL,								(getBoolT)&CKLBUIScale9::getAsset,	0	}
};

enum {
	ARG_PARENT = 1,

	ARG_ORDER,
	ARG_X,
	ARG_Y,
	ARG_WIDTH,
	ARG_HEIGHT,
	ARG_ASSET,

	ARG_REQUIRE	= ARG_ASSET,
	ARG_NUMS	= ARG_ASSET
};

CKLBUIScale9::CKLBUIScale9()
: CKLBUITask    ()
, m_handle      (0)
, m_texture     (NULL)
, m_scale9      (NULL)
, m_asset       (NULL)
, m_width       (0)
, m_height      (0)
{
	setNotAlwaysActive();
	m_newScriptModel = true;
}

CKLBUIScale9::~CKLBUIScale9() {
 KLBDELETEA(m_asset);
}

u32
CKLBUIScale9::getClassID()
{
	return CLS_KLBUISCALE9;
}


bool
CKLBUIScale9::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
    if(argc < ARG_REQUIRE || argc > ARG_NUMS) { return false; }

	u32 order	= lua.getInt(ARG_ORDER);
	float x 	= lua.getFloat(ARG_X);
	float y 	= lua.getFloat(ARG_Y);

	return initCore(order, x,y, 
		lua.getInt(ARG_WIDTH),
		lua.getInt(ARG_HEIGHT),
		lua.getString(ARG_ASSET));
}

CKLBUIScale9 *
CKLBUIScale9::create(CKLBUITask * pParent, CKLBNode * pNode,
                     u32 order, float x, float y, s32 width, s32 height,
                     const char * asset)
{
	CKLBUIScale9 * pTask = KLBNEW(CKLBUIScale9);
    if(!pTask) { return NULL; }

	if(!pTask->init(pParent, pNode, order, x, y, width, height, asset)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUIScale9::init(CKLBUITask * pParent, CKLBNode * pNode,
                   u32 order, float x, float y, s32 width, s32 height, const char * asset)
{
    if(!setupNode()) { return false; }

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(order, x, y, width, height, asset);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}

	return bResult;
}

bool
CKLBUIScale9::initCore(u32 order, float x, float y, s32 width, s32 height, const char * asset)
{
	// 対応するプロパティリストを規定する。
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}
	/* FUTURE VERSION.
	// 対応するプロパティリストを規定する。
	CKLBUITask::setupPropertyList(s_Scale9NameStatic, m_Scale9PropValue, m_Scale9PropType, m_Scale9PropChecked);
	fillPropertyList(ms_propItems);
	*/
	
	CKLBAsset* pAsset = CKLBUtility::loadAssetScript(asset,&m_handle);
	if(pAsset && (pAsset->getAssetType() == ASSET_IMAGE)) {
		CKLBImageAsset* pImage = (CKLBImageAsset*)pAsset;
		bool isScale9 = (pImage->hasStandardAttribute(CKLBImageAsset::IS_SCALE9) != 0);		
		if(isScale9) {
			m_scale9 = (CKLBSpriteScale9*)CKLBRenderingManager::getInstance().allocateCommandSprite(pImage, order);
		} else {
			klb_assertAlways("Not scale 9 image associated to UIScale9 object (%s)",asset);
		}
	}

	if(!m_scale9) {
		return false;
	}


	klb_assert((((s32)order) >= 0), "Order Problem");

	setOrder(order);
	setStrC(m_asset, asset);

	getNode()->setRender(m_scale9);
	setInitPos(x, y);
	setWidth(width);
	setHeight(height);
	m_bInit = true;
	
	return true;
}

bool 
CKLBUIScale9::setAsset(const char* asset) 
{
	u32 oldHandle = m_handle;

	CKLBAsset* pAsset = CKLBUtility::loadAssetScript(asset,&m_handle);
	if(pAsset && (pAsset->getAssetType() == ASSET_IMAGE)) {
		CKLBImageAsset* pImgAsset	= (CKLBImageAsset*)pAsset;
		bool isScale9 = (pImgAsset->hasStandardAttribute(CKLBImageAsset::IS_SCALE9) != 0);		
		if(isScale9) {
			setStrC(m_asset, asset);
			m_scale9->useImage(pImgAsset);
			// Release link on previous texture.
			CKLBUtility::deleteNode(NULL, oldHandle);
			return true;
		}
	}
	return false;
}

int
CKLBUIScale9::commandUI(CLuaState& lua, int argc, int cmd)
{
	bool result = false;
	int  ret    = 0;
	switch(cmd)
	{
	case UI_SCALE9_SETRESOURCE:
		if (argc == 3) {
			result = setAsset(lua.getString(3));
			ret = 1;
		}
		break;
	case UI_SCALE9_SETWIDTH:
		if (argc == 3) {
			s32 width = lua.getInt(3);
			setWidth(width);
			ret = 1;
			result = true;
		}
		break;
	case UI_SCALE9_SETHEIGHT:
		if (argc == 3) {
			s32 height = lua.getInt(3);
			setHeight(height);
			ret = 1;
			result = true;
		}
		break;
	case UI_SCALE9_SETSIZE:
		if (argc == 4) {
			s32 width	= lua.getInt(3);
			s32 height	= lua.getInt(4);

			setWidth(width);
			setHeight(height);
			
			ret = 1;
			result = true;
		}
		break;
	default:
		{
			result = false;
		}
		break;
	}

	lua.retBoolean(result);
	return ret;
}

void
CKLBUIScale9::execute(u32 /* deltaT */)
{
}

void
CKLBUIScale9::dieUI()
{
	CKLBUtility::deleteNode(NULL, m_handle);
}
