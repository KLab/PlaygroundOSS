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
#include "CKLBScrMgrPage.h"

static CKLBScrMgrPageFactory factory("page");

CKLBScrMgrPageFactory::CKLBScrMgrPageFactory(const char * name) 
: IMgrEntry(name) 
{
}

CKLBScrMgrPageFactory::~CKLBScrMgrPageFactory() 
{
}

CKLBScrollMgr *
CKLBScrMgrPageFactory::createManager(int argc, int args[])
{
    if(argc < 1 || argc > 3) { return NULL; }
	int pagesize = args[0];
	int delay    = (argc >= 2) ? args[1] : DEFAULT_DELAY;
	int offset   = (argc >= 3) ? args[2] : 0;
	return KLBNEWC(CKLBScrMgrPage, (pagesize, delay, offset));
}

CKLBScrollMgr *
CKLBScrMgrPageFactory::createManagerByProperty(CKLBPropertyBag * pProp)
{
	int delay    = (pProp->getIndex("delay") >= 0) ? pProp->getPropertyInt("delay") : DEFAULT_DELAY;
	int pagesize = pProp->getPropertyInt("pagesize");
	int offset   = (pProp->getIndex("offset") >= 0) ? pProp->getPropertyInt("offset") : 0;
	return KLBNEWC(CKLBScrMgrPage, (pagesize, delay, offset));
}

//
// Page Scroll Manager
//

CKLBScrMgrPage::CKLBScrMgrPage(int pagesize, int delay, int offset)
: m_posTarget   (0.0f)
, m_posNow      (0.0f)
, m_pagesize    (pagesize)
, m_delay       (delay)
, m_offset      (offset)
, m_margin_top  (0)
, m_margin_bottom   (0)
, m_mvDir       (0)
, m_speed       (0.0f)
{
}

CKLBScrMgrPage::~CKLBScrMgrPage() 
{
}

void
CKLBScrMgrPage::setMargin(int top, int bottom)
{
	m_margin_top    = top;
	m_margin_bottom = bottom;
}

void
CKLBScrMgrPage::setInitial(int pos)
{
	setPosition(pos - m_offset, 0);
	m_posTarget = loopRound(m_posTarget);
	m_posNow    = m_posTarget;	// 初期位置に合わせる
	m_initial   = true;
}

void
CKLBScrMgrPage::setPosition(int pos, int dir)
{
	int margin_top  = (m_lenLoop) ? 0 : m_margin_top;
	int upos        = pos - margin_top + m_offset;
	int mvDir       = dir;
	upos = (int)loopRound((float)upos);
//	if(upos >= -(m_pagesize / 2)) {
		int page = (upos + (m_pagesize / 2)) / m_pagesize;
		int npos = page * m_pagesize + margin_top - m_offset ;
		npos = (int)loopRound((float)npos);
        if(m_posTarget != npos) { m_mvDir = mvDir; }
		m_posTarget = loopRound(npos);
/*
	} else {
		m_posTarget = margin_top - m_offset;
	}
*/
}

int
CKLBScrMgrPage::getPosition()
{
	return (int)loopRound(m_posNow);
}

int
CKLBScrMgrPage::getBarPosition()
{
	return (int)m_posTarget;
}

void
CKLBScrMgrPage::execute(u32 /* deltaT */)
{
	if((int)(abs(m_posTarget)) == (int)(abs(m_posNow) + 0.05f)) {
		m_posNow = m_posTarget;
		m_mvDir  = 0;
		m_speed  = 0.0f;
		int cbpos = loopRound(m_posNow + m_offset);
		execCallback(cbpos);
		return;
	}
	float target = m_posTarget;
    if(m_mvDir < 0 && target > m_posNow) { target -= m_lenLoop; }
	if(m_mvDir > 0 && target < m_posNow) { target += m_lenLoop; }
	float left = target - m_posNow;

	m_speed   = left / m_delay;
	m_posNow += m_speed;
	m_posNow  = loopRound(m_posNow);
}

bool 
CKLBScrMgrPage::stillScrolling() {
	// Less than 2 pix per second.
	return fabs(m_speed) > 2.0f;
}
