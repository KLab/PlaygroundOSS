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
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace EnginePrototype
{
	public class CKLBUITextInput : CKLBUITask
	{
		#region DllImports
        // parent : CKLBUITask
        // defaultText : const char*
        // return : CKLBUITextInput*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBUITextInput_create(IntPtr parent, bool passwordMode, 
                                                            float x, float y, float width, float height, IntPtr defaultText, int widgetId,
                                                            int maxLen, uint charType);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUITextInput_getWidth(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUITextInput_setWidth(IntPtr p, uint width);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUITextInput_getHeight(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUITextInput_setHeight(IntPtr p, uint height);
		
		// return and text : const char *
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static IntPtr CKLBUITextInput_getText(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static void CKLBUITextInput_setText(IntPtr p, IntPtr text);

        // placeholder : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUITextInput_setPlaceHolder(IntPtr p, IntPtr placeholder);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUITextInput_setColor(IntPtr p, bool bTouch, uint foregroundRgb, uint backgroundRgb);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUITextInput_getMaxLen(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUITextInput_setMaxLen(IntPtr p, int maxlen);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUITextInput_setCharType(IntPtr p, uint chartype);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUITextInput_getCharCount(IntPtr p);

        // fontname : const char *
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static void CKLBUITextInput_setFont(IntPtr p, IntPtr fontName, float fontSize);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_TextInput"/*, typeof(CKLBUITextInput)*/);

        public CKLBUITextInput(CKLBUITask parent, bool passwordMode, int x, int y, uint width, uint height, String defaultText, CallBack callback, 
                                int widgetId = 0, int maxLen = 0, uint charType = (uint)(ECHAR_TYPE.TXCH_7BIT_ASCII|ECHAR_TYPE.TXCH_UTF8)) 
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUITextInput_create(parent != null ? parent.CppObject : IntPtr.Zero, passwordMode, x, y, width, height, __MarshallingUtils.NativeUtf8FromString(defaultText), widgetId, maxLen, charType);
            NativeManagement.intercepCppError();
            bind(ptr);
            m_callback = callback;
        }

        public CKLBUITextInput() : base(s_classID) { }

        #endregion

        #region CallBacks

        public delegate void CallBack(CKLBUITextInput caller, String txt, uint id);
        
        private CallBack m_callback;

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerSU(callBackFunction));
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName = null)
        {
            m_callback = (CallBack)anyDelegate;
        }

        // txt : const char* from Cpp
        public virtual void callBackFunction(IntPtr txt, uint id)
        {
            if(m_callback != null)
            {
                m_callback(this, __MarshallingUtils.StringFromNativeUtf8(txt), id);
            }
            else
            {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        #endregion

        public enum ECHAR_TYPE
        {
            TXCH_7BIT_ASCII = 0x0001,
            TXCH_UTF8       = 0x0002
        }

        public uint Width
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return CKLBUITextInput_getWidth(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUITextInput_setWidth(CppObject, value);
                else
                    throw new CKLBExceptionNullCppObject();
            }
		}
        public uint Height
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return CKLBUITextInput_getHeight(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUITextInput_setHeight(CppObject, value);
                else
                    throw new CKLBExceptionNullCppObject();
            }
		}
        public void getSize(out USize size)
        {
            if(CppObject != IntPtr.Zero)
            {
                size.width = CKLBUITextInput_getWidth(CppObject);
                size.height = CKLBUITextInput_getHeight(CppObject);
            }
            else
                throw new CKLBExceptionNullCppObject();
        }
        public void setSize(USize size)
        {
            if(CppObject != IntPtr.Zero)
            {
                CKLBUITextInput_setWidth(CppObject, size.width);
                CKLBUITextInput_setHeight(CppObject, size.height);
            }
            else
                throw new CKLBExceptionNullCppObject();
        }
        public void setSize(uint width, uint height)
        {
            if(CppObject != IntPtr.Zero)
            {
                CKLBUITextInput_setWidth(CppObject, width);
                CKLBUITextInput_setHeight(CppObject, height);
            }
            else
                throw new CKLBExceptionNullCppObject();
        }
		public String Text
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUITextInput_getText(CppObject));
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUITextInput_setText(CppObject, __MarshallingUtils.NativeUtf8FromString(value));
                else
                    throw new CKLBExceptionNullCppObject();
            }
		}
        public int MaxLen
        {
            get
            {
                if(CppObject != IntPtr.Zero)
                    return CKLBUITextInput_getMaxLen(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUITextInput_setMaxLen(CppObject, value);
                else
                    throw new CKLBExceptionNullCppObject();
            }
        }
        public int CharCount 
        {
            get
            {
                if(CppObject != IntPtr.Zero)
                    return CKLBUITextInput_getCharCount(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
        }

        public void setColor(bool bTouch, uint foregroundRgb, uint backgroundRgb)
        {
            if(CppObject != IntPtr.Zero)
                CKLBUITextInput_setColor(CppObject, bTouch, foregroundRgb, backgroundRgb);
            else
                throw new CKLBExceptionNullCppObject();
        }

        public void setFont(String fontName, float fontSize)
        {
            if(CppObject != IntPtr.Zero)
                CKLBUITextInput_setFont(CppObject, __MarshallingUtils.NativeUtf8FromString(fontName), fontSize);
            else
                throw new CKLBExceptionNullCppObject();
        }

        public void setCharType(ECHAR_TYPE chartype)
        {
            if(CppObject != IntPtr.Zero)
                CKLBUITextInput_setCharType(CppObject, (uint)chartype);
            else
                throw new CKLBExceptionNullCppObject();
        }

        public void setPlaceHolder(String placeHolder)
        {
            if(CppObject != IntPtr.Zero)
                CKLBUITextInput_setPlaceHolder(CppObject, __MarshallingUtils.NativeUtf8FromString(placeHolder));
            else
                throw new CKLBExceptionNullCppObject();
        }
	}
}
