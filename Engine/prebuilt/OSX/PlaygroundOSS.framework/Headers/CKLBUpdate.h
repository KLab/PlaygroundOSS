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
#ifndef CKLBUpdate_h
#define CKLBUpdate_h

#include "CKLBLuaTask.h"
#include "CKLBHTTPInterface.h"
#include "CUnZip.h"
#include "ILuaFuncLib.h"
#include "MultithreadedNetwork.h"

/*!
* \class CKLBLuaLibUPDATE
* \brief Lua Lib Update Class
* 
* 
*/
class CKLBLuaLibUPDATE : public ILuaFuncLib
{
private:
	CKLBLuaLibUPDATE();
public:
	CKLBLuaLibUPDATE(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibUPDATE();

	void addLibrary();
private:
	static int luaUpdateHasLock		(lua_State * L);
	static int luaUpdateKillLock	(lua_State * L);
};

class CUpdateUnZip : public CUnZip
{
protected:
	bool afterExtract(const char * extract_path, bool isDirectory, size_t size);
public:
	CUpdateUnZip(const char * zipPath);
	virtual ~CUpdateUnZip();
};

/*!
* \class CKLBUpdate
* \brief Updater Task class.
* 
* CKLBUpdate is used to update files.
* It downloads it from a specified URL and unzips it.
* Specific callbacks can be registered to be called after different steps
* such as the end of the dowload step, the unzipping step or when the whole 
* process is over.
*/
class CKLBUpdate : public CKLBLuaTask
{
	friend class CKLBTaskFactory<CKLBUpdate>;
protected:
	CKLBUpdate();
	virtual ~CKLBUpdate();
public:
	virtual u32  getClassID	();
	virtual bool initScript	(CLuaState& lua);

	void execute			(u32 deltaT);
	void die				();

	static bool lockExist	();
protected:
	void exec_init_download	(u32 deltaT);
	void exec_download		(u32 deltaT);
	void exec_init_unzip	(u32 deltaT);
	void exec_unzip			(u32 deltaT);
	void exec_complete		(u32 deltaT);
	void exec_finish		(u32 deltaT);

	bool isUpdating			();
	void cleanUpdate		(const char* tmpFile);
	bool saveUpdate			();

		   s32					workThread			();
	static s32					threadFunc			(void* pThread, void* data);

protected:
	CKLBHTTPInterface	*	m_httpIF;
	CUpdateUnZip		*	m_unzip;

	enum STEP {
		S_INIT_DL,		// ダウンロード初期化
		S_DOWNLOAD,		// ダウンロード中
		S_INIT_UNZIP,	// ZIP展開初期化
		S_UNZIP,		// ZIP展開中
		S_COMPLETE,		// Ensure that zip is fully unzipped
		S_FINISHED,		// 完了
	};

	const char			*	m_callbackDL;
	const char			*	m_callbackZIP;
	const char			*	m_callbackFinish;
	const char			*	m_callbackError;
	
	void*					m_thread;
	const char			*	m_outPath;
	const char			*	m_tmpPath;
	const char			*	m_zipURL;
	s64						m_zipSize;
	float					m_maxProgress;

	volatile
	STEP					m_eStep;		// 進行ステップ
	bool					m_extracting;	// 展開中

	s64						m_dlSize;	// ダウンロード終了サイズ
	int						m_zipEntry;	// zip内のエントリ数
};

/*!
* \class CKLBUpdateZip
* \brief Updater through Zip Task class.
* 
* CKLBUpdateZip works the same way as CKLBUpdate but only unzips a file already downloaded.
*/
class CKLBUpdateZip : public CKLBUpdate
{
public:
	CKLBUpdateZip();
	virtual ~CKLBUpdateZip();

public:
	virtual u32  getClassID();
	virtual bool initScript(CLuaState& lua);
};

#endif // CKLBUpdate_h
