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
#include "CS_Array.h"

namespace System {

// -----------------------------------------------------------------------
// Virtual methods

/*virtual*/
bool AbstractArray::_isInstanceOf(u32 typeID) {
	_INSTANCEOF(AbstractArray,Object);
};

/*virtual*/
u32 AbstractArray::_processGC() {
	if(m_arrayObject) {
		u32 lastProcessIndex	= Memory::getLastProcessIndex();
		u32 countMax			= Memory::getProcessSizeMax();

		if((m_typeIDOfElement & ET_BASETYPE) != ET_BASETYPE) {
			if((_getTypeIDOfElement() & ET_STRUCT) == ET_STRUCT) {
				for(int i = lastProcessIndex; i < GetLength(); ++i) {
					// There will always be a struct in i event if it is a 0 filled one.
					// So we always call __Internal_Struct_processGC.
					if(!countMax) {
						if(((__GCStruct*)((u8*)m_array + i * m_sizeOfElement))->_processGC() == INCOMPLETE) {
							Memory::setLastProcessIndex(i);
							return INCOMPLETE;
						}
					}
					countMax = Memory::getProcessSizeMax();
				}
			} else {
				for(int i = lastProcessIndex; i < GetLength(); ++i) {
					__GCObject* obj = *(__GCObject**)((u8*)m_array + i * m_sizeOfElement);
					if(obj) {
						if(!(countMax--)) {
							Memory::setLastProcessIndex(i);
							return INCOMPLETE;
						}
						Memory::pushList(obj, 0);
					}
				}
			}
		}

		// There are at least 32 places left.
		Memory::pushList(m_arrayObject, 0);
	}
	return COMPLETE;
}

/*virtual*/
void AbstractArray::_move(__GCObject* prevobj, __GCObject* newobj) {
	if((__GCObject*)m_arrayObject == prevobj) {
		m_arrayObject = (__GCMalloc*)newobj;
		m_array = m_arrayObject->getBlock();
	
		if((m_typeIDOfElement & ET_BASETYPE) != ET_BASETYPE) {
			void* old = ((__GCMalloc*)prevobj)->getBlock();
			if((m_typeIDOfElement & ET_CLASS) == ET_CLASS) {
				for(int i = 0; i < m_length; ++i) {
					__GCObject** obj = (__GCObject**)((u8*)m_array + i * m_sizeOfElement);
					if(*obj) {
						(*obj)->_moveRef((__GCObject**)((u8*)old + i * m_sizeOfElement), obj);
					}
				}
			} else if((m_typeIDOfElement & ET_STRUCT) == ET_STRUCT) {
				for(int i = 0; i < m_length; ++i) {
					__GCStruct* str = (__GCStruct*)((u8*)m_array + i * m_sizeOfElement);
					str->_moveAlert((u8*)str - ((u8*)old + i * m_sizeOfElement));
				}
			}
		}

	}
}

/*virtual*/
void AbstractArray::_releaseGC() {
	if(m_arrayObject) {
		if((m_typeIDOfElement & ET_BASETYPE) != ET_BASETYPE) {
			if((m_typeIDOfElement & ET_STRUCT) == ET_STRUCT) {
				for(int i = 0; i < m_length; ++i) {
					((__GCStruct*)((u8*)m_array + i * m_sizeOfElement))->_releaseGC();
				}
			} else {
				for(int i = 0; i < m_length; ++i) {
					__GCObject* obj = *(__GCObject**)this->_getValuePtr(i);
					if(obj && !obj->isFreed()) {
						obj->_releaseGC();
						obj->_removeRef((__GCObject**)_getValuePtr(i));
					}
				}
			}
		}
		if(!m_arrayObject->isFreed()) { m_arrayObject->_removeOwner(this); }
	}
}

/*virtual*/
void AbstractArray::_moveAlert(u32 offset) {
	Object::_moveAlert(offset);
	if(m_arrayObject) { m_arrayObject->_moveOwnerAsRef((__GCObject**)((u8*)this - offset) , (__GCObject**)this); }
	if(!(m_infos & OWN_LENGTHS_BUFFER))			{ m_lengths = (u32*)&m_length;			}
	if(!(m_infos & OWN_LOWER_BOUNDS_BUFFER))	{ m_lowerBounds = (u32*)&m_lowerBound;	}
}

// -----------------------------------------------------------------------

// -----------------------------------------------------------------------
// Constructors - Destructor

AbstractArray::AbstractArray(u32 rank, u32 length, u32 typeID, size_t sizeOfElement)
: m_array			(NULL)
, m_lengths			(NULL)
, m_lowerBound		(0)
, m_rank			(rank)
, m_length			(length)
, m_typeIDOfElement	(typeID)
, m_sizeOfElement	(sizeOfElement)
, m_infos			(0)
{
	m_lowerBounds	= &m_lowerBound;
	m_lengths		= (u32*)&m_length;
	
	m_array = __GCMalloc::allocBlock(sizeOfElement * length, m_arrayObject);
	m_arrayObject->_addOwner(this);
}
	
AbstractArray::AbstractArray(u32 rank, u32* lengths, u32 typeID, u32 sizeOfElement, u32* lowerBounds)
: m_array			(NULL)
, m_lowerBounds		(NULL)
, m_lengths			(NULL)
, m_lowerBound		(0)
, m_rank			(rank)
, m_length			(0)
, m_typeIDOfElement	(typeID)
, m_sizeOfElement	(sizeOfElement)
, m_infos			(0)
{
	if(rank < 1 || !lowerBounds || !lengths) {
		THROW(CS_NEW CppException());
	}

	m_lowerBounds	= (u32*)CS_MALLOC(sizeof(u32) * rank);
	m_lengths		= (u32*)CS_MALLOC(sizeof(u32) * rank);
	m_infos			= OWN_LENGTHS_BUFFER | OWN_LOWER_BOUNDS_BUFFER;

	memcpy(m_lowerBounds, lowerBounds, rank * sizeof(u32));
	memcpy(m_lengths, lengths, rank * sizeof(u32));

	m_length		= 1;
	for(u32 i = 0; i < rank; ++i) {
		if(lengths[i] > 0) {
			m_length *= lengths[i];
		}
	}
	
	m_array = __GCMalloc::allocBlock((u32)(sizeOfElement * m_length), m_arrayObject);
	m_arrayObject->_addOwner(this);
}

AbstractArray::~AbstractArray() {
	CS_FREE(m_lowerBounds);
	CS_FREE(m_lengths);

	_releaseGC();
}



// -----------------------------------------------------------------------

// -----------------------------------------------------------------------
// Protected Methods

Object*	AbstractArray::_getValue(s32 index) {
	if(m_rank != 1) { THROW(CS_NEW ArgumentException()); }
	if((u32)index < m_lowerBounds[0] || index >= (m_lowerBounds[0] + m_length)) { THROW(CS_NEW IndexOutOfRangeException()); }
	return *((System::Object**)((u8*)m_array + ((index - m_lowerBounds[0]) * m_sizeOfElement)));
}

// -----------------------------------------------------------------------
// Public Methods

// For objects which inherits System::Object.
/*static*/
s32 AbstractArray::BinarySearch(AbstractArray* _array, Object* value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if(!value->_isInstanceOf(_array->_getTypeIDOfElement())) { THROW(CS_NEW ArgumentException()); }
	
	s32 startIdx	= _array->GetLowerBound(1);
	s32 endIdx		= (s32)(startIdx + _array->m_length - 1);

	if(value->CompareTo(_array->_getValue(endIdx)) > 0) {
		return ~(endIdx + 1);
	}

	s32 currentIdx;
	s32 compRes;
	while(startIdx <= endIdx) {
		 currentIdx = (startIdx + endIdx) / 2;
		
		// Throws an ArgumentException if CompareTo throws a CppNotComparable Exception
		TRY
			compRes = value->CompareTo(_array->_getValue(currentIdx));
			if(compRes == 0) {
				return currentIdx;
			} else if(compRes == 1) {
				startIdx = currentIdx + 1;
			} else /*if(compRes == -1)*/ {
				endIdx = currentIdx - 1;
			}
		CTRY
		FIRSTCATCH(CppNotComparable, ex)
			THROW(CS_NEW InvalidOperationException());
		FINALLY
		ETRY
	}
	return ~startIdx;
}

// For value types
s32 AbstractArray::BinarySearch(AbstractArray* _array, s64 value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if(_array->_getTypeIDOfElement() != TYPE_LONG) { THROW(CS_NEW ArgumentException()); }
	
	return AbstractArray::BinarySearch((Array<s64>*) _array, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, u64 value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if(_array->_getTypeIDOfElement() != TYPE_ULONG) { THROW(CS_NEW ArgumentException()); }
	
	return AbstractArray::BinarySearch((Array<u64>*) _array, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, s32 value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if(_array->_getTypeIDOfElement() != TYPE_INT) { THROW(CS_NEW ArgumentException()); }
	
	return AbstractArray::BinarySearch((Array<s32>*) _array, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, u32 value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if(_array->_getTypeIDOfElement() != TYPE_UINT) { THROW(CS_NEW ArgumentException()); }
	
	return AbstractArray::BinarySearch((Array<u32>*) _array, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, s16 value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if(_array->_getTypeIDOfElement() != TYPE_SHORT) { THROW(CS_NEW ArgumentException()); }
	
	return AbstractArray::BinarySearch((Array<s16>*) _array, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, u16 value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if(_array->_getTypeIDOfElement() != TYPE_USHORT) { THROW(CS_NEW ArgumentException()); }
	
	return AbstractArray::BinarySearch((Array<u16>*) _array, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, s8 value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if(_array->_getTypeIDOfElement() != TYPE_SBYTE) { THROW(CS_NEW ArgumentException()); }
	
	return AbstractArray::BinarySearch((Array<s8>*) _array, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, u8 value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if(_array->_getTypeIDOfElement() != TYPE_BYTE) { THROW(CS_NEW ArgumentException()); }
	
	return AbstractArray::BinarySearch((Array<u8>*) _array, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, float value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if(_array->_getTypeIDOfElement() != TYPE_FLOAT) { THROW(CS_NEW ArgumentException()); }
	
	return AbstractArray::BinarySearch((Array<float>*) _array, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, double value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if(_array->_getTypeIDOfElement() != TYPE_DOUBLE) { THROW(CS_NEW ArgumentException()); }
	
	return AbstractArray::BinarySearch((Array<double>*) _array, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, bool value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if(_array->_getTypeIDOfElement() != TYPE_BOOL) { THROW(CS_NEW ArgumentException()); }
	
	return AbstractArray::BinarySearch((Array<bool>*) _array, value);
}

/*x*/	//static s32			BinarySearch			(AbstractArray* _array, Object* value, IComparer* comparer);

// For objects which inherits System::Object.
/*static*/
s32 AbstractArray::BinarySearch(AbstractArray* _array, s32 index, s32 length, Object* value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if(index < _array->GetLowerBound(1) || length < 0)		{ THROW(CS_NEW ArgumentOutOfRangeException());	}
	if(!value->_isInstanceOf(_array->_getTypeIDOfElement()) || (index + length) > _array->GetUpperBound(1) + 1)	{ THROW(CS_NEW ArgumentException()); }
	
	// Same comportment as C#
	if(length == 0) { return -1; }

	s32 startIdx	= index;
	s32 endIdx		= startIdx + length - 1;

	// Throws an InvalidOperationException if CompareTo throws a CppNotComparable Exception
	TRY
		if(value->CompareTo(_array->_getValue(endIdx)) > 0) {
			return ~(endIdx + 1);
		}

		while(startIdx <= endIdx) {
			s32 currentIdx = (startIdx + endIdx) / 2;
			s32 compRes = value->CompareTo(_array->_getValue(currentIdx));
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

// For value types
s32 AbstractArray::BinarySearch(AbstractArray* _array, s32 index, s32 length, s64 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_LONG))	{ THROW(CS_NEW ArgumentException());		}
	
	return AbstractArray::BinarySearch((Array<s64>*)_array, index, length, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, s32 index, s32 length, u64 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_ULONG))	{ THROW(CS_NEW ArgumentException());		}
	
	return AbstractArray::BinarySearch((Array<u64>*)_array, index, length, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, s32 index, s32 length, s32 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_INT))		{ THROW(CS_NEW ArgumentException());		}
	
	return AbstractArray::BinarySearch((Array<s32>*)_array, index, length, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, s32 index, s32 length, u32 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_UINT))	{ THROW(CS_NEW ArgumentException());		}
	
	return AbstractArray::BinarySearch((Array<u32>*)_array, index, length, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, s32 index, s32 length, s16 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_SHORT))	{ THROW(CS_NEW ArgumentException());		}
	
	return AbstractArray::BinarySearch((Array<s16>*)_array, index, length, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, s32 index, s32 length, u16 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_USHORT))	{ THROW(CS_NEW ArgumentException());		}
	
	return AbstractArray::BinarySearch((Array<u16>*)_array, index, length, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, s32 index, s32 length, s8 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_SBYTE))	{ THROW(CS_NEW ArgumentException());		}
	
	return AbstractArray::BinarySearch((Array<s8>*)_array, index, length, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, s32 index, s32 length, u8 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_BYTE))	{ THROW(CS_NEW ArgumentException());		}
	
	return AbstractArray::BinarySearch((Array<s64>*)_array, index, length, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, s32 index, s32 length, float value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_FLOAT))	{ THROW(CS_NEW ArgumentException());		}
	
	return AbstractArray::BinarySearch((Array<float>*)_array, index, length, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, s32 index, s32 length, double value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_DOUBLE))	{ THROW(CS_NEW ArgumentException());		}
	
	return AbstractArray::BinarySearch((Array<double>*)_array, index, length, value);
}
s32 AbstractArray::BinarySearch(AbstractArray* _array, s32 index, s32 length, bool value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_BOOL))	{ THROW(CS_NEW ArgumentException());		}
	
