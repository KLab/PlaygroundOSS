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
	public class CKLBUILabel : CKLBUITask
	{
		#region DllImports
        //return : CKLBUILabel*
        // pParent : CKLBUITask*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBUILabel_create(IntPtr pParent, uint order, float x, float y, uint argb, IntPtr font, uint size, IntPtr text, uint align);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUILabel_getOrder(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUILabel_setOrder(IntPtr p, uint order);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUILabel_getAlign(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUILabel_setAlign(IntPtr p, uint align);
		
		// return and text : const char *
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static IntPtr CKLBUILabel_getText(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static void CKLBUILabel_setText(IntPtr p, IntPtr text);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUILabel_getColor(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUILabel_setColor(IntPtr p, uint color);
		
		// return and font : const char *
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static IntPtr CKLBUILabel_getFont(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static void CKLBUILabel_setFont(IntPtr p, IntPtr font);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUILabel_getFontSize(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUILabel_setFontSize(IntPtr p, uint size);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUILabel_setPosition(IntPtr p, float x, float y);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_Label"/*, typeof(CKLBUILabel)*/);

        public CKLBUILabel(CKLBUITask parent, uint order, float x, float y, uint argb, String font_name, uint font_size, String text, EALIGN align)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUILabel_create(parent != null ? parent.CppObject : IntPtr.Zero, order, x, y, argb, __MarshallingUtils.NativeUtf8FromString(font_name), font_size, __MarshallingUtils.NativeUtf8FromString(text), (uint)align);
            NativeManagement.intercepCppError();
            bind(ptr);
        }

        public CKLBUILabel() : base(s_classID) { Console.WriteLine("YOLO"); }

        #endregion

        public enum EALIGN : uint
        {
            MID = 5,
            TOP_LEFT = 10,
            TOP = 9,
            TOP_RIGHT = 8,
            LEFT = 6,
            RIGHT = 4,
            BOTTOM_LEFT = 2,
            BOTTOM = 1,
            BOTTOM_RIGHT = 0
        }

		public  uint    Order
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUILabel_getOrder(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUILabel_setOrder(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public String   FontName
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUILabel_getFont(CppObject));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUILabel_setFont(CppObject, __MarshallingUtils.NativeUtf8FromString(value));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
		public  uint    FontSize
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUILabel_getFontSize(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUILabel_setFontSize(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
        public  void    setFont(String name, uint size)
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUILabel_setFont(CppObject, __MarshallingUtils.NativeUtf8FromString(name));
				CKLBUILabel_setFontSize(CppObject, size);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
		public  uint    TxtArgb
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUILabel_getColor(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUILabel_setColor(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public  String  Text
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUILabel_getText(CppObject));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUILabel_setText(CppObject, __MarshallingUtils.NativeUtf8FromString(value));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public  EALIGN  Align
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return (EALIGN)CKLBUILabel_getAlign(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUILabel_setAlign(CppObject, (uint)value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}

        public  void    setPosition(float x, float y)
        {
			if(CppObject != IntPtr.Zero) {
				CKLBUILabel_setPosition(CppObject, x, y);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
        }
	}
}

