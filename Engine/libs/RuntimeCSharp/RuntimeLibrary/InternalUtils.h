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
#ifndef _InternalUtils_
#define _InternalUtils_

#include "../CompilerProject/BaseType.h"
#include "CS_Object.h"

namespace System {
	class AbstractArray;
	class String;
	template<class T> class Array;
	class Delegate;

	namespace Collections {
		namespace Generic {
			template<class T> class List;
			template<class TKey, class TValue> class Dictionary;
			class KeyNotFoundException;
		}
	}
}

#include "inline/classPrototypes.inl"

class __InternalUtils {
public:
	static void* m_nullStruct;
	static void init();

	template<class T> 
	static bool _isNullPtr		(T element);

	template<class T>
	static bool _areEqual		(T first, T second);

	template<class T>
	static u32	_getHashCode	(T element);

	template<class T>
	static s32 _binarySearch	(T* _array, s32 index, s32 length, T value);

	template<class T>
	static s32 _compare			(T first, T second);
};

class UtilDiv {
public:
	static inline s8  _divBy(s8 & r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = (s8 )(r / v); }
	static inline s8  _divBy(s8 & r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = (s8 )(r / v); }
	static inline s8  _divBy(s8 & r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = (s8 )(r / v); }
	static inline s8  _divBy(s8 & r, u32 v) { if (v==0) { THROWDIVZERO; }; return r = (s8 )(r / v); }

	static inline u8  _divBy(u8 & r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = (u8 )(r / v); }
	static inline u8  _divBy(u8 & r, u32 v) { if (v==0) { THROWDIVZERO; }; return r = (u8 )(r / v); }
	static inline u8  _divBy(u8 & r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = (u8 )(r / v); }
	static inline u8  _divBy(u8 & r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = (u8 )(r / v); }

	static inline s16 _divBy(s16& r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = (s16)(r / v); }
	static inline s16 _divBy(s16& r, u32 v) { if (v==0) { THROWDIVZERO; }; return r = (s16)(r / v); }
	static inline s16 _divBy(s16& r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = (s16)(r / v); }
	static inline s16 _divBy(s16& r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = (s16)(r / v); }

	static inline u16 _divBy(u16& r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = (u16)(r / v); }
	static inline u16 _divBy(u16& r, u32 v) { if (v==0) { THROWDIVZERO; }; return r = (u16)(r / v); }
	static inline u16 _divBy(u16& r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = (u16)(r / v); }
	static inline u16 _divBy(u16& r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = (u16)(r / v); }

	static inline s32 _divBy(s32& r, s32 v) { if (v==0) { THROWDIVZERO; }; return r =		r / v;  }
	static inline s32 _divBy(s32& r, u32 v) { if (v==0) { THROWDIVZERO; }; return r = (s32)(r / v); }
	static inline s32 _divBy(s32& r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = (s32)(r / v); }
	static inline s32 _divBy(s32& r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = (s32)(r / v); }

	static inline u32 _divBy(u32& r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = (u32)(r / v); }
	static inline u32 _divBy(u32& r, u32 v) { if (v==0) { THROWDIVZERO; }; return r =		r / v;  }
	static inline u32 _divBy(u32& r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = (u32)(r / v); }
	static inline u32 _divBy(u32& r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = (u32)(r / v); }

	static inline s64 _divBy(s64& r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = r / v; }
	static inline s64 _divBy(s64& r, u32 v) { if (v==0) { THROWDIVZERO; }; return r = r / v; }
	static inline s64 _divBy(s64& r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = r / v; }
	static inline s64 _divBy(s64& r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = r / v; }
	
	static inline u64 _divBy(u64& r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = r / v; }
	static inline u64 _divBy(u64& r, u32 v) { if (v==0) { THROWDIVZERO; }; return r = r / v; }
	static inline u64 _divBy(u64& r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = r / v; }
	static inline u64 _divBy(u64& r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = r / v; }

