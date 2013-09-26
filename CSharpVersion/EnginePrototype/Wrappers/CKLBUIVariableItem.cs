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
	public class CKLBUIVariableItem : CKLBUITask
	{

		#region DllImports
        // pParent : CKLBUITask*
        // asset : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIVariableItem_create(IntPtr pParent, uint order, float x, float y, float width, float height, IntPtr asset);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIVariableItem_getOrder(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVariableItem_setOrder(IntPtr p, uint order);

        // return : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIVariableItem_getAsset(IntPtr p);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIVariableItem_getWidth(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVariableItem_setWidth(IntPtr p, float width);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIVariableItem_getHeight(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVariableItem_setHeight(IntPtr p, float height);
		
        // assetName : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIVariableItem_changeAsset(IntPtr p, IntPtr assetName);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVariableItem_changeUV(IntPtr p, float x, float y, float width, float height);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVariableItem_resetUV(IntPtr p);

        // assetName : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIVariableItem_setMaskAsset(IntPtr p, IntPtr assetName);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_VariableItem"/*, typeof(CKLBUIVariableItem)*/);

		public CKLBUIVariableItem(CKLBUITask parent, uint order, float x, float y, float width, float height, String asset = null)
            : base(s_classID)
		{
			NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIVariableItem_create( parent != null ? parent.CppObject : IntPtr.Zero, 
                                                    order, x, y, width, height, __MarshallingUtils.NativeUtf8FromString(asset));
            NativeManagement.intercepCppError();
            bind(ptr);
		}

        public CKLBUIVariableItem() : base(s_classID) { }

        #endregion

		public uint   Order
		{
			get 
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUIVariableItem_getOrder(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIVariableItem_setOrder(CppObject, value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public String Asset
		{
			get 
            {
				if(CppObject != IntPtr.Zero) {
					return __MarshallingUtils.StringFromNativeUtf8(CKLBUIVariableItem_getAsset(CppObject));
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
            { 
                if(CppObject != IntPtr.Zero) {
                    NativeManagement.resetCppError();
					CKLBUIVariableItem_changeAsset(CppObject, __MarshallingUtils.NativeUtf8FromString(value));
                    NativeManagement.intercepCppError();
				} else {
					throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public float  Width
		{
			get 
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUIVariableItem_getWidth(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIVariableItem_setWidth(CppObject, value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public float  Height
		{
			get 
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUIVariableItem_getHeight(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIVariableItem_setHeight(CppObject, value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public void   getSize(out FSize size)
		{
			if(CppObject != IntPtr.Zero) {
				size.width = CKLBUIVariableItem_getWidth(CppObject);
				size.height = CKLBUIVariableItem_getHeight(CppObject);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

        public void setUV(float x, float y, float width, float height) {
            if(CppObject != IntPtr.Zero) {
				CKLBUIVariableItem_changeUV(CppObject, x, y, width, height);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
        }

        public void resetUV() {
            if(CppObject != IntPtr.Zero) {
				CKLBUIVariableItem_resetUV(CppObject);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
        }

        public bool setMaskAsset(String assetName)
        {
            if(CppObject != IntPtr.Zero) {
				return CKLBUIVariableItem_setMaskAsset(CppObject, __MarshallingUtils.NativeUtf8FromString(assetName));
			} else {
				throw new CKLBExceptionNullCppObject();
            }
        }
	}
}
