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
#ifndef __CLB_PROPERTY_BAG
#define __CLB_PROPERTY_BAG

#include "BaseType.h"

#define MAX_PROP_BUFFER_COUNT	(2000)
#define STRING_BUFFER_SIZE		(2000)
#define MAX_PROPERTYBAG_COUNT	(100)

class CKLBPropertyBag {
public:
	static CKLBPropertyBag*		getPropertyBag		();
	static void 				releasePropertyBag	(CKLBPropertyBag* pBag);
	
	bool	init();
	
	void 	setPropertyInt		(const char* name, s32 value);
	void	setPropertyBool		(const char* name, bool value);
	void	setPropertyFloat	(const char* name, float value);
	void	setPropertyString	(const char* name, const char* value);
	
	u32		getFieldType		(const char* name);
	s32		getPropertyInt		(const char* name);
	bool	getPropertyBool		(const char* name);
	float	getPropertyFloat	(const char* name);
	const char*
			getPropertyString	(const char* name);
	
	s32		getIndex(const char* name);
private:
	CKLBPropertyBag();
	~CKLBPropertyBag();
	
	void appendProperty();
	const char*	allocateName(const char* originalName, int addlen = 0);
	
	struct _v {
		union v {
			float 			f;
			s32				i;
			const char*		s;
			bool			b;
		} v;
		const char* name;
	};
	
	_v*			m_propertyValues;
	u8*			m_propertyTypes;
	u8			m_propertyCount;
	u8			m_propertyMax;		// Current buffer size by maximum number of properties.
	bool		m_free;

	CKLBPropertyBag		*	m_prev;
	CKLBPropertyBag		*	m_next;



	static void compact();
/*
	static CKLBPropertyBag 	bags			[MAX_PROPERTYBAG_COUNT];
	static _v 				properties		[MAX_PROP_BUFFER_COUNT];
	static u8				propertyTypes	[MAX_PROP_BUFFER_COUNT];
	static char				strings			[STRING_BUFFER_SIZE];

	static u32				propAlloc;
	static u32				bagAlloc;
	static u32				stringAlloc;
	static bool				deletionFlag;
	*/

	static CKLBPropertyBag	*	ms_begin;
	static CKLBPropertyBag	*	ms_end;

	enum {
		PROPERTY_BLOCK_COUNT = 10
	};
};

#endif
