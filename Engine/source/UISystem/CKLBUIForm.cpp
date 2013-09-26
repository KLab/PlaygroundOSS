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
#include "CKLBUIForm.h"
#include "CKLBAction.h"
#include "CKLBDataHandler.h"
#include "CKLBUtility.h"
#include "CKLBTouchEventUI.h"
#include "CKLBTextInputNode.h"
#include "CKLBWebViewNode.h"
#include "CKLBFormGroup.h"
#include "CKLBScriptEnv.h"
#include "CKLBLuaLibSOUND.h"

// Command Values
enum {
	UI_FORM_SET_ENABLED = 0,
	UI_FORM_UPDATE_NODE,
	UI_FORM_EXIST_NODE,
	UI_FORM_INPUT_ENABLE,       // フォーム単位でのパネル入力許可/禁止

	UI_FORM_ANIM_CALLBACK,      // アニメーションコールバックを設定
	UI_FORM_ANIM_GET_CALLBACK,	// アニメーションコールバック名を取得
	UI_FORM_ANIMATION,          // アニメーションを開始
	UI_FORM_SKIP_ANIM,          // アニメーションを強制的に終了状態に

	UI_FORM_IS_ANIM,

	UI_FORM_ANIM_ENTER,
	UI_FORM_ANIM_LEAVE,

	UI_FORM_SET_GROUP,          // フォームをグループに所属させる(フォーム間排他)
	UI_FORM_SET_VOLUME,
};


