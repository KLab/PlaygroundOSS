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
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <WinSock.h>
#include <Rpc.h>
#include "openssl/sha.h"
#include "CWin32KeyChain.h"

#include "assert.h"
#include "RenderingFramework.h"

#include "CWin32Platform.h"
#include "CWin32ReadFileStream.h"
#include "CSockReadStream.h"
#include "CWin32HttpStream.h"
#include "CWin32Audio.h"
#include "CWin32PathConv.h"
#include "CWin32TmpFile.h"

#pragma comment(lib, "Rpcrt4.lib")
#pragma comment(lib, "libeay32.lib")

#include "FontRendering.h"

bool CWin32Platform::g_useDecryption = false;

void CWin32Platform::setEncrypt(bool encrypt) {
	g_useDecryption = encrypt;
}

CWin32Platform::CWin32Platform(HWND hWnd)
: IPlatformRequest  ()
, m_hWnd            (hWnd)
, m_version_string  (NULL)
, m_bNoDefaultFont  (false)
{
	// WinSock 初期化
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
	m_hDC = GetDC(m_hWnd);

	// OSとバージョンをあらわす文字列を作っておく
	m_version_string = create_version_string();
}

CWin32Platform::~CWin32Platform()
{
	delete [] m_version_string;

	ReleaseDC(m_hWnd, m_hDC);
	// WinSock 後始末
	WSACleanup();
}

const char *
CWin32Platform::create_version_string()
{
	char buf[4096];
	OSVERSIONINFO verInfo;
	TIME_ZONE_INFORMATION tzInfo;
	char * OSlabel;

	// Win32 API でOSのバージョンを取得する。
	memset(&verInfo, 0, sizeof(OSVERSIONINFO));
	verInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&verInfo);

	switch(verInfo.dwPlatformId)
	{
	case VER_PLATFORM_WIN32_NT:			OSlabel = "WinNT";		break;
	case VER_PLATFORM_WIN32_WINDOWS:	OSlabel = "Windows";	break;
	default:	                        OSlabel = "unknown";	break;
	}

	// Win32 API で、動作環境のタイムゾーンを取得する。
	memset(&tzInfo, 0, sizeof(TIME_ZONE_INFORMATION));
	GetTimeZoneInformation(&tzInfo);

	// Win32 APIは各国語でTimezone名を返すので、そこを何とかせんといかんのですが、
	// どうするかは後で考えます。とりあえずこの場はJST固定で実装。

	sprintf(buf,
			"Win32;%s %d.%d.%d/%s;JST",
			OSlabel,
			verInfo.dwMajorVersion, verInfo.dwMinorVersion, verInfo.dwBuildNumber,
			verInfo.szCSDVersion);

	int len = strlen(buf);

	char * ver = new char [ len + 1 ];
	strcpy(ver, buf);

	return (const char *)ver;
}

const char *
CWin32Platform::getPlatform()
{
	// 生成済みのバージョン文字列を返す
	return m_version_string;
}

u32 CWin32Platform::getPhysicalMemKB() {
	// Do not want to mess with WMI (Windows Management Instrumentation)
	// We will return a "virtual" 4 GB RAM memory computer.
	return 4 << (10 + 10);
}

void
CWin32Platform::detailedLogging(const char * /*basefile*/, const char * /*functionName*/, int /*lineNo*/, const char * format, ...)
{
	va_list	ap;
	char log	[1024];

	va_start(ap, format);
	vsprintf_s( log,1024, format, ap);
	va_end(ap);
	strcat(log, "\n");

	// 生成された文字列は utf8 文字列であるはずなので、
	// 出力用にShiftJIS変換する
	const char * sjisStr = utf8toSJIS(log);

	// 生成した文字列を何らかの方法で出力する
	OutputDebugString(sjisStr);
	printf("%s", sjisStr);
	delete [] sjisStr;
}

void
CWin32Platform::logging(const char * format, ...)
{
	va_list	ap;
	char log	[1024];

	va_start(ap, format);
	vsprintf_s( log,1024, format, ap);
	va_end(ap);
	strcat(log, "\n");

	// 生成された文字列は utf8 文字列であるはずなので、
	// 出力用にShiftJIS変換する
	const char * sjisStr = utf8toSJIS(log);

	// 生成した文字列を何らかの方法で出力する
	OutputDebugString(sjisStr);
	printf("%s", sjisStr);
	delete [] sjisStr;
}

