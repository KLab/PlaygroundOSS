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
// Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.
// Further optimization commited by R.Piquois <laxer3a@hotmail.com>
//
#include "UTF8Parse.h"

// 10x4 + 11x4 = 84 byte
static const u32 utf8d[] = {
	/* Original compacted table ==> Need to reverse the BIT by quad.
	0x00000000,	// 0
	0x11111111,	// 1
	0x22222222,	// 2
	0x33333433,	// 3	--> Special pattern.
	0x88222222,	// 4	--> Special pattern.
	0xA3333333,	// 5	--> Special pattern.
	0xB6665888,	// 6	--> Special pattern.
	0x77777777,	// 7
	0x88888888,	// 8
	0x99999999,	// 9
	*/
	0x00000000,	// 0
	0x11111111,	// 1
	0x22222222,	// 2
	0x33433333,	// 3	--> Special pattern.
	0x22222288,	// 4	--> Special pattern.
	0x3333333A,	// 5	--> Special pattern.
	0x8885666B,	// 6	--> Special pattern.
	0x77777777,	// 7
	0x88888888,	// 8
	0x99999999,	// 9

	// State Table Compressed Entry.
	0x17853210,	// IT0
	0x11116411,	// IT1
	0x11111111,	// IT2
	0x01111101,	// IT3
	0x11111101,	// IT4
	0x21111121,	// IT5
	0x11111121,	// IT6
	0x21111111,	// IT7
	0x31111111,	// IT8
	0x11111131,	// IT9
	0x31111131,	// ITA
};             

#define IT0	(10)
#define IT1	(11)
#define IT2	(12)
#define IT3	(13)
#define IT4	(14)
#define IT5	(15)
#define IT6	(16)
#define IT7	(17)
#define IT8	(18)
#define IT9	(19)
#define ITA	(20)

// Could compact this table in 16 bytes, but overhead of shift and decode is pretty pointless.
// 32 Bytes.
static const u8 code[] = {
	/*
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, // 00..1f
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, // 20..3f
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, // 40..5f
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, // 60..7f
	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 9,9,9,9,9,9,9,9, 9,9,9,9,9,9,9,9, // 80..9f
	7,7,7,7,7,7,7,7, 7,7,7,7,7,7,7,7, 7,7,7,7,7,7,7,7, 7,7,7,7,7,7,7,7, // a0..bf
	8,8,2,2,2,2,2,2, 2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2, // c0..df
	A,3,3,3,3,3,3,3, 3,3,3,3,3,4,3,3, // e0..ef
	B,6,6,6,5,8,8,8, 8,8,8,8,8,8,8,8, // f0..ff
	*/
	0,0,0,0, // 00..1f
	0,0,0,0, // 20..3f
	0,0,0,0, // 40..5f
	0,0,0,0, // 60..7f
	1,1,9,9, // 80..9f
	7,7,7,7, // A0..BF
	4,2,2,2, // C0..DF
	5,3,6,8, // E0..FF
};

// 18 Byte table.
static const u8 code2[] = {
/*	Original, non reverse packed.
	0x01,0x23,0x58,0x71,0x11,0x46,0x11,0x11, // s0..s0
	0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,
	0x10,0x11,0x11,0x10,0x10,0x11,0x11,0x11, // s1..s2
	0x12,0x11,0x11,0x12,0x12,0x11,0x11,0x11,
	0x11,0x11,0x11,0x12,0x11,0x11,0x11,0x11, // s3..s4
	0x12,0x11,0x11,0x11,0x12,0x11,0x11,0x11,
	0x11,0x11,0x11,0x13,0x13,0x11,0x11,0x11, // s5..s6
	0x13,0x11,0x11,0x13,0x13,0x11,0x11,0x11,
	0x13,0x11,0x11,0x11,0x11,0x11,0x11,0x11,  // s7 ..s8
	*/

	/* Compressed Version Non Reverse
	0x01235871,0x11461111, // s0..s0
	0x11111111,0x11111111,
	0x10111110,0x10111111, // s1..s2
	0x12111112,0x12111111,
	0x11111112,0x11111111, // s3..s4
	0x12111111,0x12111111,
	0x11111113,0x13111111, // s5..s6
	0x13111113,0x13111111,
	0x13111111,0x11111111,  // s7 ..s8*/

	IT0,IT1, // s0..s0
	IT2,IT2,
	IT3,IT4, // s1..s2
	IT5,IT6,
	IT7,IT2, // s3..s4
	IT6,IT6,
	IT8,IT9, // s5..s6
	ITA,IT9,
	IT9,IT2, // s7..s8
};

u32 decode(u32* state, u32* codep, u8 byte) {
  u32 type = (utf8d[code[byte>>3]]>>((byte & 7)<<2)) & 0xF;

  *codep = (*state != UTF8_ACCEPT) ?
    (byte & 0x3fu) | (*codep << 6) :
    (0xff >> type) & (byte);

  byte = (u8)((*state)*16 + type);
  *state = (utf8d[code2[byte>>3]]>>((byte & 7)<<2)) & 0xF;
  return *state;
}

u32 toUtf16(const u8* src, u32 srcSizeBytes, u16* dst, u32 dstSizeWord) {
	const u8* src_actual_end = src + srcSizeBytes;
	const u8* s = src;
	u16* d = dst;
	u32 codepoint;
	u32 state = 0;
	u32 count = 0;

	while (s < src_actual_end) {
		u32 dst_words_free = dstSizeWord - (d - dst);
		const u8* src_current_end = s + dst_words_free;

		if (src_actual_end < src_current_end)
			src_current_end = src_actual_end;

		if (src_current_end <= s)
			goto toosmall;

		while (s < src_current_end) {

			if (decode(&state, &codepoint, *s++))
			continue;

			if (codepoint > 0xffff) {
				*d++ = (u16)(0xD7C0 + (codepoint >> 10));
				*d++ = (u16)(0xDC00 + (codepoint & 0x3FF));
				count += 2;
			} else {
				*d++ = (u16)codepoint;
				count += 1;
			}
		}
	}

toosmall:
  /*
  if (state != UTF8_ACCEPT) {
    ...
  }

  if ((dstWords - (d - dst)) == 0)
    goto toosmall;

  *d++ = 0;
  ...

  ...
  */
  return count;
}
