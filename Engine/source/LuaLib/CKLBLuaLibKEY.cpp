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
//  CKLBLuaLibKEY.cpp
//  GameEngine
//
//

#include "CKLBLuaLibKEY.h"
#include "CKLBNetAPIKeyChain.h"

static ILuaFuncLib::DEFCONST luaConst[] = {
    { 0, 0 }
};

static CKLBLuaLibKEY libdef(luaConst);

CKLBLuaLibKEY::CKLBLuaLibKEY(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibKEY::~CKLBLuaLibKEY() {}

void
CKLBLuaLibKEY::addLibrary()
{
    addFunction("KEY_genUserID",	CKLBLuaLibKEY::luaGenUserID    );
    addFunction("KEY_genUserPW",	CKLBLuaLibKEY::luaGenUserPW    );
    addFunction("KEY_setSecureID", 	CKLBLuaLibKEY::luaSetKeyChainID);
    addFunction("KEY_setSecurePW", 	CKLBLuaLibKEY::luaSetKeyChainPW);
    addFunction("KEY_getSecureID", 	CKLBLuaLibKEY::luaGetKeyChainID);
    addFunction("KEY_getSecurePW", 	CKLBLuaLibKEY::luaGetKeyChainPW);

    addFunction("KEY_delSecureID", 	CKLBLuaLibKEY::luaDelKeyChainID);
    addFunction("KEY_delSecurePW", 	CKLBLuaLibKEY::luaDelKeyChainPW);
}

int
CKLBLuaLibKEY::luaGenUserID(lua_State *L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc > 0) {
        lua.retNil();
        return 1;
    }
    char buf[1024];
    int len = genUserID(buf, 1024);
    if(!len) {
        lua.retNil();
    } else {
        lua.retString(buf);
    }
    return 1;
}

int
CKLBLuaLibKEY::luaGenUserPW(lua_State *L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc != 1) {
        lua.retNil();
        return 1;
    }
    const char * user_id = lua.getString(1);
    char buf[1024];
    int len = genUserPW(user_id, buf, 1024);
    if(!len) {
        lua.retNil();
    } else {
        lua.retString(buf);
    }
    return 1;
}

int
CKLBLuaLibKEY::luaSetKeyChainID(lua_State * L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc != 2) {
        lua.retBoolean(false);
        return 1;
    }
    const char * service_name = lua.getString(1);
    const char * user_id = lua.getString(2);
    bool result = setSecureID(service_name, user_id);
    lua.retBoolean(result);    
    return 1;
}

int
CKLBLuaLibKEY::luaSetKeyChainPW(lua_State * L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc != 2) {
        lua.retBoolean(false);
        return 1;
    }
    const char * service_name = lua.getString(1);
    const char * passwd = lua.getString(2);
    bool result = setSecurePW(service_name, passwd);
    lua.retBoolean(result);
    return 1;
}

int
CKLBLuaLibKEY::luaGetKeyChainID(lua_State * L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc != 1) {
        lua.retBoolean(false);
        return 1;
    }
    const char * service_name = lua.getString(1);
    char buf[1024];
    int len = getSecureID(service_name, buf, 1024);
    if(!len) {
        lua.retNil();
    } else {
        lua.retString(buf);
    }
    return 1;
}

int
CKLBLuaLibKEY::luaGetKeyChainPW(lua_State * L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc != 1) {
        lua.retBoolean(false);
        return 1;
    }
    const char * service_name = lua.getString(1);
    char buf[1024];
    int len = getSecurePW(service_name, buf, 1024);
    if(!len) {
        lua.retNil();
    } else {
        lua.retString(buf);
    }
    return 1;    
}

int
CKLBLuaLibKEY::luaDelKeyChainID(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();

	if(argc != 1) {
		lua.retBool(false);
		return 1;
	}

	const char * service_name = lua.getString(1);
	bool bResult = delSecureID(service_name);
	lua.retBool(bResult);
	return 1;
}

int
CKLBLuaLibKEY::luaDelKeyChainPW(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();

	if(argc != 1) {
		lua.retBool(false);
		return 1;
	}

	const char * service_name = lua.getString(1);
	bool bResult = delSecurePW(service_name);
	lua.retBool(bResult);
	return 1;
}

