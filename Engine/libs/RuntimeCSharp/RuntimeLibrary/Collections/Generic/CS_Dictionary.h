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
#ifndef _CS_Dictionary_
#define _CS_Dictionary_

#include "../../CS_Object.h"
#include "../../CS_String.h"
#include "../../InternalUtils.h"

namespace System {
namespace Collections {
namespace Generic {

	// Prime numbers from 2 to 1M with a minimal increase of 1% between 2 prime numbers.
	// Array of 772 elements.
	extern const u32 _dictionary_primeArray[];
	
	template<class TKey, class TValue>
	class KeyValuePair : public Object {
	private:
		TKey m_key;
		TValue m_value;
	public:
		KeyValuePair(TKey key, TValue value);
		TKey			_acc_gKey();
		inline TKey     _acc_gKey$()    { CHCKTHIS; return _acc_gKey();   }
		TValue          _acc_gValue();
		inline TValue   _acc_gValue$()  { CHCKTHIS; return _acc_gValue(); }
	};

	///
	/// Dictionary<TKey,TValue>
	/// Implementation based on :
	///		http://msdn.microsoft.com/en-us/library/xfhwa508.aspx
	///		http://www.simple-talk.com/blogs/2011/09/16/the-net-dictionary/
	///	
	template<class TKey, class TValue>
	class Dictionary : public Object {
		friend class Object;

	public:
		struct Entry {
			Entry*	m_pNext;
			TKey	m_key;
			TValue	m_value;
			s32		m_hashCode;
			bool	m_isFilled;

			Entry();
			Entry(TKey key, TValue value, s32 hashCode, Entry* next);
			~Entry();
			void set(TKey key, TValue value, s32 hashCode, Entry* next);
		};

	private:
		static const u32	_TYPEID = _TYPE_DICTIONARY;
	public:
		virtual bool	_isInstanceOf	(u32 typeID);
		virtual	u32		_processGC		();
		virtual void	_releaseGC		();
		virtual void	_move			(__GCObject* prevobj, __GCObject* newobj);
		virtual void	_moveAlert		(u32 offset);
	private:
		// members
		s32*		m_buckets;
		Entry*		m_entries;
		Entry*		m_freeList;
		__GCMalloc*	m_bucketsObject;
		__GCMalloc* m_entriesObject;
		u32			m_count;
		u32			m_capacity;
		u32			m_countRemoved;

	public:
		Dictionary<TKey, TValue>(s32 capacity = 17);
		~Dictionary();

		// Properties
/*x*/	//IEqualityComparer<TKey>		_g$Comparer				();
		inline s32						_acc_gCount				()									{ return m_count;						}
		inline s32						_acc_gCount$			()									{ CHCKTHIS; return _acc_gCount();		}
		TValue&							_idx_g					(TKey key);
		inline TValue&					_idx_g$					(TKey key)							{ CHCKTHIS; return _idx_g(key);			}
		TValue							_idx_s					(TKey key, TValue value);
		inline TValue					_idx_s$					(TKey key, TValue value)			{ CHCKTHIS; return _idx_s(key, value);	}
/*x*/	//Dictionary<T>.KeyCollection	_g$Keys					();
/*x*/	//Dictionary<T>.ValueCollection	_g$Values				();

		// Methods
		void							Add						(TKey key, TValue value);
		inline void						Add$					(TKey key, TValue value)			{ CHCKTHIS; Add(key, value);				}
		void							Clear					();
		inline void						Clear$					()									{ CHCKTHIS; Clear();						}
		bool							ContainsKey				(TKey key);
		inline bool						ContainsKey$			(TKey key)							{ CHCKTHIS;  return ContainsKey(key);		}
		bool							ContainsValue			(TValue value);
		inline bool						ContainsValue$			(TValue value)						{ CHCKTHIS; return ContainsValue(value);	}
		IEnumerator<KeyValuePair<TKey,TValue>*>*
										GetEnumerator			();
		inline IEnumerator<KeyValuePair<TKey,TValue>*>*
										GetEnumerator$			()									{ CHCKTHIS; return GetEnumerator();			}
/*x*/	//int							GetHashCode				();
		bool							Remove					(TKey key);
		inline bool						Remove$					(TKey key)							{ CHCKTHIS; return Remove(key);				}
		bool							_ref_TryGetValue		(TKey key, /*out*/ TValue& value);
		bool							TryGetValue				(TKey key, /*out*/ TValue& value);
		inline bool						TryGetValue$			(TKey key, /*out*/ TValue& value)	{ CHCKTHIS; return TryGetValue(key, value);	}

