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
#ifndef _CS_Array_h_
#define _CS_Array_h_

#include "CS_Object.h"
#include "Collections/Generic/Generic.h"
#include "InternalUtils.h"

namespace System {
	class String;
	template<class T>
	class Array;

	class AbstractArray : public Object {
	private:
		static const u32	_TYPEID = _TYPE_ABSTRACTARRAY;

		static const u8		OWN_LENGTHS_BUFFER		= 0x01;
		static const u8		OWN_LOWER_BOUNDS_BUFFER	= 0x02;
	public:
		virtual bool	_isInstanceOf	(u32 typeID);
		virtual	u32		_processGC		();
		virtual	void	_releaseGC		();
		virtual void	_move			(__GCObject* prevobj, __GCObject* newobj);
		virtual void	_moveAlert		(u32 offset);

	protected:
		void*		m_array;
		__GCMalloc* m_arrayObject;
	private:
		u32*		m_lowerBounds;
		u32*		m_lengths;
		u32			m_lowerBound;
		u32			m_rank;
		u64			m_length;
		u32			m_typeIDOfElement;
		u32			m_sizeOfElement;
		u8			m_infos;

	public:
		AbstractArray(u32 rank, u32 length, u32 typeID, size_t sizeOfElement);
		AbstractArray(u32 rank, u32* lengths, u32 typeID, size_t sizeOfElement, u32* lowerBounds);
		~AbstractArray();

		inline s32		_acc_gRank			()				{ return (s32)m_rank;						}
		inline s32		_acc_gRank$			()				{ CHCKTHIS; return _acc_gRank();			}
		inline s32		_acc_gLength		()				{ return (s32)m_length;						}
		inline s32		_acc_gLength$		()				{ CHCKTHIS; return _acc_gLength();			}
		inline s64		_acc_gLongLength	()				{ return (s64)m_length;						}
		inline s64		_acc_gLongLength$	()				{ CHCKTHIS; return _acc_gLongLength();		}
		inline s32		GetLength			()				{ return (s32)m_length;						}
		inline s32		GetLength$			()				{ CHCKTHIS; return GetLength();				}
		inline s64		GetLongLength		()				{ return (s64)m_length;						}
		inline s64		GetLongLength$		()				{ CHCKTHIS; return GetLongLength();			}
		inline s32		GetLowerBound		(s32 dimension) { return (s32)m_lowerBounds[dimension - 1]; }
		inline s32		GetLowerBound$		(s32 dimension) { CHCKTHIS; return GetLowerBound(dimension);}
		inline s32		GetUpperBound		(s32 dimension) { return (s32)(m_lowerBounds[dimension - 1] + m_lengths[dimension - 1] - 1);	}
		inline s32		GetUpperBound$		(s32 dimension) { CHCKTHIS; return GetUpperBound(dimension);}

	// Internal Methods
	public:
		inline	void*	_getPArray			()						{ return m_array;												}
		inline void		_setMemCpy			(const void* buffer)	{ memcpy(m_array, buffer, (size_t)(m_length * m_sizeOfElement));}
	protected:
		inline	void*	_getValuePtr		(s32 idx)		{ return ((u8*)m_array + (idx - m_lowerBounds[0]) * m_sizeOfElement);	}
		inline	u32		_getSizeOfElement	()				{ return m_sizeOfElement;		}
		inline	u32		_getTypeIDOfElement	()				{ return m_typeIDOfElement;		}
		inline	void	_setTypeIDOfElement	(u32 typeID)	{ m_typeIDOfElement = typeID;	}
		inline	u32*	_getLengths			()				{ return m_lengths;				}
		inline	u32*	_getLowerBounds		()				{ return m_lowerBounds;			}
		Object*			_getValue			(s32 index);
		inline void		_setLength			(u64 value)		{ m_length = value;				}

