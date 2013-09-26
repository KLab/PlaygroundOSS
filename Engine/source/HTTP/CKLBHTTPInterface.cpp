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
#include "CKLBHTTPInterface.h"
#include "CKLBUtility.h"
#include <string.h>
#include <ctype.h>
;

#ifdef USE_NEW_CURL_WRAPPER

#include "curl.h"

// Prototypes
int strncmpi(const char* str1, const char* str2, int len);

// static
bool CKLBHTTPInterface::initHTTPLib()
{
	return curl_global_init(CURL_GLOBAL_ALL) == CURLE_OK;
}

// static
void CKLBHTTPInterface::releaseHTTPLib() {
	curl_global_cleanup();
}

//_______________________________________________________________________
//  Thread
//_______________________________________________________________________

// static
s32 CKLBHTTPInterface::HTTPConnectionThread(void * /*hThread*/, void * data) 
{
	((CKLBHTTPInterface*)data)->download();
	return 1;
}

void CKLBHTTPInterface::download() {
	m_threadStop = 0;
	m_pCurl      = curl_easy_init();
	if(m_pCurl)
	{
		curl_slist* headerlist = NULL;
		if (m_post) {
			headerlist = curl_slist_append(headerlist, "Expect:");
		}

		for (u32 n = 0; n < m_headerEntryCount; n++) {
			// printf("Hdr : %s\n",m_headerEntry[n]);
			headerlist = curl_slist_append(headerlist, m_headerEntry[n]);
		}

		curl_httppost* formpost = NULL;
		curl_httppost* lastptr  = NULL;
		if (m_post && m_postForm) {
			for(u32 i = 0; m_postForm[i]; i++) {
				char * formItem = (char*)m_postForm[i]; // We need to put back as writable.

				// split into two strings.
				// Search for first "=" and patch with 0.
				char * ptr = formItem;
				while (*ptr != 0 && *ptr != '=') { ptr++; }

				if (*ptr != 0) {
					*ptr = 0;
					// printf("Form : %s = %s\n",formItem,&ptr[1]);
					curl_formadd(
						&formpost,
						&lastptr,
						CURLFORM_COPYNAME, formItem,
						CURLFORM_CONTENTSLENGTH, strlen(&ptr[1]),
						CURLFORM_COPYCONTENTS, &ptr[1],
						CURLFORM_END
					);
					// Restore array in case of reuse...
					*ptr = '=';
				}
			}
		}

		curl_easy_setopt(m_pCurl, CURLOPT_HTTPHEADER, headerlist);
		if (m_post) {
			curl_easy_setopt(m_pCurl, CURLOPT_HTTPPOST, formpost);
		}

		curl_easy_setopt(m_pCurl, CURLOPT_URL,				m_url			);
		curl_easy_setopt(m_pCurl, CURLOPT_WRITEDATA,		(void*)this		);
		curl_easy_setopt(m_pCurl, CURLOPT_WRITEFUNCTION,	write_func		);
//		curl_easy_setopt(m_pCurl, CURLOPT_READFUNCTION,		my_read_func	);
		curl_easy_setopt(m_pCurl, CURLOPT_NOPROGRESS,		0L				);
		curl_easy_setopt(m_pCurl, CURLOPT_NOSIGNAL,			1				);
		curl_easy_setopt(m_pCurl, CURLOPT_PROGRESSFUNCTION,	progress_func	);
		curl_easy_setopt(m_pCurl, CURLOPT_PROGRESSDATA,		(void*)this		);
		curl_easy_setopt(m_pCurl, CURLOPT_WRITEHEADER,		(void*)this		);
 		curl_easy_setopt(m_pCurl, CURLOPT_HEADERFUNCTION,	headerReceive_func);
#ifndef _WIN32
		curl_easy_setopt(m_pCurl, CURLOPT_ACCEPT_ENCODING,	"gzip,deflate");
#endif
		CURLcode res = curl_easy_perform(m_pCurl);
		if (res == CURLE_OK) {
			curl_easy_getinfo (m_pCurl, CURLINFO_RESPONSE_CODE, &m_errorCode);
			// WARNING : IN THAT ORDER, because of multithreading, flag set LAST, after everything else.
			m_receivedData	= m_buffer;
			m_receivedSize	= m_writeIndex;
			m_bDataComplete = true;
		} else {
			// printf("HTTP FAIL\n");
			
			// In some cases, the server cut the connection, resulting in a CURL error
			// But there is 0 byte of data and the error code is valid.
			// In this case, we allow the upper layer to consider returning a safe error code.
			if ((this->m_receivedSize == 0) && (
				((m_tmpErrorCode >= 500) && (m_tmpErrorCode <= 599)) || (m_tmpErrorCode == 204)
				)) {
				m_errorCode = m_tmpErrorCode;
			}
		}

		if (formpost) {
			curl_formfree(formpost);
		}

		if (headerlist) {
			curl_slist_free_all(headerlist);
		}

		// always cleanup
		curl_easy_cleanup(m_pCurl);
		m_pCurl = NULL;

		if (m_bDownload) {
			// Close file anyway
			if (m_pTmpFile) {
				delete m_pTmpFile; // No macro, get alloc from porting layer.
				m_pTmpFile = NULL;
			}
		}
	}
	m_threadStop = 1;
}

int strncmpi(const char* str1, const char* str2, int len) {
	while ((*str1 != 0) && (*str2 != 0) && (tolower(*str1++)) == (tolower(*str2++)) && (len-- != 0)) {
	}

	if ((len == 0) || ((*str1 == 0) && (*str2 == 0))) {
		return 0;
	} else {
		str1--;
		str2--;
		return tolower(*str1) < tolower(*str2) ? -1 : +1; 
	}
}

// static
size_t CKLBHTTPInterface::headerReceive_func( void *ptr, size_t size, size_t nmemb, void *userdata) {
	u32 totalSize = size * nmemb;
	const char* data = (const char*)ptr;
	if (strncmpi("Maintenance:", data, 12/*Maintenance: 1*/) == 0) {
		data+=12; // Skip Maintenance
		while ((*data != '\r') && (*data != '\n') && (*data != 0)) {
			if (*data == '1') {
				((CKLBHTTPInterface*)userdata)->m_maintenance = true;
				break;
			}
			data++;
		}
	}

	if (strncmpi("Status: ",data, 8/*Status: */)==0) {
		int code = 0;
		while ((*data >= '0') && (*data <= '9')) {
			code = (code * 10) + (*data);
			data++;
		}
		((CKLBHTTPInterface*)userdata)->m_tmpErrorCode = code;
	}

	if (strncmpi("Server-Version:", data, 15/*Server-Version*/) == 0) {
		u32 lineSize = size * nmemb;	// Full Size
		lineSize -= 15;					// Remove Server-Version
		data += 15;
		
		// skip : and space before and after
		while (*data == ' ') {
			data++;
			lineSize--;
		}

		char* mem =	(char*)CKLBUtility::copyMem(data, lineSize + 1);
		if (mem) {
			mem[lineSize] = 0;
			((CKLBHTTPInterface*)userdata)->m_pServerVersion = mem;
			// IPlatformRequest& pForm = CPFInterface::getInstance().platform();
			// pForm.logging("HTTPInterface::get Server-Version %s %8X",mem);

		}
	}
	if (!((CKLBHTTPInterface*)userdata)->m_stopThread) {
		return totalSize;
	} else {
		return 0xFFFFFFFF;
	}
}

