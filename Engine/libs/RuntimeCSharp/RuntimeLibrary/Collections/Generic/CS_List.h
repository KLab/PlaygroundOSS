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
#ifndef _CS_List_
#define _CS_List_

#include "../../CS_Object.h"
#include "../../CS_Array.h"
#include "../Collections.h"
#include "Generic.h"
#include "../../InternalUtils.h"

namespace System {
namespace Collections {
namespace Generic {
    
	///
	/// List<T>
	/// C# documentation : http://msdn.microsoft.com/en-us/library/6sh2ey19.aspx
	///
	///
    template<class T>
    class List : public Object {
        
    private:
        static const u32	_TYPEID = _TYPE_LIST;

        u32			m_count;
        u32			m_capacity;
        T*			m_list;
		__GCMalloc* m_listObject;
    public:
        virtual bool	_isInstanceOf	(u32 typeID);
		virtual	u32		_processGC		();
		virtual void	_releaseGC		();
		virtual void	_move			(__GCObject* prevobj, __GCObject* newobj);
		virtual void	_moveAlert		(u32 offset);
    public:
        // Constructors
        List<T>();
/*x*/   List<T>(System::Collections::Generic::IEnumerable<T>*);
        List<T>(s32 capacity);

		~List();

		void			_list_refSetValue		(s32 idx, T item);
		void			_list_removeValue		(s32 idx);
		inline void		_setMemCpy				(const void* buffer)	{ memcpy(m_list, buffer, m_count * m_sizeOfElement);	}
		inline List<T>* _s						(s32 idx, T item)		{ _list_refSetValue(idx, item); return this;			}
        
        // Properties
        inline s32      _acc_gCapacity			()					{ return (s32)m_capacity;				}
        inline s32      _acc_gCapacity$			()					{ CHCKTHIS; return _acc_gCapacity();	}
        inline s32      _acc_gCount				()					{ return (s32)m_count;					}
        inline s32      _acc_gCount$			()					{ CHCKTHIS; return _acc_gCount();		}
        inline	T&      _idx_g					(s32 idx)			{ return m_list[idx];					}
        inline	T&      _idx_g$					(s32 idx)			{ CHCKTHIS; return _idx_g(idx);			}
        inline	T&      _idx$_g					(s32 idx)			{ if (((u32)idx) >= m_count) { THROW(CS_NEW ArgumentOutOfRangeException()); } return m_list[idx]; }
		inline	T&      _idx$_g$				(s32 idx)			{ CHCKTHIS; return _idx$_g(idx);		}
		inline	T		_idx_s					(s32 idx, T item)	{ _list_refSetValue(idx, item);	return item;	}
		inline	T		_idx_s$					(s32 idx, T item)	{ CHCKTHIS; return _idx_s(idx, item);	}
		inline	T		_idx$_s					(s32 idx, T item)	{ if (((u32)idx) >= m_count) { THROW(CS_NEW ArgumentOutOfRangeException()); } _list_refSetValue(idx, item); return item; }
		inline	T	    _idx$_s$				(s32 idx, T item)	{ CHCKTHIS; return _idx$_s(idx, item);	}
		void            _acc_sCapacity			(s32 val);
		inline void     _acc_sCapacity$			(s32 val)			{ CHCKTHIS; _acc_sCapacity();			}

        // Methods
	    void            Add						(T item);
		inline void     Add$					(T item)																				{ CHCKTHIS; Add(item);							}
		inline List<T>*	AddRT					(T item)																				{ Add(item); return this;						}
/*x*/   void            AddRange				(System::Collections::Generic::IEnumerable<T>* collection);
/*x*/   //ReadOnlyCollection<T>* AsReadOnly		(); //System.Collections.ObjectModel.ReadOnlyCollection<T>
		s32             BinarySearch			(T item);
		inline s32      BinarySearch$			(T item)																				{ CHCKTHIS; return BinarySearch(item);			}
/*x*/   s32             BinarySearch			(T item, System::Collections::Generic::IComparer<T>* comparer);
/*x*/   s32             BinarySearch			(s32 idx, s32 count, T item, System::Collections::Generic::IComparer<T>* comparer);
		void            Clear					();
		inline void     Clear$					()																						{ CHCKTHIS; Clear();							}
		bool            Contains				(T item);
		inline bool     Contains$				(T item)																				{ CHCKTHIS; return Contains(item);				}
        
/*x*/   /*List<TOutput>*  ConvertAll<TOutput>   (Converter<T, TOutput>* converter);*/
        
