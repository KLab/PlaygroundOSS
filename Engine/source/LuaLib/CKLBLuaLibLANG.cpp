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
#include "CKLBLuaLibLANG.h"
#include "CKLBUtility.h"

static ILuaFuncLib::DEFCONST defcmd[] = {
	{ 0, 0 }
};

static CKLBLuaLibLANG libdef(defcmd);

CKLBLuaLibLANG::CKLBLuaLibLANG(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibLANG::~CKLBLuaLibLANG() {}

void CKLBLuaLibLANG::addLibrary()
{
	addFunction("LANG_addString",		CKLBLuaLibLANG::luaAddString);
	addFunction("LANG_getString",		CKLBLuaLibLANG::luaGetString);
	addFunction("LANG_removeString",	CKLBLuaLibLANG::luaRemoveString);
	addFunction("LANG_useDB",			CKLBLuaLibLANG::luaUseDB);
	addFunction("LANG_loadGroup",		CKLBLuaLibLANG::luaLoadGroup);
}

int
CKLBLuaLibLANG::luaUseDB(lua_State * L) {
	CLuaState lua(L);
	int argc = lua.numArgs();

	/*
	bool	setupDB			(const char* dbFile,
							 const char* tableName, 
							 const char* keyField, 
							 const char* valueField,
							 [OPT] const char* groupField	 */
	if(argc < 4) {
		lua.retBool(false);
		return 1;
	}

	const char * dbFile = lua.getString(1);
	const char * table  = lua.getString(2);
	const char * keyF   = lua.getString(3);
	const char * valueF = lua.getString(4);
	const char * groupF = (argc == 5) ? lua.getString(5) : NULL;

	bool bResult = useDB(dbFile, table, keyF, valueF, groupF);

	lua.retBool(bResult);
	return 1;
}

int
CKLBLuaLibLANG::luaLoadGroup(lua_State * L) {

	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retBool(false);
		return 1;
	}

	const char* groupID = lua.getString(1);

	bool bResult = loadGroup(groupID);
	
	lua.retBool(bResult);
	return 1;
}

int
CKLBLuaLibLANG::luaAddString(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 2) {
		lua.retBool(false);
		return 1;
	}

	const char * id = lua.getString(1);
	const char * string = lua.getString(2);

	bool bResult = addString(id, string);

	lua.retBool(bResult);
	return 1;
}

int
CKLBLuaLibLANG::luaGetString(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retNil();
		return 1;
	}

	const char * id = lua.getString(1);

	const char * string = getString(id);

	if(string) {
		lua.retString(string);
	} else {
		lua.retNil();
	}
	return 1;
}

int
CKLBLuaLibLANG::luaRemoveString(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retBool(false);
		return 1;
	}
	const char * id = lua.getString(1);

	removeString(id);

	lua.retBool(true);
	return 1;
}

