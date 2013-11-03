/*
 iOS の API をたたくので、Objective-C++ で実装される。
 */
#import <GLKit/GLKit.h>

#include <iostream>
#import <mach/mach_time.h>

#include "CPFInterface.h"
#include "iOSFileLocation.h"
#include "CiOSPathConv.h"
#include "CiOSAudio.h"
#include "CiOSReadFileStream.h"
#include "CiOSPlatform.h"

// #define DEBUG_AUDIO

// 論理トップレベルディレクトリと、物理ディレクトリパスの対応を行うテーブル。
const CiOSAudio::LOCLIST CiOSAudio::m_toplevel[3] = {
	{ "external/",  PATH_EXTERN  },   // インストール後、更新の対象となる可変ファイル
	{ "install/",   PATH_INSTALL },   // インストール時に配置される固定ファイル
	{ 0, 0 }
};

cAudioFadeParam *cAudioFadeParam::s_fadeParamList = NULL;
void *cAudioFadeParam::s_fadeParamThread = NULL;

// フェードパラメータクラス
cAudioFadeParam::cAudioFadeParam()
: m_fadeCnt(0)
, m_startVol(0.0f)
, m_endVol(0.0f)
, m_fadeRatio(1.0f)
, m_nowFadeInterType(INTER_TYPE_NONE)
, m_nowFadeType(FADE_TYPE_NONE)
, m_fadeMiliSec(0)
, m_bfade(false)
, m_prevmseq(0)
, m_pAudio(NULL)
, m_pSession(NULL)
, m_prev(NULL)
, m_next(NULL) {
	attach();
}

cAudioFadeParam::~cAudioFadeParam() {
	detach();
}

void cAudioFadeParam::attach() {
	if (s_fadeParamList == NULL) {
		s_fadeParamList = this;
	}
	else {
		// 先頭と入れ替え
		m_next = s_fadeParamList;
		s_fadeParamList->m_prev = this;
		s_fadeParamList = this;
	}
}

void cAudioFadeParam::detach() {
	if (m_pAudio != NULL || m_pSession != NULL) {
		return;
	}
    
	if (m_next && m_prev) {
		m_next->m_prev = m_prev;
		m_prev->m_next = m_next;
	}
	else if (m_prev) {
		// 前方のみがいるつまりは自身は末尾
		m_prev->m_next = NULL;
	}
	else if (m_next) {
		// 後方のみがいるつまりは自身は先頭
		m_next->m_prev = NULL;
		s_fadeParamList = m_next;
	}
	else {
		// 自身のみ
		s_fadeParamList = NULL;
	}
    
	m_next = NULL;
	m_prev = NULL;
}

void cAudioFadeParam::exec() {
	if (m_pAudio == NULL && m_pSession == NULL) return;
    
	s64 nowSeq = 0;
    
	if ((m_bfade == false) && (m_nowFadeType != FADE_TYPE_NONE)) {
		m_bfade = true;
		if (m_pAudio) {
			m_prevmseq = m_pAudio->tell();
		}
		else if (m_pSession) {
			m_prevmseq = m_pSession->tell();
		}
#ifdef DEBUG_AUDIO
		CPFInterface::getInstance().platform().logging("[sound] bgm[%p] se[%p]: fade start!", m_pAudio, m_pSession);
#endif
	}
	if (m_bfade) {
		if (m_pAudio) {
			nowSeq = m_pAudio->tell();
		}
		else if (m_pSession) {
			nowSeq = m_pSession->tell();
		}
        
		// フェードカウントインクリメント
		m_fadeCnt += (nowSeq - m_prevmseq);
		if (m_fadeCnt >= m_fadeMiliSec) {
			m_fadeCnt = m_fadeMiliSec;
		}
		else if (m_fadeCnt < 0) {
			m_fadeCnt = 0;
		}
        
		// 係数計算
		if (m_fadeCnt >= 0) {
			m_fadeRatio = m_startVol + ((m_endVol - m_startVol) * ((float)m_fadeCnt / (float)m_fadeMiliSec));
			if (m_fadeRatio < 0.0f) {
				m_fadeRatio = 0.0f;
			}
			else if (m_fadeRatio > 1.0f) {
				m_fadeRatio = 1.0f;
			}
		}
        
		// サウンドに大して設定
		if (m_pAudio) {
			m_pAudio->setFadeRatio(m_fadeRatio);
		}
		else if (m_pSession) {
			m_pSession->setFadeRatio(m_fadeRatio);
		}
        
		// フェード終了の確認
		if (m_fadeCnt >= m_fadeMiliSec) {
			m_fadeCnt = m_fadeMiliSec;
			m_bfade = false;
            
			if (m_nowFadeType == FADE_TYPE_STOP) {
				if (m_pAudio) {
					m_pAudio->stop();
				}
				else if (m_pSession) {
					m_pSession->stop();
					m_pSession->checkSessionStoped();
				}
			}
			else if (m_nowFadeType == FADE_TYPE_PAUSE) {
				if (m_pAudio) {
					m_pAudio->pause();
				}
				else if (m_pSession) {
					//m_pSession->stop(); // SEは現在ポーズの概念が無い
				}
			}
            
			if (m_pAudio) {
				cAudioFadeParam::Remove(m_pAudio);
			}
			else if (m_pSession) {
				cAudioFadeParam::Remove(m_pSession);
			}
			m_nowFadeType = FADE_TYPE_NONE;
		}
        
		if (m_pAudio) {
			m_prevmseq = m_pAudio->tell();
		}
		else if (m_pSession) {
			m_prevmseq = m_pSession->tell();
		}
	}
}

