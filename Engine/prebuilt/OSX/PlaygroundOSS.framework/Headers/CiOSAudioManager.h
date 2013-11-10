#ifndef CiOSAudioManager_h
#define CiOSAudioManager_h


#import <GLKit/GLKit.h>
#import <mach/time_value.h>
#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <AudioToolbox/ExtendedAudioFile.h>
#import <AudioToolbox/AudioFile.h>

#import "CiOSPlatform.h"
#import "CiOSAudio.h"

#define IOS_HARDWARE_IO_BUFFER_SIZE     (256)   // IOバッファサイズ(最小128の最大1024くらいまでの2の乗数倍の値推奨)

class CiOSAudioManager
{
public:
	// サウンドの割り込みタイプ
	enum eINTERRUPTION_TYPE {
		eINTERRUPTION_TYPE_NONE = -1,
        
		eINTERRUPTION_TYPE_CALLING = 0,         //!< 電話、Siriなどの割り込み
		eINTERRUPTION_TYPE_RESIGN_ACTIVE,       //!< ホームボタンダブルタップなどによる非アクティブ状態
		eINTERRUPTION_TYPE_ENTER_BACKGROUND,    //!< ホームボタンなどによるアプリがバックグラウンドにある状態
        
		eINTERRUPTION_TYPE_MAX
	};
    
private:
	CiOSAudioManager();
	virtual ~CiOSAudioManager();
	const CiOSAudioManager& operator = (const CiOSAudioManager &_manager) { return *this; }
    
public:
	//! インスタンスの取得
	static CiOSAudioManager& GetInstance(void) {
		return m_instance;
	}
    
	//! 初期化処理
	bool Initialize(void);
    
	//! 終了処理
	bool Termination(void);
    
	//! サウンドハンドル作成
	void *CreateAudioHandle(const char *_url, CiOSPlatform *_platform);
    
	//! AudioSessionの初期化
	bool AudioSessionInit(void);
    
	//! AudioSessionプロパティの設定
	bool AudioSessionPropertySetting(void);
    
	//! 割り込み開始処理
	void AudioBeginInterruption(void);
    
	//! 割り込み終了処理
	void AudioEndInterruption(void);
    
	//! 非アクティブになる瞬間の処理
	void AudioDidResignActive(void);
    
	//! アクティブに戻る瞬間の処理
	void AudioDidBecomeActive(void);
    
	//! バックグラウンドに行く瞬間の処理
	void AudioDidEnterBackground(void);
    
	//! バックグラウンドから戻る際の処理
	void AudioDidEnterForeground(void);
    
	//! サウンドとミュージックの並行処理タイプ
	void SetAudioMultiProcessType(s32 _type);
    
	inline s32 GetAudioMultiProcessType(void) {
		return m_multiProcessType;
	}
    
	//! サウンドの割り込み処理をエンジン側で制御するかどうか
	inline void setPauseOnInterruption(bool _bPauseOnInterruption) {
		m_bPauseOnInterruption = _bPauseOnInterruption;
	}
    
	inline bool getPauseOnInterruption(void) {
		return m_bPauseOnInterruption;
	}
    
	//! iPodミュージックプレーヤーの再生状態取得
	bool isMusicPlayerPlaying(void);
    
	//! 音量設定
	void SetSEMasterVolume(float _vol);
	void SetBGMMasterVolume(float _vol);
	float GetSEMasterVolume(void);
	float GetBGMMasterVolume(void);
	void UpdateVolume(void);
    
	//! 現在の設定によりマスターボリュームのON/OFF
	void chackAudioMasterVolume(void);
    
	//! 毎フレーム行う処理
	void Exec(void);
    
private:
	static CiOSAudioManager m_instance;
    
private:
	enum {
		SND_SLOT = 256     // サウンドスロット数
	};
	CiOSAudio m_audio[SND_SLOT];
    
	// サウンドとミュージックの並行処理タイプ
	s32 m_multiProcessType;
    
	// ボリューム関係
	float m_masterVol_se;           //!< SEのマスターボリューム
	float m_masterVol_bgm;          //!< BGMのマスターボリューム
    
	// サウンドのON/OFF
	bool m_bSEOff;                  //!< SE
	bool m_bBGMOff;                 //!< BGM
    
	//
	bool m_bInit;                   //!< 初期化フラグ
    
	bool m_bPauseOnInterruption;        //!< サウンドのPauseをエンジン側で制御するかどうか
};

#endif // CiOSAudioManager_h