		void            CopyTo					(Array<T>* _array);
		inline void     CopyTo$					(Array<T>* _array)																		{ CHCKTHIS; CopyTo(_array);						}
		void            CopyTo					(Array<T>* _array, s32 arrayIndex);
		inline void     CopyTo$					(Array<T>* _array, s32 arrayIndex)														{ CHCKTHIS; CopyTo(_array, arrayIndex);			}
		void            CopyTo					(s32 index, Array<T>* _array, s32 arrayIndex, s32 count);
		inline void     CopyTo$					(s32 index, Array<T>* _array, s32 arrayIndex, s32 count)								{ CHCKTHIS; CopyTo(index, _array, arrayIndex, count);	}
/*x*/   /*bool          Exists					(Predicate<T>* match);
/*x*/   //T             Find					(Predicate<T>* match);
/*x*/   //List<T>*      FindAll					(Predicate<T>* match);
/*x*/   //int           FindIndex				(Predicate<T>* match);
/*x*/   //int           FindIndex				(s32 startIndex, Predicate<T>* match);
/*x*/   //int           FindIndex				(s32 startIndex, s32 count, Predicate<T>* match);
/*x*/   //T             FindLast				(Predicate<T>* match);
/*x*/   //int           FindLastIndex			(Predicate<T>* match);
/*x*/   //int           FindLastIndex			(int startIndex, Predicate<T>* match);
/*x*/   //int           FindLastIndex			(int startIndex, s32 count, Predicate<T>* match);
/*x*/   //void          ForEach					(Action<T>* action);*/
		IEnumerator<T>* GetEnumerator           ();
		inline IEnumerator<T>* GetEnumerator$   ()                                                                                      { CHCKTHIS; return GetEnumerator();			        }
		List<T>*        GetRange				(s32 index, s32 count);
		inline List<T>* GetRange$				(s32 index, s32 count)																	{ CHCKTHIS; return GetRange(index, count);			}
		int             IndexOf					(T item);
		inline int      IndexOf$				(T item)																				{ CHCKTHIS; return IndexOf(item);					}
		int             IndexOf					(T item, s32 index);
		inline int      IndexOf$				(T item, s32 index)																		{ CHCKTHIS; return IndexOf(item, index);			}
		int             IndexOf					(T item, s32 index, s32 count);
		inline int      IndexOf$				(T item, s32 index, s32 count)															{ CHCKTHIS; return IndexOf(item, index, count);		}
		void            Insert					(s32 index, T item);
		inline void     Insert$					(s32 index, T item)																		{ CHCKTHIS; Insert(index, item);					}
/*x*/   void            InsertRange				(s32 index, System::Collections::Generic::IEnumerable<T>* collection);
		int             LastIndexOf				(T item);
		inline int      LastIndexOf$			(T item)																				{ CHCKTHIS; return LastIndexOf(item);				}
		int             LastIndexOf				(T item, s32 index);
		inline int      LastIndexOf$			(T item, s32 index)																		{ CHCKTHIS; return LastIndexOf(item, index);		}
		int             LastIndexOf				(T item, s32 index, s32 count);
		inline int      LastIndexOf$			(T item, s32 index, s32 count)															{ CHCKTHIS; return LastIndexOf(item, index, count);	}
		bool            Remove					(T item);
		inline bool     Remove$					(T item)																				{ CHCKTHIS; return Remove(item);					}
/*x*/   //int           RemoveAll				(Predicate<T> match);
		void            RemoveAt				(s32 index);
		inline void     RemoveAt$				(s32 index)																				{ CHCKTHIS; RemoveAt(index);						}
		void            RemoveRange				(s32 index, s32 count);
		inline void     RemoveRange$			(s32 index, s32 count)																	{ CHCKTHIS; RemoveRange(index, count);				}
		void            Reverse					();
		inline void     Reverse$				()																						{ CHCKTHIS; Reverse();								}
		void            Reverse					(s32 index, s32 count);
		inline void     Reverse$				(s32 index, s32 count)																	{ CHCKTHIS; Reverse(index, count);					}
		void            Sort					();
		inline void     Sort$					()																						{ CHCKTHIS; Sort();									}
/*x*/   //void          Sort			        (Comparison<T> comparison);
/*x*/   void            Sort		            (System::Collections::Generic::IComparer<T>* comparer);
/*x*/   void            Sort				    (s32 index, s32 count, System::Collections::Generic::IComparer<T>* comparer);
		Array<T>*       ToArray				    ();
		inline Array<T>*ToArray$				()																						{ CHCKTHIS; return ToArray();						}
		void            TrimExcess		        ();
		inline void     TrimExcess$		        ()																						{ CHCKTHIS; TrimExcess();							}
/*x*/   //bool          TrueForAll				(Predicate<T> match);
        
	private:
		void			_valueType_Sort			();
		s32				_valueType_BinarySearch	(T item);

		class Enumerator : public IEnumerator<T> {
		private:
			T* m_list;
			u32 m_count;
			u32 m_nextIndex;
			static const u32 c_uninitialized = 0xFFFFFFFF;
		public:
			Enumerator(List<T>* list);
			T _acc_gCurrent();
			bool MoveNext();
			void Dispose();
		};
    };


	// -----------------------------------------------------------------------
	// refSetValue.

