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
#ifndef _CS_String_
#define _CS_String_

#include "CS_Object.h"
#include "Collections/Generic/Generic.h"
#include "CS_Array.h"
#include "MarshallingUtils.h"

namespace System {

	class __MarshallingUtils;
/* Allocate string on buffer as long as we can...
	// Buffer full Failure occurs.
	//
	//	--> 1. Call for garbage collector.
	//	--> 2. Parse all the string in the list and force them to make a copy
	//  --> 3. Reset Buffer
	*/
	
	
/*
IFormatProvider*
CharEnumerator*
CultureInfo*
*/

	///
	/// StringGlobalAllocator is a huge uniChar buffer used to avoid using MALLOC for each String.
	///
	/// When the Warning Zone is reached, a garbage collection is done.
	///	Non garbage collectable Strings make a copy in their own buffer.
	///
	/// It must be initialized with the init(u32 bufferSize) method at the beginning of the program.
	/// A reasonnable size must be allocated to it in order not to have to detach String very often.
	/// The Warning Zone is defaulty 10% of the total allocator size.
	///
	/// 
	
	class _x_StringGlobalAllocator
	{
		friend class String;
	public:
		static bool		init(u32 bufferSize);
	private:
		static uniChar*	getStartPointer(u32 optionnalSize = 0);
		static uniChar*	getLimitPointer();
		static bool		closeString(String* pString, uniChar* end);
		static bool		compact();
		
		// ------------------------
		static uniChar*	s_pBuffer;
		static uniChar*	s_pLastBegin;
		static uniChar*	s_pWarningZone;
		static uniChar*	s_pBufferEnd;
		static String*	s_userList;
	#ifdef _DEBUG_STRING_
		static bool		s_isBuilding;
	#endif
	};

	enum Encoding 
	{
		// TODO.
	};

    enum StringSplitOptions
    {
        None						= 0,
        RemoveEmptyEntries			= 1,
    };

    enum StringComparison
    {
        CurrentCulture 				= 0,
        CurrentCultureIgnoreCase	= 1,
        InvariantCulture			= 2,
        InvariantCultureIgnoreCase	= 3,
        Ordinal						= 4,
        OrdinalIgnoreCase			= 5,
    };
	
    enum NormalizationForm
    {
        FormC						= 1,
        FormD						= 2,
        FormKC						= 5,
        FormKD						= 6,
	};

	///
	/// String
	/// C# Documentation : http://msdn.microsoft.com/en-us/library/system.string.aspx
	///
	///
    class String : public Object /*, IComparable, ICloneable, IConvertible, IComparable<string>, IEnumerable<char>, IEnumerable, IEquatable<string>*/
	{
		friend class _x_StringGlobalAllocator;
		friend class Object;
		friend class __MarshallingUtils;
	private:
		static const u32	_TYPEID = _TYPE_STRING;
	public:
		static	bool	init				();
		virtual bool	_isInstanceOf		(u32 typeID);
		inline	bool	_isInstanceOf$		(u32 typeID)			{ CHCKTHIS; return _isInstanceOf(typeID);	}
		virtual	u32		_processGC			();
		virtual	void	_releaseGC			();
		virtual void	_move				(__GCObject* prevobj, __GCObject* newobj);
		virtual void	_moveAlert			(u32 offset);
	private:
		// Link list of string using Allocator.
		String*			m_next;
		String*			m_prev;

		// Buffer
		const uniChar*	m_allocBuffer;		// For Alloc / Free
		__GCMalloc*		m_allocBufferObject;
		const uniChar*	m_stringBuffer;		// Pointer could be reduced after a split, trim etc...
		u32				m_stringOffset;		// Offset in m_stringBuffer IF AND ONLY IF m_stringBuffer belongs to another System::String (m_pBufferOwner)

		// Temporary list
		String*			m_tmpStringPtr;

		// Reference for GC
		String*			m_pBufferOwner;

		u32				m_length;
		bool			m_bNotOwnBuffer;
		
		// Internal Stuff.
	public: // TODO REMOVE "public:" (just for tests)
		~String										();
		bool			copyStringFromAllocator		();
		bool			disconnect					();
	public:

