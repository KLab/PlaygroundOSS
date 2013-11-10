#ifndef CiOSAudio_h
#define CiOSAudio_h


#import <GLKit/GLKit.h>
#import <mach/time_value.h>
#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AudioToolbox/ExtendedAudioFile.h>
#import <AudioToolbox/AudioFile.h>
#include "CSoundAnalysis.h"
#include "encryptFile.h"

class CiOSPlatform;
class CiOSAudio;
class CiOSAudioSession;


class cAudioFadeParam
{
	friend class CiOSAudio;
	friend class CiOSAudioSession;
public:
	cAudioFadeParam();
	virtual ~cAudioFadeParam();
    
	void attach();
	void detach();
	void exec();
	bool setFadeParam(s16 _fadeType, float _tgtVol, u32 _msec, s16 _interType = INTER_TYPE_LINEAR, float _startVolume = 1.0f);
    
	static void AudioFadeParamInit();
	static void AudioFadeParamExit();
	static void SetFadeParam(CiOSAudio *_audio, CiOSAudioSession *_settion, s16 _fadeType, float _tgtVol, u32 _msec, s16 _interType = INTER_TYPE_LINEAR, float _startVolume = 0.0f);
	static void Remove(void *_audio);
	static s32 ThreadAudioFadeParam(void *hThread, void *data);
    
public:
	// フェード関係のパラメータ
	enum FADE_TYPE {
		FADE_TYPE_NONE = 0,
		FADE_TYPE_PLAY,         //!< fade in
		FADE_TYPE_STOP,         //!< fade out
		FADE_TYPE_PAUSE,        //!< fade out
		FADE_TYPE_RESUME,       //!< fade in
		FADE_TYPE_PLAYING,      //!< fade
        
		FADE_TYPE_NUM,
	};
    
	enum INTER_TYPE {
		INTER_TYPE_NONE = 0,
		INTER_TYPE_LINEAR,         //!< Linear
        
		INTER_TYPE_NUM,
	};
    
private:
	s32 m_fadeCnt;                          //!< フェードカウント(ミリ秒)
	float m_startVol;                       //!< フェード開始のボリューム値(0.0f~1.0f)
	float m_endVol;                         //!< フェード終了のボリューム値(0.0f~1.0f)
	float m_fadeRatio;                      //!< フェード割合(0.0f〜1.0f)
	s32 m_fadeMiliSec;                      //!< フェードに要する時間(ミリ秒)
	s16 m_nowFadeInterType;                 //!< 現在のフェード補間タイプ
	s16 m_nowFadeType;                      //!< 現在のフェードタイプ
	bool m_bfade;                           //!< フェード中？
	s64 m_prevmseq;                         //!< 前回の再生時間
    
	CiOSAudio *m_pAudio;                    //!< 対象者
	CiOSAudioSession *m_pSession;           //!< 対象者
    
	cAudioFadeParam *m_prev;    //!< 前のフェードパラメータ
	cAudioFadeParam *m_next;    //!< 次のフェードパラメータ
    
	static cAudioFadeParam *s_fadeParamList;
	static void *s_fadeParamThread;
};

class CiOSAudioSession
{
	friend class CiOSAudio;
private:
	CiOSAudioSession(CiOSAudio * pAudio);
	virtual ~CiOSAudioSession();
    
	void init();
    
public:
	void play();
	void stop();
	void pause();
	void resume();
	s64 tell();
	void checkSessionStoped();
    
	inline bool isPlaying() {
		return m_isPlaying;
	}
    
	inline bool isPause() {
		return m_isPause;
	}
    
	inline float getFadeRatio(void) {
		return m_fadeRatio;
	}
    
	void setFadeRatio(float _fadeRatio);
    
private:
	CiOSAudioSession *m_prev;
	CiOSAudioSession *m_next;
    
	CiOSAudio *m_audio;
	AudioUnit m_audioUnit;
    
	SInt64 m_currentFrame;              //!< 現在の再生フレーム
	bool m_isDone;                      //!< 再生終了？
	bool m_isPlaying;                   //!< 再生中？
	bool m_isPause;                     //!< pause中？
    
	float m_volume;                     //!< ボリューム(0.0f~1.0f)
	float m_panL;                       //!< 左ボリューム
	float m_panR;                       //!< 右ボリューム
    
	float m_fadeRatio;
    
	OSStatus callbackSE(AudioUnitRenderActionFlags *ioActionFlags,
	                    const AudioTimeStamp *      inTimeStamp,
	                    UInt32                      inBusNumber,
	                    UInt32                      inNumberFrames,
	                    AudioBufferList *           ioData);
    
	static OSStatus renderCallback(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags,
	                               const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames, AudioBufferList *ioData);
};

