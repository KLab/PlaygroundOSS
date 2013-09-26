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
#ifndef _CS_Memory_h_
#define _CS_Memory_h_

#include "../CompilerProject/BaseType.h"

/*
	Memory System Description :

	0 - Does NOT support multitasking.
		It is oriented for scripting and be light weight as possible, easy implementation
		for now.

	1 - All big objects will be allocated in a special pool.
	
	2 - All small objects will have a 2 Generation Heap (0 and 1).
	
	3 - The 2 Generation heap are using the same heap space, allowing dynamic balancing between both heaps.

		The trick is that the second generation (generation 1) is using the memory
		from the highest memory pointer to the lowest, while first generation
		is using memory from the lowest to the highest.
		=> When they meet, it means that memory is full.

		(like the heap and stack using the same memory)

	4 - Garbage collection is a mix of both reference counting-like mecanism, and mark & sweep.

	The technical reason are the following :
		- Mark & Sweep is perfect for detecting all the leaks, but must be an ATOMIC operation.
		Thus, is very costly.

		- Reference counting allow to handle destruction, recollection of memory little by little.
		Thus, allow to delay memory processing over multiple frames, more adapted to real-time.
		Problem : Reference counting does not work well with cyclic graph, thus need a more
		complex way to sometime reclaim memory.

	5 - Actually we do not use reference counting, but keep track of all object owner inside the object itself.
		- This allows us to perform compaction very easily : we can move a single object and update the owner directly.

	6 - WARNING, our system has the following limitation for now :
		
		6.1 - We do NOT scan the stack.
		
		WARNING => Garbage collection must occur ONLY when script is NOT executing.
		It means that your system has better to garbage collect little by little to make
		sure that you have enough room for allocation.

		WARNING => Do not modify the new allocator to force recompaction, else make sure
		that you have implemented support for local variables.

		Again, I repeat to make clean : garbage collection MUST always occurs outside of script execution.

	7 - Logic / Algorithm implementation is the following.
		
		7.1 -	Each time a static or instance member has a pointer modified (write),
				the previous and new pointer are updated of owner ship change.
				
				When no ownership is set, it is marked as being FREED.
				When ownership    is set, it is marked as being NOT FREED.

				TRICK : When object is freed, there is a link list of object marked freed,
				we reuse the reference pointer to this new purpose.

		7.2 -	Compaction / Memory recollection :

				For each item in the heap
					If the item is marked as free
						=> Update references => Other object may marked free and added to list of object to destroy.
						=> Parse the list of item to destroy until list is empty.
					else
						=> Move the object if adress has changed (Object Copy + Update references to object)

				We keep track of the last valid item to decide where to move the object when doing the compaction.
				
				Compaction can be performed atomically for one item only , thus allowing to run the compaction
				the way we want for multiple items :
				- Time limited
				- Number of item limited
				- Amount of memory processed
				- Etc... etc...

		7.3 -	Function Dependancies
			
				garbageCollection / member write
					releaseGC()
						_removeRef	
							->	injectToDieList
						_addRef		
							->	rejectFromDieList

				Inside garbage collection, parse "die list" and call releaseGC for each.

	
	All and all, our system is quite primitive. But it should be efficient enough
	for scripting and real time execution for video games.

	- The limitation for allocation error at runtime can be compensated easily by
	regular low cost maintenance collection.

	- Allocation of list for more than 2 references to object is something more costly,
	but those kind of memory structure are rare, and the overhead of such should be bearable for scripting then.

 */

#define MAGICNUMBER 0xC0FEBABE
//#define _DEBUG_MEMORY_

void*	CS_malloc(size_t size);
void	CS_free(void* ptr);
void*	CS_realloc(void *memblock, size_t size, size_t oldSize);

#define CS_MALLOC(size)					CS_malloc(size)
#define CS_FREE(ptr)					CS_free(ptr)
#define CS_REALLOC(ptr,size,oldSize)	CS_realloc(ptr,size,oldSize)

#define	CS_NEW			new
#define CS_DELETE		delete
#define CS_DELETEA		delete[]
#define CS_NEWA(a,b)	new a[b]

