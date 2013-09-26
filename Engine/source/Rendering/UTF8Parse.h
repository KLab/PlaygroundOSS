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
#ifndef __NVM_UTF8_CONV__
#define __NVM_UTF8_CONV__

// #include "NVMtypes.h"
#include "BaseType.h"

#define UTF8_ACCEPT 0
#define UTF8_REJECT 1

u32 toUtf16(const u8* src, u32 srcSizeByte, u16* dst, u32 dstSizeWord);

#endif
