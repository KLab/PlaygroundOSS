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
#include "CKLBUpdate.h"
#include "CKLBLuaEnv.h"
#include "CKLBUtility.h"

/**
	.lock file structure :
	Byte 0000..0999 : Tmp Zip file full path
	Byte 1000..2503 : Zip URL
	Byte 2504..2512 : Size.
	Byte 2513..2999 : UNUSED.
 */
static const char*	gUpdateFile = "file://external/_Upload_Task_Marker_.lock";

static ILuaFuncLib::DEFCONST defcmd[] = {
	{ 0, 0 }
};

static CKLBLuaLibUPDATE libdef(defcmd);

CKLBLuaLibUPDATE::CKLBLuaLibUPDATE(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibUPDATE::~CKLBLuaLibUPDATE() {}

void 
CKLBLuaLibUPDATE::addLibrary()
{
	addFunction("ONLINE_hasLock",		CKLBLuaLibUPDATE::luaUpdateHasLock);
	addFunction("ONLINE_killLock",		CKLBLuaLibUPDATE::luaUpdateKillLock);
}

int
CKLBLuaLibUPDATE::luaUpdateHasLock(lua_State * L) 
{
	CLuaState lua(L);
	bool res = CKLBUpdate::lockExist();
	lua.retBool(res);
	return 1;
}

int
CKLBLuaLibUPDATE::luaUpdateKillLock(lua_State * L) 
{
	CLuaState lua(L);
	CPFInterface::getInstance().platform().removeTmpFile(gUpdateFile);
	return 0;
}

enum {
	UPDATE_HASLOCK			= 0,
	UPDATE_KILL_LOCK		= 1,
};

static IFactory::DEFCMD cmd[] = {
	{ 0, 0 }
};

static CKLBTaskFactory<CKLBUpdate>		factoryA("ONLINE_Update",			CLS_KLBAPPUPDATE,		cmd);
static CKLBTaskFactory<CKLBUpdateZip>	factoryB("ONLINE_CompleteZip",		CLS_KLBAPPUPDATEZIP,	cmd);

enum {
	ARG_ZIPURL = 1,
	ARG_ZIPSIZE,

	ARG_TMPNAME,

	ARG_DOWNLOAD_CALLBACK,
	ARG_UNZIP_CALLBACK,
	ARG_FINISH_CALLBACK,
	ARG_ERROR_CALLBACK,

	ARG_REQUIRE = ARG_TMPNAME,
	ARG_NUM = ARG_ERROR_CALLBACK
};

enum {
	ARG_ZIPTMPNAME = 1,

	ARG_ZIPUNZIP_CALLBACK,
	ARG_ZIPFINISH_CALLBACK,
	ARG_ZIPERROR_CALLBACK,

	ARG_ZIPREQUIRE	= ARG_ZIPTMPNAME,
	ARG_ZIPNUM		= ARG_ZIPERROR_CALLBACK
};


CUpdateUnZip::CUpdateUnZip(const char * zipPath) : CUnZip(zipPath) {}
CUpdateUnZip::~CUpdateUnZip() {}

bool
CUpdateUnZip::afterExtract(const char * extract_path, bool isDirectory, size_t size)
{
    if(isDirectory || (size > 0) || (extract_path == 0)) { return true; }

	// ディレクトリではないファイルがサイズ0の場合、そのファイルは削除対象となる。
	CPFInterface::getInstance().platform().removeTmpFile(extract_path);
	return true;
}

CKLBUpdateZip::CKLBUpdateZip()
:CKLBUpdate()
{
}

CKLBUpdateZip::~CKLBUpdateZip()
{
}

bool
CKLBUpdateZip::initScript(CLuaState& lua)
{
	// bool res = true;

	int argc = lua.numArgs();

	// 引数チェック
	if(argc < ARG_ZIPREQUIRE || argc > ARG_ZIPNUM) {
		return false;
	}

	const char * callbackUnzip		= (argc >= ARG_ZIPUNZIP_CALLBACK)   ? lua.getString(ARG_ZIPUNZIP_CALLBACK)  : NULL;
	const char * callbackFinish		= (argc >= ARG_ZIPFINISH_CALLBACK)  ? lua.getString(ARG_ZIPFINISH_CALLBACK) : NULL;
	const char * callbackError		= (argc >= ARG_ZIPERROR_CALLBACK)   ? lua.getString(ARG_ZIPERROR_CALLBACK)  : NULL;
	
	const char * tmp_name			= lua.getString(ARG_ZIPTMPNAME);
	m_tmpPath						= CKLBUtility::copyString(tmp_name);

	// Load "Update" info if any
	if (lockExist()) {
		m_eStep = S_INIT_UNZIP;

		m_zipEntry			= 0;
		m_callbackZIP		= CKLBUtility::copyString(callbackUnzip);
		m_callbackFinish	= CKLBUtility::copyString(callbackFinish);
		m_callbackError		= callbackError ? CKLBUtility::copyString(callbackError) : NULL;

		return regist(NULL, P_NORMAL);
	} else {
		return false;
	}
}

u32 
CKLBUpdateZip::getClassID() 
{
	return CLS_KLBAPPUPDATEZIP;
}

CKLBUpdate::CKLBUpdate()
: CKLBLuaTask   ()
, m_unzip       (NULL)
, m_callbackDL  (NULL)
, m_callbackZIP (NULL)
, m_callbackFinish  (NULL)
, m_callbackError   (NULL)
, m_tmpPath     (NULL)
, m_zipURL      (NULL)
, m_zipSize     (0)
, m_dlSize      (0)
, m_zipEntry    (0)
, m_eStep       (S_INIT_DL)
, m_httpIF      (NULL)
{
	m_httpIF = NetworkManager::createConnection();
}

CKLBUpdate::~CKLBUpdate() {
	NetworkManager::releaseConnection(m_httpIF);
	m_httpIF = NULL;
}

u32 
CKLBUpdate::getClassID() 
{
	return CLS_KLBAPPUPDATE;
}

/*static*/
bool 
CKLBUpdate::lockExist() 
{
	IPlatformRequest& ptf = CPFInterface::getInstance().platform();
	IReadStream* pStream = ptf.openReadStream(gUpdateFile,ptf.useEncryption());
	// Does the file exist ?
	if (pStream->getStatus() == IReadStream::NORMAL) {
		delete pStream; // Do not use KLBDELETE : object created by porting layer.
		return true;
	} else {
		return false;
	}
}

void 
CKLBUpdate::cleanUpdate(const char* tmpFile) 
{
	// - DELETE Tmp Zip file if exist
	CPFInterface::getInstance().platform().removeTmpFile(tmpFile);
}

bool 
CKLBUpdate::saveUpdate() 
{
	// - Create Tmp Operation file with all data inside
	ITmpFile* file	= CPFInterface::getInstance().platform().openTmpFile(gUpdateFile);
	if (file) {
		// Close file
		delete file;
		return true;
	} else {
		return false;
	}
}

/* No Command for now.
int
CKLBUpdate::commandScript(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < 2) {
		lua.retBoolean(false);
		return 1;
	}

	int cmd = lua.getInt(2);
	switch(cmd)
	{
	}
}*/

bool
CKLBUpdate::initScript(CLuaState& lua)
{
	// bool res = true;

	int argc = lua.numArgs();

	// 引数チェック
	if(argc < ARG_REQUIRE || argc > ARG_NUM) {
		return false;
	}

	const char * callbackDownload	= (argc >= ARG_DOWNLOAD_CALLBACK)	? lua.getString(ARG_DOWNLOAD_CALLBACK)	: NULL;
	const char * callbackUnzip		= (argc >= ARG_UNZIP_CALLBACK)		? lua.getString(ARG_UNZIP_CALLBACK)		: NULL;
	const char * callbackFinish		= (argc >= ARG_FINISH_CALLBACK)		? lua.getString(ARG_FINISH_CALLBACK)	: NULL;
	const char * callbackError		= (argc >= ARG_ERROR_CALLBACK)		? lua.getString(ARG_ERROR_CALLBACK)		: NULL;
	
	const char * zip_url;
	const char * zip_size;
	const char * tmp_name;
	zip_url				= lua.getString(ARG_ZIPURL);
	zip_size			= lua.getString(ARG_ZIPSIZE);	// サイズは狂いがあると困るのでstringで受ける
	tmp_name			= lua.getString(ARG_TMPNAME);

	m_tmpPath			= CKLBUtility::copyString(tmp_name);
	m_zipURL			= CKLBUtility::copyString(zip_url);
	m_zipSize			= CKLBUtility::stringNum64(zip_size);

	m_eStep	= S_INIT_DL;
	// Start from scratch and download
	m_dlSize			= -1;
	m_zipEntry			= 0;
	m_callbackDL		= CKLBUtility::copyString(callbackDownload);
	m_callbackZIP		= CKLBUtility::copyString(callbackUnzip);
	m_callbackFinish	= CKLBUtility::copyString(callbackFinish);
	m_callbackError		= callbackError ? CKLBUtility::copyString(callbackError) : NULL;

	return regist(NULL, P_NORMAL);
}

void
CKLBUpdate::execute(u32 deltaT)
{
	switch(m_eStep)
	{
	case S_INIT_DL:		exec_init_download(deltaT); break;
	case S_DOWNLOAD:	exec_download(deltaT);		break;
	case S_INIT_UNZIP:	exec_init_unzip(deltaT);	break;
	case S_UNZIP:		/* Now multithreaded */		break;
	case S_COMPLETE:	exec_complete(deltaT);		break;
	case S_FINISHED:	exec_finish(deltaT);		break;
	}
}

/*static*/ 
s32 
CKLBUpdate::threadFunc(void* /*pThread*/, void* data) 
{
	return ((CKLBUpdate*)data)->workThread();
}

s32 
CKLBUpdate::workThread() 
{
	while (m_eStep != S_COMPLETE) {
		exec_unzip(0);
	}
	return 1;
}

void
CKLBUpdate::die()
{
	if (m_thread) {
		CPFInterface::getInstance().platform().deleteThread(m_thread);
		m_thread = NULL;
	}

	KLBDELETEA(m_zipURL);
	KLBDELETEA(m_tmpPath);
	KLBDELETEA(m_callbackZIP);
	KLBDELETEA(m_callbackDL);
	KLBDELETEA(m_callbackFinish);
	KLBDELETEA(m_callbackError);

	KLBDELETE(m_unzip);
}

void
CKLBUpdate::exec_init_download(u32 /*deltaT*/)
{
	m_httpIF->reuse();
	m_httpIF->setDownload(m_tmpPath);	// ダウンロードモードで使用する
	m_httpIF->httpGET(m_zipURL, false);	// zip取得のrequestを投げる
	m_eStep = S_DOWNLOAD;
	m_maxProgress = -1.0f; // Force first callback when set to 0.0f
}

void
CKLBUpdate::exec_download(u32 /*deltaT*/)
{
	bool bResult = m_httpIF->httpRECV();
	// Current downloaded size (may be inacurate)
	s64 size			= m_httpIF->getDwnldSize();
	// Completly download size (accurate but updated at the end)
	s64 completeOnSize	= m_httpIF->getSize();

	if(size != m_dlSize) {
		m_dlSize = size;	// 読み込み済サイズを更新
		if(m_callbackDL) {
			float progress = (m_dlSize * 1000 / m_zipSize) / 1000.0f;
			if (progress < 0.0f) {
				progress = 0.0f;

			// Trick :
			// - avoid callback at 100% because 100% is better to be done when we are sure
			//   that download is complete.
			// - because of inacurracy, we may also go over 100%
			} else if (progress >= 0.999f) {	
				progress = 0.999f;
			}

			char buf[64];
			CKLBUtility::numString64(buf, (u64)(m_zipSize * progress));

			// Ensure that we get only higher values, no backward.
			if (progress > m_maxProgress) {
				m_maxProgress = progress;
				// Only perform callback here when progress is NOT complete.
				if (!bResult) {
					CKLBScriptEnv::getInstance().call_eventUpdateDownload(m_callbackDL, this, (double)progress, buf);
				}
			}
		}
	}

	// 平成24年12月17日(月)
	// RECVの結果がtrueの時、
	// もしdownload sizeとそもそものzip sizeとの値が異なっている場合は正常に受信できていないので、
	// ひとまずリトライするようにしてみる.
	if(bResult) {
		if (completeOnSize == m_zipSize) {
			char buf[64];
			CKLBUtility::numString64(buf, completeOnSize);
			// Perform a 100% callback here because we know download IS complete.
			CKLBScriptEnv::getInstance().call_eventUpdateDownload(m_callbackDL, this, (double)1.0, buf);
			saveUpdate();
			m_eStep = S_INIT_UNZIP;
		} else {
			CKLBScriptEnv::getInstance().call_eventUpdateError(m_callbackError, this);
			DEBUG_PRINT("[update] download success but with invalid size. retry.");
			m_eStep = S_INIT_DL;
		}
	}
}

void
CKLBUpdate::exec_init_unzip(u32 /*deltaT*/)
{
	const char * fullpath = CPFInterface::getInstance().platform().getFullPath(m_tmpPath);
	m_unzip = KLBNEWC(CUpdateUnZip, (fullpath));

	if (!m_unzip->getStatus()) {	// invalid zip file
		CKLBScriptEnv::getInstance().call_eventUpdateError(m_callbackError, this);
		DEBUG_PRINT("[update] invalid zip file");
		// do not change m_eStep, thus it will retry again as the download step do
		return;
	}

	m_zipEntry   = m_unzip->numEntry();	// あらかじめエントリ数を取得しておく
	m_extracting = false;
	m_eStep      = S_UNZIP;

	m_thread = CPFInterface::getInstance().platform().createThread(threadFunc,this);
}

void
CKLBUpdate::exec_unzip(u32 /*deltaT*/)
{
	bool bResult = true;
	if(m_extracting) {
		if(m_unzip->isFinishExtract()) {
			// 戻り値が true であれば読み込みが終わっている
			m_extracting = false;
			bResult = m_unzip->gotoNextFile();	// 次のファイルへ

			// 現在展開済みのファイル数を得る
			int finished = m_unzip->getFinishedEntry();
			CKLBScriptEnv::getInstance().call_eventUpdateZIP(m_callbackZIP, this, finished, m_zipEntry);

			if(!bResult) {
				// 展開終了
				KLBDELETE(m_unzip);
				m_unzip = NULL;
				// テンポラリzip削除
				CPFInterface::getInstance().platform().removeTmpFile(m_tmpPath);
				m_eStep = S_COMPLETE;
			}
		}
	}
	// 次のファイルがあり、なおかつ展開処理が終了していれば次のファイルの読み込みを開始する
	if(bResult && !m_extracting) {
		if(m_unzip->readCurrentFileInfo()) {
			m_unzip->extractCurrentFile("file://external/");
			m_extracting = true;
		}
	}
}

void
CKLBUpdate::exec_complete(u32 /*deltaT*/) 
{
	if (m_thread) {
		CPFInterface::getInstance().platform().deleteThread(m_thread);
		m_thread = NULL;
	}
	// Delete Update State file.
	m_eStep = S_FINISHED;
	CPFInterface::getInstance().platform().removeTmpFile(gUpdateFile);
}

void
CKLBUpdate::exec_finish(u32 /*deltaT*/)
{
	CKLBScriptEnv::getInstance().call_eventUpdateComplete(m_callbackFinish, this);
	kill();
}
