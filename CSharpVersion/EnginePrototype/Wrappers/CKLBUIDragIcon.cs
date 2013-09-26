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
	public class CKLBUIDragIcon : CKLBUITask
	{
		#region DllImports
        //return : CKLBUIDragIcon*
        // pParent : CKLBUITask*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIDragIcon_create(IntPtr pParent, uint order, float x, float y, ref Area tap_area, IntPtr asset, IntPtr drag_asset,
                                                            int drag_order_offset, float drag_alpha, float center_x, float center_y, uint flags);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIDragIcon_getOrder(IntPtr p);

        //return : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBUIDragIcon_getAsset(IntPtr p);

        //return : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBUIDragIcon_getDrag(IntPtr p);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIDragIcon_getFlags(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIDragIcon_setFlags(IntPtr p, uint flag);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIDragIcon_getEnable(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIDragIcon_setEnable(IntPtr p, bool enable);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIDragIcon_getDragScaleX(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIDragIcon_setDragScaleX(IntPtr p, float x);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIDragIcon_getDragScaleY(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIDragIcon_setDragScaleY(IntPtr p, float y);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIDragIcon_dragArea(IntPtr p, ref Area area);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_DragIcon"/*, typeof(CKLBUIDragIcon)*/);

        public CKLBUIDragIcon(  CKLBUITask parent, 
                                uint order, float x, float y, ref Area tap_area, String asset, String drag_asset, 
                                int drag_order_offset, float drag_alpha, float center_x, float center_y, CallBack callback, uint flags = 0)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIDragIcon_create( parent != null ? parent.CppObject : IntPtr.Zero, 
                                                order, x, y, ref tap_area, __MarshallingUtils.NativeUtf8FromString(asset), __MarshallingUtils.NativeUtf8FromString(drag_asset),
                                                drag_order_offset, drag_alpha, center_x, center_y, flags);
            NativeManagement.intercepCppError();
            bind(ptr);
            m_callback = callback;
        }

        public CKLBUIDragIcon() : base(s_classID) { }

        #endregion

        #region CallBacks

        public delegate void CallBack(CKLBUIDragIcon caller, uint type, int x, int y);
        
        private CallBack m_callback;

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerUII(callBackFunction));
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName = null)
        {
            m_callback = (CallBack)anyDelegate;
        }

        public virtual void callBackFunction(uint type, int x, int y)
        {
            if(m_callback != null){
                m_callback(this, type, x, y);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        #endregion

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct Area
        {
            public Area(int _x, int _y, int _width, int _height)
            {
                x       = _x;
                y       = _y;
                width   = _width;
                height  = _height;
            }

            public int x;
            public int y;
            public int width;
            public int height;

            public void setValues(int _x, int _y, int _width, int _height)
            {
                x       = _x;
                y       = _y;
                width   = _width;
                height  = _height;
            }
        }

        public enum ESTEP
        {
            DRAG,
            RELEASE
        }

        public enum EFLAGS : uint
        {
            F_DICON_BASEINVISIBLE = 4
        }

		public uint Order 
		{
			get
			{
				if(CppObject != IntPtr.Zero)
					return CKLBUIDragIcon_getOrder (CppObject);
				else
					throw new CKLBExceptionNullCppObject ();
			}
			//set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public String Asset
		{
			get
            {
                if(CppObject != IntPtr.Zero) {
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUIDragIcon_getAsset(CppObject));
                } else {
                    throw new CKLBExceptionNullCppObject();
				}
            }
			//set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public String DragAsset
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUIDragIcon_getDrag(CppObject));
                } else {
                    throw new CKLBExceptionNullCppObject();
				}
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public EFLAGS Flags
		{
			get
			{
				if(CppObject != IntPtr.Zero) {
					return (EFLAGS)CKLBUIDragIcon_getFlags(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
				}
			}
			set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIDragIcon_setFlags(CppObject, (uint)value);
				} else {
					throw new CKLBExceptionNullCppObject();
				}
			}
		}
		public float DragScaleX
		{
			get
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUIDragIcon_getDragScaleX(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
				}
			}
			set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIDragIcon_setDragScaleX(CppObject,value);
				} else {
					throw new CKLBExceptionNullCppObject();
				}
			}
		}
		public float DragScaleY
		{
			get
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUIDragIcon_getDragScaleY(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
				}
			}
			set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIDragIcon_setDragScaleY(CppObject,value);
				} else {
					throw new CKLBExceptionNullCppObject();
				}
			}
		}
        public bool Enable
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIDragIcon_getEnable(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
				}
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIDragIcon_setEnable(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
				}
            }
        }

        public void dragArea(Area area) 
        {  
            if(CppObject != IntPtr.Zero) {
                CKLBUIDragIcon_dragArea(CppObject, ref area);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
	}
}