namespace System {

class Object;
class __GCObject;

struct RefHolder {
	System::__GCObject**	pHolder;
	System::__GCObject*		holderValue;
};

class GC {
public:
	static void Collect(s32 generation);
	static s32  CollectionCount(s32 generation);
	static s32	GetGeneration(Object* object);
	static s32	GetTotalMemory(bool forceFullCollection);
};

struct SAllocMSEntry {
	u32				startIndex;
	__GCObject*		object;
	SAllocMSEntry*	next;
	SAllocMSEntry*	prev;
};

struct RefList {
	void updateListMove			(__GCObject* prevObjMoving, __GCObject* objMoving);
	void addList				(__GCObject** newRef);
	void removeList				(__GCObject* obj,		__GCObject** ref);
	void removeListOwner		(__GCObject* obj,		__GCObject* ptrOwner);
	void moveRefList			(__GCObject** oldRef,	__GCObject** newRef);
	void moveRefListOwner		(__GCObject* oldObj,	__GCObject* newObj);
	static RefList* createList	(__GCObject* obj,		__GCObject** newRef);

	__GCObject**	m_refArr[4];
	RefList*		m_next;			// Note : can store bottom 2 bit for counter.
};

struct SAllocHeader {
	SAllocHeader* 	m_prev;
	SAllocHeader* 	m_next;
	u32		  		m_info;	// Bit 24..31 : Info
							// Bit  0..23 : Size, 16 MB Max

	static const int SHIFT_INFO = 24;
	static const int MASK_INFO	= 0x0F000000;
	static const int SIZE_INFO	= 0x00FFFFFF;
	static const int FREED		= 0x80000000;
	static const int MSMARK		= 0x40000000;
	static const int DESTROYED	= 0x20000000;
	static const int SURVIVED	= 0x10000000;

	inline void setSize(u32 size) {
		m_info = (m_info & MASK_INFO) | size;
	}

	inline u32 getSize() {
		return m_info & SIZE_INFO;
	}

	inline void incGCCount() {
		m_info += (SIZE_INFO + 1);
	}

	inline u32 getGCCount() {
		return m_info & MASK_INFO >> SHIFT_INFO;
	}

	inline bool getFreed() {
		return (m_info & FREED) != 0;
	}

	inline void setFreed() {
		m_info |= FREED;
	}

	inline void unsetFreed() {
		m_info &= ~FREED;
	}

	inline bool getDestroyed() {
		return (m_info & DESTROYED) != 0;
	}

	inline void setDestroyed() {
		m_info |= DESTROYED;
	}

	inline bool getSurvived() {
		return (m_info & SURVIVED) != 0;
	}

	inline void setSurvived() {
		m_info |= SURVIVED; 
	}

	inline void unsetSurvived() {
		m_info &= ~SURVIVED; 
	}

	inline void setMark() {
		m_info |= MSMARK;
	}

	inline bool getMark() {
		return (m_info & MSMARK) != 0;
	}

	inline void unsetMark() {
		m_info &= ~MSMARK;
	}
};

template <class T>
class _CS_ArrayAllocator {
protected:
	struct ArrayItem {
	public:
		ArrayItem() {}
		~ArrayItem() {}

		T 	entry;
		u16	next;
		u16 prev;
	};
	static const u16 NULL_INDEX = 0xFFFF;
public:
	_CS_ArrayAllocator()
	:m_array		(NULL)
	,m_arrayCount	(0)
	,m_freeList		(NULL_INDEX)
	,m_usedList		(NULL_INDEX)
	{
	}

	~_CS_ArrayAllocator()
	{
		release();
	}
	
	bool init(u16 entryCount) {
		m_array = (ArrayItem*)CS_MALLOC(entryCount*sizeof(ArrayItem));
		if (m_array) {
			m_arrayCount = entryCount;
			m_allocated	 = 0;

			for (int n=0; n < entryCount; n++) {
				m_array[n].next = n+1;
				m_array[n].prev = n-1;
			}
		
			m_array[0].prev				= NULL_INDEX;
			m_array[entryCount-1].next	= NULL_INDEX;
			m_freeList					= 0;
			m_usedList					= NULL_INDEX;
			return true;
		}
		return false;
	}

	void release() {
		CS_FREE(m_array);
		m_array = NULL;
	}
	
