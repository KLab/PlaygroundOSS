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
#ifndef CKLBBinArray_h
#define CKLBBinArray_h

#include <stdio.h>
#include "BaseType.h"
#include "CKLBObject.h"

class CKLBBinArray : public CKLBObjectScriptable
{
public:
	CKLBBinArray();
	virtual ~CKLBBinArray();

	u32 getClassID();

	static void removeAll();
	static bool dumpAll();

	bool loadAsset(const char * path);

	inline size_t getSize() const { return m_size; }
	inline u8 getByte(int offset) { return *(m_pBuf + offset); }
	inline u16 getWordLE(int offset) {
		u16 val = *(m_pBuf + offset);
		val |= (u16)*(m_pBuf + offset + 1) << 8;
		return val;
	}
	inline u32 getLongLE(int offset) {
		u32 val = *(m_pBuf + offset);
		val |= (u32)*(m_pBuf + offset + 1) << 8;
		val |= (u32)*(m_pBuf + offset + 1) << 16;
		val |= (u32)*(m_pBuf + offset + 1) << 24;
		return val;
	}

	inline u16 getWordBE(int offset) {
		u16 val = (u16)*(m_pBuf + offset) << 8;
		val |= *(m_pBuf + offset + 1);
		return val;
	}
	inline u32 getLongBE(int offset) {
		u32 val = (u32)*(m_pBuf + offset) << 24;
		val |= (u32)*(m_pBuf + offset + 1) << 16;
		val |= (u32)*(m_pBuf + offset + 1) << 8;
		val |= (u32)*(m_pBuf + offset + 1);
		return val;
	}

private:
	const char	*	m_name;
	size_t			m_size;
	u8			*	m_pBuf;


	CKLBBinArray	*	m_prev;
	CKLBBinArray	*	m_next;

	static CKLBBinArray	*	ms_begin;
	static CKLBBinArray	*	ms_end;
};

#endif // CKLBBinArray_h