	public:
		static s32				BinarySearch			(AbstractArray* _array, Object* value);
		static s32				BinarySearch			(AbstractArray* _array, s64 value);
		static s32				BinarySearch			(AbstractArray* _array, u64 value);
		static s32				BinarySearch			(AbstractArray* _array, s32 value);
		static s32				BinarySearch			(AbstractArray* _array, u32 value);
		static s32				BinarySearch			(AbstractArray* _array, s16 value);
		static s32				BinarySearch			(AbstractArray* _array, u16 value);
		static s32				BinarySearch			(AbstractArray* _array, s8 value);
		static s32				BinarySearch			(AbstractArray* _array, u8 value);
		static s32				BinarySearch			(AbstractArray* _array, float value);
		static s32				BinarySearch			(AbstractArray* _array, double value);
		static s32				BinarySearch			(AbstractArray* _array, bool value);
/*x*/	//static s32			BinarySearch			(AbstractArray* _array, Object* value, IComparer* comparer);
		static s32				BinarySearch			(AbstractArray* _array, s32 index, s32 length, Object* value);
		static s32				BinarySearch			(AbstractArray* _array, s32 index, s32 length, s64 value);
		static s32				BinarySearch			(AbstractArray* _array, s32 index, s32 length, u64 value);
		static s32				BinarySearch			(AbstractArray* _array, s32 index, s32 length, s32 value);
		static s32				BinarySearch			(AbstractArray* _array, s32 index, s32 length, u32 value);
		static s32				BinarySearch			(AbstractArray* _array, s32 index, s32 length, s16 value);
		static s32				BinarySearch			(AbstractArray* _array, s32 index, s32 length, u16 value);
		static s32				BinarySearch			(AbstractArray* _array, s32 index, s32 length, s8 value);
		static s32				BinarySearch			(AbstractArray* _array, s32 index, s32 length, u8 value);
		static s32				BinarySearch			(AbstractArray* _array, s32 index, s32 length, float value);
		static s32				BinarySearch			(AbstractArray* _array, s32 index, s32 length, double value);
		static s32				BinarySearch			(AbstractArray* _array, s32 index, s32 length, bool value);
		static void				Clear					(AbstractArray* _array, s32 index, s32 length);
		virtual Object*			Clone					() = 0;
/*x*/	static void				ConstrainedCopy			(AbstractArray* sourceArray, s32 sourceIndex, AbstractArray* destinationArray, s32 destinationIndex, s32 length);
/*a*/	static void				Copy					(AbstractArray* sourceArray, AbstractArray* destinationArray, s32 length);
/*a*/	static void				Copy					(AbstractArray* sourceArray, AbstractArray* destinationArray, s64 length);
/*a*/	static void				Copy					(AbstractArray* sourceArray, s32 sourceIndex, AbstractArray* destinationArray, s32 destinationIndex, s32 length);
/*a*/	static void				Copy					(AbstractArray* sourceArray, s64 sourceIndex, AbstractArray* destinationArray, s64 destinationIndex, s64 length);
/*a*/	void					CopyTo					(AbstractArray* _array, s32 index);
/*a*/	void					CopyTo					(AbstractArray* _array, s64 index);
/*x*/	static AbstractArray*	CreateInstance			(Type elementType, s32 length);
/*x*/	static AbstractArray*	CreateInstance			(Type elementType, s32 lengths, ...);
/*x*/	static AbstractArray*	CreateInstance			(Type elementType, s64 lengths, ...);
/*x*/	static AbstractArray*	CreateInstance			(Type elementType, s32 length1, s32 length2);
/*x*/	static AbstractArray*	CreateInstance			(Type elementType, Array<s32>* lengths, Array<s32>* lowerBounds);
/*x*/	static AbstractArray*	CreateInstance			(Type elementType, s32 length1, s32 length2, s32 length3);
/*NO*/	//Object*				GetValue				(s64 index);
/*NO*/	//Object*				GetValue				(s32 index1, s32 index2);
/*NO*/	//Object*				GetValue				(s64 index1, s64 index2);
/*NO*/	//Object*				GetValue				(s32 index1, s32 index2, s32 index3);
/*NO*/	//Object*				GetValue				(s64 index1, s64 index2, s64 index3);
/*NO*/	//Object*				GetValue				(s32 index1, s32 index2, s32 index3, s32 additionalIndexes, ...);
/*NO*/	//Object*				GetValue				(s64 index1, s64 index2, s64 index3, s64 additionalIndexes, ...);
		static s32				IndexOf					(AbstractArray* _array, Object* value);
		static s32				IndexOf					(AbstractArray* _array, s64 value);
		static s32				IndexOf					(AbstractArray* _array, u64 value);
		static s32				IndexOf					(AbstractArray* _array, s32 value);
		static s32				IndexOf					(AbstractArray* _array, u32 value);
		static s32				IndexOf					(AbstractArray* _array, s16 value);
		static s32				IndexOf					(AbstractArray* _array, u16 value);
		static s32				IndexOf					(AbstractArray* _array, s8 value);
		static s32				IndexOf					(AbstractArray* _array, u8 value);
		static s32				IndexOf					(AbstractArray* _array, float value);
		static s32				IndexOf					(AbstractArray* _array, double value);
		static s32				IndexOf					(AbstractArray* _array, bool value);
		static s32				IndexOf					(AbstractArray* _array, Object* value, s32 startIndex);
		static s32				IndexOf					(AbstractArray* _array, s64 value, s32 startIndex);
		static s32				IndexOf					(AbstractArray* _array, u64 value, s32 startIndex);
		static s32				IndexOf					(AbstractArray* _array, s32 value, s32 startIndex);
		static s32				IndexOf					(AbstractArray* _array, u32 value, s32 startIndex);
		static s32				IndexOf					(AbstractArray* _array, s16 value, s32 startIndex);
		static s32				IndexOf					(AbstractArray* _array, u16 value, s32 startIndex);
		static s32				IndexOf					(AbstractArray* _array, s8 value, s32 startIndex);
		static s32				IndexOf					(AbstractArray* _array, u8 value, s32 startIndex);
		static s32				IndexOf					(AbstractArray* _array, float value, s32 startIndex);
		static s32				IndexOf					(AbstractArray* _array, double value, s32 startIndex);
		static s32				IndexOf					(AbstractArray* _array, bool value, s32 startIndex);
		static s32				IndexOf					(AbstractArray* _array, Object* value, s32 startIndex, s32 count);
		static s32				IndexOf					(AbstractArray* _array, s64 value, s32 startIndex, s32 count);
		static s32				IndexOf					(AbstractArray* _array, u64 value, s32 startIndex, s32 count);
		static s32				IndexOf					(AbstractArray* _array, s32 value, s32 startIndex, s32 count);
		static s32				IndexOf					(AbstractArray* _array, u32 value, s32 startIndex, s32 count);
		static s32				IndexOf					(AbstractArray* _array, s16 value, s32 startIndex, s32 count);
		static s32				IndexOf					(AbstractArray* _array, u16 value, s32 startIndex, s32 count);
		static s32				IndexOf					(AbstractArray* _array, s8 value, s32 startIndex, s32 count);
		static s32				IndexOf					(AbstractArray* _array, u8 value, s32 startIndex, s32 count);
		static s32				IndexOf					(AbstractArray* _array, float value, s32 startIndex, s32 count);
		static s32				IndexOf					(AbstractArray* _array, double value, s32 startIndex, s32 count);
		static s32				IndexOf					(AbstractArray* _array, bool value, s32 startIndex, s32 count);
/*x*/	void					Initialize				();
		static s32				LastIndexOf				(AbstractArray* _array, Object* value);
		static s32				LastIndexOf				(AbstractArray* _array, s64 value);
		static s32				LastIndexOf				(AbstractArray* _array, u64 value);
		static s32				LastIndexOf				(AbstractArray* _array, s32 value);
		static s32				LastIndexOf				(AbstractArray* _array, u32 value);
		static s32				LastIndexOf				(AbstractArray* _array, s16 value);
		static s32				LastIndexOf				(AbstractArray* _array, u16 value);
		static s32				LastIndexOf				(AbstractArray* _array, s8 value);
		static s32				LastIndexOf				(AbstractArray* _array, u8 value);
		static s32				LastIndexOf				(AbstractArray* _array, float value);
		static s32				LastIndexOf				(AbstractArray* _array, double value);
		static s32				LastIndexOf				(AbstractArray* _array, bool value);
		static s32				LastIndexOf				(AbstractArray* _array, Object* value, s32 startIndex);
		static s32				LastIndexOf				(AbstractArray* _array, s64 value, s32 startIndex);
		static s32				LastIndexOf				(AbstractArray* _array, u64 value, s32 startIndex);
		static s32				LastIndexOf				(AbstractArray* _array, s32 value, s32 startIndex);
		static s32				LastIndexOf				(AbstractArray* _array, u32 value, s32 startIndex);
		static s32				LastIndexOf				(AbstractArray* _array, s16 value, s32 startIndex);
		static s32				LastIndexOf				(AbstractArray* _array, u16 value, s32 startIndex);
		static s32				LastIndexOf				(AbstractArray* _array, s8 value, s32 startIndex);
		static s32				LastIndexOf				(AbstractArray* _array, u8 value, s32 startIndex);
		static s32				LastIndexOf				(AbstractArray* _array, float value, s32 startIndex);
		static s32				LastIndexOf				(AbstractArray* _array, double value, s32 startIndex);
		static s32				LastIndexOf				(AbstractArray* _array, bool value, s32 startIndex);
		static s32				LastIndexOf				(AbstractArray* _array, Object* value, s32 startIndex, s32 count);
		static s32				LastIndexOf				(AbstractArray* _array, s64 value, s32 startIndex, s32 count);
		static s32				LastIndexOf				(AbstractArray* _array, u64 value, s32 startIndex, s32 count);
		static s32				LastIndexOf				(AbstractArray* _array, s32 value, s32 startIndex, s32 count);
		static s32				LastIndexOf				(AbstractArray* _array, u32 value, s32 startIndex, s32 count);
		static s32				LastIndexOf				(AbstractArray* _array, s16 value, s32 startIndex, s32 count);
		static s32				LastIndexOf				(AbstractArray* _array, u16 value, s32 startIndex, s32 count);
		static s32				LastIndexOf				(AbstractArray* _array, s8 value, s32 startIndex, s32 count);
		static s32				LastIndexOf				(AbstractArray* _array, u8 value, s32 startIndex, s32 count);
		static s32				LastIndexOf				(AbstractArray* _array, float value, s32 startIndex, s32 count);
		static s32				LastIndexOf				(AbstractArray* _array, double value, s32 startIndex, s32 count);
		static s32				LastIndexOf				(AbstractArray* _array, bool value, s32 startIndex, s32 count);
		static void				Reverse					(AbstractArray* _array);
		static void				Reverse					(AbstractArray* _array, s32 index, s32 length);
/*NO*/	//void					SetValue				(Object* value, s32 index);
/*NO*/	//void					SetValue				(Object* value, s32 indices, ...);
/*NO*/	//void					SetValue				(Object* value, s64 index);
/*NO*/	//void					SetValue				(Object* value, s64 indices, ...);
/*NO*/	//void					SetValue				(Object* value, s32 index1, s32 index2);
/*NO*/	//void					SetValue				(Object* value, s64 index1, s64 index2);
/*NO*/	//void					SetValue				(Object* value, s32 index1, s32 index2, s32 index3);
/*NO*/	//void					SetValue				(Object value, s64 index1, s64 index2, s64 index3);
		static void				Sort					(AbstractArray* _array);
/*x*/	static void				Sort					(AbstractArray* keys, AbstractArray* items);
/*x*/	//static void			Sort					(AbstractArray* _array, IComparer* comparer);
/*x*/	//static void			Sort					(AbstractArray* keys, AbstractArray* items, IComparer* comparer);
		static void				Sort					(AbstractArray* _array, s32 index, s32 length);
/*x*/	static void				Sort					(AbstractArray* keys, AbstractArray* items, s32 index, s32 length);
/*x*/	//static void			Sort					(AbstractArray* _array, s32 index, s32 length, IComparer* comparer);
/*x*/	//static void			Sort					(AbstractArray* keys, AbstractArray* items, s32 index, s32 length, IComparer* comparer);

// template methods
/*x*/	//template<class T> static ReadOnlyCollection<T>* AsReadOnly		(Array<T>* _array);
		template<class T> static s32				BinarySearch			(Array<T>* _array, T value);
/*x*/	//template<class T> static s32				BinarySearch			(Array<T>* _array, T value, IComparer<T> comparer);
		template<class T> static s32				BinarySearch			(Array<T>* _array, s32 index, s32 length, T value);
/*x*/	//template<class T> static s32				BinarySearch			(Array<T>* _array, s32 index, s32 length, T value, IComparer<T>* comparer);
/*x*/	//template<class TInput, class TOutput> 
/*x*/	//					static Array<TOutput>*	ConvertAll				(Array<TInput>* array, Converter<TInput, TOutput>* converter);
/*x*/	//template<class T> static bool				Exists					(Array<T>* _array, Predicate<T>* match);
/*x*/	//template<class T> static T*				Find					(Array<T>* _array, Predicate<T>* match);
/*x*/	//template<class T> static Array<T>*		FindAll					(Array<T>* _array, Predicate<T>* match);
/*x*/	//template<class T> static s32				FindIndex				(Array<T>* _array, Predicate<T>* match);
/*x*/	//template<class T> static s32				FindIndex				(Array<T>* _array, s32 startIndex, Predicate<T>* match);
/*x*/	//template<class T> static s32				FindIndex				(Array<T>* _array, s32 startIndex, s32 count, Predicate<T>* match);
/*x*/	//template<class T> static T*				FindLast				(Array<T>* _array, Predicate<T>* match);
/*x*/	//template<class T> static s32				FindLastIndex			(Array<T>* _array, Predicate<T>* match);
/*x*/	//template<class T> static s32				FindLastIndex			(Array<T>* _array, s32 startIndex, Predicate<T>* match);
/*x*/	//template<class T> static int				FindLastIndex			(Array<T>* _array, s32 startIndex, s32 count, Predicate<T>* match);
/*x*/	//template<class T> static void				ForEach					(Array<T>* _array, Action<T> action);
		template<class T> static s32				IndexOf					(Array<T>* _array, T value);
		template<class T> static s32				IndexOf					(Array<T>* _array, T value, s32 startIndex);
		template<class T> static s32				IndexOf					(Array<T>* _array, T value, s32 startIndex, s32 count);
		template<class T> static s32				LastIndexOf				(Array<T>* _array, T value);
		template<class T> static s32				LastIndexOf				(Array<T>* _array, T value, s32 startIndex);
		template<class T> static s32				LastIndexOf				(Array<T>* _array, T value, s32 startIndex, s32 count);
		template<class T> static void				Resize					(Array<T>*& _array, s32 newSize);
		template<class T> static void				Sort					(Array<T>* _array);
/*x*/	//template<class T> static void				Sort					(Array<T>* _array, IComparer<T>* comparer);
/*x*/	//template<class T> static void				Sort					(Array<T>* _array, Comparison<T> comparison);
		template<class T> static void				Sort					(Array<T>* _array, s32 index, s32 length);
/*x*/	//template<class T> static void				Sort					(Array<T>* _array, s32 index, s32 length, IComparer<T>* comparer);
/*x*/	//template<class TKey, class TValue> 
/*x*/	//					static void				Sort					(Array<TKey>* keys, Array<TValue>* items);
/*x*/	//template<class TKey, class TValue> 
/*x*/	//					static void				Sort					(Array<TKey>* keys, Array<TValue>* items, IComparer<TKey>* comparer);
/*x*/	//template<class TKey, class TValue> 
/*x*/	//					static void				Sort					(Array<TKey>* keys, Array<TValue>* items, s32 index, s32 length);
/*x*/	//template<class TKey, class TValue> 
/*x*/	//					static void				Sort					(Array<TKey>* keys, Array<TValue>* items, s32 index, s32 length, IComparer<TKey>* comparer);
/*x*/	//template<class T> static bool				TrueForAll				(Array<T>* _array, Predicate<T>* match);

