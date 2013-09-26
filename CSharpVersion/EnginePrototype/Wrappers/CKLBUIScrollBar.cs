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
	public class CKLBUIScrollBar : CKLBUITask
	{
		#region DllImports
        // pParent : CKLBUITask*
        // image   : const char*
        // return  : CKLBUIScrollBar*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIScrollBar_create(
            IntPtr pParent,
	        uint order, float x, float y, float width, float height,
	        int minValue, int maxValue, int pos,
	        IntPtr image,
	        int slider_size, int min_slider_size, 
	        uint colorNormal, uint colorSelect, bool vert, bool active, bool hideMode);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIScrollBar_getMin(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScrollBar_setMin(IntPtr p, int value);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIScrollBar_getMax(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScrollBar_setMax(IntPtr p, int value);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIScrollBar_getPos(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScrollBar_setPos(IntPtr p, int value);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIScrollBar_getSliderSize(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScrollBar_setSliderSize(IntPtr p, int value);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIScrollBar_getSliderSizeMin(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScrollBar_setSliderSizeMin(IntPtr p, int value);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIScrollBar_getTouchActive(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScrollBar_setTouchActive(IntPtr p, bool active);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIScrollBar_getNormalColor(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScrollBar_setNormalColor(IntPtr p, uint color);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIScrollBar_getActiveColor(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScrollBar_setActiveColor(IntPtr p, uint color);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScrollBar_setMode(IntPtr p, uint mode);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIScrollBar_getVertical(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScrollBar_setVertical(IntPtr p, bool vertical);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static int CKLBUIScrollBar_getWidth(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScrollBar_setWidth(IntPtr p, int width);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static int CKLBUIScrollBar_getHeight(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScrollBar_setHeight(IntPtr p, int height);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBUIScrollBar_getOrder(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScrollBar_setOrder(IntPtr p, uint order);

        // return : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private extern static IntPtr CKLBUIScrollBar_getImage(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBUIScrollBar_getMode(IntPtr p);

        // name : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIScrollBar_selectScrMgr(IntPtr p, IntPtr name, int len, int[] args);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_ScrollBar"/*, typeof(CKLBUIScrollBar)*/);

        public CKLBUIScrollBar(
                                CKLBUITask parent, 
                                uint order, float x, float y, float width, float height, 
                                int minValue, int maxValue, int pos, 
                                String image, 
                                int sliderSize, int minSliderSize,
                                uint argbNormal = 0xFFFFFFFF, uint argbSelect = 0xFFFFFFFF, bool vert = true, bool active = true, bool hideMode = false, ScrollBarCallBack callback = null)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIScrollBar_create(
                        parent != null ? parent.CppObject : IntPtr.Zero,
	                    order, x, y, width, height,
	                    minValue, maxValue, pos,
	                    __MarshallingUtils.NativeUtf8FromString(image),
	                    sliderSize, minSliderSize, 
	                    argbNormal, argbSelect, vert, active, hideMode);
            NativeManagement.intercepCppError();
            bind(ptr);
            m_callback = callback;
        }

        public CKLBUIScrollBar() : base(s_classID) { }

        #endregion

        #region CallBacks

        //the "type" parameter is an ETYPE enum
        public delegate void ScrollBarCallBack(CKLBUIScrollBar caller, uint type, int pos);

        private ScrollBarCallBack m_callback;    // callback number 3

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerUI(callBackFunction), 3);
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName = null)
        {
            m_callback = (ScrollBarCallBack)anyDelegate;
        }

        public virtual void callBackFunction(uint type, int pos)
        {
            if(m_callback != null) {
                m_callback(this, type, pos);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        #endregion

        public enum ETYPE
        {
            SCROLLBAR_DRAG      = 0,
            SCROLLBAR_RELEASE   = 1
        }

		public uint Order
		{
			get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScrollBar_getOrder(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIScrollBar_setOrder(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
        public int Width
        {
            get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScrollBar_getWidth(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIScrollBar_setWidth(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        public int Height
        {
            get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScrollBar_getHeight(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIScrollBar_setHeight(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        public void getSize(out Size size)
        {
            size.width  = CKLBUIScrollBar_getWidth(CppObject);
            size.height = CKLBUIScrollBar_getHeight(CppObject);
        }
        public void setSize(Size size)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIScrollBar_setWidth(CppObject, size.width);
                CKLBUIScrollBar_setHeight(CppObject, size.height);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
        public void setSize(int width, int height)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIScrollBar_setWidth(CppObject, width);
                CKLBUIScrollBar_setHeight(CppObject, height);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
		public int Start
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScrollBar_getMin(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIScrollBar_setMin(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public int End
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScrollBar_getMax(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIScrollBar_setMax(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public int Pos
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScrollBar_getPos(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIScrollBar_setPos(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public String Img
		{
			get
            {
                if(CppObject != IntPtr.Zero) {
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUIScrollBar_getImage(CppObject));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
			//set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public int SliderSize
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScrollBar_getSliderSize(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIScrollBar_setSliderSize(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public int SliderSizeMin
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScrollBar_getSliderSizeMin(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIScrollBar_setSliderSizeMin(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public bool IsVertical
		{
			get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScrollBar_getVertical(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIScrollBar_setVertical(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public uint ArgbNormal 
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScrollBar_getNormalColor(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIScrollBar_setNormalColor(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public uint ArgbActive 
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScrollBar_getActiveColor(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIScrollBar_setActiveColor(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public bool IsTouchActive
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScrollBar_getTouchActive(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIScrollBar_setTouchActive(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
        public uint Mode
        {
            get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScrollBar_getMode(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIScrollBar_setMode(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }

		public void selectScrollManager(String name, int[] args = null)
        {
            if(CppObject != IntPtr.Zero) {
                if(args != null) {
                    CKLBUIScrollBar_selectScrMgr(CppObject, __MarshallingUtils.NativeUtf8FromString(name), args.Length, args);
                } else {
                    CKLBUIScrollBar_selectScrMgr(CppObject, __MarshallingUtils.NativeUtf8FromString(name), 0, null);
                }
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
	}
}

