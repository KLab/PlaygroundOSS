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
#include "include.h"

int TypeGenericDefinitionEntry::getGenre() {
	return EGENRE::_GENDEFENTRY;
}

int TypeGenericDefinitionEntry::nbEntries() {
	int n = 0;
	TypeGenericDefinitionEntry* pEntry = this;
	while(pEntry) {
		pEntry = pEntry->m_pNextGenericEntry;
		n++;
	}
	return n;
}

TypeObject::TypeObject(EnumTypeObject defType)
:m_ranks		(NULL)
,m_rankCount	(0)
,m_ptrLevel		(0)
,m_originalType	(0)
,m_typeID		(defType)
,m_typeForCodeCache		(NULL)
,m_generic		(NULL)
,m_isGC_Able	(true)
,m_definitionNameSpace	(NULL)
,m_definitionAC			(NULL)
,m_definitionEnum		(NULL)
,m_definitionDelegate	(NULL)
,m_definitionGeneric	(NULL)
,m_genreID		(-1)
{
}

TypeObject::TypeObject()
:m_ranks		(NULL)
,m_rankCount	(0)
,m_ptrLevel		(0)
,m_originalType	(0)
,m_typeID		(TYPE_UNRESOLVED)
,m_typeForCodeCache	(NULL)
,m_generic		(NULL)
,m_isGC_Able	(true)
,m_definitionNameSpace	(NULL)
,m_definitionAC	(NULL)
,m_definitionEnum(NULL)
,m_definitionDelegate(NULL)
,m_definitionGeneric(NULL)
,m_genreID		(-1)
{
}

TypeObject::~TypeObject() {
	delete[] m_ranks;
}

// TYPE_UNRESOLVED	
TypeObject	t_SBYTE		(TYPE_SBYTE);
TypeObject	t_BYTE		(TYPE_BYTE);
TypeObject	t_SHORT		(TYPE_SHORT);
TypeObject	t_USHORT	(TYPE_USHORT);
TypeObject	t_INT		(TYPE_INT);
TypeObject	t_UINT		(TYPE_UINT);
TypeObject	t_LONG		(TYPE_LONG);
TypeObject	t_ULONG		(TYPE_ULONG);
TypeObject	t_CHAR		(TYPE_CHAR);
TypeObject	t_FLOAT		(TYPE_FLOAT);
TypeObject	t_DOUBLE	(TYPE_DOUBLE);
TypeObject	t_BOOL		(TYPE_BOOL);
TypeObject	t_OBJECT	(TYPE_OBJECT);
TypeObject	t_STRING	(TYPE_STRING);
TypeObject	t_VOID		(TYPE_VOID);
TypeObject	t_NULL		(TYPE_NULL);
TypeObject	t_INTPTR	(TYPE_INTPTR);
TypeObject	t_ARRAY		(TYPE_ARRAY);
TypeObject	t_DELEGATE	(TYPE_DELEGATE);

