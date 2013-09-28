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
#ifndef KLBOpenSLAudioPlayer_h
#define KLBOpenSLAudioPlayer_h

#include "CPFInterface.h"
#include "CAndroidRequest.h"
#include "encryptFile.h"
#include "ivorbisfile.h"
#include "KLBPlatformMetrics.h"
#include <pthread.h>
#include <assert.h>
#include <jni.h>
#include <string.h>
#include <math.h>

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include <android/log.h>
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class KLBOpenSLEngine;
class KLBOpenSLSoundAssetLoader;
class KLBOpenSLSoundAsset;
class KLBOpenSLSoundHandle;

class KLBOpenSLEngine
{
public:
    ~KLBOpenSLEngine();

    static KLBOpenSLEngine* getInstance();
	static inline void terminate()
	{
		delete KLBOpenSLEngine::getInstance();
	}
	KLBOpenSLSoundHandle* assignSoundHandle(KLBOpenSLSoundAsset *pAsset);
	void discardCorrespondingSoundHandles(KLBOpenSLSoundAsset *pAsset, bool isLockGained = false);
	s32 tellCorrespondingSoundHandle(KLBOpenSLSoundAsset *pAsset);
	void setFadeParamOnCorrespondingSoundHandles(KLBOpenSLSoundAsset *pAsset, float _tgtVol, u32 _millisec);
	void stopCorrespondingSoundHandles(KLBOpenSLSoundAsset *pAsset, bool isLockGained = false, float _tgtVol=1.0f, u32 _millisec=0);
	void pauseCorrespondingSoundHandles(KLBOpenSLSoundAsset *pAsset, bool isLockGained = false, float _tgtVol=0.0f, u32 _millisec=0);
	void resumeCorrespondingSoundHandles(KLBOpenSLSoundAsset *pAsset, bool isLockGained = false, float _tgtVol=1.0f, u32 _millisec=0);
	s32 getStateOfCorrespondingSoundHandle(KLBOpenSLSoundAsset *pAsset);
	void setMasterVolume(float volume, bool is_se);
	inline float GetSEMasterVolume() {
    	return is_se_off ? 0.0f : master_volume_se;
	}
	inline float GetBGMMasterVolume() {
    	return is_bgm_off ? 0.0f : master_volume_bgm;
	}
	inline float GetMasterVolume(bool is_se) {
		return is_se ? GetSEMasterVolume() : GetBGMMasterVolume();
	}
	inline bool isSoundPaused() { return is_sound_paused; }
	void setVolumeOnCorrespondingSoundHandles(KLBOpenSLSoundAsset *pAsset, float volume, bool isLockGained = false);
	KLBOpenSLSoundAsset* load(const char * path, bool is_se);
	void unload(KLBOpenSLSoundAsset* asset);
	inline void setAudioMultiProcessType(s32 _type) { m_multiProcessType = _type; }
	void chackAudioMasterVolume();

	SLObjectItf outputMixObject;
	SLEngineItf engineEngine;
	static s32 ThreadSoundEngineParam(void * hThread, void * data);
	void registerAssetForRefilling(KLBOpenSLSoundAsset* asset);
	void updateFadeRatio();
	void performRefillOnCurrentAsset();
	void onActivityPause();
	void onActivityResume();
	static const char MAX_SOUND_ASSETS = 32;
	static const char MAX_SOUND_HANDLE = 10;
	// サウンドの割り込みタイプ
	enum eINTERRUPTION_TYPE
	{
		eINTERRUPTION_TYPE_NONE = -1,

		eINTERRUPTION_TYPE_CALLING = 0,		 //!< 電話、Siriなどの割り込み
		eINTERRUPTION_TYPE_RESIGN_ACTIVE,	   //!< ホームボタンダブルタップなどによる非アクティブ状態
		eINTERRUPTION_TYPE_ENTER_BACKGROUND,	//!< ホームボタンなどによるアプリがバックグラウンドにある状態

		eINTERRUPTION_TYPE_MAX
	};

private:
	KLBOpenSLEngine();
	SLObjectItf engineObject;
	IPlatformRequest* platform;
	KLBOpenSLSoundAssetLoader* assetLoader;
	const char *home;
	KLBOpenSLSoundHandle** soundHandles;
	KLBOpenSLSoundAsset** soundAssets;
    void* observingThread;
	float master_volume_bgm;
	float master_volume_se;
	bool is_bgm_off;
	bool is_se_off;
	bool is_sound_paused;
	s32 m_multiProcessType;
	
	pthread_mutex_t cs_mutex;
	pthread_mutex_t asset_refill_mutex;
	KLBOpenSLSoundAsset* asset_waiting_refill;
};

class KLBOpenSLSoundAssetLoader
{
friend class KLBOpenSLEngine;
public:
	virtual ~KLBOpenSLSoundAssetLoader();
	KLBOpenSLSoundAsset* openFile(const char * path, bool isFullBuffered);

private:
	static const unsigned SRC_BUFFER_SIZE = 65536;
	KLBOpenSLSoundAssetLoader();
	void startObservation();
	void stopObservation();
	void fillBuffer(KLBOpenSLSoundAsset* soundAsset);
	void registerAsset(KLBOpenSLSoundAsset *pAsset);
	void unregisterAsset(KLBOpenSLSoundAsset *pAsset);
	static int FileObservationThreadParam(void* hThread, void* data);

