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
#include "CWin32HttpStream.h"
#pragma comment(lib, "wininet.lib")
CWin32HttpStream::CWin32HttpStream() : m_fullpath(0), m_bufHTTP(0)
{}

CWin32HttpStream::~CWin32HttpStream()
{
	delete [] m_bufHTTP;
    delete [] m_fullpath;
}

CWin32HttpStream *
CWin32HttpStream::openStream(const char * path, const char * /*home*/)
{
    CWin32HttpStream * pStream = NULL;
    try {
        pStream = new CWin32HttpStream();
		if(!pStream){
			return NULL;
		}
        pStream->m_fullpath = NULL;

		char * buf = new char [ strlen(path) + 1 ];
		if(!buf) {
			pStream->m_eStat = NOT_FOUND;
			return pStream;
		}
		strcpy(buf, path);
		pStream->m_fullpath = (const char *)buf;

		bool bHttps = false;

		// 一応 HTTPS も対応する
        if(!strncmp(pStream->m_fullpath, "https://", 8)) { bHttps = true; }

		// WININET で HTTP リソースにアクセスする
		HINTERNET hInternet;
		HINTERNET hHttpRequest;

		hInternet = InternetOpen(
			"GameEngine HTTP Stream",
			INTERNET_OPEN_TYPE_PRECONFIG,
			NULL,
			NULL,
			0);

		if(hInternet == NULL) {
			pStream->m_eStat = NOT_FOUND;
			return pStream;
		}			

		hHttpRequest = InternetOpenUrl(
			hInternet,
			pStream->m_fullpath,
			NULL,
			0,
			INTERNET_FLAG_RELOAD,
			0);

		if(hHttpRequest == NULL) {
			InternetCloseHandle(hInternet);
			pStream->m_eStat = NOT_FOUND;
			return pStream;
		}

	
		DWORD dwLength  = 0;
		DWORD dwSize    = sizeof(dwLength);
		DWORD dwReadSize;
		BOOL bResult    = HttpQueryInfo(
			hHttpRequest,
			HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER,
			(LPVOID)&dwLength,
			&dwSize,
			NULL);

		if(!bResult) {
			InternetCloseHandle(hHttpRequest);
			InternetCloseHandle(hInternet);
			pStream->m_eStat = NOT_FOUND;
			return pStream;
		}
		char * httpbuf = new char [ dwLength ];
		if(!httpbuf) {
			InternetCloseHandle(hHttpRequest);
			InternetCloseHandle(hInternet);
			pStream->m_eStat = NOT_FOUND;
			return pStream;
		}

		bResult = InternetReadFile(
			hHttpRequest,
			httpbuf,
			dwLength,
			&dwReadSize);

		// ここで読み終わり

		InternetCloseHandle(hHttpRequest);
		InternetCloseHandle(hInternet);
		pStream->m_pos      = 0;
		pStream->m_bufHTTP  = (const u8 *)httpbuf;
		pStream->m_bufLen   = dwLength;

		if(bResult) {
			pStream->m_eStat = NORMAL;
		} else {
			pStream->m_eStat = NOT_FOUND;
		}
		return pStream;
        
    } catch(...) {
        delete pStream;
        return NULL;
    }
}

CWin32HttpStream *
CWin32HttpStream::openAssets(const char * path, const char * home)
{
	return openStream(path, home);
	// 中身が openStream() と全く同じになってしまったので。
}

s32 
CWin32HttpStream::getSize()
{
    return (s32)m_bufLen;
}

s32
CWin32HttpStream::getPosition()
{
    return (s32)m_pos;
}

u8       
CWin32HttpStream::readU8()
{
    return (u8)*(m_bufHTTP + m_pos);
}

u16      
CWin32HttpStream::readU16()
{
    if(m_pos > m_bufLen - 2) { return 0; }
	u16 ret = ((u16)m_bufHTTP[m_pos] << 8) | (u16)m_bufHTTP[m_pos+1];
	m_pos += 2;
	return ret;
}

u32      
CWin32HttpStream::readU32()
{
    if(m_pos > m_bufLen - 4) { return 0; }

	u32 ret = ((u32)m_bufHTTP[m_pos] << 24) | ((u32)m_bufHTTP[m_pos+1] << 16) |
		((u32)m_bufHTTP[m_pos+2] << 8) | (u32)m_bufHTTP[m_pos+3];
	m_pos += 4;
	return ret;
}

float    
CWin32HttpStream::readFloat()
{
    if(m_pos > m_bufLen - sizeof(float)) { return 0.0f; }
    float f;
	memcpy(&f, m_bufHTTP + m_pos, sizeof(float));
	m_pos += sizeof(float);
	return f;
}

bool     
CWin32HttpStream::readBlock(void * buffer, u32 byteSize)
{
    if(m_pos + byteSize > m_bufLen) { return false; }
	memcpy(buffer, m_bufHTTP + m_pos, byteSize);
	m_pos += byteSize;
	return true;
}

IReadStream::ESTATUS  
CWin32HttpStream::getStatus()
{
    return m_eStat;
}

IWriteStream *  
CWin32HttpStream::getWriteStream()
{
	return NULL;
}

int
CWin32HttpStream::readU16arr(u16 *pBufferU16, int items)
{
	size_t len = sizeof(u16) * items;
	int cnt = items;
	if(m_pos + len > m_bufLen) {
		cnt = (m_bufLen - m_pos) / sizeof(u16);
	}

	len = sizeof(u16) * cnt;
	memcpy(pBufferU16, m_bufHTTP + m_pos, len);
	m_pos += len;
    
    return cnt;
}

int
CWin32HttpStream::readU32arr(u32 *pBufferU32, int items)
{
	size_t len = sizeof(u32) * items;
	int cnt = items;
	if(m_pos + len > m_bufLen) {
		cnt = (m_bufLen - m_pos) / sizeof(u32);
	}

	len = sizeof(u32) * cnt;
	memcpy(pBufferU32, m_bufHTTP + m_pos, len);
	m_pos += len;
    
    return cnt;
}
