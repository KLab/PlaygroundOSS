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
//  CiOSHttpStream.h
//  GameEngine
//
//

#ifndef CiOSHttpStream_h
#define CiOSHttpStream_h

#include "BaseType.h"
#include "FileSystem.h"

class CiOSHttpStream : public IReadStream
{
private:
    CiOSHttpStream();
public:
    virtual ~CiOSHttpStream();

    static CiOSHttpStream * openStream(const char * path, const char * home);
    static CiOSHttpStream * openAssets(const char * path, const char * home);

    s32 getSize();
    s32 getPosition();
    u8  readU8();
    u16 readU16();
    u32 readU32();
    float readFloat();
    bool readBlock(void * buffer, u32 byteSize);
    ESTATUS getStatus();
    
    int readU16Arr(u16 * pBufferU16, int items);
    int readU32Arr(u32 * pBufferU32, int items);

    IWriteStream * getWriteStream();
private:
    const char  *   m_fullpath;
    ESTATUS         m_eStat;

    const u8    *   m_bufHTTP;
    u32             m_bufLen;
    u32             m_pos;
};


#endif
