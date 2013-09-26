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
//  CWin32Audio.cpp
//

#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <share.h>
#include <stdio.h>
#include <math.h>

#include "CWin32Platform.h"
#include "Win32FileLocation.h"
#include "CWin32PathConv.h"
#include "CWin32Audio.h"
#include "CWin32ReadFileStream.h"
#include "CSoundAnalysis.h"

float CWin32Audio::m_masterBGMVolume = 1.0f;
float CWin32Audio::m_masterSEVolume  = 1.0f;

cAudioFadeParam* cAudioFadeParam::s_fadeParamList   = NULL;
void*            cAudioFadeParam::s_fadeParamThread = NULL;

// サウンド関係の初期化
void SoundSystemInitFor_Win32()
{
    // フェード管理の初期化
    cAudioFadeParam::AudioFadeParamInit();
}

// サウンド関係の終了処理
void SoundSystemExitFor_Win32()
{
    // フェード管理の終了
    cAudioFadeParam::AudioFadeParamExit();
}

// フェードパラメータクラス
cAudioFadeParam::cAudioFadeParam()
: m_fadeCnt (0)
, m_startVol(0.0f)
, m_endVol  (0.0f)
, m_fadeRatio       (0.0f)
, m_nowFadeInterType(INTER_TYPE_NONE)
, m_nowFadeType     (FADE_TYPE_NONE)
, m_fadeMiliSec     (0)
, m_bfade   (false)
, m_prevmseq(0)
, m_pAudio  (NULL)
, m_prev    (NULL)
, m_next    (NULL)
{
    attach();
}

cAudioFadeParam::~cAudioFadeParam()
{
    detach();
}

void cAudioFadeParam::attach()
{
    if( s_fadeParamList == NULL ) {
        s_fadeParamList = this;
    } else {
        // 先頭と入れ替え
        m_next = s_fadeParamList;
        s_fadeParamList->m_prev = this;
        s_fadeParamList = this;
    }
}

void cAudioFadeParam::detach()
{
    if( m_pAudio != NULL ) {
        return;
    }
    
    if( m_next && m_prev ) {
        m_next->m_prev = m_prev;
        m_prev->m_next = m_next;
    } else if( m_prev ) {
        // 前方のみがいるつまりは自身は末尾
        m_prev->m_next = NULL;
    } else if( m_next ) {
        // 後方のみがいるつまりは自身は先頭
        m_next->m_prev = NULL;
        s_fadeParamList = m_next;
    } else {
        // 自身のみ
        s_fadeParamList = NULL;
    }
    
    m_next = NULL;
    m_prev = NULL;
}

void cAudioFadeParam::exec()
{
    if( m_pAudio == NULL ) { return; }
    
    s64 nowSeq = 0;
    
    if( (m_bfade == false) && (m_nowFadeType != FADE_TYPE_NONE) )
    {
        m_bfade = true;
        if( m_pAudio ) {
            m_prevmseq = m_pAudio->tell();
        }
        //CPFInterface::getInstance().platform().logging("[sound] sound[%p]: fade start!", m_pAudio);
    }
    if( m_bfade )
    {
        if( m_pAudio ) {
            nowSeq = m_pAudio->tell();
        }
        
        // フェードカウントインクリメント
        m_fadeCnt += (s32)(nowSeq - m_prevmseq);
        if( m_fadeCnt >= m_fadeMiliSec ) {
            m_fadeCnt = m_fadeMiliSec;
        } else if (m_fadeCnt < 0) {
			m_fadeCnt = 0;
		}
        
        // 係数計算
        if( m_fadeCnt >= 0 ) {

            m_fadeRatio = m_startVol + ((m_endVol - m_startVol) * ((float)m_fadeCnt / (float)m_fadeMiliSec));
            if( m_fadeRatio < 0.0f ) {
                m_fadeRatio = 0.0f;
            } else if( m_fadeRatio > 1.0f ) {
                m_fadeRatio = 1.0f;
            }
        }
        
        // サウンドに大して設定
        if( m_pAudio ) {
            m_pAudio->setFadeRatio(m_fadeRatio);
        }
        
        // フェード終了の確認
        if( m_fadeCnt >= m_fadeMiliSec ) {
            m_fadeCnt = m_fadeMiliSec;
            m_bfade = false;
            
            if( m_nowFadeType == FADE_TYPE_STOP ) {
                if( m_pAudio ) {
                    m_pAudio->stop();
                }
            } else if( m_nowFadeType == FADE_TYPE_PAUSE ) {
                if( m_pAudio ) {
                    m_pAudio->pause();
                }
            }
            
            if( m_pAudio ) {
                cAudioFadeParam::Remove(m_pAudio);
            }
            m_nowFadeType = FADE_TYPE_NONE;
        }
        
        if( m_pAudio ) {
            m_prevmseq = m_pAudio->tell();
        }
    }
}

