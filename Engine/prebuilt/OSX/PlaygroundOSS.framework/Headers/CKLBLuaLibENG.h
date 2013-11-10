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
#ifndef CKLBLuaLibENG_h
#define CKLBLuaLibENG_h

#include "ILuaFuncLib.h"
#include "CPFInterface.h"
#include "CKLBTask.h"

class CKLBLuaLibENG : public ILuaFuncLib
{
private:
	CKLBLuaLibENG();
public:
	CKLBLuaLibENG(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibENG();

	void addLibrary();

	static bool			isRelease		();
	static const char*	getPlatform		();
	static void			getNanoTime		(s32* milli, s32* nano);
	static void			startNanoTime	(int idx);
	static void			endNanoTime		(int idx, s32* milli, s32* nano);
	inline
	static u32			getFrameID		() {
		CKLBTaskMgr& mgr = CKLBTaskMgr::getInstance();
		return mgr.getFrameID();
	}


private:
    static int luaGetAppVersion (lua_State * L);
	static int luaGetPlatform	(lua_State * L);
	static int luaIsRelease		(lua_State * L);
	static int luaGetNanoTime	(lua_State * L);
	static int luaStartNanoTime	(lua_State * L);
	static int luaEndNanoTime	(lua_State * L);
	static int luaGetFrameID	(lua_State * L);
    static int luaGetElapsedTime(lua_State * L);
    static int luaForbidSleep   (lua_State * L);
	enum {
		SCRIPT_TIMER_COUNT = 10,
	};

	static s64  ms_timers[SCRIPT_TIMER_COUNT];
};

#endif // CKLBLuaLibENG_h