bool CKLBHTTPInterface::hasHeader(const char* header, const char** value) {
	if (strcmp("Server-Version", header) == 0) {
		// IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		// pForm.logging("HTTPInterface::hasHeader %s %8X",header,m_pServerVersion);
		if (value) {
			// pForm.logging("Value:%s",m_pServerVersion);
			*value = m_pServerVersion;
		}
		return (m_pServerVersion != NULL);
	} else {
		klb_assertAlways("Does not support other header for now than 'Server-Version'");
		return false;
	}
}


// static
int CKLBHTTPInterface::progress_func(	void* ctx, 
										double total,		// dltotal
										double dl,			// dlnow
										double /*ultotal*/,	
										double /*ulnow*/)
{
	u64 uiTotal = (u64)total;
	u64 uiDownl = (u64)dl;
	((CKLBHTTPInterface*)ctx)->progress(uiTotal, uiDownl);
	if (!((CKLBHTTPInterface*)ctx)->m_stopThread) {
		return 0;
	} else {
		return -1;
	}
}

void CKLBHTTPInterface::progress(u64 /*total*/, u64 download) {
	m_receivedSize = download;
}

// static
size_t CKLBHTTPInterface::write_func(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	return ((CKLBHTTPInterface*)userdata)->write(ptr, size, nmemb);
}

size_t CKLBHTTPInterface::write(char* ptr, size_t size, size_t nmemb)
{
	bool noErr = false;

	u64 blockSize   = size * nmemb;
	u64 oldByteSize = m_writeIndex;
	u64 newByteSize = oldByteSize + blockSize;	// Optimize with fixed size allocation ?

	if (m_pTmpFile && (m_bothFileAndMem == false)) {
		if (m_pTmpFile->writeTmp(ptr, blockSize) == blockSize) {
			noErr = true;
		}
	} else {
		u8* pNewBuff = KLBNEWA(u8, newByteSize);
		if (pNewBuff) {
			if (m_buffer) {
				memcpy(pNewBuff, m_buffer, oldByteSize);
				KLBDELETEA(m_buffer);
			}
			memcpy(&pNewBuff[oldByteSize],	ptr, blockSize);
			m_buffer		= pNewBuff;
			m_writeIndex	= newByteSize;
			if (m_pTmpFile) {
				if (m_pTmpFile->writeTmp(ptr, blockSize) == blockSize) {
					noErr = true;
				}
			} else {
				noErr = true;
			}
		}
	}

	if (noErr) {
		return blockSize;
	} else {
		return 0;
	}
}

//_______________________________________________________________________
//  Object
//_______________________________________________________________________

CKLBHTTPInterface::CKLBHTTPInterface()
: m_errorCode       (-1)
, m_bDataComplete   (false)
, m_bDownload       (false)
, m_pTmpFile        (NULL)
, m_receivedSize    (0)
, m_writeIndex      (0)
, m_receivedData    (NULL)
, m_thread          (NULL)
, m_buffer          (NULL)
, m_bothFileAndMem  (true)
, m_headers         (NULL)
, m_headerEntry     (NULL)
, m_headerEntryLen  (NULL)
, m_hdrlen          (0)
, m_headerEntryCount(0)
, m_post            (false)
, m_url             (NULL)
, m_pCurl           (NULL)
, m_postForm        (NULL)
, m_pServerVersion  (NULL)
, m_maintenance     (false)
, m_threadStop      (0)
, m_stopThread      (false)
, m_tmpErrorCode    (-1)
{
	init();
}

// virtual
CKLBHTTPInterface::~CKLBHTTPInterface()
{
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();

	// True : thread still working
	bool result = false;
 	if (m_thread) {
		int status;
		result = pForm.watchThread(m_thread, &status);
		m_stopThread = true;
		while (m_threadStop == 0) {
		}
	}

	// May use result here...

	if (m_thread) {
		pForm.deleteThread(m_thread);
		m_thread = NULL;
	}

	/* NEVER DO THAT, thread may be still alive.
	if (m_pCurl) {
		curl_easy_cleanup(m_pCurl);	
		m_pCurl = NULL;
	} */

	clear();
}

// 追加HTTPヘッダの持
bool CKLBHTTPInterface::setHeader(const char ** headers)
{
	m_headerEntryCount = 0;
	while (headers[m_headerEntryCount++]) { }
	m_headerEntryCount--;

	if (m_headerEntryCount) {
		m_headerEntry		= KLBNEWA(const char*, m_headerEntryCount);
		m_headerEntryLen	= KLBNEWA(u32, m_headerEntryCount);
        if ((!m_headerEntry) || (!m_headerEntryLen)) { return false; }

		int len = 1;	// 終端コードサイズは先に設宁E
		for(int i = 0; headers[i]; i++) {
			m_headerEntryLen[i] = strlen(headers[i]);
			len += m_headerEntryLen[i] + 2;
		}

		char * buf = KLBNEWA(char, len);
		if(!buf) return false;

		KLBDELETEA(m_headers);

		m_headers = buf;

		for(int i = 0; headers[i]; i++) {
			len = m_headerEntryLen[i];
			strcpy(buf, headers[i]);
			m_headerEntry[i] = buf;
			buf += len;
//			strcpy(buf, "\r\n"); Replace the chars by end of string.
			*buf++ = 0;
		}
		*buf = 0;

		m_hdrlen = buf - m_headers;
	}

	return true;
}

// 持フォーム値のURLencode
char * CKLBHTTPInterface::setForm(const char ** postForm)
{
	// DEBUG_PRINT("HTTPInterface::setForm");

	// 持されpostForm から、POST斁を生成する
	// postForm は URLencodeされておらず個頁が連結されて態
	/*
	char * basebuf = retbuf;
	if(!basebuf) return NULL;
	*/

	u32 i = 0;
	while (postForm[i++]) { }

	m_postForm = KLBNEWA(const char*, i);

	if (m_postForm) {
		for(u32 n = 0; postForm[n]; n++) {
			const char * formItem = postForm[n];
			m_postForm[n] = CKLBUtility::copyString(formItem);
		}
		m_postForm[i-1] = NULL;
	}

	return NULL;
}

void CKLBHTTPInterface::reuse() {
	// DEBUG_PRINT("HTTPInterface::reuse");
	clear();
	init();
}

void CKLBHTTPInterface::init() {
	m_errorCode         = -1;
	m_bDataComplete	    = false;
	m_bDownload         = false;
	m_pTmpFile          = NULL;
	m_receivedSize      = 0;
	m_writeIndex        = 0;
	m_receivedData      = NULL;
	m_thread            = NULL;
	m_buffer            = NULL;
	m_bothFileAndMem    = true;
	m_headers           = NULL;
	m_headerEntry       = NULL;
	m_headerEntryLen    = NULL;
	m_hdrlen            = 0;
	m_headerEntryCount  = 0;
	m_post              = false;
	m_url               = NULL;
	m_pCurl             = NULL;
	m_postForm          = NULL;
	m_pServerVersion    = NULL;
	m_maintenance       = false;
	m_threadStop        = 0;
	m_stopThread        = false;
}