	// Internal methods.
	private:
/*x*/	void							_resize					(u32 newSize = -1);
		void							_addToFreeList			(s32 idx);
		Entry*							_popFreeList			();
		Entry*							_popFreeListAndFill		(TKey* key, TValue* value, s32 hashCode, Entry* pNext);

	public: 
		void							_display				();

	private:
		class Enumerator : public IEnumerator<KeyValuePair<TKey,TValue>*> {
		private:
			u32 m_capacity;
			u32 m_currentBucket;
			s32* m_buckets;
			Entry* m_entries;
			Entry* m_currentEntry;
			static const u32 c_uninitialized = 0xFFFFFFFF;
		public:
			Enumerator(Dictionary<TKey,TValue>* dict);
			KeyValuePair<TKey,TValue>* _acc_gCurrent();
			bool MoveNext();
			void Dispose();
		};
	};

	// ------------------------------------------------------
	// KeyValuePair<TKey, TValue> methods
	
	template<class TKey, class TValue>
	KeyValuePair<TKey,TValue>::KeyValuePair(TKey key, TValue value) {
		m_key = key;
		m_value = value;
	}

	template<class TKey, class TValue>
	TKey KeyValuePair<TKey,TValue>::_acc_gKey() {
		return m_key;
	}
	
	template<class TKey, class TValue>
	TValue KeyValuePair<TKey,TValue>::_acc_gValue() {
		return m_value;
	}

	// ------------------------------------------------------
	// Virtual methods
	
	template<class TKey, class TValue>
	bool Dictionary<TKey,TValue>::_isInstanceOf(u32 typeID) {
		_INSTANCEOF(Dictionary,Object);
	}

	template<class TKey, class TValue>
	u32 Dictionary<TKey,TValue>::_processGC() {
		u32 keyType = __InternalUtilsGetTypeID<TKey>::getIt();

		// If lastProcessIndex is >= 0 that means the Keys the previous iteration didn't occure 
		// OR it was stopped during the Key procession.
		// If it is < 0 that means it was during the Value procession.
		// The next index to process will be ~lastProcessIndex
		s32 lastProcessIndex = (s32)Memory::getLastProcessIndex();
		u32 countMax = Memory::getProcessSizeMax();

		if(lastProcessIndex >= 0) {
			if((keyType & ET_BASETYPE) != ET_BASETYPE) {
				if((keyType & ET_STRUCT) == ET_STRUCT) {
					for(u32 i = lastProcessIndex; i < m_count + m_countRemoved; ++i) {
						if(m_entries[i].m_isFilled) {
							if(!countMax) {
								if(((__GCStruct*)(&m_entries[i].m_key))->_processGC() == INCOMPLETE) {
									// If the struct _processGC is not completed, the last struct processed will be processed again
									// during the next processGC of the Dictionary.
									Memory::setLastProcessIndex(i);
									return INCOMPLETE;
								}
							}
							// Impossible to know how many elements have been added in the list during the _processGC method of the struct with the current implementation
							// So we must update countMax recalling getProcessSizeMax
							countMax = Memory::getProcessSizeMax();
						}
					}
				} else {
					for(u32 i = Memory::getLastProcessIndex(); i < m_count + m_countRemoved; ++i) {
						if(m_entries[i].m_isFilled) {
							if(!(countMax--)) {
								Memory::setLastProcessIndex(i);
								return INCOMPLETE;
							}
							Memory::pushList(m_entries[i].m_key, 0);
						}
					}
				}
			}
		}

		u32 valType = __InternalUtilsGetTypeID<TValue>::getIt();

		if(lastProcessIndex < 0) {
			lastProcessIndex = ~lastProcessIndex;
		}

		if((valType & ET_BASETYPE) != ET_BASETYPE) {
			if((valType & ET_STRUCT) == ET_STRUCT) {
				for(u32 i = lastProcessIndex; i < m_count + m_countRemoved; ++i) {
					if(m_entries[i].m_isFilled) {
						if(!countMax) {
							if(((__GCStruct*)(&m_entries[i].m_value))->_processGC() == INCOMPLETE) {
								Memory::setLastProcessIndex(~i);
								return INCOMPLETE;
							}
						}
						countMax = Memory::getProcessSizeMax();
					}
				}
			} else {
				for(u32 i = Memory::getLastProcessIndex(); i < m_count + m_countRemoved; ++i) {
					if(m_entries[i].m_isFilled) {
						if(!(countMax--)) {
							Memory::setLastProcessIndex(~i);
							return INCOMPLETE;
						}
						Memory::pushList(m_entries[i].m_value, 0);
					}
				}
			}
		}
		
		// There are at least 32 places left.
		if(m_bucketsObject) { Memory::pushList(m_bucketsObject, 0); }
		if(m_entriesObject) { Memory::pushList(m_entriesObject, 0); }
		return COMPLETE;
	}

