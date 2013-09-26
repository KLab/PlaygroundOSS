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
	public class CKLBUITouchPad : CKLBTask
	{
		#region DllImports
        // pParent : CKLBTask*
        // return : CKLBUITouchPad*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUITouchPad_create(IntPtr pParent, bool modal);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUITouchPad_setGroup(IntPtr p, IntPtr group_name);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUITouchPad_setLock(IntPtr p, bool lock_mode);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUITouchPad_setGetAll(IntPtr p, bool bAll);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_TouchPad"/*, typeof(CKLBUITouchPad)*/);

        public CKLBUITouchPad(CKLBTask parent, CallBack callback, bool modal = false)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUITouchPad_create(parent != null ? parent.CppObject : IntPtr.Zero, modal);
            NativeManagement.intercepCppError();
            bind(ptr);
            m_callback = callback;
        }

        public CKLBUITouchPad() : base(s_classID) { }

        #endregion

        #region CallBacks

        //the "type" parameter is an ETYPE enum
        public delegate void CallBack(CKLBUITouchPad caller, uint execount, uint type, uint id, int x, int y);
        
        private CallBack m_callback;

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerUUUII(callBackFunction));
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName = null)
        {
            m_callback = (CallBack)anyDelegate;
        }

        public virtual void callBackFunction(uint execount, uint type, uint id, int x, int y)
        {
            if(m_callback != null)
            {
                m_callback(this, execount, type, id, x, y);
            }
            else
            {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        #endregion

        public enum ETYPE
        {
            TAP,
            DRAG,
            RELEASE
        }

        public void setGetAll(bool bGetAll)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUITouchPad_setGetAll(CppObject, bGetAll);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
		public void setLock(bool bLock)
		{
    	    if(CppObject != IntPtr.Zero) {
				CKLBUITouchPad_setLock(CppObject, bLock);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
        
        public bool setGroup(String group_name) 
		{
			if(CppObject != IntPtr.Zero) {
				return CKLBUITouchPad_setGroup(CppObject, __MarshallingUtils.NativeUtf8FromString(group_name));
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
	}
}