	template <class T>
	inline void List<T>::_list_refSetValue(s32 idx, T item) { 
		if((__InternalUtilsGetTypeID<T>::getIt() & ET_STRUCT) == ET_STRUCT) {
			((__GCStruct*)(m_list + idx))->_RefSetValue(&item);
		} else {
			__GCObject::_RefSetValue((__GCObject**)(m_list + idx), (__GCObject*)item);
		}
	}

	template <> inline void List<u64>::_list_refSetValue	(s32 idx, u64 item)		{ m_list[idx] = item; }
	template <> inline void List<s64>::_list_refSetValue	(s32 idx, s64 item)		{ m_list[idx] = item; }
	template <> inline void List<u32>::_list_refSetValue	(s32 idx, u32 item)		{ m_list[idx] = item; }
	template <> inline void List<s32>::_list_refSetValue	(s32 idx, s32 item)		{ m_list[idx] = item; }
	template <> inline void List<u16>::_list_refSetValue	(s32 idx, u16 item)		{ m_list[idx] = item; }
	template <> inline void List<s16>::_list_refSetValue	(s32 idx, s16 item)		{ m_list[idx] = item; }
	template <> inline void List<u8>::_list_refSetValue		(s32 idx, u8  item)		{ m_list[idx] = item; }
	template <> inline void List<s8>::_list_refSetValue		(s32 idx, s8  item)		{ m_list[idx] = item; }
	template <> inline void List<bool>::_list_refSetValue	(s32 idx, bool item)	{ m_list[idx] = item; }
	template <> inline void List<double>::_list_refSetValue	(s32 idx, double item)	{ m_list[idx] = item; }
	template <> inline void List<float>::_list_refSetValue	(s32 idx, float item)	{ m_list[idx] = item; }

	template <class T>
	inline void List<T>::_list_removeValue(s32 idx) { 
		if((__InternalUtilsGetTypeID<T>::getIt() & ET_STRUCT) == ET_STRUCT) {
			((__GCStruct*)(m_list + idx))->_RefSetValue((T*)__InternalUtils::m_nullStruct);
		} else {
			__GCObject::_RefSetValue((__GCObject**)(m_list + idx), (__GCObject*)NULL);
		}
	}

	template <> inline void List<u64>::_list_removeValue	(s32 idx)	{ m_list[idx] = 0; }
	template <> inline void List<s64>::_list_removeValue	(s32 idx)	{ m_list[idx] = 0; }
	template <> inline void List<u32>::_list_removeValue	(s32 idx)	{ m_list[idx] = 0; }
	template <> inline void List<s32>::_list_removeValue	(s32 idx)	{ m_list[idx] = 0; }
	template <> inline void List<u16>::_list_removeValue	(s32 idx)	{ m_list[idx] = 0; }
	template <> inline void List<s16>::_list_removeValue	(s32 idx)	{ m_list[idx] = 0; }
	template <> inline void List<u8>::_list_removeValue		(s32 idx)	{ m_list[idx] = 0; }
	template <> inline void List<s8>::_list_removeValue		(s32 idx)	{ m_list[idx] = 0; }
	template <> inline void List<bool>::_list_removeValue	(s32 idx)	{ m_list[idx] = 0; }
	template <> inline void List<double>::_list_removeValue	(s32 idx)	{ m_list[idx] = 0; }
	template <> inline void List<float>::_list_removeValue	(s32 idx)	{ m_list[idx] = 0; }

	// -----------------------------------------------------------------------
	// Virtual methods.