	static inline s8  _modBy(s8& r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = (s8)(r % v); }
	static inline s8  _modBy(s8& r, u32 v) { if (v==0) { THROWDIVZERO; }; return r = (s8)(r % v); }
	static inline s8  _modBy(s8& r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = (s8)(r % v); }
	static inline s8  _modBy(s8& r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = (s8)(r % v); }

	static inline u8  _modBy(u8& r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = (u8)(r % v); }
	static inline u8  _modBy(u8& r, u32 v) { if (v==0) { THROWDIVZERO; }; return r = (u8)(r % v); }
	static inline u8  _modBy(u8& r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = (u8)(r % v); }
	static inline u8  _modBy(u8& r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = (u8)(r % v); }

	static inline s16 _modBy(s16& r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = (s16)(r % v); }
	static inline s16 _modBy(s16& r, u32 v) { if (v==0) { THROWDIVZERO; }; return r = (s16)(r % v); }
	static inline s16 _modBy(s16& r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = (s16)(r % v); }
	static inline s16 _modBy(s16& r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = (s16)(r % v); }

	static inline u16 _modBy(u16& r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = (u16)(r % v); }
	static inline u16 _modBy(u16& r, u32 v) { if (v==0) { THROWDIVZERO; }; return r = (u16)(r % v); }
	static inline u16 _modBy(u16& r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = (u16)(r % v); }
	static inline u16 _modBy(u16& r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = (u16)(r % v); }

	static inline s32 _modBy(s32& r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = (s32)(r % v); }
	static inline s32 _modBy(s32& r, u32 v) { if (v==0) { THROWDIVZERO; }; return r = (s32)(r % v); }
	static inline s32 _modBy(s32& r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = (s32)(r % v); }
	static inline s32 _modBy(s32& r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = (s32)(r % v); }

	static inline u32 _modBy(u32& r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = (u32)(r % v); }
	static inline u32 _modBy(u32& r, u32 v) { if (v==0) { THROWDIVZERO; }; return r =       r % v;  }
	static inline u32 _modBy(u32& r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = (u32)(r % v); }
	static inline u32 _modBy(u32& r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = (u32)(r % v); }

	static inline s64 _modBy(s64& r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = (s64)(r % v); }
	static inline s64 _modBy(s64& r, u32 v) { if (v==0) { THROWDIVZERO; }; return r = (s64)(r % v); }
	static inline s64 _modBy(s64& r, s64 v) { if (v==0) { THROWDIVZERO; }; return r =		r % v;  }
	static inline s64 _modBy(s64& r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = (s64)(r % v); }

	static inline u64 _modBy(u64& r, s32 v) { if (v==0) { THROWDIVZERO; }; return r = (u64)(r % v); }
	static inline u64 _modBy(u64& r, u32 v) { if (v==0) { THROWDIVZERO; }; return r = (u64)(r % v); }
	static inline u64 _modBy(u64& r, s64 v) { if (v==0) { THROWDIVZERO; }; return r = (u64)(r % v); }
	static inline u64 _modBy(u64& r, u64 v) { if (v==0) { THROWDIVZERO; }; return r = r % v; }

	static inline s32 _divByWrp(s32 r, s32 v) { if (v==0) { THROWDIVZERO; }; return r / v; }
	static inline u32 _divByWrp(u32 r, u32 v) { if (v==0) { THROWDIVZERO; }; return r / v; }
	static inline s64 _divByWrp(s64 r, s64 v) { if (v==0) { THROWDIVZERO; }; return r / v; }
	static inline u64 _divByWrp(u64 r, u64 v) { if (v==0) { THROWDIVZERO; }; return r / v; }

	static inline s32 _modByWrp(s32 r, s32 v) { if (v==0) { THROWDIVZERO; }; return r % v; }
	static inline u32 _modByWrp(u32 r, u32 v) { if (v==0) { THROWDIVZERO; }; return r % v; }
	static inline s64 _modByWrp(s64 r, s64 v) { if (v==0) { THROWDIVZERO; }; return r % v; }
	static inline u64 _modByWrp(u64 r, u64 v) { if (v==0) { THROWDIVZERO; }; return r % v; }