		String(bool bUseAllocator = true);
		String(const uniChar* buffer, u32 size); // You must NOT call _appendClose() with this Constructor.

		// String Builder.
		String* _appendStr	(String* pStr);
		String* _appendStr	(String* pStr, s32 startIndex, s32 length);
		String* _appendCte	(const uniChar* buffer, u32 size);
		String* _appendC	(uniChar c);
		String* _appendL	(s64	l);
		String* _appendUL	(u64	u);
		String* _appendI	(s32	i);
		String* _appendU	(u32	u);
		String* _appendS	(s16	s);
		String* _appendUS	(u16	u);
		String* _appendS8	(s8		s);
		String* _appendU8	(u8		u);
		String* _appendF	(float	f);
		String* _appendD	(double d);
		String* _appendB	(bool	b);
		String* _appendClose();

		String& operator+	(String&	pStr);
		String& operator+	(uniChar	c);
		String& operator+	(s64		l);
		String& operator+	(u64		u);
		String& operator+	(s32		i);
		String& operator+	(u32		u);
		String& operator+	(s16		s);
		String& operator+	(s8			s);
		String& operator+	(u8			u);
		String& operator+	(float		f);
		String& operator+	(double		d);
		String& operator+	(bool		b);

		const uniChar*	_getStringBuffer() const;

		static int	_leftSearch		(String* source, String* pattern, s32 startSearch, s32 searchCount);
		static int	_rightSearch	(String* source, String* pattern, s32 startSearch, s32 searchCount);
		static int	_leftSearchAny	(String* source, Array<uniChar>* any, s32 startSearch, s32 searchCount);
		static int	_rightSearchAny	(String* source, Array<uniChar>* any, s32 startSearch, s32 searchCount);

	public:
		static String* Empty;
		static const uniChar emptyStr = '\0';
		static String* _acc_gEmpty() { return Empty; }

/*NO*/	//String(const uniChar* value,	bool bUseAllocator = true);								// You must NOT call _appendClose() with this Constructor.
		String(Array<uniChar>* value,	bool bUseAllocator = true);								// You must NOT call _appendClose() with this Constructor.
/*NO*/	//String(sbyte* value,			bool bUseAllocator = true);								// You must NOT call _appendClose() with this Constructor.
		String(uniChar c, s32 count,	bool bUseAllocator = true);								// You must NOT call _appendClose() with this Constructor.
		String(const uniChar* value, s32 startIndex, s32 length);								// You must NOT call _appendClose() with this Constructor.
		String(Array<uniChar>* value, s32 startIndex, s32 length,	bool bUseAllocator = true);	// You must NOT call _appendClose() with this Constructor.
/*NO*/	//String(sbyte* value, s32 startIndex, s32 length,			bool bUseAllocator = true);	// You must NOT call _appendClose() with this Constructor.
/*xUTF8*/
		String(sbyte* value, s32 startIndex, s32 length, Encoding enc, bool bUseAllocator = false);

		s32				_acc_gLength			();
		inline s32		_acc_gLength$			()								{ CHCKTHIS; return _acc_gLength();	}

		// TODO $afe version.
		uniChar _idx_g(s32 index)												{ return m_stringBuffer[index];		}
		uniChar _idx_g$(s32 index)												{ CHCKTHIS; return _idx_g(index);	}

		const uniChar&			operator[]			(s32 index) const;
		inline bool				operator==			(String& b)					{ CHCKTHIS; return Equals(&b);		}
		inline bool				operator==			(Object& b)					{ CHCKTHIS; return Equals(&b);		}
		inline bool				operator!=			(String& b)					{ CHCKTHIS; return !(*this==b);		}
		inline bool				operator!=			(Object& b)					{ CHCKTHIS; return !(*this==b);		}

