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
	public class CKLBUIForm : CKLBUITask
	{
        #region DllImports
        //return : CKLBUIForm*
        // pParent : CKLBUITask*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBUIForm_create(IntPtr pParent, uint order, float x, float y, bool bAssetFile, IntPtr asset, bool bExclusive, bool modal, bool urgent);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBUIForm_getAsset(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBUIForm_getOrder(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIForm_getExclusive(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIForm_setExclusive(IntPtr p, bool exclusive);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIForm_getIsFile(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIForm_setEnable(IntPtr p, bool isEnabled);

        // name : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIForm_existNode(IntPtr p, IntPtr name);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIForm_inputEnable(IntPtr p, bool bEnable);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIForm_animation(IntPtr p, IntPtr animname, bool blend);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIForm_animEnter(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIForm_animLeave(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIForm_isAnim(IntPtr p, IntPtr name);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIForm_skipAnim(IntPtr p, IntPtr name);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIForm_setGroup(IntPtr p, IntPtr groupName);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIForm_setGlobalVolume(IntPtr p, float volume);
        #endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_Form"/*, typeof(CKLBUIForm)*/);

        public CKLBUIForm(CKLBUITask parent, uint order, int x, int y, bool assetFile, String asset_name, bool bExclusive = false, bool modal = false, bool urgent = false)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBUIForm_create(parent != null ? parent.CppObject : IntPtr.Zero, order, x, y, assetFile, __MarshallingUtils.NativeUtf8FromString(asset_name), bExclusive, modal, urgent);
            NativeManagement.intercepCppError();
            bind(ptr);
        }

        public CKLBUIForm() : base(s_classID) { }

        #endregion

        #region CallBacks

        public delegate void SelectableCallBack(CKLBUIForm caller, String name, int type, int param);
        public delegate void AnimCallBack(CKLBUIForm caller, String name, uint id);

        private SelectableCallBack m_selectableCallback;    // callback number 0
        private AnimCallBack m_animCallback;                // callback number 4

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerSII(selectableCallbackFunction), 0);
            registerCallBack(new NativeManagement.FunctionPointerSU (animCallBackFunction)      , 4);
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName)
        {
            if(delegateName == "selectable") {
                m_selectableCallback = (SelectableCallBack)anyDelegate;
            } else if(delegateName == "anim") {
                m_animCallback = (AnimCallBack)anyDelegate;
            } else {
                throw new CKLBException("Unvalid delegate name");
            }
        }

        // name : const char* from Cpp
        public virtual void animCallBackFunction(IntPtr name, uint id)
        {
            if(m_animCallback != null) {
                m_animCallback(this, __MarshallingUtils.StringFromNativeUtf8(name), id);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        // name : const char* from Cpp
        public virtual void selectableCallbackFunction(IntPtr name, int type, int param)
        {
            if(m_selectableCallback != null) {
                m_selectableCallback(this, __MarshallingUtils.StringFromNativeUtf8(name), type, param);
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
                    return CKLBUIForm_getOrder(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public String Asset
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return __MarshallingUtils.StringFromNativeUtf8(CKLBUIForm_getAsset(CppObject));
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public bool IsFile
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIForm_getIsFile(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public bool Exclusive
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIForm_getExclusive(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIForm_setExclusive(CppObject,value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}

        public void setEnabled(bool isEnabled) 
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIForm_setEnable(CppObject, isEnabled);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public bool existNode(String name)
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBUIForm_existNode(CppObject, __MarshallingUtils.NativeUtf8FromString(name));
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void inputEnable(bool bEnable) 
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIForm_inputEnable(CppObject, bEnable);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public bool animation(String animationName, bool blend = false) 
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBUIForm_animation(CppObject, __MarshallingUtils.NativeUtf8FromString(animationName), blend);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public bool isRunningAnimation(String animationName = null) 
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBUIForm_isAnim(CppObject, __MarshallingUtils.NativeUtf8FromString(animationName));
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public bool skipAnim(String animationName = null)
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBUIForm_skipAnim(CppObject, __MarshallingUtils.NativeUtf8FromString(animationName));
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public bool animEnter() 
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBUIForm_animEnter(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public bool animLeave() 
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBUIForm_animLeave(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public bool setGroup(String groupName)
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBUIForm_setGroup(CppObject, __MarshallingUtils.NativeUtf8FromString(groupName));
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void setGlobalVolume(float volume)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIForm_setGlobalVolume(CppObject, volume);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
	}
}