void CKLBHTTPInterface::clear() {
	// Force file closing if necessary.
	delete m_pTmpFile;
	m_pTmpFile = NULL;

	KLBDELETEA(m_url);
	KLBDELETEA(m_buffer);
	KLBDELETEA(m_headers);
	KLBDELETEA(m_headerEntry);
	KLBDELETEA(m_headerEntryLen);
	KLBDELETEA(m_pServerVersion);

	if (m_postForm) {
		u32 i = 0;
		while (m_postForm[i]) {
			KLBDELETEA(m_postForm[i]);
			i++;
		}
		KLBDELETEA(m_postForm);
		m_postForm = NULL;
	}

	m_url				= NULL;
	m_buffer			= NULL;
	m_headers			= NULL;
	m_headerEntry		= NULL;
	m_headerEntryLen	= NULL;
	m_pServerVersion	= NULL;

	init();
}

// GET発衁
bool CKLBHTTPInterface::httpGET(const char * url, bool isProxy)
{
	klb_assert(isProxy==false,"Proxy Not supported");

	m_post	= false;
	KLBDELETEA(m_url);
	m_url = CKLBUtility::copyString(url);

    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	//pForm.logging("HTTPInterface::httpGET");
	m_thread = pForm.createThread(CKLBHTTPInterface::HTTPConnectionThread, this);
	return (m_thread != NULL);
}

// POST発衁
bool CKLBHTTPInterface::httpPOST(const char * url, bool isProxy)
{
	klb_assert(isProxy==false,"Proxy Not supported");

	m_post = true;
	KLBDELETEA(m_url);
	m_url = CKLBUtility::copyString(url);

    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	// pForm.logging("HTTPInterface::httpPost");
	m_thread = pForm.createThread(CKLBHTTPInterface::HTTPConnectionThread, this);
	return (m_thread != NULL);
}

// ダウンロード保存パス名を持し、ダウンロードモードでの動作を開始する
// NULL持で通常のオンメモリモードでの動作に戻めE
bool CKLBHTTPInterface::setDownload(const char * path) 
{
	m_bDownload = false;
	if(path) {
		// ダウンロードファイル名 file://external/ 以下パスで与えられねばならな
		m_pTmpFile = CPFInterface::getInstance().platform().openTmpFile(path);
		if(m_pTmpFile) {
			m_bDownload = true;
		}
	}
	return m_bDownload; 
}

// 受信リソースの取征
u8* CKLBHTTPInterface::getRecvResource() {
	return m_receivedData;
}

// 現在の受信サイズ
s64 CKLBHTTPInterface::getSize()
{
	return m_receivedSize;
}

// 受信スチEタス
bool CKLBHTTPInterface::httpRECV()
{
	return m_bDataComplete;
}

// httpのstate取征2013.2.13  追加
int CKLBHTTPInterface::getHttpState()
{
	return m_errorCode;
}

#else

CKLBHTTPInterface::CKLBHTTPInterface()
: m_url         (NULL)
, m_host        (NULL)
, m_path        (NULL)
, m_port        (0)
, m_headers     (NULL)
, m_hdrlen      (0)
, m_pSocket     (NULL)
, m_pWRSock     (NULL)
, m_http_recv   (NULL)
, m_proxy_host  (NULL)
, m_begin       (NULL)
, m_end         (NULL)
, m_sThreadSig  (0)
, m_hThread     (NULL)
, m_bufSend     (NULL)
, m_sizeSend    (0)
, m_bDownload   (false)
, m_chunked     (false)
, m_pTmpFile    (NULL)
, m_http_state  (0)
, m_pConnectName(NULL)
, m_pMethod     (NULL)
, m_pMethod_header  (NULL)
, m_pBody       (NULL)
, m_bIsProxy    (false)
, m_test_body_length(0)
{
}

CKLBHTTPInterface::~CKLBHTTPInterface()
{
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	if(m_hThread) {
		// pForm.breakThread(m_hThread);	// 走ってスレチを中断させる
		m_sThreadSig = 1;
		s32 status;
        while(pForm.watchThread(m_hThread, &status)) { status = 0; }
		pForm.deleteThread(m_hThread);	// スレチを破棁E
		m_hThread = NULL;
	}

	//delete m_pWRSock;
	delete m_pSocket;	// socketを閉じる

	if(m_begin || m_end) {
		// chunk読み取り中なので、それらのバッファをすべて解放する
		CHUNK * pChunk = m_begin;
		while(pChunk) {
			CHUNK * pNext = pChunk->next;
			KLBDELETEA(pChunk);
			pChunk = pNext;
		}
		m_begin = m_end = NULL;
	} else {
		// 読み取り中でなければ、m_http_recv が唯一のバッファを握って
		KLBDELETEA(m_http_recv);
	}

	// 送中は送バッファを握ってので解放
	if(m_bufSend) {
		KLBDELETEA(m_bufSend);
		m_bufSend  = NULL;
		m_sizeSend = 0;
	}
	KLBDELETEA(m_url);
	KLBDELETEA(m_host);
	KLBDELETEA(m_path);
	KLBDELETEA(m_proxy_host);
	KLBDELETEA(m_headers);

    if( m_pConnectName ) {
        KLBDELETEA( m_pConnectName );
        m_pConnectName = NULL;
    }
    if( m_pBody ) {
        KLBDELETEA( m_pBody );
        m_pBody = NULL;
    }
    if( m_pMethod_header ) {
        KLBDELETEA( m_pMethod_header );
        m_pMethod_header = NULL;
    }
    if( m_pMethod ) {
        KLBDELETEA( m_pMethod );
        m_pMethod = NULL;
    }
	if (m_pTmpFile) {
		delete m_pTmpFile;
	}
}

bool
CKLBHTTPInterface::url_parse(const char * url)
{
	// 元URL保孁
	KLBDELETEA(m_url);
	m_url = CKLBUtility::copyString(url);

	// hostとportを得る
	const char * ptr;
	if(!strncmp("http://", url, 7)) {
		m_port = 80;
		ptr = url + 7;
	} else if(!strncmp("https://", url, 8)) {
		//TODO
		return false;
	} else {
		return false;
	}

	int last;
	for(last = 0; ptr[last]; last++) {
		if(ptr[last] == '/' || ptr[last] == ':') break;
	}
	char * buf = KLBNEWA(char, last + 1);
	strncpy(buf, ptr, last);
	buf[last] = 0;
	KLBDELETEA(m_host);
	m_host = (const char *)buf;

	if(ptr[last] == ':') {	// port が指定されて
		last++;
		m_port = 0;
		while(ptr[last] && ptr[last] != '/') {
			if(ptr[last] < '0' || ptr[last] > '9') return false;
			m_port = m_port * 10 + ptr[last] - '0';
			last++;
		}
	}

	//if(ptr[last] != 0) last++;
	// 2012.11.28  解放せずに次のを作り出すでここで解放
	if( m_path ) {
		KLBDELETEA( m_path );
	}
	m_path = CKLBUtility::copyString(ptr + last);

    if(m_host && m_path && m_url) { return true; }
	return false;
}

