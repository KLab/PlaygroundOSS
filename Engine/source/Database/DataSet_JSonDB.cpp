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
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "DataSet_JSonDB.h"

JSonDB::JSonDB()
:m_startRecord			(NULL)
,mStringRecordBuffer	(NULL)
{
}

JSonDB::~JSonDB() {
	clean();
}

void JSonDB::clean() {
	RecordListHeader* pRecord = m_startRecord;
	while (pRecord) {
		RecordListHeader* pNextRecord = pRecord->pNextRecord;
		KLBDELETE(pRecord->fields);
		KLBDELETE(pRecord);
		pRecord = pNextRecord;
	}
	m_startRecord = NULL;

	KLBDELETEA(mStringRecordBuffer);
	mStringRecordBuffer = NULL;
}

/*static*/ int JSonDB::read_start_map		(void * ctx, unsigned int size)
{ return ((JSonDB*)ctx)->readStartMap(size); }
/*static*/ int JSonDB::read_null			(void * ctx)
{ return ((JSonDB*)ctx)->readNull(); }
/*static*/ int JSonDB::read_boolean			(void * ctx, int boolean)
{ return ((JSonDB*)ctx)->readBoolean(boolean); }
/*static*/ int JSonDB::read_int				(void * ctx, long long integerVal)
{ return ((JSonDB*)ctx)->readInt(integerVal); }
/*static*/ int JSonDB::read_double			(void * ctx, double doubleVal)
{ return ((JSonDB*)ctx)->readDouble(doubleVal); }
/*static*/ int JSonDB::read_string			(void * ctx, const unsigned char * stringVal, size_t stringLen, int cte_pool)
{ return ((JSonDB*)ctx)->readString(stringVal, stringLen,cte_pool); }
/*static*/ int JSonDB::read_map_key			(void * ctx, const unsigned char * stringVal, size_t stringLen, int cte_pool)
{ return ((JSonDB*)ctx)->readMapKey(stringVal, stringLen,cte_pool); }
/*static*/ int JSonDB::read_end_map			(void * ctx)
{ return ((JSonDB*)ctx)->readEndMap(); }
/*static*/ int JSonDB::read_start_array		(void * ctx, unsigned int size)
{ return ((JSonDB*)ctx)->readStartArray(size); }
/*static*/ int JSonDB::read_end_array		(void * ctx)
{ return ((JSonDB*)ctx)->readEndArray(); }

/*static*/
IDataSource* JSonDB::openDB(const u8* source, u32 sourceLength) {
	JSonDB* newDB = KLBNEW(JSonDB);
	if (!newDB->readDBInternal(source, sourceLength)) {
		KLBDELETE(newDB);
		newDB = NULL;
	}
	return newDB;
}


bool JSonDB::readDBInternal(const u8* source, u32 sourceLength) {
	bool res = false;
	m_baseRecordHeader.fields		= &m_field[0];
	m_baseRecordHeader.pNextRecord	= NULL;
	m_arrayCnt		= 0;
	m_record		= 0;
	m_recordEntry	= 0;
	m_stringAlloc	= 0;
	m_startRecord	= NULL;
	m_currRecIdx	= 0;
	m_mapCnt		= 0;
	m_res			= MOVE_UNFETCH;

	mStringRecordBuffer	= KLBNEWA(char, sourceLength);
	mStringRecordCount  = 0;
	m_StringRecordBufferSize = sourceLength;

	if (mStringRecordBuffer) {
		static yajl_callbacks callbacks = {  
			JSonDB::read_null,  
			JSonDB::read_boolean,  
			JSonDB::read_int,  
			JSonDB::read_double,  
			NULL,  
			JSonDB::read_string,  
			JSonDB::read_start_map,  
			JSonDB::read_map_key,  
			JSonDB::read_end_map,  
			JSonDB::read_start_array,  
			JSonDB::read_end_array
		};

		memcpy(mStringRecordBuffer, source, sourceLength);
		yajl_handle hand;
		/* generator config */  
//		yajl_gen g;				// My Context. 2012.12.06  使用していなかったのでコメントアウト
		yajl_status stat;  
  
//		g = yajl_gen_alloc(NULL); // 2012.12.06  使用していなかったのでコメントアウト

		/* ok.  open file.  let's read and parse */  
		hand = yajl_alloc(&callbacks, NULL, this);
		if (hand) {
			this->parserCtx = hand;

			/* and let's allow comments by default */  
			yajl_config(hand, yajl_allow_comments, 1);

			stat = yajl_parse(hand, (const unsigned char*)mStringRecordBuffer, sourceLength);

			if (stat == yajl_status_ok) {
				stat = yajl_complete_parse(hand);
				if (stat == yajl_status_ok) {
					res = true;
				}
			}
		}
	}

	if (!res) {
		clean();
	}
	m_recordPtr		= m_startRecord;
	return res;
}