	return AbstractArray::BinarySearch((Array<bool>*)_array, index, length, value);
}

void AbstractArray::Clear(AbstractArray* _array, s32 index, s32 length) {
	if(!_array) { THROW(CS_NEW ArgumentNullException()); }
	if((index < _array->GetLowerBound(1)) || (length < 0) || ((index + length) > _array->_acc_gLength())) { 
		THROW(CS_NEW IndexOutOfRangeException()); 
	}

	u32 startIndex = index - _array->GetLowerBound(1);
	memset((u8*)(_array->m_array) + startIndex * _array->m_sizeOfElement , 0, length * _array->m_sizeOfElement);
}

/*x*/	static void				ConstrainedCopy			(AbstractArray* sourceArray, s32 sourceIndex, AbstractArray* destinationArray, s32 destinationIndex, s32 length);

/*static*/
void AbstractArray::Copy(AbstractArray* sourceArray, AbstractArray* destinationArray, s32 length) {
	if(!sourceArray || !destinationArray)											{ THROW(CS_NEW ArgumentNullException());		}
	if(sourceArray->m_rank != destinationArray->m_rank)								{ THROW(CS_NEW RankException());				}
	if(destinationArray->_isInstanceOf(sourceArray->m_typeIDOfElement))				{ THROW(CS_NEW ArrayTypeMismatchException());	}
	// TODO InvalidCastException
	if(length < 0)																	{ THROW(CS_NEW ArgumentOutOfRangeException());	}
	if((length > sourceArray->m_length) || (length > destinationArray->m_length))	{ THROW(CS_NEW ArgumentException());			}

	// TODO : types checking
	if(((sourceArray->m_typeIDOfElement & ET_BASETYPE) == ET_BASETYPE) && ((destinationArray->m_typeIDOfElement & ET_BASETYPE) == ET_BASETYPE)) {
		memcpy(destinationArray->m_array, sourceArray->m_array, length * sourceArray->m_sizeOfElement);
	} else {
		if((sourceArray->m_typeIDOfElement & ET_STRUCT) == ET_STRUCT) {
			for(int i = 0; i < length; ++i) {
				__GCStruct* dst = (__GCStruct*)(destinationArray->_getValuePtr(i));
				__GCStruct* src = (__GCStruct*)(sourceArray->_getValuePtr(i));
				dst->_RefSetValue(src);
			}
		} else {
			for(int i = 0; i < length; ++i) {
				__GCObject** dst = (__GCObject**)(destinationArray->_getValuePtr(i));
				__GCObject** src = (__GCObject**)(sourceArray->_getValuePtr(i));
				__GCObject::_RefSetValue(dst, *src);
			}
		}
	}
}

