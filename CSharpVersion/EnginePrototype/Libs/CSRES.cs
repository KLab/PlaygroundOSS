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
    public static class CSRES
    {
        #region DllImports
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibRES_dumpSceneGraph(IntPtr task);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibRES_dumpRendering(bool detailed);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibRES_dumpAssets();

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibRES_dumpDataSet();

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibRES_dumpTexturePacker(bool detailed);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibRES_dumpGeometryCost(bool detailed);
        #endregion
		
        public static void dumpSceneGraph(CKLBUITask task = null)
        {
            if(task != null) {
                CKLBLuaLibRES_dumpSceneGraph(task.CppObject);
            } else {
                CKLBLuaLibRES_dumpSceneGraph(IntPtr.Zero);
            }
        }

        public static void dumpRendering(bool detailed = false)
        {
            CKLBLuaLibRES_dumpRendering(detailed);
        }

        public static void dumpAssets()
        {
            CKLBLuaLibRES_dumpAssets();
        }

        public static void dumpDataSet()
        {
            CKLBLuaLibRES_dumpDataSet();
        }

        public static void dumpTexturePacker(bool detailed = false)
        {
            CKLBLuaLibRES_dumpTexturePacker(detailed);
        }

        public static void dumpGeometryCost(bool detailed = false)
        {
            CKLBLuaLibRES_dumpGeometryCost(detailed);
        }
    }
}

