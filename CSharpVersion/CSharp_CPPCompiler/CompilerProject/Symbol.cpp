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

Symbol::Symbol() 
:m_pNext			(NULL)
,m_pAlias			(NULL)
,m_name				(NULL)
,m_dependancyList	(NULL)
,m_stdAttribute		(0)
{
	m_uniqueId	= gGlobalClassID;
	m_line		= yylineno;
}

Symbol::~Symbol()
{
	delete[] m_name;
}

const char*	Symbol::getName() {
	return m_name;
}

void Symbol::setName(const char* name) {
	m_name = concat(name);
}

/**
	Abstract container or enum
 */
void Symbol::use(Symbol* v) {
	// Check if already used to avoid double registration.
	Dependancy* p = m_dependancyList;
	while (p) {
		if (p->m_uses == v) { return ; }
		p = p->m_pNext;
	}

	// Insert only new element
	p = new Dependancy();
	p->m_uses = v;
	p->m_pNext = m_dependancyList;
	m_dependancyList = p;
}

void Symbol::unuseAll() {
	Dependancy* p	= m_dependancyList;
	while (p) {
		Dependancy* n	= p->m_pNext;
		delete p;
		p = n;
	}
}

void Symbol::unuse(Symbol* v) {
	Dependancy* p	= m_dependancyList;
	Dependancy* prev	= NULL;

	// multiple registration checked, so we delete only once.
	while (p) {
		if (p->m_uses == v) {
			if (prev) {
				prev->m_pNext = p->m_pNext;
			} else {
				m_dependancyList = p->m_pNext;
			}

			delete p;
			return;
		}
		prev = p;
		p = p->m_pNext;
	}
}

bool Symbol::stillUsing(u32 mask) {
	if (mask == 0xFFFF) {
		return m_dependancyList != NULL;
	} else {
		Dependancy* p = m_dependancyList;
		while (p) {
			if (p->m_uses->getGenre() & mask) {
				return true;
			}
			p = p->m_pNext;
		}
		return false;
	}
}

Symbol* createNotFoundSymbol() {
	Symbol* notFound = new Symbol();
	notFound->setName("[Symbol not found]");
	return notFound;
}