	/*virtual*/
	template<class T>
	u32 List<T>::_processGC() {

		u32 lastProcessIndex	= Memory::getLastProcessIndex();
		u32 countMax			= Memory::getProcessSizeMax();

		if((__InternalUtilsGetTypeID<T>::getIt() & ET_STRUCT) == ET_STRUCT) {
			for(u32 i = 0; i < m_count; ++i) {
				// There will always be a struct in i event if it is a 0 filled one.
				if(countMax > 0) {
					if(((__GCStruct*)(&m_list[i]))->_processGC() == INCOMPLETE) {
						Memory::setLastProcessIndex(i);
						return INCOMPLETE;
					}
				}
				countMax = Memory::getProcessSizeMax();
			}
		} else {
			for(u32 i = lastProcessIndex; i < m_count; ++i) {
				if(m_list[i]) {
					if(!countMax--) {
						Memory::setLastProcessIndex(i);
						return INCOMPLETE;
					}
					Memory::pushList(m_list[i],0);
				}
			}
		}

		// There are at least 32 places left.
		if(m_listObject) { 
			Memory::pushList(m_listObject, 0);
		}
		return COMPLETE;
	}
	template<> inline u32 List<s32>::_processGC		()	{ if(m_listObject) { Memory::pushList(m_listObject, 0); } return COMPLETE; }
	template<> inline u32 List<u32>::_processGC		()	{ if(m_listObject) { Memory::pushList(m_listObject, 0); } return COMPLETE; }
	template<> inline u32 List<s16>::_processGC		()	{ if(m_listObject) { Memory::pushList(m_listObject, 0); } return COMPLETE; }
	template<> inline u32 List<u16>::_processGC		()	{ if(m_listObject) { Memory::pushList(m_listObject, 0); } return COMPLETE; }
	template<> inline u32 List<s8 >::_processGC		()	{ if(m_listObject) { Memory::pushList(m_listObject, 0); } return COMPLETE; }
	template<> inline u32 List<u8 >::_processGC		()	{ if(m_listObject) { Memory::pushList(m_listObject, 0); } return COMPLETE; }
	template<> inline u32 List<s64>::_processGC		()	{ if(m_listObject) { Memory::pushList(m_listObject, 0); } return COMPLETE; }
	template<> inline u32 List<u64>::_processGC		()	{ if(m_listObject) { Memory::pushList(m_listObject, 0); } return COMPLETE; }
	template<> inline u32 List<float>::_processGC	()	{ if(m_listObject) { Memory::pushList(m_listObject, 0); } return COMPLETE; }
	template<> inline u32 List<double>::_processGC	()	{ if(m_listObject) { Memory::pushList(m_listObject, 0); } return COMPLETE; }
	template<> inline u32 List<bool>::_processGC	()	{ if(m_listObject) { Memory::pushList(m_listObject, 0); } return COMPLETE; }
	template<> inline u32 List<s32*>::_processGC	()	{ if(m_listObject) { Memory::pushList(m_listObject, 0); } return COMPLETE; }

	/*virtual*/
	template<class T>
	bool List<T>::_isInstanceOf(u32 typeID) {
		_INSTANCEOF(List,Object);
	};

	/*virtual*/
	template<class T>
	void List<T>::_move(__GCObject* prevobj, __GCObject* newobj) {
		if((__GCObject*)m_listObject == prevobj) {
			m_listObject = (__GCMalloc*)newobj;
			m_list = (T*)m_listObject->getBlock();

			if((__InternalUtilsGetTypeID<T>::getIt() & ET_BASETYPE) != ET_BASETYPE) {
				void* old = ((__GCMalloc*)prevobj)->getBlock();
				if((__InternalUtilsGetTypeID<T>::getIt() & ET_CLASS) == ET_CLASS) {
					for(u32 i = 0; i < m_count; ++i) {
						__GCObject** obj = (__GCObject**)(m_list + i);
						if(*obj) {
							(*obj)->_moveRef((__GCObject**)((T*)old + i), obj);
						}
					}
				} else if((__InternalUtilsGetTypeID<T>::getIt() & ET_STRUCT) == ET_STRUCT) {
					for(u32 i = 0; i < m_count; ++i) {
						__GCStruct* str = (__GCStruct*)(m_list + i);
						if(str) {
							str->_moveAlert((u8*)str - (u8*)((T*)old + i));
						}
					}
				}
			}
		}
	}

	/*virtual*/
	template<class T>
	void List<T>::_releaseGC() {
		if(m_listObject) {
			if((__InternalUtilsGetTypeID<T>::getIt() & ET_BASETYPE) != ET_BASETYPE) {
				if((__InternalUtilsGetTypeID<T>::getIt() & ET_STRUCT) == ET_STRUCT) {
					for(u32 i = 0; i < m_count; ++i) {
						((__GCStruct*)(m_list + i))->_releaseGC();
					}
				} else {
					for(u32 i = 0; i < m_count; ++i) {
						__GCObject* obj = *(__GCObject**)(m_list + i);
						if(obj && !obj->isFreed()) {
							obj->_releaseGC();
							obj->_removeRef((__GCObject**)(m_list + i));
						}
					}
				}
			}
			if(!m_listObject->isFreed()) { m_listObject->_removeOwner(this); }
		}
	}
	template<> inline void List<s32>::_releaseGC	()	{ if(m_listObject && !m_listObject->isFreed()) { m_listObject->_removeOwner(this); } }
	template<> inline void List<u32>::_releaseGC	()	{ if(m_listObject && !m_listObject->isFreed()) { m_listObject->_removeOwner(this); } }
	template<> inline void List<s16>::_releaseGC	()	{ if(m_listObject && !m_listObject->isFreed()) { m_listObject->_removeOwner(this); } }
	template<> inline void List<u16>::_releaseGC	()	{ if(m_listObject && !m_listObject->isFreed()) { m_listObject->_removeOwner(this); } }
	template<> inline void List<s8 >::_releaseGC	()	{ if(m_listObject && !m_listObject->isFreed()) { m_listObject->_removeOwner(this); } }
	template<> inline void List<u8 >::_releaseGC	()	{ if(m_listObject && !m_listObject->isFreed()) { m_listObject->_removeOwner(this); } }
	template<> inline void List<s64>::_releaseGC	()	{ if(m_listObject && !m_listObject->isFreed()) { m_listObject->_removeOwner(this); } }
	template<> inline void List<u64>::_releaseGC	()	{ if(m_listObject && !m_listObject->isFreed()) { m_listObject->_removeOwner(this); } }
	template<> inline void List<float>::_releaseGC	()	{ if(m_listObject && !m_listObject->isFreed()) { m_listObject->_removeOwner(this); } }
	template<> inline void List<double>::_releaseGC	()	{ if(m_listObject && !m_listObject->isFreed()) { m_listObject->_removeOwner(this); } }
	template<> inline void List<bool>::_releaseGC	()	{ if(m_listObject && !m_listObject->isFreed()) { m_listObject->_removeOwner(this); } }


