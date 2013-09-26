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
//
//  CKLBLuaEnv.cpp
//
#include <typeinfo>
#include "CKLBLuaEnv.h"
#include "CKLBLuaTask.h"
#include "ILuaFuncLib.h"
#include "CKLBLuaPropTask.h"
#include "CKLBDrawTask.h"
#include "CKLBUtility.h"
#include "KLBPlatformMetrics.h"
#ifdef _WIN32
#include <Windows.h>

#ifdef DEBUG_LUAEDIT
#include "RemoteDebugger.hpp"
#pragma comment(lib, "rdbglua52dll.lib")
#else
#pragma comment(lib, "lua52.lib")
#endif

#endif
;

CKLBLuaEnv::CKLBLuaEnv()
: m_L               (NULL)
, m_nowFile         (NULL)
, m_state           (NULL)
, m_bLoadScript     (false)
, m_nextLoadScript  (NULL)
, m_sysLoadEnable   (true)
, m_lowGC           (1)
, m_highGC          (1000)
, m_collect         (0)
{
}

CKLBLuaEnv::~CKLBLuaEnv()
{
    finishLuaEnv();
}

CKLBLuaEnv&
CKLBLuaEnv::getInstance()
{
    static CKLBLuaEnv instance;
    return instance;
}

void
CKLBLuaEnv::finishLuaEnv()
{
    KLBDELETE(m_state);             m_state = NULL;
    KLBDELETEA(m_nextLoadScript);   m_nextLoadScript = NULL;
    KLBDELETEA(m_nowFile);          m_nowFile = NULL;

	// Lua環境を破棄する前に、ILuaFuncLib によって生成されたリソースの破棄を行う。
	ILuaFuncLib::destroyAllResources();

    if(m_L) {
#ifdef DEBUG_LUAEDIT
		StopLuaEditRemoteDebugger();
#endif
		lua_close(m_L);
		m_L = NULL;
	}
}

bool
CKLBLuaEnv::defineInt(const char * defName, int value)
{
	// 指定された名称のグローバルラベルがすでに存在していればエラーを出す。
	lua_getglobal(m_L, defName);
	if(!lua_isnil(m_L, -1)) {
		lua_pop(m_L, 1);
		// 指定されたグローバルラベルがnilではないということは、
		// 同名で値が定義済みであるため、エラーを出す。
		return false;
	}
	lua_pop(m_L, 1);
	lua_pushinteger(m_L, value);
	lua_setglobal(m_L, defName);
	return true;
}

bool
CKLBLuaEnv::defineNum(const char * defName, float value)
{
	// 指定された名称のグローバルラベルがすでに存在していればエラーを出す。
	lua_getglobal(m_L, defName);
	if(!lua_isnil(m_L, -1)) {
		lua_pop(m_L, 1);
		// 指定されたグローバルラベルがnilではないということは、
		// 同名で値が定義済みであるため、エラーを出す。
		return false;
	}
	lua_pop(m_L, 1);
	lua_pushnumber(m_L, value);
	lua_setglobal(m_L, defName);
	return true;
}

bool
CKLBLuaEnv::defineString(const char * defName, const char * string)
{
	// 指定された名称のグローバルラベルがすでに存在していればエラーを出す。
	lua_getglobal(m_L, defName);
	if(!lua_isnil(m_L, -1)) {
		lua_pop(m_L, 1);
		// 指定されたグローバルラベルがnilではないということは、
		// 同名で値が定義済みであるため、エラーを出す。
		return false;
	}
	lua_pop(m_L, 1);
	lua_pushstring(m_L, string);
	lua_setglobal(m_L, defName);
	return true;
}

