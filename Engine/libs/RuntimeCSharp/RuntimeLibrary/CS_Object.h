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
#ifndef _CS_Object_
#define _CS_Object_

#include <setjmp.h>
#include <stdlib.h>
#include "../CompilerProject/BaseType.h"
#include "CS_Memory.h"

//----------------------------------------------------------------------------
// Standard Define
//

#define	memcpy32	memcpy
#define memcpy16	memcpy
#define memset16(dst, val, size)	{ u16 v = (u16)(val); u16* ptrStart = (u16*)(dst); u16* ptrEnd = &ptrStart[(size)>>1]; while (ptrStart != ptrEnd) { *ptrStart++ = v; } }
#define memset32(dst, val, size)	{ u32 v = (u32)(val); u32* ptrStart = (u32*)(dst); u32* ptrEnd = &ptrStart[(size)>>2]; while (ptrStart != ptrEnd) { *ptrStart++ = v; } }

#ifndef NULL
#define	NULL			(0)
#endif

// Heap checking (via crtdbg) is windows-only, so use it cautiously
#ifdef _WIN32
  #include <crtdbg.h>
  #define		CHECKMEM()			CS_Assert(_CrtCheckMemory(),"Heap Corrupted")
#else
  #define		CHECKMEM()			;
#endif

enum _CS_CLASS_TYPE {
	_TYPE_OBJECT						= ET_PREINSTALL	|	ET_CLASS			|	0xFFFF,
	_TYPE_ARRAY							= ET_PREINSTALL	|	ET_CLASS			|	0xFFFE,
	_TYPE_ABSTRACTARRAY					= ET_PREINSTALL	|	ET_CLASS			|	0xFFFD,
	_TYPE_STRING						= ET_PREINSTALL	|	ET_CLASS			|	0xFFFC,
	_TYPE_LIST							= ET_PREINSTALL	|	ET_CLASS			|	0xFFFB,
	_TYPE_DICTIONARY					= ET_PREINSTALL	|	ET_CLASS			|	0xFFFA,
	_TYPE_DELEGATE						= ET_PREINSTALL	|	ET_CLASS			|	0xFFF9,

	_TYPE_EXCEPTION						= ET_PREINSTALL	|	ET_CLASS			|	0xFF7F,
	_TYPE_SYSTEMEXCEPTION				= ET_PREINSTALL	|	ET_CLASS			|	0xFF7E,
	_TYPE_INDEXOUTOFRANGEEXCEPTION		= ET_PREINSTALL	|	ET_CLASS			|	0xFF7D,
	_TYPE_NULLEXCEPTION					= ET_PREINSTALL	|	ET_CLASS			|	0xFF7C,
	_TYPE_OUTOFMEMORYEXCEPTION			= ET_PREINSTALL	|	ET_CLASS			|	0xFF7B,
	_TYPE_ARGUMENTEXCEPTION				= ET_PREINSTALL	|	ET_CLASS			|	0xFF7A,
	_TYPE_ARGUMENTOUTOFRANGEEXCEPTION	= ET_PREINSTALL	|	ET_CLASS			|	0xFF79,
	_TYPE_ARGUMENTNULLEXCEPTION			= ET_PREINSTALL	|	ET_CLASS			|	0xFF78,
	_TYPE_RANKEXCEPTION					= ET_PREINSTALL	|	ET_CLASS			|	0xFF76,
	_TYPE_CPPNOTCOMPARABLEEXCEPTION		= ET_PREINSTALL	|	ET_CLASS			|	0xFF75,
	_TYPE_INVALIDOPERATIONEXCEPTION		= ET_PREINSTALL	|	ET_CLASS			|	0xFF74,
	_TYPE_ARRAYTYPEMISMATCHEXCEPTION	= ET_PREINSTALL	|	ET_CLASS			|	0xFF73,
	_TYPE_KEYNOTFOUNDEXCEPTION			= ET_PREINSTALL	|	ET_CLASS			|	0xFF72,
	_TYPE_ARITHMETICEXCEPTION			= ET_PREINSTALL	|	ET_CLASS			|	0xFF71,
	_TYPE_DIVISIONBYZEROEXCEPTION		= ET_PREINSTALL	|	ET_CLASS			|	0xFF70,
	_TYPE_CPPEXCEPTION					= ET_PREINSTALL	|	ET_CLASS			|	0xFF6F,
};

