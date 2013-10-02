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
// #include <iostream>
// #include <string>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <pthread.h>
#include <setjmp.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <jni.h>
#include <unistd.h>
#include <linux/ioctl.h>
#include <sys/vfs.h>
#include <android/log.h>
#include "CAndroidPathConv.h"
#include "CAndroidRequest.h"
#include "CAndroidTmpFile.h"
#include "CAndroidWidget.h"
#include "CJNI.h"
#include "KLBOpenSLAudioPlayer.h"
#include "PackageDefine.h"
#include "KLBPlatformMetrics.h"
#include "FontRendering.h"

#include <vector>
// #include "klb_android_GameEngine_PFInterface.h"

// Android は stdarg.h をサポートしない(そのかわりincludeしてもエラーを出さない)ため、
// va_start/va_arg/va_end が定義されない。gcc のビルトインを定義してやる。
#if !defined(va_start)
#define va_start(ap, last) __builtin_va_start(ap, last)
#endif
#if !defined(va_end)
#define va_end(ap) __builtin_va_end(ap)
#endif
#if !defined(va_arg)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#endif
#if !defined(va_list)
typedef __builtin_va_list va_list;
#endif

CAndroidRequest * CAndroidRequest::ms_instance = 0;

CAndroidRequest::CAndroidRequest(const char* model, const char * brand, const char * board, const char * version, const char * tz)
: m_homePath(0), m_master_BGM(1.0f), m_master_SE(1.0f), m_regId(0)
{
	int len = strlen(model);
	len += strlen(brand);
	len += strlen(board);
	len += strlen(version);
	len += strlen(tz);
	len += 15;	// "Android;%s %s %s;%s"

	char * buf = new char [ len ];
	sprintf(buf, "Android;%s %s %s %s;%s", model, brand, board, version, tz);
	m_platform = (const char *)buf;
	ms_instance = this;
}

CAndroidRequest::~CAndroidRequest() {
	delete [] m_homePath;
	delete [] m_platform;
        delete [] m_regId;
}

CAndroidRequest *
CAndroidRequest::getInstance()
{
	return ms_instance;
}

void
CAndroidRequest::nativeSignal(int cmd, int param)
{
	enum {
		MOVIE_FINISHED = 1,
	};
	DEBUG_PRINT("nativeSignal(%d, %d)", cmd, param);

	switch(cmd)
	{
	case MOVIE_FINISHED:
	{
		CAndroidMovieWidget * pWidget = CAndroidMovieWidget::getWidget(param);
		if(pWidget) pWidget->m_status = 1;
		break;
	}
	default:
		break;
	}
}

void
CAndroidRequest::init()
{
}
void
CAndroidRequest::detailedLogging(const char * basefile, const char * functionName, int lineNo, const char * format, ...)
{
#if DEBUG
#ifndef DEBUG_PRINT_OFF
	const short logLength = 1024;
    char log[logLength];
	int hdrLength = 0;

	hdrLength = snprintf(log, logLength, "[%d at %s][FUNC:%s] ", lineNo, basefile, functionName);
	if (hdrLength < 0 || hdrLength == logLength) {
		return;
	}

    // format済み文字列を生成
    va_list ap;
    va_start(ap, format);
    int log_len = vsnprintf(log + hdrLength, logLength - hdrLength, format, ap);
    va_end(ap);

    // Java側のログ出力メソッドを呼ぶ
    __android_log_write(ANDROID_LOG_DEBUG, "Cpp", log);
	KLBPlatformMetrics::getInstance()->appendLog(log, log_len);
#endif // DEBUG_PRINT_OFF
#endif // DEBUG
}

void
CAndroidRequest::logging(const char * format, ...)
{
#if DEBUG
    char log[1024];

    // format済み文字列を生成
    va_list ap;
    va_start(ap, format);
    vsprintf(log, format, ap);
    va_end(ap);

    // Java側のログ出力メソッドを呼ぶ
    __android_log_write(ANDROID_LOG_DEBUG, "Cpp", log);
#endif
}

const char*
CAndroidRequest::getBundleVersion() {
    jvalue value;
    CAndroidRequest::getInstance()->callJavaMethod(value, "getVersionName", 'S', "");
    jstring jstr = (jstring)value.l;
    const char * str = CJNI::getJNIEnv()->GetStringUTFChars(jstr, NULL);
    CJNI::getJNIEnv()->ReleaseStringUTFChars(jstr, str);
    // FIXME ReleaseStringUTFChars 後のポインタを返してしまっている
    return str;
}

ITmpFile *
CAndroidRequest::openTmpFile(const char * tmpPath)
{
	const char * target = "file://external/";
	int len = strlen(target);
	if(!strncmp(tmpPath, target, len)) {
		// 平成24年11月27日(火)
		// CiOSTmpFileのファイルパスの解決の仕方が'file://'を抜いた状態で解釈するため、
		// CiOSTmpFileへ渡すファイルパスのprefixを'file://'分進めて渡しています。
		tmpPath = tmpPath + 7;
		CAndroidTmpFile * pTmpFile = new CAndroidTmpFile(tmpPath);
		if(!pTmpFile->isReady()) {
			delete pTmpFile;
			pTmpFile = 0;
		}
		return pTmpFile;
	}
	return 0;
}

#include "FileDelete.h"

const char* getFullNativePath(const char* path) {
	CAndroidPathConv& pathconv = CAndroidPathConv::getInstance();
	return pathconv.fullpath(path + 7);
}

bool
CAndroidRequest::removeFileOrFolder(const char* filePath) {
	const char * target = "file://external/";
	int len = strlen(target);
	if(!strncmp(filePath, target, len)) {
		return deleteFiles(filePath);
	} else {
		return false;
	}
}

void removeTmpFileNative(const char* filePath) {
	remove(filePath);
}

void
CAndroidRequest::removeTmpFile(const char *tmpPath)
{
	CAndroidPathConv& pathconv = CAndroidPathConv::getInstance();

	const char * target = "file://external/";
	int len = strlen(target);
	if(!strncmp(tmpPath, target, len)) {
		const char * fullpath = pathconv.fullpath(tmpPath + 7);
		unlink(fullpath);
		delete [] fullpath;
	}
}

u32
CAndroidRequest::getFreeSpaceExternalKB() {
	struct statfs diskInfo;
	const int ret = statfs(CAndroidPathConv::getInstance().fullpath("external/"), &diskInfo);
	if (ret != 0) {
		// error fetching free space size. return "no more space left" for safety
		return 0;
	}
	// calculate free space in KB available to non-superusers
	unsigned long long freeKB = (diskInfo.f_bavail * diskInfo.f_bsize) >> 10;
	if (freeKB & ~0xFFFFFF) {
		return 0xFFFFFF;
	}
	return (u32)freeKB;
}

