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
#ifndef __FILE_SYSTEM_KLB__
#define __FILE_SYSTEM_KLB__

class IWriteStream;

/*!
* \class IReadStream
* \brief Read Stream Interface
* 
* IReadStream defines an Interface for Read Stream classes.
* It provides methods for file decryption.
* Read data can either be u8, u16, u32, float or blocks.
*/
class IReadStream {
public:
	enum ESTATUS {
		NOT_FOUND,		// Failed open
		NORMAL,			// Open success
		NOT_AVAILABLE,	// Killed during read
        NOT_CONNECT,
		CLOSED			// File close
	};

	virtual ~IReadStream() { }
	
	virtual		s32		getSize		()	= 0;	// -1 : Undefined, >= 0 file size
	virtual		s32		getPosition	()	= 0;
	virtual 	u8		readU8		() 	= 0;	// Use cast to support s8
	virtual		u16		readU16		()	= 0;	// Use cast to support s16
	virtual		u32		readU32		()	= 0;	// Use cast to support s32
    
    virtual     int     readU16arr  (u16 * pBufferU16, int items) = 0;
    virtual     int     readU32arr  (u32 * pBufferU32, int items) = 0;
    
	virtual		float	readFloat	()	= 0;	//
	virtual		bool	readBlock	(void* buffer, u32 byteSize)	= 0;
	virtual		ESTATUS	getStatus	()	= 0;
	
	// Socket specialized
	virtual		IWriteStream* getWriteStream()  = 0;
};

/*!
* \class IWriteStream
* \brief Write Stream Interface
* 
* IWriteStream defines an Interface for Write Stream classes.
* It provides methods for file encryption.
* Written data can either be u8, u16, u32, float or blocks.
*/
class IWriteStream {
public:
	enum ESTATUS {
		// TODO WRITE Status...
        CAN_NOT_WRITE,
        NORMAL,
        NOT_AVAILABLE,
        CLOSED
	};

	virtual ~IWriteStream() { }
	
	virtual		ESTATUS	getStatus	()			= 0;
	virtual		s32		getPosition	()			= 0;
	virtual 	void	writeU8		(u8 value) 	= 0;	// Use cast to support s8
	virtual		void	writeU16	(u16 value)	= 0;	// Use cast to support s16
	virtual		void	writeU32	(u32 value)	= 0;	// Use cast to support s32
	virtual		void	writeFloat	(float)		= 0;
	virtual		void	writeBlock	(void* buffer, u32 byteSize)	= 0;
};

enum WRITE_MODE {
	CREATE_FILE	= 1,
};

IReadStream* 	openReadStream		(char* path);
IWriteStream*	openWriteStream		(char* path, WRITE_MODE writeMode); 
void			closeReadStream		(IReadStream* 	pReadStream);
void			closeWriteStream	(IWriteStream*	pWriteStream);

#endif