bool cAudioFadeParam::setFadeParam(s16 _fadeType, float _tgtVol, u32 _msec, s16 _interType, float _startVolume)
{
    if( _msec <= 0 || _fadeType >= FADE_TYPE_NUM || _fadeType <= FADE_TYPE_NONE ) {
        // フェードしないため初期化
        m_nowFadeType   = INTER_TYPE_NONE;
        m_nowFadeType   = FADE_TYPE_NONE;
        m_endVol        = 0.0f;
        m_fadeCnt       = 0;
        //m_fadeRatio   = 1.0f;
        m_fadeMiliSec   = 0;
        m_bfade         = false;
        m_prevmseq      = 0;
        return true;
    }
    
    m_fadeCnt       = 0;
    m_endVol        = _tgtVol;
    m_nowFadeType   = _fadeType;
    m_nowFadeInterType = _interType;
    switch( _fadeType )
    {
        case FADE_TYPE_PLAY:
        case FADE_TYPE_RESUME:
            m_startVol  = _startVolume;
            m_fadeRatio = _startVolume;
            break;
                
        case FADE_TYPE_STOP:
        case FADE_TYPE_PAUSE:
        case FADE_TYPE_PLAYING:
            if( m_pAudio ) {
                m_startVol = m_pAudio->getFadeRatio();
            }
            m_fadeRatio = m_startVol;
            break;
    }
    m_fadeMiliSec   = _msec;
    m_bfade         = false;
    m_prevmseq      = 0;
    return true;
}

/*
    @brief  サウンドのフェードパラメータの初期処理(スレッドの作成など)
 */
void cAudioFadeParam::AudioFadeParamInit()
{
    // フェード管理用のスレッド作成
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    if( s_fadeParamThread == NULL ) {
        s_fadeParamThread = pForm.createThread(ThreadAudioFadeParam, NULL);
    }
}

void cAudioFadeParam::AudioFadeParamExit()
{
    // フェード管理用のスレッド破棄
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    if( s_fadeParamThread != NULL ) {
        pForm.deleteThread(s_fadeParamThread);
        s_fadeParamThread = NULL;
    }
    
    cAudioFadeParam * pfadeParam = s_fadeParamList;
    while( pfadeParam ) {
        cAudioFadeParam* pNext = pfadeParam->m_next;
        pfadeParam->detach();
        delete pfadeParam;
        
        pfadeParam = pNext;
    }
}

void cAudioFadeParam::SetFadeParam(CWin32Audio * _audio, s16 _fadeType, float _tgtVol, u32 _msec, s16 _interType, float _startVol)
{
    // 現在の設定がある場合は上書き
    bool bFind = false;

    cAudioFadeParam * pfadeParam = s_fadeParamList;
    while( pfadeParam ) {
        cAudioFadeParam * pNext = pfadeParam->m_next;
        if( pfadeParam->m_pAudio == _audio && _audio != NULL ) {
            pfadeParam->setFadeParam(_fadeType, _tgtVol, _msec, _interType,_startVol);
            bFind = true;
            break;
        }
        pfadeParam = pNext;
    }
    
    // 見つからなかった場合は新規で作成
    if( bFind == false ) {
        cAudioFadeParam * pNew = new cAudioFadeParam;
        pNew->m_pAudio = _audio;
        pNew->setFadeParam(_fadeType, _tgtVol, _msec,1,_startVol);
    }
}

