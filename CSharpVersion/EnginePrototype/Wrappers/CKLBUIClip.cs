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
	public class CKLBUIClip : CKLBUITask
	{
        
		#region DllImports
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIClip_create(IntPtr pParent, uint baseOrder, uint maxOrder, float x, float y, float clipWidth, float clipHeight);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIClip_getOrder(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIClip_setOrder(IntPtr p, uint order);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIClip_getMaxOdr(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIClip_setMaxOdr(IntPtr p, uint maxodr);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIClip_getWidth(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIClip_setWidth(IntPtr p, float width);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIClip_getHeight(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIClip_setHeight(IntPtr p, float height);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIClip_setPosition(IntPtr p, float x, float y);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIClip_setSize(IntPtr p, float width, float height);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_Clip"/*, typeof(CKLBUIClip)*/);

		public CKLBUIClip(CKLBUITask parent, uint baseOrder, uint maxOrder, float x, float y, float clipWidth, float clipHeight)
            : base(s_classID)
		{
			NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIClip_create( parent != null ? parent.CppObject : IntPtr.Zero, 
                                                baseOrder, maxOrder, x, y, clipWidth, clipHeight);
            NativeManagement.intercepCppError();
            bind(ptr);
		}

        public CKLBUIClip() : base(s_classID) { }

        #endregion

		public uint  Order
		{
			get 
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUIClip_getOrder(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIClip_setOrder(CppObject, value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public uint  MaxOrder
		{
			get 
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUIClip_getMaxOdr(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIClip_setMaxOdr(CppObject, value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public float Width
		{
			get 
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUIClip_getWidth(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIClip_setWidth(CppObject, value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public float Height
		{
			get 
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUIClip_getHeight(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIClip_setHeight(CppObject, value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public void  getSize(out FSize size)
		{
			if(CppObject != IntPtr.Zero) {
				size.width  = CKLBUIClip_getWidth(CppObject);
				size.height = CKLBUIClip_getHeight(CppObject);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
		public void  setSize(FSize size)
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUIClip_setSize(CppObject, size.width, size.height);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
		public void  setSize(float width, float height)
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUIClip_setSize(CppObject, width, height);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public void setPosition(float x, float y)
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUIClip_setPosition(CppObject, x, y);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
	}
}
