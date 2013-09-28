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
//  CAndroidReadFileStream.h
//
//

#ifndef CAndroidReadFileStream_h
#define CAndroidReadFileStream_h

#include "BaseType.h"
#include "FileSystem.h"
#include "encryptFile.h"

class CAndroidWriteFileStream;

// ファイルアクセスクラス実装
class CAndroidReadFileStream : public IReadStream
{
	friend class CAndroidWriteFileStream;
private:
    typedef struct {
        const char * top;
        const char * phisical;
        bool		 readonly;
    } LOCLIST;
    static const LOCLIST m_toplevel[];

    // ファクトリとなるクラスメソッド以外で勝手に new はできない
    CAndroidReadFileStream();
public:
    // delete はできる。
    virtual ~CAndroidReadFileStream();

    // 指定されたパスで CAndroidReadStream インスタンスを作り、そのポインタを返す。
    static CAndroidReadFileStream * openStream(const char * path, const char * home);
    
    // 指定されたパス名称を EXTERN -> INSTALL の順に検索し、先に見つかった方でCiOSReadStreamインスタンスを作る。
    static CAndroidReadFileStream * openAssets(const char * path, const char * home);

    s32     getSize();
    s32     getPosition();
    u8      readU8();
    u16     readU16();
    u32     readU32();
    float   readFloat();
    bool    readBlock(void * buffer, u32 byteSize);
    ESTATUS getStatus();
    
    int		readU16arr(u16 * pBufferU16, int items);
    int		readU32arr(u32 * pBufferU32, int items);

    IWriteStream * getWriteStream();
private:

    const char	  * m_fullpath;
    ESTATUS     m_eStat;
    FILE      * m_fp;
    int         m_fd;

    bool		m_bReadOnly;
    CAndroidWriteFileStream * m_writeStream;

public:
	inline u32 decryptSetup(const u8* ptr) {
		u8 hdr[4];
		hdr[0] = 0;
		hdr[1] = 0;
		hdr[2] = 0;
		hdr[3] = 0;

		if (m_fp) {
			fread(hdr, 1, 4, m_fp); 
		}

		u32 res = m_decrypter.decryptSetup(ptr, hdr);
		if (res == 0) {
			if (m_fp) {
				fseek(m_fp, 0, SEEK_SET);
			}
		}
		return res;
	}
private:
    CDecryptBaseClass m_decrypter;
    inline void decrypt(void* ptr, u32 length) {
        m_decrypter.decryptBlck(ptr, length);
    }
};


#endif
