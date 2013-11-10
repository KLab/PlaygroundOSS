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
#ifndef __ARRAY_ALLOCATOR_KLB_H_
#define __ARRAY_ALLOCATOR_KLB_H_

#include "BaseType.h"

template <class T>
class ArrayAllocator {
protected:
	struct ArrayItem {
	public:
		ArrayItem () {}
		~ArrayItem() {}

		T 	entry;
		u16	next;
		u16 prev;
	};
private:
	struct AllocatorContext {
		AllocatorContext*	m_next;
		ArrayItem*			m_array;
		u32					m_allocated;
		u32					m_arrayCount;
		u32					m_freeList;
		u32					m_usedList;

		T* allocEntry() {
			if (m_freeList == NULL_IDX) {
				klb_assertAlways("Allocator Full");
				return NULL;
			} else {
				m_allocated++;

				u16 newItem = m_freeList;
		
				// Remove from free list.
				m_freeList	= m_array[newItem].next;
				if (m_freeList != NULL_IDX) {	m_array[m_freeList].prev = NULL_IDX;	}
		
				// Add to used list.
				m_array[newItem].next = m_usedList;
				m_array[newItem].prev = NULL_IDX;
				if (m_usedList != NULL_IDX) {	m_array[m_usedList].prev = newItem;		}
				m_usedList = newItem;
				return &m_array[newItem].entry;
			}
		}

		void freeEntry(T* entry) {
			if (!entry)	{ return ;}	// Safe delete
			ArrayItem* pItem = (ArrayItem*)entry;
	
			m_allocated--;

			//
			// Remove from active list
			//
			if (pItem->prev != NULL_IDX) {
				m_array[pItem->prev].next = pItem->next;
			} else {
				m_usedList = pItem->next;
			}
	
			if (pItem->next != NULL_IDX) {
				m_array[pItem->next].prev = pItem->prev;
			}
	
			//
			// Add to free list
			//
			u16 idx = pItem - m_array;
			if (m_freeList != NULL_IDX) {
				m_array[m_freeList].prev = idx;
			}
	
			pItem->next = m_freeList;
			pItem->prev = NULL_IDX;

			// Position.
			m_freeList = idx;
		}

	};

	AllocatorContext m_defaultSlot;
	u16				 m_extendSize;
public:
	ArrayAllocator()
	{
		m_defaultSlot.m_next		= NULL;
		m_defaultSlot.m_array		= NULL;
		m_defaultSlot.m_freeList	= NULL_IDX;
		m_defaultSlot.m_usedList	= NULL_IDX;
		m_defaultSlot.m_arrayCount	= 0;
	}

	~ArrayAllocator()
	{
		release();
	}
	
	bool addSlot(u32 entryCount, AllocatorContext* pSlot) {
		pSlot->m_array = (ArrayItem*)KLBNEWA(u8, entryCount*sizeof(ArrayItem));
		if (pSlot->m_array) {
			pSlot->m_arrayCount  = entryCount;
			pSlot->m_allocated	 = 0;

			for (u32 n=0; n < entryCount; n++) {
				pSlot->m_array[n].next = n+1;
				pSlot->m_array[n].prev = n-1;
			}
		
			pSlot->m_array[0].prev				= NULL_IDX;
			pSlot->m_array[entryCount-1].next	= NULL_IDX;
			pSlot->m_freeList					= 0;
			pSlot->m_usedList					= NULL_IDX;
			return true;
		}
		return false;
	}

	bool init(u16 entryCount) {
		m_extendSize = entryCount / 3;
		return addSlot(entryCount, &m_defaultSlot);
	}

	void release() {
		AllocatorContext* pContext = &m_defaultSlot;
		while (pContext) {
			KLBDELETEA((u8*)pContext->m_array);
			pContext->m_array = NULL;
			pContext = pContext->m_next;
		}

		// Destroy sub slot struct.
		pContext = m_defaultSlot.m_next;
		while (pContext) {
			AllocatorContext* pNext = pContext->m_next;
			KLBDELETE(pContext);
			pContext = pNext;
		}
	}
	
	T* allocEntry() {
		// 1. Find first slot with free item
		AllocatorContext* pContext		= &m_defaultSlot;
		AllocatorContext* pPrevContext	= NULL;
		while (pContext) {
			if (pContext->m_freeList != NULL_IDX) {
				return pContext->allocEntry();
			}
			pPrevContext = pContext;
			pContext = pContext->m_next;
		}
		
		// 2. If none found, create new lost and allocated item.
		pPrevContext->m_next = KLBNEW(AllocatorContext);
		if (pPrevContext->m_next) {
			pContext = pPrevContext->m_next;
			if (addSlot(m_extendSize, pContext)) {
				return pContext->allocEntry();
			}
		}

		return NULL;
	}

	void freeEntry(T* entry) {
		// 1.Find from which slot it has been allocated.
		AllocatorContext* pContext		= &m_defaultSlot;
		AllocatorContext* pPrevContext	= NULL;
		while (pContext) {
			ArrayItem*	start = pContext->m_array;
			ArrayItem*  end   = &start[pContext->m_arrayCount];
			if (((void*)entry >= (void*)start) && ((void*)entry < (void*)end)) {
				// Found slot
				pContext->freeEntry(entry);
				// 2.If counter reach zero AND is NOT default slot, remove from list and destroy slot.
				if ((pContext->m_allocated == 0) && (pContext != &m_defaultSlot)) {
					// Remove from slot list
					pPrevContext->m_next = pContext->m_next;
					// Remove array
					KLBDELETEA((u8*)pContext->m_array);
					// Remove slot
					KLBDELETE(pContext);
				}
				return;
			}
			pPrevContext	= pContext;
			pContext		= pContext->m_next;
		}

	}
};

#endif
