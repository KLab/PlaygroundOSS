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

	public class AnimationInfo {

        private enum EIDX : uint {
            X_COORD			= 0,
	        Y_COORD			= 1,
	        SCALE_COORD		= 2,
	        R_COLOR			= 3,
	        G_COLOR			= 4,
	        B_COLOR			= 5,
	        A_COLOR			= 6,
	        SCALEX_COORD	= 7,
	        SCALEY_COORD	= 8,
	        ROTATION_COORD	= 9,

            COUNT = 9	// ROTATION_COORD
        }

        private         uint        m_mask      = 0;
        private static  uint[]      ms_maskArr  = new uint[] { 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7, 1<<8, 1<<9, 1<<10  };
        private static  int[]       ms_indexes  = new int[]  { 0,    2,    4,    8,    10,   12,   14,   16,   18,   20     };
        private         float[]     m_internalArray = new float[22];

		public void createAlphaAnimation    (float start, float end) 
        {
            m_mask |= ms_maskArr[(uint)EIDX.A_COLOR];
            m_internalArray[ms_indexes[(int)EIDX.A_COLOR]    ] = start;
            m_internalArray[ms_indexes[(int)EIDX.A_COLOR] + 1] = end;
        }
        public void createRGBAnimation      (float RStart, float REnd, float GStart, float GEnd, float BStart, float BEnd) 
        {
            m_mask |= ms_maskArr[(uint)EIDX.R_COLOR];
            m_internalArray[ms_indexes[(int)EIDX.R_COLOR]    ] = RStart;
            m_internalArray[ms_indexes[(int)EIDX.R_COLOR] + 1] = REnd;
            m_mask |= ms_maskArr[(uint)EIDX.G_COLOR];
            m_internalArray[ms_indexes[(int)EIDX.G_COLOR]    ] = GStart;
            m_internalArray[ms_indexes[(int)EIDX.G_COLOR] + 1] = GEnd;
            m_mask |= ms_maskArr[(uint)EIDX.B_COLOR];
            m_internalArray[ms_indexes[(int)EIDX.R_COLOR]    ] = BStart;
            m_internalArray[ms_indexes[(int)EIDX.R_COLOR] + 1] = BEnd;
        }
        public void createScaleAnimation    (float start, float end) 
        {
            m_mask |= ms_maskArr[(uint)EIDX.SCALE_COORD];
            m_internalArray[ms_indexes[(int)EIDX.SCALE_COORD]    ] = start;
            m_internalArray[ms_indexes[(int)EIDX.SCALE_COORD] + 1] = end;
            m_internalArray[ms_indexes[(int)EIDX.SCALE_COORD] + 2] = start;
            m_internalArray[ms_indexes[(int)EIDX.SCALE_COORD] + 3] = end;
        }
        public void createXOffsetAnimation  (float start, float end) 
        {
            m_mask |= ms_maskArr[(uint)EIDX.X_COORD];
            m_internalArray[ms_indexes[(int)EIDX.X_COORD]    ] = start;
            m_internalArray[ms_indexes[(int)EIDX.X_COORD] + 1] = end;
        }
        public void createYOffsetAnimation  (float start, float end) 
        { 
            m_mask |= ms_maskArr[(uint)EIDX.Y_COORD];
            m_internalArray[ms_indexes[(int)EIDX.Y_COORD]    ] = start;
            m_internalArray[ms_indexes[(int)EIDX.Y_COORD] + 1] = end;
        }
        //public void createRotationAnimation(float rotationStart, float rotationEnd); // Not supported yet.
		
        internal void getAnimInfo(ref uint type, ref uint affected, ref float[] arrayParam)
        {
            affected    = m_mask;
            type        = 1;
            arrayParam  = new float[22];

            int idx = 0;
            for(int i = 0; i <= (int)EIDX.COUNT; ++i) {
                uint currentAnim = ms_maskArr[i];
                if(((uint)m_mask & currentAnim) == currentAnim) {
                    int currentIdx = ms_indexes[i];
					arrayParam[idx++] = m_internalArray[currentIdx];
					arrayParam[idx++] = m_internalArray[currentIdx + 1];
                    if(currentAnim == (uint)EIDX.SCALE_COORD) {
						arrayParam[idx++] = m_internalArray[currentIdx + 2];
						arrayParam[idx++] = m_internalArray[currentIdx + 3];
                    }
                }
            }
        }
	}
	
	public class CKLBUIScore : CKLBUITask
	{
		#region DllImports
        // pParent : CKLBUITask*
        // texTable : const char**
        // return : CKLBUIScore*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIScore_create(IntPtr pParent, 
                                                        uint order, int orderOffset,
                                                        float x, float y, IntPtr[] texTable, 
                                                        float stepX, float stepY, int column,
                                                        bool fillZero, bool animFlags,
                                                        uint align, bool countClip);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIScore_getValue(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScore_setValue(IntPtr p, uint value);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBUIScore_getOrder(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScore_setOrder(IntPtr p, uint value);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBUIScore_getOrderOffset(IntPtr p);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIScore_getStepX(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScore_setStepX(IntPtr p, int value);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIScore_getStepY(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScore_setStepY(IntPtr p, int value);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIScore_getColumn(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScore_setColumn(IntPtr p, uint value);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIScore_getFillZero(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScore_setFillZero(IntPtr p, bool value);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIScore_getAnim(IntPtr p);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIScore_getAlign(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScore_setAlign(IntPtr p, int align);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBUIScore_getTextures(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIScore_getCountClip(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScore_setCountClip(IntPtr p, bool value);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScore_setEnterAnimation(IntPtr p, uint milliSecondsPlayTime, int timeShift, uint type, uint affected, float[] arrayParam);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIScore_setExitAnimation(IntPtr p, uint milliSecondsPlayTime, int timeShift, uint type, uint affected, float[] arrayParam);
		
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_Score"/*, typeof(CKLBUIScore)*/);

        public CKLBUIScore( CKLBUITask parent, uint order, int orderOffset, float x, float y, String[] textureTable, 
                            float stepX, float stepY, int column, bool fillZeroFlag, bool animationFlag, EALIGN align = EALIGN.ALIGN_RIGHT, bool countClip = false)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIScore_create(parent != null ? parent.CppObject : IntPtr.Zero, order, orderOffset,
                                            x, y, __MarshallingUtils.NativeUtf8ArrayFromStringArray(textureTable, textureTable.Length),
                                            stepX, stepY, column, fillZeroFlag, animationFlag, (uint)align, countClip);
            NativeManagement.intercepCppError();
            bind(ptr);
        }

        public CKLBUIScore() : base(s_classID) { }

        #endregion

        public enum EALIGN {
		    ALIGN_RIGHT  = 0,
		    ALIGN_CENTER = 1,
		    ALIGN_LEFT   = 2,
	    };

        public uint     Order
		{
			get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScore_getOrder(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
			set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIScore_setOrder(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public uint     Odoff
		{
			get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScore_getOrderOffset(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public int      StepX
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScore_getStepX(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIScore_setStepX(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
			}
		}
        public int      StepY
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScore_getStepY(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIScore_setStepY(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public uint     Cols
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScore_getColumn(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIScore_setColumn(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public bool     FillZero
		{
			get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScore_getFillZero(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIScore_setFillZero(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
			}
		}
		public bool     IsAnim
		{
			get 
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScore_getAnim(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public uint     Value
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIScore_getValue(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIScore_setValue(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public EALIGN   Align
		{
			get
			{
				if(CppObject != IntPtr.Zero) {
					return (EALIGN)CKLBUIScore_getAlign(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
			}
			set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIScore_setAlign(CppObject, (int)value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
			}
		}
        public bool     CountClip
		{
			get
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUIScore_getCountClip(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
			}
			set
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIScore_setCountClip(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
			}
		}
        
		public String[] Textures
		{
			get 
            {
                if(CppObject != IntPtr.Zero) {
                    return __MarshallingUtils.StringArrayFromNativeUtf8IntPtr(CKLBUIScore_getTextures(CppObject), 10);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
		}

        public void reset() 
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUIScore_setValue(CppObject, 0);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

        public void enterAnim(AnimationInfo animation, uint msPlayTime, int timeShift)
        {
			if(CppObject != IntPtr.Zero) {

                uint type           = 0;
                uint affected       = 0;
                float[] param_array = null;
                
                if(animation != null) {
                    animation.getAnimInfo(ref type, ref affected, ref param_array);
                }

                CKLBUIScore_setEnterAnimation(CppObject, msPlayTime, timeShift, type, affected, param_array);
			} else {
				throw new CKLBExceptionNullCppObject();
			}
		}
		
        public void exitAnim(AnimationInfo animation, uint msPlayTime, int timeShift)
        {
			if(CppObject != IntPtr.Zero) {

                uint type           = 0;
                uint affected       = 0;
                float[] param_array = null;

                if(animation != null) {
                    animation.getAnimInfo(ref type, ref affected, ref param_array);
                }

                CKLBUIScore_setExitAnimation(CppObject, msPlayTime, timeShift, type, affected, param_array);
            } else {
				throw new CKLBExceptionNullCppObject();
            }
		}
	}
}