void cAudioFadeParam::Remove(void * _audio)
{
    if( _audio == NULL ) { return; }
    
    cAudioFadeParam * pfadeParam = s_fadeParamList;
    while( pfadeParam ) {
        // 先頭で次の要素を保持しておく
        cAudioFadeParam* pNext = pfadeParam->m_next;
        
        if( pfadeParam->m_pAudio == _audio ) {
            pfadeParam->m_pAudio = NULL;
            //CPFInterface::getInstance().platform().logging("[sound] sound[%p]: fade end!", _audio );
        }
        
        pfadeParam = pNext;
    }
}

s32 cAudioFadeParam::ThreadAudioFadeParam(void * /*hThread*/, void * /*data*/)
{
    while( 1 ) {
        cAudioFadeParam * pfadeParam = s_fadeParamList;
        while( pfadeParam ) {
            cAudioFadeParam* pNext = pfadeParam->m_next;
            pfadeParam->exec();
            pfadeParam = pNext;
        }
        
        pfadeParam = s_fadeParamList;
        while( pfadeParam ) {
            cAudioFadeParam* pNext = pfadeParam->m_next;
            
            // detach
            if( pfadeParam->m_pAudio == NULL ) {
                delete pfadeParam;
                pfadeParam = NULL;
            }
            
            pfadeParam = pNext;
        }
		Sleep(16);	// sleep
    }
    
    return 0; // end
}

CWin32Audio::CWin32Audio()
: m_bActive     (false)
, m_soundPath   (NULL)
, m_preLoad     (false)
, m_step        (IClientRequest::E_SOUND_STATE_INVALID_HANDLE)
, m_volume      (1.0f)
, m_fadeRatio   (1.0f)
, m_totalPlayTime(0)
, m_pDSBuffer   (0)
{
}

CWin32Audio::~CWin32Audio()
{
    closeAudio();
}

bool
CWin32Audio::openAudio(const char * path)
{
    closeAudio();
    
    CWin32PathConv& pathconv = CWin32PathConv::getInstance();
//    m_soundPath = pathconv.fullpath(path, ".wav");
    m_soundPath = pathconv.fullpath(path, ".mp3");
	m_loop_cnt = 0;
	m_step = STEP_WAIT;
    m_bActive = (m_soundPath) ? true : false;
	m_totalPlayTime = 0;

	// 演奏時間を取得
	if( m_bActive ) {
		// サウンドデータを解析
		sSoundAnalysisData analysisData;
		if( GetSoundAnalysisData(m_soundPath, &analysisData) ) {
			m_totalPlayTime = (u32)analysisData.m_totalTime;
		}
	}

    return m_bActive;
}

bool
CWin32Audio::loadMem()
{
    if(!m_bActive) { return false; }
    if(m_preLoad)  { return true;  } // 2012.12.06  同じ処理を複数回しないように追加

	CPFInterface::getInstance().platform().logging("path:%s", m_soundPath);

	CWin32AudioMgr::getInstance().loadSound(*this);

    m_preLoad = true;
    return true;
}

void
CWin32Audio::play(s32 _msec, float _tgtVol, float _startVol)
{
    if(!m_bActive) { return; }

	if(m_step == STEP_PAUSE) {
		resume(_msec, _tgtVol);
	}

	// SEとして再生
	if(m_preLoad) {
		if(m_pDSBuffer) {
			if(m_preLoad) {
				m_pDSBuffer->Stop();
				m_pDSBuffer->SetCurrentPosition(0);	// next play by top
				m_pDSBuffer->Play(0, 0, 0);
				m_step      = STEP_PLAY;
				m_loop_cnt  = 0;
				m_fadeRatio = _startVol;
				updateVolume();
				if( _msec > 0 && (_tgtVol != _startVol) ) {
					cAudioFadeParam::SetFadeParam(this, cAudioFadeParam::FADE_TYPE_PLAY, _tgtVol, _msec, (s16)_tgtVol, _startVol);
				}
			}
		}
		return;
	}

	if(m_step == STEP_PAUSE) {
		resume(_msec, _tgtVol);
		return;
	}
	if(m_step != STEP_WAIT) return;

	if(!m_bInit) {
		m_bInit = true;
	}
	m_loop_cnt = 0;

	if(!m_pDSBuffer) {
		CWin32AudioMgr::getInstance().loadSound(*this);
	}
	if(m_pDSBuffer) {
		m_pDSBuffer->Stop();
		m_pDSBuffer->Play(0, 0, DSBPLAY_LOOPING);
		m_step = STEP_PLAY;
		if( _msec > 0 && (_tgtVol != _startVol) ) {
			cAudioFadeParam::SetFadeParam(this, (s16)cAudioFadeParam::FADE_TYPE_PLAY, _tgtVol, _msec, (s16)_tgtVol, _startVol);
		}
	}
}