bool
CKLBHTTPInterface::setHeader(const char ** headers)
{
	int len = 1;	// 終端コードサイズは先に設宁
	for(int i = 0; headers[i]; i++) {
		len += strlen(headers[i]) + 2;
	}
	char * buf = KLBNEWA(char, len);
    if(!buf) { return false; }

	KLBDELETEA(m_headers);

	m_headers = buf;

	for(int i = 0; headers[i]; i++) {
		len = strlen(headers[i]);
		strcpy(buf, headers[i]);
		buf += len;
		strcpy(buf, "\r\n");
		buf += 2;
	}
	*buf = 0;

	m_hdrlen = strlen(m_headers);

	return true;
}

bool
CKLBHTTPInterface::setDownload(const char * path)
{
	m_bDownload = false;
	if(path) {
		// ダウンロードファイル名 file://external/ 以下パスで与えられねばならな
		m_pTmpFile = CPFInterface::getInstance().platform().openTmpFile(path);
		if(m_pTmpFile) {
			m_bDownload = true;
		}
	} else {
		m_bDownload = false;
	}
	return m_bDownload; 
}

bool
CKLBHTTPInterface::httpRECV()
{
	if(m_b_finished) {
        // DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> Finished !");
		return true;
	}
	if(!m_pSocket) return false;

    switch( m_eStep )
    {
    //-------------------------------------------
    // チEタ送信
    case E_CONNECT_WAITING:
        {
            DEBUG_PRINT("--- E_CONNECT_WAITING ---");
            // スレチ実行征
            s32 status;
            IPlatformRequest& pForm = CPFInterface::getInstance().platform();
            bool result = false;
            result = pForm.watchThread( m_hThread , &status );
            if( result ) { break; }
            
            // スレチ実行が終亁てぁばrequestの出力完亁
            pForm.deleteThread( m_hThread );
            m_hThread = NULL;
            
            DEBUG_PRINT("--- E_CONNECT_WAITING END---");
            // Connect後処琁する < 中でm_eStepを移させて
            httpMethod_AfterConnect();
        }
        break;
    //-------------------------------------------
    // チEタ送信
    case E_SENDING:
        {
			// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_SENDING");
            s32 status;
            IPlatformRequest& pForm = CPFInterface::getInstance().platform();
            bool result = false;
            result = pForm.watchThread( m_hThread , &status );
            if( result ) break;

            // スレチ実行が終亁てぁばrequestの出力完亁
            pForm.deleteThread( m_hThread );
            m_hThread = NULL;

            // 送EチEタバッファを破棁め
            KLBDELETEA(m_bufSend);
            m_bufSend  = NULL;
            m_sizeSend = 0;

            // response征に入め
            m_eStep = E_STARTUP;
        }
        // break; // こ呼び出しかめEresponse 征に入るため、意図皁breakを行わな
    case E_STARTUP:
        {
			// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_STARTUP");
            m_begin = m_end = NULL;

            m_eStep         = E_RDHDR;

            m_read_size     = 0;
            m_recv_size     = 0;
            m_header_size   = 0;
            m_pReadNow      = NULL;

            m_bChunkDebug   = false;

            // ヘッダーのchunkを作る
            create_chunk(HEADER_BUF_SIZE);

        }
    //-------------------------------------------
    // こままヘッダーの処琁
    case E_RDHDR:
        {
			// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_RDHDR");
            // ヘッダーサイズの初期匁E
            m_header_size = 0;

            // ヘッダを読み、下記惁を得る
            // Content-Length		チEタ自体全体サイズ
            // Transfer-Encoding	送信形式が chunked であるか否
            s32 size = m_pSocket->getSize();
			// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_RDHDR Size : %i", size);
            if(!size) {
                break;
            }

            // m_http_recvへsize刁み込む
            if(HEADER_BUF_SIZE - m_recv_size < (u32)size) { 
                size = HEADER_BUF_SIZE - m_recv_size;
            }
            if(!m_pSocket->readBlock(m_http_recv, size)) {
                break;
            }
			// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_RDHDR Read Block : %i", size);
            m_read_size  = size;
            m_recv_size += size;

            // ヘッダを読み終わったかの検査(空行を見つけてぁ)
            bool find = false;
            for(size_t pos = 0; pos <= m_recv_size - 4; pos++) {
                if(m_http_recv[pos] != '\r') { continue; }

                if(!strncmp((const char *)m_http_recv + pos, "\r\n\r\n", 4)) {
                    find = true;
                    break;
                }
            }
            if(!find) {
                break;
            }

            // ヘッダ終端を見つけてぁらチを解析する
            // ヘッダからbodyの長さと chunked か否かを得る
            m_chunked = false;
            m_notchunk_length = 0;
            get_format((char *)m_http_recv, &m_chunked, &m_notchunk_length);

            // 現在の読み込み場所をチー空行まで進める
            m_pReadNow  = strstr( (char*)m_http_recv , "\r\n\r\n" );
            m_pReadNow += 4;    // 空行進める

            m_header_size = m_pReadNow - (char*)m_http_recv;
            m_read_size -= m_header_size;   // ヘッダー刁ら

			// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_RDHDR Header Size : %i", m_header_size);

            // 1つ目のchunkはヘッダー部刁Eみで終亁せる
            m_end->size = m_header_size;

            // 次のスチプへ
            if(!m_chunked) {
                m_eStep = E_RD_BODY_NOT_CHUNKED;
            } else {
                m_eStep = E_RD_BODY_CHUNKED;
            }
        }
        break;

    //-------------------------------------------
    // chunkで無ぁ合読み込み
    case E_RD_BODY_NOT_CHUNKED:
        {
			// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_RD_BODY_NOT_CHUNKED");
            // こ場合チEタのサイズは全体からチー部刁引いたサイズ
            int chunk_size = m_notchunk_length;

            // chunkを作る
            create_chunk( chunk_size );
			m_rdSize = chunk_size;	// 20130222 

            // 読み込んだ残りをchunkへコピする
            int copy_size = chunk_size;
            if( copy_size >= m_read_size ) {
                // コピするサイズが読み込んでぁサイズよりも大きい場合続きを読み込まなぁぁな
                copy_size = m_read_size;
                m_eStep = E_RDBODY;
            }
            
            // chunkへコピする
            memcpy( m_http_recv , m_pReadNow , copy_size );
            m_read_size -= copy_size;
            m_recv_size += copy_size;

			// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_RD_BODY_NOT_CHUNKED %i %i ", m_read_size, m_recv_size);


            // 次のスチプへ行かなぁ合終亁E
            if( m_eStep != E_RDBODY ) {
                // 既にbodyの読み込みが終亁てぁため、終亁ェーズに入る
                //m_rdSize = m_recv_size;	// 20130222 　コメントアウチE
                if(m_bDownload) {
                    // そbody刁チポラリに書き
                    m_pTmpFile->writeTmp(m_http_recv, m_recv_size);
                    // 最後 chink を破棁めEヘッダのchunkのみが残される)
                    remove_last_chunk();
                }
                read_finish();

				// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_RD_BODY_NOT_CHUNKED break");
                break;
            }

            // 残りを読み込むスレチ関数を仕掛ける
            IPlatformRequest& pForm = CPFInterface::getInstance().platform();
            m_hThread = pForm.createThread(CKLBHTTPInterface::ThreadHTTP, this);
        }
        break;

    //-------------------------------------------
    // body の残り読み込み中
    case E_RDBODY:
        {
			// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_RD_BODY");
            s32 status;
            IPlatformRequest& pForm = CPFInterface::getInstance().platform();
            bool result = pForm.watchThread(m_hThread, &status);
            if(result) { break; }
            pForm.deleteThread(m_hThread);
            m_hThread = NULL;
            // スレチが終亁てぁば、結琁行い終亁せる
            if(m_bDownload) {
                // 最後 chunk を破棁ることによりチchunkのみが残される
                // ダウンロードモードではヘッダのみをオンメモリで扱
                remove_last_chunk();
            }
            read_finish();
        }
        break;

    //-------------------------------------------
    // chunkの場合チEタ読み込み
    case E_RD_BODY_CHUNKED:
        {
			// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_RD_BODY_CHUNKED");
            // chunkに書き込むべきサイズを取得すめ
            // チEタの残りのサイズ刁れめE
            char* body = get_chunk_size(m_pReadNow, m_read_size, &m_rightsize);
            // ここでまず判定すめE
            if(!body) {
                // 最初 chunk サイズが取得できず、response が異常であるため
                // ここで受信冁を完結させる
                read_finish();
                // klb_assertAlways("could not get chunk size.");
				// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_RD_BODY_CHUNKED break");
                break;	// 最初chunkサイズが取得できなかっ
            }
            m_read_size -= (body-m_pReadNow);   // chunkサイズ刁E改行
            m_pReadNow = body;

            // chunkを作る
            create_chunk( m_rightsize );
			m_rdSize += m_rightsize;	// 20130222 

            // 読み込んだ残りをchunkへコピする
            int copy_size = m_rightsize;
            if( copy_size > m_read_size ) {
                // コピするサイズが読み込んでサイズよりも大きい場合続きを読み込まなぁぁな
                copy_size = m_read_size;
                m_eStep = E_RDCHUNK;
            }

            // chunkへコピ
            memcpy(m_http_recv, m_pReadNow, copy_size );
            m_recv_size += copy_size;
            m_read_size -= copy_size;

            // 次のスチプへ行く
            if( m_eStep == E_RDCHUNK ) {
                // 残りを読み込むスレチ関数を仕掛ける
                IPlatformRequest& pForm = CPFInterface::getInstance().platform();
                m_hThread = pForm.createThread(CKLBHTTPInterface::ThreadHTTP, this);
            } else {
                m_pReadNow += copy_size;
                m_pReadNow += 2;    // 改行
                m_read_size-=2;     // 改行
                // 次のchunkがあるか調べめEこStepの先頭へ戻め
                m_eStep = E_RD_BODY_CHUNKED;
                m_bChunkDebug = true;
            }
        }
        break;

    //-------------------------------------------
    // chunk時残りチEタ読み込み
    case E_RDCHUNK:
        {
			// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_RD_CHUNK");
            s32 status;
            IPlatformRequest& pForm = CPFInterface::getInstance().platform();
            bool result = pForm.watchThread(m_hThread, &status);
            if(result) break;	// thread は実行中

            // thread の実行が終亁て
            // ダウンロードモードであれば、そのthreadで読み込み中であったchunk冁はファイルに追加されて
            pForm.deleteThread(m_hThread);	// thread 破棁
            m_hThread = 0;
            m_tmpsize = 0;

            if(m_bDownload) {
                // ダウンロードモードではヘッダchunk以外をオンメモリで扱わなぁめ
                // 今琁終わった最後chunkは不要となるため破棁
                remove_last_chunk();
            }

            m_eStep = E_NEXTCHUNK;
            // thread を殺し、次のchunkのサイズを得る
        }

    //-------------------------------------------
    // chunk時残りチEタ読み込み
    case E_NEXTCHUNK:
        {
			// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_NEXTCHUNK");
            int retry = 0;
            // 次の1024byte以冁改行があるかどぁ調べめ
            do {
                m_read_size = m_pSocket->getSize();
                if(!m_read_size) {
                    if(retry < RETRY) {
                        retry++;
                        continue;
                    } else {
                        retry = RETRY;
                        DEBUG_PRINT("recv timedout");
                    }
                }

                if(m_read_size + m_tmpsize > 1024) { 
                    m_read_size = 1024 - m_tmpsize;
                }
                if(!m_pSocket->readBlock(m_tmpBuf + m_tmpsize, m_read_size)) {
                    if(retry < RETRY) {
                        retry++;
                        continue;
                    } else {
                        retry = RETRY;
                        DEBUG_PRINT("recv timedout");
                    }
                }
                m_tmpsize += m_read_size;
                // chunk のサイズを得るためにここまでのサイズは不要
                if(m_tmpsize >= 1024) {
                    break;
                }
            } while(m_tmpsize < 2 || find_crlf((char *)m_tmpBuf + 2, m_tmpsize - 2) < 0);

            // 次のchunkを探
            bool loop_count  = 0;
            // 改行を見つける
            while(!strncmp((const char *)m_tmpBuf, "\r\n", 2)) {
                loop_count++;

                // 現在のバッファ中に改行があれば、そこまで進める
                size_t pos = 2;
                while( pos<m_tmpsize && (char)m_tmpBuf[pos]!='\r') { pos++; }
                if(pos < m_tmpsize && !strncmp((const char *)m_tmpBuf + pos, "\r\n", 2)) 
                {// 改行が見つかっ

					// 改行まで読んだので、m_tmpBuf には次のchunk size がある
					size_t size = 0;
					for(int i = 2; i < (int)pos; i++) {
						size = size * 16;
						int c = tolower((int)m_tmpBuf[i]);
						if(c >= '0' && c <= '9') size += c - '0';
						if(c >= 'a' && c <= 'f') size += c - 'a' + 10;
					}
					DEBUG_PRINT("chunk: size = %08lx (%ld)", size, size);
					if(size == 0) {
						// 全てのchunkを読み終わったで、終亁ェーズに移行
						read_finish();
						break;
					}
					// サイズ刁chunkを確俁E
					/* CHUNK * pChunk = */ create_chunk(size);
					m_rdSize += size;	// 20130222 

					// バッファに既に読み込んでぁchunk刁あれば頭にコピする
					int read_size = m_tmpsize - (pos + 2);
					size_t copysize = (read_size > size) ? size : read_size;
					if(copysize > 0) {
						memcpy(m_http_recv, m_tmpBuf + pos + 2, copysize);
						m_recv_size = copysize;
					}

					if(m_bDownload) {
						// そbody刁チポラリに書き
						m_pTmpFile->writeTmp(m_http_recv, m_recv_size);
						// 最後 chink を破棁めEヘッダのchunkのみが残される)
						remove_last_chunk();
					}

					// こ時点でchunkのサイズが終亁てしまったら、その次から次のchunk惁が始まって
					// (大抵はそこで終わめ
					if(read_size > copysize) {
						m_tmpsize = read_size - copysize;
						memcpy(m_tmpBuf, m_tmpBuf + pos + 2 + copysize, m_tmpsize);
						// 平戁E5年2朁E9日(火)
						// CKLBHTTPInterface::ThreadHTTP冁行われるべき琁行われなでここで意図皁加算す
						//m_rdSize += m_recv_size; //20130222  コメントアウチ

						// 続きを読む
						do {
							int size = m_pSocket->getSize();

							if(!size) {
								if(retry < RETRY) {
									retry++;
									continue;
								} else {
									retry = RETRY;
									DEBUG_PRINT("recv timedout");
								}
							}
							if(size + m_tmpsize > 1024) { 
                                size = 1024 - m_tmpsize;
                            }
							if(!m_pSocket->readBlock(m_tmpBuf + m_tmpsize, size)) {
								if(retry < RETRY) {
									retry++;
									continue;
								} else {
									retry = RETRY;
									DEBUG_PRINT("recv timedout");
								}
							}

							m_tmpsize += size;
							// chunk のサイズを得るためにここまでのサイズは不要
                            if(m_tmpsize >= 1024) { break; }
						} while(m_tmpsize < 2 || find_crlf((char *)m_tmpBuf + 2, m_tmpsize - 2) < 0);
						// 新たな先頭から次のサイズを読み込む(ためE)

					} else {
						// 続きをthreadに読ませる
						IPlatformRequest& pForm = CPFInterface::getInstance().platform();
						m_hThread = pForm.createThread(CKLBHTTPInterface::ThreadHTTP, this);
						m_eStep = E_RDCHUNK;
						break;
					}
                }

            }
			if(!loop_count) {

				m_tmpBuf[m_tmpsize] = 0;
				// chunkフォーマットが異常なので、現在までの受信冁でレスポンスを完結させる
				read_finish();
				// klb_assertAlways("bad chunk format.");
				// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_NEXTCHUNK break");
				break;
			}

//            printf( ">>>>> read_size : %d \n",m_read_size );
        }
        break;

    //-------------------------------------------
    // bodyの読み込みが終亁
    case E_END:
        {
			// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_END");
            s32 status;
            IPlatformRequest& pForm = CPFInterface::getInstance().platform();
            bool result = pForm.watchThread(m_hThread, &status);
            if(result) {
				// DEBUG_PRINT("CKLBHTTPInterface::httpRECV -> E_END break");
				break;	// thread は実行中
			}

            pForm.deleteThread(m_hThread);
            m_hThread = NULL;

            // スレチが終亁てぁば、chunkの連結が終亁たとぁこと

            // 連結が終亁たで全chunkバッファを破棁る
            CHUNK * pChunk = m_begin;
            while(pChunk)
            {
                CHUNK * next = pChunk->next;
                KLBDELETEA(((u8 *)pChunk));
                pChunk = next;
            }
            m_begin = m_end = NULL;

            // ダウンロードモード場合、終亁同時にチポラリをクローズする
            if(m_bDownload)
            {
                delete m_pTmpFile;
                m_pTmpFile  = NULL;
                m_bDownload = false;
            }

            delete m_pSocket;
            m_pSocket    = NULL;
            m_pWRSock    = NULL;
            m_b_finished = true;
        }
        break;
    }

    return false;
}