bool
CKLBLuaEnv::setupLuaEnv()
{
	m_L = luaL_newstate();
	if(!m_L) return false;

	if(lua_checkstack(m_L, 200) == 0) {
		klb_assertAlways("can not setup lua stack.");
		return false;
	}
#ifdef DEBUG_LUAEDIT
	StartLuaEditRemoteDebugger(22001, m_L);
	Sleep(1000);
#endif

	m_state = KLBNEWC(CLuaState, (m_L));
    if(!m_state) {
        lua_close(m_L);
        return false;
    }

    // ライブラリをフルセット読み込む
    luaL_openlibs(m_L);
    
	// 全てに先駆けて、NULL を定義する
	lua_pushlightuserdata(m_L, 0);
	lua_setglobal(m_L, "NULL");

    // ファクトリが生成されている全てのタスクに対し、起動関数を登録する
    IFactory::registLuaFunctions(m_L);

	// 別途定義されたLua関数ライブラリを登録する
	ILuaFuncLib::registAllLibs(m_L);
    
	// システム関数の定義
    lua_register(m_L, "sysLoad"			,CKLBLuaEnv::load		);
	lua_register(m_L, "isSysLoading"	,CKLBLuaEnv::isLoading	);
    lua_register(m_L, "sysCommand"		,CKLBLuaEnv::command	);
    lua_register(m_L, "syslog"			,CKLBLuaEnv::logging	);
    lua_register(m_L, "sysExit"			,CKLBLuaEnv::exitGame	);
	lua_register(m_L, "include"			,CKLBLuaEnv::includefile);
    lua_register(m_L, "sysInfo"			,CKLBLuaEnv::systemInfo	);
	lua_register(m_L, "sysReboot"		,CKLBLuaEnv::reboot		);
	lua_register(m_L, "sysGCRatio"		,CKLBLuaEnv::setGCRatio	);

    // ビットごとのAND/OR演算子がLuaにはないので、フラグ値計算用に関数を用意しておく。
    lua_register(m_L, "bitOR"			,CKLBLuaEnv::bitOR		);
    lua_register(m_L, "bitAND"			,CKLBLuaEnv::bitAND		);

	// ***********************
	// 注意
	// ***********************
	// 以前ここで定義されていたLua関数のうち、機能がカテゴリ的に分類できるものは、
    // 実装がそれぞれ LuaLib 以下のモジュールに移動されました。
	// Lua script から見た際に使える関数の種類や呼び出し方に変更はありません。
	//
	// CKLBLuaLibTASK	タスク操作ライブラリ
	// CKLBLuaLibDATA	データセット関連ライブラリ
	// CKLBLuaLibDB		SQLite用DBアクセスライブラリ
	// CKLBLuaLibCONV	Json<->Luaを中心としたデータ変換ライブラリ
	// CKLBLuaLibBIN	バイナリファイルライブラリ
	//
#ifdef DEBUG_LUAEDIT
	StartLuaEditRemoteDebugger(22001, m_L);
#endif

    return true;
}

int
CKLBLuaEnv::setGCRatio(lua_State * L)
{
    CLuaState lua(L);
    CKLBLuaEnv& env = CKLBLuaEnv::getInstance();
    int argc = lua.numArgs();
    if(argc == 2) {
		env.m_lowGC		= lua.getInt(1); 
		env.m_highGC	= lua.getInt(2);
	}
	lua.retBool(argc == 2);
	return 1;
}

int
CKLBLuaEnv::reboot(lua_State * L)
{
	CLuaState lua(L);
	bool bResult = false;
	if(lua.numArgs() == 0) {
		bResult = true;
		CPFInterface::getInstance().client().reboot();
	    CKLBLuaEnv& LuaEnv(CKLBLuaEnv::getInstance());
	    if (LuaEnv.m_sysLoadEnable == false) {
	        LuaEnv.m_sysLoadEnable = true; // こうする事でメンテナンス中に制御可能になれるはず.
	    }
	}
	lua.retBool(bResult);
	return 1;
}

int
CKLBLuaEnv::load(lua_State *L)
{
    CLuaState lua(L);
    CKLBLuaEnv& env = CKLBLuaEnv::getInstance();
    int argc = lua.numArgs();
    if(1 > argc) {
        env.errMsg("URL not given to sysLoad() function.");
        return 0;
    }
    if(1 < argc) {
        env.errMsg("too many argument to sysLoad() function.");
        return 0;
    }

	klb_assert(!env.m_nextLoadScript, "sysLoad() It is already called." ); 

    const char * scriptUrl = lua.getString(1);
	bool bResult = false;
    if(scriptUrl) {
		bResult = env.sysLoad(scriptUrl);
	}
	lua.retBoolean(bResult);
    return 1;
}

