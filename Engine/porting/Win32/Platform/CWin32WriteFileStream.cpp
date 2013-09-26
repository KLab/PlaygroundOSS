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
//  CWin32WriteFileStream.cpp
//
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <share.h>
#include <stdio.h>
#include <iostream>

#include "CWin32WriteFileStream.h"
#include "CWin32ReadFileStream.h"


CWin32WriteFileStream::CWin32WriteFileStream(CWin32ReadFileStream& rdStream) 
: m_fd      (-1)
, m_fp      (NULL)
, m_eStat   (CLOSED)
{
    if(rdStream.m_fp && rdStream.m_eStat == IReadStream::NORMAL) {
        fclose(rdStream.m_fp);
        rdStream.m_fp = NULL;
        rdStream.m_fd = -1;
    }

	if(_sopen_s(&m_fd, rdStream.m_fullpath, _O_CREAT | _O_RDWR, _SH_DENYRW, _S_IREAD | _S_IWRITE)) {
		return;
	}
    m_fp = _fdopen(m_fd, "r+b");
    if(!m_fp) {
        _close(m_fd);
        m_fd = -1;
        return;
    }
    rdStream.m_fd = m_fd;
    rdStream.m_fp = m_fp;    
    m_eStat = NORMAL;
}

CWin32WriteFileStream::~CWin32WriteFileStream() {}

IWriteStream::ESTATUS
CWin32WriteFileStream::getStatus()
{
    return m_eStat;
}

s32
CWin32WriteFileStream::getPosition()
{
    m_eStat = NORMAL;
    return ftell(m_fp);
}

void
CWin32WriteFileStream::writeU8(u8 value)
{
    m_eStat = NORMAL;
    if(EOF == fputc(value, m_fp)) {
        m_eStat = NOT_AVAILABLE;
    }
}

void
CWin32WriteFileStream::writeU16(u16 value)
{
    u8 arr[2];
    m_eStat = NORMAL;
    arr[0] = (value >> 8) & 0xff;
    arr[1] = value & 0xff;
    if(1 > fwrite(arr, 2, 1, m_fp)) {
        m_eStat = NOT_AVAILABLE;
    }
}

void
CWin32WriteFileStream::writeU32(u32 value)
{
    u8 arr[4];
    m_eStat = NORMAL;
    arr[0] = (value >> 24) & 0xff;
    arr[1] = (value >> 16) & 0xff;
    arr[2] = (value >> 8) & 0xff;
    arr[3] = value & 0xff;
    if(1 > fwrite(arr, 4, 1, m_fp)) {
        m_eStat = NOT_AVAILABLE;
    }
}

void
CWin32WriteFileStream::writeFloat(float fval)
{
    m_eStat = NORMAL;
    if(1 > fwrite(&fval, sizeof(float), 1, m_fp)) {
        m_eStat = NOT_AVAILABLE;
    }
}

void
CWin32WriteFileStream::writeBlock(void* buffer, u32 byteSize)
{
    m_eStat = NORMAL;
    if(1 > fwrite(buffer, byteSize, 1, m_fp)) {
        m_eStat = NOT_AVAILABLE;
    }
}
