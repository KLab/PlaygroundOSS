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
#ifndef CKLBLuaLibDEBUG_h
#define CKLBLuaLibDEBUG_h

#include "ILuaFuncLib.h"
#include "CKLBDebugMenu.h"

class CKLBLuaLibDEBUG : public ILuaFuncLib
{
private:
	CKLBLuaLibDEBUG();
public:
	CKLBLuaLibDEBUG(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibDEBUG();

	void addLibrary();

	static DBG_MENU*	s_arrMenu;
	static u32			s_maxCount;
	static u32			s_idx;
	static const char*  s_caption;
	static const char*  s_key;

	static void startMenu	(u32 maxCount, const char * caption, const char * key);
	static void addItem		(u32 mode, const char* caption, const char* key, s32 min, s32 max, s32 value, const char** items, u32 itemsCount);
	static void endMenu		();
	static void removeMenu	(const char * key);
private:
	static int luaDBGSetCallback	(lua_State * L);
	static int luaDBGSetMenu		(lua_State * L);
	static int luaDBGRemoveMenu		(lua_State * L);
};


#endif // CKLBLuaLibDEBUG_h
