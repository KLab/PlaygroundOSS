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
#ifndef CWin32Platform_h
#define CWin32Platform_h

#include "CPFInterface.h"
#include "CWin32Audio.h"
#include "CWin32Widget.h"
#include <setjmp.h>


#define W32_KEYCHAIN_FILENAME  "GE_keychain.key"


class CWin32Platform;

class CWin32Font
{
	friend class CWin32Platform;
public:
	CWin32Font(HDC hDC, int size, const char * fontname = 0);
	virtual ~CWin32Font();

	inline float ascent	() const { return m_ascent;		}
	inline float descent() const { return m_descent;	}
	inline float top	() const { return m_top;		}
	inline float bottom	() const { return m_bottom;		}

	inline HFONT get_hFont() const { return m_hFont;	}

private:
	int		m_size;
	HFONT	m_hFont;
	LOGFONT	m_logfont;

	float	m_ascent;
	float	m_descent;
	float	m_top;
	float	m_bottom;
};


class CWin32Platform : public IPlatformRequest
{
	friend class CWin32Font;
	friend class CWin32Widget;
	friend class CWin32AudioMgr;
	friend class CWin32MP3;
public:
	CWin32Platform(HWND hWnd);
	virtual ~CWin32Platform();

	//! Use Encryption for disk I/O
	virtual bool useEncryption	();
	static  void setEncrypt		(bool encrypt);

	//! ログ出力
	void detailedLogging(const char * basefile, const char * functionName, int lineNo, const char * format, ...);
	void logging(const char * format, ...);

	//! ナノ秒時刻取得
	s64  nanotime();
    
    // バンドルバージョン取得
    const char* getBundleVersion();

	//! ストリーム取得
	IReadStream* openReadStream(const char* fileName, bool decrypt);

	//! テンポラリファイルオープン
	ITmpFile *	openTmpFile			 (const char * filePath);
	void		removeTmpFile		 (const char * filePath);
	virtual bool removeFileOrFolder	 (const char * filePath);
	virtual u32	 getFreeSpaceExternalKB();
	virtual u32	 getPhysicalMemKB	 ();
	void		excludePathFromBackup(const char * fullpath);

	virtual void*		ifopen	(const char* name, const char* mode);
	virtual void		ifclose	(void* file);
	virtual int			ifseek	(void* file, long int offset, int origin);
	virtual u32			ifread	(void* ptr, u32 size, u32 count, void* file );
	virtual u32			ifwrite	(const void * ptr, u32 size, u32 count, void* file);
	virtual int			ifflush	(void* file);
	virtual long int	iftell	(void* file);
	virtual bool		icreateEmptyFile(const char* name);

	//! サウンド
	void*   loadAudio		(const char* url, bool is_se = false);
	bool	setBufSize		(void* handle, int level);
	bool    preLoad			(void* handle);
	void    playAudio		(void* handle, s32 _msec = 0, float _tgtVol = 1.0f, float _startVol = 1.0f);
	void    stopAudio		(void* handle, s32 _msec = 0, float _tgtVol = 0.0f);
	void	setAudioVolume	(void * handle, float volume);
	void	setAudioPan		(void * handle, float pan);
	void	setMasterVolume	(float volume, bool SEmode);
	void    releaseAudio	(void* handle);

	void	pauseAudio		(void * handle, s32 _msec = 0, float _tgtVol = 0.0f);
	void	resumeAudio		(void * handle, s32 _msec = 0, float _tgtVol = 1.0f);
	void	seekAudio		(void * handle, s32 millisec);
	s32		tellAudio		(void * handle);
	s32		totalTimeAudio	(void * handle);

	s32		getState(void * handle);

	void	setFadeParam(void * _handle, float _tgtVol, u32 _msec);

	//! サウンドとミュージックの並行処理タイプ設定
	void setAudioMultiProcessType( s32 /*_processType*/ ) {}
    
    //! サウンドの割り込み処理をエンジン側で制御するかどうか
    void setPauseOnInterruption(bool /*_bPauseOnInterruption*/) {}

