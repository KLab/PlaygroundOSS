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
	public class CKLBUIProgressBar : CKLBUITask
	{
		#region DllImports
        // pParent : CKLBUITask*
        // fullImage & emptyImage & barfilterImage : const char*
        // return : CKLBUIProgressBar*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIProgressBar_create(  IntPtr pParent,
                                                                uint order, float x, float y, float width, float height,
                                                                IntPtr fullImage, IntPtr emptyImage, 
                                                                int startPix, int endPix, int anim, bool vert,
                                                                IntPtr barfilterImage);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIProgressBar_getOrder(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIProgressBar_setOrder(IntPtr p, uint order);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIProgressBar_getWidth(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIProgressBar_setWidth(IntPtr p, float width);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIProgressBar_getHeight(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIProgressBar_setHeight(IntPtr p, float height);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIProgressBar_getVertical(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIProgressBar_setVertical(IntPtr p, bool vertical);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIProgressBar_getAnimTime(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIProgressBar_setAnimTime(IntPtr p, uint time);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIProgressBar_getStart(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIProgressBar_setStart(IntPtr p, float start);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIProgressBar_getEnd(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIProgressBar_setEnd(IntPtr p, float end);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUIProgressBar_getValue(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIProgressBar_setValue(IntPtr p, float value);

        // return : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private extern static IntPtr CKLBUIProgressBar_getImgEmpty(IntPtr p);
        // empty_image : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIProgressBar_setImgEmpty(IntPtr p, IntPtr imageEmpty);

        // return : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBUIProgressBar_getImgFull(IntPtr p);
        // full_image : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIProgressBar_setImgFull(IntPtr p, IntPtr imageFull);

         // return : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private extern static IntPtr CKLBUIProgressBar_getImgFilter(IntPtr p);
        // empty_image : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIProgressBar_setImgFilter(IntPtr p, IntPtr imageFilter);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIProgressBar_reset(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIProgressBar_getFilterVisible(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIProgressBar_setFilterVisible(IntPtr p, bool value);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIProgressBar_getFilterColor(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIProgressBar_setFilterColor(IntPtr p, uint value);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIProgressBar_setFilterAnim(IntPtr p, bool bColAnim, uint argb1, uint argb2, uint freq);

		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_ProgressBar"/*, typeof(CKLBUIProgressBar)*/);

        public CKLBUIProgressBar(   CKLBUITask parent, 
                                    uint order, float x, float y, float width, float height, 
                                    String imageFull, String imageEmpty,
                                    int startPix = -1, int endPix = -1, int animTime = 0, bool verticalFlag = false,
                                    String barfilterImage = null)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIProgressBar_create(  parent != null ? parent.CppObject : IntPtr.Zero,
                                                    order, x, y, width, height,
                                                    __MarshallingUtils.NativeUtf8FromString(imageFull), __MarshallingUtils.NativeUtf8FromString(imageEmpty),
                                                    startPix, endPix, animTime, verticalFlag, 
                                                    __MarshallingUtils.NativeUtf8FromString(barfilterImage));
            NativeManagement.intercepCppError();
            bind(ptr);
        }

        public CKLBUIProgressBar() : base(s_classID) { }

        #endregion

        public uint     Order
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIProgressBar_getOrder(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIProgressBar_setOrder(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
        public float    Width
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIProgressBar_getWidth(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIProgressBar_setWidth(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        public float    Height
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIProgressBar_getHeight(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIProgressBar_setHeight(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        public void     getSize(out FSize size)
        {
            if(CppObject != IntPtr.Zero) {
                size.width = CKLBUIProgressBar_getWidth(CppObject);
                size.height = CKLBUIProgressBar_getHeight(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
        public void     setSize(FSize size)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIProgressBar_setWidth(CppObject, size.width);
                CKLBUIProgressBar_setHeight(CppObject, size.height);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
        public void     setSize(float width, float height)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIProgressBar_setWidth(CppObject, width);
                CKLBUIProgressBar_setHeight(CppObject, height);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
		public bool     IsVertical
		{
            get
            {
               if(CppObject != IntPtr.Zero) {
                    return CKLBUIProgressBar_getVertical(CppObject);
               } else {
                    throw new CKLBExceptionNullCppObject();
               }
            }
            set
            {
               if(CppObject != IntPtr.Zero) {
                    CKLBUIProgressBar_setVertical(CppObject, value);
               } else {
                    throw new CKLBExceptionNullCppObject();
               }
            }
		}
        public uint     AnimTime
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIProgressBar_getAnimTime(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIProgressBar_setAnimTime(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public float    Start 
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIProgressBar_getStart(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIProgressBar_setStart(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public float    End 
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIProgressBar_getEnd(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIProgressBar_setEnd(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
        public String   ImageEmpty
		{
			get 
            {
                if(CppObject != IntPtr.Zero) {
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUIProgressBar_getImgEmpty(CppObject));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIProgressBar_setImgEmpty(CppObject, __MarshallingUtils.NativeUtf8FromString(value));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public String   ImageFull
		{
			get 
            {
                if(CppObject != IntPtr.Zero) {
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUIProgressBar_getImgFull(CppObject));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIProgressBar_setImgFull(CppObject, __MarshallingUtils.NativeUtf8FromString(value));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
        public String   ImageFilter
		{
			get
            {
                if(CppObject != IntPtr.Zero) {
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUIProgressBar_getImgFilter(CppObject));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIProgressBar_setImgFilter(CppObject, __MarshallingUtils.NativeUtf8FromString(value));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public float    Value
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIProgressBar_getValue(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIProgressBar_setValue(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
        public bool     FilterVisible
        {
            get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIProgressBar_getFilterVisible(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIProgressBar_setFilterVisible(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        public uint     FilterColor
        {
            get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIProgressBar_getFilterColor(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIProgressBar_setFilterColor(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }

        public void reset() 
        {
			if(CppObject != IntPtr.Zero) {
                CKLBUIProgressBar_reset(CppObject);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
        public void complete() 
		{ 
			if(CppObject != IntPtr.Zero) {
                CKLBUIProgressBar_setValue(CppObject, CKLBUIProgressBar_getEnd(CppObject));
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

        public bool setFilterAnim(bool bColAnim, uint argb1 = 0xffffffff, uint argb2 = 0xffffffff, uint freq = 500)
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBUIProgressBar_setFilterAnim(CppObject,bColAnim, argb1, argb2, freq);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
	}
}

