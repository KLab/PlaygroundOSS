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
#ifndef __SCRIPT_ENV_
#define __SCRIPT_ENV_

#include "CKLBObject.h"

class CKLBJsonItem;	// Ptr Param for callback.

class CKLBScriptEnv
{
protected:
    CKLBScriptEnv();
    ~CKLBScriptEnv();

public:
    static CKLBScriptEnv& getInstance();
    
	u32*			getCallCounter	();
	u32*			getErrorReader	();
	const char*		getErrorString	();
	void			resetError		();

	bool boot			(const char* bootScriptURL);
    bool setupScriptEnv	();
    void finishScriptEnv();

    void error			(const char * str, ...);
	void errMsg			(const char* str);
public:
	void destroy					(unsigned int handle);

	void call_onDie					(const char* funcNAme, CKLBObjectScriptable* obj);

	// Generic Task
	void call_genTaskExecute		(const char* funcName, CKLBObjectScriptable* obj, u32 deltaT, const char* arrayIndex);
	void call_genTaskDie			(const char* funcName, CKLBObjectScriptable* obj, const char* arrayIndex);

	// Timer Task
	void call_intervalTimerExecute	(const char* funcName, CKLBObjectScriptable* obj, u32 timerID);

	void call_asyncFileCopy			(const char* funcName, CKLBObjectScriptable* obj, u32 perc, u32 size);
	void call_asyncLoader			(const char* funcName, CKLBObjectScriptable* obj, u32 loaded, u32 total);

	// Web Area Task
	void call_webTask				(const char* funcName, CKLBObjectScriptable* obj, u32 type, const char* url);

	// CKLBPauseCtrl
	void call_pause					(const char* funcName, CKLBObjectScriptable* obj);
	void call_resume				(const char* funcName, CKLBObjectScriptable* obj);

	// CKLBStoreService
	void call_storeEvent			(const char* funcName, CKLBObjectScriptable* obj, u32 type, const char* itemID, const char* param2);
	
	// Sinc VM for Unit
	void call_fromSincVM			(const char* funcName, CKLBObjectScriptable* obj, u32 id, s32 param);
	
	// Virtual Doc
	void call_eventVirtualDoc		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 param1, s32 param2, s32 param3, s32 param4);
	
	// Touch Pad
	void call_touchPadCSharp		(CKLBObjectScriptable* obj, u32 m_execount, u32 type, u32 id, s32 x, s32 y);
	void call_touchPad				(const char* funcName, CKLBObjectScriptable* obj);
	
	// Device buttons
	void call_button				(const char* funcName, CKLBObjectScriptable* obj);

	// CKLBUITextInput
	void call_textInput				(const char* funcName, CKLBObjectScriptable* obj, const char* txt, u32 id);
	
	// Selectable Element
	void call_eventSelectable		(const char* funcName, CKLBObjectScriptable* obj, const char* name, s32 type, s32 param);
	
	// Swf Player
	void call_eventSwf				(const char* funcName, CKLBObjectScriptable* obj, const char* label);
	// UI List
	void call_eventUIListDynamic	(const char* funcName, CKLBObjectScriptable* obj, u32 type, u32 itemID);
	void call_eventUIList			(const char* funcName, CKLBObjectScriptable* obj, u32 type, u32 itemCnt, s32 listLength, s32 pos);
	// TODO : pb with NULL funcName != behavior before call.
	void call_eventUIListDrag		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 param1, s32 param2);

	// UI Control
	void call_eventDragIF			(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 deltaX, s32 deltaY);
	void call_eventUIControlDrag	(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 deltaX, s32 deltaY);
	void call_eventUIControlPinch	(const char* funcName, CKLBObjectScriptable* obj, u32 type, float pinch, float rot);
	void call_eventUIControlClick	(const char* funcName, CKLBObjectScriptable* obj, s32 x, s32 y);
	void call_eventUIControlDblClick(const char* funcName, CKLBObjectScriptable* obj, s32 x, s32 y);
	void call_eventUIControlLongTap	(const char* funcName, CKLBObjectScriptable* obj,  u32 time, s32 x, s32 y);
	
	// UI Drag Icon
	void call_eventDragIcon			(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 dragX, s32 dragY);
	
	// UI Movie
	void call_eventMovie			(const char* funcName, CKLBObjectScriptable* obj);

	// UI Cell Anim
	void call_eventCellAnim			(const char* funcName, CKLBObjectScriptable* obj);
	
	// UI Canvas
	void call_canvasOnDraw			(const char* funcName, CKLBObjectScriptable* obj);

	// UI Node Pack Anim
	void call_eventNodeAnimPack		(const char* funcName, CKLBObjectScriptable* obj, const char * name, u32 id);
	
	// UI Touch Event UI
	void call_eventUITouchEvent		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 x, s32 y, s32 dx, s32 dy);

	// CKLBDebugMenu
	void call_eventDebugItem		(const char* funcName, CKLBObjectScriptable* obj, u32 id);
	
	// UI Scroll Bar / UI List task
	void call_eventScrollBar		(const char* funcName, CKLBObjectScriptable* obj, u32 type, s32 pos);
	void call_eventScrollBarStop	(const char* funcName, CKLBObjectScriptable* obj, s32 pos);

	// World Task
	void call_eventWorld			(const char* funcName, CKLBObjectScriptable* obj, s32 serial, s32 msg, s32 status);

	void call_eventUpdateDownload	(const char* funcName, CKLBObjectScriptable* obj, double progress, const char* progressStr);
	void call_eventUpdateZIP		(const char* funcName, CKLBObjectScriptable* obj, int progress, int total);
	void call_eventUpdateComplete	(const char* funcName, CKLBObjectScriptable* obj);
	void call_eventUpdateError		(const char* funcName, CKLBObjectScriptable* obj);

	// NetAPI
	bool call_netAPI_callback		(const char* funcName, CKLBObjectScriptable* obj, int uniq, int msg, int status, CKLBJsonItem * pRoot);
	void call_netAPI_versionUp		(const char* funcName, CKLBObjectScriptable* obj, const char* clientVer, const char* serverVer);

};

#endif
