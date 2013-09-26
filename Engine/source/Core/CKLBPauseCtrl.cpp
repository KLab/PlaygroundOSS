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
#include "CKLBPauseCtrl.h"
#include "CKLBUtility.h"
#include "CKLBOSCtrlEvent.h"
#include "CPFInterface.h"
#include "CKLBScriptEnv.h"

static CKLBTaskFactory<CKLBPauseCtrl> factory("PAUSECtrl", CLS_KLBPAUSECTRL);

CKLBPauseCtrl::CKLBPauseCtrl()
: CKLBLuaTask() 
{
}

CKLBPauseCtrl::~CKLBPauseCtrl() 
{
}

CKLBPauseCtrl* 
CKLBPauseCtrl::create(CKLBTask* pParentTask, const char* pause, const char* resume) {
	CKLBPauseCtrl* pTask = KLBNEW(CKLBPauseCtrl);
    if(!pTask) { return NULL; }

	if(!pTask->init(pParentTask, pause,resume)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool CKLBPauseCtrl::init(CKLBTask* pTask, const char* pause, const char* resume) {
	m_callbackPause  = (pause)  ? CKLBUtility::copyString(pause)  : NULL;
	m_callbackResume = (resume) ? CKLBUtility::copyString(resume) : NULL;

	return regist(pTask, P_NORMAL);
}

bool
CKLBPauseCtrl::initScript(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc != 2) {
		return false;
	}
	const char * pause  = (lua.isNil(1)) ? NULL : lua.getString(1);
	const char * resume = (lua.isNil(2)) ? NULL : lua.getString(2);
	
	return init(NULL, pause, resume);
}

void
CKLBPauseCtrl::die()
{
	KLBDELETEA(m_callbackPause);
	KLBDELETEA(m_callbackResume);
}

void
CKLBPauseCtrl::execute(u32 /*deltaT*/)
{
	CKLBOSCtrlQueue& osq = CKLBOSCtrlQueue::getInstance();
	const OSCTRL *  item = NULL;
	osq.startItem();

	while(NULL != (item = osq.getItem(0))) {
		switch(item->type)
		{
		default: break;
		case IClientRequest::E_PAUSE:	if(m_callbackPause)		CKLBScriptEnv::getInstance().call_pause	(m_callbackPause,  this);	break;
		case IClientRequest::E_RESUME:	if(m_callbackResume)	CKLBScriptEnv::getInstance().call_resume(m_callbackResume, this);	break;
		}
	}
}
