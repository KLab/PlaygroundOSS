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
#ifndef _MarshallingUtils_
#define _MarshallingUtils_

#include "../CompilerProject/BaseType.h"
#include "CS_Object.h"
#include "CS_String.h"

namespace System {


class __MarshallingUtils 
{
public:
	static	s32*							NativeUtf8FromString				(System::String* str);
	static	System::String*					StringFromNativeUtf8				(s32* utf8intptr);
	static	System::Array<System::String*>*	StringArrayFromNativeUtf8IntPtr		(s32* utf8intptr, int size);
	static	System::Array<s32*>*			NativeUtf8ArrayFromStringArray		(System::Array<System::String*>* stringArray, int size);
	static	System::Array<s32>*				IntArrayFromIntPtr					(s32* intptr, int size);
};

u32 _utf8ToUtf16(const u8* src, u32 srcSizeBytes, u16* dst, u32 dstSizeWord);
u32 _utf16ToUtf8(const uniChar* src, u32 srcSizeWord, u8* dst, u32 dstSizeBytes);

}

#endif