/*x*/	static void				Copy					(AbstractArray* sourceArray, AbstractArray* destinationArray, s64 length);
/*x*/	static void				Copy					(AbstractArray* sourceArray, s32 sourceIndex, AbstractArray* destinationArray, s32 destinationIndex, s32 length);
/*x*/	static void				Copy					(AbstractArray* sourceArray, s64 sourceIndex, AbstractArray* destinationArray, s64 destinationIndex, s64 length);
/*x*/	void					CopyTo					(AbstractArray* _array, s32 index);
/*x*/	void					CopyTo					(AbstractArray* _array, s64 index);
/*x*/	static AbstractArray*	CreateInstance			(Type elementType, s32 length);
/*x*/	static AbstractArray*	CreateInstance			(Type elementType, s32 lengths, ...);
/*x*/	static AbstractArray*	CreateInstance			(Type elementType, s64 lengths, ...);
/*x*/	static AbstractArray*	CreateInstance			(Type elementType, s32 length1, s32 length2);
/*x*/	static AbstractArray*	CreateInstance			(Type elementType, Array<s32>* lengths, Array<s32>* lowerBounds);
/*x*/	static AbstractArray*	CreateInstance			(Type elementType, s32 length1, s32 length2, s32 length3);
/*x*/	//IEnumerator			GetEnumerator			();