void initBaseType() {
	gGlobalClassID			= 0;
	t_SBYTE.m_isGC_Able		= false;

	t_BYTE.m_isGC_Able		= false;
	t_SHORT.m_isGC_Able		= false;
	t_USHORT.m_isGC_Able	= false;
	t_INT.m_isGC_Able		= false;
	t_UINT.m_isGC_Able		= false;
	t_LONG.m_isGC_Able		= false;
	t_ULONG.m_isGC_Able		= false;
	t_CHAR.m_isGC_Able		= false;
	t_FLOAT.m_isGC_Able		= false;
	t_DOUBLE.m_isGC_Able	= false;
	t_BOOL.m_isGC_Able		= false;
	t_INTPTR.m_isGC_Able	= false;
	/* TRUE BY DEFAULT
	t_OBJECT
	t_STRING	
	*/
	t_VOID.m_isGC_Able		= false;
	t_NULL.m_isGC_Able		= false;

	// Forbid the defined classes to be exported.
	g_noDump = true;

	useOrCreateNameSpace(NULL, "System");

	{
		AbstractContainer* pInt		= CreateClass(NULL, ATT_PUBLIC, "int");
		t_INT.m_res.pSymbol			= pInt;
		t_INT.m_name				= pInt->m_name;
		t_INT.m_res.symbolType		= EGENRE::_ABSTRACTCONTAINER;
		t_INT.m_genreID				= EGENRE::_ABSTRACTCONTAINER;
		t_INT.m_definitionAC		= pInt;
		pInt->overrideType(&t_INT);
		unuseNameSpace();
	}

	{
		AbstractContainer* pUInt		= CreateClass(NULL, ATT_PUBLIC, "uint");
		t_UINT.m_res.pSymbol		= pUInt;
		t_UINT.m_name				= pUInt->m_name;
		t_UINT.m_res.symbolType		= EGENRE::_ABSTRACTCONTAINER;
		t_UINT.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_UINT.m_definitionAC		= pUInt;
		pUInt->overrideType(&t_UINT);
		unuseNameSpace();
	}

	{
		AbstractContainer* pInt16	= CreateClass(NULL, ATT_PUBLIC, "short");
		t_SHORT.m_res.pSymbol		= pInt16;
		t_SHORT.m_name				= pInt16->m_name;
		t_SHORT.m_res.symbolType	= EGENRE::_ABSTRACTCONTAINER;
		t_SHORT.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_SHORT.m_definitionAC		= pInt16;
		pInt16->overrideType(&t_SHORT);
		unuseNameSpace();
	}

	{
		AbstractContainer* pUInt16	= CreateClass(NULL, ATT_PUBLIC, "ushort");
		t_USHORT.m_res.pSymbol		= pUInt16;
		t_USHORT.m_name				= pUInt16->m_name;
		t_USHORT.m_res.symbolType	= EGENRE::_ABSTRACTCONTAINER;
		t_USHORT.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_USHORT.m_definitionAC		= pUInt16;
		pUInt16->overrideType(&t_USHORT);
		unuseNameSpace();
	}

	{
		AbstractContainer* pInt8	= CreateClass(NULL, ATT_PUBLIC, "sbyte");
		t_SBYTE.m_res.pSymbol		= pInt8;
		t_SBYTE.m_name				= pInt8->m_name;
		t_SBYTE.m_res.symbolType	= EGENRE::_ABSTRACTCONTAINER;
		t_SBYTE.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_SBYTE.m_definitionAC		= pInt8;
		pInt8->overrideType(&t_SBYTE);
		unuseNameSpace();
	}

	{
		AbstractContainer* pUInt8	= CreateClass(NULL, ATT_PUBLIC, "byte");
		t_BYTE.m_res.pSymbol		= pUInt8;
		t_BYTE.m_name				= pUInt8->m_name;
		t_BYTE.m_res.symbolType		= EGENRE::_ABSTRACTCONTAINER;
		t_BYTE.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_BYTE.m_definitionAC		= pUInt8;
		pUInt8->overrideType(&t_BYTE);
		unuseNameSpace();
	}

	{
		AbstractContainer* pInt64	= CreateClass(NULL, ATT_PUBLIC, "long");
		t_LONG.m_res.pSymbol		= pInt64;
		t_LONG.m_name				= pInt64->m_name;
		t_LONG.m_res.symbolType		= EGENRE::_ABSTRACTCONTAINER;
		t_LONG.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_LONG.m_definitionAC		= pInt64;
		pInt64->overrideType(&t_LONG);
		unuseNameSpace();
	}

	{
		AbstractContainer* pUInt64	= CreateClass(NULL, ATT_PUBLIC, "ulong");
		t_ULONG.m_res.pSymbol		= pUInt64;
		t_ULONG.m_name				= pUInt64->m_name;
		t_ULONG.m_res.symbolType	= EGENRE::_ABSTRACTCONTAINER;
		t_ULONG.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_ULONG.m_definitionAC		= pUInt64;
		pUInt64->overrideType(&t_ULONG);
		unuseNameSpace();
	}

	{
		AbstractContainer* pFloat	= CreateClass(NULL, ATT_PUBLIC, "float");
		t_FLOAT.m_res.pSymbol		= pFloat;
		t_FLOAT.m_name				= pFloat->m_name;
		t_FLOAT.m_res.symbolType	= EGENRE::_ABSTRACTCONTAINER;
		t_FLOAT.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_FLOAT.m_definitionAC		= pFloat;
		pFloat->overrideType(&t_FLOAT);
		unuseNameSpace();
	}

	{
		AbstractContainer* pDouble	= CreateClass(NULL, ATT_PUBLIC, "double");
		t_DOUBLE.m_res.pSymbol		= pDouble;
		t_DOUBLE.m_name				= pDouble->m_name;
		t_DOUBLE.m_res.symbolType	= EGENRE::_ABSTRACTCONTAINER;
		t_DOUBLE.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_DOUBLE.m_definitionAC		= pDouble;
		pDouble->overrideType(&t_DOUBLE);
		unuseNameSpace();
	}

	{
		AbstractContainer* pChar	= CreateClass(NULL, ATT_PUBLIC, "char");
		t_CHAR.m_res.pSymbol		= pChar;
		t_CHAR.m_name				= pChar->m_name;
		t_CHAR.m_res.symbolType		= EGENRE::_ABSTRACTCONTAINER;
		t_CHAR.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_CHAR.m_definitionAC		= pChar;
		pChar->overrideType(&t_CHAR);
		unuseNameSpace();
	}

	{
		AbstractContainer* pBool	= CreateClass(NULL, ATT_PUBLIC, "bool");
		t_BOOL.m_res.pSymbol		= pBool;
		t_BOOL.m_name				= pBool->m_name;
		t_BOOL.m_res.symbolType		= EGENRE::_ABSTRACTCONTAINER;
		t_BOOL.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_BOOL.m_definitionAC		= pBool;
		pBool->overrideType(&t_BOOL);
		unuseNameSpace();
	}

	{
		AbstractContainer* pObject	= CreateClass(NULL, ATT_PUBLIC, "Object");
		t_OBJECT.m_res.pSymbol		= pObject;
		t_OBJECT.m_res.symbolType	= EGENRE::_ABSTRACTCONTAINER;
		t_OBJECT.m_name				= pObject->m_name;
		t_OBJECT.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_OBJECT.m_definitionAC		= pObject;
		t_OBJECT.m_typeID			= TYPE_OBJECT;
		pObject->m_uniqueId			= TYPE_OBJECT;
		pObject->overrideType(&t_OBJECT);
		unuseNameSpace();
	}

	{
		AbstractContainer* pString	= CreateClass(NULL, ATT_PUBLIC, "String");
		t_STRING.m_res.pSymbol		= pString;
		t_STRING.m_res.symbolType	= EGENRE::_ABSTRACTCONTAINER;
		t_STRING.m_name				= pString->m_name;
		t_STRING.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_STRING.m_typeID			= TYPE_STRING;
		t_STRING.m_definitionAC		= pString;
		pString->m_uniqueId			= TYPE_STRING;
		pString->overrideType(&t_STRING);
		unuseNameSpace();
	}

	{
		AbstractContainer* pArray	= CreateClass(NULL, ATT_PUBLIC, "Array");
		t_ARRAY.m_res.pSymbol		= pArray;
		t_ARRAY.m_res.symbolType	= EGENRE::_ABSTRACTCONTAINER;
		t_ARRAY.m_name				= pArray->m_name;
		t_ARRAY.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_ARRAY.m_typeID			= TYPE_ARRAY;
		t_ARRAY.m_definitionAC		= pArray;
		pArray->m_uniqueId			= TYPE_ARRAY;
		pArray->overrideType(&t_ARRAY);
		unuseNameSpace();
	}

	{
		AbstractContainer* pIntPtr	= CreateClass(NULL, ATT_PUBLIC, "IntPtr");
		t_INTPTR.m_res.pSymbol		= pIntPtr;
		t_INTPTR.m_res.symbolType	= EGENRE::_ABSTRACTCONTAINER;
		t_INTPTR.m_name				= pIntPtr->m_name;
		t_INTPTR.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_INTPTR.m_definitionAC		= pIntPtr;
		pIntPtr->m_bAsGCAbleMember	= false;
		pIntPtr->m_uniqueId			= TYPE_INTPTR;
		pIntPtr->overrideType(&t_INTPTR);
		unuseNameSpace();
	}

	{
		AbstractContainer* pDelegate	= CreateClass(NULL, ATT_PUBLIC, "Delegate");
		t_DELEGATE.m_res.pSymbol		= pDelegate;
		t_DELEGATE.m_res.symbolType		= EGENRE::_ABSTRACTCONTAINER;
		t_DELEGATE.m_name				= pDelegate->m_name;
		t_DELEGATE.m_genreID			= EGENRE::_ABSTRACTCONTAINER;
		t_DELEGATE.m_definitionAC		= pDelegate;
		pDelegate->m_uniqueId			= TYPE_DELEGATE;
		pDelegate->overrideType(&t_DELEGATE);
		unuseNameSpace();
	}

	unuseNameSpace(); // Pop "System"

	// Release the limitation.
	g_noDump = false;

	/*
	PushSpace(gCurrentNameSpace);
		gCurrentNameSpace = new NameSpace();
		gCurrentNameSpace->setName("System");

		// double
			// float
				// long
					// int
						// u16 / char
						// s16 
						// u8
						// s8
					// uint
						// u8
						// u16 / char
					// ulong
						// int again
							// [subs]
						// uint again
							// [subs]
		// bool

		AbstractContainer* pBool = CreateClass(NULL, ATT_PUBLIC, "Bool");
		pBool->overrideType(&t_BOOL);

		unuseNameSpace();

		AbstractContainer* pUInt = CreateClass(NULL, ATT_PUBLIC, "UInt32");
		pUInt->overrideType(&t_UINT);
		unuseNameSpace();

		AbstractContainer* pByte = CreateClass(NULL, ATT_PUBLIC, "Byte");	
		pByte->overrideType(&t_BYTE);
		unuseNameSpace();

		AbstractContainer* pSByte = CreateClass(NULL, ATT_PUBLIC, "SByte");	
		pSByte->overrideType(&t_SBYTE);
		unuseNameSpace();


		AbstractContainer* pInt16 = CreateClass(NULL, ATT_PUBLIC, "Int16");
		pInt16->overrideType(&t_SHORT);
		unuseNameSpace();

		AbstractContainer* pUInt16 = CreateClass(NULL, ATT_PUBLIC, "UInt16");
		pUInt16->overrideType(&t_USHORT);
		unuseNameSpace();

		AbstractContainer* pFloat = CreateClass(NULL, ATT_PUBLIC, "Single");	
		pFloat->overrideType(&t_FLOAT);
		unuseNameSpace();

		AbstractContainer* pDouble = CreateClass(NULL, ATT_PUBLIC, "Double");	
		pDouble->overrideType(&t_DOUBLE);
		unuseNameSpace();

		AbstractContainer* pInt64 = CreateClass(NULL, ATT_PUBLIC, "Int64");
		pInt64->overrideType(&t_LONG);
		unuseNameSpace();

		AbstractContainer* pUInt64 = CreateClass(NULL, ATT_PUBLIC, "UInt64");
		pInt64->overrideType(&t_ULONG);
		unuseNameSpace();

	PopSpace();
	*/
}

