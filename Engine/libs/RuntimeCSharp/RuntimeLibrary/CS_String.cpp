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
#include "CS_String.h"
#include "CS_Array.h"

#include <memory.h>
#include <cstdio>

namespace System {

// --------------------------------------------------------
// StringGlobalAllocator

// static members
uniChar*	_x_StringGlobalAllocator::s_pBuffer			= NULL;
uniChar*	_x_StringGlobalAllocator::s_pLastBegin		= NULL;
uniChar*	_x_StringGlobalAllocator::s_pWarningZone	= NULL;
uniChar*	_x_StringGlobalAllocator::s_pBufferEnd		= NULL;
String*		_x_StringGlobalAllocator::s_userList		= NULL;
#ifdef _DEBUG_STRING_
bool		_x_StringGlobalAllocator::s_isBuilding		= false;
#endif

bool _x_StringGlobalAllocator::init(u32 bufferSize) {
	s_pBuffer		= (uniChar*)CS_MALLOC(sizeof(uniChar) * bufferSize);
	s_pLastBegin	= s_pBuffer;
	s_pWarningZone	= s_pBuffer + bufferSize - bufferSize * 10 / 100;
	s_pBufferEnd	= s_pBuffer + bufferSize;
#ifdef _DEBUG_STRING_
	s_isBuilding	= false;
#endif

	return true;
}
	
uniChar* _x_StringGlobalAllocator::getStartPointer(u32 optionnalSize) {
	if(s_pLastBegin >= s_pWarningZone) {
		// TODO : garbageCollector();
		compact();
	}

	if(optionnalSize == 0) {
		return s_pLastBegin;
	} else {
		return ((&s_pLastBegin[optionnalSize]) <= s_pBufferEnd) ? s_pLastBegin : NULL;
	}
}
	
uniChar* _x_StringGlobalAllocator::getLimitPointer() {
	return s_pBufferEnd;
}
	
bool _x_StringGlobalAllocator::closeString(String* pString, uniChar* end) {
	CS_Assert(pString, "null ptr");
		
	if(end > s_pBufferEnd) {
		// With 0 default alloc size, String implementation MUST have checked.
		CS_AssertAlways("String implementation is incorrect, please fix it.");
		return false;
	} else {
		pString->m_stringBuffer	= s_pLastBegin;
		pString->m_length		= end - s_pLastBegin;
		s_pLastBegin			= end;
		if(pString->m_length == 0) {
			pString->m_stringBuffer = NULL;
		}

		// Add the String to the list
		if(s_userList) {
			System::__GCObject::_RefSetValue((__GCObject**)&pString->m_next, s_userList);
			System::__GCObject::_RefSetValue((__GCObject**)&s_userList->m_prev, pString);
		}
		System::__GCObject::_RefSetValue((__GCObject**)&s_userList, pString);
			
		return true;
	}
}

bool _x_StringGlobalAllocator::compact() {
	String*	pList = s_userList;
	while (pList) {
		String* pListNext = pList->m_next;
		if(pList->copyStringFromAllocator()) {
			pList->disconnect();	// Always return true in this case.
		} else {
			return false;
		}
		pList = pListNext;
	}
	System::__GCObject::_RefSetValue((__GCObject**)&s_userList, NULL);
	s_pLastBegin = s_pBuffer;
	return true;
}
	
// --------------------------------------------------------

// --------------------------------------------------------
// String Constructors - Destructor

// Private Constructors

String::String(bool bUseAllocator)
: m_next			(NULL)
, m_prev			(NULL)
, m_allocBuffer		(NULL)
, m_stringBuffer	(NULL)
, m_stringOffset	(0)
, m_tmpStringPtr	(NULL)
, m_pBufferOwner	(NULL)
, m_length			(0)
, m_bNotOwnBuffer	(true)
{
	if(bUseAllocator) {
	#ifdef _DEBUG_STRING_
		CS_Assert(!_x_StringGlobalAllocator::s_isBuilding, "A String is already beeing built!");
		_x_StringGlobalAllocator::s_isBuilding = true;
	#endif

		_x_StringGlobalAllocator::s_pLastBegin	= _x_StringGlobalAllocator::getStartPointer();
		m_stringBuffer							= _x_StringGlobalAllocator::s_pLastBegin;
	} else {
		m_bNotOwnBuffer = false;
	}
}

String::String(const uniChar* buffer, u32 size)
: m_next				(NULL)
, m_prev				(NULL)
, m_allocBuffer			(NULL)
, m_allocBufferObject	(NULL)
, m_stringBuffer		(buffer)
, m_stringOffset		(0)
, m_tmpStringPtr		(NULL)
, m_pBufferOwner		(NULL)
, m_length				(size)
, m_bNotOwnBuffer		(true)
{
	
}

// Public Constructors

String::String(System::Array<uniChar>* value, bool bUseAllocator)
: m_next				(NULL)
, m_prev				(NULL)
, m_allocBuffer			(NULL)
, m_allocBufferObject	(NULL)
, m_stringBuffer		(NULL)
, m_stringOffset		(0)
, m_tmpStringPtr		(NULL)
, m_pBufferOwner		(NULL)
, m_length				(0)
, m_bNotOwnBuffer		(true)
{
	if(bUseAllocator) {
		if(value && (value->_acc_gLength() > 0)) {
		#ifdef _DEBUG_STRING_
			CS_Assert(!_x_StringGlobalAllocator::s_isBuilding, "A String is already beeing built!");
			_x_StringGlobalAllocator::s_isBuilding = true;
		#endif

			_x_StringGlobalAllocator::s_pLastBegin = _x_StringGlobalAllocator::getStartPointer();
			m_stringBuffer = _x_StringGlobalAllocator::s_pLastBegin;
			memcpy((uniChar*)m_stringBuffer, (uniChar*)value->_getPArray(), value->_acc_gLength() * sizeof(uniChar));
			m_length = value->_acc_gLength();
			_appendClose();
		}
	} else {
		m_length = value->_acc_gLength();
		m_allocBuffer = (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * m_length, m_allocBufferObject);
		m_allocBufferObject->_addOwner(this);
		m_stringBuffer = m_allocBuffer;
		memcpy((uniChar*)m_stringBuffer, (uniChar*)value->_getPArray(), value->_acc_gLength() * sizeof(uniChar));
		m_bNotOwnBuffer = false;
	}
}

String::String(uniChar c, s32 count, bool bUseAllocator)
: m_next				(NULL)
, m_prev				(NULL)
, m_allocBuffer			(NULL)
, m_allocBufferObject	(NULL)
, m_stringBuffer		(NULL)
, m_stringOffset		(0)
, m_tmpStringPtr		(NULL)
, m_pBufferOwner		(NULL)
, m_bNotOwnBuffer		(true)
{
	if(count < 0) { THROW(CS_NEW ArgumentOutOfRangeException()); }

	if(bUseAllocator) {
	#ifdef _DEBUG_STRING_
		CS_Assert(!_x_StringGlobalAllocator::s_isBuilding, "A String is already beeing built!");
		_x_StringGlobalAllocator::s_isBuilding = true;
	#endif

		m_stringBuffer	= _x_StringGlobalAllocator::getStartPointer();
		m_length		= count;
		_x_StringGlobalAllocator::s_pLastBegin = _x_StringGlobalAllocator::getStartPointer();
		memset16((uniChar*)m_stringBuffer, c, sizeof(uniChar) * count);
		_appendClose();
	} else {
		m_length = count;
		m_allocBuffer = (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * m_length, m_allocBufferObject);
		m_allocBufferObject->_addOwner(this);
		m_stringBuffer = m_allocBuffer;
		memset16((uniChar*)m_stringBuffer, c, sizeof(uniChar) * count);
		m_bNotOwnBuffer = false;
	}
}

String::String(const uniChar* value, s32 startIndex, s32 length) 
: m_next				(NULL)
, m_prev				(NULL)
, m_allocBuffer			(NULL)
, m_allocBufferObject	(NULL)
, m_stringBuffer		((uniChar*)value + startIndex)
, m_stringOffset		(0)
, m_tmpStringPtr		(NULL)
, m_pBufferOwner		(NULL)
, m_length				(length)
, m_bNotOwnBuffer		(true)
{

}

String::String(System::Array<uniChar>* value, s32 startIndex, s32 length, bool bUseAllocator)
: m_next				(NULL)
, m_prev				(NULL)
, m_allocBuffer			(NULL)
, m_allocBufferObject	(NULL)
, m_stringBuffer		(NULL)
, m_stringOffset		(0)
, m_tmpStringPtr		(NULL)
, m_pBufferOwner		(NULL)
, m_length				(0)
, m_bNotOwnBuffer		(true)
{
	if(!value) { THROW(CS_NEW ArgumentNullException()); }
	if(((startIndex | length) < 0) || ((startIndex + length) > value->_acc_gLength())) { THROW(CS_NEW ArgumentOutOfRangeException()); }

	if(bUseAllocator) {
		#ifdef _DEBUG_STRING_
			CS_Assert(!_x_StringGlobalAllocator::s_isBuilding, "A String is already beeing built!");
			_x_StringGlobalAllocator::s_isBuilding = true;
		#endif

		_x_StringGlobalAllocator::s_pLastBegin = _x_StringGlobalAllocator::getStartPointer();
		m_stringBuffer = _x_StringGlobalAllocator::s_pLastBegin;
		memcpy((uniChar*)m_stringBuffer, (uniChar*)value->_getPArray() + startIndex, length * sizeof(uniChar));
		m_length = length;
		_appendClose();
	} else {
		m_length = length;
		m_allocBuffer = (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * m_length, m_allocBufferObject);
		m_allocBufferObject->_addOwner(this);
		m_stringBuffer = m_allocBuffer;
		memcpy((uniChar*)m_stringBuffer, (uniChar*)value->_getPArray() + startIndex, length * sizeof(uniChar));
		m_bNotOwnBuffer = false;
	}
}

// Destructor
String::~String() {
	_releaseGC();
}

// --------------------------------------------------------

// --------------------------------------------------------
// Virtual methods

/*virtual*/
u32 String::_processGC() {
	if(m_pBufferOwner) 		{ Memory::pushList(m_pBufferOwner, 0);		}
	if(m_allocBufferObject)	{ Memory::pushList(m_allocBufferObject, 0);	}
	if(m_next)				{ Memory::pushList(m_next, 0);				}
	if(m_prev)				{ Memory::pushList(m_prev, 0);				}
	return COMPLETE;
}

/*virtual*/
bool String::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(String,Object);
};

