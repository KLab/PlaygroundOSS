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
using System.Runtime.InteropServices; // Contains DllImport

namespace EnginePrototype
{
	public class CKLBUIWebArea : CKLBUITask
	{

		#region DllImports
        // pParent : CKLBUITask*
        // url : const char*
        // return : CKLBUIWebArea*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIWebArea_create(IntPtr pParent, bool mode, float x, float y, float width, float height, IntPtr url);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIWebArea_getWidth(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIWebArea_setWidth(IntPtr p, int width);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIWebArea_getHeight(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIWebArea_setHeight(IntPtr p, int height);
		
		// text and return : const char * : 
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static IntPtr CKLBUIWebArea_getText(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static void CKLBUIWebArea_setText(IntPtr p, IntPtr text);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIWebArea_setScalesPageToFit(IntPtr p, bool b);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIWebArea_setBgColor(IntPtr p, uint argb);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_WebView"/*, typeof(CKLBUIWebArea)*/);

        public CKLBUIWebArea(CKLBUITask parent, bool mode, float x, float y, float width, float height, String url, CallBack callback)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIWebArea_create(parent != null ? parent.CppObject : IntPtr.Zero, mode, x, y, width, height, __MarshallingUtils.NativeUtf8FromString(url));
            NativeManagement.intercepCppError();
            bind(ptr);
            m_callback = callback;
        }

        public CKLBUIWebArea() : base(s_classID) { }

        #endregion

        #region CallBacks

        public delegate void CallBack(CKLBUIWebArea caller, uint uint1, String url);
        
        private CallBack m_callback;

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerUS(callBackFunction));
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName = null)
        {
            m_callback = (CallBack)anyDelegate;
        }

        // url : const char* from Cpp
        public virtual void callBackFunction(uint uint1, IntPtr url)
        {
            if(m_callback != null)
            {
                m_callback(this, uint1, __MarshallingUtils.StringFromNativeUtf8(url));
            }
            else
            {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }
        #endregion

        public int Width
		{
			get 
			{ 
				if(CppObject != IntPtr.Zero)
					return CKLBUIWebArea_getWidth(CppObject);
				else
					throw new CKLBExceptionNullCppObject();
			}
			set 
			{
				if(CppObject != IntPtr.Zero)
					CKLBUIWebArea_setWidth(CppObject,value);
				else
					throw new CKLBExceptionNullCppObject();
			}
		}
        public int Height
		{
			get 
			{
				if(CppObject != IntPtr.Zero)
					return CKLBUIWebArea_getHeight(CppObject);
				else
					throw new CKLBExceptionNullCppObject();
			}
			set 
			{
				if(CppObject != IntPtr.Zero)
					CKLBUIWebArea_setHeight(CppObject,value);
				else
					throw new CKLBExceptionNullCppObject();
			}
		}
        public void getSize(out Size size)
        {
            if(CppObject != IntPtr.Zero)
            {
                size.width = CKLBUIWebArea_getWidth(CppObject);
                size.height = CKLBUIWebArea_getHeight(CppObject);
            }
            else
                throw new CKLBExceptionNullCppObject();
        }
        public void setSize(Size size)
        {
            if(CppObject != IntPtr.Zero)
            {
                CKLBUIWebArea_setWidth(CppObject, size.width);
                CKLBUIWebArea_setHeight(CppObject, size.height);
            }
            else
                throw new CKLBExceptionNullCppObject();
        }
        public void setSize(int width, int height)
        {
            CKLBUIWebArea_setWidth(CppObject, width);
            CKLBUIWebArea_setHeight(CppObject, height);
        }
		public String Url
		{ 
			get 
			{
				if(CppObject != IntPtr.Zero)
					return __MarshallingUtils.StringFromNativeUtf8(CKLBUIWebArea_getText(CppObject));
				else
					throw new CKLBExceptionNullCppObject();
			}
			set 
			{
				if(CppObject != IntPtr.Zero)
                    CKLBUIWebArea_setText(CppObject, __MarshallingUtils.NativeUtf8FromString(value));
				else
					throw new CKLBExceptionNullCppObject();
			}
		}

        public void setScalesPageToFit(bool b)
        {
            if(CppObject != IntPtr.Zero) {
				CKLBUIWebArea_setScalesPageToFit(CppObject, b);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
        }
        
        public void setBgColor(uint argb)
        {
            if(CppObject != IntPtr.Zero) {
				CKLBUIWebArea_setBgColor(CppObject, argb);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
        }
	}
}