void
CWin32Audio::stop(s32 _msec, float _tgtVol)
{
    if(!m_bActive)   { return; }

    if(!m_pDSBuffer) { return; }

	if( _msec <= 0 ) {
		m_pDSBuffer->Stop();
		m_pDSBuffer->SetCurrentPosition(0);	// next play by top
		m_loop_cnt = 0;
		m_step = STEP_WAIT;	
	} else {
		cAudioFadeParam::SetFadeParam(this, cAudioFadeParam::FADE_TYPE_STOP, _tgtVol, _msec, 1, 0.0f);
	}
}

void
CWin32Audio::pause(s32 _msec, float _tgtVol)
{
    if(!m_pDSBuffer) { return; }

	if( m_step == STEP_PLAY ) {
		if( _msec <= 0 ) {
			m_pDSBuffer->Stop();
			m_bSeeked = false;
			m_step = STEP_PAUSE;
		} else {
			cAudioFadeParam::SetFadeParam(this, cAudioFadeParam::FADE_TYPE_PAUSE, _tgtVol, _msec, 1, 0.0f);
		}
	}
}

void
CWin32Audio::resume(s32 _msec, float _tgtVol)
{
    if(!m_pDSBuffer) { return; }

	if( m_step == STEP_PAUSE ) {
		if( m_preLoad ) {
			m_pDSBuffer->Play(0, 0, 0);
		} else {
			m_pDSBuffer->Play(0, 0, DSBPLAY_LOOPING);
		}
		m_step = STEP_PLAY;
		cAudioFadeParam::SetFadeParam(this, cAudioFadeParam::FADE_TYPE_RESUME, _tgtVol, _msec);
	}
}

void
CWin32Audio::seek(s32 /*millisec*/)
{
    if(!m_pDSBuffer) { return; }
}

s32
CWin32Audio::tell()
{
	if( m_pDSBuffer == NULL ) {
		return 0;
	}

	s32 playTime  = 0;
	DWORD playPos = 0;

	// ループ分の再生位置
	playTime = (s32)((m_sound_buf_size * m_loop_cnt * 1000.0f) / m_nAvgBytesPerSec);

	// 現在の再生位置
	m_pDSBuffer->GetCurrentPosition( &playPos, NULL );
	playTime += (s32)((playPos * 1000.0f) / m_nAvgBytesPerSec);

	return playTime;
}

/*
	@brief	総演奏時間を取得
	@param[in]	void
	@return		s32		演奏時間(ミリ秒)
*/
s32
CWin32Audio::totalPlayTime()
{
	return m_totalPlayTime;
}

s32
CWin32Audio::getState()
{
	if( m_pDSBuffer == NULL ) {
		return IClientRequest::E_SOUND_STATE_INVALID_HANDLE;
	}

	s32 state = IClientRequest::E_SOUND_STATE_INVALID_HANDLE;
	switch( m_step )
	{
	case STEP_PLAY:
		state = IClientRequest::E_SOUND_STATE_PLAY;
		break;
	case STEP_PAUSE:
		state = IClientRequest::E_SOUND_STATE_PAUSE;
		break;
	case STEP_WAIT:
		state = IClientRequest::E_SOUND_STATE_STOP;
		break;
	}
	return state;
}

void
CWin32Audio::setFadeParam(float _tgtVol, u32 _msec)
{
    if( m_step == STEP_PLAY ) {
		cAudioFadeParam::SetFadeParam(this, cAudioFadeParam::FADE_TYPE_PLAYING, _tgtVol, _msec);
    }
}

void
CWin32Audio::closeAudio()
{
    if(!m_bActive) { return; }

	// フェード管理から除外
	cAudioFadeParam::Remove(this);

    m_bActive = false;
    m_preLoad = false;
	if(m_pDSBuffer) {
		m_pDSBuffer->Release();
	}
	m_pDSBuffer = 0;
    delete [] m_soundPath;
    m_soundPath = NULL;
}

