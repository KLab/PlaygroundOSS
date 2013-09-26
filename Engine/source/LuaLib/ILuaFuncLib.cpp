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
#include "ILuaFuncLib.h"

ILuaFuncLib * ILuaFuncLib::m_begin = NULL;
ILuaFuncLib * ILuaFuncLib::m_end   = NULL;

ILuaFuncLib::ILuaFuncLib() {}
ILuaFuncLib::ILuaFuncLib(DEFCONST * arrCmdItem){ addLink(arrCmdItem); }
ILuaFuncLib::~ILuaFuncLib()
{
	if(m_pPrev) {
		m_pPrev->m_pNext = m_pNext;
	} else {
		m_begin = m_pNext;
	}
	if(m_pNext) {
		m_pNext->m_pPrev = m_pPrev;
	} else {
		m_end = m_pPrev;
	}
}

bool
ILuaFuncLib::exist()
{
	return true;
}

void
ILuaFuncLib::destroyResources() {}

bool
ILuaFuncLib::dumpObjects(IPlatformRequest& /*pForm*/) 
{
	return false;
}

void
ILuaFuncLib::addLink(DEFCONST * arrCmdItem)
{
	m_arrCmdItem = arrCmdItem;
	m_pPrev = NULL;
    m_pNext = m_begin;
	if(m_pNext) {
		m_pNext->m_pPrev = this;
	} else {
		m_end = this;
	}
    m_begin = this;
}

void
ILuaFuncLib::registLib(lua_State * L)
{
	m_L = L;
	addLibrary();	// 関数群定義が書かれている筈の関数を呼び出す
	registConst();	// 指定された定数リストを読んで定義する
}

void
ILuaFuncLib::registConst()
{
	IPlatformRequest& pfif = CPFInterface::getInstance().platform();

	// 定数定義リストが与えられていなければ、行う処理はない。
	DEFCONST * pConst;
	for(pConst = m_arrCmdItem; pConst && pConst->name; pConst++) {
		lua_getglobal(m_L, pConst->name);
		if(!lua_isnil(m_L, -1)) {
			lua_pop(m_L, 1);
			// 指定されたグローバルラベルがnilではないということは、
			// 同名で値が定義済みであるため、エラーを出す。
			DEBUG_PRINT("[LIB REGISTRATION ERROR] %s it is redefined.\n", pConst->name);
			continue;
		}
		lua_pop(m_L, 1);
		lua_pushinteger(m_L, pConst->cmd);
		lua_setglobal(m_L, pConst->name);
		pfif.logging("\t\t[def] %s = %d", pConst->name, pConst->cmd);
	}
}

void
ILuaFuncLib::addFunction(const char * luaFuncName, int (*func)(lua_State * L))
{
	lua_register(m_L, luaFuncName, func);
	DEBUG_PRINT("  [func] %s", luaFuncName);
}

bool
ILuaFuncLib::registAllLibs(lua_State * L)
{
	ILuaFuncLib * pLib = m_begin;
	IPlatformRequest& pfif = CPFInterface::getInstance().platform();

	// オブジェクトダンプ関数を登録する
	lua_register(L, "LuaLibDUMP", ILuaFuncLib::luaDumpObjects);

	pfif.logging("<<<supported Lua functions>>>");

	while(pLib) {
		pLib->registLib(L);
		pLib = pLib->m_pNext;
	}
	return true;
}

void
ILuaFuncLib::destroyAllResources()
{
	ILuaFuncLib * pLib = m_begin;
	while(pLib) {
		pLib->destroyResources();
		pLib = pLib->m_pNext;
	}
}

int
ILuaFuncLib::luaDumpObjects(lua_State * L)
{
	CLuaState lua(L);

	// この関数について、引数は一切考慮しない。
	// 全ての引数を無視する。
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();

	ILuaFuncLib * pLib = m_begin;
	while(pLib) {
		pLib->dumpObjects(pForm);
		pLib = pLib->m_pNext;
	}
	lua.retBool(true);
	return 1;
}
