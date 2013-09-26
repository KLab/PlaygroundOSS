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
#include "FontRendering.h"

#include "CPFInterface.h"
#include "CKLBUtility.h"
#include "utf8.h"

// Prototype to avoid warning.
void test();

class FntDebug {
public:
	static void check();
private:
	static void checkTreeRec(u32 depth, u32 idx, u32 code);
};

// ==========================================================================================
//   Global Static Variables
// ==========================================================================================

/*static*/ CharDictionnary	CharDictionnary::s_dicoArray[DICO_ELEMENT_COUNT];
/*static*/ u16				CharDictionnary::s_freeList = 0xFFFF;
/*static*/ u16				CharDictionnary::s_usedList = 0xFFFF;

/*static*/ CharCache		CharCache::s_cacheArray[CHAR_CACHE_SIZE];
/*static*/ u16				CharCache::s_cacheStart		= 0xFFFF;
/*static*/ u16				CharCache::s_cacheEnd		= 0;// First allocated object.
/*static*/ u16				CharCache::s_allocCounter	= 0;

/*static*/ FontObject*		FontObject::s_list			= NULL;
/*static*/ bool				FontObject::s_init			= false;
/*static*/ FT_Library		FontObject::s_library;
/*static*/ FontObject::FONTALIAS	FontObject::g_fonts[5];
/*static*/ u32				FontObject::g_fontInstalled	= 0;

/*static*/ MemoryBlock*		MemoryBlock::s_blockList	= NULL;
/*static*/ u16				MemoryBlock::s_blockCounter	= 0;

// ==========================================================================================
//   Global reboot function
// ==========================================================================================

int g_checkCount = 0;
int g_counterChar;

void FntDebug::check() {
	/*
	// 1. For each font
	FontObject* pFnt = FontObject::s_list;
	int totalCount = 0;
	while (pFnt) {
//		printf("===== Font : '%s' [%i]\n", pFnt->m_name, pFnt->m_refCount);
		g_counterChar = 0;
		// 2. Parse the cache tree and lookup.
		checkTreeRec(0,pFnt->m_dicoStart, 0);
		pFnt = pFnt->m_next;
//		printf("===== Has %i unicode entry\n", g_counterChar);
		totalCount += g_counterChar;
	}
//	printf("===== Total %i charFont, Alloc Total : %i\n", totalCount, CharCache::s_allocCounter);
	g_checkCount++;
	*/
}

void FntDebug::checkTreeRec(u32 depth, u32 idx, u32 code) {
	if (depth < 8) {
		CharDictionnary* pEntry = &CharDictionnary::s_dicoArray[idx];
//		printf("D:%i %04i ", depth, idx);

		for (u32 n=0; n < depth; n++) {
//			printf(" ");
		}

		for (u32 n=0; n < 16; n++) {
			if (pEntry->m_idxTbl[n] != 0xFFFF) {
//				printf("[%2i]%04i ", n, pEntry->m_idxTbl[n]);
			} else {
//				printf("[%2i]NULL ", n);
			}
		}
//		printf("\n");
		
		for (int n=0; n < 16; n++) {
			if (pEntry->m_idxTbl[n] != 0xFFFF) {
				checkTreeRec(depth + 1, pEntry->m_idxTbl[n], (code << 4) | n);
			}
		}
	} else {
		CharCache* pChar = &CharCache::s_cacheArray[idx];
		if (pChar->m_unicode != code) {
			klb_assertAlways(" Adr Code : %08X <-> Char : %08X\n", code, pChar->m_unicode);
		} else {
//			printf(" Char : %08X\n", code);
			g_counterChar++;
		}
	}
}

namespace FontSystem {
	void reboot() {
		// Release Font
		FontObject::releaseFontSystem();
		// Clean Dictionnary entries.
		CharDictionnary::reboot();
		// Clean Character cache.
		CharCache::reboot();
		// Clean Memory Block
		MemoryBlock::reboot();
	}
} // end FontSystem

/*static*/ void test() {
	FontObject::test();
	CharDictionnary::test();
	MemoryBlock::test();
	CharCache::test();
}

/*static*/ void FontObject::test() {
	DEBUG_PRINT("Font Object Test====\n");
	FontObject* p    = s_list;
	FontObject* prev = NULL;
	DEBUG_PRINT("Init : %i\n", s_init ? 1 : 0);
	DEBUG_PRINT("Forward Parse.\n");
	while (p) {
		DEBUG_PRINT("\t%8X RefCount\n",p, p->m_refCount);
		prev = p;
		p = p->m_next;
	}
	p = prev;
	DEBUG_PRINT("Backward Parse.\n");
	while (p) {
		DEBUG_PRINT("\t%8X\n",p);
		p = p->m_prev;
	}
}