void
CWin32Audio::setVolume(float volume)
{
    if(volume >= 1.0f) { volume = 1.0f; }
	if(volume <= 0.0f) { volume = 0.0f; }
	m_volume = volume;

	updateVolume();
}

void
CWin32Audio::updateVolume()
{
	LONG vol;
	float volume = m_volume * m_fadeRatio * ((m_preLoad) ? m_masterSEVolume : m_masterBGMVolume);
	if(volume >= 1.0f) {
		vol = DSBVOLUME_MAX;
	} else if(volume <= 0.0f) {
		vol = DSBVOLUME_MIN;
	} else {
		vol = (LONG)(33.2f * log10(volume) * 100);
	}

  if (m_pDSBuffer) {
	  m_pDSBuffer->SetVolume(vol);
  }
}

void
CWin32Audio::setFadeRatio(float _fadeRatio)
{
	m_fadeRatio = _fadeRatio;
    updateVolume();
}

void
CWin32Audio::setPan(float /*pan*/)
{
}

void
CWin32Audio::setMasterVolume(float volume, bool SEmode)
{
    if(volume >= 1.0f) { volume = 1.0f; }
	if(volume <= 0.0f) { volume = 0.0f; }

	if(SEmode) {
		m_masterSEVolume = volume;
	} else {
		m_masterBGMVolume = volume;
	}
}

DWORD WINAPI
CWin32Audio::soundBufEventThread(LPVOID _lpParam)
{
	if(_lpParam) {
		return ((CWin32Audio*)_lpParam)->soundBufEvent(_lpParam);
	}
	return (DWORD)0;
}

DWORD WINAPI
CWin32Audio::soundBufEvent(LPVOID /*_lpParam*/)
{
	while( 1 ) {
		DWORD eventNo = WaitForMultipleObjects(SOUND_EVENT_NUM, m_soundEvent.m_eventHandle, FALSE, INFINITE);
		switch( eventNo ) 
		{
		case SOUND_EVENT_BUFEND:
			{
				m_loop_cnt++;

				// SEの場合はこの時点で再生停止しているため停止状態にする
				if( m_preLoad ) {
					m_step = STEP_WAIT;
					m_loop_cnt = 0;
					cAudioFadeParam::Remove(this);
				}
			}
			break;
		}
	}
	return (DWORD)0;
}

CWin32AudioMgr::CWin32AudioMgr()
: m_pDS8    (0)
, m_primary (0) 
{
}

CWin32AudioMgr::~CWin32AudioMgr()
{
	release();
}

CWin32AudioMgr&
CWin32AudioMgr::getInstance()
{
	static CWin32AudioMgr instance;
	return instance;
}


bool
CWin32AudioMgr::init(HWND hwnd)
{
	HRESULT result;
	result = DirectSoundCreate8(0, &m_pDS8, 0);
	if(result == DS_OK)	{ 
        result = m_pDS8->SetCooperativeLevel(hwnd, DSSCL_PRIORITY);
    }

	// プライマリサウンドバッファの作成
	if(result == DS_OK) {
		DSBUFFERDESC desc;
		memset((void *)&desc, 0, sizeof(DSBUFFERDESC));
		desc.dwSize     = sizeof(DSBUFFERDESC);
		desc.dwFlags    = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
		desc.dwBufferBytes  = 0;
		desc.lpwfxFormat    = 0;
		result = m_pDS8->CreateSoundBuffer(&desc, &m_primary, 0);
	}
	if(result == DS_OK) {
		WAVEFORMATEX wf;
		memset((void *)&wf, 0, sizeof(WAVEFORMATEX));
		wf.cbSize       = sizeof(WAVEFORMATEX);
		wf.wFormatTag   = WAVE_FORMAT_PCM;
		wf.nChannels    = 2;
		wf.nSamplesPerSec = 44100;
		wf.wBitsPerSample = 16;
		wf.nBlockAlign  = wf.nChannels * (wf.wBitsPerSample / 8);
		wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
		result = m_primary->SetFormat(&wf);
	}
	bool ret = false;
	if(result == DS_OK) { 
        ret = true;
    }

	return ret;
}