bool cAudioFadeParam::setFadeParam(s16 _fadeType, float _tgtVol, u32 _msec, s16 _interType, float _startVolume) {
	if (_msec <= 0 || _fadeType >= FADE_TYPE_NUM || _fadeType <= FADE_TYPE_NONE) {
		// フェードしないため初期化
		m_nowFadeType = INTER_TYPE_NONE;
		m_nowFadeType = FADE_TYPE_NONE;
		m_endVol = 0.0f;
		m_fadeCnt = 0;
		//m_fadeRatio = 1.0f;
		m_fadeMiliSec = 0;
		m_bfade = false;
		m_prevmseq = 0;
		return true;
	}
    
	m_fadeCnt = 0;
	m_endVol = _tgtVol;
	m_nowFadeType = _fadeType;
	m_nowFadeInterType = _interType;
	switch (_fadeType) {
		case FADE_TYPE_PLAY:
		case FADE_TYPE_RESUME:
			m_startVol = _startVolume;
			m_fadeRatio = _startVolume;
			break;
            
		case FADE_TYPE_STOP:
		case FADE_TYPE_PAUSE:
		case FADE_TYPE_PLAYING:
			if (m_pAudio) {
				m_startVol = m_pAudio->getFadeRatio();
			}
			else {
				m_startVol = m_pSession->getFadeRatio();
			}
			m_fadeRatio = m_startVol;
			break;
	}
	m_fadeMiliSec = _msec;
	m_bfade = false;
	m_prevmseq = 0;
	return true;
}

/*
 @brief  サウンドのフェードパラメータの初期処理(スレッドの作成など)
 */
void cAudioFadeParam::AudioFadeParamInit() {
	// フェード管理用のスレッド作成
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	if (s_fadeParamThread == NULL) {
		s_fadeParamThread = pForm.createThread(ThreadAudioFadeParam, NULL);
	}
}

void cAudioFadeParam::AudioFadeParamExit() {
	// フェード管理用のスレッド破棄
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	if (s_fadeParamThread != NULL) {
		pForm.deleteThread(s_fadeParamThread);
		s_fadeParamThread = NULL;
	}
    
	cAudioFadeParam *pfadeParam = s_fadeParamList;
	while (pfadeParam) {
		cAudioFadeParam *pNext = pfadeParam->m_next;
		pfadeParam->detach();
		delete pfadeParam;
        
		pfadeParam = pNext;
	}
}

void cAudioFadeParam::SetFadeParam(CiOSAudio *_audio, CiOSAudioSession *_settion, s16 _fadeType, float _tgtVol, u32 _msec, s16 _interType, float _startVolume) {
	// 現在の設定がある場合は上書き
	bool bFind = false;
    
	cAudioFadeParam *pfadeParam = s_fadeParamList;
	while (pfadeParam) {
		cAudioFadeParam *pNext = pfadeParam->m_next;
		if (pfadeParam->m_pAudio == _audio && _audio != NULL) {
			pfadeParam->setFadeParam(_fadeType, _tgtVol, _msec, _interType, _startVolume);
			bFind = true;
			break;
		}
		else if (pfadeParam->m_pSession == _settion && _settion != NULL) {
			pfadeParam->setFadeParam(_fadeType, _tgtVol, _msec, _interType, _startVolume);
			bFind = true;
			break;
		}
		pfadeParam = pNext;
	}
    
	// 見つからなかった場合は新規で作成
	if (bFind == false) {
		cAudioFadeParam *pNew = new cAudioFadeParam;
		pNew->m_pAudio = _audio;
		pNew->m_pSession = _settion;
		pNew->setFadeParam(_fadeType, _tgtVol, _msec, _interType, _startVolume);
	}
}

void cAudioFadeParam::Remove(void *_audio) {
	if (_audio == NULL) return;
    
	cAudioFadeParam *pfadeParam = s_fadeParamList;
	while (pfadeParam) {
		// 先頭で次の要素を保持しておく
		cAudioFadeParam *pNext = pfadeParam->m_next;
        
		if (pfadeParam->m_pAudio == _audio) {
			pfadeParam->m_pAudio = NULL;
#ifdef DEBUG_AUDIO
			CPFInterface::getInstance().platform().logging("[sound] bgm[%p] se[%p]: fade end!", _audio, NULL);
#endif
		}
		if (pfadeParam->m_pSession == _audio) {
			pfadeParam->m_pSession = NULL;
#ifdef DEBUG_AUDIO
			CPFInterface::getInstance().platform().logging("[sound] bgm[%p] se[%p]: fade end!", NULL, _audio);
#endif
		}
        
		pfadeParam = pNext;
	}
}

s32 cAudioFadeParam::ThreadAudioFadeParam(void *hThread, void *data) {
	while (1) {
		cAudioFadeParam *pfadeParam = s_fadeParamList;
		while (pfadeParam) {
			cAudioFadeParam *pNext = pfadeParam->m_next;
			pfadeParam->exec();
			pfadeParam = pNext;
		}
        
		pfadeParam = s_fadeParamList;
		while (pfadeParam) {
			cAudioFadeParam *pNext = pfadeParam->m_next;
            
			// デタッチ
			if (pfadeParam->m_pAudio == NULL && pfadeParam->m_pSession == NULL) {
				delete pfadeParam;
				pfadeParam = NULL;
			}
            
			pfadeParam = pNext;
		}
		[NSThread sleepForTimeInterval:0.016]; // sleep
	}
    
	return 0; // 終了
}

// iOSオーディオクラス
CiOSAudio::CiOSAudio()
: m_bActive(false)
, m_soundPath(0)
, m_preLoad(false)
, m_queue(0)
, m_bInit(false)
, m_luaPause(false)
, m_volume(1.0f)
, m_pan(0.0f)
, m_step(STEP_WAIT)
, m_begin(0), m_end(0)
, m_fadeRatio(1.0f)
, m_ASPD(NULL)
, m_interruptionType(CiOSAudioManager::eINTERRUPTION_TYPE_NONE) {
}

CiOSAudio::~CiOSAudio() {
	closeAudio();
}

