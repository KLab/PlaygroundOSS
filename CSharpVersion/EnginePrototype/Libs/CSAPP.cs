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
    public static class CSAPP
    {
        #region DllImports
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibAPP_callApplication(APP_TYPE type, IntPtr addr, IntPtr subject, IntPtr body);
        #endregion

        public enum APP_TYPE
        {
            APP_MAIL,
            APP_BROWSER,
        };

        public static bool callApplication(APP_TYPE type, String addr, String subject, String body)
        {
            return CKLBLuaLibAPP_callApplication(type, __MarshallingUtils.NativeUtf8FromString(addr), __MarshallingUtils.NativeUtf8FromString(subject), __MarshallingUtils.NativeUtf8FromString(body));
        }
    };
}
