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
#ifndef CUnZip_h
#define CUnZip_h

#include <stdio.h>
#include <stdlib.h>

#include "zlib.h"
#include "unzip.h"
#pragma comment(lib, "zlib.lib")

#include "BaseType.h"
#include "ITmpFile.h"

/*!
* \class CUnZip
* \brief UnZip Class
* 
* 
*/
class CUnZip
{
public:
	CUnZip();
	CUnZip(const char * zip_path);
	virtual ~CUnZip();

	bool Open(const char * zip_path);

	inline bool getStatus() {
		return m_bReady;
	}
	inline unsigned long numEntry() { return m_globalInfo.number_entry; }
	bool readCurrentFileInfo();
	bool extractCurrentFile	(const char * extract_root);
	bool isFinishExtract	();
	bool gotoNextFile		();

	inline int getFinishedEntry() { return m_finished_entry; }

	// 展開処理
	bool unCompress(const char * extract_root);

protected:
	// ファイル個別の展開が終了したときに、そのファイルのパス名と展開サイズを引数として呼び出される。
	virtual bool afterExtract(const char * extract_path, bool isDirectory, size_t size);

private:
	bool	make_directory			(const char * dir_name);
	bool	CreateDirectoryReflex	(const char * strPath);
	bool	IsFileExist				(const char * strFilename);

	s32		ThreadExtract			(void * hThread, void * data);

	static s32 ThreadExtractEntry	(void * hThread, void * data);


	unzFile			m_hUnzip;
	unz_global_info	m_globalInfo;
    unz_file_info	m_fileInfo;
	char			m_currentPath[512];
	int				m_lenPath;

	ITmpFile	*	m_wrfile;
	unsigned long	m_dwSizeWrite;

	char		*	m_targetPath;
	bool			m_extractFinish;
	void		*	m_hThread;

	int				m_finished_entry;

	bool			m_bReady;

	enum {
		BUF_SIZE = 8192
	};
};


#endif // CUnZip_h
