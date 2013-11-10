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
/*!
    \brief  Root Task Class (CKLBTask) and Task Manager (CLKBTaskMgr) definition
    \file   CKLBTask.h
  */
#ifndef CKLBTask_h
#define CKLBTask_h

#include <string.h>
#include "CKLBObject.h"

class CKLBTask;
class CKLBTaskMgr;

class CKLBRegistedTaskList
{
public:
	CKLBRegistedTaskList();
	virtual ~CKLBRegistedTaskList();

	void addTask(CKLBTask * pTask);
	void killTaskList(bool kill_task = true);

private:
	struct TASKITEM {
		TASKITEM	*	prev;
		TASKITEM	*	next;

		CKLBTask	*	pTask;
	};

	TASKITEM	*	m_begin;
	TASKITEM	*	m_end;
};


struct TASK_LIST {
    CKLBTask * begin;
    CKLBTask * end;
};

// Change Task Execution Flag because order changed.
#define	REFRESH_A			setStatusFlag(0x1)
#define CHANGE_A			getStatusFlag(0x1)
#define RESET_A				resetStatusFlag(0x1)

// Change Task Execution Flag because geometry related property changed
#define REFRESH_B			setStatusFlag(0x2)
#define CHANGE_B			getStatusFlag(0x2)
#define RESET_B				resetStatusFlag(0x2)

// Change Task Execution Flag because animation is active.
#define REFRESH_C			setStatusFlag(0x4)
#define CHANGE_C			getStatusFlag(0x4)
#define RESET_C				resetStatusFlag(0x4)

// Change Task Execution Flag because animation is active.
#define REFRESH_D			setStatusFlag(0x8)
#define CHANGE_D			getStatusFlag(0x8)
#define RESET_D				resetStatusFlag(0x8)

// Change Task Execution Flag because animation is active.
#define REFRESH_E			setStatusFlag(0x10)
#define CHANGE_E			getStatusFlag(0x10)
#define RESET_E				resetStatusFlag(0x10)

//! ゲームタスククラス
/*!
  ゲーム中のすべての処理はフレーム単位で行われ、それぞれの処理単位は「タスク」と呼ばれるクラスで管理されます。
 「フレーム単位で実行される処理」は、すべて「タスク」として実装することで、
  ゲームプログラムは一貫性が保たれ、またシンプルなものになります。

  CKLBTask はゲーム中のすべてのタスクの基底クラスとなり、実装されたタスククラスのインスタンスを
  タスクマネージャに登録することで、ゲーム中の処理として実行されるようになります。
  */

/*!
* \class CKLBTask
* \brief Engine Root Task class
* 
* The Game Engine is based on a frame-by-frame processing.
* Each unit processed each frame is managed by the class CKLBTask.
* CKLBTask is the base class for all the tasks of the engine.
* By registering a task in the TaskManager it will be run as a process in the game.
*/
class CKLBTask : public CKLBObjectScriptable
{
    friend class CKLBTaskMgr;
public:
    
    typedef enum {
        TASK_SIMPLE,
        TASK_LUA_BASIC,
        TASK_LUA_PROPERTY,
        TASK_LUA_UI
    } TASKTYPE;

    virtual TASKTYPE getTaskType();


