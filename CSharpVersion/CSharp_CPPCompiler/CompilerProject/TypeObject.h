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
#ifndef TYPEOBJECT_H
#define TYPEOBJECT_H

#include "BaseType.h"

class TypeGenericDefinitionEntry : public Symbol {
public :
	const char*					m_genericName;
	TypeGenericDefinitionEntry*	m_pNextGenericEntry;

	virtual int getGenre();
	int			nbEntries();
};

struct TypeGenericEntry {
	const char*	m_genericName;		// Not solved until we solve the owner TypeObject
	TypeObject*	m_instanceType;		// Not solved until resolution.
	TypeGenericEntry*	m_pNext;
};

class TypeObject : public Symbol {
public:
	TypeObject();
	TypeObject(EnumTypeObject defType);
	~TypeObject();

	virtual int getGenre() { compilerError(ERR_INTERNAL,"Internal Error : never use TypeObject::getGenre() !"); return -1; }
	virtual const char* getFullName(NameSpace* ref);

	// Helper functions for parser
	static TypeObject* getTypeObject(EnumTypeObject defType);
	static TypeObject* getTypeObject(const char* typeName, EnumTypeObject defType);
	
	TypeObject* getResolvedBlend(TypeObject* other);
	TypeObject* setGeneric(TypeGenericEntry* listGeneric);
	TypeObject* clone();
	TypeObject* createArrayType(int dimension);
	TypeObject* addPointer	();
	TypeObject* addRank		(int rank);	// Null return this.
	TypeObject* addType		(TypeObject* type);
	const char*	getGenParams();
	const char* dumpTypeForCode(NameSpace* ctx, Method* localMethod = NULL);
	SRSymbol	getResolvedType(NameSpace* nameSpaceContext, Method* localMethod = NULL);
	bool		hasCompatibleGenerics(TypeObject* type, bool* out_identical = NULL);
	bool		hasImplicitConversion(TypeObject* type);
	bool		isArray		()	{ return m_rankCount >= 1; }
	TypeObject*	getArrayType();

	inline
	bool		isGC_Able	() { return m_isGC_Able; }

	bool	m_isGC_Able;
	EnumTypeObject	m_typeID;
	int				m_genreID;

	NameSpace*					m_definitionNameSpace;
	AbstractContainer*			m_definitionAC;
	Enum*						m_definitionEnum;
	Delegate*					m_definitionDelegate;
	TypeGenericDefinitionEntry*	m_definitionGeneric;
	SRSymbol					m_res;
	TypeObject*					m_originalType;

	struct SRank {
		int	m_dimensionCount;
	};
	SRank*	m_ranks;
	int		m_rankCount;
	int		m_ptrLevel;
	const char*	m_typeForCodeCache;

	TypeGenericEntry* m_generic;

	void addRankInternal(SRank rank);

	bool isAbstractArray();
};

void addGenericType(TypeObject* type);
TypeGenericEntry* GetGenericType();

ECOMPARISON	compareConversions(TypeObject* type, TypeObject* type1, TypeObject* type2);
ECOMPARISON compareGenerics(TypeObject* type1, TypeObject* type2);

#endif	//TYPEOBJECT_H
