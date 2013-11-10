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
//
// Wrapper around SQL Lite
//

#ifndef __KLB_DATABASE__
#define __KLB_DATABASE__

#include "sqlite3.h"
#include "BaseType.h"

/**
	Database Singleton.
 */
class CKLBDatabase {
public:
	inline
	static CKLBDatabase& getInstance() {
		static CKLBDatabase instance;
		return instance;
	}
	static void release		()	{ getInstance()._release();	}

	bool	init			(const char* dbFile, int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

	s32		lookup			(const char* table, const char* resultField, const char* className, const char* filterField, s32 filterValue);

	int		callBack		(int colNum,char** columnText,char** columnName);
private:
	sqlite3*	m_dataBase;
	bool		m_pragmaJournal;
	char*		m_lastDB;
	s32			m_result;
	
	CKLBDatabase			(CKLBDatabase const&);		// Dont implement.
	void operator=			(CKLBDatabase const&);		// Dont implement.

	bool	runStatement	(const char* SQLStatement);

	void	init			();

	CKLBDatabase ();
	~CKLBDatabase();
	void _release();
};

#endif