/* static */
TypeObject* TypeObject::getTypeObject(EnumTypeObject defType) {
	switch (defType) {
	case TYPE_SBYTE:	return &t_SBYTE;
	case TYPE_BYTE:		return &t_BYTE;
	case TYPE_SHORT:	return &t_SHORT;
	case TYPE_USHORT:	return &t_USHORT;
	case TYPE_CHAR:		return &t_CHAR;
	case TYPE_INT:		return &t_INT;
	case TYPE_UINT:		return &t_UINT;
	case TYPE_LONG:		return &t_LONG;
	case TYPE_ULONG:	return &t_ULONG;
	case TYPE_FLOAT:	return &t_FLOAT;
	case TYPE_DOUBLE:	return &t_DOUBLE;
	case TYPE_BOOL:		return &t_BOOL;
	case TYPE_OBJECT:	return &t_OBJECT;
	case TYPE_STRING:	return &t_STRING;
	case TYPE_VOID:		return &t_VOID;
	case TYPE_NULL:		return &t_NULL;
	case TYPE_INTPTR:	return &t_INTPTR;
	case TYPE_DELEGATE:	return &t_DELEGATE;
	default:			
		compilerError(ERR_INTERNAL,"Invalid type retrieval");
		return NULL;	// Generate a problem on purpose.
	}
}

/* static */
TypeObject* TypeObject::getTypeObject(const char* typeName, EnumTypeObject defType) {
	// Always unresolved for now.
	if (defType == TYPE_UNRESOLVED) {
		// Search in current name space first
		TypeObject* pType = new TypeObject(defType);
		pType->setName(typeName);
		return pType;
	}
	return NULL;
}
	
NameSpace* common(NameSpace* ref, NameSpace* nm) {
	NameSpace* obj0[50];
	NameSpace* obj1[50];
	int obj0Cnt = 0;
	int obj1Cnt = 0;

	NameSpace* p;
	p = ref;
	while (p) { obj0[obj0Cnt++] = p; p = p->m_pParent; }
	p = nm;
	while (p) { obj1[obj1Cnt++] = p; p = p->m_pParent; }

	NameSpace* result = NULL;
	while ((obj0Cnt > 0) && (obj1Cnt > 0) && (obj0[--obj0Cnt] == obj1[--obj1Cnt])) {
		result = obj0[obj0Cnt];
	}

	return result;
}

