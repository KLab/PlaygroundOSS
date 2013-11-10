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
#ifndef CKLBHTTPInterface_h
#define CKLBHTTPInterface_h

#include "CPFInterface.h"
#include <string.h>

#define USER_AGENT "UserAgent"

// SocketStream を利用して、HTTP/1.1 による通信を行う。
// オンメモリ読み込みのほか、ダウンロード読み込み対応。

#define USE_NEW_CURL_WRAPPER

#ifdef USE_NEW_CURL_WRAPPER
class ConnectionEntry;

/*!
* \class CKLBHTTPInterface
* \brief HTTP Interface Class
* 
* 
*/
class CKLBHTTPInterface
{
	friend class ConnectionEntry;
private:
	CKLBHTTPInterface();
	virtual ~CKLBHTTPInterface();
public:
	void reuse();

	// 追加HTTPヘッダの指定
	bool setHeader(const char ** headers);

	// 指定フォーム値のURLencode
	char * setForm(const char ** postForm);

	// GET発行
	bool httpGET(const char * url, bool isProxy);

	// POST発行
	bool httpPOST(const char * url, bool isProxy);

	// ダウンロード保存パス名を指定し、ダウンロードモードでの動作を開始する。
	// NULL指定で通常のオンメモリモードでの動作に戻る
	bool setDownload(const char * path);

	// 受信ステータス
	bool httpRECV();

	// 現在の受信サイズ
	s64 getSize();
	inline s64 getDwnldSize()	{ return m_receivedSize; }

	// 受信リソースの取得
	u8 * getRecvResource();

    // httpのstate取得 2013.2.13  追加
	int getHttpState();

	bool isMaintenance()										{ return this->m_maintenance; }
	bool hasHeader(const char* header, const char** value);
private:
	void clear();
	void init ();

	static s32	HTTPConnectionThread(void * hThread, void * data);
	static int	progress_func		(void* ctx, double t, double d, double ultotal, double ulnow);
	static size_t write_func		(char *ptr, size_t size, size_t nmemb, void *userdata); 
	static size_t headerReceive_func(void *ptr, size_t size, size_t nmemb, void *userdata);

	void		progress(u64 total, u64 download);
	size_t		write	(char *ptr, size_t size, size_t nmemb);
	void		download();

	// HTTP Error Code
	int			m_errorCode;
	int			m_tmpErrorCode;
	bool		m_bDataComplete;
	bool		m_bDownload;
	bool		m_bothFileAndMem;
	bool		m_post;
	bool		m_maintenance;
	const char*	m_url;
	void*		m_pCurl;
	const char*	m_pServerVersion;

	ITmpFile*	m_pTmpFile;
	s64			m_receivedSize;
	s64			m_writeIndex;
	u8*			m_receivedData;
	u8*			m_buffer;
	void*		m_thread;
public:
	volatile u32 m_threadStop;
private:
	bool		m_stopThread;

	// 追加HTTPヘッダ
	const char*	m_headers;
	const char** m_headerEntry;
	const char** m_postForm;
	u32*		m_headerEntryLen;
	u32			m_hdrlen;
	u32			m_headerEntryCount;
public:
	static		bool initHTTPLib();
	static		void releaseHTTPLib();
};

#else

class CKLBHTTPInterface
{
public:
	CKLBHTTPInterface();
	virtual ~CKLBHTTPInterface();

	// 追加HTTPヘッダの指定
	bool setHeader(const char ** headers);

	// 指定フォーム値のURLencode
	char * URLencode(char * retbuf, int maxlen, const char ** postForm);

	// GET発行
	inline bool httpGET(const char * url, bool isProxy) {
		return httpMethod("GET", "", url, isProxy, 0);
	}

	// POST発行
	inline bool httpPOST(const char * url, bool isProxy, const char * encodedForm) {
		char buf[1024];
		int postLen = strlen(encodedForm);
		sprintf(buf,
                "Content-type: application/x-www-form-urlencoded; charset=UTF-8\r\n"
                "Content-Length: %d\r\n", postLen);
		return httpMethod("POST", buf, url, isProxy, encodedForm);
	}

	// ダウンロード保存パス名を指定し、ダウンロードモードでの動作を開始する。
	// NULL指定で通常のオンメモリモードでの動作に戻る
	bool setDownload(const char * path);

	// 受信ステータス
	bool httpRECV();

	// 現在の受信サイズ
	inline s64 getSize		()	{ return m_rdSize;		}
	inline s64 getDwnldSize	()	{ return m_recv_size;	}
	// 受信リソースの取得
	inline u8 * getRecvResource() {
		if(!m_b_finished) return 0;	// まだ受信が終わっていない場合
		return m_http_recv;
	}

    // httpのstate取得 2013.2.13  追加
    inline int getHttpState	()	{ return m_http_state; }

private:
	// 受信情報のクリア
	inline void crearRecvResource() {
		KLBDELETEA(m_http_recv);
		m_buf_size = 0;
		m_recv_size = 0;
		m_b_finished = false;
	}
    