int 
CKLBLuaEnv::isLoading(lua_State* L) {
	CLuaState lua(L);
	CKLBLuaEnv& env = CKLBLuaEnv::getInstance();
	lua.retBoolean(env.m_nextLoadScript != NULL);
    return 1;
}

int
CKLBLuaEnv::command(lua_State *L)
{
    CLuaState lua(L);
    CKLBLuaEnv& env = CKLBLuaEnv::getInstance();
    int argc = lua.numArgs();

    if(1 > argc) {
        env.errMsg("Target TASK not given to sysCommand() function.");
        return 0;
    }
    CKLBLuaTask * pTask = (CKLBLuaTask *)lua.getPointer(1);
    if(!pTask) return 0;
	CHECKTASK(pTask);

#ifdef INTERNAL_BENCH
	s64 startCommand = CPFInterface::getInstance().platform().nanotime();
#endif
	CKLBTaskMgr::getInstance().setCurrentTask(pTask);
	int res = pTask->commandScript(lua);
	CKLBTaskMgr::getInstance().setCurrentTask(NULL);
#ifdef INTERNAL_BENCH
	logTime('F', CPFInterface::getInstance().platform().nanotime() - startCommand, pTask->getClassID());
#endif
	return res;
}

int
CKLBLuaEnv::logging(lua_State * L)
{
    CLuaState lua(L);
    CKLBLuaEnv& env = CKLBLuaEnv::getInstance();
    int argc = lua.numArgs();
    
    if(1 > argc) {
        env.errMsg("string not given to echo() function.");
        return 0;
    }
    if(1 < argc) {
        env.errMsg("too many argument to sysLog() function.");
        return 0;
    }
    const char * msg = lua.getString(1);

	cmdLogging(msg);
	
	return 0;
}

int
CKLBLuaEnv::exitGame(lua_State * /* L */)
{
    // 終了フラグセット
    CKLBTaskMgr::getInstance().setExit();
    return 0;
}


int
CKLBLuaEnv::bitOR(lua_State * L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    int val = 0;
    for(int i = 1; i <= argc; i++) {
        val |= lua.getInt(i);
    }
    lua.retInt(val);
    return 1;
}

int
CKLBLuaEnv::bitAND(lua_State *L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    int val = 0xffffffff;
    for(int i = 1; i <= argc; i++) {
        val &= lua.getInt(i);
    }
    if(argc == 0) val = 0;
    lua.retInt(val);
    return 1;
}

int
CKLBLuaEnv::systemInfo(lua_State * L)
{
    CLuaState lua(L);
    CKLBDrawResource& res = CKLBDrawResource::getInstance();

    lua.tableNew();
    
    lua.retString("width");
    lua.retInt(res.width());
    lua.tableSet();

    lua.retString("height");
    lua.retInt(res.height());
    lua.tableSet();

    // 上記以外にシステム情報として取りたい値があれば、
    // 同様に名称、値の順にスタックに積み、lua.tableSet();

    // スタック上に残る唯一の値であるテーブルが戻り値となる。
    
    return 1;
}

IReadStream *
CKLBLuaEnv::openScript(const char * scriptUrl)
{
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	IReadStream * pRds = 0;

#ifdef COMPILED_LUA
	char * script_path = (char *)CKLBUtility::copyString(scriptUrl);
	char * ext = strstr(script_path, ".lua");
	if(ext) {
		strcpy(ext, ".lc");
	} else {
		KLBDELETEA(script_path);
		script_path = NULL;
	}

	// 中間コードバイナリ名でのオープンを試みる(.lc)
	pRds = pForm.openReadStream(script_path);
	KLBDELETEA(script_path);	// パス名は用済み

	if(pRds && pRds->getStatus() == IReadStream::NORMAL) {
		return pRds;
	}
	// オープンに失敗している場合
	delete pRds;
#endif

	// 元の名前でのオープンを試みる(.lua)
	pRds = pForm.openReadStream(scriptUrl, pForm.useEncryption());
	if (pRds == NULL || pRds->getStatus() != IReadStream::NORMAL) {
		delete pRds;
		DEBUG_PRINT("SCRIPT ERROR: script not found. : %s", scriptUrl);
		klb_assertAlways("SCRIPT ERROR: script not found. : %s", scriptUrl);
		return NULL;	// オープンに失敗したら必ずNULLが返る
	}

	return pRds;
}

