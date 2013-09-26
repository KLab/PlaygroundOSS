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

NameSpace::NameSpace()
:m_pInner			(NULL)
,m_innerCount		(0)
,m_pChildSpace		(NULL)
,m_pNextSpace		(NULL)
,m_enums			(NULL)
,m_enumCount		(0)
,m_delegates		(NULL)
,m_delegateCount	(0)
,m_usingCount		(0)
,m_usings			(NULL)
,m_attribute		(NULL)
,m_pParent			(NULL)
,m_bIsAbstract		(false)
,m_noDump			(false)
{
}

int NameSpace::getGenre() { return EGENRE::_NAMESPACE; }

const char*	NameSpace::getFullName(NameSpace* ctx) {
#ifdef __FULLNAMES__
	ctx = gRootNameSpace;
#endif
	if(getGenre() == EGENRE::_ABSTRACTCONTAINER) {
		AbstractContainer* pAC = (AbstractContainer*)this;
		if(pAC->m_cppRepresentation) {
			return pAC->m_cppRepresentation->getFullName(ctx);
		}
	}

	char prefix[1000];
	char prefix2[1000];

	NameSpace* stack[50];
	int countNameSpace = 0;

	//
	// Compute full identifier
	//
	NameSpace* p = this;
	while (p) {
		if (p == ctx) {
			break;
		}
		stack[countNameSpace++] = p;
		p = p->m_pParent;
	}

	char* pSrc = prefix;
	char* pDst = prefix2;
	pSrc[0] = 0;
	pDst[0] = 0;
	if (countNameSpace) {
		while (countNameSpace) {
			countNameSpace--;
			if (!pSrc[0]) {
				sprintf(pDst, "%s", stack[countNameSpace]->getName());
			} else {
				sprintf(pDst, "%s::%s", pSrc, stack[countNameSpace]->getName());
			}

			char* swap = pSrc;
			pSrc = pDst;
			pDst = swap;
		}
		return strdup(pSrc);
	} else {
		if (ctx == this) {
			return m_name;
		} else {
			compilerError(ERR_INTERNAL, "no Common node but pointer is different !?");
			return NULL;
		}
	}
}

Delegate* NameSpace::addDelegate(Attribute* attribute, u32 modifier, TypeObject* type, const char* name, Variable* variable) {
	Delegate* d		= new Delegate();
	d->m_attribute	= attribute;
	d->m_modifier	= modifier;
	d->m_returnType	= type;
	d->setName(name);
	d->m_parameters	= variable;
	d->setupHasDefaultParams();
	d->m_pOwner		= (AbstractContainer*)this;
	EXPAND(m_delegateCount, m_delegates, d);

	if (this->getGenre() == EGENRE::_ABSTRACTCONTAINER) {
		// Create an unnested C++ equivalent		
		char buff[1024];
		static int gInnerClassOut = 0;
		sprintf(buff,"%s_inner%i",name,gInnerClassOut++);
		
		NameSpace* pureNameSpace = gCurrentNameSpace;
		while (pureNameSpace->getGenre() == EGENRE::_ABSTRACTCONTAINER) {
			pureNameSpace = pureNameSpace->m_pParent;
		}

		Delegate* dCpp = pureNameSpace->addDelegate(attribute, modifier, type, buff, variable);
		dCpp->m_csharpRepresentation	= d;
		d->m_cppRepresentation			= dCpp;
	}
	else if(g_registerClasses) {
		gClassDictionary->add(concat2(d->getFullName(gRootNameSpace), "*"), d->generateTypeID());
	}

	return d;
}

void NameSpace::addNameSpace(NameSpace* pNameSpace)
{
	// Update
	pNameSpace->m_pParent = this;

	// Link list
	if (m_pChildSpace) {
		NameSpace* p = m_pChildSpace;
		while (p->m_pNextSpace) {	p = p->m_pNextSpace;	}
		p->m_pNextSpace = pNameSpace;
	} else {
		m_pChildSpace = pNameSpace;
	}
}

