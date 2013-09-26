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
#include "FileDelete.h"

#define MAX_SIZE_BUFFER_QUEUE_PATH	(200000)
#define MAX_SIZE_ENTRY_COUNT		(1000)

// Prototypes
struct SDelContext;
void EmptyQueue(SDelContext* pCtx);
void QueueList(SDelContext* pCtx, const char* path);
const char* GetQueueItem(SDelContext* pCtx);
void deleteRecurse(SDelContext* pCtx, const char* path, bool delFile);

struct SDelContext {
	char*	m_deleteQueue;
	u32*	m_deleteQueueIndex;

	char*	m_deleteQueueStart;
	u32		m_deleteCountCount;
	u32		m_deleteCountCountParse;
};

void EmptyQueue(SDelContext* pCtx) {
	pCtx->m_deleteCountCount			= 0;
	pCtx->m_deleteCountCountParse		= 0;
	pCtx->m_deleteQueueStart			= pCtx->m_deleteQueue;
}

void QueueList(SDelContext* pCtx, const char* path) {
	u32 length = strlen(path) + 1; // Include zero.

	// Index.
	klb_assert(pCtx->m_deleteCountCount < MAX_SIZE_ENTRY_COUNT, "Reach limit");

	pCtx->m_deleteQueueIndex[pCtx->m_deleteCountCount++] = pCtx->m_deleteQueueStart - pCtx->m_deleteQueue;
	
	klb_assert(pCtx->m_deleteQueueIndex[pCtx->m_deleteCountCount-1] + length < MAX_SIZE_BUFFER_QUEUE_PATH,"Reach limit");

	// Copy String.
	memcpy(pCtx->m_deleteQueueStart, path, length); // Copy string
	// Go next
	pCtx->m_deleteQueueStart += length;
}

const char* GetQueueItem(SDelContext* pCtx) {
	if (pCtx->m_deleteCountCountParse < pCtx->m_deleteCountCount) {
		return &pCtx->m_deleteQueue[pCtx->m_deleteQueueIndex[pCtx->m_deleteCountCountParse++]];
	} else {
		return NULL;
	}
}

void deleteRecurse(SDelContext* pCtx, const char* path, bool delFile) {
	DIR *pDIR = opendir(path);
	if (pDIR) {

		//
		// 1.Recursive phase folder only, just for "parsing"
		//
		DIR *pDIR2;
		struct dirent* entry = readdir(pDIR);
		while(entry) {
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ) {
				char buff[1000];
				sprintf(buff, "%s/%s",path, entry->d_name);
				if ((pDIR2=opendir(buff))) {
					deleteRecurse(pCtx, buff, false);
				}
			}
			entry = readdir(pDIR);
		}
		closedir(pDIR);

		//
		// 2.Reopen current path now we know that ALL content is empty (empty folder or files only : no more recursion)
		//
		EmptyQueue(pCtx);

		pDIR = opendir(path);
		entry = readdir(pDIR);
		while(entry) {
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ) {
				char buff[1000];
				sprintf(buff, "%s/%s",path, entry->d_name);
				QueueList(pCtx, buff);
			}
			entry = readdir(pDIR);
		}
		closedir(pDIR);

		const char* pathToDelete = GetQueueItem(pCtx);
		while (pathToDelete) {
			removeTmpFileNative(pathToDelete);
			pathToDelete = GetQueueItem(pCtx);
		}
	} else {
		if (delFile) {
			removeTmpFileNative(path);
		}
	}
}

bool deleteFiles(const char* path) {
	SDelContext ctx;
	// 0. Alloc a buffer of 200 KB for text buffering. 
	ctx.m_deleteQueue		= new char[MAX_SIZE_BUFFER_QUEUE_PATH];
	ctx.m_deleteQueueIndex	= new u32[MAX_SIZE_ENTRY_COUNT];

	bool res = false;
	if (ctx.m_deleteQueue && ctx.m_deleteQueueIndex) {
		// 1. Convert abstract path to OS path.
		const char* pathNative;
		if ((pathNative = getFullNativePath(path))) {
			// Check if there is a "/" at the end, if so remove it.
			u32 length = strlen(pathNative);
			if ((pathNative[length-1] == '/') || (pathNative[length-1] == '\\'))
			{
				const char* patchAdr = &pathNative[length-1];
				char* writeAdr = (char*)patchAdr;
				*writeAdr = 0; // End string.
			}

			deleteRecurse(&ctx, pathNative, true);
			// 2. Call to free
			res = true;

			// Delete path after finishing using it.
			delete pathNative;
		}
	}

	// 3. Free buffer
	delete ctx.m_deleteQueue;
	delete ctx.m_deleteQueueIndex;
	return res;
}
