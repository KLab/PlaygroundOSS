#ifndef CiOSReadFileStream_h
#define CiOSReadFileStream_h

#include "BaseType.h"
#include "FileSystem.h"
#include "encryptFile.h"

class CiOSWriteFileStream;

// ファイルアクセスクラス実装
class CiOSReadFileStream : public IReadStream
{
	friend class CiOSWriteFileStream;
private:
	typedef struct {
		const char *top;
		int loc;                // 0 で　install, 1 で external
		bool readonly;          // true の場合、その領域には書き込めない
	} LOCLIST;
	static const LOCLIST m_toplevel[];
    
	// ファクトリとなるクラスメソッド以外で勝手に new はできない
	CiOSReadFileStream();
    
	inline void decrypt(void *ptr, u32 length) {
		m_decrypter.decryptBlck(ptr, length);
	}
    
public:
	// delete はできる。
	virtual ~CiOSReadFileStream();
	inline u32 decryptSetup(const u8 *ptr) {
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
    
	// 指定されたパスで CiOSReadStream インスタンスを作り、そのポインタを返す。
	static CiOSReadFileStream *openStream(const char *path, const char *home);
    
	// 指定されたパス名称を EXTERN -> INSTALL の順に検索し、先に見つかった方でCiOSReadStreamインスタンスを作る。
	static CiOSReadFileStream *openAssets(const char *path, const char *home);
    
	s32 getSize();
	s32 getPosition();
	u8 readU8();
	u16 readU16();
	u32 readU32();
	float readFloat();
	bool readBlock(void *buffer, u32 byteSize);
	ESTATUS getStatus();
    
	int readU16arr(u16 *pBufferU16, int items);
	int readU32arr(u32 *PBufferU32, int items);
    
	IWriteStream *getWriteStream();
    
private:
	CDecryptBaseClass m_decrypter;
    
	const char *m_fullpath; //!< オープン後は基本不要だが、ファイルの物理的フルパス文字列
	ESTATUS m_eStat;
	FILE *m_fp;
	int m_fd;
	bool m_bReadOnly;           // true のときは read only なので、CiOSWriteStreamを返さない。
	CiOSWriteFileStream *m_writeStream;
    
#ifdef DEBUG_MEMORY
	CiOSReadFileStream *m_pPrev;
	CiOSReadFileStream *m_pNext;
    
	static CiOSReadFileStream *ms_pBegin;
	static CiOSReadFileStream *ms_pEnd;
#endif
};


#endif