	/*virtual*/
	template<class T>
	void List<T>::_moveAlert(u32 offset) {
		Object::_moveAlert(offset);
		if(m_listObject) { m_listObject->_moveOwnerAsRef((__GCObject**)((u8*)this - offset) , (__GCObject**)this); }
	}

	// -----------------------------------------------------------------------
	
	// -----------------------------------------------------------------------
	// Constructors - Destructors

	template<class T>
	List<T>::List()
	: m_count		(0)
	, m_capacity	(0)
	, m_list		(NULL)
	, m_listObject	(NULL)
	{
	}

	template<class T>
	List<T>::List(System::Collections::Generic::IEnumerable<T>*) {
		// TODO
	}

	template<class T>
	List<T>::List(s32 capacity)
	: m_count		(0)
	, m_capacity	(capacity)
	, m_list		(NULL)
	, m_listObject	(NULL)
	{
		if(capacity > 0) {
			m_list = (T*)__GCMalloc::allocBlock(sizeof(T) * capacity, m_listObject);
			m_listObject->_addOwner(this);
		}
	}

	template<class T>
	List<T>::~List() {
		_releaseGC();
	}

	// -----------------------------------------------------------------------

	// -----------------------------------------------------------------------

	template<class T>
	void List<T>::_acc_sCapacity(s32 val) {
		if(val < (s32)m_count) THROW(CS_NEW ArgumentOutOfRangeException());

		if(m_capacity == 0) {
			if(m_listObject) {
				m_listObject->_removeOwner(this);
			}
			m_list = (T*)__GCMalloc::allocBlock(sizeof(T) * val, m_listObject);
			m_listObject->_addOwner(this);
		} else {
			void* old = m_list;

			m_listObject->_removeOwner(this);
			m_list = (T*)__GCMalloc::allocBlock(sizeof(T) * val, m_listObject);
			m_listObject->_addOwner(this);

			u32 length = ((u32)val > m_count) ? m_count : (u32)val;

			memcpy(m_list, old, length * sizeof(T));

			if((__InternalUtilsGetTypeID<T>::getIt() & ET_CLASS) == ET_CLASS) {
				u32 i = 0;
				for(; i < length; ++i) {
					__GCObject** obj = (__GCObject**)(m_list + i);
					if(*obj) {
						(*obj)->_moveRef((__GCObject**)((T*)old + i), obj);
					}
				}
				for(; i < m_count; ++i) {
					__GCObject::_RefSetValue((__GCObject**)((T*)old + i), NULL);
				}
			} else if((__InternalUtilsGetTypeID<T>::getIt() & ET_STRUCT) == ET_STRUCT) {
				u32 i = 0;
				for(; i < length; ++i) {
					__GCStruct* str = (__GCStruct*)(m_list + i);
					if(str) {
						str->_moveAlert((u8*)str - (u8*)((T*)old + i));
					}
				}
				for(; i < m_count; ++i) {
					((__GCStruct*)((T*)old + i))->_RefSetValue((T*)__InternalUtils::m_nullStruct);
				}
			}
		}
		m_capacity = val;
	}

	template<class T>
	void  List<T>::Add (T item) {
		if(m_capacity == 0) {
			_acc_sCapacity(4);
		}
		if(m_count == m_capacity) {
			_acc_sCapacity(m_capacity * 2);
		}

		_list_refSetValue(m_count++, item);
	}

	template<class T>
/*x*/   void            AddRange            (System::Collections::Generic::IEnumerable<T>* collection);

/*x*/   //ReadOnlyCollection<T>* AsReadOnly    (); //System.Collections.ObjectModel.ReadOnlyCollection<T>

	template<class T>
	inline s32 List<T>::BinarySearch(T item) {
		s32 startIdx	= 0;
		s32 endIdx		= m_count - 1;

		TRY
			if(item->CompareTo(m_list[endIdx]) == 1) {
				return ~(endIdx + 1);
			}

			while(startIdx <= endIdx) {
				s32 currentIdx = (startIdx + endIdx) / 2;
				s32 compRes = item->CompareTo(m_list[currentIdx]);
				if(compRes == 0) {
					return currentIdx;
				} else if(compRes == 1) {
					startIdx = currentIdx + 1;
				} else /*if(compRes == -1)*/ {
					endIdx = currentIdx - 1;
				}
			}
		CTRY
		FIRSTCATCH(CppNotComparable, ex)
			THROW(CS_NEW InvalidOperationException());
		FINALLY
		ETRY
		return ~startIdx;
	}