	//! 経過時間を取得
	s64 getElapsedTime( void );

	//! フォント
	bool	registerFont	(const char* logicalName, const char* physFile, bool default_);
	void *	getFont			(int size, const char * fontName = 0, float* pAscent = NULL);
	void	deleteFont		(void * pFont);
	void *	getFontSystem	(int size, const char * fontName = 0);
	void	deleteFontSystem(void * pFont);

	//! テキストレンダリング
	bool renderText(const char* utf8String, void * pFont, u32 color,
		u16 width, u16 height, u8 * pBuffer8888,
		s16 stride, s16 base_x, s16 base_y, bool use4444 = false);
	bool getTextInfo(const char* utf8String, void * pFont, STextInfo* pReturnInfo);

	void *			getGLExtension(const char * ext);

	const char *	getPlatform();

	const char *	getFullPath(const char * assetPath, bool* isReadOnly);


	IWidget * createControl(IWidget::CONTROL type, int id,
						 const char * caption, int x, int y, int width, int height, ...);

	void destroyControl(IWidget * pControl);

	bool callApplication(APP_TYPE type, ... );

	void *	createThread	(s32 (*thread_func)(void * hThread, void * data), void * data);
	void	exitThread		(void * hThread, s32 status);
	bool	watchThread		(void * hThread, s32 * status);
	void	deleteThread	(void * hThread);
	void	breakThread		(void * hThread);

	int		genUserID		(char * retBuf, int maxlen);
	int		genUserPW		(const char * salt, char * retBuf, int maxlen);

	bool	readyDevID		();
	int		getDevID		(char * retBuf, int maxlen);

	bool	setSecureDataID	(const char * service_name, const char * user_id);
	bool	setSecureDataPW	(const char * service_name, const char * passwd);
	int		getSecureDataID	(const char * service_name, char * retBuf, int maxlen);
	int		getSecureDataPW	(const char * service_name, char * retBuf, int maxlen);

	bool	delSecureDataID	(const char * service_name);
	bool	delSecureDataPW	(const char * service_name);

	//! ストア機能
	void	initStoreTransactionObserver	();
	void	releaseStoreTransactionObserver	();
	void	buyStoreItems	(const char * item_id);
	void	getStoreProducts(const char * json, bool currency_mode);
	void	finishStoreTransaction(const char* receipt);


	inline HWND get_hWnd() const { return m_hWnd; }

	virtual void *	allocMutex		();
	virtual void	freeMutex		(void * mutex);
	virtual void	mutexLock		(void * mutex);
	virtual void	mutexUnlock		(void * mutex);

	virtual void *	allocEventLock	();
	virtual void	freeEventLock	(void * lock);
	virtual void	eventSleep		(void * lock);
	virtual void	eventWakeup		(void * lock);
	
	void	startAlertDialog( const char* /*title*/ , const char* /*message*/){};

	void	setNoDefaultFont() {
		m_bNoDefaultFont = true;
	}

	inline void forbidSleep(bool is_forbidden) {}

private:
	bool m_bNoDefaultFont;

	static bool g_useDecryption;

	struct PF_THREAD {
		jmp_buf jmp;
		HANDLE	hWin32Thread;
		DWORD	idWin32Thread;
		s32 (*thread_func)(void *, void *);
		void * data;
		s32 result;
	};

	int		sha512		(const char * string, char * buf, int maxlen);
	bool	setKeyChain	(const char * service_name, const char * key, const char * value);
	int		getKeyChain	(const char * service_name, const char * key, char * retBuf, int maxlen);
	bool	delKeyChain	(const char * service_name, const char * key);

	const char * utf8toSJIS(const char * utf8str);
	const char * SJIStoUTF8(const char * SJISstr);
	const char * create_version_string();

	enum {
		SND_SLOT = 256
	};
	CWin32Audio			m_audio[ SND_SLOT ];
	HWND				m_hWnd;
	HDC					m_hDC;

	const char		*	m_version_string;

	static DWORD WINAPI ThreadProc(LPVOID lpParam);
};


#endif // CWin32Platform_h
