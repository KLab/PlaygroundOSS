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
//  CKLBLuaEnv.h
//

#ifndef CKLBLuaEnv_h
#define CKLBLuaEnv_h

#include "lua.hpp"
#include "CLuaState.h"
#include "CPFInterface.h"


class CKLBLuaEnv
{
private:
    CKLBLuaEnv();
    ~CKLBLuaEnv();
    
public:
    static CKLBLuaEnv& getInstance();
    
    bool setupLuaEnv		();
    void finishLuaEnv		();

	// 定数定義を動作中に行う
	bool defineInt			(const char * defName, int value);
	bool defineNum			(const char * defName, float value);
	bool defineString		(const char * defName, const char * string);

    bool loadScript			(const char * scriptName);
    void execScript			(int deltaT);

	bool sysLoad			(const char * script_name);
	bool intoMaintenance	();
	bool exitMaintenance	();

    void errMsg				(const char * str);
    
    static int load			(lua_State * L);
    static int isLoading	(lua_State * L);
    static int command		(lua_State * L);
    static int logging		(lua_State * L);
    static int exitGame		(lua_State * L);
	static int includefile	(lua_State * L);
    static int systemInfo	(lua_State * L);
	static int reboot		(lua_State * L);
	static int setGCRatio	(lua_State * L);

	// Script additional operator functions.
    static int bitOR		(lua_State * L);
    static int bitAND		(lua_State * L);

    inline const char * nowFile	() const { return m_nowFile; }

	inline CLuaState&	getState() const { return *m_state; }

	static void cmdLogging		(const char* msg);
	static void cmdExit			();
	static void cmdSystemInfo	(int* width, int* height);

private:
	static IReadStream * openScript(const char * scriptUrl);

	u32				m_lowGC;
	u32				m_highGC;
	u32				m_collect;

    lua_State   *   m_L;
	CLuaState	*	m_state;
    const char  *   m_nowFile;

	bool			m_leave;
	bool			m_sysLoadEnable;
    
    bool            m_bLoadScript;
    const char  *   m_nextLoadScript;
	int				m_loadReserveFrame;

};

#endif
