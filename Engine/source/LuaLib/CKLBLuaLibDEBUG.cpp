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
#include "CKLBLuaLibDEBUG.h"
#include "CKLBUtility.h"

static ILuaFuncLib::DEFCONST luaConst[] = {
	{ "DBG_M_SWITCH",	DBG_MENU::M_SWITCH },
	{ "DBG_M_SELECT",	DBG_MENU::M_SELECT },
	{ "DBG_M_NUMBER",	DBG_MENU::M_NUMBER },
	{ 0, 0 }
};

static CKLBLuaLibDEBUG libdef(luaConst);

/*static*/ DBG_MENU*	CKLBLuaLibDEBUG::s_arrMenu	= NULL;
/*static*/ u32			CKLBLuaLibDEBUG::s_maxCount	= 0;
/*static*/ u32			CKLBLuaLibDEBUG::s_idx		= 0;
/*static*/ const char*  CKLBLuaLibDEBUG::s_caption	= NULL;
/*static*/ const char*  CKLBLuaLibDEBUG::s_key		= NULL;

CKLBLuaLibDEBUG::CKLBLuaLibDEBUG(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef){}
CKLBLuaLibDEBUG::~CKLBLuaLibDEBUG() {}

// Lua関数の追加
void
CKLBLuaLibDEBUG::addLibrary()
{
	addFunction("DEBUG_SetCallback",		CKLBLuaLibDEBUG::luaDBGSetCallback);
	addFunction("DEBUG_AddItem",			CKLBLuaLibDEBUG::luaDBGSetMenu);
	addFunction("DEBUG_DelItem",			CKLBLuaLibDEBUG::luaDBGRemoveMenu);
}

int
CKLBLuaLibDEBUG::luaDBGRemoveMenu(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retBoolean(false);
		return 1;
	}
#ifdef DEBUG_MENU
	const char * key = lua.getString(1);

	CKLBDebugResource& dbg = CKLBDebugResource::getInstance();
	dbg.removeGroup(key);
#endif
	lua.retBoolean(true);
	return 1;
}

int
CKLBLuaLibDEBUG::luaDBGSetMenu(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();

	if(argc != 3) {
		lua.retBoolean(false);
		return 1;
	}
#ifdef DEBUG_MENU
	const char * caption = lua.getString(1);
	const char * key = lua.getString(2);

	CKLBDebugResource& dbg = CKLBDebugResource::getInstance();

	// 3番目の引数として与えられたテーブルをスタック最上位に積みなおす
	lua.retValue(3);

	// その配列でデバッグメニューを登録する
	dbg.setGroupLua(caption, key, lua);

	// 積んであったテーブルをスタックから取り除く
	lua.pop(1);
#endif
	// 戻り値はtrue
	lua.retBoolean(true);
	return 1;
}

int
CKLBLuaLibDEBUG::luaDBGSetCallback(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc > 1) {
		lua.retBoolean(false);
		return 1;
	}

#ifdef DEBUG_MENU
	CKLBDebugResource& dbg = CKLBDebugResource::getInstance();
	const char * callback = 0;
	if(argc == 1) callback = lua.getString(1);

	dbg.setCallback(callback);
#endif
	lua.retBoolean(true);
	return 1;
}

/*static*/
void
CKLBLuaLibDEBUG::startMenu(u32 maxCount, const char * caption, const char * key) 
{
#ifdef DEBUG_MENU
	CKLBLuaLibDEBUG::s_maxCount	= maxCount;
	CKLBLuaLibDEBUG::s_arrMenu	= KLBNEWA(DBG_MENU, maxCount + 1);
	CKLBLuaLibDEBUG::s_caption	= CKLBUtility::copyString(caption);
	CKLBLuaLibDEBUG::s_key		= CKLBUtility::copyString(key);
#endif
}

/*static*/
void 
CKLBLuaLibDEBUG::addItem(u32 mode, const char* caption, const char* key, s32 min, s32 max, s32 value, const char** items, u32 itemsCount) 
{
#ifdef DEBUG_MENU
	klb_assert(CKLBLuaLibDEBUG::s_idx <= CKLBLuaLibDEBUG::s_maxCount, "Max Count reached.");
	
	CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].mode		= (DBG_MENU::MODE)mode;
	CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].caption	= (caption) ? CKLBUtility::copyString(caption)	: NULL;
	CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].key		= (key)		? CKLBUtility::copyString(key)		: NULL;
	switch(CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].mode)
	{
	case DBG_MENU::M_SWITCH:
		{
			CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].value	= value;
			CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].min		= 0;
			CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].max		= 1;
			CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].items	= NULL;
		}
		break;
	case DBG_MENU::M_SELECT:
		{
			CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].value = 0;
			const char ** disp = KLBNEWA(const char *, itemsCount);
			for(u32 idx = 0; idx < itemsCount; idx++) {
				disp[idx] = (items[idx]) ? CKLBUtility::copyString(items[idx]) : NULL;
			}
			CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].value	= value;
			CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].min		= 0;
			CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].max		= itemsCount - 1;
			CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].items	= disp;
		}
		break;
	case DBG_MENU::M_NUMBER:
		{
			CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].min		= min;
			CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].max		= max;
			CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].value	= value;
			CKLBLuaLibDEBUG::s_arrMenu[CKLBLuaLibDEBUG::s_idx].items	= NULL;
		}
		break;
	}
	CKLBLuaLibDEBUG::s_idx++;

#endif
}

/*static*/
void
CKLBLuaLibDEBUG::endMenu() 
{
#ifdef DEBUG_MENU
	CKLBDebugResource& dbg = CKLBDebugResource::getInstance();
	for(u32 i = CKLBLuaLibDEBUG::s_idx; i < CKLBLuaLibDEBUG::s_maxCount + 1; ++i) {
		CKLBLuaLibDEBUG::s_arrMenu[i].caption = NULL;
	}
	dbg.addDebugItem(CKLBLuaLibDEBUG::s_caption, CKLBLuaLibDEBUG::s_key, CKLBLuaLibDEBUG::s_arrMenu);
	for(u32 i = 0; i < CKLBLuaLibDEBUG::s_idx; i++) {
		KLBDELETEA(CKLBLuaLibDEBUG::s_arrMenu[i].items);
	}
	KLBDELETEA(CKLBLuaLibDEBUG::s_arrMenu);
	KLBDELETE(CKLBLuaLibDEBUG::s_caption);
	KLBDELETE(CKLBLuaLibDEBUG::s_key);
	CKLBLuaLibDEBUG::s_arrMenu	= NULL;
	CKLBLuaLibDEBUG::s_caption	= NULL;
	CKLBLuaLibDEBUG::s_key		= NULL;
	CKLBLuaLibDEBUG::s_maxCount	= 0;
	CKLBLuaLibDEBUG::s_idx		= 0;
#endif
}

/*static*/
void
CKLBLuaLibDEBUG::removeMenu(const char * key) 
{
#ifdef DEBUG_MENU
	CKLBDebugResource& dbg = CKLBDebugResource::getInstance();
	dbg.removeGroup(key);
#endif
}
