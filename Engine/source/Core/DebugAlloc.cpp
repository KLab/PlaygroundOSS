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
#include <stdlib.h>
//#include <malloc.h>
//#include <Windows.h>

#include "BaseType.h"
#include "DebugAlloc.h"

int	CMemDebug::m_cntFail = 0;
int	CMemDebug::m_numFail = 0;

void * 
operator new(size_t size)
{
    void* ret = NULL;
#ifdef INTERNAL_MEMORY_STARVING
    if(CMemDebug::isFail()) { return ret; }
#endif

    if( size <= 0 ) { return ret; }

	ret = malloc(size);
	klb_assert(ret, "memory allocation failed.");
	return ret;
}

void * 
operator new[](size_t size)
{
    void* ret = NULL;
#ifdef INTERNAL_MEMORY_STARVING
    if(CMemDebug::isFail()) { return ret; }
#endif

    if( size <= 0 ) { return ret; }

    ret = malloc(size);
	klb_assert(ret, "memory allocation failed.");
	return ret;
}

void 
operator delete(void * ptr)
{
    free(ptr);
}

void 
operator delete[](void * ptr)
{
	free(ptr);
}
