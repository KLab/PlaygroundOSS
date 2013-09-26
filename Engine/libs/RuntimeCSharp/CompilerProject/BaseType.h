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
#ifndef BASETYPE_H
#define BASETYPE_H

#include <string>
#include <iostream>

#pragma warning( disable : 4996 )
#pragma warning( disable : 4482 )

#define EXPAND(count,arr,item)	expand(&count,(void***)&arr,(void*)item)

#define CLEAR(a,b)		for (int n=0; n < b; n++) {\
							delete a[n];\
						} delete[] a; b	= 0; a = NULL


#include "assert_klb.h"
#define CS_Assert(cond,msg,...)		klb_assert(cond, msg, __VA_ARGS__)
#define CS_AssertAlways(msg,...)	klb_assertAlways(msg, __VA_ARGS__)


// -----------------------------------------------------------------------
// Global Types
// -----------------------------------------------------------------------
typedef int					s32;
typedef unsigned int		u32;
typedef short				s16;
typedef unsigned short		u16;
typedef char				s8;
typedef unsigned char		u8;
typedef long long           s64;
typedef unsigned long long  u64;
typedef unsigned int		ptrAsInt;
typedef u16					uniChar;
typedef	u32					uint;
typedef u8					byte;
typedef s8					sbyte;
#ifndef NULL
	#define NULL			(0)
#endif

// -----------------------------------------------------------------------
//  Classes used by the compiler to describe all the item in the C# Language.
// -----------------------------------------------------------------------
/** Base class for all named symbol **/
class SymbolDictionnary;
class Symbol;
class AbstractContainer;	// Struct, Class, Interface use same holder to simplify implementation.
class Accessor;
class Attribute;
class Argument;
class Enum;
class Method;
class NameSpace;
class Uses;
class TypeObject;
class Expression;
class Statement;
class Variable;
class Indexer;
class Delegate;

enum EGENRE {
	_UNDEFGENRE			= 0,
	_ABSTRACTCONTAINER	= 0x0001,
	_DELEGATE			= 0x0002,
	_ENUM				= 0x0004,
	_MEMBER				= 0x0008,
	_VARIABLE			= 0x0010,
	_METHOD				= 0x0020,
	_ACCESSOR			= 0x0040,
	_STATEMENT			= 0x0080,
	_NAMESPACE			= 0x0100,
	_ENUMENTRY			= 0x0200,
	_GENDEFENTRY		= 0x0400,
	_METHODLIST			= 0x0800,
};

struct SRSymbol {
	Symbol*		pSymbol;
	EGENRE		symbolType;
	TypeObject*	pType;

	void dump(bool assignSide);
};

struct StringID {
	int			m_id;
	const char*	m_str;
	StringID*	m_next;
	bool		m_isDumped;
};

struct SValue {
	SValue();

	union {
		double				d;
		float				f;
		s64					l;
		u64					ul;
		s32					i;
		u32					ui;
		const char*			str;
		void*				ptr;
	} v;
	int type;
	int strLen;
	StringID* pString;

	static int		operatorType(SValue& a, SValue& b);
	SValue	ToType		(int type);
};

// -----------------------------------------------------------------------
//	Defined Type used by the compiler for :
//	- Differenciate type within an abstract container
//  - Differenciate user type from predefined type
//  - Native type from instances of objets/ref
// -----------------------------------------------------------------------

const u32	ET_CLASS		= 0x01000000;
const u32	ET_INTERFACE	= 0x02000000;
const u32	ET_STRUCT		= 0x03000000;

const u32	ET_COMPLEXMASK	= 0x0000FFFF;
const u32	ET_INFOMASK		= 0x00F00000;
const u32	ET_PRIMITIVEMASK= 0xFF000000;

const u32	ET_USERSPACE	= 0x00800000;
const u32	_TYPE_USEROBJECT= ET_USERSPACE;
const u32	ET_PREINSTALL	= 0x00400000;
const u32	ET_ARRAY		= 0x00200000;

const u32	ET_BASETYPE		= 0x80000000;
const u32	ET_SIGNEDTYPE	= 0x40000000;
const u32	ET_NUMBER		= 0x20000000;
const u32	ET_POINTER		= 0x10000000;

const u32	ET_SIZE_1		= 1;
const u32	ET_SIZE_2		= 2;
const u32	ET_SIZE_4		= 4;
const u32	ET_SIZE_8		= 8;