	/*virtual*/
	template<class TKey, class TValue>
	void Dictionary<TKey,TValue>::_move(__GCObject* prevobj, __GCObject* newobj) {
		if((__GCObject*)m_bucketsObject == prevobj) {
			m_bucketsObject = (__GCMalloc*)newobj;
			m_buckets = (s32*)m_bucketsObject->getBlock();
		} else if((__GCObject*)m_entriesObject == prevobj) {
			m_entriesObject = (__GCMalloc*)newobj;
			m_entries = (Entry*)m_entriesObject->getBlock();

			if((__InternalUtilsGetTypeID<TKey>::getIt() & ET_BASETYPE) != ET_BASETYPE) {
				void* old = ((__GCMalloc*)prevobj)->getBlock();
				if((__InternalUtilsGetTypeID<TKey>::getIt() & ET_CLASS) == ET_CLASS) {
					for(u32 i = 0; i < m_capacity; ++i) {
						if(m_entries[i].m_isFilled) {
							__GCObject** newObj = (__GCObject**)(&m_entries[i].m_key);
							__GCObject** oldObj = (__GCObject**)(&((Entry*)old)[i].m_key);
							if(newObj) {
								(*newObj)->_moveRef(oldObj, newObj);
							}
						}
					}
				} else if((__InternalUtilsGetTypeID<TKey>::getIt() & ET_STRUCT) == ET_STRUCT) {
					for(u32 i = 0; i < m_capacity; ++i) {
						if(m_entries[i].m_isFilled) {
							__GCStruct* str		= (__GCStruct*)(&m_entries[i].m_key);
							__GCStruct* oldStr	= (__GCStruct*)(&((Entry*)old)[i].m_key);
							if(str) {
								str->_moveAlert((u8*)str - (u8*)oldStr);
							}
						}
					}
				}
			}

			if((__InternalUtilsGetTypeID<TValue>::getIt() & ET_BASETYPE) != ET_BASETYPE) {
				void* old = ((__GCMalloc*)prevobj)->getBlock();
				if((__InternalUtilsGetTypeID<TValue>::getIt() & ET_CLASS) == ET_CLASS) {
					for(u32 i = 0; i < m_capacity; ++i) {
						if(m_entries[i].m_isFilled) {
							__GCObject** newObj = (__GCObject**)(&m_entries[i].m_value);
							__GCObject** oldObj = (__GCObject**)(&((Entry*)old)[i].m_value);
							if(newObj) {
								(*newObj)->_moveRef(oldObj, newObj);
							}
						}
					}
				} else if((__InternalUtilsGetTypeID<TValue>::getIt() & ET_STRUCT) == ET_STRUCT) {
					for(u32 i = 0; i < m_capacity; ++i) {
						if(m_entries[i].m_isFilled) {
							__GCStruct* str		= (__GCStruct*)(&m_entries[i].m_value);
							__GCStruct* oldStr	= (__GCStruct*)(&((Entry*)old)[i].m_value);
							if(str) {
								str->_moveAlert((u8*)str - (u8*)oldStr);
							}
						}
					}
				}
			}
		}
	}

	/*virtual*/
	template<class TKey, class TValue>
	void Dictionary<TKey,TValue>::_releaseGC() {
		if(m_entriesObject) {
			if((__InternalUtilsGetTypeID<TKey>::getIt() & ET_BASETYPE) != ET_BASETYPE) {
				if((__InternalUtilsGetTypeID<TKey>::getIt() & ET_STRUCT) == ET_STRUCT) {
					for(u32 i = 0; i < m_capacity; ++i) {
						((__GCStruct*)(&m_entries[i].m_key))->_releaseGC();
					}
				} else {
					for(u32 i = 0; i < m_capacity; ++i) {
						__GCObject* obj = m_entries[i].m_key;
						if(obj && !obj->isFreed()) {
							obj->_releaseGC();
							obj->_removeRef((__GCObject**)&(m_entries[i].m_key));
						}
					}
				}
			}
		
			if((__InternalUtilsGetTypeID<TValue>::getIt() & ET_BASETYPE) != ET_BASETYPE) {
				if((__InternalUtilsGetTypeID<TValue>::getIt() & ET_STRUCT) == ET_STRUCT) {
					for(u32 i = 0; i < m_capacity; ++i) {
						((__GCStruct*)(&m_entries[i].m_value))->_releaseGC();
					}
				} else {
					for(u32 i = 0; i < m_capacity; ++i) {
						__GCObject* obj = m_entries[i].m_value;
						if(obj && !obj->isFreed()) {
							obj->_releaseGC();
							obj->_removeRef((__GCObject**)&(m_entries[i].m_value));
						}
					}
				}
			}
			if(!m_entriesObject->isFreed()) { m_entriesObject->_removeOwner(this); }
		}
	}

