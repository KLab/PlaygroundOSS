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

// Class and struct can have inner class/struct/interface
// They act as a kind of namespace.
// Support Interface inheritance mecanism
AbstractContainer::AbstractContainer()
:m_methods			(NULL)
,m_methodCount		(0)
,m_members			(NULL)
,m_memberCount		(0)
,m_accessors		(NULL)
,m_accessorCount	(0)
,m_pVariables		(NULL)
,m_modifier			(0)
,m_attribute		(NULL)
,m_inheritancesCount	(0)
,m_inheritances		(NULL)
,m_ancestor			(NULL)
,m_bCreateDefaultCtor	(false)
,m_bAsGCAbleMember		(true)
,m_cacheFullName	(NULL)
,m_operator			(0)
,m_genericParam		(NULL)
,m_ownerInner			(NULL)
,m_cppRepresentation	(NULL)
,m_csharpRepresentation	(NULL)
,m_referenceModifCount(0)
{
	m_bIsAbstract = true;
	gGlobalClassID++;
}

void AbstractContainer::setGenericParam() {
	m_genericParam = popGenericNameList();
}

TypeObject* AbstractContainer::getGenericType(TypeGenericDefinitionEntry* genericSymbol, TypeGenericEntry* genericParams) {
	if(m_genericParam) {
		TypeGenericDefinitionEntry * pDefGen = m_genericParam;
		TypeGenericEntry* pGen = genericParams;
		while(pGen && pDefGen && strcmp(pDefGen->m_genericName, genericSymbol->m_genericName)) {
			pDefGen = pDefGen->m_pNextGenericEntry;
			pGen = pGen->m_pNext;
		}
		if(!pDefGen && !pGen) {
			compilerError(ERR_INTERNAL, "Generic symbol was not found");
			return NULL;
		}
		if(!pDefGen || !pGen) {
			compilerError(ERR_INTERNAL, "Wrong number of generic parameters");
			return NULL;
		}
		return pGen->m_instanceType;
	}
	else {
		// Template definition => no instance
		return NULL;
	}
}

TypeObject* AbstractContainer::getType() {
	if (myType.m_typeID == TYPE_UNRESOLVED) {
		myType.m_definitionAC	= this;
		myType.m_isGC_Able		= ((this->m_modifier & (ATT_CLASS | ATT_INTERFACE)) != 0);
		myType.m_genreID		= EGENRE::_ABSTRACTCONTAINER;
		myType.m_name			= this->getName();
		myType.m_typeID			= (EnumTypeObject)this->m_uniqueId;
		myType.m_res.pSymbol	= this;
		myType.m_res.pType		= &myType;
		myType.m_res.symbolType	= EGENRE::_ABSTRACTCONTAINER;
	}
	return &myType;
}

void AbstractContainer::overrideType(TypeObject* pSolvedType) {
	myType.m_definitionAC	= this;
	myType.m_genreID		= pSolvedType->m_genreID;
	myType.m_isGC_Able		= pSolvedType->m_isGC_Able;
	myType.m_name			= pSolvedType->m_name;
	myType.m_res			= pSolvedType->m_res;
	myType.m_typeID			= pSolvedType->m_typeID;
}

AbstractContainer::~AbstractContainer() {
	delete[] m_inheritances;
	CLEAR(m_methods,m_methodCount);
	CLEAR(m_members,m_memberCount);
	CLEAR(m_accessors,m_accessorCount);
}

/*virtual*/
int AbstractContainer::getGenre() {
	return EGENRE::_ABSTRACTCONTAINER;
}

/*virtual*/
const char*	AbstractContainer::getName() {
	if(m_cppRepresentation) {
		// Nested
		return m_cppRepresentation->m_name;
	}
	else {
		return m_name;
	}
}

TypeObject*	AbstractContainer::getAncestor()
{
	NameSpace* nameSpaceContext = this->m_pParent;

	//
	// Use cached result to speed up, as resolution can be costly and getAncestor is called a lot.
	//
	if (!m_ancestor) {
		int search = 0;
		while (search < m_inheritancesCount) {
			TypeObject* pType = m_inheritances[search];
			pType->getResolvedType(nameSpaceContext);
			if (pType->m_definitionAC) {
				if (pType->m_definitionAC->m_modifier & (ATT_CLASS | ATT_STRUCT)) {	// Struct or Class but not interface.
					m_ancestor = pType;
					return pType;
				}
			}
			search++;
		}

		return NULL;
	} else {
		return m_ancestor;
	}
}