s64
CWin32Platform::nanotime()
{
	LARGE_INTEGER counter;
	LARGE_INTEGER freq;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&counter);
	s64 val = counter.QuadPart * 1000000000LL / freq.QuadPart;
	return val;
}

const char*
CWin32Platform::getBundleVersion() {
    return "0.0";
}

bool CWin32Platform::useEncryption() {
	return g_useDecryption;
}

IReadStream *
CWin32Platform::openReadStream(const char* pathname, bool decrypt)
{
	if(!strncmp(pathname, "file://", 7)) {
		// ファイルストリーム
		CWin32ReadFileStream * pRds = CWin32ReadFileStream::openStream(pathname + 7, 0);
		if (decrypt) { pRds->decryptSetup((const u8*)pathname + 7); }
		return pRds;
	}
	if(!strncmp(pathname, "asset://", 8)) {
		CWin32ReadFileStream * pRds = CWin32ReadFileStream::openStream(pathname, 0);
		if (decrypt) { pRds->decryptSetup((const u8*)pathname + 8); }
		return pRds;
	}
	if(!strncmp(pathname, "socket://", 9)) {
		// ソケットストリーム
		CSockReadStream * pRds = CSockReadStream::openStream(pathname + 9);
		return pRds;
	}
	if(!strncmp(pathname, "http://", 7)) {
		CWin32HttpStream * pRds = CWin32HttpStream::openStream(pathname, 0);
		return pRds;
	}
	if(!strncmp(pathname, "https://", 8)) {
		CWin32HttpStream * pRds = CWin32HttpStream::openStream(pathname, 0);
		return pRds;
	}
	
	return NULL;
}

ITmpFile *
CWin32Platform::openTmpFile(const char * filePath)
{
	// file://external/ 以外が指定された場合は処理を行わない。
	const char * target = "file://external/";
	int len = strlen(target);
	if(!strncmp(filePath, target, len)) {
		CWin32TmpFile * pTmpFile = new CWin32TmpFile(filePath);
		if(!pTmpFile->isReady()) {
			delete pTmpFile;
			pTmpFile = NULL;
		}
		return pTmpFile;
	}
	return NULL;
}

#include "FileDelete.h"

const char* getFullNativePath(const char* path) {
	return CWin32PathConv::getInstance().fullpath(path + 7);
}

bool
CWin32Platform::removeFileOrFolder(const char* filePath) {
	const char * target = "file://external/";
	int len = strlen(target);
	if(!strncmp(filePath, target, len)) {
		return deleteFiles(filePath);
	} else {
		return false;
	}
}

void removeTmpFileNative(const char* filePath) {
	char* pathStr = (char*)filePath;
	while (*pathStr != 0) {
		if (*pathStr == '/') {
			*pathStr = '\\';
		}
		pathStr++;
	}

	bool res = DeleteFile(filePath);
	if (!res) {
		u32 code = GetLastError();
		if (code == ERROR_ACCESS_DENIED) {
			res = RemoveDirectory(filePath);
			if (!res) {
				klb_assertAlways("COULD NOT DELETE THE FILE %s !!!",filePath);
			}
		}
		if (code == ERROR_FILE_NOT_FOUND) {
			klb_assertAlways("FILE DOES NOT EXIST %s !!!",filePath);
		}
	}
}

u32 CWin32Platform::getFreeSpaceExternalKB() {
	const char * fullpath = CWin32PathConv::getInstance().fullpath("external/");
	char* patch = (char*)&fullpath[3]; // e:/
	*patch = 0;
	ULARGE_INTEGER FreeByteCaller;
	ULARGE_INTEGER TotalByte;
	ULARGE_INTEGER FreeByteTotal;
	 
	BOOL success = GetDiskFreeSpaceEx(fullpath, &FreeByteCaller, &TotalByte, &FreeByteTotal);
	u32 result = 0;
	if (success) {
		s64 r = FreeByteCaller.QuadPart;
		r >>= 10; // Into KB, round down !
		if (r > 0x00FFFFFFLL) {
			r = 0x00FFFFFF;
		}
		result = (u32)r;
	}
	delete [] fullpath;
	return result;
}

