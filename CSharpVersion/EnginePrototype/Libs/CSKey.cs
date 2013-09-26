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
    public static class CSKey
    {
        #region DllImports
        // userId : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static int CKLBLuaLibKEY_genUserID(IntPtr userId, uint bufSize);

        // userId : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static int CKLBLuaLibKEY_genUserPW(IntPtr userId, IntPtr buf, uint bufSize);

        // serviceName & userId : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibKEY_setSecureID(IntPtr serviceName, IntPtr userId);

        // serviceName & userId : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibKEY_setSecurePW(IntPtr serviceName, IntPtr passwd);

        // serviceName : const char*
        // buf : char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static int CKLBLuaLibKEY_getSecureID(IntPtr serviceName, IntPtr buf, uint bufSize);

        // serviceName : const char*
        // buf : char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static int CKLBLuaLibKEY_getSecurePW(IntPtr serviceName, IntPtr buf, uint bufSize);

        // serviceName : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibKEY_delSecureID(IntPtr serviceName);

        // serviceName : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibKEY_delSecurePW(IntPtr serviceName);
        #endregion

        public static int genUserID(out String userId, uint bufSize = 1024)
        {
            IntPtr intPtr = __MarshallingUtils.NativeUtf8FromString(new String('0', (int)bufSize));
            int len = CKLBLuaLibKEY_genUserID(intPtr, bufSize);
            userId = __MarshallingUtils.StringFromNativeUtf8(intPtr);
            return len;
        }

        public static int genUserPW(String userId, out String passwd, uint bufSize = 1024)
        {
            IntPtr intPtr = __MarshallingUtils.NativeUtf8FromString(new String('0', (int)bufSize));
            int len = CKLBLuaLibKEY_genUserPW(__MarshallingUtils.NativeUtf8FromString(userId), intPtr, bufSize);
            passwd = __MarshallingUtils.StringFromNativeUtf8(intPtr);
            return len;
        }

        public static bool setSecureID(String serviceName, String userId)
        {
            return CKLBLuaLibKEY_setSecureID(__MarshallingUtils.NativeUtf8FromString(serviceName), __MarshallingUtils.NativeUtf8FromString(userId));
        }

        public static bool setSecurePW(String serviceName, String passwd)
        {
            return CKLBLuaLibKEY_setSecurePW(__MarshallingUtils.NativeUtf8FromString(serviceName), __MarshallingUtils.NativeUtf8FromString(passwd));
        }

        public static int getSecureID(String serviceName, out String secureID, uint bufSize = 1024)
        {
            IntPtr intPtr = __MarshallingUtils.NativeUtf8FromString(new String('0', (int)bufSize));
            int len = CKLBLuaLibKEY_getSecureID(__MarshallingUtils.NativeUtf8FromString(serviceName), intPtr, bufSize);
            secureID = __MarshallingUtils.StringFromNativeUtf8(intPtr);
            return len;
        }

        public static int getSecurePW(String serviceName, out String securePW, uint bufSize = 1024)
        {
            IntPtr intPtr = __MarshallingUtils.NativeUtf8FromString(new String('0', (int)bufSize));
			int len = CKLBLuaLibKEY_getSecurePW(__MarshallingUtils.NativeUtf8FromString(serviceName), intPtr, bufSize);
            securePW = __MarshallingUtils.StringFromNativeUtf8(intPtr);
            return len;
        }

        public static bool delSecureID(String serviceName)
        {
            return CKLBLuaLibKEY_delSecureID(__MarshallingUtils.NativeUtf8FromString(serviceName));
        }

        public static bool delSecurePW(String serviceName)
        {
            return CKLBLuaLibKEY_delSecurePW(__MarshallingUtils.NativeUtf8FromString(serviceName));
        }
    }
}
