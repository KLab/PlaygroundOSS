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
//  CAndroidReadFileStream.cpp
//
//
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
// #include <iostream>

#include "CAndroidPathConv.h"
#include "CAndroidReadFileStream.h"
#include "CAndroidWriteFileStream.h"
#include "AndroidFileLocation.h"
#include "CPFInterface.h"


// 論理トップレベルディレクトリと、物理ディレクトリパスの対応を行うテーブル。
const CAndroidReadFileStream::LOCLIST CAndroidReadFileStream::m_toplevel[3] = {
    { "external/",  PATH_EXTERN,  false  },   // インストール後、更新の対象となる可変ファイル
    { "install/",   PATH_INSTALL, true   },   // インストール時に配置される固定ファイル
    { 0, 0 }
};

CAndroidReadFileStream::CAndroidReadFileStream()
: m_bReadOnly(true)
, m_fd(-1)
, m_fp(0)
, m_eStat(CLOSED)
, m_fullpath(0)
, m_writeStream(0)
, m_decrypter()
{}

CAndroidReadFileStream::~CAndroidReadFileStream()
{
    if(m_fp) fclose(m_fp);
    m_fd = -1;
    m_eStat = CLOSED;    
    delete [] m_fullpath;
}

CAndroidReadFileStream *
CAndroidReadFileStream::openStream(const char * path, const char * home)
{
    CAndroidReadFileStream * pStream = 0;

    pStream = new CAndroidReadFileStream();
    if(!pStream) return 0;

    CAndroidPathConv& pathconv = CAndroidPathConv::getInstance();
    pStream->m_fullpath = pathconv.fullpath(path);

    if(!pStream->m_fullpath) {
        // ファイルセグメントが指定されていない
        pStream->m_eStat = NOT_FOUND;
        return pStream;
    }

    // 物理パスができたので、ファイルをオープンする。
    pStream->m_fd = open(pStream->m_fullpath, O_RDONLY);
    if(pStream->m_fd < 0) {
    	// オープンに失敗
    	pStream->m_eStat = NOT_FOUND;
    	return pStream;
    }
    // fopen 系関数を使うために fdopen で m_fp も作っておく
    pStream->m_fp = fdopen(pStream->m_fd, "rb");
    if(!pStream->m_fp) {
    	close(pStream->m_fd);
    	pStream->m_fd = -1;
    	pStream->m_eStat = NOT_FOUND;
    	return pStream;
    }
        
    // オープンに成功したので正常終了ステータスにする。
    pStream->m_eStat = NORMAL;
    return pStream;
}

CAndroidReadFileStream *
CAndroidReadFileStream::openAssets(const char * path, const char * home)
{
	// 今や内容が全く同じ
	return openStream(path, home);
}


s32 
CAndroidReadFileStream::getSize()
{
    struct stat file_stats;
    if(fstat(m_fd, &file_stats) < 0) {
        return -1;
    }

    return file_stats.st_size - (m_decrypter.m_useNew ? 4 : 0);
}

s32
CAndroidReadFileStream::getPosition()
{
    return (s32)(ftell(m_fp) - (m_decrypter.m_useNew ? 4 : 0));
}

u8       
CAndroidReadFileStream::readU8()
{
    // とりあえず動かすため、fgetc() で実装する。
	u8 val = fgetc(m_fp);
	decrypt(&val,1);
	return (u8)val;
}

u16      
CAndroidReadFileStream::readU16()
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
CAndroidReadFileStream::readU32()
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
CAndroidReadFileStream::readFloat()
{
    float f;
    if(1 == fread(&f, sizeof(float), 1, m_fp)) {
		decrypt(&f, sizeof(float));
        return f;
    }
    return 0.0f;
}

bool     
CAndroidReadFileStream::readBlock(void * buffer, u32 byteSize)
{
    u32 cnt;
    
    cnt = fread(buffer, 1, byteSize, m_fp);
	decrypt(buffer, cnt);
    return (cnt == byteSize) ? true : false; 
}

IReadStream::ESTATUS  
CAndroidReadFileStream::getStatus()
{
    return m_eStat;
}

IWriteStream *  
CAndroidReadFileStream::getWriteStream()
{
    if(m_bReadOnly) return 0;
    if(!m_writeStream) m_writeStream = new CAndroidWriteFileStream(*this);
    return m_writeStream;
}


int
CAndroidReadFileStream::readU16arr(u16 *pBufferU16, int items)
{
    int cnt = fread(pBufferU16, sizeof(u16), items, m_fp);
    decrypt(pBufferU16,sizeof(u16) * cnt);

    // iOS と Android/ARM では元々big endian なので、バイトオーダーの入れ替えは特に不要。
    // Windows 環境ではこれを使用して読む必要が生じるため、互換のために用意する。
    return cnt;
}

int
CAndroidReadFileStream::readU32arr(u32 *pBufferU32, int items)
{
    int cnt = fread(pBufferU32, sizeof(u32), items, m_fp);
    decrypt(pBufferU32,sizeof(u32) * cnt);

    // iOS と Android/ARM では元々big endian なので、バイトオーダーの入れ替えは特に不要。
    // Windows 環境ではこれを使用して読む必要が生じるため、互換のために用意する。
    return cnt;
}