    //! タスク登録フェーズ値定義
    /*!
     タスクシステムにはTASK_PHASEに定義された複数のフェーズがあり、
     なおかつそれぞれのフェーズに対応するタスクの実行リストを持ちます。
     
     登録されているタスクは必ず P_BEGIN から P_END 方向に向かって、
     それぞれの実行フェーズに対応する実行リストに登録されているタスクが登録順に実行されます。
     
     - 要点
        -# 異なるフェーズに登録されたタスク間における実行順は、登録順に関わらず必ずフェーズ順になることが保証される。
        -# 同じフェーズに登録されたタスク間における実行順は、必ず登録順になることが保証されている。
        .
     .
     
     通常のゲームタスクは P_PREV, P_NORMAL, P_AFTER に登録するタスクとして作成します。
     この内、ほとんどのものは P_NORMAL として作るべきであり、「必ず先に処理すべきもの」
     「必ず後に処理すべきもの」のために P_PREV, P_AFTER が用意されています。
     
     これらのフェーズは通常のゲーム進行に伴うフェーズであるため、タスクマネージャが「ポーズ状態」に
     されている状態ではフレーム処理(execute()の呼び出し)が行われません。
     
     これら以外は特殊な用途を持つフェーズであるため、原則そのフェーズに登録すべきタスク以外は登録するべきではありません。
     */
    typedef enum {
        P_BEGIN 	= 0,		//!< フレーム開始時の処理。描画エンジンのリフレッシュ処理等はこのフェーズに登録。

        P_INPUT 	= 1,        //!< ユーザ操作の取得など
        P_IMPORTANT = 2,        //!< ポーズ・フリーズ中でも走らなければならないタスク
#ifdef DEBUG_MENU
		P_DBGSIGN 	= 3,		//!< デバッグコマンド受付
		P_DBGMENU 	= 4,		//!< デバッグメニュー処理
#endif

		P_UIPREV 	= 5,		//!< 標準UIパーツより先に処理するUIフェーズ

		P_SCRIPT 	= 6,       //!< スクリプト的な処理タスクはこのフェーズに登録

		P_UIPROC 	= 7,		//!< UIパーツの処理を行うフェーズ
		P_UIAFTER 	= 8,		//!< 他のUIパーツを子タスクとして使用するUIタスク用のフェーズ

        P_MENU 		= 9,         //!< メニューフェーズ: メニュー処理タスクはこのフェーズに登録。ポーズ中でも実行される。

        // P_PREV, P_NORMAL, P_AFTER はポーズ中実行されない。
        P_PREV 		= 10,         //!< (ポーズ中停止)通常タスク以前に処理しなければならないもの
        P_NORMAL 	= 11,      //!< (ポーズ中停止)通常のタスクはここで処理
        P_AFTER 	= 12,       //!< (ポーズ中停止)通常のタスクが終わった後に処理しなければならないもの
		P_JUDGE 	= 13,       //!< ゲーム中の判定など

        P_DRAW 		= 14,        //!< 描画処理をキックするタスク等はここに登録
        P_GC		= 15,
        P_END 		= 16,         //!< 描画キック後に行う処理があればここに登録

        P_MAX 		= 17          //!< フェーズ総数
    } TASK_PHASE;

public:
    //! 破棄指令
    /*!
        タスクに破棄指令を出します。
        破棄指令が出されたフレームの最後に die() が呼び出され、タスクのインスタンスが破棄されます。
        タスクが他のタスクと親子関係を持つ場合、子として登録されているタスク全てに対し、再帰的に kill() が呼び出されます。
     */
    void kill();

	//! 一時停止指令
	/*!
		タスクに一時停止指令を出します。
		bPause がtrue で一時停止、falseで解除になります。
	*/
	void setPause(bool bPause, bool bRecursive = true);

	void interposeTimer(CKLBTask* pTimer);

	virtual u32 getClassID();
protected:
    //! コンストラクタ
    /*!
     派生させて使うためのクラスなので、protected になっています。
     */
    CKLBTask();

    //! デストラクタ
    virtual ~CKLBTask();

    //! 破棄時の処理
    /*!
     タスクが扱うリソースは、タスク破棄の際に解放される必要があります。
     タスク初期化時に生成/確保されたリソースの破棄処理は、die() の中で実装します。

     die() は、そのフレームにおけるすべてのタスクのフレーム処理が終わった後に呼び出されます。
     */
    virtual void die();
 
    //! フレーム処理実行
    /*!
     \param deltaT  直前のフレームからの経過時間(単位: [ms])

     毎フレーム行う処理を部品化するものがタスクの役割です。そのタスクがフレーム中に行うべき処理は execute() の中で実装します。
     フレーム中で処理を止めると、以後のタスクの処理ができないので注意してください。
     */
    virtual void execute(u32 deltaT);

