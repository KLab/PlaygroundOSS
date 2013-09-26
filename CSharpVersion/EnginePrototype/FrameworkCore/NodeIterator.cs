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
    /// NodeIterator is used to run through a node tree.
    /// 
    /// A NodeIterator contains an uint (counter) determined at the creation of the object.
    /// It limits its use : the NodeIterator can only be used before this counter 
    /// changes in the Engine.
    /// This counter is updated each time there is an update on the node tree.
    /// 
    /// Navigation methods can be used with registerStack to true. It will then use a 
    /// node stack which will store the previous node before returning the new one.
    /// 
    /// A NodeIterator can return the current element as : Element, Container, Selectable, AnimationNode.
    /// 
    /// It can use some navigation methods to run through the node tree.
    /// Please take a look at methods documentation for more details.
    /// 
    /// Node properties can be directly modified through a NodeIterator.
    /// </summary>
    public class NodeIterator
    {
        #region DllImports
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr node_getRoot();
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr node_getChild(IntPtr pNode);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr node_getParent(IntPtr pNode);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr node_getBrother(IntPtr pNode);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr node_getNodeFromTask(IntPtr pTask);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static float node_getNodeScaleX(IntPtr pNode);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static float node_getNodeScaleY(IntPtr pNode);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static float node_getRotation(IntPtr pNode);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static float node_getNodeTranslateX(IntPtr pNode);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static float node_getNodeTranslateY(IntPtr pNode);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr node_getName(IntPtr pNode);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void node_setName(IntPtr pNode, IntPtr name);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void node_setTranslate(IntPtr pNode, float x, float y);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void node_setRotation(IntPtr pNode, float deg);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void node_setScale(IntPtr pNode, float scaleX, float scaleY);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void node_getColorMatrixVec(IntPtr pNode, float[] dst);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void node_setColorMatrixVec(IntPtr pNode, float[] src);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint node_getColorMatrixUInt(IntPtr pNode);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void node_setColorMatrixUInt(IntPtr pNode, uint val);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void node_setVisible(IntPtr pNode, bool visible);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool node_getVisible(IntPtr pNode);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr node_asElement(IntPtr pNode);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr node_asContainer(IntPtr pNode);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr node_asSelectable(IntPtr pNode);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr node_asAnimationNode(IntPtr pNode);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr node_getUITask(IntPtr pNode);

        // name : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr node_search(IntPtr pNode, IntPtr name);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr node_searchFirstByTypeID(IntPtr pNode, uint typeID);
        #endregion

        /// <summary>
        /// Public constructor for user.
        /// The NodeIterator is defaultly empty and must be filled through UITask.getIterator or UITask.getIteratorFromName
        /// </summary>
        public NodeIterator() { }

        /// <summary>
        /// Intern constructor only.
        /// Creates a NodeIterator on a specific node given.
        /// </summary>
        /// <param name="counter">Frame counter.</param>
        /// <param name="node">Node to set the NodeIterator on.</param>
        internal NodeIterator(uint counter, IntPtr node) {
            this.m_counter = counter;
            this.m_nodeCpp = node;
        }

        private uint m_counter;
        private IntPtr m_nodeCpp;
        private List<IntPtr> m_navigation = new List<IntPtr>();

        internal static IntPtr getRoot() 
        {
            return node_getRoot();
        }

        internal static IntPtr getNodeFromTask(CKLBUITask task)
        {
            return node_getNodeFromTask(task.CppObject);
        }

		public Element getAsElement() {
            if(m_counter == NativeManagement.getContextCounter()) {
                if(node_asElement(m_nodeCpp) != IntPtr.Zero) {
                    return new Element(m_counter, node_asElement(m_nodeCpp));
                } else {
                    return null;
                }
            } else {
                throw new CKLBExceptionTooOld();
            }
        }
		
		public Container getAsContainer() {
            if(m_counter == NativeManagement.getContextCounter()) {
                if(node_asContainer(m_nodeCpp) != IntPtr.Zero) {
                    return new Container(m_counter, node_asElement(m_nodeCpp));
                } else {
                    return null;
                }
            } else {
                throw new CKLBExceptionTooOld();
            }
        }
		
		public Selectable getAsSelectable() {
            if(m_counter == NativeManagement.getContextCounter()) {
                if(node_asSelectable(m_nodeCpp) != IntPtr.Zero) {
                    return new Selectable(m_counter, node_asElement(m_nodeCpp));
                } else {
                    return null;
                }
            } else {
                throw new CKLBExceptionTooOld();
            }
        }

        public AnimationNode getAsAnimationNode()
        {
            if(m_counter == NativeManagement.getContextCounter()) {
                if(node_asAnimationNode(m_nodeCpp) != IntPtr.Zero) {
                    return new AnimationNode(m_counter, node_asElement(m_nodeCpp));
                } else {
                    return null;
                }
            } else {
                throw new CKLBExceptionTooOld();
            }
        }

        /// <summary>
        /// Go to the child node if any. Return true if successfull, false if no child is available.
        /// If registerStack is true and navigation successfull, the previous node is pushed into a navigation stack.
        /// </summary>
        /// <param name="registerStack">Push the previous node into a navigation stack.</param>
        /// <returns>True if successfull.</returns>
        public bool gotoChild(bool registerStack = false) 
        {
            if(m_counter == NativeManagement.getContextCounter()) {
                IntPtr nNode = node_getChild(m_nodeCpp);
                if(nNode != IntPtr.Zero) {
                    // Push on navigation stack if needed.
                    if(registerStack) { m_navigation.Add(m_nodeCpp); }
                    m_nodeCpp = nNode;
                    return true;
                } else {
                    return false;
                }
            }
            else
            {
                throw new CKLBExceptionTooOld();
            }
        }

        public bool gotoBrother(bool registerStack = false)
        {
            if(m_counter == NativeManagement.getContextCounter()) {
                IntPtr nNode = node_getBrother(m_nodeCpp);
                if(nNode != IntPtr.Zero) {
                    // Push on navigation stack if needed.
                    if(registerStack) { m_navigation.Add(m_nodeCpp); }
                    m_nodeCpp = nNode;
                    return true;
                } else {
                    return false;
                }
            } else {
                throw new CKLBExceptionTooOld();
            }
        }

        public bool gotoParent(bool registerStack = false)
        {
            if(m_counter == NativeManagement.getContextCounter()) {
                IntPtr nNode = node_getParent(m_nodeCpp);
                if(nNode != IntPtr.Zero) {
                    // Push on navigation stack if needed.
                    if(registerStack) { m_navigation.Add(m_nodeCpp); }
                    m_nodeCpp = nNode;
                    return true;
                } else {
                    return false;
                }
            } else {
                throw new CKLBExceptionTooOld();
            }
        }

        /// <summary>
        /// Take the latest entry inside the navigation stack if any, and jump to the node, then the node is removed from the navigation stack.
        /// Returns true if the operation is sucessfull, false if the navigation stack is empty.
        /// </summary>
        /// <returns>
        /// True if successfull.
        /// False if the navigation stack is empty.
        /// </returns>
        public bool rollback()
        {
            if(m_counter == NativeManagement.getContextCounter()) {
                if(m_navigation.Count != 0) {
                    m_nodeCpp = m_navigation[m_navigation.Count - 1];
                    // Pop from stack.
                    m_navigation.RemoveAt(m_navigation.Count - 1);
                    return true;
                } else {
                    return false;
                }
            } else {
                throw new CKLBExceptionTooOld();
            }
        }

        /// <summary>
        /// Try to find a Node designated by name in the subnode of the actual one.
        /// If the Node is found, the NodeIterator is updated.
        /// Else it keeps its reference to the current Node.
        /// </summary>
        /// <param name="name">Name of the node looked for.</param>
        /// <returns>true if succeeds, else returns false.</returns>
        public bool find(String name, bool registerStack = false)
        {
            if(m_counter == NativeManagement.getContextCounter()) {
                if(m_nodeCpp != IntPtr.Zero) {
                    IntPtr ptr = node_search(m_nodeCpp, __MarshallingUtils.NativeUtf8FromString(name));
                    if(ptr != IntPtr.Zero) {
                        if(registerStack) { m_navigation.Add(m_nodeCpp); }
                        m_nodeCpp = ptr;
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            } else {
                throw new CKLBExceptionTooOld();
            }
        }

        /// <summary>
        /// Try to get the UITask linked to the current Node of the NodeIterator.
        /// </summary>
        /// <returns>The UITask if a UITask is effectivly linked to the Node. Else returns null.</returns>
        public CKLBUITask getAsUITask()
        {
            IntPtr ptr = node_getUITask(m_nodeCpp);
            if(ptr != IntPtr.Zero) {
                NativeManagement.resetCppError();
                CKLBUITask task = new CKLBUITask(NativeManagement.getTypeID(ptr));
                NativeManagement.intercepCppError();
                task.bind(ptr);
                return task;
            } else {
                return null;
            }
        }

        /// <summary>
        /// Search in subtree from iterator (including itself),
        /// check if user task and native task are compatible,then bind.
        /// </summary>
        /// <param name="task">The UITask to bind.</param>
        /// <param name="name">Name of the node to bind with the UITask.</param>
        /// <returns>If not possible to bind returns null , if sucessfull return UITask.</returns>
        public CKLBUITask bindTask(CKLBUITask task, String name = null) 
        {
            if(name != null) {
                if(find(name, true)) {
                    task.bind(node_getUITask(m_nodeCpp));
                } else {
                    throw new CKLBException("There is not any Node with this name.");
                }
            } else {
                IntPtr ptr = node_searchFirstByTypeID(m_nodeCpp, task.TypeID);
                if(ptr != IntPtr.Zero) {
                    task.bind(ptr);
                } else {
                    throw new CKLBException("There is not any Node compatible with this task.");
                }
            }
            return task;
        }

        public uint Rgba
        {
            get
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        return node_getColorMatrixUInt(m_nodeCpp);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        node_setColorMatrixUInt(m_nodeCpp, value);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
        public float ScaleX
        {
            get
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        return node_getNodeScaleX(m_nodeCpp);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        node_setScale(m_nodeCpp, value, node_getNodeScaleY(m_nodeCpp));
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
        public float ScaleY
        {
            get
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        return node_getNodeScaleY(m_nodeCpp);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        node_setScale(m_nodeCpp, node_getNodeScaleX(m_nodeCpp), value);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
        public float Scale
        {
            // get { throw new CKLBExceptionForbiddenMethod(); }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        node_setScale(m_nodeCpp, value, value);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
        public float Rotation
        {
            get
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        return node_getRotation(m_nodeCpp);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        node_setRotation(m_nodeCpp, value);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
        public float X
        {
            get
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        return node_getNodeTranslateX(m_nodeCpp);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        node_setTranslate(m_nodeCpp, value, node_getNodeTranslateY(m_nodeCpp));
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
        public float Y
        {
            get
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        return node_getNodeTranslateY(m_nodeCpp);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        node_setTranslate(m_nodeCpp, node_getNodeTranslateX(m_nodeCpp), value);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
        public bool Visible
        {
            get
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        return node_getVisible(m_nodeCpp);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        node_setVisible(m_nodeCpp, value);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
        public void setXY(float x, float y)
        {
            if(m_counter == NativeManagement.getContextCounter()) {
                if(m_nodeCpp != IntPtr.Zero) {
                    node_setTranslate(m_nodeCpp, x, y);
                } else {
                        throw new CKLBExceptionNullCppObject();
                    }
            } else {
                throw new CKLBExceptionTooOld();
            }
        }

        public String Name
        {
            get
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        return __MarshallingUtils.StringFromNativeUtf8(node_getName(m_nodeCpp));
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodeCpp != IntPtr.Zero) {
                        node_setName(m_nodeCpp, __MarshallingUtils.NativeUtf8FromString(value));
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
    }

	public class Element {

        protected IntPtr m_nodePtr;
        protected uint m_counter;

        #region DllImports
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void element_setEnabled(IntPtr pElem, bool isEnabled);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool element_isEnabled(IntPtr pElem);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        protected extern static bool element_setAsset(IntPtr pElem, uint dest, IntPtr assetName);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void element_setPriority(IntPtr pElem, uint renderPriority);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint element_getPriority(IntPtr pElem);
        #endregion

        // Copy of C++ Def : TODO : create a system were .h and .cs could be maintained automatically.
        protected enum ASSET_TYPE
        {
            NORMAL_ASSET        = 0,
            DISABLED_ASSET      = 1,
            FOCUSED_ASSET       = 2,
            PUSHED_ASSET        = 3
        };

        internal Element(uint m_counter, IntPtr nodePtr)
        {
            this.m_counter = m_counter;
            this.m_nodePtr = nodePtr;
        }
		
		public bool Enabled
		{
            get
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        return element_isEnabled(m_nodePtr);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        element_setEnabled(m_nodePtr, value);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
		public String normalAsset
		{
            // get { throw new CKLBExceptionForbiddenMethod(); }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        NativeManagement.resetCppError();
                        if(!element_setAsset(m_nodePtr, (uint)ASSET_TYPE.NORMAL_ASSET, __MarshallingUtils.NativeUtf8FromString(value))) {
                            NativeManagement.intercepCppError();
                        }
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
		public String disableAsset
		{
            // get { throw new CKLBExceptionForbiddenMethod(); }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        NativeManagement.resetCppError();
                        if(!element_setAsset(m_nodePtr, (uint)ASSET_TYPE.DISABLED_ASSET, __MarshallingUtils.NativeUtf8FromString(value))) {
                            NativeManagement.intercepCppError();
                        }
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
	}

	public class Container : Element {

        #region DllImports
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static int container_getViewOffsetX(IntPtr pCont);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void container_setViewOffsetX(IntPtr pCont, int scrollX);
        
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static int container_getViewOffsetY(IntPtr pCont);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void container_setViewOffsetY(IntPtr pCont, int scrollY);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint container_getRadioValue(IntPtr pCont);
        #endregion

        internal Container(uint m_counter, IntPtr nodePtr):base(m_counter, nodePtr)
        {
        }

		public int ViewOffsetX {
            get
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        return container_getViewOffsetX(m_nodePtr);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        container_setViewOffsetX(m_nodePtr, value);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
		public int ViewOffsetY {
            get
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        return container_getViewOffsetY(m_nodePtr); 
                     } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        container_setViewOffsetY(m_nodePtr, value);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
		public uint RadioValue {
			get
            { 
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        return container_getRadioValue(m_nodePtr); 
                     } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
			//set { throw new CKLBExceptionForbiddenMethod(); }
		}
		
		// TODO : Add API about clipping.
		
	}
	
	public class Selectable : Element {

        #region DllImports
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void selectable_setClick(IntPtr pSelect, int coordinateX, int coordinateY, int width, int height);

        // assetAudio : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool selectable_setAudio(IntPtr pSelect, IntPtr assetAudio, uint mode, float volume);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void selectable_setStick(IntPtr pSelect, bool isStickable);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool selectable_isStickable(IntPtr pSelect);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void selectable_setSticked(IntPtr pSelect, bool isSticked);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool selectable_isSticked(IntPtr pSelect);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void selectable_setRadio(IntPtr pSelect, uint radioID);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint selectable_getRadioID(IntPtr pSelect);
        #endregion

        internal Selectable(uint m_counter, IntPtr nodePtr):base(m_counter, nodePtr)
        {
        }

		public String pushedAsset
		{
            // get { throw new CKLBExceptionForbiddenMethod(); }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        NativeManagement.resetCppError();
                        if(!element_setAsset(m_nodePtr, (uint)ASSET_TYPE.PUSHED_ASSET, __MarshallingUtils.NativeUtf8FromString(value))) {
                            NativeManagement.intercepCppError();
                        }
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }

        public bool setAudio(String assetName, uint mode, float volume)
        {
            if(m_counter == NativeManagement.getContextCounter()) {
                if(m_nodePtr != IntPtr.Zero) {
                    return selectable_setAudio(m_nodePtr, __MarshallingUtils.NativeUtf8FromString(assetName), mode, volume);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            } else {
                throw new CKLBExceptionTooOld();
            }
        }

        public void setClickArea(int x, int y, int width, int height)
        {
            if(m_counter == NativeManagement.getContextCounter()) {
                if(m_nodePtr != IntPtr.Zero) {
                    selectable_setClick(m_nodePtr, x, y, width, height);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            } else {
                throw new CKLBExceptionTooOld();
            }
        }
		
		public bool isDown {
            get
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        return selectable_isSticked(m_nodePtr);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        selectable_setStick(m_nodePtr, value);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
		}
		
		public bool checkBoxMode {
            get
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        return selectable_isStickable(m_nodePtr);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        selectable_setSticked(m_nodePtr, value);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
		
		public uint RadioID {
            get
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        return selectable_getRadioID(m_nodePtr);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
            set
            {
                if(m_counter == NativeManagement.getContextCounter()) {
                    if(m_nodePtr != IntPtr.Zero) {
                        selectable_setRadio(m_nodePtr, value);
                    } else {
                        throw new CKLBExceptionNullCppObject();
                    }
                } else {
                    throw new CKLBExceptionTooOld();
                }
            }
        }
	}

    public class AnimationNode
    {
        protected IntPtr nodePtr;
        protected uint m_counter;

        internal AnimationNode(uint m_counter, IntPtr nodePtr)
        {
            this.m_counter = m_counter;
            this.nodePtr = nodePtr;
        }

        void setAnimation(AnimationInfo animationInfo)
        {
            throw new CKLBExceptionNotImplemented();
        }
    }
}
