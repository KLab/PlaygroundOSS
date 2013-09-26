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
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace EnginePrototype
{
	public class CKLBUIFreeVertItem : CKLBUITask
	{
		#region DllImports
        // parent   : CKLBUITask*
        // asset    : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBUIFreeVertItem_create(IntPtr parent, uint order, float x, float y, IntPtr asset, float[] verticesArray);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIFreeVertItem_getOrder(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIFreeVertItem_setOrder(IntPtr p, uint order);
		
		// return : const char *
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static IntPtr CKLBUIFreeVertItem_getAsset(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private extern static void CKLBUIFreeVertItem_setVertices(IntPtr p, float[] coord);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private extern static void CKLBUIFreeVertItem_setColors(IntPtr p, uint[] colors);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIFreeVertItem_setVertCol(IntPtr p, int idx, uint argb);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private extern static void CKLBUIFreeVertItem_setUV(IntPtr p, float[] uv);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_FreeVertItem"/*, typeof(CKLBUIFreeVertItem)*/);

        public CKLBUIFreeVertItem(CKLBUITask parent, uint order, float x, float y, String asset, float[] verticesArray) : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIFreeVertItem_create(parent != null ? parent.CppObject : IntPtr.Zero, order, x, y, __MarshallingUtils.NativeUtf8FromString(asset), verticesArray);
            NativeManagement.intercepCppError();
            bind(ptr);
        }

        public CKLBUIFreeVertItem() : base(s_classID) { }

        #endregion

        public uint Order
		{
			get
			{
				if(CppObject != IntPtr.Zero)
					return CKLBUIFreeVertItem_getOrder(CppObject);
				else
					throw new CKLBExceptionNullCppObject();
			}
			set
			{
				if(CppObject != IntPtr.Zero)
					CKLBUIFreeVertItem_setOrder(CppObject,value);
				else
					throw new CKLBExceptionNullCppObject();
			}
		}
		public String Asset
		{
			get
			{
				if(CppObject != IntPtr.Zero)
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUIFreeVertItem_getAsset(CppObject));
				else
					throw new CKLBExceptionNullCppObject ();
			}
			//set { throw new CKLBExceptionForbiddenMethod();}
		}

        // 8 vertices
        public void setVertices(float[] coords)
        {
            if(coords.Length != 8)
                throw new CKLBException("Vertices must be a float[8] array.");

            if(CppObject != IntPtr.Zero)
                CKLBUIFreeVertItem_setVertices(CppObject, coords);
            else
                throw new CKLBExceptionNullCppObject();
        }

        // 4 colors
        public void setColors(uint[] colors)
        {
            if(colors.Length != 4)
                throw new CKLBException("Colors must be a uint[4] array.");

            if(CppObject != IntPtr.Zero)
                CKLBUIFreeVertItem_setColors(CppObject, colors);
            else
                throw new CKLBExceptionNullCppObject();
        }
		
        public void setVertCol(int idx, uint argb)
        {
            if(idx > 7)
                throw new CKLBException("idx must be between 0 and 7.");

            if(CppObject != IntPtr.Zero)
                CKLBUIFreeVertItem_setVertCol(CppObject, idx, argb);
            else
                throw new CKLBExceptionNullCppObject();
        }

        public void setUv(float[] uv)
        {
            if(uv.Length != 8)
                throw new CKLBException("UV must be a float[8] array.");

            if(CppObject != IntPtr.Zero)
                CKLBUIFreeVertItem_setUV(CppObject, uv);
            else
                throw new CKLBExceptionNullCppObject();
        }
	}
}