	/*virtual*/
	template<class TKey, class TValue>
	void Dictionary<TKey,TValue>::_moveAlert(u32 offset) {
		Object::_moveAlert(offset);
		if(m_bucketsObject) { m_bucketsObject->_moveOwnerAsRef((__GCObject**)((u8*)this - offset) , (__GCObject**)this); }
		if(m_entriesObject) { m_entriesObject->_moveOwnerAsRef((__GCObject**)((u8*)this - offset) , (__GCObject**)this); }
	}

	// ------------------------------------------------------
	
	// ------------------------------------------------------
	// Constructor - Destructor

	template<class TKey, class TValue>
	Dictionary<TKey,TValue>::Dictionary(s32 capacity) 
	: m_buckets			(NULL)
	, m_entries			(NULL)
	, m_freeList		(NULL)
	, m_bucketsObject	(NULL)
	, m_entriesObject	(NULL)
	, m_count			(0)
	, m_capacity		(capacity)
	, m_countRemoved	(0)
	{
		m_buckets	= (s32*)	__GCMalloc::allocBlock(sizeof(s32)   * capacity, m_bucketsObject);
		m_entries	= (Entry*)	__GCMalloc::allocBlock(sizeof(Entry) * capacity, m_entriesObject);
		m_bucketsObject->_addOwner(this);
		m_entriesObject->_addOwner(this);

		memset32(m_buckets, 0xFFFFFFFF, capacity * sizeof(s32));
		for(s32 i = 0; i < capacity - 1; ++i) {
			m_entries[i].m_pNext = &m_entries[i+1];
		}
		m_entries[capacity - 1].m_pNext = NULL;
		m_freeList = m_entries;
	}

	template<class TKey, class TValue>
	Dictionary<TKey,TValue>::~Dictionary() {
		_releaseGC();
	}

	// ------------------------------------------------------

	// ------------------------------------------------------
	// Internal Methods

	//
	// Cannot be implemented inside the template class because of partial template specialization
	// This is impossible to specialize a single method into a generic class.
	// We should have specialized the whole class.
	//
	template<class T>
	inline void _dico_RefSetValue(T* itemPtr, T* newValPtr) { 
		if((__InternalUtilsGetTypeID<T>::getIt() & ET_STRUCT) == ET_STRUCT) {
			if(newValPtr) {
				((__GCStruct*)(itemPtr))->_RefSetValue(newValPtr);
			} else {
				((__GCStruct*)(itemPtr))->_RefSetValue((T*)__InternalUtils::m_nullStruct);
			}
		} else {
			if(newValPtr) {
				__GCObject::_RefSetValue((__GCObject**)(itemPtr), *(__GCObject**)newValPtr);
			} else {
				__GCObject::_RefSetValue((__GCObject**)(itemPtr), NULL);
			}
		}
	}
	template<>	inline void _dico_RefSetValue(u64*		itemPtr, u64*	newVal)	{ *itemPtr = *newVal; }
	template<>	inline void _dico_RefSetValue(s64*		itemPtr, s64*	newVal)	{ *itemPtr = *newVal; }
	template<>	inline void _dico_RefSetValue(u32*		itemPtr, u32*	newVal)	{ *itemPtr = *newVal; }
	template<>	inline void _dico_RefSetValue(s32*		itemPtr, s32*	newVal)	{ *itemPtr = *newVal; }
	template<>	inline void _dico_RefSetValue(u16*		itemPtr, u16*	newVal)	{ *itemPtr = *newVal; }
	template<>	inline void _dico_RefSetValue(s16*		itemPtr, s16*	newVal)	{ *itemPtr = *newVal; }
	template<>	inline void _dico_RefSetValue(u8*		itemPtr, u8*	newVal)	{ *itemPtr = *newVal; }
	template<>	inline void _dico_RefSetValue(s8*		itemPtr, s8*	newVal)	{ *itemPtr = *newVal; }
	template<>	inline void _dico_RefSetValue(bool*		itemPtr, bool*	newVal)	{ *itemPtr = *newVal; }
	template<>	inline void _dico_RefSetValue(float*	itemPtr, float*	newVal)	{ *itemPtr = *newVal; }
	template<>	inline void _dico_RefSetValue(double*	itemPtr, double*newVal)	{ *itemPtr = *newVal; }

