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
//  CWin32Audio.h
//

#ifndef CWin32Audio_h
#define CWin32Audio_h

#include <Windows.h>
#include <MMSystem.h>
#include <dsound.h>
#include "encryptFile.h"

#pragma comment(lib, "Dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#include "CWin32MP3.h"


class CWin32AudioMgr;

// サウンド全体の初期化と終了
void SoundSystemInitFor_Win32();
void SoundSystemExitFor_Win32();

// サウンドフェード管理クラス
class cAudioFadeParam
{
    friend class CWin32Audio;
public:
    cAudioFadeParam();
    virtual ~cAudioFadeParam();

    void attach	();
    void detach	();
    void exec	();
    bool setFadeParam(s16 _fadeType, float _tgtVol, u32 _msec, s16 _interType=INTER_TYPE_LINEAR, float _startVol = 0.0f);
 
    static void AudioFadeParamInit();
    static void AudioFadeParamExit();
    static void SetFadeParam(CWin32Audio * _audio, s16 _fadeType, float _tgtVol, u32 _msec, s16 _interType=INTER_TYPE_LINEAR, float _startVol = 0.0f);
    static void Remove(void * _audio);
	static s32 ThreadAudioFadeParam(void * hThread, void * data);
public:
    // フェード関係のパラメータ
    enum FADE_TYPE
    {
        FADE_TYPE_NONE = 0,
        FADE_TYPE_PLAY,         //!< fade in
        FADE_TYPE_STOP,         //!< fade out
        FADE_TYPE_PAUSE,        //!< fade out
        FADE_TYPE_RESUME,       //!< fade in
        FADE_TYPE_PLAYING,      //!< fade
        
        FADE_TYPE_NUM,
    };
    
    enum INTER_TYPE
    {
        INTER_TYPE_NONE = 0,
        INTER_TYPE_LINEAR,         //!< Linear
        
        INTER_TYPE_NUM,
    };
    
private:
    s32                 m_fadeCnt;          //!< フェードカウント(ミリ秒)
    float               m_startVol;         //!< フェード開始のボリューム値(0.0f~1.0f)
    float               m_endVol;           //!< フェード終了のボリューム値(0.0f~1.0f)
    float               m_fadeRatio;        //!< フェード割合(0.0f〜1.0f)
    s32                 m_fadeMiliSec;      //!< フェードに要する時間(ミリ秒)
    s16                 m_nowFadeInterType; //!< 現在のフェード補間タイプ
    s16                 m_nowFadeType;      //!< 現在のフェードタイプ
    bool                m_bfade;            //!< フェード中？
    s64                 m_prevmseq;         //!< 前回の再生時間
    
    CWin32Audio*        m_pAudio;           //!< 対象者s
    
    cAudioFadeParam*    m_prev;				//!< 前のフェードパラメータ
    cAudioFadeParam*    m_next;				//!< 次のフェードパラメータ
    
    static cAudioFadeParam* s_fadeParamList;
    static void*            s_fadeParamThread;
};

class CWin32Audio
{
	friend class CWin32AudioMgr;
public:
    CWin32Audio();
    virtual ~CWin32Audio();

    bool openAudio		(const char * path);
    bool loadMem		();
    void play			(s32 _msec=0, float _tgtVol=1.0f, float _startVol=1.0f);
    void stop			(s32 _msec=0, float _tgtVol=0.0f);
	void pause			(s32 _msec=0, float _tgtVol=0.0f);
	void resume			(s32 _msec=0, float _tgtVol=1.0f);
	void seek			(s32 millisec);
	s32 tell			();
	s32 totalPlayTime	();

	s32 getState		();

	void setFadeParam	(float _tgtVol, u32 _msec);

    void closeAudio		();

	void setVolume		(float volume);
	void setPan			(float pan);
	void updateVolume	();
    
    inline bool isActive() { return m_bActive; }

	inline float getFadeRatio(void) { return m_fadeRatio; }
    void setFadeRatio	(float _fadeRatio);

	static void setMasterVolume(float volume, bool SEmode);
	static DWORD WINAPI soundBufEventThread(LPVOID _lpParam);
private:
	DWORD WINAPI soundBufEvent(LPVOID _lpParam);

public:
	// 再生時間計測用
	enum
	{
		SOUND_EVENT_BUFEND = 0,	// 再生時のバッファ終端に来た際のイベント
		SOUND_EVENT_NUM,		// サウンドイベントの個数
	};
	struct sSoundEvent
	{
		DSBPOSITIONNOTIFY	m_posNotify[SOUND_EVENT_NUM];	
		HANDLE				m_eventHandle[SOUND_EVENT_NUM];	// イベントハンドル
		HANDLE				m_eventThreadHandle;			// スレッドハンドル
		DWORD				m_eventThreadId;

		sSoundEvent() 
		{
			for( int i = 0; i<SOUND_EVENT_NUM; ++i ) {
				m_eventHandle[i] = 0;
			}
			m_eventThreadHandle = 0;
			m_eventThreadId = 0;
		}
	};

private:

	enum {
		BUF_CUONT = 3
	};
	enum {
		STEP_WAIT,
		STEP_PLAY,
		STEP_PAUSE,
	};

    const char    * m_soundPath;
    // char          * m_soundFullpath;
    bool            m_bActive;
    bool            m_preLoad;
	bool			m_bInit;
	bool			m_bSeeked;

	int				m_buf_level;
	int				m_step;

	float			m_volume;

	float           m_fadeRatio;
	u32				m_totalPlayTime;	// 演奏時間

	LPDIRECTSOUNDBUFFER		m_pDSBuffer;

	sSoundEvent		m_soundEvent;
	u32				m_loop_cnt;			// ループカウント
	u32				m_sound_buf_size;	// バッファサイズ
	u32				m_nAvgBytesPerSec;	// 1秒あたりの出力バイト数

	static float	m_masterBGMVolume;
	static float	m_masterSEVolume;
};

class CWin32AudioMgr
{
	friend class CWin32Audio;
private:
	CWin32AudioMgr();
	virtual ~CWin32AudioMgr();
public:
	static CWin32AudioMgr& getInstance();

	bool init		(HWND hwnd);
	void release	();

	bool loadSound	(CWin32Audio& audio);
private:
	bool loadWAV	(CWin32Audio& audio);
	bool loadMP3	(CWin32Audio& audio);

	struct SNDINFO {
		size_t			size;
		WAVEFORMATEX	format;
		char		*	data;
	};
	bool loadWAV	(CWin32Audio& audio, SNDINFO * info);
	bool loadMP3	(CWin32Audio& audio, SNDINFO * info);

	LPDIRECTSOUND8			m_pDS8;
	LPDIRECTSOUNDBUFFER		m_primary;

	CDecryptBaseClass   m_decrypter;
	inline void decrypt(void* ptr, u32 length) {
        m_decrypter.decryptBlck(ptr, length);
    }

	inline u32 decryptSetup(const u8* ptr, const u8* hdr) {
        return m_decrypter.decryptSetup(ptr,hdr);
    }
};

#endif // CWin32Audio_h
