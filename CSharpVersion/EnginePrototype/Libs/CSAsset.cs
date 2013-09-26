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
    public static class CSAsset
    {
        #region DllImports
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibASSET_getImageSize(IntPtr assetName, ref int returnWidth, ref int returnHeight);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibASSET_getBoundSize(IntPtr assetName, ref float returnWidth, ref float returnHeight);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibASSET_getAssetInfo(IntPtr assetName, ref int returnImgWidth, ref int returnImgHeight, 
                                                                                  ref float returnBoundWidth, ref float returnBoundHeight);
        #endregion

        public static void getImageSize(String assetPath, ref int width, ref int height) 
        {
            NativeManagement.resetCppError();
            CKLBLuaLibASSET_getImageSize(__MarshallingUtils.NativeUtf8FromString(assetPath), ref width, ref height);
            NativeManagement.intercepCppError();
        }
        public static void getImageSize(String assetPath, out Size size)
        {
            int width = 0, height = 0;
            NativeManagement.resetCppError();
            CKLBLuaLibASSET_getImageSize(__MarshallingUtils.NativeUtf8FromString(assetPath), ref width, ref height);
            NativeManagement.resetCppError();
            size.width = width;
            size.height = height;
        }

        public static void getBoundSize(String assetPath, ref float width, ref float height) 
        {
            NativeManagement.resetCppError();
            CKLBLuaLibASSET_getBoundSize(__MarshallingUtils.NativeUtf8FromString(assetPath), ref width, ref height);
            NativeManagement.intercepCppError();
        }
        public static void getBoundSize(String assetPath, out FSize size)
        {
            float width = 0, height = 0;
            NativeManagement.resetCppError();
            CKLBLuaLibASSET_getBoundSize(__MarshallingUtils.NativeUtf8FromString(assetPath), ref width, ref height);
            NativeManagement.intercepCppError();
            size.width = width;
            size.height = height;
        }

        public static void getAssetInfo(String assetPath, ref int imgWidth, ref int imgHeight, ref float boundWidth, ref float boundHeight)
        {
            NativeManagement.resetCppError();
            CKLBLuaLibASSET_getAssetInfo(__MarshallingUtils.NativeUtf8FromString(assetPath), ref imgWidth, ref imgHeight, ref boundWidth, ref boundHeight);
            NativeManagement.intercepCppError();
        }
        public static void getAssetInfo(String assetPath, out Size imgSize, out FSize boundSize)
        {
            int imgWidth = 0, imgHeight = 0;
            float boundWidth = 0, boundHeight = 0;
            NativeManagement.resetCppError();
            CKLBLuaLibASSET_getAssetInfo(__MarshallingUtils.NativeUtf8FromString(assetPath), ref imgWidth, ref imgHeight, ref boundWidth, ref boundHeight);
            NativeManagement.intercepCppError();
            imgSize.width    = imgWidth;
            imgSize.height   = imgHeight;
            boundSize.width  = boundWidth;
            boundSize.height = boundHeight;
        }
    }
}