namespace System {

class String;

class __GCObject {
public:
	static const u32	INCOMPLETE	= 1;
	static const u32	COMPLETE	= 0;

	void* 	operator 	new		(std::size_t);
	void* 	operator 	new		(std::size_t, std::size_t);
	// No need, GC does the work : void  	operator 	delete	(void*);

	virtual
	void	_releaseGC	() { /* Do nothing */ }

	virtual	
	u32		_processGC	() = 0;

	virtual
	void	_move		(__GCObject* prevObj, __GCObject* newObj) { /* Do nothing */ }

	virtual 
	void	_moveAlert	(u32 offset) { /* Do nothing */ }

	void	_moveUpdate	(__GCObject* obj);

	void	_removeRef	(__GCObject** ptrOwner);
	void	_addRef		(__GCObject** ptrOwner);
	void	_moveRef	(__GCObject** oldPtr, __GCObject** newPtr);

	inline
	void	_addOwner	(__GCObject*  object) { _addRef((__GCObject**)((ptrAsInt)object | 0x1)); }
	void	_removeOwner(__GCObject*  object);
	void	_moveOwner	(__GCObject*  oldObj, __GCObject* newObj);

	inline
	void	_moveOwnerAsRef(__GCObject** oldRef, __GCObject** newRef) { _moveRef((__GCObject**)((ptrAsInt)oldRef | 0x1), ((__GCObject**)((ptrAsInt)newRef | 0x1))); };

	inline
	void	mark		() { SAllocHeader* pN = (SAllocHeader*)this; pN[-1].setMark(); }
	inline
	bool	isMarked	() { SAllocHeader* pN = (SAllocHeader*)this; return pN[-1].getMark(); }

	inline
	void	destroy		() { SAllocHeader* pN = (SAllocHeader*)this; pN[-1].setDestroyed(); }
	inline
	bool	isDestroyed	() { SAllocHeader* pN = (SAllocHeader*)this; return pN[-1].getDestroyed(); }

	inline
	bool	isFreed		() { SAllocHeader* pN = (SAllocHeader*)this; return pN[-1].getFreed(); }
	/**
		If allocator set object as NON FREE,
		we have two mode :
		m_ownerA != 0xFFFFFFFF
			m_ownerA is a pointer to a reference
			m_ownerB is a pointer to a reference
			Thus allowing to have a maximum of 2 references supported by default
		m_ownerA == 0xFFFFFFFF
			m_ownerA is a magic number.
			m_ownerB is a pointer to a LIST of references.
			Thus allowing to have an unlimited amount of references supported.

		If allocator set object as FREED,
			m_ownerA = next pointer in the link list of "die-list"
			m_ownerB = prev pointer in the link list of "die-list"
	 */
	__GCObject**	m_ownerA;
	__GCObject**	m_ownerB;

	static __GCObject*	_RefSetValue	(__GCObject** m_ptrOwner, __GCObject* object);
	static __GCObject*  _RefSetOwner	(__GCObject** m_ptrOwner, __GCObject* object);
	static __GCObject*& __registerByRef	(__GCObject*& ref);