#ifdef INTERNAL_BENCH
struct BENCH_RECORD {
	s64		time;
	u32		classID;
	char	type;
	const char*	name;
};
BENCH_RECORD	gBenchArray[10000];
int				gBenchFill;
bool			gBenchLog = true;

void logDo() {
	gBenchLog = true;
}

s64 gLastTime;

void logStartTime() {
	gLastTime = CPFInterface::getInstance().platform().nanotime();
}

void logEndTime(char type, const char* name) {
	if (gBenchFill < 10000) {
		s64 deltaT = CPFInterface::getInstance().platform().nanotime() - gLastTime;
		gBenchArray[gBenchFill].classID = 0;
		gBenchArray[gBenchFill].type    = type;
		gBenchArray[gBenchFill].name    = name;
		gBenchArray[gBenchFill++].time  = deltaT;
	}
}

void logTime(char type, s64 time, u32 classID) {
	if (gBenchLog) {
	if (gBenchFill < 10000) {
		gBenchArray[gBenchFill].classID = classID;
		gBenchArray[gBenchFill].type = type;
		gBenchArray[gBenchFill++].time = time;
	}
	}
}

void logTimeDump() {
	DEBUG_PRINT("===========================================================");
	DEBUG_PRINT("====          Benchmark execution setup function       ====");
	DEBUG_PRINT("===========================================================");
	DEBUG_PRINT("");
	DEBUG_PRINT("[C]:Compile     [L]:Load   [S]:Setup Time [P]:Pure Lua time");
	DEBUG_PRINT("[T]:Create Task [F]:Command Task [A] Asset Load");

	DEBUG_PRINT("[L] Time:%f mS", ((gBenchArray[0].time / 1000) / 1000.0f));
	DEBUG_PRINT("[C] Time:%f mS", ((gBenchArray[1].time / 1000) / 1000.0f));
	DEBUG_PRINT("[S] Time:%f mS", ((gBenchArray[2].time / 1000) / 1000.0f));
	DEBUG_PRINT("[P] Time:%f mS", ((gBenchArray[3].time / 1000) / 1000.0f));
	for (int n=4; n < gBenchFill; n++) {
		const char* name    = IFactory::getClassName(gBenchArray[n].classID);
		const char* tab     = "";
		const char* assName = "";
		if (gBenchArray[n].type == 'A') { 
            tab = "  "; 
            if (gBenchArray[n].name) { assName = gBenchArray[n].name; } 
        }
		DEBUG_PRINT("%s[%c] Time:%f mS ClassName:%s [%s]", tab, gBenchArray[n].type, ((gBenchArray[n].time / 1000) / 1000.0f),  name ? name : "---", assName);
	}
	gBenchFill = 0;
}
#endif