int
CKLBHTTPInterface::find_crlf(const char * ptr, int len)
{
	for(int i = 0; i < len - 2; i++) {
		if(ptr[i] != '\r') continue;
		if(!strncmp("\r\n", ptr + i, 2)) return i;
	}
	return -1;
}

void
CKLBHTTPInterface::read_finish()
{
	// DEBUG_PRINT("=== read_finish ===");
	// 全てのchunkが読み終わってぁので、繋いで一つのバッファにする
	// pass-1: 生すべき単一バッファのサイズを求める
	CHUNK * pChunk  = m_begin;
	size_t  size    = 0;
	while(pChunk) {
		size += pChunk->size;
		pChunk = pChunk->next;
	}
	u8 * pNewBuf = KLBNEWA(u8, size + 1);

	m_http_recv = pNewBuf;
	m_recv_size = 0;
	m_eStep = E_END;

	// 読み込んだchunk bufferの冁を連結する琁別スレチで行わせる
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	m_hThread = pForm.createThread(CKLBHTTPInterface::ThreadJOINT, this);

    m_bChunkDebug = false;
	// DEBUG_PRINT("=== /read_finish ===");
}

void
CKLBHTTPInterface::remove_chunk(CHUNK * pChunk)
{
	// DEBUG_PRINT("=== remove_chunk ===");
	// DEBUG_PRINT("=== Size : %i", pChunk->size);
	if(pChunk->prev) {
		pChunk->prev->next = pChunk->next;
	} else {
		m_begin = pChunk->next;
	}
	if(pChunk->next) {
		pChunk->next->prev = pChunk->prev;
	} else {
		m_end = pChunk->prev;
	}
	KLBDELETE(pChunk);
	// DEBUG_PRINT("=== /remove_chunk ===");
}

