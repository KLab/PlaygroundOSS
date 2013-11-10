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
#ifndef CKLBLibScrollMgr_h
#define CKLBLibScrollMgr_h

#include "klb_vararg.h"
#include "CKLBScrollBarIF.h"
#include "CKLBPropertyBag.h"

class CKLBLibScrollMgr;

class IMgrEntry
{
	friend class CKLBLibScrollMgr;
public:
	IMgrEntry(const char * label);
	virtual ~IMgrEntry();

	static CKLBScrollMgr * getMgr           (const char * name, int argc = 0, ...);
	static CKLBScrollMgr * getMgrByArray    (const char * name, int argc = 0, int args[] = NULL);
	static CKLBScrollMgr * getMgrByProperty (CKLBPropertyBag * pProp);

	virtual bool exist();

protected:
	virtual CKLBScrollMgr * createManager           (int argc, int args[])      = 0;
	virtual CKLBScrollMgr * createManagerByProperty (CKLBPropertyBag * pProp)   = 0;

private:
	static IMgrEntry * search(const char * name);

	const char	*	m_name;

	IMgrEntry	*	m_prev;
	IMgrEntry	*	m_next;

	static IMgrEntry	*	ms_begin;
	static IMgrEntry	*	ms_end;
};

#endif // CKLBLibScrollMgr_h
