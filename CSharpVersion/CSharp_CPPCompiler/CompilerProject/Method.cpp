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

Method::Method()
:Symbol()
,m_attribute		(NULL)
,m_parameters		(NULL)
,m_returnType		(NULL)
,m_codeBlock		(NULL)
,m_pOwner			(NULL)
,m_modifier			(0)
,m_referenceModifCount	(0)
,m_initializerOpt	(NULL)
,m_initializerType	(-1)
,m_genericParam		(NULL)
,m_bResolvedParam	(true)
{
}

int Method::getGenre() {
	return EGENRE::_METHOD;
}

const char* Method::getName() {
	if(((m_modifier & (ATT_CTOR | ATT_DTOR)) != 0) && m_pOwner->m_cppRepresentation) {
		return m_pOwner->m_cppRepresentation->m_name;
	}
	return m_name;
}

void Method::setupHasDefaultParams() {
	//
	// Setup unresolved flag if default expression is associated with variables.
	//
	Variable* p = m_parameters;
	while (p) {
		if (p->m_expression) {
			m_bResolvedParam = false;
			break;
		}
		p = p->m_pNextVariable;
	}
}

void Method::resolveDefaultParams() {
	if (m_bResolvedParam == false) {
		AbstractContainer* backup = gCurrentAC;
		gCurrentAC = this->m_pOwner;
		Variable* p = m_parameters;
		while (p) {
			if (p->m_expression) {
				p->m_expression->AnalysisAndTransform();
			}
			p = p->m_pNextVariable;
		}
		m_bResolvedParam = true;
		gCurrentAC = backup;
	}
}

void Method::setGenericParam() {
	m_genericParam = popGenericNameList();
	if(m_genericParam != NULL && getGenre() == EGENRE::_DELEGATE) {
		compilerError(ERR_NOT_SUPPORTED_YET, "Generic delegates are not supported yet");
	}
}

TypeObject* Method::getGenericType(TypeGenericDefinitionEntry* genericSymbol, TypeGenericEntry* genericParams) {
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
		if(!pDefGen || pGen) {
			compilerError(ERR_INTERNAL, "Wrong number of generic parameters");
			return NULL;
		}
		return pGen->m_instanceType;
	}
	else {
		return NULL;
	}
}

bool Method::analyzeRef() {
	//
	// Compute the maximum amount of space necessary on the stack to track references for GC during a call.
	//
	m_referenceModifCount = 0;
	Variable* pVar = m_parameters;
	while (pVar) {
		// For each param by REFERENCE.
		if (pVar->m_modifier & ATT_REF) {
			// Not a ref on a base type : pointer on class or struct.
			if ((pVar->m_type->m_typeID &  ET_BASETYPE) == 0) {
				//
				// Check for a type to an object ptr, or a struct.
				//
				SRSymbol v = pVar->m_type->getResolvedType(this->m_pOwner);
				switch (v.symbolType) {
				case EGENRE::_ABSTRACTCONTAINER:
					{
						AbstractContainer* pCnt = (AbstractContainer*)v.pSymbol;
						if (pCnt->m_modifier & ATT_STRUCT) {
							m_referenceModifCount += pCnt->m_referenceModifCount;
						} else {
							if (pCnt->getType()->isGC_Able()) {
								m_referenceModifCount++;
							}
						}
					}
					break;
				default:
					// Do nothing
					break;
				}
			}
		}
		pVar = pVar->m_pNextVariable;
	}

	return m_referenceModifCount != 0;
}

TypeGenericDefinitionEntry*	Method::findGenericSymbol(const char* name) {
	TypeGenericDefinitionEntry* pGenericEntry = m_genericParam;
	while(pGenericEntry) {
		if(strcmp(pGenericEntry->m_genericName, name) == 0) {
			return pGenericEntry;
		}
		pGenericEntry = pGenericEntry->m_pNextGenericEntry;
	}
	return NULL;
}

MethodList::MethodList(Method* head)
:Method()
,m_method		(NULL)
,m_nextMethod	(NULL)
,m_count		(0)
{
}

int MethodList::getGenre() {
	return EGENRE::_METHODLIST;
}

void MethodList::add(Method* method) {	
	if(!m_method) {
		m_method = method;
	}
	else {
		MethodList* pMethod = this;
		while(pMethod->m_nextMethod) {
			pMethod = pMethod->m_nextMethod;
		}
		MethodList* pNewMethod = new MethodList(method);
		pMethod->m_nextMethod = pNewMethod;
	}
	m_count++;
}