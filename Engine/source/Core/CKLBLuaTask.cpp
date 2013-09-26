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
//
//  CKLBLuaTask.cpp
//

#include "CKLBLuaTask.h"

CKLBLuaTask::CKLBLuaTask() 
: CKLBTask      ()
, m_cbFuncName	(NULL)
{
}

CKLBLuaTask::~CKLBLuaTask() {
	setKillCallback(NULL);	// Free string.
}

CKLBTask::TASKTYPE
CKLBLuaTask::getTaskType()
{
    return TASK_LUA_BASIC;
}

int
CKLBLuaTask::commandScript(CLuaState& /*lua*/)
{
    return 0;
}

void 
CKLBLuaTask::setKillCallback(const char* cbFuncName) {
	KLBDELETEA(m_cbFuncName);
	if (cbFuncName) {
		m_cbFuncName = CKLBUtility::copyString(cbFuncName);
	} else {
		m_cbFuncName = NULL;
	}
}

void 
CKLBLuaTask::performKillCallback() {
	if (m_cbFuncName) {
		CKLBScriptEnv::getInstance().call_onDie(m_cbFuncName, this);
		KLBDELETEA(m_cbFuncName);
		m_cbFuncName = NULL;
	}
}


IFactory * IFactory::m_begin = NULL;

IFactory::IFactory () {}
IFactory::~IFactory() {}

void
IFactory::addLink(const char * luaFuncName, int (*luaFunc)(lua_State * L), DEFCMD * arrCmdItem, u32 classID) {
    m_funcName      = luaFuncName;
    m_luaFunc       = luaFunc;
    m_arrCmdItem    = arrCmdItem;
    m_classID       = classID;
    m_pNext         = m_begin;
    m_begin         = this;
}

u32 
IFactory::getClassID(const char* luaFuncName, bool assertIfNotFound) {
	IFactory* pFactory = m_begin;
	while (pFactory) {
		if (strcmp(pFactory->m_funcName,luaFuncName)==0) {
			return pFactory->m_classID;
		}
		pFactory = pFactory->m_pNext;
	}

	klb_assert(!assertIfNotFound, "Can not find class ID from name %s", luaFuncName);
	return 0;
}

const char* 
IFactory::getClassName(u32 classID) {
	IFactory* pFactory = m_begin;
	while (pFactory) {
		if (pFactory->m_classID == classID) {
			return pFactory->m_funcName;
		}
		pFactory = pFactory->m_pNext;
	}

	// klb_assertAlways("Can not find name from class ID %8x", classID);
	return NULL;
}

bool
IFactory::registLuaFunctions(lua_State *L)
{
    IFactory * pFactory = m_begin;
	IPlatformRequest& pfif = CPFInterface::getInstance().platform();
	pfif.logging("<<<supported task list>>>");
    while(pFactory) {
		// 生成用関数を指定の名称で登録する。
        lua_register(L, pFactory->m_funcName, pFactory->m_luaFunc);
		pfif.logging("  [task] %s", pFactory->m_funcName);

		// 指定されたコマンド値を、指定された名称で登録する
		for(const DEFCMD * pCmd = pFactory->m_arrCmdItem; pCmd && pCmd->name ; pCmd++) {
			// 指定された名称のグローバルラベルがすでに存在していればエラーを出す。
			lua_getglobal(L, pCmd->name);
			if(!lua_isnil(L, -1)) {
				lua_pop(L, 1);
				// 指定されたグローバルラベルがnilではないということは、
				// 同名で値が定義済みであるため、エラーを出す。
				pfif.logging("[TASK REGISTRATION ERROR] %s it is redefined.\n", pCmd->name);
				continue;
			}
			lua_pop(L, 1);
			lua_pushinteger(L, pCmd->cmd);
			lua_setglobal(L, pCmd->name);
			pfif.logging("\t\t[def] %s = %d", pCmd->name, pCmd->cmd);
		}
        pFactory = pFactory->m_pNext;
    }
    return true;
}

bool
CKLBLuaTask::setStrC(const char*& dst, const char * val)
{
	const char * str;
	if (val) {
		str = CKLBUtility::copyString(val);
        if (!str) { return false; }
        if (dst)  { KLBDELETEA(dst); }
	} else {
		str = NULL;
	}
	dst = str;
	return true;
}
