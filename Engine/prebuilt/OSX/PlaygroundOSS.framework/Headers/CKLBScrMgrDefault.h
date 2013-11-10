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
#ifndef CKLBScrMgrDefault_h
#define CKLBScrMgrDefault_h

#include "IMgrEntry.h"

class CKLBScrMgrDefaultFactory : public IMgrEntry
{
public:
	CKLBScrMgrDefaultFactory(const char * name);
	virtual ~CKLBScrMgrDefaultFactory();

	CKLBScrollMgr * createManager(int argc, int args[]);
	CKLBScrollMgr * createManagerByProperty(CKLBPropertyBag * pProp);

	enum {
		DEFAULT_DELAY = 10
	};
};

class CKLBScrMgrDefault : public CKLBScrollMgr
{
public:
	CKLBScrMgrDefault(int delay);
	virtual ~CKLBScrMgrDefault();

	virtual void setMargin      (int top, int bottom);
	virtual void setInitial     (int pos);
	virtual void setPosition    (int pos, int dir);
	virtual int  getPosition    ();
	virtual int  getBarPosition ();
	virtual void execute        (u32 deltaT);
	virtual bool stillScrolling ();
private:
	float		m_speed;
	float		m_posTarget;
	float		m_posNow;
	int			m_delay;
	int			m_mvDir;
};


#endif // CKLBScrMgrDefault_h
