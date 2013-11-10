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
//  CKLBLuaTask.h
//

#ifndef CKLBLuaTask_h
#define CKLBLuaTask_h

#include "lua.hpp"
#include "CKLBTask.h"
#include "CLuaState.h"
#include "CKLBUtility.h"
#include "CKLBScriptEnv.h"

/*!
* \class CKLBLuaTask
* \brief Lua Task class.
* 
* CKLBLuaTask is the abstract root class for every task 
* that can be created from a script command.
* It defines some virtual methods and some generic callbacks.
*
* CKLBLuaTask objects can interact with the scripting langage
* throught methods/commands calls depending on the scripting langage.
*/
class CKLBLuaTask : public CKLBTask
{
public:
    CKLBLuaTask();
    virtual ~CKLBLuaTask();

   
    virtual CKLBTask::TASKTYPE getTaskType();

    virtual void execute(u32 deltaT) = 0;
    virtual void die() = 0;
    
    // lua script によって起動された際の初期化メソッド。
    // 初期化に成功したら regist() の戻り値を返すこと。
    // 失敗した場合は false を返す。
    virtual bool initScript(CLuaState& lua) = 0;
    
    // lua script から動作中に送られるコマンドの受付メソッド。
    // コマンドを必要としないタスクもあるので、デフォルトでは何もしない処理が実装されている。
    // lua script に対する戻り値を持つこともできる。
    // CLuaState のメソッドで戻り値を lua スタックに積み、戻り値の数を返すこと。
    // 戻り値が無い場合は 0 を返す。
    virtual int commandScript(CLuaState& lua);

	void setKillCallback	(const char* cbFuncName);
	void performKillCallback();

	bool setStrC			(const char*& dest, const char* src);
private:
	const char*	m_cbFuncName;
};

#ifdef DEBUG_RT_CHECK
#define CHECKTASK(pTask)		{ if(!CKLBTaskMgr::getInstance().isExistTask(pTask)) CKLBScriptEnv::getInstance().error("The canceled TASK was specified.:%p", pTask); }
#define CHECKTASKNULLOK(pTask)	{ if(pTask) { if (!CKLBTaskMgr::getInstance().isExistTask(pTask)) { klb_assertAlways("Parent task does not exist yet."); } } }
#else
#define CHECKTASK(pTask)
#define CHECKTASKNULLOK(pTask)
#endif

class IFactory
{
public:
    IFactory();
    virtual ~IFactory();
    static bool			registLuaFunctions	(lua_State * L);
	static u32			getClassID			(const char* luaFuncName, bool assertIfNotFound = true);
	static const char*	getClassName		(u32 classID);

	typedef struct {
		const char * name;
		int			 cmd;
	} DEFCMD;

protected:
    void addLink(const char * luaFuncName, int (*func)(lua_State * L), DEFCMD * arrCmdItem, u32 classID);

private:
    static IFactory *	m_begin;
    IFactory		*   m_pNext;
    const char		*   m_funcName;
	const DEFCMD	*	m_arrCmdItem;
	u32					m_classID;
	int (*m_luaFunc)(lua_State * L);
};

template <class T>
class CKLBTaskFactory : public IFactory
{
public:
	CKLBTaskFactory(const char * luaFuncName, u32 classID, DEFCMD * arrCmdItem = 0) {
		addLink(luaFuncName, CKLBTaskFactory<T>::createFactory, arrCmdItem, classID);
	}
    ~CKLBTaskFactory() {}

    static int createFactory(lua_State * L) {
        CLuaState lua(L);
#ifdef INTERNAL_BENCH
		s64 startCreate = CPFInterface::getInstance().platform().nanotime();
#endif
        T * pTask = KLBNEW(T);
 
        bool bResult = false;
        if(pTask) {
			CKLBTaskMgr::getInstance().setCurrentTask(pTask);
		    bResult = pTask->initScript(lua);
			CKLBTaskMgr::getInstance().setCurrentTask(NULL);
#ifdef INTERNAL_BENCH
		logTime('T', CPFInterface::getInstance().platform().nanotime() - startCreate, pTask->getClassID());
#endif
        }
        if(bResult) {
			lua.retPointer(pTask);
		} else {
			CKLBTaskMgr::getInstance().setCurrentTask(pTask);
            KLBDELETE(pTask);
			CKLBTaskMgr::getInstance().setCurrentTask(NULL);
			lua.retBoolean(false);
		}
        return 1;
    }
};

#endif