/*static*/ void CharDictionnary::test() {
	DEBUG_PRINT("Char Dictionnary Test====\n");
	u16 p		= s_freeList;
	u16 prev	= 0xFFFF;
	DEBUG_PRINT("Forward Parse Free List.\n");
	while (p != 0xFFFF) {
		DEBUG_PRINT("\t%4X\n",p);
		prev = p;
		p = s_dicoArray[p].m_next;
	}

	p = prev;
	DEBUG_PRINT("Backward Parse free list.\n");
	while (p != 0xFFFF) {
		DEBUG_PRINT("\t%4X\n",p);
		p = s_dicoArray[p].m_prev;
	}

	p		= s_usedList;
	prev	= 0xFFFF;
	DEBUG_PRINT("Forward Parse used List.\n");
	while (p != 0xFFFF) {
		DEBUG_PRINT("\t%4X\n",p);
		prev = p;
		p = s_dicoArray[p].m_next;
	}

	p = (u16)prev;
	DEBUG_PRINT("Backward Parse used list.\n");
	while (p != 0xFFFF) {
		DEBUG_PRINT("\t%4X\n",p);
		p = s_dicoArray[p].m_prev;
	};
}

/*static*/ void CharCache::test() {
	DEBUG_PRINT("Char Cache Test====\n");
	DEBUG_PRINT("\tAlloc Count : %i\n",s_allocCounter);

	u16 p		= s_cacheStart;
	u16 prev	= 0xFFFF;
	DEBUG_PRINT("Forward Parse Allocated List.\n");
	while (p != 0xFFFF) {
		DEBUG_PRINT("\t%4X\n",p);
		prev = p;
		p = s_cacheArray[p].m_next;
	}

	if ((prev != s_cacheEnd) && (s_cacheStart != 0xFFFF)) {
		DEBUG_PRINT("ERROR !!! Char cache");
	}

	p = prev;
	DEBUG_PRINT("Backward Parse Allocated list.\n");
	while (p != 0xFFFF) {
		DEBUG_PRINT("\t%4X\n",p);
		p = s_cacheArray[p].m_prev;
	}
}

/*static*/ void MemoryBlock::test() {
}


// ==========================================================================================
//   Implementation CharCache
// ==========================================================================================

struct SubEntry {
public:
	u16 offsetBitTable;
};

CharCache::CharCache() {
}

CharCache::~CharCache() {
}

// ==========================================================================================
//   Implementation CharDictionnary
// ==========================================================================================

CharDictionnary::CharDictionnary()
{
	m_next = 0xFFFF;
	m_prev = 0xFFFF;
	memset(m_idxTbl, 0xFF, 16 * sizeof(u16));
}

/*static*/ CharCache* CharDictionnary::getChar(u32 uniCode, FontObject* pFont) {
	FntDebug::check();	// Only place with one check.

	CharCache* pEntry = findEntry(pFont, uniCode);

	if (pEntry == NULL) {
		CharDictionnary* pParse = &s_dicoArray[pFont->m_dicoStart];
		u32 copyCode = uniCode;
		for (int n=0; n < 7; n++) {
			u16 idx = pParse->m_idxTbl[copyCode>>28];
			if (idx == 0xFFFF) {
				idx = CharDictionnary::createDicoEntry();
				pParse->m_idxTbl[copyCode>>28] = idx;
				if (idx == 0xFFFF) {
					return NULL;
				}
				pParse = &s_dicoArray[idx];
			} else {
				pParse = &s_dicoArray[idx];
			}
			copyCode <<=4;
		}

		u16 idxChar;
		pEntry = CharCache::createEntry(uniCode, &idxChar, pFont);
		if (pEntry) {
			pParse->m_idxTbl[copyCode>>28] = idxChar;
		}
	}
	return pEntry;
}

/*static*/ CharCache* CharDictionnary::findEntry(FontObject* pFont, u32 uniCode) {
	CharDictionnary* pParse = &s_dicoArray[pFont->m_dicoStart];
	u16 idx = 0;
	for (int n=0; n < 8; n++) {
		idx = pParse->m_idxTbl[uniCode>>28];
		if (idx == 0xFFFF) {
			break;
		}
		pParse = &s_dicoArray[idx];
		uniCode <<=4;
	}

	if (idx != 0xFFFF) {
		return &CharCache::s_cacheArray[idx];
	} else {
		return NULL;
	}
}

/*static*/ u16		 CharDictionnary::createDicoEntry() {
	if (s_freeList == 0xFFFF && s_usedList == 0xFFFF) {
		for (int n=0; n < DICO_ELEMENT_COUNT; n++) {
			s_dicoArray[n].m_next = n+1;
			s_dicoArray[n].m_prev = n-1;
		}
		s_dicoArray[DICO_ELEMENT_COUNT-1].m_next = 0xFFFF;

		s_usedList = 0xFFFF;
		s_freeList = 0;
	}

	if (s_freeList != 0xFFFF) {
		if (s_dicoArray[s_freeList].m_next != 0xFFFF) {
			s_dicoArray[s_dicoArray[s_freeList].m_next].m_prev = s_dicoArray[s_freeList].m_prev;
		}

		if (s_dicoArray[s_freeList].m_prev != 0xFFFF) {
			s_dicoArray[s_dicoArray[s_freeList].m_prev].m_next = s_dicoArray[s_freeList].m_next;			
		}

		if (s_usedList != 0xFFFF) {
			s_dicoArray[s_usedList].m_prev = s_freeList;
		}
		
		u16 nextFree = s_dicoArray[s_freeList].m_next;

		s_dicoArray[s_freeList].m_next = s_usedList;
		s_dicoArray[s_freeList].m_prev = 0xFFFF;
		memset(s_dicoArray[s_freeList].m_idxTbl, 0xFF, 16 * sizeof(u16));

		s_usedList = s_freeList;
		s_freeList = nextFree;
		return s_usedList;
	} else {
		return 0xFFFF;
	}
}

