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
    public class CKLBStoreService : CKLBTask
    {
        #region DllImports
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBStoreService_create();

        // items : const char**
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBStoreService_buyItems(IntPtr p, IntPtr item);

        // json : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBStoreService_getProducts(IntPtr p, IntPtr json, bool currency);
        #endregion

        #region Constructors
        static uint s_classID = __FrameworkUtils.RegisterClass("STORE_Service"/*, typeof(CKLBStoreService)*/);

        public CKLBStoreService(CallBack callback)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBStoreService_create();
            NativeManagement.intercepCppError();
            m_callback = callback;
            bind(ptr);
        }

        public CKLBStoreService() : base(s_classID) { }
        #endregion

        #region CallBacks

        public delegate void CallBack(CKLBStoreService caller, IClientRequest.EVENT_TYPE type, String itemID, String param);
        
        private CallBack m_callback;

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerUSS(callBackFunction));
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName = null)
        {
            m_callback = (CallBack)anyDelegate;
        }

        public virtual void callBackFunction(/* IClientRequest.EVENT_TYPE */ uint type, IntPtr itemID, IntPtr param)
        {
            if(m_callback != null) {
                m_callback(this, (IClientRequest.EVENT_TYPE)type, __MarshallingUtils.StringFromNativeUtf8(itemID), __MarshallingUtils.StringFromNativeUtf8(param));
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }
        #endregion

        public void buyItems(String item)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBStoreService_buyItems(CppObject, __MarshallingUtils.NativeUtf8FromString(item));
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void getProducts(String json, bool currency) {
            if(CppObject != IntPtr.Zero) {
                CKLBStoreService_getProducts(CppObject, __MarshallingUtils.NativeUtf8FromString(json), currency);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
    }
}