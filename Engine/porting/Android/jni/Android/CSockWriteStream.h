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
//  CSockWriteStream.h
//
//

#ifndef CSockWriteStream_h
#define CSockWriteStream_h

#include "BaseType.h"
#include "FileSystem.h"

class CSockReadStream;

// ファイルアクセスクラス実装
class CSockWriteStream : public IWriteStream
{
    friend class CSockReadStream;
private:
    CSockWriteStream(CSockReadStream& rdStream);
    virtual ~CSockWriteStream();
    
    bool    sendData(unsigned char * buffer, size_t sndSize);
public:	
	ESTATUS	getStatus	();
	s32		getPosition	();
	void	writeU8		(u8 value);	// Use cast to support s8
	void	writeU16	(u16 value);	// Use cast to support s16
	void	writeU32	(u32 value);	// Use cast to support s32
	void	writeFloat	(float);
	void	writeBlock	(void* buffer, u32 byteSize);

private:
    int         m_fd;
    ESTATUS     m_eStat;
};

#endif // CSockWriteStream_h

