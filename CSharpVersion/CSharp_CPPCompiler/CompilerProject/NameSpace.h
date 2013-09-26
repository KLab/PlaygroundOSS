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
#ifndef NAMESPACE_H
#define NAMESPACE_H

#include "BaseType.h"
#include "Symbol.h"

extern NameSpace* gCurrentNameSpace;

// NameSpace store list of definitions.
class NameSpace : public Symbol {
public:
	static const int	PHASE_LOCAL			= 0x01;
	static const int	PHASE_GENERIC		= 0x02;
	static const int	PHASE_INHERITANCE	= 0x04;
	static const int	PHASE_USING			= 0x08;
	static const int	PHASE_HIERARCHY		= 0x10;
	static const int	PHASE_ALL			= PHASE_LOCAL | PHASE_GENERIC | PHASE_INHERITANCE | PHASE_USING | PHASE_HIERARCHY;

	NameSpace();
	virtual int getGenre();
	virtual const char* getFullName(NameSpace* ref);

	void	addUsing(const char* using_);
	void	addNameSpace(NameSpace* pNameSpace);
	void	addAbstractContainer(AbstractContainer* pCnt);
	Enum*	addEnum(Attribute* pAttrib, u32 modified, const char* name, TypeObject* type);
	Delegate*	addDelegate(Attribute* attribute, u32 modifier, TypeObject* type, const char* name, Variable* variable);

	bool isSubSystem();
	NameSpace*	findNameSpace(const char* name);
	NameSpace*	setup(Attribute* attribute, const char* nameSpace);
	Enum* findEnum(const char* name);
	Delegate* findDelegate(const char* name);

	Symbol* findContext(const char* name, u8 searchMask, int interation = 0);
	Symbol* resolve(const char* name, u8 searchMask = PHASE_ALL, int iteration = 0);

	AbstractContainer**	m_pInner;
	int					m_innerCount;
	Enum**				m_enums;
	int					m_enumCount;
	Attribute*			m_attribute;

	Delegate**			m_delegates;
	int					m_delegateCount;

	int					m_usingCount;
	const char**		m_usings;

	NameSpace*			m_pParent;
	NameSpace*			m_pChildSpace;
	NameSpace*			m_pNextSpace;
	bool				m_bIsAbstract;
	bool				m_noDump;

	// List of symbol.
	Symbol*	m_pNext;
};

#endif	//NAMESPACE_H
