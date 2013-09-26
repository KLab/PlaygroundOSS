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
    public class CKLBAsyncLoader : CKLBTask
    {
        #region DllImports
        
        // pParentTask  : CKLBTask
        // assets       : const char**
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBAsyncLoader_create(IntPtr pParentTask, IntPtr[] assets, uint count, uint datasetID);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBAsyncLoader_getProcessCount(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBAsyncLoader_getTotalCount(IntPtr p);
        #endregion

        #region Constructors
        static uint s_classID = __FrameworkUtils.RegisterClass("UTIL_AsyncLoader"/*, typeof(CKLBAsyncLoader)*/);

        public CKLBAsyncLoader(CKLBTask pParent, String[] assets, uint datasetID, CallBack callback)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBAsyncLoader_create((pParent != null) ? pParent.CppObject : IntPtr.Zero, 
                                                 __MarshallingUtils.NativeUtf8ArrayFromStringArray(assets, assets.Length), (uint)assets.Length, datasetID);
            NativeManagement.intercepCppError();
            m_callback = callback;
            bind(ptr);
        }

        public CKLBAsyncLoader() : base(s_classID) { }
        #endregion

        #region CallBacks

        public delegate void CallBack(CKLBAsyncLoader caller, uint loaded, uint total);
        
        private CallBack m_callback;

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerUU(callBackFunction));
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName = null)
        {
            m_callback = (CallBack)anyDelegate;
        }

        public virtual void callBackFunction(uint loaded, uint total)
        {
            if(m_callback != null) {
                m_callback(this, loaded, total);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }
        #endregion

        public uint ProcessCount
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBAsyncLoader_getProcessCount(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
        }
        public uint TotalCount
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBAsyncLoader_getTotalCount(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
        }

    }
}