/*virtual*/
void String::_move(__GCObject* prevobj, __GCObject* newobj) {
	if((__GCObject*)m_allocBufferObject == prevobj) {
		m_allocBufferObject = (__GCMalloc*)newobj;
		m_allocBuffer = (uniChar*)m_allocBufferObject->getBlock();
		m_stringBuffer = m_allocBuffer;
	}
}

/*virtual*/
void String::_releaseGC() {
	if(m_bNotOwnBuffer && m_pBufferOwner && !m_pBufferOwner->isFreed()) {
		m_pBufferOwner->_removeRef((__GCObject**)&m_pBufferOwner);
	}
	if((!disconnect()) && m_allocBufferObject && !m_allocBufferObject->isFreed()) {
		m_allocBufferObject->_removeOwner(this);
	}
	if(m_next && !m_next->isFreed()) {
		m_next->_removeRef((__GCObject**)&m_next);
	}
	if(m_prev && !m_prev->isFreed()) {
		m_prev->_removeRef((__GCObject**)&m_prev);
	}
}

/*virtual*/
void String::_moveAlert(u32 offset) {
	Object::_moveAlert(offset);
	if(m_pBufferOwner)	{ m_pBufferOwner->_moveRef((__GCObject**)((u8*)&m_pBufferOwner - offset), (__GCObject**)&m_pBufferOwner); }
	if(m_next)			{ m_next->_moveRef((__GCObject**)((u8*)&m_next - offset), (__GCObject**)&m_next); }
	if(m_prev)			{ m_prev->_moveRef((__GCObject**)((u8*)&m_prev - offset), (__GCObject**)&m_prev); }
}

// --------------------------------------------------------

// --------------------------------------------------------
// Internal methods

bool String::disconnect() {
	bool ret = true;
		
	if((!m_next) && (!m_prev)) {
		if(_x_StringGlobalAllocator::s_userList == this) {
			// Only String in the allocator.
			System::__GCObject::_RefSetValue((__GCObject**)&_x_StringGlobalAllocator::s_userList, NULL);
		} else {
			// Stand alone string, do nothing.
			ret = false;
		}
	} else {
		if(m_prev) {
			System::__GCObject::_RefSetValue((__GCObject**)&m_prev->m_next, this->m_next);
		} else {
			System::__GCObject::_RefSetValue((__GCObject**)&_x_StringGlobalAllocator::s_userList, this->m_next);
		}
			
		if(m_next) {
			System::__GCObject::_RefSetValue((__GCObject**)&m_next->m_prev, this->m_prev);
		}
	}
	if(m_next) { System::__GCObject::_RefSetValue((__GCObject**)&m_next, NULL); }
	if(m_prev) { System::__GCObject::_RefSetValue((__GCObject**)&m_prev, NULL); }
	return ret;
}

bool String::copyStringFromAllocator() {
	if(m_length) {
		m_allocBuffer = (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * m_length, m_allocBufferObject);
		m_allocBufferObject->_addOwner(this);

        if(!m_allocBuffer) {
            return false;
        }
		memcpy((uniChar*)m_allocBuffer, _getStringBuffer(), m_length * sizeof(uniChar));
	} else {
		m_allocBuffer = NULL;
	}
    
    m_stringBuffer	= m_allocBuffer;
    m_bNotOwnBuffer = false;
	m_pBufferOwner	= NULL;
	return true;
}

static const uniChar _str_$_null[]  = { 'n','u','l','l'		};	// 4
static const uniChar _str_$_true[]  = { 'T','r','u','e'		};	// 4
static const uniChar _str_$_false[] = { 'F','a','l','s','e' };	// 5
static const uniChar _str_toUpperArray[] =		{ 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F, 0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057, 0x0058, 0x0059, 0x005A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F, 0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x008D, 0x008E, 0x008F, 0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009A, 0x009B, 0x009C, 0x009D, 0x009E, 0x009F, 0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF, 0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x039C, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF, 0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF, 0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF, 0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF, 0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00F7, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x0178, 0x0100, 0x0100, 0x0102, 0x0102, 0x0104, 0x0104, 0x0106, 0x0106, 0x0108, 0x0108, 0x010A, 0x010A, 0x010C, 0x010C, 0x010E, 0x010E, 0x0110, 0x0110, 0x0112, 0x0112, 0x0114, 0x0114, 0x0116, 0x0116, 0x0118, 0x0118, 0x011A, 0x011A, 0x011C, 0x011C, 0x011E, 0x011E, 0x0120, 0x0120, 0x0122, 0x0122, 0x0124, 0x0124, 0x0126, 0x0126, 0x0128, 0x0128, 0x012A, 0x012A, 0x012C, 0x012C, 0x012E, 0x012E, 0x0130, 0x0049, 0x0132, 0x0132, 0x0134, 0x0134, 0x0136, 0x0136, 0x0138, 0x0139, 0x0139, 0x013B, 0x013B, 0x013D, 0x013D, 0x013F, 0x013F, 0x0141, 0x0141, 0x0143, 0x0143, 0x0145, 0x0145, 0x0147, 0x0147, 0x0149, 0x014A, 0x014A, 0x014C, 0x014C, 0x014E, 0x014E, 0x0150, 0x0150, 0x0152, 0x0152, 0x0154, 0x0154, 0x0156, 0x0156, 0x0158, 0x0158, 0x015A, 0x015A, 0x015C, 0x015C, 0x015E, 0x015E, 0x0160, 0x0160, 0x0162, 0x0162, 0x0164, 0x0164, 0x0166, 0x0166, 0x0168, 0x0168, 0x016A, 0x016A, 0x016C, 0x016C, 0x016E, 0x016E, 0x0170, 0x0170, 0x0172, 0x0172, 0x0174, 0x0174, 0x0176, 0x0176, 0x0178, 0x0179, 0x0179, 0x017B, 0x017B, 0x017D, 0x017D, 0x0053 };
static const uniChar _str_toLowerArray[] =		{ 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F, 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F, 0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067, 0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F, 0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077, 0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F, 0x0080, 0x0081, 0x0082, 0x0083, 0x0084, 0x0085, 0x0086, 0x0087, 0x0088, 0x0089, 0x008A, 0x008B, 0x008C, 0x008D, 0x008E, 0x008F, 0x0090, 0x0091, 0x0092, 0x0093, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009A, 0x009B, 0x009C, 0x009D, 0x009E, 0x009F, 0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF, 0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF, 0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF, 0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00D7, 0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00DF, 0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF, 0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF, 0x0101, 0x0101, 0x0103, 0x0103, 0x0105, 0x0105, 0x0107, 0x0107, 0x0109, 0x0109, 0x010B, 0x010B, 0x010D, 0x010D, 0x010F, 0x010F, 0x0111, 0x0111, 0x0113, 0x0113, 0x0115, 0x0115, 0x0117, 0x0117, 0x0119, 0x0119, 0x011B, 0x011B, 0x011D, 0x011D, 0x011F, 0x011F, 0x0121, 0x0121, 0x0123, 0x0123, 0x0125, 0x0125, 0x0127, 0x0127, 0x0129, 0x0129, 0x012B, 0x012B, 0x012D, 0x012D, 0x012F, 0x012F, 0x0069, 0x0131, 0x0133, 0x0133, 0x0135, 0x0135, 0x0137, 0x0137, 0x0138, 0x013A, 0x013A, 0x013C, 0x013C, 0x013E, 0x013E, 0x0140, 0x0140, 0x0142, 0x0142, 0x0144, 0x0144, 0x0146, 0x0146, 0x0148, 0x0148, 0x0149, 0x014B, 0x014B, 0x014D, 0x014D, 0x014F, 0x014F, 0x0151, 0x0151, 0x0153, 0x0153, 0x0155, 0x0155, 0x0157, 0x0157, 0x0159, 0x0159, 0x015B, 0x015B, 0x015D, 0x015D, 0x015F, 0x015F, 0x0161, 0x0161, 0x0163, 0x0163, 0x0165, 0x0165, 0x0167, 0x0167, 0x0169, 0x0169, 0x016B, 0x016B, 0x016D, 0x016D, 0x016F, 0x016F, 0x0171, 0x0171, 0x0173, 0x0173, 0x0175, 0x0175, 0x0177, 0x0177, 0x00FF, 0x017A, 0x017A, 0x017C, 0x017C, 0x017E };
static const uniChar _str_whiteSpaceArray[] =	{ 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x0020, 0x0085, 0x00A0, 0x1680, 0x180E, 0x2000, 0x2001, 0x2002, 0x2003, 0x2004, 0x2005, 0x2006, 0x2007, 0x2008, 0x2009, 0x200A, 0x2028, 0x2029, 0x202F, 0x205F, 0x3000 };
static const System::Array<uniChar>* _str_whiteSpaceSystemArray = NULL;

