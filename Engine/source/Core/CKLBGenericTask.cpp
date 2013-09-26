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
//  CKLBGenericTask.cpp
//  GameEngine
//
//
#include <string.h>
#include "CKLBGenericTask.h"
#include "CKLBScriptEnv.h"
#include "CKLBUtility.h"

// Command Values
enum {
	GENERIC_STOP_EXECUTE	= 0,
};

static IFactory::DEFCMD cmd[] = {
	{"GENERIC_STOP_EXECUTE",		GENERIC_STOP_EXECUTE		},

	// Enum
	{"TASK_P_MENU",		CKLBTask::P_MENU   },

	{"TASK_P_PREV",		CKLBTask::P_PREV   },
	{"TASK_P_NORMAL",	CKLBTask::P_NORMAL },
	{"TASK_P_AFTER",	CKLBTask::P_AFTER  },
	{"TASK_P_JUDGE",	CKLBTask::P_JUDGE  },
	{0, 0}
};

static CKLBTaskFactory<CKLBGenericTask> factory("TASK_Generic", CLS_KLBTASKGENERIC, cmd);

enum {
    ARGS_EXEC       = 1,
    ARGS_DIE,
    ARGS_ARRAY,

	ARGS_PHASE,
	ARGS_PARENT,

    ARGS_REQUIRE    = ARGS_ARRAY,
    ARGS_MAX        = ARGS_PARENT
};

CKLBGenericTask::CKLBGenericTask()
: CKLBLuaPropTask	()
, m_luaFuncExec		(NULL)
, m_luaFuncDie		(NULL)
, m_ArrayIndex		(NULL)
{
	m_newScriptModel = true;
}

CKLBGenericTask::~CKLBGenericTask() 
{
	KLBDELETEA(m_luaFuncExec);
    KLBDELETEA(m_luaFuncDie);
    KLBDELETEA(m_ArrayIndex);
}

bool 
CKLBGenericTask::init(CKLBTask* pTask, CKLBTask::TASK_PHASE phase, const char * name_exec, const char * name_die, const char * arr_index)
{
	m_luaFuncExec = CKLBUtility::copyString(name_exec);
	m_luaFuncDie  = CKLBUtility::copyString(name_die);
	m_ArrayIndex  = CKLBUtility::copyString(arr_index);

    if(!m_luaFuncExec || !m_luaFuncDie || !m_ArrayIndex) {
        KLBDELETEA(m_luaFuncExec);
        KLBDELETEA(m_luaFuncDie);
        KLBDELETEA(m_ArrayIndex);
        return false;
    }
    bool result = regist(pTask, phase);
    if(!result) {
        KLBDELETEA(m_luaFuncExec);
        KLBDELETEA(m_luaFuncDie);
        KLBDELETEA(m_ArrayIndex);
    }
    return result;
}

CKLBGenericTask* 
CKLBGenericTask::create(CKLBTask* pParentTask, CKLBTask::TASK_PHASE phase, const char * name_exec, const char * name_die, const char * arr_index)
{
	CKLBGenericTask* pTask = KLBNEW(CKLBGenericTask);
    if(!pTask) { return NULL; }

	if(!pTask->init(pParentTask, phase, name_exec, name_die, arr_index)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBGenericTask::initScript(CLuaState &lua)
{
	int argc = lua.numArgs();
    if(argc < ARGS_REQUIRE || argc > ARGS_MAX) {
        return false;
    }

    const char * name_exec = lua.getString(ARGS_EXEC);
    const char * name_die  = lua.getString(ARGS_DIE);
    const char * arr_index = lua.getString(ARGS_ARRAY);
	CKLBTask::TASK_PHASE phase = (CKLBTask::TASK_PHASE)((argc >= ARGS_PHASE) ? lua.getInt(ARGS_PHASE) : P_NORMAL);
	CKLBTask * pParent = (argc >= ARGS_PARENT) ? (CKLBTask *)lua.getPointer(ARGS_PARENT) : NULL;

	return init(pParent, phase, name_exec, name_die, arr_index);
}

void
CKLBGenericTask::execute(u32 deltaT)
{
	if (m_luaFuncExec) {
		CKLBScriptEnv::getInstance().call_genTaskExecute(m_luaFuncExec, this, deltaT, m_ArrayIndex);
	}
}

void
CKLBGenericTask::die()
{
	CKLBScriptEnv::getInstance().call_genTaskDie(m_luaFuncDie, this, m_ArrayIndex);

	KLBDELETEA(m_luaFuncExec); m_luaFuncExec = NULL;
    KLBDELETEA(m_luaFuncDie);  m_luaFuncDie  = NULL;
    KLBDELETEA(m_ArrayIndex);  m_ArrayIndex  = NULL;
}

int 
CKLBGenericTask::commandScript(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < 2) {
		lua.retBoolean(false);
		return 1;
	}
	int cmd = lua.getInt(2);
	int ret = 1;

	switch(cmd)
	{
	default:
		{
			lua.retBoolean(false);
			ret = 1;
		}
		break;
	case GENERIC_STOP_EXECUTE:
		{
			KLBDELETEA(m_luaFuncExec); m_luaFuncExec = NULL;
			lua.retBoolean(true);
			ret = 1;
		}
		break;
	}
	return ret;
}

u32
CKLBGenericTask::getClassID()
{
	return CLS_KLBTASKGENERIC;
}
