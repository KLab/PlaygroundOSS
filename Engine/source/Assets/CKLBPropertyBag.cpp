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
#include "CKLBPropertyBag.h"
#include <string.h>

/*
u32 CKLBPropertyBag::propAlloc		= 0;
u32 CKLBPropertyBag::bagAlloc		= 0;
u32 CKLBPropertyBag::stringAlloc	= 0;
bool CKLBPropertyBag::deletionFlag	= false;

//
// Global Array
//
CKLBPropertyBag			CKLBPropertyBag::bags			[MAX_PROPERTYBAG_COUNT];
CKLBPropertyBag::_v		CKLBPropertyBag::properties		[MAX_PROP_BUFFER_COUNT];
u8						CKLBPropertyBag::propertyTypes	[MAX_PROP_BUFFER_COUNT];
char					CKLBPropertyBag::strings		[STRING_BUFFER_SIZE];
*/
CKLBPropertyBag		*	CKLBPropertyBag::ms_begin = 0;
CKLBPropertyBag		*	CKLBPropertyBag::ms_end   = 0;


enum E_TYPE {
	UNDEFINED_TYPE	= 0,
	INT_TYPE		= 1,
	BOOL_TYPE		= 2,
	FLOAT_TYPE		= 3,
	STRING_TYPE		= 4,
};

/*static*/ CKLBPropertyBag*	CKLBPropertyBag::getPropertyBag() {
	return KLBNEW(CKLBPropertyBag);
/*
	// 1. Perform compaction
	compact();

	// 2. Allocate
	for (u32 n=0; n < bagAlloc; n++) {
		if (bags[n].m_free) {
			return &bags[n];
		}
	}

	// 3. Not found : Extend...
	if (bagAlloc < MAX_PROPERTYBAG_COUNT) {
		// ok
		bags[bagAlloc].m_free = true;		
		return &bags[bagAlloc++];
	} else {
		// Reach full end.
		klb_assertAlways("Property Bag Pool fully used.");
		return NULL;
	}
*/
}

/*static*/ void CKLBPropertyBag::releasePropertyBag(CKLBPropertyBag* pBag) {
	KLBDELETE(pBag);
/*
	pBag->m_free = true;
	deletionFlag = true;
*/
}
	
CKLBPropertyBag::CKLBPropertyBag()
: m_prev            (NULL)
, m_next            (NULL)
, m_propertyValues  (NULL)
, m_propertyTypes   (NULL)
, m_propertyCount   (0)
, m_propertyMax     (0)
{
	m_prev = ms_end;
	if(m_prev) {
		m_prev->m_next = this;
	} else {
		ms_begin = this;
	}
	ms_end = this;
}

