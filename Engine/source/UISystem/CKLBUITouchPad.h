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
#ifndef CKLBUITouchPad_h
#define CKLBUITouchPad_h

#include "CKLBLuaTask.h"
#include "CKLBUISystem.h"
#include "CKLBFormGroup.h"
#include "CKLBModalStack.h"

/*!
* \class CKLBUITouchPad
* \brief UI Touch Pad Task class.
* 
* CKLBUITouchPad is a simple low level Touch Pad Events handler.
* It provides a few callbacks that are called when some actions are processed
* (Only Tap, Drag and Release).
* For a higher level Touch Pad Events handling, see UIControl.
*/
class CKLBUITouchPad : public CKLBLuaTask
{
	friend class CKLBTaskFactory<CKLBUITouchPad>;
protected:
	CKLBUITouchPad();
	virtual ~CKLBUITouchPad();

public:
	static CKLBUITouchPad* create(CKLBTask* pParentTask, const char * funcName, bool modal);
	bool init(CKLBTask* pTask, const char* funcName, bool modal);

	bool    initScript      (CLuaState& lua);
	int     commandScript   (CLuaState& lua);

	inline bool setGroup    (const char* group_name) {
		CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();
		return fGrp.addForm(&m_ctrlList, group_name);
	}

	inline void lock        (bool lock_mode) {
		CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();
		fGrp.setWorking(&m_ctrlList, lock_mode, this);	// locker を指定することで、自分がかけたlockは無視できる
	}

	inline void setGetAll   (bool b) { m_bAll = b; }

	void execute(u32 deltaT);
	void die    ();

    u32 getClassID();

private:
	const char *        m_luaFunc;

	// グループ化用
	SFormCtrlList		m_ctrlList;
	CKLBModalStack		m_modalStack;

	bool				m_modal;
	bool				m_bAll;

	int m_execount;
};

#endif // CKLBUITouchPad_h
