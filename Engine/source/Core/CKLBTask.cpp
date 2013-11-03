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
//  CKLBTask.cpp
//  Base Task Class and Task Manager Implementation
//
//

#include "CKLBTask.h"
#include "CKLBLuaTask.h"
#include "CPFInterface.h"
;


CKLBRegistedTaskList::CKLBRegistedTaskList()
: m_begin   (NULL)
, m_end     (NULL)
{
}

CKLBRegistedTaskList::~CKLBRegistedTaskList()
{
}

void
CKLBRegistedTaskList::addTask(CKLBTask * pTask)
{
	TASKITEM * pItem = KLBNEW(TASKITEM);
	pItem->pTask    = pTask;
	pItem->next     = NULL;
	pItem->prev     = m_end;
	if(pItem->prev) {
		pItem->prev->next = pItem;
	} else {
		m_begin = pItem;
	}
	m_end = pItem;
}

void
CKLBRegistedTaskList::killTaskList(bool kill_child)
{
	TASKITEM * pItem = m_begin;
	while(pItem) {
		TASKITEM * next = pItem->next;
		if(kill_child) {
            pItem->pTask->kill();
        }
		KLBDELETE(pItem);
		pItem = next;
	}
	m_begin = m_end = NULL;
}

CKLBTask::CKLBTask()
: m_pExePrev    (NULL)
, m_pExeNext    (NULL)
, m_pBrsPrev    (NULL)
, m_pBrsNext    (NULL)
, m_pRmvPrev    (NULL)
, m_pRmvNext    (NULL)
, m_pStgPrev    (NULL)
, m_pStgNext    (NULL)
, m_pParent     (NULL)
, m_ePhase      (P_MAX)
, m_activeStatus(ALWAYS_ACTIVE)
{
    m_lstChild.begin = m_lstChild.end = 0;
}

CKLBTask::~CKLBTask()
{
}

// 後始末methodとフレームmethodは、デフォルトだと何もしない。
void 
CKLBTask::die() 
{
}

void 
CKLBTask::execute(u32 /*deltaT*/) 
{
}

// pause状態を指定する
void
CKLBTask::setPause(bool bPause, bool bRecursive)
{
	#define ON_PAUSE	(1<<7)
	// 自身のpause状態を指定する
	if (onPause(bPause)) {
		m_activeStatus |= ON_PAUSE;
	} else {
		m_activeStatus &= ~ON_PAUSE;
	}
	#undef ON_PAUSE

    if(!bRecursive) { return; }

	// bRecursiveがtrueで子タスクがある場合は、子タスクにもPause状態を指定する
	for(CKLBTask * pTask = m_lstChild.begin; pTask; pTask = pTask->m_pBrsNext) {
		pTask->setPause(bPause, bRecursive);
	}
}

bool 
CKLBTask::onPause(bool bPause) 
{ 
    return bPause; 
}

CKLBTask::TASKTYPE
CKLBTask::getTaskType()
{
    return TASK_SIMPLE;
}

u32
CKLBTask::getClassID()
{
	return CLS_KLBUSERTASK;
}

bool
CKLBTask::regist(CKLBTask * pParent, TASK_PHASE ePhase)
{
	// TODO when we have modified Task construction with a link list of "prenew".
	// CHECKTASKNULLOK(pParent);

    if(pParent) pParent->child(this); // 親が指定されていれば親子関係を結ぶ
    CKLBTaskMgr& mgr = CKLBTaskMgr::getInstance();
    return mgr.regist(ePhase, this);   // 実行リストへの登録
}

// 親子関係を結ぶ
void
CKLBTask::child(CKLBTask * pChild)
{
    pChild->m_pParent   = this;
    pChild->m_pBrsPrev  = m_lstChild.end;
    pChild->m_pBrsNext  = NULL;
    if(m_lstChild.end)      { m_lstChild.end->m_pBrsNext = pChild; }
    if(!m_lstChild.begin)   { m_lstChild.begin = pChild; }
    m_lstChild.end = pChild;
}

// 自身を殺す
void
CKLBTask::kill()
{
    CKLBTaskMgr& mgr = CKLBTaskMgr::getInstance();

	// 破棄フェーズ中でkill()を呼んではいけない。
	klb_assert(!mgr.isKilling(), "Don't call kill() in die(). ");

    // 自身の子全員に対し Kill を実行する。
    CKLBTask * pChild = m_lstChild.begin;
    while(pChild) {
        CKLBTask * pNext = pChild->m_pBrsNext;
        pChild->kill();
        pChild = pNext;
    }

	if (this->getTaskType() != TASK_SIMPLE) {
		CKLBLuaTask* luaTask = (CKLBLuaTask*)this;
		luaTask->performKillCallback();
	}

    // 自身をタスクマネージャの削除リストに追加
    mgr.remove(this);

    // これで、フレーム終了時にこのタスクのインスタンスは削除される。
}


