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
#ifndef CWin32HttpStream_h
#define CWin32HttpStream_h

#include <Windows.h>
#include <WinInet.h>
#include <stdio.h>
#include "BaseType.h"
#include "FileSystem.h"

class CWin32HttpStream : public IReadStream
{
private:
    CWin32HttpStream();
    
public:
    virtual ~CWin32HttpStream();
    
    static CWin32HttpStream * openStream(const char * path, const char * home);
    
    static CWin32HttpStream * openAssets(const char * path, const char * home);
    
    s32     getSize		();
    s32     getPosition	();
    u8      readU8		();
    u16     readU16		();
    u32     readU32		();
    float   readFloat	();
    bool    readBlock	(void * buffer, u32 byteSize);
    ESTATUS getStatus	();
    
    int     readU16arr	(u16 * pBufferU16, int items);
    int     readU32arr	(u32 * PBufferU32, int items);
    
    IWriteStream * getWriteStream();

private:
    const char* m_fullpath;
    ESTATUS     m_eStat;

	const u8	*	m_bufHTTP;	// read HTTP resource
	DWORD			m_bufLen;	// read size
	DWORD			m_pos;		// read point
};

#endif // CWin32HttpStream_h