void
CWin32Platform::removeTmpFile(const char * filePath)
{
	// file://external/ 以外が指定された場合は処理を行わない。
	const char * target = "file://external/";
	int len = strlen(target);
	if(!strncmp(filePath, target, len)) {
		const char * fullpath = CWin32PathConv::getInstance().fullpath(filePath + 7);
		removeTmpFileNative(fullpath);
		delete [] fullpath;
	}
}

void
CWin32Platform::excludePathFromBackup(const char * /*fullpath*/)
{
}

void *
CWin32Platform::loadAudio(const char* url, bool /*is_se*/)
{
	int i;
	for(i = 0; i < SND_SLOT; i++) {
        if(m_audio[i].isActive()) { continue; }
		bool bResult = m_audio[i].openAudio(url);
		return (bResult) ? (void *)&m_audio[i] : 0;
	}
	return NULL;
}

bool
CWin32Platform::setBufSize(void* /*handle*/, int /*level*/)
{
	return true;
}

bool
CWin32Platform::preLoad(void* handle)
{
    if(!handle) { return false; }
	CWin32Audio * audio = (CWin32Audio *)handle;
	return audio->loadMem();
}


void
CWin32Platform::playAudio(void* handle, s32 _msec, float _tgtVol, float _startVol)
{
    if(!handle) { return; }
	CWin32Audio * audio = (CWin32Audio *)handle;
	audio->play(_msec, _tgtVol, _startVol);
}


void
CWin32Platform::stopAudio(void* handle, s32 _msec, float _tgtVol)
{
    if(!handle) { return; }
	CWin32Audio * audio = (CWin32Audio *)handle;
	audio->stop(_msec, _tgtVol);
}

void
CWin32Platform::setAudioVolume(void * handle, float volume)
{
	// ToDO
    if(!handle) { return; }
	CWin32Audio * audio = (CWin32Audio *)handle;
	audio->setVolume(volume);
}

void
CWin32Platform::setAudioPan(void * handle, float pan)
{
	// ToDO
    if(!handle) { return; }
	CWin32Audio * audio = (CWin32Audio *)handle;
	audio->setPan(pan);
}

void
CWin32Platform::setMasterVolume(float volume, bool SEmode)
{
	CWin32Audio::setMasterVolume(volume, SEmode);
	for(int i = 0; i < SND_SLOT; i++) {
        if(m_audio[i].isActive()) { m_audio[i].updateVolume(); }
	}
}

void
CWin32Platform::releaseAudio(void* handle)
{
    if(!handle) { return; }
	CWin32Audio * audio = (CWin32Audio *)handle;
	audio->closeAudio();
}

void
CWin32Platform::pauseAudio(void * handle, s32 _msec, float _tgtVol)
{
    if(!handle) { return; }
	CWin32Audio * audio = (CWin32Audio *)handle;
	audio->pause(_msec, _tgtVol);
}

void
CWin32Platform::resumeAudio(void * handle, s32 _msec, float _tgtVol)
{
    if(!handle) { return; }
	CWin32Audio * audio = (CWin32Audio *)handle;
	audio->resume(_msec, _tgtVol);
}
void
CWin32Platform::seekAudio(void * /*handle*/, s32 /*millisec*/)
{

}

s32
CWin32Platform::tellAudio(void * handle)
{
    if(!handle) { return 0; }
	CWin32Audio * audio = (CWin32Audio *)handle;
	return audio->tell();
}

s32
CWin32Platform::totalTimeAudio(void * handle)
{
    if(!handle) { return 0; }
	CWin32Audio * audio = (CWin32Audio *)handle;
	return audio->totalPlayTime();
}

s32
CWin32Platform::getState(void * handle)
{
    if(!handle) { return -1; }
	CWin32Audio * audio = (CWin32Audio *)handle;
	return audio->getState();
}

void
CWin32Platform::setFadeParam(void * _handle, float _tgtVol, u32 _msec)
{
    if( !_handle ) { return; }
	CWin32Audio * audio = (CWin32Audio*)_handle;
	audio->setFadeParam( _tgtVol, _msec );
}

/*!
	@brief	経過時間を取得
	@param[in]	void
	@return		s64
*/
s64 CWin32Platform::getElapsedTime( void )
{
	LARGE_INTEGER counter;
	LARGE_INTEGER freq;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&counter);

	s64 val = counter.QuadPart / freq.QuadPart;
	return val;
}

bool CWin32Platform::registerFont(const char* logicalName, const char* physFile, bool default_) {
	// Return always true if we disabled default font to avoid ASSERT at startup.
	return FontObject::registerFont(logicalName, physFile, default_) | m_bNoDefaultFont;
}

