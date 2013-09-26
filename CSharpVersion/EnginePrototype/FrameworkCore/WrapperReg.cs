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
	/// C# Wrapper management class.
    /// 
    /// Singleton class.
    /// 
    /// It contains a GameObject array with a pointer on every single wrapper
    /// and its handle. So it is possible to find the GameObject from its handle.
    /// 
    /// It can register and unregister GameObject in the array.
	/// </summary>
	public class WrapperReg
	{
		private int m_listSize;
		private GameObject[] m_list;
        // This list is used for space optimization.
		private List<uint> m_freeHandlesList;
		private uint m_objectCounter;
		
		private WrapperReg()
		{
            Console.WriteLine("[C#] WrapperReg cctor BEGIN");
            m_listSize = 10;
			m_list = new GameObject[m_listSize]; // null by default
			m_freeHandlesList = new List<uint>();
            m_objectCounter = 0;
            Console.WriteLine("[C#] WrapperReg cctor END");
		}
		
		private static WrapperReg reg = new WrapperReg();
		
		public static WrapperReg getInstance()
		{
			return reg;
		}
		
		/// <summary>
		/// Generates a handle and registers the game object in the array
		/// </summary>
		/// <returns>
		/// The handle of the GameObject.
		/// </returns>
		/// <param name='pObj'>
		/// GameObject to register.
		/// </param>
		public uint registerGameObject(GameObject pObj)
		{
            Console.WriteLine("[C#] WrapperReg.registerGameObject BEGIN");
			if(pObj.Handle == GameObject.NULLHANDLER) {
                Console.WriteLine("[C#] WrapperReg - Handle OK");
                // no free handles in the array
				if(m_freeHandlesList.Count == 0) {
					m_list[m_objectCounter] = pObj;
					pObj.Handle = m_objectCounter;
					if(++m_objectCounter == m_listSize) {
						Console.WriteLine("[C#] WrapperReg - array RESIZE");
						Array.Resize(ref m_list, m_listSize += 10);
					}
                    Console.WriteLine("[C#] WrapperReg - Register GameObject with handle " + (m_objectCounter - 1));
					return m_objectCounter - 1;
				} else {
                    // there are free handles in the array
					uint idx = m_freeHandlesList[0];
					m_freeHandlesList.RemoveAt(0);
					m_list[idx] = pObj;
					pObj.Handle = idx;
					
					Console.WriteLine("Register GameObject with handle " + idx);
					return idx;
				}
			} else {
				throw new CKLBException("This object is already registered.");
			}
		}
		
		/// <summary>
		/// Unregisters the game object from the array and set the handle to NULLHANDLER
		/// </summary>
		/// <param name='pObj'>
        /// GameObject to register.
		/// </param>
		public void unregisterGameObject(GameObject pObj)
		{
            Console.WriteLine("[C#] WrapperReg.unregisterGameObject " + pObj + " BEGIN");
			if(pObj.Handle != GameObject.NULLHANDLER) {
				m_freeHandlesList.Add(pObj.Handle);
				m_list[pObj.Handle] = null;
				pObj.Handle = GameObject.NULLHANDLER;
			} else {
				throw new CKLBException("Already unregistered.");
			}
            Console.WriteLine("[C#] WrapperReg.unregisterGameObject END");
		}
		
		/// <summary>
		/// Gets the GameObject from a handle.
		/// </summary>
		/// <returns>
		/// The GameObject
		/// </returns>
		/// <param name='handle'>
		/// Handle.
		/// </param>
		public GameObject getObjectFromHandle(uint handle)
		{
			if(handle < m_listSize) {
				return m_list[handle];
			} else {
				throw new CKLBException("This handle is too high.");
			}
		}
		
		/// <summary>
		/// Displays this instance.
		/// </summary>
		public void display()
		{
			Console.WriteLine();
			Console.WriteLine("##################################");
			Console.WriteLine("####### Wrapper Reg Display ######");
			Console.WriteLine("##################################");
			for(int i=0; m_list[i]!= null && i < m_listSize; ++i)
				Console.WriteLine("[" + i + "]" + m_list[i]);
		}
	}

}