void
CWin32AudioMgr::release()
{
	if(m_primary) {
		m_primary->Release();
		m_primary = 0;
	}
	if(m_pDS8) {
		m_pDS8->Release();
		m_pDS8 = 0;
	}
	
}

bool
CWin32AudioMgr::loadSound(CWin32Audio& audio)
{
	// サウンドファイルの物理パス
	const char * soundpath = audio.m_soundPath;
	bool bResult;
	SNDINFO info;

	if(strstr(soundpath, ".wav")) {
		bResult = loadWAV(audio, &info);
	} else if(strstr(soundpath, ".mp3")) {
		bResult = loadMP3(audio, &info);
	} else {
		bResult = false;
	}
    if(!bResult) { return bResult; }

	HRESULT result;

	DSBUFFERDESC desc;
	memset((void *)&desc, 0, sizeof(DSBUFFERDESC));
	desc.dwSize         = sizeof(DSBUFFERDESC);
	desc.dwFlags        = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_STATIC | DSBCAPS_LOCDEFER | DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY;
	desc.dwBufferBytes  = info.size;
	desc.lpwfxFormat    = &info.format;
	desc.guid3DAlgorithm = DS3DALG_DEFAULT;

	LPDIRECTSOUNDBUFFER dsb;
	result = m_pDS8->CreateSoundBuffer(&desc, &dsb, 0);
	if(DS_OK != result) {
		return false;
	}

	// サウンドバッファイベントの登録
	if( dsb ) {
		LPDIRECTSOUNDNOTIFY8 notify;
		if( SUCCEEDED(dsb->QueryInterface(IID_IDirectSoundNotify8, (void**)&notify)) ) {
			for( int i=0; i<CWin32Audio::SOUND_EVENT_NUM; ++i ) {
				// 以前のハンドルを一度閉じる
				if( audio.m_soundEvent.m_eventHandle[i] != 0 ) {
					CloseHandle( audio.m_soundEvent.m_eventHandle[i] );
				}

				audio.m_soundEvent.m_eventHandle[i] = CreateEvent(NULL, FALSE, FALSE, NULL );

				switch( i )
				{
				case CWin32Audio::SOUND_EVENT_BUFEND:
					audio.m_soundEvent.m_posNotify[i].dwOffset = info.size - 1;
					break;
				}
				audio.m_soundEvent.m_posNotify[i].hEventNotify = audio.m_soundEvent.m_eventHandle[i];
			}

			// 以前のスレッドハンドルを一度閉じる
			if( audio.m_soundEvent.m_eventThreadHandle != 0 ) {
				CloseHandle(audio.m_soundEvent.m_eventThreadHandle);
			}

			// スレッドの作成
			DWORD threadId;
			HANDLE threadHandle;
			threadHandle = CreateThread(NULL, 0, CWin32Audio::soundBufEventThread, (LPVOID)&audio, CREATE_SUSPENDED, &threadId );
			audio.m_soundEvent.m_eventThreadId      = threadId;
			audio.m_soundEvent.m_eventThreadHandle  = threadHandle;
			if( audio.m_soundEvent.m_eventThreadHandle != 0 ) {
				ResumeThread( audio.m_soundEvent.m_eventThreadHandle );
			}

			notify->SetNotificationPositions( CWin32Audio::SOUND_EVENT_NUM, audio.m_soundEvent.m_posNotify );
			notify->Release();
		}
	}

	LPVOID p1, p2;
	DWORD size1, size2;
	result = dsb->Lock(0, info.size, &p1, &size1, &p2, &size2, 0);
	if(FAILED(result)) {
		return false;
	}

	memcpy(p1, info.data, size1);
	memcpy(p2, info.data, size2);

	// mmioRead(hsrc, (char *)p1, size1);
	// mmioRead(hsrc, (char *)p2, size2);

	dsb->Unlock(p1, size1, p2, size2);

	// ロード済みのポインタを保存する
	audio.m_pDSBuffer       = dsb;
	audio.m_sound_buf_size  = info.size;
	audio.m_nAvgBytesPerSec = info.format.nAvgBytesPerSec;

	delete [] info.data;

	return true;
}