void *
CWin32Platform::getFont(int size, const char * fontName, float* pAscent)
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

void
CWin32Platform::deleteFont(void * pFont)
{
	FontObject::destroyFont((FontObject*)pFont);
}

void *
CWin32Platform::getFontSystem(int size, const char * fontName)
{
	try {
		CWin32Font * pFont = new CWin32Font(m_hDC, size, fontName);
		return (void *)pFont;
	} catch(...) {
		return NULL;
	}
}

void
CWin32Platform::deleteFontSystem(void * pFont)
{
	CWin32Font * f_pFont = (CWin32Font *)pFont;
	delete f_pFont;
}

bool
CWin32Platform::renderText(const char* utf8String, void * pFont, u32 color,
						   u16 width, u16 height, u8 * pBuffer8888,
						   s16 stride, s16 base_x, s16 base_y, bool use4444)
{
	FontObject* pObjFont = (FontObject*)pFont;
	if (pObjFont) {
		pObjFont->renderText(base_x, base_y, utf8String, pBuffer8888, color, width, height, stride, use4444);
	}
	return true;
}


bool
CWin32Platform::getTextInfo(const char* utf8String, void * pFont, STextInfo* pReturnInfo)
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

 void *
CWin32Platform::getGLExtension(const char * /*ext*/)
 {
	// Not implemented
	 klb_assertAlways("Not used and not implemented");
	return NULL;
 }

const char *
CWin32Platform::utf8toSJIS(const char * utf8str)
{
	// UTF-8 は、一文字最長3バイト(日本語の場合)
	// Shift_JIS は、一文字最長2バイト。
	// 同じ文字列のバッファサイズが、utf-8より長くなることはない。
	size_t sizeBuffer = strlen(utf8str) + 1;
	LPWSTR pwszBuf = new wchar_t [ sizeBuffer ];
	char * lastbuf = new char [ sizeBuffer ];
	klb_assert(0 != lastbuf, "string conv buf not enough memory.");

	MultiByteToWideChar(
		CP_UTF8,
		0,
		utf8str,
		-1,
		pwszBuf,
		(int)sizeBuffer);

	WideCharToMultiByte(
		CP_ACP,
		0,
		pwszBuf,
		-1,
		lastbuf,
		(int)sizeBuffer,
		NULL,
		NULL);
	delete [] pwszBuf;

	return (const char *)lastbuf;
}

const char *
CWin32Platform::SJIStoUTF8(const char * SJISstr)
{
	// UTF-8 は、一文字最長3バイト(日本語の場合)
	// Shift_JIS は、一文字最長2バイト。
	// 同じ文字列のバッファサイズが、utf-8より長くなることはない。
	size_t sizeBuffer = strlen(SJISstr) * 3 / 2 + 1;	// 1.5倍のバッファサイズ
	LPWSTR pwszBuf = new wchar_t [ sizeBuffer ];
	char * lastbuf = new char [ sizeBuffer ];
	klb_assert(0 != lastbuf, "string conv buf not enough memory.");

	MultiByteToWideChar(
		CP_ACP,
		0,
		SJISstr,
		-1,
		pwszBuf,
		(int)sizeBuffer);

	WideCharToMultiByte(
		CP_UTF8,
		0,
		pwszBuf,
		-1,
		lastbuf,
		(int)sizeBuffer,
		NULL,
		NULL);
	delete [] pwszBuf;

	return (const char *)lastbuf;
}


const char *
CWin32Platform::getFullPath(const char * assetPath, bool* isReadOnly)
{
	CWin32PathConv& pathconv = CWin32PathConv::getInstance();

	if(!strncmp(assetPath, "file://", 7)) {
		// ファイルストリーム
		return pathconv.fullpath(assetPath + 7,0,isReadOnly);
	}
	if(!strncmp(assetPath, "asset://", 8)) {
		return pathconv.fullpath(assetPath,0,isReadOnly);
	}
	return NULL;
}



