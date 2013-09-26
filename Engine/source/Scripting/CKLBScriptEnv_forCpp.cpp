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
#include "CKLBScriptEnv.h"

#ifdef __CPP_VERSION__

#include "CKLBUtility.h"
#include "klb_vararg.h"
#include "CKLBScrollBarIF.h"
#include "RuntimeLibrary/CS_Object.h"
#include "RuntimeLibrary/CS_System.h"
#include "RuntimeLibrary/CS_Memory.h"
#include "callbackDef.h"
#include "CKLBGCTask.h"

/*static*/ CallbackDef::FP_V			CallbackDef::s_start					= NULL;
/*static*/ CallbackDef::FP_U			CallbackDef::s_destroyPtr				= NULL;
/*static*/ CallbackDef::FP_IIII			CallbackDef::s_worldCallBackPtr			= NULL;
/*static*/ CallbackDef::FP_U			CallbackDef::s_doCallBackPtrV			= NULL;
/*static*/ CallbackDef::FP_UII			CallbackDef::s_doCallBackPtrII			= NULL;
/*static*/ CallbackDef::FP_UIII			CallbackDef::s_doCallBackPtrIII			= NULL;
/*static*/ CallbackDef::FP_UIIII		CallbackDef::s_doCallBackPtrIIII		= NULL;
/*static*/ CallbackDef::FP_US			CallbackDef::s_doCallBackPtrS			= NULL;
/*static*/ CallbackDef::FP_USII			CallbackDef::s_doCallBackPtrSII			= NULL;
/*static*/ CallbackDef::FP_USU			CallbackDef::s_doCallBackPtrSU			= NULL;
/*static*/ CallbackDef::FP_USS			CallbackDef::s_doCallBackPtrSS			= NULL;
/*static*/ CallbackDef::FP_UUS			CallbackDef::s_doCallBackPtrUS			= NULL;
/*static*/ CallbackDef::FP_UUSS			CallbackDef::s_doCallBackPtrUSS			= NULL;
/*static*/ CallbackDef::FP_UU			CallbackDef::s_doCallBackPtrU			= NULL;
/*static*/ CallbackDef::FP_UUU			CallbackDef::s_doCallBackPtrUU			= NULL;
/*static*/ CallbackDef::FP_UUFF			CallbackDef::s_doCallBackPtrUFF			= NULL;
/*static*/ CallbackDef::FP_UUI			CallbackDef::s_doCallBackPtrUI			= NULL;
/*static*/ CallbackDef::FP_UUII			CallbackDef::s_doCallBackPtrUII			= NULL;
/*static*/ CallbackDef::FP_UUIIII		CallbackDef::s_doCallBackPtrUIIII		= NULL;
/*static*/ CallbackDef::FP_UUIIUU		CallbackDef::s_doCallBackPtrUIIUU		= NULL;
/*static*/ CallbackDef::FP_UUUII		CallbackDef::s_doCallBackPtrUUII		= NULL;
/*static*/ CallbackDef::FP_UUUUII		CallbackDef::s_doCallBackPtrUUUII		= NULL;
/*static*/ CallbackDef::FP_UIIIP_retB	CallbackDef::s_doCallBackPtrIIIP_retB	= NULL;
/*static*/ CallbackDef::FP_UFS			CallbackDef::s_doCallBackPtrFS			= NULL;

class CKLBScriptEnvCpp : public CKLBScriptEnv {
public:
	CKLBScriptEnvCpp()	{}
	~CKLBScriptEnvCpp()	{}
};

CKLBScriptEnv&	CKLBScriptEnv::getInstance() {
	static CKLBScriptEnvCpp env;
	return env;
}

CKLBScriptEnv::CKLBScriptEnv() {
}

CKLBScriptEnv::~CKLBScriptEnv() {
}

//
// CKLBScriptEnv_forCpp.cpp
//
u32 m_call				= 0;
u32 g_errorFlag			= 0;
const char* g_errorStr	= NULL;

u32* CKLBScriptEnv::getCallCounter() {
	return &m_call;
}