bool
CKLBLuaEnv::loadScript(const char *scriptUrl)
{
    static int callcount = 0;
    callcount++;
#ifdef INTERNAL_BENCH
	s64 loadTime = CPFInterface::getInstance().platform().nanotime();
#endif
#ifndef DEBUG_LUAEDIT

    IReadStream * pRds = openScript(scriptUrl);
    if(!pRds) { return false; }
/*
	CPFInterface::getInstance().platform().openReadStream(scriptUrl);
	if (pRds == NULL || pRds->getStatus() != IReadStream::NORMAL) {
	    if(pRds->getStatus() != IReadStream::NORMAL) {
	        delete pRds;
			DEBUG_PRINT("SCRIPT ERROR: script not found. : %s", scriptUrl);
			klb_assertAlways("SCRIPT ERROR: script not found. : %s", scriptUrl);
	    }
		return false;
	}
*/
	size_t ssize = pRds->getSize();
    u8 * buf = KLBNEWA(u8,ssize + 1);
	if(!buf) {
        delete pRds;
        return false;
    }

    // 最後まで読む
    int ret = pRds->readBlock(buf, ssize);
    delete pRds;
	buf[ ssize ] = 0;
    if(ret == 0) { return false; }
    
    
	#ifdef INTERNAL_BENCH
	s64 compileTime = CPFInterface::getInstance().platform().nanotime();
#endif

    int result = luaL_loadbuffer(m_L, (const char *)buf, ssize, scriptUrl);
	KLBDELETEA(buf);
#else
	const char * path = CPFInterface::getInstance().platform().getFullPath(scriptUrl);
	DEBUG_PRINT("[SCRIPT] load: %s", path);

	#ifdef INTERNAL_BENCH
	s64 compileTime = CPFInterface::getInstance().platform().nanotime();
#endif

	int result = luaL_loadfile(m_L, path);
	delete [] path;
#endif
    if(result) {
		const char * errmsg = lua_tostring(m_L, -1);	// エラーメッセージ取得
		char buf[1024];
		switch(result)
        {
            case LUA_ERRSYNTAX: {
                sprintf(buf, "SYNTAX ERROR: %s", errmsg);
                break;
            }
            case LUA_ERRMEM: {
                sprintf(buf, "MEMORY ERROR: %s", errmsg);
                break;
			}
			case LUA_ERRFILE: {
                sprintf(buf, "I/O ERROR: %s", errmsg);
				break;
			}
			default:
                sprintf(buf, "INTERNAL ERROR: %s", errmsg);
				break;
        }
		errMsg(buf);
		klb_assertAlways("SCRIPT ERROR: %s", buf);
        return false;
    }
    
	m_leave = false;

#ifdef INTERNAL_BENCH
	s64 startSetup = CPFInterface::getInstance().platform().nanotime();
	if (gBenchLog) {
		gBenchFill = 4;
	}
#endif

    //　グローバル域を実行
	result = lua_pcall(m_L, 0, 0, 0);

	if(result) {
    	const char * msg = NULL;
        
    	switch(result)
    	{
            default:            msg = "unknown error: %s (%s)";             break;
            case LUA_ERRRUN:    msg = "runtime error: %s (%s)";             break;
            case LUA_ERRMEM:    msg = "memory allocation error: %s (%s)";   break;
            case LUA_ERRERR:    msg = "error in error: %s (%s)";            break;
    	}
        // 呼び出しエラー: 指定の関数呼び出しに失敗
        char buf[1024];
		const char * errmsg = lua_tostring(m_L, -1);
        sprintf(buf, msg, errmsg, scriptUrl);
        errMsg(buf);
		klb_assertAlways("%s", buf);
        return false;
    }

	const char * namebuf = CKLBUtility::copyString(scriptUrl);
    if(namebuf) {
        if(m_nowFile) { KLBDELETEA(m_nowFile); }
        m_nowFile = namebuf;
    }

    m_state->callback("setup", NULL);  // setup 関数を呼ぶ
#ifdef INTERNAL_BENCH
	s64 endSetup   = CPFInterface::getInstance().platform().nanotime();

	if (gBenchLog) {
		gBenchArray[0].time = compileTime - loadTime;
		gBenchArray[1].time = startSetup - compileTime;
		gBenchArray[2].time = endSetup - startSetup;
		s64 sum = 0;
		for (int n = 4; n < gBenchFill; n++) {
			sum += gBenchArray[n].time;
		}
		gBenchArray[3].time = gBenchArray[2].time - sum;
		// gBenchLog = false;
		logTimeDump();
	}

#endif

    return true;
}

