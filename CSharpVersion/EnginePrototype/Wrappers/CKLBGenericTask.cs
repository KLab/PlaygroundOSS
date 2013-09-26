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
    public class CKLBGenericTask : CKLBTask
    {
        #region DllImports
        // pParent : CKLBTask*
        // arr_index : const char*
        // return : CKLBGenericTask*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBGenericTask_create(IntPtr pParent, uint phase);
        #endregion

        #region Constructors
        static uint s_classID = __FrameworkUtils.RegisterClass("TASK_Generic"/*, typeof(CKLBGenericTask)*/);

        public CKLBGenericTask(CKLBTask parent, CKLBTask.ETASK_PHASE phase, ExecuteCallBack executeCallBack, DieCallBack dieCallBack)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBGenericTask_create(parent != null ? parent.CppObject : IntPtr.Zero, (uint)phase);
            NativeManagement.intercepCppError();
            bind(ptr);
            m_executeCallBack = executeCallBack;
            m_dieCallBack = dieCallBack;
        }
        public CKLBGenericTask() : base(s_classID) { }
        #endregion

        #region CallBacks

        public delegate void ExecuteCallBack(CKLBGenericTask caller, uint deltaTime);
        public delegate void DieCallBack(CKLBGenericTask caller);

        private ExecuteCallBack m_executeCallBack;  // callback number 0
        private DieCallBack     m_dieCallBack;      // callback number 1

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerU(executeCallBackFunction),    0);
            registerCallBack(new NativeManagement.FunctionPointerV(dieCallBackFunction),        1);
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName)
        {
            if(delegateName == "execute")
            {
                m_executeCallBack = (ExecuteCallBack)anyDelegate;
            }
            else if(delegateName == "die")
            {
                m_dieCallBack = (DieCallBack)anyDelegate;
            }
            else {
                throw new CKLBException("Unvalid delegate name");
            }
        }

        public virtual void executeCallBackFunction(uint deltaTime)
        {
            if(m_executeCallBack != null)
            {
                m_executeCallBack(this, deltaTime);
            }
            else
            {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        public virtual void dieCallBackFunction()
        {
            if(m_dieCallBack != null) {
                m_dieCallBack(this);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }
        #endregion
    }
}