int JSonDB::readNull()  
{
	if (m_record == 1) {
		// Set data type to entry -> String for null, only type tolerated as we do not tolerate sub object / array for now.
		setFieldType(m_entryIdx, TYPE_STR);
	}
	setString(m_entryIdx, NULL, 0);
    return 1;
}
  
int JSonDB::readBoolean(int boolean)  
{
	if (m_record == 1) {
		// Set data type to entry.
		setFieldType(m_entryIdx, TYPE_BOOL);
	}

	setBool(m_entryIdx, boolean);
	return 1;  
}  

int JSonDB::readInt(long long integerVal)  
{
	if (m_record == 1) {
		// Set data type to entry.
		setFieldType(m_entryIdx, TYPE_INT);
	}

	setInt(m_entryIdx, (s32)integerVal);
    return 1;
}
  
int JSonDB::readDouble(double doubleVal)  
{	
	if (m_record == 1) {
		// Set data type to entry.
		setFieldType(m_entryIdx, TYPE_FLOAT);
	}

	setFloat(m_entryIdx, (float)doubleVal);
	return 1;
}
  
int JSonDB::readString(const unsigned char * stringVal, size_t stringLen, int /*cte_pool*/)  
{
	if (m_record == 1) {
		// Set data type to entry.
		setFieldType(m_entryIdx, TYPE_STR);
	}

	setString(m_entryIdx, stringVal, stringLen);
	return 1;
}

/*static*/
int JSonDB::readMapKey(const unsigned char * stringVal, size_t stringLen, int cte_pool)  
{
	if (m_record == 1) {
		if (m_recordEntry < MAX_FIELD_PER_RECORD) {
			// Store name and index.
			m_entryIdx = addField(stringVal, stringLen);
			m_recordEntry++;
		} else {
			klb_assertAlways("Limit is 64 field / record");
			return 0;
		}
	} else {
		if (cte_pool > -1) {
			int id = bjson_getCPCacheID((yajl_handle)this->parserCtx, cte_pool);
			if (id != -1) {
				m_entryIdx = id;
				return 1;
			}
		}

		// remap key to index.
		m_entryIdx = getFieldID(stringVal, stringLen);
		if (m_entryIdx == -1) {
			klb_assertAlways("Record structure changed between records.");
		}

		if (cte_pool > -1) {
			bjson_setCPCacheID((yajl_handle)this->parserCtx, cte_pool, m_entryIdx);
		}
	}
	return 1;
}

int JSonDB::readStartMap(unsigned int /*size*/) {
	if (m_mapCnt == 0) {
		if (allocateRecord()) {
			m_record++;
		} else {
			return 0;
		}
	}
	return 1;
}

int JSonDB::readEndMap()  
{
	if (m_record == 1) {
		if (!allocateRecord()) {
			return 0;
		}
		copyFromTempToRecord();
		m_startRecord = m_currRecord;
	}
	return 1;  
}

int JSonDB::readStartArray(unsigned int /*size*/)
{
	if (m_arrayCnt == 0) {
		// First level
	} else {
		klb_assertAlways("Do not support nested arrays in DB for now");
	}
	m_arrayCnt++;
	return 1;
}

/*static*/ 
int JSonDB::readEndArray()  {
	m_arrayCnt--;
	return 1;
}