bool
CWin32AudioMgr::loadWAV(CWin32Audio& audio, SNDINFO * info)
{
	bool res = false;

	// サウンドファイルの物理パス
	HRESULT result;
	const char * soundpath = audio.m_soundPath;
	HMMIO hsrc = 0;
	MMCKINFO file;
	MMCKINFO fmt;
	MMCKINFO data;
	MMIOINFO mmioInfo;
	memset(&mmioInfo, 0, sizeof(MMIOINFO));

	//
	// Read from file system and decrypt first.
	//
	u8*		lpBuffer		= NULL;
	u32		dwBufferLength	= 0;
	FILE*	pFile			= NULL;

	pFile = fopen(soundpath,"rb");
	if (!pFile) {
		goto exit;
	}

	// Decryption
	u32 hasHeader = 0;
	if (CWin32Platform::g_useDecryption) {
		u8 hdr[4];
		hdr[0] = 0;
		hdr[1] = 0;
		hdr[2] = 0;
		hdr[3] = 0;
		fread(hdr,1,4,pFile);
		hasHeader = decryptSetup((const u8*)soundpath, hdr);
	}

	fseek	(pFile, 0, SEEK_END);
    dwBufferLength=ftell (pFile) - (hasHeader * 4);
	if (!dwBufferLength) {
		goto exit;
	} else {
		lpBuffer = (u8*)malloc(dwBufferLength);
		if (!lpBuffer) {
			goto exit;
		}
	}
	fseek	(pFile, hasHeader * 4, SEEK_SET);
	fread	(lpBuffer, 1, dwBufferLength, pFile);

	decrypt(lpBuffer, dwBufferLength);

	// Read Complete file and 
	mmioInfo.pchBuffer = (HPSTR)lpBuffer;
	mmioInfo.cchBuffer = dwBufferLength;
	mmioInfo.fccIOProc = FOURCC_MEM;

	hsrc = mmioOpen(NULL, &mmioInfo, MMIO_ALLOCBUF|MMIO_READ|MMIO_COMPAT);
	if(!hsrc) { goto exit; }

	memset((void *)&file, 0, sizeof(MMCKINFO));
	result = mmioDescend(hsrc, &file, 0, MMIO_FINDRIFF);
	if(file.fccType != mmioFOURCC('W', 'A', 'V', 'E')) {
		goto exit;
	}
	memset((void *)&fmt, 0, sizeof(MMCKINFO));
	result = mmioDescend(hsrc, &fmt, &file, MMIO_FINDCHUNK);
	if(fmt.ckid != mmioFOURCC('f', 'm', 't', ' ')) {
		goto exit;
	}
	// Header Calculation
	int hdrsize = fmt.cksize;
    if(hdrsize < sizeof(WAVEFORMATEX)) { hdrsize = sizeof(WAVEFORMATEX); }

	memset((void *)&(info->format), 0, sizeof(WAVEFORMATEX));

	// Buffer ensure
	char * pBuf = (char *)&(info->format);
	// LPWAVEFORMATEX wf = (LPWAVEFORMATEX)pBuf;
	result = mmioRead(hsrc, pBuf, fmt.cksize);
	if(FAILED(result)) {
		goto exit;
	}
	mmioAscend(hsrc, &fmt, 0);
	for(;;) {
		result = mmioDescend(hsrc, &data, &file, 0);
		if(FAILED(result)) {
			delete [] pBuf;
			goto exit;
		}
        if(data.ckid == mmioStringToFOURCC("data", 0)) { break; }
		result = mmioAscend(hsrc, &data, 0);
	}
	char * buf = new char [ data.cksize ];
	if(!buf) {
		goto exit;
	}
	// 
	mmioRead(hsrc, buf, data.cksize);
	info->size = data.cksize;
	info->data = buf;
	res = true;

exit:
	if (pFile)		{ fclose(pFile);		}
	if (lpBuffer)	{ free(lpBuffer);		}
	if (hsrc)		{ mmioClose(hsrc, 0);	}
	return res;
}

bool
CWin32AudioMgr::loadMP3(CWin32Audio& audio, SNDINFO * info)
{
	const char * soundpath = audio.m_soundPath;
	CWin32MP3 mp3(soundpath);

    if(!mp3.getStatus()) { return false; }

	info->size = mp3.getSize();
	info->data = new char [ info->size ];
	mp3.getFormat(&(info->format));
	return mp3.readData(info->data, info->size);
}