const u32	ET_VOID			= ET_BASETYPE	| 0;
const u32	ET_BOOL			= ET_BASETYPE	| 0x11;
const u32	ET_NULL			= ET_BASETYPE	| 0x12;
const u32	ET_INTPTR		= ET_BASETYPE	| 0x13;
const u32	ET_INT8			= ET_BASETYPE	| ET_SIGNEDTYPE	|	ET_SIZE_1;
const u32	ET_INT16		= ET_BASETYPE	| ET_SIGNEDTYPE	|	ET_SIZE_2;
const u32	ET_INT32		= ET_BASETYPE	| ET_SIGNEDTYPE	|	ET_SIZE_4;
const u32	ET_INT64		= ET_BASETYPE	| ET_SIGNEDTYPE	|	ET_SIZE_8;
const u32	ET_UINT8		= ET_BASETYPE	|					ET_SIZE_1;
const u32	ET_UINT16		= ET_BASETYPE	|					ET_SIZE_2;
const u32	ET_UINT32		= ET_BASETYPE	|					ET_SIZE_4;
const u32	ET_UINT64		= ET_BASETYPE	|					ET_SIZE_8;
const u32	ET_CHAR			= ET_UINT16		| 0x20; // Just to make sure that CHAR and UINT16 have actually a unique code.
const u32	ET_FLOAT		= ET_BASETYPE	| ET_NUMBER		|	ET_SIZE_4;
const u32	ET_DOUBLE		= ET_BASETYPE	| ET_NUMBER		|	ET_SIZE_8;

//
// Standard Types
//
enum EnumTypeObject {
	TYPE_UNRESOLVED		= 0x7FFFFFFF,
	TYPE_UNDEFINED		= TYPE_UNRESOLVED,
	TYPE_SBYTE			= ET_INT8,
	TYPE_BYTE			= ET_UINT8,
	TYPE_SHORT			= ET_INT16,
	TYPE_USHORT			= ET_UINT16,
	TYPE_INT			= ET_INT32,
	TYPE_UINT			= ET_UINT32,
	TYPE_LONG			= ET_INT64,
	TYPE_ULONG			= ET_UINT64,
	TYPE_CHAR			= ET_CHAR,
	TYPE_FLOAT			= ET_FLOAT,
	TYPE_DOUBLE			= ET_DOUBLE,
	TYPE_BOOL			= ET_BOOL,
	TYPE_OBJECT			= ET_CLASS | ET_PREINSTALL | 0xFFFF,	// Object	is 0xFFFF
	TYPE_STRING			= ET_CLASS | ET_PREINSTALL | 0xFFFC,	// String	is 0xFFFC
	TYPE_ARRAY			= ET_CLASS | ET_PREINSTALL | 0xFFFB,	// Array	is 0xFFFB
	TYPE_DELEGATE		= ET_CLASS | ET_PREINSTALL | 0xFFFA,	// Delegate	is 0xFFFA
	TYPE_VOID			= ET_VOID,
	TYPE_INTPTR			= ET_INTPTR,
	TYPE_NULL			= ET_NULL	// Only in constant int type.
};


//
// Standard Attributes
//
enum EATTRIBUTE {
	ATT_STATIC		= 0x00000001,
	ATT_PUBLIC		= 0x00000002,
	ATT_PRIVATE		= 0x00000004,
	ATT_PROTECTED	= 0x00000008,
	ATT_INTERNAL	= 0x00000010,
	ATT_UNSAFE		= 0x00000020,
	ATT_VIRTUAL		= 0x00000040,
	ATT_FINAL		= 0x00000080,
	ATT_NATIVE		= 0x00000100,
	ATT_ABSTRACT	= 0x00000200,
	ATT_OPERATOR	= 0x00000400,
	ATT_READONLY	= 0x00000800,
	ATT_VOLATILE	= 0x00001000,
	ATT_CTOR		= 0x00002000,
	ATT_DTOR		= 0x00004000,
	ATT_NEW			= 0x00008000,
	ATT_CONST		= 0x00010000,	// Same as read only ?
	ATT_SEALED		= 0x00000080,	// Same as FINAL
	ATT_EXTERN		= 0x00020000,
	ATT_PARTIAL		= 0x00000400,	// Same as OPERATOR but no conflict : use only for class/interface/struct.

	ATTR_NEW		= 0x00040000,
	// Attribute type
	ATTRB_ASSEMBLY	= 0x80000000,
	ATTRB_ANONDELEGATE	= 0x40000000,	// Same as FIELD.
	ATTRB_FIELD		= 0x40000000,
	ATTRB_EVENT		= 0x20000000,
	ATTRB_METHOD	= 0x10000000,
	ATTRB_MODULE	= 0x08000000,
	ATTRB_PARAM		= 0x04000000,
	ATTRB_PROPERTY	= 0x02000000,
	ATTRB_RETURN	= 0x01000000,
	ATTRB_TYPE		= 0x00800000,

	// Attribute for param.
	ATT_REF			= 0x00400000,
	ATT_OUT			= 0x00200000,

	ATT_CLASS		= 0x00100000,
	ATT_STRUCT		= 0x00080000,
	ATT_INTERFACE	= 0x00040000,	// Same as new.
};

//
// All possible expression AST type.
//
enum EnumExpressionType {
	// Multiple
	EXPR_LIST,
	EXPR_LIST_INIT,