	private:
		template<class T> static s32				_valueType_BinarySearch	(Array<T>* _array, T value);
		template<class T> static s32				_valueType_BinarySearch	(Array<T>* _array, s32 index, s32 length, T value);
		template<class T> static void				_valueType_Sort			(Array<T>* _array);
		template<class T> static void				_valueType_Sort			(Array<T>* _array, s32 index, s32 length);
	};




	template<class T>
	class Array : public AbstractArray {
		friend class String;
	private:
		static const u32	_TYPEID = _TYPE_ARRAY;
	public:
		virtual bool		_isInstanceOf(u32 typeID);

	public:
		Array<T>(u32 length);
/*x*/	Array<T>(u32 rank, u32* lengths);
/*x*/	Array<T>(u32 rank, System::Collections::Generic::IEnumerable<T>*);

		~Array<T>();

		void					_array_refSetValue		(s32 idx, T item);
		
		inline T&				_idx_g_0based			(s32 idx)			{ return ((T*)m_array)[idx];						}
		inline T&				_idx_g					(s32 idx)			{ return ((T*)m_array)[idx - GetLowerBound(1)];		}
		inline T&				_idx_g$					(s32 idx)			{ CHCKTHIS; return _idx_g(idx);						}
		inline T&				_idx$_g					(s32 idx)			{ if(((u32)idx) >= (u32)(GetLowerBound(1) + _acc_gLength()) || ((u32)idx < (u32)GetLowerBound(1)) ) { THROW(CS_NEW IndexOutOfRangeException()); } return ((T*)m_array)[idx - GetLowerBound(1)];  }
		inline T&				_idx$_g$				(s32 idx)			{ CHCKTHIS; return _idx$_g(idx);					}
		inline T				_idx_s					(s32 idx, T item)	{ _array_refSetValue(idx, item); return item;		}
		inline T				_idx_s$					(s32 idx, T item)	{ CHCKTHIS; return _idx_s(idx, item);				}
		inline T				_idx$_s					(s32 idx, T item)	{ 
			if(((u32)idx) >= (u32)GetLowerBound(1) + _acc_gLength() || ((u32)idx < (u32)GetLowerBound(1)))	{ THROW(CS_NEW IndexOutOfRangeException()); }
			if(_acc_gRank() > 1)	{ THROW(CS_NEW ArgumentException()); }
			_array_refSetValue(idx, item);
			return item;
		}
		inline T				_idx$_s$				(s32 idx, T item)	{ CHCKTHIS; return _idx$_s(idx, item);				}
		inline Array<T>*		_s						(s32 idx, T item)	{ _array_refSetValue(idx, item); return this;		}

