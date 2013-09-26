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
#include "CKLBLuaLibTASK.h"
#include "CKLBBinArray.h"
#include "CKLBLuaPropTask.h"
#include "CLuaState.h"
#include "CKLBLuaEnv.h"
;
static CKLBLuaLibTASK libdef(0);

CKLBLuaLibTASK::CKLBLuaLibTASK(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibTASK::~CKLBLuaLibTASK() {}

// Lua関数の追加
void
CKLBLuaLibTASK::addLibrary()
{
	// プロパティタスク操作
    addFunction("TASK_getProperty",		CKLBLuaLibTASK::getProperty);
    addFunction("TASK_setProperty",		CKLBLuaLibTASK::setProperty);

	// タスク破棄
	addFunction("TASK_kill",			CKLBLuaLibTASK::killTask);
	addFunction("TASK_isKilled",		CKLBLuaLibTASK::isKill);
	addFunction("TASK_registerkill",	CKLBLuaLibTASK::registerKill);

	// ステージタスク操作
    addFunction("TASK_StageOnly",		CKLBLuaLibTASK::setStageTask);
    addFunction("TASK_StageClear",		CKLBLuaLibTASK::clearStageTask);

	// タスクのpause状態設定
	addFunction("TASK_Pause",			CKLBLuaLibTASK::setPause);

	// タスクマネージャレベルでpauseをかける
	addFunction("TASK_ManagerPause",	CKLBLuaLibTASK::setManagerPause);
}

int
CKLBLuaLibTASK::getProperty(lua_State * L)
{
	CLuaState lua(L);
	if(lua.numArgs() != 1) return 0;
    if(lua.isNil(1)) return 0;

	CKLBLuaTask * pTask = (CKLBLuaTask *)lua.getPointer(1);
	if(!pTask) return 0;

	CHECKTASK(pTask);

#if defined (DEBUG_RT_CHECK)
    klb_assert(pTask->getTaskType() >= CKLBTask::TASK_LUA_PROPERTY, "SCRIPT ERROR %s(%d): the task does not have property.",
               CKLBLuaEnv::getInstance().nowFile(), lua.getNumLine());
#endif
    if(pTask->getTaskType() < CKLBTask::TASK_LUA_PROPERTY) return 0;
	return ((CKLBLuaPropTask *)pTask)->getPropertyByScript(L);
}

int
CKLBLuaLibTASK::setProperty(lua_State * L)
{
	CLuaState lua(L);
	if(lua.numArgs() != 2) return 0;
    if(lua.isNil(1)) return 0;
    
    CKLBLuaTask * pTask = (CKLBLuaTask *)lua.getPointer(1);
    if(!pTask) return 0;

	CHECKTASK(pTask);

#if defined (DEBUG_RT_CHECK)
    klb_assert(pTask->getTaskType() >= CKLBTask::TASK_LUA_PROPERTY, "SCRIPT ERROR %s(%d): the task does not have property.",
               CKLBLuaEnv::getInstance().nowFile(), lua.getNumLine());
#endif
    if(pTask->getTaskType() < CKLBTask::TASK_LUA_PROPERTY) return 0;
    return ((CKLBLuaPropTask *)pTask)->setPropertyByScript(L);    
}

int
CKLBLuaLibTASK::killTask(lua_State *L)
{
    CLuaState lua(L);
    if(lua.numArgs() != 1) return 0;
    if(!lua.isNil(1)) {
        CKLBLuaTask * pTask = (CKLBLuaTask *)lua.getPointer(1);
        if(!pTask) return 0;
		CHECKTASK(pTask);
        pTask->kill();
    }
    lua.retNil();
    return 1;
}

int
CKLBLuaLibTASK::isKill(lua_State * L)
{
	CLuaState lua(L);
	if(lua.numArgs() != 1) return 0;
	bool isRemove = true;
	if(!lua.isNil(1)) {
		CKLBLuaTask * pTask = (CKLBLuaTask *)lua.getPointer(1);
		if(!pTask) return 0;
		CHECKTASK(pTask);
		CKLBTaskMgr& mgr = CKLBTaskMgr::getInstance();
		isRemove = mgr.is_remove(pTask);
	}
	lua.retBool(isRemove);
	return 1;
}

int
CKLBLuaLibTASK::registerKill(lua_State * L)
{
	CLuaState lua(L);
	bool bResult = false;
	if(lua.numArgs() == 2) {
		CKLBLuaTask * pTask = (CKLBLuaTask *)lua.getPointer(1);
		if(!pTask) return 0;
		CHECKTASK(pTask);

		const char* cb = NULL;

		if (lua.isString(2)) {
			cb = lua.getString(2);
        }

		CKLBTaskMgr::getInstance().setCurrentTask(pTask);
		pTask->setKillCallback(cb);
		CKLBTaskMgr::getInstance().setCurrentTask(NULL);
		bResult = true;
	}
	lua.retBool(bResult);
	return 1;
}

int
CKLBLuaLibTASK::setStageTask(lua_State * L)
{
    CLuaState lua(L);
    if(lua.numArgs() != 1) return 0;
    if(lua.isNil(1)) return 0;
    CKLBLuaTask * pTask = (CKLBLuaTask *)lua.getPointer(1);
    if(!pTask) return 0;
	CHECKTASK(pTask);

	CKLBTaskMgr::getInstance().registStageTask(pTask);
    return 0;
}

int
CKLBLuaLibTASK::clearStageTask(lua_State *L)
{
    CLuaState lua(L);
    if(lua.numArgs() > 0) return 0;
    CKLBTaskMgr::getInstance().clearStageTask();
    return 0;    
}

int
CKLBLuaLibTASK::setPause(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc < 2 || argc > 3) {
		lua.retBoolean(false);
		return 1;
	}

    CKLBLuaTask * pTask = (CKLBLuaTask *)lua.getPointer(1);
    if(!pTask) return 0;
	CHECKTASK(pTask);

	bool bPause = lua.getBool(2);
	bool bRecursive = (argc >= 3) ? lua.getBool(3) : true;

	pTask->setPause(bPause, bRecursive);

	return 0;
}

int
CKLBLuaLibTASK::setManagerPause(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retBoolean(false);
		return 1;
	}
	bool bPause = lua.getBool(1);
	CKLBTaskMgr& mgr = CKLBTaskMgr::getInstance();
	mgr.setPause(bPause);

	lua.retBoolean(true);
	return 1;
}
