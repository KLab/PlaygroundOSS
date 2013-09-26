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
    public static class CSGL
    {

        #region DllImports
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibGL_GLClearColor(float r, float g, float b, float a);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibGL_GLSetResolution(int width, int height);

        // name : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibGL_GLCreateScreenAsset(IntPtr name);

        // name : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibGL_GLDoScreenShot(IntPtr name);

        // name : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibGL_GLFreeScreenAsset(IntPtr name);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibGL_SGGetGuardBand(ref float leftBorder, ref float rightBorder, ref float topBorder, ref float bottomBorder);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibGL_SGSetGuardBand(float leftBorder, float rightBorder, float topBorder, float bottomBorder);
        #endregion

        public static void clearColor(float r, float g, float b, float a)
        {
            CKLBLuaLibGL_GLClearColor(r, g, b, a);
        }

        public static void setResolution(int width, int height)
        {
            CKLBLuaLibGL_GLSetResolution(width, height);
        }

        public static bool createScreenAsset(String name)
        {
            return CKLBLuaLibGL_GLCreateScreenAsset(__MarshallingUtils.NativeUtf8FromString(name));
        }

        public static bool doScreenShot(String name)
        {
            return CKLBLuaLibGL_GLDoScreenShot(__MarshallingUtils.NativeUtf8FromString(name));
        }

        public static void freeScreenAsset(String name)
        {
            CKLBLuaLibGL_GLFreeScreenAsset(__MarshallingUtils.NativeUtf8FromString(name));
        }

        public static void getGuardBand(ref float leftBorder, ref float rightBorder, ref float topBorder, ref float bottomBorder)
        {
            CKLBLuaLibGL_SGGetGuardBand(ref leftBorder, ref rightBorder, ref topBorder, ref bottomBorder);
        }

        public static void setGuardBand(float leftBorder, float rightBorder, float topBorder, float bottomBorder)
        {
            CKLBLuaLibGL_SGSetGuardBand(leftBorder, rightBorder, topBorder, bottomBorder);
        }
    }
}
