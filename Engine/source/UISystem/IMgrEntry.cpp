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
#include "IMgrEntry.h"

IMgrEntry * IMgrEntry::ms_begin = NULL;
IMgrEntry * IMgrEntry::ms_end   = NULL;

IMgrEntry::IMgrEntry(const char * name) 
: m_name    (name)
, m_next    (NULL)
, m_prev    (NULL)
{
	m_next = ms_begin;
	if(m_next) {
		m_next->m_prev = this;
	} else {
		ms_end = this;
	}
	ms_begin = this;
}

IMgrEntry::~IMgrEntry()
{
	if(m_prev) {
		m_prev->m_next = m_next;
	} else {
		ms_begin = m_next;
	}
	if(m_next) {
		m_next->m_prev = m_prev;
	} else {
		ms_end = m_prev;
	}
}

bool
IMgrEntry::exist()
{
	return true;
}

IMgrEntry *
IMgrEntry::search(const char * name)
{
	// 指定された名称を持つscroll managerを検索する
	IMgrEntry * pEntry = ms_begin;
	while(pEntry) {
        if(!strcmp(pEntry->m_name, name)) { break; }
		pEntry = pEntry->m_next;
	}
	return pEntry;
}

CKLBScrollMgr *
IMgrEntry::getMgr(const char * name, int argc, ...)
{
	// 指定された名称を持つscroll managerを検索する
	IMgrEntry * pEntry = search(name);
    if(!pEntry) { return NULL; }

	int * params = NULL;
	if(argc > 0) {
		params = KLBNEWA(int, argc);
		va_list ap;
		va_start(ap, argc);
		for(int i = 0; i < argc; i++) {
			params[i] = va_arg(ap, int);
		}
		va_end(ap);
	}
	CKLBScrollMgr * mgr = pEntry->createManager(argc, params);

	KLBDELETEA(params);

	return mgr;
}

CKLBScrollMgr *
IMgrEntry::getMgrByArray(const char * name, int argc, int args[])
{
	IMgrEntry * pEntry = search(name);
    if(!pEntry) { return NULL; }

	CKLBScrollMgr * mgr = pEntry->createManager(argc, args);

	return mgr;
}

CKLBScrollMgr *
IMgrEntry::getMgrByProperty(CKLBPropertyBag * pProp)
{
	const char * name = pProp->getPropertyString("name");
	IMgrEntry * pEntry = search(name);
    if(!pEntry) { return NULL; }

	CKLBScrollMgr * mgr = pEntry->createManagerByProperty(pProp);
	return mgr;
}