bool CiOSAudio::openAudio(const char *path, CiOSPlatform *platform) {
	closeAudio(); // 既に開いている場合は一旦閉じる
    
	m_platform = platform;
	CiOSPathConv& pathconv = CiOSPathConv::getInstance();
	m_soundPath = pathconv.fullpath(path, ".mp3");
	m_nowPlayTime = 0;
	m_startPackNum = 0;
	m_step = STEP_WAIT;
	m_buf_level = 1;
	m_last_delta = 0;
	m_fadeRatio = 1.0f;
	m_volume = 1.0f;
	m_luaPause = false;
    
	// fullpath が出来ている。
	m_bActive = (m_soundPath) ? true : false;
	float rad = M_PI / 4.0f;
	m_panL = sin(rad);
	m_panR = cos(rad);
	m_bInit = false;
    
	if (m_bActive) {
		// サウンドデータ解析
		if (GetSoundAnalysisData(m_soundPath, &m_soundAnalysisData)) {
		}
	}
    
	return m_bActive;
}

bool CiOSAudio::loadMem() {
	if (!m_bActive) return false;
	if (m_preLoad) return true; // 2012.12.06 同じ処理を複数回しないように追加
	m_preLoad = true;
    
	// SEとしてメモリ上にロードしておく
	initSE();
	return true;
}

void CiOSAudio::play(s32 _msec, float _tgtVol, float _startVolume) {
	if (!m_bActive) return;
    
	// 一時停止中は再生再開
	if (m_step == STEP_PAUSE) {
		resume(_msec, _tgtVol);
		return;
	}
    
	// SEの場合
	if (m_preLoad) {
		playSE(_msec, _tgtVol, _startVolume);
		return;
	}
    
	// ここはなにやってるの？
	/*
     if(m_step == STEP_PAUSE) {
     m_nowPlayTime = 0;
     m_startPackNum = 0;
     resume(_msec, _tgtVol);
     return true;
     }
	 */
    
	if (m_step != STEP_WAIT) return;
    
	if (!m_bInit) {
		// BGMとして設定されている場合
		initBGM();  // ロードして再生準備
		m_bInit = true;
		m_last_delta = 0;
	}
	m_nowPlayTime = 0;
	m_startPackNum = 0;
	m_pauseTime = 0;
	m_fadeRatio = _startVolume;
	playBGM();  // 再生を開始する
	if (_msec > 0 && (_tgtVol != _startVolume)) {
		cAudioFadeParam::SetFadeParam(this, NULL, cAudioFadeParam::FADE_TYPE_PLAY, _tgtVol, _msec, _startVolume);
	}
	OSStatus err = AudioQueueStart(m_queue, 0);
	/*
     if( err != kAudioSessionNoError )
     {
     CiOSAudioManager::GetInstance().AudioSessionInit();
     while( AudioQueueStart(m_queue, 0) != kAudioSessionNoError ) {
     CiOSAudioManager::GetInstance().AudioSessionInit();
     }
     }
	 */
    
	m_step = STEP_PLAY;
	return;
}

void CiOSAudio::updateVolume() {
	if (m_preLoad) {
		// SEの場合
		float rad = (1.0f - m_pan) * M_PI / 4.0f;
		m_panL = sin(rad);
		m_panR = cos(rad);
		CiOSAudioSession *pSession = m_begin;
		while (pSession) {
			CiOSAudioSession *next = pSession->m_next;
			pSession->m_volume = m_volume;          // seボリューム設定
			pSession->setFadeRatio(m_fadeRatio);    // フェード係数設定
			pSession = next;
		}
	}
	else {
		// BGMの場合
		OSStatus err = noErr;
		float master = m_platform->getMasterVolume(false);
		AudioQueueParameterValue vol = (AudioQueueParameterValue)(m_volume * master * m_fadeRatio);
		// volが1.0より大きい場合にAudioQueueSetParameterで音量を設定したときにアサーションが起きてしまう、
		// そもそも音量は1.0以上大きくなっても音量が1.0より大きくなる訳ではないので丸めてしまう。
		if (vol > 1.0f) {
			vol  = 1.0f;
		}
		if (m_queue) {
			err = AudioQueueSetParameter(m_queue, kAudioQueueParam_Volume, vol);
			klb_assert(!err, "Sound volume error.");
            
			// BGMの場合
			err = noErr;
			AudioQueueParameterValue vpan = (AudioQueueParameterValue)m_pan;
			err = AudioQueueSetParameter(m_queue, kAudioQueueParam_Pan, vpan);
			klb_assert(!err, "Sound pan error. err code[%d]", (int)err);
		}
	}
}

void CiOSAudio::checkSessionStoped() {
	CiOSAudioSession *pSession = m_begin;
	bool bEnd = true;
	while (pSession) {
		CiOSAudioSession *next = pSession->m_next;
		if (pSession->isPlaying() == true) {
			bEnd = false;
			break;
		}
		pSession = next;
	}
	if (bEnd) {
		m_nowPlayTime = 0;
		m_pauseTime = 0;
		m_step = STEP_WAIT;
	}
}

/*!
 @brief  再生終了のSEを削除
 */
void CiOSAudio::audioSessionCleanup() {
	// SEの終了を監視し終わっている物は削除
	cleanup();
}

void CiOSAudio::setVolume(float volume) {
	m_volume = volume;
	updateVolume();
}

void CiOSAudio::setPan(float pan) {
	m_pan = pan;
	updateVolume();
}

void CiOSAudio::cleanup() {
	CiOSAudioSession *pSession = m_begin;
	while (pSession) {
		CiOSAudioSession *next = pSession->m_next;
		if (!pSession->isPlaying()) {
			cAudioFadeParam::Remove(pSession);
			delete pSession;
		}
		pSession = next;
	}
}