//----------------------
// ここよりタスクマネージャ
// ---------------------
CKLBTaskMgr::CKLBTaskMgr()
: m_bPause      (false)
, m_bExit       (true)
, m_bStageClear (false)
, m_frameId     (0)
, m_pRegList    (NULL)
, m_currentTask (NULL)
, m_bKilling    (false)
#ifdef DEBUG_MENU
, m_bDbgPause   (false)
#endif
#if defined(DEBUG_MEMORY)
, m_bFreeze     (false)
#endif
{
    int i;
    for(i = 0; i < CKLBTask::P_MAX; i++) {
        m_lstTask[i].begin = m_lstTask[i].end = NULL;
    }
    m_lstRemove.begin = m_lstRemove.end = NULL;
    m_lstStage.begin  = m_lstStage.end  = NULL;
}

CKLBTaskMgr::~CKLBTaskMgr() 
{
}

CKLBTaskMgr&
CKLBTaskMgr::getInstance()
{
    static CKLBTaskMgr instance;
    return instance;
}

bool
CKLBTaskMgr::regist(CKLBTask::TASK_PHASE ePhase, CKLBTask * pTask)
{
    // 実行リストへの追加
    pTask->m_ePhase     = ePhase;
    pTask->m_pExePrev   = m_lstTask[ePhase].end;
    pTask->m_pExeNext   = NULL;
    if(m_lstTask[ePhase].end)    { m_lstTask[ePhase].end->m_pExeNext = pTask; }
    if(!m_lstTask[ePhase].begin) { m_lstTask[ePhase].begin = pTask; }
    m_lstTask[ePhase].end = pTask;

	// 起動タスクリスト記録の必要があれば記録する
    if(m_pRegList) { m_pRegList->addTask(pTask); }

    return true;
}

// 登録されている全タスクを破棄する。
// おもに client クラスから呼び出される。タスクから呼んではならない。
void
CKLBTaskMgr::clearTaskList()
{
    int i;
    CKLBTask * pTask;
	CKLBTask * pNext;

	// タスクが親子関係を持っていることがあるので、
	// 全フェーズのタスクに対し、まずはkill()を発行する。
	// これにより、削除リストは必ず子→親の順番に登録される。
	//
	// - kill() は、既に削除リストに登録されているタスクを二重登録することはない。
	// - kill() は、指定されたタスクの子を再帰的に検索し、ツリーの末端から削除リストに登録する。
	//
	// 以上の特徴により、必ず子から親に向けて削除されるリストが出来上がる。
	for(i = 0; i < CKLBTask::P_MAX; i++) {
		pTask = m_lstTask[i].begin;
		while(pTask) {
			pNext = pTask->m_pExeNext;
            pTask->kill();
			pTask = pNext;
        }
    }

	// 削除リストに登録されたタスクを、登録順に削除する。
	// 必ず子→親の順番にリストが作成されている。
	remove_killlist();

	for(i = 0; i < CKLBTask::P_MAX; i++) {
		// should not be necessary as each task will update the links.
		m_lstTask[i].end	= NULL;
		m_lstTask[i].begin	= NULL;
    }
}

// 指定されたタスクをステージタスク登録する
void
CKLBTaskMgr::registStageTask(CKLBTask *pTask)
{
	// 既にステージタスクとして登録されていたら登録せずに帰る。
	if(pTask->m_pStgPrev || pTask->m_pStgNext || 
        (m_lstStage.begin == pTask) || (m_lstStage.end == pTask)) { return; }

    // ステージタスクリストへの追加
    pTask->m_pStgPrev = m_lstStage.end;
    pTask->m_pStgNext = NULL;
    if(pTask->m_pStgPrev) {
		pTask->m_pStgPrev->m_pStgNext = pTask;
	} else {
		m_lstStage.begin = pTask;
	}
    m_lstStage.end = pTask;
}

// ステージタスクとして登録されている全てのタスクを破棄予約する。
void
CKLBTaskMgr::clearStageTask()
{
	//CKLBTaskMgr& mgr = CKLBTaskMgr::getInstance();

	// 破棄フェーズ中でclearStageTask()を呼んではいけない。
	klb_assert(!m_bKilling, "Don't call clearStageTask() in die(). ");

    m_bStageClear = true;
}

bool
CKLBTaskMgr::isExistTask(CKLBTask * pTask)
{
    int i;
	bool bResult = false;
    CKLBTask * pItem;
    for(i = 0; i < CKLBTask::P_MAX; i++) {
        for(pItem = m_lstTask[i].begin; pItem; pItem = pItem->m_pExeNext) {
			if(pItem == pTask) {
				bResult = true;
				break;
			}
		}
		if(bResult) break;
	}
	return bResult;
}