s32	 JSonDB::addField(const unsigned char* str, s32 strLen) {
	klb_assert((m_stringAlloc + strLen+1) < DB_MAX_STRING_POOL_SIZE, "Field Name String pool too small.");
	memcpy(&m_stringBuffer[m_stringAlloc], str, strLen);
	m_fieldName[m_recordEntry] = (u16)m_stringAlloc;
	m_stringBuffer[m_stringAlloc + strLen] = 0; // End string.
	m_stringAlloc += strLen + 1;
	return m_recordEntry;
}

void JSonDB::setFieldType	(s32 field, u8 type) {
	klb_assert(((u32)field) < MAX_FIELD_PER_RECORD, "Invalid field index");
	m_fieldType[field] = type;
}

bool JSonDB::allocateRecord	() {
	if (m_record != 0) {
		RecordListHeader* pRecord = (RecordListHeader*)KLBNEWA(u8, sizeof(RecordListHeader) + 4 + (m_recordEntry * sizeof(Field)));
		if (pRecord) {
			// Init new record.
			pRecord->pNextRecord	= NULL;
			pRecord->fields			= (Field*)&pRecord[1];	// Trick : use field after record header in memory.

			// Connect to link list and go to next element.
			m_currRecord->pNextRecord	= pRecord;
			m_currRecord				= pRecord;
		} else {
			return false;
		}
	} else {
		m_currRecord = &m_baseRecordHeader;
	}
	return true;
}

void JSonDB::copyFromTempToRecord() {
	// Move data to first allocated record
	memcpy(m_currRecord->fields, this->m_field,m_recordEntry * sizeof(Field));
}

void JSonDB::setInt			(s32 idx, s32 value) {
	klb_assert(m_fieldType[idx]==TYPE_INT,"Type does not match");
	klb_assert(((u32)idx) < m_recordEntry, "Field index out of range");
	m_currRecord->fields[idx].v.i = value;
}

void JSonDB::setFloat		(s32 idx, float value) {
	klb_assert(m_fieldType[idx]==TYPE_FLOAT,"Type does not match");
	klb_assert(((u32)idx) < m_recordEntry, "Field index out of range");
	m_currRecord->fields[idx].v.f = value;
}

void JSonDB::setBool		(s32 idx, s32 value) {
	klb_assert(m_fieldType[idx]==TYPE_BOOL,"Type does not match");
	klb_assert(((u32)idx) < m_recordEntry, "Field index out of range");
	m_currRecord->fields[idx].v.b = value ? true : false;
}

s32 JSonDB::getTotalRecordCount		() {
	return m_record;
}

s32 JSonDB::getCurrentRecordCount	() {
	return m_record;
}

bool JSonDB::fetchRecords			(u32 /*count*/) {
	// All fetched
	return true;
}

bool JSonDB::receivedUpdate			() {
	// Data always available
	return true;
}

const char*	JSonDB::getFieldName(u32 index, u32& len) {
	klb_assert(index < m_recordEntry, "Field index out of range");
	len = strlen(&m_stringBuffer[m_fieldName[index]]);
	return &m_stringBuffer[m_fieldName[index]];
}

s32 JSonDB::getFieldID(const unsigned char* str, s32 strLen) {
	klb_assert((m_stringAlloc + strLen+1) < DB_MAX_STRING_POOL_SIZE, "Field Name String pool too small for temp usage.");

	// Copy and create temp string (do NOT modify m_stringAlloc : no allocation really done)
	memcpy(&m_stringBuffer[m_stringAlloc], str, strLen);
	m_stringBuffer[m_stringAlloc + strLen] = 0; // End string.

	return this->getFieldIndex(&m_stringBuffer[m_stringAlloc]);
}

void JSonDB::setString		(s32 idx, const unsigned char* str, s32 strLen) { 
	klb_assert(m_fieldType[idx]==TYPE_STR,"Type does not match");
	klb_assert(((u32)idx) < m_recordEntry, "Field index out of range");
	klb_assert((mStringRecordCount+strLen) < m_StringRecordBufferSize, "String buffer full");

	if (str && strLen) {
		memcpy(&mStringRecordBuffer[mStringRecordCount], str, strLen);
		mStringRecordBuffer[mStringRecordCount + strLen] = 0; // End string.

		m_currRecord->fields[idx].v.str = mStringRecordCount;
		mStringRecordCount += strLen + 1;
	} else {
		m_currRecord->fields[idx].v.str = -1;
	}
}

