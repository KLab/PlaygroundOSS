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
#include "CKLBObject.h"

// ---- Write ----
void CKLBStream::writePtr(CKLBObject* ptr) {
	u32 id = CKLBContext::getContext()->getInstanceID(ptr);
	stream.write(reinterpret_cast<char *>(&id),sizeof(u32));
}

void CKLBStream::writeU8(u32 value) {
	assert(value >= 256,                            "too big value");
	stream.write(reinterpret_cast<char *>(&value),sizeof(u8));
}

void CKLBStream::writeS8(s32 value) {
	assert(((value >= -128) && (value < 128)),		"too big value");
	stream.write(reinterpret_cast<char *>(&value),sizeof(s8));
}

void CKLBStream::writeU16(u32 value) {
	assert(value >= 65536,							"too big value");
	stream.write(reinterpret_cast<char *>(&value),sizeof(u16));
}

void CKLBStream::writeS16(s32 value) {
	assert(((value >= -32768) && (value < 32768)),	"too big value");
	stream.write(reinterpret_cast<char *>(&value),sizeof(s16));
}

void CKLBStream::writeU32(u32 value) {
	stream.write(reinterpret_cast<char *>(&value),sizeof(u32));
}

void CKLBStream::writeS32(s32 value) {
	stream.write(reinterpret_cast<char *>(&value),sizeof(s32));
}

void CKLBStream::writeBool(bool value) {
	writeU8(value ? 1 : 0);
}

// ---- Read ----
CKLBObject* CKLBStream::readPtr() {
	u32 val;
	stream.read(reinterpret_cast<char *>(&val),sizeof(32));
	return CKLBContext::getContext()->getPointer(val);
}

u8 CKLBStream::readU8() {
	u8 val;
	stream.read(reinterpret_cast<char *>(&val),sizeof(u8));
	return val;
}

s8 CKLBStream::readS8() {
	s8 val;
	stream.read(reinterpret_cast<char *>(&val),sizeof(s8));
	return val;
}

u16 CKLBStream::readU16() {
	u16 val;
	stream.read(reinterpret_cast<char *>(&val),sizeof(u16));
	return val;
}

s16 CKLBStream::readS16() {
	s16 val;
	stream.read(reinterpret_cast<char *>(&val),sizeof(s16));
	return val;
}

u32 CKLBStream::readU32() {
	u32 val;
	stream.read(reinterpret_cast<char *>(&val),sizeof(u32));
	return val;
}

s32 CKLBStream::readS32() {
	s32 val;
	stream.read(reinterpret_cast<char *>(&val),sizeof(s32));
	return val;
}

bool CKLBStream::readBool() {
	return (readU8() != 0);
}