void AbstractContainer::addMethod			(Method*	pMethod) {
	EXPAND(m_methodCount, m_methods, pMethod);
	pMethod->m_pOwner = this;
}

void AbstractContainer::addMember			(Variable*	pMember) {
	EXPAND(m_memberCount, m_members, pMember);
	pMember->m_ownerClass = this;
}

void AbstractContainer::addAccessor			(Accessor*	pAccess) {
	EXPAND(m_accessorCount, m_accessors, pAccess);
	pAccess->m_ownerClass = this;
}

AbstractContainer*	AbstractContainer::addInheritance(TypeObject* type) {
	EXPAND(m_inheritancesCount, m_inheritances, type);
	return this;
}

void AbstractContainer::fixInheritance() {
	if (m_inheritancesCount == 0) {
		addInheritance(&t_OBJECT);
	}
}

Variable*			AbstractContainer::addVariable(Attribute* attribute, u32 modifier, TypeObject* type, Variable* variable) {
	// Member
	Variable* pVar = variable;
	while (pVar) {
		EXPAND(m_memberCount, m_members, pVar);
		pVar->setType(type);
		pVar->setModifier(modifier);
		pVar->setAttribute(attribute);
		pVar->m_ownerClass = this;
		pVar = pVar->m_pNextVariable;
	}
	return variable;
}

AbstractContainer*	AbstractContainer::addProperty(Attribute* attribute, u32 modifier, TypeObject* type, const char* name, Accessor* accessor) {
	for(int i = 0 ; i < strlen(name) ; i ++) {
		if(name[i] == '.') {
			compilerError(ERR_NOT_SUPPORTED_YET, "Explicit implementation of interfaces is not supported yet");
			break;
		}
	}
	bool hasEmptyGetter = accessor->m_get && accessor->m_get->m_statement == NULL;
	bool hasEmptySetter = accessor->m_set && accessor->m_set->m_statement == NULL;
	if((hasEmptyGetter || hasEmptySetter) && !(m_modifier & ATT_INTERFACE) && !(m_modifier & ATT_ABSTRACT)) {
		compilerError(ERR_NOT_SUPPORTED_YET, "Auto-properties are not supported");
	}
	accessor->setName(name);
	accessor->m_type		= type;
	accessor->m_attribute	= attribute;
	accessor->m_modifier	= modifier;
	accessor->m_ownerClass  = this;
	EXPAND(m_accessorCount, m_accessors, accessor);
	return this;
}

AbstractContainer*	AbstractContainer::addProperty(Attribute* attribute, u32 modifier, Accessor* indexer) {
	bool hasEmptyGetter = indexer->m_get && indexer->m_get->m_statement == NULL;
	bool hasEmptySetter = indexer->m_set && indexer->m_set->m_statement == NULL;
	if((hasEmptyGetter || hasEmptySetter) && !(m_modifier & ATT_INTERFACE)) {
		compilerError(ERR_NOT_SUPPORTED_YET, "Auto-properties are not supported");
	}
	indexer->m_attribute = attribute;
	indexer->m_modifier	= modifier | ATT_OPERATOR;
	indexer->m_ownerClass  = this;
	EXPAND(m_accessorCount, m_accessors, indexer);
	this->m_operator |= OPOVR_INDEXER;
	return this;
}

Method* AbstractContainer::addConstructor(Attribute* attribute, u32 modifier, const char* name, Variable* params, Statement* code, Expression* initializerOpt, s32 optType) {
	if(strcmp(m_name, name) != 0) {
		compilerError(ERR_INTERNAL, "The class and its constructor have different names");
	}
	Method* m = new Method();
	m->m_codeBlock	= code;
	m->m_parameters = params;
	m->setupHasDefaultParams();
	m->m_attribute	= attribute;
	m->m_modifier	= modifier | ATT_CTOR;
	m->setName(name);
	m->m_pOwner		= this;
	m->m_initializerOpt	= initializerOpt;
	m->m_initializerType = optType;
	EXPAND(m_methodCount, m_methods, m);
	return m;
}

Method* AbstractContainer::addDestructor(Attribute* attribute, u32 modifier, const char* name, Statement* code) {
	if(strcmp(m_name, name) != 0) {
		compilerError(ERR_INTERNAL, "The class and its destructor have different names");
	}
	Method* m = new Method();
	m->m_codeBlock	= code;
	m->m_attribute	= attribute;
	m->m_modifier	= modifier | ATT_DTOR;
	m->m_pOwner		= this;
	m->setName(name);
	EXPAND(m_methodCount, m_methods, m);
	return m;
}

