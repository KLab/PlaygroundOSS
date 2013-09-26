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
#include "CPFInterface.h"
#include "CUnZip.h"
#include <string.h>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define IsShiftJIS(x) ((BYTE)((x ^ 0x20) - 0xA1) <= 0x3B)

CUnZip::CUnZip()
: m_hUnzip  (0)
, m_bReady  (false)
, m_finished_entry  (0) 
{
}

CUnZip::CUnZip(const char * zip_path)
: m_hUnzip      (0)
, m_bReady      (false)
, m_finished_entry  (0)
, m_wrfile      (NULL)
{
	Open(zip_path);
    memset(m_currentPath, 0, sizeof(m_currentPath));
}

CUnZip::~CUnZip()
{
	if(m_hUnzip) unzClose(m_hUnzip);
}

bool
CUnZip::Open(const char * zip_path)
{
	m_bReady = false;
	m_hUnzip = unzOpen(zip_path);
	if (!m_hUnzip){
		return false;
	}
	unzGetGlobalInfo(m_hUnzip, &m_globalInfo);
	m_bReady = true;
	m_finished_entry = 0;
	return true;
}


bool
CUnZip::afterExtract(const char * /*extract_path*/, bool /*isDirectory*/, size_t /*size*/)
{
	return true;
}

bool
CUnZip::IsFileExist(const char * strFilename)
{
#ifdef _WIN32
	return GetFileAttributes(strFilename) != 0xffffffff;
#else
	struct stat st;
	int ret = stat(strFilename, &st);
	return (!ret) ? true : false;
#endif
}

bool
CUnZip::make_directory(const char * dir_name)
{
#ifdef _WIN32
	return CreateDirectory(dir_name, 0) ? true : false;
#else
	// 平成24年11月27日(火)
	// ディレクトリ下にファイル等を作成する権限がなかったため、適切な権限を付与するよう変更
	bool ret = (!mkdir(dir_name, 0755)) ? true : false;
    if (ret == true) {
        CPFInterface::getInstance().platform().excludePathFromBackup(dir_name);
    }
    return ret;
#endif
}

bool
CUnZip::CreateDirectoryReflex(const char * assetPath)
{
	const char * strPath = CPFInterface::getInstance().platform().getFullPath(assetPath);
	char * strSubPath = new char [ strlen(strPath) + 1 ];
	for (const char * p = strPath; *p; p++) {
		if (*p == '/') {
			int len = p - strPath + 1;
			strncpy(strSubPath, strPath, len);
			strSubPath[len] = 0;
			if (!IsFileExist(strSubPath)) {
				if (!make_directory(strSubPath)) {
					delete [] strSubPath;
					delete [] strPath;
					return false;
				}
			}
		}
	}
	delete [] strSubPath;
	delete [] strPath;
	return true;
}

bool
CUnZip::readCurrentFileInfo()
{
	if(!m_bReady) return false;

	bool bResult = (UNZ_OK == unzGetCurrentFileInfo(m_hUnzip, &m_fileInfo, m_currentPath, sizeof(m_currentPath), 0, 0, 0, 0));
	m_lenPath = 0;
	if(bResult) {
		m_lenPath = strlen(m_currentPath);
		for (int i = 0; i < m_lenPath; ++i) {
			if (m_currentPath[i] == '\\') m_currentPath[i] = '/';
		}
	}
	return bResult;
}

