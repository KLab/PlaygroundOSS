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
	public class CKLBUISimpleItem : CKLBUITask
	{
		#region DllImports
        // pParent : CKLBUITask*
        // asset : const char*
        // return : CKLBUISimpleItem*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUISimpleItem_create(IntPtr pParent, uint order, float x, float y, IntPtr asset);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUISimpleItem_getOrder(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUISimpleItem_setOrder(IntPtr p, uint order);

		// return : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static IntPtr CKLBUISimpleItem_getAsset(IntPtr p);
		#endregion

        #region Constructor

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_SimpleItem"/*, typeof(CKLBUISimpleItem)*/);

        public CKLBUISimpleItem(CKLBUITask parent, uint order, float x, float y, String asset) : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUISimpleItem_create(parent != null ? parent.CppObject : IntPtr.Zero, order, x, y, __MarshallingUtils.NativeUtf8FromString(asset));
            NativeManagement.intercepCppError();
            bind(ptr);
        }

        public CKLBUISimpleItem() : base(s_classID) { }

        #endregion

        public uint   Order
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return CKLBUISimpleItem_getOrder(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUISimpleItem_setOrder(CppObject, value);
                else
                    throw new CKLBExceptionNullCppObject();
            }
		}
		public String Asset
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUISimpleItem_getAsset(CppObject));
                else
                    throw new CKLBExceptionNullCppObject();
            }
			//set { throw new CKLBExceptionForbiddenMethod(); }
		}
	}
}

