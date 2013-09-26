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
	public class CSSound : GameObject
    {
        #region DllImports
        // sndAsset : const char*
        // return CKLBLuaLibSOUND::SOUND*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBLuaLibSOUND_cmdSoundOpen(IntPtr sndAsset, bool fBgm);

        // pSnd CKLBLuaLibSOUND::SOUND*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBLuaLibSOUND_cmdSoundSetBufSize(IntPtr pSnd, int level);

        // pSnd CKLBLuaLibSOUND::SOUND*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibSOUND_cmdSoundClose(IntPtr pSnd);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static int CKLBLuaLibSOUND_removeSoundAll();
        
        // pSnd CKLBLuaLibSOUND::SOUND*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibSOUND_cmdSoundPlay(IntPtr pSnd, uint fade_msec, float tgtVol, float globalVol);

        // pSnd CKLBLuaLibSOUND::SOUND*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibSOUND_cmdSoundStop(IntPtr pSnd, uint fade_msec, float tgtVol);

        // pSnd CKLBLuaLibSOUND::SOUND*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibSOUND_cmdSoundVolume(IntPtr pSnd, float volume);

        // pSnd CKLBLuaLibSOUND::SOUND*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibSOUND_cmdSoundPan(IntPtr pSnd, float pan);

        // pSnd CKLBLuaLibSOUND::SOUND*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibSOUND_cmdSoundPause(IntPtr pSnd);

        // pSnd CKLBLuaLibSOUND::SOUND*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibSOUND_cmdSoundResume(IntPtr pSnd);

        // pSnd CKLBLuaLibSOUND::SOUND*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibSOUND_cmdSoundSeek(IntPtr pSnd, int millisec);

        // pSnd CKLBLuaLibSOUND::SOUND*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static int CKLBLuaLibSOUND_cmdSoundTell(IntPtr pSnd);

        // pSnd CKLBLuaLibSOUND::SOUND*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static int CKLBLuaLibSOUND_cmdSoundState(IntPtr pSnd);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibSOUND_cmdVolumeBGM(float volume);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibSOUND_cmdVolumeSE(float volume);

        // pSnd CKLBLuaLibSOUND::SOUND*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static int CKLBLuaLibSOUND_cmdGetLength(IntPtr pSnd);

        // pSnd CKLBLuaLibSOUND::SOUND*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibSOUND_cmdSetFade(IntPtr pSnd, int millisec, float tgtVol);
        #endregion

        #region Constructors

		static uint s_classID = __FrameworkUtils.RegisterClass("LibSound"/*, typeof(CSSound)*/);

		public CSSound(String sound_asset, bool bgmMode = false) 
			: base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBLuaLibSOUND_cmdSoundOpen(__MarshallingUtils.NativeUtf8FromString(sound_asset), bgmMode);
            NativeManagement.intercepCppError();
            bind(ptr);
        }

        #endregion

        public enum EBUF_SIZE
        {
            SND_BUF_SMALL  = 0,
            SND_BUF_MEDIUM = 1,
            SND_BUF_LARGE  = 2,
        }

        private EBUF_SIZE   m_bufSize;
        private float       m_volume;
        private float       m_pan;

        public EBUF_SIZE    BufSize
        {
            get { return m_bufSize; }
            //set { throw new CKLBExceptionForbiddenMethod(); }
        }
        public bool         setBufSize(EBUF_SIZE size)
        {
            if(CppObject != IntPtr.Zero) {
                m_bufSize = size;
                return CKLBLuaLibSOUND_cmdSoundSetBufSize(CppObject, (int)size);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
        public float        Volume 
        { 
            get { return m_volume; }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    m_volume = value;
                    CKLBLuaLibSOUND_cmdSoundVolume(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
		public float        Pan 
        { 
            get { return m_pan; }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    m_pan = value;
                    CKLBLuaLibSOUND_cmdSoundPan(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        public int          Length
        {
            get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBLuaLibSOUND_cmdGetLength(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
        }

        internal override void clearInternals()
		{
			if(CppObject != IntPtr.Zero) {
				CKLBLuaLibSOUND_cmdSoundClose(CppObject);
            }
		}

        public static void closeAll()
        {
            CKLBLuaLibSOUND_removeSoundAll();
        }

		public void play(uint fade_msec = 0, float tgtVol = 1.0f, float globalVol = 1.0f) 
        {
            if(CppObject != IntPtr.Zero) {
                CKLBLuaLibSOUND_cmdSoundPlay(CppObject, fade_msec, tgtVol, globalVol);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

		public void stop(uint fade_msec = 0, float tgtVol = 0.0f) 
        {
            if(CppObject != IntPtr.Zero) {
                CKLBLuaLibSOUND_cmdSoundStop(CppObject, fade_msec, tgtVol);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void pause() 
        {
            if(CppObject != IntPtr.Zero) {
                CKLBLuaLibSOUND_cmdSoundPause(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void resume() 
        {
            if(CppObject != IntPtr.Zero) {
                CKLBLuaLibSOUND_cmdSoundResume(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void seek(int milliseconds) 
        {
            if(CppObject != IntPtr.Zero) {
                CKLBLuaLibSOUND_cmdSoundSeek(CppObject, milliseconds);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public int  tell()
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBLuaLibSOUND_cmdSoundTell(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public int  state()
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBLuaLibSOUND_cmdSoundState(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void setFade(int millisec, float tgtVol)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBLuaLibSOUND_cmdSetFade(CppObject, millisec, tgtVol);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

		public static void volumeBGM(float volume) 
        {
            CKLBLuaLibSOUND_cmdVolumeBGM(volume);
        }

		public static void volumeSE(float volume) 
        {
            CKLBLuaLibSOUND_cmdVolumeSE(volume);
        }
	}
}