// For objects which inherits System::Object.
/*static*/ 
s32 AbstractArray::IndexOf(AbstractArray* _array, Object* value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}

	for(int i = _array->GetLowerBound(1); i <= _array->GetUpperBound(1); ++i) {
		if(_array->_getValue(i)->Equals(value)) {
			return i;
		}
	}
	return _array->GetLowerBound(1) - 1;
}

// For value types
s32 AbstractArray::IndexOf(AbstractArray* _array, s64 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_LONG))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<s64>*)_array, value);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, u64 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_ULONG))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<u64>*)_array, value);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, s32 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_INT))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<s32>*)_array, value);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, u32 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_UINT))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<u32>*)_array, value);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, s16 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_SHORT))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<s16>*)_array, value);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, u16 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_USHORT))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<u16>*)_array, value);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, s8 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_SBYTE))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<s8>*)_array, value);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, u8 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_BYTE))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) - AbstractArray::IndexOf((Array<u8>*)_array, value);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, float value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_FLOAT))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<float>*)_array, value);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, double value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_DOUBLE))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<double>*)_array, value);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, bool value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if((_array->_getTypeIDOfElement() != TYPE_BOOL))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<bool>*)_array, value);
}

// For objects which inherits System::Object.
/*static*/
s32 AbstractArray::IndexOf(AbstractArray* _array, Object* value, s32 startIndex) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }

	for(int i = startIndex; i <= _array->GetUpperBound(1); ++i) {
		if(_array->_getValue(i)->Equals(value)) {
			return i;
		}
	}
	return _array->GetLowerBound(1) - 1;
}

// For value types
s32 AbstractArray::IndexOf(AbstractArray* _array, s64 value, s32 startIndex) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if((_array->_getTypeIDOfElement() != TYPE_LONG))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<s64>*)_array, value, startIndex - _array->GetLowerBound(1));
}
s32 AbstractArray::IndexOf(AbstractArray* _array, u64 value, s32 startIndex) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if((_array->_getTypeIDOfElement() != TYPE_ULONG))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<u64>*)_array, value, startIndex - _array->GetLowerBound(1));
}
s32 AbstractArray::IndexOf(AbstractArray* _array, s32 value, s32 startIndex) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if((_array->_getTypeIDOfElement() != TYPE_INT))		{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<s32>*)_array, value, startIndex - _array->GetLowerBound(1));
}
s32 AbstractArray::IndexOf(AbstractArray* _array, u32 value, s32 startIndex) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if((_array->_getTypeIDOfElement() != TYPE_UINT))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<u32>*)_array, value, startIndex - _array->GetLowerBound(1));
}
s32 AbstractArray::IndexOf(AbstractArray* _array, s16 value, s32 startIndex) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if((_array->_getTypeIDOfElement() != TYPE_SHORT))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<s16>*)_array, value, startIndex - _array->GetLowerBound(1));
}
s32 AbstractArray::IndexOf(AbstractArray* _array, u16 value, s32 startIndex) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if((_array->_getTypeIDOfElement() != TYPE_USHORT))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<u16>*)_array, value, startIndex - _array->GetLowerBound(1));
}
s32 AbstractArray::IndexOf(AbstractArray* _array, s8 value, s32 startIndex) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if((_array->_getTypeIDOfElement() != TYPE_SBYTE))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<s8>*)_array, value, startIndex - _array->GetLowerBound(1));
}
s32 AbstractArray::IndexOf(AbstractArray* _array, u8 value, s32 startIndex) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if((_array->_getTypeIDOfElement() != TYPE_BYTE))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) - AbstractArray::IndexOf((Array<u8>*)_array, value, startIndex - _array->GetLowerBound(1));
}
s32 AbstractArray::IndexOf(AbstractArray* _array, float value, s32 startIndex) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if((_array->_getTypeIDOfElement() != TYPE_FLOAT))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<float>*)_array, value, startIndex - _array->GetLowerBound(1));
}
s32 AbstractArray::IndexOf(AbstractArray* _array, double value, s32 startIndex) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if((_array->_getTypeIDOfElement() != TYPE_DOUBLE))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<double>*)_array, value, startIndex - _array->GetLowerBound(1));
}
s32 AbstractArray::IndexOf(AbstractArray* _array, bool value, s32 startIndex) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());			}
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if((_array->_getTypeIDOfElement() != TYPE_BOOL))	{ return _array->GetLowerBound(1) - 1;		}

	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<bool>*)_array, value, startIndex - _array->GetLowerBound(1));
}