	template<class T>
	s32 List<T>::_valueType_BinarySearch(T value) {
		s32 startIdx	= 0;
		s32 endIdx		= m_count - 1;

		
		if(value > m_list[endIdx]) {
			return ~(endIdx + 1);
		}

		while(startIdx <= endIdx) {
			s32 currentIdx = (startIdx + endIdx) / 2;
			if(m_list[currentIdx] == value) {
				return currentIdx;
			} else if(value > m_list[currentIdx]) {
				startIdx = currentIdx + 1;
			} else /*if(value < m_list[currentIdx])*/ {
				endIdx = currentIdx - 1;
			}
		}
		return ~startIdx;
	}
	template<> inline s32 List<s64>::BinarySearch	(s64	item)	{ return _valueType_BinarySearch(item);	}
	template<> inline s32 List<u64>::BinarySearch	(u64	item)	{ return _valueType_BinarySearch(item);	}
	template<> inline s32 List<s32>::BinarySearch	(s32	item)	{ return _valueType_BinarySearch(item);	}
	template<> inline s32 List<u32>::BinarySearch	(u32	item)	{ return _valueType_BinarySearch(item);	}
	template<> inline s32 List<s16>::BinarySearch	(s16	item)	{ return _valueType_BinarySearch(item);	}
	template<> inline s32 List<u16>::BinarySearch	(u16	item)	{ return _valueType_BinarySearch(item);	}
	template<> inline s32 List<s8>::BinarySearch	(s8		item)	{ return _valueType_BinarySearch(item);	}
	template<> inline s32 List<u8>::BinarySearch	(u8		item)	{ return _valueType_BinarySearch(item);	}
	template<> inline s32 List<float>::BinarySearch	(float	item)	{ return _valueType_BinarySearch(item);	}
	template<> inline s32 List<double>::BinarySearch(double item)	{ return _valueType_BinarySearch(item);	}
	template<> inline s32 List<bool>::BinarySearch	(bool	item)	{ return _valueType_BinarySearch(item);	}
	
	template<class T>
/*x*/   s32             BinarySearch        (T item, System::Collections::Generic::IComparer<T>* comparer);
	template<class T>
/*x*/   s32             BinarySearch        (s32 idx, s32 count, T item, System::Collections::Generic::IComparer<T>* comparer);

	template<class T>
	void List<T>::Clear () {
		m_count = 0;
	}

	template<class T>
	inline bool List<T>::Contains (T item) {
		for(u32 i = 0; i < m_count; ++i) {
			if(__InternalUtils::_areEqual(m_list[i],item)) {
				return true;
			}
		}
		return false;
	}

/*x*/   /*List<TOutput>*  ConvertAll<TOutput>   (Converter<T, TOutput>* converter);*/

    template<class T>    
	void List<T>::CopyTo (Array<T>* _array) {
		if(!_array)							{ THROW(CS_NEW ArgumentNullException());	}
		if((u32)_array->_acc_gLength() < m_count)	{ THROW(CS_NEW ArgumentException());		}

		for(u32 i = 0; i < m_count; ++i) {
			_array->_array_refSetValue(i, m_list[i]);
		}
	}

	template<class T>
	void List<T>::CopyTo(Array<T>* _array, s32 arrayIndex) {
		if(!_array)										{ THROW(CS_NEW ArgumentNullException());		}
		if(arrayIndex < 0)								{ THROW(CS_NEW ArgumentOutOfRangeException());	}
		if((u32)_array->_acc_gLength() < m_count + arrayIndex)	{ THROW(CS_NEW ArgumentException());			}

		for(u32 i = 0; i < m_count; ++i) {
			_array->_array_refSetValue(arrayIndex + i, m_list[i]);
		}
	}

	template<class T>
	void List<T>::CopyTo(s32 index, Array<T>* _array, s32 arrayIndex, s32 count) {
		if(!_array)										{ THROW(CS_NEW ArgumentNullException());		}
		if((index | arrayIndex | count) < 0)			{ THROW(CS_NEW ArgumentOutOfRangeException());	}
		if(((u32)index >= m_count) || ((u32)(index + count) > m_count) || (_array->_acc_gLength() < count + arrayIndex))	{ THROW(CS_NEW ArgumentException());	}

		for(u32 i = 0; i < (u32)count; ++i) {
			_array->_array_refSetValue(arrayIndex + i, m_list[index + i]);
		}
	}

/*x*/   /*bool            Exists              (Predicate<T>* match);
/*x*/   //T               Find                (Predicate<T>* match);
/*x*/   //List<T>*        FindAll             (Predicate<T>* match);
/*x*/   //int             FindIndex           (Predicate<T>* match);
/*x*/   //int             FindIndex           (s32 startIndex, Predicate<T>* match);
/*x*/   //int             FindIndex           (s32 startIndex, s32 count, Predicate<T>* match);
/*x*/   //T               FindLast            (Predicate<T>* match);
/*x*/   //int             FindLastIndex       (Predicate<T>* match);
/*x*/   //int             FindLastIndex       (s32 startIndex, Predicate<T>* match);
/*x*/   //int             FindLastIndex       (s32 startIndex, s32 count, Predicate<T>* match);
/*x*/   //void            ForEach             (Action<T>* action);*/

