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
    public class CSData : GameObject
    {
        #region DllImports
        // return : CKLBDataSet*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBLuaLibDATA_cmdCreateData(uint dataSetID);

        // pDataSet : CKLBDataSet*
        // nameAsset & nameData : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibDATA_cmdRegistData(IntPtr pDataSet, IntPtr nameAsset, ref uint pReturnHandle);

        // pDataSet : CKLBDataSet*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibDATA_cmdDelete(IntPtr pDataSet);
        #endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("LibDATA"/*, typeof(CSData)*/);

        public CSData(uint ID)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBLuaLibDATA_cmdCreateData(ID);
            NativeManagement.intercepCppError();
            bind(ptr);
        }

        #endregion

        public bool registerData(String nameAsset, ref uint pReturnHandle) 
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBLuaLibDATA_cmdRegistData(CppObject, __MarshallingUtils.NativeUtf8FromString(nameAsset), ref pReturnHandle);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        internal override void clearInternals() 
        {
            if(CppObject != IntPtr.Zero) {
                CKLBLuaLibDATA_cmdDelete(CppObject);
            }
        }
    }
}
