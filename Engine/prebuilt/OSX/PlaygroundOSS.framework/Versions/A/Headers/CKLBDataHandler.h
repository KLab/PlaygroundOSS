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
#ifndef __KLB_DATAHANDLER__
#define __KLB_DATAHANDLER__

#include "BaseType.h"
#include "CKLBTask.h"

class CKLBDataSet;

class CKLBDataHandler {
	friend class CKLBDataSet;
public:
	static bool		init			(u16 handlerCount);
	static void		release			();

	static 
	CKLBDataSet*	createSet		(u32 userDebugID);

	static void		destroySet		(CKLBDataSet* set);
	static void		clearAllSet		();
	static void		dumpDataSet		();

	static u16		allocateHandle	();
	static void		setPointer		(u16 handle, void* ptr);
	static void		releaseHandle	(u16 handle);
	static u16		allocateHandle	(void* ptr);

	static void*	getPointer		(u16 handle);
private:
	static u32		s_maxHandler;
};

class CKLBDataSet : public CKLBObjectScriptable {
	friend class CKLBDataHandler;
private:

	CKLBDataSet				();
	~CKLBDataSet			();

public:
	u32 getClassID();

	bool	lock				(CKLBTask * pTask);
	void	unlock				();
	u16		allocateHandle		(void* ptr,  char* name);
	u16		getHandleFromName	(char* name);
	
	inline	
	void*	getPointer			(u16 handle) {
		return CKLBDataHandler::getPointer(handle);
	}

private:
	struct Handle {
		Handle* next;
		u32 handle;
		char* name;
	};

	struct TaskWrapper {
		TaskWrapper*	m_pNext;
		void*			ptrTask;
	};

	bool	addTask				(void* ptrTask);
	void	removeTask			(void* ptrTask);
	Handle*	addHandle			(u16 handle, char* name);

	CKLBDataSet*	m_next;
	Handle*			m_listHandle;
	TaskWrapper*	m_listTask;
	u32				m_userID;
};


#endif