static IFactory::DEFCMD cmd[] = {
	{ "UI_FORM_SET_ENABLED",	UI_FORM_SET_ENABLED             },
	{ "UI_FORM_UPDATE_NODE",	UI_FORM_UPDATE_NODE             },
	{ "UI_FORM_EXIST_NODE",		UI_FORM_EXIST_NODE              },
	{ "UI_FORM_INPUT_ENABLE",	UI_FORM_INPUT_ENABLE            },
	{ "UI_FORM_ANIM_CALLBACK",	UI_FORM_ANIM_CALLBACK           },
	{ "UI_FORM_ANIM_GET_CALLBACK",	UI_FORM_ANIM_GET_CALLBACK   },
	{ "UI_FORM_ANIMATION",		UI_FORM_ANIMATION               },

	{ "UI_FORM_IS_ANIM",		UI_FORM_IS_ANIM         },
	{ "UI_FORM_SKIP_ANIM",		UI_FORM_SKIP_ANIM       },
	
	{ "UI_FORM_ANIM_ENTER",		UI_FORM_ANIM_ENTER      },
	{ "UI_FORM_ANIM_LEAVE",		UI_FORM_ANIM_LEAVE      },

	{ "UI_FORM_SET_GROUP",		UI_FORM_SET_GROUP       },
//	{ "UI_FORM_SET_VOLUME",		UI_FORM_SET_VOLUME      }, Private for now.
	{ "ACTION_UNDEF",	ACTION_UNDEF    },
	{ "ACTION_PUSH",	ACTION_PUSH     },
	{ "ACTION_RELEASE",	ACTION_RELEASE  },
	{ "ACTION_CLOSE",	ACTION_CLOSE    },
	{ "ACTION_ENDANIM",	ACTION_ENDANIM  },
	{ "ACTION_CHANGE",	ACTION_CHANGE   },
	{ "ACTION_FOCUS",	ACTION_FOCUS    },
	{ "ACTION_CUSTOM",	ACTION_CUSTOM   },
	{ "ACTION_CLICK",   ACTION_CLICK    },


	// サブコマンド定数定義
	{ "FORM_NODE_POINTER",			CKLBFormIF::FORM_NODE_POINTER   },
	{ "FORM_NODE_RECURSIVE",		CKLBFormIF::FORM_NODE_RECURSIVE },
	{ "FORM_NODE_TRANS",			CKLBFormIF::FORM_NODE_TRANS     },
	{ "FORM_NODE_SCALE",			CKLBFormIF::FORM_NODE_SCALE     },
	{ "FORM_NODE_ROT",				CKLBFormIF::FORM_NODE_ROT       },
	{ "FORM_NODE_COLOR",			CKLBFormIF::FORM_NODE_COLOR     },
	{ "FORM_NODE_VISIBLE",			CKLBFormIF::FORM_NODE_VISIBLE   },
	{ "FORM_NODE_ORDER",			CKLBFormIF::FORM_NODE_ORDER     },
	{ "FORM_NODE_GET_ORDER",		CKLBFormIF::FORM_NODE_GET_ORDER },
	{ "FORM_NODE_TASK",				CKLBFormIF::FORM_NODE_TASK      },

	{ "FORM_UIE_SET_ENABLED",		CKLBFormIF::FORM_UIE_SET_ENABLED    },
	{ "FORM_UIE_GET_ENABLED",		CKLBFormIF::FORM_UIE_GET_ENABLED    },
	{ "FORM_UIE_SET_ASSET",			CKLBFormIF::FORM_UIE_SET_ASSET      },

	{ "FORM_UIS_SET_CLICK",			CKLBFormIF::FORM_UIS_SET_CLICK  },
	{ "FORM_UIS_SET_STICK",			CKLBFormIF::FORM_UIS_SET_STICK  },
	{ "FORM_UIS_SET_RADIO",			CKLBFormIF::FORM_UIS_SET_RADIO  },
	{ "FORM_UIS_GET_STICK",			CKLBFormIF::FORM_UIS_GET_STICK  },
	{ "FORM_UIS_SET_CALLBACK",		CKLBFormIF::FORM_UIS_SET_CALLBACK   },

	{ "FORM_CONT_VIEWOFFSET",		CKLBFormIF::FORM_CONT_VIEWOFFSET        },
	{ "FORM_CONT_GET_RADIO_VALUE",	CKLBFormIF::FORM_CONT_GET_RADIO_VALUE   },

	{ "FORM_TEXT_SET",				CKLBFormIF::FORM_TEXT_SET       },
	{ "FORM_TEXT_GET",				CKLBFormIF::FORM_TEXT_GET       },

	{ "FORM_WEB_SET_URI",			CKLBFormIF::FORM_WEB_SET_URI    },
	{ "FORM_WEB_GET_URI",			CKLBFormIF::FORM_WEB_GET_URI    },

	{ "FORM_LBL_SET_TEXT",			CKLBFormIF::FORM_LBL_SET_TEXT   },
	{ "FORM_LBL_GET_TEXT",			CKLBFormIF::FORM_LBL_GET_TEXT   },

	{ "FORM_ASSET_NORMAL",			CKLBUIElement::NORMAL_ASSET     },
	{ "FORM_ASSET_DISABLED",		CKLBUIElement::DISABLED_ASSET   },
	{ "FORM_ASSET_FOCUSED",			CKLBUIElement::FOCUSED_ASSET    },
	{ "FORM_ASSET_PUSHED",			CKLBUIElement::PUSHED_ASSET     },


	{0, 0}
};

static CKLBTaskFactory<CKLBUIForm> factory("UI_Form", CLS_KLBUIFORM, cmd);


// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUIForm::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",			R_UINTEGER,	NULL,									(getBoolT)&CKLBUIForm::getOrder,		0	},
	{	"asset",			R_STRING,	NULL,									(getBoolT)&CKLBUIForm::getAsset,		0	},
	{	"isfile",			R_BOOLEANT,	NULL,									(getBoolT)&CKLBUIForm::getAssetFile,	0	},
	{	"exclusive",		BOOLEANT,	(setBoolT)&CKLBUIForm::setExclusive,	(getBoolT)&CKLBUIForm::getExclusive,	0	}
};

enum {
	ARG_PARENT = 1,

	ARG_ORDER,
	ARG_X,
	ARG_Y,

	ARG_ASSET,

	ARG_EXCLUSIVE,

	ARG_MODAL,

	ARG_URGENT,

