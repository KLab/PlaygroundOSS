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
#include "CWin32Platform.h"
#include "CWin32MP3.h"
#include "encryptFile.h"

CWin32MP3::CWin32MP3(const char * mp3name) 
: m_status  (true)
, m_lgf     (NULL)
, m_hip     (0)
, m_begin   (NULL)
, m_end     (NULL)
, m_decrypter()
{
	// Lame の初期化
	m_lgf = lame_init();
    if(!m_lgf) { m_status = false; }

	// Lameの初期化に成功していたらdecode関数の初期化
	if(m_status && !(m_hip = hip_decode_init())) {
		lame_close(m_lgf);
		m_status = false;
	}
    if(m_status) { m_status = loadMP3(mp3name); }
}

CWin32MP3::~CWin32MP3()
{

	MP3BLOCK * block = m_begin;
	while(block) {
		MP3BLOCK * next = block->next;
		delete block;
		block = next;
	}

	if(m_hip) {
		hip_decode_exit(m_hip);
		m_hip = 0;
	}
	if(m_lgf) {
		lame_close(m_lgf);
		m_lgf = 0;
	}
}

bool
CWin32MP3::toRPCM(short * buf, int frameCount, int stereo, size_t buf_size)
{
    if(buf_size < ((size_t)frameCount) * 2 * stereo) { return false; }

	short * p = buf;
	short * pL = m_bufL;
	short * pR = m_bufR;
	while(frameCount--) {
		*p++ = *pL++;
		if(stereo == 2) {
			*p++ = *pR++;
		}
	}
	return true;
}

bool
CWin32MP3::getFormat(WAVEFORMATEX * format)
{
	memcpy(format, &m_format, sizeof(WAVEFORMATEX));
	return true;
}

bool
CWin32MP3::readData(char * buf, size_t max)
{
	short * ptr     = (short *)buf;
	size_t maxlen   = max / 2;

	MP3BLOCK * block = m_begin;
	while(block && maxlen > 0)
	{
		size_t size = block->size;
        if(maxlen < size) { size = maxlen; }
		memcpy(ptr, block->buf, size * 2);
		ptr     += size;
		maxlen  -= size;
		block   = block->next;
	}
    if(block->next) { return false; }
	return true;
}