bool
CKLBTaskMgr::is_remove(CKLBTask * pTask)
{
	// 指定されたポインタが、実行リストのどこにも登録されていなければ
	// 破棄ずみの領域を再度破棄しようとしている可能性がある。
	bool bResult = isExistTask(pTask);
	klb_assert(bResult, "unknow task pointer !");

	// 既に削除リストに登録されている場合
    if(pTask->m_pRmvNext || pTask->m_pRmvPrev) { return true; }
    if(m_lstRemove.begin == pTask || m_lstRemove.end == pTask) { return true; }

	// まだ削除予約はされていない
	return false;
}

bool
CKLBTaskMgr::remove(CKLBTask * pTask)
{
	// 既に削除リストに登録されている場合は何もしない
	if(is_remove(pTask)) return true;

	// 削除リストへの追加
    pTask->m_pRmvPrev = m_lstRemove.end;
    pTask->m_pRmvNext = NULL;
    if(m_lstRemove.end)     { m_lstRemove.end->m_pRmvNext = pTask; }
    if(!m_lstRemove.begin)  { m_lstRemove.begin = pTask; }
    m_lstRemove.end = pTask;
    
    // これが呼ばれる時点では実行リストからの削除は行わない
    return true;
}

void
CKLBTaskMgr::remove_killlist()
{
	m_bKilling = true;

    CKLBTask * pNext;
    CKLBTask * pTask = m_lstRemove.begin;
    while(pTask) {
        pNext = pTask->m_pRmvNext;

        // タスクが独自に握っているリソースの解放処理を行う。
        m_currentTask = pTask;
        pTask->die();

        // 実行リストから削除する
        if(pTask->m_pExePrev) {
            pTask->m_pExePrev->m_pExeNext = pTask->m_pExeNext;
        } else {
            m_lstTask[pTask->m_ePhase].begin = pTask->m_pExeNext;
        }
        if(pTask->m_pExeNext) {
            pTask->m_pExeNext->m_pExePrev = pTask->m_pExePrev;
        } else {
            m_lstTask[pTask->m_ePhase].end = pTask->m_pExePrev;
        }
        pTask->m_pExeNext = pTask->m_pExePrev = 0;
        // 実行リストからの削除完了
        
        // 親や兄弟から登録を抹消する
        if(pTask->m_pBrsPrev) {
            pTask->m_pBrsPrev->m_pBrsNext = pTask->m_pBrsNext;
        } else {
            // リスト先頭なので、親から削除
            if(pTask->m_pParent) {
                // 親タスクがある場合のみ必要。親タスクがない場合は、兄弟もいない
                pTask->m_pParent->m_lstChild.begin = pTask->m_pBrsNext;
            }
        }
        if(pTask->m_pBrsNext) {
            pTask->m_pBrsNext->m_pBrsPrev = pTask->m_pBrsPrev;
        } else {
            // リスト終端なので、親から削除
            if(pTask->m_pParent) {
                // 親タスクがある場合のみ処理が必要。親タスクが無い場合は兄弟もいない。
                pTask->m_pParent->m_lstChild.end = pTask->m_pBrsPrev;
            }
        }
        pTask->m_pBrsNext = pTask->m_pBrsPrev = NULL;
        pTask->m_pParent  = NULL;
        // 親兄弟との縁切り完了。
        
        if(pTask->m_pStgPrev) {
            pTask->m_pStgPrev->m_pStgNext = pTask->m_pStgNext;
        } else {
            if(m_lstStage.begin == pTask) m_lstStage.begin = pTask->m_pStgNext;
        }
        if(pTask->m_pStgNext) {
            pTask->m_pStgNext->m_pStgPrev = pTask->m_pStgPrev;
        } else {
            if(m_lstStage.end == pTask) m_lstStage.end = pTask->m_pStgPrev;            
        }
        
        // 
        // インスタンスを破棄
        KLBDELETE(pTask);
        pTask = NULL;

        pTask = pNext;
    }
    m_currentTask = NULL;

	m_bKilling = false;

	// 2013.02.28  executeの最初でしか初期化されない->reboot時に前のが残ったままなので、ここでも初期化処理を入れておく
	m_lstRemove.begin = m_lstRemove.end = NULL;
}