CKLBHTTPInterface::CHUNK *
CKLBHTTPInterface::create_chunk(size_t size)
{
	CHUNK * pChunk = (CHUNK *)KLBNEWA(u8, sizeof(CHUNK) + size + 1);
	klb_assert(pChunk, "could not alloc chunk buffer(HTTP)");
    if(!pChunk) { return NULL; }

	pChunk->size = size;
	pChunk->prev = m_end;
	pChunk->next = NULL;
	if(pChunk->prev) {
		pChunk->prev->next = pChunk;
	} else {
		m_begin = pChunk;
	}
	m_end       = pChunk;
	m_http_recv = (u8 *)&pChunk[1];
	m_recv_size = 0;
	// DEBUG_PRINT("=== /createchunk %i ===", size);
	return pChunk;
}

s32
CKLBHTTPInterface::ThreadJOINT(void * /* hThread */, void * data)
{
	CKLBHTTPInterface * pHTTP = (CKLBHTTPInterface *)data;

	pHTTP->SetBodySize(0);

	CHUNK * pChunk = pHTTP->m_begin;
	size_t pos = 0;
	while(pChunk) {
		if(pHTTP->m_sThreadSig) {
			break;
		}
		memcpy(pHTTP->m_http_recv + pos, &pChunk[1], pChunk->size);
        if( pos > 0 ) { pHTTP->AddBodySize( pChunk->size ); }
		pos += pChunk->size;
		pChunk = pChunk->next;
	}
	pHTTP->m_http_recv[pos] = 0; // 斁として閉じめ

	return 0;
}

s32
CKLBHTTPInterface::ThreadSEND(void * /* hThread */, void * data)
{
	CKLBHTTPInterface * pHTTP = (CKLBHTTPInterface *)data;
	pHTTP->sending();
	return 0;
}