class AudioFileMemory
{
public:
	AudioFileMemory();
	~AudioFileMemory()
	{
	}
    
public:
	u8 *m_decryptBuffer;
	u32 m_dataLength;
    
public:
	bool loadFile(const char *url);
	void release();
    
private:
	CDecryptBaseClass m_decrypter;
	inline void decrypt(void *ptr, u32 length) {
		m_decrypter.decryptBlck(ptr, length);
	}
    
	inline u32 decryptSetup(const u8 *ptr, const u8 *hdr) {
		return m_decrypter.decryptSetup(ptr, hdr);
	}
};

class CiOSAudio
{
	friend class CiOSAudioSession;
private:
	typedef struct {
		const char *top;
		const char *phisical;
	} LOCLIST;
	static const LOCLIST m_toplevel[];
    
public:
	CiOSAudio();
	virtual ~CiOSAudio();
    
	bool openAudio(const char *path, CiOSPlatform *platform);
	bool loadMem(); // オンメモリ化
    
	inline void setLuaPause(bool _bLuaPause) {
		m_luaPause = _bLuaPause;
	}
    
	inline bool getLuaPause(void) {
		return m_luaPause;
	}
    
	void play(s32 _msec = 0, float _tgtVol = 1.0f, float _startVol = 1.0f);
	void stop(s32 _msec = 0, float _tgtVol = 0.0f);
	void pause(s32 _msec = 0, float _tgtVol = 0.0f);
	void resume(s32 _msec = 0, float _tgtVol = 1.0f);
	void seek(s32 millisec);
	s32 tell();
	s32 totalPlayTime();
    
	void setFadeParam(float _tgtVol, u32 _msec);
    
	inline float getFadeRatio(void) {
		return m_fadeRatio;
	}
    
	void setFadeRatio(float _fadeRatio);
	s32 getState();
    
	void closeAudio();
    
	void setVolume(float volume);
    
	inline float getVolume() {
		return m_volume;
	}
    
	void setPan(float pan);
    
	inline float getPan() {
		return m_pan;
	}
    
	inline bool isActive() {
		return m_bActive;
	}
    
	inline int getInterruptionType() {
		return m_interruptionType;
	}
    
	inline void setInterruptionType(int _interruptionType) {
		m_interruptionType = _interruptionType;
	}
    
	inline bool setBufSize(int level) {
		if (level < 0 || level > 2) return false;
		m_buf_level = level;
		return true;
	}
    
	void updateVolume();
	void checkSessionStoped();
	void audioSessionCleanup();
    
private:
	enum {
		BUF_COUNT = 3
	};
	enum {
		STEP_WAIT,
		STEP_PLAY,
		STEP_PAUSE
	};
	const char *m_soundPath;
	// char                         *   m_soundFullpath;
	bool m_bActive;
	bool m_preLoad;
	bool m_bInit;
	bool m_bSeeked;
	int m_interruptionType;                                    //!< サウンドの割り込みタイプ
	bool m_luaPause;
    
	int m_buf_level;
	int m_step;
    
	NSURL *m_soundURL;
	AudioFileID m_audioID;
	AudioStreamBasicDescription m_ASBD;
	AudioStreamPacketDescription *m_ASPD;
	AudioQueueRef m_queue;
	AudioQueueBufferRef m_qBuf[BUF_COUNT];
	AudioQueueTimelineRef m_TlineRef;
    
	int m_bufIndex;
    
	UInt64 m_numPacketPerTime;
	UInt32 m_maxPacketSize;
	SInt64 m_startPackNum;
	SInt64 m_pauseTime;
	s32 m_nowPlayTime;                                  // BGMの現在再生時刻
	uint64_t m_tval;
	uint64_t m_last_delta;
    
    
	float m_volume;
	float m_pan;
	float m_panR;
	float m_panL;
    
	float m_fadeRatio;
	sSoundAnalysisData m_soundAnalysisData;
    
	ExtAudioFileRef m_extAudioID;
	AudioStreamBasicDescription m_clientFormat;
	SInt64 m_totalFrames;
    
	AudioUnitSampleType **m_playBuffer;
    
	CiOSAudioSession *m_begin;
	CiOSAudioSession *m_end;
    
	CiOSPlatform *m_platform;
	AudioFileMemory m_encFile;
private:
	void initBGM();
	void playBGM();
	void initSE();
	void playSE(s32 _msec = 0, float _tgtVol = 1.0f, float _startVol = 1.0f);
    
	void cleanup();
    
	void sendQueue(AudioQueueRef inAQ, AudioQueueBufferRef inBuffer);
    
	static void queueCallback(void *inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inBuffer);
};

#endif // CiOSAudio_h
