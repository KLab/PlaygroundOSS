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
    /// <summary>
    /// NativeManagement is a static class used to interact with C++.
    /// It is able to register and unregister C# wrappers for each C++ object.
    /// It also has a static method to destroy a C# wrapper directly
    /// from the C++ Engine.
    /// 
    /// The pointer of this static function must be sent to the C++ Engine 
    /// at the beginning of the program.
    /// </summary>
	public static class NativeManagement
	{
		#region DllImports

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBObject_getTypeID(IntPtr p);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBObjectScriptable_getScriptContext(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBObjectScriptable_setScriptContext(IntPtr p, uint handle);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBScriptEnv_getCallBackCount();

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBScriptEnv_getErrorPtr();

        // return : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CKLBScriptEnv_getErrorString();

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBScriptEnv_resetError();
		#endregion

        public delegate void FunctionPointerV       ();

        public delegate void FunctionPointerII      (int int_1, int int_2);
        public delegate void FunctionPointerIII     (int int_1, int int_2, int int_3);
        public delegate void FunctionPointerIIII    (int int_1, int int_2, int int_3, int int_4);

        public delegate void FunctionPointerS       (IntPtr intptr_1);
        public delegate void FunctionPointerSII     (IntPtr intptr_1, int int_1, int int_2);
        public delegate void FunctionPointerSU      (IntPtr intptr_1, uint uint_1);
        public delegate void FunctionPointerSS      (IntPtr intptr_1, IntPtr intptr_2);
        public delegate void FunctionPointerUS      (uint uint_1, IntPtr intptr_1);
        public delegate void FunctionPointerUSS     (uint uint_1, IntPtr intptr_1, IntPtr intptr_2);
        
        public delegate void FunctionPointerU       (uint uint_1);
        public delegate void FunctionPointerUU      (uint uint_1, uint uint_2);
        public delegate void FunctionPointerUFF     (uint uint_1, float float_1, float float_2);
        public delegate void FunctionPointerUI      (uint uint_1, int int_1);
        public delegate void FunctionPointerUII     (uint uint_1, int int_1, int int_2);
        public delegate void FunctionPointerUIIII   (uint uint_1, int int_1, int int_2, int int_3, int int_4);
        public delegate void FunctionPointerUIIUU   (uint uint_1, int int_1, int int_2, uint uint_2, uint uint_3);

        public delegate void FunctionPointerUUII    (uint uint_1, uint uint_2, int int_1, int int_2);
        public delegate void FunctionPointerUUUII   (uint uint_1, uint uint_2, uint uint_3, int int_1, int int_2);

		public delegate bool FunctionPointerIIIP_retB(int int_1, int int_2, int int_3, IntPtr obj_1);

        public delegate void FunctionPointerFS      (float float_1, IntPtr intptr_1);

        #region CppErrorHandling

        /// <summary>
        /// Pointer  to the global variable in Cpp.
        /// This variable is set to 1 when an error has occured.
        /// It is set to 0 when reset.
        /// </summary>
        private static IntPtr ms_cppErrorFlag = CKLBScriptEnv_getErrorPtr();
        public static uint CppErrorFlag
        {
            get { return (uint)Marshal.ReadInt32(ms_cppErrorFlag); }
            //set { throw new CKLBExceptionForbiddenMethod(); }
        }

        public static String CppErrorString
        {
            get
            {
                return __MarshallingUtils.StringFromNativeUtf8(CKLBScriptEnv_getErrorString());
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
        }

        public static void resetCppError()
        {
            CKLBScriptEnv_resetError();
        }

        /// <summary>
        /// Raises an exception if there is an error in C++.
        /// resetCppError() must be used before in order not to catch a previous error.
        /// </summary>
        public static void intercepCppError()
        {
            if(CppErrorFlag != 0) {
                throw new CKLBException("Error from C++ Engine : " + CppErrorString);
            }
        }

        #endregion

        // Get Timer adress on startup.
        private static IntPtr ms_counter = CKLBScriptEnv_getCallBackCount();
        internal static uint getContextCounter()
        {
            return (uint)Marshal.ReadInt32(ms_counter);
        }

		/// <summary>
		/// Gets the typeID of a C++ GameObject.
		/// </summary>
		/// <returns>
		/// The typeID.
		/// </returns>
		/// <param name='cppObj'>
		/// C++ object IntPtr.
		/// </param>
		public static uint getTypeID(IntPtr cppObj)
		{ 
            return CKLBObject_getTypeID(cppObj);
		}

		/// <summary>
		/// Links a C++ object to its C# wrapper.
		/// </summary>
		/// <param name='cppObj'>
		/// Pointer to the CppObject to register.
		/// </param>
		/// <param name='handle'>
		/// Handle of the C# object.
		/// </param>
		public static void  registerWrapper(IntPtr cppObj, uint handle)
		{
            Console.WriteLine("[C#] NativeManagement.registerWrapper BEGIN");
			GameObject gameObject = WrapperReg.getInstance().getObjectFromHandle(handle);

			if(cppObj != IntPtr.Zero) {
				// C# and C++ classes must have the same typeID to be bound
                //Console.WriteLine("[C#] NativeManagement.registerWrapper - native typeID : 0x" + NativeManagement.getTypeID(cppObj).ToString("X") + " - C# typeID : 0x" + gameObject.TypeID.ToString("X"));
				if(NativeManagement.getTypeID(cppObj) == gameObject.TypeID) {
					//Console.WriteLine("[C#] Register Wrapper : handle = " + handle);
                    CKLBObjectScriptable_setScriptContext(cppObj, handle);
				} else {
					throw new CKLBException("C# object and C++ object don't have the same typeID, impossible to bind them.");
				}

				// Debug
				//uint handleResult = GameObject_getHandle(cppObj);
				//Console.WriteLine("Result : " + handleResult);
			} else {
				throw new CKLBExceptionNullCppObject();
			}
            Console.WriteLine("[C#] NativeManagement.registerWrapper END");
		}

		/// <summary>
		/// Breaks the link between the C++ object and its wrapper.
		/// </summary>
		/// <param name='cppObj'>
		/// Pointer to the CppObject to unregister.
		/// </param>
		public static void unregisterWrapper(IntPtr cppObj)
		{
			if(cppObj != IntPtr.Zero) {
				Console.WriteLine("Unregister Wrapper");
                CKLBObjectScriptable_setScriptContext(cppObj, GameObject.NULLHANDLER);
			} else {
				throw new CKLBExceptionNullCppObject();
			}
		}

		/// <summary>
		/// Destroys the C# object designated by handle.
        /// It can be called from C++.
		/// </summary>
		/// <param name='handle'>
		/// Handle of the C# object to destroy.
		/// </param>
		public static void destroyFromNative(uint handle)
		{
			GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);
            if(obj != null) {
                WrapperReg.getInstance().unregisterGameObject(obj);
                obj.CppObject = IntPtr.Zero;
                obj.Dispose();
            }
		}

        public static void doCallBackV(uint cbInfos)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerV cb = (FunctionPointerV)obj.getCallBack(callbackIndex);
                cb();
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }

        public static void doCallBackII(uint cbInfos, int int_1, int int_2)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerII cb = (FunctionPointerII)obj.getCallBack(callbackIndex);
                cb(int_1, int_2);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        public static void doCallBackIII(uint cbInfos, int int_1, int int_2, int int_3)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerIII cb = (FunctionPointerIII)obj.getCallBack(callbackIndex);
                cb(int_1, int_2, int_3);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        public static void doCallBackIIII(uint cbInfos, int int_1, int int_2, int int_3, int int_4)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerIIII cb = (FunctionPointerIIII)obj.getCallBack(callbackIndex);
                cb(int_1, int_2, int_3, int_4);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }

        public static void doCallBackS(uint cbInfos, IntPtr intptr_1)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerS cb = (FunctionPointerS)obj.getCallBack(callbackIndex);
                cb(intptr_1);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        public static void doCallBackSII(uint cbInfos, IntPtr intptr_1, int int_1, int int_2)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerSII cb = (FunctionPointerSII)obj.getCallBack(callbackIndex);
                cb(intptr_1, int_1, int_2);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        public static void doCallBackSU(uint cbInfos, IntPtr intptr_1, uint uint_1)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerSU cb = (FunctionPointerSU)obj.getCallBack(callbackIndex);
                cb(intptr_1, uint_1);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        public static void doCallBackSS(uint cbInfos, IntPtr intptr_1, IntPtr intptr_2)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerSS cb = (FunctionPointerSS)obj.getCallBack(callbackIndex);
                cb(intptr_1, intptr_2);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }

        public static void doCallBackUS(uint cbInfos, uint uint_1, IntPtr intptr_1)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerUS cb = (FunctionPointerUS)obj.getCallBack(callbackIndex);
                cb(uint_1, intptr_1);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        public static void doCallBackUSS(uint cbInfos, uint uint_1, IntPtr intptr_1, IntPtr intptr_2)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerUSS cb = (FunctionPointerUSS)obj.getCallBack(callbackIndex);
                cb(uint_1, intptr_1, intptr_2);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        
        public static void doCallBackU(uint cbInfos, uint uint_1)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerU cb = (FunctionPointerU)obj.getCallBack(callbackIndex);
                cb(uint_1);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        public static void doCallBackUU(uint cbInfos, uint uint_1, uint uint_2)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerUU cb = (FunctionPointerUU)obj.getCallBack(callbackIndex);
                cb(uint_1, uint_2);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        public static void doCallBackUFF(uint cbInfos, uint uint_1, float float_1, float float_2)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);
            
            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerUFF cb = (FunctionPointerUFF)obj.getCallBack(callbackIndex);
                cb(uint_1, float_1, float_2);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        public static void doCallBackUI(uint cbInfos, uint uint_1, int int_1)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerUI cb = (FunctionPointerUI)obj.getCallBack(callbackIndex);
                cb(uint_1, int_1);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        public static void doCallBackUII(uint cbInfos, uint uint_1, int int_1, int int_2)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerUII cb = (FunctionPointerUII)obj.getCallBack(callbackIndex);
                cb(uint_1, int_1, int_2);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        public static void doCallBackUIIII(uint cbInfos, uint uint_1, int int_1, int int_2, int int_3, int int_4)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerUIIII cb = (FunctionPointerUIIII)obj.getCallBack(callbackIndex);
                cb(uint_1, int_1, int_2, int_3, int_4);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        public static void doCallBackUIIUU(uint cbInfos, uint uint_1, int int_1, int int_2, uint uint_2, uint uint_3)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerUIIUU cb = (FunctionPointerUIIUU)obj.getCallBack(callbackIndex);
                cb(uint_1, int_1, int_2, uint_2, uint_3);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        public static void doCallBackUUII(uint cbInfos, uint uint_1, uint uint_2, int int_1, int int_2)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerUUII cb = (FunctionPointerUUII)obj.getCallBack(callbackIndex);
                cb(uint_1, uint_2, int_1, int_2);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
        public static void doCallBackUUUII(uint cbInfos, uint uint_1, uint uint_2, uint uint_3, int int_1, int int_2)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerUUUII cb = (FunctionPointerUUUII)obj.getCallBack(callbackIndex);
                cb(uint_1, uint_2, uint_3, int_1, int_2);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
		
        public static bool doCallBackIIIP_retB(uint cbInfos, int int_1, int int_2, int int_3, IntPtr obj_1)
		{
			uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
			uint handle = cbInfos & 0x1FFFFFFF;
			GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);
			
			if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
				FunctionPointerIIIP_retB cb = (FunctionPointerIIIP_retB)obj.getCallBack(callbackIndex);
				return cb(int_1, int_2, int_3, obj_1);
			} else {
				throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
			}
		}
        
        public static void doCallBackFS(uint cbInfos, float float_1, IntPtr intptr_1)
        {
            uint callbackIndex = (cbInfos & 0xE0000000) >> 29;
            uint handle = cbInfos & 0x1FFFFFFF;
            GameObject obj = WrapperReg.getInstance().getObjectFromHandle(handle);

            if(0 <= callbackIndex && callbackIndex < GameObject.NBCALLBACKS) {
                FunctionPointerFS cb = (FunctionPointerFS)obj.getCallBack(callbackIndex);
                cb(float_1, intptr_1);
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }
	}
}
