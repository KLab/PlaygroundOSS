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
#ifndef CKLBLuaDB_h
#define CKLBLuaDB_h
#include "sqlite3.h"
//#include "sqlite3ext.h"
#include "CLuaState.h"
#include "CKLBObject.h"

class CKLBLuaDB : public CKLBObjectScriptable
{
public:
	CKLBLuaDB();
	CKLBLuaDB(const char * db_asset, int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
	virtual ~CKLBLuaDB();

	u32 getClassID();

	inline bool state() {
		return (m_db) ? true : false;
	}

	bool setName(const char * name);

	// DBファイルのオープン: 現在オープンしているDBがあれば、一旦クローズして再オープン
	bool open(const char * db_asset, int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

	// DBファイルのクローズ
	bool close();

	// SQLの実行。selectionがある場合、その内容をLuaテーブルとしてスタックに積む
	int query(CLuaState * lua, const char * sql);
	const char** query(const char* query); // lua-free.

	// 現在生成されているCKLBLuaDB全てをクローズする
	static void closeAll();

	// 現在生成されているCKLBLuaDB全てをダンプする
	static bool dumpAll();

private:
	void add_link();
	void remove_link();

	const char		*	m_name;
	bool				m_pragmaJournal;

	sqlite3			*	m_db;
	CLuaState		*	m_pLua;
	int					m_idx;

	CKLBLuaDB		*	m_prev;
	CKLBLuaDB		*	m_next;

	static int row_callback			(void* ctx,int colNum,char** columnText,char** columnName);
	static int row_callback_luaFree	(void* ctx,int colNum,char** columnText,char** columnName);

	static	CKLBLuaDB	*	ms_begin;
	static	CKLBLuaDB	*	ms_end;
};


#endif // CKLBLuaDB_h
