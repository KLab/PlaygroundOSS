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
    public static class CSUI
    {
        public enum E_POSITION {
	        LEFT	 = 0x00000001,
	        RIGHT    = 0x00000002,
	        H_CENTER = 0x00000003, // LEFT | RIGHT

	        TOP      = 0x00000004,
	        BOTTOM   = 0x00000008,
	        V_CENTER = 0x0000000c, // TOP | BOTTOM
        };

        #region DllImports
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibUI_calcPosition(float x, float y, float w, float h, uint mask, ref float out_rx, ref float out_ry);
        #endregion

        public static void calcPosition(float x, float y, float w, float h, E_POSITION mask, ref float out_rx, ref float out_ry)
        {
            CKLBLuaLibUI_calcPosition(x, y, w, h, (uint)mask, ref out_rx, ref out_ry);
        }
    }
}
