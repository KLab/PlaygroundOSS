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
#include "CKLBDataHandler.h"
#include "CKLBAsset.h"

#include "CKLBTask.h"
#include "mem.h"

// =====================================================================
//   General Handler data set.
// =====================================================================

CKLBAbstractAsset**	tempArray	= NULL;
u16*				next		= NULL;
u16*				prev		= NULL;
u16					m_freeList	= 0;
u16					m_usedList	= 0;
CKLBDataSet*		g_dataSet	= NULL;
u32 CKLBDataHandler::s_maxHandler	= 0;

bool 
CKLBDataHandler::init(u16 handleCount) {
	if (handleCount) {
		tempArray	= KLBNEWA(CKLBAbstractAsset*,	handleCount);
		next		= KLBNEWA(u16,					handleCount);
		prev		= KLBNEWA(u16,					handleCount);
		if (tempArray && next && prev) {
			memset32(tempArray,NULL, handleCount * sizeof(CKLBAbstractAsset*));

			for (u32 n=1; n < handleCount; n++) {
				next[n]			= n+1;
				prev[n]			= n-1;
			}

			prev[1]				= 0;
			next[handleCount-1] = 0;

			next[0]				= 0;
			prev[0]				= 0;
			tempArray[0]		= NULL;

			m_freeList			= 1;
			m_usedList			= 0;
			s_maxHandler		= handleCount;

			return true;
		}
		release();
	}
	return false;
}

void 
CKLBDataHandler::release() {
	clearAllSet();

	if (tempArray)	{ KLBDELETEA(tempArray); tempArray  = NULL; }
	if (next)		{ KLBDELETEA(next);      next       = NULL; }
	if (prev)		{ KLBDELETEA(prev);      prev       = NULL; }

	klb_assert(m_usedList == 0, "still allocated handle");
	klb_assert(g_dataSet  == NULL, "still allocated data set %i", g_dataSet->m_userID);

}

u16 
CKLBDataHandler::allocateHandle() {
	u16 handle = m_freeList;
	klb_assert(handle, "No free handle available !!!");
	if (handle) {
		m_freeList = next[m_freeList];

		if (m_usedList) {
			klb_assert(m_usedList < s_maxHandler, "Invalid Index");
			prev[m_usedList] = handle;
		}

		next[handle] = m_usedList;
		prev[handle] = 0;
		m_usedList	 = handle;
	}
	return handle;
}

void 
CKLBDataHandler::releaseHandle(u16 handle) {
	if (handle) {
		klb_assert(handle < s_maxHandler, "Invalid Index");

		//
		// Remove from active list.
		//
		if (next[handle]) {
			klb_assert(next[handle] < s_maxHandler, "Invalid Index");
			prev[next[handle]]	= prev[handle];
		}

		if (prev[handle]) {
			klb_assert(prev[handle] < s_maxHandler, "Invalid Index");
			next[prev[handle]]	= next[handle];
		} else {
			m_usedList			= next[handle];
		}

		if (tempArray[handle]) {
			tempArray[handle]->decrementRefCount();
			tempArray[handle] = NULL;
		}

		//
		// Add to free list.
		//
		next[handle] = m_freeList;
		prev[handle] = 0;
		m_freeList	 = handle;
		if (m_freeList) {
			klb_assert(m_freeList < s_maxHandler, "Invalid Index");
			prev[m_freeList] = handle;
		}
	}
}

u16 
CKLBDataHandler::allocateHandle(void* ptr) {
	u16 handle = allocateHandle();
	if (handle) {
		klb_assert(handle < s_maxHandler, "Invalid Index");

		tempArray[handle] = (CKLBAbstractAsset*)ptr;
		if (ptr) {
			tempArray[handle]->incrementRefCount();
		}
	}
	return handle;
}

void 
CKLBDataHandler::setPointer(u16 handle, void* ptr) {
	if (handle) {
		klb_assert(handle < s_maxHandler, "Invalid Index");

		if (tempArray[handle]) {
			tempArray[handle]->decrementRefCount();
		}

		tempArray[handle] = (CKLBAbstractAsset*)ptr;

		if (ptr) {
			tempArray[handle]->incrementRefCount();
		}
	}
}

void* 
CKLBDataHandler::getPointer(u16 handle) {
	klb_assert(handle < s_maxHandler, "Invalid Index");
	return tempArray[handle];
}

void 
CKLBDataHandler::dumpDataSet() {
	CKLBDataSet* pSet = g_dataSet;
	FILE* pFile = CPFInterface::getInstance().client().getShellOutput();
	fprintf(pFile,"\n==== Global Data Set (lock list) Start ===\n");
	int count = 0;
	while (pSet) {
		fprintf(pFile,"[List %i]\n",count++);
		CKLBDataSet::Handle* pHandle = pSet->m_listHandle;
		while (pHandle) {
			u32 handle = pHandle->handle;
			CKLBAbstractAsset* pAsset = (CKLBAbstractAsset*)getPointer(handle);
			fprintf(pFile,"Handle[%i] %s (Cnt:%i)\n", handle, pHandle->name,pAsset->getRefCount());

			pHandle = pHandle->next;
		}
		pSet = pSet->m_next;
	}
	fprintf(pFile,"\n==== Global Data Set End ===\n");
}

