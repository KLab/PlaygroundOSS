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
    public static class CSLang
    {

        #region DllImports
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibLANG_addString(IntPtr id, IntPtr str);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBLuaLibLANG_getString(IntPtr id);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibLANG_removeString(IntPtr id);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibLANG_useDB(IntPtr dbFile, IntPtr table, IntPtr keyF, IntPtr valueF, IntPtr groupF);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibLANG_loadGroup(IntPtr groupId);
        #endregion

        public static bool addString(String id, String str) 
        {
            return CKLBLuaLibLANG_addString(__MarshallingUtils.NativeUtf8FromString(id), __MarshallingUtils.NativeUtf8FromString(str));
        }
        public static String getString(String id) 
        {
            return __MarshallingUtils.StringFromNativeUtf8(CKLBLuaLibLANG_getString(__MarshallingUtils.NativeUtf8FromString(id)));
        }
        public static void removeString(String id)
        {
            CKLBLuaLibLANG_removeString(__MarshallingUtils.NativeUtf8FromString(id));
        }
        public static bool useDB(String dbFile, String table, String keyF, String valueF, String groupF = null) 
        {
            return CKLBLuaLibLANG_useDB(__MarshallingUtils.NativeUtf8FromString(dbFile), __MarshallingUtils.NativeUtf8FromString(table), __MarshallingUtils.NativeUtf8FromString(keyF), __MarshallingUtils.NativeUtf8FromString(valueF), __MarshallingUtils.NativeUtf8FromString(groupF));
        }
        public static bool loadGroup(String groupId)
        {
            return CKLBLuaLibLANG_loadGroup(__MarshallingUtils.NativeUtf8FromString(groupId));
        }
    }
}
