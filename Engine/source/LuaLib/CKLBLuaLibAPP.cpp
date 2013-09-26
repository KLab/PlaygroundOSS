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
#include "CKLBLuaLibAPP.h"

;
static ILuaFuncLib::DEFCONST luaConst[] = {
	{ "APP_MAIL",		IPlatformRequest::APP_MAIL },		// 各環境のメールアプリ
	{ "APP_BROWSER",	IPlatformRequest::APP_BROWSER },	// 各環境のブラウザアプリ
	{ "APP_UPDATE",		IPlatformRequest::APP_UPDATE },		// 各環境のアップデートアプリ
	{ 0, 0 }
};

static CKLBLuaLibAPP libdef(luaConst);

CKLBLuaLibAPP::CKLBLuaLibAPP(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibAPP::~CKLBLuaLibAPP() {}

// Lua関数の追加
void
CKLBLuaLibAPP::addLibrary()
{
	addFunction("APP_CallApplication",		CKLBLuaLibAPP::luaCallApplication);
	addFunction("APP_GetPhysicalMem",		CKLBLuaLibAPP::luaGetPhysicalMem);
}

int
CKLBLuaLibAPP::luaGetPhysicalMem(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();

	u32 value = CPFInterface::getInstance().platform().getPhysicalMemKB();
	if (value >= 0x1000000) {
		// 24 bit significant.
		value = 0xFFFFFF;
	}
	lua.retInt(value);
	return 1;
}

int
CKLBLuaLibAPP::luaCallApplication(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc < 1) {
		lua.retBoolean(false);
		return 1;
	}

	bool result = false;
	IPlatformRequest::APP_TYPE type = (IPlatformRequest::APP_TYPE)lua.getInt(1);
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();

	switch(type)
	{
	case IPlatformRequest::APP_MAIL:
		{
			const char * addr = (lua.isNil(2)) ? "" : lua.getString(2);
			const char * subject = (lua.isNil(3)) ? "" : lua.getString(3);
			const char * body = (lua.isNil(4)) ? "" : lua.getString(4);

			result = pForm.callApplication(type, addr, subject, body);
		}
		break;
	case IPlatformRequest::APP_BROWSER:
		{
			const char * url = (lua.isNil(2)) ? "" : lua.getString(2);

			result = pForm.callApplication(type, url);
		}
		break;
	case IPlatformRequest::APP_UPDATE:
		{
			const char * search_key = (argc >= 2 && !lua.isNil(2)) ? lua.getString(2) : "";
			result = pForm.callApplication(type, search_key);
		}
		break;
	default:
		break;
	}
	lua.retBoolean(result);
	return 1;
}

// For C#
bool CKLBLuaLibAPP::callApplication(IPlatformRequest::APP_TYPE type, const char* addr, const char* subject, const char* body)
{
	bool result = false;
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();

	switch(type)
	{
	case IPlatformRequest::APP_MAIL:
		{
			result = pForm.callApplication(type, addr, subject, body);
		}
		break;
    case IPlatformRequest::APP_BROWSER:
        {
            result = pForm.callApplication(type, addr);
        }
        break;
	default:
		break;
	}
	return result;
}