	// Debug methods
	#ifdef _DEBUG_MEMORY_
		void _debug_displayReferences(u8 tabsNb = 0, u8 tabsOnFirstLine = 0);
	#endif
};

class __GCMalloc : public __GCObject {
public:
	static void* allocBlock(u32 byteCount, __GCMalloc*& wrapper);
	void*		 getBlock()		{ return &((u8*)this)[sizeof(__GCMalloc)];	}
	virtual	u32	 _processGC	()	{ return COMPLETE;							}
	virtual void _releaseGC	()	{ /* Do nothing */							}
};

class __GCStruct {
public:
	virtual	u32		_processGC	() = 0;
	virtual void*	_RefSetValue(void* newStruct) = 0;
	virtual void	_moveAlert	(u32 offset) = 0;		// Must be called after moving a struct to update its pointers' references.
	virtual void	_releaseGC	()	= 0;
};

/* 
	COMPILER TODO 
	1.Generate and called by destructor
	void _releaseGC() {
		...
		...
		if (m_memberA) { m_memberA->_removeRef(&m_memberA); }
		...
		...
		Memory::injectToDieList(this);
	}

	2.Call to _RefSetValue
*/


//----------------------------------------------------------------------------
// Object Class
//

	class String;
	class Type;

#define _INSTANCEOF(curr, base)	if (typeID == curr::_TYPEID) { return true; } else { return base::_isInstanceOf(typeID); }
#define _CLASSOF(curr, base)	if (typeID == curr::_TYPEID) { return true; } else { return base::_isClassOf(typeID); }

	class Object : public __GCObject
	{
	private:
		static const u32	_TYPEID = _TYPE_OBJECT;
	public:
		virtual bool	_isInstanceOf	(u32 typeID);
				bool 	_isInstanceOf$	(u32 typeID);
		static	bool	_isClassOf		(u32 typeID);
				bool	_isClassOf$		(u32 typeID);
		virtual	u32		_processGC		();
	public:
        Object();
		~Object();

		virtual	bool	Equals			(Object* obj);
				bool	Equals$			(Object* obj);
		static	bool	Equals			(Object* objA, Object* objB);
				bool	Equals$			(Object* objA, Object* objB);
		virtual s32		GetHashCode		();
				s32		GetHashCode$	();
		/*Type* GetType();	Not Supported for now, but should be in the future : allow data loader using reflection*/
		// This is NOT a correct definition, but it allows to use this method for debug in C#.
				String* GetType			();
				String* GetType$		();
		virtual s32		CompareTo		(Object* obj); // Implementation of IComparable
				s32		CompareTo$		(Object* obj); // Implementation of IComparable
		static	bool	ReferenceEquals	(Object* objA, Object* objB);
				bool	ReferenceEquals$(Object* objA, Object* objB);
		virtual String*	ToString		();
				String*	ToString$		();
	protected:
		
		/*Object* MemberwiseClone();	To Support ? */
	};
	
	typedef Object	object;
	typedef Object*	PObject;

	//
	// Exception macro and classes
	//

	//------------------------------------------------------------------------
	// Exception Mecanism V1.0
	// Based on the work from : http://www.di.unipi.it/~nids/docs/longjump_try_trow_catch.html
	// Added global exception stack, allowing to have THROW outside of
	// TRY function.
	//------------------------------------------------------------------------

	//
	// Stack of 100 try catch.
	//
	extern jmp_buf	_g_excStack[100];
	extern int		_g_excDepth;

	//
	// Macro to handle jump context stack.
	//
	#define POPEXC			(&System::_g_excStack[--System::_g_excDepth])
	#define PUSHEXC			(&System::_g_excStack[System::_g_excDepth++])
	#define DELEXC			(--System::_g_excDepth)

	//
	// Try-Catch-Finally-Throw creation macro.
	//
	// Minimum to use : 
	// TRY
	// CTRY
	// ETRY
	//
	// If using a CATCH, you must end it with a FINALLY
	//
	#define THROW(x)		longjmp(*POPEXC, (u32)x)
	#define TRY				{ jmp_buf* pBuf = PUSHEXC; System::Exception* exceptPtr = (System::Exception*)setjmp(*pBuf); if (exceptPtr == NULL) {
	#define CTRY			  DELEXC; } else {
	#define FIRSTCATCH(x,y)	    if (exceptPtr->_isInstanceOf(x::_TYPEID)) { x* y = (x*)exceptPtr;
	#define ELSECATCH(x,y)	    } else if (exceptPtr->_isInstanceOf(x::_TYPEID)) { x* y = (x*)exceptPtr;
	#define FINALLY			    }
	#define ETRY			} }
	