        static s32				Compare				(String* strA, String* strB);
        static s32				Compare				(String* strA, String* strB, bool ignoreCase);
        static String*			Concat				(Object* arg0);
        static String*			Concat				(/*params*/ Array<Object*>* args);
        static String*			Concat				(/*params*/ Array<String*>* values);
        static String*			Copy				(String* str);
        static bool				Equals				(String* a, String* b);
/*x*/	static bool				Equals				(String* a, String* b, StringComparison comparisonType);
/*x*/	static String*			Format				(String* format, Object* arg0);
/*x*/	static String*			Format				(String* format, /*params*/ Array<Object*>* args);
        static bool				IsNullOrEmpty		(String* value);
/*x*/	static bool				IsNullOrWhiteSpace	(String* value);
		static String*			Join				(String* separator, /*params*/ Array<String*>* value);
		static String*			Join				(String* separator, Array<String*>* value, s32 startIndex, s32 count);

		Object*					Clone				();
		inline Object*			Clone$				()																							{ CHCKTHIS; return Clone();									}
		s32						CompareTo			(Object* value);
		inline s32				CompareTo$			(Object* value)																				{ CHCKTHIS; return CompareTo(value);						}
		s32						CompareTo			(String* strB);
		inline s32				CompareTo$			(String* strB)																				{ CHCKTHIS; return CompareTo(strB);							}
		bool					Contains			(String* value);
		inline bool				Contains$			(String* value)																				{ CHCKTHIS; return Contains(value);							}
		void					CopyTo				(s32 sourceIndex, Array<uniChar>* destination, s32 destinationIndex, s32 count);
		inline void				CopyTo$				(s32 sourceIndex, Array<uniChar>* destination, s32 destinationIndex, s32 count)				{ CHCKTHIS; CopyTo(sourceIndex, destination, destinationIndex, count);	}
		bool					EndsWith			(String* value);
		inline bool				EndsWith$			(String* value)																				{ CHCKTHIS; return EndsWith(value);							}
		bool					Equals				(Object* obj);
		inline bool				Equals$				(Object* obj)																				{ CHCKTHIS; return Equals(obj);								}
		bool					Equals				(String* value);
		inline bool				Equals$				(String* value)																				{ CHCKTHIS; return Equals(value);							}
/*x*/	bool					Equals				(String* value, StringComparison comparisonType);
		Collections::Generic::IEnumerator<uniChar>*	
			                    GetEnumerator		();
		inline Collections::Generic:: IEnumerator<uniChar>* 
			                    GetEnumerator$      ()				                                                                            { CHCKTHIS; return GetEnumerator();	                        }
		s32						GetHashCode			();
		inline s32				GetHashCode$		()																							{ CHCKTHIS; return GetHashCode();							}
/*x*/	/*TypeCode GetTypeCode		();*/
		s32						IndexOf				(uniChar value);
		inline s32				IndexOf$			(uniChar value)																				{ CHCKTHIS; return IndexOf(value);							}
		s32						IndexOf				(String* value);
		inline s32				IndexOf$			(String* value)																				{ CHCKTHIS; return IndexOf(value);							}
		s32						IndexOf				(uniChar value, s32 startIndex);
		inline s32				IndexOf$			(uniChar value, s32 startIndex)																{ CHCKTHIS; return IndexOf(value, startIndex);				}
		s32						IndexOf				(String* value, s32 startIndex);
		inline s32				IndexOf$			(String* value, s32 startIndex)																{ CHCKTHIS; return IndexOf(value, startIndex);				}
		s32						IndexOf				(uniChar value, s32 startIndex, s32 count);
		inline s32				IndexOf$			(uniChar value, s32 startIndex, s32 count)													{ CHCKTHIS; return IndexOf(value, startIndex, count);		}
		s32						IndexOf				(String* value, s32 startIndex, s32 count);
		inline s32				IndexOf$			(String* value, s32 startIndex, s32 count)													{ CHCKTHIS; return IndexOf(value, startIndex, count);		}
		s32						IndexOfAny			(Array<uniChar>* anyOf);
		inline s32				IndexOfAny$			(Array<uniChar>* anyOf)																		{ CHCKTHIS; return IndexOfAny(anyOf);						}
		s32						IndexOfAny			(Array<uniChar>* anyOf, s32 startIndex);
		inline s32				IndexOfAny$			(Array<uniChar>* anyOf, s32 startIndex)														{ CHCKTHIS; return IndexOfAny(anyOf, startIndex);			}
		s32						IndexOfAny			(Array<uniChar>* anyOf, s32 startIndex, s32 count);
		inline s32				IndexOfAny$			(Array<uniChar>* anyOf, s32 startIndex, s32 count)											{ CHCKTHIS; return IndexOfAny(anyOf, startIndex, count);	}
		String*					Insert				(s32 startIndex, String* value);
		inline String*			Insert$				(s32 startIndex, String* value)																{ CHCKTHIS; return Insert(startIndex, value);				}
		s32						LastIndexOf			(uniChar value);
		inline s32				LastIndexOf$		(uniChar value)																				{ CHCKTHIS; return LastIndexOf(value);						}
		s32						LastIndexOf			(String* value);
		inline s32				LastIndexOf$		(String* value)																				{ CHCKTHIS; return LastIndexOf(value);						}
		s32						LastIndexOf			(uniChar value, s32 startIndex);
		inline s32				LastIndexOf$		(uniChar value, s32 startIndex)																{ CHCKTHIS; return LastIndexOf(value, startIndex);			}
		s32						LastIndexOf			(String* value, s32 startIndex);
		inline s32				LastIndexOf$		(String* value, s32 startIndex)																{ CHCKTHIS; return LastIndexOf(value, startIndex);			}
		s32						LastIndexOf			(uniChar value, s32 startIndex, s32 count);
		inline s32				LastIndexOf$		(uniChar value, s32 startIndex, s32 count)													{ CHCKTHIS; return LastIndexOf(value, startIndex, count);	}
		s32						LastIndexOf			(String* value, s32 startIndex, s32 count);
		inline s32				LastIndexOf$		(String* value, s32 startIndex, s32 count)													{ CHCKTHIS; return LastIndexOf(value, startIndex, count);	}
		s32						LastIndexOfAny		(Array<uniChar>* anyOf);
		inline s32				LastIndexOfAny$		(Array<uniChar>* anyOf)																		{ CHCKTHIS; return LastIndexOfAny(anyOf);					}
		s32						LastIndexOfAny		(Array<uniChar>* anyOf, s32 startIndex);
		inline s32				LastIndexOfAny$		(Array<uniChar>* anyOf, s32 startIndex)														{ CHCKTHIS; return LastIndexOfAny(anyOf, startIndex);		}
		s32						LastIndexOfAny		(Array<uniChar>* anyOf, s32 startIndex, s32 count);
		inline s32				LastIndexOfAny$		(Array<uniChar>* anyOf, s32 startIndex, s32 count)											{ CHCKTHIS; return LastIndexOfAny(anyOf, startIndex, count);	}
		String*					PadLeft				(s32 totalWidth, uniChar paddingChar = ' ');
		inline String*			PadLeft$			(s32 totalWidth, uniChar paddingChar = ' ')													{ CHCKTHIS; return PadLeft(totalWidth, paddingChar);		}
		String*					PadRight			(s32 totalWidth, uniChar paddingChar = ' ');
		inline String*			PadRight$			(s32 totalWidth, uniChar paddingChar = ' ')													{ CHCKTHIS; return PadRight(totalWidth, paddingChar);		}
		String*					Remove				(s32 startIndex);
		inline String*			Remove$				(s32 startIndex)																			{ CHCKTHIS; return Remove(startIndex);						}
		String*					Remove				(s32 startIndex, s32 count);
		inline String*			Remove$				(s32 startIndex, s32 count)																	{ CHCKTHIS; return Remove(startIndex, count);				}
		String*					Replace				(uniChar oldChar, uniChar newChar);
		inline String*			Replace$			(uniChar oldChar, uniChar newChar)															{ CHCKTHIS; return Replace(oldChar, newChar);				}
		String*					Replace				(String* oldValue, String* newValue);
		inline String*			Replace$			(String* oldValue, String* newValue)														{ CHCKTHIS; return Replace(oldValue, newValue);				}
		Array<String*>*			Split				(Array<uniChar>* separator, StringSplitOptions options);
		inline Array<String*>*	Split$				(Array<uniChar>* separator, StringSplitOptions options)										{ CHCKTHIS; return Split(separator, options);				}
		Array<String*>*			Split				(Array<String*>* separator, StringSplitOptions options);
		inline Array<String*>*	Split$				(Array<String*>* separator, StringSplitOptions options)										{ CHCKTHIS; return Split(separator, options);				}
		Array<String*>*			Split				(Array<uniChar>* separator, s32 count = 0xffff, StringSplitOptions options = None);
		inline Array<String*>*	Split$				(Array<uniChar>* separator, s32 count = 0xffff, StringSplitOptions options = None)		{ CHCKTHIS; return Split(separator, count, options);		}
		Array<String*>*			Split				(Array<String*>* separator, s32 count, StringSplitOptions options);
		inline Array<String*>*	Split$				(Array<String*>* separator, s32 count, StringSplitOptions options)							{ CHCKTHIS; return Split(separator, count, options);		}
		bool					StartsWith			(String* value);
		inline bool				StartsWith$			(String* value)																				{ CHCKTHIS; return StartsWith(value);						}
		String*					Substring			(s32 startIndex);
		inline String*			Substring$			(s32 startIndex)																			{ CHCKTHIS; return Substring(startIndex);					}
		String*					Substring			(s32 startIndex, s32 length);
		inline String*			Substring$			(s32 startIndex, s32 length)																{ CHCKTHIS; return Substring(startIndex, length);			}
		Array<uniChar>*			ToCharArray			();
		inline Array<uniChar>*	ToCharArray$		()																							{ CHCKTHIS; return ToCharArray();							}
		Array<uniChar>*			ToCharArray			(s32 startIndex, s32 length);
		inline Array<uniChar>*	ToCharArray$		(s32 startIndex, s32 length)																{ CHCKTHIS; return ToCharArray(startIndex, length);			}
		String*					ToLower				();
		inline String*			ToLower$			()																							{ CHCKTHIS; return ToLower();								}
		virtual String*			ToString			();
		inline String*			ToString$			()																							{ CHCKTHIS; return ToString();								}
		String*					ToUpper				();
		inline String*			ToUpper$			()																							{ CHCKTHIS; return ToUpper();								}
		String*					Trim				(/*params*/ Array<uniChar>* trimChars = NULL);
		inline String*			Trim$				(/*params*/ Array<uniChar>* trimChars = NULL)												{ CHCKTHIS; return Trim(trimChars);							}
		String*					TrimEnd				(/*params*/ Array<uniChar>* trimChars = NULL);
		inline String*			TrimEnd$			(/*params*/ Array<uniChar>* trimChars = NULL)												{ CHCKTHIS; return TrimEnd(trimChars);						}
		String*					TrimStart			(/*params*/ Array<uniChar>* trimChars = NULL);
		inline String*			TrimStart$			(/*params*/ Array<uniChar>* trimChars = NULL)												{ CHCKTHIS; return TrimStart(trimChars);					}

	public:
		inline static const char*	_toCStr			(String* str)			{ if(!str) { return NULL; } return str->_toCStr();	}
		const char*					_toCStr			();
		inline const char*			_toCStr$		()						{ CHCKTHIS; return this->_toCStr();					}

	private:
		class CharEnumerator : public Collections::Generic::IEnumerator<uniChar> {
		private:
			String* m_str;
			s32 m_nextIndex;
		public:
			CharEnumerator(String* str);
			uniChar _acc_gCurrent();
			bool MoveNext();
			void Dispose();
		};
	};

	class AnyToString {
/*x*/	static String ToString	(int    value);	
/*x*/	static String ToString	(float	value);
/*x*/	static String ToString	(uint	value);
/*x*/	static String ToString	(bool	value);
/*x*/	static String ToString	(long	value);
/*x*/	static String ToString	(double value);
/*x*/	static String ToString	(byte	value);
/*x*/	static String ToString	(sbyte	value);
/*x*/	static String ToString	(short	value);
/*x*/	static String ToString	(uniChar value);
	};
}

#endif
