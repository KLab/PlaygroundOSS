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
#ifndef __CKLBLanguageDatabase_h__
#define __CKLBLanguageDatabase_h__

#include "Dictionnary.h"
#include "sqlite3.h"

class CKLBLanguageDatabase {
public:
	static CKLBLanguageDatabase& getInstance() {
		static CKLBLanguageDatabase instance;
		return instance;
	}
	
	static void release() {	getInstance()._release();	}
	
	bool	init			();
	bool	addString		(const char* id, const char* string);
	void	removeString	(const char* id);
	const char*	getString	(const char* id);

	bool	setupDB			(const char* dbFile,
							 const char* tableName, 
							 const char* keyField, 
							 const char* valueField,
							 const char* groupField
							 );

	bool	preLoadGroup	(const char* groupID);

private:
	/* C like callback with object context for SQLite */
	static
	int			callbackFct			(void* ctx,int colNum,char** columnText,char** columnName);

	/* Callback to object */
	int			callBack			(int /*colNum*/,char** columnText,char** /*columnName*/);

	const char*	loadStringFromDB	(const char* id);
	bool		runStatement		(const char* SQLStatement);

	sqlite3*		m_db;
	const char*		m_tableName;
	const char*		m_fieldValue;
	const char*		m_fieldGroup;
	const char*		m_fieldKey;
	Dictionnary*	m_dictionnary;
	
	CKLBLanguageDatabase ();
	~CKLBLanguageDatabase();
	void _release();
	
	static void callbackDictionnary(const void* this_, const void* ptrToDelete);
};

#endif // 
