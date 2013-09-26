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
#include "CKLBAsyncLoader.h"
#include "CKLBScriptEnv.h"
;
static CKLBTaskFactory<CKLBAsyncLoader> factory("UTIL_AsyncLoader", CLS_KLBASYNCLOADER);

static volatile int gAsyncCount = 0;

CKLBAsyncLoader::CKLBAsyncLoader() 
:CKLBLuaPropTask	()
,m_callback			(NULL)
,m_pDataSet			(NULL)
,m_pAssets			(NULL)
,m_thread			(NULL)
{
	gAsyncCount++;
	m_newScriptModel = true;
}

CKLBAsyncLoader::~CKLBAsyncLoader() {
	gAsyncCount--;
}

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBAsyncLoader::ms_propItems[] = {
	{	"totalcount",	R_UINTEGER,	NULL,	(getBoolT)&CKLBAsyncLoader::getTotalCount,	0	},
	{	"processcount",	R_UINTEGER,	NULL,	(getBoolT)&CKLBAsyncLoader::getProcessCount,0	}
};

enum {
	ARG_DATASETID = 1,
	ARG_ASSET_LIST,
	ARG_CALLBACK,		            // Function name for callback
	ARG_REQUIRE		= ARG_CALLBACK,	
	ARG_NUMS		= ARG_CALLBACK
};

u32
CKLBAsyncLoader::getClassID()
{
	return CLS_KLBASYNCLOADER;
}

/*static*/
s32 
CKLBAsyncLoader::ThreadLoader(void * /* hThread */, void * data)
{
	CKLBAsyncLoader* p				= (CKLBAsyncLoader*)data;
	CKLBAssetManager::SAsset* pList	= p->m_pAssets;
	int count						= p->m_count;

	int n = 0;
	while (n < count) {
		pList[n].loadingStarted = true;
		CKLBAssetManager::getInstance().setCurrentAsyncAsset(&pList[n]);	// Loader can fill information.
		pList[n].asset = CKLBAssetManager::getInstance().loadAssetByFileName(pList[n].name, 0, false, true);
		pList[n].loadingComplete = true;
		n++;
	}

	p->m_alive = false;
	return 0;
}

CKLBAsyncLoader*
CKLBAsyncLoader::create(CKLBTask* pParentTask, const char** assets, u32 count, u32 datasetID, const char* callback) {
	CKLBAsyncLoader* pTask = KLBNEW(CKLBAsyncLoader);
    if(!pTask) { return NULL; }

	if(!pTask->init(pParentTask, assets, count, datasetID, callback)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBAsyncLoader::init(CKLBTask* pTask, const char** assets, u32 count, u32 datasetID, const char* callback) {
	// Can not create more than ONE async loader at a time.
	if (gAsyncCount > 1) { return false; }

	setStrC(m_callback,callback);

    if(!m_callback) { return false; }

	// Properties definition
	if(!setupPropertyList((const char**)CKLBAsyncLoader::ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	m_alive     = true;
	m_count	    = count;
	m_done	    = 0;
	m_lastdone  = 0;

	m_error     = 0;
	m_pDataSet  = CKLBDataHandler::createSet(datasetID);
	if (!m_pDataSet) {
		return false;
	}

	m_pAssets = KLBNEWA(CKLBAssetManager::SAsset,count * sizeof(CKLBAssetManager::SAsset));
	for (u32 n = 0; n < count; n++) {
		CKLBAssetManager::SAsset* asset = &m_pAssets[n];
		asset->name				= CKLBUtility::copyString(assets[n]);
		asset->asset			= NULL;
		asset->checked			= false;
		asset->loadingComplete	= false;
		asset->loadingStarted	= false;
		asset->added			= false;

		asset->processByMainThread	
								= true;	// Mark as not waiting anything.
		asset->pTexAsset		= NULL;
	}

	CKLBAssetManager::getInstance().setAsyncLoading(true);

	m_thread = CPFInterface::getInstance().platform().createThread(ThreadLoader,this);
	if (!m_thread) {
		return false;
	}

	return regist(pTask, P_UIPREV);
}

bool
CKLBAsyncLoader::initScript(CLuaState& lua)
{
	int argc = lua.numArgs();

    if(argc < ARG_REQUIRE || argc > ARG_NUMS) { return false; }

	const char * callback	= lua.getString(ARG_CALLBACK);
	u32 datasetID			= lua.getInt(ARG_DATASETID);

	// Get the asset list
	lua.retValue(ARG_ASSET_LIST);

	// Count the number of elements
	int max = 0;
	lua.retNil();

	// Read indexes and count entries.
	while(lua.tableNext()) {
		lua.retValue(-2);
		int idx = lua.getInt(-1);
		if(max < idx) max = idx;
		lua.pop(2);
	}

	const char** items = KLBNEWA(const char*, max);
	if(!items) return false;

	// Reset all handle to NULL
	for (int idx = 0; idx < max; idx++) {
		items[idx] = NULL;
	}

	lua.retNil();
	while(lua.tableNext()) {
		lua.retValue(-2);
		int idx = lua.getInt(-1) - 1;
		const char * name = lua.getString(-2);
		lua.pop(2);

		items[idx] = name;
	}

	return init(NULL, items, max, datasetID,callback);
}

void
CKLBAsyncLoader::die()
{
	KLBDELETEA(m_callback);
}

void
CKLBAsyncLoader::execute(u32 /*deltaT*/)
{
	bool alive = m_alive; // Copy here only ! Because of thread, do NOT read directly m_alive after.

	//
	// Check list, validate current % done.
	//
	CKLBAssetManager::SAsset* pList = m_pAssets;
	u32 n = 0;
	m_error		= 0;
	m_done		= 0;
	m_lastdone	= 0;

	while (n < m_count) {
		//
		// Is there also texture waiting for OpenGL upload ?
		//
		if (pList->loadingComplete) {
			if (pList->added == false) {
				pList->added = true;
				m_done++;
				if (pList->asset) {
					u16 handle = m_pDataSet->allocateHandle(pList->asset, NULL);
					if (handle == 0) {
						m_error++;				
					}
				} else {
					m_error++;
				}
			}
		}

		if (pList->processByMainThread == false) {
			CKLBTextureAsset* pNewAsset = pList->pTexAsset;
			CKLBOGLWrapper&		pOGLMgr			= CKLBOGLWrapper::getInstance();
			pNewAsset->m_pTexture	= pOGLMgr.createTexture(pNewAsset->m_width,
														pNewAsset->m_height,
														pList->pixelFormat,
														pList->channel,
														pNewAsset->m_bitmap,
														pList->textureSize,
														(CKLBOGLWrapper::TEX_OPTION)pList->opt);				
			pList->processByMainThread	= true;
		}
		pList++;
		n++;
	}

	if (m_done != m_lastdone) {
		m_lastdone = m_done;
		CKLBScriptEnv::getInstance().call_asyncLoader(m_callback,this,m_done,m_count);
	}

	if (!alive) {
		// Thread is dead, all texture have been processed -> Die.
		CPFInterface::getInstance().platform().deleteThread(m_thread);
		m_thread = NULL;
		CKLBAssetManager::getInstance().setAsyncLoading(false);
		kill();
	}
}
