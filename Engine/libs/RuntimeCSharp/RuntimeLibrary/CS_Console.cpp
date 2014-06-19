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
#include "CS_Console.h"

namespace System {

/*static*/
void Console::Write(bool value) {
	printf("%s", value ? "True" : "False");
}

/*static*/
void Console::Write(uniChar value) {
	u8 utf8buff[4];
	u32 endPos = _utf16ToUtf8(&value, 1, utf8buff, 3);
	utf8buff[endPos] = '\0';
	// TODO: utf-8 is not suitable for Windows.
	printf("%s", utf8buff);
}

/*static*/
void Console::Write(System::Array<uniChar>* buffer) {
	u8* utf8buff = (u8*)CS_MALLOC(buffer->_acc_gLength() * 3 + 1);
	u32 endPos = _utf16ToUtf8((uniChar*)buffer->_getPArray(), buffer->_acc_gLength(), utf8buff, buffer->_acc_gLength()*3);
	utf8buff[endPos] = '\0';
	// TODO: utf-8 is not suitable for Windows.
	printf("%s", utf8buff);
	CS_FREE(utf8buff);
}

/*static*/
void Console::Write(double value) {
	if(value == 0) {
		printf("0");
	} else {
		printf("%G", value);
	}
}

/*static*/
void Console::Write(float value) {
	printf("%LG", value);
}

/*static*/
void Console::Write(s32 value) {
	printf("%i", value);
}

/*static*/
void Console::Write(s64 value) {
	printf("%li", value);
}

/*static*/
void Console::Write(System::Object* value) {
	printf("%s", value->ToString()->_toCStr());
}

/*static*/
void Console::Write(System::String* value) {
	// TODO: Unicode support.
	printf("%s", value->_toCStr());
}

/*static*/
void Console::Write(u32 value) {
	printf("%u", value);
}

/*static*/
void Console::Write(u64 value) {
	printf("%u", value);
}

/*static*/
void Console::Write(System::Array<uniChar>* buffer, u32 index, u32 count) {
	u8* utf8buff = (u8*)CS_MALLOC(count * 3 + 1);
	u32 endPos =_utf16ToUtf8((uniChar*)buffer->_getPArray() + index, count, utf8buff, count * 3);
	utf8buff[endPos] = '\0';
	printf("%s", utf8buff);
	CS_FREE(utf8buff);
}

}