	template<class T>
	inline void _dico_RefResetValue(T* oldPtr, T* newPtr, T* itemPtr) { 
		if((__InternalUtilsGetTypeID<T>::getIt() & ET_STRUCT) == ET_STRUCT) {
			if(newPtr) {
				*newPtr = *itemPtr;
				((__GCStruct*)itemPtr)->_moveAlert((u8*)newPtr - (u8*)oldPtr);
			} else {
				((__GCStruct*)(itemPtr))->_RefSetValue((T*)__InternalUtils::m_nullStruct);
			}
		} else {
			if(newPtr) {
				*newPtr = *itemPtr;
				(*(__GCObject**)itemPtr)->_moveRef((__GCObject**)oldPtr, (__GCObject**)newPtr);
			} else {
				__GCObject::_RefSetValue((__GCObject**)(itemPtr), NULL);
			}
		}
	}
	template<>	inline void _dico_RefResetValue(u64*	/*oldPtr*/,	u64*	newPtr,	u64*	itemPtr) { *itemPtr = *newPtr; }
	template<>	inline void _dico_RefResetValue(s64*	/*oldPtr*/,	s64*	newPtr,	s64*	itemPtr) { *itemPtr = *newPtr; }
	template<>	inline void _dico_RefResetValue(u32*	/*oldPtr*/,	u32*	newPtr,	u32*	itemPtr) { *itemPtr = *newPtr; }
	template<>	inline void _dico_RefResetValue(s32*	/*oldPtr*/,	s32*	newPtr,	s32*	itemPtr) { *itemPtr = *newPtr; }
	template<>	inline void _dico_RefResetValue(u16*	/*oldPtr*/,	u16*	newPtr,	u16*	itemPtr) { *itemPtr = *newPtr; }
	template<>	inline void _dico_RefResetValue(s16*	/*oldPtr*/,	s16*	newPtr,	s16*	itemPtr) { *itemPtr = *newPtr; }
	template<>	inline void _dico_RefResetValue(u8 *	/*oldPtr*/,	u8 *	newPtr,	u8*		itemPtr) { *itemPtr = *newPtr; }
	template<>	inline void _dico_RefResetValue(s8 *	/*oldPtr*/,	s8 *	newPtr,	s8*		itemPtr) { *itemPtr = *newPtr; }
	template<>	inline void _dico_RefResetValue(bool*	/*oldPtr*/,	bool*	newPtr,	bool*	itemPtr) { *itemPtr = *newPtr; }
	template<>	inline void _dico_RefResetValue(float*	/*oldPtr*/,	float*	newPtr,	float*	itemPtr) { *itemPtr = *newPtr; }
	template<>	inline void _dico_RefResetValue(double*	/*oldPtr*/,	double*	newPtr,	double*	itemPtr) { *itemPtr = *newPtr; }


	template<class TKey, class TValue>
	Dictionary<TKey,TValue>::Entry::Entry()
	: m_pNext	(NULL)
	, m_isFilled(false)
	{
	}

	template<class TKey, class TValue>
	Dictionary<TKey,TValue>::Entry::Entry(TKey key, TValue value, s32 hashCode, Entry* next)
	: m_hashCode(hashCode)
	, m_pNext	(next)
	, m_isFilled(true)
	{
		_dico_RefSetValue(&m_key, &key);
		_dico_RefSetValue(&m_value, &value);
	}

	template<class TKey, class TValue>
	void Dictionary<TKey,TValue>::Entry::set(TKey key, TValue value, s32 hashCode, Entry* next) {
		template <class T>
		_dico_RefSetValue(&m_key, &key);
		_dico_RefSetValue(&m_value, &value);
		m_hashCode	= hashCode;
		m_pNext		= next;
		m_isFilled	= true;
	}

	template<class TKey, class TValue>
	Dictionary<TKey,TValue>::Entry::~Entry() 
	{
		_dico_RefSetValue(&m_key, (T*)NULL);
		_dico_RefSetValue(&m_value, (T*)NULL);
	}

	template<class TKey, class TValue>
	void Dictionary<TKey,TValue>::_addToFreeList(s32 idx) {
		m_entries[idx].m_pNext	= m_freeList;
		m_freeList				= &m_entries[idx];
		_dico_RefSetValue(&(m_entries[idx].m_key),   (TKey*)NULL);
		_dico_RefSetValue(&(m_entries[idx].m_value), (TValue*)NULL);
		m_count--;
	}