/*static*/ void CharDictionnary::destroyTree(u16 entry, u16 depth) {
	if (entry != 0xFFFF) {
		if (depth <= 7) {
			u16* p16 = s_dicoArray[entry].m_idxTbl;
			for (int n=0; n < 16; n++) {
				destroyTree(p16[n], depth+1);
			}

			removeEntry(entry);
		}
	}
}

/*static*/ void CharDictionnary::removeEntry(u16 entry) {
	if (s_dicoArray[entry].m_next != 0xFFFF) {
		s_dicoArray[s_dicoArray[entry].m_next].m_prev = s_dicoArray[entry].m_prev;
	}

	if (s_dicoArray[entry].m_prev != 0xFFFF) {
		s_dicoArray[s_dicoArray[entry].m_prev].m_next = s_dicoArray[entry].m_next;			
	} else {
		s_usedList = s_dicoArray[entry].m_next;
	}

	s_dicoArray[entry].m_next = s_freeList;
	s_dicoArray[entry].m_prev = 0xFFFF;

	if (s_freeList != 0xFFFF) {
		s_dicoArray[s_freeList].m_prev = entry;
	}

	s_freeList = entry;
}

/*static*/ void	CharDictionnary::removeDicoEntry(u16 startEntry, u32 unicode) {
	removeDicoEntryRec(startEntry, 0, unicode,startEntry);
}

/*static*/ u16 CharDictionnary::removeDicoEntryRec(u16 entry, u32 depth, u32 unicode,u16 startEntry) {
	if (depth < 7) {
		u16 next = s_dicoArray[entry].m_idxTbl[unicode>>28];
		u16 idx  = 0xFFFF;
		if (next != 0xFFFF) {
			idx = removeDicoEntryRec(next, depth + 1, unicode << 4, startEntry);
			if (idx != 0xFFFF) {
				s_dicoArray[entry].m_idxTbl[unicode>>28] = 0xFFFF;
			}
		}
	} else {
		// Remove entry.
		s_dicoArray[entry].m_idxTbl[unicode>>28] = 0xFFFF;
	}

	u16* p16 = s_dicoArray[entry].m_idxTbl;
	if ((p16[0] == 0xFFFF) && (p16[1] == 0xFFFF) && (p16[2] == 0xFFFF) && (p16[3] == 0xFFFF) && (p16[4] == 0xFFFF) && (p16[5] == 0xFFFF) && (p16[6] == 0xFFFF) && (p16[7] == 0xFFFF) 
		&& (p16[8] == 0xFFFF) && (p16[9] == 0xFFFF) && (p16[10] == 0xFFFF) && (p16[11] == 0xFFFF) && (p16[12] == 0xFFFF) && (p16[13] == 0xFFFF) && (p16[14] == 0xFFFF) && (p16[15] == 0xFFFF)) {

		if (entry != startEntry) {	// Never delete the root node
			removeEntry(entry);
		}

		return entry;
	} else {
		return 0xFFFF;
	}
}

// ==========================================================================================
//   Implementation Memory Block
// ==========================================================================================

/*static*/ void MemoryBlock::reboot() {
	MemoryBlock* parse = s_blockList;
	while (parse) {
		MemoryBlock* next = parse->m_next;
		delete parse;
		parse = next;
	}
	s_blockList		= NULL;
	s_blockCounter	= 0;
}

/*static*/ void MemoryBlock::freeBlock(u16 blockID, u16 subID) {
	MemoryBlock* parse = s_blockList;
	MemoryBlock* prev  = NULL;
	while (parse) {
		if (parse->m_id == blockID) {
			parse->m_allocFlag &= ~(1<<subID);	// Reset flag subID

			if (parse->m_allocFlag == 0) {
				if (parse != s_blockList) {	// Better to keep always ONE block as we need to render text anyway.
					// ... prev is then ALWAYS a valid pointer.
					prev->m_next = parse->m_next;
					delete parse;
				}
			}
			break;
		}
		prev  = parse;
		parse = parse->m_next;
	}
}

