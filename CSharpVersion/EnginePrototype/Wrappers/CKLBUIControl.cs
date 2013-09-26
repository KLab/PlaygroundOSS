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
    public class CKLBUIControl : CKLBUITask
    {
        #region DllImports
        // pParent : CKLBTask*
        // return : CKLBUIControl*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBUIControl_create(IntPtr pParent);

		// group_name : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIControl_setGroup(IntPtr p, IntPtr groupName);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIControl_setMask(IntPtr p, ushort mask);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIControl_lock(IntPtr p, bool lockMode);
        #endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_Control"/*, typeof(CKLBUIControl)*/);

        public CKLBUIControl(CKLBTask parent, OnClickCallBack onClickCallBack, OnDragCallBack onDragCallBack)
            : base(s_classID) 
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIControl_create(parent != null ? parent.CppObject : IntPtr.Zero);
            NativeManagement.intercepCppError();
            bind(ptr);
            m_onDragCallBack = onDragCallBack;
            m_onClickCallBack = onClickCallBack;
        }

        public CKLBUIControl() : base(s_classID) { }

        #endregion
        
        #region CallBacks

        public delegate void OnClickCallBack    (CKLBUIControl caller, int x, int y);
        public delegate void OnDblClickCallBack (CKLBUIControl caller, int x, int y);
        public delegate void OnDragCallBack     (CKLBUIControl caller, EMODE mode, int x, int y, int mvX, int mvY);
        public delegate void OnPinchCallBack    (CKLBUIControl caller, EMODE mode, float pinch, float rotation);
        public delegate void OnLongTapCallBack  (CKLBUIControl caller, uint elapsedTime, int x, int y);

        private OnDragCallBack m_onDragCallBack;            // callback number 0
        private OnPinchCallBack m_onPinchCallBack;          // callback number 1
        private OnClickCallBack m_onClickCallBack;          // callback number 2
        private OnDblClickCallBack m_onDblClickCallBack;    // callback number 3
        private OnLongTapCallBack m_onLongTapCallBack;      // callback number 4

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerUIIII  (onDragCallBackFunction),      0);
            registerCallBack(new NativeManagement.FunctionPointerUFF    (onPinchCallBackFunction),     1);
            registerCallBack(new NativeManagement.FunctionPointerII     (onClickCallBackFunction),     2);
            registerCallBack(new NativeManagement.FunctionPointerII     (onDblClickCallBackFunction),  3);
            registerCallBack(new NativeManagement.FunctionPointerUII    (onLongTapCallBackFunction),   4);
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName)
        {
		/* To support in compiler
            switch(delegateName)
            {
                case "onDrag":
                    m_onDragCallBack = (OnDragCallBack)anyDelegate;
                    break;
                case "onPinch":
                    m_onPinchCallBack = (OnPinchCallBack) anyDelegate;
                    break;
                case "onClick":
                    m_onClickCallBack = (OnClickCallBack)anyDelegate;
                    break;
                case "onDblClick":
                    m_onDblClickCallBack = (OnDblClickCallBack)anyDelegate;
                    break;
                case "onLongtap":
                    m_onLongTapCallBack = (OnLongTapCallBack)anyDelegate;
                    break;
                default:
                    throw new CKLBException("Unvalid delegate name");
            }
			*/

			if(delegateName == "onDrag")
            {
                m_onDragCallBack = (OnDragCallBack)anyDelegate;
            }
            else if(delegateName == "onPinch")
            {
                m_onPinchCallBack = (OnPinchCallBack)anyDelegate;
            }
            else if(delegateName == "onClick")
            {
                m_onClickCallBack = (OnClickCallBack)anyDelegate;
            }
            else if(delegateName == "onDblClick")
            {
                m_onDblClickCallBack = (OnDblClickCallBack)anyDelegate;
            }
            else if(delegateName == "onLongtap")
            {
                m_onLongTapCallBack = (OnLongTapCallBack)anyDelegate;
            }
            else
            {
                throw new CKLBException("Unvalid delegate name");
            }
        }

        public virtual void onClickCallBackFunction(int x, int y)
        {
            if(m_onClickCallBack != null)
            {
                m_onClickCallBack(this, x, y);
            }
            else
            {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }
        public virtual void onDragCallBackFunction(uint /*EMODE*/ mode, int x, int y, int mvX, int mvY)
        {
            if(m_onDragCallBack != null)
            {
                m_onDragCallBack(this, (EMODE)mode, x, y, mvX, mvY);
            }
            else
            {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }
        public virtual void onPinchCallBackFunction(uint /*EMODE*/ mode, float pinch, float rotation)
        {
            if(m_onPinchCallBack != null)
            {
                m_onPinchCallBack(this, (EMODE)mode, pinch, rotation);
            }
            else
            {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }
        public virtual void onDblClickCallBackFunction(int x, int y)
        {
            if(m_onDblClickCallBack != null)
            {
                m_onDblClickCallBack(this, x, y);
            }
            else
            {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }
        public virtual void onLongTapCallBackFunction(uint elapsedTime, int x, int y)
        {
            if(m_onLongTapCallBack != null)
            {
                m_onLongTapCallBack(this, elapsedTime, x, y);
            }
            else
            {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        #endregion

        public enum EMODE : uint
        {
            TAP,
            DRAG,
            RELEASE
        }
        public enum EMASK : ushort {
	        MASK_CLICK     = 0x0001,
	        MASK_DRAG      = 0x0002,
	        MASK_PINCH     = 0x0004,
	        MASK_DBLCLICK  = 0x0008,
	        MASK_LONGTAP   = 0x0010
        };

        public bool setGroup(String groupName) 
		{
			if(CppObject != IntPtr.Zero) {
				return CKLBUIControl_setGroup(CppObject, __MarshallingUtils.NativeUtf8FromString(groupName));
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
        public void setMask(EMASK mask)
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUIControl_setMask(CppObject, (ushort)mask);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
        public void setLock(bool lockBool)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIControl_lock(CppObject, lockBool);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
    }
}