    //! 初期化時に使用する実行リストへの登録
    /*!
     \param pParent     親タスクインスタンスのポインタ
     \param ePhase      タスクを登録する実行フェーズ値
     
     タスクインスタンスをタスクマネージャの実行リストに登録します。
     この登録を行わなければタスクは実行されないため、必ずタスク初期化処理の中で呼び出し、
     実行リストへの登録を行う必要があります。
     
     タスクの実行リストへの登録は、タスクインスタンスの生成が完了していない状態で行うべきではありません。
     このため、コンストラクタ内やメンバの初期化が完了していない状態で呼び出すことは避けてください。
     
     また、pParent として指定される親タスクは、生成が完了し実行リストへの登録が完了しているタスクである必要があります。
     regist() が実行されていないタスクインスタンスのポインタを pParent に指定することは避けてください。
     */
    bool regist(CKLBTask * pParent = 0, TASK_PHASE ePhase = P_NORMAL);

	inline CKLBTask * getParent() const { return m_pParent; }

protected:
    void child(CKLBTask * pChild);
	virtual bool onPause(bool bPause);

	inline
	void setStatusFlag	(u8 mask)	{	klb_assert(mask<64,"Bit 0..5 only are usable"); m_activeStatus |=mask; }

	inline
	void resetStatusFlag(u8 mask)	{	klb_assert(mask<64,"Bit 0..5 only are usable"); m_activeStatus &=~mask; }

	inline
	u8	 getStatusFlag	(u8 mask)	{	return m_activeStatus & mask; }

	void setNotAlwaysActive()		{	m_activeStatus &= ~ALWAYS_ACTIVE; }
private:
    // 実行関連情報(std::list<...>が使えない場合を想定し、ポインタで実装)
    TASK_PHASE       m_ePhase;     // 自身の実行フェーズ
    // タスク間の親子関連情報
    CKLBTask       * m_pParent;    // 親タスクへのポインタ

    // 子タスクへのリストを持つ
    TASK_LIST m_lstChild;
 
    // 実行リスト用のリンク
    CKLBTask       * m_pExePrev;   // 実行フェーズリスト中の前のタスク
    CKLBTask       * m_pExeNext;   // 実行フェーズリスト中の次のタスク

    // 兄弟タスクへのリンク
    CKLBTask       * m_pBrsPrev;

    CKLBTask       * m_pBrsNext;

    // 死ぬときのタスクリスト用リンク
    CKLBTask       * m_pRmvPrev;
    CKLBTask       * m_pRmvNext;
    

    // ステージタスクとして登録された際のリンク
    CKLBTask       * m_pStgPrev;
    CKLBTask       * m_pStgNext;

	static const s8	ALWAYS_ACTIVE	= 1<<6;
	s8				m_activeStatus;
};

//! タスクマネージャクラス
/*!
 タスクマネージャクラスは、CKLBTask から派生したインスタンスを登録し、
 実行、管理を行う機能を持つSingletonクラスです。
 
 タスクの実行リストを持ち、登録されている CKLBTask の execute() を順次呼び出すことで
 1フレーム分全体の処理を行うのは CKLBTaskMgr の役割です。
 ゲーム中において動作している全タスク
 */
class CKLBTaskMgr
{
    friend class CKLBTask;
private:
    CKLBTaskMgr();
    virtual ~CKLBTaskMgr();
public:
    //! インスタンス取得
    /*!
     \return CKLBTaskMgr インスタンスの参照
     
     CKLBTaskMgr のインスタンスへの参照を取得する。
     */
    static CKLBTaskMgr& getInstance();

	//! Dump list of instanciated tasks.
	void dump();

	//! クリア処理
	/*!
	 登録されているすべてのタスクを破棄する。
	 終了処理に使用。
	 */
	void clearTaskList();

    //! ステージタスク登録
    /*!
     指定されたタスクをステージタスクとして登録する。
     */
    void registStageTask(CKLBTask * pTask);

    //! ステージタスククリア処理
    /*!
     ステージタスクとして登録されているタスクを全て破棄予約する。
     ステージ間の切り替えで使用。ステージタスク以外は破棄しない。
     */
    void clearStageTask();

	//! タスクポインタ有効確認
	/*!
	 指定されたタスクポインタが、実行リスト中に存在しているかを確認する。
	 デバッグ用機能なので、リリース版では無効化されるべき。
	*/
	bool isExistTask(CKLBTask * pTask);

	//! 登録されるタスクを記録するCKLBRegistedTaskListを指定する
	/*!
	 0 が指定されたら登録タスクの記録を行わない
	 */
	inline void setRegistedTaskList(CKLBRegistedTaskList * pRegList = 0) {
		m_pRegList = pRegList;
	}


