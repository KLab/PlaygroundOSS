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
	public class CKLBUIRubberBand : CKLBUITask
	{
		#region DllImports
        //return : CKLBUIRubberBand*
        // pParent : CKLBUITask*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIRubberBand_create(IntPtr pParent, uint order, float x, float y, uint resolution, IntPtr origin, IntPtr joint,
                                                             IntPtr point, uint flags, uint animTime, int joint_order_off, int point_order_off, bool rot_origin, bool rot_joint, bool rot_point);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIRubberBand_getOriginX(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIRubberBand_setOriginX(IntPtr p, float x);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIRubberBand_getOriginY(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIRubberBand_setOriginY(IntPtr p, float y);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIRubberBand_getPointX(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIRubberBand_setPointX(IntPtr p, float x);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIRubberBand_getPointY(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIRubberBand_setPointY(IntPtr p, float y);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIRubberBand_getFAnim(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIRubberBand_setFAnim(IntPtr p, bool fAnim);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIRubberBand_getFAnimRT(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIRubberBand_setFAnimRT(IntPtr p, bool fAnimRT);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBUIRubberBand_getAnimTime(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIRubberBand_setAnimTime(IntPtr p, uint animTime);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIRubberBand_getOrder(IntPtr p);
		
		// return : const char *
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static IntPtr CKLBUIRubberBand_getAssetOrigin(IntPtr p);
		
		// return : const char *
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static IntPtr CKLBUIRubberBand_getAssetJoint(IntPtr p);
		
		// return : const char *
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static IntPtr CKLBUIRubberBand_getAssetPoint(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIRubberBand_setOrder(IntPtr p, uint orderOrigin, uint orderJoint, uint orderPoint);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_RubberBand"/*, typeof(CKLBUIRubberBand)*/);

        public CKLBUIRubberBand(CKLBUITask parent, uint order, float origin_x, float origin_y, String origin_asset, 
                                String joint_asset, String point_asset, uint resolution = 10, uint option_flags = 0, 
                                uint animation_time = 0, int joint_priority_offset = 0, int point_priority_offset = 0, 
                                bool rot_origin = true, bool rot_joint = false, bool rot_point = true)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIRubberBand_create(parent != null ? parent.CppObject : IntPtr.Zero, order, origin_x, origin_y, resolution, __MarshallingUtils.NativeUtf8FromString(origin_asset),
                                                 __MarshallingUtils.NativeUtf8FromString(joint_asset), __MarshallingUtils.NativeUtf8FromString(point_asset), option_flags,
                                                 animation_time, joint_priority_offset, point_priority_offset, rot_origin, rot_joint, rot_point);
            NativeManagement.intercepCppError();
            bind(ptr);
        }

        public CKLBUIRubberBand() : base(s_classID) { }

        #endregion

        public uint Order
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return CKLBUIRubberBand_getOrder(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public String AssetOrigin
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUIRubberBand_getAssetOrigin(CppObject));
                else
                    throw new CKLBExceptionNullCppObject();
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
		}
        public String AssetJoint
        {
            get
            {
                if(CppObject != IntPtr.Zero)
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUIRubberBand_getAssetJoint(CppObject));
                else
                    throw new CKLBExceptionNullCppObject();
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
        }
		public String AssetPoint
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUIRubberBand_getAssetPoint(CppObject));
                else
                    throw new CKLBExceptionNullCppObject();
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public float OriginX
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return CKLBUIRubberBand_getOriginX(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUIRubberBand_setOriginX(CppObject, value);
                else
                    throw new CKLBExceptionNullCppObject();
            }
		}
		public float OriginY
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return CKLBUIRubberBand_getOriginY(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUIRubberBand_setOriginY(CppObject, value);
                else
                    throw new CKLBExceptionNullCppObject();
            }
		}
		public float PointX
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return CKLBUIRubberBand_getPointX(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUIRubberBand_setPointX(CppObject, value);
                else
                    throw new CKLBExceptionNullCppObject();
            }
		}
		public float PointY
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return CKLBUIRubberBand_getPointY(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUIRubberBand_setPointY(CppObject, value);
                else
                    throw new CKLBExceptionNullCppObject();
            }
		}
		public bool AnimFlag
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return CKLBUIRubberBand_getFAnim(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUIRubberBand_setFAnim(CppObject, value);
                else
                    throw new CKLBExceptionNullCppObject();
            }
		}
		public bool RealTimeFlag
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return CKLBUIRubberBand_getFAnimRT(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUIRubberBand_setFAnimRT(CppObject, value);
                else
                    throw new CKLBExceptionNullCppObject();
            }
		}
		public uint AnimTime
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return CKLBUIRubberBand_getAnimTime(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUIRubberBand_setAnimTime(CppObject, value);
                else
                    throw new CKLBExceptionNullCppObject();
            }
		}

        public void setOrder(uint orderOrigin, uint orderJoint, uint orderPoint) 
        {
            if(CppObject != IntPtr.Zero)
                    CKLBUIRubberBand_setOrder(CppObject, orderOrigin, orderJoint, orderPoint);
                else
                    throw new CKLBExceptionNullCppObject();
        }
	}
}

