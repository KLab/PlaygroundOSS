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
#ifndef CKLBLuaLibDB_h
#define CKLBLuaLibDB_h

#include "ILuaFuncLib.h"
#include "CKLBLuaDB.h"
#include "CKLBLibRegistrator.h"

class CKLBLuaLibDB : public ILuaFuncLib
{
private:
	CKLBLuaLibDB();
	static CKLBLibRegistrator::LIBREGISTSTRUCT* ms_libRegStruct;
public:
	CKLBLuaLibDB			(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibDB	();

	void addLibrary			();
	void destroyResources	();
	bool dumpObjects		(IPlatformRequest& pForm);

	// lua-free
	static CKLBLuaDB*	dbopen	(const char* db_asset, bool b_write, bool b_create);
	static void			dbclose	(CKLBLuaDB* pDB);
private:

	static int dbopen		(lua_State * L);
	static int dbclose		(lua_State * L);
	static int dbcloseAll	(lua_State * L);
	static int dbquery		(lua_State * L);
};


#endif // CKLBLuaLibDB_h