bool
CUnZip::extractCurrentFile(const char * extract_root)
{
	if(!m_bReady) return false;

	m_targetPath = new char [ strlen(extract_root) + 512 + 1 ];
	strcpy(m_targetPath, extract_root);
	strcat(m_targetPath, m_currentPath);
	CreateDirectoryReflex(m_targetPath);	// 指定されたディレクトリが無ければ作る
	m_extractFinish = true;

	// ディレクトリの場合
	if (m_currentPath[m_lenPath - 1] == '/') {
		// 展開後処理の呼び出し
		m_finished_entry++;
		afterExtract(m_targetPath, true, 0);
		if (m_targetPath) {
			delete [] m_targetPath;
			m_targetPath = NULL;
		}
		return true;
	}

	// ファイルの場合
	if (unzOpenCurrentFile(m_hUnzip) != UNZ_OK) {
		if (m_targetPath) {
			delete [] m_targetPath;
			m_targetPath = NULL;
		}
		return false;
	}

	m_wrfile = CPFInterface::getInstance().platform().openTmpFile(m_targetPath);
	if(!m_wrfile) {
		// ファイルが書き込めない場合
		unzCloseCurrentFile(m_hUnzip);
		if (m_targetPath) {
			delete [] m_targetPath;
			m_targetPath = NULL;
		}
		return false;
	}

	// unzReadCurrentFile() は最初の一回のみ malloc() を呼ぶため、
	// その最初の一回はメインスレッドで実行してやる。
	unsigned char szBuffer[BUF_SIZE];
	unsigned long dwSizeRead;
	m_dwSizeWrite = 0;
    memset(szBuffer, 0, sizeof(szBuffer));
	if((dwSizeRead = unzReadCurrentFile(m_hUnzip, szBuffer, sizeof szBuffer)) > 0) {
		m_dwSizeWrite += m_wrfile->writeTmp(szBuffer, dwSizeRead);
        memset(szBuffer, 0, sizeof(szBuffer));
	}

	// この段階で展開が終了していたら、わざわざ別スレッドを立ち上げる必要はない。
	if(m_dwSizeWrite == m_fileInfo.uncompressed_size) {
		return true;
	}

	// 展開はこれから別スレッドで行う。スレッド立ち上げ前に展開終了ステータスを false にする
	m_extractFinish = false;
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	m_hThread = pForm.createThread(CUnZip::ThreadExtractEntry, this);

	return true;
}

bool
CUnZip::isFinishExtract()
{
	if(!m_extractFinish) {
		// 展開が終了していない場合はスレッドをウォッチ
		s32 status = 0;
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		bool result = pForm.watchThread(m_hThread, &status);
        if(result) { return false; }    // thread は実行中
		pForm.deleteThread(m_hThread);
		m_hThread = NULL;
		m_extractFinish = true;
	}

    if (m_wrfile) {
        delete m_wrfile;
        m_wrfile = NULL;
    }
	unzCloseCurrentFile(m_hUnzip);
/*
	if(m_dwSizeWrite != m_fileInfo.uncompressed_size) {
		delete [] m_targetPath;
		m_targetPath = 0;
		return true;
	}
*/
	// 展開後処理呼び出し
	m_finished_entry++;
	afterExtract(m_targetPath, false, m_dwSizeWrite);
    if (m_targetPath) {
        DEBUG_PRINT("[unzip] m_targetpath delete %s", m_targetPath);
        delete [] m_targetPath;
        m_targetPath = NULL;
    }
	return true;
}

s32
CUnZip::ThreadExtract(void * /* hThread */, void * /*data*/)
{
	unsigned char szBuffer[BUF_SIZE];
	unsigned long dwSizeRead;
    memset(szBuffer, 0, sizeof(szBuffer));
    while ((dwSizeRead = unzReadCurrentFile(m_hUnzip, szBuffer, sizeof szBuffer)) > 0) {
		m_dwSizeWrite += m_wrfile->writeTmp(szBuffer, dwSizeRead);
        memset(szBuffer, 0, sizeof(szBuffer));
	}

	// 展開が終わったのでスレッド終了
	return 0;
}

s32
CUnZip::ThreadExtractEntry(void * hThread, void * data)
{
	CUnZip * pUnZip = (CUnZip *)data;
	return pUnZip->ThreadExtract(hThread, data);
}

bool
CUnZip::gotoNextFile()
{
    if(!m_bReady) { return false; }
	return unzGoToNextFile(m_hUnzip) != UNZ_END_OF_LIST_OF_FILE;
}

bool
CUnZip::unCompress(const char * extract_root)
{
    if(!m_bReady) { return false; }
	do {
		if(!readCurrentFileInfo()) {
			return false;
		}
		extractCurrentFile(extract_root);
	} while (gotoNextFile());

	return true;
}