void CiOSAudio::stop(s32 _msec, float _tgtVol) {
	if (!m_bActive) return;
    
	// SEの再生が終了してるものに関しては止める必要も無いので削除
	cleanup();
    
	if (_msec <= 0) {
		// 即時停止
		if (m_preLoad) {
			// SEの停止
			CiOSAudioSession *pSession = m_begin;
			while (pSession) {
				CiOSAudioSession *next = pSession->m_next;
				cAudioFadeParam::Remove(pSession);
				delete pSession;
				pSession = next;
			}
			m_nowPlayTime = 0;
			m_pauseTime = 0;
			m_step = STEP_WAIT;
		}
		else {
			// BGMの停止
			cAudioFadeParam::Remove(this);
			AudioQueueStop(m_queue, true);
			AudioQueueDisposeTimeline(m_queue, m_TlineRef);
			m_nowPlayTime = 0;
			m_startPackNum = 0;
			m_pauseTime = 0;
			m_step = STEP_WAIT;
		}
	}
	else {
		// フェード
		if (m_preLoad) {
			// SEの停止
			CiOSAudioSession *pSession = m_begin;
			while (pSession) {
				CiOSAudioSession *next = pSession->m_next;
				cAudioFadeParam::SetFadeParam(NULL, pSession, cAudioFadeParam::FADE_TYPE_STOP, _tgtVol, _msec, 0.0f);
				pSession = next;
			}
		}
		else {
			// BGMの停止
			cAudioFadeParam::SetFadeParam(this, NULL, cAudioFadeParam::FADE_TYPE_STOP, _tgtVol, _msec, 0.0f);
		}
	}
}

void CiOSAudio::closeAudio() {
	if (!m_bActive) return;
    
	if (m_preLoad) {
		// SEの停止
		// このSEの全セッションを破棄
		CiOSAudioSession *pSession = m_begin;
		while (pSession) {
			CiOSAudioSession *next = pSession->m_next;
			cAudioFadeParam::Remove(pSession);
			delete pSession;
			pSession = next;
		}
		for (int i = 0; i < m_ASBD.mChannelsPerFrame; i++) {
			delete[] m_playBuffer[i];
		}
		delete[] m_playBuffer;
	}
	else {
		// BGMの破棄
		cAudioFadeParam::Remove(this);
		AudioQueueStop(m_queue, true);
		AudioQueueDispose(m_queue, true);
		AudioQueueDisposeTimeline(m_queue, m_TlineRef);
		AudioFileClose(m_audioID);
		m_queue = 0;
	}
	// open前に戻す
	m_bActive = false;
	m_preLoad = false;
	m_bInit = false;
	if (m_soundPath) {
		delete[] m_soundPath;
		m_soundPath = 0;
	}
	if (m_ASPD) {
		delete[] m_ASPD;
		m_ASPD = NULL;
	}
    
	m_encFile.release();
}

// SEは同時に複数再生され、どれを止めればよいかわからないため、BGMに対してのみ有効。
void CiOSAudio::pause(s32 _msec, float _tgtVol) {
	if (m_step == STEP_PLAY) {
		if (m_preLoad) {
			// SEの場合現状何をポーズさせるか不明なのでスルー
			CiOSAudioSession *pSession = m_begin;
			while (pSession) {
				CiOSAudioSession *next = pSession->m_next;
				pSession->pause();
				pSession = next;
			}
			m_step = STEP_PAUSE;
		}
		else {
			// BGMのポーズ
			if (_msec <= 0.0f) {
				m_pauseTime = m_startPackNum;
				cAudioFadeParam::Remove(this);
                
				//AudioQueuePause(m_queue);
				// 停止前に現在の再生時間を取得
				m_nowPlayTime = tell();
				AudioQueueStop(m_queue, true);
                
				m_bSeeked = false;
				m_step = STEP_PAUSE;
#ifdef DEBUG_AUDIO
				CiOSPlatform::getInstance()->logging("[Audio] pause Audio!");
#endif
			}
			else {
				cAudioFadeParam::SetFadeParam(this, NULL, cAudioFadeParam::FADE_TYPE_PAUSE, _tgtVol, _msec, 1.0f /*_startVolume*/);
			}
		}
	}
}

void CiOSAudio::resume(s32 _msec, float _tgtVol) {
	if (m_step == STEP_PAUSE) {
		if (m_preLoad) {
			// SEの場合ポーズが現状できないので一時停止解除もスルー
			CiOSAudioSession *pSession = m_begin;
			while (pSession) {
				CiOSAudioSession *next = pSession->m_next;
				pSession->resume();
				pSession = next;
			}
			m_step = STEP_PLAY;
		}
		else {
			// BGMの一時停止解除
            /*
             AudioQueueStop(m_queue, false);
             m_startPackNum = m_pauseTime;
             m_nowPlayTime = (s32)(m_startPackNum * m_ASBD.mFramesPerPacket * (UInt64)1000 / m_ASBD.mSampleRate);
             */
			uint64_t tval = mach_absolute_time();
			mach_timebase_info_data_t base;
			mach_timebase_info(&base);
			uint64_t now_time = (s64)((tval * base.numer) / base.denom);
			m_tval = now_time - m_last_delta;
            
			// 再生再開前に読み出し開始位置を再設定して初期バッファ再度読み込み
			m_startPackNum = m_nowPlayTime * m_ASBD.mSampleRate / (m_ASBD.mFramesPerPacket * 1000);
			for (int i = 0; i < BUF_COUNT; i++) {
				queueCallback(this, m_queue, m_qBuf[i]);
			}
			AudioQueueStart(m_queue, 0);
            
#ifdef DEBUG_AUDIO
			CiOSPlatform::getInstance()->logging("[Audio] resume Audio!");
#endif
			/*
             if( err != kAudioSessionNoError )
             {
             CiOSAudioManager::GetInstance().AudioSessionInit();
             while( AudioQueueStart(m_queue, 0) != kAudioSessionNoError ) {
             CiOSAudioManager::GetInstance().AudioSessionInit();
             }
             }
			 */
			if (_msec > 0.0f) {
				cAudioFadeParam::SetFadeParam(this, NULL, cAudioFadeParam::FADE_TYPE_RESUME, _tgtVol, _msec, 0.0f /*_startVolume*/);
			}
			m_step = STEP_PLAY;
		}
	}
}

