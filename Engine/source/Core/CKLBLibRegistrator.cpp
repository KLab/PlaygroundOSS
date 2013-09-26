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
#include "CKLBLibRegistrator.h"

CKLBLibRegistrator::CKLBLibRegistrator()
:m_count	(0)
{
}

CKLBLibRegistrator::~CKLBLibRegistrator() 
{
	CHECKMEM();
}

CKLBLibRegistrator* 
CKLBLibRegistrator::getInstance() 
{
	static CKLBLibRegistrator reg;
	return &reg;
}

CKLBLibRegistrator::LIBREGISTSTRUCT* 
CKLBLibRegistrator::add(const char* name, u32 classID) 
{
	klb_assert(m_count < MAX_ELEM, "Reached maximum allocation space for lib registrator");
	LIBREGISTSTRUCT	*		new_element = &m_list[m_count++];
	new_element->name		= name;
	new_element->classID	= classID;
	return new_element;
}

u32 
CKLBLibRegistrator::getClassID(const char* funcName) 
{
	int n = 0;
	while (n < m_count) {
		LIBREGISTSTRUCT	* pLibReg = &m_list[n];

		if (CKLBUtility::safe_strcmp(pLibReg->name,funcName)==0) {
			return pLibReg->classID;
		}
		n++;
	}
	return 0;
}