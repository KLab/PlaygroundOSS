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
	public class CSFont : GameObject
    {
        #region DllImports
        // fontName : const char*
        // return : FONTOBJ*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBLuaLibFONT_createFont(int size, IntPtr fontName);

        // font : FONTOBJ*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibFONT_removeFont(IntPtr font);

        // str : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibFONT_cmdGetTextInfo(IntPtr str, IntPtr font, out STextInfo outInfo);
        #endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("LibFont"/*, typeof(CSFont)*/);

        public CSFont(uint size, String name)
			: base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBLuaLibFONT_createFont((int)size, __MarshallingUtils.NativeUtf8FromString(name));
            NativeManagement.intercepCppError();
            bind(ptr);
            m_size = size;
            m_name = name;
        }

        #endregion

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct STextInfo
        {
            public float width;
            public float height;
            public float ascent;
            public float descent;
            public float top;
            public float bottom;
        }

        private uint    m_size;
        private String  m_name;
        public  uint    Size
        {
            get { return m_size; }
            set 
            {  
                if(CppObject != IntPtr.Zero) {
                    m_size = value;
                    CKLBLuaLibFONT_removeFont(CppObject); // destroyes the C++ font and unregister the C# game object !
                    NativeManagement.resetCppError();
                    IntPtr ptr = CKLBLuaLibFONT_createFont((int)value, __MarshallingUtils.NativeUtf8FromString(m_name));
                    NativeManagement.intercepCppError();
                    WrapperReg.getInstance().registerGameObject(this);
                    bind(ptr);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        public  String  Name
        {
            get { return m_name; }
            set 
            {  
                if(CppObject != IntPtr.Zero) {
                    m_name = value;
                    CKLBLuaLibFONT_removeFont(CppObject);
                    NativeManagement.resetCppError();
                    IntPtr ptr = CKLBLuaLibFONT_createFont((int)m_size, __MarshallingUtils.NativeUtf8FromString(value));
                    NativeManagement.intercepCppError();
                    WrapperReg.getInstance().registerGameObject(this);
                    bind(ptr);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }

        internal override void clearInternals()
		{
            if(CppObject != IntPtr.Zero) {
                CKLBLuaLibFONT_removeFont(CppObject);
            }
		}
		
		public void getTextInfo(String text, out STextInfo info)
		{
            if(CppObject != IntPtr.Zero) {
                CKLBLuaLibFONT_cmdGetTextInfo(__MarshallingUtils.NativeUtf8FromString(text), CppObject, out info);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
		}
	}
}

