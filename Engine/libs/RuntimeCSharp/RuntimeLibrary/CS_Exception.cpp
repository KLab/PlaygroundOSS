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
#include "CS_Object.h"
#include "CS_String.h"

//
// Stack of 100 try catch.
//
jmp_buf	System::_g_excStack[100];
int		System::_g_excDepth = 0;

namespace System {

static const uniChar __NotSupportedYetStr_0[17]				= { 'N','o','t',' ','s','u','p','o','r','t','e','d',' ','y','e','t','.' };

static const uniChar __ExceptionStr_0[16]					= { 'S','y','s','t','e','m','.','E','x','c','e','p','t','i','o','n' };
static const uniChar __SystemExceptionStr_0[22]				= { 'S','y','s','t','e','m','.','S','y','s','t','e','m','E','x','c','e','p','t','i','o','n' };
static const uniChar __IndexOutOfRangeExceptionStr_0[31]	= { 'S','y','s','t','e','m','.','I','n','d','e','x','O','u','t','O','f','R','a','n','g','e','E','x','c','e','p','t','i','o','n' };
static const uniChar __NullReferenceExceptionStr_0[29]		= { 'S','y','s','t','e','m','.','N','u','l','l','R','e','f','e','r','e','n','c','e','E','x','c','e','p','t','i','o','n' };
static const uniChar __OutOfMemoryExceptionStr_0[27]		= { 'S','y','s','t','e','m','.','O','u','t','O','f','M','e','m','o','r','y','E','x','c','e','p','t','i','o','n' };
static const uniChar __ArgumentExceptionStr_0[24]			= { 'S','y','s','t','e','m','.','A','r','g','u','m','e','n','t','E','x','c','e','p','t','i','o','n' };
static const uniChar __ArgumentOutOfRangeExceptionStr_0[34]	= { 'S','y','s','t','e','m','.','A','r','g','u','m','e','n','t','O','u','t','O','f','R','a','n','g','e','E','x','c','e','p','t','i','o','n' };
static const uniChar __ArgumentNullExceptionStr_0[28]		= { 'S','y','s','t','e','m','.','A','r','g','u','m','e','n','t','N','u','l','l','E','x','c','e','p','t','i','o','n' };
static const uniChar __RankExceptionStr_0[20]				= { 'S','y','s','t','e','m','.','R','a','n','k','E','x','c','e','p','t','i','o','n' };
static const uniChar __InvalidOperationExceptionStr_0[32]	= { 'S','y','s','t','e','m','.','I','n','v','a','l','i','d','O','p','e','r','a','t','i','o','n','E','x','c','e','p','t','i','o','n' };
static const uniChar __ArrayTypeMismatchExceptionStr_0[33]	= { 'S','y','s','t','e','m','.','A','r','r','a','y','T','y','p','e','M','i','s','m','a','t','c','h','E','x','c','e','p','t','i','o','n' };
static const uniChar __ArithmeticExceptionStr_0[33]			= { 'S','y','s','t','e','m','.','A','r','r','a','y','T','y','p','e','M','i','s','m','a','t','c','h','E','x','c','e','p','t','i','o','n' };
static const uniChar __DivideByZeroExceptionStr_0[28]		= { 'S','y','s','t','e','m','.','D','i','v','i','d','e','B','y','Z','e','r','o','E','x','c','e','p','t','i','o','n' };

// ------------------------------------------------------
// System::Exception
// ------------------------------------------------------

Exception::Exception() {
	__GCObject::_RefSetValue((__GCObject**)&m_message, System::String::Empty);
}

Exception::Exception(String* msg) {
	__GCObject::_RefSetValue((__GCObject**)&m_message, msg);
}

/*virtual*/ 
bool  Exception::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(Exception, Object);
}

/*virtual*/
u32	Exception::_processGC() {
	if(m_message) { Memory::pushList(m_message, 0); }
	return COMPLETE;
}

/*virtual*/	
void Exception::_releaseGC() {
	if(m_message) {
		m_message->_removeRef((__GCObject**)&m_message);
	}
}

/*virtual*/
void Exception::_moveAlert(u32 offset) {
	Object::_moveAlert(offset);
	if(m_message) { m_message->_moveRef((__GCObject**)((u8*)&m_message - offset), (__GCObject**)&m_message); }
}

/*virtual*/
String* Exception::ToString() {
	return CS_NEW String(__ExceptionStr_0,16);
}

String* Exception::_acc_gMessage() {
	return m_message;
}

String*	Exception::_acc_gStackTrace() {
	return CS_NEW String(__NotSupportedYetStr_0, 17);
}

// ------------------------------------------------------

// ------------------------------------------------------
// System::SystemException
// ------------------------------------------------------

SystemException::SystemException(String* msg)
: Exception(msg)
{ 
	// Do nothing
}

/*virtual*/ 
bool  SystemException::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(SystemException, Exception);
}

/*virtual*/
String* SystemException::ToString() {
	return CS_NEW String(__SystemExceptionStr_0,22);
}

// ------------------------------------------------------

// ------------------------------------------------------
// System::IndexOutOfRangeException
// ------------------------------------------------------

IndexOutOfRangeException::IndexOutOfRangeException(String* msg)
: SystemException(msg)
{ 
	// Do nothing
}

/*virtual*/ 
bool IndexOutOfRangeException::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(IndexOutOfRangeException,SystemException);
}