		Object*					Clone					();
		inline Object*			Clone$					()					{ CHCKTHIS; return Clone();							}

		Collections::Generic::IEnumerator<T>*
		                        GetEnumerator           ();
		inline Collections::Generic::IEnumerator<T>*
		                        GetEnumerator$          ()	                { CHCKTHIS; return GetEnumerator();				    }
	
	public: // Internal method.
		Array<T>										(u32 length, T* _array, u32 arrayLen);

	private:
		class Enumerator : public Collections::Generic::IEnumerator<T> {
		private:
			T* m_array;
			u64 m_length;
			u64 m_nextIndex;
			static const u64 c_uninitialized = 0xFFFFFFFFFFFFFFFF;
		public:
			Enumerator(u64 length, void* theArray);
			T _acc_gCurrent();
			bool MoveNext();
			void Dispose();
		};
	};

	template<class T>
	bool Array<T>::_isInstanceOf(u32 typeID) {
		_INSTANCEOF(Array,Object);
	};

	template <class T>
	inline void Array<T>::_array_refSetValue(s32 idx, T item) {
		if((_getTypeIDOfElement() & ET_STRUCT) == ET_STRUCT) {
			((__GCStruct*)((T*)m_array + idx - GetLowerBound(1)))->_RefSetValue(&item);
		} else {
			__GCObject::_RefSetValue((__GCObject**)((T*)m_array + idx - GetLowerBound(1)), (__GCObject*)item);
		}
	}

