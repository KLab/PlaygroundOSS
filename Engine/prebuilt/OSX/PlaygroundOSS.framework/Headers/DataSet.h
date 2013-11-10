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
#ifndef INCLUDE_DATASET_H
#define INCLUDE_DATASET_H

#include "BaseType.h"

enum EMOVECODE {
	MOVE_SUCCEED,
	MOVE_EOF,
	MOVE_UNFETCH,
};

typedef void*	IDataRecord;

class IDataSource {
public:
	static const int	TYPE_INT	= 0;
	static const int	TYPE_STR	= 1;
	static const int	TYPE_BOOL	= 2;
	static const int	TYPE_FLOAT	= 3;
	static const int	TYPE_NIL	= 4;
	static const int	TYPE_BLOB	= 5;
	
	static	IDataSource*	
						doQuery					(const char* query);
	static	void		releaseQuery			(IDataSource* pQuery);
	
	// -1 : Dynamic.
	virtual	s32			getTotalRecordCount		() = 0;
	
	// Record loaded until now.
	virtual s32			getCurrentRecordCount	() = 0;
	
	// Request record if UNFETCH
	virtual bool		fetchRecords			(u32 count) = 0;
	// Result of fetching (polling from user)
	virtual bool		receivedUpdate			() = 0;
	
	virtual	EMOVECODE	moveTo					(u32 record) = 0;
	virtual	EMOVECODE	moveNext				() = 0;
	virtual	EMOVECODE	movePrevious			() = 0;

	virtual	IDataRecord getRecord				() = 0;
	
	virtual u32			getFieldCount			() = 0;
	virtual	const char*	getFieldName			(u32 index, u32& length) = 0;
	virtual u32			getFieldType			(u32 index) = 0;
	virtual u32			getFieldIndex			(const char* fieldName) = 0;

	// Access to one record.
	virtual	s32			getAsInt				(IDataRecord rec, u32 index) = 0;
	virtual const char*	getAsString				(IDataRecord rec, u32 index, u32& length) = 0;
	virtual bool		getAsBool				(IDataRecord rec, u32 index) = 0;
	virtual float		getAsFloat				(IDataRecord rec, u32 index) = 0;
    
    virtual ~IDataSource() {};
};

#endif // INCLUDE_DATASET_H
