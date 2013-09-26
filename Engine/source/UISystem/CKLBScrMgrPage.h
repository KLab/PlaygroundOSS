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
#ifndef CKLBScrMgrPage_h
#define CKLBScrMgrPage_h

#include "IMgrEntry.h"

class CKLBScrMgrPageFactory : public IMgrEntry
{
public:
	CKLBScrMgrPageFactory(const char * name);
	virtual ~CKLBScrMgrPageFactory();

	CKLBScrollMgr * createManager(int argc, int args[]);
	CKLBScrollMgr * createManagerByProperty(CKLBPropertyBag * pProp);

	enum {
		DEFAULT_DELAY = 10
	};
};

class CKLBScrMgrPage : public CKLBScrollMgr
{
public:
	CKLBScrMgrPage(int pagesize, int delay, int offset);
	virtual ~CKLBScrMgrPage();

	virtual void setMargin      (int top, int bottom);
	virtual void setInitial     (int pos);
	virtual void setPosition    (int pos, int dir);
	virtual int  getPosition    ();
	virtual int  getBarPosition ();
	virtual void execute        (u32 deltaT);
	virtual bool stillScrolling ();
private:
	int			m_pagesize;		// ページサイズ
	int			m_delay;		// ディレイ
	int			m_offset;

	float		m_speed;
	float		m_posTarget;	// スクロール目標
	float		m_posNow;		// 現在位置
	int			m_mvDir;		// 移動方向
	int			m_margin_top;
	int			m_margin_bottom;

	bool		m_initial;
};


#endif // CKLBScrMgrPage_h