void
CKLBLuaEnv::execScript(int deltaT)
{
	bool skip = false;

	// 前回のフレームで新しいスクリプトのロードが指定されていたら、ここで現在のスクリプトと入れ替える。
    if(m_bLoadScript) {
		int fid = CKLBTaskMgr::getInstance().getFrameID();
		// 予約が行われた時点のフレームから更新されていれば、実際のロードを行う。
		// このチェックを行わないと、予約が P_SCRIPT フェーズより以前に行われている場合
		// 同フレームでロードが発生してしまうため、必ずフレームの更新が行われていることを
		// 条件とする。
		if(fid != m_loadReserveFrame) {
			const char * loadname = m_nextLoadScript;
			m_nextLoadScript = NULL;
			m_bLoadScript    = false;
			// 内部で sysLoad が呼ばれたら再びm_nextLoadScriptとm_bLoadScriptが設定されるが、
			// 今回分についてはもはや問題ではない。
			loadScript(loadname);
			KLBDELETEA(loadname);
		} else {
			// Still in the same frame as sysload was executed ('leave' already executed)
			// Skip 'execute'
			skip = true;
		}
    }

    // 現在のスクリプトの execute 関数を呼び出す
	if (!skip) {
		MEASURE_THREAD_CPU_BEGIN(TASKTYPE_LUA_EXEC);
		m_state->callback("execute", "I", deltaT);
		MEASURE_THREAD_CPU_END(TASKTYPE_LUA_EXEC);
	}

    // ガベージコレクタを走らせる
	m_collect += m_lowGC;
	if (m_collect >= m_highGC) {
		m_collect -= m_highGC;
		MEASURE_THREAD_CPU_BEGIN(TASKTYPE_LUA_GC);
		lua_gc(m_L, LUA_GCCOLLECT, 0);
		MEASURE_THREAD_CPU_END(TASKTYPE_LUA_GC);
	}
}

bool
CKLBLuaEnv::sysLoad(const char * scriptUrl)
{
    if(!m_sysLoadEnable) { return false; }
    if(!scriptUrl)       { return false; }  // ファイル名が文字列ではない

    // ここまできたら、ロードすべきスクリプトが確定しているため、
    // コマンドを保存する。次回execute()の実行直前に新しいスクリプトがロードされる。
    char * url = KLBNEWA(char, strlen(scriptUrl) + 1 );
    if(!url) { return false; }
	
    strcpy(url, scriptUrl);
    m_nextLoadScript = (const char *)url;
    m_bLoadScript    = true;

	// 予約を行ったフレームIDを記録する。
	CKLBTaskMgr& mgr = CKLBTaskMgr::getInstance();
	m_loadReserveFrame = mgr.getFrameID();

    // この場でleaveを呼ぶ
	if(!m_leave) {
		m_leave = true;
		MEASURE_THREAD_CPU_BEGIN(TASKTYPE_LUA_EXEC);
	    m_state->callback("leave", "");
		MEASURE_THREAD_CPU_END(TASKTYPE_LUA_EXEC);
	}
    return true;
}

// メンテナンスモードに突入
bool
CKLBLuaEnv::intoMaintenance()
{
	// 既にメンテナンスモードであれば何もしない
    if(!m_sysLoadEnable) { return true; }

	// 必ずこのpathのスクリプトになる
	sysLoad("asset://Maintenance.lua");
	// ロード予約ができた。以降、sysLoad()の呼び出しによる再設定を禁止
	m_sysLoadEnable = false;
	return true;
}

// メンテナンスモード解除
bool
CKLBLuaEnv::exitMaintenance()
{
	m_sysLoadEnable = true;
	CPFInterface::getInstance().client().reboot();
	return true;
}

void
CKLBLuaEnv::errMsg(const char *str)
{
    lua_Debug dbg;
    if(lua_getstack(m_L, 1, &dbg)) {
        lua_getinfo(m_L, "Sl", &dbg);
    }
    // int lnum = dbg.currentline;
    DEBUG_PRINT("SCRIPT ERROR/ %s", str);
}