Method* AbstractContainer::addMethod(Attribute* attribute, u32 modifier, const char* name, Variable* params, Statement* code, TypeObject* returnType) {
	for(int i = 0 ; i < strlen(name) ; i ++) {
		if(name[i] == '.') {
			compilerError(ERR_NOT_SUPPORTED_YET, "Explicit implementation of interfaces is not supported yet");
			break;
		}
	}
	Method* m = new Method();
	m->setName(name);
	m->m_returnType = returnType;
	m->m_codeBlock	= code;
	m->m_parameters = params;
	m->setupHasDefaultParams();
	m->m_attribute	= attribute;
	m->m_modifier	= modifier;
	m->m_pOwner		= this;
	EXPAND(m_methodCount, m_methods, m);
	return m;
}

//Finds a local member
Variable* AbstractContainer::findMember(const char* name)
{
	int n=0;
	while (n < this->m_memberCount) {
		Variable* pVar = this->m_members[n];
		if (strcmp(pVar->m_name,name)==0) {
			return pVar;
		}
		n++;
	}

	return NULL;
}

//Finds a local method
Method* AbstractContainer::findMethod(const char* name, Expression* signature, TypeGenericEntry* genParams)
{
	Method* ret = NULL;
	MethodList* overloadings = new MethodList();
	for(int n = 0 ; n < m_methodCount ; n++) {
		Method* pMethod = m_methods[n];
		if (strcmp(pMethod->m_name,name)==0) {
			// Resolve parameters.
			Variable* pParameter = pMethod->m_parameters;
			while(pParameter) {
				pParameter->m_type->m_res = pParameter->m_type->getResolvedType(this, pMethod);
				if(pParameter->m_expression) {
					// Resolve default value.
					// gCurrentMethod and gCurrentAC need to be updated as it can be an external context.
					Method*				oldCurrentMethod	= gCurrentMethod;
					AbstractContainer*	oldCurrentAC		= gCurrentAC;
					gCurrentMethod	=	pMethod;
					gCurrentAC		=	pMethod->m_pOwner;
					pParameter->m_expression->AnalysisAndTransform();
					gCurrentMethod	=	oldCurrentMethod;
					gCurrentAC		=	oldCurrentAC;
				}
				pParameter = pParameter->m_pNextVariable;
			}

			overloadings->add(pMethod);
			if((genParams != NULL) && (pMethod->m_genericParam == NULL)) {
				continue;
			}
			switch(compareSignatures(pMethod->m_parameters, signature)) {
			case EMATCH::M_IDENTICAL :
				return pMethod;
			case EMATCH::M_APPLICABLE :
				if(!ret || isBetterFunctionMember(pMethod->m_parameters, ret->m_parameters, signature)) {
					ret = pMethod;
				}
				break;
			case EMATCH::M_MISMATCH :
				break;
			default :
				compilerError(ERR_INTERNAL, "Unknown comparison result");
				break;
			}
		}
	}
	if(ret) {
		return ret;
	}
	else if(overloadings->m_count == 1) {
		return overloadings->m_method;
	}
	else if(overloadings->m_count > 0) {
		return overloadings;
	}
	else {
		return NULL;
	}
}

//Version for delegate signatures
Method* AbstractContainer::findMethod(const char* name, Variable* signature, TypeGenericEntry* genParams)
{
	Method* ret = NULL;
	MethodList* overloadings = new MethodList();
	for(int n = 0 ; n < m_methodCount ; n++) {
		Method* pMethod = m_methods[n];
		if (strcmp(pMethod->m_name,name)==0) {
			// Resolve parameters.
			Variable* pParameter = pMethod->m_parameters;
			while(pParameter) {
				pParameter->m_type->m_res = pParameter->m_type->getResolvedType(this, pMethod);
				if(pParameter->m_expression) {
					// Resolve default value.
					// gCurrentMethod and gCurrentAC need to be updated as it can be an external context.
					Method*				oldCurrentMethod	= gCurrentMethod;
					AbstractContainer*	oldCurrentAC		= gCurrentAC;
					gCurrentMethod	=	pMethod;
					gCurrentAC		=	pMethod->m_pOwner;
					pParameter->m_expression->AnalysisAndTransform();
					gCurrentMethod	=	oldCurrentMethod;
					gCurrentAC		=	oldCurrentAC;
				}
				pParameter = pParameter->m_pNextVariable;
			}
		
			overloadings->add(pMethod);
			if(genParams != NULL) {
				// TODO : use getGenericType()
			}
			switch(compareSignatures(pMethod->m_parameters, signature)) {
			case EMATCH::M_IDENTICAL :
				return pMethod;
			case EMATCH::M_APPLICABLE :
				if(!ret || isBetterFunctionMember(pMethod->m_parameters, ret->m_parameters, signature)) {
					ret = pMethod;
				}
				break;
			case EMATCH::M_MISMATCH :
				break;
			default :
				compilerError(ERR_INTERNAL, "Unknown comparison result");
				break;
			}
		}
	}
	if(ret) {
		return ret;
	}
	else if(overloadings->m_count == 1) {
		return overloadings->m_method;
	}
	else if(overloadings->m_count > 0) {
		return overloadings;
	}
	else {
		return NULL;
	}
}