void CiOSAudio::seek(s32 millisec) {
	// if(!m_bInit) return;
	UInt64 milli = millisec;
	if (!m_bInit) {
		play();
		pause();
	}
	if (m_step == STEP_PLAY) {
		AudioQueuePause(m_queue);
	}
    
	AudioQueueFlush(m_queue);
	m_startPackNum = milli * m_ASBD.mSampleRate / (m_ASBD.mFramesPerPacket * 1000);
	m_nowPlayTime = (s32)(m_startPackNum * m_ASBD.mFramesPerPacket * (UInt64)1000 / m_ASBD.mSampleRate);
    
	if (!m_bSeeked) {
		AudioQueueStop(m_queue, 0);
		m_bSeeked = true;
	}
	if (m_step == STEP_PLAY) {
		AudioQueueStart(m_queue, 0);
		m_bSeeked = false;
	}
}

s32 CiOSAudio::tell() {
	if (m_step == STEP_WAIT || m_step == STEP_PAUSE) {
		return m_nowPlayTime;
        //        return 0;
	}
	AudioTimeStamp outTime;
	AudioQueueGetCurrentTime(m_queue, m_TlineRef, &outTime, 0);
	s32 playtime = outTime.mSampleTime * 1000 / m_ASBD.mSampleRate;
	if (playtime < 0) {
		playtime = 0;
	}
	return m_nowPlayTime + playtime;
	/*
     if(m_step == STEP_PLAY) {
     uint64_t tval = mach_absolute_time();
     mach_timebase_info_data_t base;
     mach_timebase_info(&base);
     uint64_t delta = (s64)((tval * base.numer) / base.denom) - m_tval;
     m_last_delta = (delta / 1000000);
     }
     return m_nowPlayTime + m_last_delta;
	 */
}

s32 CiOSAudio::totalPlayTime() {
	return m_soundAnalysisData.m_totalTime;
}

void CiOSAudio::setFadeParam(float _tgtVol, u32 _msec) {
	if (m_preLoad) {
		cleanup(); // SE再生してない物は破棄
		CiOSAudioSession *pSession = m_begin;
		while (pSession) {
			CiOSAudioSession *next = pSession->m_next;
			cAudioFadeParam::SetFadeParam(NULL, pSession, cAudioFadeParam::FADE_TYPE_PLAYING, _tgtVol, _msec);
			pSession = next;
		}
	}
	else {
		if (m_step == STEP_PLAY) {
			cAudioFadeParam::SetFadeParam(this, NULL, cAudioFadeParam::FADE_TYPE_PLAYING, _tgtVol, _msec);
		}
	}
}

void CiOSAudio::setFadeRatio(float _fadeRatio) {
	m_fadeRatio = _fadeRatio;
	updateVolume();
}