	#define CHCKTHIS		if (!this) { THROW(new System::NullReferenceException()); }
	#define THROWDIVZERO	THROW(new System::DivideByZeroException());

	class Exception : public Object {
	private:
		String* m_message;
	public:
		static const u32	_TYPEID = _TYPE_EXCEPTION;
	public:
		Exception();
		~Exception() { }
		Exception(String* msg);

		virtual bool	_isInstanceOf		(u32 typeID);
		bool			_isInstanceOf$		(u32 typeID);
		virtual	u32		_processGC			();
		virtual	void	_releaseGC			();
		virtual void	_moveAlert			(u32 offset);
		virtual String* ToString			();
		String*			ToString$			();
		String*			_acc_gMessage		();
		String*			_acc_gMessage$		();
		String*			_acc_gStackTrace	();
		String*			_acc_gStackTrace$	();
	};

	class SystemException : public Exception {
	public:
		static const u32	_TYPEID = _TYPE_SYSTEMEXCEPTION;
	public:
		SystemException						()							{ }
		~SystemException					()							{ }
		SystemException						(String* msg);

		virtual bool	_isInstanceOf		(u32 typeID);
		bool			_isInstanceOf$		(u32 typeID);
		virtual String* ToString			();
		String*			ToString$			();
	};

	class NullReferenceException : public SystemException {
	public:
		static const u32	_TYPEID = _TYPE_NULLEXCEPTION;
	public:
		NullReferenceException				()							{ }
		~NullReferenceException				()							{ }
		NullReferenceException				(String* msg);
		
		virtual bool	_isInstanceOf		(u32 typeID);
		bool			_isInstanceOf$		(u32 typeID);
		virtual String* ToString			();
		String*			ToString$			();
	};

	class IndexOutOfRangeException : public SystemException {
	public:
		static const u32	_TYPEID = _TYPE_INDEXOUTOFRANGEEXCEPTION;
	public:
		IndexOutOfRangeException			()							{ }
		~IndexOutOfRangeException			()							{ }
		IndexOutOfRangeException			(String* msg);
		
		virtual bool	_isInstanceOf		(u32 typeID);
		bool			_isInstanceOf$		(u32 typeID);
		virtual String* ToString			();
		String*			ToString$			();
	};

	class OutOfMemoryException : public SystemException {
	public:
		static const u32	_TYPEID = _TYPE_OUTOFMEMORYEXCEPTION;
	public:
		OutOfMemoryException				()							{ }
		~OutOfMemoryException				()							{ }
		OutOfMemoryException				(String* msg);
		
		virtual bool	_isInstanceOf		(u32 typeID);
		bool			_isInstanceOf$		(u32 typeID);
		virtual String* ToString			();
		String*			ToString$			();
	};

	class ArgumentException : public SystemException {
	public:
		static const u32	_TYPEID = _TYPE_ARGUMENTEXCEPTION;
	public:
		ArgumentException					()							{ }
		~ArgumentException					()							{ }
		ArgumentException					(String* msg);
		
		virtual bool	_isInstanceOf		(u32 typeID);
		bool			_isInstanceOf$		(u32 typeID);
		virtual String* ToString			();
		String*			ToString$			();
	};

	class ArgumentOutOfRangeException : public ArgumentException {
	public:
		static const u32	_TYPEID = _TYPE_ARGUMENTOUTOFRANGEEXCEPTION;
	public:
		ArgumentOutOfRangeException			()							{ }
		~ArgumentOutOfRangeException		()							{ }
		ArgumentOutOfRangeException			(String* msg);
		
		virtual bool	_isInstanceOf		(u32 typeID);
		bool			_isInstanceOf$		(u32 typeID);
		virtual String* ToString			();
		String*			ToString$			();
	};

	class ArgumentNullException : public ArgumentException {
	public:
		static const u32	_TYPEID = _TYPE_ARGUMENTNULLEXCEPTION;
	public:
		ArgumentNullException				()							{ }
		~ArgumentNullException				()							{ }
		ArgumentNullException				(String* msg);
		
