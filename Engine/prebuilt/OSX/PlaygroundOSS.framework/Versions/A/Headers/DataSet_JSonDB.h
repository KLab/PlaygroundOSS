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
#ifndef DataSet_JSonDB_h
#define DataSet_JSonDB_h

#include "../../libs/JSonParser/api/yajl_parse.h"
#include "../../libs/JSonParser/api/yajl_gen.h"

#include "DataSet.h"

struct Field {
	union {
		float	f;
		s32		i;
		s32		str;	// Strinf offset index.
		bool	b;
	} v;
};

struct RecordListHeader {
	RecordListHeader*	pNextRecord;
	Field*				fields;
};

class JSonDB : IDataSource {
	#define MAX_FIELD_PER_RECORD	(64)
public:
	static
	IDataSource*		openDB					(const u8* source, u32 sourceLength);

	static
	void				closeDB					(IDataSource* pSrc);

	virtual	s32			getTotalRecordCount		();
	virtual s32			getCurrentRecordCount	();
	virtual bool		fetchRecords			(u32 count);
	virtual bool		receivedUpdate			();

	virtual	EMOVECODE	moveTo					(u32 record);
	virtual	EMOVECODE	moveNext				();
	virtual	EMOVECODE	movePrevious			();

	virtual	IDataRecord getRecord				();
	virtual u32			getFieldCount			();
	virtual	const char*	getFieldName			(u32 index, u32& len);
	virtual u32			getFieldType			(u32 index);
	virtual u32			getFieldIndex			(const char* fieldName);

	virtual	s32			getAsInt				(IDataRecord rec, u32 index);
	virtual const char*	getAsString				(IDataRecord rec, u32 index, u32& len);
	virtual bool		getAsBool				(IDataRecord rec, u32 index);
	virtual float		getAsFloat				(IDataRecord rec, u32 index);
protected:
	bool readDBInternal	(const u8* source, u32 sourceLength);
private:
	JSonDB();
	~JSonDB();

	//
	// Parser Call back.
	//
	int readStartMap	(unsigned int size);
	int readNull		();
	int readBoolean		(int boolean);
	int readInt			(long long integerVal);
	int readDouble		(double doubleVal);
	int readString		(const unsigned char * stringVal, size_t stringLen, int cte_pool);
	int readMapKey		(const unsigned char * stringVal, size_t stringLen, int cte_pool);
	int readEndMap		();
	int readStartArray	(unsigned int size);
	int readEndArray	();

	static int read_start_map	(void * ctx, unsigned int size);
	static int read_null		(void * ctx);
	static int read_boolean		(void * ctx, int boolean);
	static int read_int			(void * ctx, long long integerVal);
	static int read_double		(void * ctx, double doubleVal);
	static int read_string		(void * ctx, const unsigned char * stringVal, size_t stringLen, int cte_pool);
	static int read_map_key		(void * ctx, const unsigned char * stringVal, size_t stringLen, int cte_pool);
	static int read_end_map		(void * ctx);
	static int read_start_array	(void * ctx, unsigned int size);
	static int read_end_array	(void * ctx);


	//
	// Record setup inner.
	//
	s32  getFieldID		(const unsigned char* str, s32 strLen);
	s32	 addField		(const unsigned char* str, s32 strLen);
	void setFieldType	(s32 field, u8 type);
	bool allocateRecord	();
	void copyFromTempToRecord();
	void setInt			(s32 idx, s32 value);
	void setFloat		(s32 idx, float value);
	void setString		(s32 idx, const unsigned char* str, s32 strLen);
	void setBool		(s32 idx, s32 value);
	void clean			();

private:
	EMOVECODE	m_res;

	#define DB_MAX_STRING_POOL_SIZE	(1000)

	char				m_stringBuffer[DB_MAX_STRING_POOL_SIZE];	// Field Name only, 1 KB should be enough
	u32					m_stringAlloc;

	u8					m_fieldType[64];	// Limit to 64 field per record.
	u16					m_fieldName[64];
	RecordListHeader	m_baseRecordHeader;
	Field				m_field[64];
	RecordListHeader*	m_currRecord;		// Current parser record.
	RecordListHeader*	m_startRecord;
	RecordListHeader*	m_recordPtr;		// Current navigation record.

	char*				mStringRecordBuffer;
	u32					mStringRecordCount;
	u32					m_StringRecordBufferSize;

	s32 m_entryIdx;			// Current Field
	u32 m_record;			// Record Count
	u32 m_recordEntry;		// Field Count
	u32 m_mapCnt;			// Parser Map Nest Counter
	u32 m_arrayCnt;			// Parser Array Nest Count
	u32 m_currRecIdx;		// Current navigation record index.
	yajl_handle parserCtx;	// Parser context pointer for callback.
};

#endif // DataSet_JSonDB_h