// For objects which inherits System::Object.
/*static*/
s32 AbstractArray::IndexOf(AbstractArray* _array, Object* value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1) || (count < 0) || (startIndex + count > _array->GetUpperBound(1) + 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
		
	for(int i = startIndex; i < startIndex + count; ++i) {
		if(_array->_getValue(i)->Equals(value)) {
			return i;
		}
	}
	return _array->GetLowerBound(1) - 1;
}

// For value types
s32 AbstractArray::IndexOf(AbstractArray* _array, s64 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1) || (count < 0) || (startIndex + count > _array->GetUpperBound(1) + 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if((_array->_getTypeIDOfElement() != TYPE_LONG)) { return _array->GetLowerBound(1) - 1;		}
	
	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<s64>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, u64 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1) || (count < 0) || (startIndex + count > _array->GetUpperBound(1) + 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if((_array->_getTypeIDOfElement() != TYPE_ULONG)) { return _array->GetLowerBound(1) - 1;		}
	
	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<u64>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, s32 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1) || (count < 0) || (startIndex + count > _array->GetUpperBound(1) + 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if((_array->_getTypeIDOfElement() != TYPE_INT)) { return _array->GetLowerBound(1) - 1;		}
	
	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<s32>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, u32 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1) || (count < 0) || (startIndex + count > _array->GetUpperBound(1) + 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if((_array->_getTypeIDOfElement() != TYPE_UINT)) { return _array->GetLowerBound(1) - 1;		}
	
	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<u32>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, s16 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1) || (count < 0) || (startIndex + count > _array->GetUpperBound(1) + 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if((_array->_getTypeIDOfElement() != TYPE_SHORT)) { return _array->GetLowerBound(1) - 1;		}
	
	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<s16>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, u16 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1) || (count < 0) || (startIndex + count > _array->GetUpperBound(1) + 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if((_array->_getTypeIDOfElement() != TYPE_USHORT)) { return _array->GetLowerBound(1) - 1;		}
	
	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<u16>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, s8 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1) || (count < 0) || (startIndex + count > _array->GetUpperBound(1) + 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if((_array->_getTypeIDOfElement() != TYPE_SBYTE)) { return _array->GetLowerBound(1) - 1;		}
	
	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<s8>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, u8 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1) || (count < 0) || (startIndex + count > _array->GetUpperBound(1) + 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if((_array->_getTypeIDOfElement() != TYPE_BYTE)) { return _array->GetLowerBound(1) - 1;		}
	
	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<u8>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, float value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1) || (count < 0) || (startIndex + count > _array->GetUpperBound(1) + 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if((_array->_getTypeIDOfElement() != TYPE_FLOAT)) { return _array->GetLowerBound(1) - 1;		}
	
	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<float>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, double value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1) || (count < 0) || (startIndex + count > _array->GetUpperBound(1) + 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if((_array->_getTypeIDOfElement() != TYPE_DOUBLE)) { return _array->GetLowerBound(1) - 1;		}
	
	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<double>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::IndexOf(AbstractArray* _array, bool value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1) || (count < 0) || (startIndex + count > _array->GetUpperBound(1) + 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if((_array->_getTypeIDOfElement() != TYPE_BOOL)) { return _array->GetLowerBound(1) - 1;		}
	
	return _array->GetLowerBound(1) + AbstractArray::IndexOf((Array<bool>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}

/*x*/	void					Initialize				();

// For objects which inherits System::Object.
/*static*/
s32 AbstractArray::LastIndexOf(AbstractArray* _array, Object* value) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }

	for(s32 i = _array->GetUpperBound(1); i >= _array->GetLowerBound(1); --i) {
		if(_array->_getValue(i)->Equals(value)) {
			return i;
		}
	}
	return _array->GetLowerBound(1) - 1;
}

// For value types
s32 AbstractArray::LastIndexOf(AbstractArray* _array, s64 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());		 }
	if(_array->_getTypeIDOfElement() != TYPE_LONG)		{ return _array->GetLowerBound(1) - 1;	 }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<s64>*)_array, value);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, u64 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());		 }
	if(_array->_getTypeIDOfElement() != TYPE_ULONG)		{ return _array->GetLowerBound(1) - 1;	 }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<u64>*)_array, value);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, s32 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());		 }
	if(_array->_getTypeIDOfElement() != TYPE_INT)		{ return _array->GetLowerBound(1) - 1;	 }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<s32>*)_array, value);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, u32 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());		 }
	if(_array->_getTypeIDOfElement() != TYPE_UINT)		{ return _array->GetLowerBound(1) - 1;	 }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<u32>*)_array, value);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, s16 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());		 }
	if(_array->_getTypeIDOfElement() != TYPE_SHORT)		{ return _array->GetLowerBound(1) - 1;	 }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<s16>*)_array, value);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, u16 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());		 }
	if(_array->_getTypeIDOfElement() != TYPE_USHORT)	{ return _array->GetLowerBound(1) - 1;	 }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<u16>*)_array, value);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, s8 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());		 }
	if(_array->_getTypeIDOfElement() != TYPE_SBYTE)		{ return _array->GetLowerBound(1) - 1;	 }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<s8>*)_array, value);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, u8 value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());		 }
	if(_array->_getTypeIDOfElement() != TYPE_BYTE)		{ return _array->GetLowerBound(1) - 1;	 }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<u8>*)_array, value);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, float value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());		 }
	if(_array->_getTypeIDOfElement() != TYPE_FLOAT)		{ return _array->GetLowerBound(1) - 1;	 }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<float>*)_array, value);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, double value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());		 }
	if(_array->_getTypeIDOfElement() != TYPE_DOUBLE)	{ return _array->GetLowerBound(1) - 1;	 }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<double>*)_array, value);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, bool value) {
	if(!_array)											{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)								{ THROW(CS_NEW RankException());		 }
	if(_array->_getTypeIDOfElement() != TYPE_BOOL)		{ return _array->GetLowerBound(1) - 1;	 }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<bool>*)_array, value);
}

