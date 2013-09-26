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
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace EnginePrototype
{

    /// <summary>
    /// GameObject is the most generic class of the C# framework.
    /// All wrappers inherit this class.
    /// Each GameObject can be bound to 1 and only 1 C++ object.
    /// The default behavior is to bind directly when instantiating a C# object, 
    /// but it is also possible to create an empty C# object (without C++ object bound)
    /// and to bind it later.
    /// 
    /// GameObject is IDisposable,
    /// so you can call the Dipose() method to dispose it.
    /// Override clearInternals() if needed. It is supposed to clear every single object
    /// contained in the C# class.
    /// 
    /// It can also register callbacks in the C++ Engine.
    /// Take a look at the callbacks methods documentation for more details.
    /// 
    /// It contains a handle, a typeID, a tag and a pointer to a CppObject.
    /// 
    /// The handle is a unique uint which identifies the C# object.
    /// It is given and registered in the C++ object when binding,
    /// so the C++ object could identify the C# object bound with it.
    /// 
    /// The typeID is used to verify that the C++ and the C# object are the same type,
    /// and to authorize the binding or not.
    /// </summary>
	public abstract class GameObject : IDisposable
	{
		#region DllImports
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBObjectScriptable_getScriptContext(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBObjectScriptable_setScriptContext(IntPtr p, uint handle);
        #endregion
		
		public const uint NULLHANDLER = 0xffffffff;
        public const uint NBCALLBACKS = 6;
		
		private Object m_tag;
		private uint m_typeID;
		private uint m_handle = NULLHANDLER;
		private IntPtr m_cppObject;
		private Delegate[] m_callbacksArray = new Delegate[NBCALLBACKS];
		
         /// <summary>
        /// User can associate any C# object to an object from our framework.
        /// It is just used as a user storage linked to any engine classes instance.
        /// It is never accessed, set or used by the framework.
        /// </summary>
       public Object Tag
		{
			get { return m_tag;}
			set { m_tag = value;}
		}
        /// <summary>
        /// Internal ID associated with engine classes.
        /// Can be used for debugging or find a specific type for casting (less costly than typeof())
        /// </summary>
		internal uint TypeID
		{
			get { return m_typeID; }
            //set { throw new CKLBExceptionForbiddenMethod(); }
		}
        /// <summary>
        /// Internal ID mapping, replaces adress when the C# object is seen/accessed from C++. (C# object can change of adress)
        /// </summary>
		internal uint Handle
		{
			get { return m_handle; }
			set { m_handle = value; }
		}
        /// <summary>
        /// Pointer to the C++ Object as seen from C#. Stored as IntPtr for language convenience.
        /// </summary>
		internal IntPtr CppObject
		{
			get { return m_cppObject;}
			set { m_cppObject = value;}
		}

        /// <summary>
		/// Know if the C# object is stand alone or binded to a engine C++ object.
        /// </summary>
		public bool isBoundToCpp()
		{
			return m_cppObject != IntPtr.Zero;
		}
        /// <summary>
        /// Game object constructor
        /// It registers the typeID given in argument.
        /// </summary>
        /// <param name="typeID">typeID of the C# object.</param>
		public GameObject(uint typeID)
		{
            //Console.WriteLine("[C#] GameObject cctor BEGIN.");
            m_typeID = typeID;
			WrapperReg.getInstance().registerGameObject(this);
            m_cppObject = IntPtr.Zero;
            //Console.WriteLine("[C#] GameObject cctor END.");
		}
		
		/// <summary>
		/// Associates the C++ to the C# GameObject.
		/// </summary>
		/// <param name='cppObj'>
		/// Cpp object.
		/// </param>
		internal void bind(IntPtr cppObj)
		{
			if(cppObj != IntPtr.Zero) {
				if(m_cppObject == IntPtr.Zero) {
                    uint nativeHandle = CKLBObjectScriptable_getScriptContext(cppObj);
					// Is this object already bound ? if yes it must already have a Handle.
					if(nativeHandle == NULLHANDLER) {
						NativeManagement.registerWrapper(cppObj, m_handle);
                        m_cppObject = cppObj;
                        doSetupCallbacks();
					} else {
						throw new CKLBException("This C++ object is already wrapped.");
					}
				} else {
					throw new CKLBException("This GameObject is already binded.");
				}
			} else {
				throw new CKLBException("Impossible to bind a null pointer (It can be a failure on Engine side while creating C++ instance).");
			}
		}

        /// <summary>
        /// Bind a GameObject to a C++ ObjectScriptable through its node name.
        /// </summary>
        /// <param name="nodeName">Name of the Node to bind.</param>
        public void bind(String nodeName)
        {
            if(nodeName == null)            { throw new CKLBException("Impossible to bind with a null name.");  }
            if(m_cppObject != IntPtr.Zero)  { throw new CKLBException("This GameObject is already binded.");    }

            NodeIterator nodeIterator = new NodeIterator(NativeManagement.getContextCounter(), NodeIterator.getRoot());
            if(nodeIterator.find(nodeName)) {
                IntPtr cppObj       = nodeIterator.getAsUITask().CppObject;
                uint nativeHandle   = CKLBObjectScriptable_getScriptContext(cppObj);

                if(nativeHandle == NULLHANDLER) {
                    NativeManagement.registerWrapper(cppObj, m_handle);
                    m_cppObject = cppObj;
                    doSetupCallbacks();
                } else {
					throw new CKLBException("This C++ object is already wrapped.");
				}
            } else {
                throw new CKLBException("There is not any Node with this name.");
            }
        }

        /// <summary>
        /// Breaks the link between the C++ and the C# object.
        /// </summary>
        public void unbind()
        {
            Console.WriteLine("[C#] GameObject.unbind() BEGIN");
            if(m_cppObject != IntPtr.Zero) {
                CKLBObjectScriptable_setScriptContext(m_cppObject, NULLHANDLER);
                m_cppObject = IntPtr.Zero;
            } else {
                throw new CKLBExceptionNullCppObject();
            }
            Console.WriteLine("[C#] GameObject.unbind() END");
        }

        protected virtual void doSetupCallbacks() { }

		/// <summary>
		/// Clears the internal objects which won't be automatically destroyed.
		/// </summary>
		internal virtual void clearInternals()    // Should be private, visible only from callers.
		{
			
		}
		
		/// <summary>
		/// Dispose is called by the programmer to "free" the object.
		/// C# object instance stays alive but all internal data and ressources are freed.
		/// </summary>
		public virtual void Dispose() //	Inherited classes with unmanaged resources have to dispose them first.
		{
			//Console.WriteLine("[C#] " + this + " is disposing.");
            Console.WriteLine("[C#] GameObject.Dispose BEGIN");
			clearInternals();
			if(m_handle != NULLHANDLER) {
                WrapperReg.getInstance().unregisterGameObject(this);
			} 
            if(CppObject != IntPtr.Zero) {
                unbind();
            }

            Console.WriteLine("[C#] GameObject.Dispose END");
		}
		
		/// <summary>
		/// Releases unmanaged resources and performs other cleanup operations before the
		/// <see cref="EnginePrototype.GameObject"/> is reclaimed by garbage collection.
        /// This method is called if the object has not been disposed with Dipose().
		/// </summary>
		~GameObject()
		{
			//Console.WriteLine(this + " is dying");
			Dispose();
		}

        // delegateName must have a null default value in daughter classes if only 1 delegate
        /// <summary>
        /// Set anyDelegate to the delegate designed by delegateName
        /// Uses the different functions defined in daughter classes.
        /// </summary>
        /// <param name='anyDelegate'>
        /// Object got from a delegate
        /// </param>
        /// <param name='delegateName'>
        /// String designing the delegate name (if the class has only 1 delegate, it has a default value) 
        /// </param>
        public virtual void setDelegate(Delegate anyDelegate, String delegateName)
        {
            throw new CKLBException("This class doesn't have any callback");
        }

        /// <summary>
        /// Static equivalent of setDelegate
        /// </summary>
        /// <param name='handle'>
        /// handle of the object. Used to get the C# object associated.
        /// </param>
        /// <param name='anyDelegate'>
        /// Object got from a delegate
        /// </param>
        /// <param name='delegateName'>
        /// String designing the delegate name (if the class has only 1 delegate, it has a default value) 
        /// </param>
        public static void staticSetDelegate(uint handle, Delegate delegatePtr, String delegateName)
        {
            WrapperReg.getInstance().getObjectFromHandle(handle).setDelegate(delegatePtr, delegateName);
        }

        /// <summary>
        /// This function is called to setupCallbacks.
        /// It gives the C++ Engine the pointer of the Virtual C# function which executes the delegate.
        /// </summary>
        /// <param name="delegateName">delegate name</param>
        protected void forceSetupCallBackWithVirtual(String delegateName = null)
        {
            setDelegate(null, delegateName);
        }

        /// <summary>
        /// Registers C# function pointer in C++ engine for the object designated by obj.
        /// </summary>
        /// <param name="obj">C++ object pointer</param>
        /// <param name="ptrFct">function pointer</param>
        /// <param name="index">
        /// index of the callback for multiple callbacks classes.
        /// is 0 by default.
        /// </param>
        protected void registerCallBack(Delegate callback, uint index = 0)
        {
            if(0 <= index && index < NBCALLBACKS) {
                if(callback != null) {
                    //Console.WriteLine("[C#] - handle "+ Handle +" - callback[" + index + "] registered");
                    m_callbacksArray[index] = callback;
                } else {
                    throw new CKLBException("NULL function pointer.");
                }
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (GameObject.NBCALLBACKS - 1)+ ".");
            }
        }

        internal Delegate getCallBack(uint index)
        {
            //Console.WriteLine("[C#] getCallBack(" + index + ") BEGIN");
            if(0 <= index && index < NBCALLBACKS) {
                //Console.WriteLine("[C#] getCallBack(" + index + ") END");
                Delegate d = m_callbacksArray[index];
                //Console.WriteLine((d == null) ? "NULL" : "NOT null");
                return d;
            } else {
                throw new CKLBException("Invalid index, it must be between 0 and " + (NBCALLBACKS - 1) + ".");
            }
        }
	}

}
