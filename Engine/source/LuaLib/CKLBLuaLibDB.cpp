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
#include "CKLBLuaLibDB.h"

static CKLBLuaLibDB libdef(0);

CKLBLibRegistrator::LIBREGISTSTRUCT* CKLBLuaLibDB::ms_libRegStruct = CKLBLibRegistrator::getInstance()->add("LibDB", CLS_KLBLUADB);

CKLBLuaLibDB::CKLBLuaLibDB(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibDB::~CKLBLuaLibDB()
{
	// クローズされていないDBがあればすべてクローズ
	CKLBLuaDB::closeAll();
}

// LuaLib全破棄時に、クローズされていないDBはすべてクローズ
void
CKLBLuaLibDB::destroyResources()
{
	CKLBLuaDB::closeAll();
}

// 現在生成されているDBオブジェクトをダンプする
bool
CKLBLuaLibDB::dumpObjects(IPlatformRequest& pForm)
{
	pForm.logging("[LuaLibDB]");
	return CKLBLuaDB::dumpAll();
}


// Lua関数の追加
void
CKLBLuaLibDB::addLibrary()
{
	addFunction("DB_open",  CKLBLuaLibDB::dbopen);
	addFunction("DB_close", CKLBLuaLibDB::dbclose);
	addFunction("DB_query", CKLBLuaLibDB::dbquery);
	addFunction("DB_closeAll", CKLBLuaLibDB::dbcloseAll);
}

int
CKLBLuaLibDB::dbopen(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc < 1 || 3 < argc) {
		lua.retNil();
		return 1;
	}

	const char * db_asset = lua.getString(1);
	bool b_write = (argc >= 2) ? lua.getBool(2) : true;
	bool b_create = (argc >= 3) ? lua.getBool(3) : true;

	CKLBLuaDB * pDB = dbopen(db_asset,b_write,b_create);
	if(pDB){
		lua.retPointer(pDB);
	}
	else {
		lua.retNil();
	}
	return 1;
}

int
CKLBLuaLibDB::dbclose(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retNil();
		return 1;
	}
	if(lua.isNil(1)) {	// ポインタとして積まれたものがnilだった
		lua.retNil();
		return 1;
	}
	CKLBLuaDB * pDB = (CKLBLuaDB *)lua.getPointer(1);
	KLBDELETE(pDB);
	lua.retNil();
	return 1;	// nilを返す
}

int
CKLBLuaLibDB::dbcloseAll(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 0) {
		lua.retBool(false);
		return 1;
	}
	CKLBLuaDB::closeAll();
	lua.retBool(true);
	return 1;	// nilを返す
}


int
CKLBLuaLibDB::dbquery(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 2) {
		lua.retNil();
		return 1;
	}
	if(lua.isNil(1)) {	// ポインタとして積まれたものがnilだった
		lua.retNil();
		return 1;
	}
	CKLBLuaDB * pDB = (CKLBLuaDB *)lua.getPointer(1);
	const char * sql = lua.getString(2);

	return pDB->query(&lua, sql);	// 失敗のときはエラーコード(int)が、成功のときはテーブルが積まれる。
}

CKLBLuaDB* CKLBLuaLibDB::dbopen(const char* db_asset, bool b_write, bool b_create)
{
	int flags = (b_write) ? SQLITE_OPEN_READWRITE : SQLITE_OPEN_READONLY;
	if(b_write && b_create) flags |= SQLITE_OPEN_CREATE;

	CKLBLuaDB * pDB = KLBNEWC(CKLBLuaDB, (db_asset, flags));
	if(!pDB || !pDB->state()) {
		KLBDELETE(pDB);
		return NULL;
	}
	pDB->setName(db_asset);	// asset名をDBの名前としてつける
	return pDB;
}

void CKLBLuaLibDB::dbclose(CKLBLuaDB* pDB)
{
	if(pDB != NULL)
	{
		KLBDELETE(pDB);
	}
	else{
		//Do nothing
	}
}