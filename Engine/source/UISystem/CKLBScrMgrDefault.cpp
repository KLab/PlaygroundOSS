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
#include "CKLBScrMgrDefault.h"

static CKLBScrMgrDefaultFactory factory("default");

CKLBScrMgrDefaultFactory::CKLBScrMgrDefaultFactory(const char * name) 
: IMgrEntry (name) 
{
}

CKLBScrMgrDefaultFactory::~CKLBScrMgrDefaultFactory() 
{
}

CKLBScrollMgr *
CKLBScrMgrDefaultFactory::createManager(int argc, int args[])
{
	int delay = (argc > 0) ? args[0] : DEFAULT_DELAY;
	return KLBNEWC(CKLBScrMgrDefault, (delay));
}

CKLBScrollMgr *
CKLBScrMgrDefaultFactory::createManagerByProperty(CKLBPropertyBag * pProp)
{
	int delay = (pProp->getIndex("delay") >= 0) ? pProp->getPropertyInt("delay") : DEFAULT_DELAY;
	return KLBNEWC(CKLBScrMgrDefault, (delay));
}


/*
  サンプルのスクロールマネージャ実装。
  与えられた位置を即その場で反映し、バーの位置 = 値の位置という極めて基本的なサンプル。
  */

CKLBScrMgrDefault::CKLBScrMgrDefault(int delay) 
: m_posTarget   (0.0f)
, m_posNow      (0.0f)
, m_delay       (delay)
, m_mvDir       (0)
, m_speed       (0.0f) 
{
}

CKLBScrMgrDefault::~CKLBScrMgrDefault() 
{
}

void
CKLBScrMgrDefault::setMargin(int /*top*/, int /*bottom*/) {}

void
CKLBScrMgrDefault::setInitial(int pos)
{
	setPosition(pos, 0);
	m_posNow = m_posTarget;
}

void
CKLBScrMgrDefault::setPosition(int pos, int dir)
{
	m_posTarget = loopRound((float)pos);
	m_mvDir = dir;	// 移動方向
}

int
CKLBScrMgrDefault::getPosition()
{
	return (int)m_posNow;
}

int
CKLBScrMgrDefault::getBarPosition()
{
	return (int)m_posTarget;
}

void
CKLBScrMgrDefault::execute(u32 /* deltaT */)
{
	if((int)m_posTarget == (int)(m_posNow + 0.05f)) {
		m_posNow    = m_posTarget;
		m_mvDir     = 0;
		m_speed     = 0.0f;
		execCallback(m_posNow);
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
CKLBScrMgrDefault::stillScrolling() {
	// Less than 2 pix per second.
	return fabs(m_speed) > 2.0f;
}