    // connect thread用
    inline void			setSocket		(IReadStream* _pSpcket) { m_pSocket = _pSpcket; }
    inline const char*	getConnectName	(void)		{ return m_pConnectName;		}
	// JOINTでのbodySize計算用に
	inline void			SetBodySize		(int _set)	{ m_test_body_length = _set;	}
	inline void			AddBodySize		(int _add)	{ m_test_body_length += _add;	}
	inline int			GetBodySize		(void)		{ return m_test_body_length;	}

	bool httpMethod(const char * method, const char * method_hdr, 
					const char * url, bool isProxy, const char * body);
	bool httpMethod_AfterConnect(void); // 上記関数内の処理をconnect終了後の処理と分割

	bool url_parse(const char * url);

	bool cmp_header(char * ptr, const char * str, size_t len);

	// Transfer-Encoding: chunked か否かを判定
	bool get_format(char * buf, bool * chunked, u64 * length);

	// chunkサイズを取得。
	char * get_chunk_size(char * buf, size_t len, size_t * chunk_size);
	int    find_crlf(const char * ptr, int len);

	// 送出中処理
	inline void sending() {
		m_pWRSock->writeBlock((void *)m_bufSend, m_sizeSend);
	}


	bool				m_proxy;
	const char		*	m_proxy_host;
	int					m_proxy_port;

	const char		*	m_url;
	const char		*	m_host;
	const char		*	m_path;
	int					m_port;

	// 追加HTTPヘッダ
	const char		*	m_headers;
	int					m_hdrlen;

	IReadStream		*	m_pSocket;
	IWriteStream	*	m_pWRSock;

	const char		*	m_bufSend;
	int					m_sizeSend;

	// 取得したリソース(コマンド実行結果)
	s64					m_rdSize;
	void			*	m_hThread;
	u8				*	m_http_recv;
	size_t				m_buf_size;		// 確保ずみバッファのサイズ
	size_t				m_recv_size;	// 受信済みサイズ
	size_t				m_total_size;	// header + body のサイズ
	size_t				m_rightsize;	// 現在の受信単位で読むべきサイズ
	int					m_sThreadSig;	// Thread を終了させる値
	bool				m_chunked;		// 送信形式が chunked であればtrueになる。
	bool				m_b_finished;	// 読み終わりフラグ

	bool				m_bDownload;	// ダウンロード読み込みモードフラグ
	ITmpFile		*	m_pTmpFile;		// ダウンロード先テンポラリ

    size_t              m_read_size;    // readBrockで読み込んでいるサイズの残り
    size_t              m_header_size;  // ヘッダーサイズ
    u64                 m_notchunk_length;  // chunkで無い場合のデータサイズ
    char*               m_pReadNow;     // 現在の見ている場所
    bool                m_bChunkDebug;
    int                 m_http_state;   // httpヘッダーのstate保存用 2013.2.13 追加
    int                 m_test_body_length;	// JOINTでのbodySize計算用に

    // connect thread用
    const char* m_pConnectName;
    const char* m_pMethod;
    const char* m_pMethod_header;
    const char* m_pBody;
    bool        m_bIsProxy;
    
    
	struct CHUNK {
		CHUNK	*	prev;
		CHUNK	*	next;
		size_t		size;
	};
	CHUNK			*	m_begin;
	CHUNK			*	m_end;

	CHUNK * create_chunk(size_t size);
	void remove_chunk(CHUNK * pChunk);
	inline void remove_last_chunk() { remove_chunk(m_end); }
	void read_finish(void);

	u8					m_tmpBuf[1025];
	size_t				m_tmpsize;
	typedef enum {
        E_CONNECT_WAITING,  // SocketのConnect待ち
		E_SENDING,	// Request送出中
		E_STARTUP,	// 開始

		E_RDHDR,	// HTTPヘッダ読み込み中 →ヘッダのみの処理にする

		E_RD_BODY_NOT_CHUNKED,  // chunkでは無いデータの場合
		E_RD_BODY_CHUNKED,      // chunkデータの場合


		// 単品bodyの場合
		E_RDBODY,	// リソース本体読み込み中

		// Transfer-Encoding: chunked の場合
		E_RDCHUNK,	// チャンク読み込み中
		E_NEXTCHUNK,// 次のチャンク読み込み待ち

		E_END		// 読み込み終了
	} STEP;

	STEP				m_eStep;

	enum {
		HEADER_BUF_SIZE			=	8192,
		BLOCK_SIZE				=	4096,
		MAX_BLOCK_IN_FRAME		=	8,

		ALLOC_SIZE				=	1024,

		RETRY					= 8,
	};

	static s32 ThreadSEND	(void * hThread, void * data);
	static s32 ThreadHTTP	(void * hThread, void * data);
	static s32 ThreadJOINT	(void * hThread, void * data);
	static s32 ThreadCONNECT(void * hThread, void * data);
public:
	static bool initHTTPLib		();
	static void releaseHTTPLib	();
};
#endif // Selection CURL lib.

#endif // CKLBHTTPInterface_h