bool
CWin32MP3::loadMP3(const char * name)
{
	const char * soundpath = name;
	char * pBuf = new char [ FILE_BUF_SIZE ];
	FILE * rfp;

	rfp = fopen(soundpath, "rb");
	if(!rfp) return false;
	
	if (CWin32Platform::g_useDecryption) {
		u8 hdr[4];
		hdr[0] = 0;
		hdr[1] = 0;
		hdr[2] = 0;
		hdr[3] = 0;
		fread(hdr,1,4,rfp);
		u32 hasHeader = decryptSetup((const u8*)name, hdr);
		if (hasHeader == 0) {
			fseek(rfp, 0, SEEK_SET);
		}
	}

	size_t nSize, nPos;
	size_t headerSize;
	s32 skipSamples = 0;

	nSize = fread(pBuf, 1, FILE_BUF_SIZE, rfp);
	if(nSize < 4) {
		klb_assert(nSize, "CWin32AudioMgr::loadMP3(): fread failed.");
		klb_assertAlways("too small file size.");
		delete [] pBuf;
		fclose(rfp);
		return false;
	}
	
	decrypt(pBuf,nSize);

	nPos = (size_t)0;
	if(!memcmp(pBuf, "ID3", 3)) {
		if(nSize < 10) {
			nPos = fread(pBuf + nSize, 1, 10 - nSize, rfp);
            if (nPos + nSize < 10) {
					klb_assert(nPos + nSize, "CWin32AudioMgr::loadMP3(): fread failed.");
					klb_assertAlways("too small file size.");
					delete [] pBuf;
					fclose(rfp);
					return false;
			}

			decrypt(pBuf + nSize,nPos);

            nSize += nPos;
        }
		headerSize = ((size_t)(pBuf[6] & 0x7F) << 21) |
            ((size_t)(pBuf[7] & 0x7F) << 14) |
            ((size_t)(pBuf[8] & 0x7F) << 7) |
            (size_t)(pBuf[9] & 0x7F);
		if(nSize - 10 >= headerSize) {
			nPos = 10 + headerSize;
			nSize -= nPos;
		} 
		else {
			// ID3データをスキップ
			while(headerSize) {
				if(headerSize > FILE_BUF_SIZE) {
					nSize = FILE_BUF_SIZE;
				} else {
					nSize = headerSize;
				}
				nPos = fread(pBuf, 1, nSize, rfp);
				if(!nPos) {
					klb_assert(nPos, "CWin32AudioMgr::loadMP3(): fread failed.");
					delete [] pBuf;
					fclose(rfp);
					return false;
				}
	
				decrypt(pBuf,nPos);

				headerSize -= (int)nPos;
			}
			if(!headerSize) {
				nPos  = 0;
				nSize = 0;
			}
		}
	}

	// ID3タグ情報をスキップしたので、再生に必要なヘッダ情報取得
	int decodeCount, nEncDelay, nEncPadding;
	mp3data_struct mp3data;

	decodeCount = -1;
	nEncDelay = nEncPadding = -1;
	mp3data.header_parsed = 0;
	for(;;) {
		if(nSize) {
			decodeCount = hip_decode1_headersB(m_hip, (unsigned char *)pBuf + nPos, nSize,
												m_bufL, m_bufR, &mp3data, &nEncDelay, &nEncPadding);

			if(decodeCount < 0) {
				klb_assert(decodeCount >= 0, "CWin32AudioMgr::loadMP3(): hip_decode1_headersB() failed.");
				delete [] pBuf;
				fclose(rfp);
				return false;
			}
			nPos = 0;
            if(mp3data.header_parsed) { break; }
		}

		// 元の評価式だとFILE_BUF_SIZEピッタリで読めた時に死ぬので、eofに達した時点でヘッダが読めなかったときにエラーを返すように変更。
		nSize = fread(pBuf, 1, FILE_BUF_SIZE, rfp);
		if(!nSize) {
	
			decrypt(pBuf,nSize);

			// 一回分のreadバッファでヘッダとデータが両方パース出来てしまった場合は、
            // もう一度デコーダを呼ばないとheader_parsedフラグが立たないようなので、修正を追記。
            // 参考：http://fossies.org/dox/xbmc-11.0/mpglib__interface_8c_source.htmldecode1_headersB_clipchoice 
            //       decode1_headersB_clipchoice関数
            decodeCount = hip_decode1_headers(m_hip, (unsigned char *)pBuf + nPos, nSize, m_bufL, m_bufR, &mp3data);

            if(decodeCount < 0)
            {
				klb_assert(decodeCount >= 0, "CWin32AudioMgr::loadMP3(): hip_decode1_headersB() failed.");
                delete [] pBuf;
                fclose(rfp);
                return false;
            }
            nPos = 0;
            if(mp3data.header_parsed) {
                break;
            } else {
                //klb_assertAlways("could not parse mp3 header");        // ファイルの末尾まで読み終わっているのでそれ以降はない
                delete [] pBuf;
                fclose(rfp);
                return false;
            }
		}
	}
	if(decodeCount < 0) {
		delete [] pBuf;
		fclose(rfp);
		return false;
	} else {
		if( nEncDelay > -1 || nEncPadding > -1 ) {
			if( nEncDelay > -1 ) {
				skipSamples = 528 + 1 + nEncDelay;
			}
			if( nEncPadding > -1 ) {
				nEncPadding -= (528 + 1);
			}
		} else {
			skipSamples = 528 + 1 + lame_get_encoder_delay(m_lgf);
		}
	}

	// WAVEFORMATEX 構造体を生成。具体的には info->format を埋める。
	m_format.wFormatTag     = WAVE_FORMAT_PCM;
	m_format.nChannels      = (WORD)mp3data.stereo;
	m_format.nSamplesPerSec = (DWORD)mp3data.samplerate;
	m_format.wBitsPerSample = 16;
	m_format.nBlockAlign    = m_format.nChannels * (m_format.wBitsPerSample / 8);
	m_format.nAvgBytesPerSec = m_format.nSamplesPerSec * m_format.nBlockAlign;
	m_format.cbSize         = 0;

	// 最初のブロックを作る
	MP3BLOCK * pBlock = NULL;
	m_begin = m_end = NULL;
	m_totalSize = 0;

	// デコードする。
	int hdrPos, nowSample;
	hdrPos      = 0;
	nowSample   = 0;
	for(;;) {
		if(!pBlock) {
			pBlock       = new MP3BLOCK;
			pBlock->size = 0;
			pBlock->prev = m_end;
			pBlock->next = NULL;
			if(pBlock->prev) {
				pBlock->prev->next = pBlock;
			} else {
				m_begin = pBlock;
			}
			m_end = pBlock;
		}

		nSize = 1;
		if(!decodeCount) {
			decodeCount = hip_decode1(m_hip, (unsigned char *)pBuf, 0, m_bufL, m_bufR);
			while(!decodeCount) {
				nSize = fread(pBuf, 1, FILE_BUF_SIZE, rfp);
				if(!nSize) {
					break;
				}
	
				decrypt(pBuf,nSize);

				decodeCount = hip_decode1(m_hip, (unsigned char *)pBuf, nSize, m_bufL, m_bufR);
				if(decodeCount < 0) {
					klb_assert(decodeCount >= 0, "CWin32AudioMgr::loadMP3(): hip_decode1() failed.");
					fclose(rfp);
					delete [] pBuf;
					return false;
				}
			}
		}
		if(!nSize || decodeCount < 0) {
			break;
		}

		// 最初のサンプルスキップ
		if( skipSamples ) {
			if( decodeCount < skipSamples ) {
				skipSamples -= decodeCount;
				continue;
			}
			memmove(&m_bufL[0], &m_bufL[skipSamples], sizeof(short) * (decodeCount - skipSamples));
			memmove(&m_bufR[0], &m_bufR[skipSamples], sizeof(short) * (decodeCount - skipSamples));
			decodeCount -= skipSamples;
			skipSamples = 0;
		}

		// 最後のサンプルスキップ
		if(nEncPadding > 0 && feof(rfp)) {
			decodeCount = (decodeCount < nEncPadding) ? 0 : (decodeCount - nEncPadding);
		}
		if(nowSample + decodeCount > mp3data.nsamp) nowSample = mp3data.nsamp - nowSample;

		

		toRPCM(pBlock->buf, decodeCount, mp3data.stereo, PCM_BUF_SIZE);
		pBlock->size = decodeCount * mp3data.stereo;
		m_totalSize += pBlock->size * 2;	// byte unit
		pBlock      = NULL;

		nowSample   += decodeCount;
		decodeCount = 0;
	}

	// 使用したリソースを解放する
	delete [] pBuf;
	fclose(rfp);

	return true;
}