Method* AbstractContainer::findDestructor()
{
	for(int n = 0 ; n < m_methodCount ; n++) {
		if(m_methods[n]->m_modifier & ATT_DTOR) {
			return m_methods[n];
		}
	}
	return NULL;
}

//Finds a local property
Accessor* AbstractContainer::findProperty(const char* name)
{
	int n=0;
	while (n < this->m_accessorCount) {
		Accessor* pProperty = this->m_accessors[n];
		if(pProperty->m_variable == NULL) {
			if (strcmp(pProperty->m_name,name)==0) {
				return pProperty;
			}
		}
		else {
			// Indexer accessors do not have a name
		}
		n++;
	}

	return NULL;
}

Accessor* AbstractContainer::findPropertyIndexer(Expression* solvedSignatureList) {
	for (int n=0; n < this->m_accessorCount; n++) {
		Accessor* pAcc = this->m_accessors[n];
		if ((pAcc->m_modifier & ATT_OPERATOR) != 0) {
			int count = 0;
			Variable* pVar = pAcc->m_variable;
			while (pVar) { count++; pVar = pVar->m_pNextVariable; }
			// TODO : differentiate only with parameter count, not with type !
			if (solvedSignatureList->m_expressionCount == count) {
				return pAcc;
			}
		}
	}
	return NULL;
}


AbstractContainer*	CreateInternal(Attribute* attribute, u32 modifier, const char* name) {
	// Find name in current name space ? --> Partial definition.
	NameSpace* fNewWorkingSpace = gCurrentNameSpace->findNameSpace(name);
	AbstractContainer* pCnt;
	if (!fNewWorkingSpace) {
		pCnt = new AbstractContainer();
		pCnt->m_attribute	= attribute;
		pCnt->m_modifier	= modifier;
		pCnt->m_noDump		= g_noDump;
		pCnt->setName(name);

		gCurrentNameSpace->addAbstractContainer(pCnt);

		if (gCurrentNameSpace->getGenre() == EGENRE::_ABSTRACTCONTAINER && ((modifier & ATTRB_ANONDELEGATE) == 0)) {
			// Create an unnested C++ equivalent
			pCnt->m_ownerInner = (AbstractContainer*)gCurrentNameSpace;
			
			AbstractContainer* pCntCpp = new AbstractContainer();
			char buff[1024];
			static int gInnerClassOut = 0;
			sprintf(buff,"%s_inner%i",name,gInnerClassOut++);
			pCntCpp->setName(buff);
			pCntCpp->m_csharpRepresentation	= pCnt;
			pCnt->m_cppRepresentation		= pCntCpp;

			pCntCpp->m_attribute	= attribute;
			pCntCpp->m_modifier		= modifier;
			pCntCpp->m_noDump		= g_noDump;

			NameSpace* pureNameSpace = gCurrentNameSpace;
			while (pureNameSpace->getGenre() == EGENRE::_ABSTRACTCONTAINER) {
				pureNameSpace = pureNameSpace->m_pParent;
			}

			pureNameSpace->addAbstractContainer(pCntCpp);
		}
	} else {
		// Previous class definition is reused.
		pCnt = (AbstractContainer*)fNewWorkingSpace;
	}

	PushSpace(gCurrentNameSpace);
	gCurrentNameSpace = pCnt;

	return pCnt;
}

AbstractContainer*	CreateClass	(Attribute* attribute, u32 modifier, const char* name) {
	return CreateInternal(attribute, modifier | ATT_CLASS, name);
}

AbstractContainer*	CreateStruct(Attribute* attribute, u32 modifier, const char* name) {
	return CreateInternal(attribute, modifier | ATT_STRUCT, name);
}

AbstractContainer*	CreateInterface(Attribute* attribute, u32 modifier, const char* name) {
	return CreateInternal(attribute, modifier | ATT_INTERFACE, name);
}
