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
//  CiOSAudioManager.cpp
//
//

#include "CiOSAudioManager.h"

// #define DEBUG_AUDIO

// インスタンス
CiOSAudioManager CiOSAudioManager::m_instance;

// 割り込み処理関数
static void AudioInterruptionCallBack( void* _userData, UInt32 _state )
{
    if( _userData == NULL ) return;
    CiOSAudioManager* pSndMng = (CiOSAudioManager*)_userData;
    // IPlatformRequest *pform = CiOSPlatform::getInstance();
    
    // 割り込み開始
    if( _state == kAudioSessionBeginInterruption )
    {
		#ifdef DEBUG_AUDIO
        if( pform ) pform->logging("[AudioManager] begin interruption!");
		#endif
        pSndMng->AudioBeginInterruption();
    }
    
    // 割り込み終了
    if( _state == kAudioSessionEndInterruption )
    {
		#ifdef DEBUG_AUDIO
        if( pform ) pform->logging("[AudioManager] end interruption!");
		#endif
        pSndMng->AudioEndInterruption();
    }
}

/*!
 @brief  コンストラクタ
 */
CiOSAudioManager::CiOSAudioManager()
: m_masterVol_se(1.0f)
, m_masterVol_bgm(1.0f)
, m_multiProcessType(IClientRequest::E_SOUND_MULTIPROCESS_MUSIC_CUT)
, m_bSEOff(false)
, m_bBGMOff(false)
, m_bPauseOnInterruption(true)
{
}

/*!
 @brief  デストラクタ
 */
CiOSAudioManager::~CiOSAudioManager()
{
}

/*!
 @brief  初期化処理
 @param[in]  void
 @return     bool    true:正常, false:異常
 */
bool CiOSAudioManager::Initialize( void )
{
    // AudioSessionの初期化
    AudioSessionInit();
    
    // フェード管理機構の初期化
    cAudioFadeParam::AudioFadeParamInit();
    
    // IOバッファサイズの設定
    Float64 sampleRate;
    UInt32 size = sizeof(sampleRate);
    OSStatus err;
    err = AudioSessionGetProperty(kAudioSessionProperty_CurrentHardwareSampleRate, &size, &sampleRate);
    klb_assert(!err, "can not get Hardware SampleRate.");
    
    Float32 duration = (Float32)IOS_HARDWARE_IO_BUFFER_SIZE / sampleRate; // iOSシステムデフォルトは(1024/sampleRate)
    err = AudioSessionSetProperty(kAudioSessionProperty_PreferredHardwareIOBufferDuration, sizeof(duration), &duration);
    klb_assert(!err, "can not set Hardware SampleRate.");
    
    m_bInit = true;
    return true;
}

/*!
 @brief  初期化処理
 @param[in]  void
 @return     bool    true:正常, false:異常
 */
bool CiOSAudioManager::Termination( void )
{
    // フェード管理機構の終了処理
    cAudioFadeParam::AudioFadeParamExit();
    
    return true;
}

/*!
 @brief  サウンドハンドル作成
 @param[in]  const char* _url    サウンドファイルパス
 @return     void*               サウンドハンドル
 */
void* CiOSAudioManager::CreateAudioHandle( const char* _url, CiOSPlatform* _platform )
{
    for( int i=0; i<SND_SLOT; ++i )
    {
        // 使用中の物はスキップ
        if( m_audio[i].isActive() ) {
            continue;
        }
        
        bool bRes = m_audio[i].openAudio( _url, _platform );
        return (bRes) ? ((void*)&m_audio[i]) : NULL;
    }
    // 空のスロットが見つからなかった
    return NULL;
}

/*!
 @brief  AudioSessionの初期化
 @param[in]  void
 @return     bool    true:正常, false:異常
 */
bool CiOSAudioManager::AudioSessionInit( void )
{
    OSStatus err = errSecSuccess;
    err = AudioSessionInitialize( NULL, NULL, AudioInterruptionCallBack, this );
    if( err != kAudioSessionNoError ) {
        //return false;
    }
 
    // AudioSessionSetProprety
    AudioSessionPropertySetting();
    
    AudioSessionSetActive( true );
    
    return true;
}

