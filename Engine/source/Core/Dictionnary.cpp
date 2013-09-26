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
#include "Dictionnary.h"
#include "CPFInterface.h"

// =========================================================================
//    Symbol Cache 1 Char Entry
// =========================================================================

CharEntry::CharEntry() 
{
}

CharEntry::CharEntry(Dictionnary* pOwner, char c, const void* value)
: m_next        (NULL)
, m_child       (NULL)
, m_pOwner      (pOwner)
, m_value       (value)
, m_char        (c)
, m_childCount  (0)
{
}

CharEntry::CharEntry(Dictionnary* pOwner)
: m_next        (NULL)
, m_child       (NULL)
, m_pOwner      (pOwner)
, m_value       (NULL)
, m_char        (0)
, m_childCount  (0)
{
}

/*static*/
void* 
CharEntry::operator new(size_t /*size*/, ArrayAllocator<CharEntry>* pAlloc)
{
	// Ignore size, we are fixed size type here.
	return pAlloc->allocEntry();
}

/*static*/
void 
CharEntry::operator delete(void *p, ArrayAllocator<CharEntry>* pAlloc)
{
	pAlloc->freeEntry((CharEntry*)p);
}

void 
CharEntry::clear() 
{
	if (m_pOwner->m_pCBDelete && m_value) {
		m_pOwner->m_pCBDelete(m_pOwner->m_pCBContext, m_value);
		m_value = NULL;
	}

	CharEntry* parse = m_child;
	while (parse) {
		CharEntry* next = parse->m_next;
		
		// Specific allocator, do NOT use KLBDELETE macro.

		// Free subtree.
		parse->clear();

		// Free only itself.
		operator delete (parse, &m_pOwner->allocator);
		parse = next;
	}

	m_childCount	= 0;
	m_child			= NULL;
}

bool 
CharEntry::findChildChar	(CharEntry** pEntry, char c) 
{
	CharEntry* start = this->m_child;
	CharEntry* last  = NULL;
	while (start && (start->m_char < c)) {
		last  = start;
		start = start->m_next;
	}
	
	if (start) {
		if (start->m_char != c) {
			// no entry or last entry with < c
			*pEntry = last;
			return false;
		} else {
			// Entry is == c
			*pEntry = start;
			return true;
		}
	} else {
		// no entry or last entry with < c
		*pEntry = last;
		return false;
	}
}

void 
CharEntry::insertChild(CharEntry* pEntryBefore, CharEntry* pEntry) 
{
	if (pEntryBefore != NULL) {
		//
		pEntry->m_next 			= pEntryBefore->m_next;
		pEntryBefore->m_next	= pEntry;
	} else {
		//
		pEntry->m_next 			= this->m_child;
		this->m_child			= pEntry;
	}
	m_childCount++;
}

void 
CharEntry::removeChild(CharEntry* pEntry) 
{
	CharEntry* pParse 	= this->m_child;
	CharEntry* last  	= NULL;
	while (pParse) {
		if (pParse == pEntry) {
			if (last) {
				last->m_next = pParse->m_next; 
			} else {
				this->m_child = pParse->m_next;
			}
			m_childCount--;
			return;
		}
		last = pParse;
		pParse = pParse->m_next;
	}
}

// =========================================================================
Dictionnary::Dictionnary()
: m_pCBDelete   (NULL)
, m_pCBContext  (NULL)
, m_pRoot       (NULL)
{
}

Dictionnary::Dictionnary(const void* callBackContext, cbDicoDelete ptrFct)
: m_pCBDelete   (ptrFct)
, m_pCBContext  (callBackContext)
, m_pRoot       (NULL)
{
}

bool 
Dictionnary::init(u16 dicoSize) 
{
	if (allocator.init(dicoSize)) {
		m_pRoot = new (&allocator) CharEntry(this);
		return true;
	}
	return false;
}