/* Switch to faster algorithm*/

int String::_leftSearch(String* source, String* pattern, s32 startSearch, s32 searchCount) {
	// Negative search count or startSearch = search space smaller than pattern length !
	if((searchCount | startSearch) < 0) {
		return -1;
	}

	const uniChar* pSrc		= source->_getStringBuffer() + startSearch;
	const uniChar* pESrc	= pSrc + searchCount;
	const uniChar* pDstO	= pattern->_getStringBuffer();
	const uniChar* pDstE	= pDstO + pattern->m_length;

	while (pSrc < pESrc) {
		const uniChar* pSrcLocal	= pSrc;
		const uniChar* pDst			= pDstO;
		while (pDst < pDstE) {
			if((*pDst) != (*pSrcLocal++)) {
				break;
			}
			pDst++;
		}

		if(pDst == pDstE) {
			return pSrc - source->_getStringBuffer();
		}
		pSrc++;
	}

	return -1;
}

int String::_rightSearch(String* source, String* pattern, s32 startSearch, s32 searchCount) {
	// Negative search count or startSearch = search space smaller than pattern length !
	if((searchCount | startSearch) < 0) {
		return -1;
	}
	if(searchCount > startSearch) {
		searchCount = startSearch;
	}

	const uniChar* pSrc		= source->_getStringBuffer() + startSearch;
	const uniChar* pESrc	= source->_getStringBuffer() + startSearch - searchCount -1;
	const uniChar* pDstO	= pattern->_getStringBuffer();
	const uniChar* pDstE	= pDstO + pattern->m_length;

	while(pSrc > pESrc) {
		const uniChar* pSrcLocal	= pSrc;
		const uniChar* pDst			= pDstO;
		while(pDst < pDstE) {
			if((*pDst) != (*pSrcLocal++)) {
				break;
			}
			pDst++;
		}

		if(pDst == pDstE) {
			return pSrc - source->_getStringBuffer();
		}
		pSrc--;
	}

	return -1;
}

int String::_leftSearchAny(String* source, Array<uniChar>* array_, s32 startSearch, s32 searchCount) {
	// Negative search count or startSearch = search space smalled than pattern length !
	if((searchCount | startSearch) < 0) {
		return -1;
	}

	const uniChar* pSrc		= source->_getStringBuffer() + startSearch;
	const uniChar* pESrc	= pSrc + searchCount;
	const uniChar* pDstO	= &array_->_idx_g_0based(0);
	const uniChar* pDstE	= pDstO + array_->_acc_gLength();

	while (pSrc < pESrc) {
		const uniChar* pDst	= pDstO;
		while (pDst < pDstE) {
			if((*pDst) == (*pSrc)) {
				break;
			}
			pDst++;
		}

		if(pDst != pDstE) {
			return pSrc - source->_getStringBuffer();
		}

		pSrc++;
	}

	return -1;
}

int String::_rightSearchAny(String* source, Array<uniChar>* array_, s32 startSearch, s32 searchCount) {
	// Negative search count or startSearch = search space smalled than pattern length !
	if((searchCount | startSearch) < 0) {
		return -1;
	}
	if(searchCount > startSearch) {
		searchCount = startSearch;
	}

	const uniChar* pSrc		= source->_getStringBuffer() + startSearch;
	const uniChar* pESrc	= source->_getStringBuffer() + startSearch - searchCount -1;
	const uniChar* pDstO	= &array_->_idx_g_0based(0);
	const uniChar* pDstE	= pDstO + array_->_acc_gLength();

	while (pSrc > pESrc) {
		const uniChar* pDst	= pDstO;
		while (pDst < pDstE) {
			if((*pDst) == (*pSrc)) {
				break;
			}
			pDst++;
		}

		if(pDst != pDstE) {
			return pSrc - source->_getStringBuffer();
		}

		pSrc--;
	}

	return -1;
}

void asciiToUnicode16(u8* pSrc, u32 len, uniChar* pDst) {
	u8* pSrcE = &pSrc[len];
	while (pSrc != pSrcE) {
		*pDst++ = *pSrc++;
	}
}

const uniChar* String::_getStringBuffer() const {
	if(m_bNotOwnBuffer) {
		if(m_pBufferOwner) {
			return m_pBufferOwner->m_stringBuffer + m_stringOffset;
		}
	}
	return m_stringBuffer;
}

// --------------------------------------------------------

// --------------------------------------------------------
// Properties

s32 String::_acc_gLength() {
	return m_length;
}

const uniChar& String::operator[](s32 index) const  {
	CHCKTHIS;
	if((u32)index >= m_length) { THROW(CS_NEW IndexOutOfRangeException()); }
	return *(_getStringBuffer() + index);
}

// --------------------------------------------------------

// --------------------------------------------------------
// Operator Overload


// --------------------------------------------------------

// --------------------------------------------------------
// Static
/*static*/ // See String::init() function for initialization.
String* String::Empty = NULL;

/*static*/
s32 String::Compare(String* strA, String* strB) {
	if(strA == strB) {
		return 0;		// Same pointer, same string. Valid for null.
	} else {
		if(!strA) {
			return -1;
		}
		if(!strB) {
			return +1;
		}

		const uniChar* aBuff = strA->_getStringBuffer();
		const uniChar* bBuff = strB->_getStringBuffer();
		u32 lenA		= strA->m_length;
		u32 lenB		= strB->m_length;
		u32 parseLen	= lenA < lenB ? lenA : lenB;
		u32 parseNow	= 0;
		while (parseNow != parseLen) {
			uniChar a = *aBuff++;
			uniChar b = *bBuff++;

			// Without any CompareOptions C# will consider a lower case character is before its upper character.
			if((a >= 0x0061 && a <= 0x017E) && b == _str_toUpperArray[a-0x0061]) {
				return -1;
			} else if((b >= 0x0061 && b <= 0x017E) && a == _str_toUpperArray[b-0x0061]) {
				return 1;
			} else {
				if(a < b) { return -1; }
				if(a > b) { return +1; }
			}
			parseNow++;
		}

		// Reached last char of shortest string.
		if(parseNow < lenA) { return 1;  }
		if(parseNow < lenB) { return -1; }

		// Both size were equal and content is the same.
		return 0;
	}
}

/*static*/
s32 String::Compare(String* strA, String* strB, bool ignoreCase) {
	if(ignoreCase == false) {
		return Compare(strA, strB);
	}

	if(strA == strB) {
		return 0;		// Same pointer, same string. Valid for null.
	} else {
		if(!strA) {
			return -1;
		}
		if(!strB) {
			return +1;
		}

		const uniChar* aBuff = strA->_getStringBuffer();
		const uniChar* bBuff = strB->_getStringBuffer();
		u32 lenA		= strA->m_length;
		u32 lenB		= strB->m_length;
		u32 parseLen	= lenA < lenB ? lenA : lenB;
		u32 parseNow	= 0;
		while (parseNow != parseLen) {
			uniChar a = *aBuff++;
			uniChar b = *bBuff++;
			
			// to lower case
			if(a >= 0x0041 && a <= 0x017D) { a = _str_toLowerArray[a-0x0041]; }
			if(b >= 0x0041 && b <= 0x017D) { b = _str_toLowerArray[b-0x0041]; }			

			if(a < b) { return -1; }
			if(a > b) { return +1; }
			parseNow++;
		}

		// Reached last char of shortest string.
		if(parseNow < lenA) { return 1;  }
		if(parseNow < lenB) { return -1; }

		// Both size were equal and content is the same.
		return 0;
	}
}

String* String::Concat(Object* obj) {
	return obj->ToString();
}

String* String::Concat(/*params*/ Array<Object*>* args) {
	if(!args)	{ THROW(CS_NEW ArgumentNullException()); }
	
	// [ToRemove] when allocator issue is solved in Compilator - begin
	String* pS = CS_NEW String(false);
	if(!pS)		{ THROW(CS_NEW OutOfMemoryException()); }

	for(int n=0; n < args->_acc_gLength(); n++) {
		if(args->_idx_g(n)) {
			pS->m_length += args->_idx_g(n)->ToString()->_acc_gLength();
		}
	}

	pS->m_allocBuffer = (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * pS->m_length, pS->m_allocBufferObject);
	pS->m_allocBufferObject->_addOwner(pS);
	pS->m_stringBuffer = pS->m_allocBuffer;
	// [ToRemove] - end

	u32 currentLen = 0;
	for(int n=0; n < args->_acc_gLength(); n++) {
		Object* obj = args->_idx_g(n);
		if(obj) {
			// uses allocator
			//pS->_appendStr(obj->ToString());
			String* strObj = obj->ToString();
			memcpy((uniChar*)pS->m_stringBuffer + currentLen, strObj->_getStringBuffer(), strObj->m_length * sizeof(uniChar));
			currentLen += strObj->m_length;
		}

	}
	
	// uses allocator
	//return pS->_appendClose();
	return pS;
}

String* String::Concat(/*params*/ Array<String*>* values) {

	// [ToRemove] when allocator issue is solved in Compilator - begin
	String* pS = CS_NEW String(false);
	if(!pS)		{ THROW(CS_NEW OutOfMemoryException()); }

	for(int n=0; n < values->_acc_gLength(); n++) {
		if(values->_idx_g(n)) {
			pS->m_length += values->_idx_g(n)->_acc_gLength();
		}
	}

	pS->m_allocBuffer = (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * pS->m_length, pS->m_allocBufferObject);
	pS->m_allocBufferObject->_addOwner(pS);
	pS->m_stringBuffer = pS->m_allocBuffer;
	// [ToRemove] - end

	u32 currentLen = 0;
	for(int n=0; n < values->_acc_gLength(); n++) {
		String* str = values->_idx_g(n);
		if(str) {
			// uses allocator
			//pS->_appendStr(str);
			memcpy((uniChar*)pS->m_stringBuffer + currentLen, str->_getStringBuffer(), str->m_length * sizeof(uniChar));
			currentLen += str->m_length;
		}
	}
	// uses allocator
	//return pS->_appendClose();
	return pS;
}

