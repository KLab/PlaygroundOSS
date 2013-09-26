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
#include "CS_Memory.h"
#include "CS_Object.h"

System::RefHolder	g_globTempRefStack[256];
System::RefHolder*	g_globStack = g_globTempRefStack;

u32 _refCallFinish_(System::RefHolder* array_) {
	u32 res = g_globStack - g_globTempRefStack;
	memcpy(array_, g_globTempRefStack, res * sizeof(System::RefHolder));
	g_globStack = g_globTempRefStack;
	return res;
}

void _refRemove_(u32 count, System::RefHolder* array_) {
	for (u32 n = 0; n < count; n++) {
		System::__GCObject** holder = array_[n].pHolder;
		System::__GCObject* newRef = *holder;
		System::__GCObject* oldRef = array_[n].holderValue;
		if (newRef != oldRef) {
			if (oldRef) 	{ oldRef->_removeRef(holder); 	}
			if (newRef)		{ newRef->_addRef(holder); 		}
		}
	}
}

//
// Memory system itself
//
namespace System {

//
// TODO : have option to perform compaction on gen0 or gen1
// TODO : have option to move from gen0 to gen1
//	-> Mark the object after a first pass (move on 2nd pass) ?
//  Moving in gen1 while doing a progressive parsing is meaningless.
//	-> We must parse the whole heap of gen0 before moving them.
//  -> Thus use a marking and have the next parsing do the move.
//

/*static*/ __GCObject*		Memory::g_destroyList			= NULL;
/*static*/ u8*				Memory::s_bufferStart			= NULL;
/*static*/ u8* 				Memory::s_bufferEnd				= NULL;
/*static*/ u8* 				Memory::s_bufferStartGen1		= NULL;
/*static*/ u8* 				Memory::s_bufferAllocGen0		= NULL;		// Pointer to start of next freely available block
/*static*/ SAllocHeader*	Memory::s_bufferAllocGen0Prev	= NULL;		// Pointer to start of latest allocated block
/*static*/ SAllocHeader*	Memory::s_bufferAllocGen1Prev	= NULL;		// Pointer to start of latest allocated block in Gen1
/*static*/ u8* 				Memory::s_bufferAllocGen1		= NULL;		// Downward
/*static*/ SAllocHeader*	Memory::s_lastCompaction		= NULL;
/*static*/ u32				Memory::s_initMagic				= 0;
/*static*/ __GCObject***	Memory::g_rootList				= NULL;
/*static*/ u32				Memory::g_rootCount				= 0;
/*static*/ u32				Memory::ROOTCOUNT				= 0;
/*static*/ _CS_ArrayAllocator<RefList>*			Memory::g_allocPage		= NULL;
/*static*/ _CS_ArrayAllocator<SAllocMSEntry>*	Memory::g_allocMSEntry	= NULL;

void Memory::removeObject(__GCObject* obj) {
	Memory::injectToDieList(obj);

	// This may trigger a cascade of reference update here =>
	// This will increase the probability to reclaim memory in this pass
	// And make sure that all the memory is reclaimed in the 2nd pass after this one.
	while (obj && !obj->isDestroyed()) {
		obj->_releaseGC();
		obj->destroy();
		obj = (__GCObject*)obj->m_ownerA; // If not null, cascade occured.
	}

	// Empty List.
	g_destroyList = NULL;
}

void Memory::compactionInternal(CompactionContext& ctx) {
	SAllocHeader* pN = ctx.p->m_next;
	__GCObject* obj = (__GCObject*)&ctx.p[1];
	if (ctx.p->getFreed()) {
		#ifdef _DEBUG_MEMORY_
			printf("[REMOVED]\t0x%08x\t \t \t%x\n", ctx.p, ctx.p->getSize());
		#endif
		
		removeObject(obj);

		// Memory is reclaimed.
		if(!ctx.firstFreeGen0 && !ctx.firstFreeGen1) {
			if(ctx.genParsing == 0) {
				// Generation 0 - next moving object must move to Gen1
				ctx.firstFreeGen0 = ctx.p;
				ctx.firstFreeGen1 = (SAllocHeader*)System::Memory::s_bufferAllocGen1;
			} else {
				// Generation 1 - next moving object stays in Gen1
				ctx.firstFreeGen1	= ctx.p;
			}
		}
		ctx.removed++;
	} else {
		if(!ctx.firstFreeGen1 && ctx.genParsing == 0 && ctx.p->getSurvived()) {
			// The object has already survived a compaction, it must move to Gen1 in any case.
			ctx.firstFreeGen1 = (SAllocHeader*)System::Memory::s_bufferAllocGen1;
		}

		if(ctx.firstFreeGen1) {
			#ifdef _DEBUG_MEMORY_
				printf("[MOVED]\t\t0x%08x ->\t 0x%08x \t%x\n", ctx.p, ctx.firstFreeGen1, ctx.p->getSize());
			#endif
			u32 size = ctx.p->getSize() + sizeof(SAllocHeader);
			
			// firstFreeGen1 patch if this is not the first entry
			if((u8*)ctx.firstFreeGen1 == s_bufferEnd) {
				s_bufferStartGen1 = ((u8*)ctx.firstFreeGen1 - size);
			}
			if(ctx.genParsing == 0 && !ctx.lastValidGen1) {
				ctx.lastValidGen1 = (SAllocHeader*)System::Memory::s_bufferAllocGen1Prev;
			}
			
			ctx.firstFreeGen1 = (SAllocHeader*)((u8*)ctx.firstFreeGen1 - size);
			
			__GCObject* prev = (__GCObject*)&ctx.p[1];
			memcpy(ctx.firstFreeGen1, ctx.p, size);
			obj = (__GCObject*)&ctx.firstFreeGen1[1];
			obj->_moveUpdate(prev);
			ctx.p = ctx.firstFreeGen1;
			ctx.firstFreeGen1 = (SAllocHeader*)((u8*)ctx.p - size);
			ctx.moved	+= size;
		} else {
			if(ctx.genParsing == 0) {
				// if the object is still in Gen0 it is marked as SURVIVED to be move during the next compaction
				ctx.p->setSurvived();
			}
		}
		
		if(ctx.lastValidGen0 && !ctx.firstFreeGen1) {
			ctx.lastValidGen0->m_next	= ctx.p;
		} else if(ctx.lastValidGen1) {
			ctx.lastValidGen1->m_next	= ctx.p;
		}

		if(ctx.genParsing == 0 && !ctx.firstFreeGen1) {
			ctx.p->m_prev	= ctx.lastValidGen0;
		} else {
			ctx.p->m_prev	= ctx.lastValidGen1;
		}

		if(ctx.genParsing == 0 && !ctx.firstFreeGen1) {
			ctx.lastValidGen0 = ctx.p;
			ctx.lastValidGen1 = (SAllocHeader*)System::Memory::s_bufferAllocGen1Prev; // Not to remove s_bufferAllocGen1Prev after this method call.
		} else {
			ctx.lastValidGen1 = ctx.p;
		}
	}

	ctx.p = pN;
}

/*static*/
void Memory::injectToDieList(__GCObject* obj) {

	// Add to a link list of destroyed item.
	obj->m_ownerA = (__GCObject**)g_destroyList;
	// obj->m_ownerB = NULL; // Is already null !
	if (g_destroyList) {
		g_destroyList->m_ownerB = (__GCObject**)obj;
	}
	g_destroyList = obj;

	// Mark as destroyed.
	SAllocHeader* pN = (SAllocHeader*)obj;
	pN[-1].setFreed();
}

/*static*/
void Memory::rejectFromDieList(__GCObject* obj) {
	//
	// Remove from double link list.
	//
	if (obj->m_ownerA) {
		((__GCObject*)(obj->m_ownerA))->m_ownerB = obj->m_ownerB;
	}

	if (obj->m_ownerB) {
		((__GCObject*)(obj->m_ownerB))->m_ownerA = obj->m_ownerA;
	} else {
		g_destroyList = (__GCObject*)obj->m_ownerA;
	}

	// Mark as destroyed.
	SAllocHeader* pN = (SAllocHeader*)obj;
	pN[-1].unsetFreed();
	// m_ownerA is going to be filled.
	obj->m_ownerB = NULL;
}

/*static*/
void Memory::compactionSmall(u32 infos) {
	if(!(infos & (COMPACT_GEN0 | COMPACT_GEN1))) {
		return;
	}

	CompactionContext ctx;
	// If no item were allocated at all, no item to compact.
	// If last item exist, then first item exist at start adress. (compaction will garantee first entry at base adress)
	if(infos & COMPACT_GEN1) {
		ctx.p = s_bufferAllocGen1Prev ? (SAllocHeader*)s_bufferStartGen1 : NULL;
	} else {
		ctx.p = s_bufferAllocGen0Prev ? (SAllocHeader*)s_bufferStart : NULL;
	}
	ctx.lastValidGen0	= NULL;
	ctx.lastValidGen1	= NULL;
	ctx.firstFreeGen0	= NULL;
	ctx.firstFreeGen1	= NULL;
	ctx.moved		= 0;
	ctx.removed		= 0;
	ctx.genParsing	= (infos & COMPACT_GEN1) ? 1 : 0;

	#ifdef _DEBUG_MEMORY_
		CompactionContext dctx;
		dctx.genParsing	= (infos & COMPACT_GEN1) ? 1 : 0;
		if(dctx.genParsing == 0) {
			dctx.p = s_bufferAllocGen0Prev ? (SAllocHeader*)s_bufferStart : NULL;
		} else {
			dctx.p = s_bufferAllocGen1Prev ? (SAllocHeader*)s_bufferStartGen1 : NULL;
		}
		_debug_displayMemory(dctx);
	#endif

	while (ctx.p) {
		compactionInternal(ctx);
	}
	if(ctx.lastValidGen0) { ctx.lastValidGen0->m_next = NULL; }
	if(ctx.lastValidGen1) { ctx.lastValidGen1->m_next = NULL; }

	//
	// When compaction reach the end, we can modifiy :
	//
	// Take last allocated item and point to the next free block.
	// Then update last allocated item pointer.
	s_bufferAllocGen0 = (ctx.firstFreeGen0) ? (u8*)ctx.firstFreeGen0 : s_bufferStart;
	s_bufferAllocGen0Prev = ctx.lastValidGen0;

	if((ctx.genParsing == 0 && ctx.moved > 0) || (ctx.genParsing == 1 && (ctx.moved > 0 || ctx.removed > 0))) {
		s_bufferAllocGen1 = (ctx.firstFreeGen1) ? (u8*)ctx.firstFreeGen1 : s_bufferEnd;
		s_bufferAllocGen1Prev = ctx.lastValidGen1;
	}

	#ifdef _DEBUG_MEMORY_
		dctx.p = s_bufferAllocGen1Prev ? (SAllocHeader*)s_bufferStartGen1 : NULL;
		dctx.genParsing = 1;
		_debug_displayMemory(dctx);
	#endif

	#ifdef _DEBUG_MEMORY_
		dctx.p = s_bufferAllocGen0Prev ? (SAllocHeader*)s_bufferStart : NULL;
		dctx.genParsing = 0;
		_debug_displayMemory(dctx);
	#endif

	if((infos & COMPACT_GEN1) && (infos & COMPACT_GEN0)) {
		compactionSmall((infos & ~COMPACT_GEN1));
	}
}

SAllocMSEntry*	gEntryEnd;
SAllocMSEntry*	gEntryStart;
u32				gEntryCount;
u32				gEntryTotal;

bool Memory::pushList(__GCObject* obj, u32 startIndex) {
	// Push at end of list.
	SAllocMSEntry* pEntry = Memory::g_allocMSEntry->allocEntry();
	if (pEntry) {
		pEntry->prev		= gEntryEnd;
		if(gEntryEnd && gEntryEnd != pEntry) {
			gEntryEnd->next = pEntry;
		}
		pEntry->next		= NULL;
		pEntry->object		= obj;
		pEntry->startIndex	= startIndex;
		gEntryEnd			= pEntry;
		if (!gEntryStart) {
			gEntryStart = gEntryEnd;
		}
		gEntryCount++;
		return true;
	}
	return false;
}

u32 gLastIndex;

__GCObject* Memory::removeNext() {
	// Pop at beginning of the list
	if (gEntryStart) {
		SAllocMSEntry*	pRes = gEntryStart;
		__GCObject*		pObj = pRes->object;
		Memory::g_allocMSEntry->freeEntry(gEntryStart);
		gLastIndex		= pRes->startIndex;
		gEntryStart		= pRes->next;
		gEntryCount--;
		return pObj;
	}
	return NULL;
}

// TODO : inline to optimize.
bool Memory::emptyList() {
	return (gEntryCount == 0);
}

// TODO : inline to optimize.
u32 Memory::getProcessSizeMax() {
	// use gEntryCount, nb items
	u32 remain = gEntryTotal - gEntryCount;
	if (remain < 32) {
		return 0;
	}

	// Always leave a margin of 32.
	return remain - 32;
}

u32 Memory::getLastProcessIndex() {
	return gLastIndex;
}

void Memory::setLastProcessIndex(u32 index) {
	gLastIndex = index;
}

/*static*/
void Memory::compactionMS(u32 infos) {
	//
	// Phase 1 : Unmark Everything, Buffer will need to be __GCObject to avoid problems.
	//

	CompactionContext ctx;
	ctx.p = s_bufferAllocGen1Prev ? (SAllocHeader*)s_bufferStartGen1 : NULL;

	#ifdef _DEBUG_MEMORY_
		CompactionContext dctx;
		dctx.p = ctx.p;
		dctx.genParsing = 1;
		_debug_displayMemory(dctx);
	#endif

	while (ctx.p) {
		SAllocHeader* pN = ctx.p->m_next;
		ctx.p->unsetMark();
		ctx.p = pN;
	}

	ctx.p = s_bufferAllocGen0Prev ? (SAllocHeader*)s_bufferStart : NULL;
	
	#ifdef _DEBUG_MEMORY_
		dctx.p = ctx.p;
		dctx.genParsing = 0;
		_debug_displayMemory(dctx);
	#endif

	while (ctx.p) {
		SAllocHeader* pN = ctx.p->m_next;
		ctx.p->unsetMark();
		ctx.p = pN;
	}

	//
	// Phase 2 : Mark only alive.
	//

	// List reset
	gEntryEnd	= NULL;
	gEntryStart	= NULL;
	gEntryCount	= 0;

	for(u32 n = 0; n < g_rootCount; n++) {
		__GCObject** ptrOwner = g_rootList[n];
		if(*ptrOwner) {
			if(pushList(*ptrOwner,0)) {
				while(!emptyList()) {
					__GCObject* pObj = removeNext();
					u32 size = getProcessSizeMax();
					if(pObj && !pObj->isMarked() && (size != 0)) {
						if(pObj->_processGC() == __GCObject::INCOMPLETE) {
							// Push back at the end.
							// Call modify Size and return the next point to process during the call.
							pushList(pObj, getLastProcessIndex());
						} else {
							#ifdef _DEBUG_MEMORY_
								//SAllocHeader* pN = (SAllocHeader*)pObj;
								//printf("[MARKED]\t0x%08x\t%s %s %s\t\t%x\n", &pN[-1], pN[-1].getFreed() ? "F":" ", pN[-1].getDestroyed() ? "D":" ", pN[-1].getDestroyed() ? "S":" ", pN[-1].getSize());
							#endif
							pObj->mark();
						}
					}
				}
			}
		}
	}

	#ifdef _DEBUG_MEMORY_
		printf("\n");
	#endif

	//
	// Phase 3 : Delete Unmarked object.
	//
	if(!(infos & COMPACT_NOW)) {
		// Mark as Freed Gen 1
		ctx.p = (s_bufferAllocGen1 != s_bufferEnd) ? (SAllocHeader*)s_bufferStartGen1 : NULL;
		while(ctx.p) {
			SAllocHeader* pN = ctx.p->m_next;
			if(!ctx.p->getMark()) {
				Memory::injectToDieList((__GCObject*)&ctx.p[1]);
			}
			ctx.p = pN;
		}

		// Mark as Freed Gen 0
		ctx.p = s_bufferAllocGen0Prev ? (SAllocHeader*)s_bufferStart : NULL;
		while(ctx.p) {
			SAllocHeader* pN = ctx.p->m_next;
			if(!ctx.p->getMark()) {
				Memory::injectToDieList((__GCObject*)&ctx.p[1]);
			}
			ctx.p = pN;
		}
	} else {
		// GEN 1
		ctx.p				= (s_bufferAllocGen1 != s_bufferEnd) ? (SAllocHeader*)s_bufferStartGen1 : NULL;
		ctx.firstFreeGen0	= NULL;
		ctx.firstFreeGen1	= NULL;
		ctx.lastValidGen0	= NULL;
		ctx.lastValidGen1	= NULL;
		ctx.moved			= 0;
		ctx.removed			= 0;
		ctx.genParsing		= 1;
		while(ctx.p) {
			if(!ctx.p->getMark()) {
				Memory::injectToDieList((__GCObject*)&ctx.p[1]);
			}
			compactionInternal(ctx);
		}
		if(ctx.lastValidGen1) { ctx.lastValidGen1->m_next = NULL; }

		//
		// When compaction reach the end, we can modifiy :
		//
		// Take last allocated item and point to the next free block.
		if(ctx.moved > 0 || ctx.removed > 0) {
			s_bufferAllocGen1		= (ctx.firstFreeGen1) ? (u8*)ctx.firstFreeGen1 : s_bufferEnd;
			s_bufferAllocGen1Prev	= ctx.lastValidGen1;
		}

		// GEN 0
		ctx.p				= s_bufferAllocGen0Prev ? (SAllocHeader*)s_bufferStart : NULL;
		ctx.firstFreeGen0	= NULL;
		ctx.firstFreeGen1	= NULL;
		ctx.lastValidGen0	= NULL;
		ctx.lastValidGen1	= NULL;
		ctx.moved			= 0;
		ctx.removed			= 0;
		ctx.genParsing		= 0;
		while(ctx.p) {
			if(!ctx.p->getMark()) {
				Memory::injectToDieList((__GCObject*)&ctx.p[1]);
			}
			compactionInternal(ctx);
		}
		if(ctx.lastValidGen0) { ctx.lastValidGen0->m_next = NULL; }
		if(ctx.lastValidGen1) { ctx.lastValidGen1->m_next = NULL; }

		//
		// When compaction reach the end, we can modifiy :
		//
		// Take last allocated item and point to the next free block.
		// Then update last allocated item pointer.
		s_bufferAllocGen0		= (ctx.firstFreeGen0) ? (u8*)ctx.firstFreeGen0 : s_bufferStart;
		s_bufferAllocGen0Prev	= ctx.lastValidGen0;
		if(ctx.moved > 0) {
			s_bufferAllocGen1		= (ctx.firstFreeGen1) ? (u8*)ctx.firstFreeGen1 : s_bufferEnd;
			s_bufferAllocGen1Prev	= ctx.lastValidGen1;
		}
	}

	#ifdef _DEBUG_MEMORY_
		dctx.p = s_bufferAllocGen1Prev ? (SAllocHeader*)s_bufferStartGen1 : NULL;
		dctx.genParsing = 1;
		_debug_displayMemory(dctx);
	#endif

	#ifdef _DEBUG_MEMORY_
		dctx.p = s_bufferAllocGen0Prev ? (SAllocHeader*)s_bufferStart : NULL;
		dctx.genParsing = 0;
		_debug_displayMemory(dctx);
	#endif
}

/*static*/
void* Memory::allocate(u32 size) {
	size = (size + 3) & 0xFFFFFFFC;
	u32 asize = size + sizeof(SAllocHeader);
	
	u8* newPostAdress = &s_bufferAllocGen0[asize];

	/* WARNING : CAN NOT PERFORM COMPACTION HERE IN CURRENT IMPLEMENTATION :
	   LOCAL VARIABLE ARE NOT PROCESSED :
	   Variable-only link will lead to a destruction of a valid object !

	if (newPostAdress >= s_bufferAllocGen1) {
		compactionSmall();
	}*/

	if (newPostAdress < s_bufferAllocGen1) {
		// Get Base Adress.
		SAllocHeader* pAlloc = (SAllocHeader*)s_bufferAllocGen0;

		// Update related structure.
		pAlloc->m_info	= size;
		pAlloc->m_prev	= s_bufferAllocGen0Prev;
		pAlloc->m_next	= NULL;
		if(s_bufferAllocGen0Prev) {
			s_bufferAllocGen0Prev->m_next = pAlloc;
		}
		
		// Increment allocator
		s_bufferAllocGen0Prev	= pAlloc; 
		s_bufferAllocGen0		= newPostAdress;

		// Clean allocated memory.
		__GCObject* obj = (__GCObject*)&pAlloc[1];
		memset(obj, 0, size);

		// Put in the die list right away : nobody points to it.
		injectToDieList(obj);

		// Return object base adress.
		return obj;
	} else {
		return NULL;
	}
}

/*static*/
void Memory::release() {
	if (s_bufferStart) {
		CS_FREE(s_bufferStart);
		s_bufferStart = NULL;
	}

	if (g_rootList) {
		CS_FREE(g_rootList);
		g_rootList = NULL;
	}

	if (g_allocPage) {
		delete g_allocPage;
		g_allocPage = NULL;
	}

	if (g_allocMSEntry) {
		delete g_allocMSEntry;
		g_allocMSEntry = NULL;
	}
}

/*static*/
bool Memory::setGlobalMemory(u32 size, u32 rootCount, u16 MultipleRefPageCount, u16 MarkAndSweepStackSize) {
	s_bufferStart	= (u8*)CS_MALLOC(size);
	g_rootList		= (__GCObject***)CS_MALLOC(rootCount * sizeof(__GCObject**));
	g_allocPage		= new _CS_ArrayAllocator<System::RefList>();
	g_allocMSEntry	= new _CS_ArrayAllocator<System::SAllocMSEntry>();
	
	if (s_bufferStart && g_rootList && g_allocPage && g_allocMSEntry) {
		if ((g_allocPage->init(MultipleRefPageCount)) && (g_allocMSEntry->init(MarkAndSweepStackSize))) {
			s_initMagic			= MAGICNUMBER;	// Magic number checking for allocation.
			s_bufferEnd			= s_bufferStart + size;
			s_bufferStartGen1	= NULL;
			s_bufferAllocGen0	= s_bufferStart;
			s_bufferAllocGen1	= s_bufferEnd;
			g_rootCount			= 0;
			gEntryTotal			= MarkAndSweepStackSize;
			ROOTCOUNT			= rootCount;
			return true;
		}
	}

	release();
	return false;
}

void Memory::registerGCRoot(void* ptr) {
	__GCObject** ptrOwner = (__GCObject**)ptr;
	CS_Assert(g_rootCount != ROOTCOUNT, "Please change root count, maximum reached.");
	g_rootList[g_rootCount++] = ptrOwner;
	if (*ptrOwner) {
		(*ptrOwner)->_addRef(ptrOwner);
	}
}

//
// Object Allocation
//

void* __GCObject::operator new(size_t size)
{	
	CS_Assert(Memory::s_initMagic == MAGICNUMBER, "Memory::setGlobalMemory not set yet !");
	__GCObject* obj = (__GCObject*)Memory::allocate(size);
	if (!obj) {
		THROW(CS_NEW OutOfMemoryException());
	}
	
	return obj;
}

void* __GCObject::operator new(size_t size, size_t sizeBuffer)
{	
	CS_Assert(Memory::s_initMagic == MAGICNUMBER, "Memory::setGlobalMemory not set yet !");
	__GCObject* obj = (__GCObject*)Memory::allocate(sizeBuffer);
	if (!obj) {
		THROW(CS_NEW OutOfMemoryException());
	}
	
	return obj;
}

/*static*/
void* __GCMalloc::allocBlock(u32 byteCount, __GCMalloc*& wrapper) {
	__GCMalloc* obj = new(byteCount + sizeof(__GCMalloc)) __GCMalloc();
	
	wrapper = obj;
	return &((u8*)obj)[sizeof(__GCMalloc)];
}

//
// Wrapper to assign object to member.
//
/*static*/
__GCObject* __GCObject::_RefSetValue(__GCObject** m_ptrOwner, __GCObject* object) {
	if (*m_ptrOwner && !(*m_ptrOwner)->isFreed()) 	{ 
		(*m_ptrOwner)->_removeRef(m_ptrOwner);
	}
	if (object)			{ 
		object->_addRef(m_ptrOwner); 		
	}
	*m_ptrOwner = object;
	return object;
}

/*static*/
__GCObject* __GCObject::_RefSetOwner(__GCObject** m_ptrOwner, __GCObject* object) {
	if(*m_ptrOwner) {
		(*m_ptrOwner)->_removeOwner(*m_ptrOwner);
		if (object)	{ 
			object->_addOwner(*m_ptrOwner);
		}
		*m_ptrOwner = object;
	}
	return object;
}

//
// Compaction
//
void __GCObject::_moveUpdate(__GCObject* beforeMoveObj) {
	if (m_ownerA != (__GCObject**)0xFFFFFFFF) {
		if (m_ownerA)	{
			if(((ptrAsInt)m_ownerA & 0x3) == 0x3) {
				CS_AssertAlways("It should be impossible to have this kind of reference now. Not used in current version.");
			} else if(((ptrAsInt)m_ownerA & 0x3) == 0x1) {
				__GCObject* obj = (__GCObject*)((ptrAsInt)m_ownerA & ~0x1);
				obj->_move(beforeMoveObj, this);
			} else if(((ptrAsInt)m_ownerA & 0x3) == 0x2) {
				CS_AssertAlways("It should be impossible to have this kind of reference now. Not used in current version.");
			} else {
				*m_ownerA = this;
			}
		}
		if (m_ownerB)	{ 
			if(((ptrAsInt)m_ownerB & 0x3) == 0x3) {
				CS_AssertAlways("It should be impossible to have this kind of reference now. Not used in current version.");
			} else if(((ptrAsInt)m_ownerB & 0x3) == 0x1) {
				__GCObject* obj = (__GCObject*)((ptrAsInt)m_ownerB & ~0x1);
				obj->_move(beforeMoveObj, this);
			} else if(((ptrAsInt)m_ownerB & 0x3) == 0x2) {
				CS_AssertAlways("It should be impossible to have this kind of reference now. Not used in current version.");
			} else {
				*m_ownerB = this;
			}
		}
	} else {
		((RefList*)m_ownerB)->updateListMove(beforeMoveObj, this);
	}

	// After moving, the object must patch its own members
	_moveAlert((u8*)this - (u8*)beforeMoveObj);
}

//
// Reference Maintenance
//
void __GCObject::_removeRef(__GCObject** ptrOwner) {
	if(m_ownerA == ptrOwner) {
		m_ownerA = m_ownerB;
		m_ownerB = NULL;
		if (m_ownerA == NULL) {
			Memory::injectToDieList(this);
		}
	} else if (m_ownerB == ptrOwner) {
		m_ownerB = NULL;
	} else {
		((RefList*)m_ownerB)->removeList(this,ptrOwner);
	}
}

void __GCObject::_addRef(__GCObject** ptrOwner) {
	if(m_ownerA == ((__GCObject**)0xFFFFFFFF)) {
		((RefList*)m_ownerB)->addList(ptrOwner);
	} else {
		SAllocHeader* pN = (SAllocHeader*)this;
		if(pN[-1].getFreed()) {
			Memory::rejectFromDieList(this);
			m_ownerA = ptrOwner;
		} else {
			if(m_ownerB == NULL) {
				m_ownerB = ptrOwner;
			} else {
				m_ownerB = (__GCObject**)RefList::createList(this, ptrOwner);
				m_ownerA = (__GCObject**)0xFFFFFFFF;
			}
		}
	}
}

void __GCObject::_moveRef(__GCObject** oldPtr, __GCObject** newPtr) {
	if(m_ownerA == oldPtr) {
		m_ownerA = newPtr;
	} else if (m_ownerB == oldPtr) {
		m_ownerB = newPtr;
	} else {
		((RefList*)m_ownerB)->moveRefList(oldPtr,newPtr);
	}
}

void __GCObject::_removeOwner(__GCObject* ptrOwner) {
	__GCObject** ptrOwner1 = (__GCObject**)((ptrAsInt)ptrOwner | 0x1);
	//__GCObject** ptrOwner2 = (__GCObject**)((ptrAsInt)ptrOwner | 0x3);
	if(m_ownerA == ptrOwner1 /*|| m_ownerA == ptrOwner2*/) {
		m_ownerA = m_ownerB;
		m_ownerB = NULL;
		if (m_ownerA == NULL) {
			Memory::injectToDieList(this);
		}
	} else if (m_ownerB == ptrOwner1 /*|| m_ownerB == ptrOwner2*/) {
		m_ownerB = NULL;
	} else {
		((RefList*)m_ownerB)->removeListOwner(this, ptrOwner);
	}
}

void __GCObject::_moveOwner(__GCObject*  oldObj, __GCObject* newObj) {
	__GCObject** oldObjPtr1 = (__GCObject**)((ptrAsInt)oldObj | 0x1);
	__GCObject** newObjPtr1 = (__GCObject**)((ptrAsInt)newObj | 0x1);
	if(m_ownerA == oldObjPtr1) {
		m_ownerA = newObjPtr1;
	} else if (m_ownerB == oldObjPtr1) {
		m_ownerB = newObjPtr1;
	} else {
		((RefList*)m_ownerB)->moveRefListOwner(oldObj, newObj);
	}
}


void RefList::updateListMove(__GCObject* prevObjMoving, __GCObject* objMoving) {
	RefList* p = this;
loop:
	for (int n=0; n < 4; n++) {
		__GCObject** adr = p->m_refArr[n];
		if (adr)	{
			if(((ptrAsInt)adr & 0x3) == 0x3) {
				CS_AssertAlways("It should be impossible to have this kind of reference now. Not used in current version.");
			} else if(((ptrAsInt)adr & 0x3) == 0x1) {
				__GCObject* obj = (__GCObject*)((ptrAsInt)adr & ~0x1);
				// Just call the Owner _move virtual method.
				obj->_move(prevObjMoving, objMoving);
			} else if(((ptrAsInt)adr & 0x3) == 0x2) {
				CS_AssertAlways("It should be impossible to have this kind of reference now. Not used in current version.");
			} else {
				*adr = objMoving;
			}
		}
	}
	if (p->m_next)		{ p = p->m_next; goto loop; }
}

void RefList::addList(__GCObject** newRef) {
	RefList* p = this;
loop:
	if (p->m_refArr[0] == NULL)	{ p->m_refArr[0] = newRef; }
	else
	if (p->m_refArr[1] == NULL)	{ p->m_refArr[1] = newRef; }
	else
	if (p->m_refArr[2] == NULL)	{ p->m_refArr[2] = newRef; }
	else
	if (p->m_refArr[3] == NULL)	{ p->m_refArr[3] = newRef; }
	else {
		// Tries to fill existing list first...
		if (p->m_next == NULL) {
			p->m_next = Memory::g_allocPage->allocEntry();
		}
		p = p->m_next;
		goto loop;
	}
}

void RefList::removeList(__GCObject* obj, __GCObject** ref) {
	RefList* pList	= this;
	RefList* pPrev  = NULL;
	bool found		= false;
loop:
	int idx = 0;
	while (idx < 4) {
		if (pList->m_refArr[idx] == ref) {
			found = true;
			break;
		}
		idx++;
	}

	if (found == false) {
		pPrev = pList;
		pList = pList->m_next;
		goto loop;	// IF should not be necessary : pointer always inside.
	}

	//
	// Perform reduction.
	//
	int n = idx;
	while(n < 3) {
		pList->m_refArr[n] = pList->m_refArr[n+1];
		n++;
	}
	pList->m_refArr[3] = NULL;


	// Stand alone, remain only 2 entries
	if ((pPrev == NULL) && (pList->m_next == NULL) && (pList->m_refArr[2] == NULL)) {
		obj->m_ownerA	= pList->m_refArr[0];
		obj->m_ownerB	= pList->m_refArr[1];
		Memory::g_allocPage->freeEntry(pList);

		//Early exit.
		return;
	}

	// List has previous or successor...
	// Is empty ?
	if (pList->m_refArr[0] == NULL) {
		if (pPrev) {
			pPrev->m_next = pList->m_next;
		} else {
			// List may be empty or beginning of list.
			obj->m_ownerB = (__GCObject**)pList->m_next;
		}
		Memory::g_allocPage->freeEntry(pList);
	}
}

void RefList::removeListOwner(__GCObject* obj, __GCObject* ptrOwner) {
	__GCObject** ptrOwner1 = (__GCObject**)((ptrAsInt)ptrOwner | 0x1);
	RefList* pList	= this;
	RefList* pPrev  = NULL;
	bool found		= false;
loop:
	int idx = 0;
	while (idx < 4) {
		if (pList->m_refArr[idx] == ptrOwner1) {
			found = true;
			break;
		}
		idx++;
	}

	if (found == false) {
		pPrev = pList;
		pList = pList->m_next;
		goto loop;	// IF should not be necessary : pointer always inside.
	}

	//
	// Perform reduction.
	//
	int n = idx;
	while(n < 3) {
		pList->m_refArr[n] = pList->m_refArr[n+1];
		n++;
	}
	pList->m_refArr[3] = NULL;


	// Stand alone, remain only 2 entries
	if ((pPrev == NULL) && (pList->m_next == NULL) && (pList->m_refArr[2] == NULL)) {
		obj->m_ownerA	= pList->m_refArr[0];
		obj->m_ownerB	= pList->m_refArr[1];
		Memory::g_allocPage->freeEntry(pList);

		//Early exit.
		return;
	}

	// List has previous or successor...
	// Is empty ?
	if (pList->m_refArr[0] == NULL) {
		if (pPrev) {
			pPrev->m_next = pList->m_next;
		} else {
			// List may be empty or beginning of list.
			obj->m_ownerB = (__GCObject**)pList->m_next;
		}
		Memory::g_allocPage->freeEntry(pList);
	}
}

void RefList::moveRefList(__GCObject** oldRef, __GCObject** newRef) {
	RefList* p = this;
loop:
	if		(p->m_refArr[0] == oldRef)	{ p->m_refArr[0] = newRef; }
	else if (p->m_refArr[1] == oldRef)	{ p->m_refArr[1] = newRef; }
	else if (p->m_refArr[2] == oldRef)	{ p->m_refArr[2] = newRef; }
	else if (p->m_refArr[3] == oldRef)	{ p->m_refArr[3] = newRef; }
	else {
		p = p->m_next;
		goto loop;
	}
}

void RefList::moveRefListOwner(__GCObject* oldObj, __GCObject* newObj) {
	RefList* p = this;
	__GCObject** oldRef1 = (__GCObject**)((ptrAsInt)oldObj | 0x1);
	__GCObject** newRef1 = (__GCObject**)((ptrAsInt)newObj | 0x1);
loop:
	if		(p->m_refArr[0] == oldRef1)	{ p->m_refArr[0] = newRef1; }
	else if (p->m_refArr[1] == oldRef1)	{ p->m_refArr[1] = newRef1; }
	else if (p->m_refArr[2] == oldRef1)	{ p->m_refArr[2] = newRef1; }
	else if (p->m_refArr[3] == oldRef1)	{ p->m_refArr[3] = newRef1; }
	else {
		p = p->m_next;
		goto loop;
	}
}

RefList* RefList::createList(__GCObject* obj, __GCObject** newRef) {
	// 1. Create new list
	RefList* pList	= Memory::g_allocPage->allocEntry();

	// 2.
	pList->m_refArr[0]	= obj->m_ownerA;
	pList->m_refArr[1]	= obj->m_ownerB;
	pList->m_refArr[2]	= newRef;
	pList->m_refArr[3]	= NULL;
	pList->m_next		= NULL;
	return pList;
}

/*
	1. Have struct count the number of ref GCObject
	2. Have struct count the combined count also. (struct in struct)
	3. Have the compiler do the sum of those to get the max amount of possible references


	// Compiler now need to generate something like this :

	fct_ref(ref a, ref b) {
		RefHolder array[MAX_COUNT];		
		u32 count = _refCallFinish(array);

		... perform call here ...

		_refRemove_(count,array);
	}
 */

/*static*/
__GCObject*& __GCObject::__registerByRef(__GCObject*& ref) {
	// TODO Check stack end reach.
	// TODO Compiler can check also max needed limit.
	g_globStack->holderValue	= ref;
	g_globStack->pHolder		= &ref;
	g_globStack++;
	return ref;
}

#ifdef _DEBUG_MEMORY_

void __GCObject::_debug_displayReferences(u8 tabsNb, u8 tabsOnFirstLine) {
	if(m_ownerA != (__GCObject**)0xFFFFFFFF) {
		if(m_ownerA) {
			for(u8 i = 0; i < tabsOnFirstLine; ++i) { printf("\t"); }
			if(((ptrAsInt)m_ownerA & 0x3) == 0x3) {
				CS_AssertAlways("It should be impossible to have this kind of reference now. Not used in current version.");
			} else if(((ptrAsInt)m_ownerA & 0x3) == 0x1) {
				printf("+ 0x%08x [A][OWNER]\n", ((ptrAsInt)m_ownerA & ~0x1));
			} else if(((ptrAsInt)m_ownerA & 0x3) == 0x2) {
				CS_AssertAlways("It should be impossible to have this kind of reference now. Not used in current version.");
			} else {
				printf("+ 0x%08x [A]\n", m_ownerA);
			}
		}
		if(m_ownerB)	{ 
			for(u8 i = 0; i < tabsNb; ++i) { printf("\t"); }
			if(((ptrAsInt)m_ownerB & 0x3) == 0x1) {
				CS_AssertAlways("It should be impossible to have this kind of reference now. Not used in current version.");
			} else if(((ptrAsInt)m_ownerB & 0x3) == 0x1) {
				printf("+ 0x%08x [B][OWNER]\n", ((ptrAsInt)m_ownerB & ~0x1));
			} else if(((ptrAsInt)m_ownerB & 0x3) == 0x2) {
				CS_AssertAlways("It should be impossible to have this kind of reference now. Not used in current version.");
			} else {
				printf("+ 0x%08x [B]\n", m_ownerB);
			}
		}
	} else {
		RefList* pList = ((RefList*)m_ownerB);
		u8 rank = 1;
		while(pList) {
			for(u8 i = 0; i < 4; ++i) {
				__GCObject** adr = pList->m_refArr[i];
				if(adr) {
					for(u8 j = 0; j < ((rank == 1 && i == 0) ? tabsOnFirstLine : tabsNb); ++j) { printf("\t"); }
					for(u8 j = 0; j < rank*2; ++j) { printf("+"); };
					if(((ptrAsInt)adr & 0x3) == 0x3) {
						CS_AssertAlways("It should be impossible to have this kind of reference now. Not used in current version.");
					} else if(((ptrAsInt)adr & 0x3) == 0x1) {
						printf("+ 0x%08x [%i][OWNER]\n", ((ptrAsInt)adr & ~0x1), i);
					} else if(((ptrAsInt)adr & 0x3) == 0x2) {
						CS_AssertAlways("It should be impossible to have this kind of reference now. Not used in current version.");
					} else {
						printf("+ 0x%08x [%i]\n", adr, i);
					}
				} else {
					break;
				}
			}
			++rank;
			pList = pList->m_next;
		}
	}
}

void Memory::_debug_displayMemory(CompactionContext ctx) {
	u32 parsingStart	= (ctx.genParsing == 0) ? (u32)s_bufferStart			: (u32)s_bufferStartGen1;
	u32 parsingEnd		= (ctx.genParsing == 0) ? (u32)s_bufferAllocGen0Prev	: (u32)s_bufferAllocGen1Prev;
	printf("\n");
	printf("=======================================================================\n");
	printf("\tMemory Dump - GENERATION %i - from 0x%08x to 0x%08x\n", ctx.genParsing, parsingStart, parsingEnd);
	printf("=======================================================================\n");
	printf("INDEX \t\t ADDRESS \t INFOS \t SIZE\n");
	printf("=======================================================================\n");
	u32 debugCount = 0;
	while(ctx.p) {
		printf("[%i]\t\t0x%08x\t%s %s %s\t\t%x", debugCount, ctx.p, ctx.p->getFreed() ? "F":" ", ctx.p->getDestroyed() ? "D":" ", ctx.p->getSurvived() ? "S":" ", ctx.p->getSize());
		if(!ctx.p->getFreed()) {
			((__GCObject*)(&ctx.p[1]))->_debug_displayReferences(7,1);
		} else {
			printf("\n");
		}
		debugCount++;
		ctx.p = ctx.p->m_next;
	}
	printf("=======================================================================\n");
	printf("\n");
}

#endif

}
