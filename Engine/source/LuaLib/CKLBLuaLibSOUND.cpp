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
#include "CKLBLuaLibSOUND.h"
#include "CPFInterface.h"
#include "CKLBUtility.h"

CKLBLibRegistrator::LIBREGISTSTRUCT* CKLBLuaLibSOUND::ms_libRegStruct = CKLBLibRegistrator::getInstance()->add("LibSound", CLS_KLBSOUNDOBJ);

static ILuaFuncLib::DEFCONST luaConst[] = {
	{ "SND_BUF_SMALL",	0 },
	{ "SND_BUF_MEDIUM",	1 },
	{ "SND_BUF_LARGE",	2 },
    
    // 再生状態lua定数
    { "SND_STATE_PLAY", IClientRequest::E_SOUND_STATE_PLAY },
    { "SND_STATE_PAUSE", IClientRequest::E_SOUND_STATE_PAUSE },
    { "SND_STATE_STOP", IClientRequest::E_SOUND_STATE_STOP },
    { "SND_STATE_INVALID_HANDLE", IClientRequest::E_SOUND_STATE_INVALID_HANDLE },
    
    // サウンドのミュージックとの並行処理タイプlua定数
    { "SND_MULTIPROCESS_MUSIC_CUT",     IClientRequest::E_SOUND_MULTIPROCESS_MUSIC_CUT },
    { "SND_MULTIPROCESS_SOUND_CUT",     IClientRequest::E_SOUND_MULTIPROCESS_SOUND_CUT },
    { "SND_MULTIPROCESS_SOUND_BGM_CUT", IClientRequest::E_SOUND_MULTIPROCESS_SOUND_BGM_CUT },
    
	{ 0, 0 }
};
static CKLBLuaLibSOUND libdef(luaConst);

CKLBLuaLibSOUND::SOUND * CKLBLuaLibSOUND::ms_begin = 0;
CKLBLuaLibSOUND::SOUND * CKLBLuaLibSOUND::ms_end = 0;
float					 CKLBLuaLibSOUND::s_formGlobalVolume = 1.0f;

u32
CKLBLuaLibSOUND::SOUND::getClassID()
{
	return CLS_KLBSOUNDOBJ;
}

