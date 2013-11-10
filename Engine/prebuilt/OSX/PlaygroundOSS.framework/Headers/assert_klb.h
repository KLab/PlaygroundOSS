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
#ifndef __ASSERT_SYSTEM__
#define __ASSERT_SYSTEM__

#ifdef __cplusplus
extern "C" {
#endif

//#ifdef assert
//#error "Already using standard C Assert"
//#endif
//#undef assert
	void assertFunction(int line, const char* file, const char* msg,...);
#ifdef _WIN32
#define klb_assert(cond,msg,...)		if (!(cond)) { assertFunction(__LINE__, __FILE__, msg, __VA_ARGS__); }
#define klb_assertNull(cond, msg, ...)	;
#define klb_assertAlways(msg,...)		{ assertFunction(__LINE__, __FILE__, msg, __VA_ARGS__); }
#else
#if (DEBUG == 1)
#define klb_assert(cond,msg...)			if(!(cond)) { assertFunction(__LINE__, __FILE__, msg); }
#define klb_assertNull(cond, msg, ...)	;
#define klb_assertAlways(msg...)		{ assertFunction(__LINE__, __FILE__, msg); }
#else
#define klb_assert(cond,msg...)			;
#define klb_assertNull(cond, msg, ...)	;
#define klb_assertAlways(msg...)		;
#endif
#endif

void msgBox(char* msg);

#ifdef __cplusplus
}
#endif

#endif