	template <> inline void Array<u64>::_array_refSetValue	(s32 idx, u64 item)		{ ((u64*)m_array)[idx - GetLowerBound(1)] = item; }
	template <> inline void Array<s64>::_array_refSetValue	(s32 idx, s64 item)		{ ((s64*)m_array)[idx - GetLowerBound(1)] = item; }
	template <> inline void Array<u32>::_array_refSetValue	(s32 idx, u32 item)		{ ((u32*)m_array)[idx - GetLowerBound(1)] = item; }
	template <> inline void Array<s32>::_array_refSetValue	(s32 idx, s32 item)		{ ((u32*)m_array)[idx - GetLowerBound(1)] = item; }
	template <> inline void Array<u16>::_array_refSetValue	(s32 idx, u16 item)		{ ((u16*)m_array)[idx - GetLowerBound(1)] = item; }
	template <> inline void Array<s16>::_array_refSetValue	(s32 idx, s16 item)		{ ((u16*)m_array)[idx - GetLowerBound(1)] = item; }
	template <> inline void Array<u8 >::_array_refSetValue	(s32 idx, u8  item)		{ ((u8 *)m_array)[idx - GetLowerBound(1)] = item; }
	template <> inline void Array<s8 >::_array_refSetValue	(s32 idx, s8  item)		{ ((u8 *)m_array)[idx - GetLowerBound(1)] = item; }
	template <> inline void Array<bool>::_array_refSetValue	 (s32 idx, bool item)	{ ((bool*)m_array)	[idx - GetLowerBound(1)] = item; }
	template <> inline void Array<double>::_array_refSetValue(s32 idx, double item)	{ ((double*)m_array)[idx - GetLowerBound(1)] = item; }
	template <> inline void Array<float>::_array_refSetValue (s32 idx, float item)	{ ((float*)m_array)	[idx - GetLowerBound(1)] = item; }
	template <> inline void Array<s32*>::_array_refSetValue (s32 idx, s32* item)	{ ((s32**)m_array)	[idx - GetLowerBound(1)] = item; }
	
	// Constructors - Destructor
	// -----------------------------------
	template<class T>
	Array<T>::Array(u32 length)
	: AbstractArray(1, length, __InternalUtilsGetTypeID<T>::getIt(), sizeof(T))
	{
	}

	template<class T>
	Array<T>::Array(u32 length, T* _array, u32 arrayLen)
	: AbstractArray(1, length, __InternalUtilsGetTypeID<T>::getIt(), sizeof(T))
	{
		memcpy(m_array, _array, arrayLen * sizeof(T));
	}

/*x*/ //Array<T>(u32 typeID, u32 rank, System::Collections::Generic::IEnumerable<T>*);

	template<class T>
	Array<T>::~Array() {
		
	}

	// -----------------------------------
	// Methods
	// -----------------------------------

	
	template<class T>
	Object* Array<T>::Clone() {
		Array<T>* obj = CS_NEW Array<T>(_acc_gLength());
		AbstractArray::Copy(this, obj, _acc_gLength());
		return (Object*)obj;
	}










// ===================================
// ===================================
// AbstractArray Template Methods
// ===================================
// ===================================

/*x*/	//static ReadOnlyCollection<T>* AsReadOnly		(Array<T>* _array);

	template<class T>
	s32 AbstractArray::_valueType_BinarySearch(Array<T>* _array, T value) {
		if(!_array)	{ THROW(CS_NEW ArgumentNullException());	}

		s32 startIdx	= 0;
		s32 endIdx		= _array->_acc_gLength() - 1;

		if(value > _array->_idx_g(endIdx)) {
			return ~(endIdx + 1);
		}

		while(startIdx <= endIdx) {
			s32 currentIdx = (startIdx + endIdx) / 2;
			if(_array->_idx_g(currentIdx) == value) {
				return currentIdx;
			} else if(value > _array->_idx_g(currentIdx)) {
				startIdx = currentIdx + 1;
			} else /*if(value < _array->_idx_g(currentIdx))*/ {
				endIdx = currentIdx - 1;
			}
		}
		return ~startIdx;
	}

