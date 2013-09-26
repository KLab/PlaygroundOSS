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
//  CLuaState.cpp
//
#include <stdio.h>
#include "klb_vararg.h"
#include "CLuaState.h"
#include "CKLBLuaEnv.h"

CLuaState::CLuaState(lua_State * L) 
: m_L(L) 
{
}

CLuaState::~CLuaState() 
{
}

const char *
CLuaState::getScriptName()
{
    return CKLBLuaEnv::getInstance().nowFile();
}

void
CLuaState::errorMsg(const char *type_name, int argnum)
{
    char buf[128];
    sprintf(buf, "invalid argment type (arg:%d is not %s.)", argnum, type_name);
    //CKLBLuaEnv::getInstance().errMsg(buf);
    error("%s", buf);
}

bool
CLuaState::callback(const char * func, const char * argform, ...)
{
	va_list ap;
	va_start(ap, argform);
	bool result = call_luafunction(0, func, argform, ap);
	va_end(ap);
	return result;
}

bool
CLuaState::retcall(int retnum, const char * func, const char * argform, ...)
{
	va_list ap;
	va_start(ap, argform);
	bool result = call_luafunction(retnum, func, argform, ap);
	va_end(ap);
	return result;
}

bool
CLuaState::call_luafunction(int retnum, const char *func, const char *argform, va_list ap)
{
    // lua関数の名称をスタックに積む
    lua_getglobal(m_L, func);

    int count = 0;
        
    // 引数をスタックに積む
    if(argform) {
        for(const char * sp = argform; *sp; sp++) {
            switch(*sp)
            {
                case 'B': {
                    int b = va_arg(ap, int);
                    retBoolean((b) ? true : false);
                    count++;
                    break;
                }
                case 'I': {
                    int i = va_arg(ap, int);
                    retInt(i);
                    count++;
                    break;
                }
                case 'N': {
                    double d = va_arg(ap, double);
                    retDouble(d);
                    count++;
                    break;
                }
                case 'S':{
                    const char * str = va_arg(ap, const char *);
					retString(str);
                    count++;
                    break;
                }
                case 'P':{
                    void * p = va_arg(ap, void *);
                    retPointer(p);
                    count++;
                    break;
                }
                case 'G': {
                    const char * p = va_arg(ap, const char *);
                    retGlobal(p);
                    count++;
                    break;
                }
            }
        }
    }
	return call(count, func, retnum);
}

bool
CLuaState::call(int args, const char * func, int nresults)
{
    int result = lua_pcall(m_L, args, nresults, 0);
    if(result) {
    	const char * msg = NULL;
        
    	switch(result)
    	{
            default:            msg = "unknown error: %s (%s)";             break;
            case LUA_ERRRUN:    msg = "runtime error: %s (%s)";             break;
            case LUA_ERRMEM:    msg = "memory allocation error: %s (%s)";   break;
            case LUA_ERRERR:    msg = "error in error: %s (%s)";            break;
    	}
        // 呼び出しエラー: 指定の関数呼び出しに失敗
        char buf[1024];
		const char * errmsg = getString(-1);
        sprintf(buf, msg, errmsg, func);
        CKLBLuaEnv::getInstance().errMsg(buf);
		klb_assertAlways("%s", buf);
        return false;
    }
    return true;
}

int
CLuaState::error(const char * fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	char msg[1024];
	vsprintf(msg, fmt, ap);
	va_end(ap);

	return luaL_error(m_L, msg);
}