// For objects which inherits System::Object.
/*static*/
s32 AbstractArray::LastIndexOf(AbstractArray* _array, Object* value, s32 startIndex) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }

	for(s32 i = startIndex; i >= _array->GetLowerBound(1); --i) {
		if(_array->_getValue(i)->Equals(value)) {
			return i;
		}
	}
	return _array->GetLowerBound(1) - 1;
}

// For value types
s32 AbstractArray::LastIndexOf(AbstractArray* _array, s64 value, s32 startIndex) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if(_array->_getTypeIDOfElement() != TYPE_LONG)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<s64>*)_array, value, startIndex);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, u64 value, s32 startIndex) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if(_array->_getTypeIDOfElement() != TYPE_ULONG)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<u64>*)_array, value, startIndex);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, s32 value, s32 startIndex) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if(_array->_getTypeIDOfElement() != TYPE_INT)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<s32>*)_array, value, startIndex);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, u32 value, s32 startIndex) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if(_array->_getTypeIDOfElement() != TYPE_UINT)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<u32>*)_array, value, startIndex);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, s16 value, s32 startIndex) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if(_array->_getTypeIDOfElement() != TYPE_SHORT)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<s16>*)_array, value, startIndex);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, u16 value, s32 startIndex) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if(_array->_getTypeIDOfElement() != TYPE_USHORT)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<u16>*)_array, value, startIndex);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, s8 value, s32 startIndex) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if(_array->_getTypeIDOfElement() != TYPE_SBYTE)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<s8>*)_array, value, startIndex);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, u8 value, s32 startIndex) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if(_array->_getTypeIDOfElement() != TYPE_BYTE)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<u8>*)_array, value, startIndex);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, float value, s32 startIndex) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if(_array->_getTypeIDOfElement() != TYPE_FLOAT)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<float>*)_array, value, startIndex);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, double value, s32 startIndex) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if(_array->_getTypeIDOfElement() != TYPE_DOUBLE)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<double>*)_array, value, startIndex);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, bool value, s32 startIndex) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException()); }
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());		 }
	if(startIndex < _array->GetLowerBound(1) || startIndex > _array->GetUpperBound(1)) { THROW(CS_NEW ArgumentOutOfRangeException()); }
	if(_array->_getTypeIDOfElement() != TYPE_BOOL)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<bool>*)_array, value, startIndex);
}