IWidget *
CWin32Platform::createControl(IWidget::CONTROL type, int id,
							  const char * caption, int x, int y, int width, int height, ...)
{
	IWidget * pWidget = NULL;
	va_list ap;
	va_start(ap, height);
	switch(type)
	{
	case IWidget::TEXTBOX:
	case IWidget::PASSWDBOX:
		{
			int maxlen = va_arg(ap, int);
			CWin32TextWidget * pTextWidget = new CWin32TextWidget(this, maxlen);
			if(!pTextWidget || !pTextWidget->create(type, id, caption, x, y, width, height)) {
				delete pTextWidget;
				pTextWidget = NULL;
			}
			pWidget = pTextWidget;
		}
		break;
	case IWidget::WEBVIEW:
	case IWidget::WEBNOJUMP:
		{
			const char * token  = va_arg(ap, const char *);
			const char * region = va_arg(ap, const char *);
			const char * client = va_arg(ap, const char *);
			const char * cKey   = va_arg(ap, const char *);
			const char * appID  = va_arg(ap, const char *);
			const char * userID	= va_arg(ap, const char *);

			CWin32WebWidget * pWebWidget = new CWin32WebWidget(this);
			if(!pWebWidget || !pWebWidget->create(type, id, caption, x, y, width, height,
												  token, region, client, cKey, appID, userID)) {
				delete pWebWidget;
				pWebWidget = NULL;
			}
			pWidget = pWebWidget;
		}
		break;
	case IWidget::MOVIEPLAYER:
	case IWidget::BGMOVIEPLAYER:
		{
			CWin32MovieWidget * pMovieWidget = new CWin32MovieWidget(this);
			if(!pMovieWidget || !pMovieWidget->create(type, id, caption, x, y, width, height)) {
				delete pMovieWidget;
				pMovieWidget = NULL;
			}
			pWidget = pMovieWidget;
		}
		break;
	case IWidget::ACTIVITYINDICATOR:
		{
			CWin32ActivityIndicator * pActIWidget = new CWin32ActivityIndicator(this);
			if(!pActIWidget || !pActIWidget->create(type, id, caption, x, y, width, height)) {
				delete pActIWidget;
				pActIWidget = NULL;
			}
			pWidget = pActIWidget;
		}
		break;
	}
	return pWidget;
}

void
CWin32Platform::destroyControl(IWidget * pControl)
{
	delete pControl;
}


bool
CWin32Platform::callApplication(IPlatformRequest::APP_TYPE type, ... )
{
	bool result = true;
	va_list ap;
	va_start(ap, type);

	switch(type)
	{
	default:
		result = false;
		break;

	case IPlatformRequest::APP_UPDATE:
		{
			const char * search_key = va_arg(ap, const char *);
			MessageBox(m_hWnd, search_key, "CALL Application", MB_OK);
		}
		break;
	}

	va_end(ap);
	return result;
}

CWin32Font::CWin32Font(HDC hDC, int size, const char * fontname) : m_size(size)
{
	// 指定されたフォント名から実際にAPIに渡すフォント名を得る

	// サイズからフォントを生成
	memset((void *)&m_logfont, 0, sizeof(LOGFONT));
	m_logfont.lfCharSet = DEFAULT_CHARSET;
	m_logfont.lfHeight = (LONG)size;

	// 指定されたフォント名があれば、設定する。
    if(fontname) { strcpy( m_logfont.lfFaceName, fontname); }

	m_hFont = CreateFontIndirect(&m_logfont);

	TEXTMETRIC metric;
	// フォントの metrics を取得

	// font metric はフォントそのものではなく、
	// フォントが適用されている DCから取得するため、
	// 上記で生成したフォントを hDC のフォントとして選択してやらねばならない。
	// そうしないと、直前に設定されたフォントのmetricを拾ってしまう。
	SelectObject(hDC, m_hFont);


	GetTextMetrics(hDC, &metric);
	m_ascent    = (float)metric.tmAscent;
	m_descent   = -(float)metric.tmDescent;
	m_top       = m_ascent + (metric.tmHeight - (m_ascent - m_descent)) / 3.0f;
	m_bottom    = m_top - metric.tmHeight;
}

CWin32Font::~CWin32Font()
{
	DeleteObject(m_hFont);
}

// 直接OSから呼ばれる thread 関数。
// 内容的には、各ワークに保存された関数ポインタを呼び出す
DWORD WINAPI
CWin32Platform::ThreadProc(LPVOID lpParam)
{
	PF_THREAD * pThread = (PF_THREAD *)lpParam;
	if(!(pThread->result = setjmp(pThread->jmp))) {
		pThread->result = (pThread->thread_func)(pThread, pThread->data);
	}
	ExitThread(TRUE);
}