	// Create a delegate code, class definition, etc...
	EXPR_DELEGATECREATE,

	// Leaf
	EXPR_THIS,
	EXPR_TYPEOF,	// + Type
	EXPR_BASE,
	EXPR_CTE,
	EXPR_IDENT,

	// Single
	EXPR_REF,
	EXPR_PLUSPLUS,
	EXPR_MINUSMINUS,
	EXPR_ARROW,		// + Id
	EXPR_NOT,		// !
	EXPR_LNOT,		// ~
	EXPR_ADRESSOF,
	EXPR_SIZEOF,	// + Type
	EXPR_PREINCR,
	EXPR_PREDECR,
	EXPR_UNARYPLUS,
	EXPR_UNARYMINUS,
	EXPR_UNARYMULT,
	EXPR_IS,
	EXPR_AS,
	EXPR_UNCHECKED,
	EXPR_CHECKED,

	// Double & Single
	EXPR_ACCESS,	// + Expr|Id
	EXPR_NEW,		// + Type
	
	// Double
	EXPR_DOT,
	EXPR_INVOKE,
	EXPR_CAST,
	EXPR_CAST_PTR,
	EXPR_MULT,
	EXPR_DIV,
	EXPR_MOD,
	EXPR_PLUS,
	EXPR_MINUS,
	EXPR_LSHFT,
	EXPR_RSHFT,
	EXPR_LESS,
	EXPR_MORE,
	EXPR_LESSEQ,
	EXPR_MOREEQ,
	EXPR_EQUTST,
	EXPR_DIFFTST,
	EXPR_LAND,
	EXPR_LXOR,
	EXPR_LOR,
	EXPR_AND,
	EXPR_OR,
	EXPR_XOR,
	
	// Double (Assignment)
	EXPR_ASS_EQ,
	EXPR_ASS_PLUSEQ,
	EXPR_ASS_MINUSEQ,
	EXPR_ASS_STAREQ,
	EXPR_ASS_DIVEQ,
	EXPR_ASS_MODEQ,
	EXPR_ASS_XOREQ,
	EXPR_ASS_ANDEQ,
	EXPR_ASS_OREQ,
	EXPR_ASS_RSHFTEQ,
	EXPR_ASS_LSHFTEQ,
	
	// Triple
	EXPR_COND,
	
};

enum EnumStatementType {
	STM_UNDEFINED,

	STM_BLOCK,
	STM_NILWRAPPER,	// Empty expression.
	STM_NULL,
	STM_LABEL,
	STM_LOCALVAR,
	STM_LOCAL_PERVAR,
	STM_WRAP_EXP,
	STM_ASSIGN_EXPR,
	STM_WRAPPER_POSTINCR,
	STM_WRAPPER_POSTDECR,
	STM_WRAPPER_PREINCR,
	STM_WRAPPER_PREDECR,
	STM_IF,
	STM_SWITCH,
	STM_CASE,
	STM_CASEDEFAULT,
	STM_UNSAFE,
	STM_WHILE,
	STM_DOWHILE,
	STM_FOR,
	STM_FOREACH,
	STM_BREAK,
	STM_CONTINUE,
	STM_GOTO,
	STM_GOTOCASE,
	STM_GOTODEFAULT,
	STM_RETURN,
	STM_THROW,
	STM_TRY,
	STM_CATCH,
	STM_FINALLY,
	STM_CHECKED,
	STM_UNCHECKED,
	STM_LOCK,
	STM_USING,
};

enum EOVEROP {
	OP_PLUS,
	OP_MINUS,
	OP_LNOT,
	OP_NOT,
	OP_PLUSPLUS,
	OP_MINUSMINUS,
	OP_TRUE,
	OP_FALSE,
	OP_MULT,
	OP_DIV,
	OP_MOD,
	OP_AND,
	OP_OR,
	OP_XOR,
	OP_LSHFT,
	OP_RSHFT,
	OP_EQUAL,
	OP_DIFF,
	OP_MORE,
	OP_LESS,
	OP_MOREEQ,
	OP_LESSEQ,
};

enum ECOMPARISON {
	COMP_BETTER,
	COMP_EQUIVALENT,
	COMP_WORSE,
};

enum EMATCH {
	M_IDENTICAL, 
	M_APPLICABLE,
	M_MISMATCH,
};

// -----------------------------------------------------------------------
// Compiler Specific Define & Functions
// -----------------------------------------------------------------------
#define ERR_TODO			(0000)
#define	UNSUPPORTED			(0001)
#define ERR_INVALID_CHAR	(0002)

// Compiler options
const u32	COMPIL_USE_FRAMEWORK	= 0x00000001;
const u32	COMPIL_IS_FRAMEWORK		= 0x00000002;

void compilerError(int err, const char* format, ...);
void expand(int* count, void*** array_, void* newEntry);

#endif	//BASETYPE_H
