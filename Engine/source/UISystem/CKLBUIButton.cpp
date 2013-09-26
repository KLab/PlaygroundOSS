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
#include "CKLBUIButton.h"
#include "CKLBLuaEnv.h"
#include "CKLBDeviceKeyEvent.h"
#include "CKLBScriptEnv.h"

;
enum {
	UI_TOUCHPAD_SET_GROUP,
	UI_TOUCHPAD_LOCK,
	UI_TOUCHPAD_GET_ALL,
};

static IFactory::DEFCMD cmd[] = {
	{ 0, 0}
};
static CKLBTaskFactory<CKLBUIButton> factory("UI_Button", CLS_KLBUIBUTTON, cmd);

enum {
	ARG_CALLBACK = 1,

	ARG_REQUIRE = ARG_CALLBACK,
	ARG_NUMS = ARG_CALLBACK
};

CKLBUIButton::CKLBUIButton() 
: CKLBLuaTask	()
, m_luaFunc		(NULL)
, m_bAll		(false) 
{

}

CKLBUIButton::~CKLBUIButton() {}

u32
CKLBUIButton::getClassID()
{
	return CLS_KLBUIBUTTON;
}

CKLBUIButton* CKLBUIButton::create(CKLBTask* pParentTask, const char * funcName) {
	CKLBUIButton* pTask = KLBNEW(CKLBUIButton);
	if(!pTask) return 0;

	if(!pTask->init(pParentTask, funcName)) {
		KLBDELETE(pTask);
		return 0;
	}
	return pTask;
}

bool CKLBUIButton::init(CKLBTask* pTask, const char* funcname) {
	if(funcname) setStrC(m_luaFunc, funcname);

	m_ctrlList.pGroup			= NULL;
	m_ctrlList.pGrpPrev			= NULL;
	m_ctrlList.pGrpNext			= NULL;

	m_ctrlList.pBegin			= NULL;
	m_ctrlList.next				= NULL;
	m_ctrlList.bEnable			= true;
	m_ctrlList.bExclusive		= false;
	m_ctrlList.bWorking			= false;
	m_ctrlList.pCallbackIF		= NULL;
	m_ctrlList.nativeCallback	= NULL;
	m_ctrlList.pID				= NULL;

    bool result = regist(pTask, P_AFTER);
    if(!result) {
        KLBDELETEA(m_luaFunc);
    }

	m_execount = 0;
    return true;
}

bool
CKLBUIButton::initScript(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < ARG_REQUIRE || argc > ARG_NUMS) return false;

	const char * funcname = lua.getString(ARG_CALLBACK);

	return init(NULL, funcname);
}

void
CKLBUIButton::execute(u32 /*deltaT*/)
{
	m_execount++;

	CKLBDeviceKeyEventQueue& keq = CKLBDeviceKeyEventQueue::getInstance();

	keq.startItem();

	const DEVICE_KEY_ITEM * item = keq.getItem();
	if(!item) return;		// そのフレームには通知すべきイベントがない

	// IPlatformRequest& platform = CPFInterface::getInstance().platform();

	// platform.logging("TP[%d]", m_execount);

	// 通知すべきイベントがあるので、Lua配列を生成する。													
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.retGlobal(m_luaFunc);
	lua.tableNew();

	int index = 1;
	do {
		lua.retInt(index);

		lua.tableNew();

		lua.retString("type");
		lua.retInt(item->type);
		lua.tableSet();

		lua.retString("id");
		lua.retInt(item->id);
		lua.tableSet();

		lua.tableSet();

		index++;
		item = keq.getItem();
	} while(item);

	// 引数とすべき値は、すでにLuaスタックに積まれている。
	CKLBScriptEnv::getInstance().call_button(m_luaFunc, this);
}

void
CKLBUIButton::die()
{
	KLBDELETEA(m_luaFunc);
}

int
CKLBUIButton::commandScript(CLuaState& lua)
{
	lua.retBool(true);
	return 1;
}