NameSpace* common(NameSpace* ref, Delegate* delegate_) {
	return common(ref, (NameSpace*)delegate_->getOwner());
}

NameSpace* common(NameSpace* ref, Enum* enum_) {
	return common(ref, enum_->m_parent);
}

/*virtual*/
const char* TypeObject::getFullName(NameSpace* ref) {
#ifdef __FULLNAMES__
	ref = gRootNameSpace;
#endif
	if (this->m_typeID == TYPE_UNRESOLVED) {
		getResolvedType(ref);
		if (this->m_typeID != TYPE_UNRESOLVED) {
			return getFullName(ref);
		} else {
			compilerError(ERR_INTERNAL,"Could not resolve.");
		}
	} else {
		if (m_definitionEnum)		{ return m_definitionEnum->getFullName(common(ref, m_definitionEnum));	}
		if (m_definitionAC)			{
			if (m_definitionAC->m_cppRepresentation) {
				return m_definitionAC->m_cppRepresentation->getFullName(common(ref, m_definitionAC->m_cppRepresentation));		
			} else {
				return m_definitionAC->getFullName(common(ref, m_definitionAC));		
			}
		}
		if (m_definitionDelegate)	{ return m_definitionDelegate->getFullName(common(ref, m_definitionDelegate)); }

		compilerError(ERR_INTERNAL,"Internal error : Trying to getFullName on a solved TypeObject but not enum or abstract container");
	}
	return NULL;
}

int isStdType(TypeObject* type) {
	int res = -1;
	if (type->m_typeID == t_BOOL.m_typeID)		{ res = 0;	}
	if (type->m_typeID == t_BYTE.m_typeID)		{ res = 1;	}
	if (type->m_typeID == t_SBYTE.m_typeID)		{ res = 2;	}
	if (type->m_typeID == t_USHORT.m_typeID)	{ res = 3;	}
	if (type->m_typeID == t_CHAR.m_typeID)		{ res = 3;	}
	if (type->m_typeID == t_SHORT.m_typeID)		{ res = 4;	}
	if (type->m_typeID == t_UINT.m_typeID)		{ res = 5;	}
	if (type->m_typeID == t_INT.m_typeID)		{ res = 6;	}
	if (type->m_typeID == t_ULONG.m_typeID)		{ res = 7;	}
	if (type->m_typeID == t_LONG.m_typeID)		{ res = 8;	}
	if (type->m_typeID == t_FLOAT.m_typeID)		{ res = 9;	}
	if (type->m_typeID == t_DOUBLE.m_typeID)	{ res = 10;	}
	if (type->m_typeID == t_STRING.m_typeID)	{ res = -2; }
	return res;
}

TypeObject* TypeObject::getResolvedBlend(TypeObject* other) {
	if(m_res.pSymbol == other->m_res.pSymbol) {
		// No blend
		return this;
	}
	if(m_typeID == TYPE_NULL) {
		return other;
	}
	if(other->m_typeID == TYPE_NULL) {
		return this;
	}
	//
	// - Signed over unsigned.
	// - Biggest over smallest.
	// - Filter all to be sure than only base type are compared.
	//
	int resThis		= isStdType(this);
	int resOther	= isStdType(other);
	if (resThis > -1 && resOther > -1) {
		int res = resThis > resOther ? resThis : resOther;
		switch (res) {
		case 0:	return &t_BOOL;
		case 1:	return &t_BYTE;
		case 2:	return &t_SBYTE;
		case 3:	return &t_USHORT;
		case 4:	return &t_SHORT;	
		case 5:	return &t_UINT;	
		case 6:	return &t_INT;		
		case 7:	return &t_ULONG;	
		case 8:	return &t_LONG;	
		case 9:	return &t_FLOAT;	
		case 10:return &t_DOUBLE;	
		default:
			compilerError(ERR_INTERNAL,"impossible case");
			return NULL;
		}
	} else {
		// Trick : operator with String always return a string ! So we ignore the other parameter.
		if (resThis == -2) {
			return &t_STRING;
		}
		compilerError(ERR_INTERNAL,"Expression used operator with unknown type");
		return NULL;
	}
}

