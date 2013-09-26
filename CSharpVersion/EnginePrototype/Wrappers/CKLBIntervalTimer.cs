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
	public class CKLBIntervalTimer : CKLBUITask
	{
		#region DllImports
        // pParent : CKLBUITask*
        // return : CKLBIntervalTimer*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBIntervalTimer_create(IntPtr pParent, uint interval, bool repeat, byte mode);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBIntervalTimer_getTimerID(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBIntervalTimer_setTimerID(IntPtr p, uint ID);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBIntervalTimer_getRepeat(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBIntervalTimer_setRepeat(IntPtr p, bool boolean);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBIntervalTimer_getInterval(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBIntervalTimer_setInterval(IntPtr p, uint interval);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static byte CKLBIntervalTimer_getMode(IntPtr p);
		#endregion

        #region Constructors
        static uint s_classID = __FrameworkUtils.RegisterClass("UTIL_IntervalTimer"/*, typeof(CKLBIntervalTimer)*/);

        public CKLBIntervalTimer(CKLBTask parent, uint interval, CallBack callback, bool repeat = false, ETIMERMODE mode = ETIMERMODE.INTERVALTIMER_TIME) 
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBIntervalTimer_create(parent != null ? parent.CppObject : IntPtr.Zero, interval, repeat, (byte)mode);
            NativeManagement.intercepCppError();
            bind(ptr);

            m_callback = callback;
        }

        public CKLBIntervalTimer() : base(s_classID) { }
        #endregion

        #region CallBacks

        public delegate void CallBack(CKLBIntervalTimer caller);

        private CallBack m_callback;

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerV(callBackFunction));
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName = null)
        {
            m_callback = (CallBack)anyDelegate;
        }

        public virtual void callBackFunction()
        {
            if(m_callback != null) {
                m_callback(this);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        #endregion

        public enum ETIMERMODE : byte
        {
            INTERVALTIMER_TIME = 0,
            INTERVALTIMER_FRAME
        }

        public ETIMERMODE   Mode 
        {
            get
			{
				if(CppObject != IntPtr.Zero) {
					return (ETIMERMODE)CKLBIntervalTimer_getMode(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
            //set { throw new CKLBExceptionForbiddenMethod(); }
        }
		public uint         Interval
		{
			get
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBIntervalTimer_getInterval(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBIntervalTimer_setInterval(CppObject,value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public bool         Repeat
		{
			get
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBIntervalTimer_getRepeat(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBIntervalTimer_setRepeat(CppObject,value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
	}
}
