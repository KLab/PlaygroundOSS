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
#ifndef CKLBAsyncLoader_h
#define CKLBAsyncLoader_h

#include "CKLBLuaPropTask.h"

/*!
* \class CKLBAsyncLoader
* \brief Asynchronus Loader Task class
* 
* Loading resources can be a long task for the Game and make it long to load some scenes.
* In order to be able to keep on processing the Game Logic while loading resources, 
* CKLBAsyncLoader has been implemented.
* It allows the Engine to load resources through another thread.
* 
* To copy a file in an asynchronous way, see CKLBAsyncLoader.
*/
class CKLBAsyncLoader : public CKLBLuaPropTask
{
	friend class CKLBTaskFactory<CKLBAsyncLoader>;
private:
	CKLBAsyncLoader();
	virtual ~CKLBAsyncLoader();

	bool init(CKLBTask* pParentTask, const char** assets, u32 count, u32 datasetID, const char* callback);
public:
	static CKLBAsyncLoader* create(CKLBTask* pParentTask, const char** assets, u32 count, u32 datasetID, const char* callback);

	bool		initScript		(CLuaState& lua);

	void		execute			(u32 deltaT);
	void		die				();

	virtual u32 getClassID		();

	inline u32	getTotalCount	()		{ return m_count;	}

	inline u32	getProcessCount	()	{ return m_done;	}

private:
	static s32 ThreadLoader(void * hThread, void * data);
	CKLBAssetManager::SAsset*	m_pAssets;
	volatile bool				m_alive;
	const char	*				m_callback;
	CKLBDataSet *				m_pDataSet;
	void*						m_thread;
	u32							m_done;
	u32							m_lastdone;
	u32							m_error;
	u32							m_count;
	static	PROP_V2				ms_propItems[];
};


#endif // CKLBIntervalTimer_h
