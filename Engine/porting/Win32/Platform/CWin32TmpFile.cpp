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


#include "CWin32PathConv.h"
#include "CWin32TmpFile.h"

CWin32TmpFile::CWin32TmpFile(const char * path)
{
	const char * ptr = path;
	if(!strncmp("file://", path, 7)) ptr += 7;
	m_fullpath = CWin32PathConv::getInstance().fullpath(ptr);
	m_hHandle = CreateFile(	m_fullpath,
							GENERIC_WRITE, 
							0,
							0,
							CREATE_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,
							0);
}

CWin32TmpFile::~CWin32TmpFile()
{
	if(m_hHandle) {
		FlushFileBuffers(m_hHandle);
		CloseHandle(m_hHandle);
	}
	delete [] m_fullpath;
}

size_t
CWin32TmpFile::writeTmp(void * ptr, size_t size)
{
	DWORD dwWrittenSize = 0;
	WriteFile(m_hHandle, ptr, size, &dwWrittenSize, 0);
	return (size_t)dwWrittenSize;
}
