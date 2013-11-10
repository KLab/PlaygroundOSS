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
#ifndef KLB_DICTIONNARY_H
#define KLB_DICTIONNARY_H

#include "BaseType.h"
#include "ArrayAllocator.h"

class Dictionnary;

class CharEntry {
	friend class Dictionnary;
public:
	static void* operator new		(size_t size, ArrayAllocator<CharEntry>* pAlloc); 
	static void  operator delete	(void *p,	  ArrayAllocator<CharEntry>* pAlloc);

	CharEntry			();
	CharEntry			(Dictionnary* pOwner, char c, const void* value);
	CharEntry			(Dictionnary* pOwner);

	void clear			();
	bool findChildChar	(CharEntry** pEntry, char c);
	void insertChild	(CharEntry* pEntryBefore, CharEntry* pEntry);
	void removeChild	(CharEntry* pEntry);
	
protected:
	CharEntry*			m_next;
	CharEntry*			m_child;
	Dictionnary*		m_pOwner;
public:
	const void*			m_value;
	u8					m_childCount;
	char				m_char;
};

typedef	void	(*cbDicoDelete)(const void* ctx, const void* ptr);

class Dictionnary {
	friend class CharEntry;
public:
	Dictionnary			();
	Dictionnary			(const void* ctx, cbDicoDelete ptrFct);
	virtual ~Dictionnary();
	
	bool init			(u16 dicoSize);
	void dump			();
	const void* find	(const char* string);
	void add			(const char* string, const void* value);
	void remove			(const char* string);
	void clear			();
	void setOwnerCallback(const void* callBackContext, cbDicoDelete ptrFct);
private:
	void removeRecursive(CharEntry* pNode, const char* curr, bool* pDel);
	void dump			(CharEntry* pNode, int level, bool fitLine);

	ArrayAllocator<CharEntry>	
						allocator;
	CharEntry*			m_pRoot;
	cbDicoDelete		m_pCBDelete;
	const void*			m_pCBContext;
};

#endif // KLB_DICTIONNARY_H
