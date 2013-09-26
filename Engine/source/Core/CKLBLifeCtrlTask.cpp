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
#include "CKLBLifeCtrlTask.h"

enum {
	LIFECTRL_ADD_CHILD,

	LIFECTRL_TIME,
	LIFECTRL_FRAME,
};
static IFactory::DEFCMD cmd[] = {
	{ "LIFECTRL_ADD_CHILD",	LIFECTRL_ADD_CHILD },
	{ "LIFECTRL_TIME",		LIFECTRL_TIME },
	{ "LIFECTRL_FRAME",		LIFECTRL_FRAME },
	{ 0, 0 }
};

static CKLBTaskFactory<CKLBLifeCtrlTask> factory("LIFECtrl", CLS_KLBLIFECTRL, cmd);

CKLBLifeCtrlTask::CKLBLifeCtrlTask()
: CKLBLuaTask	()
, m_bLinked		(false)
, m_taskLink	(NULL) 
{
}

CKLBLifeCtrlTask::~CKLBLifeCtrlTask() 
{
}

CKLBLifeCtrlTask* 
CKLBLifeCtrlTask::create(CKLBTask* pParentTask, u32 mode, u32 limit) {
	CKLBLifeCtrlTask* pTask = KLBNEW(CKLBLifeCtrlTask);
    if(!pTask) { return NULL; }

	if(!pTask->init(pParentTask, mode, limit)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool CKLBLifeCtrlTask::init(CKLBTask* pTask, u32 mode, u32 limit) {
	m_count	= 0;
	m_mode	= mode;
	m_limit = limit;

	return regist(pTask);
}

bool
CKLBLifeCtrlTask::initScript(CLuaState& lua)
{
	return init(NULL,lua.getInt(1),lua.getInt(2));
}

int
CKLBLifeCtrlTask::commandScript(CLuaState& lua)
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
	case LIFECTRL_ADD_CHILD:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			CKLBTask * pTask = (CKLBTask *)lua.getPointer(3);
			child(pTask);	// 自身の子として登録
		}
		break;
	}
	return ret;
}


void
CKLBLifeCtrlTask::execute(u32 deltaT)
{
	switch(m_mode)
	{
	case LIFECTRL_TIME:	m_count += deltaT;	break;
	case LIFECTRL_FRAME: m_count++;			break;
	}
	// カウンタが指定されたリミットに達していたら、自殺する。
	// 自殺と同時に子として追加されていたタスクは道連れになる。
	if(m_count >= m_limit) {
		kill();
		if (m_bLinked) {
			m_taskLink->kill();
		}
	}
}

void
CKLBLifeCtrlTask::die()
{
}
