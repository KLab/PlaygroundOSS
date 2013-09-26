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
#include "CKLBLanguageDatabase.h"
#include "CKLBUtility.h"

bool CKLBLanguageDatabase::addString(const char* id, const char* string) {
	const char* newstr = CKLBUtility::copyString(string);
	if (newstr) {
		m_dictionnary->add(id, newstr);
		return true;
	} else {
		return false;
	}
}

void CKLBLanguageDatabase::removeString(const char* id) {
	const char * string = (const char*)m_dictionnary->find(id);
	if(string) {
		m_dictionnary->remove(id);
		KLBDELETEA(string);
	}
}

const char* CKLBLanguageDatabase::loadStringFromDB(const char* id) {
	if (m_db) {
		// 1. SQL Load
		// 2. Add to dictionnary : done in callback
		// 3. Return loaded value.
		char buffer[512];
		sprintf(buffer, "SELECT %s,%s FROM %s WHERE %s='%s';", m_fieldKey, m_fieldValue, m_tableName, m_fieldKey, id);

		if (runStatement(buffer)) {
			return (const char*)m_dictionnary->find(id);
		} else {
			return NULL;
		}
	} else {
		return NULL;
	}
}

bool CKLBLanguageDatabase::preLoadGroup(const char* groupID) {
	char buffer[512];

	if (groupID && m_fieldGroup) {
		// Load a Group.
		sprintf(buffer, "SELECT %s,%s FROM %s WHERE %s='%s';", m_fieldKey, m_fieldValue, m_tableName, m_fieldGroup, groupID);
	} else {
		// Load complete table.
		sprintf(buffer, "SELECT %s,%s FROM %s;", m_fieldKey, m_fieldValue, m_tableName);
	}

	if (m_fieldGroup && runStatement(buffer)) {
		return true;
	} else {
		return false;
	}
}

bool CKLBLanguageDatabase::setupDB(const char* dbFile, const char* tableName, const char* keyField, const char* valueField, const char* groupField)
{
	IPlatformRequest& platform = CPFInterface::getInstance().platform();
	const char* fullPath = platform.getFullPath(dbFile);

	//int rc = sqlite3_open(fullPath, &m_dataBase);
	int rc = sqlite3_open_v2(fullPath, &m_db, SQLITE_OPEN_READONLY, NULL);
	delete[] fullPath;

	if (rc) {
		_release();
		return false;
	}

	m_tableName		= CKLBUtility::copyString(tableName);
	m_fieldValue	= CKLBUtility::copyString(valueField);
	m_fieldKey		= CKLBUtility::copyString(keyField);

	if (groupField) {
		m_fieldGroup	= CKLBUtility::copyString(groupField);
	}

	return (m_tableName!=NULL) && (m_fieldValue!=NULL) && (m_fieldKey!=NULL) && ((groupField!=NULL) ? (m_fieldGroup!=NULL) : true);
}


/**
 * Call back from SQLite for each record when loading language records.
 * -> Callback transfered to C++ callback.
 */
int CKLBLanguageDatabase::callbackFct (void* ctx,int colNum,char** columnText,char** columnName) {
	return ((CKLBLanguageDatabase*)ctx)->callBack(colNum,columnText,columnName);
}

int CKLBLanguageDatabase::callBack(int /*colNum*/,char** columnText,char** /*columnName*/) {
	if (columnText[0]) {
		// If each entry is valid. Add to the DB.
		const char* newstr = CKLBUtility::copyString(columnText[1]);
		if (newstr) {
			m_dictionnary->add(columnText[0],newstr);
		} else {
			return 1; // Error.
		}
	}
	return 0;
}

bool CKLBLanguageDatabase::runStatement(const char* SQLStatement) {
	char* errMsg;
	if (m_db) {
		int rc = sqlite3_exec(m_db, SQLStatement, CKLBLanguageDatabase::callbackFct, this, &errMsg);
		if (rc!=SQLITE_OK) {
			klb_assertAlways("DB Error : %s", errMsg);
			sqlite3_free(errMsg);
			return false;
		}
		return true;
	} else {
		klb_assertAlways("DB Not open");
		return false;
	}
}

const char*	CKLBLanguageDatabase::getString(const char* id) {
	if (id) {
		if (id[0] == '#') {
			const char* old = id;
			id = (const char*)m_dictionnary->find(&id[1]);
			if (!id) {
				id = loadStringFromDB(&old[1]);
				if (!id) {
					// Asked for removal because assert popup during game.
					// klb_assertAlways("%s is not in Language database.",old);
					id = old;
				}
			}
		}
	}
	return id;
}

CKLBLanguageDatabase::CKLBLanguageDatabase()
: m_db          (NULL)
, m_tableName   (NULL)
, m_fieldValue  (NULL)
, m_fieldGroup  (NULL)
, m_fieldKey    (NULL) 
, m_dictionnary (NULL)
{
	// Do nothing.
}

bool CKLBLanguageDatabase::init() {
	m_dictionnary = KLBNEW(Dictionnary);
	if (m_dictionnary) {
		m_dictionnary->setOwnerCallback(this, callbackDictionnary);
		if (m_dictionnary->init(3000)) {
			return true;
		}
	}
	return false;
}

CKLBLanguageDatabase::~CKLBLanguageDatabase() {
	// Dictionnary destroyed automatically.
}

void CKLBLanguageDatabase::callbackDictionnary(const void* /*this_*/, const void* ptrToDelete) {
	// Dico Entry Name String.
	KLBDELETEA((const char *)ptrToDelete);	
}

void CKLBLanguageDatabase::_release() {
	if (m_dictionnary) {
		m_dictionnary->clear();
	}

	if (m_db) {
		sqlite3_close(m_db);
		m_db = NULL;
	}

	KLBDELETEA(m_tableName);
	KLBDELETEA(m_fieldValue);
	KLBDELETEA(m_fieldGroup);
	KLBDELETEA(m_fieldKey);
	KLBDELETE(m_dictionnary);
}