u32* CKLBScriptEnv::getErrorReader() {
	return &g_errorFlag;
}

const char* CKLBScriptEnv::getErrorString() {
	return g_errorStr;
}

void setError(const char* err) {
	g_errorFlag = 1;
	if (g_errorStr) {
		KLBDELETEA(g_errorStr);
		g_errorStr = NULL;
	}
	if (err) {
		g_errorStr = CKLBUtility::copyString(err);
	}
}

void CKLBScriptEnv::resetError() {
	g_errorFlag = 0;
	KLBDELETEA(g_errorStr);
	g_errorStr = NULL;
}

void CKLBScriptEnv::errMsg(const char * str) {
	error(str);
}

void CKLBScriptEnv::error(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	char msg[1024];
	vsprintf(msg, fmt, ap);
	va_end(ap);

	setError(msg);
}

bool CKLBScriptEnv::boot(const char* bootScriptURL)
{
	if(CKLBGCTask::create(15000000, 2048, 4096, 4096, 100, 1.0f, 1.0f)) {
		TRY
			System::initRuntime();
			registerWorldGC();
			CallbackDef::s_start();
		CTRY
		FIRSTCATCH(System::Exception, ex)
			DEBUG_PRINT("Exception raised during CKLBScriptEnv::boot : %s", ex->_acc_gMessage$()->_toCStr$());
			return false;
		FINALLY
		ETRY
	
		return true;
	}
	return false;
}

//Does nothing, function kept for compatibility with Lua.
bool CKLBScriptEnv::setupScriptEnv() {
	return true;
}

void CKLBScriptEnv::finishScriptEnv() {
	resetError();
}



