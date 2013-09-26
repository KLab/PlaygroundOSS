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
#include "CKLBUITouchPad.h"
#include "CKLBTouchPad.h"
#include "CKLBLuaEnv.h"
#include "CKLBScriptEnv.h"

;
enum {
	UI_TOUCHPAD_SET_GROUP,
	UI_TOUCHPAD_LOCK,
	UI_TOUCHPAD_GET_ALL,
};

static IFactory::DEFCMD cmd[] = {
	{ "UI_TOUCHPAD_SET_GROUP",	UI_TOUCHPAD_SET_GROUP },
	{ "UI_TOUCHPAD_LOCK",		UI_TOUCHPAD_LOCK },
	{ "UI_TOUCHPAD_GET_ALL",	UI_TOUCHPAD_GET_ALL },

	{ "PAD_ITEM_TAP",       PAD_ITEM::TAP },
	{ "PAD_ITEM_DRAG",      PAD_ITEM::DRAG },
	{ "PAD_ITEM_RELEASE",	PAD_ITEM::RELEASE },

	{ 0, 0}
};
static CKLBTaskFactory<CKLBUITouchPad> factory("UI_TouchPad", CLS_KLBUITOUCHPAD, cmd);

enum {
	ARG_CALLBACK = 1,
	ARG_MODAL,

	ARG_REQUIRE = ARG_CALLBACK,
	ARG_NUMS = ARG_MODAL
};

CKLBUITouchPad::CKLBUITouchPad() 
: CKLBLuaTask   ()
, m_luaFunc     (NULL)
, m_bAll        (false) 
{
}

CKLBUITouchPad::~CKLBUITouchPad() 
{
}

u32
CKLBUITouchPad::getClassID()
{
	return CLS_KLBUITOUCHPAD;
}

CKLBUITouchPad* 
CKLBUITouchPad::create(CKLBTask* pParentTask, const char * funcName, bool modal) 
{
	CKLBUITouchPad* pTask = KLBNEW(CKLBUITouchPad);
    if(!pTask) { return NULL; }

	if(!pTask->init(pParentTask, funcName, modal)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool 
CKLBUITouchPad::init(CKLBTask* pTask, const char* funcname, bool modal) 
{
	if(funcname) setStrC(m_luaFunc, funcname);
	m_modal = modal;

	m_ctrlList.pGroup           = NULL;
	m_ctrlList.pGrpPrev         = NULL;
	m_ctrlList.pGrpNext         = NULL;

	m_ctrlList.pBegin           = NULL;
	m_ctrlList.next             = NULL;
	m_ctrlList.bEnable          = true;
	m_ctrlList.bExclusive       = false;
	m_ctrlList.bWorking         = false;
	m_ctrlList.pCallbackIF      = NULL;
	m_ctrlList.nativeCallback   = NULL;
	m_ctrlList.pID              = NULL;

	if(m_modal) {
		m_modalStack.setModal(false);
		m_modalStack.push();	// modal stack に積む
	}
    bool result = regist(pTask, P_AFTER);
    if(!result) {
        KLBDELETEA(m_luaFunc);
    }

	m_execount = 0;
    return true;
}

bool
CKLBUITouchPad::initScript(CLuaState& lua)
{
	int argc = lua.numArgs();
    if(argc < ARG_REQUIRE || argc > ARG_NUMS) { return false; }

	const char * funcname = lua.getString(ARG_CALLBACK);
	bool modal = (argc >= ARG_MODAL) ? lua.getBool(ARG_MODAL) : false;

	return init(NULL, funcname, modal);
}

void
CKLBUITouchPad::execute(u32 /*deltaT*/)
{
	m_execount++;
	CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();

	bool bEnable = (m_modal) ? m_modalStack.isEnable() : true;
	bEnable = bEnable && !fGrp.isWorking(&m_ctrlList, this);	// locker 指定により、自分以外のロックのみを見る

	// モーダル状態と、グループによる排他制御状態で反応を返すべきか判断する
    if(!bEnable) { return; }    // どちらかにより無効にされていたら処理しない。

	CKLBTouchPadQueue& tpq = CKLBTouchPadQueue::getInstance();

	tpq.startItem();

	const PAD_ITEM * item = tpq.getItem(m_bAll);
    if(!item) { return; }       // そのフレームには通知すべきイベントがない

	// IPlatformRequest& platform = CPFInterface::getInstance().platform();

	// platform.logging("TP[%d]", m_execount);

#if defined(__CSHARP_VERSION__) || defined(__CPP_VERSION__)
	do {
		CKLBScriptEnv::getInstance().call_touchPadCSharp(this, m_execount,item->type, item->id, item->x, item->y);
		item = tpq.getItem(m_bAll);
	} while(item);
#else
	// 通知すべきイベントがあるので、Lua配列を生成する。													
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.retGlobal(m_luaFunc);
	lua.tableNew();

	int index = 1;
	do {
		// platform.logging("type[%d] id[%d] x[%d] y[%d]", item->type, item->id, item->x, item->y);

		lua.retInt(index);

		lua.tableNew();

		lua.retString("type");
		lua.retInt(item->type);
		lua.tableSet();

		lua.retString("id");
		lua.retInt(item->id);
		lua.tableSet();

		lua.retString("x");
		lua.retDouble(item->x);
		lua.tableSet();

		lua.retString("y");
		lua.retDouble(item->y);
		lua.tableSet();

		lua.tableSet();

		index++;
		item = tpq.getItem(m_bAll);
	} while(item);

	// 引数とすべき値は、すでにLuaスタックに積まれている。
	CKLBScriptEnv::getInstance().call_touchPad(m_luaFunc, this);
#endif
}

void
CKLBUITouchPad::die()
{
	CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();
	fGrp.delForm(&m_ctrlList);

    if(m_modal) { m_modalStack.remove(); }

	KLBDELETEA(m_luaFunc);
}

int
CKLBUITouchPad::commandScript(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < 2) {
		lua.retBool(false);
		return 1;
	}

	int cmd = lua.getInt(2);
	int ret = 1;
	switch(cmd)
	{
	default:
		{
			lua.retBool(false);
			ret = 1;
		}
		break;
	case UI_TOUCHPAD_SET_GROUP:
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
	case UI_TOUCHPAD_LOCK:
		{
			bool result = false;
			if(argc == 3) {
				bool lock_mode = lua.getBool(3);
				lock(lock_mode);
				result = true;
			}
			lua.retBoolean(true);
			ret = 1;
		}
		break;
	case UI_TOUCHPAD_GET_ALL:
		{
			bool result = false;
			if(argc == 3) {
				setGetAll(lua.getBool(3));
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	}
	return ret;
}
