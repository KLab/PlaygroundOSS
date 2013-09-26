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
	public class CKLBUIScale9 : CKLBUITask
	{
		#region DllImports
        // pParent : CKLBUITask*
        // asset : const char*
        // return : CKLBUIScale9*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIScale9_create(IntPtr pParent, uint order, float x, float y, int width, int height, IntPtr asset);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIScale9_getWidth(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScale9_setWidth(IntPtr p, int width);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIScale9_getHeight(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScale9_setHeight(IntPtr p, int height);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIScale9_getOrder(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScale9_setOrder(IntPtr p, uint order);
		
        // const char* : asset & return
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static IntPtr CKLBUIScale9_getAsset(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIScale9_setAsset(IntPtr p, IntPtr asset);
		#endregion

        #region Constructor

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_Scale9"/*, typeof(CKLBUIScale9)*/);

        public CKLBUIScale9(CKLBUITask parent, uint order, float x, float y, int width, int height, String asset)
            : base(s_classID)
		{
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIScale9_create(parent != null ? parent.CppObject : IntPtr.Zero, order, x, y, width, height, __MarshallingUtils.NativeUtf8FromString(asset));
            NativeManagement.intercepCppError();
            bind(ptr);
		}

        public CKLBUIScale9() : base(s_classID) { }

        #endregion

        public uint Order
		{
			get 
			{ 
				if(CppObject != IntPtr.Zero) {
					return CKLBUIScale9_getOrder(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIScale9_setOrder(CppObject,value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public int  Width
		{
			get 
			{ 
				if(CppObject != IntPtr.Zero) {
					return CKLBUIScale9_getWidth(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIScale9_setWidth(CppObject,value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public int  Height
		{
			get 
			{ 
				if(CppObject != IntPtr.Zero) {
					return CKLBUIScale9_getHeight(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIScale9_setHeight(CppObject,value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
        public void getSize(out Size size)
        {
            if(CppObject != IntPtr.Zero) {
                size.width = CKLBUIScale9_getWidth(CppObject);
                size.height = CKLBUIScale9_getHeight(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
        public void setSize(Size size)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIScale9_setWidth(CppObject, size.width);
                CKLBUIScale9_setHeight(CppObject, size.height);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
        public void setSize(int width, int height)
        {
            CKLBUIScale9_setWidth(CppObject, width);
            CKLBUIScale9_setHeight(CppObject, height);
        }
		public String Asset
		{
			get 
			{ 
				if(CppObject != IntPtr.Zero) {
					return __MarshallingUtils.StringFromNativeUtf8(CKLBUIScale9_getAsset(CppObject));
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
			{
                if(CppObject != IntPtr.Zero) {
					NativeManagement.resetCppError();
                    CKLBUIScale9_setAsset(CppObject, __MarshallingUtils.NativeUtf8FromString(value));
                    NativeManagement.intercepCppError();
                } else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
	}
}