//! AudioSessionプロパティの設定
bool CiOSAudioManager::AudioSessionPropertySetting( void )
{
    // サウンドとミュージックの並行処理の設定
    UInt32 category = kAudioSessionCategory_AmbientSound;
    // IPlatformRequest *pform = CiOSPlatform::getInstance();
    switch( m_multiProcessType )
    {
        case IClientRequest::E_SOUND_MULTIPROCESS_MUSIC_CUT:
            category = kAudioSessionCategory_SoloAmbientSound;
			#ifdef DEBUG_AUDIO
			if( pform ) pform->logging("[AudioManager] multi process:music_cut");
			#endif
            break;
        case IClientRequest::E_SOUND_MULTIPROCESS_SOUND_CUT:
            category = kAudioSessionCategory_AmbientSound;
			#ifdef DEBUG_AUDIO
            if( pform ) pform->logging("[AudioManager] multi process:sound_cut");
			#endif
            break;
        case IClientRequest::E_SOUND_MULTIPROCESS_SOUND_BGM_CUT:
            category = kAudioSessionCategory_AmbientSound;
			#ifdef DEBUG_AUDIO
            if( pform ) pform->logging("[AudioManager] multi process:sound_bgm_cut");
			#endif
            break;
    }
    AudioSessionSetProperty(kAudioSessionProperty_AudioCategory, sizeof(category), &category);

    // マスターボリュームON/OFF設定
    chackAudioMasterVolume();
    
    AudioSessionSetActive( true );
    
    return true;
}

/*!
 @brief  割り込み開始処理
 @param[in]  void
 @return     void
 */
void CiOSAudioManager::AudioBeginInterruption( void )
{
    /*
    // ポーズ処理をエンジン側で制御しないのでリターン
    if( getPauseOnInterruption() == false ) return;

    for( int i=0; i<SND_SLOT; ++i )
    {
        if( m_audio[i].isActive() &&
           (m_audio[i].getState() == IClientRequest::E_SOUND_STATE_PLAY) &&
           (m_audio[i].getInterruptionType() == eINTERRUPTION_TYPE_NONE) )
        {
            // サウンドを停止し割り込みフラグをたてる
            m_audio[i].pause();
            m_audio[i].setInterruptionType(eINTERRUPTION_TYPE_CALLING);
        }
    }
     */
}

/*!
 @brief  割り込み終了処理
 @param[in]  void
 @return     void
 */
void CiOSAudioManager::AudioEndInterruption( void )
{
    /*
    AudioSessionSetActive( true );
    
    // 電話などの割り込み復帰後にSessionが無効化されるのでSessionを再設定
    AudioSessionInit();
    
    // マスターボリュームON/OFF設定
    chackAudioMasterVolume();
    
    for( int i=0; i<SND_SLOT; ++i )
    {
        if( m_audio[i].isActive() && (m_audio[i].getInterruptionType() == eINTERRUPTION_TYPE_CALLING) )
        {
            // 割り込みフラグがたっている物に限り再生を再開
            if( !m_audio[i].getLuaPause() ) {
                m_audio[i].resume();
            }
            m_audio[i].setInterruptionType(eINTERRUPTION_TYPE_NONE);
        }
    }
     */
}

/*!
 @brief  非アクティブになる瞬間の処理
 @param[in]  void
 @return     void
 */
void CiOSAudioManager::AudioDidResignActive( void )
{
    // ポーズ処理をエンジン側で制御しないのでリターン
    if( getPauseOnInterruption() == false ) return;

    for( int i=0; i<SND_SLOT; ++i )
    {
        if( m_audio[i].isActive() &&
           (m_audio[i].getState() == IClientRequest::E_SOUND_STATE_PLAY) &&
           (m_audio[i].getInterruptionType() == eINTERRUPTION_TYPE_NONE) )
        {
            // サウンドを停止し割り込みフラグをたてる
            m_audio[i].pause();
            m_audio[i].setInterruptionType(eINTERRUPTION_TYPE_RESIGN_ACTIVE);
        }
    }
}

/*!
 @brief  アクティブに戻る瞬間の処理
 @param[in]  void
 @return     void
 */