	template<class TKey, class TValue>
	typename Dictionary<TKey,TValue>::Entry* Dictionary<TKey,TValue>::_popFreeList() {
		if(m_freeList) {
			if(m_countRemoved > 0) {
				m_countRemoved--;
			}
			Entry* ret		= m_freeList;
			m_freeList		= m_freeList->m_pNext;
			ret->m_pNext	= NULL;
			return ret;
		} else {
			return NULL;
		}
	}

	template<class TKey, class TValue>
	typename Dictionary<TKey,TValue>::Entry* Dictionary<TKey,TValue>::_popFreeListAndFill(TKey* key, TValue* value, s32 hashCode, Entry* pNext) {
		if(m_freeList) {
			if(m_countRemoved > 0) {
				m_countRemoved--;
			}

			Entry* ret = m_freeList;
			m_freeList = m_freeList->m_pNext;

			_dico_RefSetValue(&ret->m_key, key);
			_dico_RefSetValue(&ret->m_value, value);
			ret->m_hashCode	= hashCode;
			ret->m_pNext	= pNext;
			ret->m_isFilled = false;

			return ret;
		} else {
			return NULL;
		}
	}

	template<class TKey, class TValue>
	void Dictionary<TKey,TValue>::_resize(u32 newSize) {
		s32 idx = __InternalUtils::_binarySearch((u32*)_dictionary_primeArray, 0, 772, (newSize == -1) ? (m_capacity << 1) : newSize);
		
		// TODO : ok for this exception?
		if(idx == -1)	{ THROW(CS_NEW OutOfMemoryException()); }

		m_count = 0;
		u32 newCapacity = (idx == 0) ? _dictionary_primeArray[0] : _dictionary_primeArray[~idx];
		
		m_bucketsObject->_removeOwner(this);
		m_entriesObject->_removeOwner(this);
		s32*   newBuckets	= (s32*)	__GCMalloc::allocBlock(sizeof(s32)   * newCapacity, m_bucketsObject);
		Entry* newEntries	= (Entry*)	__GCMalloc::allocBlock(sizeof(Entry) * newCapacity, m_entriesObject);
		m_bucketsObject->_addOwner(this);
		m_entriesObject->_addOwner(this);
		memset32(newBuckets, 0xFFFFFFFF, newCapacity * sizeof(s32));

		for(u32 i = 0; i < m_capacity; ++i) {
			if(m_buckets[i] != -1) {
				Entry* pEntry = &m_entries[m_buckets[i]];
				while(pEntry) {
					u32 newIdx			= pEntry->m_hashCode % newCapacity;
					Entry* pNewEntry	= &newEntries[m_count++];
					if(newBuckets[newIdx] != -1) {
						pNewEntry->m_pNext = &newEntries[newBuckets[newIdx]];
					}
					_dico_RefResetValue(&pEntry->m_key,		&pNewEntry->m_key,		&pEntry->m_key);
					_dico_RefResetValue(&pEntry->m_value,	&pNewEntry->m_value,	&pEntry->m_value);
					pNewEntry->m_hashCode	= pEntry->m_hashCode;
					pNewEntry->m_isFilled	= pEntry->m_isFilled;
					newBuckets[newIdx]		= pNewEntry - newEntries;

					pEntry = pEntry->m_pNext;
				}
			}
		}

		m_buckets	= newBuckets;
		m_entries	= newEntries;
		m_capacity	= newCapacity;
		m_freeList  = &newEntries[m_count];
		for(u32 i = m_count; i < m_capacity - 1; ++i) {
			newEntries[i].m_pNext = &newEntries[i+1];
		}
		newEntries[m_capacity].m_pNext = NULL;
	}

	template<class TKey, class TValue>
	inline void Dictionary<TKey,TValue>::_display() {
		
	}

	template<>
	inline void Dictionary<System::String*,System::String*>::_display() {
		for(u32 i = 0; i < m_capacity; ++i) {
			Entry* pEntry	= &m_entries[i];
			if(pEntry && pEntry->m_key && pEntry->m_value) {
				printf("Key = %s Value = %s\n", pEntry->m_key->PadRight(15)->_toCStr(), pEntry->m_value->_toCStr());
			}
		}
	}

	// ------------------------------------------------------

	// ------------------------------------------------------
	// Properties

	template<class TKey, class TValue>
	TValue& Dictionary<TKey,TValue>::_idx_g(TKey key) {
		if(__InternalUtils::_isNullPtr(key)) { THROW(CS_NEW ArgumentNullException()); }

		u32 idx			= m_buckets[__InternalUtils::_getHashCode(key) % m_capacity];
		Entry* pEntry	= NULL;
		if(idx != -1) {
			pEntry = &m_entries[idx];

			while(pEntry && !__InternalUtils::_areEqual(pEntry->m_key, key)) {
				pEntry = pEntry->m_pNext;
			}
		}

		if(!pEntry) { THROW(CS_NEW KeyNotFoundException()); }

		return pEntry->m_value;
	}