	T* allocEntry() {
		if (m_freeList == NULL_INDEX) {
			CS_AssertAlways("Allocator Full");
			return NULL;
		} else {
			m_allocated++;

			u16 newItem = m_freeList;
		
			// Remove from free list.
			m_freeList	= m_array[newItem].next;
			if (m_freeList != NULL_INDEX) {	m_array[m_freeList].prev = NULL_INDEX;	}
		
			// Add to used list.
			m_array[newItem].next = m_usedList;
			m_array[newItem].prev = NULL_INDEX;
			if (m_usedList != NULL_INDEX) {	m_array[m_usedList].prev = newItem;		}
			m_usedList = newItem;

			// Clean entry before returning it.
			memset(&m_array[newItem].entry, 0, sizeof(T));

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
		if (pItem->prev != NULL_INDEX) {
			m_array[pItem->prev].next = pItem->next;
		} else {
			m_usedList = pItem->next;
		}
	
		if (pItem->next != NULL_INDEX) {
			m_array[pItem->next].prev = pItem->prev;
		}
	
		//
		// Add to free list
		//
		u16 idx = pItem - m_array;
		if (m_freeList != NULL_INDEX) {
			m_array[m_freeList].prev = idx;
		}
	
		pItem->next = m_freeList;
		pItem->prev = NULL_INDEX;

		// Position.
		m_freeList = idx;
	}
	
	ArrayItem*	m_array;
	u32			m_allocated;
	u32			m_arrayCount;
	u32			m_freeList;
	u32			m_usedList;
};

class Memory {
	friend class __GCObject;
public:
	static bool setGlobalMemory			(u32 size,u32 rootCount, u16 MultipleRefPageCount, u16 MarkAndSweepStackSize);
	static void release					();

	static void* allocate				(u32 size);
	//
	// Ref counter Collection System.
	//
	static void compactionSmall			(u32 infos);

	//
	// Mark & Sweep Collection System.
	//

	static const u32 COMPACT_GEN0	= 0x00000001;
	static const u32 COMPACT_GEN1	= 0x00000002;
	static const u32 COMPACT_NOW	= 0x00000010;

	static void compactionMS			(u32 infos = (COMPACT_GEN0 | COMPACT_NOW));
	static void registerGCRoot			(void* ptr);
	static bool pushList				(__GCObject* obj, u32 startIndex);
	static __GCObject* removeNext		();
	static void setLastProcessIndex		(u32 size);
	static u32	getLastProcessIndex		();
	static bool emptyList				();
	static u32	getProcessSizeMax		();

	static _CS_ArrayAllocator<RefList>*			g_allocPage;
protected:
	struct CompactionContext {
		SAllocHeader*	p;
		SAllocHeader*	lastValidGen0;
		SAllocHeader*	lastValidGen1;
		SAllocHeader*	firstFreeGen0;
		SAllocHeader*	firstFreeGen1;
		u32				moved;
		u32				removed;
		u32				genParsing;		// Which generation is being compacted
	};

	static void injectToDieList			(__GCObject* obj);
	static void rejectFromDieList		(__GCObject* obj);
	static void compactionInternal		(CompactionContext& ctx);
	static void removeObject			(__GCObject* obj);

private:
	static __GCObject*		g_destroyList;
	static u8*				s_bufferStart;
	static u8* 				s_bufferEnd;
	static u8*				s_bufferStartGen1;
	static u8* 				s_bufferAllocGen0;		// Pointer to start of next freely available block
	static SAllocHeader*	s_bufferAllocGen0Prev;	// Pointer to start of latest allocated block
	static SAllocHeader*	s_bufferAllocGen1Prev;	// Pointer to start of latest allocated block in Gen1
	static u8* 				s_bufferAllocGen1;		// Downward
	static SAllocHeader*	s_lastCompaction;
	static u32				s_initMagic;
	static __GCObject***	g_rootList;
	static u32				g_rootCount;
	static u32				ROOTCOUNT;
	static _CS_ArrayAllocator<SAllocMSEntry>*	g_allocMSEntry;

//	static SAllocHeader*	s_allocatedSmall;
//	static SAllocHeader*	s_allocatedSmallPrev;
//	static SAllocHeader*	s_allocatedBig;
//	static SAllocHeader*	s_freeList;

	#ifdef _DEBUG_MEMORY_
		static void			_debug_displayMemory(CompactionContext ctx);
	#endif

};


}

// Outside of name space.
u32  _refCallFinish_	(System::RefHolder* array_);
void _refRemove_		(u32 count, System::RefHolder* array_);

#endif // _CS_Memory_h_
