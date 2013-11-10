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
//
//  CGenericTask.h
//  GameEngine
//
//

#ifndef CKLBGenericTask_h
#define CKLBGenericTask_h

#include "CKLBLuaPropTask.h"

/*!
* \class CKLBGenericTask
* \brief Generic Task Class
* 
* CKLBGenericTask is the most generic class of the Engine that can be used
* for scripting purpose.
* It is just made to execute some script code every frame.
*/
class CKLBGenericTask : public CKLBLuaPropTask
{
private:
	bool init(CKLBTask* pTask, CKLBTask::TASK_PHASE phase, const char * name_exec, const char * name_die, const char * arr_index);
public:
	static CKLBGenericTask* create(CKLBTask* pParentTask, CKLBTask::TASK_PHASE phase, const char * name_exec, const char * name_die, const char * arr_index);
    CKLBGenericTask();
    virtual ~CKLBGenericTask();

    bool	initScript		(CLuaState& lua);
    int		commandScript	(CLuaState& lua);

    void	execute			(u32 deltaT);
    void	die				();

	u32		getClassID		();
private:

    const char  *   m_luaFuncExec;
    const char  *   m_luaFuncDie;
    const char  *   m_ArrayIndex;
};

#endif // CKLBGenericTask_h
