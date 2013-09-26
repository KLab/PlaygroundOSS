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
#ifndef CWin32TmpFile_h
#define CWin32TmpFile_h

#include <Windows.h>
#include "ITmpFile.h"

class CWin32TmpFile : public ITmpFile
{
public:
	CWin32TmpFile(const char * path);
	virtual ~CWin32TmpFile();

	virtual size_t	writeTmp(void * ptr, size_t size);

	inline bool		isReady	() { return (m_hHandle) ? true : false; }
private:
	const char	*	m_fullpath;
	HANDLE			m_hHandle;
};

#endif // CWin32TmpFile_h
