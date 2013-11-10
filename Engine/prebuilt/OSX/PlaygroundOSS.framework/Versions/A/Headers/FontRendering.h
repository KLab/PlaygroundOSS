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
#ifndef H_FNT_RENDERING_KLB_
#define H_FNT_RENDERING_KLB_

#include "CPFInterface.h"
#include <stdio.h>
#include <string.h>

// assume POSIX / Linux
#ifndef _WIN32
# include <strings.h>
# define stricmp(s1, s2) strcasecmp(s1, s2)
#endif

#include <ft2build.h>
#include FT_FREETYPE_H

// ==========================================================================================
//   Definitions
// ==========================================================================================
struct CharDictionnary;
struct CharCache;
struct MemoryBlock;
class  FntDebug;
namespace FontSystem {
	void reboot();
};

struct FontObject {
	friend class FntDebug;
	friend struct CharDictionnary;
	friend struct CharCache;
public:
	static bool	registerFont(const char* logicalName, const char* physicalFont, bool asDefault);
	static FontObject* createFont(const char* fontName, u32 size);
	static void destroyFont(FontObject* pFont, bool force = false);
	static void releaseFontSystem();
	
	FT_GlyphSlot renderChar(u32 unicode);
	void renderText	(s32 x, s32 y, const char* text, u8* greyBuffer, u32 colorARGB8888, u32 buffWidth, u32 buffHeight, s32 strideByte, bool use4444);
	void getTextInfo(const char* text, STextInfo* result);
	float getAscent();

	static void test();
	
private:
	FontObject();
	~FontObject();
	
	static FontObject*  s_list;
	static bool			s_init;
	static FT_Library	s_library;

	FontObject*	m_prev;
	FontObject* m_next;
	
	FT_Face		m_face;
	u32			m_lenName;
	u32 		m_size;
	u32			m_refCount;
	u16			m_dicoStart;
	FT_Bool		m_hasKerning;
	const char*	m_name;

	struct FONTALIAS {
		const char * logicalName;
		const char * physicalName;
		bool		 isDefault;
	};

	static FONTALIAS	g_fonts[5];
	static u32			g_fontInstalled;

	static const char* getFileFromFontName(const char* fontName, char* tmpBuffer);
};

#define CHAR_CACHE_SIZE	(512)

struct CharCache {
	friend class FntDebug;
	friend struct CharDictionnary;
	friend struct FontObject;
public:
	static CharCache* createEntry(u32 uniCode, u16* outIndex, FontObject* pFont);
	
	static void test();
	static void reboot() {
		s_cacheStart	= 0xFFFF;
		s_cacheEnd		= 0;
		s_allocCounter	= 0;
	}

	u8* m_ptr;
	FontObject* m_pFontObj;
private:
	u32 m_unicode;
public:
	s32 m_offsetX;
	s32	m_offsetY;
private:
	u16	m_next;
	u16 m_prev;
public:
	u16 m_blockIndex;
	u16	m_blockCharIndex;
	u16 m_tblOffset;
	// ---- Rendering box
	u8  m_width;
	u8  m_height;
	s8  m_advanceX;
	s8  m_advanceY;
	// ------------------
private:
	CharCache();
	~CharCache();

	static u16 s_cacheStart;
	static u16 s_cacheEnd;
	static CharCache s_cacheArray[CHAR_CACHE_SIZE];
	static u16 s_allocCounter;
};

struct CharDictionnary {
	friend struct FontObject;
	friend class FntDebug;
public:
	static CharCache* getChar(u32 uniCode, FontObject* pFont);
	static void	removeDicoEntry(u16 startEntry, u32 unicode);
	static void destroyTree(u16 entry, u16 depth);
	static void removeEntry(u16 entry);

	static void reboot() {
		s_freeList = s_usedList = 0xFFFF;
	}
	static void test();
private:
	CharDictionnary();

	static const u32 DICO_ELEMENT_COUNT = 1000;
	static CharCache*	findEntry(FontObject* pFont,u32 uniCode);
	static CharCache*	createEntry(FontObject* pFont, u32 uniCode);
	static u16			createDicoEntry();
	static u16			removeDicoEntryRec(u16 entry, u32 depth, u32 unicode, u16 startEntry);

	static CharDictionnary	s_dicoArray[DICO_ELEMENT_COUNT];
	static u16				s_freeList;
	static u16				s_usedList;

	u16			m_next;			// 2
	u16			m_prev;			// 2
	u16			m_idxTbl[16];	// 8 byte
};

#define	MB_BLOCK_ITEM_SIZE	(64*64)

struct MemoryBlock {
	friend class FntDebug;

	static void test();
	static void reboot();
	static void freeBlock(u16 blockID, u16 subID);
	static bool allocBlock(u16* returnBlock, u16* returnSubID, u8** ppData);
private:
	static MemoryBlock*	s_blockList;
	static u16			s_blockCounter;

	MemoryBlock*	m_next;
	u16				m_id;
	u32				m_allocFlag;
	u32				partSize;
	// Aligned by partSize.
	u8				m_mem[32*MB_BLOCK_ITEM_SIZE];
};

#endif // H_FNT_RENDERING_KLB_