/*static*/ bool MemoryBlock::allocBlock(u16* returnBlock, u16* returnSubID, u8** ppData) {
	MemoryBlock* parse = s_blockList;
	while (parse) {
		u32 flag = parse->m_allocFlag; 
		if (flag != 0xFFFFFFFF) {
			u16 size = 16;
			u16 mask = (1 << size)-1;
			u16 idx  = 0;

			// log free bit search : 5 iteration only.
			while (size > 1) {
				if (((flag>>idx) & mask) != mask) {
					// Lower part
				} else {
					// Higher part
					idx += size;
				}
				size >>= 1;
				mask >>= size;
			}

			if (((flag>>idx) & mask) == mask) {
				// Higher part
				idx++;
			}
			parse->m_allocFlag |= 1<<idx;
			*returnBlock	= parse->m_id;
			*returnSubID	= idx;
			*ppData			= &parse->m_mem[MB_BLOCK_ITEM_SIZE * idx];
			return true;
		}
		parse = parse->m_next;
	}

	parse = new MemoryBlock();
	if (parse) {
		parse->m_next	= s_blockList;
		s_blockList		= parse;

		parse->m_allocFlag	= 1;
		parse->m_id			= s_blockCounter++;
		parse->partSize		= MB_BLOCK_ITEM_SIZE;

		*returnBlock	= parse->m_id;
		*returnSubID	= 0;
		*ppData			= &parse->m_mem[0];

		return true;
	} else {
		return false;
	}
}

/*static*/ const char* FontObject::getFileFromFontName(const char* fontName, char* tmpBuffer) {

	u32 idx			= 0xFFFF;
	u32 defaultIdx	= 0xFFFF;

	// Search logical name
	for (u32 n=0; n < g_fontInstalled; n++) {
		if (fontName && stricmp(fontName, g_fonts[n].logicalName) == 0) {
			idx = n;
			break;
		}
		if (g_fonts[n].isDefault) {
			defaultIdx = n;
		}
	}

	// Search physical name
	if ((idx == 0xFFFF) && fontName) {
		for (u32 n=0; n < g_fontInstalled; n++) {
			if (strstr(g_fonts[n].physicalName, fontName)) {
				idx = n;
				break;
			}
		}
	}

	// If not found, use default.
	if (idx == 0xFFFF) {
		idx = defaultIdx;
	}

	if (idx == 0xFFFF) {
		DEBUG_PRINT("Call porting registerFont function from entry point (ie entrance) or LUA start.");
		return NULL;
	} else {
		// Copy back to user
		sprintf(tmpBuffer,"%s",g_fonts[idx].physicalName);

		// return input buffer;
		return tmpBuffer;
	}
}

/*static*/ void FontObject::releaseFontSystem() {
	if (s_init) {
		s_init = false;
		while (s_list) {
			// s_list modified by destroyFont
			destroyFont(s_list, true);
		}
		FT_Done_FreeType( s_library );
		for (u32 n=0; n < g_fontInstalled; n++) {
			delete g_fonts[n].physicalName;		// Porting layer 'new'
			KLBDELETEA(g_fonts[n].logicalName);	// Used copy utility to do copy, KLBNEWA
		}
		g_fontInstalled = 0;
	}
}

/*static*/ bool	FontObject::registerFont(const char* logicalName, const char* physicalFont, bool asDefault) {
	if ((g_fontInstalled < 5) && logicalName && physicalFont) {
		IPlatformRequest& platform = CPFInterface::getInstance().platform();
		const char* fullpath = platform.getFullPath(physicalFont);	// Check also that file exists.
		if (fullpath) {
			const char* logicN	= CKLBUtility::copyString(logicalName);
			if (logicN) {
				if (asDefault) {
					for (u32 n=0; n < g_fontInstalled;n++) {
						g_fonts[n].isDefault = false;						
					}
					g_fonts[g_fontInstalled		].isDefault		= true;
				} else {
					bool hasDefault = false;
					for (u32 n=0; n < g_fontInstalled;n++) {
						hasDefault |= g_fonts[n].isDefault;
					}

					if (!hasDefault) {
						g_fonts[g_fontInstalled].isDefault		= true;
					}
				}

				g_fonts[g_fontInstalled		].logicalName	= logicN;
				g_fonts[g_fontInstalled++	].physicalName	= fullpath;

				return true;
			}
			delete fullpath;
		}
	}
	return false;
}

/*
	We render the same size IN PIXEL
	We do not want the font to have the same PHYSICAL size in millimeter on each device !
	Thus using the SAME DPI for any screen.
*/
#define FIXED_DPI	(60)