    //! 1フレーム分の処理実行
    /*!
     \param deltaT  直前のフレームからの経過時間(単位[ms])
     
     実行リストに登録されている全 CKLBTask派生クラスのexecute()を呼び出し、1フレーム分の処理を行う。
     そのフレーム中に削除が指定されたタスクおよびその子タスクについては、すべての execute() を呼び出し終わった後に
     die() を呼び出し、インスタンスを削除する。
     */
    bool execute(u32 deltaT);

    //! ポーズ状態を指定する
    /*!
     \param bPause  ポーズ状態
     
     タスクマネージャのポーズ状態を指定します。
     bPause が true のときポーズ状態、false のとき通常実行状態になります。

     ポーズ状態では、CKLBTaskMgr::execute() を呼び出しても P_PREV,P_NORMAL,P_AFTER, P_JUDGE フェーズの
     タスクについては execute() が呼び出されなくなります。
     */
    inline bool setPause(bool bPause) { return m_bPause = bPause; }

    //! ポーズ状態の取得
    /*!
     \return 現在のポーズ状態
     
     タスクマネージャのポーズ状態を取得します。
     ポーズ状態については setPause() の解説も参照してください。
     */
    inline bool getPause() { return m_bPause; }

	inline bool isKilling() const { return m_bKilling; }

#ifdef DEBUG_MENU
	//! デバッグ用全停止指令
	/*!
		trueを与えることで、P_UIPREVからP_JUDGEまでの入力とデバッグ、描画を除いた
		すべてのフェーズの実行を一時停止します。
		falseで解除されます。
	*/
	bool setDbgPause(bool bPause) { return m_bDbgPause = bPause; }
#endif

    //! Exit
    /*!
    　タスクマネージャにExitフラグを立てます。
     そのフレーム以降execute()はfalseを返すようになります。
     この値は、フレーム駆動システム側にによってゲーム終了の指示として扱われます。
     */
    inline void			setExit			()					{ m_bExit = false; }

    inline CKLBTask *	getCurrentTask	()					{ return m_currentTask; }
    
    inline void			setCurrentTask	(CKLBTask * pTask)	{ m_currentTask = pTask; }

	inline u32			getFrameID		() const			{ return m_frameId; }

	//! 指定されたタスクがすでに削除予約されているか否かを返す
	bool is_remove(CKLBTask * pTask);

	inline void setFreeze	(bool bFreeze)	{ m_bFreeze = bFreeze;	}
	inline bool getFreeze	()				{ return m_bFreeze;		}

	inline s64 getStartTime	()				{ return m_startTime;	}
	inline s64 getScriptTime()				{ return m_scriptTime;	}

private:
    //! タスクを指定されたフェーズの実行リストに登録する
    bool regist(CKLBTask::TASK_PHASE ePhase, CKLBTask * pTask);
    
    //! 指定されたタスクを削除予約する。
    bool remove(CKLBTask * pTask);

	//! 削除リストに登録されているタスクを順に削除する
	void remove_killlist();

private:
    CKLBTask    *   m_currentTask;

    TASK_LIST       m_lstTask[ CKLBTask::P_MAX ];
    TASK_LIST       m_lstRemove;
    
    TASK_LIST       m_lstStage;

	// フレームID。毎フレーム値が更新される。同じフレームでは同じ値になる。
	u32				m_frameId;

    // Exitフラグ。ゲーム終了指示が出された際に true になる。
    bool            m_bExit;

    // ポーズ状態
    bool            m_bPause;     // ポーズ状態。true の時はポーズ状態として、P_PREV, P_NORMAL, P_AFTER をスキップする。

	// kill処理中フラグ
	bool			m_bKilling;	  // kill中は true。それ以外は false

	//
	s64				m_startTime;
	s64				m_scriptTime;

	// タスクリスト記録
	CKLBRegistedTaskList	*	m_pRegList;

#ifdef DEBUG_MENU
	bool			m_bDbgPause;
#endif

    // true にされたフレームの最後に、ステージタスクとして登録されている全タスクを破棄対象とする。
    bool            m_bStageClear;
	bool			m_bFreeze;
};


#endif
