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
#include "CS_System.h"

namespace System {

bool initRuntime() {
	__InternalUtils::init();
	System::_x_StringGlobalAllocator::init(32768);
	System::String::init();
	
	return true;
}

static const uniChar __delStr_1[] = { 'S','y','s','t','e','m','.','D','e','l','e','g','a','t','e' };
/*virtual*/
String* Delegate::ToString() {
	return CS_NEW String(__delStr_1, 15);
}

/*static*/ /*const*/ s32*	IntPtr::Zero	= 0;
/*static*/ /*const*/ s32	IntPtr::Size	= sizeof(s32*);
/*static*/ /*const*/ u32*	UIntPtr::Zero	= 0;
/*static*/ /*const*/ s32	UIntPtr::Size	= sizeof(s32*);

}
