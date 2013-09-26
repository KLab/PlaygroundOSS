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
using System;
using System.Runtime.InteropServices;

namespace EnginePrototype
{
    /// <summary>
    /// A task is the basic object instance in our framework.
    /// Everything in a game is based on tasks from network to rendering or event processing.
    /// 
    /// Tasks are executed in a specific order called phase (See ETASKPhase enum).
    /// 
    /// Inside a phase, order is not garanteed, so multiple tasks inside the same phase
    /// have no garanteed order.
    /// 
    /// Task can have child/parent relationship and it is possible for parents to have different phases from their children.
    /// 
    /// When a parent task dies, all the subtree of task also dies within the same frame.
    /// 
    /// Because of possible relations that could occur between tasks. All tasks are killed at the end of the frame
    /// and not right away. Thus allowing dependancy or execution order to be impactless when a task dies.
    /// But still, tasks should not be modified by other tasks except the "scripting" itself.
    /// 
    /// As an example, a progress bar is modified by the game logic tasks performed before the progress bar task.
    /// But any other task should not modify the progress bar too, or have its own logic based on the output from the progress bar.
    /// 
    /// Consider that we could one day declare tasks to be multithreaded and executed seperatly on another CPU.
    /// Thus there must be no dependancy between tasks in any way and only the main game logic should be able to set/get things
    /// with tasks.
    /// 
    /// </summary>
    public class CKLBTask : GameObject
    {
        #region DllImports
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Task_kill(IntPtr task);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Task_setStageTask(IntPtr task);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Task_clearStageTask();

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Task_setPause(IntPtr task, bool bPause, bool bRecursive);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Task_setManagerPause(bool bPause);

        // pTask & pTimer : CKLBTask
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Task_interposeTimer(IntPtr pTask, IntPtr pTimer);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool Task_isKill(IntPtr task);
        #endregion

        #region Constructors
        // Just throws the classID to GameObject
        internal CKLBTask(uint classID) : base(classID) { 
            m_timer = null;
        }

        #endregion

        #region CallBacks
        public delegate void onDieCallBack(CKLBTask caller);

        private onDieCallBack m_callback;

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerV(onDieCallBackFunction), 5);
        }

        public void setOnDieCallBack(onDieCallBack anyDelegate)
        {
            m_callback = anyDelegate;
        }

        public virtual void onDieCallBackFunction()
        {
            if(m_callback != null) {
                m_callback(this);
            } /*else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }*/
        }

        #endregion

        private CKLBIntervalTimer m_timer;

        /// <summary>
        /// Phase where the task can be executed.
        /// </summary>
        public enum ETASK_PHASE
        {
            P_BEGIN     = 0,        //!< フレーム開始時の処理。描画エンジンのリフレッシュ処理等はこのフェーズに登録。

            P_INPUT     = 1,        //!< ユーザ操作の取得など

		    P_DBGSIGN   = 2,		//!< デバッグコマンド受付
		    P_DBGMENU   = 3,		//!< デバッグメニュー処理

		    P_UIPREV    = 4,		//!< 標準UIパーツより先に処理するUIフェーズ

		    P_SCRIPT    = 5,       //!< スクリプト的な処理タスクはこのフェーズに登録

		    P_UIPROC    = 6,		//!< UIパーツの処理を行うフェーズ
		    P_UIAFTER   = 7,		//!< 他のUIパーツを子タスクとして使用するUIタスク用のフェーズ

            P_MENU      = 8,         //!< メニューフェーズ: メニュー処理タスクはこのフェーズに登録。ポーズ中でも実行される。

            // P_PREV, P_NORMAL, P_AFTER はポーズ中実行されない。
            P_PREV      = 9,         //!< (ポーズ中停止)通常タスク以前に処理しなければならないもの
            P_NORMAL    = 10,      //!< (ポーズ中停止)通常のタスクはここで処理
            P_AFTER     = 11,       //!< (ポーズ中停止)通常のタスクが終わった後に処理しなければならないもの
		    P_JUDGE     = 12,       //!< ゲーム中の判定など

            P_DRAW      = 13,        //!< 描画処理をキックするタスク等はここに登録
            P_GC		= 14,
            P_END       = 15,         //!< 描画キック後に行う処理があればここに登録

            P_MAX       = 16          //!< フェーズ総数
        }

        /// <summary>
        /// Kills (remove and destroy) the task from the game. Object stays valid until the end of the frame, after all tasks have been executed.
        /// </summary>
        public void kill()
        {
            if(CppObject != IntPtr.Zero) {
                onDieCallBackFunction();
                IntPtr cppObject = CppObject;
                unbind();
                Task_kill(cppObject);
            }
        }

        /// <summary>
		/// [TODO]
        /// </summary>
        public bool isKill()
        {
            if(CppObject != IntPtr.Zero) {
                return Task_isKill(CppObject);
            }
            return true;
        }

        /// <summary>
        /// When disposing the ressource, we automatically kill the associated task.
        /// </summary>
        public override void Dispose()
        {
            kill();
			base.Dispose();
        }

        /// <summary>
        /// Pause or reactivate execution of a task.
        /// If the task has children it is possible to decide if the children are affected or not.
        /// Note that task by default are active.
        /// </summary>
        /// <param name="bPause">True : Pause the task, False : Activate the task.</param>
        /// <param name="bRecursive">Apply also the bPause to children (true) also or not (false)</param>
        public void setPause(bool bPause, bool bRecursive)
        {
            if(CppObject != IntPtr.Zero) {
                Task_setPause(CppObject, bPause, bRecursive);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        /// <summary>
        /// Assign a timer to the task. When the timer reach its target time, the task is killed.
        /// </summary>
        /// <param name="mode">Timer in millisecond or frame</param>
        /// <param name="time">Amount of time</param>
        public void setLifeTime(CKLBIntervalTimer.ETIMERMODE mode, uint time)
        {
            if(m_timer == null) {
                CKLBIntervalTimer.CallBack cb = delegate(CKLBIntervalTimer caller) {};
                m_timer = new CKLBIntervalTimer(null, time, cb, false, mode);
                Task_interposeTimer(CppObject, m_timer.CppObject);
            } else {
                m_timer.Interval = time;
            }
        }

        /// <summary>
        /// Allow the task to be associated to a global group of task called "stage".
        /// This is usefull avoiding to remember each task to kill when the game
        /// need a complete changes of tasks and many tasks need to be killed at once.
        /// Just call this function to register the task to the global stage.
        /// 
        /// See clearStage()
        /// See ? global clearStage ? Not static from task ?
        /// </summary>
        public void stageOnly()
        {
            if(CppObject != IntPtr.Zero) {
                Task_setStageTask(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        /// <summary>
        /// Remove a specific task from the stage.
        /// See stageOnly()
        /// </summary>
        /// <param name="task">task to be removed</param>
        public static void clearStage()
        {
            Task_clearStageTask();
        }

        /// <summary>
        /// Allow to stop/restart the task manager and freeze/run again all tasks instances in the game.
        /// Note : internal tasks not seen by the game develloper do not stop, things like rendering as an example.
        /// </summary>
        /// <param name="bPause"></param>
        public static void setManagerPause(bool bPause)
        {
            Task_setManagerPause(bPause);
        }
    }
}