	ARG_REQUIRE = ARG_ASSET,
	ARG_NUMS    = ARG_URGENT
};

CKLBUIForm::CKLBUIForm()
: CKLBUITask    ()
, m_modalStack  (false)
, m_asset       (NULL)
, m_bInputEnable(true) 
{
	m_formIF = this;
	m_newScriptModel = true;
}

CKLBUIForm::~CKLBUIForm() 
{
	KLBDELETEA(m_asset);
}

u32
CKLBUIForm::getClassID()
{
	return CLS_KLBUIFORM;
}

CKLBUIForm* 
CKLBUIForm::create(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, bool bAssetFile, const char* asset, bool bExclusive, bool modal, bool urgent) {
	CKLBUIForm* pTask = KLBNEW(CKLBUIForm);
    if (!pTask) { return NULL; }
	if (!pTask->init(pParent, pNode, order, x,y,bAssetFile,asset,bExclusive,modal, urgent)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

void 
CKLBUIForm::setGlobalVolume(float volume) 
{
	setGlobalVolume_r(getNode(), volume);
}


#include "CKLBUISystem.h"

void 
CKLBUIForm::setGlobalVolume_r(CKLBNode* pNode, float volume) 
{
	if (pNode->getClassID() == CLS_KLBUISELECTABLE) {
		CKLBUISelectable* pSelect = (CKLBUISelectable*)pNode;
		pSelect->setMultiplyVolume(0, volume);
		pSelect->setMultiplyVolume(1, volume);
	}
	CKLBNode* pList = pNode->getChild();
	while (pList) {
		setGlobalVolume_r(pList, volume);
		pList = pList->getBrother();
	}
}

bool
CKLBUIForm::init(CKLBUITask* parent, CKLBNode* pNode, u32 order, float x, float y, bool bAssetFile, const char* asset, bool bExclusive, bool modal, bool urgent) 
{
	if (!setupNode()) return false;
	bool bResult = initCore(order, x, y, bAssetFile, asset, 0, bExclusive, modal, urgent);
	bResult = registUI(parent, bResult);
	if (pNode) {
		parent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}
	return bResult;
}

bool
CKLBUIForm::initCore(u32 order, float x, float y, bool bAssetFile, const char* asset, u32 size, bool bExclusive, bool modal, bool urgent)
{
	if (!setupPropertyList((const char**)ms_propItems, SizeOfArray(ms_propItems))) {
		return false;
	}

	setInitPos(x, y);

	klb_assert((((s32)order) >= 0), "Order Problem");

	m_order = order;

	// assetがファイルで与えられた場合true, luaテーブルで与えられた場合false
	m_bAssetFile = bAssetFile;
	if(size == 0) { 
		setStrC(m_asset, asset); 
	} else {
		m_asset = CKLBUtility::copyMem(asset, size);
	}
	m_modalStack.setModal(modal, urgent);

	m_bExclusive = bExclusive;

	// form によって起動されたタスクの中に、UI_DragIconのようなモーダルスタック対応タスクがある場合があるので、
	// form を作る前に自身をモーダルスタックに積む。
	m_modalStack.push();

	m_ctrlList.pGroup           = NULL;
	m_ctrlList.pGrpPrev         = NULL;
	m_ctrlList.pGrpNext         = NULL;

	m_ctrlList.pBegin           = NULL;
	m_ctrlList.next             = NULL;
	m_ctrlList.bEnable          = true;
	m_ctrlList.bExclusive       = bExclusive;
	m_ctrlList.bWorking         = false;
	m_ctrlList.pCallbackIF      = NULL;
	m_ctrlList.nativeCallback   = NULL;
	m_ctrlList.pID              = NULL;

	CKLBUISystem::setFormList(&m_ctrlList);
	// DEBUG_PRINT(" FORM:ctrl: %p", &m_ctrlList);

	CKLBAssetManager& pAssetManager = CKLBAssetManager::getInstance();
	if(bAssetFile) {
		m_pFormNode = CKLBUtility::createCompositeNodeScript(this, m_asset, m_order, &m_handle, pAssetManager.getPlugin('P'));
	} else {
		m_pFormNode = NULL;
		CKLBAsset * pAsset = CKLBUtility::readAsset((u8 *)m_asset, size, &m_handle, pAssetManager.getPlugin('P'));
		if(!pAsset) {
			CKLBScriptEnv::getInstance().error("could not load asset: %s", m_asset);
		} else {
			m_pFormNode = ((CKLBCompositeAsset*)pAsset)->createSubTree(this, m_order);
			if(!m_pFormNode) {
				CKLBScriptEnv::getInstance().error("Node create failed. Json arg.");
			}
		}
	}
	CKLBUISystem::setFormList(NULL);
	if(!m_pFormNode) {
		// フォームのツリー生成に失敗した場合、すべてをご破算にしてタスク生成を失敗させる
		return false;
	}
	// フォーム単位として登録する
	CKLBTouchEventUIMgr::getInstance().registForm(&m_ctrlList);

	// CKLBUISystem::setFormList(&m_ctrlList) ～ CKLBUISystem::setFormList(0) までの処理で、
	// m_ctrlList 内に、このフォームで作られたものに限定された CKLBUISelectable のリストが得られる。

	getNode()->addNode(m_pFormNode);
	// getNode()->setTranslate(getNum(PR_X), getNum(PR_Y));	// generic property として設定される

	setGlobalVolume(CKLBLuaLibSOUND::getFormGlobalVolume());

	m_bEnable = false;
	setFormEnable(true);

//	setVisible(true);

	return true;
}

bool
CKLBUIForm::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
    if(argc < ARG_REQUIRE || argc > ARG_NUMS) { return false; }

	const char* asset;
	bool bAssetFile = true;
	u32 size = 0;
	if(lua.isString(ARG_ASSET)) {
		// 指定されたassetが文字列であれば、パス名として使用
		asset = lua.getString(ARG_ASSET);
	} else {
		// 指定されたassetが文字列でなければ、おそらくLuaテーブル。
		// Luaテーブルを元にJSONを生成し、それをassetとして使用する。
		bAssetFile = false;
		lua.retValue(ARG_ASSET);
		asset = CKLBUtility::lua2BJson(lua,size);
		lua.pop(1);
	}

	bool bExclusive = (argc >= ARG_EXCLUSIVE)	? lua.getBool(ARG_EXCLUSIVE)	: false;
	bool modal		= (argc >= ARG_MODAL)		? lua.getBool(ARG_MODAL)		: false;
	bool urgent		= (argc >= ARG_URGENT)		? lua.getBool(ARG_URGENT)		: false;
	
	bool res = initCore(lua.getInt(ARG_ORDER),
						lua.getFloat(ARG_X), 
						lua.getFloat(ARG_Y),
						bAssetFile,
						asset, size,
						bExclusive,
						modal,
						urgent);

	if(!bAssetFile) {
		KLBDELETEA(asset);
	}

	return res;
}

void
CKLBUIForm::dieUI()
{
	// モーダル制御
	setVisible(false);	// フォームが無効になるので、スタックから取り除く処理。

	CKLBTouchEventUIMgr& mgr = CKLBTouchEventUIMgr::getInstance();


	CKLBUISelectable * pItem = m_ctrlList.pBegin;
	CKLBUISelectable * pNext;
	while(pItem) {
		pNext = pItem->getNextSelectable();
		// フォームのコントロールが操作中であれば、操作中ステータスをリセットする
		mgr.resetSelectable(pItem);
		pItem = pNext;
	}

	// フォームグループから削除する
	CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();
	fGrp.delForm(&m_ctrlList);

	CKLBUtility::deleteNode(m_pFormNode, m_handle);

	// フォームを破棄
	// Remove last.
	mgr.removeForm(&m_ctrlList);
}

void
CKLBUIForm::execute(u32 /*deltaT*/)
{
	setFormEnable(m_modalStack.isEnable());	// modal 状態反映
	m_animpack.watchFinishedAnim(this);
}


int
CKLBUIForm::commandUI(CLuaState& lua, int argc, int cmd)
{
	int ret = 0;

	switch(cmd)
	{
	default:
		{
			// 知らないコマンドの場合
			lua.retBoolean(false);
			ret = 1;
		}
		break;
	case UI_FORM_SET_ENABLED:
		{
			// フォーム操作の許可/禁止(全体)
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			bool isEnable = lua.getBool(3);

			setEnable(isEnable);

			lua.retBoolean(true);
			ret = 1;
		}
		break;
	case UI_FORM_UPDATE_NODE:
		{
			if(argc < 4) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			// const char * name = lua.getString(3);
			int subcmd = lua.getInt(4);
			CKLBNode * pParent = getNode();
			ret = m_formIF.updateNode(lua, argc, 4, pParent, 3, subcmd);
		}
		break;
	case UI_FORM_EXIST_NODE:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			const char * name =  lua.getString(3);

			bool bResult = existNode(name);
			
			lua.retBool(bResult);
			ret = 1;
		}
		break;
	case UI_FORM_INPUT_ENABLE:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			bool bEnable = lua.getBool(3);

			inputEnable(bEnable);
			
			lua.retBoolean(true);
			ret = 1;
		}
		break;

	case UI_FORM_ANIM_CALLBACK:
		{
			bool result = false;
			if(argc == 3) {
				const char * callback = (lua.isNil(3)) ? NULL : lua.getString(3);
				result = setAnimCallback(callback);
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;

	case UI_FORM_ANIM_GET_CALLBACK:
		{
			if(argc == 2) {
				const char * callback = m_animpack.getCallback();
				lua.retString(callback);
			} else {
				lua.retNil();
			}
			ret = 1;
		}
		break;

	case UI_FORM_ANIMATION:
		{
			bool result = false;
			if(argc >= 3 && argc <= 4) {
				const char * animname = lua.getString(3);
				bool blend = (argc >= 4) ? lua.getBool(4) : false;

				result = animation(animname, blend);
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_FORM_IS_ANIM:
		{
			bool result = false;
			if(argc >= 2 && argc <= 3) {
				const char * name = 0;
				if(argc >= 3 && !lua.isNil(3)) name = lua.getString(3);
				
				result = isAnim(name);
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_FORM_SKIP_ANIM:
		{
			bool result = false;
			if(argc >= 2 && argc <= 3) {
				const char * name = 0;
				if(argc >= 3 && !lua.isNil(3)) name = lua.getString(3);
				
				result = skipAnim(name);
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_FORM_ANIM_ENTER:
		{
			bool result = false;
			if(argc == 2) {
				result = animEnter();
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_FORM_ANIM_LEAVE:
		{
			bool result = false;
			if(argc == 2) {
				result = animLeave();
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;

	case UI_FORM_SET_GROUP:
		{
			bool result = false;
			if(argc == 3) {
				const char * group_name = lua.getString(3);
				
				result = setGroup(group_name);
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_FORM_SET_VOLUME:
		{
			bool result = false;
			if(argc == 3) {
				float volume = lua.getFloat(3);
				setGlobalVolume(volume);
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	}
	return ret;
}

bool
CKLBUIForm::setFormEnable(bool bEnable)
{
//	if(m_bEnable == bEnable) return bEnable;

	m_bEnable = bEnable;
	m_ctrlList.bEnable = m_bEnable && m_bInputEnable;

	/*
	SFormCtrl * pItem;
	for(pItem = m_ctrlList.pBegin; pItem; pItem = pItem->pNext) {
		pItem->pCtrl->setEnabled(bEnable);
	}
	*/
	return bEnable;
}

void
CKLBUIForm::setVisible(bool visible)
{
	if(visible != getVisible()) {
		CKLBUITask::setVisible(visible);
		if(visible) {
			// 有効にされた場合
			m_modalStack.push();
		} else {
			// 無効にされた場合
			m_modalStack.remove();
		}
	}
}
