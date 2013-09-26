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

void* CS_malloc(size_t size) {
	size = ((size + 3) & 0xFFFFFFFC);
	void* ptr = malloc(size);
	if(ptr) { memset32(ptr, 0, size); }
	return ptr;
}

void CS_free(void* ptr) {
	free(ptr);
}

void* CS_realloc(void *memblock, size_t size, size_t oldSize) {
	size = ((size + 3) & 0xFFFFFFFC);
	void* ptr = realloc(memblock, size);
	if(ptr && size > oldSize) {
		memset32((u8*)ptr + oldSize, 0, size - oldSize); 
	}
	return ptr;
}



namespace System {

// TODO override new / delete

Object::Object() {
}

/*virtual*/
u32 Object::_processGC() {
	// Do nothing.
	return COMPLETE;
}

bool Object::Equals(Object* obj) {
	return obj == this;
}

/*static*/
bool Object::Equals(Object* objA, Object* objB) {
	return objA == objB;
}

s32 Object::GetHashCode() {
	return (s32)this;
}

/** Unsupported
Type* Object::GetType() {
	return NULL;
}*/

static const uniChar __NotSupportedYetStr_0[17]				= { 'N','o','t',' ','s','u','p','o','r','t','e','d',' ','y','e','t','.' };

String* Object::GetType() {
	return CS_NEW String(__NotSupportedYetStr_0, 17);
}


/** Unsupported
Object* Object::MemberwiseClone() {
	return new Object();
}*/

/*vitual*/
s32 Object::CompareTo(Object* obj) {
	THROW(CS_NEW CppNotComparable());
}

/*static*/
bool Object::ReferenceEquals(Object* objA, Object* objB) {
	return objA == objB;
}

static const uniChar __objStr_1[] = { 'S','y','s','t','e','m','.','O','b','j','e','c','t' };
String* Object::ToString() {
	return CS_NEW String(__objStr_1,13);
}

Object::~Object() {
}

/*virtual*/ 
bool Object::_isInstanceOf(u32 typeID) {
	if(typeID == Object::_TYPEID) {
		return true;
	} else {
		return false;
	}
}

bool Object::_isClassOf(u32 typeID) {
	if(typeID == Object::_TYPEID) {
		return true;
	} else {
		return false;
	}
}

}

void* _as_(System::Object* ptr, u32 classID) {
	return (ptr ? (ptr->_isInstanceOf(classID) ? ptr : NULL) : NULL);
}