s32
CKLBHTTPInterface::ThreadHTTP(void * /* hThread */, void * data)
{
	CKLBHTTPInterface * pHTTP = (CKLBHTTPInterface *)data;

	while(pHTTP->m_recv_size < pHTTP->m_end->size) {
		if(pHTTP->m_sThreadSig) {
			break;
		}
		size_t size = pHTTP->m_pSocket->getSize();
		if(size > pHTTP->m_end->size - pHTTP->m_recv_size) {
			size = pHTTP->m_end->size - pHTTP->m_recv_size;
		}
		if(!pHTTP->m_pSocket->readBlock(pHTTP->m_http_recv + pHTTP->m_recv_size, size)) {
			continue;
		}
		pHTTP->m_recv_size += size;
	}

	*(pHTTP->m_http_recv + pHTTP->m_recv_size) = 0;

    // トタル読み込みサイズを更新
	//pHTTP->m_rdSize += pHTTP->m_recv_size;	// 20130222  コメントアウチ

    // そセチョンがダウンロードモードであるなら
	// pHTTP->m_http_recv から pHTTP->m_recv_size 刁チポラリに書き込む
	if(pHTTP->m_bDownload) {
		pHTTP->m_pTmpFile->writeTmp(pHTTP->m_http_recv, pHTTP->m_recv_size);
	}

	// 読み終わったでスレチを終亁る
	return 0;
}

s32
CKLBHTTPInterface::ThreadCONNECT(void * /* hThread */, void * data)
{
	CKLBHTTPInterface * pHTTP = (CKLBHTTPInterface *)data;
	pHTTP->setSocket( CPFInterface::getInstance().platform().openReadStream( pHTTP->getConnectName() , false) );
	return 0;
}

bool
CKLBHTTPInterface::cmp_header(char * ptr, const char * str, size_t len)
{
	for(size_t i = 0; i < len && str[i]; i++) {
		if(!ptr[i]) return false;
		if(tolower(ptr[i]) != tolower(str[i])) return false;
	}
	return true;
}

char *
CKLBHTTPInterface::get_chunk_size(char * buf, size_t len, size_t * size)
{
	*size = 0;
	size_t pos;
	for(pos = 0; !isspace(buf[pos]) && pos < len; pos++) {
		int c = tolower(buf[pos]);
		*size = *size * 16;
		if(c >= '0' && c <= '9') {
			*size += c - '0';
			continue;
		}
		if(c >= 'a' && c <= 'f') {
			*size += c - 'a' + 10;
			continue;
		}
		// 不正な斁E
		return NULL;
	}
	// バッファ終端にたどり着ぁ場合、値の有効性が疑わしで取得失敗
    if(pos == len)      { return NULL; }
	// そ直後が改行であることが確認できなぁ合ポインタが胡散臭で取得失敗扱
    if(len - pos < 2)   { return NULL; }

	// 値が取得でき、その直後が改行であることが確認できたら取得功、それ以外失敗
    if(strncmp(buf + pos, "\r\n", 2)) { return NULL; }

	return buf + pos + 2;
}

bool
CKLBHTTPInterface::get_format(char * buf, bool * f_chunked, u64 * length)
{
	bool finish = false;
	char * recv = buf;
	size_t pos  = 0;
	const char *    c_length    = "content-length: ";
	const char *    tr_encoding = "transfer-encoding:";
	const int       len_len     = strlen(c_length);
	const int       enc_len     = strlen(tr_encoding);
	const char *    chunked     = "chunked";
	const int       chunked_len = strlen(chunked);

    const char*     http_head   ="HTTP";
    const int       http_head_len = strlen(http_head);

    m_http_state = 0;
    // 最初行からHTTPの状態を取得すめE2013.2.13 追加
    if( cmp_header(recv,http_head,http_head_len) ) {
        int state_buff_pos=0;
        int state_check_pos = http_head_len;
        bool bIsSpace = false;
        // HTTPをみつけたら次のスペスをさがす(最長で8斁まで)
        while( state_check_pos<http_head_len+8) {
            bIsSpace = isspace(recv[state_check_pos]);
            state_check_pos++;
            if( bIsSpace == true ) break;
        }

        if( bIsSpace == true ) {
            char state_buff[4]={0};
            while( !isspace(recv[state_check_pos]) && state_buff_pos<4 ) {
                state_buff[state_buff_pos] = recv[state_check_pos];
                state_check_pos++;state_buff_pos++;
            }

            m_http_state = atoi(state_buff);
        }
    }

	*f_chunked  = false;
	*length     = 0LL;
	bool hasContentLength = false;

	while(!finish) {
		int len;
		for(len = 0; recv[len]; len++) {
            if(!strncmp(recv + len, "\r\n", 2)) { break; }
		}
		if(len == 0) {	// 長さが0 すなわち空行に到遁E
			finish = true;
			continue;
		}
		if(cmp_header(recv, tr_encoding, enc_len)) {
			// 目皁Eヘッダ(1): Transfer-Encoding
			char * val = recv + enc_len;
            while(*val && *val == ' ') { val++; } // 空白を読み飛
			if(!strncmp(val, chunked, chunked_len) && (isspace(val[chunked_len]))) {
				// Transfer-Encoding: chunked だったで true を返す
				*f_chunked = true;
			}
		} else if(cmp_header(recv, c_length, len_len)) {
			hasContentLength = true;
			// 目皁Eヘッダ(2): Content-Length
			char * val = recv + len_len;
            while(*val && *val == ' ') { val++; }
			*length = 0;
			while(!isspace(*val)) {
				int num = *val;
				if(num < '0' || num > '9') break;
				num -= '0';
				*length = *length * 10LL + num;
				val++;
			}
		}
		recv += len + 2;
		pos += len + 2;
	}

	if (!hasContentLength) {
		if (*f_chunked == false) {
			// klb_assertAlways("Server Side stream has neither content-length or chunk query");
			DEBUG_PRINT(" ");
			DEBUG_PRINT("### !!!! ERROR !!!! ####");
			DEBUG_PRINT("### !!!! CKLBHTTPInterface::Server Side stream has neither content-length nor chunk query !!!! ####");
			DEBUG_PRINT("### !!!! ERROR !!!! ####");
			DEBUG_PRINT(" ");
		}
	}
	// ヘッダが見つからなかったで false を返す
	return true;
}

char *
CKLBHTTPInterface::URLencode(char * retbuf, int maxlen, const char ** postForm)
{
	// 持されpostForm から、POST斁を生成する
	// postForm は URLencodeされておらず、個頁が連結されてぁぁ態
	char *  basebuf  = (retbuf) ? retbuf : KLBNEWA(char, ALLOC_SIZE);
	int     now_size = (retbuf) ? maxlen : ALLOC_SIZE;
    if(!basebuf) { return NULL; }

	char * ptr = basebuf;

	for(int i = 0; postForm[i]; i++) {
		const char * formItem = postForm[i];

		if(i > 0) {
			*ptr++ = '&';
			if(ptr - basebuf >= now_size - 1) {
				// バッファが与えられてぁ場合エラー終亁E
                if(retbuf) { return NULL; }

				// 冁で確保されたバッファを用ぁ場合,バッファを継ぎ足
				int len = ptr - basebuf;
				char * newptr = KLBNEWA(char, now_size + ALLOC_SIZE);
				if(!newptr) {
					KLBDELETEA(basebuf);
					return NULL;
				}
				memcpy(newptr, basebuf, len);
				KLBDELETEA(basebuf);
				basebuf = newptr;
				ptr = basebuf + len;
				now_size += ALLOC_SIZE;
			}
		}
		for(const char * src = formItem; *src; src++) {
			int reqsize = 1;
			char tmpbuf[10];
			const char * data = 0;
			if(('0'<= *src && *src <= '9')  ||
				('a'<= *src && *src <= 'z') ||
				('A'<= *src && *src <= 'Z') ||
				*src == '_' || *src == '-'  ||
				*src == '.' || *src == '*'  || *src == '=') {
	
				// そままぁる文孁
				data = src;
			} else if(*src == ' ') {

				// 空白の置き換
				data = "+";

			} else {
				reqsize = 3;
				sprintf(tmpbuf, "%%%02x", (int)*(unsigned char *)src);
				data = (const char *)tmpbuf;
			}
			if((ptr + reqsize) - basebuf >= now_size - 1) {
				// バッファが与えられてぁ場合エラー終亁E
                if(retbuf) { return NULL; }

				// 冁で確保されたバッファを用ぁ場合,バッファを継ぎ足
				int len = ptr - basebuf;
				char * newptr = KLBNEWA(char, now_size + ALLOC_SIZE);
				if(!newptr) {
					KLBDELETEA(basebuf);
					return NULL;
				}
				memcpy(newptr, basebuf, len);
				KLBDELETEA(basebuf);
				basebuf  = newptr;
				ptr      = basebuf + len;
				now_size += ALLOC_SIZE;
			}
			memcpy(ptr, data, reqsize);
			ptr += reqsize;
		}
	}
	*ptr = 0;
	return basebuf;
}