		virtual bool	_isInstanceOf		(u32 typeID);
		bool			_isInstanceOf$		(u32 typeID);
		virtual String* ToString			();
		String*			ToString$			();
	};

	class RankException : public SystemException {
	public:
		static const u32	_TYPEID = _TYPE_RANKEXCEPTION;
	public:
		RankException						()							{ }
		~RankException						()							{ }
		RankException						(String* msg);
		
		virtual bool	_isInstanceOf		(u32 typeID);
		bool			_isInstanceOf$		(u32 typeID);
		virtual String* ToString			();
		String*			ToString$			();
	};

	class InvalidOperationException : public SystemException {
	public:
		static const u32	_TYPEID = _TYPE_INVALIDOPERATIONEXCEPTION;
	public:
		InvalidOperationException			()							{ }
		~InvalidOperationException			()							{ }
		InvalidOperationException			(String* msg);
		
		virtual bool	_isInstanceOf		(u32 typeID);
		bool			_isInstanceOf$		(u32 typeID);
		virtual String* ToString			();
		String*			ToString$			();
	};

	class ArrayTypeMismatchException : public SystemException {
	public:
		static const u32	_TYPEID = _TYPE_ARRAYTYPEMISMATCHEXCEPTION;
	public:
		ArrayTypeMismatchException			()							{ }
		~ArrayTypeMismatchException			()							{ }
		ArrayTypeMismatchException			(String* msg);
		
		virtual bool	_isInstanceOf		(u32 typeID);
		bool			_isInstanceOf$		(u32 typeID);
		virtual String* ToString			();
		String*			ToString$			();
	};

	class ArithmeticException : public SystemException {
	public:
		static const u32	_TYPEID = _TYPE_ARITHMETICEXCEPTION;
	public:
		ArithmeticException					()							{ }
		~ArithmeticException				()							{ }
		ArithmeticException					(String* msg);
		
		virtual bool	_isInstanceOf		(u32 typeID);
		bool			_isInstanceOf$		(u32 typeID);
		virtual String* ToString			();
		String*			ToString$			();
	};
	
	class DivideByZeroException : public ArithmeticException {
	public:
		static const u32	_TYPEID = _TYPE_DIVISIONBYZEROEXCEPTION;
	public:
		DivideByZeroException				()							{ }
		~DivideByZeroException				()							{ }
		DivideByZeroException				(String* msg);
		
		virtual bool	_isInstanceOf		(u32 typeID);
		bool			_isInstanceOf$		(u32 typeID);
		virtual String* ToString			();
		String*			ToString$			();
	};


	// Internal Exceptions

	class CppNotComparable : public SystemException {
	public:
		static const u32	_TYPEID = _TYPE_CPPNOTCOMPARABLEEXCEPTION;
	public:
		virtual bool _isInstanceOf(u32 typeID);
	};

	class CppException : public SystemException {
	public:
		static const u32	_TYPEID = _TYPE_CPPEXCEPTION;
	public:
		virtual bool _isInstanceOf(u32 typeID);
	};

	inline bool		Object::_isInstanceOf$	(u32 typeID)						{ CHCKTHIS; return _isInstanceOf(typeID);		}
	inline bool		Object::_isClassOf$		(u32 typeID)						{ CHCKTHIS; return _isClassOf(typeID);			}
	inline bool		Object::Equals$			(Object* obj)						{ CHCKTHIS; return Equals(obj);					}
	inline bool		Object::Equals$			(Object* objA, Object* objB)		{ CHCKTHIS; return Equals(objA, objB);			}
	inline s32		Object::GetHashCode$	()									{ CHCKTHIS; return GetHashCode();				}
	inline s32		Object::CompareTo$		(Object* obj)						{ CHCKTHIS; return CompareTo(obj);				}
	inline bool		Object::ReferenceEquals$(Object* objA, Object* objB)		{ CHCKTHIS; return ReferenceEquals(objA,objB);	}
	inline String*	Object::ToString$		()									{ CHCKTHIS; return ToString();					}
	inline String*	Object::GetType$		()									{ CHCKTHIS; return GetType();					}