CKLBPropertyBag::~CKLBPropertyBag() {

	// プロパティの持つ名前(およびstringと一体になっている)を破棄
	for(int i = 0; i < m_propertyCount; i++) {
		KLBDELETEA(m_propertyValues[i].name);
	}
	KLBDELETEA(m_propertyValues);
	KLBDELETEA(m_propertyTypes);

	// 自身をリンクから切り離す
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

bool CKLBPropertyBag::init() {
	return true;
/*
	bool res = true;
	
	this->m_propertyValues	= &properties		[propAlloc];
	this->m_propertyTypes	= &propertyTypes	[propAlloc];
	this->m_propertyCount	= 0;
	this->m_free			= !res;
	return res;
*/
}

const char*	CKLBPropertyBag::allocateName(const char* originalName, int addlen) {
	u32 len = strlen(originalName) + 1;
	char * buf = KLBNEWA(char, len + addlen);
	memcpy(buf, originalName, len);
	return (const char *)buf;
}

/*static*/
void CKLBPropertyBag::compact() {
/*
	//
	// Do NOT compact PropertyBag array itself -> Pointer will change !
	//

	if (deletionFlag) {
		deletionFlag = false;
		_v* packProp		= properties;
		u8*	packPropType	= propertyTypes;
		char* packString	= strings;

		for (u32 n=0; n < bagAlloc; n++) {
			if (bags[n].m_free == false) {
				CKLBPropertyBag* pBag = &bags[n];

				//
				// Move properties.
				//
				if (pBag->m_propertyValues != packProp) {
					memcpy(packProp, pBag->m_propertyValues, sizeof(_v) * pBag->m_propertyCount);
					memcpy(packPropType, pBag->m_propertyTypes, sizeof(u8) * pBag->m_propertyCount);
					pBag->m_propertyValues	= packProp;
					pBag->m_propertyTypes	= packPropType;
				}

				packProp		+= pBag->m_propertyCount;
				packPropType	+= pBag->m_propertyCount;

				//
				// Move String name / value
				//
				for (u32 m=0; m < pBag->m_propertyCount; m++) {
					const char* str = pBag->m_propertyValues[m].name;
					u32 len = strlen(str) + 1;

					if (str != packString) 
					{
						memcpy(packString, str, len);
						pBag->m_propertyValues[m].name = packString;
					}
					packString += len;

					if (pBag->m_propertyTypes[m] == STRING_TYPE) {
						str = pBag->m_propertyValues[m].v.s;
						len = strlen(str) + 1;
						if (pBag->m_propertyValues[m].name != packString)
						{
							memcpy(packString, str, len);
							pBag->m_propertyValues[m].v.s = packString;
						}
						packString += len;
					}
				}
			}
		}

		// Compact string allocator.
		stringAlloc = packString - strings;
		// Compact prop allocator;
		propAlloc	= packProp - properties;
	}
	*/
}

void
CKLBPropertyBag::appendProperty()
{
	int cnt = m_propertyCount + 1;
    if(cnt <= m_propertyMax) { return; }

	cnt = m_propertyMax + PROPERTY_BLOCK_COUNT;
	_v * tmpValues = KLBNEWA(_v, cnt);
	u8 * tmpTypes  = KLBNEWA(u8, cnt);
	if(m_propertyValues) {
		memcpy(tmpValues, m_propertyValues, sizeof(_v) * m_propertyCount);
		memcpy(tmpTypes , m_propertyTypes,  sizeof(u8) * m_propertyCount);
		KLBDELETEA(m_propertyValues);
		KLBDELETEA(m_propertyTypes);
	}
	m_propertyValues= tmpValues;
	m_propertyTypes = tmpTypes;
	m_propertyMax   = cnt;
}


void  CKLBPropertyBag::setPropertyInt(const char* name, s32 value) {
	// klb_assert(propAlloc < MAX_PROP_BUFFER_COUNT, "No more space for properties");
	appendProperty();
	m_propertyValues[m_propertyCount].name = allocateName(name);
	m_propertyValues[m_propertyCount].v.i  = value;
	m_propertyTypes[m_propertyCount]       = INT_TYPE;
	m_propertyCount++;
}

void CKLBPropertyBag::setPropertyBool(const char* name, bool value) {
	//klb_assert(propAlloc < MAX_PROP_BUFFER_COUNT, "No more space for properties");
	appendProperty();
	m_propertyValues[m_propertyCount].name = allocateName(name);
	m_propertyValues[m_propertyCount].v.b  = value;
	m_propertyTypes[m_propertyCount]       = BOOL_TYPE;
	m_propertyCount++;
}

void CKLBPropertyBag::setPropertyFloat(const char* name, float value) {
	//klb_assert(propAlloc < MAX_PROP_BUFFER_COUNT, "No more space for properties");
	appendProperty();
	m_propertyValues[m_propertyCount].name = allocateName(name);
	m_propertyValues[m_propertyCount].v.f  = value;
	m_propertyTypes[m_propertyCount]       = FLOAT_TYPE;
	m_propertyCount++;
}

void CKLBPropertyBag::setPropertyString(const char* name, const char* value) {
	//klb_assert(propAlloc < MAX_PROP_BUFFER_COUNT, "No more space for properties");
	appendProperty();

	int namelen  = strlen(name) + 1;
	int valuelen = strlen(value) + 1;

	const char * vname = allocateName(name, valuelen);
	char * vstring = (char *)vname + namelen;
	strcpy(vstring, value);

	m_propertyValues[m_propertyCount].name = vname;
	m_propertyValues[m_propertyCount].v.s  = vstring;
	m_propertyTypes[m_propertyCount]       = STRING_TYPE;
	m_propertyCount++;
}

s32 CKLBPropertyBag::getIndex(const char* name) {
	for(u32 n = 0; n < m_propertyCount; n++) {
		if (strcmp(name, m_propertyValues[n].name) == 0) {
			return n;
		}
	}
	
	return -1;
}

u32 CKLBPropertyBag::getFieldType(const char* name) {
	s32 idx = getIndex(name);
	if (idx != -1) {
		return m_propertyTypes[idx];
	} else {
		return UNDEFINED_TYPE;
	}
}

s32 CKLBPropertyBag::getPropertyInt(const char* name) {
	s32 idx = getIndex(name);
	if ((idx != -1) && (m_propertyTypes[idx] == INT_TYPE)) {
		return m_propertyValues[idx].v.i;
	} else {
		klb_assertAlways("Unknown property or non matching type %s", name);
		return 0;
	}
}

bool CKLBPropertyBag::getPropertyBool(const char* name) {
	s32 idx = getIndex(name);
	if (idx != -1) {
		if (m_propertyTypes[idx] == BOOL_TYPE) {
			return m_propertyValues[idx].v.b;
		} else if (m_propertyTypes[idx] == INT_TYPE) {
			return m_propertyValues[idx].v.i ? true : false;
		}
	}

	klb_assertAlways("Unknown property or non matching type %s", name);
	return false;
}

float CKLBPropertyBag::getPropertyFloat(const char* name) {
	s32 idx = getIndex(name);
	if ((idx != -1) && (m_propertyTypes[idx] == BOOL_TYPE)) {
		return m_propertyValues[idx].v.f;
	} else {
		klb_assertAlways("Unknown property or non matching type %s", name);
		return 0.0f;
	}
}

const char* CKLBPropertyBag::getPropertyString(const char* name) {
	s32 idx = getIndex(name);
	if ((idx != -1) && (m_propertyTypes[idx] == STRING_TYPE)) {
		return m_propertyValues[idx].v.s;
	} else {
		klb_assertAlways("Unknown property or non matching type %s", name);
		return NULL;
	}
}