	template<class TKey, class TValue>
	TValue Dictionary<TKey,TValue>::_idx_s(TKey key, TValue value) {
		if(__InternalUtils::_isNullPtr(key)) { THROW(CS_NEW ArgumentNullException()); }

		u32 hashCode	= __InternalUtils::_getHashCode(key);
		u32 idx			= hashCode % m_capacity;
		Entry* pEntry	= &m_entries[m_buckets[idx]];

		// if a bucket is empty, it will contain -1
		if(m_buckets[idx] != -1) {
			while((pEntry->m_pNext) && !__InternalUtils::_areEqual(pEntry->m_key, key)) {
				pEntry = pEntry->m_pNext;
			}
			if(!__InternalUtils::_areEqual(pEntry->m_key, key)) {
				pEntry = _popFreeListAndFill(&key, NULL, hashCode, &m_entries[m_buckets[idx]]);
				m_count++;
			}
		} else {
			pEntry = _popFreeListAndFill(&key, NULL, hashCode, NULL);
			m_count++;
		}
		_dico_RefSetValue(&pEntry->m_value, &value);
		pEntry->m_isFilled	= true;
		m_buckets[idx]		= pEntry - m_entries;

		if(m_count == m_capacity) {
			_resize();
		}

		return value;
	}

	// ------------------------------------------------------

	// ------------------------------------------------------
	// Methods
	
	template<class TKey, class TValue>
	void Dictionary<TKey,TValue>::Add(TKey key, TValue value) {
		if(__InternalUtils::_isNullPtr(key)) { THROW(CS_NEW ArgumentNullException()); }

		u32 hashCode	= __InternalUtils::_getHashCode(key);
		u32 idx			= hashCode % m_capacity;
		Entry* pEntry	= NULL;
		if(m_buckets[idx] != -1) {
			pEntry = &m_entries[m_buckets[idx]];
			while((pEntry->m_pNext) && !__InternalUtils::_areEqual(pEntry->m_key, key)) {
				pEntry = pEntry->m_pNext;
			}
			if(__InternalUtils::_areEqual(pEntry->m_key, key)) { THROW(CS_NEW ArgumentException()); }
		}

		pEntry = _popFreeList();
		_dico_RefSetValue(&pEntry->m_key, &key);
		_dico_RefSetValue(&pEntry->m_value, &value);
		pEntry->m_hashCode	= hashCode;
		pEntry->m_isFilled	= true;
		// if a bucket is empty, it will contain -1
		if(m_buckets[idx] != -1) {
			pEntry->m_pNext = &m_entries[m_buckets[idx]];
		}
		
		m_buckets[idx] = pEntry - m_entries;
		m_count++;

		if(m_count == m_capacity) {
			_resize();
		}
	}
	
	template<class TKey, class TValue>
	void Dictionary<TKey, TValue>::Clear() {
		for(u32 i = 0; i < m_capacity - 1; ++i) {
			m_entries[i].m_pNext = &m_entries[i+1];
			_dico_RefSetValue(&m_entries[i].m_value, (TValue*)NULL);
		}
		m_entries[m_capacity - 1].m_pNext = NULL;
		m_freeList = m_entries;

		memset32(m_buckets, 0xFFFFFFFF, m_capacity * sizeof(s32));

		m_count		= 0;
	}
	
	template<class TKey, class TValue>
	bool Dictionary<TKey,TValue>::ContainsKey(TKey key) {
		if(__InternalUtils::_isNullPtr(key)) { THROW(CS_NEW ArgumentNullException()); }
		
		u32 idx			= m_buckets[__InternalUtils::_getHashCode(key) % m_capacity];
		Entry* pEntry	= NULL;
		if(idx != -1) {
			pEntry = &m_entries[idx];

			while(pEntry && !__InternalUtils::_areEqual(pEntry->m_key, key)) {
				pEntry = pEntry->m_pNext;
			}
		}

		return (pEntry != NULL);
	}
	
	template<class TKey, class TValue>
	bool Dictionary<TKey,TValue>::ContainsValue(TValue value) {
		for(u32 i = 0; i < (m_count + m_countRemoved); ++i) {
			Entry* pEntry	= &m_entries[i];
			if(pEntry->m_isFilled) {
				while((pEntry->m_pNext) && !__InternalUtils::_areEqual(pEntry->m_value, value)) {
					pEntry = pEntry->m_pNext;
				}
				if(__InternalUtils::_areEqual(pEntry->m_value, value)) {
					return true;
				}
			}
		}
		return false;
	}

