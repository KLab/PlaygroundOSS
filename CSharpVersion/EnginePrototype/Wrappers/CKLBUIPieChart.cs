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
	public class CKLBUIPieChart : CKLBUITask
	{
		#region DllImports
        //return : CKLBUIPieChart*
        // pParent : CKLBUITask*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIPieChart_create(IntPtr pParent, uint order, float x, float y, float width, float height, IntPtr asset,
                                                            float start, float end, int anim, float initial);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIPieChart_getStart(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIPieChart_setStart(IntPtr p, float start);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIPieChart_getEnd(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIPieChart_setEnd(IntPtr p, float end);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIPieChart_getValue(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIPieChart_setValue(IntPtr p, float value);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIPieChart_getAnim(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBUIPieChart_getOrder(IntPtr p);

        // assetName : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIPieChart_changeAsset(IntPtr p, IntPtr assetName);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_PieChart"/*, typeof(CKLBUIPieChart)*/);

        public CKLBUIPieChart(CKLBUITask parent, uint order, float x, float y, float width, float height, String image_asset, float start_angle, float end_angle, int anim_time = 0, float initial_value = 0.0f)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIPieChart_create(parent != null ? parent.CppObject : IntPtr.Zero, order, x, y, width, height, __MarshallingUtils.NativeUtf8FromString(image_asset), start_angle, end_angle, anim_time, initial_value);
            NativeManagement.intercepCppError();
            bind(ptr);
        }

        public CKLBUIPieChart() : base(s_classID) { }

        #endregion

        public uint  Order
		{
			get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIPieChart_getOrder(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
			//set { throw new CKLBExceptionForbiddenMethod (); }
		}
		public float Start
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIPieChart_getStart(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIPieChart_setStart(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
		public float End
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIPieChart_getEnd(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIPieChart_setEnd(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
		public float Value
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIPieChart_getValue(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIPieChart_setValue(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
		public int   Anim
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIPieChart_getAnim(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
        }

        public bool changeAsset(String assetName)
        {
            if(CppObject != IntPtr.Zero) {
                NativeManagement.resetCppError();
                bool res = CKLBUIPieChart_changeAsset(CppObject, __MarshallingUtils.NativeUtf8FromString(assetName));
                NativeManagement.intercepCppError();
                return res;
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
	}
}
