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
#include "compilerLibrary.h"

Accessor::Accessor	()
:m_attribute		(NULL)
,m_type				(NULL)
,m_get				(NULL)
,m_set				(NULL)
,m_indexer			(NULL)
,m_statement		(NULL)
,m_ownerClass		(NULL)
,m_variable			(NULL)
,m_modifier			(0)
{
}

Accessor::~Accessor()
{
}

/*virtual*/
int Accessor::getGenre() {
	return EGENRE::_ACCESSOR;
}

void Accessor::dumpParams(bool call, bool addComma) {
	Variable* pVar = m_variable;
	if(pVar) {
		NameSpace* context = (NameSpace*)m_ownerClass;
		while(pVar) {
			if(!call) {
				printf("%s ", pVar->m_type->dumpTypeForCode(context));
			}
			printf("%s", pVar->m_name);
			pVar = pVar->m_pNextVariable;
			if(pVar) {
				printf(", ");
			}
		}
		if(addComma) {
			printf(", ");
		}
	}
}
