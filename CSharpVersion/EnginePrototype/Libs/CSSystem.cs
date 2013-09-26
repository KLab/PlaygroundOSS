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
    public static class CSSystem
    {
        #region DllImports
        // msg : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaEnv_cmdLogging(IntPtr msg);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaEnv_cmdExit();

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaEnv_cmdSystemInfo(ref int width, ref int height);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaEnv_cmdSystemReboot();
        #endregion

        public struct SystemInfo
        {
            public int width;
            public int height;
        }

        public static void logging(String msg) 
        {
            CKLBLuaEnv_cmdLogging(__MarshallingUtils.NativeUtf8FromString(msg));
        }

        public static void exitGame() 
        {
            CKLBLuaEnv_cmdExit();
        }

        public static void getInfo(out SystemInfo sysInfos)
        {
            int width = 0, height = 0;
            CKLBLuaEnv_cmdSystemInfo(ref width, ref height);
            sysInfos.width = width;
            sysInfos.height = height;
        }

        public static void reboot()
        {
            CKLBLuaEnv_cmdSystemReboot();
        }
    }
}
