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
#include "CKLBScrMgrSolid.h"

static CKLBScrMgrSolidFactory factory("solid");

CKLBScrMgrSolidFactory::CKLBScrMgrSolidFactory(const char * name) 
: IMgrEntry (name) 
{
}

CKLBScrMgrSolidFactory::~CKLBScrMgrSolidFactory() 
{
}

CKLBScrollMgr *
CKLBScrMgrSolidFactory::createManager(int /*argc*/, /*int args[]*/ int*)
{
	return KLBNEW(CKLBScrMgrSolid);
}

CKLBScrollMgr *
CKLBScrMgrSolidFactory::createManagerByProperty(CKLBPropertyBag * /*pProp*/)
{
	return KLBNEW(CKLBScrMgrSolid);
}

/*
  サンプルのスクロールマネージャ実装。
  与えられた位置を即その場で反映し、バーの位置 = 値の位置という極めて基本的なサンプル。
  */

CKLBScrMgrSolid::CKLBScrMgrSolid() 
: m_pos (0) 
{
}

CKLBScrMgrSolid::~CKLBScrMgrSolid() 
{
}

void
CKLBScrMgrSolid::setMargin(int /*top*/, int /*bottom*/) 
{
}

void
CKLBScrMgrSolid::setInitial(int pos)
{
	m_pos = pos;
}

void
CKLBScrMgrSolid::setPosition(int pos, int /*dir*/)
{
	/*
	if(pos < 0) pos = 0;
	if(pos > m_maxPos) pos = m_maxPos;
*/
	m_pos = loopRound(pos);
}

int
CKLBScrMgrSolid::getPosition()
{
	return m_pos;
}

int
CKLBScrMgrSolid::getBarPosition()
{
	return m_pos;
}

void
CKLBScrMgrSolid::execute(u32 /* deltaT */)
{
	execCallback(m_pos);
}

bool 
CKLBScrMgrSolid::stillScrolling() {
	return false;
}
