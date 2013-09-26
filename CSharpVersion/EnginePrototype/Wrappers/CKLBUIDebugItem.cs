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
	public class CKLBUIDebugItem : CKLBUITask
	{
		#region DllImports
        //return : CKLBUIDebugItem*
        // pParent : CKLBUITask*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIDebugItem_create(IntPtr pParent,uint order, float x, float y, uint argb, IntPtr font, uint size, IntPtr text, uint id);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIDebugItem_getOrder(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIDebugItem_setOrder(IntPtr p, uint order);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIDebugItem_getColor(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIDebugItem_setColor(IntPtr p, uint order);
		
		// return and font : const char *
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static IntPtr CKLBUIDebugItem_getFont(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static void CKLBUIDebugItem_setFont(IntPtr p, IntPtr font);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIDebugItem_getSize(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIDebugItem_setSize(IntPtr p, uint order);
		
		// return and text : const char *
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static IntPtr CKLBUIDebugItem_getText(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static void CKLBUIDebugItem_setText(IntPtr p, IntPtr text);
		#endregion

        #region Constructors 

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_DbgLabel"/*, typeof(CKLBUIDebugItem)*/);

        //a string is given to the constructor which creates a font object
        public CKLBUIDebugItem(CKLBUITask parent, uint order, float x, float y, uint argb, String font_name, uint font_size, String text, uint cmdID, CallBack callback)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIDebugItem_create(parent != null ? parent.CppObject : IntPtr.Zero, order, x, y, argb, __MarshallingUtils.NativeUtf8FromString(font_name), font_size, __MarshallingUtils.NativeUtf8FromString(text), cmdID);
            NativeManagement.intercepCppError();
            bind(ptr);
            m_callback = callback;
        }

        public CKLBUIDebugItem() : base(s_classID) { }
        
        #endregion

        #region CallBacks

        public delegate void CallBack(CKLBUIDebugItem caller, uint cmdID);

        private CallBack m_callback;

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerU(callBackFunction));
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName = null)
        {
            m_callback = (CallBack)anyDelegate;
        }

        public virtual void callBackFunction(uint cmdID)
        {
            if(m_callback != null)
            {
                m_callback(this, cmdID);
            }
            else
            {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        #endregion

        public uint     Order
		{
			get
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUIDebugItem_getOrder(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIDebugItem_setOrder(CppObject,value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
	    public String   Font
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUIDebugItem_getFont(CppObject));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIDebugItem_setFont(CppObject, __MarshallingUtils.NativeUtf8FromString(value));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
		public uint     Size
		{
			get
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUIDebugItem_getSize(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIDebugItem_setSize(CppObject,value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public uint     TextArgb
		{
			get
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUIDebugItem_getColor(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIDebugItem_setColor(CppObject,value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public String   Text
		{
			get
			{
				if(CppObject != IntPtr.Zero) {
					return __MarshallingUtils.StringFromNativeUtf8(CKLBUIDebugItem_getText(CppObject));
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIDebugItem_setText(CppObject, __MarshallingUtils.NativeUtf8FromString(value));
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
	}
}
