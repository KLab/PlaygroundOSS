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
//  CSockReadStream.h
//

#ifndef CSockReadStream_h
#define CSockReadStream_h

#include <WinSock.h>
#include "BaseType.h"
#include "FileSystem.h"

class CSockWriteStream;

class CSockReadStream : public IReadStream
{
    friend class CSockWriteStream;
private:
    enum {
        READ_BUFSIZ = 4096
    };
    CSockReadStream();

public:
    virtual ~CSockReadStream();

    static CSockReadStream * openStream(const char * path);
    

    s32     getSize		();
    s32     getPosition	();
    u8      readU8		();
    u16     readU16		();
    u32     readU32		();
    float   readFloat	();
    bool    readBlock	(void * buffer, u32 byteSize);
    ESTATUS getStatus	();
    
    int     readU16arr	(u16 * pBufferU16, int items);
    int     readU32arr	(u32 * pBufferU32, int items);
    
    
    IWriteStream * getWriteStream();
private:
    int     sock_connect	(const char * hostname, int port);
    bool    readRingBuf		();
    bool    requestData		(unsigned char * buf, size_t size);
    bool    setStatus		();

	inline size_t	left_size() {
		size_t leftSize = 0;
		if(m_lastPos > m_getPos) {
			leftSize = m_lastPos - m_getPos;
		} else if(m_lastPos < m_getPos) {
			leftSize = m_lastPos + READ_BUFSIZ - m_getPos;
		} else {
			if(m_lastPos) {
				leftSize = READ_BUFSIZ;
			}
		}
		return leftSize;
	}
private:
    ESTATUS     m_eStat;
    SOCKET      m_fd;
    
	u8          m_readBuf[ READ_BUFSIZ ];
    int         m_lastPos;
    int         m_getPos;

    CSockWriteStream    *   m_writeStream;
};


#endif // CSockReadStream_h