CKLBLuaLibSOUND::CKLBLuaLibSOUND(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibSOUND::~CKLBLuaLibSOUND()
{
	// 全てのサウンドを同時に破棄
	removeSoundAll();
}

// LuaLib全破棄時に、生成したサウンドリソースをすべて破棄
void
CKLBLuaLibSOUND::destroyResources()
{
	removeSoundAll();
}

// 現在オープンされているサウンドオブジェクトのダンプ
bool
CKLBLuaLibSOUND::dumpObjects(IPlatformRequest& pForm)
{
	pForm.logging("[LuaLibSOUND]");

	SOUND * pSnd = ms_begin;
	bool bResult = false;
	while(pSnd) {
		pForm.logging("[SOUND] <%p>: %s", pSnd, (pSnd->name) ? pSnd->name : "(unknown)");
		pSnd = pSnd->next;
		bResult = true;
	}

	return bResult;
}

/*static*/ void CKLBLuaLibSOUND::s_dumpObjects() {
	FILE* pFile = CPFInterface::getInstance().client().getShellOutput();
	SOUND * pSnd = ms_begin;
	while(pSnd) {
		fprintf(pFile, " Audio Asset <%p>: %s", pSnd, (pSnd->name) ? pSnd->name : "[NO NAME]");
		pSnd = pSnd->next;
	}
}

// Lua関数の追加
void
CKLBLuaLibSOUND::addLibrary()
{
	// addFunction("<Lua関数名>",     CKLBLuaLibSOUND::<static関数名>);
	// …を列挙することで関数定義
	addFunction("SND_Open",			CKLBLuaLibSOUND::luaSoundOpen);
    addFunction("SND_setBufSize",	CKLBLuaLibSOUND::luaSetBufSize);
	addFunction("SND_Close",		CKLBLuaLibSOUND::luaSoundClose);
	addFunction("SND_CloseAll",		CKLBLuaLibSOUND::luaSoundCloseAll);
	addFunction("SND_Play",			CKLBLuaLibSOUND::luaSoundPlay);
	addFunction("SND_Stop",			CKLBLuaLibSOUND::luaSoundStop);
	addFunction("SND_Volume",		CKLBLuaLibSOUND::luaSoundVolume);
	addFunction("SND_Pan",			CKLBLuaLibSOUND::luaSoundPan);

    addFunction("SND_Pause",		CKLBLuaLibSOUND::luaSoundPause);
    addFunction("SND_Resume",		CKLBLuaLibSOUND::luaSoundResume);
    addFunction("SND_Seek",			CKLBLuaLibSOUND::luaSoundSeek);
    addFunction("SND_Tell",			CKLBLuaLibSOUND::luaSoundTell);
	addFunction("SND_getLength", 	CKLBLuaLibSOUND::luaGetLength);
    addFunction("SND_State", 		CKLBLuaLibSOUND::luaSoundState);
    addFunction("SND_Fade", 		CKLBLuaLibSOUND::luaSoundSetFade);
    
	addFunction("SND_VolumeBGM",	CKLBLuaLibSOUND::luaVolumeBGM);
	addFunction("SND_VolumeSE",		CKLBLuaLibSOUND::luaVolumeSE);
	addFunction("SND_VolumeFormSE",	CKLBLuaLibSOUND::luaVolumeFormSE);
    
    addFunction("SND_MultiProcess", CKLBLuaLibSOUND::luaSoundSetMultiProcessType);
    
    addFunction("SND_PauseOnInterruption",  CKLBLuaLibSOUND::luaSoundPauseOnInterruption);
}

CKLBLuaLibSOUND::SOUND *
CKLBLuaLibSOUND::createSound(const char * snd_asset, bool is_se)
{
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	void * hSND = pForm.loadAudio(snd_asset, is_se);
	if(!hSND) return NULL;

	SOUND * pSnd = KLBNEW(SOUND);
	if(!pSnd) {
		pForm.releaseAudio(hSND);
		return NULL;
	}
	pSnd->name = CKLBUtility::copyString(snd_asset);

	pSnd->hSND = hSND;
	pSnd->prev = ms_end;
	if(pSnd->prev) {
		pSnd->prev->next = pSnd;
	} else {
		ms_begin = pSnd;
	}
	pSnd->next = NULL;
	ms_end = pSnd;

	return pSnd;
}

int
CKLBLuaLibSOUND::removeSoundAll()
{
	SOUND * pSnd = ms_begin;
	int cnt = 0;
	while(pSnd) {
		SOUND * pNxt = pSnd->next;
		removeSound(pSnd);
		pSnd = pNxt;
		cnt++;
	}
	return cnt;
}

void
CKLBLuaLibSOUND::removeSound(SOUND * pSnd)
{
    // 与えられたポインタが無効であれば何もしない
    if(!checkSoundExist(pSnd)) return;
    
	if(pSnd->prev) {
		pSnd->prev->next = pSnd->next;
	} else {
		ms_begin = pSnd->next;
	}
	if(pSnd->next) {
		pSnd->next->prev = pSnd->prev;
	} else {
		ms_end = pSnd->prev;
	}

	// サウンドをクローズ
	CPFInterface::getInstance().platform().releaseAudio(pSnd->hSND);
	
	// 名前を破棄
	KLBDELETEA(pSnd->name);

	// 領域を破棄
	KLBDELETE(pSnd);
}

int 
CKLBLuaLibSOUND::luaGetLength(lua_State * L) 
{
	CLuaState lua(L);
	int argc = lua.numArgs();
    if(argc < 1) {
		lua.retBoolean(false);
		return 1;
	}
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    
	SOUND * pSnd = (SOUND *)lua.getPointer(1);

	s32 length = -1;
	if(checkSoundExist(pSnd)) {
		length = pForm.totalTimeAudio(pSnd->hSND);
	}
	lua.retInt(length);
	return 1;
}

int
CKLBLuaLibSOUND::luaSoundOpen(lua_State * L)
{
	CLuaState lua(L);

	int argc = lua.numArgs();
	if(argc < 1 || argc > 2) {
		lua.retNil();
		return 1;
	}
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	const char * snd_asset = lua.getString(1);
	bool f_bgm = (argc >= 2) ? lua.getBool(2) : false;

	SOUND * pSnd = createSound(snd_asset, !f_bgm);

	if( !f_bgm && pSnd ) pForm.preLoad(pSnd->hSND);	// SEモードの場合はオンメモリ状態にしておく

	lua.retPointer(pSnd);
	return 1;
}

int
CKLBLuaLibSOUND::luaSetBufSize(lua_State *L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc < 1 || argc > 2) {
        lua.retNil();
        return 1;
    }
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    SOUND * pSnd = (SOUND *)lua.getPointer(1);
    int level = lua.getInt(2);
    bool bResult = pForm.setBufSize(pSnd->hSND, level);
    lua.retBool(bResult);
    return 1;
}

int
CKLBLuaLibSOUND::luaSoundClose(lua_State * L)
{
	CLuaState lua(L);

	int argc = lua.numArgs();
	if(argc < 1) return 0;

	for(int i = 1; i <= argc; i++) {
		SOUND * pSnd = (SOUND *)lua.getPointer(i);
		removeSound(pSnd);
		lua.retNil();
	}
	return argc;
}