SRSymbol TypeObject::getResolvedType(NameSpace* nameSpaceContext, Method* localMethod) {
	// Resolve generic parameters
	TypeGenericEntry* pGen = m_generic;
	while(pGen) {
		pGen->m_instanceType->getResolvedType(nameSpaceContext, localMethod);
		pGen->m_genericName = pGen->m_instanceType->dumpTypeForCode(nameSpaceContext, localMethod);
		pGen = pGen->m_pNext;
	}
	if(m_originalType) {
	// Resolve array sub type
		m_originalType->getResolvedType(nameSpaceContext, localMethod);
	}

	if (this->m_typeID == TYPE_UNRESOLVED) {
		if (this->m_originalType) {
			if (this->m_originalType->m_typeID == TYPE_UNRESOLVED) {
				this->m_originalType->getResolvedType(nameSpaceContext, localMethod);
			}

			m_genreID	= m_originalType->m_genreID;
			m_typeID	= m_originalType->m_typeID;
			m_res		= m_originalType->m_res;

			// Early return.
			return m_res;
		}

		Symbol* result;

		if(localMethod) {
			// First check whether the type is a local generic symbol.
			result = localMethod->findGenericSymbol(getName());
			if(!result) {
				if(nameSpaceContext != localMethod->m_pOwner &&
				// Special case (anonymous delegates)
				nameSpaceContext->m_pParent != localMethod->m_pOwner) {
					compilerError(ERR_INTERNAL, "The namespace context should be the class directly above the method");
				}
				result = nameSpaceContext->resolve(getName());
			}
		}
		else {
			result = nameSpaceContext->resolve(getName());
		}
		SRSymbol res;

		if (result) {
			switch (result->getGenre()) {
			case EGENRE::_ABSTRACTCONTAINER: // struct, class, interface
				this->m_definitionAC = (AbstractContainer*)result;
				this->m_isGC_Able    = ((this->m_definitionAC->m_modifier & (ATT_CLASS | ATT_INTERFACE)) != 0) && (this->m_definitionAC->m_bAsGCAbleMember);
				break;
			case EGENRE::_ENUM: // Enum
				this->m_isGC_Able      = false;
				this->m_definitionEnum = (Enum*)result;
				break;
			case EGENRE::_DELEGATE: // Delegate
				this->m_definitionDelegate = (Delegate*)result;
				break;
			case EGENRE::_NAMESPACE: // NameSpace
				this->m_definitionNameSpace = (NameSpace*)result;
			case EGENRE::_GENDEFENTRY: // Generic definition entry
				this->m_definitionGeneric = (TypeGenericDefinitionEntry*)result;
				break;
			default:
				compilerError(ERR_INTERNAL, "Undefined genre");
				res.symbolType = EGENRE::_UNDEFGENRE;
				return res;
			}
			m_genreID	= result->getGenre();
			m_typeID	= (EnumTypeObject)result->m_uniqueId;
			res.symbolType	= (EGENRE)m_genreID;
			res.pSymbol		= result;
			res.pType		= this;
			m_res = res;
			return res;
		} else {
			compilerError(ERR_USER, concat2(m_name," is not supported"));
			
			res.symbolType = EGENRE::_UNDEFGENRE;
			return res;
		}
	} else {
		return this->m_res;
	}
}

TypeObject* TypeObject::clone()
{
	TypeObject* pNew = new TypeObject(this->m_typeID);
	pNew->m_ptrLevel		= this->m_ptrLevel;
	pNew->m_generic			= this->m_generic;

	for (int n=0; n < this->m_rankCount; n++) {
		pNew->addRankInternal(this->m_ranks[n]);
	}
	return pNew;
}

TypeObject* TypeObject::addPointer() 
{
	TypeObject* pObj = this;
	if (this->m_typeID != TYPE_UNRESOLVED) {
		pObj = this->clone();
	}
	pObj->m_ptrLevel++; return pObj;
}

TypeGenericDefinitionEntry* gNameListEntry = NULL;

TypeGenericDefinitionEntry* popGenericNameList() {
	TypeGenericDefinitionEntry* result = gNameListEntry;
	gNameListEntry = NULL;
	return result;
}

void addGenericName(const char* name) {
	TypeGenericDefinitionEntry* pEntry = new TypeGenericDefinitionEntry();
	pEntry->m_genericName				= concat(name);
	pEntry->m_pNextGenericEntry	= NULL;
	if (gNameListEntry == NULL) {
		gNameListEntry = pEntry;
	} else {
		TypeGenericDefinitionEntry* pList = gNameListEntry;
		while (pList->m_pNextGenericEntry) {
			pList = pList->m_pNextGenericEntry;
		}
		pList->m_pNextGenericEntry = pEntry;
	}
}

TypeGenericEntry*	gListEntry = NULL;

void addGenericType(TypeObject* type) {
	TypeGenericEntry*	pEntry = new TypeGenericEntry();
	pEntry->m_genericName	= NULL;
	pEntry->m_instanceType	= type;
	pEntry->m_pNext			= NULL;
	if (gListEntry == NULL) {
		gListEntry = pEntry;
	} else {
		TypeGenericEntry* pList = gListEntry;
		while (pList->m_pNext) {
			pList = pList->m_pNext;
		}
		pList->m_pNext = pEntry;
	}
}

TypeGenericEntry* g_stackGenEntry[100];
int g_stackGenEntryCount = 0;
void PushGenericType(TypeGenericEntry* data) {
	g_stackGenEntry[g_stackGenEntryCount++] = data;
	gListEntry = NULL;
}

TypeGenericEntry* PopGenericType() {
	return gListEntry = g_stackGenEntry[--g_stackGenEntryCount];
}

TypeGenericEntry* GetGenericType() {
	TypeGenericEntry* result = gListEntry;
	gListEntry = NULL;
	return result;
}

TypeObject* TypeObject::setGeneric(TypeGenericEntry* genericList) {
	m_generic = genericList;
	return this;
}

TypeObject* TypeObject::createArrayType(int dimension) {
	TypeObject* newType = new TypeObject();
	newType->m_originalType = this;
	newType->m_rankCount	= 1;
	newType->m_ranks		= new TypeObject::SRank();
	newType->m_ranks->m_dimensionCount = dimension;

	AbstractContainer* array_ = t_ARRAY.m_definitionAC;
	newType->m_definitionAC	= array_;
	newType->m_isGC_Able	= true;
	newType->m_genreID		= EGENRE::_ABSTRACTCONTAINER;
	newType->m_name			= array_->getName();
	newType->m_typeID		= (EnumTypeObject)array_->m_uniqueId;
	newType->m_res.pSymbol	= array_;
	newType->m_res.pType	= newType;
	newType->m_res.symbolType	= EGENRE::_ABSTRACTCONTAINER;

	return newType;
}

void TypeObject::addRankInternal(SRank rank) {
	// Get old information.
	SRank* oldArray = m_ranks;
	int oldCount	= m_rankCount;

	// Allocate new array and copy old array into new array.
	SRank* newArray = new SRank[oldCount+1];
	if (oldArray) {
		memcpy(newArray,oldArray,oldCount * sizeof(void*));
	}

	// Add new element
	newArray[oldCount] = rank;
	m_rankCount++;

	// Delete old array
	if (oldArray) { delete[] oldArray; }

	m_ranks = newArray;
}

