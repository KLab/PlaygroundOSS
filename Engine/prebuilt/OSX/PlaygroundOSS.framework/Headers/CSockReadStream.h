#ifndef CSockReadStream_h
#define CSockReadStream_h

#include "BaseType.h"
#include "FileSystem.h"

class CSockWriteStream;

// ファイルアクセスクラス実装
class CSockReadStream : public IReadStream
{
	friend class CSockWriteStream;
private:
	enum {
		READ_BUFSIZ = 4096
	};
	// ファクトリとなるクラスメソッド以外で勝手に new はできない
	CSockReadStream();
    
public:
	// delete はできる。
	virtual ~CSockReadStream();
    
	// 指定されたIPアドレスまたはFQDNとPORTで CSockReadStream インスタンスを作り、そのポインタを返す。
	// このクラスメソッドはプラットフォーム側のために用意され、ゲーム側では IReadStream のポインタとして
	// 扱われるため、このメソッドを扱うことは出来ない(可能ではあるが推奨されない)
	static CSockReadStream *openStream(const char *path);
    
    
	s32 getSize();
	s32 getPosition();
	u8 readU8();
	u16 readU16();
	u32 readU32();
	float readFloat();
	bool readBlock(void *buffer, u32 byteSize);
	ESTATUS getStatus();
    
	int readU16arr(u16 *pBufferU16, int items);
	int readU32arr(u32 *pBufferU32, int items);
    
    
	IWriteStream *getWriteStream();
    
private:
	int sock_connect(const char *hostname, int port);
	bool readRingBuf();
	bool requestData(unsigned char *buf, size_t size);
	bool setStatus();
    
	inline size_t left_size() {
		size_t leftSize = 0;
		if (m_lastPos > m_getPos) {
			leftSize = m_lastPos - m_getPos;
		}
		else if (m_lastPos < m_getPos) {
			leftSize = m_lastPos + READ_BUFSIZ - m_getPos;
		}
		else {
			if (m_lastPos) {
				leftSize = READ_BUFSIZ;
			}
		}
		return leftSize;
	}
    
private:
	ESTATUS m_eStat;
	int m_fd;
    
	// 読み込みバッファ: 受信データは一度このバッファを経由する。
	u8 m_readBuf[READ_BUFSIZ];
	int m_lastPos;          // データ終端
	int m_getPos;           // データ始端
    
	// 同じ fd を使用して送出に使用される CSockWriteStream のポインタ
	CSockWriteStream *m_writeStream;
};


#endif // CSockReadStream_h
