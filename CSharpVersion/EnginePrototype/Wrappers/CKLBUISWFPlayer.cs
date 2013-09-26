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
	public class CKLBUISWFPlayer  : CKLBUITask 
    {
		#region DllImports
        // parent    : CKLBUITask*
        // asset     : const char*
        // movieName : const char*
        // return    : CKLBUISWFPlayer*
        // replaceList : const char**
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUISWFPlayer_create(IntPtr parent, uint order, float x, float y, IntPtr asset, IntPtr movieNameconst, IntPtr[] replaceList, int assetCnt);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUISWFPlayer_getPlay(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUISWFPlayer_setPlay(IntPtr p, bool play);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBUISWFPlayer_getOrder(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUISWFPlayer_setOrder(IntPtr p, uint order);
		
		// label : const char *
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static void CKLBUISWFPlayer_gotoFrame(IntPtr p, IntPtr label);
		
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUISWFPlayer_getFrameRate(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUISWFPlayer_setFrameRate(IntPtr p, uint fps);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUISWFPlayer_isAnimating(IntPtr p);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUISWFPlayer_setFrameRateScale(IntPtr p, float scale);

        // return : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private extern static IntPtr CKLBUISWFPlayer_getAsset(IntPtr p);

        // return : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private extern static IntPtr CKLBUISWFPlayer_getMovieName(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static float CKLBUISWFPlayer_getVolume(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUISWFPlayer_setVolume(IntPtr p, float volume);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_SWFPlayer"/*, typeof(CKLBUISWFPlayer)*/);

        public CKLBUISWFPlayer(CKLBUITask parent, uint order, float x, float y, String asset, String movieName, CallBack callback, String[] replaceList = null, int assetCnt = 0)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUISWFPlayer_create(parent != null ? parent.CppObject : IntPtr.Zero, order, x, y, 
                                        __MarshallingUtils.NativeUtf8FromString(asset), __MarshallingUtils.NativeUtf8FromString(movieName),
                                        (replaceList != null) ? __MarshallingUtils.NativeUtf8ArrayFromStringArray(replaceList, replaceList.Length) : null, assetCnt);
            NativeManagement.intercepCppError();
            bind(ptr);
            m_callback = callback;
        }

        public CKLBUISWFPlayer() : base(s_classID) { }

        #endregion

        #region CallBacks

        public delegate void CallBack(CKLBUISWFPlayer caller, String label);
        
        private CallBack m_callback;

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerS(callBackFunction));
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName = null)
        {
            m_callback = (CallBack)anyDelegate;
        }

        // label : const char* from Cpp
        public virtual void callBackFunction(IntPtr label)
        {
            if(m_callback != null) {
                m_callback(this, __MarshallingUtils.StringFromNativeUtf8(label));
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
                    return CKLBUISWFPlayer_getOrder(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set 
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUISWFPlayer_setOrder(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public String Asset
		{
			get 
            {
                if(CppObject != IntPtr.Zero) {
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUISWFPlayer_getAsset(CppObject));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
			//set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public String MovieName
		{
			get 
            {
                if(CppObject != IntPtr.Zero) {
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUISWFPlayer_getMovieName(CppObject));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public bool IsPlaying
		{
            get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUISWFPlayer_getPlay(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUISWFPlayer_setPlay(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
        public uint Framerate
        {
            get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUISWFPlayer_getFrameRate(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUISWFPlayer_setFrameRate(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        public bool IsAnim
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUISWFPlayer_isAnimating(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
        }
        public float Volume
        {
            get 
            { 
                if(CppObject != IntPtr.Zero) {
                    return CKLBUISWFPlayer_getVolume(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUISWFPlayer_setVolume(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }

        public void play()
		{ 
			if(CppObject != IntPtr.Zero) {
				CKLBUISWFPlayer_setPlay(CppObject, true);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
        public void stop() 
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUISWFPlayer_setPlay(CppObject, false);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
        public void goToFrame(String label) 
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUISWFPlayer_gotoFrame(CppObject, __MarshallingUtils.NativeUtf8FromString(label));
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
        public void setFramerateScale(float scale)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUISWFPlayer_setFrameRateScale(CppObject, scale);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
        // added : replaceAssets()
	}
}

