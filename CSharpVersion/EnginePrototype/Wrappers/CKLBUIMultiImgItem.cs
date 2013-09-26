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
//using System.Security;

namespace EnginePrototype
{
	public class CKLBUIMultiImgItem : CKLBUITask
	{
		#region DllImports
        // pParent          : CKLBUITask*
        // pArrayAsset      : const char**
        // pArrayIndexes    : uint*
        // return           : CKLBUIMultiImgItem*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBUIMultiImgItem_create(IntPtr pParent, uint order, float x, float y, uint idx, IntPtr[] pArrayAsset,
												                uint[] pArrayIndexes, uint assetCount);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIMultiImgItem_getIndexMax(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIMultiImgItem_setIndexMax(IntPtr p, uint index);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIMultiImgItem_getOrder(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIMultiImgItem_setOrder(IntPtr p, uint order);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIMultiImgItem_getIndex(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIMultiImgItem_setIndex(IntPtr p, uint index);

        // pArrayAsset      : const char**
        // pArrayIndexes    : uint*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIMultiImgItem_changeAssets(IntPtr p, IntPtr[] pArrayAsset, uint[] pArrayIndexes, uint assetCount);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_MultiImgItem"/*, typeof(CKLBUIMultiImgItem)*/);

        public CKLBUIMultiImgItem(  CKLBUITask parent, uint order, float x, float y, String[] pArrayAsset, 
                                    uint[] pArrayIndexes, uint index = 0)
            : base(s_classID)
        {
            if(pArrayAsset.Length != pArrayAsset.Length) {
                throw new CKLBException("ArrayAsset and ArrayIndexes must have the same size.");
            }

            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIMultiImgItem_create( parent != null ? parent.CppObject : IntPtr.Zero, order, x, y, index, __MarshallingUtils.NativeUtf8ArrayFromStringArray(pArrayAsset, pArrayAsset.Length),
                                                    pArrayIndexes, (uint)pArrayAsset.Length);
            NativeManagement.intercepCppError();
            bind(ptr);
        }

        public CKLBUIMultiImgItem() : base(s_classID) { }

        #endregion

        public uint Order
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIMultiImgItem_getOrder(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIMultiImgItem_setOrder(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        public uint Index 
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIMultiImgItem_getIndex(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIMultiImgItem_setIndex(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        public uint IdMax 
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIMultiImgItem_getIndexMax(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIMultiImgItem_setIndexMax(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }

        public bool changeAssets(String[] pArrayAsset, uint[] pArrayIndexes) 
        {
            if(pArrayAsset.Length != pArrayIndexes.Length) {
                throw new CKLBException("pArrayAsset and pArrayIndexes must have the same length.");
            }

            if(CppObject != IntPtr.Zero) {
                NativeManagement.resetCppError();
                bool res = CKLBUIMultiImgItem_changeAssets(CppObject, __MarshallingUtils.NativeUtf8ArrayFromStringArray(pArrayAsset, pArrayAsset.Length), pArrayIndexes, (uint)pArrayAsset.Length);
                NativeManagement.intercepCppError();
                return res;
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
	}
}
