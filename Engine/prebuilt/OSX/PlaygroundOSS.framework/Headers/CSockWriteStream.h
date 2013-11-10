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
	CSockWriteStream(CSockReadStream & rdStream);
	virtual ~CSockWriteStream();
    
	bool sendData(unsigned char *buffer, size_t sndSize);
    
public:
	ESTATUS getStatus();
	s32 getPosition();
	void writeU8(u8 value);         // Use cast to support s8
	void writeU16(u16 value);           // Use cast to support s16
	void writeU32(u32 value);           // Use cast to support s32
	void writeFloat(float);
	void writeBlock(void *buffer, u32 byteSize);
    
private:
	int m_fd;
	ESTATUS m_eStat;
};

#endif // CSockWriteStream_h
