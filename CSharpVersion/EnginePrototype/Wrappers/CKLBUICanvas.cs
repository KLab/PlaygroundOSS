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
	public class CKLBUICanvas : CKLBUITask
	{
		#region DllImports
        // pParent : CKLBUITask*
        // return : CKLBUICanvas*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUICanvas_create(IntPtr pParent, uint order, float x, float y, uint vertexMax, uint indexMax);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUICanvas_getOrder(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUICanvas_setOrder(IntPtr p, uint order);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBUICanvas_getIdxMax(IntPtr p);
		
        // asset : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUICanvas_addResource(IntPtr p, IntPtr asset);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUICanvas_setFreeze(IntPtr p, bool freeze);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUICanvas_drawImage(IntPtr p, float x, float y, uint idx, uint color);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUICanvas_drawImageScale(IntPtr p, float x, float y, float scale, uint idx, uint color);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUICanvas_fillRect(IntPtr p, float x, float y, float w, float h, uint color);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUICanvas_startDynamicSection(IntPtr p, uint idx);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUICanvas_endDynamicSection(IntPtr p, uint idx);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUICanvas_dynamicSectionTranslate(IntPtr p, uint idx, float deltaX, float deltaY);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUICanvas_dynamicSectionColor(IntPtr p, uint idx, uint color);
		#endregion

        #region Constructors
        static uint s_classID = __FrameworkUtils.RegisterClass("UI_Canvas"/*, typeof(CKLBUICanvas)*/);

        public CKLBUICanvas(CKLBUITask parent, uint order, float x, float y, uint vertexMax, uint indexMax, CallBack onDrawCallBack)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUICanvas_create(parent != null ? parent.CppObject : IntPtr.Zero, order, x, y, vertexMax, indexMax);
            NativeManagement.intercepCppError();
            bind(ptr);
            m_callback = onDrawCallBack;
        }

        public CKLBUICanvas() : base(s_classID) { }
        #endregion

        #region CallBacks

        public delegate void CallBack(CKLBUICanvas caller);
        private CallBack m_callback;

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerV(callBackFunction));
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName = null)
        {
            m_callback = (CallBack)anyDelegate;
        }

        public virtual void callBackFunction()
        {
            if(m_callback != null) {
                m_callback(this);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }
        #endregion

        public uint Order
		{
			get
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUICanvas_getOrder(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
			set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUICanvas_setOrder(CppObject,value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public uint IdxMax
		{
			get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUICanvas_getIdxMax(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
			//set { throw new CKLBExceptionForbiddenMethod(); }
		}
        public bool Freeze
        {
            //get { throw new CKLBExceptionForbiddenMethod(); }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUICanvas_setFreeze(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }

        public bool addResource(String asset)
        {
            if(CppObject != IntPtr.Zero) {
                NativeManagement.resetCppError();
                bool res = CKLBUICanvas_addResource(CppObject, __MarshallingUtils.NativeUtf8FromString(asset));
                NativeManagement.intercepCppError();
                return res;
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void drawImage(float x, float y, uint idx, uint color)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUICanvas_drawImage(CppObject, x, y, idx, color);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void drawImageScale(float x, float y, float scale, uint idx, uint color)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUICanvas_drawImageScale(CppObject, x, y, scale, idx, color);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void fillRect(float x, float y, float w, float h, uint color)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUICanvas_fillRect(CppObject, x, y, w, h, color);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void startDynamicSection(uint idx)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUICanvas_startDynamicSection(CppObject, idx);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void endDynamicSection(uint idx)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUICanvas_endDynamicSection(CppObject, idx);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void dynamicSectionTranslate(uint idx, float deltaX, float deltaY)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUICanvas_dynamicSectionTranslate(CppObject, idx, deltaX, deltaY);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void dynamicSectionColor(uint idx, uint color)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUICanvas_dynamicSectionColor(CppObject, idx, color);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
	}
}