Dictionnary::~Dictionnary() 
{
	allocator.freeEntry(m_pRoot);
}

void 
Dictionnary::setOwnerCallback(const void* callBackContext, cbDicoDelete ptrFct)
{
	m_pCBDelete		= ptrFct;
	m_pCBContext	= callBackContext;
}

const void* 
Dictionnary::find(const char* string) 
{
	CharEntry* pNavigation = m_pRoot;
	// printf("Find : %s\n",string);
	while (*string != 0) {
		CharEntry* nextItem;
		bool res = pNavigation->findChildChar(&nextItem, *string);
		if (res) {
			// Character found, new child item found... continue.
			string++;
			pNavigation = nextItem;
		} else {
			// printf("NOT Found : %s\n", string);
			return NULL;
		}
	}
	
	// printf("Found : %s\n", string);
	return pNavigation->m_value;
}

void 
Dictionnary::add(const char* string, const void* value) 
{
	if (string != NULL) {
		// DEBUG_PRINT("Add : %s\n",string);
		CharEntry* pNavigation = m_pRoot;
		while (*string != 0) {
			CharEntry* nextItem;
			bool res = pNavigation->findChildChar(&nextItem, *string);
			if (res) {
				// Character found, new child item found... continue.
				pNavigation = nextItem;
			} else {
				CharEntry* createItem = new(&allocator) CharEntry(this, *string, (string[1] == 0) ? value : NULL);

				// Character not found : Create and insert
				pNavigation->insertChild(nextItem, createItem);
				pNavigation = createItem;
			}
			string++;
		}
		// dump();
	}
}

void 
Dictionnary::clear() 
{
	if (m_pRoot) {
		m_pRoot->clear();
	}
}

void 
Dictionnary::remove(const char* string) 
{
	if (string != NULL) {
		// DEBUG_PRINT("Remove : %s\n",string);
		bool del = true;
		removeRecursive(m_pRoot, string, &del);
		// dump();
		/*
		while (*string != 0) {
			CharEntry* nextItem;
			bool res = pNavigation->findChildChar(&nextItem, *string);
			if (res) {
				if (nextItem->m_childCount == 1) {
					// Delete entry only.
					pNavigation->removeChild(nextItem);
					// Delete sub tree.
					KLBDELETE(nextItem);
				
					return;
				}
			}
		}*/
	}
}

void 
Dictionnary::removeRecursive(CharEntry* pNode, const char* curr, bool* pDel) 
{
	CharEntry* nextItem;

	bool res = pNode->findChildChar(&nextItem, *curr);
	if (res) {
		removeRecursive(nextItem, &curr[1],pDel);
		if (nextItem->m_childCount == 0) {
			if (*pDel) {
				pNode->removeChild(nextItem);
				allocator.freeEntry(nextItem); // Direct call to allocator, do NOT delete
				if (m_pCBDelete && pNode->m_value) {
					m_pCBDelete(m_pCBContext, pNode->m_value);
				}
			}
		} else {
			*pDel = false;
		}
	} else {
		// ===============
		// Multiple texture can have same image sub symbol. --> Multiple delete on the same symbol can occur.
		// So assert is commented out.
		//
		// klb_assert((*curr==0),"Symbol not found for deletion");
		// ===============
	}
}

void Dictionnary::dump() {
	printf("==== Start Dico dump ====\n");
	dump(m_pRoot, 0, false);
	printf("\n==== End Dico dump ====\n");
}

void Dictionnary::dump(CharEntry* pNode, int level, bool fitLine) {
	if (fitLine) {
		for (int n = 0; n < level; n++) {
			printf(" ");
		}
	}
	fitLine = false;

	printf("%c",pNode->m_char);
	level++;
	CharEntry* pC = pNode->m_child;
	while (pC) {
		dump(pC, level, fitLine);
		pC = pC->m_next;
		if (pC) {
			fitLine = true;
			printf("\n");
		}
	}
}