void 
CKLBDataHandler::clearAllSet() {
	while (g_dataSet) {
		// g_dataSet is updated inside the destroy.
		destroySet(g_dataSet);
	}
}

CKLBDataSet* 
CKLBDataHandler::createSet(u32 setUserID) {
	CKLBDataSet* pDataSet = KLBNEW(CKLBDataSet);
	if (pDataSet) {
		pDataSet->m_next	= g_dataSet;
		pDataSet->m_userID	= setUserID;
		g_dataSet			= pDataSet;
	}
	return pDataSet;
}

void 
CKLBDataHandler::destroySet(CKLBDataSet* set) {
	if (set) {
		CKLBDataSet* curr = g_dataSet;
		CKLBDataSet* prev = NULL;

		while (curr) {
			if (curr == set) {
				// Remove from link list.
				if (prev == NULL) {
					g_dataSet = curr->m_next;
				} else {
					prev->m_next	= curr->m_next;
				}

				KLBDELETE(set);

				return; // Exit the function
			}
			prev = curr;
			curr = curr->m_next;
		}

		klb_assertAlways("Try to delete a set that is already deleted !");
	} else {
		klb_assertAlways("Can not destroy null data set.");
	}
}


// =====================================================================
//   Handler data set.
// =====================================================================

CKLBDataSet::CKLBDataSet()
: m_listHandle	(NULL)
, m_next		(NULL)
, m_listTask	(NULL)
{
}

CKLBDataSet::~CKLBDataSet() {
	Handle* pHandle = m_listHandle;
	while (pHandle) {
		Handle* pHandleNext = pHandle->next;
		//
		CKLBDataHandler::releaseHandle(pHandle->handle);
		KLBDELETEA(pHandle->name);
		KLBDELETE(pHandle);
		//
		pHandle = pHandleNext;
	}
	m_listHandle = NULL;

	klb_assert(!m_listTask, "List Task should be empty.");
	TaskWrapper* pTask = m_listTask;
	while (pTask) {
		TaskWrapper* pNTask = pTask->m_pNext;
		KLBDELETE(pTask);
		pTask = pNTask;
	}
	m_listTask = NULL;
}

u32 
CKLBDataSet::getClassID()
{
	return CLS_KLBDATASET;
}


u16 
CKLBDataSet::allocateHandle(void* ptr, char* /*name*/) {
	u16 handle = 0;
	if (/*name &&*/ ptr) {
//		u32 strLen = strlen(name) + 1;
//		char* newName = (char*)KLBNEWA(char*,strLen);
//		if (newName) {
//			memcpy(newName, name, strLen);
			handle = CKLBDataHandler::allocateHandle(ptr);
			if (handle) {
				addHandle(handle , NULL/*newName*/);
//			} else {
//				KLBDELETEA(newName);
			}
//		}
	} else {
		klb_assertNull(0,"can not store null pointer");
	}
	return handle;
}

/*
u16 
CKLBDataSet::getHandleFromName(char* name) {
	if (name) {
		Handle* pHandle = m_listHandle;
		while (pHandle) {
			if (strcmp(name, pHandle->name)==0) {
				return pHandle->handle;
			}
			pHandle = pHandle->next;
		}
	}
	klb_assertNull(0, "return null handle");
	return 0;
}*/

CKLBDataSet::Handle* 
CKLBDataSet::addHandle(u16 handle, char* name) {
	Handle* newHandle = KLBNEW(Handle);
	if (newHandle) {
		newHandle->handle	= handle;
		newHandle->name		= name;

		newHandle->next     = m_listHandle;
		m_listHandle	    = newHandle;
	}
	return newHandle;
}

bool 
CKLBDataSet::addTask(void* ptrTask) {
	TaskWrapper* newTaskWrapper = KLBNEW(TaskWrapper);
	if (newTaskWrapper) {
		newTaskWrapper->ptrTask	= ptrTask;
		newTaskWrapper->m_pNext = m_listTask;
		m_listTask	= newTaskWrapper;
		return true;
	}
	return false;
}

void 
CKLBDataSet::removeTask(void* ptrTask) {
	if (ptrTask) {
		TaskWrapper* curr = m_listTask;
		TaskWrapper* prev = NULL;

		while (curr) {
			if (curr->ptrTask == ptrTask) {
				// Remove from link list.
				if (prev == NULL) {
					m_listTask		= curr->m_pNext;
				} else {
					prev->m_pNext	= curr->m_pNext;
				}

				KLBDELETE(curr);
				break;
			}
			prev = curr;
			curr = curr->m_pNext;
		}
	}
}

bool 
CKLBDataSet::lock(CKLBTask * pTask) {
	return addTask(pTask);
}

void 
CKLBDataSet::unlock() {
	removeTask(CKLBTaskMgr::getInstance().getCurrentTask());
}