int
CKLBLuaEnv::includefile(lua_State * L)
{
	CLuaState lua(L);
	const char * modname = lua.getString(1);
#ifndef DEBUG_LUAEDIT
	IReadStream * pStream = openScript(modname);
	if(!pStream) {
		lua.retBoolean(false);
		return 1;
	}
	/*
	IReadStream * pStream;
	pStream = CPFInterface::getInstance().platform().openReadStream(modname);
	if(!pStream || pStream->getStatus() != IReadStream::NORMAL) {
		delete pStream;
		DEBUG_PRINT("SCRIPT ERROR: script not found. : %s", modname);
		klb_assertAlways("SCRIPT ERROR: script not found. : %s", modname);
		lua.retBoolean(false);
		return 1;
	}
	*/
	u32 fsize = pStream->getSize();
	u8 * pool = KLBNEWA(u8, fsize + 1);
	pStream->readBlock(pool, fsize);
	pool[fsize] = 0;
	delete pStream;

	// バッファ pool の内容をチャンク modname として読み込む
	int result = luaL_loadbuffer(L, (const char *)pool, fsize, modname);
	KLBDELETEA(pool);
#else
	const char * path = CPFInterface::getInstance().platform().getFullPath(modname);
	DEBUG_PRINT("[SCRIPT] include: %s", path);
	MEASURE_THREAD_CPU_BEGIN(TASKTYPE_LUA_LOAD);
	int result = luaL_loadfile(L, path);
	MEASURE_THREAD_CPU_END(TASKTYPE_LUA_LOAD);
	delete [] path;
#endif
    if(result) {
		const char * errmsg = lua_tostring(L, -1);	// エラーメッセージ取得
		char buf[1024];
		switch(result)
        {
            case LUA_ERRSYNTAX: {
                sprintf(buf, "SYNTAX ERROR: %s", errmsg);
                break;
            }
            case LUA_ERRMEM: {
                sprintf(buf, "MEMORY ERROR: %s", errmsg);
                break;
			}
			case LUA_ERRFILE: {
                sprintf(buf, "I/O ERROR: %s", errmsg);
				break;
			}
			default:
                sprintf(buf, "INTERNAL ERROR: %s", errmsg);
				break;
        }
		getInstance().errMsg(buf);
		klb_assertAlways("SCRIPT ERROR: %s", buf);
		lua.retBoolean(false);
        return 1;
    }
    
    //　グローバル域を実行
	MEASURE_THREAD_CPU_BEGIN(TASKTYPE_LUA_EXEC);
	result = lua_pcall(L, 0, 0, 0);
	MEASURE_THREAD_CPU_END(TASKTYPE_LUA_EXEC);
	bool bRet = true;
	if(result) {
    	const char * msg = NULL;
        
    	switch(result)
    	{
            default:            msg = "unknown error: %s (%s)";             break;
            case LUA_ERRRUN:    msg = "runtime error: %s (%s)";             break;
            case LUA_ERRMEM:    msg = "memory allocation error: %s (%s)";   break;
            case LUA_ERRERR:    msg = "error in error: %s (%s)";            break;
    	}
        // 呼び出しエラー: 指定の関数呼び出しに失敗
        char buf[1024];
		const char * errmsg = lua.getString(-1);
        sprintf(buf, msg, errmsg, "[SYS]include");
        CKLBLuaEnv::getInstance().errMsg(buf);
		klb_assertAlways("%s", buf);
		bRet = false;
    }

	lua.retBoolean(bRet);
	return 1;
}

void 
CKLBLuaEnv::cmdLogging(const char* msg)
{
	// script から256byte以上の文字列が渡されることがあるので、
	// porting layer の最低要件制約にひっかからないよう255byte単位に区切って出力する。
	// ただし、platformのlogging実装によっては、
	//
	// - 出力がつながらないことがある
	// - 多バイト文字の途中で分断されてしまった挙句つながらないと、文字化けの恐れがある
	//
	// ので、「きれいに出力される」ことは保証できない。
	char buf[256];
	const char * ptr;
	int len = strlen(msg);
	ptr = msg;
	while(len > 255) {
		strncpy(buf, ptr, 255);
		buf[255] = 0;
		DEBUG_PRINT("%s", (const char *)buf);
		ptr += 255;
		len -= 255;
	}
	if(strlen(ptr) > 0) {
		DEBUG_PRINT("%s", ptr);
	}
}

void 
CKLBLuaEnv::cmdSystemInfo(int* width, int* height)
{
    CKLBDrawResource& res = CKLBDrawResource::getInstance();
    *width  = res.width();
    *height = res.height();
}

void 
CKLBLuaEnv::cmdExit()
{ 
	CKLBTaskMgr::getInstance().setExit(); 
}
