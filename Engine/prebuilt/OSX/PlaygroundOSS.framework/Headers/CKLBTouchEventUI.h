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
#ifndef CKLBTouchEventUI_h
#define CKLBTouchEventUI_h

#include "CKLBTask.h"
#include "CKLBUISystem.h"

class CKLBTouchEventUIMgr
{
	friend class CKLBUISystem;
private:
	CKLBTouchEventUIMgr();
	virtual ~CKLBTouchEventUIMgr();

public:
	static CKLBTouchEventUIMgr& getInstance();

	void processUI      ();
	void resetSelectable(CKLBUISelectable * pSelectable);

	void registForm     (SFormCtrlList * pList);
	void removeForm     (SFormCtrlList * pList);
	SFormCtrlList * searchCtrl(CKLBUISelectable * pCtrl);

	enum {
		MAX_TOUCH_POINT = 10,
		MV_BORDER = 20	// TAPからこのpixel数以上DRAGしたら、クリック操作ではないと判断
	};
private:
	// 現在稼働中のフォームごとに、各フォームのコントロールリストが登録される。
	SFormCtrlList		*	m_pFormBegin;

	CKLBUISelectable	*	m_pTarget[ MAX_TOUCH_POINT ];
	struct {
		int x;
		int y;
	} m_tapPos[ MAX_TOUCH_POINT ];
};


/*!
* \class CKLBTouchEventUITask
* \brief Touch Event handler task class.
* 
* CKLBTouchEventUITask is in charge of handling the various touch events 
* of the game and redistribute it to the right item. 
* Forms can be registered in order to be able to process some actions 
* on Touch Pad events.
* This task is instanciated when the game starts.
*/
class CKLBTouchEventUITask : public CKLBTask
{
private:
	CKLBTouchEventUITask();
	virtual ~CKLBTouchEventUITask();

public:
	static CKLBTouchEventUITask * create();

	void execute(u32 deltaT);
	void die    ();

	u32 getClassID();

private:
	bool init();
};

#endif
