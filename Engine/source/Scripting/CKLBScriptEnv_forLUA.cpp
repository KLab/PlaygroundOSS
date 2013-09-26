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

#ifndef __CSHARP_VERSION__
#ifndef __CPP_VERSION__

#include "CKLBUtility.h"
#include "CKLBLuaEnv.h"
#include "klb_vararg.h"
#include "CLuaState.h"
#include "CKLBLuaScript.h"

CKLBScriptEnv::CKLBScriptEnv() {
}

CKLBScriptEnv::~CKLBScriptEnv() {
}

CKLBScriptEnv&	CKLBScriptEnv::getInstance() {
	static CKLBScriptEnv env;
	return env;
}

//
// CKLBScriptEnv_forLUA.cpp
//	

u32* CKLBScriptEnv::getCallCounter()
{
	return NULL;
}

u32* CKLBScriptEnv::getErrorReader() 
{
	return NULL;
}

const char* CKLBScriptEnv::getErrorString()
{
	return NULL;
}

void CKLBScriptEnv::resetError()
{
}

bool CKLBScriptEnv::boot(const char* bootScriptURL)
{
	return CKLBLuaScript::create(bootScriptURL) != NULL;
}

bool CKLBScriptEnv::setupScriptEnv() {
	// ::boot already do the call to setupLuaEnv
	// Nothing do to here !
	// Never do CKLBLuaEnv::getInstance().setupLuaEnv();
	return true;
}

void CKLBScriptEnv::finishScriptEnv() {
	// 
	// TODO possibe : CKLBLuaEnv::getInstance().finishLuaEnv();
	// and remove direct call from GameApplication class.
}

void CKLBScriptEnv::errMsg(const char * str) {
	CKLBLuaEnv::getInstance().errMsg(str);
}

void CKLBScriptEnv::error(const char* fmt,...) {
	va_list ap;
	va_start(ap, fmt);
	char msg[1024];
	vsprintf(msg, fmt, ap);
	va_end(ap);

	CKLBLuaEnv::getInstance().getState().error(msg);
}

void CKLBScriptEnv::destroy(unsigned int /*handle*/)	// Does nothing, only used in C#
{
}

void CKLBScriptEnv::call_onDie					(const char* funcName, CKLBObjectScriptable* obj)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"P",obj);
}

// Generic Task
void CKLBScriptEnv::call_genTaskExecute			(const char* funcName, CKLBObjectScriptable* obj, u32 deltaT, const char* arrayIndex)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PIS",obj,deltaT, arrayIndex);
}

void CKLBScriptEnv::call_genTaskDie				(const char* funcName, CKLBObjectScriptable* obj, const char* arrayIndex)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PS",obj,arrayIndex);
}

void CKLBScriptEnv::call_intervalTimerExecute	(const char* funcName, CKLBObjectScriptable* /*obj*/, u32 timerID)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"I",timerID);
}

void CKLBScriptEnv::call_asyncLoader			(const char* funcName, CKLBObjectScriptable* /*obj*/, u32 loaded, u32 total)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"II",loaded,total);
}

void CKLBScriptEnv::call_asyncFileCopy			(const char* funcName, CKLBObjectScriptable* obj, u32 donePerc, u32 doneSize)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PII",obj,donePerc,doneSize);
}

void CKLBScriptEnv::call_webTask				(const char* funcName, CKLBObjectScriptable* obj, u32 type,const char* url)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PIS",obj,type,url);
}

void CKLBScriptEnv::call_pause					(const char* funcName, CKLBObjectScriptable* /*obj*/)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"");
}

void CKLBScriptEnv::call_resume					(const char* funcName, CKLBObjectScriptable* /*obj*/)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"");
}

void CKLBScriptEnv::call_storeEvent				(const char* funcName, CKLBObjectScriptable* obj, u32 type, const char* itemID, const char* param)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PISS",obj,type,itemID, param);
}

void CKLBScriptEnv::call_fromSincVM				(const char* funcName, CKLBObjectScriptable* obj, u32 id, s32 param)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PII",obj,id,param);
}

void CKLBScriptEnv::call_eventVirtualDoc		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 param1, s32 param2, s32 param3, s32 param4)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PIIIII",obj,type,param1,param2,param3,param4);
}

void CKLBScriptEnv::call_touchPad				(const char* funcName, CKLBObjectScriptable* /*obj*/)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.call(1, funcName);
}

void CKLBScriptEnv::call_touchPadCSharp(CKLBObjectScriptable* /*obj*/, u32 /*m_execount*/, u32 /*type*/, u32 /*id*/, s32 /*x*/, s32 /*y*/)
{
	klb_assertAlways("Call back interface for C#");
}

void CKLBScriptEnv::call_button				(const char* funcName, CKLBObjectScriptable* obj)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.call(1, funcName);
}

void CKLBScriptEnv::call_textInput				(const char* funcName, CKLBObjectScriptable* obj, const char* txt, u32 id)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PSI",obj,txt,id);
}

void CKLBScriptEnv::call_eventSelectable		(const char* funcName, CKLBObjectScriptable* /*obj*/, const char* name, s32 type, s32 param)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"SII",name,type,param);
}
void CKLBScriptEnv::call_eventSwf				(const char* funcName, CKLBObjectScriptable* obj, const char* label)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PS",obj,label);
}

