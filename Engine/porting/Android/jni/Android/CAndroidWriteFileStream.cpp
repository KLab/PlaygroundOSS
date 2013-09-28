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
//  CAndroidWriteFileStream.cpp
//
//
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <stdio.h>

#include "CAndroidWriteFileStream.h"
#include "CAndroidReadFileStream.h"


CAndroidWriteFileStream::CAndroidWriteFileStream(CAndroidReadFileStream& rdStream) : m_fd(-1), m_fp(0), m_eStat(CLOSED)
{
    if(rdStream.m_fp && rdStream.m_eStat == IReadStream::NORMAL) {
        fclose(rdStream.m_fp);
        rdStream.m_fp = 0;
        rdStream.m_fd = -1;
    }
    
    if(0 > (m_fd = open(rdStream.m_fullpath, O_CREAT|O_RDWR))) return;
    m_fp = fdopen(m_fd, "r+b");
    if(!m_fp) {
        close(m_fd);
        m_fd = -1;
        return;
    }
    rdStream.m_fd = m_fd;
    rdStream.m_fp = m_fp;    
    m_eStat = NORMAL;
}

// 必ず ReadStream 経由で破棄されるため、こちらではクローズしない
CAndroidWriteFileStream::~CAndroidWriteFileStream() {}

IWriteStream::ESTATUS
CAndroidWriteFileStream::getStatus()
{
    return m_eStat;
}

s32
CAndroidWriteFileStream::getPosition()
{
    m_eStat = NORMAL;
    return ftell(m_fp);
}

void
CAndroidWriteFileStream::writeU8(u8 value)
{
    m_eStat = NORMAL;
    if(EOF == fputc(value, m_fp)) {
        m_eStat = NOT_AVAILABLE;
    }
}

void
CAndroidWriteFileStream::writeU16(u16 value)
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
CAndroidWriteFileStream::writeU32(u32 value)
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
CAndroidWriteFileStream::writeFloat(float fval)
{
    m_eStat = NORMAL;
    if(1 > fwrite(&fval, sizeof(float), 1, m_fp)) {
        m_eStat = NOT_AVAILABLE;
    }
}

void
CAndroidWriteFileStream::writeBlock(void* buffer, u32 byteSize)
{
    m_eStat = NORMAL;
    if(1 > fwrite(buffer, byteSize, 1, m_fp)) {
        m_eStat = NOT_AVAILABLE;
    }
}
