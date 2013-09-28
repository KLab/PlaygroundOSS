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
//  CiOSWriteFileStream.h
//
//

#ifndef CAndroidWriteFileStream_h
#define CAndroidWriteFileStream_h


#include "BaseType.h"
#include "FileSystem.h"

class CAndroidReadFileStream;

class CAndroidWriteFileStream : public IWriteStream
{
    friend class CAndroidReadFileStream;
private:
    CAndroidWriteFileStream(CAndroidReadFileStream& rdStream);
    virtual ~CAndroidWriteFileStream();
    
public:
    ESTATUS	getStatus();
	s32	getPosition();
	void writeU8(u8 value);	// Use cast to support s8
	void writeU16(u16 value);	// Use cast to support s16
	void writeU32(u32 value);	// Use cast to support s32
	void writeFloat(float);
	void writeBlock(void* buffer, u32 byteSize);
    
private:
    int         m_fd;
    FILE    *   m_fp;
    
    ESTATUS     m_eStat;
};

#endif // CAndroidWriteFileStream_h
