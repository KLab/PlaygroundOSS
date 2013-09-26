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

	public class CKLBUIVirtualDoc : CKLBUITask
	{
		#region DllImports
        // pParent : CKLBUITask*
        // return  : CKLBUIVirtualDoc*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBUIVirtualDoc_create(   IntPtr pParent,
                                                                uint order, float x, float y,
                                                                uint docWidth, uint docHeight,
                                                                uint viewWidth, uint viewHeight,
                                                                uint maxCommandNums, bool verticalFlag);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVirtualDoc_clear(IntPtr p, uint color);
		
		//  fontName : const char *
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static void CKLBUIVirtualDoc_setFont(IntPtr p, uint idx, IntPtr fontName, uint fontSize);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVirtualDoc_setViewPortPos(IntPtr p, int x, int y);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVirtualDoc_drawLine(IntPtr p, int x0, int y0, int x1, int y1, uint color);
		
		// image : const char *
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static void CKLBUIVirtualDoc_drawImage(IntPtr p, int x0, int y0, IntPtr image, uint alpha);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVirtualDoc_fillRect(IntPtr p, int x0, int y0, uint width, uint height, uint color, bool fill);
		
		// str : const char *
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static void CKLBUIVirtualDoc_drawText(IntPtr p, int x0, int y0, IntPtr str, uint color, uint fontidx);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVirtualDoc_startDocument(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIVirtualDoc_checkDocumentSize(IntPtr p);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVirtualDoc_endDocument(IntPtr p);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIVirtualDoc_getCommandMax(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVirtualDoc_setCommandMax(IntPtr p, uint command);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIVirtualDoc_getDocHeight(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVirtualDoc_setDocHeight(IntPtr p, uint command);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIVirtualDoc_getDocWidth(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVirtualDoc_setDocWidth(IntPtr p, uint command);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIVirtualDoc_getVertical(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVirtualDoc_setVertical(IntPtr p, bool vertical);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIVirtualDoc_getViewHeight(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVirtualDoc_setViewHeight(IntPtr p, uint height);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIVirtualDoc_getViewWidth(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVirtualDoc_setViewWidth(IntPtr p, uint width);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIVirtualDoc_getOrder(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVirtualDoc_setOrder(IntPtr p, uint order);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIVirtualDoc_setAlign(IntPtr p, uint align, int alignWidth);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_VirtualDoc"/*, typeof(CKLBUIVirtualDoc)*/);

        public CKLBUIVirtualDoc(CKLBUITask parent, uint order, float x, float y, uint docWidth, uint docHeight, uint viewWidth, uint viewHeight, uint maxCommandNums, bool verticalFlag, CallBack callback)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIVirtualDoc_create(parent != null ? parent.CppObject : IntPtr.Zero, order, x, y, docWidth, docHeight, viewWidth, viewHeight, maxCommandNums, verticalFlag);
            NativeManagement.intercepCppError();
            bind(ptr);
            m_callback = callback;
            m_isLocked = false;
        }

        public CKLBUIVirtualDoc() : base(s_classID) { }

        #endregion

        #region CallBacks

        public delegate void CallBack(CKLBUIVirtualDoc caller, ETYPE type, int x, int y, uint moveX, uint moveY);
        
        private CallBack m_callback;

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerUIIUU(callBackFunction));
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName = null)
        {
            m_callback = (CallBack)anyDelegate;
        }

        public virtual void callBackFunction(uint type, int x, int y, uint moveX, uint moveY)
        {
            if(m_callback != null) {
                m_callback(this, (ETYPE)type, x, y, moveX, moveY);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        #endregion

        private bool m_isLocked;

        public enum ETYPE : uint
        {
            TAP,
            DRAG,
            RELEASE
        }
        public enum EALIGN : uint {
            VD_ALIGN_LEFT = 0,
	        VD_ALIGN_CENTER,
	        VD_ALIGN_RIGHT,
        }

		public uint Order
		{
			get 
			{
				if(CppObject != IntPtr.Zero) {
                    return CKLBUIVirtualDoc_getOrder(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
			{
				if(CppObject != IntPtr.Zero) {
                    CKLBUIVirtualDoc_setOrder(CppObject, value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public uint CmdMax
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIVirtualDoc_getCommandMax(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIVirtualDoc_setCommandMax(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public bool Vertical
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIVirtualDoc_getVertical(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIVirtualDoc_setVertical(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public uint DocWidth
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIVirtualDoc_getDocWidth(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIVirtualDoc_setDocWidth(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
        public uint DocHeight
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIVirtualDoc_getDocHeight(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIVirtualDoc_setDocHeight(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        public void getDocSize(out USize size)
        {
            if(CppObject != IntPtr.Zero) {
                size.width = CKLBUIVirtualDoc_getDocWidth(CppObject);
                size.height = CKLBUIVirtualDoc_getDocHeight(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
        public void setDocSize(USize size)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIVirtualDoc_setDocWidth(CppObject, size.width);
                CKLBUIVirtualDoc_setDocHeight(CppObject, size.height);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
        public void setDocSize(uint width, uint height)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIVirtualDoc_setDocWidth(CppObject, width);
                CKLBUIVirtualDoc_setDocHeight(CppObject, height);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
		public uint ViewWidth
		{
			get 
			{
				if(CppObject != IntPtr.Zero) {
                    return CKLBUIVirtualDoc_getViewWidth(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
			{
				if(CppObject != IntPtr.Zero) {
                    CKLBUIVirtualDoc_setViewWidth(CppObject, value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public uint ViewHeight
		{
			get 
			{
				if(CppObject != IntPtr.Zero) {
                    return CKLBUIVirtualDoc_getViewHeight(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set 
			{
				if(CppObject != IntPtr.Zero) {
                    CKLBUIVirtualDoc_setViewHeight(CppObject, value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
        public void getViewSize(out USize size)
        {
            if(CppObject != IntPtr.Zero) {
                size.width = CKLBUIVirtualDoc_getViewWidth(CppObject);
                size.height = CKLBUIVirtualDoc_getViewHeight(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
        public void setViewSize(USize size)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIVirtualDoc_setViewWidth(CppObject, size.width);
                CKLBUIVirtualDoc_setViewHeight(CppObject, size.height);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
        public void setViewSize(uint width, uint height)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIVirtualDoc_setViewWidth(CppObject, width);
                CKLBUIVirtualDoc_setViewHeight(CppObject, height);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

		public void setFont(uint index, String name, uint size)
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUIVirtualDoc_setFont(CppObject, index, __MarshallingUtils.NativeUtf8FromString(name), size);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

        public void clear(uint argb)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIVirtualDoc_clear(CppObject, argb);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void setViewPortPos(int x, int y)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIVirtualDoc_setViewPortPos(CppObject, x, y);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        // Default value : ViewWidth
		public void setAlign(EALIGN align, int alignWidth = -1)
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUIVirtualDoc_setAlign(CppObject, (uint)align, (alignWidth == -1) ? (int)ViewWidth : alignWidth);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
		
        public void startDrawList(uint commandCount) {
            if(CppObject != IntPtr.Zero) {
                CKLBUIVirtualDoc_setCommandMax(CppObject, commandCount);
                CKLBUIVirtualDoc_checkDocumentSize(CppObject);
                CKLBUIVirtualDoc_startDocument(CppObject);
                m_isLocked = true;
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void endDrawList() {
            CKLBUIVirtualDoc_endDocument(CppObject);
            m_isLocked = false;
        }

        public void drawLine(int x0, int y0, int x1, int y1, uint argb)
        {
            if(CppObject == IntPtr.Zero) { throw new CKLBExceptionNullCppObject(); }

            if(m_isLocked) {
                CKLBUIVirtualDoc_drawLine(CppObject, x0, y0, x1, y1, argb);
            } else {
                throw new CKLBException("Please use the draw functions in startDrawList()/endDrawList() blocks");
            }
        }

		public void drawText(int x0, int y0, String str, uint argb, uint font_index) 
		{
            if(CppObject == IntPtr.Zero) { throw new CKLBExceptionNullCppObject(); }

            if(m_isLocked) {
                CKLBUIVirtualDoc_drawText(CppObject, x0, y0, __MarshallingUtils.NativeUtf8FromString(str), argb, font_index);
            } else {
                throw new CKLBException("Please use the draw functions in startDrawList()/endDrawList() blocks");
            }
		}

        public void drawFillRect(int x0, int y0, uint width, uint height, uint argb, bool fill) 
		{
            if(CppObject == IntPtr.Zero) { throw new CKLBExceptionNullCppObject(); }

            if(m_isLocked) {
                CKLBUIVirtualDoc_fillRect(CppObject, x0, y0, width, height, argb, fill);
            } else {
                throw new CKLBException("Please use the draw functions in startDrawList()/endDrawList() blocks");
            }
		}

        public void drawImage(int x, int y, String image, uint alpha)
        {
            if(CppObject == IntPtr.Zero) { throw new CKLBExceptionNullCppObject(); }

            if(m_isLocked) {
                NativeManagement.resetCppError();
                CKLBUIVirtualDoc_drawImage(CppObject, x, y, __MarshallingUtils.NativeUtf8FromString(image), alpha);
                NativeManagement.intercepCppError();
            } else {
                throw new CKLBException("Please use the draw functions in startDrawList()/endDrawList() blocks");
            }
        }

	}
}