u32
CAndroidRequest::getPhysicalMemKB() {
	FILE* f = fopen("/proc/meminfo", "r");
	u32 outValue = 0; // Default if fail

	if (f) {
		int state = 0; 	// Beginning of parsing state machine.
		char title[64];	// Storage for descriptor text.
		int titleWrite = 0;
		u32 value = 0;

		while (!feof(f)) {
			char c = fgetc(f);
			
			switch (state) {
			case 0:	// Read Title
				if (c == ':') {
					state = 1;
					title[titleWrite++] = 0; // Close string
				} else if (c >' ') { // Protect from 0xA or 0xD if multiple
					title[titleWrite++] = c;
				}
				break;
			case 1:
				// Cross the sea of spaces after ':'
				// Compute the value for value 0..9
				// Detect the end of line
				if ((c >= '0') && (c <= '9')) {
					value = (value * 10) + (c - '0');
				} else if ((c == 0xA) || (c == 0xD)) {
					//
					// Here we check the value
					//
					if (strcmp("MemTotal", title) == 0) {
						outValue = value;
					}
					
					// Ready to read the next entry
					state = 0;
					value = 0;
					titleWrite = 0;
				}
			}
		}
		
		// State machine fails if no EOF in last line, check here.
		if (state == 1) {
			if (strcmp("MemTotal", title) == 0) {
				outValue = value;
			}
		}
		
		fclose(f);
	}
	return outValue;
}

void
CAndroidRequest::excludePathFromBackup(const char * fullpath)
{
	// TODO
}

bool CAndroidRequest::useEncryption() {
	return true;
}

s64
CAndroidRequest::nanotime()
{
#if 0
	jclass cls_pfif = CJNI::getJNIEnv()->FindClass(JNI_LOAD_PATH);
	jmethodID nanotime_id = CJNI::getJNIEnv()->GetStaticMethodID(cls_pfif, "nanotime", "()J");
//	jclass cls_pfif = CJNI::getJNIEnv()->FindClass("java/lang/System");
//	jmethodID nanotime_id = CJNI::getJNIEnv()->GetStaticMethodID(cls_pfif, "nanoTime", "()J");
	jlong nanotime = CJNI::getJNIEnv()->CallStaticLongMethod(cls_pfif, nanotime_id);
#endif
	struct timespec tspec;
	clock_gettime(CLOCK_REALTIME, &tspec);
	s64 nanotime = (s64)tspec.tv_sec * 1000000000LL + (s64)tspec.tv_nsec;
	return nanotime;
}

IReadStream *
CAndroidRequest::openReadStream(const char *pathname, bool decrypt)
{
	// DEBUG_PRINT("opening file: pathname=%s, decrypt=%d", pathname, decrypt);
    // ファイル名の scheme で、どのファイルを開くべきかが決まる。
    if(!strncmp(pathname, "file://", 7)) {
        // ファクトリには scheme を除いたパスが渡される。
        CAndroidReadFileStream * pRds = CAndroidReadFileStream::openStream(pathname + 7, 0);
        if (decrypt) { pRds->decryptSetup((const u8*)pathname + 7); }
        return pRds;
    }
    if(!strncmp(pathname, "asset://", 8)) {
        CAndroidReadFileStream * pRds = CAndroidReadFileStream::openAssets(pathname, 0);
        if (decrypt) { pRds->decryptSetup((const u8*)pathname + 8); }
        return pRds;
    }

    if(!strncmp(pathname, "socket://", 9)) {
        CSockReadStream * pRds = CSockReadStream::openStream(pathname + 9);
        logging("Socket: %s (%p)", pathname, pRds);
        return pRds;
    }

    if(!strncmp(pathname, "http:", 5)) {
        return 0;
    }
    if(!strncmp(pathname, "https:", 6)) {
        return 0;
    }
    return 0;
}

void *
CAndroidRequest::loadAudio(const char * url, bool is_se)
{
	const char * path = (!strncmp(url, "asset://", 8)) ? url : (url + 7);
	DEBUG_PRINT("loading audio: %s", path);
	KLBOpenSLSoundAsset * audio = KLBOpenSLEngine::getInstance()->load(path, is_se);
	return audio;
}

bool
CAndroidRequest::preLoad(void * handle)
{
	if(!handle) return false;
	KLBOpenSLSoundAsset * audio = (KLBOpenSLSoundAsset *)handle;
	audio->prepare(-1);
	return true;
}

bool
CAndroidRequest::setBufSize(void *handle, int level)
{
    // TODO
    return true;
}

void
CAndroidRequest::playAudio(void *handle, s32 _milisec, float _tgtVol, float _startVol)
{
	if(!handle) return;
	KLBOpenSLSoundAsset * audio = (KLBOpenSLSoundAsset *)handle;
	audio->play(KLBOpenSLSoundAsset::ONCE, _milisec, _tgtVol, _startVol);
	// TODO:
}

void
CAndroidRequest::stopAudio(void *handle, s32 _milisec, float _tgtVol)
{
	if(!handle) return;
	//KLBOpenSLEngine::getInstance()->discardCorrespondingSoundHandles((KLBOpenSLSoundAsset *)handle);
	KLBOpenSLEngine::getInstance()->stopCorrespondingSoundHandles((KLBOpenSLSoundAsset *)handle, false, _tgtVol, _milisec);
}

void
CAndroidRequest::setMasterVolume(float volume, bool SEmode)
{
	DEBUG_PRINT("AUDIO; setting master volume. seMode=%d, vol=%f", SEmode, volume);
	KLBOpenSLEngine::getInstance()->setMasterVolume(volume, SEmode);
}

void
CAndroidRequest::setAudioVolume(void *handle, float volume)
{
    if(!handle) return;
	KLBOpenSLEngine::getInstance()->setVolumeOnCorrespondingSoundHandles((KLBOpenSLSoundAsset *)handle, volume);
}

void
CAndroidRequest::setAudioPan(void *handle, float pan)
{
	return;
	if(!handle) return;
	/*
	CAndroidAudio * audio = (CAndroidAudio *)handle;
	audio->setPan(pan);
	*/
}

void
CAndroidRequest::releaseAudio(void * handle)
{
	if(!handle) return;
	KLBOpenSLSoundAsset * audio = (KLBOpenSLSoundAsset *)handle;
	REPORT_METRICS("before closing audio asset");
	delete audio;
	REPORT_METRICS("after closing audio asset");
}

void
CAndroidRequest::pauseAudio(void * handle, s32 _milisec, float _tgtVol)
{
	if(!handle) return;
	KLBOpenSLEngine::getInstance()->pauseCorrespondingSoundHandles((KLBOpenSLSoundAsset *)handle, false, _tgtVol, _milisec);
}

