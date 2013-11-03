#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

#include "CPFInterface.h"
#include "iOSFileLocation.h"
#include "CiOSPathConv.h"
#include "CiOSReadFileStream.h"
#include "CiOSWriteFileStream.h"

#ifdef DEBUG_MEMORY
CiOSReadFileStream *CiOSReadFileStream::ms_pBegin = 0;
CiOSReadFileStream *CiOSReadFileStream::ms_pEnd;
#endif

// 論理トップレベルディレクトリと、物理ディレクトリパスの対応を行うテーブル。
const CiOSReadFileStream::LOCLIST CiOSReadFileStream::m_toplevel[3] = {
	{ "external/",  1, false },   // インストール後、更新の対象となる可変ファイル
	{ "install/",   0, true },   // インストール時に配置される固定ファイル
	{ 0, 0 }
};

CiOSReadFileStream::CiOSReadFileStream()
: m_bReadOnly(true)
, m_fd(-1)
, m_fp(0)
, m_eStat(CLOSED)
, m_fullpath(0)
, m_writeStream(0)
, m_decrypter()
#ifdef DEBUG_MEMORY
, m_pPrev(0), m_pNext(0)
#endif
{
#ifdef DEBUG_MEMORY
	m_pPrev = ms_pEnd;
	if (ms_pEnd) ms_pEnd->m_pNext = this;
	ms_pEnd = this;
	if (!ms_pBegin) ms_pBegin = this;
#endif
}

CiOSReadFileStream::~CiOSReadFileStream() {
	if (m_fp) fclose(m_fp);
	if (m_fd > 0) close(m_fd);
	m_fd = -1;
	m_eStat = CLOSED;
    
	delete[] m_fullpath;
#ifdef DEBUG_MEMORY
	if (m_pPrev) {
		m_pPrev->m_pNext = m_pNext;
	}
	else {
		ms_pBegin = m_pNext;
	}
	if (m_pNext) {
		m_pNext->m_pPrev = m_pPrev;
	}
	else {
		ms_pEnd = m_pPrev;
	}
#endif
}

CiOSReadFileStream *CiOSReadFileStream::openStream(const char *path, const char *home) {
	CiOSReadFileStream *pStream = 0;
	try {
		pStream = new CiOSReadFileStream();
		if (!pStream) {
			return 0;
		}
        
		pStream->m_fullpath = 0;
        
		CiOSPathConv& pathconv = CiOSPathConv::getInstance();
		pStream->m_fullpath = pathconv.fullpath(path);
        
		if (!pStream->m_fullpath) {
			// ファイルセグメントが指定されていない
			pStream->m_eStat = NOT_FOUND;
			return pStream;
		}
        
		// 物理パスができたので、ファイルをオープンする。
		pStream->m_fd = open(pStream->m_fullpath, O_RDONLY);
		if (pStream->m_fd < 0) {
			// オープンに失敗
			pStream->m_eStat = NOT_FOUND;
#ifdef DEBUG_MEMORY
			CPFInterface& pfif = CPFInterface::getInstance();
			CiOSReadFileStream *p = ms_pBegin;
			while (p) {
				pfif.platform().logging("not closed stream: %s", p->m_fullpath);
				p = p->m_pNext;
			}
			pfif.platform().logging("errno = %d", errno);
#endif
            //          klb_assertAlways("could not open.");
			return pStream;
		}
		// fopen 系関数を使うために fdopen で m_fp も作っておく
		pStream->m_fp = fdopen(pStream->m_fd, "rb");
		if (!pStream->m_fp) {
			close(pStream->m_fd);
			pStream->m_fd = -1;
			pStream->m_eStat = NOT_FOUND;
			return pStream;
		}
        
		// オープンに成功したので正常終了ステータスにする。
		pStream->m_eStat = NORMAL;
		return pStream;
	}
	catch (std::bad_alloc& ex)
	{
		delete pStream;
		return 0;
	}
}