	inline bool		Exception::_isInstanceOf$					(u32 typeID)	{ CHCKTHIS; return this->_isInstanceOf(typeID); }
	inline String*	Exception::ToString$						()				{ CHCKTHIS; return this->ToString();			}
	inline String*	Exception::_acc_gMessage$					()				{ CHCKTHIS; return this->_acc_gMessage();		}
	inline String*	Exception::_acc_gStackTrace$				()				{ CHCKTHIS; return this->_acc_gStackTrace();	}

	inline bool		SystemException::_isInstanceOf$				(u32 typeID)	{ CHCKTHIS; return this->_isInstanceOf(typeID); }
	inline String*	SystemException::ToString$					()				{ CHCKTHIS; return this->ToString();			}

	inline bool		IndexOutOfRangeException::_isInstanceOf$	(u32 typeID)	{ CHCKTHIS; return this->_isInstanceOf(typeID); }
	inline String*	IndexOutOfRangeException::ToString$			()				{ CHCKTHIS; return this->ToString();			}

	inline bool		NullReferenceException::_isInstanceOf$		(u32 typeID)	{ CHCKTHIS; return this->_isInstanceOf(typeID); }
	inline String*	NullReferenceException::ToString$			()				{ CHCKTHIS; return this->ToString();			}

	inline bool		OutOfMemoryException::_isInstanceOf$		(u32 typeID)	{ CHCKTHIS; return this->_isInstanceOf(typeID); }
	inline String*	OutOfMemoryException::ToString$				()				{ CHCKTHIS; return this->ToString();			}

	inline bool		ArgumentException::_isInstanceOf$			(u32 typeID)	{ CHCKTHIS; return this->_isInstanceOf(typeID); }
	inline String*	ArgumentException::ToString$				()				{ CHCKTHIS; return this->ToString();			}

	inline bool		ArgumentOutOfRangeException::_isInstanceOf$	(u32 typeID)	{ CHCKTHIS; return this->_isInstanceOf(typeID); }
	inline String*	ArgumentOutOfRangeException::ToString$		()				{ CHCKTHIS; return this->ToString();			}

	inline bool		ArgumentNullException::_isInstanceOf$		(u32 typeID)	{ CHCKTHIS; return this->_isInstanceOf(typeID); }
	inline String*	ArgumentNullException::ToString$			()				{ CHCKTHIS; return this->ToString();			}

	inline bool		RankException::_isInstanceOf$				(u32 typeID)	{ CHCKTHIS; return this->_isInstanceOf(typeID); }
	inline String*	RankException::ToString$					()				{ CHCKTHIS; return this->ToString();			}

	inline  bool	InvalidOperationException::_isInstanceOf$	(u32 typeID)	{ CHCKTHIS; return this->_isInstanceOf(typeID); }
	inline String*	InvalidOperationException::ToString$		()				{ CHCKTHIS; return this->ToString();			}

	inline bool		ArrayTypeMismatchException::_isInstanceOf$	(u32 typeID)	{ CHCKTHIS; return this->_isInstanceOf(typeID); }
	inline String*	ArrayTypeMismatchException::ToString$		()				{ CHCKTHIS; return this->ToString();			}

	inline bool		ArithmeticException::_isInstanceOf$			(u32 typeID)	{ CHCKTHIS; return this->_isInstanceOf(typeID); }
	inline String*	ArithmeticException::ToString$				()				{ CHCKTHIS; return this->ToString();			}

	inline bool		DivideByZeroException::_isInstanceOf$		(u32 typeID)	{ CHCKTHIS; return this->_isInstanceOf(typeID); }
	inline String*	DivideByZeroException::ToString$			()				{ CHCKTHIS; return this->ToString();			}


	void* _as_(Object* ptr, u32 classID);

}

#endif
