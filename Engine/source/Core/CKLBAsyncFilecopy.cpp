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
#include "CKLBAsyncFilecopy.h"
#include "CKLBScriptEnv.h"
;
static CKLBTaskFactory<CKLBAsyncFilecopy> factory("UTIL_AsyncFilecopy", CLS_KLBASYNCFILECOPY);

#define NO_ERROR			(0)
#define ERROR_SETUP			(1)
#define ERROR_DURINGCOPY	(2)

#define ERROR_SRCFILEERR	(0x10)
#define ERROR_DSTFILEERR	(0x20)
#define ERROR_NAMING		(0x30)

CKLBAsyncFilecopy::CKLBAsyncFilecopy() 
:CKLBLuaPropTask	()
,m_callback			(NULL)
,m_thread			(NULL)
,m_fileNameSrc		(NULL)
,m_fileNameDst		(NULL)
,m_done				(0)
,m_error			(NO_ERROR)
{
	m_newScriptModel = true;
}

CKLBAsyncFilecopy::~CKLBAsyncFilecopy() {
}

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBAsyncFilecopy::ms_propItems[] = {
	{	"progress",	R_UINTEGER,	NULL,	(getBoolT)&CKLBAsyncFilecopy::getProcessCount,	0	},
	{	"error",	R_UINTEGER,	NULL,	(getBoolT)&CKLBAsyncFilecopy::getError,			0	},
};

enum {
	ARG_FILENAMESRC = 1,
	ARG_FILENAMEDST,
	ARG_CALLBACK,		            // Function name for callback
	ARG_REQUIRE		= ARG_CALLBACK,	
	ARG_NUMS		= ARG_CALLBACK
};

u32
CKLBAsyncFilecopy::getClassID()
{
	return CLS_KLBASYNCFILECOPY;
}

const char* 
extractName(const char* fullpath) {
	u32 buffLen	= strlen((const char*)fullpath);
	s32 len		= buffLen-1;

	// Start from end rollback to start.
	while (len >= 0) {
		if ((fullpath[len] == '/') || (fullpath[len] == '\\')) {
			break;
		}
		len--;
	}
	len++; // Start from next char : skip '/' or previous char (len < 0)

	fullpath = &fullpath[len];
	return fullpath;
}

/*static*/
s32 
CKLBAsyncFilecopy::ThreadLoader(void * /* hThread */, void * data)
{
	CKLBAsyncFilecopy* p			= (CKLBAsyncFilecopy*)data;

	u8 block[4096];	// 4 KB Page
	
	IPlatformRequest& pfif = CPFInterface::getInstance().platform();
	
	// Open Source
	IReadStream* pSrc	= NULL;
	if (p->m_fileNameSrc) {
		pSrc = pfif.openReadStream(p->m_fileNameSrc, pfif.useEncryption());
	}

	// Create Tmp
	ITmpFile* pDest		= NULL;
	if (p->m_fileNameDst) {
		// Force deletion if file exist.
		pfif.removeTmpFile(p->m_fileNameDst);
		// Create new file.
		pDest = pfif.openTmpFile(p->m_fileNameDst);
	}
	
	if (pSrc && (pSrc->getStatus() == IReadStream::NORMAL) && pDest && (p->m_error == 0)) {
		// Success both ?
		p->m_doneSize	= 0;
		p->m_done		= 0;

		u32 toCopy = pSrc->getSize();
		u32 fullSize = toCopy;
		
		while (toCopy) {
			u32 size;

			if (toCopy >= 4096) {
				size = 4096;
				toCopy -= size;
			} else {
				size = toCopy;
				toCopy = 0;
			}
			
			bool readOK		= pSrc->readBlock(block, size);
			u32  writeSize	= pDest->writeTmp(block, size);
			
			if (readOK && (writeSize == size)) { 
				p->m_doneSize += size;
				p->m_done = (p->m_doneSize * 100) / fullSize;
			} else {
				toCopy = 0;
				p->m_error |= ERROR_DURINGCOPY;
			}
		}

		if (p->m_error & ERROR_DURINGCOPY) {
			pfif.removeTmpFile(p->m_fileNameDst);
		}
	} else {
		p->m_error |= ERROR_SETUP;	
		if (!pSrc) {
			p->m_error |= ERROR_SRCFILEERR;
		} else if (pSrc->getStatus() != IReadStream::NORMAL) {
			p->m_error |= ERROR_SRCFILEERR;
		}
		
		if (!pDest) {
			p->m_error |= ERROR_DSTFILEERR;
		}
	}

	if (pSrc)	{ delete pSrc;  }
	if (pDest)	{ delete pDest; }

	return 0;
}

CKLBAsyncFilecopy*
CKLBAsyncFilecopy::create(CKLBTask* pParentTask, const char* filesource, const char* filedest, const char* callback) {
	CKLBAsyncFilecopy* pTask = KLBNEW(CKLBAsyncFilecopy);
    if(!pTask) { return NULL; }

	if(!pTask->init(pParentTask, filesource, filedest, callback)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBAsyncFilecopy::init(CKLBTask* pTask, const char* filesource, const char* filedest, const char* callback) {
	setStrC(m_callback,callback);

	if(!m_callback) return false;

	// Properties definition
	if(!setupPropertyList((const char**)CKLBAsyncFilecopy::ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	m_done	= 0;
	m_error	= 0;

	// Error setup :
	// - Dest or src are null ?
	const char* nameDst = NULL;
	if (filedest) {
		nameDst = extractName(filedest);
	}

	const char* nameSrc = NULL;
	if (filesource) {
		nameSrc = extractName(filesource);
	}

	if (!nameDst) {
		m_fileNameDst = NULL;
		m_error		|= ERROR_SETUP | ERROR_NAMING | ERROR_DSTFILEERR;
	} else if (!nameSrc) {
		m_fileNameDst = NULL;
		m_error		|= ERROR_SETUP | ERROR_NAMING | ERROR_SRCFILEERR;
	} else {
		if ((strcmp(nameSrc, nameDst) == 0) 
			&& (strncmp(filesource, "file://install/" , 15) == 0)
			&& (strncmp(filedest  , "file://external/", 16) == 0)) {
			m_fileNameSrc = CKLBUtility::copyString(filesource);
			m_fileNameDst = CKLBUtility::copyString(filedest);
		} else {
			m_error |= ERROR_SETUP | ERROR_NAMING;
		}
	}
	
	m_thread = CPFInterface::getInstance().platform().createThread(ThreadLoader,this);
	if (!m_thread) {
		return false;
	}

	return regist(pTask, P_UIPREV);
}

bool
CKLBAsyncFilecopy::initScript(CLuaState& lua)
{
	int argc = lua.numArgs();

	if(argc < ARG_REQUIRE || argc > ARG_NUMS) return false;

	const char * callback       = lua.getString(ARG_CALLBACK);
	const char * srcfilename    = lua.getString(ARG_FILENAMESRC);
	const char * dstfilename    = lua.getString(ARG_FILENAMEDST);

	return init(this, srcfilename, dstfilename, callback);
}

void
CKLBAsyncFilecopy::die()
{
	KLBDELETEA(m_callback);
	KLBDELETEA(m_fileNameSrc);
	KLBDELETEA(m_fileNameDst);
}

void
CKLBAsyncFilecopy::execute(u32 /*deltaT*/)
{
	if (m_checkSize != m_doneSize) {
		m_checkSize = m_doneSize;
		CKLBScriptEnv::getInstance().call_asyncFileCopy(m_callback,this,m_done,m_doneSize);
	}
}
