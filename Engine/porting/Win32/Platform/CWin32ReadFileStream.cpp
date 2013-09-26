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
//  CWin32ReadFileStream.cpp
//
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <share.h>
#include <stdio.h>

#include <iostream>

#include "Win32FileLocation.h"
#include "CWin32PathConv.h"
#include "CWin32ReadFileStream.h"
#include "CWin32WriteFileStream.h"

CWin32ReadFileStream::CWin32ReadFileStream()
: m_bReadOnly   (true)
, m_fd          (-1)
, m_fp          (NULL)
, m_eStat       (CLOSED)
, m_fullpath    (NULL)
, m_writeStream (NULL)
, m_decrypter   ()
{
}

CWin32ReadFileStream::~CWin32ReadFileStream()
{
	//if(m_fd > 0) { _close(m_fd); }
    if(m_fp) { fclose(m_fp); }
    m_fd    = -1;
    m_eStat = CLOSED;
    
    delete [] m_fullpath;
}


CWin32ReadFileStream *
CWin32ReadFileStream::openStream(const char * path, const char * /*home*/)
{
    CWin32ReadFileStream * pStream = NULL;
    try {
        pStream = new CWin32ReadFileStream();
		if(!pStream){
			return NULL;
		}
        pStream->m_fullpath = NULL;
        
        CWin32PathConv& pathconv = CWin32PathConv::getInstance();
        pStream->m_fullpath      = pathconv.fullpath(path);

        if(!pStream->m_fullpath) {
            pStream->m_eStat = NOT_FOUND;
            return pStream;
        }
        
		int result = _sopen_s(&(pStream->m_fd), pStream->m_fullpath, _O_RDONLY | _O_BINARY, _SH_DENYRW, 0);
        if(result != 0) {
			pStream->m_eStat = NOT_FOUND;
            return pStream;
        }
        pStream->m_fp = _fdopen(pStream->m_fd, "rb");
        if(!pStream->m_fp) {
            _close(pStream->m_fd);
            pStream->m_fd = -1;
            pStream->m_eStat = NOT_FOUND;
            return pStream;
        }
        
        pStream->m_eStat = NORMAL;
        return pStream;
        
    } catch(...) {
        delete pStream;
        return NULL;
    }
}

CWin32ReadFileStream *
CWin32ReadFileStream::openAssets(const char * path, const char * home)
{
	return openStream(path, home);
	// 中身が openStream() と全く同じになってしまったので。
}

s32 
CWin32ReadFileStream::getSize()
{
    struct _stat file_stats;
    if(_fstat(m_fd, &file_stats) < 0) {
        return -1;
    }
	return file_stats.st_size - (m_decrypter.m_useNew ? 4 : 0);
}

s32
CWin32ReadFileStream::getPosition()
{
    return (s32)(ftell(m_fp) - (m_decrypter.m_useNew ? 4 : 0));
}

u8       
CWin32ReadFileStream::readU8()
{
	u8 val = fgetc(m_fp);
	decrypt(&val,1);
	return (u8)val;
}

u16      
CWin32ReadFileStream::readU16()
{
	u8 buf[2];
	if(1 == fread(buf, 2, 1, m_fp)) {
		decrypt(buf,2);
		u16 ret = ((u16)buf[0] << 8) | (u16)buf[1];
		return ret;
	}
	return 0;
}

u32      
CWin32ReadFileStream::readU32()
{
	u8 buf[4];
	if(1 == fread(buf, 4, 1, m_fp)) {
		decrypt(buf,4);
		u32 ret = ((u32)buf[0] << 24) | ((u16)buf[1] <<16) | ((u16)buf[2] << 8) | (u16)buf[3];
		return ret;
	}
	return 0;
}

float    
CWin32ReadFileStream::readFloat()
{
	float f;
	if(1 == fread(&f, sizeof(float), 1, m_fp)) {
		decrypt(&f, sizeof(float));
		return f;
	}
	return 0.0f;
}

bool     
CWin32ReadFileStream::readBlock(void * buffer, u32 byteSize)
{
	u32 cnt;
    
	cnt = fread(buffer, 1, byteSize, m_fp);
	decrypt(buffer, cnt);
	return (cnt == byteSize) ? true : false; 
}

IReadStream::ESTATUS  
CWin32ReadFileStream::getStatus()
{
    return m_eStat;
}

IWriteStream *  
CWin32ReadFileStream::getWriteStream()
{
    if(m_bReadOnly) { return NULL; }
	if(!m_writeStream) { 
        m_writeStream = new CWin32WriteFileStream(*this);
    }
    return m_writeStream;
}

int
CWin32ReadFileStream::readU16arr(u16 *pBufferU16, int items)
{
    int cnt = fread(pBufferU16, sizeof(u16), items, m_fp);
	decrypt(pBufferU16,sizeof(u16) * cnt);    
    return cnt;
}

int
CWin32ReadFileStream::readU32arr(u32 *pBufferU32, int items)
{
    int cnt = fread(pBufferU32, sizeof(u32), items, m_fp);    
	decrypt(pBufferU32,sizeof(u32) * cnt);
    return cnt;
}