// スレッドを作る。
void *
CWin32Platform::createThread(s32 (*thread_func)(void *, void *), void *data)
{
	PF_THREAD * thread = new PF_THREAD;
    if(!thread) { return NULL; }

	thread->data        = data;
	thread->thread_func = thread_func;
	thread->result      = 0;

	// Windowsのthreadは、CWin32Platform::ThreadProc() を呼ぶように作る。
	thread->hWin32Thread = CreateThread(
		NULL , 0 , CWin32Platform::ThreadProc , thread, 0 , &(thread->idWin32Thread));

	return thread;
}

// スレッドの中から呼ばれる、スレッドを中断する関数
void
CWin32Platform::exitThread(void * hThread, s32 status)
{
	PF_THREAD * pThread = (PF_THREAD *)hThread;
	longjmp(pThread->jmp, status);
}

// スレッドの外から呼ばれる、スレッドの状態を取得する関数
bool
CWin32Platform::watchThread(void * hThread, s32 * status)
{
	PF_THREAD * pThread = (PF_THREAD *)hThread;
	DWORD dwParam;
	GetExitCodeThread(pThread->hWin32Thread, &dwParam);
	if(dwParam == STILL_ACTIVE) {
		// スレッドは実行中
		return true;
	}
	// スレッドは終了しているので、終了コードを *status に返す
	*status = pThread->result;
	return false;	// スレッド終了なので false を返す
}

// スレッドを破棄する。
void
CWin32Platform::deleteThread(void * hThread)
{
	PF_THREAD * pThread = (PF_THREAD *)hThread;
	CloseHandle( pThread->hWin32Thread );
	delete pThread;
}

// スレッドを強制中断する
void
CWin32Platform::breakThread(void * hThread)
{
	PF_THREAD * pThread = (PF_THREAD *)hThread;
	TerminateThread(pThread->hWin32Thread, 0);
}

int
CWin32Platform::genUserID(char * retBuf, int maxlen)
{
	unsigned char * p;
	UUID uuid;
	::UuidCreate(&uuid);
	::UuidToString(&uuid, &p);

	int i = 0;
    for(i = 0; i < maxlen - 1 && p[i]; i++) { retBuf[i] = p[i]; }
	retBuf[i] = 0;

	::RpcStringFree(&p);

	return i;
}

int
CWin32Platform::genUserPW(const char * salt, char * retbuf, int maxlen)
{
	char buf[1024];
	time_t tm;
	int rnd = rand();
	time(&tm);
	sprintf(buf, "%d.%ld.%s", rnd, (u32)tm, salt);
	return sha512(buf, retbuf, maxlen);
}

bool
CWin32Platform::readyDevID()
{
	return true;	// 常にデバイスID取得処理は完了したことにする
}

int
CWin32Platform::getDevID(char * /*retBuf*/, int /*maxlen*/)
{
	return 0;	// 常にデバイスID取得に失敗したことにする
}

bool
CWin32Platform::setSecureDataID(const char * service_name, const char * user_id)
{
	return setKeyChain(service_name, "user_id", user_id);
}

bool
CWin32Platform::setSecureDataPW(const char * service_name, const char * passwd)
{
	return setKeyChain(service_name, "passwd", passwd);
}

int
CWin32Platform::getSecureDataID(const char * service_name, char * retBuf, int maxlen)
{
	return getKeyChain(service_name, "user_id", retBuf, maxlen);
}

int
CWin32Platform::getSecureDataPW(const char * service_name, char * retBuf, int maxlen)
{
	return getKeyChain(service_name, "passwd", retBuf, maxlen);
}

bool
CWin32Platform::delSecureDataID(const char * service_name)
{
	return delKeyChain(service_name, "user_id");
}

bool
CWin32Platform::delSecureDataPW(const char * service_name)
{
	return delKeyChain(service_name, "passwd");
}


int
CWin32Platform::sha512(const char * string, char * buf, int maxlen)
{
	unsigned char obuf[64];
	SHA512((const unsigned char *)string, strlen(string), obuf);
	char * ptr = buf;
	for(int i = 0; i < 64 && (i * 2 + 1 < maxlen); i++) {
		sprintf(ptr, "%02x", obuf[i]);
		ptr += strlen(ptr);
	}
	return strlen(buf);
}