// For objects which inherits System::Object.
/*static*/
s32 AbstractArray::LastIndexOf(AbstractArray* _array, Object* value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if((startIndex < _array->GetLowerBound(1)) || (startIndex > _array->GetUpperBound(1)) || (count < 0) || (startIndex - count < _array->GetLowerBound(1) - 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}

	for(s32 i = startIndex; i > startIndex - count; --i) {
		if(_array->_getValue(i)->Equals(value)) {
			return i;
		}
	}
	return _array->GetLowerBound(1) - 1;
}

// For value types
s32 AbstractArray::LastIndexOf(AbstractArray* _array, s64 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if((startIndex < _array->GetLowerBound(1)) || (startIndex > _array->GetUpperBound(1)) || (count < 0) || (startIndex - count < _array->GetLowerBound(1) - 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if(_array->_getTypeIDOfElement() != TYPE_LONG)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<s64>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, u64 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if((startIndex < _array->GetLowerBound(1)) || (startIndex > _array->GetUpperBound(1)) || (count < 0) || (startIndex - count < _array->GetLowerBound(1) - 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if(_array->_getTypeIDOfElement() != TYPE_ULONG)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<u64>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, s32 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if((startIndex < _array->GetLowerBound(1)) || (startIndex > _array->GetUpperBound(1)) || (count < 0) || (startIndex - count < _array->GetLowerBound(1) - 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if(_array->_getTypeIDOfElement() != TYPE_INT)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<s32>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, u32 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if((startIndex < _array->GetLowerBound(1)) || (startIndex > _array->GetUpperBound(1)) || (count < 0) || (startIndex - count < _array->GetLowerBound(1) - 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if(_array->_getTypeIDOfElement() != TYPE_UINT)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<u32>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, s16 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if((startIndex < _array->GetLowerBound(1)) || (startIndex > _array->GetUpperBound(1)) || (count < 0) || (startIndex - count < _array->GetLowerBound(1) - 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if(_array->_getTypeIDOfElement() != TYPE_SHORT)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<s16>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, u16 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if((startIndex < _array->GetLowerBound(1)) || (startIndex > _array->GetUpperBound(1)) || (count < 0) || (startIndex - count < _array->GetLowerBound(1) - 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if(_array->_getTypeIDOfElement() != TYPE_USHORT)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<u16>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, s8 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if((startIndex < _array->GetLowerBound(1)) || (startIndex > _array->GetUpperBound(1)) || (count < 0) || (startIndex - count < _array->GetLowerBound(1) - 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if(_array->_getTypeIDOfElement() != TYPE_SBYTE)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<s8>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, u8 value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if((startIndex < _array->GetLowerBound(1)) || (startIndex > _array->GetUpperBound(1)) || (count < 0) || (startIndex - count < _array->GetLowerBound(1) - 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if(_array->_getTypeIDOfElement() != TYPE_BYTE)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<u8>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, float value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if((startIndex < _array->GetLowerBound(1)) || (startIndex > _array->GetUpperBound(1)) || (count < 0) || (startIndex - count < _array->GetLowerBound(1) - 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if(_array->_getTypeIDOfElement() != TYPE_FLOAT)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<float>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, double value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if((startIndex < _array->GetLowerBound(1)) || (startIndex > _array->GetUpperBound(1)) || (count < 0) || (startIndex - count < _array->GetLowerBound(1) - 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if(_array->_getTypeIDOfElement() != TYPE_DOUBLE)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<double>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}
s32 AbstractArray::LastIndexOf(AbstractArray* _array, bool value, s32 startIndex, s32 count) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if((startIndex < _array->GetLowerBound(1)) || (startIndex > _array->GetUpperBound(1)) || (count < 0) || (startIndex - count < _array->GetLowerBound(1) - 1)) { 
		THROW(CS_NEW ArgumentOutOfRangeException());
	}
	if(_array->_getTypeIDOfElement() != TYPE_BOOL)	{ return _array->GetLowerBound(1) - 1; }

	return _array->GetLowerBound(1) + AbstractArray::LastIndexOf((Array<bool>*)_array, value, startIndex - _array->GetLowerBound(1), count);
}

/*static*/
void AbstractArray::Reverse(AbstractArray* _array) {
	AbstractArray::Reverse(_array, _array->GetLowerBound(1), (s32)_array->m_length);
}

/*static*/
void AbstractArray::Reverse(AbstractArray* _array, s32 index, s32 length) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if((index < _array->GetLowerBound(1)) || (length < 0))	{ THROW(CS_NEW ArgumentOutOfRangeException());	}
	if(index + length > _array->GetUpperBound(1) + 1)		{ THROW(CS_NEW ArgumentException());			}

	switch(_array->m_sizeOfElement) {
	case 1:
		{
			// Here the struct cannot contain any pointer.
			u8* pStart	= (u8*)_array->m_array + index;
			u8* pEnd	= (u8*)_array->m_array + index + (length >> 1);
			u8* pFill	= (u8*)_array->m_array + index + length - 1;
			while(pStart < pEnd) {
				u8 tmp		= *pStart;
				*pStart++	= *pFill;
				*pFill--	= tmp;
			}
		}
		break;
	case 2:
		{
			// Here the struct cannot contain any pointer.
			u16* pStart	= (u16*)_array->m_array + index;
			u16* pEnd	= (u16*)_array->m_array + index + (length >> 1);
			u16* pFill	= (u16*)_array->m_array + index + length - 1;
			while(pStart < pEnd) {
				u16 tmp		= *pStart;
				*pStart++	= *pFill;
				*pFill--	= tmp;
			}
		}
		break;
	case 4:
		{
			u32* pStart	= (u32*)_array->m_array + index;
			u32* pEnd	= (u32*)_array->m_array + index + (length >> 1);
			u32* pFill	= (u32*)_array->m_array + index + length - 1;
			if((_array->m_typeIDOfElement & ET_BASETYPE) == ET_BASETYPE) {
				while(pStart < pEnd) {
					u32 tmp		= *pStart;
					*pStart++	= *pFill;
					*pFill--	= tmp;
				}
			} else {
				if((_array->m_typeIDOfElement & ET_STRUCT) == ET_STRUCT) {
					while(pStart < pEnd) {
						u32 tmp		= *pStart;
						((__GCStruct*)(pStart))->_RefSetValue(pFill);
						((__GCStruct*)(pFill))->_RefSetValue(&tmp);
						*pStart++;
						*pFill--;
					}
				} else {
					while(pStart < pEnd) {
						u32 tmp = *pStart;
						__GCObject::_RefSetValue((__GCObject**)pStart, *(__GCObject**)pFill);
						__GCObject::_RefSetValue((__GCObject**)pFill,  (__GCObject*)tmp);
						pStart++;
						pFill--;
					}
				}
			}
		}
		break;
	case 8:
		{
			u64* pStart	= (u64*)_array->m_array + index;
			u64* pEnd	= (u64*)_array->m_array + index + (length >> 1);
			u64* pFill	= (u64*)_array->m_array + index + length - 1;
			if((_array->m_typeIDOfElement & ET_BASETYPE) == ET_BASETYPE) {
				while(pStart < pEnd) {
					u64 tmp		= *pStart;
					*pStart++	= *pFill;
					*pFill--	= tmp;
				}
			} else {
				if((_array->m_typeIDOfElement & ET_STRUCT) == ET_STRUCT) {
					while(pStart < pEnd) {
						u64 tmp		= *pStart;
						((__GCStruct*)(pStart))->_RefSetValue(pFill);
						((__GCStruct*)(pFill))->_RefSetValue(&tmp);
						*pStart++;
						*pFill--;
					}
				}
			}
		}
		break;
	default:
		{
			// it must be a struct
			u8* pStart	= (u8*)_array->m_array + index * _array->m_sizeOfElement;
			u8* pEnd	= (u8*)_array->m_array + (index + (length >> 1)) * _array->m_sizeOfElement;
			u8* pFill	= (u8*)_array->m_array + (index + length - 1) * _array->m_sizeOfElement;
			u8* tmp		= (u8*)CS_MALLOC(sizeof(u8) * _array->m_sizeOfElement);
			while(pStart < pEnd) {
				memcpy(tmp,	pStart, _array->m_sizeOfElement);
				((__GCStruct*)(pStart))->_RefSetValue(pFill);
				((__GCStruct*)(pFill))->_RefSetValue(tmp);
				pStart = pStart + _array->m_sizeOfElement;
				pFill  = pFill  - _array->m_sizeOfElement;
			}
			CS_FREE(tmp);
		}
		break;
	}
}

/*static*/
void AbstractArray::Sort(AbstractArray* _array) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}

	if((_array->m_typeIDOfElement & ET_CLASS) == ET_CLASS) {
		Array<System::Object*>::Sort((Array<System::Object*>*)_array);
	} else {
		if((_array->m_typeIDOfElement & ET_STRUCT) == ET_STRUCT) {
			// TODO - struct - need an implementation of IComparable.
		} else {
			switch(_array->m_sizeOfElement) {
			case 1:
				AbstractArray::Sort((Array<u8>*)_array);
				break;
			case 2:
				AbstractArray::Sort((Array<u16>*)_array);
				break;
			case 4:
				AbstractArray::Sort((Array<u32>*)_array);
				break;
			case 8:
				AbstractArray::Sort((Array<u64>*)_array);
				break;
			default:
				break;
			}
		}
	}
}

/*x*/	static void				Sort					(AbstractArray* keys, AbstractArray* items);
/*x*/	//static void			Sort					(AbstractArray* _array, IComparer* comparer);
/*x*/	//static void			Sort					(AbstractArray* keys, AbstractArray* items, IComparer* comparer);

/*static*/
void AbstractArray::Sort(AbstractArray* _array, s32 index, s32 length) {
	if(!_array)				{ THROW(CS_NEW ArgumentNullException());	}
	if(_array->m_rank > 1)	{ THROW(CS_NEW RankException());			}
	if((index < _array->GetLowerBound(1)) || (length < 0))	{ THROW(CS_NEW ArgumentOutOfRangeException());	}
	if(index + length > _array->GetUpperBound(1) + 1)		{ THROW(CS_NEW ArgumentException());			}

	if((_array->m_typeIDOfElement & ET_CLASS) == ET_CLASS) {
		Array<System::Object*>::Sort((Array<System::Object*>*)_array, index - _array->GetLowerBound(1), length);
	} else {
		if((_array->m_typeIDOfElement & ET_STRUCT) == ET_STRUCT) {
			// TODO - struct - need an implementation of IComparable.
		} else {
			switch(_array->m_sizeOfElement) {
			case 1:
				AbstractArray::Sort((Array<u8>*)_array, index - _array->GetLowerBound(1), length);
				break;
			case 2:
				AbstractArray::Sort((Array<u16>*)_array, index - _array->GetLowerBound(1), length);
				break;
			case 4:
				AbstractArray::Sort((Array<u32>*)_array, index - _array->GetLowerBound(1), length);
				break;
			case 8:
				AbstractArray::Sort((Array<u64>*)_array, index - _array->GetLowerBound(1), length);
				break;
			default:
				// Here it should be a struct
				break;
			}
		}
	}
}

/*x*/	static void				Sort					(AbstractArray* keys, AbstractArray* items, s32 index, s32 length);
/*x*/	//static void			Sort					(AbstractArray* _array, s32 index, s32 length, IComparer* comparer);
/*x*/	//static void			Sort					(AbstractArray* keys, AbstractArray* items, s32 index, s32 length, IComparer* comparer);

}