void CKLBScriptEnv::destroy(u32 handle)
{
	TRY
		CallbackDef::s_destroyPtr(handle);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("CKLBScriptEnv::destroy raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}

void callbackV(u32 cbInfos)
{
	TRY
		CallbackDef::s_doCallBackPtrV(cbInfos);
	CTRY
	FIRSTCATCH(System::Exception, ex)
	DEBUG_PRINT("callbackV raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackII(u32 cbInfos, s32 int_1, s32 int_2)
{
	TRY
		CallbackDef::s_doCallBackPtrII(cbInfos, int_1, int_2);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackII raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackIII(u32 cbInfos, s32 int_1, s32 int_2, s32 int_3)
{
	TRY
		CallbackDef::s_doCallBackPtrIII(cbInfos, int_1, int_2, int_3);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackIII raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackIIII(u32 cbInfos, s32 int_1, s32 int_2, s32 int_3, s32 int_4)
{
	TRY
		CallbackDef::s_doCallBackPtrIIII(cbInfos, int_1, int_2, int_3, int_4);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackIIII raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackS(u32 cbInfos, const char* string_1)
{
	TRY
		CallbackDef::s_doCallBackPtrS(cbInfos, (s32*)string_1);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackS raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackSII(u32 cbInfos, const char* string_1, s32 int_1, s32 int_2)
{
	TRY
		CallbackDef::s_doCallBackPtrSII(cbInfos, (s32*)string_1, int_1, int_2);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackSII raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackSU(u32 cbInfos, const char* string_1, u32 uint_1)
{
	TRY
		CallbackDef::s_doCallBackPtrSU(cbInfos, (s32*)string_1, uint_1);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackSU raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackSS(u32 cbInfos, const char* string_1, const char* string_2)
{
	TRY
		CallbackDef::s_doCallBackPtrSS(cbInfos, (s32*)string_1, (s32*)string_2);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackSS raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackUS(u32 cbInfos, u32 uint_1, const char* string_1)
{
	TRY
		CallbackDef::s_doCallBackPtrUS(cbInfos, uint_1, (s32*)string_1);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackUS raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackUSS(u32 cbInfos, u32 uint_1, const char* string_1, const char* string_2)
{
	TRY
		CallbackDef::s_doCallBackPtrUSS(cbInfos, uint_1, (s32*)string_1, (s32*)string_2);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackUSS raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackU(u32 cbInfos, u32 uint_1)
{
	TRY
		CallbackDef::s_doCallBackPtrU(cbInfos, uint_1);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackU raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackUU(u32 cbInfos, u32 uint_1, u32 uint_2)
{
	TRY
		CallbackDef::s_doCallBackPtrUU(cbInfos, uint_1, uint_2);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackUU raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackUFF(u32 cbInfos, u32 uint_1, float float_1, float float_2)
{
	TRY
		CallbackDef::s_doCallBackPtrUFF(cbInfos, uint_1, float_1, float_2);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackUFF raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackUI(u32 cbInfos, u32 uint_1, s32 int_1)
{
	TRY
		CallbackDef::s_doCallBackPtrUI(cbInfos, uint_1, int_1);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackUI raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackUII(u32 cbInfos, u32 uint_1, s32 int_1, s32 int_2)
{
	TRY
		CallbackDef::s_doCallBackPtrUII(cbInfos, uint_1, int_1, int_2);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackUII raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackUIIII(u32 cbInfos, u32 uint_1, s32 int_1, s32 int_2, s32 int_3, s32 int_4)
{
	TRY
		CallbackDef::s_doCallBackPtrUIIII(cbInfos, uint_1, int_1, int_2, int_3, int_4);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackUIIII raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackUIIUU(u32 cbInfos, u32 uint_1, s32 int_1, s32 int_2, u32 uint_2, u32 uint_3)
{
	TRY
		CallbackDef::s_doCallBackPtrUIIUU(cbInfos, uint_1, int_1, int_2, uint_2, uint_3);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackUIIUU raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackUUII(u32 cbInfos, u32 uint_1, u32 uint_2, s32 int_1, s32 int_2)
{
	TRY
		CallbackDef::s_doCallBackPtrUUII(cbInfos, uint_1, uint_2, int_1, int_2);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackUUII raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackUUUII(u32 cbInfos, u32 uint_1, u32 uint_2, u32 uint_3, s32 int_1, s32 int_2)
{
	TRY
		CallbackDef::s_doCallBackPtrUUUII(cbInfos, uint_1, uint_2, uint_3, int_1, int_2);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackUUUII raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
bool callbackIIIP_retB(u32 cbInfos, s32 int_1, s32 int_2, s32 int_3, void* ptr_1)
{
	TRY
		return CallbackDef::s_doCallBackPtrIIIP_retB(cbInfos, int_1, int_2, int_3, (s32*)ptr_1);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackIIIP_retB raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}
void callbackFS(u32 cbInfos, float float_1, const char* string_1)
{
	TRY
		CallbackDef::s_doCallBackPtrFS(cbInfos, float_1, (s32*)string_1);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackFS raised an exception : %s", ex->_acc_gMessage$()->_toCStr$());
	FINALLY
	ETRY
}

void CKLBScriptEnv::call_onDie					(const char* funcNAme, CKLBObjectScriptable* obj)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	// This callback is stored for each C# Object with an index of 5 in the Delegate array.
	callbackV((5<<29) + objectHandle);
}

// Generic Task
void CKLBScriptEnv::call_genTaskExecute			(const char* funcName, CKLBObjectScriptable* obj, u32 deltaT, const char* arrayIndex)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackU(objectHandle, deltaT);
}

void CKLBScriptEnv::call_genTaskDie				(const char* funcName, CKLBObjectScriptable* obj, const char* arrayIndex)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	if(objectHandle != _NULLHANDLER) {
		callbackV((1<<29) + objectHandle);
	}
}

void CKLBScriptEnv::call_intervalTimerExecute	(const char* funcName, CKLBObjectScriptable* obj, u32 timerID)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	// timerID is useless for C#
	callbackV(objectHandle);
}

void CKLBScriptEnv::call_asyncLoader			(const char* funcName, CKLBObjectScriptable* obj, u32 loaded, u32 total)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackII(objectHandle, loaded, total);
}

void CKLBScriptEnv::call_asyncFileCopy			(const char* funcName, CKLBObjectScriptable* obj, u32 donePerc, u32 doneSize)
{
    m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	// TODO
}

void CKLBScriptEnv::call_webTask				(const char* funcName, CKLBObjectScriptable* obj, u32 type, const char* url)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUS(objectHandle, type, url);
}

void CKLBScriptEnv::call_pause					(const char* funcName, CKLBObjectScriptable* obj)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackV(objectHandle);
}

void CKLBScriptEnv::call_resume					(const char* funcName, CKLBObjectScriptable* obj)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackV(objectHandle);
}

void CKLBScriptEnv::call_storeEvent				(const char* funcName, CKLBObjectScriptable* obj, u32 type, const char* itemID, const char* param)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUSS(objectHandle, type, itemID, param);
}

void CKLBScriptEnv::call_fromSincVM				(const char* funcName, CKLBObjectScriptable* obj, u32 id, s32 param)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUI(objectHandle, id, param);
}

void CKLBScriptEnv::call_eventVirtualDoc		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 param1, s32 param2, s32 param3, s32 param4)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUIIII(objectHandle, type, param1, param2, param3, param4);
}

void CKLBScriptEnv::call_touchPad				(const char* funcName, CKLBObjectScriptable* obj)
{
	klb_assertAlways("Call back interface for C#");
}

void CKLBScriptEnv::call_touchPadCSharp			(CKLBObjectScriptable* obj, u32 execount, u32 type, u32 id, s32 x, s32 y)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUUUII(objectHandle, execount, type, id, x, y);
}

void CKLBScriptEnv::call_button				(const char* funcName, CKLBObjectScriptable* obj)
{
    m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	// TODO
}

void CKLBScriptEnv::call_textInput				(const char* funcName, CKLBObjectScriptable* obj, const char* txt, u32 id)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackSU(objectHandle, txt, id);
}

void CKLBScriptEnv::call_eventSelectable		(const char* funcName, CKLBObjectScriptable* obj, const char* name, s32 type, s32 param)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackSII(objectHandle, name, type, param);
}

void CKLBScriptEnv::call_eventSwf				(const char* funcName, CKLBObjectScriptable* obj, const char* label)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackS(objectHandle, label);
}

// 2 call back for list

void CKLBScriptEnv::call_eventUIListDynamic		(const char* funcName, CKLBObjectScriptable* obj, u32 index, u32 id) {
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackII((2<<29) + objectHandle, index, id);
}

void CKLBScriptEnv::call_eventUIList			(const char* funcName, CKLBObjectScriptable* obj, u32 type, u32 itemCnt, s32 listLength, s32 pos)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUUII((1<<29) + objectHandle, type, itemCnt, listLength, pos);
}

void CKLBScriptEnv::call_eventUIListDrag		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 param1, s32 param2)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUIIII(objectHandle, type, x, y, param1, param2);
}

void CKLBScriptEnv::call_eventDragIF			(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 deltaX, s32 deltaY)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUIIII(objectHandle, type, x, y, deltaX, deltaY);
}

// UI Control
// 5 call back for UI Control
void CKLBScriptEnv::call_eventUIControlDrag		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 deltaX, s32 deltaY)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUIIII(objectHandle, type, x, y, deltaX, deltaY);
}