Enum* NameSpace::addEnum(Attribute* pAttrib, u32 modifier, const char* name, TypeObject* type)
{
	Enum* pEnum = new Enum();
	pEnum->m_attribute	= pAttrib;
	pEnum->m_modifier	= modifier;
	pEnum->setName(name);
	pEnum->m_type		= type;
	pEnum->m_parent		= this;
	
	EXPAND(m_enumCount,m_enums,pEnum);

	return pEnum;
}

void NameSpace::addAbstractContainer(AbstractContainer* pCnt) {
	EXPAND(m_innerCount,m_pInner,pCnt);
	pCnt->m_pParent = this;
	if(g_registerClasses
		&& !pCnt->isSubSystem()
		&& !((pCnt->m_modifier & ATTRB_ANONDELEGATE) == ATTRB_ANONDELEGATE)
		&& (this->getGenre() != EGENRE::_ABSTRACTCONTAINER)
	) {
		gClassDictionary->add(concat2(pCnt->getFullName(gRootNameSpace), (pCnt->m_modifier & ATT_STRUCT) ? "" : "*"),
							  pCnt->generateTypeID());
	}
}

void NameSpace::addUsing(const char* using_) {
	for(int n = 0; n < m_usingCount ; n ++) {
		if(strcmp(m_usings[n], using_) == 0) {
			// The namespace already has this using
			return;
		}
	}
	EXPAND(m_usingCount,m_usings,using_);
}

NameSpace* NameSpace::setup(Attribute* attribute, const char* nameSpace) 
{
	this->m_attribute = attribute;
	this->setName(nameSpace);
	return this;
}

bool NameSpace::isSubSystem()
{
	NameSpace* lastParent = this;
	while(lastParent->m_pParent->m_name[0]) {
		lastParent = lastParent->m_pParent;
	}
	if(strcmp(lastParent->m_name, "System") == 0) {
		return true;
	}
	return false;
}

NameSpace* NameSpace::findNameSpace(const char* name)
{
	// Search in name space
	NameSpace* p = this->m_pChildSpace;
	while (p) {
		if (strcmp(p->m_name,name)==0) {
			return p;
		}
		p = p->m_pNextSpace;
	} 
	
	// Search in list of abstract container
	int n=0;
	while (n < this->m_innerCount) {
		AbstractContainer* p = this->m_pInner[n];
		if (strcmp(p->m_name,name)==0) {
			return p;
		}
		n++;
	}

	return NULL;
}

Enum* NameSpace::findEnum(const char* name)
{
	int n=0;
	while (n < this->m_enumCount) {
		Enum* pEnum = this->m_enums[n];
		if (strcmp(pEnum->m_name,name)==0) {
			return pEnum;
		}
		n++;
	}

	return NULL;
}

Delegate* NameSpace::findDelegate(const char* name) {
	int n=0;
	while (n < this->m_delegateCount) {
		Delegate* pDelegate = this->m_delegates[n];
		if (strcmp(pDelegate->m_name,name)==0) {
			return pDelegate;
		}
		n++;
	}

	return NULL;
}