void CiOSAudioManager::AudioDidBecomeActive( void )
{
    AudioSessionSetActive( true );
    
    // マスターボリュームON/OFF設定
    chackAudioMasterVolume();
    
    for( int i=0; i<SND_SLOT; ++i )
    {
        if( m_audio[i].isActive() && (m_audio[i].getInterruptionType() == eINTERRUPTION_TYPE_RESIGN_ACTIVE) )
        {
            // 割り込みフラグがたっている物に限り再生を再開
            if( !m_audio[i].getLuaPause() ) {
                m_audio[i].resume();
            }
            m_audio[i].setInterruptionType(eINTERRUPTION_TYPE_NONE);
        }
    }
}

/*!
 @brief  バックグラウンドに行く瞬間の処理
 @param[in]  void
 @return     void
 */
void CiOSAudioManager::AudioDidEnterBackground( void )
{
    /*
    // ポーズ処理をエンジン側で制御しないのでリターン
    if( getPauseOnInterruption() == false ) return;

    for( int i=0; i<SND_SLOT; ++i )
    {
        if( m_audio[i].isActive() &&
           (m_audio[i].getState() == IClientRequest::E_SOUND_STATE_PLAY) &&
           (m_audio[i].getInterruptionType() == eINTERRUPTION_TYPE_NONE) )
        {
            // サウンドを停止し割り込みフラグをたてる
            m_audio[i].pause();
            m_audio[i].setInterruptionType(eINTERRUPTION_TYPE_ENTER_BACKGROUND);
        }
    }
     */
}

/*!
 @brief  バックグラウンドから戻る際の処理
 @param[in]  void
 @return     void
 */
void CiOSAudioManager::AudioDidEnterForeground( void )
{
    /*
    AudioSessionSetActive( true );
    
    // マスターボリュームON/OFF設定
    chackAudioMasterVolume();
    
    for( int i=0; i<SND_SLOT; ++i )
    {
        if( m_audio[i].isActive() && (m_audio[i].getInterruptionType() == eINTERRUPTION_TYPE_ENTER_BACKGROUND) )
        {
            // 割り込みフラグがたっている物に限り再生を再開
            if( !m_audio[i].getLuaPause() ) {
                m_audio[i].resume();
            }
            m_audio[i].setInterruptionType(eINTERRUPTION_TYPE_NONE);
        }
    }
     */
}

/*!
 @brief  サウンドとミュージックの並行処理タイプ
 @param[in]  s32
 @return     void
 */
void CiOSAudioManager::SetAudioMultiProcessType( s32 _type )
{
    m_multiProcessType = _type;
    
    // AudioSession再設定
    AudioSessionInit();

    // ボリュームの再設定
    for( int i=0; i<SND_SLOT; ++i )
    {
        if( m_audio[i].isActive() ) {
            m_audio[i].updateVolume();
        }
    }
}

/*!
 @brief  SEのマスターボリューム設定
 @param[in]  void
 @return     void
 */
void CiOSAudioManager::SetSEMasterVolume( float _vol )
{
    if( _vol < 0.0f ) {
        _vol = 0.0f;
    } else if( _vol > 1.0f ) {
        _vol = 1.0f;
    }
    m_masterVol_se = _vol;
}

//! iPodミュージックプレーヤーの再生状態取得
/*!
 @brief  iPodミュージックの再生状態の取得
 @param[in]  void
 @return     bool   true:再生中, false:未再生
 */