void CKLBScriptEnv::call_eventUIControlPinch	(const char* funcName, CKLBObjectScriptable* obj, u32 type, float pinch, float rot)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUFF((1<<29) + objectHandle, type, pinch, rot);
}

void CKLBScriptEnv::call_eventUIControlClick	(const char* funcName, CKLBObjectScriptable* obj, s32 x, s32 y)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackII((2<<29) + objectHandle, x, y);
}

void CKLBScriptEnv::call_eventUIControlDblClick	(const char* funcName, CKLBObjectScriptable* obj, s32 x, s32 y)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackII((3<<29) + objectHandle, x, y);
}

void CKLBScriptEnv::call_eventUIControlLongTap	(const char* funcName, CKLBObjectScriptable* obj, u32 time, s32 x, s32 y)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUII((4<<29) + objectHandle, time, x, y);
}

// UI Drag Icon
void CKLBScriptEnv::call_eventDragIcon		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 dragX, s32 dragY)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUII(objectHandle, type, dragX, dragY);
}

// UI Movie
void CKLBScriptEnv::call_eventMovie			(const char* funcName, CKLBObjectScriptable* obj)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackV(objectHandle);
}

// UI Cell Anim
void CKLBScriptEnv::call_eventCellAnim		(const char* funcName, CKLBObjectScriptable* obj)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackV(objectHandle);
}

