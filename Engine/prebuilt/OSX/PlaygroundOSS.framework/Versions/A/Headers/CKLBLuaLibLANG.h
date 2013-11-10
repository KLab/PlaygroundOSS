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
#ifndef CKLBLuaLibLANG_h
#define CKLBLuaLibLANG_h

#include "ILuaFuncLib.h"
#include "CKLBLanguageDatabase.h"

class CKLBLuaLibLANG : public ILuaFuncLib
{
private:
	CKLBLuaLibLANG();
public:
	CKLBLuaLibLANG(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibLANG();

	void addLibrary();
	
	inline static
	bool addString(const char* id, const char* str) {
		return CKLBLanguageDatabase::getInstance().addString(id, str);
	}

	inline static
	const char* getString(const char* id) {
		return CKLBLanguageDatabase::getInstance().getString(id);
	}
	
	inline static
	void removeString(const char* id) {
		CKLBLanguageDatabase& ldb = CKLBLanguageDatabase::getInstance();
		ldb.removeString(id);
	}

	inline static
	bool useDB(const char* dbFile, const char* table, const char* keyF, const char* valueF, const char* groupF) {
		return CKLBLanguageDatabase::getInstance().setupDB(dbFile, table, keyF, valueF, groupF);
	}

	inline static
	bool loadGroup(const char* groupId) {
		return CKLBLanguageDatabase::getInstance().preLoadGroup(groupId);
	}

private:
	static int luaAddString		(lua_State * L);
	static int luaGetString		(lua_State * L);
	static int luaRemoveString	(lua_State * L);
	static int luaUseDB			(lua_State * L);
	static int luaLoadGroup		(lua_State * L);
};

#endif // CKLBLiaLibUI_h
