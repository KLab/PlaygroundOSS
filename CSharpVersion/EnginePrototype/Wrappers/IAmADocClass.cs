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
/*
using System;
using System.Runtime.InteropServices;

namespace EnginePrototype
{

    class IAmADocClass : GameObject
    {
        /// The DllImports region contains all the private DllImports of the class.
        /// You must use the following library : System.Runtime.InteropServices
        #region DllImports

        /// <summary>
        /// Static constructor of C++ object
        /// </summary>
        /// <param name="pParent">Parent pointer</param>
        /// <returns>IntPtr to the C++ class which has been instanciated</returns>
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CppClassName_create(IntPtr pParent);

        /// <summary>
        /// Normal DllImport
        /// </summary>
        /// <param name="pObject">Pointer to Cpp Object bound by this class</param>
        /// <param name="intArg">int/uint/float/double/bool type is passed directly as this one</param>
        /// <returns>int/uint/float/double directly</returns>
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CppClassName_getSetArg(IntPtr pObject, int intArg);

        /// <summary>
        /// Get a bool
        /// </summary>
        /// <param name="p">Pointer to Cpp Object bound by this class</param>
        /// <returns>boolean which miust be Marshalled</returns>
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CppClassName_getBool(IntPtr p);

        /// <summary>
        /// Set String from C# to a C++ char* or const char*
        /// </summary>
        /// <param name="p">Pointer to Cpp Object bound by this class</param>
        /// <param name="myString">
        /// My String passed as an IntPtr.
        /// To convert a String to an UTF8 IntPtr,
        /// you must use the following function : __MarshallingUtils.NativeUtf8FromString(String)
        /// </param>
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CppClassName_setString(IntPtr p, IntPtr myString);

        /// <summary>
        /// Get a C# String from a C++ char* or const char*
        /// </summary>
        /// <param name="p"></param>
        /// <returns>
        /// IntPtr to the C++ char*.
        /// To convert this IntPtr to a String,
        /// you must use the following function : __MarshallingUtils.StringFromNativeUtf8(IntPtr)
        /// </returns>
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CppClassName_getString(IntPtr p);

        #endregion

        // The Constructors region contains the classID, the basic constructor and a constructor for later binding.
        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("Class name", typeof(IAmADocClass));

        /// <summary>
        /// IAmADocClass constructor.
        /// Create C# object.
        /// Create C++ object.
        /// Check if there is an error in C++ Engine
        /// Bind both objects.
        /// Register callbacks if there is/are some to register in constructor
        /// </summary>
        /// <param name="parent"></param>
        /// <param name="arg"></param>
        /// <param name="onDrawCallBack"></param>
        public IAmADocClass(CKLBUITask parent, int arg, CallBack1 callback1)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CppClassName_create(parent != null ? parent.CppObject : IntPtr.Zero);
            NativeManagement.intercepCppError();
            bind(ptr);
            m_callback1 = callback1;
        }

        /// <summary>
        /// Empty constructor for later binding.
        /// </summary>
        public IAmADocClass() : base(s_classID) { }
        #endregion

        // The Callback region contains Callbacks delegates definitions
        // and the virtual methods overide which will be called back from C++
        #region CallBacks

        /// <summary>
        /// Declaration of the CallBack signature
        /// </summary>
        /// <param name="caller">Emulate a this</param>
        public delegate void CallBack1(IAmADocClass caller);
        public delegate void CallBack2(IAmADocClass caller);

        private CallBack1 m_callback1;  // callback number 0
        private CallBack2 m_callback2;  // callback number 1

        /// <summary>
        /// This method is used in the bind function.
        /// It sends the virtual callBackFunction pointer to the C++ Engine so that it can callback C#.
        /// The callback index is between 0 and 4.
        /// </summary>
        protected override void doSetupCallbacks()
        {
            // If there is only 1 callback, you can call registerCallBack(IntPtr CppObj, IntPtr functionPtr) whithout uint.
            registerCallBack((NativeManagement.FunctionPointerV)callBackFunction1, 0);
            registerCallBack((NativeManagement.FunctionPointerV)callBackFunction2, 1);
        }

        /// <summary>
        /// Set anyDelegate to the delegate designed by delegateName
        /// If there is only 1 delegate in the class, set a default value to null and don't do any switch
        /// </summary>
        /// <param name="anyDelegate"></param>
        /// <param name="delegateName"></param>
        public override void setDelegate(Delegate anyDelegate, String delegateName)
        {
            switch(delegateName)
            {
                case "callback1":
                    m_callback1 = (CallBack1)anyDelegate;
                    break;
                case "callback2":
                    m_callback2 = (CallBack2)anyDelegate;
                    break;
            }
        }

        /// <summary>
        /// These methods will be called back from C++
        /// Don't forget to test the nullity of the C# delegate before calling it.
        /// </summary>
        public virtual void callBackFunction1()
        {
            if(m_callback1 != null) {
                m_callback1(this);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        public virtual void callBackFunction2()
        {
            if(m_callback2 != null) {
                m_callback2(this);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }
       
        #endregion
    }
}
*/