TypeObject* TypeObject::addRank(int dimensions)
{
	TypeObject* pObj = this;
	if (this->m_rankCount == 0) {
		pObj = createArrayType(dimensions);
	} else {
		pObj = this->clone();
		pObj->m_originalType = this;

		SRank rankV;
		rankV.m_dimensionCount = dimensions;
		pObj->addRankInternal(rankV);
	}

	return pObj;
}

const char* TypeObject::getGenParams() {
	char buff[500];
	buff[0] = 0;
	char* ptr = buff;

	if(m_generic) {
		sprintf(ptr++, "<");
		TypeGenericEntry* pGen = m_generic;
		do {
			ptr += sprintf(ptr, "%s%s", pGen->m_genericName, pGen->m_pNext ? ", " : "");
			pGen = pGen->m_pNext;
		} while(pGen);
		sprintf(ptr, ">");
	}
	return concat(buff);
}

const char* TypeObject::dumpTypeForCode(NameSpace* ctx, Method* localMethod) {
	// Trick : dump return type, if pointer is null -> void.
	if (this == NULL) { 
		return "void";
	}

	if (!ctx) {
		ctx = gRootNameSpace;
	}

	char buffA[500];
	char* ptr = buffA;
	for (int n=0; n < this->m_ptrLevel; n++) {
		int v = sprintf(ptr, "*");
		ptr += v;
	}

	if (this->m_originalType) {
		this->m_originalType->getResolvedType(ctx, localMethod);

		int v = sprintf(ptr,this->m_originalType->dumpTypeForCode(ctx, localMethod));
		ptr += v;
	} else {

		int v;

		this->getResolvedType(ctx, localMethod);

		switch (this->m_typeID) {
		case TYPE_SBYTE:	v = sprintf(ptr,"s8"); break;
		case TYPE_BYTE:		v = sprintf(ptr,"u8"); break;
		case TYPE_SHORT:	v = sprintf(ptr,"s16"); break;
		case TYPE_USHORT:	v = sprintf(ptr,"u16"); break;
		case TYPE_CHAR:		v = sprintf(ptr,"u16"); break;
		case TYPE_INT:		v = sprintf(ptr,"s32"); break;
		case TYPE_UINT:		v = sprintf(ptr,"u32"); break;
		case TYPE_LONG:		v = sprintf(ptr,"s64"); break;
		case TYPE_ULONG:	v = sprintf(ptr,"u64"); break;
		case TYPE_FLOAT:	v = sprintf(ptr,"float"); break;
		case TYPE_DOUBLE:	v = sprintf(ptr,"double"); break;
		case TYPE_BOOL:		v = sprintf(ptr,"bool"); break;
		case TYPE_OBJECT:	v = sprintf(ptr,"System::Object*"); break;
		case TYPE_STRING:	v = sprintf(ptr,"System::String*"); break;
		case TYPE_VOID:		v = sprintf(ptr,"void"); break;
		case TYPE_NULL:		v = sprintf(ptr,"NULL"); break;
		case TYPE_INTPTR:	v = sprintf(ptr,"s32*"); break;
		default:			
			switch (this->m_genreID) {
			case EGENRE::_ABSTRACTCONTAINER: // Interface / Class / Struct
				if (this->m_definitionAC->m_modifier & ATT_STRUCT) {
					v = sprintf(ptr,"%s%s",this->getFullName(ctx), getGenParams());
				} else {
					v = sprintf(ptr,"%s%s*",this->getFullName(ctx), getGenParams());
				}
				break;
			case EGENRE::_DELEGATE:
				// Delegate
				// Interface / Class
				v = sprintf(ptr,"%s*",this->getFullName(ctx));
				break;
			case EGENRE::_ENUM:
				// All the enum types are replaced with s32 to avoid dependency issues.
				v = sprintf(ptr,"%s",Enum::substitute());
				break;
			case EGENRE::_GENDEFENTRY:
				// Generic definition entry
				v = sprintf(ptr,"%s",this->m_name);
				break;
			default:
				compilerError(ERR_INTERNAL, "internal error");
				v = 0;
				break;
			}
		}

		ptr += v;
	}

	/*
	for (int n=0; n< this->m_rankCount; n++) {
		int v;
		v = sprintf(ptr,"["); ptr += v;
		for (int m=1; m < this->m_ranks[n].m_dimensionCount; m++) {
			v = sprintf(ptr,","); ptr += v;
		}
		v = sprintf(ptr,"]"); ptr += v;
	}*/
	if (this->isArray()) {
		// TODO : support rank count > 1
		if (this->m_rankCount == 1) {
			char buff2[500];
			sprintf(buff2, "System::Array<%s>*", buffA);
			m_typeForCodeCache = strdup(buff2);
		} else {
			return NULL;	// Force invalid type for unsupported type.
		}
	} else {
		m_typeForCodeCache = strdup(buffA);
	}
	return m_typeForCodeCache;
}

bool TypeObject::hasCompatibleGenerics(TypeObject* type, bool* out_identical) {
	bool compatible	= true;
	bool identical	= true;
	if(m_generic) {
		TypeGenericEntry* thisGen = m_generic;
		TypeGenericEntry* typeGen = type->m_generic;
		for(; thisGen && typeGen ; thisGen = thisGen->m_pNext, typeGen = typeGen->m_pNext) {
			if(typeGen->m_instanceType->m_genreID == EGENRE::_GENDEFENTRY) {
				identical = false;
			} else if(thisGen->m_instanceType->m_res.pSymbol == typeGen->m_instanceType->m_res.pSymbol
						&& thisGen->m_instanceType->hasCompatibleGenerics(typeGen->m_instanceType, &identical)) {
				continue;
			}
			else {
				compatible = false;
				break;
			}
		}
		if((thisGen != NULL) || (typeGen != NULL)) {
			compatible = false;
		}
	}
	else {
		compatible = (type->m_generic == NULL);
	}
	if(out_identical) {
		*out_identical = (compatible && identical);
	}
	return compatible;
}

