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
#ifndef cppinterface_h
#define cppinterface_h

#include <string.h>
#include <time.h>
#include <pthread.h>
#include <setjmp.h>

// #include "klb_android_GameStartup_PFInterface.h"
#include "CPFInterface.h"
#include "CAndroidReadFileStream.h"
#include "CSockReadStream.h"
#include "CJNI.h"

class CAndroidRequest : public IPlatformRequest
{
public:
	CAndroidRequest(const char * model,const char * brand, const char * board, const char * version, const char * tz);
	virtual ~CAndroidRequest();

	static CAndroidRequest * getInstance();

	void nativeSignal(int cmd, int param);

	void init();

	//! Use Encryption for disk I/O
	virtual bool useEncryption();

	void detailedLogging(const char * basefile, const char * functionName, int lineNo, const char * format, ...);
	void logging(const char * format, ...);
	s64	nanotime();
    
    // バンドルバージョン取得
    const char* getBundleVersion();

	IReadStream * openReadStream(const char * fileName, bool decrypt);
	ITmpFile * openTmpFile(const char * tmpPath);
    void removeTmpFile(const char * tmpPath);
	virtual bool removeFileOrFolder	 (const char * filePath);
	virtual u32 getFreeSpaceExternalKB();
	virtual u32 getPhysicalMemKB	 ();
    void excludePathFromBackup(const char * fullpath);
    void*		ifopen	(const char* name, const char* mode);
	void		ifclose	(void* file);
	int			ifseek	(void* file, long int offset, int origin);
	u32			ifread	(void* ptr, u32 size, u32 count, void* file );
	u32			ifwrite	(const void * ptr, u32 size, u32 count, void* file);
	int			ifflush	(void* file);
	long int	iftell	(void* file);
	bool		icreateEmptyFile(const char* name);

	void * loadAudio(const char * url, bool is_se);
    bool   preLoad(void * handle);
    bool   setBufSize(void * handle, int level);
    void   playAudio(void * handle, s32 _milisec=0, float _tgtVol=1.0f, float _startVol=1.0f);
    void   stopAudio(void * handle, s32 _milisec=0, float _tgtVol=0.0f);
    void   setMasterVolume(float volume, bool SEmode);
    void   setAudioVolume(void * handle, float volume);
    void   setAudioPan(void * handle, float pan);
    void   releaseAudio(void * handle);
	
	void pauseAudio(void * handle, s32 _milisec=0, float _tgtVol=0.0f);
    void resumeAudio(void * handle, s32 _milisec=0, float _tgtVol=1.0f);
    void seekAudio(void * handle, s32 millisec);
    s32  tellAudio(void * handle);
    s32  totalTimeAudio(void * handle);
	
    s32 getState(void * handle);
    
    //! サウンドとミュージックの並行処理タイプ設定
    void setAudioMultiProcessType( s32 _processType );
    
    //! サウンドの割り込み処理をエンジン側で制御するかどうか
    void setPauseOnInterruption(bool _bPauseOnInterruption);
    
    //! 経過時間を取得(sec)
    s64 getElapsedTime(void);
    
    void setFadeParam(void* _handle, float _tgtVol, u32 _milisec);

    //! フォントオブジェクト取得
	bool registerFont(const char* logicalName, const char* physFile, bool default_);
	void * getFont(int size, const char * fontName = 0, float* pAscent = NULL);
	void * getFontSystem(int size, const char * fontName = 0);

    //! フォントオブジェクト破棄
    void deleteFont(void * pFont);
    void deleteFontSystem(void * pFont);

    //! フォントテクスチャ描画
    bool renderText(const char* utf8String, void * pFont, u32 color,    //!< 描画する文字列とフォントの指定
                    u16 width, u16 height, u8 * pBuffer8888,    		//!< 描画対象とするテクスチャバッファとそのピクセルサイズ
                    s16 stride, s16 base_x, s16 base_y, bool use4444);  //!< baseline起点とするテクスチャ内の位置

    bool getTextInfo(const char* utf8String, void * pFont, STextInfo* pReturnInfo);

    void* getGLExtension(const char*);

    // 追加分method

    const char * getFullPath(const char * assetPath, bool* isReadOnly);

    const char * getPlatform();

    IWidget * createControl(IWidget::CONTROL type, int id, const char * caption, int x, int y, int width, int height, ...);
    void destroyControl(IWidget * pControl);
    bool callApplication(APP_TYPE type, ...);

    void * createThread(s32 (*thread_func)(void * hThread, void * data), void * data);
    void exitThread(void * hThread, s32 status);
    bool watchThread(void * hThread, s32 * status);
    void deleteThread(void * hThread);
    void breakThread(void * hThread);

    int genUserID(char * retBuf, int maxlen);
    int genUserPW(const char * salt, char * retBuf, int maxlen);
	
    bool readyDevID();
    int getDevID(char * retBuf, int maxlen);
	
    bool setSecureDataID(const char * service_name, const char * user_id);
    bool setSecureDataPW(const char * service_name, const char * passwd);
    int getSecureDataID(const char * service_name, char * retBuf, int maxlen);
    int getSecureDataPW(const char * service_name, char * retBuf, int maxlen);

	bool delSecureDataID(const char * service_name);
    bool delSecureDataPW(const char * service_name);
	
    // alert dialog
    void startAlertDialog( const char* title , const char* message );
	
	inline void setHomePath(const char * home) {
		int len = strlen(home);
		m_homePath = new char [len + 1];
		strcpy(m_homePath, home);
	}
	bool callJavaMethod(jvalue& ret, const char * method, const char rettype, const char * form, ...);

	inline float getMasterVolume(bool SEmode) const { return (SEmode) ? m_master_SE : m_master_BGM; }


	//! ストア機能
	//! トランザクション監視開始
	void initStoreTransactionObserver();
	//! トランザクション監視終了
	void releaseStoreTransactionObserver();
	//! 購入要求: アイテムID(文字列)の配列と、その数を渡す
    void buyStoreItems(const char * item_id);
	//! プロダクトリスト取得要求: アイテムIDの配列とその数、及びcurrency表示にするかの判定とcallbackを渡す.
    void getStoreProducts(const char* json, bool currency_mode);
	//! サーバー通信後にトランザクションを閉じて購入処理を確定させる。
	void finishStoreTransaction(const char* receipt);

	virtual void*	allocMutex		();
	virtual void	freeMutex		(void* mutex);
	virtual void	mutexLock		(void* mutex);
	virtual void	mutexUnlock		(void* mutex);

	virtual void*	allocEventLock	();
	virtual void	freeEventLock	(void* lock);
	virtual void	eventSleep		(void* lock);
	virtual void	eventWakeup		(void* lock);

	void forbidSleep(bool is_forbidden);

private:
	struct PF_THREAD {
		jmp_buf		jmp;
		pthread_t	id;
		s32 (*thread_func)(void *, void *);
		void * data;
		s32 result;
	};
	static void * ThreadProc(void * data);
	int sha512(const char * string, char * buf, int maxlen);

	enum {
		SND_SLOT = 256
	};
	char 			*	m_homePath;
	const char		*	m_platform;
	float				m_master_BGM;
	float				m_master_SE;

	const char		*	m_regId;

	static CAndroidRequest * ms_instance;
	static void getElapsedTimeSpec(struct timespec * ts);
	static s64 getElapsedNanoTime(void);
};

#endif // cppinterface_h
