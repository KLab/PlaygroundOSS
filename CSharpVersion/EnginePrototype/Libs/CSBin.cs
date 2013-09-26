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
	public class CSBin : GameObject
    {
        #region DllImports
        //return : CKLBBinArray*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBLuaLibBIN_open(IntPtr bin_asset);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibBIN_close(IntPtr pBIN);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibBIN_peek(IntPtr pBIN, int offset, ref int value);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibBIN_peek_u16(IntPtr pBIN, int offset, ref uint value, bool f_bigendian);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibBIN_peek_u32(IntPtr pBIN, int offset, ref uint value, bool f_bigendian);
        #endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("LibBIN"/*, typeof(CSBin)*/);

        public CSBin(String bin_asset)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBLuaLibBIN_open(__MarshallingUtils.NativeUtf8FromString(bin_asset));
            NativeManagement.intercepCppError();
            bind(ptr);
        }

        #endregion

        internal override void clearInternals()
        {
            if(CppObject != IntPtr.Zero) {
                CKLBLuaLibBIN_close(CppObject);
            }
        }

        public bool peek(int offset, ref int value)
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBLuaLibBIN_peek(CppObject, offset, ref value);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public bool peek_u16(int offset, ref uint value, bool f_bigendian = false)
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBLuaLibBIN_peek_u16(CppObject, offset, ref value, f_bigendian);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public bool peek_u32(int offset, ref uint value, bool f_bigendian = false)
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBLuaLibBIN_peek_u32(CppObject, offset, ref value, f_bigendian);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
	}
}