// Returns true if the variable can be implicitly converted to the parameter type
// TODO : support user-defined implicit conversions
bool TypeObject::hasImplicitConversion(TypeObject* type) {
	u32 thisID = this->m_typeID;
	u32 typeID = type->m_typeID;
	if(thisID == TYPE_UNRESOLVED || typeID == TYPE_UNRESOLVED) {
		compilerError(ERR_INTERNAL, "Tried to match an unresolved type");
		return false;
	}
	if(type->m_genreID == EGENRE::_ENUM) {
		compilerError(ERR_INTERNAL, "Cannot test conversions to enum (the variable value is required)");
	}
	if(thisID == typeID) {
		if(thisID == TYPE_ARRAY) {
			if(this->m_originalType) {
				if(type->m_originalType) {
					return this->m_originalType->hasImplicitConversion(type->m_originalType);
				}
				return true;
			}
			return (type->m_originalType == NULL);
		}
		return this->hasCompatibleGenerics(type);
	}
	if(type->m_genreID == EGENRE::_GENDEFENTRY) {
		return true;
	}
	if(this->m_genreID == EGENRE::_GENDEFENTRY) {
		return false;
	}
	if(this->m_typeID == TYPE_NULL) {
		return type->isGC_Able();
	}
	if((thisID & ET_BASETYPE) || (typeID & ET_BASETYPE)) {
		if(!(thisID & ET_BASETYPE) || !(typeID & ET_BASETYPE)) {
			return (this->m_genreID == EGENRE::_ENUM);
		}
		switch(thisID) {
		case TYPE_SBYTE :
			return ((typeID & (TYPE_SHORT | TYPE_INT | TYPE_LONG | TYPE_FLOAT | TYPE_DOUBLE)) == typeID);
		case TYPE_BYTE :
			return ((typeID & (TYPE_SHORT | TYPE_USHORT | TYPE_INT | TYPE_UINT | TYPE_LONG | TYPE_ULONG | TYPE_FLOAT | TYPE_DOUBLE)) == typeID);
		case TYPE_SHORT :
			return ((typeID & (TYPE_INT | TYPE_LONG | TYPE_FLOAT | TYPE_DOUBLE)) == typeID);
		case TYPE_USHORT :
			return ((typeID & (TYPE_INT | TYPE_UINT | TYPE_LONG | TYPE_ULONG | TYPE_FLOAT | TYPE_DOUBLE)) == typeID);
		case TYPE_INT :
			return ((typeID & (TYPE_LONG | TYPE_FLOAT | TYPE_DOUBLE)) == typeID);
		case TYPE_UINT :
			return ((typeID & (TYPE_LONG | TYPE_ULONG | TYPE_FLOAT | TYPE_DOUBLE)) == typeID);
		case TYPE_LONG :
			return ((typeID & (TYPE_FLOAT | TYPE_DOUBLE)) == typeID);
		case TYPE_ULONG :
			return ((typeID & (TYPE_FLOAT | TYPE_DOUBLE)) == typeID);
		case TYPE_CHAR :
			return ((typeID & (TYPE_USHORT | TYPE_INT | TYPE_UINT | TYPE_LONG | TYPE_ULONG | TYPE_FLOAT | TYPE_DOUBLE)) == typeID);
		case TYPE_FLOAT :
			return (typeID == TYPE_DOUBLE);
		default :
			return false;
		}
	}
	if(this->m_genreID == EGENRE::_ENUMENTRY || type->m_genreID == EGENRE::_ENUMENTRY) {
		compilerError(ERR_INTERNAL, "Tested a conversion with an enum entry instead of an enum type");
		return false;
	}
	if(type->m_genreID == EGENRE::_ABSTRACTCONTAINER) {
		if(typeID == TYPE_DELEGATE) {
			// Special case : delegate type as a System.Delegate class type parameter
			if(this->m_genreID == EGENRE::_DELEGATE) {
				return true;
			}
			return false;
		}
		if(this->m_genreID != EGENRE::_ABSTRACTCONTAINER) {
			compilerError(ERR_INTERNAL, "Class type expected");
			return false;
		}
		AbstractContainer* pAC = (AbstractContainer*)this->m_definitionAC;
		for(int n = 0 ; n < pAC->m_inheritancesCount ; n++) {
			TypeObject* ancestorType = pAC->m_inheritances[n];
			ancestorType->getResolvedType(pAC);
			if(ancestorType->hasImplicitConversion(type)) {
				return true;
			}
		}
		return false;
	}
	if(type->m_genreID == EGENRE::_DELEGATE) {
		if(this->m_genreID == EGENRE::_METHOD) {
			return (compareSignatures(((Method*)this->m_res.pSymbol)->m_parameters, type->m_definitionDelegate->m_parameters) != EMATCH::M_MISMATCH);
		}
		return false;
	}

	compilerError(ERR_INTERNAL, "Unknown conversion test case");
	return false;
}