/*virtual*/
String* IndexOutOfRangeException::ToString() {
	return CS_NEW String(__IndexOutOfRangeExceptionStr_0,31);
}

// ------------------------------------------------------

// ------------------------------------------------------
// System::NullReferenceException
// ------------------------------------------------------

NullReferenceException::NullReferenceException(String* msg)
: SystemException(msg)
{ 
	// Do nothing
}

/*virtual*/ 
bool NullReferenceException::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(NullReferenceException,SystemException);
}

/*virtual*/
String* NullReferenceException::ToString() {
	return CS_NEW String(__NullReferenceExceptionStr_0,29);
}

// ------------------------------------------------------

// ------------------------------------------------------
// System::OutOfMemoryException
// ------------------------------------------------------

OutOfMemoryException::OutOfMemoryException(String* msg)
: SystemException(msg)
{ 
	// Do nothing
}

/*virtual*/ 
bool OutOfMemoryException::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(OutOfMemoryException,SystemException);
}

/*virtual*/
String* OutOfMemoryException::ToString() {
	return CS_NEW String(__OutOfMemoryExceptionStr_0,27);
}

// ------------------------------------------------------

// ------------------------------------------------------
// System::ArgumentException
// ------------------------------------------------------

ArgumentException::ArgumentException(String* msg)
: SystemException(msg)
{ 
	// Do nothing
}

/*virtual*/ 
bool ArgumentException::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(ArgumentException,SystemException);
}

/*virtual*/
inline 
String* ArgumentException::ToString() {
	return CS_NEW String(__ArgumentExceptionStr_0,24);
}

// ------------------------------------------------------

// ------------------------------------------------------
// System::ArgumentOutOfRangeException
// ------------------------------------------------------

ArgumentOutOfRangeException::ArgumentOutOfRangeException(String* msg)
: ArgumentException(msg)
{ 
	// Do nothing
}

/*virtual*/ 
bool ArgumentOutOfRangeException::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(ArgumentOutOfRangeException,SystemException);
}

/*virtual*/
String* ArgumentOutOfRangeException::ToString() {
	return CS_NEW String(__ArgumentOutOfRangeExceptionStr_0,34);
}

// ------------------------------------------------------

// ------------------------------------------------------
// System::ArgumentNullException
// ------------------------------------------------------

ArgumentNullException::ArgumentNullException(String* msg)
: ArgumentException(msg)
{ 
	// Do nothing
}

/*virtual*/ 
bool ArgumentNullException::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(ArgumentNullException,SystemException);
}

/*virtual*/
String* ArgumentNullException::ToString() {
	return CS_NEW String(__ArgumentNullExceptionStr_0,28);
}

// ------------------------------------------------------

// ------------------------------------------------------
// System::RankException
// ------------------------------------------------------

RankException::RankException(String* msg)
: SystemException(msg)
{ 
	// Do nothing
}

/*virtual*/
bool RankException::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(RankException,SystemException);
}

/*virtual*/
inline 
String* RankException::ToString() {
	return CS_NEW String(__RankExceptionStr_0,20);
}

// ------------------------------------------------------

// ------------------------------------------------------
// System::InvalidOperationException
// ------------------------------------------------------

InvalidOperationException::InvalidOperationException(String* msg)
: SystemException(msg)
{ 
	// Do nothing
}

/*virtual*/ 
bool InvalidOperationException::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(InvalidOperationException,SystemException);
}

/*virtual*/
inline 
String* InvalidOperationException::ToString() {
	return CS_NEW String(__InvalidOperationExceptionStr_0,32);
}

// ------------------------------------------------------

// ------------------------------------------------------
// System::ArrayTypeMismatchException
// ------------------------------------------------------

ArrayTypeMismatchException::ArrayTypeMismatchException(String* msg)
: SystemException(msg)
{ 
	// Do nothing
}

/*virtual*/ 
bool ArrayTypeMismatchException::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(ArrayTypeMismatchException,SystemException);
}

/*virtual*/
inline 
String* ArrayTypeMismatchException::ToString() {
	return CS_NEW String(__ArrayTypeMismatchExceptionStr_0,33);
}

// ------------------------------------------------------

// ------------------------------------------------------
// System::ArithmeticException
// ------------------------------------------------------

ArithmeticException::ArithmeticException(String* msg)
: SystemException(msg)
{ 
	// Do nothing
}

/*virtual*/ 
bool ArithmeticException::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(ArithmeticException,SystemException);
}

/*virtual*/
String* ArithmeticException::ToString() {
	return CS_NEW String(__ArithmeticExceptionStr_0,33);
}

// ------------------------------------------------------

// ------------------------------------------------------
// System::DivideByZeroException
// ------------------------------------------------------

DivideByZeroException::DivideByZeroException(String* msg)
: ArithmeticException(msg)
{ 
	// Do nothing
}

/*virtual*/ 
bool DivideByZeroException::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(DivideByZeroException,ArithmeticException);
}

/*virtual*/
String* DivideByZeroException::ToString() {
	return CS_NEW String(__DivideByZeroExceptionStr_0,28);
}

// ------------------------------------------------------

// ------------------------------------------------------
// System::CppException
// ------------------------------------------------------

/*virtual*/ bool CppException::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CppException,SystemException);
}

// ------------------------------------------------------

// ------------------------------------------------------
// System::CppNotComparable
// ------------------------------------------------------

/*virtual*/ bool CppNotComparable::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(CppNotComparable,SystemException);
}

// ------------------------------------------------------

}