void
CKLBTaskMgr::dump() {
	FILE* pFile = CPFInterface::getInstance().client().getShellOutput();
	fprintf(pFile,"==== Task Instances List ====\n");
	int count = 0;
    for(int i = 0; i < CKLBTask::P_MAX; i++) {
        for(CKLBTask* pTask = m_lstTask[i].begin; pTask; pTask = pTask->m_pExeNext) {
			fprintf(pFile,"[T%4i] Phase : %i Task : %8lX [%s] Type:%s\n",
				count++,
				i,
				reinterpret_cast<uintptr_t>(pTask),
				(pTask->m_activeStatus > 0) ? "ACTIVE" : "SLEEP ",
				IFactory::getClassName(pTask->getClassID())
			);
		}
	}
	fprintf(pFile,"==== Task Instances List (%i Tasks) ====\n",count);
}

bool
CKLBTaskMgr::execute(u32 deltaT)
{
    // すべてのタスクを呼び出す前に、削除リストを初期化する。
    m_lstRemove.begin = m_lstRemove.end = NULL;
    
	// フレームID更新: 16bit の値が毎フレーム変わる。
	m_frameId = (++m_frameId) & 0xffff;

    // 全タスク呼び出し
    int i;
    CKLBTask * pTask;
	m_startTime = CPFInterface::getInstance().platform().nanotime();
	s64 scriptTime;
	// s64 lastTime = time;
	// s64 execTime[30];

    for(i = 0; i < CKLBTask::P_MAX; i++) {

#ifdef DEBUG_MENU
		// デバッグモード用。デバッグモードが使うフェーズ以外すべてを停止させる。
		if (m_bDbgPause &&(i > CKLBTask::P_DBGMENU && i < CKLBTask::P_DRAW)) continue;
#endif
		// ポーズ中であれば、P_PREV - P_JUDGE はスキップする。
        if (m_bPause && (i >= CKLBTask::P_PREV && i < CKLBTask::P_DRAW)) continue;
        // フリーズ中(pauseGame)はINPUT系と、それに準ずる重要タスク以外はスキップする
		if (m_bFreeze && (i > CKLBTask::P_IMPORTANT && i < CKLBTask::P_DRAW)) continue;
#ifdef DEBUG_PERFORMANCE
		if (i == CKLBTask::P_SCRIPT) {
			scriptTime = CPFInterface::getInstance().platform().nanotime();
		}
#else
        scriptTime = 0;
#endif

        for(pTask = m_lstTask[i].begin; pTask; pTask = pTask->m_pExeNext) {
            m_currentTask = pTask;
			// taskCount++;

            // 開始時刻の取得
#ifdef DEBUG_PERFORMANCE
            s64 ntbegin = CPFInterface::getInstance().platform().nanotime();
#endif

            
            // ポーズ状態になければexecute()を実行。
			// If 1xxxxxxx	: Sleeping
			// If 00000000  : Active but nothing to do : same as 1xxxxxxx
			// If 0???????  : Execute
			if(pTask->m_activeStatus > 0) {
				pTask->execute(deltaT);
			}

            // 終了時刻の取得
#ifdef DEBUG_PERFORMANCE
            s64 ntend = CPFInterface::getInstance().platform().nanotime();
			if (((ntend - ntbegin)/1000000) >= 3000) {
				DEBUG_PRINT("Task ClassID[%i] '%s' takes %i millisec to execute",pTask->getClassID(),IFactory::getClassName(pTask->getClassID()),(int)((ntend - ntbegin)/1000000));
			}
#endif
        }

		// execTime[i] = CPFInterface::getInstance().platform().nanotime() - time;
#ifdef DEBUG_PERFORMANCE
		if (i == CKLBTask::P_SCRIPT) {
			m_scriptTime = CPFInterface::getInstance().platform().nanotime() - scriptTime;
		}
#else
        m_scriptTime = 0;
#endif
    }
	// printf("\n");

    // ステージタスク破棄コマンドが出ていたら、ステージタスクを破棄対象に加える
    if(m_bStageClear) {
        for(pTask = m_lstStage.begin; pTask; pTask = pTask->m_pStgNext) {
            pTask->kill();  // 削除リストに追加(親子関係を加味してkill()で登録)
        }
        m_bStageClear = false;
    }
        
    // 削除リストに登録済みのタスクを実行リストから削除し、インスタンスを delete する。
	remove_killlist();
    
#if defined (DEBUG_MEMORY)
    // トラッキングのフレームを更新
    CTracker::updateFrame();
#endif

	m_currentTask = NULL;
    
    return m_bExit;
}

void
CKLBTask::interposeTimer(CKLBTask* pTimer) {
	if(pTimer) {
		pTimer->m_pParent	= m_pParent;
		pTimer->m_pBrsPrev	= NULL;
		pTimer->m_pBrsNext	= NULL;
		pTimer->m_lstChild.begin	= this;	
		pTimer->m_lstChild.end		= this;	
	
		m_pParent	= pTimer;
	}
}