CiOSReadFileStream *CiOSReadFileStream::openAssets(const char *path, const char *home) {
	return openStream(path, home);
#if 0
	CiOSReadFileStream *pStream = 0;
	try {
		pStream = new CiOSReadFileStream();
		if (!pStream) {
			return 0;
		}
		pStream->m_fullpath = 0;
        
		CiOSPathConv& pathconv = CiOSPathConv::getInstance();
		pStream->m_fullpath = pathconv.fullpath(path);
        
		if (!pStream->m_fullpath) {
			// ファイルが見つからなかった
			pStream->m_eStat = NOT_FOUND;
			return pStream;
		}
		// 物理パスができたので、ファイルをオープンする。
		pStream->m_fd = open(pStream->m_fullpath, O_RDONLY);
		if (pStream->m_fd < 0) {
			// オープンに失敗
			pStream->m_eStat = NOT_FOUND;
#ifdef DEBUG_MEMORY
			CPFInterface& pfif = CPFInterface::getInstance();
			CiOSReadFileStream *p = ms_pBegin;
			while (p) {
				pfif.platform().logging("not closed stream: %s", p->m_fullpath);
				p = p->m_pNext;
			}
			pfif.platform().logging("errno = %d", errno);
#endif
			return pStream;
		}
        
		// fopen 系関数を使うために fdopen で m_fp も作っておく
		pStream->m_fp = fdopen(pStream->m_fd, "rb");
		if (!pStream->m_fp) {
			close(pStream->m_fd);
			pStream->m_fd = -1;
			pStream->m_eStat = NOT_FOUND;
			return pStream;
		}
        
		// オープンに成功したので正常終了ステータスにする。
		pStream->m_decrypter.decryptSetup((const u8 *)pStream->m_fullpath);
		pStream->m_eStat = NORMAL;
		return pStream;
	}
	catch (std::bad_alloc& ex)
	{
		delete pStream;
		return 0;
	}
#endif
}

s32 CiOSReadFileStream::getSize() {
	struct stat file_stats;
	if (fstat(m_fd, &file_stats) < 0) {
		return -1;
	}
    
	return file_stats.st_size - (m_decrypter.m_useNew ? 4 : 0);
}

s32 CiOSReadFileStream::getPosition() {
	return (s32)(ftell(m_fp) - (m_decrypter.m_useNew ? 4 : 0));
}

u8 CiOSReadFileStream::readU8() {
	// とりあえず動かすため、fgetc() で実装する。
	u8 val = fgetc(m_fp);
	m_decrypter.decryptBlck(&val, 1);
	return (u8)val;
}

u16 CiOSReadFileStream::readU16() {
	u8 buf[2];
	if (1 == fread(buf, 2, 1, m_fp)) {
		m_decrypter.decryptBlck(buf, 2);
		u16 ret = ((u16)buf[0] << 8) | (u16)buf[1];
		return ret;
	}
	return 0;
}

u32 CiOSReadFileStream::readU32() {
	u8 buf[4];
	if (1 == fread(buf, 4, 1, m_fp)) {
		m_decrypter.decryptBlck(buf, 4);
		u32 ret = ((u32)buf[0] << 24) | ((u16)buf[1] << 16) | ((u16)buf[2] << 8) | (u16)buf[3];
		return ret;
	}
	return 0;
}

float CiOSReadFileStream::readFloat() {
	float f;
	if (1 == fread(&f, sizeof(float), 1, m_fp)) {
		m_decrypter.decryptBlck(&f, sizeof(float));
		return f;
	}
	return 0.0f;
}

bool CiOSReadFileStream::readBlock(void *buffer, u32 byteSize) {
	u32 cnt;
    
	cnt = fread(buffer, 1, byteSize, m_fp);
	m_decrypter.decryptBlck(buffer, cnt);
	return (cnt == byteSize) ? true : false;
}

IReadStream::ESTATUS CiOSReadFileStream::getStatus() {
	return m_eStat;
}

IWriteStream *CiOSReadFileStream::getWriteStream() {
	if (m_bReadOnly) return 0;  // m_bReadOnly が true の場合は read only 領域へのストリームなので、WriteStreamを返さない。
	if (!m_writeStream) m_writeStream = new CiOSWriteFileStream(*this);
	return m_writeStream;
}

int CiOSReadFileStream::readU16arr(u16 *pBufferU16, int items) {
	int cnt = fread(pBufferU16, sizeof(u16), items, m_fp);
	m_decrypter.decryptBlck(pBufferU16, sizeof(u16) * cnt);
    
	// iOS と Android/ARM では元々big endian なので、バイトオーダーの入れ替えは特に不要。
	// Windows 環境ではこれを使用して読む必要が生じるため、互換のために用意する。
	return cnt;
}

int CiOSReadFileStream::readU32arr(u32 *pBufferU32, int items) {
	int cnt = fread(pBufferU32, sizeof(u32), items, m_fp);
	m_decrypter.decryptBlck(pBufferU32, sizeof(u32) * cnt);
    
	// iOS と Android/ARM では元々big endian なので、バイトオーダーの入れ替えは特に不要。
	// Windows 環境ではこれを使用して読む必要が生じるため、互換のために用意する。
	return cnt;
}
