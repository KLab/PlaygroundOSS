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
#ifndef CWin32MP3_h
#define CWin32MP3_h

#include <Windows.h>
#include <MMSystem.h>
#include <dsound.h>
#include "lame.h"
#include "encryptFile.h"
#pragma comment(lib, "libmp3lame.lib")


class CWin32MP3
{
public:
	CWin32MP3(const char * mp3path);
	virtual ~CWin32MP3();

	bool getFormat	(WAVEFORMATEX * format);
	bool readData	(char * buf, size_t max);

	inline bool		getStatus	()	{ return m_status; }
	inline size_t	getSize		()	{ return m_totalSize; }

private:
	bool loadMP3(const char * name);
	bool toRPCM	(short * buf, int frameCount, int stereo, size_t buf_size);

private:
	enum {
		FILE_BUF_SIZE	= 8192,
		MP3_MAX_SAMPLES = 1152,
		PCM_BUF_SIZE	= (MP3_MAX_SAMPLES * 4)
	};
	struct MP3BLOCK {
		MP3BLOCK	*	prev;
		MP3BLOCK	*	next;
		size_t			size;
		short			buf[ MP3_MAX_SAMPLES * 2 ];
	};

	bool					m_status;
	lame_global_flags	*	m_lgf;
	hip_t					m_hip;
	WAVEFORMATEX			m_format;
	size_t					m_totalSize;
	MP3BLOCK	*			m_begin;
	MP3BLOCK	*			m_end;
	short					m_bufL[ MP3_MAX_SAMPLES ];
	short					m_bufR[ MP3_MAX_SAMPLES ];
	inline u32 decryptSetup(const u8* ptr, const u8* hdr) {
        return m_decrypter.decryptSetup(ptr,hdr);
    }
private:
	CDecryptBaseClass   m_decrypter;
	inline void decrypt(void* ptr, u32 length) {
        m_decrypter.decryptBlck(ptr, length);
    }
};

#endif // CWin32MP3_h
