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
	public class CKLBUIMoviePlayer : CKLBUITask
	{
		#region DllImports
        //return : CKLBUIMoviePlayer*
        // pParent : CKLBUITask*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIMoviePlayer_create(IntPtr pParent, bool mode, float x, float y, float width, float height, IntPtr url);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIMoviePlayer_getWidth(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIMoviePlayer_setWidth(IntPtr p, uint width);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBUIMoviePlayer_getHeight(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIMoviePlayer_setHeight(IntPtr p, uint height);
		
		// return and text : const char *
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static IntPtr CKLBUIMoviePlayer_getText(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIMoviePlayer_setText(IntPtr p, IntPtr text);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIMoviePlayer_moviePlay(IntPtr p);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIMoviePlayer_movieStop(IntPtr p);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIMoviePlayer_moviePause(IntPtr p);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIMoviePlayer_movieResume(IntPtr p);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_MoviePlayer"/*, typeof(CKLBUIMoviePlayer)*/);

        public CKLBUIMoviePlayer(CKLBUITask parent, bool background_mode, float x, float y, float width, float height, CallBack callback, String url = null)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIMoviePlayer_create(parent != null ? parent.CppObject : IntPtr.Zero, background_mode, x, y, width, height, __MarshallingUtils.NativeUtf8FromString(url));
            NativeManagement.intercepCppError();
            bind(ptr);
            m_callback = callback;
        }

        public CKLBUIMoviePlayer() : base(s_classID) { }

        #endregion

        #region CallBacks

        public delegate void CallBack(CKLBUIMoviePlayer caller);

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
            if(m_callback != null)
            {
                m_callback(this);
            }
            else
            {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        #endregion

        public uint Width
        {
            get
            {
                if(CppObject != IntPtr.Zero)
                    return CKLBUIMoviePlayer_getWidth(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUIMoviePlayer_setWidth(CppObject, value);
                else
                    throw new CKLBExceptionNullCppObject();
            }
        }
        public uint Height
        {
            get {
                if(CppObject != IntPtr.Zero)
                    return CKLBUIMoviePlayer_getHeight(CppObject);
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUIMoviePlayer_setHeight(CppObject, value);
                else
                    throw new CKLBExceptionNullCppObject();
            }
        }
        public void getSize(out USize size)
		{
            if(CppObject != IntPtr.Zero)
            {
                size.width = CKLBUIMoviePlayer_getWidth(CppObject);
                size.height = CKLBUIMoviePlayer_getHeight(CppObject);
            }
            else
                throw new CKLBExceptionNullCppObject();
		}
        public void setSize(USize size)
		{
            if(CppObject != IntPtr.Zero)
            {
                CKLBUIMoviePlayer_setWidth(CppObject, size.width);
                CKLBUIMoviePlayer_setHeight(CppObject, size.height);
            }
            else
                throw new CKLBExceptionNullCppObject();
		}
        public void setSize(uint width, uint height)
		{
            CKLBUIMoviePlayer_setWidth(CppObject, width);
            CKLBUIMoviePlayer_setHeight(CppObject, height);
		}
		public String Path
		{
            get
            {
                if(CppObject != IntPtr.Zero)
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUIMoviePlayer_getText(CppObject));
                else
                    throw new CKLBExceptionNullCppObject();
            }
            set
            {
                if(CppObject != IntPtr.Zero)
                    CKLBUIMoviePlayer_setText(CppObject, __MarshallingUtils.NativeUtf8FromString(value));
                else
                    throw new CKLBExceptionNullCppObject();
            }
		}

        public void play()
        {
            if(CppObject != IntPtr.Zero)
                CKLBUIMoviePlayer_moviePlay(CppObject);
            else
                throw new CKLBExceptionNullCppObject();
        }
		public void pause()
        {
            if(CppObject != IntPtr.Zero)
                CKLBUIMoviePlayer_moviePause(CppObject);
            else
                throw new CKLBExceptionNullCppObject();
        }
		public void stop()
        {
            if(CppObject != IntPtr.Zero)
                CKLBUIMoviePlayer_movieStop(CppObject);
            else
                throw new CKLBExceptionNullCppObject();
        }
		public void resume()
        {
            if(CppObject != IntPtr.Zero)
                CKLBUIMoviePlayer_movieResume(CppObject);
            else
                throw new CKLBExceptionNullCppObject();
        }
	}
}