//name is an atomic name, ie it does not compose several namespace/class names
//searchMask : do the nth search phase if the nth bit is set to 1
Symbol* NameSpace::findContext(const char* name, u8 searchMask, int iteration)
{
	if(iteration > 100)
	{
		compilerError(ERR_INTERNAL, "Maximum iteration number reached");
	}
	NameSpace* nameSpaceRes		= NULL;
	Enum* enumRes				= NULL;
	Symbol* symbolRes			= NULL;
	Delegate* delegateRes		= NULL;

	//note : the order is important

	// Step 1 : search in the local namespace
	if(searchMask & PHASE_LOCAL)
	{
		if(nameSpaceRes = findNameSpace(name)) {
			// if source namespace & target namespace visibility compatible.
			return nameSpaceRes;
		}
		if(enumRes = findEnum(name)) {
			// if source namespace & target namespace visibility compatible.
			return enumRes;
		}
		if (delegateRes = findDelegate(name)) {
			return delegateRes;
		}
		if(strcmp(m_name,name)==0) {
			// if source namespace & target namespace visibility compatible.
			return this;
		}
	}

	// Step 2 : search in the local generic symbols
	if((searchMask & PHASE_GENERIC) && (getGenre() == EGENRE::_ABSTRACTCONTAINER))
	{
		AbstractContainer* localAC = (AbstractContainer*)this;
		TypeGenericDefinitionEntry* pGen = localAC->m_genericParam;
		while(pGen) {
			if(strcmp(pGen->m_genericName, name) == 0) {
				return pGen;
			}
			pGen = pGen->m_pNextGenericEntry;
		}
	}

	// Step 3 : search in the mother class / interfaces
	if((searchMask & PHASE_INHERITANCE) && (getGenre() == EGENRE::_ABSTRACTCONTAINER))
	{
		AbstractContainer* localAC = (AbstractContainer*)this;
		int n=0;
		while (n < localAC->m_inheritancesCount) {
			TypeObject* parentType = localAC->m_inheritances[n];
			AbstractContainer* mother;
			if(parentType->m_definitionAC) {
				mother = parentType->m_definitionAC;
			}
			else {
				mother = (AbstractContainer*)this->resolve(localAC->m_inheritances[n]->m_name,PHASE_LOCAL | PHASE_USING | PHASE_HIERARCHY, iteration + 1);
			}
			symbolRes = mother->resolve(name,PHASE_LOCAL | PHASE_INHERITANCE, iteration + 1);
			if(symbolRes) {
				return symbolRes;
			}
			n++;
		}
	}

	// Step 4 : search in the usings
	if(searchMask & PHASE_USING)
	{
		//search in usings
		int n=0;
		while (n < this->m_usingCount) {
			const char* usingName = this->m_usings[n];
			NameSpace* usingNameSpace = (NameSpace*)resolve(usingName,PHASE_LOCAL | PHASE_HIERARCHY, iteration + 1);
			if(usingNameSpace) {	//The used namespace has been resolved, is supposed to be always true.
				symbolRes = usingNameSpace->findContext(name,PHASE_LOCAL,iteration + 1);
				if(symbolRes) {
					return symbolRes;
				}
			}
			n++;
		}
	}

	// Step 5 : search in the higher hierarchy
	if(searchMask & PHASE_HIERARCHY)
	{
		if(m_pParent)
		{
			symbolRes = m_pParent->resolve(name,PHASE_LOCAL | PHASE_INHERITANCE | PHASE_USING | PHASE_HIERARCHY, iteration + 1);
			if(symbolRes) {
				return symbolRes;
			}
		}
	}

	return NULL;
}

Symbol* NameSpace::resolve(const char* name, u8 searchMask, int iteration)
{
	if(iteration > 100)	{
		compilerError(ERR_INTERNAL, "Maximum iteration number reached");
		return NULL;
	}
	if (!this) {
		compilerError(ERR_INTERNAL, "Null NameSpace for resolve");
	}
	Symbol* pResult = NULL;
	NameSpace* pCurrNameSpace = this;
	StringList* splitList = split(name);
	while(splitList && pCurrNameSpace) {
		pResult = pCurrNameSpace->findContext(splitList->content, searchMask, iteration + 1);
		if(splitList = splitList->pNext) {
			searchMask = PHASE_LOCAL | PHASE_INHERITANCE;// (useless since the file is precompiled)
			pCurrNameSpace = (NameSpace*)pResult;
		}
	}
	if(iteration == 0 && !pResult)
	{
		char buf[100];
		sprintf(buf, "\"%s\" was not found", name);
		compilerError(ERR_INTERNAL, buf);
	}
	return pResult;
}