/*static*/ FontObject* FontObject::createFont(const char* fontName, u32 size) {
	// 0. Init library if not done yet.
	s32 error;
	if (!s_init) {
		error = FT_Init_FreeType( &s_library );              /* initialize library */
		if ( !error ) {
			s_init = true;
		}
	}

	// 1. Search matching font
	FontObject* pFont = s_list;
	
	u32 lenN = 0;
	if (fontName) {
		lenN = strlen(fontName);
	
		while (pFont) {
			if (pFont->m_lenName == lenN) {
				if (pFont->m_size == size) {
					if (strcmp(pFont->m_name, fontName) == 0) {
						pFont->m_refCount++;
						return pFont;
					}
				}
			}
			pFont = pFont->m_next;
		}
	}
	
	FT_Face face;
	
	// Internal Font
	char buff[512];

	error = FT_New_Face( s_library, FontObject::getFileFromFontName(fontName, buff), 0, &face );/* create face object */
	if ( !error ) {
		error = FT_Set_Char_Size( 	face, 		/* handle to face object			*/ 
									0,			/* char_width same as char_height	*/
									size<<6,	/* char_height in 1/64th of points	*/ 
									FIXED_DPI,	/* horizontal device resolution		*/
									FIXED_DPI 	/* vertical device resolution		*/
								);
		/* TODO potential API usage instead.
		error = FT_Set_Pixel_Sizes( face,	// Handle to face object
									0, 		// Width Same as height (pixel)
									size * ratio);
		 */
		if ( !error ) {
			pFont = new FontObject();
			
			if (pFont) {
				pFont->m_prev = NULL;
				// 2. If not found, add at the beginning of the list
				if (s_list) {
					s_list->m_prev = pFont;
					pFont->m_next = s_list;
				} else {
					pFont->m_next = NULL;
				}
				s_list = pFont;
				
				pFont->m_refCount	= 1;
				pFont->m_size		= size;
				pFont->m_face		= face;
				pFont->m_lenName	= lenN;
				pFont->m_name		= fontName ? CKLBUtility::copyString(fontName) : NULL;
				pFont->m_hasKerning = FT_HAS_KERNING( face );
				pFont->m_dicoStart	= CharDictionnary::createDicoEntry();
				if (pFont->m_dicoStart != 0xFFFF) {
					return pFont;
				}
				destroyFont(pFont);
				return NULL;
			}
		}
		FT_Done_Face ( face );
	} else {
		if (fontName) {
			// Try to create default font.
			if (strcmp(fontName, "")!=0) {
				return createFont("", size);
			}
		}
	}
	// Error.
	return NULL;
}

/*static*/ void FontObject::destroyFont(FontObject* pFont, bool force) {
	if (pFont) {
		if ((--pFont->m_refCount == 0) || force) {
			// 1. Remove from list
			if (pFont->m_prev != NULL) {
				pFont->m_prev->m_next	= pFont->m_next;
			} else {
				s_list = pFont->m_next;
			}
			
			if (pFont->m_next != NULL) {
				pFont->m_next->m_prev = pFont->m_prev;
			}
			
			// 2. Destroy face
			FT_Done_Face ( pFont->m_face );

			CharDictionnary::destroyTree(pFont->m_dicoStart, 0);

			// 3. Destroy object
			delete pFont;
		}
	}
}

FontObject::FontObject()
{ /* Do nothing, all done inside static functions */ }

FontObject::~FontObject()
{
	// Scan all the allocated character and remove any pointer reference to font object.
	for (int n=0; n < CharCache::s_allocCounter; n++) {
		if (CharCache::s_cacheArray[n].m_pFontObj == this) {
			CharCache::s_cacheArray[n].m_pFontObj = NULL;
		}
	}

	KLBDELETEA(m_name);
	m_name = NULL;
}

float FontObject::getAscent() {
	FT_Size_Metrics* met = &this->m_face->size->metrics;
	return (float)(met->ascender >> 6);
}

FT_GlyphSlot FontObject::renderChar(u32 unicode) {
	FT_GlyphSlot glyphslt = m_face->glyph;
	u32 glyph_index = FT_Get_Char_Index( m_face, unicode );
	FT_Error error = FT_Load_Glyph(	m_face,				/* handle to face object */
							glyph_index,		/* glyph index */
							FT_LOAD_RENDER );	/* does render with FT_RENDER_MODE_NORMAL as we do not perform any transform */
	if (!error) {
		return glyphslt;
	} else {
		return NULL;
	}
}