	template<class T>
	inline s32 AbstractArray::BinarySearch(Array<T>* _array, T value) {
		if(!_array)	{ THROW(CS_NEW ArgumentNullException());	}

		s32 startIdx	= 0;
		s32 endIdx		= _array->_acc_gLength() - 1;

		// Throws an ArgumentException if CompareTo throws a CppNotComparable Exception
		TRY
			if(value->CompareTo(_array->_idx_g(endIdx)) > 0) {
				return ~(endIdx + 1);
			}

			while(startIdx <= endIdx) {
				s32 currentIdx = (startIdx + endIdx) / 2;
				s32 compRes = value->CompareTo(_array->_idx_g(currentIdx));
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
	template<> inline s32 AbstractArray::BinarySearch(Array<s64>* _array, s64 value)		{ return _valueType_BinarySearch(_array, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<u64>* _array, u64 value)		{ return _valueType_BinarySearch(_array, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<s32>* _array, s32 value)		{ return _valueType_BinarySearch(_array, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<u32>* _array, u32 value)		{ return _valueType_BinarySearch(_array, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<s16>* _array, s16 value)		{ return _valueType_BinarySearch(_array, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<u16>* _array, u16 value)		{ return _valueType_BinarySearch(_array, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<s8>* _array, s8 value)			{ return _valueType_BinarySearch(_array, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<u8>* _array, u8 value)			{ return _valueType_BinarySearch(_array, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<float>* _array, float value)	{ return _valueType_BinarySearch(_array, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<double>* _array, double value)	{ return _valueType_BinarySearch(_array, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<bool>* _array, bool value)		{ return _valueType_BinarySearch(_array, value); }

/*x*/	//static s32			BinarySearch			(Array<T>* _array, T value, IComparer<T> comparer);

	template<class T>
	inline s32 AbstractArray::BinarySearch(Array<T>* _array, s32 index, s32 length, T value) {
		if(!_array)					{ THROW(CS_NEW ArgumentNullException());	}
		if((index | length) < 0)	{ THROW(CS_NEW ArgumentOutOfRangeException());	}
		if(!value->_isInstanceOf(_array->_getTypeIDOfElement()) || (index + length) > _array->_acc_gLength())	{ THROW(CS_NEW ArgumentException());			}

		// Same comportment as C#
		if(length == 0) { return -1; }

		s32 startIdx	= index;
		s32 endIdx		= startIdx + length - 1;

		// Throws an ArgumentException if CompareTo throws a CppNotComparable Exception
		TRY
			if(value->CompareTo(_array->_idx_g_0based(endIdx)) > 0) {
				return ~(endIdx + 1);
			}

			while(startIdx <= endIdx) {
				s32 currentIdx = (startIdx + endIdx) / 2;
				s32 compRes = value->CompareTo(_array->_idx_g_0based(currentIdx));
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
	s32 AbstractArray::_valueType_BinarySearch(Array<T>* _array, s32 index, s32 length, T value) {
		if(!_array)									{ THROW(CS_NEW ArgumentNullException());		}
		if((index | length) < 0)					{ THROW(CS_NEW ArgumentOutOfRangeException());	}
		if((index + length) > _array->_acc_gLength()) 	{ THROW(CS_NEW ArgumentException());			}

		// Same comportment as C#
		if(length == 0) { return -1; }

		s32 startIdx	= index;
		s32 endIdx		= startIdx + length - 1;

		if(value > _array->_idx_g_0based(endIdx)) {
			return ~(endIdx + 1);
		}

		while(startIdx <= endIdx) {
			s32 currentIdx = (startIdx + endIdx) / 2;
			if(value == _array->_idx_g_0based(currentIdx)) {
				return currentIdx;
			} else if(value > _array->_idx_g_0based(currentIdx)) {
				startIdx = currentIdx + 1;
			} else /*if(value < _array->_idx_g_0based(currentIdx))*/ {
				endIdx = currentIdx - 1;
			}
		}
		return ~startIdx;
	}
	template<> inline s32 AbstractArray::BinarySearch(Array<s64>* _array, s32 index, s32 length, s64 value)			{ return _valueType_BinarySearch(_array, index, length, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<u64>* _array, s32 index, s32 length, u64 value)			{ return _valueType_BinarySearch(_array, index, length, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<s32>* _array, s32 index, s32 length, s32 value)			{ return _valueType_BinarySearch(_array, index, length, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<u32>* _array, s32 index, s32 length, u32 value)			{ return _valueType_BinarySearch(_array, index, length, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<s16>* _array, s32 index, s32 length, s16 value)			{ return _valueType_BinarySearch(_array, index, length, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<u16>* _array, s32 index, s32 length, u16 value)			{ return _valueType_BinarySearch(_array, index, length, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<s8>* _array, s32 index, s32 length, s8 value)			{ return _valueType_BinarySearch(_array, index, length, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<u8>* _array, s32 index, s32 length, u8 value)			{ return _valueType_BinarySearch(_array, index, length, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<float>* _array, s32 index, s32 length, float value)		{ return _valueType_BinarySearch(_array, index, length, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<double>* _array, s32 index, s32 length, double value)	{ return _valueType_BinarySearch(_array, index, length, value); }
	template<> inline s32 AbstractArray::BinarySearch(Array<bool>* _array, s32 index, s32 length, bool value)		{ return _valueType_BinarySearch(_array, index, length, value); }


/*x*/	//static s32			BinarySearch			(Array<T>* _array, s32 index, s32 length, T value, IComparer<T>* comparer);
	
/*x*/	//static bool			Exists					(Array<T>* _array, Predicate<T>* match);
/*x*/	//static T*				Find					(Array<T>* _array, Predicate<T>* match);
/*x*/	//static Array<T>*		FindAll					(Array<T>* _array, Predicate<T>* match);
/*x*/	//static s32			FindIndex				(Array<T>* _array, Predicate<T>* match);
/*x*/	//static s32			FindIndex				(Array<T>* _array, s32 startIndex, Predicate<T>* match);
/*x*/	//static s32			FindIndex				(Array<T>* _array, s32 startIndex, s32 count, Predicate<T>* match);
/*x*/	//static T*				FindLast				(Array<T>* _array, Predicate<T>* match);
/*x*/	//static s32			FindLastIndex			(Array<T>* _array, Predicate<T>* match);
/*x*/	//static s32			FindLastIndex			(Array<T>* _array, s32 startIndex, Predicate<T>* match);
/*x*/	//static int			FindLastIndex			(Array<T>* _array, s32 startIndex, s32 count, Predicate<T>* match);
/*x*/	//static void			ForEach					(Array<T>* _array, Action<T> action);
	
	template<class T>
	inline s32 AbstractArray::IndexOf(Array<T>* _array, T value) {
		if(!_array) { THROW(CS_NEW ArgumentNullException()); }

		for(int i = 0; i < _array->_acc_gLength(); ++i) {
			if(__InternalUtils::_areEqual(value, _array->_idx_g_0based(i))) {
				return i;
			}
		}
		return -1;
	}

	template<class T>
	inline s32 AbstractArray::IndexOf(Array<T>* _array, T value, s32 startIndex) {
		if(!_array) { THROW(CS_NEW ArgumentNullException()); }
		if((u32)startIndex >= (u32)_array->_acc_gLength()) { THROW(CS_NEW ArgumentOutOfRangeException()); }
		
		for(int i = startIndex; i < _array->_acc_gLength(); ++i) {
			if(__InternalUtils::_areEqual(value, _array->_idx_g_0based(i))) {
				return i;
			}
		}
		return -1;
	}

	template<class T>
	inline s32	AbstractArray::IndexOf(Array<T>* _array, T value, s32 startIndex, s32 count) {
		if(!_array) { THROW(CS_NEW ArgumentNullException()); }
		if(((u32)startIndex >= (u32)_array->_acc_gLength()) || (count < 0) || (startIndex + count > _array->_acc_gLength())) { 
			THROW(CS_NEW ArgumentOutOfRangeException()); 
		}
		
		for(int i = startIndex; i < startIndex + count; ++i) {
			if(__InternalUtils::_areEqual(value, _array->_idx_g_0based(i))) {
				return i;
			}
		}
		return -1;
	}

	template<class T>
	inline s32 AbstractArray::LastIndexOf(Array<T>* _array, T value) {
		if(!_array) { THROW(CS_NEW ArgumentNullException()); }

		for(s32 i = _array->_acc_gLength() - 1; i >= 0; --i) {
			if(__InternalUtils::_areEqual(value, _array->_idx_g_0based(i))) {
				return i;
			}
		}
		return -1;
	}

	template<class T>
	inline s32 AbstractArray::LastIndexOf(Array<T>* _array, T value, s32 startIndex) {
		if(!_array) { THROW(CS_NEW ArgumentNullException()); }
		if((u32)startIndex >= (u32)_array->_acc_gLength()) { THROW(CS_NEW ArgumentOutOfRangeException()); }
		
		for(s32 i = startIndex; i >= 0; --i) {
			if(__InternalUtils::_areEqual(value, _array->_idx_g_0based(i))) {
				return i;
			}
		}
		return -1;
	}

	template<class T>
	inline s32 AbstractArray::LastIndexOf(Array<T>* _array, T value, s32 startIndex, s32 count) {
		if(!_array) { THROW(CS_NEW ArgumentNullException()); }
		if(((u32)startIndex >= (u32)_array->_acc_gLength()) || (count < 0) || (startIndex - count < -1)) { 
			THROW(CS_NEW ArgumentOutOfRangeException());
		}
		
		for(s32 i = startIndex; i > startIndex - count; --i) {
			if(__InternalUtils::_areEqual(value, _array->_idx_g_0based(i))) {
				return i;
			}
		}
		return -1;
	}

	template<class T>
	void AbstractArray::Resize(Array<T>*& _array, s32 newSize) {
		if(newSize < 0) { THROW(CS_NEW ArgumentOutOfRangeException()); }
		if(_array && _array->_acc_gLength() == newSize) return;

		_array->m_arrayObject->_removeOwner(_array);
		void* tmp = __GCMalloc::allocBlock(newSize * _array->_getSizeOfElement(), _array->m_arrayObject);
		_array->m_arrayObject->_addOwner(_array);

		u32 length = (newSize > _array->_acc_gLength()) ? _array->_acc_gLength() : newSize;

		memcpy(tmp, _array->m_array, length * sizeof(T));
		
		if((_array->_getTypeIDOfElement() & ET_STRUCT) == ET_STRUCT) {
			u32 i = 0;
			for(; i < length; ++i) {
				__GCStruct* str = (__GCStruct*)((T*)tmp + i);
				if(str) {
					str->_moveAlert((u8*)str - (u8*)((T*)_array->m_array + i));
				}
			}
			for(; i < (u32)_array->_acc_gLength(); ++i) {
				((__GCStruct*)((T*)_array->m_array + i))->_RefSetValue((T*)__InternalUtils::m_nullStruct);
			}
		} else if((_array->_getTypeIDOfElement() & ET_CLASS) == ET_CLASS) {
			u32 i = 0;
			for(; i < length; ++i) {
				__GCObject** obj = (__GCObject**)((T*)tmp + i);
				if(*obj) {
					(*obj)->_moveRef((__GCObject**)((T*)_array->m_array + i), obj);
				}
			}
			for(; i < (u32)_array->_acc_gLength(); ++i) {
				_RefSetValue((__GCObject**)((T*)_array->m_array + i), NULL);
			}
		}
		
		_array->m_array = (T*)tmp;
		_array->_setLength(newSize);
	}
	
	template<class T>
	void AbstractArray::_valueType_Sort(Array<T>* _array) {
		if(!_array) { THROW(CS_NEW ArgumentNullException()); }
		// TODO ? quick sort if m_count > ?
		for(u32 i = 1; i < (u32)_array->_acc_gLength(); ++i) {
			u32 j = i;
			T tmp = _array->_idx_g_0based(i);
			while((j > 0) && (_array->_idx_g_0based(j - 1) > tmp)) {
				_array->_array_refSetValue(j, _array->_idx_g_0based(j-1));
				--j;
			}
			_array->_array_refSetValue(j, tmp);
		}
	}

	template<class T>
	inline void AbstractArray::Sort(Array<T>* _array) {
		if(!_array) { THROW(CS_NEW ArgumentNullException()); }

		for(u32 i = 1; i < (u32)_array->_acc_gLength(); ++i) {
			u32 j = i;
			T tmp = _array->_idx_g_0based(i);

			// Throws an InvalidOperationException if CompareTo throws a CppNotComparable Exception
			TRY
				while(j > 0 && (_array->_idx_g_0based(j-1)->CompareTo(tmp) > 0)) {
					_array->_array_refSetValue(j, _array->_idx_g_0based(j-1));
					--j;
				}
			CTRY
			FIRSTCATCH(CppNotComparable, ex)
				THROW(CS_NEW InvalidOperationException());
			FINALLY
			ETRY
			_array->_array_refSetValue(j, tmp);
		}
	}
	template<> inline void AbstractArray::Sort(Array<s64>* _array)		{ _valueType_Sort(_array); }
	template<> inline void AbstractArray::Sort(Array<u64>* _array)		{ _valueType_Sort(_array); }
	template<> inline void AbstractArray::Sort(Array<s32>* _array)		{ _valueType_Sort(_array); }
	template<> inline void AbstractArray::Sort(Array<u32>* _array)		{ _valueType_Sort(_array); }
	template<> inline void AbstractArray::Sort(Array<s16>* _array)		{ _valueType_Sort(_array); }
	template<> inline void AbstractArray::Sort(Array<u16>* _array)		{ _valueType_Sort(_array); }
	template<> inline void AbstractArray::Sort(Array<s8 >* _array)		{ _valueType_Sort(_array); }
	template<> inline void AbstractArray::Sort(Array<u8 >* _array)		{ _valueType_Sort(_array); }
	template<> inline void AbstractArray::Sort(Array<float>* _array)	{ _valueType_Sort(_array); }
	template<> inline void AbstractArray::Sort(Array<double>* _array)	{ _valueType_Sort(_array); }
	template<> inline void AbstractArray::Sort(Array<bool>* _array)		{ _valueType_Sort(_array); }

/*x*/	//static void			Sort					(Array<T>* _array, IComparer<T>* comparer);
/*x*/	//static void			Sort					(Array<T>* _array, Comparison<T> comparison);
	
	template<class T>
	void AbstractArray::_valueType_Sort(Array<T>* _array, s32 index, s32 length) {
		if(!_array)									{ THROW(CS_NEW ArgumentNullException()); }
		if((index | length) < 0)					{ THROW(CS_NEW ArgumentOutOfRangeException());	}
		if(index + length > _array->_acc_gLength())	{ THROW(CS_NEW ArgumentException()); }

		for(int i = index + 1; i < index + length; ++i) {
			int j = i;
			T tmp = _array->_idx_g_0based(i);
			while(j > index && _array->_idx_g_0based(j - 1) > tmp) {
				_array->_array_refSetValue(j, _array->_idx_g_0based(j - 1));
				--j;
			}
			_array->_array_refSetValue(j, tmp);
		}
	}

	template<class T>
	inline void AbstractArray::Sort(Array<T>* _array, s32 index, s32 length) {
		if(!_array)									{ THROW(CS_NEW ArgumentNullException()); }
		if((index | length) < 0)					{ THROW(CS_NEW ArgumentOutOfRangeException());	}
		if(index + length > _array->_acc_gLength())	{ THROW(CS_NEW ArgumentException()); }
		
		for(int i = index + 1; i < index + length; ++i) {
			int j = i;
			T tmp = _array->_idx_g(i);
			// Throws an InvalidOperationException if CompareTo throws a CppNotComparable Exception
			TRY
				while(j > index && _array->_idx_g_0based(j - 1)->CompareTo(tmp) > 0) {
					_array->_array_refSetValue(j, _array->_idx_g_0based(j - 1));
					--j;
				}
			CTRY
			FIRSTCATCH(CppNotComparable, ex)
				THROW(CS_NEW InvalidOperationException());
			FINALLY
			ETRY
			_array->_array_refSetValue(j, tmp);
		}
	}
	template<> inline void AbstractArray::Sort(Array<s64>* _array, s32 index, s32 length)		{ _valueType_Sort(_array, index, length); }
	template<> inline void AbstractArray::Sort(Array<u64>* _array, s32 index, s32 length)		{ _valueType_Sort(_array, index, length); }
	template<> inline void AbstractArray::Sort(Array<s32>* _array, s32 index, s32 length)		{ _valueType_Sort(_array, index, length); }
	template<> inline void AbstractArray::Sort(Array<u32>* _array, s32 index, s32 length)		{ _valueType_Sort(_array, index, length); }
	template<> inline void AbstractArray::Sort(Array<s16>* _array, s32 index, s32 length)		{ _valueType_Sort(_array, index, length); }
	template<> inline void AbstractArray::Sort(Array<u16>* _array, s32 index, s32 length)		{ _valueType_Sort(_array, index, length); }
	template<> inline void AbstractArray::Sort(Array<s8 >* _array, s32 index, s32 length)		{ _valueType_Sort(_array, index, length); }
	template<> inline void AbstractArray::Sort(Array<u8 >* _array, s32 index, s32 length)		{ _valueType_Sort(_array, index, length); }
	template<> inline void AbstractArray::Sort(Array<float>*  _array, s32 index, s32 length)	{ _valueType_Sort(_array, index, length); }
	template<> inline void AbstractArray::Sort(Array<double>* _array, s32 index, s32 length)	{ _valueType_Sort(_array, index, length); }
	template<> inline void AbstractArray::Sort(Array<bool>*   _array, s32 index, s32 length)	{ _valueType_Sort(_array, index, length); }

/*x*/	//static void			Sort					(Array<T>* _array, s32 index, s32 length, IComparer<T>* comparer);
/*x*/	//static void			Sort					(Array<TKey>* keys, Array<TValue>* items);
/*x*/	//static void			Sort					(Array<TKey>* keys, Array<TValue>* items, IComparer<TKey>* comparer);
/*x*/	//static void			Sort					(Array<TKey>* keys, Array<TValue>* items, s32 index, s32 length);
/*x*/	//static void			Sort					(Array<TKey>* keys, Array<TValue>* items, s32 index, s32 length, IComparer<TKey>* comparer);
/*x*/	//static bool			TrueForAll				(Array<T>* _array, Predicate<T>* match);

	template<class T>
	Collections::Generic::IEnumerator<T>* Array<T>::GetEnumerator() {
		return CS_NEW Enumerator(this->_acc_gLongLength$(), this->m_array);
	}
	
	// -----------------------------------------------------------------------
	// Enumerator
	template<class T>
	Array<T>::Enumerator::Enumerator(u64 length, void* theArray) {
		m_nextIndex = c_uninitialized;
		m_array = (T*)theArray;
		m_length = length;
	}

	template<class T>
	T Array<T>::Enumerator::_acc_gCurrent() {
		if(m_nextIndex == c_uninitialized || m_nextIndex > m_length) {
			THROW(CS_NEW InvalidOperationException());
		}
		return m_array[m_nextIndex];
	}

	template<class T>
	bool Array<T>::Enumerator::MoveNext() {
		return ((++m_nextIndex) < m_length);
	}

	template<class T>
	void Array<T>::Enumerator::Dispose() {
		// nop
	}	
}

#endif