// Tells if conversion from type to type1 is better or worse than conversion from type to type2
ECOMPARISON	compareConversions(TypeObject* type, TypeObject* type1, TypeObject* type2) {
	if(type1->isAbstractArray() && type2->isAbstractArray()) {
		return ECOMPARISON::COMP_EQUIVALENT;
	}
	else if(type->isAbstractArray() && type1->isAbstractArray() || !type->isAbstractArray() && !type1->isAbstractArray() && type2->isAbstractArray()) {
		if(type->m_typeID != type1->m_typeID) {
			compilerError(ERR_INTERNAL, "Cannot compare impossible conversions");
		}
		return ECOMPARISON::COMP_BETTER;
	}
	else if(type->isAbstractArray() && type2->isAbstractArray() || !type->isAbstractArray() && !type2->isAbstractArray() && type1->isAbstractArray()) {
		if(type->m_typeID != type2->m_typeID) {
			compilerError(ERR_INTERNAL, "Cannot compare impossible conversions");
		}
		return ECOMPARISON::COMP_WORSE;
	}

	if(!type->hasImplicitConversion(type1) || !type->hasImplicitConversion(type2)) {
		compilerError(ERR_INTERNAL, "Cannot compare impossible conversions");
		return ECOMPARISON::COMP_EQUIVALENT;
	}
	u32 typeID1	= type1->m_typeID;
	u32 typeID2	= type2->m_typeID;
	u32 typeID	= type->m_typeID;
	if(typeID1 == typeID2) {
		if((typeID == typeID1) && (typeID == TYPE_ARRAY)) {
			return compareConversions(type->m_originalType, type1->m_originalType, type2->m_originalType);
		}
		bool identical;
		if(!type1->hasCompatibleGenerics(type2, &identical)) {
			compilerError(ERR_INTERNAL, "There are no implicit conversions between generic arguments");
		}
		if(identical) {
			return ECOMPARISON::COMP_EQUIVALENT;
		}
		return compareGenerics(type1, type2);
	}
	if(typeID == typeID1) {
		return ECOMPARISON::COMP_BETTER;
	}
	if(typeID == typeID2) {
		return ECOMPARISON::COMP_WORSE;
	}
	if(type1->hasImplicitConversion(type2) && !type2->hasImplicitConversion(type1)) {
		return ECOMPARISON::COMP_BETTER;
	}
	if(type2->hasImplicitConversion(type1) && !type1->hasImplicitConversion(type2)) {
		return ECOMPARISON::COMP_WORSE;
	}
	if((typeID1 & ET_BASETYPE) && (typeID2 & ET_BASETYPE)) {
		if((typeID1 == TYPE_SBYTE) && ((typeID2 & (TYPE_BYTE | TYPE_USHORT | TYPE_UINT | TYPE_ULONG)) == typeID2)) {
			return ECOMPARISON::COMP_BETTER;
		}
		if((typeID2 == TYPE_SBYTE) && ((typeID1 & (TYPE_BYTE | TYPE_USHORT | TYPE_UINT | TYPE_ULONG)) == typeID1)) {
			return ECOMPARISON::COMP_WORSE;
		}
		if((typeID1 == TYPE_SHORT) && ((typeID2 & (TYPE_USHORT | TYPE_UINT | TYPE_ULONG)) == typeID2)) {
			return ECOMPARISON::COMP_BETTER;
		}
		if((typeID2 == TYPE_SHORT) && ((typeID1 & (TYPE_USHORT | TYPE_UINT | TYPE_ULONG)) == typeID1)) {
			return ECOMPARISON::COMP_WORSE;
		}
		if((typeID1 == TYPE_INT) && ((typeID2 & (TYPE_UINT | TYPE_ULONG)) == typeID2)) {
			return ECOMPARISON::COMP_BETTER;
		}
		if((typeID2 == TYPE_INT) && ((typeID1 & (TYPE_UINT | TYPE_ULONG)) == typeID1)) {
			return ECOMPARISON::COMP_WORSE;
		}
		if((typeID1 == TYPE_LONG) && (typeID2 == TYPE_ULONG)) {
			return ECOMPARISON::COMP_BETTER;
		}
		if((typeID2 == TYPE_LONG) && (typeID1 == TYPE_ULONG)) {
			return ECOMPARISON::COMP_WORSE;
		}
	}
	return ECOMPARISON::COMP_EQUIVALENT;
}

// COMP_BETTER means that type1 is more specialised than type2
ECOMPARISON compareGenerics(TypeObject* type1, TypeObject* type2) {
	TypeGenericEntry* pGen1 = type1->m_generic;
	TypeGenericEntry* pGen2 = type2->m_generic;
	if(pGen1 == NULL) {
		if(pGen2 == NULL) {
			return ECOMPARISON::COMP_EQUIVALENT;
		}
		return ECOMPARISON::COMP_BETTER;
	}
	if(pGen2 == NULL) {
		return ECOMPARISON::COMP_WORSE;
	}
	
	ECOMPARISON res = ECOMPARISON::COMP_EQUIVALENT;

	for(; pGen1 && pGen2 ; pGen1 = pGen1->m_pNext, pGen2 = pGen2->m_pNext) {
		TypeObject* type1 = pGen1->m_instanceType;
		TypeObject* type2 = pGen2->m_instanceType;
		ECOMPARISON currentComparison;

		if(type1->m_genreID == EGENRE::_GENDEFENTRY) {
			if(type2->m_genreID == EGENRE::_GENDEFENTRY) {
				currentComparison = ECOMPARISON::COMP_EQUIVALENT;
			}
			else {
				currentComparison = ECOMPARISON::COMP_WORSE;
			}
		}
		else if(type2->m_genreID == EGENRE::_GENDEFENTRY) {
			currentComparison = ECOMPARISON::COMP_BETTER;
		}
		else {
			currentComparison = compareGenerics(type1, type2);
		}

		if(currentComparison == res || currentComparison == ECOMPARISON::COMP_EQUIVALENT) {
			continue;
		}
		else {
			if(res == ECOMPARISON::COMP_EQUIVALENT) {
				res = currentComparison;
			}
			else {
				return ECOMPARISON::COMP_EQUIVALENT;
			}
		}
	}

	if(pGen1 || pGen2) {
		compilerError(ERR_INTERNAL, "The number of argument does not match");
	}

	return res;
}

bool TypeObject::isAbstractArray() {
	return (this->m_typeID == TYPE_ARRAY && !this->m_originalType);
}
