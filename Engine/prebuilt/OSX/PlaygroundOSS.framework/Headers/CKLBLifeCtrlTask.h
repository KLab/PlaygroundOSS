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
#ifndef CKLBLifeCtrlTask_h
#define CKLBLifeCtrlTask_h

#include "CKLBLuaTask.h"

/*!
* \class CKLBLifeCtrlTask
* \brief Life Control Task
* 
* CKLBLifeCtrlTask is a Task made for controlling the life of another Task
* of the Engine. 
* CKLBLifeCtrlTask has 2 mods : TIME and FRAME.
* A Task can be linked with an instance of CKLBLifeCtrlTask. In that case, the 
* CKLBLifeCtrlTask will kill the Task after X milliseconds or frames.
*/
class CKLBLifeCtrlTask : public CKLBLuaTask
{
	friend class CKLBTaskFactory<CKLBLifeCtrlTask>;
private:
	CKLBLifeCtrlTask();
	virtual ~CKLBLifeCtrlTask();

	bool init(CKLBTask* pTask, u32 mode, u32 limit);
public:
	static CKLBLifeCtrlTask* create(CKLBTask* pParentTask, u32 mode, u32 limit);

	bool	initScript		(CLuaState& lua);
	int		commandScript	(CLuaState& lua);

	inline void setTime(u32 mode, u32 unit) {
		m_count = 0;
		m_limit	= unit;
		m_mode	= mode;
	}

	inline void link(CKLBTask* taskToKill) {
		m_bLinked	= (taskToKill != NULL);
		m_taskLink  =  taskToKill;
	}

	void execute(u32 deltaT);
	void die();

private:
	bool			m_bLinked;
	CKLBTask*		m_taskLink;
	int				m_mode;
	u32				m_limit;
	u32				m_count;
};
	

#endif // CKLBIntervalTask_h