void
CAndroidRequest::resumeAudio(void * handle, s32 _milisec, float _tgtVol)
{
	if(!handle) return;
	KLBOpenSLEngine::getInstance()->resumeCorrespondingSoundHandles((KLBOpenSLSoundAsset *)handle, false, _tgtVol, _milisec);
}

void
CAndroidRequest::seekAudio(void * handle, s32 millisec)
{
    // TODO
}

s32
CAndroidRequest::tellAudio(void * handle)
{
	if(!handle) return 0;
	return KLBOpenSLEngine::getInstance()->tellCorrespondingSoundHandle((KLBOpenSLSoundAsset *)handle);
}

s32
CAndroidRequest::totalTimeAudio(void * handle)
{
    if(!handle) return 0;
	KLBOpenSLSoundAsset * audio = (KLBOpenSLSoundAsset *)handle;
	return audio->totalPlayTime();
}

s32
CAndroidRequest::getState(void * handle)
{
	if(!handle) return 0;
	return KLBOpenSLEngine::getInstance()->getStateOfCorrespondingSoundHandle((KLBOpenSLSoundAsset *)handle);
}

//! サウンドとミュージックの並行処理タイプ設定
void
CAndroidRequest::setAudioMultiProcessType( s32 _processType )
{
	switch( _processType )
	{
		case IClientRequest::E_SOUND_MULTIPROCESS_MUSIC_CUT:
		case IClientRequest::E_SOUND_MULTIPROCESS_SOUND_CUT:
		case IClientRequest::E_SOUND_MULTIPROCESS_SOUND_BGM_CUT:
			KLBOpenSLEngine::getInstance()->setAudioMultiProcessType(_processType);
			break;
	}
}

//! サウンドの割り込み処理をエンジン側で制御するかどうか
void CAndroidRequest::setPauseOnInterruption(bool _bPauseOnInterruption)
{
    // TODO:2013/06/10 現在はiOSのみ対応が必要なのでAndroid側は特に対応なし
}

#define ANDROID_ALARM_ELAPSED_REALTIME (3)
inline void CAndroidRequest::getElapsedTimeSpec(struct timespec * ts)
{
	// ref: AOSP source code; frameworks/native/libs/utils/SystemClock.cpp
	int fd = open("/dev/alarm", O_RDONLY);
	if (fd == -1) {
		klb_assertAlways("failed to claim alarm counter.");
	}

	int result = ioctl(fd, _IOW('a', 4 | (ANDROID_ALARM_ELAPSED_REALTIME << 4), struct timespec), ts);

	close(fd);

	if (result == -1) {
		klb_assertAlways("failed to fetch alarm clock via ioctl");
	}
}

inline s64 CAndroidRequest::getElapsedNanoTime(void)
{
	struct timespec ts;
	getElapsedTimeSpec(&ts);
	return ((s64)ts.tv_sec * 1000000000) + ts.tv_nsec;
}

/*!
    @brief  経過時間を取得(sec)
    @param[in]  void
    @return     s64     経過時間(sec)
 */
s64 CAndroidRequest::getElapsedTime(void)
{
	struct timespec ts;
	getElapsedTimeSpec(&ts);
	return (s64)ts.tv_sec;
}

void
CAndroidRequest::setFadeParam(void* _handle, float _tgtVol, u32 _millisec)
{
	if(!_handle) return;
	KLBOpenSLEngine::getInstance()->setFadeParamOnCorrespondingSoundHandles((KLBOpenSLSoundAsset *)_handle, _tgtVol, _millisec);
}

//! フォントオブジェクト取得

bool CAndroidRequest::registerFont(const char* logicalName, const char* physFile, bool default_) {
	return FontObject::registerFont(logicalName, physFile, default_);
}

void *
CAndroidRequest::getFont(int size, const char * fontName, float* pAscent)
{
	FontObject* pFont = FontObject::createFont(fontName, size);
	if (pFont) {
		// pFont->
		if (pAscent) {
			*pAscent = pFont->getAscent();
		}
	}
	return pFont;
}

void *
CAndroidRequest::getFontSystem(int size, const char * fontName)
{
	CAndroidFont * pFont = new CAndroidFont(size, fontName);
	return (void *)pFont;
}

//! フォントオブジェクト破棄
void
CAndroidRequest::deleteFont(void * pFont)
{
	FontObject::destroyFont((FontObject*)pFont);
}

void
CAndroidRequest::deleteFontSystem(void * pFont)
{
	CAndroidFont * p_cFont = (CAndroidFont *)pFont;
	delete p_cFont;
}

//! フォントテクスチャ描画
bool
CAndroidRequest::renderText(const char* utf8String, void * pFont, u32 color,	//!< 描画する文字列とフォントの指定
							u16 width, u16 height, u8 * pBuffer8888,    		//!< 描画対象とするテクスチャバッファとそのピクセルサイズ
							s16 stride, s16 base_x, s16 base_y, bool use4444)         		//!< baseline起点とするテクスチャ内の位置
{
	FontObject* pObjFont = (FontObject*)pFont;
	if (pObjFont) {
		pObjFont->renderText(base_x, base_y, utf8String, pBuffer8888, color, width, height, stride, use4444);
	}
	return true;
}