	KLBOpenSLSoundAsset** assets;
	AAssetManager* mgr;
	JNIEnv* env;
	char const *home;
	void* observationThread;
};

class KLBOpenSLSoundAsset
{
friend class KLBOpenSLSoundAssetLoader;
public:
	enum REPEAT_MODE {
		ONCE,
		INFINITE_LOOP
	};
	static const int MAX_BUFFER_SAMPLES = 176400;
	static const int DEFAULT_LOAD_SAMPLES = 44100;
	static const int VORBIS_READ_BUFFER = 4096;
	KLBOpenSLSoundAsset(const char* path, bool isFullBuffered);
	virtual ~KLBOpenSLSoundAsset();

	void prepare(int frames);
	inline bool isFullyBuffered() { return src_buf_flags & 0x04; }
	KLBOpenSLSoundHandle* play(REPEAT_MODE = ONCE, s32 _milisec=0, float _tgtVol=1.0f, float _startVol=0.0f);
	void stopAll();
	void fetchNextPcmBuffer(KLBOpenSLSoundHandle* soundHandle);
	inline void readVorbisSamples(int samplesToRead) {
		MEASURE_THREAD_CPU_BEGIN(TASKTYPE_SOUND_DECODE);
		readVorbisSamplesImpl(samplesToRead);
		MEASURE_THREAD_CPU_END(TASKTYPE_SOUND_DECODE);
	}
	void close();
	inline long getSrcFileSize() { return src_file_size; }
	inline const char* getSrcFullPath() { return src_full_path; }
	void seekSrcChunk(unsigned int new_pos);
	int putNextSrcChunk(void *ptraddr, int bytes_to_read);
	inline int getPcmSamplingRate() { return pcm_sampling_rate; }
	inline char getChannels() { return channels; }
	inline int totalPlayTime() { return playtime_ms; }
	inline unsigned int getPcmTotalReadPos() { return pcm_total_read_pos; }
	inline bool isBufferEndReached() { return pcm_total_samples == pcm_total_read_pos && pcm_buffer_read_pos == pcm_buffer_consumed_pos; }
	inline void resetBuffer() {
		pcm_total_read_pos = 0;
		pcm_buffer_read_pos = 0;
		pcm_buffer_consumed_pos = 0;
		ov_raw_seek(vf, 0);
	}
	void closeVorbisFile();
	inline bool isSE() { return is_se; }

	static size_t read_func(void *ptr, size_t size, size_t nmemb, void *datasource);
	static int seek_func(void *datasource, ogg_int64_t offset, int whence);
	static int close_func(void *datasource);
	static long tell_func(void *datasource);

private:
	void readVorbisSamplesImpl(int samplesToRead);
	KLBOpenSLSoundAssetLoader* assetLoader;
	const char* src_path;
	const char* src_full_path;
	long src_file_size;
	char channels;
	int playtime_ms;
	unsigned int src_location;
	// composite flag for buffer status.
	// b00000X000: 1 if initialization done
	// b000000X00: 1 if src file is fully buffered (target is SE or is smaller than buffer size)
	// b0000000X0: 1 if former half of this buffer is filled (no need to refill)
	// b00000000X: 1 if latter half of this buffer is filled (no need to refill)
	char src_buf_flags;
	inline bool isBufferInitialized() { return src_buf_flags & 0x08; }
	inline bool isFormerHalfBufferFilled() { return src_buf_flags & 0x02; }
	inline bool isLatterHalfBufferFilled() { return src_buf_flags & 0x01; }
	short* pcm_samples;
	int pcm_sampling_rate;
	int pcm_buffer_size;
	unsigned int pcm_total_samples;
	unsigned int pcm_total_read_pos;
	unsigned int pcm_buffer_read_pos;
	unsigned int pcm_buffer_consumed_pos;
	FILE* fp;
	CDecryptBaseClass decryptor;
	bool is_se;

	OggVorbis_File* vf;
	ov_callbacks callbacks;
};

class KLBOpenSLSoundHandle
{
friend class KLBOpenSLSoundAsset;
public:
	KLBOpenSLSoundHandle();
	virtual ~KLBOpenSLSoundHandle();

