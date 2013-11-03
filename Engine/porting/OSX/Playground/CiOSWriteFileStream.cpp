#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

#include "CiOSWriteFileStream.h"
#include "CiOSReadFileStream.h"


CiOSWriteFileStream::CiOSWriteFileStream(CiOSReadFileStream& rdStream) : m_fd(-1), m_fp(0), m_eStat(CLOSED) {
	if (rdStream.m_fp && rdStream.m_eStat == IReadStream::NORMAL) {
		fclose(rdStream.m_fp);
		rdStream.m_fp = 0;
		rdStream.m_fd = -1;
	}
    
	if (0 > (m_fd = open(rdStream.m_fullpath, O_CREAT | O_RDWR))) return;
	m_fp = fdopen(m_fd, "r+b");
	if (!m_fp) {
		close(m_fd);
		m_fd = -1;
		return;
	}
	rdStream.m_fd = m_fd;
	rdStream.m_fp = m_fp;
	m_eStat = NORMAL;
}

// 必ず ReadStream 経由で破棄されるため、こちらではクローズしない
CiOSWriteFileStream::~CiOSWriteFileStream() {
}

IWriteStream::ESTATUS CiOSWriteFileStream::getStatus() {
	return m_eStat;
}

s32 CiOSWriteFileStream::getPosition() {
	m_eStat = NORMAL;
	return ftell(m_fp);
}

void CiOSWriteFileStream::writeU8(u8 value) {
	m_eStat = NORMAL;
	if (EOF == fputc(value, m_fp)) {
		m_eStat = NOT_AVAILABLE;
	}
}

void CiOSWriteFileStream::writeU16(u16 value) {
	u8 arr[2];
	m_eStat = NORMAL;
	arr[0] = (value >> 8) & 0xff;
	arr[1] = value & 0xff;
	if (1 > fwrite(arr, 2, 1, m_fp)) {
		m_eStat = NOT_AVAILABLE;
	}
}

void CiOSWriteFileStream::writeU32(u32 value) {
	u8 arr[4];
	m_eStat = NORMAL;
	arr[0] = (value >> 24) & 0xff;
	arr[1] = (value >> 16) & 0xff;
	arr[2] = (value >> 8) & 0xff;
	arr[3] = value & 0xff;
	if (1 > fwrite(arr, 4, 1, m_fp)) {
		m_eStat = NOT_AVAILABLE;
	}
}

void CiOSWriteFileStream::writeFloat(float fval) {
	m_eStat = NORMAL;
	if (1 > fwrite(&fval, sizeof(float), 1, m_fp)) {
		m_eStat = NOT_AVAILABLE;
	}
}

void CiOSWriteFileStream::writeBlock(void *buffer, u32 byteSize) {
	m_eStat = NORMAL;
	if (1 > fwrite(buffer, byteSize, 1, m_fp)) {
		m_eStat = NOT_AVAILABLE;
	}
}