String* String::Copy(String* str) {
	// Must create a new String object but content pointer can be the same.
	String* newStr = CS_NEW String(false);
	if(!newStr) THROW(CS_NEW OutOfMemoryException());
	newStr->m_length		= str->m_length;
	newStr->m_stringBuffer	= str->m_stringBuffer;
	newStr->m_stringOffset	= str->m_stringOffset;
    newStr->m_bNotOwnBuffer	= true;
    newStr->m_pBufferOwner	= str;
    str->_addRef((__GCObject**)&newStr->m_pBufferOwner);
	return newStr;
}

bool String::Equals(String* a, String* b) {
	return (Compare(a, b) == 0);
}

/*x*/	static String* Format(String* format, Object* arg0);
/*x*/	static String* Format(String* format, /*params*/ Array<Object*>* args);

bool String::IsNullOrEmpty(String* value) {
	return value ? (value->m_length == 0) : true;
}

/*static*/
String* String::Join(String* separator, Array<String*>* value) {
	if(!value) { THROW(CS_NEW ArgumentNullException()); }
	
	if(!separator) { return String::Join(String::Empty, value); }

	String* newStr	= CS_NEW String(false);
	if(!newStr) THROW(CS_NEW OutOfMemoryException());

	// [ToRemove] when allocator issue is solved in Compilator - begin
	for(int i = 0; i < value->_acc_gLength(); ++i) {
		newStr->m_length += value->_idx_g(i)->_acc_gLength();
	}
	if(value->_acc_gLength() > 0) {
		newStr->m_length += separator->m_length * (value->_acc_gLength() - 1);
	}

	newStr->m_allocBuffer = (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * newStr->m_length, newStr->m_allocBufferObject);
	newStr->m_allocBufferObject->_addOwner(newStr);
	newStr->m_stringBuffer = newStr->m_allocBuffer;
	newStr->m_bNotOwnBuffer = false;
	// [ToRemove] - end

	u32 currentLen = 0;
	for(int i = 0; i < value->_acc_gLength() - 1; ++i) {
		// uses Allocator
		//newStr->_appendStr(value->_idx_g(i))->_appendStr(separator);
		memcpy((uniChar*)newStr->m_stringBuffer + currentLen, value->_idx_g(i)->_getStringBuffer(), value->_idx_g(i)->m_length * sizeof(uniChar));
		currentLen += value->_idx_g(i)->m_length;
		memcpy((uniChar*)newStr->m_stringBuffer + currentLen, separator->_getStringBuffer(), separator->m_length * sizeof(uniChar));
		currentLen += separator->m_length;
	}

	// uses Allocator
	//return newStr->_appendStr(value->_idx_g(value->_acc_gLength() - 1))->_appendClose();
	memcpy((uniChar*)newStr->m_stringBuffer + currentLen, value->_idx_g(value->_acc_gLength() - 1)->_getStringBuffer(), value->_idx_g(value->_acc_gLength() - 1)->m_length * sizeof(uniChar));
	return newStr;
}

/*static*/
String* String::Join(String* separator, Array<String*>* value, s32 startIndex, s32 count) {
	if(!value) { THROW(CS_NEW ArgumentNullException()); }
	if((startIndex < 0) || (count < 0) || (startIndex + count) > value->_acc_gLength()) { THROW(CS_NEW ArgumentOutOfRangeException()); }

	if(!separator) { return String::Join(String::Empty, value, startIndex, count); }

	String* newStr = CS_NEW String(false);
	if(!newStr) { THROW(CS_NEW OutOfMemoryException()); }

	// [ToRemove] when allocator issue is solved in Compilator - begin
	for(int i = startIndex; i < startIndex + count; ++i) {
		newStr->m_length += value->_idx_g(i)->_acc_gLength();
	}
	if(value->_acc_gLength() > 0) {
		newStr->m_length += separator->m_length * (count - 1);
	}

	newStr->m_allocBuffer = (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * newStr->m_length, newStr->m_allocBufferObject);
	newStr->m_allocBufferObject->_addOwner(newStr);
	newStr->m_stringBuffer = newStr->m_allocBuffer;
	newStr->m_bNotOwnBuffer = false;
	// [ToRemove] - end

	u32 currentLen = 0;
	for(int i = startIndex; i < startIndex + count - 1; ++i) {
		// uses Allocator
		//newStr->_appendStr(value->_idx_g(i))->_appendStr(separator);
		memcpy((uniChar*)newStr->m_stringBuffer + currentLen, value->_idx_g(i)->_getStringBuffer(), value->_idx_g(i)->m_length * sizeof(uniChar));
		currentLen += value->_idx_g(i)->m_length;
		memcpy((uniChar*)newStr->m_stringBuffer + currentLen, separator->_getStringBuffer(), separator->m_length * sizeof(uniChar));
		currentLen += separator->m_length;
	}
	
	// uses Allocator
	//return newStr->_appendStr(value->_idx_g(startIndex + count - 1))->_appendClose();
	memcpy((uniChar*)newStr->m_stringBuffer + currentLen, value->_idx_g(startIndex + count - 1)->_getStringBuffer(), value->_idx_g(startIndex + count - 1)->m_length * sizeof(uniChar));
	return newStr;
}

// --------------------------------------------------------

// --------------------------------------------------------
// Public methods

Object* String::Clone() {
	return (Object*)this;
}

s32 String::CompareTo(Object* value) {
	if(!value->_isInstanceOf(_TYPE_STRING)) {
		THROW(CS_NEW ArgumentException());
	}
	return Compare(this, (value ? value->ToString() : NULL));
}

s32 String::CompareTo(String* strB) {
	return String::Compare(this, strB);
}

bool String::Contains(String* value) {
	if(!value) { THROW(CS_NEW ArgumentNullException()); }

	// Cheap trick : no way that value can fit into this string.
	if(value->m_length > this->m_length) {
		return false;
	}

	return (_leftSearch(this, value, 0, (this->m_length - value->m_length) + 1) != -1);
}