	static inline float  _modBy(float & r, double v)	{ s32 tmp = ((s32)(r / v)); return r = (float)(r-(tmp*v)); }
	static inline double _modBy(double& r, double v)	{ s32 tmp = ((s32)(r / v)); return r = r-(tmp*v); }

	static inline float  _modByWrp(float  r, double v)	{ s32 tmp = ((s32)(r / v)); return (float)(r-(tmp*v)); }
	static inline double _modByWrp(double r, double v)	{ s32 tmp = ((s32)(r / v)); return r-(tmp*v); }
};

/*static*/
template<class T>	inline bool	__InternalUtils::_isNullPtr(T element)		{ return (element) ? false:true; }
template<>			inline bool __InternalUtils::_isNullPtr(s64 element)	{ return false;	}
template<>			inline bool __InternalUtils::_isNullPtr(u64 element)	{ return false;	}
template<>			inline bool __InternalUtils::_isNullPtr(s32 element)	{ return false;	}
template<>			inline bool __InternalUtils::_isNullPtr(u32 element)	{ return false;	}
template<>			inline bool __InternalUtils::_isNullPtr(s16 element)	{ return false;	}
template<>			inline bool __InternalUtils::_isNullPtr(u16 element)	{ return false;	}
template<>			inline bool __InternalUtils::_isNullPtr(s8 element)		{ return false;	}
template<>			inline bool __InternalUtils::_isNullPtr(u8 element)		{ return false;	}
template<>			inline bool __InternalUtils::_isNullPtr(bool element)	{ return false;	}
template<>			inline bool __InternalUtils::_isNullPtr(float element)	{ return false;	}
template<>			inline bool __InternalUtils::_isNullPtr(double element)	{ return false;	}

/*static*/
template<class T>	inline bool __InternalUtils::_areEqual(T first, T second)				{ return first->Equals(second); }
template<>			inline bool __InternalUtils::_areEqual(s64 first, s64 second)			{ return first == second; }
template<>			inline bool __InternalUtils::_areEqual(u64 first, u64 second)			{ return first == second; }
template<>			inline bool __InternalUtils::_areEqual(s32 first, s32 second)			{ return first == second; }
template<>			inline bool __InternalUtils::_areEqual(u32 first, u32 second)			{ return first == second; }
template<>			inline bool __InternalUtils::_areEqual(s16 first, s16 second)			{ return first == second; }
template<>			inline bool __InternalUtils::_areEqual(u16 first, u16 second)			{ return first == second; }
template<>			inline bool __InternalUtils::_areEqual(s8 first, s8 second)				{ return first == second; }
template<>			inline bool __InternalUtils::_areEqual(u8 first, u8 second)				{ return first == second; }
template<>			inline bool __InternalUtils::_areEqual(bool first, bool second)			{ return first == second; }
template<>			inline bool __InternalUtils::_areEqual(float first, float second)		{ return first == second; }
template<>			inline bool __InternalUtils::_areEqual(double first, double second)		{ return first == second; }