int
CKLBLuaLibSOUND::luaSoundCloseAll(lua_State * L)
{
	CLuaState lua(L);

	int argc = lua.numArgs();
	if(argc < 1) return 0;

	int result = removeSoundAll();

	lua.retInt(result);
	return 1;
}


int
CKLBLuaLibSOUND::luaSoundPlay(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc < 1 || argc > 4) {
		lua.retBoolean(false);
		return 1;
	}
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    
	SOUND * pSnd = (SOUND *)lua.getPointer(1);
    u32 fade_msec = 0;
    float tgtVol = 1.0f;
	float globalVol = 1.0f;
    if( argc > 1 ) {
        fade_msec = (u32)lua.getInt(2);
    }
    if( argc > 2 ) {
        tgtVol = (float)lua.getDouble(3);
    }
    if (argc > 3 ) {
		globalVol = (float)lua.getDouble(4);
	}
    // 与えられたポインタが無効であれば何もしない
	float startVol = (fade_msec > 0.0f) ? (0.0f) : (1.0f);
    if(checkSoundExist(pSnd)) pForm.playAudio(pSnd->hSND, fade_msec, tgtVol * globalVol, startVol * globalVol);
    
	lua.retBoolean(true);
	return 1;

}

int
CKLBLuaLibSOUND::luaSoundStop(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
    if(argc < 1 || argc > 3) {
		lua.retBoolean(false);
		return 1;
	}
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    
    u32 fade_msec = 0;
    float tgtVol = 0.0f;
    if( argc > 1 ) {
        fade_msec = (u32)lua.getInt(2);
    }
    if( argc > 2 ) {
        tgtVol = (float)lua.getDouble(3);
    }
    
	SOUND * pSnd = (SOUND *)lua.getPointer(1);
    if(checkSoundExist(pSnd)) pForm.stopAudio(pSnd->hSND, fade_msec, tgtVol);
	lua.retBoolean(true);
	return 1;
}

int
CKLBLuaLibSOUND::luaSoundVolume(lua_State *L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc != 2) {
        lua.retBoolean(false);
        return 1;
    }
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    SOUND * pSnd = (SOUND *)lua.getPointer(1);
    float volume = lua.getFloat(2);
    if(checkSoundExist(pSnd)) pForm.setAudioVolume(pSnd->hSND, volume);
    lua.retBoolean(true);
    return 1;
}

int
CKLBLuaLibSOUND::luaSoundPan(lua_State *L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc != 2) {
        lua.retBoolean(false);
        return 1;
    }
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    SOUND * pSnd = (SOUND *)lua.getPointer(1);
    float pan = lua.getFloat(2);
    if(checkSoundExist(pSnd)) pForm.setAudioPan(pSnd->hSND, pan);
    lua.retBoolean(true);
    return 1;
}

bool
CKLBLuaLibSOUND::checkSoundExist(CKLBLuaLibSOUND::SOUND *pSnd)
{
    SOUND * p = ms_begin;
    while(p) {
        if(p == pSnd) return true;
        p = p->next;
    }
    return false;
}

int
CKLBLuaLibSOUND::luaVolumeBGM(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retBool(false);
		return 1;
	}
	float volume = lua.getFloat(1);
	CPFInterface::getInstance().platform().setMasterVolume(volume, false);
	lua.retBool(true);
	return 1;
}

int
CKLBLuaLibSOUND::luaVolumeSE(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retBool(false);
		return 1;
	}
	float volume = lua.getFloat(1);
	CPFInterface::getInstance().platform().setMasterVolume(volume, true);
	lua.retBool(true);
	return 1;
}

#include "CKLBNode.h"
#include "CKLBUIForm.h"
#include "CKLBDrawTask.h"
static void setFormVolume_r(CKLBNode* pNode, float volume) {
	CKLBUITask* pTask = pNode->getUITask();
	if (pTask && pTask->getClassID() == CLS_KLBUIFORM) {
		CKLBUIForm* pForm = (CKLBUIForm*)pTask;
		pForm->setGlobalVolume(volume);
	} else {
		CKLBNode* pList = pNode->getChild();
		while (pList) {
			setFormVolume_r(pList, volume);
			pList = pList->getBrother();
		}
	}
}

int
CKLBLuaLibSOUND::luaVolumeFormSE(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retBool(false);
		return 1;
	}

	float volume = lua.getFloat(1);
	s_formGlobalVolume = volume;
	setFormVolume_r(CKLBDrawResource::getInstance().getRoot(), volume);

	lua.retBool(true);
	return 1;
}