void String::CopyTo(s32 sourceIndex, Array<uniChar>* destination, s32 destinationIndex, s32 count) {
	if(!destination) { THROW(CS_NEW ArgumentNullException()); }
	if(((sourceIndex | destinationIndex | count) < 0) || ((u32)(sourceIndex + count) > m_length) || (destinationIndex + count > destination->_acc_gLength())) {
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	memcpy((u8*)(destination->_getPArray()) + destinationIndex * sizeof(uniChar), _getStringBuffer() + sourceIndex, count * sizeof(uniChar));
}

bool String::EndsWith(String* value) {
	if(!value) { THROW(CS_NEW ArgumentNullException()); }
	return (_leftSearch(this, value, (m_length - value->m_length), 1) != -1);
}

bool String::Equals(Object* obj) {
	if(!obj) {
		return false;
	}

	if(!obj->_isInstanceOf(_TYPE_STRING)) {
		return false;
	}
	return Equals(obj->ToString());
}

bool String::Equals(String* value) {
	return (Compare(this, value) == 0);
}

Collections::Generic::IEnumerator<uniChar>* String::GetEnumerator() {
	return CS_NEW CharEnumerator(this);
}

s32 String::GetHashCode() {
	/*
	const uniChar* chPtr = this->_getStringBuffer();
	int num = 352654597;
	int num2 = num;
	int* numPtr = (int*)chPtr;
	for (u32 i = this->m_length; i > 0; i -= 4)
	{
	    num = (((num << 5) + num) + (num >> 27)) ^ numPtr[0];
	    if(i <= 2)
	    {
		break;
	    }
	    num2 = (((num2 << 5) + num2) + (num2 >> 27)) ^ numPtr[1];
	    numPtr += 2;
	}
	return (num + (num2 * 1566083941));
    */
	
	//
	// Reimplementation Based on MSFT algorithm as seen on :
	// http://www.dotnetperls.com/gethashcode
	//
	// Could switch to https://github.com/PeterScott/murmur3/blob/master/murmur3.c if necessary.
	//
	const uniChar* chPtr	= this->_getStringBuffer();
	int num					= 0x15051505;
	int num2				= num;
	int* numPtr				= (int*)chPtr;
	int* numPtrE			= &numPtr[(this->m_length & 0xFFFFFFFC)>>1];	// Array of unicode pair end.
	
	// Process 2 unicode char x 2 time / iteration.
	while (numPtr != numPtrE) {
		num		= (((num  << 5) + num ) + (num  >> 27)) ^ (*numPtr++);
		num2	= (((num2 << 5) + num2) + (num2 >> 27)) ^ (*numPtr++);
	}

	// Process last pair of character.
	if(!(this->m_length & 4)) {
		num		= (((num  << 5) + num ) + (num  >> 27)) ^ (*numPtr++);
	}
	return (num + (num2 * 0x5D588B65));
	
}

/*x*/	/*TypeCode GetTypeCode		();*/

s32 String::IndexOf(uniChar value) {
	// Local Object
	String l((const uniChar*)&value, 1); 
	return _leftSearch(this, &l, 0, this->m_length);
}

s32 String::IndexOf(String* value) {
	if(!value) { THROW(CS_NEW ArgumentNullException()); }

	if(value->m_length == 0) {
		return -1;
	}

	return _leftSearch(this, value, 0, (this->m_length - value->m_length) + 1);
}

s32 String::IndexOf(uniChar value, s32 startIndex) {
	if((startIndex < 0) || ((u32)startIndex >= this->m_length)) {
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	String l((const uniChar*)&value, 1);
	return _leftSearch(this, &l, startIndex, this->m_length - startIndex);
}

s32 String::IndexOf(String* value, s32 startIndex) {
	if(!value) { THROW(CS_NEW ArgumentNullException()); }

	if(value->m_length == 0) {
		return -1;
	}

	if((startIndex < 0) || ((u32)startIndex >= this->m_length)) {
		THROW(CS_NEW ArgumentOutOfRangeException());
	}

	return _leftSearch(this, value, startIndex, ((this->m_length - value->m_length) + 1)-startIndex);
}

s32 String::IndexOf(uniChar value, s32 startIndex, s32 count) {
	if((count < 0) || (startIndex < 0) || ((u32)(startIndex + count) > this->m_length)) {
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	String l((const uniChar*)&value, 1);
	return _leftSearch(this, &l, startIndex, count);
}

s32 String::IndexOf(String* value, s32 startIndex, s32 count) {
	if(!value) {
		THROW(CS_NEW ArgumentNullException());
	}

	if(value->m_length == 0) {
		return -1;
	}	

	if((count < 0) || (startIndex < 0) || ((u32)(startIndex + count) > this->m_length)) {
		THROW(CS_NEW ArgumentOutOfRangeException());
	}

	return _leftSearch(this, value, startIndex, (count - value->m_length) + 1);
}

s32 String::IndexOfAny(Array<uniChar>* anyOf) {
	if(!anyOf) { THROW(CS_NEW ArgumentNullException()); }
	return _leftSearchAny(this, anyOf, 0, m_length);
}

s32 String::IndexOfAny(Array<uniChar>* anyOf, s32 startIndex) {
	if(!anyOf) { THROW(CS_NEW ArgumentNullException()); }
	if((((u32)startIndex) >= m_length)) {
		THROW(CS_NEW ArgumentOutOfRangeException());
	}

	return _leftSearchAny(this, anyOf, startIndex, m_length - startIndex);
}

s32 String::IndexOfAny(Array<uniChar>* anyOf, s32 startIndex, s32 count) {
	if(!anyOf) { THROW(CS_NEW ArgumentNullException()); }
	if((count < 0) || (startIndex < 0) || ((u32)(startIndex + count) > this->m_length)) {
		THROW(CS_NEW IndexOutOfRangeException());
	}

	return _leftSearchAny(this, anyOf, startIndex, count);
}

String* String::Insert(s32 startIndex, String* value) {
	if(!value)						{ THROW(CS_NEW ArgumentNullException());		}
	if((u32)startIndex > m_length)	{ THROW(CS_NEW ArgumentOutOfRangeException());	}

	// [ToRemove] when allocator issue is solved in Compilator - begin
	String* newStr = CS_NEW String(false);
	newStr->m_length = m_length + value->m_length;
	newStr->m_allocBuffer = (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * newStr->m_length, newStr->m_allocBufferObject);
	newStr->m_allocBufferObject->_addOwner(newStr);
	newStr->m_stringBuffer = newStr->m_allocBuffer;
	// [ToRemove] - end

	// uses Allocator
	//return newStr->_appendStr(this, 0, startIndex)->_appendStr(value, 0, value->m_length)->_appendStr(this, startIndex, m_length - startIndex)->_appendClose();
	memcpy((uniChar*)newStr->m_stringBuffer,								_getStringBuffer(),					sizeof(uniChar) * startIndex);
	memcpy((uniChar*)newStr->m_stringBuffer + startIndex,					value->_getStringBuffer(),			sizeof(uniChar) * value->m_length);
	memcpy((uniChar*)newStr->m_stringBuffer + startIndex + value->m_length,	_getStringBuffer() + startIndex,	sizeof(uniChar) * (m_length - startIndex));
	return newStr;
}

s32 String::LastIndexOf(uniChar value) {
	String l((const uniChar*)&value, 1);
	return _rightSearch(this, &l, this->m_length, this->m_length);
}

s32 String::LastIndexOf(String* value) {
	if(!value) { THROW(CS_NEW ArgumentNullException()); }

	if(value->m_length == 0) {
		return -1;
	}

	return _rightSearch(this, value, (this->m_length - value->m_length) + 1, (this->m_length - value->m_length) + 1);
}

s32 String::LastIndexOf(uniChar value, s32 startIndex) {
	if((startIndex < 0) || ((u32)startIndex >= this->m_length)) {
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	String l((const uniChar*)&value, 1);
	return _rightSearch(this, &l, startIndex, startIndex);
}

s32 String::LastIndexOf(String* value, s32 startIndex) {
	if(!value) { THROW(CS_NEW ArgumentNullException()); }

	if(value->m_length == 0) {
		return -1;
	}

	if((startIndex < 0) || ((u32)startIndex >= this->m_length)) {
		THROW(CS_NEW ArgumentOutOfRangeException());
	}

	return _rightSearch(this, value, startIndex, ((this->m_length - value->m_length) + 1));
}

s32 String::LastIndexOf(uniChar value, s32 startIndex, s32 count) {
	if((count < 0) || (startIndex < 0) || ((u32)(startIndex + count) > this->m_length)) {
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	String l((const uniChar*)&value, 1);
	return _rightSearch(this, &l, startIndex, count);
}

s32 String::LastIndexOf(String* value, s32 startIndex, s32 count) {
	if(!value) {
		THROW(CS_NEW ArgumentNullException());
	}

	if(value->m_length == 0) {
		return -1;
	}	

	if((count < 0) || (startIndex < 0) || ((u32)(startIndex + count) > this->m_length)) {
		THROW(CS_NEW ArgumentOutOfRangeException());
	}

	return _rightSearch(this, value, startIndex, (count - value->m_length) + 1);
}

s32 String::LastIndexOfAny(Array<uniChar>* anyOf) {
	if(!anyOf) { THROW(CS_NEW ArgumentNullException()); }
	return _rightSearchAny(this, anyOf, m_length-1, m_length-1);
}

s32 String::LastIndexOfAny(Array<uniChar>* anyOf, s32 startIndex) {
	if(!anyOf) { THROW(CS_NEW ArgumentNullException()); }
	if((((u32)startIndex) >= m_length)) {
		THROW(CS_NEW ArgumentOutOfRangeException());
	}

	return _rightSearchAny(this, anyOf, startIndex, startIndex);
}

s32 String::LastIndexOfAny(Array<uniChar>* anyOf, s32 startIndex, s32 count) {
	if(!anyOf) { THROW(CS_NEW ArgumentNullException()); }
	if((count < 0) || (startIndex < 0) || ((startIndex - count) < 0)) {
		THROW(CS_NEW IndexOutOfRangeException());
	}

	return _rightSearchAny(this, anyOf, startIndex, count);
}

String* String::PadLeft(s32 totalWidth, uniChar paddingChar) {
	if(totalWidth < 0) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if((u32)totalWidth <= m_length) { return this; }
	
	// [ToRemove] when allocator issue is solved in Compilator - begin
	String* newStr = CS_NEW String(false);
	newStr->m_length = totalWidth;
	newStr->m_allocBuffer = (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * newStr->m_length, newStr->m_allocBufferObject);
	newStr->m_allocBufferObject->_addOwner(newStr);
	newStr->m_stringBuffer = newStr->m_allocBuffer;
	// [ToRemove] - end

	// uses Allocator
	//newStr->m_length = totalWidth - m_length;
	//memset16(_x_StringGlobalAllocator::s_pLastBegin, paddingChar, newStr->m_length << 1);
	//return newStr->_appendStr(this)->_appendClose();

	memset16((uniChar*)newStr->m_stringBuffer, paddingChar, (totalWidth - m_length) * sizeof(uniChar));
	memcpy((uniChar*)newStr->m_stringBuffer + (totalWidth - m_length), _getStringBuffer(), m_length * sizeof(uniChar));

	return newStr;
}

String* String::PadRight(s32 totalWidth, uniChar paddingChar) {
	if(totalWidth < 0) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if((u32)totalWidth <= m_length) { return this; }

	// [ToRemove] when allocator issue is solved in Compilator - begin
	String* newStr = CS_NEW String(false);
	newStr->m_length = totalWidth;
	newStr->m_allocBuffer = (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * newStr->m_length, newStr->m_allocBufferObject);
	newStr->m_allocBufferObject->_addOwner(newStr);
	newStr->m_stringBuffer = newStr->m_allocBuffer;
	// [ToRemove] - end
	
	// uses Allocator
	//newStr->_appendStr(this);
	//memset16(_x_StringGlobalAllocator::s_pLastBegin + m_length, paddingChar, (totalWidth - m_length) << 1);
	//newStr->m_length += totalWidth - m_length;
	//return newStr->_appendClose();

	memcpy((uniChar*)newStr->m_stringBuffer, _getStringBuffer(), m_length * sizeof(uniChar));
	memset16((uniChar*)newStr->m_stringBuffer  + m_length, paddingChar, (totalWidth - m_length) * sizeof(uniChar));
	return newStr;
}

String* String::Remove(s32 startIndex) {
	if((u32)startIndex >= m_length) { THROW(CS_NEW ArgumentOutOfRangeException()); }

	String* newStr			= CS_NEW String(false);
	newStr->m_length		= startIndex;
	newStr->m_stringBuffer	= m_stringBuffer;
	newStr->m_stringOffset	= 0;
    newStr->m_bNotOwnBuffer	= true;
    newStr->m_pBufferOwner	= this;
	this->_addRef((__GCObject**)&newStr->m_pBufferOwner);
	return newStr;
}

String* String::Remove(s32 startIndex, s32 count) {
	if((startIndex < 0) || ((u32)(startIndex + count) > m_length)) { THROW(CS_NEW ArgumentOutOfRangeException()); }

	// uses Allocator
	//String* newStr = CS_NEW String();
	//return newStr->_appendStr(this, 0, startIndex)->_appendStr(this, startIndex + count, m_length - startIndex - count)->_appendClose();

	// [ToRemove] when allocator issue is solved in Compilator - begin
	String* newStr = CS_NEW String(false);
	newStr->m_length = m_length - count;
	newStr->m_allocBuffer = (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * newStr->m_length, newStr->m_allocBufferObject);
	newStr->m_allocBufferObject->_addOwner(newStr);
	newStr->m_stringBuffer = newStr->m_allocBuffer;

	memcpy((uniChar*)newStr->m_stringBuffer,				_getStringBuffer(),							sizeof(uniChar) * startIndex);
	memcpy((uniChar*)newStr->m_stringBuffer + startIndex,	_getStringBuffer() + startIndex + count,	sizeof(uniChar) * (m_length - count));

	return newStr;
	// [ToRemove] - end
}

String* String::Replace(uniChar oldChar, uniChar newChar) {
	// uses Allocator
	//String* newStr = CS_NEW String();
	//const uniChar* pSrc	= _getStringBuffer();
	//const uniChar* pEnd	= pSrc + m_length;
	//uniChar* pDst		= (uniChar*)newStr->m_stringBuffer; // is in StringAllocator
	//while(pSrc < pEnd) {
	//	*pDst++ = (*pSrc == oldChar) ? newChar : *pSrc;
	//	pSrc++;
	//}
	//newStr->m_length = m_length;
	//return newStr->_appendClose();

	// [ToRemove] when allocator issue is solved in Compilator - begin
	String* newStr = CS_NEW String(false);
	newStr->m_length = m_length;
	newStr->m_allocBuffer = (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * newStr->m_length, newStr->m_allocBufferObject);
	newStr->m_allocBufferObject->_addOwner(newStr);
	newStr->m_stringBuffer = newStr->m_allocBuffer;

	const uniChar* pSrc	= _getStringBuffer();
	const uniChar* pEnd	= pSrc + m_length;
	uniChar* pDst		= (uniChar*)newStr->m_stringBuffer;
	while(pSrc < pEnd) {
		*pDst++ = (*pSrc == oldChar) ? newChar : *pSrc;
		pSrc++;
	}

	return newStr;
	// [ToRemove] - end
}

String* String::Replace(String* oldValue, String* newValue) {
	if(!oldValue) { THROW(CS_NEW ArgumentNullException()); }
	if(oldValue->m_length == 0) { THROW(CS_NEW ArgumentException()); }
	
	// uses Allocator
	//String* newStr = CS_NEW String();
	//s32 idx	= IndexOf(oldValue);
	//if(idx == -1) {
	//	return newStr->_appendStr(this)->_appendClose();
	//}
	//
	//s32 startIdx	= 0;
	//while(idx != -1) {
	//	newStr->_appendStr(this, startIdx, idx - startIdx)->_appendStr(newValue);
	//	startIdx = idx + newValue->m_length;
	//	idx = IndexOf(oldValue, idx + 1);
	//}
	//return newStr->_appendStr(this, startIdx, m_length - startIdx)->_appendClose();

	// [ToRemove] when allocator issue is solved in Compilator - begin
	String* newStr = CS_NEW String(false);

	s32 idx	= IndexOf(oldValue);
	if(idx == -1) {
		newStr->m_stringBuffer  = m_stringBuffer;
		newStr->m_length		= m_length;
		if(newStr->m_length > 0) {
			newStr->m_bNotOwnBuffer = true;
			newStr->m_pBufferOwner	= this;
			this->_addRef((__GCObject**)&newStr->m_pBufferOwner);
		}
		return newStr;
	}

	newStr->m_length	= m_length;
	u32 startIdx		= 0;
	u32 lengthRatio		= newValue->m_length / oldValue->m_length;
	if(lengthRatio < 1) { lengthRatio = 1; }
	uniChar* tmpBuff = (uniChar*)CS_MALLOC(sizeof(uniChar) * m_length * lengthRatio);
	while(idx != -1) {
		memcpy(tmpBuff + startIdx,			this->_getStringBuffer(),		sizeof(uniChar) * idx);
		memcpy(tmpBuff + startIdx + idx,	newValue->_getStringBuffer(),	sizeof(uniChar) * newValue->m_length);
		newStr->m_length += newValue->m_length - oldValue->m_length;
		startIdx = idx + newValue->m_length;

		idx = IndexOf(oldValue, idx + 1);
	}
	// add last string
	memcpy(tmpBuff + startIdx, this->_getStringBuffer() + startIdx,	sizeof(uniChar) * (m_length - startIdx));

	newStr->m_allocBuffer = (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * newStr->m_length, newStr->m_allocBufferObject);
	newStr->m_allocBufferObject->_addOwner(newStr);
	newStr->m_stringBuffer = newStr->m_allocBuffer;
	memcpy((uniChar*)newStr->m_stringBuffer, tmpBuff, sizeof(uniChar) * newStr->m_length);
	CS_FREE(tmpBuff);
	
	return newStr;
	// [ToRemove] - end
}

Array<String*>* String::Split(Array<uniChar>* separator, StringSplitOptions options) {
	return Split(separator, 0xffff, options);
}

Array<String*>* String::Split(Array<String*>* separator, StringSplitOptions options) {
	return Split(separator, 0xffff, options);
}

Array<String*>* String::Split(Array<uniChar>* separator, s32 count, StringSplitOptions options) {
	if(count < 0) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	// TODO ArgumentException <= options is not one of the StringSplitOptions values.

	if(!separator || separator->_acc_gLength() == 0) {
		return Split((Array<uniChar>*) _str_whiteSpaceSystemArray, count, options);
	}

	String* newStr;
	String* prevStr			= NULL;
	const uniChar* pSrc		= _getStringBuffer();
	const uniChar* pPrev	= pSrc;
	const uniChar* pEnd		= pSrc + m_length;
	u32 idx					= 0;
	const uniChar* pOChars	= &separator->_idx_g_0based(0);
	const uniChar* pEChars	= pOChars + separator->_acc_gLength();
	while(pSrc < pEnd && idx < (u32)count - 1) {
		const uniChar* pChar	= pOChars;
		while(pChar < pEChars) {
			if(*pSrc == *pChar++) {
				if((options == None) || ((options == RemoveEmptyEntries) && (pSrc - pPrev > 0))) {
					newStr = CS_NEW String(false);
					newStr->m_stringBuffer  = m_stringBuffer;
					newStr->m_stringOffset	= m_stringOffset + pPrev - _getStringBuffer();
					newStr->m_length		= pSrc - pPrev;
					if(newStr->m_length > 0) {
						newStr->m_bNotOwnBuffer = true;
						newStr->m_pBufferOwner	= this;
						this->_addRef((__GCObject**)&newStr->m_pBufferOwner);
					}
					newStr->m_tmpStringPtr	= prevStr;
					prevStr	= newStr;
					pPrev	= pSrc + 1;
					idx++;
				} else {
					pPrev++;
				}
				break;
			}
		}
		pSrc++;
	}

	// Last String
	if(options == RemoveEmptyEntries) {
		while(pSrc < pEnd) {
			const uniChar* pChar	= pOChars;
			while (pChar < pEChars) {
				if(*pSrc == *pChar) { 
					break;
				}
				pChar++;
			}
			if(pChar == pEChars) {
				break;
			}
			pPrev = ++pSrc;
		}
	}
	newStr = CS_NEW String(false);
	newStr->m_stringBuffer  = m_stringBuffer;
	newStr->m_stringOffset	= m_stringOffset + pPrev - _getStringBuffer();
	newStr->m_length		= pEnd - pPrev ;
	if(newStr->m_length > 0) {
		newStr->m_bNotOwnBuffer = true;
		newStr->m_pBufferOwner	= this;
		this->_addRef((__GCObject**)&newStr->m_pBufferOwner);
	}
	newStr->m_tmpStringPtr	= prevStr;
	idx++;

	Array<String*>* arr = CS_NEW Array<String*>(idx);
	while(idx--) {
		arr->_idx_s(idx, newStr);
		newStr = newStr->m_tmpStringPtr;
	}

	return arr;
}

Array<String*>* String::Split(Array<String*>* separator, s32 count, StringSplitOptions options) {
	if(count < 0) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	// TODO ArgumentException <= options is not one of the StringSplitOptions values.

	if(!separator || separator->_acc_gLength() == 0) {
		return Split((Array<uniChar>*) _str_whiteSpaceSystemArray, count, options);
	}

	String* newStr;
	String* prevStr = NULL;
	const uniChar* pSrc		= _getStringBuffer();
	const uniChar* pPrev	= pSrc;
	const uniChar* pEnd		= pSrc + m_length;
	u32 idx					= 0;
	while(pSrc < pEnd && idx < (u32)count - 1) {
		for(s32 i = 0; i < separator->_acc_gLength(); ++i) {
			if(_leftSearch(this, separator->_idx_g(i), m_length - (pEnd - pSrc), 1) ==  m_length - (pEnd - pSrc)) {
				pSrc += separator->_idx_g(i)->m_length - 1;
				if((options == None) || ((options == RemoveEmptyEntries) && (pSrc - pPrev > (s32)separator->_idx_g(i)->m_length))) {
					newStr = CS_NEW String(false);
					newStr->m_stringBuffer  = m_stringBuffer;
					newStr->m_stringOffset	= m_stringOffset + pPrev - _getStringBuffer();
					newStr->m_length		= pSrc - pPrev - separator->_idx_g(i)->m_length + 1;
					newStr->m_bNotOwnBuffer = true;
					newStr->m_pBufferOwner	= this;
					this->_addRef((__GCObject**)&newStr->m_pBufferOwner);
					newStr->m_tmpStringPtr	= prevStr;
					prevStr	= newStr;
					pPrev	= pSrc + 1;
					idx++;
				} else {
					pPrev++;
				}
				break;
			}
		}
		pSrc++;
	}

	// Last String
	if(options == RemoveEmptyEntries) {
		while(pSrc < pEnd) {
			for(s32 i = 0; i < separator->_acc_gLength(); ++i) {
				if(_leftSearch(this, separator->_idx_g(i), m_length - (pEnd - pSrc), 1) ==  m_length - (pEnd - pSrc)) {
					pSrc += separator->_idx_g(i)->m_length - 1;
					pPrev = pSrc+1;
					break;
				}
			}
			if(pPrev == pSrc+1) {
				break;
			}
			pSrc++;
		}
	}
	newStr = CS_NEW String(false);
	newStr->m_stringBuffer  = m_stringBuffer;
	newStr->m_stringOffset	= m_stringOffset + pPrev - _getStringBuffer();
	newStr->m_length		= pEnd - pPrev;
	if(newStr->m_length > 0) {
		newStr->m_bNotOwnBuffer = true;
		newStr->m_pBufferOwner	= this;
		this->_addRef((__GCObject**)&newStr->m_pBufferOwner);
	}
	newStr->m_tmpStringPtr	= prevStr;
	idx++;

	Array<String*>* arr = CS_NEW Array<String*>(idx);
	while(idx--) {
		arr->_idx_s(idx, newStr);
		newStr = newStr->m_tmpStringPtr;
	}

	return arr;
}

bool String::StartsWith(String* value) {
	if(!value) { THROW(CS_NEW ArgumentNullException()); }
	return (_leftSearch(this, value, 0, 1) != -1);
}

String* String::Substring(s32 startIndex) {
	if((u32)startIndex > m_length) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if(startIndex == m_length) { return Empty; }

	String* newStr = CS_NEW String(false);
	newStr->m_stringBuffer	= m_stringBuffer;
	newStr->m_stringOffset	= m_stringOffset + startIndex;
	newStr->m_length		= m_length - startIndex;
	newStr->m_bNotOwnBuffer = true;
	newStr->m_pBufferOwner	= this;
	this->_addRef((__GCObject**)&newStr->m_pBufferOwner);
	return newStr;
}

String* String::Substring(s32 startIndex, s32 length) {
	if((startIndex < 0) || (length < 0) || ((u32)(startIndex + length) > m_length)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if(startIndex == m_length) { return Empty; }

	String* newStr = CS_NEW String(false);
	newStr->m_stringBuffer	= m_stringBuffer;
	newStr->m_stringOffset	= m_stringOffset + startIndex;
	newStr->m_length		= length;
	newStr->m_bNotOwnBuffer = true;
	newStr->m_pBufferOwner	= this;
	this->_addRef((__GCObject**)&newStr->m_pBufferOwner);
	return newStr;
}

Array<uniChar>* String::ToCharArray() {
	Array<uniChar>* arr = CS_NEW Array<uniChar>(m_length);
	memcpy(arr->_getPArray(), _getStringBuffer(), m_length * sizeof(uniChar));
	return arr;
}

Array<uniChar>* String::ToCharArray	(s32 startIndex, s32 length) {
	if((startIndex < 0) || (length < 0) || ((u32)(startIndex + length) > m_length)) { THROW(CS_NEW ArgumentOutOfRangeException()); }

	Array<uniChar>* arr = CS_NEW Array<uniChar>(length);
	memcpy(arr->_getPArray(), _getStringBuffer() + startIndex, length * sizeof(uniChar));
	return arr;
}

String* String::ToLower() {
	// uses Allocator
	//String* newStr		= CS_NEW String();
	//const uniChar* pSrc	= _getStringBuffer();
	//const uniChar* pEnd	= pSrc + m_length;
	//uniChar* pDst		= (uniChar*)newStr->m_stringBuffer; // is in StringAllocator
	//while(pSrc < pEnd) {
	//	*pDst++ = (*pSrc >= 0x0041 && *pSrc <= 0x017D) ? _str_toLowerArray[*pSrc - 0x0041] : *pSrc;
	//	pSrc++;
	//}
	//newStr->m_length = m_length;
	//return newStr->_appendClose();

	String* newStr			= CS_NEW String(false);
	newStr->m_length		= m_length;
	newStr->m_allocBuffer	= (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * newStr->m_length, newStr->m_allocBufferObject);
	newStr->m_allocBufferObject->_addOwner(newStr);
	newStr->m_stringBuffer	= newStr->m_allocBuffer;

	const uniChar* pSrc		= _getStringBuffer();
	const uniChar* pEnd		= pSrc + m_length;
	uniChar* pDst			= (uniChar*)newStr->m_stringBuffer;
	while(pSrc < pEnd) {
		*pDst++ = (*pSrc >= 0x0041 && *pSrc <= 0x017D) ? _str_toLowerArray[*pSrc - 0x0041] : *pSrc;
		pSrc++;
	}
	return newStr;
}

String* String::ToString() {
	return this;
}

String* String::ToUpper() {
	// uses Allocator
	//String* newStr		= CS_NEW String();
	//const uniChar* pSrc	= _getStringBuffer();
	//const uniChar* pEnd	= pSrc + m_length;
	//uniChar* pDst		= (uniChar*)newStr->m_stringBuffer; // is in StringAllocator
	//while(pSrc < pEnd) {
	//	*pDst++ = (*pSrc >= 0x0061 && *pSrc <= 0x017E) ? _str_toUpperArray[*pSrc - 0x0061] : *pSrc;
	//	pSrc++;
	//}
	//newStr->m_length = m_length;
	//return newStr->_appendClose();

	String* newStr			= CS_NEW String(false);
	newStr->m_length		= m_length;
	newStr->m_allocBuffer	= (uniChar*)__GCMalloc::allocBlock(sizeof(uniChar) * newStr->m_length, newStr->m_allocBufferObject);
	newStr->m_allocBufferObject->_addOwner(newStr);
	newStr->m_stringBuffer	= newStr->m_allocBuffer;

	const uniChar* pSrc		= _getStringBuffer();
	const uniChar* pEnd		= pSrc + m_length;
	uniChar* pDst			= (uniChar*)newStr->m_stringBuffer;
	while(pSrc < pEnd) {
		*pDst++ = (*pSrc >= 0x0061 && *pSrc <= 0x017E) ? _str_toUpperArray[*pSrc - 0x0061] : *pSrc;
		pSrc++;
	}
	return newStr;
}

String* String::Trim(Array<uniChar>* trimChars) {
	if(!trimChars || trimChars->_acc_gLength() == 0) {
		return Trim((Array<uniChar>*)_str_whiteSpaceSystemArray);
	} else {
		String* newStr = CS_NEW String(false);
		
		newStr->m_stringBuffer	= m_stringBuffer;
		newStr->m_bNotOwnBuffer = true;
		newStr->m_pBufferOwner	= this;
		this->_addRef((__GCObject**)&newStr->m_pBufferOwner);

		const uniChar* pSrc		= _getStringBuffer();
		const uniChar* pEnd		= pSrc + m_length - 1;
		const uniChar* pOChars	= &trimChars->_idx_g_0based(0);
		const uniChar* pEChars	= pOChars + trimChars->_acc_gLength();
		bool bContinue			= true;
		while(pSrc <= pEnd && bContinue) {
			const uniChar* pChar	= pOChars;
			bContinue				= false;
			while (pChar < pEChars) {
				if((*pChar++) == (*pSrc)) {
					bContinue = true;
					break;
				}
			}
			pSrc++;
		}

		bContinue = true;
		while (pSrc <= pEnd && bContinue) {
			const uniChar* pChar	= pOChars;
			bContinue				= false;
			while (pChar < pEChars) {
				if((*pChar++) == (*pEnd)) {
					bContinue = true;
					break;
				}
			}
			pEnd--;
		}

		newStr->m_stringOffset  = m_stringOffset + pSrc - m_stringBuffer - 1;
		newStr->m_length		= m_length - (newStr->m_stringOffset - m_stringOffset) - (_getStringBuffer() + m_length - 1 - pEnd - 1);
		return newStr;
	}
}

String* String::TrimEnd(Array<uniChar>* trimChars) {
	if(!trimChars || trimChars->_acc_gLength() == 0) {
		return TrimEnd((Array<uniChar>*)_str_whiteSpaceSystemArray);
	} else {
		String* newStr = CS_NEW String(false);

		newStr->m_stringBuffer	= m_stringBuffer;
		newStr->m_stringOffset	= m_stringOffset;
		newStr->m_bNotOwnBuffer = true;
		newStr->m_pBufferOwner	= this;
		this->_addRef((__GCObject**)&newStr->m_pBufferOwner);

		const uniChar* pSrc		= _getStringBuffer();
		const uniChar* pEnd		= pSrc + m_length - 1;
		const uniChar* pOChars	= &trimChars->_idx_g_0based(0);
		const uniChar* pEChars	= pOChars + trimChars->_acc_gLength();
		bool bContinue			= true;
		while (pSrc <= pEnd && bContinue) {
			const uniChar* pChar	= pOChars;
			bContinue				= false;
			while (pChar < pEChars) {
				if((*pChar++) == (*pEnd)) {
					bContinue = true;
					break;
				}
			}
			pEnd--;
		}
		
		newStr->m_length		= m_length - (m_stringBuffer + m_length - 1 - pEnd - 1);
	
		return newStr;
	}
}

String* String::TrimStart(Array<uniChar>* trimChars) {
	if(!trimChars || trimChars->_acc_gLength() == 0) {
		return TrimStart((Array<uniChar>*)_str_whiteSpaceSystemArray);
	} else {
		String* newStr = CS_NEW String(false);

		newStr->m_stringBuffer  = m_stringBuffer;
		newStr->m_bNotOwnBuffer = true;
		newStr->m_pBufferOwner	= this;
		this->_addRef((__GCObject**)&newStr->m_pBufferOwner);

		const uniChar* pSrc		= _getStringBuffer();
		const uniChar* pEnd		= pSrc + m_length - 1;
		const uniChar* pOChars	= &trimChars->_idx_g_0based(0);
		const uniChar* pEChars	= pOChars + trimChars->_acc_gLength();
		bool bContinue			= true;
		while(pSrc <= pEnd && bContinue) {
			const uniChar* pChar	= pOChars;
			bContinue				= false;
			while (pChar < pEChars) {
				if((*pChar++) == (*pSrc)) {
					bContinue = true;
					break;
				}
			}
			pSrc++;
		}
		newStr->m_stringOffset  = m_stringOffset + (pSrc - m_stringBuffer - 1);
		newStr->m_length		= m_length - (newStr->m_stringOffset - m_stringOffset);
		return newStr;
	}
}

// --------------------------------------------------------

// --------------------------------------------------------
// String Builder.

String* String::_appendStr(String* pStr) {
	if(pStr) {
		memcpy(_x_StringGlobalAllocator::s_pLastBegin + m_length, pStr->_getStringBuffer(), pStr->m_length * sizeof(uniChar));
		m_length += pStr->m_length;
	}
	return this;
}
String* String::_appendStr(String* pStr, s32 startIndex, s32 length) {	
	if(pStr) {
		memcpy(_x_StringGlobalAllocator::s_pLastBegin + m_length, pStr->_getStringBuffer() + startIndex, length * sizeof(uniChar));
		m_length += length;
	}
	return this;
}
String* String::_appendCte(const uniChar* buffer, u32 size) {
    memcpy((uniChar*)m_stringBuffer + m_length, buffer, size * sizeof(uniChar));
    m_length += size;
    return this;
}
String* String::_appendI(s32 i) {
	// max int is 2,147,483,647

	if(i < 0) {
		this->_appendC('-');
		i = -i;
	}

	bool isAfterFirstNonZero = false;
	for(int n = 1000000000; n > 1; n/=10) {
		if(isAfterFirstNonZero || i/n != 0) {
			this->_appendC('0' + i/n);
			i -= (i/n) * n;
			isAfterFirstNonZero = true;
		}
	}
	this->_appendC('0' + i);
	return this;
}
String* String::_appendU(u32 u) {
	// max uint is 4,294,967,295

	bool isAfterFirstNonZero = false;
	for(int n = 1000000000; n > 1; n/=10) {
		if(isAfterFirstNonZero || u/n != 0) {
			this->_appendC('0' + u/n);
			u -= (u/n) * n;
			isAfterFirstNonZero = true;
		}
	}
	this->_appendC('0' + u);
	return this;
}
String* String::_appendF(float f) {
	// TODO
	// 3 digits for exponent instead of 2.
	// precision problems with %G (not with %E).
	char charBuffer[50];
	uniChar uniCharBuffer[50];
	int len = sprintf(charBuffer, "%G", f);
	asciiToUnicode16((u8*)charBuffer, len, uniCharBuffer);
	_appendCte(uniCharBuffer, len);
	return this;
}
String* String::_appendC(uniChar c) {
	*(_x_StringGlobalAllocator::s_pLastBegin + m_length++) = c;
	return this;
}
String* String::_appendS(s16 s) {
	// max short is 32,767
	if(s < 0) {
		this->_appendC('-');
		s = -s;
	}

	bool isAfterFirstNonZero = false;
	for(int n = 10000; n > 1; n/=10) {
		if(isAfterFirstNonZero || s/n != 0) {
			this->_appendC('0' + s/n);
			s -= (s/n) * n;
			isAfterFirstNonZero = true;
		}
	}
	this->_appendC('0' + s);
	return this;
}
String* String::_appendUS(u16 u) {
	// max short is 65,535

	bool isAfterFirstNonZero = false;
	for(int n = 10000; n > 1; n/=10) {
		if(isAfterFirstNonZero || u/n != 0) {
			this->_appendC('0' + u/n);
			u -= (u/n) * n;
			isAfterFirstNonZero = true;
		}
	}
	this->_appendC('0' + u);
	return this;
}
String* String::_appendS8(s8 s) {
	// max s8 is 127

	if(s < 0) {
		this->_appendC('-');
		s = -s;
	}

	if(s > 100) {
		this->_appendC('0' + s/100);
		s -= s/100 * 100;
	}
	if(s > 10) {
		this->_appendC('0' + s/10);
		s -= s/10 * 10;
	}
	this->_appendC('0' + s);
	return this;
}
String* String::_appendU8(u8 u) {
	// max u8 is 255

	if(u > 100) {
		this->_appendC('0' + u/100);
		u -= u/100 * 100;
	}
	if(u > 10) {
		this->_appendC('0' + u/10);
		u -= u/10 * 10;
	}
	this->_appendC('0' + u);
	return this;
}
String* String::_appendB(bool b) {
	if(b) {
		String tmp(_str_$_true, 4);
		this->_appendStr(&tmp);
	} else {
		String tmp(_str_$_false, 5);
		this->_appendStr(&tmp);
	}
	return this;
}
String* String::_appendL(s64 l) {
	// max long is 9,223,372,036,854,775,807

	if(l < 0) {
		this->_appendC('-');
		l = -l;
	}

	bool isAfterFirstNonZero = false;
	for(s64 n = 1000000000000000000; n > 1; n/=10) {
		if(isAfterFirstNonZero || l/n != 0) {
			this->_appendC((uniChar)('0' + l/n));
			l -= (l/n) * n;
			isAfterFirstNonZero = true;
		}
	}
	this->_appendC((uniChar)('0' + l));
	return this;
}
String* String::_appendUL(u64 u) {
	// max uint is 18,446,744,073,709,551,615

	bool isAfterFirstNonZero = false;
	for(u64 n = 10000000000000000000; n > 1; n/=10) {
		if(isAfterFirstNonZero || u/n != 0) {
			this->_appendC((uniChar)('0' + u/n));
			u -= (u/n) * n;
			isAfterFirstNonZero = true;
		}
	}
	this->_appendC((uniChar)('0' + u));
	return this;
}
String* String::_appendD(double d) {
	// TODO
	return this;
}
String* String::_appendClose() {
#ifdef _DEBUG_STRING_
	CS_Assert(_x_StringGlobalAllocator::s_isBuilding, "You are trying to close a String which has not been allocated in the StringAllocator!");
	_x_StringGlobalAllocator::s_isBuilding = false;
#endif

	if(_x_StringGlobalAllocator::closeString(this, (uniChar*)&this->m_stringBuffer[this->m_length])) {
		return this;
	} else {
		return NULL;
	}
}

String& String::operator+(String& pStr) {
	return *_appendStr(&pStr);
}
String& String::operator+(uniChar c) {
	return *_appendC(c);
}
String& String::operator+(s64 l) {
	return *_appendL(l);
}
String& String::operator+(u64 u) {
	return *_appendUL(u);
}
String& String::operator+(s32 i) {
	return *_appendI(i);
}
String& String::operator+(u32 u) {
	return *_appendU(u);
}
String& String::operator+(s16 s) {
	return *_appendS(s);
}
String& String::operator+(s8 s) {
	return *_appendS8(s);
}
String& String::operator+(u8 u) {
	return *_appendU8(u);
}
String& String::operator+(float f) {
	return *_appendF(f);
}
String& String::operator+(double d) {
	return *_appendD(d);
}
String& String::operator+(bool b) {
	return *_appendB(b);
}

// --------------------------------------------------------

const char* String::_toCStr() {
	int* intptr = __MarshallingUtils::NativeUtf8FromString(this);
	return (intptr) ? (char*)intptr : "";
}

// --------------------------------------------------------
// CharEnumerator
String::CharEnumerator::CharEnumerator(String* str) {
	m_str = str;
	m_nextIndex = -1;
}

uniChar String::CharEnumerator::_acc_gCurrent() {
	if(m_nextIndex < 0 || m_nextIndex > m_str->m_length) {
		THROW(CS_NEW InvalidOperationException());
	}
	return m_str->_idx_g(m_nextIndex);
}

bool String::CharEnumerator::MoveNext() {
	return ((++m_nextIndex) < m_str->m_length);
}

void String::CharEnumerator::Dispose() {
	// nop
}	
// --------------------------------------------------------

// --------------------------------------------------------
// init

/*static*/
bool String::init() {
	_str_whiteSpaceSystemArray = CS_NEW System::Array<uniChar>(26, (uniChar*)_str_whiteSpaceArray, 26);
	String::Empty = CS_NEW String(false);
	String::Empty->m_stringBuffer = &System::String::emptyStr;
	System::Memory::registerGCRoot(&_str_whiteSpaceSystemArray);
	System::Memory::registerGCRoot(&String::Empty);
	return true;
}

// --------------------------------------------------------

}
