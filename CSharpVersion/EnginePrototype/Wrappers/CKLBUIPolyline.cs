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
	public class CKLBUIPolyline : CKLBUITask
	{
		#region DllImports
        // parent : CKLBUITask*
        // return : CKLBUIPolyline*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIPolyline_create(IntPtr parent, uint order, uint maxPoint);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIPolyline_getMaxPoint(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIPolyline_setMaxPoint(IntPtr p, uint maxpointcount);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIPolyline_getOrder(IntPtr p);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIPolyline_getPointCount(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIPolyline_setPointCount(IntPtr p, uint pointcount);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIPolyline_setPoint(IntPtr p, uint idx, float x, float y);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIPolyline_getColor(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIPolyline_setColor(IntPtr p, uint color);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_Polyline"/*, typeof(CKLBUIPolyline)*/);

        public CKLBUIPolyline(CKLBUITask parent, uint order, uint maxPoint) : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIPolyline_create(parent != null ? parent.CppObject : IntPtr.Zero, order, maxPoint);
            NativeManagement.intercepCppError();
            bind(ptr);
        }

        public CKLBUIPolyline() : base(s_classID) { }

        #endregion

        public uint Order
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIPolyline_getOrder(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
			//set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public uint MaxPointCount 
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIPolyline_getMaxPoint(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIPolyline_setMaxPoint(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
        public uint PointCount
        {
            get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIPolyline_getPointCount(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    if(value > 0) {
                        CKLBUIPolyline_setPointCount(CppObject, value);
                    } else {
                        throw new CKLBException("PointCount must be strictly positive");
                    }
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        public uint Color
        {
            get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIPolyline_getColor(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIPolyline_setColor(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }

        public void setPoint(uint point_index, float x, float y)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIPolyline_setPoint(CppObject, point_index, x, y);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
	}
}