int
CKLBLuaLibSOUND::luaSoundPause(lua_State * L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc < 1 || argc > 3) {
		lua.retBoolean(false);
		return 1;
	}
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    
    SOUND * pSnd = (SOUND *)lua.getPointer(1);
    u32 fade_msec = 0;
    float tgtVol = 0.0f;
    if( argc > 1 ) {
        fade_msec = (u32)lua.getInt(2);
    }
    if( argc > 2 ) {
        tgtVol = (float)lua.getDouble(3);
    }
    
    if(checkSoundExist(pSnd)) pForm.pauseAudio(pSnd->hSND, fade_msec, tgtVol);
    lua.retBoolean(true);
    return 1;
}

int
CKLBLuaLibSOUND::luaSoundResume(lua_State * L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc < 1 || argc > 3) {
		lua.retBoolean(false);
		return 1;
	}
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    
    SOUND * pSnd = (SOUND *)lua.getPointer(1);
    u32 fade_msec = 0;
    float tgtVol = 1.0f;
    if( argc > 1 ) {
        fade_msec = (u32)lua.getInt(2);
    }
    if( argc > 2 ) {
        tgtVol = (float)lua.getDouble(3);
    }
    
    if(checkSoundExist(pSnd)) pForm.resumeAudio(pSnd->hSND, fade_msec, tgtVol);
    lua.retBoolean(true);
    return 1;
}

int
CKLBLuaLibSOUND::luaSoundSeek(lua_State * L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc != 2) {
        lua.retBoolean(false);
        return 1;
    }
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    SOUND * pSnd = (SOUND *)lua.getPointer(1);
    s32 millisec = (s32)lua.getDouble(2);
    if(checkSoundExist(pSnd)) pForm.seekAudio(pSnd->hSND, millisec);
    lua.retBoolean(true);
    return 1;
}

int
CKLBLuaLibSOUND::luaSoundTell(lua_State * L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc != 1) {
        lua.retNil();
        return 1;
    }
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    SOUND * pSnd = (SOUND *)lua.getPointer(1);
    s32 millisec = 0;
    if(checkSoundExist(pSnd)) millisec = pForm.tellAudio(pSnd->hSND);
	lua.retInt(millisec);
    return 1;
}

/*!
    @brief  指定されたサウンドハンドルの状態を取得
    @param[in]  lua_state * L   luaポインタ
    @return     int             戻り値の個数
 */
int
CKLBLuaLibSOUND::luaSoundState(lua_State * L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc != 1) {
        lua.retNil();
        return 1;
    }
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    SOUND * pSnd = (SOUND *)lua.getPointer(1);
    s32 state = 0;
    if( checkSoundExist(pSnd) ) {
        // ハンドルが見つかったのでステータスを返す
        state = pForm.getState(pSnd->hSND);
    } else {
        // ハンドルが見つからない
        state = IClientRequest::E_SOUND_STATE_INVALID_HANDLE;
    }
    lua.retInt((int)state);
    return 1;
}

/*!
 @brief  指定されたサウンドハンドルの状態を取得
 @param[in]  lua_state * L   luaポインタ
 @return     int             戻り値の個数
 */
int
CKLBLuaLibSOUND::luaSoundSetFade(lua_State * L)
{
    
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc != 3) {
        lua.retBoolean(false);
        return 1;
    }
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    SOUND * pSnd = (SOUND *)lua.getPointer(1);
    s32 millisec = (s32)lua.getDouble(2);
    float tgtVol = (float)lua.getDouble(3);
    
    if(checkSoundExist(pSnd)) pForm.setFadeParam(pSnd->hSND, tgtVol, millisec);
    lua.retBoolean(true);
    return 1;
}

/*!
 @brief  サウンドのミュージックとの並行処理タイプ
 @param[in]  lua_state * L   luaポインタ
 @ret
 */
int
CKLBLuaLibSOUND::luaSoundSetMultiProcessType(lua_State * L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc != 1) {
        lua.retBoolean(false);
        return 1;
    }
    
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    s32 type = (s32)lua.getInt(1);
    pForm.setAudioMultiProcessType(type);
    
    lua.retBoolean(true);
    return 1;
}

/*!
    @brief  端末のサスペンド時の処理をエンジン側で制御するかどうか
    @param[in]  lua_state * L   luaポインタ
    @return
 */
int CKLBLuaLibSOUND::luaSoundPauseOnInterruption(lua_State * L)
{
    CLuaState lua(L);
    int argc = lua.numArgs();
    if(argc != 1) {
        lua.retBoolean(false);
        return 1;
    }
    
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    bool pauseOnInterruption = lua.getBool(1);
    pForm.setPauseOnInterruption(pauseOnInterruption);
    
    lua.retBoolean(true);
    return 1;
}