void CKLBScriptEnv::call_eventUIListDynamic		(const char* funcName, CKLBObjectScriptable* obj, u32 index, u32 id) {
	if (!funcName) { return; } 
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName, "PII", obj, index, id);
}

void CKLBScriptEnv::call_eventUIList			(const char* funcName, CKLBObjectScriptable* obj, u32 type, u32 itemCnt, s32 listLength, s32 pos)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PIIII",obj,type,itemCnt,listLength,pos);
}

void CKLBScriptEnv::call_eventUIListDrag		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 param1, s32 param2)
{
	klb_assertAlways("Unused");

	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PIIIII",obj,type,x,y,param1,param2);
}

// UI Control
void CKLBScriptEnv::call_eventUIControlDrag		(const char* funcName, CKLBObjectScriptable* /*obj*/, u32 type, s32 x, s32 y, s32 deltaX, s32 deltaY)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"IIIII",type,x,y,deltaX,deltaY);
}

void CKLBScriptEnv::call_eventDragIF			(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 deltaX, s32 deltaY)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PIIIII",obj,type,x,y,deltaX,deltaY);
}

void CKLBScriptEnv::call_eventUIControlPinch	(const char* funcName, CKLBObjectScriptable* /*obj*/, u32 type, float pinch, float rot)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"INN",type,pinch,rot);
}

void CKLBScriptEnv::call_eventUIControlClick	(const char* funcName, CKLBObjectScriptable* /*obj*/, s32 x, s32 y)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"II",x,y);
}

void CKLBScriptEnv::call_eventUIControlDblClick	(const char* funcName, CKLBObjectScriptable* /*obj*/, s32 x, s32 y)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"II",x,y);
}

void CKLBScriptEnv::call_eventUIControlLongTap	(const char* funcName, CKLBObjectScriptable* /*obj*/, u32 time, s32 x, s32 y)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"III",time,x,y);
}

// UI Drag Icon
void CKLBScriptEnv::call_eventDragIcon		(const char* funcName, CKLBObjectScriptable* /*obj*/, u32 type, s32 dragX, s32 dragY)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"III",type,dragX,dragY);
}

// UI Movie
void CKLBScriptEnv::call_eventMovie			(const char* funcName, CKLBObjectScriptable* obj)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"P",obj);
}

// UI Cell Anim
void CKLBScriptEnv::call_eventCellAnim		(const char* funcName, CKLBObjectScriptable* /*obj*/)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"");
}

// UI Canvas
void CKLBScriptEnv::call_canvasOnDraw		(const char* funcName, CKLBObjectScriptable* obj)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"P",obj);
}

// UI Node Pack Anim
void CKLBScriptEnv::call_eventNodeAnimPack	(const char* funcName, CKLBObjectScriptable* obj, const char * name, u32 id)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PSI",obj,name,id);
}

// UI Touch Event UI
void CKLBScriptEnv::call_eventUITouchEvent	(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 dx, s32 dy)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PIIIII",obj,type,x,y,dx,dy);
}

// CKLBDebugMenu
void CKLBScriptEnv::call_eventDebugItem		(const char* funcName, CKLBObjectScriptable* obj, u32 id)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PI",obj,id);
}

// UI Scroll Bar / UI List task
void CKLBScriptEnv::call_eventScrollBar		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 pos)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PII",obj,type,pos);
}

void CKLBScriptEnv::call_eventScrollBarStop	(const char* funcName, CKLBObjectScriptable* obj, s32 pos) {
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PI",obj,pos);
}

// World Task
void CKLBScriptEnv::call_eventWorld			(const char* funcName, CKLBObjectScriptable* /*obj*/, s32 serial, s32 msg, s32 status)
{
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"III",serial,msg,status);
}

void CKLBScriptEnv::call_eventUpdateDownload(const char* funcName, CKLBObjectScriptable* obj, double progress, const char* progressStr) {
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName,"PNS",obj,progress,progressStr);
}

void CKLBScriptEnv::call_eventUpdateZIP		(const char* funcName, CKLBObjectScriptable* obj, int progress, int total) {
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName, "PII", obj, progress, total);
}

void CKLBScriptEnv::call_eventUpdateComplete(const char* funcName, CKLBObjectScriptable* obj) {
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName, "P", obj);
}

void CKLBScriptEnv::call_eventUpdateError(const char* funcName, CKLBObjectScriptable* obj) {
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName, "P", obj);
}

bool CKLBScriptEnv::call_netAPI_callback(const char* funcName, CKLBObjectScriptable* /*obj*/, int uniq, int msg, int status, CKLBJsonItem * pRoot) {
	if(!funcName) return false;

	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.getGlobal(funcName);
	lua.retInt(uniq);
	lua.retInt(msg);
	lua.retInt(status);
	if(pRoot) {
		CKLBUtility::jsonItem2lua(lua, pRoot);
	} else {
		lua.retNil();
	}
	return lua.call(4, funcName);
}

void CKLBScriptEnv::call_netAPI_versionUp		(const char* funcName, CKLBObjectScriptable* obj, const char* clientVer, const char* serverVer) {
	if (!funcName) { return; }
	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	lua.callback(funcName, "PSS", obj, clientVer, serverVer);
}

#endif
#endif