/*static*/ CharCache* CharCache::createEntry(u32 uniCode, u16* outIdx, FontObject* pFont) {
	CharCache* pItem = NULL;

	// Render Glyph
	FT_GlyphSlot glyphslt = pFont->renderChar(uniCode);
	
	// Add to block	
	u16 blockIdx;
	u16 blockCharIdx;
	u8* ptrBuff;

	if (glyphslt && MemoryBlock::allocBlock(&blockIdx, &blockCharIdx, &ptrBuff)) {
		u16 idx;
		if (s_allocCounter < CHAR_CACHE_SIZE) {
			idx = s_allocCounter++;
		} else {
			idx = s_cacheEnd;
			CharCache* pItem = &s_cacheArray[idx];
			// 1.Remove from link list -> maintain head AND queue.
			if (pItem->m_prev != 0xFFFF) {
				s_cacheArray[pItem->m_prev].m_next = 0xFFFF;
				s_cacheEnd = pItem->m_prev;
			} else {
				s_cacheEnd = s_cacheStart; // Should never arrive
			}

			// 2.Remove data from block
			MemoryBlock::freeBlock(pItem->m_blockIndex, pItem->m_blockCharIndex);

			// 3.Remove entry from dictionnary
			if (pItem->m_pFontObj) {
				CharDictionnary::removeDicoEntry(pItem->m_pFontObj->m_dicoStart, pItem->m_unicode);
			}
		}
		
		pItem = &s_cacheArray[idx];
		*outIdx = idx;
		pItem->m_unicode = uniCode;

		// Add to link list
		pItem->m_next	 = s_cacheStart;
		pItem->m_prev	 = 0xFFFF;
		if (s_cacheStart != 0xFFFF) {
			s_cacheArray[s_cacheStart].m_prev = idx;
		}
		s_cacheStart = idx;	// s_cacheEnd is 0 by default -> always point to first allocated item.

		FT_Bitmap* bmp		= &glyphslt->bitmap;
		pItem->m_width		= bmp->width;
		pItem->m_height		= bmp->rows;
		pItem->m_offsetX	= glyphslt->bitmap_left;
		pItem->m_offsetY	= -glyphslt->bitmap_top;
		pItem->m_advanceX	= (s8)(glyphslt->advance.x >> 6);
		pItem->m_advanceY	= (s8)(glyphslt->advance.y >> 6);
		pItem->m_blockIndex	= blockIdx;
		pItem->m_blockCharIndex = blockCharIdx;
		pItem->m_ptr		= ptrBuff;
		pItem->m_pFontObj	= pFont;

		u8* write	= pItem->m_ptr;
		u8* src		= bmp->buffer;
//#define PRESKIP

#ifdef PRESKIP
		write++;
#endif
		for (int y=0; y < bmp->rows; y++) {
#ifdef PRESKIP
			u8 start = 0xFF;
			for (int x=0; x < bmp->width; x++) {
				if ((*src) && (start==0xFF)) {
					start = x;
				}
				*write++ = *src++;
			}
			write[-(bmp->width+1)] = start;
			write++;
#else
			memcpy(write, src, bmp->width);
			src		+= bmp->pitch;
			write	+= bmp->width;
#endif
		}

		pItem->m_tblOffset = ((pItem->m_width * bmp->rows) + 3) & 0xFFFC;
		u32 size = ((bmp->width+31)>>5)*(bmp->rows<<2);	// number of 32 bit mask for storage. 
		if ((pItem->m_tblOffset < MB_BLOCK_ITEM_SIZE) && ((pItem->m_tblOffset+size) <= MB_BLOCK_ITEM_SIZE)) {
			u32* p = (u32*)&pItem->m_ptr[pItem->m_tblOffset];
			for (int x=0; x < bmp->width; x += 32) {
				bool last = (x + 32) >= bmp->width;
				u32 ex = 32;

				if (last) {
					if (bmp->width != 32) {
						ex = bmp->width & 0x1F;
					}
				}

				for (int y=0; y < bmp->rows; y++) {
					u32 mask = 0;

					u8* ptr = &pItem->m_ptr[x + (y * bmp->width)]; 
					for (u32 xi=0; xi < ex; xi++) {
						if (*ptr++) {
							mask |= 1 << xi;
						}
					}
					*p++ = mask;
				}
			}
		} else {
			klb_assertAlways("Font char does not fit into cache size : MB_BLOCK_ITEM_SIZE");
		}
	}

	return pItem;
}