bool
CKLBHTTPInterface::httpMethod(const char * method, const char * method_hdr,
							  const char * url,
							  bool isProxy, const char * body)
{
	char buf[1024];

    if(!url_parse(url)) { return false; }
    
    // connect用にここで引数をメンバにコピしたりすめ
    if( m_pMethod ) {
        KLBDELETEA( m_pMethod );
        m_pMethod = NULL;
    }
	if( method != NULL ) {
		m_pMethod = KLBNEWA( char , strlen(method)+1 );
		memset( (void*)m_pMethod , 0, strlen(method)+1 );
		memcpy( (void*)m_pMethod , method , strlen(method) );
	}

    if( m_pMethod_header ) {
        KLBDELETEA( m_pMethod_header );
        m_pMethod_header = NULL;
    }
	if( method_hdr != NULL ) {
		m_pMethod_header = KLBNEWA( char , strlen(method_hdr)+1 );
		memset( (void*)m_pMethod_header , 0, strlen(method_hdr)+1 );
		memcpy( (void*)m_pMethod_header , method_hdr , strlen(method_hdr) );
	}

    if( m_pBody ) {
        KLBDELETEA( m_pBody );
        m_pBody = NULL;
    }
	if( body != NULL) {
		m_pBody = KLBNEWA( char , strlen(body)+1 );
		memset( (void*)m_pBody , 0, strlen(body)+1 );
		memcpy( (void*)m_pBody , body , strlen(body) );
	}
    
    m_bIsProxy = isProxy;

	m_rdSize = 0;	// サイズ初期匁

	// プロキシが設定されており、なおかつそ使用を指示されてぁ場吁
	if(isProxy && m_proxy) {
		sprintf(buf, "socket://%s:%d", m_proxy_host, m_proxy_port);
	} else {
		sprintf(buf, "socket://%s:%d", m_host, m_port);
	}
	if(m_pWRSock) delete m_pWRSock;
	if(m_pSocket) delete m_pSocket;

	m_pWRSock = NULL;
	m_pSocket = NULL;

    // connect用スレチをたてめ
    if( m_pConnectName ) {
        KLBDELETEA( m_pConnectName );
        m_pConnectName = NULL;
    }
    m_pConnectName = KLBNEWA( char , strlen(buf)+1 );
    memset( (void*)m_pConnectName , 0 , strlen(buf)+1 );
    memcpy( (void*)m_pConnectName , buf , strlen(buf) );
    
    DEBUG_PRINT("--- ConnectName >");
    DEBUG_PRINT("%s",m_pConnectName);
    
    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    m_hThread = pForm.createThread(CKLBHTTPInterface::ThreadCONNECT, this);
    m_eStep = E_CONNECT_WAITING;

	m_http_recv  = NULL;
	m_recv_size  = 0;
	m_buf_size   = 0;
	m_b_finished = false;
	return true;
}

bool
CKLBHTTPInterface::httpMethod_AfterConnect(void)
{
    char buf[1024];
    
	if(!m_pSocket || m_pSocket->getStatus() != IReadStream::NORMAL) {
		m_pSocket = 0;
		return false;
	}
	m_pWRSock = m_pSocket->getWriteStream();
	if(!m_pWRSock) {
		delete m_pSocket;
		m_pSocket = 0;
		return false;
	}
    
	// 基本methodとUserAgentを送る
	if(m_proxy && m_bIsProxy) {
		sprintf(buf,
				"%s %s HTTP/1.1\r\n"
				"Host: %s:%d\r\n"
				"Connection: close\r\n"
				"User-Agent: %s\r\n%s", m_pMethod, m_url, m_host, m_port, USER_AGENT, m_pMethod_header);
	} else {
		sprintf(buf,
				"%s %s HTTP/1.1\r\n"
				"Host: %s:%d\r\n"
				"Connection: close\r\n"
				"User-Agent: %s\r\n%s", m_pMethod, m_path, m_host, m_port, USER_AGENT, m_pMethod_header);
	}
	m_pWRSock->writeBlock(buf, strlen(buf));
    
	// そ他追加HTTPヘッダを追加するhdrlen
	if(m_hdrlen > 0) {
        m_pWRSock->writeBlock((void *)m_headers, m_hdrlen);
    }
    
	// 番人を送る
	m_pWRSock->writeBlock((void *)"\r\n", 2);
	m_eStep = E_STARTUP;
    
	// bodyを送る。体的には送E用チEタバッファを確保し、別スレチでパケチの送Eを行わせる
	if(m_pBody) {
		// 送E冁と送Eサイズをメンバに取り込む
		m_sizeSend = strlen(m_pBody);
		m_bufSend = KLBNEWA(char, m_sizeSend);
		memcpy((void *)m_bufSend, m_pBody, m_sizeSend); // Since size can be specified when sent out by socket, \0 is unnecessary.
        
		// 送Eスレチを立ち上げる
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		m_hThread   = pForm.createThread(CKLBHTTPInterface::ThreadSEND, this);
		m_eStep     = E_SENDING;
	}
	KLBDELETEA(m_http_recv);

    // スレチ終亁に呼ばれるはずなのでnewした物は解放する
    if( m_pConnectName ) {
        KLBDELETEA( m_pConnectName );
        m_pConnectName = NULL;
    }
    if( m_pBody ) {
        KLBDELETEA( m_pBody );
        m_pBody = NULL;
    }
    if( m_pMethod_header ) {
        KLBDELETEA( m_pMethod_header );
        m_pMethod_header = NULL;
    }
    if( m_pMethod ) {
        KLBDELETEA( m_pMethod );
        m_pMethod = NULL;
    }
    
	m_http_recv  = NULL;
	m_recv_size  = 0;
	m_buf_size   = 0;
	m_b_finished = false;
    return true;
}

// static
bool 
CKLBHTTPInterface::initHTTPLib()
{
	return true;
}

// static
void 
CKLBHTTPInterface::releaseHTTPLib() 
{
	// Do nothing
}

#endif