const char*	JSonDB::getAsString	(IDataRecord rec, u32 index, u32& len) {
	klb_assert(m_fieldType[index]==TYPE_STR,"Type does not match");
	klb_assert(index < m_recordEntry, "Field index out of range");
	RecordListHeader* pRecord = (RecordListHeader*)rec;
	const char* res;
	if (pRecord->fields[index].v.str != -1) {
		res = &mStringRecordBuffer[pRecord->fields[index].v.str];
		len = strlen(res);
	} else {
		res = NULL;
		len = 0;
	}
	return res;
}

EMOVECODE JSonDB::moveTo(u32 rec) {
	RecordListHeader* p = m_startRecord;
	u32 counter = 0;
	while (p) {
		if (counter == rec) {
			m_res			= MOVE_SUCCEED;
			m_recordPtr		= p;
			m_currRecIdx	= rec;
			return m_res;
		}
	}

	m_res		= MOVE_EOF;
	m_recordPtr = p;
	m_currRecIdx= m_record;
	return m_res;
}

EMOVECODE JSonDB::moveNext() {
	if (m_currRecIdx < m_record) {
		m_currRecIdx++;
		m_recordPtr = m_recordPtr->pNextRecord;
	} else {
		m_recordPtr = NULL;
	}

	m_res = (m_recordPtr != NULL) ? MOVE_SUCCEED : MOVE_EOF;
	return m_res;
}

EMOVECODE JSonDB::movePrevious() {
	if (m_currRecIdx > 0) {
		m_currRecIdx--;
		moveTo(m_currRecIdx);
	} else {
		m_recordPtr = NULL;
	}
	m_res = (m_recordPtr != NULL) ? MOVE_SUCCEED : MOVE_EOF;
	return m_res;
}

IDataRecord JSonDB::getRecord() {
	if (m_res == MOVE_SUCCEED) {
		return (IDataRecord)m_recordPtr;
	} else {
		return NULL;
	}
}

u32	JSonDB::getFieldCount() {
	return this->m_recordEntry;
}

u32	JSonDB::getFieldType(u32 index) {
	klb_assert(((u32)index) < MAX_FIELD_PER_RECORD, "Invalid field index");
	return m_fieldType[index];
}

u32	JSonDB::getFieldIndex(const char* fieldName) {
	for (u32 idx = 0; idx < m_recordEntry; idx++) {
		if (strcmp(fieldName, &this->m_stringBuffer[m_fieldName[idx]]) == 0) {
			return idx;
		}
	}
	return 0xFFFFFFFF;
}

s32	JSonDB::getAsInt		(IDataRecord rec, u32 index) {
	klb_assert(m_fieldType[index]==TYPE_INT,"Type does not match");
	klb_assert(index < m_recordEntry, "Field index out of range");
	RecordListHeader* pRecord = (RecordListHeader*)rec;
	return pRecord->fields[index].v.i;
}

bool JSonDB::getAsBool		(IDataRecord rec, u32 index) {
	klb_assert(m_fieldType[index]==TYPE_BOOL,"Type does not match");
	klb_assert(index < m_recordEntry, "Field index out of range");
	RecordListHeader* pRecord = (RecordListHeader*)rec;
	return pRecord->fields[index].v.b;
}

float JSonDB::getAsFloat	(IDataRecord rec, u32 index) {
	klb_assert(m_fieldType[index]==TYPE_FLOAT,"Type does not match");
	klb_assert(index < m_recordEntry, "Field index out of range");
	RecordListHeader* pRecord = (RecordListHeader*)rec;
	return pRecord->fields[index].v.f;
}

/*
static const char* testStr = "[ { \"hello\": 1, \"valuebool\": true, \"nilfield\": null, \"strfield\": \"hello world\" }, { \"hello\": 2, \"valuebool\": false, \"nilfield\": \"string guys\", \"strfield\": \"hello world 2\" } ]";

class DInitializer {
public:
	DInitializer();
};

// Global variable force constructor exec.
DInitializer _gInit;

DInitializer::DInitializer() {
	IDataSource* pDBObj = JSonDB::openDB((const u8*)testStr, strlen(testStr));
}
*/
