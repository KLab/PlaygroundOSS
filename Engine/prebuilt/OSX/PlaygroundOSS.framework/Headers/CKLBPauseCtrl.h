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
#ifndef CKLBPauseCtrl_h
#define CKLBPauseCtrl_h

#include "CKLBLuaTask.h"
#include "CKLBOSCtrlEvent.h"

/*!
* \class CKLBPauseCtrl
* \brief Pause Control Task class
* 
* CKLBPauseCtrl allows to add control to a class when you pause and/or resume it, 
* as it is not provided by default in a CKLBTask.
* You can register callbacks that will be called when pausing and resuming the Task.
*/
class CKLBPauseCtrl : public CKLBLuaTask
{
	friend class CKLBTaskFactory<CKLBPauseCtrl>;
private:
	CKLBPauseCtrl();
	virtual ~CKLBPauseCtrl();

	bool init(CKLBTask* pTask, const char* pause, const char* resume);
public:
	static CKLBPauseCtrl* create(CKLBTask* pParentTask, const char* pause, const char* resume);

	bool initScript	(CLuaState& lua);

	void execute	(u32 deltaT);
	void die		();

private:
	const char *	m_callbackPause;
	const char *	m_callbackResume;
};


#endif // CKLBPauseCtrl_h