	static void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context);

	void play(int _msec=0, float _tgtVol=1.0f, float _startVol=1.0f);
	void stop(int _msec=0, float _tgtVol=0.0f);
	void pause(int _msec=0, float _tgtVol=0.0f);
	void resume(int _msec=0, float _tgtVol=1.0f);
	void closeAudio(void);
	void setVolume(float volume);
	void refreshVolume();
	void updateVolume();
	s32 tellAudio();
	void fillPcmBuffer(SLAndroidSimpleBufferQueueItf bq, bool is_starting);

	void setSoundAsset(KLBOpenSLSoundAsset *asset);
	inline KLBOpenSLSoundAsset* getSoundAsset() { return asset; }
    bool setFadeParam(s16 _fadeType, float _tgtVol, u32 _msec, s16 _interType=INTER_TYPE_LINEAR, float _startVolume=1.0f);
	void updateFadeParam();
	inline float getVolume() { return volume; }
	void setPan(float pan);
	inline float getPan() { return m_pan; }

	inline bool isActive() { return m_bActive; }
	inline bool isInitiated() { return is_initiated; }
	inline bool isPlaying() { return state == IClientRequest::E_SOUND_STATE_PLAY; }
	inline int getInterruptionType() { return m_interruptionType; }
	inline void setInterruptionType( int _interruptionType ) { m_interruptionType = _interruptionType; }
	inline char getPcmDepth() { return pcm_depth; }
    inline s32 getState() { return state; }
	inline SLuint32 getSlSampleFormat() {
		switch (pcm_depth) {
			case 1: return SL_PCMSAMPLEFORMAT_FIXED_8;
			case 2: return SL_PCMSAMPLEFORMAT_FIXED_16;
			default: return SL_PCMSAMPLEFORMAT_FIXED_16;
		}
	}
	inline SLuint32 getSlChannelMask() {
		switch (pcm_channels) {
			case 1: return SL_SPEAKER_FRONT_CENTER;
			case 2: return SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
			default: return SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT;
		}
	}
	inline char getPcmChannels() { return pcm_channels; }
	inline SLuint32 getSlSamplingRate() {
		switch (pcm_sampling_rate) {
			case   8000: return SL_SAMPLINGRATE_8;
			case  11025: return SL_SAMPLINGRATE_11_025;
			case  12000: return SL_SAMPLINGRATE_12;
			case  16000: return SL_SAMPLINGRATE_16;
			case  22050: return SL_SAMPLINGRATE_22_05;
			case  24000: return SL_SAMPLINGRATE_24;
			case  32000: return SL_SAMPLINGRATE_32;
			case  44100: return SL_SAMPLINGRATE_44_1;
			case  48000: return SL_SAMPLINGRATE_48;
			case  64000: return SL_SAMPLINGRATE_64;
			case  88200: return SL_SAMPLINGRATE_88_2;
			case  96000: return SL_SAMPLINGRATE_96;
			case 192000: return SL_SAMPLINGRATE_192;
			default:     return SL_SAMPLINGRATE_44_1;
		}
	}
	inline s64 getTimeStarted() { return time_started; }

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
	void initInternalResources();
	void destroyOpenSLObjects();
	inline void updateAsset(KLBOpenSLSoundAsset *asset) {
		this->asset = asset;
		this->pcm_depth = 2;
		this->pcm_channels = asset->getChannels();
		this->pcm_sampling_rate = asset->getPcmSamplingRate();
	}
	KLBOpenSLSoundAsset::REPEAT_MODE repeatMode;
	KLBOpenSLSoundAsset* asset;
	SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;
	SLObjectItf bqPlayerObject;
	SLPlayItf bqPlayerPlay;
	SLVolumeItf bqPlayerVol;
    float volume;
    float m_pan;
    bool m_bActive;
    int m_interruptionType;
	s64 time_started;
	s64 time_elapsed;
	inline void updateTimeStarted() { time_started = CAndroidRequest::getInstance()->nanotime(); }
	inline SLmillibel gain_to_attenuation(float volume, SLmillibel max_mbel)
	{
		// using this code snippet. http://www.verious.com/qa/audio-output-level-in-a-form-that-can-be-converted-to-decibel/
		SLmillibel volume_mb;
		if(volume>=1.0f) volume_mb=max_mbel;
		else if(volume<=0.02f) volume_mb=SL_MILLIBEL_MIN;
		else
		{
			volume_mb=M_LN2/log(1.0f/(1.0f-volume))*-1000.0f;
			if(volume_mb>0) volume_mb=SL_MILLIBEL_MIN;
		}
		return volume_mb;
	}
	short* current_head;
	unsigned head_bufsize;
	unsigned consumed_pos;
	char pcm_depth;
	char pcm_channels;
	unsigned pcm_sampling_rate;
	bool is_playing;
	bool is_initiated;
	bool is_destroyed;
	struct fade_param_type {
		s32                 m_fadeCnt;          //!< フェードカウント(ミリ秒)
		float               m_startVol;         //!< フェード開始のボリューム値(0.0f~1.0f)
		float               m_endVol;           //!< フェード終了のボリューム値(0.0f~1.0f)
		float               m_fadeRatio;        //!< フェード割合(0.0f〜1.0f)
		s32                 m_fadeMiliSec;      //!< フェードに要する時間(ミリ秒)
		s16                 m_nowFadeInterType; //!< 現在のフェード補間タイプ
		s16                 m_nowFadeType;      //!< 現在のフェードタイプ
		bool                m_bfade;            //!< フェード中？
		s64                 m_prevmseq;         //!< 前回の再生時間
	} fade_param;
	s32 state;
	bool is_loop_requested;
	pthread_mutex_t buf_fill_lock;
	s32 last_error;
	SLmillibel cur_mbel;
};

#endif
