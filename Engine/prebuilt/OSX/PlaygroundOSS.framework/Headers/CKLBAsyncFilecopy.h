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
#ifndef CKLBAsyncFilecopy_h
#define CKLBAsyncFilecopy_h

#include "CKLBLuaPropTask.h"

/*!
* \class CKLBAsyncFilecopy
* \brief Asynchronus File Copy Task class
* 
* File copy may be a long operation to process.
* In order to lighten the process cost for the game, it can be done
* by another thread through a CKLBAsyncFilecopy object.
* To load a resource in an asynchronous way, see CKLBAsyncLoader.
*/
class CKLBAsyncFilecopy : public CKLBLuaPropTask
{
	friend class CKLBTaskFactory<CKLBAsyncFilecopy>;
private:
	CKLBAsyncFilecopy();
	virtual ~CKLBAsyncFilecopy();

	bool init(CKLBTask* pParentTask, const char* sourceFile, const char* destFile, const char* callback);
public:
	static CKLBAsyncFilecopy* create(CKLBTask* pParentTask, const char* sourceFile, const char* destFile, const char* callback);

	bool		initScript		(CLuaState& lua);

	void		execute			(u32 deltaT);
	void		die				();

	virtual u32 getClassID		();

	inline u32 getProcessCount	()		{ return m_done;	}
	inline u32 getError			()		{ return m_error;	}

private:
	static s32 ThreadLoader(void * hThread, void * data);
	const char *				m_callback;
	const char *				m_fileNameSrc;
	const char *				m_fileNameDst;
	void*						m_thread;
	u32							m_done;
	u32							m_doneSize;
	u32							m_checkSize;
	u32							m_error;
	static	PROP_V2				ms_propItems[];
};


#endif // CKLBAsyncFilecopy_h