bool CiOSAudioManager::isMusicPlayerPlaying( void )
{
    // IPlatformRequest *pform = CiOSPlatform::getInstance();
    MPMusicPlaybackState ipodState = [[MPMusicPlayerController iPodMusicPlayer] playbackState];
    // MPMusicPlaybackState appliState = [[MPMusicPlayerController applicationMusicPlayer] playbackState];
    
    //MPMediaItem *ipodMusicItem = [[MPMusicPlayerController iPodMusicPlayer] nowPlayingItem];
    //MPMediaItem *appliMusicItem = [[MPMusicPlayerController applicationMusicPlayer] nowPlayingItem];
    //if( pform ) pform->logging("[AudioManager] musioc ipod:%p", ipodMusicItem);
    //if( pform ) pform->logging("[AudioManager] musioc appli:%p", appliMusicItem);
	#ifdef DEBUG_AUDIO
    if( pform ) pform->logging("[AudioManager] musioc state:%d", ipodState);
    if( pform ) pform->logging("[AudioManager] appli state:%d", appliState);
	#endif
    if( ipodState != MPMusicPlaybackStatePlaying )
    //if( ipodState == MPMusicPlaybackStateStopped || ipodState == MPMusicPlaybackStatePaused )
    //if( appliState == MPMusicPlaybackStateStopped || appliState == MPMusicPlaybackStatePaused )
    {
        // 停止中・一時停止中
		#ifdef DEBUG_AUDIO
        if( pform ) pform->logging("[AudioManager] musioc play:false");
		#endif
        return false;
    }
	#ifdef DEBUG_AUDIO
    if( pform ) pform->logging("[AudioManager] musioc play:true");
	#endif
    return true;
    
    /*
    UInt32 playing;
    UInt32 propertySize = sizeof(playing);
    
    AudioSessionGetProperty( kAudioSessionProperty_OtherAudioIsPlaying, &propertySize, &playing );
    
    if( playing != 0 ) {
        if( pform ) pform->logging("[AudioManager] musioc play:true");
        return true;
    }
    if( pform ) pform->logging("[AudioManager] musioc play:false");
    return false;
     */
}

/*!
 @brief  BGMのマスターボリューム設定
 @param[in]  void
 @return     void
 */
void CiOSAudioManager::SetBGMMasterVolume( float _vol )
{
    if( _vol < 0.0f ) {
        _vol = 0.0f;
    } else if( _vol > 1.0f ) {
        _vol = 1.0f;
    }
    m_masterVol_bgm = _vol;
}

/*!
 @brief  SEのマスターボリューム取得
 @param[in]  void
 @return     float  SEマスターボリューム(0.0f〜1.0f)
 */
float CiOSAudioManager::GetSEMasterVolume( void )
{
    // SEオフの状態なのでマスターを常に０でリターン
    if( m_bSEOff ) {
        return 0.0f;
    }
    return m_masterVol_se;
}

/*!
 @brief  BGMのマスターボリューム取得
 @param[in]  void
 @return     float  BGMマスターボリューム(0.0f〜1.0f)
 */
float CiOSAudioManager::GetBGMMasterVolume( void )
{
    // BGMオフの状態なのでマスターを常に０でリターン
    if( m_bBGMOff ) {
        return 0.0f;
    }
    return m_masterVol_bgm;
}

/*!
 @brief  サウンドの音量更新
 @param[in]  void
 @return     void
 */
void CiOSAudioManager::UpdateVolume( void )
{
    for( int i=0; i<SND_SLOT; ++i ) {
        if( m_audio[i].isActive() ) m_audio[i].updateVolume();
    }
}

/*!
 @brief 現在の設定によりマスターボリュームのON/OFF
 @param[in] void
 @return    void
 */
void CiOSAudioManager::chackAudioMasterVolume( void )
{
    switch( m_multiProcessType )
    {
        case IClientRequest::E_SOUND_MULTIPROCESS_MUSIC_CUT:    // iPodミュージックを無効
            m_bSEOff = false;
            m_bBGMOff = false;
            break;
        case IClientRequest::E_SOUND_MULTIPROCESS_SOUND_CUT:    // ゲームサウンドを無効
            m_bSEOff = true;
            m_bBGMOff = true;
            if( isMusicPlayerPlaying() == false )
            {
                m_bSEOff = false;
                m_bBGMOff = false;
            }
            break;
        case IClientRequest::E_SOUND_MULTIPROCESS_SOUND_BGM_CUT: // ゲームのBGMサウンドのみ無効
            m_bSEOff = false;
            m_bBGMOff = true;
            if( isMusicPlayerPlaying() == false ) {
                m_bBGMOff = false;
            }
            break;
    }
    UpdateVolume();
}

/*!
 @brief  毎フレーム行う処理
 @param[in]  void
 @return     void
 */
void CiOSAudioManager::Exec( void )
{
    for( int i=0; i<SND_SLOT; ++i ) {
        if( m_audio[i].isActive() ) m_audio[i].audioSessionCleanup();
    }
}






