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
#ifndef CKLBUIButton_h
#define CKLBUIButton_h

#include "CKLBLuaTask.h"
#include "CKLBUISystem.h"
#include "CKLBFormGroup.h"
#include "CKLBModalStack.h"

class CKLBUIButton : public CKLBLuaTask
{
	friend class CKLBTaskFactory<CKLBUIButton>;
protected:
	CKLBUIButton();
	virtual ~CKLBUIButton();

public:
	static CKLBUIButton* create(CKLBTask* pParentTask, const char * funcName);
	bool init(CKLBTask* pTask, const char* funcName);

	bool initScript(CLuaState& lua);
	int commandScript(CLuaState& lua);

	inline bool setGroup(const char* group_name) {
		CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();
		return fGrp.addForm(&m_ctrlList, group_name);
	}

	inline void lock(bool lock_mode) {
		CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();
		fGrp.setWorking(&m_ctrlList, lock_mode, this);	// locker を指定することで、自分がかけたlockは無視できる
	}

	inline void setGetAll(bool b) { m_bAll = b; }

	void execute(u32 deltaT);
	void die();

    u32 getClassID();

private:
	const char * m_luaFunc;

	// グループ化用
	SFormCtrlList		m_ctrlList;

	bool				m_bAll;

	int m_execount;
};

#endif // CKLBUIButton_h