s32 CiOSAudio::getState() {
	s32 state = IClientRequest::E_SOUND_STATE_INVALID_HANDLE;
	switch (m_step) {
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

AudioFileMemory::AudioFileMemory()
: m_decrypter()
, m_decryptBuffer(NULL)
, m_dataLength(0) {
}

bool AudioFileMemory::loadFile(const char *url) {
	//
	// Open File, Get Size and setup decryption.
	//
	bool res    = false;
	m_decryptBuffer = NULL;
	FILE *pFile = fopen(url, "rb");
	if (pFile) {
		u8 hdr[4];
		fread(hdr, 1, 4, pFile);
        
		u32 hasHeader = decryptSetup((u8 *)url, hdr);
        
		// get Size
		fseek(pFile, 0, SEEK_END);
		m_dataLength = ftell(pFile) - (hasHeader * 4);
		fseek(pFile, (hasHeader * 4), SEEK_SET);
        
		// Alloc buffer
		m_decryptBuffer = new u8[m_dataLength];
        
		if (m_decryptBuffer) {
			//
			// Read & Decrypt
			//
			u32 count = fread(m_decryptBuffer, 1, m_dataLength, pFile);
			decrypt(m_decryptBuffer, count);
			res = true;
		}
        
		// Complete
		fclose(pFile);
	}
    
	if ((res == false) && m_decryptBuffer) {
		release();
	}
	return res;
}

void AudioFileMemory::release() {
	delete m_decryptBuffer;
	m_decryptBuffer = NULL;
}

OSStatus AudioFileReadProc(void *inClientData, SInt64 inPosition, UInt32 requestCount, void *buffer, UInt32 *actualCount) {
	// check parameters
	if (!inClientData || !buffer || !actualCount) {
		return EINVAL;
	}
    
	AudioFileMemory *audioFileMemory = (AudioFileMemory *)inClientData;
    
	// [OPTION] Use FILE* and use fread instead of preload.
    
	// make sure position is within bounds
	if (inPosition < 0 || inPosition >= audioFileMemory->m_dataLength) {
		*actualCount = 0;
		return noErr;
	}
    
	// see if we need to cap requested length
	*actualCount = requestCount;
	SInt64 endPosition = inPosition + requestCount;
	if (endPosition >= audioFileMemory->m_dataLength) {
		*actualCount = requestCount - (endPosition - audioFileMemory->m_dataLength);
	}
    
	memcpy(buffer, audioFileMemory->m_decryptBuffer + inPosition, *actualCount);
	// [OPTION] Can decrypt here instead of preload.
	// --> Need to recompute the decrypt key for given position.
	return noErr;
}

SInt64 AudioFileGetSizeProc(void *inClientData) {
	if (!inClientData) {
		return EINVAL;
	}
    
	AudioFileMemory *audioFileMemory = (AudioFileMemory *)inClientData;
	return audioFileMemory->m_dataLength;
}

AudioFileTypeID GetAudioFileTypeId(CFURLRef inFileURL) {
	return kAudioFileMP3Type;
}

void CiOSAudio::initBGM() {
	if (m_bActive) {
		OSStatus err = noErr;
		m_encFile.loadFile(m_soundPath);
		err = AudioFileOpenWithCallbacks(&m_encFile,
		                                 AudioFileReadProc,
		                                 NULL,  // Write
		                                 AudioFileGetSizeProc,
		                                 NULL,  // Set Size
		                                 kAudioFileMP3Type, &m_audioID
		                                 );
        
		if (!err) {
			UInt32 size = sizeof(m_ASBD);
			err = AudioFileGetProperty(m_audioID, kAudioFilePropertyDataFormat, &size, &m_ASBD);
			klb_assert(!err && m_ASBD.mFormatID == kAudioFormatMPEGLayer3, "format not support.");
		}
	}
}

void CiOSAudio::playBGM() {
	// BGMとしてロードされている場合
	// 実態としてはアクセス用のパスを作ったところで終わっているので、
	// そのパスの音声を再生するAVAudioPlayerクラスを作成する。
	OSStatus err = noErr;
	err = AudioQueueNewOutput(&m_ASBD, CiOSAudio::queueCallback, this, CFRunLoopGetCurrent(), kCFRunLoopCommonModes, 0, &m_queue);
    
	float master = m_platform->getMasterVolume(false);
	AudioQueueParameterValue vol = (AudioQueueParameterValue)(master * m_volume * m_fadeRatio);
	err = AudioQueueSetParameter(m_queue, kAudioQueueParam_Volume, vol);
    
	UInt32 size = sizeof(m_maxPacketSize);
	err = AudioFileGetProperty(m_audioID, kAudioFilePropertyPacketSizeUpperBound, &size, &m_maxPacketSize);
    
	// m_numPacketPerTime = m_ASBD.mSampleRate / (m_ASBD.mFramesPerPacket * 12);
    
	// できるだけ高い精度で再生時刻を取得するため、m_numPacketPerTime を強制的に 1 として扱う
	// 1パケット中に含まれるPCMフレーム数は m_ASBD.mFramesPerPacket にあり、1パケットあたりの経過時間の累計で
	// 現在時刻を算出できる。
	switch (m_buf_level) {
		case 0:
			m_numPacketPerTime = 1;
			break;
            
		case 1:
			m_numPacketPerTime = m_ASBD.mFramesPerPacket;
			break;
            
		case 2:
			m_numPacketPerTime = m_ASBD.mFramesPerPacket * 2;
			break;
            
		default:
			break;
	}
	// m_numPacketPerTime = 1;
    
	AudioQueueCreateTimeline(m_queue, &m_TlineRef);
    
	if (m_ASPD) {
		delete[] m_ASPD;
	}
	m_ASPD = new AudioStreamPacketDescription[(int)m_numPacketPerTime];
	UInt32 bufSize = m_numPacketPerTime * m_maxPacketSize;
    
	for (int i = 0; i < 3; i++) {
		err = AudioQueueAllocateBuffer(m_queue, bufSize, &(m_qBuf[i]));
		if (err) {
			klb_assert(!err, "queue allocation error.");
		}
		queueCallback(this, m_queue, m_qBuf[i]);
	}
    
	// 音量更新
	updateVolume();
}

void CiOSAudio::initSE() {
	if (!m_bActive) return;
    
	NSString *nspath = [NSString stringWithUTF8String:m_soundPath];
	m_soundURL = [NSURL fileURLWithPath:nspath];
	OSStatus err = noErr;
    
	// Old code : err = ExtAudioFileOpenURL((CFURLRef)m_soundURL, &m_extAudioID);
	m_encFile.loadFile(m_soundPath);
	err = AudioFileOpenWithCallbacks(&m_encFile,
	                                 AudioFileReadProc,
	                                 NULL,  // Write
	                                 AudioFileGetSizeProc,
	                                 NULL,  // Set Size
	                                 kAudioFileMP3Type, &m_audioID
	                                 );
    
	klb_assert(err == noErr, "could not open SE file.");
    
	err = ExtAudioFileWrapAudioFileID(
                                      m_audioID,
                                      false,
                                      &m_extAudioID
                                      );
    
	klb_assert(err == noErr, "could not open SE file.");
    
	UInt32 size = sizeof(m_ASBD);
	err = ExtAudioFileGetProperty(m_extAudioID, kExtAudioFileProperty_FileDataFormat, &size, &m_ASBD);
	klb_assert(err == noErr && m_ASBD.mFormatID == kAudioFormatMPEGLayer3, "format not support.");
	//m_volume = 1.0f;
    
	//m_clientFormat.mSampleRate        = 44100.0;
	m_clientFormat.mSampleRate        = m_ASBD.mSampleRate;     // 2012/12/04 サンプリングレートが固定値で44100で入力されていたのが間違い、これだとサンプリングレートが44100以外の音声が途切れたりしてしまう。
	m_clientFormat.mFormatID          = kAudioFormatLinearPCM;
	m_clientFormat.mFormatFlags       = kAudioFormatFlagsAudioUnitCanonical;
	m_clientFormat.mChannelsPerFrame  = m_ASBD.mChannelsPerFrame;
	m_clientFormat.mBytesPerFrame     = sizeof(AudioUnitSampleType);
	m_clientFormat.mBytesPerPacket    = sizeof(AudioUnitSampleType);
	m_clientFormat.mFramesPerPacket   = 1;
	m_clientFormat.mBitsPerChannel    = 8 * sizeof(AudioUnitSampleType);
	m_clientFormat.mReserved          = 0;
    
	// フォーマットの取得
	err = ExtAudioFileSetProperty(m_extAudioID, kExtAudioFileProperty_ClientDataFormat, sizeof(AudioStreamBasicDescription), &m_clientFormat);
	klb_assert(!err, "could not open SE file.");
    
	// バッファサイズの取得
	size = sizeof(SInt64);
	err = ExtAudioFileGetProperty(m_extAudioID, kExtAudioFileProperty_FileLengthFrames, &size, &m_totalFrames);
	klb_assert(!err, "could not open SE file.");
    
	// バッファの確保等
	m_playBuffer = new AudioUnitSampleType * [m_ASBD.mChannelsPerFrame];
	for (int i = 0; i < m_ASBD.mChannelsPerFrame; i++) {
		m_playBuffer[i] = new AudioUnitSampleType[m_totalFrames];
	}
    
	AudioBufferList *bufList = (AudioBufferList *)malloc(sizeof(AudioBufferList) + sizeof(AudioBuffer) * (m_ASBD.mChannelsPerFrame - 1));
	bufList->mNumberBuffers = m_ASBD.mChannelsPerFrame;
	for (int i = 0; i < m_ASBD.mChannelsPerFrame; i++) {
		bufList->mBuffers[i].mNumberChannels = 1;
		bufList->mBuffers[i].mDataByteSize = sizeof(AudioUnitSampleType) * m_totalFrames;
		bufList->mBuffers[i].mData = m_playBuffer[i];
	}
    
	UInt32 readFrameSize = m_totalFrames;
	err = ExtAudioFileRead(m_extAudioID, &readFrameSize, bufList);
	klb_assert(!err, "could not open SE file.");
    
	ExtAudioFileDispose(m_extAudioID);
	free(bufList);
    
	/*
     m_isDone = false;
     AudioComponentDescription cd;
     cd.componentType            = kAudioUnitType_Output;
     cd.componentSubType         = kAudioUnitSubType_RemoteIO;
     cd.componentManufacturer    = kAudioUnitManufacturer_Apple;
     cd.componentFlags           = 0;
     cd.componentFlagsMask       = 0;
     AudioComponent component = AudioComponentFindNext(0, &cd);
     AudioComponentInstanceNew(component, &m_audioUnit);
     AudioUnitInitialize(m_audioUnit);
     
     
     AURenderCallbackStruct callbackStruct;
     callbackStruct.inputProc = CiOSAudio::renderCallback;
     callbackStruct.inputProcRefCon = this;
     
     AudioUnitSetProperty(m_audioUnit,
     kAudioUnitProperty_SetRenderCallback,
     kAudioUnitScope_Input,
     0,
     &callbackStruct,
     sizeof(AURenderCallbackStruct));
     
     AudioUnitSetProperty(m_audioUnit,
     kAudioUnitProperty_StreamFormat,
     kAudioUnitScope_Input,
     0,
     &m_clientFormat,
     sizeof(AudioStreamBasicDescription));
	 */
}

void CiOSAudio::playSE(s32 _msec, float _tgtVol, float _startVolume) {
	cleanup();  // 既に再生が終了しているSEセッションを破棄する
	CiOSAudioSession *pSession = new CiOSAudioSession(this);
	if (_msec > 0 && (_tgtVol != _startVolume)) {
		cAudioFadeParam::SetFadeParam(NULL, pSession, cAudioFadeParam::FADE_TYPE_PLAY, _tgtVol, _msec, _startVolume);
	}
	m_step = STEP_PLAY;
	m_fadeRatio = _startVolume;
	updateVolume();
	pSession->play();
}

void CiOSAudio::sendQueue(AudioQueueRef inAQ, AudioQueueBufferRef inBuffer) {
	OSStatus err = noErr;
	float master = m_platform->getMasterVolume(false);
	AudioQueueParameterValue vol = (AudioQueueParameterValue)(master * m_volume * m_fadeRatio);
	err = AudioQueueSetParameter(inAQ, kAudioQueueParam_Volume, vol);
    
	// NSLog(@"sendQueue(%d)", (int)m_startPackNum);
	UInt32 numBytes = 0;
	UInt32 numPackets = m_numPacketPerTime;
	err = AudioFileReadPackets(m_audioID, NO, &numBytes, m_ASPD, m_startPackNum, &numPackets, inBuffer->mAudioData);
	// klb_assert(numBytes > 0, "no audio data.");
    
	if (numPackets <= 0) {
		// ループ処理
		numBytes = 0;
		numPackets = m_numPacketPerTime;
		m_startPackNum = 0;
        
		err = AudioFileReadPackets(m_audioID, NO, &numBytes, m_ASPD, m_startPackNum, &numPackets, inBuffer->mAudioData);
	}
	inBuffer->mAudioDataByteSize = numBytes;
	err = AudioQueueEnqueueBuffer(inAQ, inBuffer, numPackets, m_ASPD);
	// klb_assert(err != noErr, "error: AudioQueueDataByteSize");
    
	// 現在時刻を算出し、保管しておく。
    
	//m_nowPlayTime = (s32)(m_startPackNum * m_ASBD.mFramesPerPacket * (UInt64)1000 / m_ASBD.mSampleRate);
	m_startPackNum += numPackets;
    
	/*
     uint64_t tval = mach_absolute_time();
     mach_timebase_info_data_t base;
     mach_timebase_info(&base);
     
     m_tval = (s64)((tval * base.numer) / base.denom);
     m_last_delta = 0;
	 */
}

void CiOSAudio::queueCallback(void *inUserData,
                              AudioQueueRef inAQ, AudioQueueBufferRef inBuffer) {
	CiOSAudio *pAudio = (CiOSAudio *)inUserData;
	pAudio->sendQueue(inAQ, inBuffer);
}

// 個々の発音セッションクラス
CiOSAudioSession::CiOSAudioSession(CiOSAudio *audio)
: m_audio(audio)
, m_prev(0)
, m_next(0)
, m_isPause(false) {
	// 自身を指定されたデータの親クラスに登録する
	m_prev = m_audio->m_end;
	if (m_prev) {
		m_prev->m_next = this;
	}
	else {
		m_audio->m_begin = this;
	}
	m_audio->m_end = this;
    
	init();
}

CiOSAudioSession::~CiOSAudioSession() {
	m_isDone = true;
	m_isPlaying = false;
	cAudioFadeParam::Remove(this);
	AudioOutputUnitStop(m_audioUnit);
	AudioUnitUninitialize(m_audioUnit);
	AudioComponentInstanceDispose(m_audioUnit);
    
	// 自身を親から削除する
	if (m_prev) {
		m_prev->m_next = m_next;
	}
	else {
		m_audio->m_begin = m_next;
	}
	if (m_next) {
		m_next->m_prev = m_prev;
	}
	else {
		m_audio->m_end = m_prev;
	}
}

void CiOSAudioSession::init() {
	m_currentFrame = 0;
	m_isDone = false;
	m_isPlaying = false;
	m_isPause = false;
    
	m_volume = m_audio->m_volume;
	m_panL = m_audio->m_panL;
	m_panR = m_audio->m_panR;
    
	m_fadeRatio = 1.0f;
    
	AudioComponentDescription cd;
	cd.componentType            = kAudioUnitType_Output;
	cd.componentManufacturer    = kAudioUnitManufacturer_Apple;
	cd.componentFlags           = 0;
	cd.componentFlagsMask       = 0;
	AudioComponent component = AudioComponentFindNext(0, &cd);
	AudioComponentInstanceNew(component, &m_audioUnit);
	AudioUnitInitialize(m_audioUnit);
    
    
	AURenderCallbackStruct callbackStruct;
	callbackStruct.inputProc = CiOSAudioSession::renderCallback;
	callbackStruct.inputProcRefCon = this;
    
	AudioUnitSetProperty(m_audioUnit,
	                     kAudioUnitProperty_SetRenderCallback,
	                     kAudioUnitScope_Input,
	                     0,
	                     &callbackStruct,
	                     sizeof(AURenderCallbackStruct));
    
	AudioUnitSetProperty(m_audioUnit,
	                     kAudioUnitProperty_StreamFormat,
	                     kAudioUnitScope_Input,
	                     0,
	                     &m_audio->m_clientFormat,
	                     sizeof(AudioStreamBasicDescription));
    
	AudioOutputUnitStart(m_audioUnit);
}

void CiOSAudioSession::play() {
	m_isDone = false;
	m_currentFrame = 0;
	m_isPlaying = true;
}

void CiOSAudioSession::stop() {
	//AudioOutputUnitStop(m_audioUnit);
	m_isDone = true;
	m_isPlaying = false;
	cAudioFadeParam::Remove(this);
}

void CiOSAudioSession::pause() {
	//m_isDone = true;
	m_isPause = true;
	cAudioFadeParam::Remove(this);
	//m_isPlaying = false;
}

void CiOSAudioSession::resume() {
	//m_isPlaying = true;
	m_isPause = false;
}

s64 CiOSAudioSession::tell() {
	s64 ret = 0;
    
	if (m_currentFrame != 0) {
		ret = (m_currentFrame * 1000) / m_audio->m_clientFormat.mSampleRate;
	}
	return ret;
}

void CiOSAudioSession::checkSessionStoped() {
	if (m_audio) {
		m_audio->checkSessionStoped();
	}
}

void CiOSAudioSession::setFadeRatio(float _fadeRatio) {
	m_fadeRatio = _fadeRatio;
}

OSStatus CiOSAudioSession::callbackSE(AudioUnitRenderActionFlags *ioActionFlags,
                                      const AudioTimeStamp *      inTimeStamp,
                                      UInt32                      inBusNumber,
                                      UInt32                      inNumberFrames,
                                      AudioBufferList *           ioData) {
	int indexR = (m_audio->m_ASBD.mChannelsPerFrame == 2) ? 1 : 0;
	AudioUnitSampleType *outL = (AudioUnitSampleType *)ioData->mBuffers[0].mData;
	AudioUnitSampleType *outR = (AudioUnitSampleType *)ioData->mBuffers[indexR].mData;
    
	// ポーズ中or末尾まで再生終了してる時はバッファに0を書き込み
	if (m_isDone || m_isPause) {
		for (int i = 0; i < inNumberFrames; i++) {
			*outL++ = *outR++ = 0;
		}
		return noErr;
	}
	// 左右の音量にかける係数を求める。
	// 設定されているボリュームと、パン位置によって決まる。
	// 使われるボリューム/パンの値は、セッションの再生開始時の値であり、その後変更されても影響を受けない。
	float master = m_audio->m_platform->getMasterVolume(true);    // マスターボリュームを取得
	float nL = master * m_volume * m_panL * m_fadeRatio;
	float nR = master * m_volume * m_panR * m_fadeRatio;
    
	// 丸め
	if (nL > 1.0f) {
		nL = 1.0f;
	}
	if (nR > 1.0f) {
		nR = 1.0f;
	}
    
	UInt32 left = (m_isDone) ? 0 : (m_audio->m_totalFrames - m_currentFrame);
	UInt32 fnum = (left > inNumberFrames) ? inNumberFrames : left;
	UInt32 right = inNumberFrames - fnum;
    
	for (int i = 0; i < fnum; i++) {
		*outL++ = nL * m_audio->m_playBuffer[0][m_currentFrame];
		*outR++ = nR * m_audio->m_playBuffer[indexR][m_currentFrame++];
	}
	for (int i = 0; i < right; i++) {
		*outL++ = *outR++ = 0;
	}
	if (m_currentFrame == m_audio->m_totalFrames ||
	    tell() >= m_audio->m_soundAnalysisData.m_totalTime) {
		m_isDone = true;
		m_isPlaying = false;
		cAudioFadeParam::Remove(this);
		checkSessionStoped();
	}
	return noErr;
}

OSStatus CiOSAudioSession::renderCallback(void *                      inRefCon,
                                          AudioUnitRenderActionFlags *ioActionFlags,
                                          const AudioTimeStamp *      inTimeStamp,
                                          UInt32                      inBusNumber,
                                          UInt32                      inNumberFrames,
                                          AudioBufferList *           ioData) {
	CiOSAudioSession *audio = (CiOSAudioSession *)inRefCon;
	return audio->callbackSE(ioActionFlags, inTimeStamp, inBusNumber, inNumberFrames, ioData);
}