	template<class TKey, class TValue>
	IEnumerator<KeyValuePair<TKey,TValue>*>* Dictionary<TKey,TValue>::GetEnumerator() {
		return CS_NEW Enumerator(this);
	}
	
	template<class TKey, class TValue>
	bool Dictionary<TKey,TValue>::Remove(TKey key) {
		if(__InternalUtils::_isNullPtr(key)) { THROW(CS_NEW ArgumentNullException()); }

		u32 hashCodeMod	= __InternalUtils::_getHashCode(key) % m_capacity;
		u32 idx			= m_buckets[hashCodeMod];
		Entry* pEntry	= NULL;
		
		if(idx != -1) {
			pEntry = &m_entries[idx];
			if(__InternalUtils::_areEqual(pEntry->m_key, key)) {
				if(pEntry->m_pNext) {
					m_buckets[hashCodeMod] = pEntry->m_pNext - m_entries;
				} else {
					m_buckets[hashCodeMod] = -1;
				}
				_addToFreeList(idx);
				m_countRemoved++;
				return true;
			}

			Entry* pPrev	= pEntry;
			pEntry			= pEntry->m_pNext;
			while(pEntry && !__InternalUtils::_areEqual(pEntry->m_key, key)) {
				pPrev	= pEntry;
				pEntry	= pEntry->m_pNext;
			}
			
			if(pEntry) {
				pPrev->m_pNext = pEntry->m_pNext;
				_addToFreeList(pEntry - m_entries);
				m_countRemoved++;
				return true;
			}
		}
		return false;
	}

	template<class TKey, class TValue>
	bool Dictionary<TKey,TValue>::_ref_TryGetValue(TKey key, /*out*/ TValue& value) {
		if(__InternalUtils::_isNullPtr(key)) { THROW(CS_NEW ArgumentNullException()); }
		
		u32 idx			= m_buckets[__InternalUtils::_getHashCode(key) % m_capacity];
		Entry* pEntry	= NULL;
		if(idx != -1) {
			pEntry = &m_entries[idx];

			while(pEntry && !__InternalUtils::_areEqual(pEntry->m_key, key)) {
				pEntry = pEntry->m_pNext;
			}
		}

		if(!pEntry) {
			value = (TValue)NULL;
			return false;
		}

		value = pEntry->m_value;
		return true;
	}
	
	template<class TKey, class TValue>
	bool Dictionary<TKey,TValue>::TryGetValue(TKey key, /*out*/ TValue& value) {
		System::RefHolder _cs_refholder_loc_array[1];
		u32 _cs_count_refholder = _refCallFinish_(_cs_refholder_loc_array);
		bool r = _ref_TryGetValue(key, value);
		_refRemove_(_cs_count_refholder,_cs_refholder_loc_array);
		return r;
	}
	
	// -----------------------------------------------------------------------
	// Enumerator
	template<class TKey, class TValue>
	Dictionary<TKey, TValue>::Enumerator::Enumerator(Dictionary<TKey, TValue>* dict) {
		m_capacity = dict->m_capacity;
		m_buckets = dict->m_buckets;
		m_entries = dict->m_entries;
		m_currentBucket = c_uninitialized;
		m_currentEntry = NULL;
	}

	template<class TKey, class TValue>
	KeyValuePair<TKey, TValue>* Dictionary<TKey, TValue>::Enumerator::_acc_gCurrent() {
		if(m_currentEntry == NULL) {
			THROW(CS_NEW InvalidOperationException());
		}

		return CS_NEW KeyValuePair<TKey,TValue>(m_currentEntry->m_key, m_currentEntry->m_value);
	}

	template<class TKey, class TValue>
	bool Dictionary<TKey, TValue>::Enumerator::MoveNext() {
		while(m_currentBucket < m_capacity || m_currentBucket == c_uninitialized) {
			if(!m_currentEntry || !(m_currentEntry->m_pNext)) {
				while(true){
					m_currentBucket++;

					if(m_currentBucket == m_capacity) {
						// Now ends
						m_currentEntry = NULL;
						return false;
					}

					if (m_buckets[m_currentBucket] >= 0) {
						Entry* entry = m_entries + m_buckets[m_currentBucket];
						if (entry) {
							// Found
							m_currentEntry = entry;
							return true;
						}
					}
				}
			}
			
			m_currentEntry = m_currentEntry->m_pNext;
			return true;
		}

		// Already ended (or empty).
		return false;
	}

	template<class TKey, class TValue>
	void Dictionary<TKey, TValue>::Enumerator::Dispose() {
		// nop
	}	
}
}
}

#endif