/*static*/
template<class T>	inline s32	__InternalUtils::_compare(T first, T second)				{ return first->CompareTo(second); }
template<>			inline s32	__InternalUtils::_compare(s64 first, s64 second) { 
	if(first < second) { return -1; }
	if(first > second) { return +1; }
	return 0;
	
}
template<>			inline s32	__InternalUtils::_compare(u64 first, u64 second) { 
	if(first < second) { return -1; }
	if(first > second) { return 1;	}
	return 0;
}
template<>			inline s32	__InternalUtils::_compare(s32 first, s32 second) { 
	if(first < second) { return -1; }
	if(first > second) { return +1;	}
	return 0;
}
template<>			inline s32	__InternalUtils::_compare(u32 first, u32 second) { 
	if(first < second) { return -1; }
	if(first > second) { return +1;	}
	return 0;
}
template<>			inline s32	__InternalUtils::_compare(s16 first, s16 second) { 
	if(first < second) { return -1; }
	if(first > second) { return +1;	}
	return 0; 
}
template<>			inline s32	__InternalUtils::_compare(u16 first, u16 second) { 
	if(first < second) { return -1; }
	if(first > second) { return +1;	}
	return 0;
}
template<>			inline s32	__InternalUtils::_compare(s8 first, s8 second) { 
	if(first < second) { return -1; }
	if(first > second) { return +1;	}
	return 0;
}
template<>			inline s32	__InternalUtils::_compare(u8 first, u8 second) { 
	if(first < second) { return -1; }
	if(first > second) { return +1;	}
	return 0;
}
template<>			inline s32	__InternalUtils::_compare(bool first, bool second) { 
	if(first < second) { return -1; }
	if(first > second) { return +1;	}
	return 0;
}
template<>			inline s32	__InternalUtils::_compare(float first, float second) { 
	if(first < second) { return -1; }
	if(first > second) { return +1;	}
	return 0;
}
template<>			inline s32	__InternalUtils::_compare(double first, double second) { 
	if(first < second) { return -1; }
	if(first > second) { return +1;	}
	return 0;
}

/*static*/
template<class T>	inline u32 __InternalUtils::_getHashCode(T element)	{ return (u32)element->GetHashCode();	}
template<>			inline u32 __InternalUtils::_getHashCode(s32 element)	{ return (u32)element;					}
template<>			inline u32 __InternalUtils::_getHashCode(u32 element)	{ return element;						}

/*static*/
template<class T>
s32 __InternalUtils::_binarySearch(T* _array, s32 index, s32 length, T value) {
		if(!_array || length == 0)	{ return -1; }

		s32 startIdx	= index;
		s32 endIdx		= startIdx + length - 1;

		if(value > _array[endIdx]) {
			return ~(endIdx + 1);
		}

		while(startIdx <= endIdx) {
			s32 currentIdx = (startIdx + endIdx) / 2;
			if(value == _array[currentIdx]) {
				return currentIdx;
			} else if(value > _array[currentIdx]) {
				startIdx = currentIdx + 1;
			} else {
				endIdx = currentIdx - 1;
			}
		}
		return ~startIdx;
	}

template<class T>
struct __InternalUtilsGetTypeID {
	static u32 getIt() { THROW(CS_NEW System::SystemException()); }
};