bool
CWin32Platform::setKeyChain(const char * service_name, const char * key, const char * value)
{
	bool result = true;
	CWin32KeyChain keychain;

	keychain.loadKeyChain(W32_KEYCHAIN_FILENAME);
	result = keychain.setValue(service_name, key, value);
	return result && keychain.saveKeyChain(W32_KEYCHAIN_FILENAME);
}

int
CWin32Platform::getKeyChain(const char * service_name, const char * key, char * retBuf, int maxlen)
{
	CWin32KeyChain keychain;

	keychain.loadKeyChain(W32_KEYCHAIN_FILENAME);
	const char * value = keychain.getValue(service_name, key);
	if(!value) return 0;
	int i = 0;
    for(i = 0; i < maxlen - 1 && value[i]; i++) { retBuf[i] = value[i]; }
	retBuf[i] = 0;
	return i;
}

bool
CWin32Platform::delKeyChain(const char * service_name, const char * key)
{
	CWin32KeyChain keychain;

	keychain.loadKeyChain(W32_KEYCHAIN_FILENAME);
	bool bResult = keychain.delValue(service_name, key);
	return bResult && keychain.saveKeyChain(W32_KEYCHAIN_FILENAME);
}

void
CWin32Platform::initStoreTransactionObserver()
{
}

void
CWin32Platform::releaseStoreTransactionObserver()
{
}

void
CWin32Platform::buyStoreItems(const char * /*item_id*/)
{
}

void
CWin32Platform::getStoreProducts(const char* /*json*/, bool /*currency_mode*/)
{
}

void
CWin32Platform::finishStoreTransaction(const char* /*receipt*/)
{
}

void*		CWin32Platform::ifopen	(const char* name, const char* mode) {
	return fopen(name, mode);
}

void		CWin32Platform::ifclose	(void* file) {
	if (file) {
		fclose((FILE*)file);
	}
}

int			CWin32Platform::ifseek	(void* file, long int offset, int origin) {
	return fseek((FILE*)file,offset,origin);
}

u32			CWin32Platform::ifread	(void* ptr, u32 size, u32 count, void* file ) {
	return fread(ptr, size, count, (FILE*)file);
}

u32			CWin32Platform::ifwrite	(const void * ptr, u32 size, u32 count, void* file) {
	return fwrite(ptr, size, count, (FILE*)file);
}

int			CWin32Platform::ifflush	(void* file) {
	return fflush((FILE*)file);
}

long int	CWin32Platform::iftell	(void* file) {
	return ftell((FILE*)file);
}

bool CWin32Platform::icreateEmptyFile(const char* name) {
	FILE* f = fopen(name,"a");
	if (f) {
		fclose(f);
		return true;
	}
	return false;
}

void*	CWin32Platform::allocMutex		()
{
	CRITICAL_SECTION* pSection = new CRITICAL_SECTION();
	if (pSection) {
		InitializeCriticalSection(pSection);
	}
	return pSection;
}

void	CWin32Platform::freeMutex		(void* mutex)
{
	if (mutex) {
		DeleteCriticalSection((CRITICAL_SECTION*)mutex); 
		delete mutex;
	}
}

void	CWin32Platform::mutexLock		(void* mutex)
{
	if (mutex) { EnterCriticalSection((CRITICAL_SECTION*)mutex); }
}

void	CWin32Platform::mutexUnlock		(void* mutex)
{
	if (mutex) { LeaveCriticalSection((CRITICAL_SECTION*)mutex); }
}

void*	CWin32Platform::allocEventLock	()
{
	HANDLE* pEvent = new HANDLE();
	if (pEvent) {
		*pEvent = CreateEvent(NULL,false,false,NULL);
	}
	return pEvent;
}

void	CWin32Platform::freeEventLock	(void* lock)
{
	if (lock) {
		HANDLE* pHandle = (HANDLE*)lock;
		if (*pHandle) {
			CloseHandle(*pHandle);
		}
		delete pHandle;
	}
}

void	CWin32Platform::eventSleep		(void* lock)
{
	if (lock) {
		HANDLE* pHandle = (HANDLE*)lock;
		if (*pHandle) {
			WaitForSingleObject( *pHandle , INFINITE );
		}
	}
}

void	CWin32Platform::eventWakeup		(void* lock)
{
	if (lock) {
		HANDLE* pHandle = (HANDLE*)lock;
		if (*pHandle) {
			SetEvent(*pHandle);
		}
	}
}