void FontObject::renderText	(s32 x, s32 y, const char* text, u8* Buffer8888, u32 colorARGB8888, u32 buffWidth, u32 buffHeight, s32 strideByte, bool use4444) {
	// FT_GlyphSlot glyphslt = m_face->glyph;
	s32 currX = x;
	s32 currY = y;

	// ARGB
	u32 rgb32 = 0;
	u8* pCol = (u8*)&rgb32;
	pCol[0] = colorARGB8888>>16;
	pCol[1] = colorARGB8888>>8;
	pCol[2] = colorARGB8888;

	u16 rgb16 = ((colorARGB8888 >> 8) & 0xF000)		// Red
			  | ((colorARGB8888 >> 4) & 0x0F00)		// Green
			  | ((colorARGB8888 >> 0) & 0x00F0)		// Blue
			  ;

	u32 arrayUnicode[1500];
	u32 charCount = 1500;

	if (wind_utf8ucs4(text, arrayUnicode, &charCount) == 0)
	for (u32 n=0; n < charCount; n++) {
		u32 charcode = arrayUnicode[n];
		// DEBUG_PRINT("RENDERING; letter: %x(%c)", charcode, (char)charcode);

		CharCache* pChar = CharDictionnary::getChar(charcode, this);
		
		if (pChar) {
			//========================================
			//========================================
			// Rendering
			//========================================
			//========================================


			//----------------------------------------
			//  Clipping
			//----------------------------------------

			s32 Wwidth		= pChar->m_width;
			s32 Wheight		= pChar->m_height;	// Number of line to process.

			s32 px			= currX + pChar->m_offsetX;
			s32 py			= currY + pChar->m_offsetY;
			u32 startX		= 0;
			u32 startY		= 0;
			// DEBUG_PRINT("RENDERING; -- stepping into rendering path: %x(%c)", charcode, (char)charcode);
			// DEBUG_PRINT("RENDERING; px=%d, py=%d, buffWidth=%d, buffHeight=%d", px, py, buffWidth, buffHeight);

			// Top Left Clipping
			if (px < 0)
			{
				Wwidth	+= px;
				startX  -= px;
				px		= 0;
			}

			if (py < 0) {
				Wheight	+= py;
				startY  -= py;
				py		= 0;
			}

			// Bottom right Clipping
			s32 overRight = buffWidth  - (Wwidth + px);
			s32 overBottom= buffHeight - (Wheight+ py);

			if (overRight < 0) {
				Wwidth += overRight;
			}

			if (overBottom < 0) {
				Wheight += overBottom;
			}

			if ((Wwidth<=0) || (Wheight<=0)) {
				currX += pChar->m_advanceX;
				continue;
			}
			// DEBUG_PRINT("RENDERING; survived clipping");

			// Process by vertical 32 pixel chunks.
			u32 slab32	= 0;
			u32 slab	= 0;
			while (slab < pChar->m_width) {

				// Code for continue...
				slab	= slab32;
				slab32 	= slab+32;

				if (startX >= slab32) {
					continue;	// This slab has no drawn pixel.
				}
				// DEBUG_PRINT("RENDERING; ---- this slab has at least one pixel: %x(%c)", charcode, (char)charcode);

				u32 endX = startX + Wwidth;

				if (endX <= slab) {
					continue;
				}

				// Now endX is INCLUDED in clip area.
				endX--;

				u32 clipMask = (u32)(-1);

				
				// Left side clipping inside slab.
				if ((startX >= slab) && (startX < slab32)) {
					clipMask -= ((1<<(startX & 0x1F))-1);
				}

				// Right side clipping inside slab.
				if ((endX >= slab) && (endX < slab32)) {
					clipMask &= (0xFFFFFFFF)>>(31 - (endX & 0x1F));
				}

				if (clipMask == 0) {
					continue;
				}

				//----------------------------------------
				//  Rendering
				//----------------------------------------
				u32* pMaskInfo	= (u32*)&pChar->m_ptr[pChar->m_tblOffset + ((pChar->m_height<<2)*(slab>>5)) + (startY<<2)];
#ifdef PRESKIP
				u8* buffSrc		= &pChar->m_ptr[1];
				s32 strideSrc	= pChar->m_width - 1;
#else
				u8* buffSrc		= pChar->m_ptr;
				s32 strideSrc	= pChar->m_width;
#endif
				u32 roundX		= (((startX & 0x1F)>>2)<<2);
				u8* pSrcL		= &buffSrc		[roundX + (startY * strideSrc) + slab];

				if (use4444) {
					u16* pDstL	= (u16*)(&Buffer8888	[(px<<1) + (py * strideByte) + (slab << 1)]);
					u16* pDstE	= &pDstL[Wheight * (strideByte >> 1)];
				
					//
					// Could do a fct ptr here if various rendering needed (ie alpha)
					// fct(pDstL, pDstE, pSrcL, pMaskInfo, clipMask, roundX, rgb32)
					//
					while (pDstL < pDstE) {
						//
						// Render the slab
						//
						// 1. recompute roundX with start : roundX += roundX - start>roundX)

	#ifdef PRESKIP
						s32 delta = pSrcL[-1] - roundX;
						delta	= (delta < 0) ? 0 : (delta>>2)<<2;
						roundX	+= delta;
	#endif
						u32 mask = (*pMaskInfo++) & clipMask;
						mask >>= roundX;
	#ifdef PRESKIP
						u8* src = &pSrcL[delta];
	#else
						u8* src = pSrcL;
	#endif
						u16* dst = pDstL;

						while (mask) {
							// Write RGBA then overwrite alpha.
							// #define RGBA(idx,alpha)	dst[idx]=(rgb16 | ((src[idx] >>1)>>4))
							#define RGBA(idx)	dst[idx]=(rgb16 | (src[idx]>>4))

							switch (mask & 0xF) {
							case 0x0: break;
							case 0x1: RGBA(0); break;
							case 0x2: RGBA(1); break;
							case 0x3: RGBA(0); RGBA(1); break;
							case 0x4: RGBA(2); break;
							case 0x5: RGBA(0); RGBA(2); break;
							case 0x6: RGBA(1); RGBA(2); break;
							case 0x7: RGBA(0); RGBA(1); RGBA(2); break;
							case 0x8: RGBA(3); break;
							case 0x9: RGBA(0); RGBA(3); break;
							case 0xA: RGBA(1); RGBA(3); break;
							case 0xB: RGBA(0); RGBA(1); RGBA(3); break;
							case 0xC: RGBA(2); RGBA(3); break;
							case 0xD: RGBA(0); RGBA(2); RGBA(3); break;
							case 0xE: RGBA(1); RGBA(2); RGBA(3); break;
							case 0xF: RGBA(0); RGBA(1); RGBA(2); RGBA(3); break;
							}
							#undef RGBA
							dst += 4;
							src += 4;
							mask >>= 4;
						}

						pSrcL += strideSrc;
						pDstL += strideByte>>1;
					}
				} else {
					u8* pDstL		= &Buffer8888	[(px<<2) + (py * strideByte) + (slab << 2)];
					u8* pDstE		= &pDstL		[Wheight * strideByte];
				
					//
					// Could do a fct ptr here if various rendering needed (ie alpha)
					// fct(pDstL, pDstE, pSrcL, pMaskInfo, clipMask, roundX, rgb32)
					//
					while (pDstL < pDstE) {
						//
						// Render the slab
						//
						// 1. recompute roundX with start : roundX += roundX - start>roundX)

	#ifdef PRESKIP
						s32 delta = pSrcL[-1] - roundX;
						delta	= (delta < 0) ? 0 : (delta>>2)<<2;
						roundX	+= delta;
	#endif
						u32 mask = (*pMaskInfo++) & clipMask;
						mask >>= roundX;
	#ifdef PRESKIP
						u8* src = &pSrcL[delta];
	#else
						u8* src = pSrcL;
	#endif
						u8* dst = pDstL;

						#define DBG(idx)	(*((u32*)(&dst[idx<<2])))=0xFFFF00FF;
						// DBG(0);

						while (mask) {
							// Write RGBA then overwrite alpha.
							#define RGB(idx)	(*((u32*)(&dst[idx<<2])))=rgb32

							switch (mask & 0xF) {
							case 0x0: break;
							case 0x1: RGB(0); dst[ 3] = src[0]; break;
							case 0x2: RGB(1); dst[ 7] = src[1]; break;
							case 0x3: RGB(0); dst[ 3] = src[0]; RGB(1); dst[ 7] = src[1]; break;
							case 0x4: RGB(2); dst[11] = src[2]; break;
							case 0x5: RGB(0); dst[ 3] = src[0]; RGB(2); dst[11] = src[2]; break;
							case 0x6: RGB(1); dst[ 7] = src[1]; RGB(2); dst[11] = src[2]; break;
							case 0x7: RGB(0); dst[ 3] = src[0]; RGB(1); dst[ 7] = src[1]; RGB(2); dst[11] = src[2]; break;
							case 0x8: RGB(3); dst[15] = src[3]; break;
							case 0x9: RGB(0); dst[ 3] = src[0]; RGB(3); dst[15] = src[3]; break;
							case 0xA: RGB(1); dst[ 7] = src[1]; RGB(3); dst[15] = src[3]; break;
							case 0xB: RGB(0); dst[ 3] = src[0]; RGB(1); dst[ 7] = src[1]; RGB(3); dst[15] = src[3]; break;
							case 0xC: RGB(2); dst[11] = src[2]; RGB(3); dst[15] = src[3]; break;
							case 0xD: RGB(0); dst[ 3] = src[0]; RGB(2); dst[11] = src[2]; RGB(3); dst[15] = src[3]; break;
							case 0xE: RGB(1); dst[ 7] = src[1]; RGB(2); dst[11] = src[2]; RGB(3); dst[15] = src[3]; break;
							case 0xF: RGB(0); dst[ 3] = src[0]; RGB(1); dst[ 7] = src[1]; RGB(2); dst[11] = src[2]; RGB(3); dst[15] = src[3]; break;
							}
							#undef RGB
							dst += 4*4;
							src += 4;
							mask >>= 4;
						}

						pSrcL += strideSrc;
						pDstL += strideByte;
					}
				}
			}
			currX += pChar->m_advanceX;
		}
	}
}

