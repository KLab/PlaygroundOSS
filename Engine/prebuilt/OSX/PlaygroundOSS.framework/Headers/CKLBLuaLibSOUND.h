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
#ifndef CKLBLuaLibSOUND_h
#define CKLBLuaLibSOUND_h

#include "ILuaFuncLib.h"
#include "CKLBObject.h"
#include "CKLBLibRegistrator.h"

class CKLBLuaLibSOUND : public ILuaFuncLib
{
private:
	CKLBLuaLibSOUND();
public:
	CKLBLuaLibSOUND(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibSOUND();

	static CKLBLibRegistrator::LIBREGISTSTRUCT* ms_libRegStruct;

	void addLibrary();
	void destroyResources();
	bool dumpObjects(IPlatformRequest& pForm);
	static void s_dumpObjects();

	struct SOUND : public CKLBObjectScriptable {
		u32 getClassID();

		SOUND	*	prev;
		SOUND	*	next;

		void	*	hSND;	// サウンドハンドル
		const char * name;
	};
	
	inline
	static SOUND* cmdSoundOpen(const char* snd_asset, bool f_bgm) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		SOUND * pSnd = createSound(snd_asset, !f_bgm);
		if(!f_bgm) pForm.preLoad(pSnd->hSND);	// SEモードの場合はオンメモリ状態にしておく
		return pSnd;
	}

	static int removeSoundAll();

	inline
	static void cmdSoundPlay(SOUND* pSnd, u32 fade_msec, float tgtVol, float globalVol) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		// 与えられたポインタが無効であれば何もしない
		float startVol = (fade_msec > 0.0f) ? (0.0f) : (1.0f);
		if(checkSoundExist(pSnd)) pForm.playAudio(pSnd->hSND, fade_msec, tgtVol * globalVol, startVol * globalVol);
	}

	inline
	static void cmdSoundStop(SOUND* pSnd, u32 fade_msec, float tgtVol) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		if(checkSoundExist(pSnd)) pForm.stopAudio(pSnd->hSND, fade_msec, tgtVol);
	}

	inline
	static void cmdSoundVolume(SOUND* pSnd, float volume) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		if(checkSoundExist(pSnd)) pForm.setAudioVolume(pSnd->hSND, volume);
	}

	inline
	static void cmdSoundPan(SOUND* pSnd, float pan) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		if(checkSoundExist(pSnd)) pForm.setAudioPan(pSnd->hSND, pan);
	}

	inline
	static void cmdSoundPause(SOUND* pSnd) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		if(checkSoundExist(pSnd)) pForm.pauseAudio(pSnd->hSND);
	}

	inline
	static void cmdSoundResume(SOUND* pSnd) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		if(checkSoundExist(pSnd)) pForm.resumeAudio(pSnd->hSND);
	}

	inline 
	static void cmdSoundSeek(SOUND* pSnd, s32 millisec) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		if(checkSoundExist(pSnd)) pForm.seekAudio(pSnd->hSND, millisec);
	}

	inline
	static s32  cmdSoundTell(SOUND* pSnd) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		s32 millisec = 0;
		if(checkSoundExist(pSnd)) millisec = pForm.tellAudio(pSnd->hSND);
		return millisec;
	}

	inline
	static s32  cmdSoundState(SOUND* pSnd) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		s32 state = 0;
		if(checkSoundExist(pSnd)) {
			// ハンドルが見つかったのでステータスを返す
			state = pForm.getState(pSnd->hSND);
		} else {
			// ハンドルが見つからない
			state = IClientRequest::E_SOUND_STATE_INVALID_HANDLE;
		}
		return state;
	}

	inline
	static void cmdVolumeBGM(float volume) {
		CPFInterface::getInstance().platform().setMasterVolume(volume, false);
	}

	inline
	static void cmdVolumeSE(float volume) { 
		CPFInterface::getInstance().platform().setMasterVolume(volume, true);
	}

	static void removeSound(SOUND * pSnd);

	inline
	static s32 cmdGetLength(SOUND * pSnd) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		s32 length = -1;
		if(checkSoundExist(pSnd)) {
			length = pForm.totalTimeAudio(pSnd->hSND);
		}
		return length;
	}

	inline
	static void cmdSetFade(SOUND * pSnd, s32 millisec, float tgtVol) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		if(checkSoundExist(pSnd)) pForm.setFadeParam(pSnd->hSND, tgtVol, millisec);
	}
	
	inline
	static bool cmdSoundSetBufSize(SOUND* pSnd, s32 value) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		return pForm.setBufSize(pSnd->hSND, value);
	}

	inline
	static float getFormGlobalVolume() {
		return s_formGlobalVolume;
	}
private:
	static SOUND * createSound(const char * snd_asset, bool is_se);


	static int luaGetLength		(lua_State * L);
	static int luaSoundOpen		(lua_State * L);
    static int luaSetBufSize	(lua_State * L);
	static int luaSoundClose	(lua_State * L);
	static int luaSoundCloseAll	(lua_State * L);

	static int luaSoundPlay		(lua_State * L);
	static int luaSoundStop		(lua_State * L);
    static int luaSoundVolume	(lua_State * L);
    static int luaSoundPan		(lua_State * L);
	static int luaVolumeBGM		(lua_State * L);
	static int luaVolumeSE		(lua_State * L);
	static int luaVolumeFormSE	(lua_State * L);
    static int luaSoundPause	(lua_State * L);
    static int luaSoundResume	(lua_State * L);
    static int luaSoundSeek		(lua_State * L);
    static int luaSoundTell		(lua_State * L);
    
    static int luaSoundState	(lua_State * L);
    static int luaSoundSetFade	(lua_State * L);

    static int luaSoundSetMultiProcessType	(lua_State * L);
    static int luaSoundPauseOnInterruption  (lua_State * L);
    
    static bool checkSoundExist	(SOUND * pSnd);
private:


	static float		s_formGlobalVolume;
	static SOUND	*	ms_begin;
	static SOUND	*	ms_end;
};


#endif // CKLBLuaLIbSOUND_h
