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
#include "CKLBLuaDB.h"
#include "CPFInterface.h"
#include "CKLBUtility.h"

CKLBLuaDB	*	CKLBLuaDB::ms_begin = NULL;
CKLBLuaDB	*	CKLBLuaDB::ms_end	= NULL;


CKLBLuaDB::CKLBLuaDB() 
: m_name(NULL)
, m_db	(NULL)
, m_pLua(NULL)
, m_idx	(0)
, m_prev(NULL)
, m_next(NULL)
{
	add_link();
}

CKLBLuaDB::CKLBLuaDB(const char * db_asset, int flags) 
: m_name(NULL)
, m_db	(NULL)
, m_pLua(NULL)
, m_idx	(0)
, m_prev(NULL)
, m_next(NULL)
{
	add_link();
	open(db_asset, flags);
}

CKLBLuaDB::~CKLBLuaDB()
{
	close();
	remove_link();
	KLBDELETEA(m_name);
}

u32
CKLBLuaDB::getClassID()
{
	return CLS_KLBLUADB;
}


void
CKLBLuaDB::add_link()
{
	m_prev = ms_end;
	if(m_prev) {
		m_prev->m_next = this;
	} else {
		ms_begin = this;
	}
	ms_end = this;
}

void
CKLBLuaDB::remove_link()
{
	if(m_prev) {
		m_prev->m_next = m_next;
	} else {
		ms_begin = m_next;
	}
	if(m_next) {
		m_next->m_prev = m_prev;
	} else {
		ms_end = m_prev;
	}
}

bool
CKLBLuaDB::setName(const char * name)
{
	KLBDELETEA(m_name);
	m_name = NULL;
	if(name) {
		int len = strlen(name);
		char * buf = KLBNEWA(char, len + 1);
        if(!buf) { return false; }
		strcpy(buf, name);
		m_name = (const char *)buf;
	}
	return true;
}

bool
CKLBLuaDB::open(const char * db_asset, int flags)
{
	IPlatformRequest& platform = CPFInterface::getInstance().platform();
	bool isReadOnly;
	const char* fullpath = platform.getFullPath(db_asset,&isReadOnly);

	//
	if (isReadOnly && (flags & SQLITE_OPEN_READONLY) == 0) {
		klb_assertAlways("DB Write Enabled on Read Only file system.");
	}

	if (!isReadOnly) {
		flags |= SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE;
		flags &= ~SQLITE_OPEN_READONLY;
	}

	// create が指定されていない場合、対象のDBファイルが見つからなければその時点でエラー
	/*
	if(!(flags & SQLITE_OPEN_CREATE)) {
		klb_assert(fullpath, "DB file not found: %s", db_asset);
		return false;
	}*/

	// int rc = sqlite3_open(fullpath, &m_db);
	int rc = sqlite3_open_v2(fullpath, &m_db, flags, NULL);
    if (!isReadOnly) {
        CPFInterface::getInstance().platform().excludePathFromBackup(fullpath);
    }
	
	delete[] fullpath;
	if (rc) {
		klb_assertAlways("Can not open db %s", db_asset);
		close();
		return false;
	}

	char * errMsg;
	m_pragmaJournal = true;
	rc = sqlite3_exec(m_db, "PRAGMA journal_mode = OFF;", CKLBLuaDB::row_callback, this, &errMsg);
	m_pragmaJournal = false;

	if (rc) {
		platform.logging("Impossible to disable journal");
	}

	return true;
}

bool
CKLBLuaDB::close()
{
	if (m_db) {
		sqlite3_close(m_db);
		m_db = NULL;
	}
	return true;
}

int
CKLBLuaDB::query(CLuaState * plua, const char * query)
{
	CLuaState& lua = *plua;
	char * errMsg;
	if(!m_db) {
		lua.retBoolean(false);
		return 1;
	}

	m_pLua = plua;
	m_idx = 1;

	lua.retBoolean(true);	// 成功前提でtrueを積んでおく
	lua.tableNew();	// 親テーブルをスタック上に積んでおく
	int rc = sqlite3_exec(m_db, query, CKLBLuaDB::row_callback, this, &errMsg);

	if (rc != SQLITE_OK) {
		// 一応出力コンソールにログは出しておく。
		DEBUG_PRINT("[SQLite]%s", errMsg);

		// lua.error(errMsg);	// Luaでエラーを出すとscriptが中断されるので、エラーメッセージは基本出さない
		sqlite3_free(errMsg);
		lua.pop(2);		// 積んでしまったテーブルをスタックから除去
		lua.retBoolean(false);	// 第一戻り値としてfalseを積む
		lua.retInt(rc);	// 第二戻り値としてエラーコードを積む
		return 2;
	}

	return 2;
}

const char**
CKLBLuaDB::query(const char* query) 
{
	if(!m_db) { return NULL; }

	char * errMsg;
	m_idx = 1;

	int rc = sqlite3_exec(m_db, query, CKLBLuaDB::row_callback_luaFree, this, &errMsg);
	
	if (rc != SQLITE_OK) {
		DEBUG_PRINT("[SQLite]%s", errMsg);
		sqlite3_free(errMsg);
	}

	return (const char**)m_pLua;
}

int
CKLBLuaDB::row_callback(void* ctx, int colNum, char** columnText, char** columnName)
{
	CKLBLuaDB * pLDB = (CKLBLuaDB *)ctx;
	if (!pLDB->m_pragmaJournal) {
		CLuaState& lua = *(pLDB->m_pLua);

		// row になるtableのキーをスタックに積む
		lua.retInt(pLDB->m_idx);
		lua.tableNew();	// rowになるテーブルをスタック上に新しく作る

		for(int i = 0; i < colNum; i++) {
			lua.retString(columnName[i]);	// keyの値
			lua.retString(columnText[i]);	// valueの値
			lua.tableSet();					// その二つをテーブルに格納
		}

		lua.tableSet();	// テーブルを親テーブルに格納

		pLDB->m_idx++;
	}

	return 0;
}

int
CKLBLuaDB::row_callback_luaFree(void* ctx, int colNum, char** columnText, char** columnName)
{
	CKLBLuaDB * pLDB = (CKLBLuaDB *)ctx;
	if (!pLDB->m_pragmaJournal) {
		const char** strArr = KLBNEWA(const char*, colNum*2 + 1);

		strArr[0] = (const char*)colNum;
		u32 idx = 1;
		for(int i = 0; i < colNum; ++i) {
			strArr[idx++] =	(columnName[i])	? CKLBUtility::copyString(columnName[i]) : NULL;	// keyの値
			strArr[idx++] =	(columnText[i])	? CKLBUtility::copyString(columnText[i]) : NULL;	// valueの値
		}

		pLDB->m_pLua = (CLuaState *)strArr;
	}

	return 0;
}

void
CKLBLuaDB::closeAll()
{
	CKLBLuaDB * pDB = ms_begin;
	while(pDB) {
		CKLBLuaDB * pNXT = pDB->m_next;
		KLBDELETE(pDB);
		pDB = pNXT;
	}
}

bool
CKLBLuaDB::dumpAll()
{
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();

	bool bResult = false;
	CKLBLuaDB * pDB = ms_begin;
	while(pDB) {
		pForm.logging("[DB]<%p>:%s", pDB, (pDB->m_name) ? pDB->m_name : "(no name)");
		bResult = true;
		pDB = pDB->m_next;
	}
	return bResult;
}
