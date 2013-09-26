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

#include <stdlib.h>
#include "mem.h"
#include "CPFInterface.h"

#define EXTENSION_STEP		(8192)

CKLBContext gContext;

CKLBContext* CKLBContext::getContext() {
	return &gContext;
}

CKLBContext::CKLBContext()
{
}

CKLBContext::~CKLBContext() {
}

//
// Do not use MALLOC / FREE macro here.
// Those functions are used by NEW DELETE and already wrapped.
//
void* CKLBContext::allocate(unsigned int numByte) {

#ifdef INTERNAL_MEMORY_STARVING
    if(CMemDebug::isFail()) { return NULL; }
#endif
	void* ptr = malloc(numByte);
	if (ptr) {
		return ptr;//(void *)((ALLOCHDR*)ptr + 1);
	}
	return NULL;
}

void CKLBContext::disallocate(void* ptr) {
    // ALLOCHDR * apt = (ALLOCHDR *)ptr - 1;
	// free(apt);
	free(ptr);
}
