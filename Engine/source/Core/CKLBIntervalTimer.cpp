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
#include "CKLBIntervalTimer.h"
#include "CKLBScriptEnv.h"
;

enum {
	INTERVALTIMER_TIME = 0,
	INTERVALTIMER_FRAME
};

static CKLBTaskFactory<CKLBIntervalTimer> factory("UTIL_IntervalTimer", CLS_KLBINTERVALTIMER);

CKLBIntervalTimer::CKLBIntervalTimer() 
:CKLBLuaPropTask	()
,m_callback			(NULL) 
{
	m_newScriptModel = true;
}

CKLBIntervalTimer::~CKLBIntervalTimer() {}

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBIntervalTimer::ms_propItems[] = {
	{	"timer_id",		UINTEGER,	(setBoolT)&CKLBIntervalTimer::setTimerID,	(getBoolT)&CKLBIntervalTimer::getTimerID,	0	},
	{	"interval",		UINTEGER,	(setBoolT)&CKLBIntervalTimer::setInterval,	(getBoolT)&CKLBIntervalTimer::getInterval,	0	},
	{	"is_repeating",	BOOLEANT,	(setBoolT)&CKLBIntervalTimer::setRepeat,	(getBoolT)&CKLBIntervalTimer::getRepeat,	0	}
};

enum {
	ARG_TIMER_ID = 1,	// callbackの引数に与えらえるタイマーID
	ARG_CALLBACK,		// callbackに使用する関数名称
	ARG_INTERVAL,		// 起動後にcallbackを呼ぶまでの時間(ミリ秒)
	ARG_REPEAT,			// デフォルトではfalse
						// falseでは一回callbackを呼び出した後、タスクは自殺する。
						// true の場合、ARG_INTERVAL間隔でcallbackを呼び出す。
	ARG_PARENT,
	ARG_REQUIRE = ARG_INTERVAL,	
	ARG_NUMS    = ARG_PARENT
};

u32
CKLBIntervalTimer::getClassID()
{
	return CLS_KLBINTERVALTIMER;
}

CKLBIntervalTimer*
CKLBIntervalTimer::create(CKLBTask* pParentTask, u32 timerID, u32 interval, bool repeat, const char* callback, u8 mode, bool killIfUpdate) {
	CKLBIntervalTimer* pTask = KLBNEW(CKLBIntervalTimer);
    if(!pTask) { return NULL; }

	if(!pTask->init(pParentTask, timerID, interval, repeat, callback, mode, killIfUpdate)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBIntervalTimer::init(CKLBTask* pTask, u32 timerID, u32 interval, bool repeat, const char* callback, u8 mode, bool killIfUpdate) {
	setStrC(m_callback,callback);

	if(!m_callback) return false;

	// Properties definition
	if(!setupPropertyList((const char**)CKLBIntervalTimer::ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	// 引数取り込み
	setTimerID	(timerID);
	setInterval	(interval);
	setRepeat	(repeat);
	m_mode			= mode;
	m_killIfUpdate	= killIfUpdate;

	m_countup = 0;

	return regist(pTask, P_UIPREV);
}

bool
CKLBIntervalTimer::initScript(CLuaState& lua)
{
	int argc = lua.numArgs();

    if(argc < ARG_REQUIRE || argc > ARG_NUMS) { return false; }

	const char * callback = lua.getString(ARG_CALLBACK);
	bool b_repeat = (argc >= ARG_REPEAT) ? lua.getBool(ARG_REPEAT) : false;
	CKLBTask* pParent = NULL;
	if (argc >= ARG_PARENT) { pParent = (CKLBTask*)lua.getPointer(ARG_PARENT); }
	return init(pParent, lua.getInt(ARG_TIMER_ID),lua.getInt(ARG_INTERVAL), b_repeat, callback, INTERVALTIMER_TIME, true);
}

void
CKLBIntervalTimer::die()
{
	KLBDELETEA(m_callback);
}

void
CKLBIntervalTimer::execute(u32 deltaT)
{
	switch(m_mode) {
		case INTERVALTIMER_TIME	: m_countup += deltaT;	break;
		case INTERVALTIMER_FRAME: m_countup++;			break;
	}
	
	if(m_countup >= m_interval) {
		m_countup -= m_interval;
		u32 oldCountUp = m_countup;

		CKLBScriptEnv::getInstance().call_intervalTimerExecute(m_callback, this, m_timerID);

		// REPEATがfalseであれば、callbackを呼んだ後に自殺する。
		if(!m_repeat) {
			if(m_killIfUpdate) {
				kill();
			} else {
				if(oldCountUp == m_countup) {
					kill();
				}
			}
        }
	}
}