template<> struct __InternalUtilsGetTypeID<s64>						{ static u32 getIt() { return TYPE_LONG;			} };
template<> struct __InternalUtilsGetTypeID<u64>						{ static u32 getIt() { return TYPE_ULONG;			} };
template<> struct __InternalUtilsGetTypeID<s32>						{ static u32 getIt() { return TYPE_INT;				} };
template<> struct __InternalUtilsGetTypeID<u32>						{ static u32 getIt() { return TYPE_UINT;			} };
template<> struct __InternalUtilsGetTypeID<s16>						{ static u32 getIt() { return TYPE_SHORT;			} };
template<> struct __InternalUtilsGetTypeID<u16>						{ static u32 getIt() { return TYPE_USHORT;			} };
template<> struct __InternalUtilsGetTypeID<s8>						{ static u32 getIt() { return TYPE_SBYTE;			} };
template<> struct __InternalUtilsGetTypeID<u8>						{ static u32 getIt() { return TYPE_BYTE;			} };
template<> struct __InternalUtilsGetTypeID<bool>					{ static u32 getIt() { return TYPE_BOOL;			} };
template<> struct __InternalUtilsGetTypeID<float>					{ static u32 getIt() { return TYPE_FLOAT;			} };
template<> struct __InternalUtilsGetTypeID<double>					{ static u32 getIt() { return TYPE_DOUBLE;			} };
template<> struct __InternalUtilsGetTypeID<s32*>					{ static u32 getIt() { return TYPE_INTPTR;			} };
template<> struct __InternalUtilsGetTypeID<System::Object*>			{ static u32 getIt() { return _TYPE_OBJECT;			} };
template<> struct __InternalUtilsGetTypeID<System::String*>			{ static u32 getIt() { return _TYPE_STRING;			} };
template<> struct __InternalUtilsGetTypeID<System::AbstractArray*>	{ static u32 getIt() { return _TYPE_ABSTRACTARRAY;	} };
template<> struct __InternalUtilsGetTypeID<System::Delegate*>		{ static u32 getIt() { return _TYPE_DELEGATE;		} };
template<> struct __InternalUtilsGetTypeID<System::Exception*>						{ static u32 getIt() { return _TYPE_EXCEPTION;					} };
template<> struct __InternalUtilsGetTypeID<System::SystemException*>				{ static u32 getIt() { return _TYPE_SYSTEMEXCEPTION;			} };
template<> struct __InternalUtilsGetTypeID<System::IndexOutOfRangeException*>		{ static u32 getIt() { return _TYPE_INDEXOUTOFRANGEEXCEPTION;	} };
template<> struct __InternalUtilsGetTypeID<System::NullReferenceException*>			{ static u32 getIt() { return _TYPE_NULLEXCEPTION;				} };
template<> struct __InternalUtilsGetTypeID<System::OutOfMemoryException*>			{ static u32 getIt() { return _TYPE_OUTOFMEMORYEXCEPTION;		} };
template<> struct __InternalUtilsGetTypeID<System::ArgumentException*>				{ static u32 getIt() { return _TYPE_ARGUMENTEXCEPTION;			} };
template<> struct __InternalUtilsGetTypeID<System::ArgumentOutOfRangeException*>	{ static u32 getIt() { return _TYPE_ARGUMENTOUTOFRANGEEXCEPTION;} };
template<> struct __InternalUtilsGetTypeID<System::ArgumentNullException*>			{ static u32 getIt() { return _TYPE_ARGUMENTNULLEXCEPTION;		} };
template<> struct __InternalUtilsGetTypeID<System::RankException*>					{ static u32 getIt() { return _TYPE_RANKEXCEPTION;				} };
template<> struct __InternalUtilsGetTypeID<System::InvalidOperationException*>		{ static u32 getIt() { return _TYPE_INVALIDOPERATIONEXCEPTION;	} };
template<> struct __InternalUtilsGetTypeID<System::ArrayTypeMismatchException*>		{ static u32 getIt() { return _TYPE_ARRAYTYPEMISMATCHEXCEPTION;	} };
template<> struct __InternalUtilsGetTypeID<System::ArithmeticException*>			{ static u32 getIt() { return _TYPE_ARITHMETICEXCEPTION;		} };
template<> struct __InternalUtilsGetTypeID<System::DivideByZeroException*>			{ static u32 getIt() { return _TYPE_DIVISIONBYZEROEXCEPTION;	} };
template<> struct __InternalUtilsGetTypeID<System::Collections::Generic::KeyNotFoundException*>	{ static u32 getIt() { return _TYPE_KEYNOTFOUNDEXCEPTION;		} };

template<class T>					struct __InternalUtilsGetTypeID<System::Array<T>*>										{ static u32 getIt() { return _TYPE_ARRAY;			} };
template<class T>					struct __InternalUtilsGetTypeID<System::Collections::Generic::List<T>*>					{ static u32 getIt() { return _TYPE_LIST;			} };
template<class TKey, class TValue>	struct __InternalUtilsGetTypeID<System::Collections::Generic::Dictionary<TKey,TValue>*> { static u32 getIt() { return _TYPE_DICTIONARY;		} };
#include "inline/__InternalUtilsGetTypeID_specializations.inl"

#endif
