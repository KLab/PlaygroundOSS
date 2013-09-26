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
    public class CSDB : GameObject
    {
        #region DllImports
        //return : CKLBLuaDB*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBLuaLibDB_dbopen(IntPtr db_asset, bool b_write, bool b_create);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibDB_dbclose(IntPtr pDB);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibDB_closeAll();

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBLuaLibDB_query(IntPtr pDB, IntPtr sqlQuery, ref int nbEntries);
        #endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("LibDB"/*, typeof(CSDB)*/);

        public CSDB(String db_asset, bool b_write = true, bool b_create = true)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBLuaLibDB_dbopen(__MarshallingUtils.NativeUtf8FromString(db_asset), b_write, b_create);
            NativeManagement.intercepCppError();
            bind(ptr);
            m_isWritable = b_write;
            m_isCreatable = b_create;
        }

        #endregion

        private bool m_isWritable;
        private bool m_isCreatable;

        public bool IsWritable
        {
            get { return m_isWritable; }
        }
        public bool IsCreatable
        {
            get { return m_isCreatable; }
        }

        internal override void clearInternals()
        {
            if(CppObject != IntPtr.Zero) {
                CKLBLuaLibDB_dbclose(CppObject);
            }
        }

        public static void closeAll()
        {
            CKLBLuaLibDB_closeAll();
        }

        public void query(String sqlQuery, out String[] results)
        {
            int nbEntries = 0;
            IntPtr p = CKLBLuaLibDB_query(CppObject, __MarshallingUtils.NativeUtf8FromString(sqlQuery), ref nbEntries);

            results = __MarshallingUtils.StringArrayFromNativeUtf8IntPtr(p, nbEntries * 2);
        }
    }
}
