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
#ifndef _MEM_MACRO_KLB_
#define _MEM_MACRO_KLB_

// Memcpy / Memset / strlen
#include "string.h"

//
// "Slow" implementation for now.
//
#define	memcpy32	memcpy
#define memcpy16	memcpy
#define memset16(dst, val, size)	{ u16 v = (u16)(val); u16* ptrStart = (u16*)(dst); u16* ptrEnd = &ptrStart[(size)>>1]; while (ptrStart != ptrEnd) { *ptrStart++ = v; } }
#define memset32(dst, val, size)	{ u32 v = (u32)(val); u32* ptrStart = (u32*)(dst); u32* ptrEnd = &ptrStart[(size)>>2]; while (ptrStart != ptrEnd) { *ptrStart++ = v; } }

#endif

