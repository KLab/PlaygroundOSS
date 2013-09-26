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
	public class CKLBUIGroup : CKLBUITask
	{
		#region DllImports
        // parent : CKLBUITask*
        // return : CKLBUIGroup*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBUIGroup_create(IntPtr parent, float x, float y);

		// callback : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIGroup_setAnimCallback(IntPtr p, IntPtr callback);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIGroup_setAnimation(IntPtr p, IntPtr anim_name, bool blend);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIGroup_isAnim(IntPtr p, IntPtr anim_name);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIGroup_skipAnim(IntPtr p, IntPtr anim_name);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_Group"/*, typeof(CKLBUIGroup)*/);

        public CKLBUIGroup(CKLBUITask parent, float x, float y)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIGroup_create(parent != null ? parent.CppObject : IntPtr.Zero, x, y);
            NativeManagement.intercepCppError();
            bind(ptr);
        }

        public CKLBUIGroup() : base(s_classID) { }

        #endregion

        #region CallBacks

        public delegate void AnimCallBack(CKLBUIGroup caller, String name, uint id);

        private AnimCallBack m_animCallback;

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerSU(animCallBackFunction));
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName)
        {
            if(delegateName == "anim")
            {
                m_animCallback = (AnimCallBack)anyDelegate;
            }
            else
            {
                throw new CKLBException("Unvalid delegate name");
            }
        }

        // name : const char* from Cpp
        public virtual void animCallBackFunction(IntPtr name, uint id)
        {
            if(m_animCallback != null)
            {
                m_animCallback(this, __MarshallingUtils.StringFromNativeUtf8(name), id);
            }
            else
            {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        #endregion

        public bool setAnimation(String animationName, bool blendFlag = false) 
		{
			if(CppObject != IntPtr.Zero)
				return CKLBUIGroup_setAnimation(CppObject, __MarshallingUtils.NativeUtf8FromString(animationName), blendFlag);
			else
				throw new CKLBExceptionNullCppObject();
		}
        
        public bool isRunningAnimation(String animationName = null)
		{
			if(CppObject != IntPtr.Zero)
				return CKLBUIGroup_isAnim(CppObject, __MarshallingUtils.NativeUtf8FromString(animationName));
			else
				throw new CKLBExceptionNullCppObject();
		}
		
        public bool skipAnim(String animationName = null) 
		{
			if(CppObject != IntPtr.Zero)
				return CKLBUIGroup_skipAnim(CppObject, __MarshallingUtils.NativeUtf8FromString(animationName));
			else
				throw new CKLBExceptionNullCppObject();
		}
	}
}