void FontObject::getTextInfo(const char* text, STextInfo* result) {
	s32 currX = 0;
	s32 maxX  = 0;
	u32 arrayUnicode[1500];
	u32 charCount = 1500;
	if (wind_utf8ucs4(text, arrayUnicode, &charCount) == 0) {
		for (u32 n=0; n < charCount; n++) {
			u32 charcode = arrayUnicode[n];

			CharCache* pChar = CharDictionnary::getChar(charcode, this);
		
			if (pChar) {
				s32 Wwidth		= pChar->m_width;
				s32 px			= currX + pChar->m_offsetX;
				s32 ex			= px + Wwidth;
				if (ex > maxX) {
					maxX = ex;
				}
				currX 		   += pChar->m_advanceX;
			}
		}

		// Unit in pixels -> OK.
		result->width	= (float)currX;

		FT_Size_Metrics* met = &this->m_face->size->metrics;
		result->height	=(met->height	+ 63) >> 6;	// round up 1 pixel.
		result->ascent  = met->ascender >> 6;
		result->descent = met->descender>> 6;
		result->top		= result->ascent + (result->height - (result->ascent - result->descent)) / 3.0f;
		result->bottom	= result->top - result->height;
	} else {
		result->height	= 0.0f;
		result->ascent  = 0.0f;
		result->descent = 0.0f;
		result->top		= 0.0f;
		result->bottom	= 0.0f;
	}
	// DEBUG_PRINT("text info: height=%f, ascent=%f, descent=%f, top=%f, bottom=%f",
	// 		result->height, result->ascent, result->descent, result->top, result->bottom);
}