// UI Canvas
void CKLBScriptEnv::call_canvasOnDraw		(const char* funcName, CKLBObjectScriptable* obj)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackV(objectHandle);
}

// UI Node Pack Anim
void CKLBScriptEnv::call_eventNodeAnimPack	(const char* funcName, CKLBObjectScriptable* obj, const char * name, u32 id)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	// Special Case : owned by different classes : use 4 to avoid conflict.
	callbackSU((4<<29) + objectHandle, name, id);
}

// UI Touch Event UI
void CKLBScriptEnv::call_eventUITouchEvent	(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 dx, s32 dy)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUIIII(objectHandle, type, x, y, dx, dy);
}

// CKLBDebugMenu
void CKLBScriptEnv::call_eventDebugItem		(const char* funcName, CKLBObjectScriptable* obj, u32 id)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackU(objectHandle, id);
}

// UI Scroll Bar / UI List task
void CKLBScriptEnv::call_eventScrollBar		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 pos)
{
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUI((3<<29) + objectHandle, type, pos);
}

void CKLBScriptEnv::call_eventScrollBarStop	(const char* funcName, CKLBObjectScriptable* obj, s32 pos)
{
	if(!obj) { return; }

	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackUI((3<<29) + objectHandle, CKLBScrollBarIF::SCROLLBAR_STOPPED, pos);
}



// World Task
void CKLBScriptEnv::call_eventWorld(const char* funcName, CKLBObjectScriptable* obj, s32 serial, s32 msg, s32 status)
{
	m_call++;
	
	TRY
		// funcname is in fact an int* to the callback index.
		CallbackDef::s_worldCallBackPtr(serial, msg, status, *(int*)funcName);
	CTRY
	FIRSTCATCH(System::Exception, ex)
		DEBUG_PRINT("callbackV raised an exception.");
	FINALLY
	ETRY
}

void CKLBScriptEnv::call_eventUpdateDownload	(const char* funcName, CKLBObjectScriptable* obj, double progress, const char* progressStr) {
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackFS(objectHandle,(float)progress,progressStr);
}

void CKLBScriptEnv::call_eventUpdateZIP		(const char* funcName, CKLBObjectScriptable* obj, s32 progress, s32 total) {
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackII(objectHandle,progress,total);
}

void CKLBScriptEnv::call_eventUpdateComplete	(const char* funcName, CKLBObjectScriptable* obj) {
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackV(objectHandle);
}

void CKLBScriptEnv::call_eventUpdateError(const char* funcName, CKLBObjectScriptable* obj) {
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	// TODO
}

bool CKLBScriptEnv::call_netAPI_callback(const char* funcName, CKLBObjectScriptable* obj, s32 uniq, s32 msg, s32 status, CKLBJsonItem * pRoot) {
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	return callbackIIIP_retB(objectHandle,uniq,msg,status,pRoot);
}

void CKLBScriptEnv::call_netAPI_versionUp		(const char* funcName, CKLBObjectScriptable* obj, const char* clientVer, const char* serverVer) {
	m_call++;
	u32 objectHandle = obj->getScriptHandle();
	klb_assert(objectHandle != _NULLHANDLER,"ScriptHandle is null");
	callbackSS((1<<29) + objectHandle,clientVer,serverVer);
}

#endif
