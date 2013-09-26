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
#include "MarshallingUtils.h"
#include "CS_Memory.h"

namespace System {

/*static*/
int* __MarshallingUtils::NativeUtf8FromString(System::String* str) {
	if(!str) { 
		return NULL;
	}
	if(str->_acc_gLength() == 0) {
		return (int*)System::String::Empty->_getStringBuffer();
	}

	u8* utf8buff = (u8*)CS_MALLOC(str->_acc_gLength() * 2);
	u32 utf8Length = _utf16ToUtf8(str->_getStringBuffer(), str->_acc_gLength(), utf8buff, str->_acc_gLength() * 2);
	return (int*)utf8buff;
}

/*static*/	
System::String* __MarshallingUtils::StringFromNativeUtf8(s32* utf8intptr) {
	u8* utf8ptr = (u8*)utf8intptr;
	u32 utf8len = 0;
	while(utf8ptr[utf8len] != 0) { ++utf8len; }

	if(!utf8intptr || (utf8len == 0)) { 
		return System::String::Empty; 
	}

	System::String* str = CS_NEW System::String(false);
	str->m_allocBuffer = (const uniChar*)System::__GCMalloc::allocBlock((utf8len * 3), str->m_allocBufferObject);
	str->m_allocBufferObject->_addOwner(str);
	str->m_bNotOwnBuffer = false;
	str->m_stringBuffer  = str->m_allocBuffer;

	str->m_length = _utf8ToUtf16((u8*)utf8ptr, utf8len, (u16*)str->m_allocBuffer, (utf8len * 3));

	return str;
}

/*static*/	
System::Array<System::String*>* __MarshallingUtils::StringArrayFromNativeUtf8IntPtr(s32* utf8intptr, int size) {
	System::Array<System::String*>* arr = CS_NEW System::Array<System::String*>(size);

	for(int i = 0; i < size; ++i) {
		arr->_array_refSetValue(i, StringFromNativeUtf8((int*)*utf8intptr));
		utf8intptr++;
	}

	return arr;
}

/*static*/	
System::Array<s32*>* __MarshallingUtils::NativeUtf8ArrayFromStringArray(System::Array<System::String*>* stringArray, int size) {
	if(!stringArray) {
		return NULL;
	}

	System::Array<s32*>* arr = CS_NEW System::Array<s32*>(size);

	for(int i = 0; i < size; ++i) {
		arr->_array_refSetValue(i, NativeUtf8FromString(stringArray->_idx_g_0based(i)));
	}

	return arr;
}

/*static*/	
System::Array<s32>* __MarshallingUtils::IntArrayFromIntPtr(s32* intptr, int size) {

	System::Array<s32>* arr = CS_NEW System::Array<s32>(size);
	memcpy(arr->_getPArray(), intptr, size * sizeof(s32));

	return arr;
}

// --------------------------------------------------------
// --------------------------------------------------------

#define UTF8_ACCEPT 0
#define UTF8_REJECT 1

// 10x4 + 11x4 = 84 byte
static const u32 utf8d[] = {
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

u32 _utf8ToUtf16(const u8* src, u32 srcSizeBytes, u16* dst, u32 dstSizeWord) {
	const u8* src_actual_end = src + srcSizeBytes;
	const u8* s = src;
	u16* d = dst;
	u32 codepoint;
	u32 state = 0;
	u32 count = 0;

	while (s < src_actual_end) {
		u32 dst_words_free = dstSizeWord - (d - dst);
		const u8* src_current_end = s + dst_words_free;

		if(src_actual_end < src_current_end)
			src_current_end = src_actual_end;

		if(src_current_end <= s)
			goto toosmall;

		while (s < src_current_end) {

			if(decode(&state, &codepoint, *s++))
			continue;

			if(codepoint > 0xffff) {
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
  if(state != UTF8_ACCEPT) {
    ...
  }

  if((dstWords - (d - dst)) == 0)
    goto toosmall;

  *d++ = 0;
  ...

  ...
  */
  return count;
}

u32 _utf16ToUtf8(const uniChar* src, u32 srcSizeWord, u8* dst, u32 dstSizeBytes) {
	const u8* dstStart = dst;
	const uniChar* end = src + srcSizeWord;

	while(src < end) {
		if((*src >= 0x0001) && (*src <= 0x007F)) {
			*dst++ = (u8)*src;
		} else if((*src >= 0x0080) && (*src <= 0x07FF)) {
			*dst++ = (0xC0 | ((*src >>  6) & 0x1F));
			*dst++ = (0x80 | ((*src >>  0) & 0x3F));
		} else if(((*src >= 0x0800) && (*src <= 0xFFFF)) && !(*src >= 0xD800 && *src <= 0xDFFF)) {
			*dst++ = (0xE0 | ((*src >> 12) & 0x0F));
			*dst++ = (0x80 | ((*src >>  6) & 0x3F));
			*dst++ = (0x80 | ((*src >>  0) & 0x3F));
		} else {
			// unicode characters encoded on 4 bytes.
			u32	upper = (0x000F & (*src >> 6)) + 1; // 5 bits : 000xxxxx
		
			*dst++ = (0xF0 | ((upper >> 2) & 0x07));
			*dst++ = (0x80 | (((upper) & 0x03) << 4) + ((*src >> 2) & 0x0F));
			*dst++ = (0x80 | (((*src >> 0) & 0x03) << 4) + ((*++src >> 6) & 0x0F));
			*dst++ = (0x80 | ((*src >> 0) & 0x3F));
		}
		src++;
	}

	return (dst - dstStart);
}

}
