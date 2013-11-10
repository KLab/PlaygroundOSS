#ifndef CiOSWriteFileStream_h
#define CiOSWriteFileStream_h


#include "BaseType.h"
#include "FileSystem.h"

class CiOSReadFileStream;

class CiOSWriteFileStream : public IWriteStream
{
	friend class CiOSReadFileStream;
private:
	CiOSWriteFileStream(CiOSReadFileStream & rdStream);
	virtual ~CiOSWriteFileStream();
    
public:
	ESTATUS getStatus();
	s32 getPosition();
	void writeU8(u8 value); // Use cast to support s8
	void writeU16(u16 value);   // Use cast to support s16
	void writeU32(u32 value);   // Use cast to support s32
	void writeFloat(float);
	void writeBlock(void *buffer, u32 byteSize);
    
private:
	int m_fd;
	FILE *m_fp;
    
	ESTATUS m_eStat;
};

#endif // CiOSWriteFileStream_h