extern "C" {

bool
CAndroidRequest::getTextInfo(const char* utf8String, void * pFont, STextInfo* pReturnInfo)
{
	FontObject* pF = (FontObject*)pFont;
	if (pF) {
		pF->getTextInfo(utf8String, pReturnInfo);
	} else {
		pReturnInfo->ascent		= 0.0f;
		pReturnInfo->descent	= 0.0f;
		pReturnInfo->bottom		= 0.0f;
		pReturnInfo->top		= 0.0f;
		pReturnInfo->width		= 0.0f;
		pReturnInfo->height		= 0.0f;
	}
	return true;
}

void*
CAndroidRequest::getGLExtension(const char*)
{
	return 0;
}

const char *
CAndroidRequest::getFullPath(const char * assetPath,bool* isReadOnly)
{
    CAndroidPathConv& pathconv = CAndroidPathConv::getInstance();

    // ファイル名の scheme で、どのファイルを開くべきかが決まる。
    if(!strncmp(assetPath, "file://", 7)) {
        return pathconv.fullpath(assetPath + 7,0,isReadOnly);
    }
    // scheme が asset であれば、作るのは CiOSReadFileStream だが、EXTERN -> INSTALL の順で検索する。
    if(!strncmp(assetPath, "asset://", 8)) {
        return pathconv.fullpath(assetPath,0,isReadOnly);
    }
    return 0;
}

const char *
CAndroidRequest::getPlatform()
{
	return m_platform;
}

IWidget *
CAndroidRequest::createControl(IWidget::CONTROL type, int id, const char * caption, int x, int y, int width, int height, ...)
{
	IWidget * pWidget = 0;
	va_list ap;
	va_start(ap, height);
	switch(type)
	{
	case IWidget::TEXTBOX:
	case IWidget::PASSWDBOX:
	{
		int maxlen = va_arg(ap, int);
		CAndroidTextWidget * pTextWidget = new CAndroidTextWidget(this);
		if(!pTextWidget || !pTextWidget->create(type, id, caption, x, y, width, height)) {
			delete pTextWidget;
			pTextWidget = 0;
		} else {
			pTextWidget->setMaxlen(maxlen);
    }
		pWidget = pTextWidget;
		break;
	}
	case IWidget::WEBVIEW:
	case IWidget::WEBNOJUMP:
	{
		const char * token  = va_arg(ap, const char *);
		const char * region = va_arg(ap, const char *);
		const char * client = va_arg(ap, const char *);
		const char * cKey   = va_arg(ap, const char *);
		const char * appId  = va_arg(ap, const char *);
		const char * userId = va_arg(ap, const char *);

		CAndroidWebWidget * pWebWidget = new CAndroidWebWidget(this);
		if(!pWebWidget || !pWebWidget->create(type, id, caption, x, y, width, height,
												token, region, client, cKey, appId, userId)) {
			delete pWebWidget;
			pWebWidget = 0;
		}
		pWidget = pWebWidget;
		break;
	}
	case IWidget::MOVIEPLAYER:
	{
		CAndroidMovieWidget * pMovieWidget = new CAndroidMovieWidget(this);
		if(!pMovieWidget || !pMovieWidget->create(type, id, caption, x, y, width, height)) {
			delete pMovieWidget;
			pMovieWidget = 0;
		}
		pWidget = pMovieWidget;
		break;
	}
	case IWidget::ACTIVITYINDICATOR:
	{
		CAndroidActivityIndicator * actI = new CAndroidActivityIndicator(this);
		if(!actI || !actI->create(type, id, caption, x, y, width, height)) {
			delete actI;
			actI = 0;
		}
		pWidget = actI;
		break;
	}
	}
	va_end(ap);
	return pWidget;
}

void
CAndroidRequest::destroyControl(IWidget * pControl)
{
	delete pControl;
}

bool
CAndroidRequest::callApplication(APP_TYPE type, ...)
{

    bool result = true;

    va_list ap;
    va_start(ap, type);
	switch (type)
	{
	// メーラー起動
	case IPlatformRequest::APP_MAIL:
		{
			const char * addr = va_arg(ap, const char *);
			const char * subject = va_arg(ap, const char *);
			const char * body = va_arg(ap, const char *);
			jvalue value;
			callJavaMethod(value, "startMailer", 'V', "SSS" , addr , subject , body );
		}
		break;

	// ブラウザ起動
	case IPlatformRequest::APP_BROWSER:
		{
			const char * url = va_arg(ap, const char *);
			jvalue value;
			callJavaMethod(value, "startBrowser", 'V', "S" , url );
		}
		break;

	// アップデート
	case IPlatformRequest::APP_UPDATE:
		result = false;
		break;

	default:
		result = false;
		break;
	}
	va_end(ap);
	return result;

}

void *
CAndroidRequest::createThread(s32 (*thread_func)(void * hThread, void * data), void * data)
{
	PF_THREAD * thread = new PF_THREAD;
	if(!thread) return 0;
	thread->data = data;
	thread->thread_func = thread_func;
	thread->result = 0;
	pthread_create(&(thread->id), 0, ThreadProc, thread);
	return thread;
}

void
CAndroidRequest::exitThread(void * hThread, s32 status)
{
	PF_THREAD * pThread = (PF_THREAD *)hThread;
	longjmp(pThread->jmp, status);
}

bool
CAndroidRequest::watchThread(void * hThread, s32 * status)
{
	PF_THREAD * pThread = (PF_THREAD *)hThread;
	if(pthread_kill(pThread->id, 0) != ESRCH) {
		return true;
	}
	*status = pThread->result;
	return false;
}

void
CAndroidRequest::deleteThread(void * hThread)
{
	PF_THREAD * pThread = (PF_THREAD *)hThread;
	pthread_join(pThread->id, 0);
	delete pThread;
}

void
CAndroidRequest::breakThread(void * hThread)
{
	PF_THREAD * pThread = (PF_THREAD *)hThread;
	pthread_kill(pThread->id, SIGKILL);
}

void *
CAndroidRequest::ThreadProc(void * data)
{
	PF_THREAD * pThread = (PF_THREAD *)data;
	if(!(pThread->result = setjmp(pThread->jmp))) {
		pThread->result = (pThread->thread_func)(pThread, pThread->data);
	}
	return 0;
}

int
CAndroidRequest::genUserID(char * retBuf, int maxlen)
{
	jvalue value;
	callJavaMethod(value, "genUserID", 'S', "");
	jstring jstr = (jstring)value.l;
	const char * str = CJNI::getJNIEnv()->GetStringUTFChars(jstr, NULL);
	int i = 0;
	for(i = 0; str[i] && i < maxlen - 1; i++) retBuf[i] = str[i];
	retBuf[i] = 0;
	CJNI::getJNIEnv()->ReleaseStringUTFChars(jstr, str);
	return i;
}

int
CAndroidRequest::genUserPW(const char * salt, char * retBuf, int maxlen)
{
	char buf[1024];
	time_t tm;
	int rnd = rand();
	time(&tm);
	sprintf(buf, "%d.%d.%s", rnd, (u32)tm, salt);
	return sha512(buf, retBuf, maxlen);
}

bool
CAndroidRequest::readyDevID()
{
	if(m_regId) return true;	// 既に取得していれば問題無し。
	bool bResult = false;
	jvalue ret;
	callJavaMethod(ret, "readyRegID", 'S', "");
	JNIEnv * env = CJNI::getJNIEnv();
	const char *bytes = env->GetStringUTFChars((jstring)ret.l, NULL);
	// DEBUG_PRINT("readyDevID ret.l:%s", (char*)ret.l);
	// DEBUG_PRINT("readyDevID bytes:%s", bytes);
	if(bytes) {
		int len = strlen(bytes);
		if(len > 0) {
			char * buf = new char [len + 1];
			strcpy(buf, bytes);
			m_regId = (const char *)buf;
			bResult = true;
		}
		env->ReleaseStringUTFChars((jstring)ret.l, bytes);
	}
	// DEBUG_PRINT("readyDevID ret:%d", bResult);
	return bResult;
}

int
CAndroidRequest::getDevID(char * retBuf, int maxlen)
{
	if(!m_regId) return 0;

	int i;
	for(i = 0; m_regId[i] && i < maxlen - 1; i++) retBuf[i] = m_regId[i];
	retBuf[i] = 0;
	return i;
}

bool
CAndroidRequest::setSecureDataID(const char * service_name, const char * user_id)
{
	jvalue ret;
	callJavaMethod(ret, "setKeyChain", 'Z', "SSS", service_name, "user_id", user_id);
	return (bool)ret.z;
}

bool
CAndroidRequest::setSecureDataPW(const char * service_name, const char * passwd)
{
	jvalue ret;
	callJavaMethod(ret, "setKeyChain", 'Z', "SSS", service_name, "passwd", passwd);
	return (bool)ret.z;

}

int
CAndroidRequest::getSecureDataID(const char * service_name, char * retBuf, int maxlen)
{
	jvalue ret;
	callJavaMethod(ret, "getKeyChain", 'S', "SS", service_name, "user_id");
	JNIEnv * env = CJNI::getJNIEnv();
	const char *bytes = env->GetStringUTFChars((jstring)ret.l, NULL);
	int i;
	for(i = 0; bytes[i] && i < maxlen - 1; i++) retBuf[i] = bytes[i];
	retBuf[i] = 0;

	env->ReleaseStringUTFChars((jstring)ret.l, bytes);

	return i;
}

int
CAndroidRequest::getSecureDataPW(const char * service_name, char * retBuf, int maxlen)
{
	jvalue ret;
	callJavaMethod(ret, "getKeyChain", 'S', "SS", service_name, "passwd");
	JNIEnv * env = CJNI::getJNIEnv();
	const char *bytes = env->GetStringUTFChars((jstring)ret.l, NULL);
	int i;
	for(i = 0; bytes[i] && i < maxlen - 1; i++) retBuf[i] = bytes[i];
	retBuf[i] = 0;

	env->ReleaseStringUTFChars((jstring)ret.l, bytes);

	return i;
}
    
bool
CAndroidRequest::delSecureDataID(const char * service_name)
{
	jvalue ret;
	callJavaMethod(ret, "delKeyChain", 'Z', "SS", service_name,"user_id");
	return (bool)ret.z;
}

bool
CAndroidRequest::delSecureDataPW(const char * service_name)
{
	jvalue ret;
	callJavaMethod(ret, "delKeyChain", 'Z', "SS", service_name,"passwd");
	return (bool)ret.z;
}

void
CAndroidRequest::startAlertDialog( const char* title , const char* message )
{
	jvalue ret;
	callJavaMethod(ret, "startAlertDialog", 'V', "SS", title , message);
}

int
CAndroidRequest::sha512(const char * string, char * buf, int maxlen)
{
	JNIEnv * env = CJNI::getJNIEnv();
	jstring jstr = env->NewStringUTF(string);
	jclass cls_pfif = env->FindClass(JNI_LOAD_PATH);
	jmethodID methodID = env->GetStaticMethodID(cls_pfif, "sha512", "(Ljava/lang/String;)[B");
	jbyteArray jbarr = (jbyteArray)env->CallStaticObjectMethod(cls_pfif, methodID, jstr);
	jbyte* digest = env->GetByteArrayElements(jbarr, NULL);

	int len = env->GetArrayLength(jbarr);
	char * ptr = buf;
	for(int i = 0; i < len && i * 2 < maxlen - 1; i++) {
		sprintf(ptr, "%02x", 0xff & (int)digest[i]);
		ptr += strlen(ptr);
	}
	env->ReleaseByteArrayElements(jbarr, digest, 0);

	CJNI::getJNIEnv()->DeleteLocalRef(jstr);
	CJNI::getJNIEnv()->DeleteLocalRef(cls_pfif);
	//CJNI::getJNIEnv()->DeleteLocalRef(methodID);
	CJNI::getJNIEnv()->DeleteLocalRef(jbarr);
	//CJNI::getJNIEnv()->DeleteLocalRef(digest);

	return strlen(buf);
}

bool
CAndroidRequest::callJavaMethod(jvalue& ret, const char * method, const char rettype, const char * form, ...)
{
	using namespace std;
	//引数の数を数える
	int count = 0;
	for(const char * ptr = form; *ptr; ptr++) {
		if(*ptr != ' ') count++;
	}
	//DEBUG_PRINT("args count: %d", count);
	JNIEnv* env = CJNI::getJNIEnv();

	vector<jstring> jstrs;
	jvalue * arrArgs = NULL;
	jmethodID methodID = 0;
	char signature[1024];
	char * wp = signature;
	strcpy(wp, "(");
	wp += strlen(wp);
	if( count > 0 )
	{
		arrArgs = new jvalue [ count ];

		va_list ap;
		va_start(ap, form);
		count = 0;
		for(const char * ptr = form; *ptr; ptr++) {
			if(*ptr == ' ')continue;
			switch(*ptr) {
			case 'Z':
			{
				bool bval = (bool)va_arg(ap, int);
				arrArgs[count++].z = (jboolean)bval;
				strcpy(wp, "Z");
				wp += strlen(wp);
				break;
			}
			case 'C':
			{
				char cval = (char)va_arg(ap, int);
				arrArgs[count++].c = (jchar)cval;
				strcpy(wp, "C");
				wp += strlen(wp);
				break;
			}
			case 'I':
			{
				int ival = va_arg(ap, int);
				arrArgs[count++].i = (jint)ival;
				strcpy(wp, "I");
				wp += strlen(wp);
				break;
			}
			case 'F':
			{
				float fval = (float)va_arg(ap, double);
				arrArgs[count++].f = (jfloat)fval;
				strcpy(wp, "F");
				wp += strlen(wp);
				break;
			}
			case 'D':
			{
				double dval = va_arg(ap, double);
				arrArgs[count++].d = (jdouble)dval;
				strcpy(wp, "D");
				wp += strlen(wp);
				break;
			}
			case 'S':
			{
				const char * string = va_arg(ap, const char *);
				jstring jstr = env->NewStringUTF(string);
				arrArgs[count++].l = (jobject)jstr;
				strcpy(wp, "Ljava/lang/String;");
				wp += strlen(wp);
				jstrs.push_back(jstr);
				break;
			}
			default:
			{
				klb_assertAlways("wrong JNI signature. unknown type: %c", *ptr);
				break;
			}
			}
		}
		va_end(ap);
	}
	strcpy(wp, ")");
	wp += strlen(wp);
	jclass cls_pfif = env->FindClass(JNI_LOAD_PATH);

	switch(rettype) {
	case 'V':
	{
		strcpy(wp, "V");
		methodID = env->GetStaticMethodID(cls_pfif, method, signature);
		env->CallStaticVoidMethodA(cls_pfif, methodID, arrArgs);
		break;
	}
	case 'Z':
	{
		strcpy(wp, "Z");
		methodID = env->GetStaticMethodID(cls_pfif, method, signature);
		ret.z = env->CallStaticBooleanMethodA(cls_pfif, methodID, arrArgs);
		break;
	}
	case 'I':
	{
		strcpy(wp, "I");
		DEBUG_PRINT("return I type method call.:<%s>", signature);
		methodID = env->GetStaticMethodID(cls_pfif, method, signature);
		ret.i = env->CallStaticIntMethodA(cls_pfif, methodID, arrArgs);
		DEBUG_PRINT("return I type method call finished.");
		break;
	}
	case 'F':
	{
		strcpy(wp, "F");
		methodID = env->GetStaticMethodID(cls_pfif, method, signature);
		ret.f = env->CallStaticFloatMethodA(cls_pfif, methodID, arrArgs);
		break;
	}
	case 'D':
	{
		strcpy(wp, "D");
		methodID = env->GetStaticMethodID(cls_pfif, method, signature);
		ret.d = env->CallStaticDoubleMethodA(cls_pfif, methodID, arrArgs);
		break;
	}
	case 'S':
	{
		strcpy(wp, "Ljava/lang/String;");
		methodID = env->GetStaticMethodID(cls_pfif, method, signature);
		//DEBUG_PRINT("static methodID:%d", methodID);
		if( methodID > 0 ) {
			ret.l = env->CallStaticObjectMethodA(cls_pfif, methodID, arrArgs);
			break;
		}

		// staticMethodから見つからなかった場合はstaticではないMethodから検索
		methodID = env->GetMethodID(cls_pfif, method, signature);
		//DEBUG_PRINT("public methodID:%d", methodID);
		if( methodID > 0 ) {
			ret.l = env->CallObjectMethodA(cls_pfif, methodID, arrArgs);
			break;
		}
		break;
	}
	}

	// 文字列を引数として渡した場合はそれを解放する。
	count = 0;
	for(const char * ptr = form; *ptr; ptr++) {
		if(*ptr == ' ')continue;
		if(*ptr != 'S') {
			count++;
			continue;
		}
		// 平成25年8月14日(水)
		// jstringをchar*に変換しているわけではないからいらないのでは.
		// env->ReleaseStringUTFChars((jstring)arrArgs[count].l, 0);
		count++;
	}
	// 引数として使用した配列を解放する
	if( arrArgs != NULL ) {
		delete [] arrArgs;
	}

	env->DeleteLocalRef(cls_pfif);
	vector<jstring>::iterator it = jstrs.begin();
	while (it != jstrs.end()) {
		env->DeleteLocalRef(*it);
		++it;
	}
	//CJNI::getJNIEnv()->DeleteLocalRef(arrArgs);
	//CJNI::getJNIEnv()->DeleteLocalRef(methodID);

	return true;
}


JNIEXPORT jboolean JNICALL APP_FUNC(initSequence)
  (JNIEnv *env, jobject obj, jint j_width, jint j_height, jstring j_strPath,
		  jstring j_model , jstring j_brand, jstring j_board, jstring j_version, jstring j_tz)
{
	const char * strPath  = env->GetStringUTFChars(j_strPath, 0);
	const char * strModel = env->GetStringUTFChars(j_model, 0);
	const char * strBrand = env->GetStringUTFChars(j_brand, 0);
	const char * strBoard = env->GetStringUTFChars(j_board, 0);
	const char * strVersion = env->GetStringUTFChars(j_version, 0);
	const char * strTZ = env->GetStringUTFChars(j_tz, 0);

#if DEBUG
	char buf[1024];
	sprintf(buf, "%s|%s|%s|%s|%s|%s", strPath, strModel, strBrand, strBoard, strVersion, strTZ);
    __android_log_write(ANDROID_LOG_DEBUG, "Proxy", buf);
#endif

	int width = j_width;
	int height = j_height;

	CAndroidRequest * pRequest = new CAndroidRequest(strModel, strBrand, strBoard, strVersion, strTZ);
	CPFInterface& pfif = CPFInterface::getInstance();

#if DEBUG
    __android_log_write(ANDROID_LOG_DEBUG, "Proxy", "platform plugin created.");
#endif

	CJNI::setJNIEnv(env);	//　これでC++コードの中でも簡易版 SoundPool が使える。
#if DEBUG
    __android_log_write(ANDROID_LOG_DEBUG, "Proxy", "JNIEnv initialize.");
#endif

    pRequest->init();
	pRequest->setHomePath(strPath);

#if DEBUG
    __android_log_write(ANDROID_LOG_DEBUG, "Proxy", "platform plugin created.");
#endif

	pfif.setPlatformRequest(pRequest);

	// サウンドシステム初期化
	KLBOpenSLEngine::getInstance();
#if DEBUG
	KLBPlatformMetrics::getInstance()->start();
#endif

	DEBUG_PRINT("initSequence() start!");
	DEBUG_PRINT("initSequence(): platform = [%s]", pfif.platform().getPlatform());

	GameSetup();

#if DEBUG
    __android_log_write(ANDROID_LOG_DEBUG, "Proxy", "GameStartup() finished.");
#endif

	// 起動シーケンス順に呼び出す。この呼び出し順は厳守されねばならない。
	pfif.client().setScreenInfo(true, width, height);
#if DEBUG
    __android_log_write(ANDROID_LOG_DEBUG, "Proxy", "setScreenInfo() finished.");
#endif

    pfif.client().setFilePath(0);
#if DEBUG
    __android_log_write(ANDROID_LOG_DEBUG, "Proxy", "setFilePath() finished.");
	DEBUG_PRINT("initSequence() call initGame()");
#endif
	pfif.client().initGame();
#if DEBUG
    __android_log_write(ANDROID_LOG_DEBUG, "Proxy", "initGame() finished.");
	DEBUG_PRINT("initSequence() initGame() finish.");
#endif

        env->ReleaseStringUTFChars(j_strPath, strPath);
        env->ReleaseStringUTFChars(j_model, strModel);
        env->ReleaseStringUTFChars(j_brand, strBrand);
        env->ReleaseStringUTFChars(j_board, strBoard);
        env->ReleaseStringUTFChars(j_version, strVersion);
        env->ReleaseStringUTFChars(j_tz, strTZ);

	// 初期化終了。
	return (jboolean)true;
}

/*
 * Class:     klb_android_GameEngine_PFInterface
 * Method:    frameFlip
 * Signature: (I)V
 */
JNIEXPORT void JNICALL APP_FUNC(frameFlip)
  (JNIEnv *env, jobject obj, jint j_deltaT)
{
	u32 deltaT = j_deltaT;

#if defined(DEBUG) || defined(DEBUG_PERFORMANCE)
	s64 frameProcStart = CAndroidRequest::getInstance()->nanotime();
#endif

	CPFInterface::getInstance().client().frameFlip(deltaT);

#if defined(DEBUG) || defined(DEBUG_PERFORMANCE)
	KLBPlatformMetrics::getInstance()->logFrameSummary(deltaT, frameProcStart);
#endif
}

/*
 * Class:     klb_android_GameEngine_PFInterface
 * Method:    finishGame
 * Signature: ()V
 */
JNIEXPORT void JNICALL APP_FUNC(finishGame)
  (JNIEnv *env, jobject obj)
{
	CPFInterface::getInstance().client().finishGame();

	// サウンドシステム終了
	KLBOpenSLEngine::terminate();

	return;
}

JNIEXPORT void JNICALL APP_FUNC(inputPoint)
  (JNIEnv *env, jobject obj, jint j_id, jint j_type, jint j_x, jint j_y)
{
	static IClientRequest::INPUT_TYPE type[] = {
			IClientRequest::I_CLICK,
			IClientRequest::I_DRAG,
			IClientRequest::I_RELEASE
	};
	CPFInterface::getInstance().client().inputPoint(j_id, type[j_type], j_x, j_y);
}

JNIEXPORT void JNICALL APP_FUNC(inputDeviceKey)
  (JNIEnv *env, jobject obj, jint keyId, jchar eventType)
{
	CPFInterface::getInstance().client().inputDeviceKey(keyId, eventType);
}

JNIEXPORT void JNICALL APP_FUNC(rotateScreenOrientation)
  (JNIEnv *env, jobject obj, jint j_origin, jint j_width, jint j_height)
{
	CPFInterface& pfif = CPFInterface::getInstance();
	if(!pfif.isClient()) return;
	int width = j_width;
	int height = j_height;
	int origin = j_origin;
	IClientRequest::SCRMODE mode = (width > height) ? IClientRequest::LANDSCAPE : IClientRequest::PORTRAIT;

	static IClientRequest::ORIGIN arr_origin[] = {
			IClientRequest::LEFT_TOP,
			IClientRequest::LEFT_BOTTOM,
			IClientRequest::RIGHT_BOTTOM,
			IClientRequest::RIGHT_TOP
	};

	bool bResult = pfif.client().reportScreenRotation(arr_origin[origin], mode);
	if(bResult) {
		pfif.client().changeScreenInfo(arr_origin[origin], width, height);
	}
}

JNIEXPORT void JNICALL APP_FUNC(toNativeSignal)
  (JNIEnv *env, jobject obj, jint j_cmd, jint j_param)
{
	CPFInterface& pfif = CPFInterface::getInstance();

	// porting layer class の instance を取得
	CAndroidRequest * instance = CAndroidRequest::getInstance();
	if(!instance) return;

	instance->nativeSignal((int)j_cmd, (int)j_param);
}

JNIEXPORT jint JNICALL APP_FUNC(getGLVersion)
  (JNIEnv * env, jobject obj)
{
#ifdef OPENGL2
	return 2;
#else
	return 1;
#endif
}

JNIEXPORT void  JNICALL APP_FUNC(resetViewport)
  (JNIEnv * env, jobject obj)
{
	CPFInterface& pfif = CPFInterface::getInstance();
	if(!pfif.isClient()) return;
	CPFInterface::getInstance().client().resetViewport();
}

// アプリにおけるバックグラウンドに行った際の動作
JNIEXPORT void  JNICALL APP_FUNC(onActivityPause) (void)
{
	DEBUG_PRINT("AUDIO; onPause..");
	KLBOpenSLEngine::getInstance()->onActivityPause();

    // ゲームのポーズ
	CPFInterface& pfif = CPFInterface::getInstance();
	if(!pfif.isClient()) return;
	pfif.client().pauseGame(true);
}

// アプリに置けるフォアグラウンドに行った際の動作
JNIEXPORT void  JNICALL APP_FUNC(onActivityResume) (void)
{
    // ゲームのポーズ復帰
	CPFInterface& pfif = CPFInterface::getInstance();
	if(!pfif.isClient()) return;
	pfif.client().pauseGame(false);

	pfif.client().controlEvent(IClientRequest::E_RESUME, 0, 0, 0, 0, 0);

	DEBUG_PRINT("AUDIO; onResume..");
	KLBOpenSLEngine::getInstance()->onActivityResume();
}

// WebViewの動作コールバック
JNIEXPORT void  JNICALL APP_FUNC(WebViewControlEvent) ( JNIEnv *env, jobject obj, jobject _pWeb, jint _flg )
{
	CAndroidWebWidget * pWidget = CAndroidWebWidget::get_webViewItem(_pWeb);
	CPFInterface& pfif = CPFInterface::getInstance();
	int status = -1;
	if(!pfif.isClient()) return;

	enum LOCAL_WEBEVENT_TYPE
	{
		E_DIDSTARTLOADWEB = 0,
		E_DIDLOADENDWEB,
		E_FAILEDLOADWEB,
		E_URLJUMP,
	};

	switch((int)_flg)
	{
		case E_DIDSTARTLOADWEB:
			status = IClientRequest::E_DIDSTARTLOADWEB;
			break;
		case E_DIDLOADENDWEB:
			status = IClientRequest::E_DIDLOADENDWEB;
			break;
		case E_FAILEDLOADWEB:
			status = IClientRequest::E_FAILEDLOADWEB;
			break;
		case E_URLJUMP:
		{
			size_t len = pWidget->getTmpTextLength();
			if(len > 0)
			{
				char* pTmpBuff = NULL;
				pTmpBuff = KLBNEWA(char, len + 1);
				pWidget->getTmpText(pTmpBuff, len + 1);
				pWidget->setTmpString(pTmpBuff);
				KLBDELETEA(pTmpBuff);
				status = IClientRequest::E_URLJUMP;
			}
			else
			{
				// リンク先が無ければreturn
				return;
			}
			break;
		}
		default:
			return; // 値が想定外なのでリターン
	}
	CPFInterface::getInstance().client().controlEvent((IClientRequest::EVENT_TYPE)status, pWidget, 0, 0, 0, 0);
}

JNIEXPORT void	JNICALL APP_FUNC(clientControlEvent)
	(JNIEnv * env, jobject obj, jint j_type, jint j_widget, jstring j_data_1, jstring j_data_2)
{
	IClientRequest& cli = CPFInterface::getInstance().client();
	// とりあえずストア関係だけ //
	static IClientRequest::EVENT_TYPE event_array[] =
	{
		IClientRequest::E_STORE_BAD_ITEMID,         // アイテムIDが無効
		IClientRequest::E_STORE_GET_PRODUCTS, // ProductListの取得.
		IClientRequest::E_STORE_PURCHASHING,        // 購入処理中
		IClientRequest::E_STORE_PURCHASHED,         // 購入処理終了
		IClientRequest::E_STORE_FAILED,             // 購入処理失敗
		IClientRequest::E_STORE_RESTORE,            // リストア終了
		IClientRequest::E_STORE_RESTORE_FAILED,     // リストア失敗
		IClientRequest::E_STORE_RESTORE_COMPLETED,  // 全リストア終了
	};

	const char * char_1 = env->GetStringUTFChars(j_data_1, NULL);
    const char * char_2 = env->GetStringUTFChars(j_data_2, NULL);
    // FIXME ↑の２つは ReleaseStringUTFChars されてないけど影響範囲が広いのでとりあえず後回し

    size_t len_1 = strlen(char_1);
    size_t len_2 = strlen(char_2);

    len_1 = len_1 == 0 ? 0 : len_1 + 1;
    len_2 = len_2 == 0 ? 0 : len_2 + 1;

    printf("clientEvent %d\n", j_type);

	cli.controlEvent(event_array[j_type], 0, len_1, (void *)char_1, len_2, (void *)char_2);
}

JNIEXPORT void JNICALL APP_FUNC(jniOnLoad) (JavaVM* vm, void* reserved)
{
	CJNI::setJavaVM(vm);
}

// onPauseがコールされてからonDrawFrameが初めてコールされた際の処理 //
JNIEXPORT void  JNICALL APP_FUNC(clientResumeGame) (void)
{
	CPFInterface& pfif = CPFInterface::getInstance();
	if(!pfif.isClient()) return;

	pfif.client().pauseGame(false);

	pfif.client().controlEvent(IClientRequest::E_PAUSE, 0, 0, 0, 0, 0);
	pfif.client().frameFlip(1);    // 1フレーム分まわす。経過時間は 1[ms] という扱い。
//	pfif.client().controlEvent(IClientRequest::E_RESUME, 0, 0, 0, 0, 0);

	pfif.client().pauseGame(true);
}

//================================================
// 課金
void
CAndroidRequest::initStoreTransactionObserver()
{
	jvalue value;
	callJavaMethod(value, "billingInit", 'V', "");
}

void
CAndroidRequest::releaseStoreTransactionObserver()
{
	jvalue value;
	callJavaMethod(value, "billingTerminate", 'V', "");
}

void
CAndroidRequest::buyStoreItems(const char * item_id)
{
	// 購入処理
	jvalue value;
	callJavaMethod(value, "billingBuyItem", 'V', "S" , item_id);
}

void
CAndroidRequest::getStoreProducts(const char* json, bool currency_mode)
{
	// リスト問い合わせ
	jvalue value;
	callJavaMethod(value, "billingGetProducts", 'V', "S" , json);
}

void
CAndroidRequest::finishStoreTransaction(const char* receipt)
{
	jvalue value;
	callJavaMethod(value, "billingConsume", 'V', "S", receipt);
}

//================================================
// mutex
void* CAndroidRequest::allocMutex	()
{
	pthread_mutex_t* pSection = new pthread_mutex_t();
	if (pSection) {
		if (pthread_mutex_init(pSection,NULL)) {
			delete pSection;
			return NULL;
		}
	}
	return pSection;
}

void CAndroidRequest::freeMutex		(void* mutex)
{
	if (mutex) {
		pthread_mutex_t* pSection = (pthread_mutex_t*)mutex;	
		pthread_mutex_destroy(pSection); // Error handling useless here.
		delete pSection;
	}
}

void CAndroidRequest::mutexLock		(void* mutex)
{
	if (mutex) {
		pthread_mutex_t* pSection = (pthread_mutex_t*)mutex;
		pthread_mutex_lock(pSection);
	}
}

void CAndroidRequest::mutexUnlock	(void* mutex)
{
	if (mutex) {
		pthread_mutex_t* pSection = (pthread_mutex_t*)mutex;
		pthread_mutex_unlock(pSection);
	}
}

struct EventMutex {
	pthread_mutex_t		mutex;
	pthread_cond_t		cond;
};

void* CAndroidRequest::allocEventLock()
{
	EventMutex* pEvent = new EventMutex();
	if (pEvent) {
		bool err = false;
		if (pthread_mutex_init(&pEvent->mutex, NULL) == 0) {
			if (pthread_cond_init(&pEvent->cond, NULL) == 0) {
				// Do nothing.
			} else {
				pthread_mutex_destroy(&pEvent->mutex);
				err = true;
			}
		} else {
			err = true;
		}
		
		if (err) {
			delete pEvent;
			pEvent = NULL;
		}
	}
	return pEvent;
}

void CAndroidRequest::freeEventLock	(void* lock)
{
	EventMutex* pEvent = (EventMutex*)lock;
	if (pEvent) {
		pthread_mutex_destroy	(&pEvent->mutex);
		pthread_cond_destroy	(&pEvent->cond);		
	}
}

void CAndroidRequest::eventSleep(void* lock)
{
	EventMutex* pEvent = (EventMutex*)lock;
	if (pEvent) {
		// Own mutex [Lock]
		pthread_mutex_lock		(&pEvent->mutex);
		// [Unlock] and go to [Sleep], atomically.
		pthread_cond_wait		(&pEvent->cond, &pEvent->mutex);
		// [Lock] on wake up.
		
		// [Unlock] again.
		pthread_mutex_unlock	(&pEvent->mutex);
	}
}

void CAndroidRequest::eventWakeup(void* lock)
{
	EventMutex* pEvent = (EventMutex*)lock;
	if (pEvent) {
		// Own mutex [Lock]
		pthread_mutex_lock		(&pEvent->mutex);

		pthread_cond_broadcast	(&pEvent->cond);

		// [Unlock] again.
		pthread_mutex_unlock	(&pEvent->mutex);
	}
}

void CAndroidRequest::forbidSleep(bool is_forbidden)
{
	jvalue value;
    CAndroidRequest::getInstance()->callJavaMethod(value, "forbidSleep", 'V', "Z", is_forbidden);
}

//================================================
// FileIO
void*
CAndroidRequest::ifopen	(const char* name, const char* mode)
{
	return fopen(name, mode);
}

void
CAndroidRequest::ifclose(void* file)
{
	if (file)
	{
		fclose((FILE*)file);
	}
}

int
CAndroidRequest::ifseek(void* file, long int offset, int origin)
{
	return fseek((FILE*)file,offset,origin);
}

u32
CAndroidRequest::ifread(void* ptr, u32 size, u32 count, void* file )
{
	return fread(ptr, size, count, (FILE*)file);
}

u32
CAndroidRequest::ifwrite(const void * ptr, u32 size, u32 count, void* file)
{
	return fwrite(ptr, size, count, (FILE*)file);
}

int
CAndroidRequest::ifflush(void* file)
{
	return fflush((FILE*)file);
}

long int
CAndroidRequest::iftell	(void* file)
{
	return ftell((FILE*)file);
}

bool
CAndroidRequest::icreateEmptyFile(const char* name)
{
	FILE* f = fopen(name,"a");
	if (f) {
		fclose(f);
		return true;
	}
	return false;
}

};