	template<class T>
	IEnumerator<T>* List<T>::GetEnumerator() {
		return CS_NEW Enumerator(this);			
	}

	template<class T>
	List<T>* List<T>::GetRange (s32 index, s32 count) {
		if((index | count) < 0)				{ THROW(CS_NEW ArgumentOutOfRangeException());	}
		if((u32)(index + count) > m_count)	{ THROW(CS_NEW ArgumentException());			}

		List<T>* res = CS_NEW List<T>(count);
		memcpy(res->m_list, m_list + index, count * sizeof(T));
		res->m_count = count;
		return res;
	}

	template<class T>
	int List<T>::IndexOf(T item) {
		for(u32 i = 0; i < m_count; ++i) {
			if(__InternalUtils::_areEqual(m_list[i], item)) {
				return i;
			}
		}
		return -1;
	}

	template<class T>
	int List<T>::IndexOf(T item, s32 index) {
		if((u32)index > m_count) { THROW(CS_NEW ArgumentOutOfRangeException()); }
		for(u32 i = index; i < m_count; ++i) {
			if(__InternalUtils::_areEqual(m_list[i], item)) {
				return i;
			}
		}
		return -1;
	}

	template<class T>
	int List<T>::IndexOf(T item, s32 index, s32 count) {
		if(((u32)index > m_count) || ((u32)index + (u32)count > m_count)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
		for(u32 i = (u32)index; i < (u32)(index + count); ++i) {
			if(__InternalUtils::_areEqual(m_list[i], item)) {
				return i;
			}
		}
		return -1;
	}

	template<class T>
	void List<T>::Insert(s32 index, T item) {
		if((u32)index > m_count) { THROW(CS_NEW ArgumentOutOfRangeException()); }
		if(m_count == m_capacity) {
			_acc_sCapacity(m_capacity * 2);
		}

		for(u32 i = m_count; i > (u32)index; --i) {
			_list_refSetValue(i, m_list[i-1]);
		}

		_list_refSetValue(index, item);
		m_count++;
	}

	template<class T>
/*x*/   void            InsertRange         (s32 index, System::Collections::Generic::IEnumerable<T>* collection);

	template<class T>
	int List<T>::LastIndexOf(T item) {
		for(s32 i = (s32)m_count - 1; i >= 0; --i) {
			if(__InternalUtils::_areEqual(m_list[i], item)) {
				return i;
			}
		}
		return -1;
	}

	template<class T>
	int List<T>::LastIndexOf(T item, s32 index) {
		if((u32)index > m_count) { THROW(CS_NEW ArgumentOutOfRangeException()); }

		for(s32 i = (s32)index; i >= 0; --i) {
			if(__InternalUtils::_areEqual(m_list[i], item)) {
				return i;
			}
		}
		return -1;
	}

	template<class T>
	int List<T>::LastIndexOf(T item, s32 index, s32 count) {
		if(((u32)index > m_count) || ((u32)index - (u32)count < 0)) { THROW(CS_NEW ArgumentOutOfRangeException()); }

		for(s32 i = index; i > index - count; --i) {
			if(__InternalUtils::_areEqual(m_list[i], item)) {
				return i;
			}
		}
		return -1;
	}

	template<class T>
	bool List<T>::Remove(T item) {
		for(u32 i = 0; i < m_count; ++i) {
			if(__InternalUtils::_areEqual(m_list[i], item)) {
				for(u32 j = i; j < m_count - 1; ++j) {
					_list_refSetValue(j, m_list[j+1]);
				}
				m_count--;
				return true;
			}
		}
		return false;
	}

/*x*/   /*int             RemoveAll           (Predicate<T> match);*/

	template<class T>
	void List<T>::RemoveAt (s32 index) {
		if((u32)index > m_count) { THROW(CS_NEW ArgumentOutOfRangeException()); }
		for(u32 i = index; i < m_count - 1; ++i) {
			_list_refSetValue(i, m_list[i+1]);
		}
		_list_removeValue(--m_count);
	}

	template<class T>
	void List<T>::RemoveRange(s32 index, s32 count) {
		if(index < 0 || count < 0)	{ THROW(CS_NEW ArgumentOutOfRangeException());	}
		if((u32)(index + count) > m_count) { THROW(CS_NEW ArgumentException());			}
		for(u32 i = index; i < m_count - index + count; ++i) {
			_list_refSetValue(i, m_list[count + i]);
		}
		m_count -= count;
	}

	template<class T>
	void List<T>::Reverse() {
		for(u32 i = 0; i < (m_count >> 1); ++i) {
			T tmp = m_list[i];
			_list_refSetValue(i, m_list[m_count - i - 1]);
			_list_refSetValue(m_count - i - 1, tmp);
		}
	}

	template<class T>
	void List<T>::Reverse(s32 index, s32 count) {
		if(index < 0 || count < 0)	{ THROW(CS_NEW ArgumentOutOfRangeException());	}
		if((u32)(index + count) > m_count) { THROW(CS_NEW ArgumentException());			}
		if(count < 2) return;

		for(int i = 0; i < (count >> 1); ++i) {
			T tmp = m_list[index + i];
			_list_refSetValue(index + i, m_list[index + count - i - 1]);
			_list_refSetValue(index + count - i - 1, tmp);
		}
	}

	template<class T>
	inline void List<T>::Sort () {
		// TODO ? quick sort if m_count > ?
		for(u32 i = 1; i < m_count; ++i) {
			u32 j = i;
			T tmp = m_list[i];

			TRY
				while(j > 0 && m_list[j - 1]->CompareTo(tmp) > 0) {
					_list_refSetValue(j, m_list[j-1]);
					--j;
				}
			CTRY
			FIRSTCATCH(CppNotComparable, ex)
				THROW(CS_NEW InvalidOperationException());
			FINALLY
			ETRY
			_list_refSetValue(j, tmp);
		}
	}

	template<class T>
	void List<T>::_valueType_Sort() {
		// TODO ? quick sort if m_count > ?
		for(u32 i = 1; i < m_count; ++i) {
			u32 j = i;
			T tmp = m_list[i];
			while(j > 0 && m_list[j - 1] > tmp) {
				m_list[j] = m_list[j-1];
				--j;
			}
			m_list[j] = tmp;
		}
	}
	template<> inline void List<s64>::Sort()	{ _valueType_Sort(); }
	template<> inline void List<u64>::Sort()	{ _valueType_Sort(); }
	template<> inline void List<s32>::Sort()	{ _valueType_Sort(); }
	template<> inline void List<u32>::Sort()	{ _valueType_Sort(); }
	template<> inline void List<s16>::Sort()	{ _valueType_Sort(); }
	template<> inline void List<u16>::Sort()	{ _valueType_Sort(); }
	template<> inline void List<s8>::Sort()		{ _valueType_Sort(); }
	template<> inline void List<u8>::Sort()		{ _valueType_Sort(); }
	template<> inline void List<float>::Sort()	{ _valueType_Sort(); }
	template<> inline void List<double>::Sort() { _valueType_Sort(); }
	template<> inline void List<bool>::Sort()	{ _valueType_Sort(); }

/*x*/   /*void Sort                (Comparison<T> comparison);*/
	template<class T>
/*x*/   void Sort(System::Collections::Generic::IComparer<T>* comparer);
	template<class T>
/*x*/   void Sort(s32 index, s32 count, System::Collections::Generic::IComparer<T>* comparer);
	
	template<class T>
	Array<T>* List<T>::ToArray() {
		Array<T>* ret = CS_NEW Array<T>(m_count);
		for(u32 i = 0; i < m_count; ++i) {
			ret->_array_refSetValue(i, m_list[i]);
		}
		return ret;
	}

	template<class T>
	void List<T>::TrimExcess() {
		// TrimExcess method does nothing if the list is at more than 90 percent of capacity. 
		// This avoids incurring a large reallocation cost for a relatively small gain.
		if(m_count < ((m_capacity * 921)>>10)) {
			_acc_sCapacity(m_count);
		}
	}
/*x*/   /*bool            TrueForAll          (Predicate<T> match);*/

	// -----------------------------------------------------------------------
	
	// -----------------------------------------------------------------------
	// Enumerator
	template<class T>
	List<T>::Enumerator::Enumerator(List<T>* list) {
		m_nextIndex = c_uninitialized;
		m_list = list->m_list;
		m_count = list->m_count;
	}

	template<class T>
	T List<T>::Enumerator::_acc_gCurrent() {
		if(m_nextIndex == c_uninitialized || m_nextIndex > m_count) {
			THROW(CS_NEW InvalidOperationException());
		}
		return m_list[m_nextIndex];
	}

	template<class T>
	bool List<T>::Enumerator::MoveNext() {
		return ((++m_nextIndex) < m_count);
	}

	template<class T>
	void List<T>::Enumerator::Dispose() {
		// nop
	}	
}
}
}

#endif /* defined(_CS_List_) */
