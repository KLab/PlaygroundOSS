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
    public static class CSEng
    {
        #region DllImports
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibENG_isRelease();

        // return : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBLuaLibENG_getPlatform();

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibENG_getNanoTime(ref int milli, ref int nano);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibENG_startNanoTime(int idx);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibENG_endNanoTime(int idx, ref int milli, ref int nano);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBLuaLibENG_getFrameID();
        #endregion

        public static bool      IsRelease
        {
            get
            {
                return CKLBLuaLibENG_isRelease();
            }
        }
        public static String    Platform
        {
            get
            {
                return __MarshallingUtils.StringFromNativeUtf8(CKLBLuaLibENG_getPlatform());
            }
        }
        public static uint      FrameId
        {
            get 
            {
                return CKLBLuaLibENG_getFrameID();
            }
        }

        public static void getNanoTime(ref int milli, ref int nano)
        {
            CKLBLuaLibENG_getNanoTime(ref milli, ref nano);
        }

        public static void startNanoTime(int idx)
        {
            CKLBLuaLibENG_startNanoTime(idx);
        }

        public static void endNanoTime(int idx, ref int milli, ref int nano)
        {
            CKLBLuaLibENG_endNanoTime(idx, ref milli, ref nano);
        }
    }
}

