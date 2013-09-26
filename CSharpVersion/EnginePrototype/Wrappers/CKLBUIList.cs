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
	public class CKLBUIList : CKLBUITask
	{
		#region DllImports
        //return : CKLBUIList*
        // pParent : CKLBUITask*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static IntPtr CKLBUIList_create(IntPtr pParent,uint baseOrder, uint maxOrder, float x, float y, float clipWidth,
                                                        float clipHeight, int defaultLineStep, bool vertical, uint optionalFlags);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIList_getWidth(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_setWidth(IntPtr p, uint width);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static uint CKLBUIList_getHeight(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_setHeight(IntPtr p, uint height);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static int CKLBUIList_getStepX(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIList_setStepX(IntPtr p, int x);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static int CKLBUIList_getStepY(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIList_setStepY(IntPtr p, int y);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBUIList_getOrder(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIList_setOrder(IntPtr p, uint order);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBUIList_getMaxOrder(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIList_setMaxOrder(IntPtr p, uint order);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIList_getVertical(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIList_setVertical(IntPtr p, bool vertical);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBUIList_getItems(IntPtr p);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIList_getMarginTop(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_setMarginTop(IntPtr p, int top);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIList_getMarginBottom(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_setMarginBottom(IntPtr p, int bottom);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static bool CKLBUIList_getDefaultScroll(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUIList_setDefaultScroll(IntPtr p, bool scroll);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIList_cmdItemRemove(IntPtr p, int idx);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_cmdItemMove(IntPtr p, int src, int dst);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_cmdSetMargin(IntPtr p, int top, int bottom);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIList_cmdGetPosition(IntPtr p);
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIList_cmdSetPosition(IntPtr p, int pos, int dir);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_cmdSetItemID(IntPtr p, int index, int id);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIList_cmdSearchID(IntPtr p, int id);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_cmdSetItemPos(IntPtr p, int mode, int idx, int offset);
		
		// limitCallBack : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_cmdSetLimitClip(IntPtr p, bool chklimit);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIList_cmdGetLimit(IntPtr p);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIList_cmdSetLimitArea(IntPtr p, int limitArea);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_cmdChangeStep(IntPtr p, int index, int step);
		
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_cmdInputEnable(IntPtr p, bool enable);

        // name : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIList_cmdExistNode(IntPtr p, int index, IntPtr name);

		// name : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIList_cmdAnimationItem(IntPtr p, int index, IntPtr name, bool blend);
		
		// name : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIList_cmdAnimationAll(IntPtr p, IntPtr name, bool blend);
		
		// name : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIList_cmdItemAnimSkip(IntPtr p, int idx, IntPtr name);
		
		// name : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		[return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIList_cmdAllAnimSkip(IntPtr p, IntPtr name);
		
		// group_name : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
		private extern static void CKLBUIList_cmdSetGroup(IntPtr p, IntPtr group_name);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_setLoop(IntPtr p, bool mode);

		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static int CKLBUIList_cmdSetInitial(IntPtr p, int pos);

        // image : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIList_useScrollBar(IntPtr p, uint order, bool side, int lineWeight, IntPtr image, int minSlenderSize, uint colorNormal, uint colorSelect, bool active, bool hideMode, bool shortHide);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_cmdFWModeConfig(IntPtr p, int itemStep, int maxItems);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIList_cmdSetItemMode(IntPtr p, int itemMode);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIList_cmdAddRecords(IntPtr p, int insIdx, IntPtr tpForm, IntPtr dbRecords, int step);

        // name : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        [return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIList_cmdSelectScrMgr(IntPtr p, IntPtr name, int[] optParams, uint nb);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_cmdSetClip(IntPtr p, uint orderBegin, uint orderEnd, short clipX, short clipY, short clipWidth, short clipHeight);

        // asset : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        [return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIList_cmdItemAdd(IntPtr p, IntPtr name);

        // name : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        [return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIList_cmdItemAdd2(IntPtr p, IntPtr name, int step, int id);

        // name : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIList_cmdInsertItem(IntPtr p, IntPtr name, int idx);

        // name : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUIList_cmdInsertItem2(IntPtr p, IntPtr name, int idx, int step, int id);

        // name : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        [return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUIList_cmdRemoveSelection(IntPtr p, int[] indexes, uint nb);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUIList_setDragRect(IntPtr p, int left, int top, int right, int bottom);
		#endregion

        #region Constructors

        static uint s_classID = __FrameworkUtils.RegisterClass("UI_List"/*, typeof(CKLBUIList)*/);

        public CKLBUIList(  CKLBUITask parent, uint base_priority, uint max_order, float x, float y,
                            float clip_width, float clip_height, int default_line_step, DragCallBack callback, bool vertical = true, uint option_flags = 0)
            : base(s_classID)
		{
            NativeManagement.resetCppError();
            IntPtr ptr =    CKLBUIList_create(  parent != null ? parent.CppObject : IntPtr.Zero, base_priority, max_order, x, y, 
                                                clip_width, clip_height, default_line_step, vertical, option_flags);
            NativeManagement.intercepCppError();
            bind(ptr);
            m_dragCallback = callback;
		}

        public CKLBUIList() : base(s_classID) { }

        #endregion

        #region CallBacks

        public delegate void LimitCallBack      (CKLBUIList caller, uint type, uint itemCount, int listLength, int pos);
        public delegate void DragCallBack       (CKLBUIList caller, uint type, int x, int y, int param1, int param2);
        public delegate void DynamicCallBack    (CKLBUIList caller, int index, int id);
        public delegate void ScrollBarCallBack  (CKLBUIList caller, uint type, int pos);
        public delegate void AnimCallBack       (CKLBUIList caller, String name, uint id);

        private LimitCallBack       m_limitCallback;      // callback number 0
        private DragCallBack        m_dragCallback;       // callback number 1
        private DynamicCallBack     m_dynamicCallback;    // callback number 2
        private ScrollBarCallBack   m_scrollbarCallback;  // callback number 3
        private AnimCallBack        m_animCallback;       // callback number 4

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerUIIII  (dragCallBackFunction),       0);
            registerCallBack(new NativeManagement.FunctionPointerUUII   (limitCallBackFunction),      1);
            registerCallBack(new NativeManagement.FunctionPointerII     (dynamicCallBackFunction),    2);
            registerCallBack(new NativeManagement.FunctionPointerUI     (scrollbarCallBackFunction),  3);
            registerCallBack(new NativeManagement.FunctionPointerSU     (animCallBackFunction),       4);
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName)
        {
            if(delegateName == "limit") {
                m_limitCallback = (LimitCallBack)anyDelegate;
            } else if(delegateName == "drag") {
                m_dragCallback = (DragCallBack)anyDelegate;
            } else if(delegateName == "dynamic") {
                m_dynamicCallback = (DynamicCallBack)anyDelegate;
            } else if(delegateName == "anim") {
                m_animCallback = (AnimCallBack)anyDelegate;
            } else if(delegateName == "scrollbar") {
                m_scrollbarCallback = (ScrollBarCallBack)anyDelegate;
            } else {
                throw new CKLBException("Unvalid delegate name");
            }
        }

        public virtual void dragCallBackFunction(uint type, int x, int y, int param1, int param2)
        {
            if(m_dragCallback != null) {
                m_dragCallback(this, type, x, y, param1, param2);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }
        
        public virtual void limitCallBackFunction(uint type, uint itemCount, int listLength, int pos)
        {
			if(m_limitCallback != null) {
                m_limitCallback(this, type, itemCount, listLength, pos);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        public virtual void dynamicCallBackFunction(int index, int id)
        {
			if(m_dynamicCallback != null) {
                m_dynamicCallback(this, index, id);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        public virtual void scrollbarCallBackFunction(uint type, int pos)
        {
			if(m_scrollbarCallback != null) {
                m_scrollbarCallback(this, type, pos);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
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

        #endregion

        public enum EPOSITION_MODE : int
        {
            LIST_VIEW_TOP,
            LIST_VIEW_CENTER,
            LIST_VIEW_END,
            LIST_VIEW_OFFSET
        }

        public enum ESCROLLBAR_VALUE : int
        {
            LIST_SCROVER_TOP,
            LIST_SCROVER_BOTTTOM,
            LIST_SCROVER_TAKEOFF
        }

        public enum EITEM_MODE : int {
		    LIST_ITEM_NORMAL,
		    LIST_ITEM_DYNAMIC,
		    LIST_ITEM_FLYWEIGHT,
        }

		public uint Width
		{
			get 
			{
				if(CppObject != IntPtr.Zero) {
					return CKLBUIList_getWidth(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
            }
			set 
			{
				if(CppObject != IntPtr.Zero) {
                    CKLBUIList_setWidth(CppObject,value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
        public uint Height
		{
			get 
			{ 
				if(CppObject != IntPtr.Zero) {
					return CKLBUIList_getHeight(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
            }
			set 
			{
				if(CppObject != IntPtr.Zero) {
                    CKLBUIList_setHeight(CppObject,value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
        public void getSize(out USize size)
        {
            if(CppObject != IntPtr.Zero) {
                size.width = CKLBUIList_getWidth(CppObject);
                size.height = CKLBUIList_getHeight(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
        public void setSize(USize size)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIList_setWidth(CppObject, size.width);
                CKLBUIList_setHeight(CppObject, size.height);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
        public void setSize(uint width, uint height)
        {
            CKLBUIList_setWidth(CppObject, width);
            CKLBUIList_setHeight(CppObject, height);
        }
		public int  StepX
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIList_getStepX(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIList_setStepX(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public int  StepY
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIList_getStepY(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIList_setStepY(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public uint Order
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIList_getOrder(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIList_setOrder(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public uint Maxodr
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIList_getMaxOrder(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIList_setMaxOrder(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public bool IsVertical
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIList_getVertical(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIList_setVertical(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public uint Items
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIList_getItems(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
		}
		public int  MarginTop
		{
			get 
			{ 
				if(CppObject != IntPtr.Zero) {
					return CKLBUIList_getMarginTop(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
            }
			set 
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIList_setMarginTop(CppObject, value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
            }
		}
        public int  MarginBottom
		{
			get 
			{ 
				if(CppObject != IntPtr.Zero) {
					return CKLBUIList_getMarginBottom(CppObject);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
            }
			set 
			{
				if(CppObject != IntPtr.Zero) {
					CKLBUIList_setMarginBottom(CppObject, value);
				} else {
					throw new CKLBExceptionNullCppObject();
                }
            }
		}
		public bool DefaultScroll
		{
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIList_getDefaultScroll(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIList_setDefaultScroll(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
		}
        public int  Position
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIList_cmdGetPosition(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            // set { throw new CKLBExceptionForbiddenMethod("Use setPosition instead."); } 
        }
        public int  Limit
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUIList_cmdGetLimit(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionNotImplemented(); }
        }
        public bool LoopMode
        {
            get { throw new CKLBExceptionNotImplemented(); }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUIList_setLoop(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }

        public void itemAdd(String asset)
		{
			if(CppObject != IntPtr.Zero) {
                CKLBUIList_cmdItemAdd(CppObject, __MarshallingUtils.NativeUtf8FromString(asset));
            } else {
                throw new CKLBExceptionNullCppObject();
            }
		}
		public void itemAdd(String asset, int step, int id = -1)
		{
			if(CppObject != IntPtr.Zero) {
                CKLBUIList_cmdItemAdd2(CppObject, __MarshallingUtils.NativeUtf8FromString(asset), step, id);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
		}

        public void itemInsert(String asset, int index)
		{
			if(CppObject != IntPtr.Zero) {
                CKLBUIList_cmdInsertItem(CppObject, __MarshallingUtils.NativeUtf8FromString(asset), index);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
		}
        public void itemInsert(String asset, int index, int step, int id = -1)
		{
			if(CppObject != IntPtr.Zero) {
                CKLBUIList_cmdInsertItem2(CppObject, __MarshallingUtils.NativeUtf8FromString(asset), index, step, id);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
		}

		public bool itemRemove(int index)
		{ 
			if(CppObject != IntPtr.Zero) {
				return CKLBUIList_cmdItemRemove(CppObject, index);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public void itemMove(int src, int dst)
		{ 
			if(CppObject != IntPtr.Zero) {
				CKLBUIList_cmdItemMove(CppObject, src, dst);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public void itemRemoveSelection(int[] indexes)
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUIList_cmdRemoveSelection(CppObject, indexes, (uint)indexes.Length);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public void setMargin(int margin_top, int margin_bottom)
		{ 
			if(CppObject != IntPtr.Zero) {
				CKLBUIList_cmdSetMargin(CppObject, margin_top, margin_bottom);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public void setItemPosition(EPOSITION_MODE positionMode, int index, int offset = 0)
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUIList_cmdSetItemPos(CppObject, (int)positionMode, index, offset);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public void changeStep(int index, int newStep)
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUIList_cmdChangeStep(CppObject, index, newStep);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public void setLimitClip(bool limitClipEnable)
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUIList_cmdSetLimitClip(CppObject, limitClipEnable);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
        public void setLimitClip(bool limitClipEnable, LimitCallBack limitCallback)
		{
			if(CppObject != IntPtr.Zero) {
                m_limitCallback = limitCallback;
				CKLBUIList_cmdSetLimitClip(CppObject, limitClipEnable);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public bool setLimitArea(int size)
		{
			if(CppObject != IntPtr.Zero) {
				return CKLBUIList_cmdSetLimitArea(CppObject, size);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public void setInputEnable(bool enableFlag)
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUIList_cmdInputEnable(CppObject, enableFlag);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

        public bool existNode(int index, String name)
        {
            if(CppObject != IntPtr.Zero) {
                NativeManagement.resetCppError();
                bool res = CKLBUIList_cmdExistNode(CppObject, index, __MarshallingUtils.NativeUtf8FromString(name));
                NativeManagement.intercepCppError();
                return res;
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

		public bool animationItem(int index, String animationName, bool blendFlag = false)
		{
			if(CppObject != IntPtr.Zero) {
				return CKLBUIList_cmdAnimationItem(CppObject, index, __MarshallingUtils.NativeUtf8FromString(animationName), blendFlag);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public bool animationAll(String animationName, bool blendFlag = false)
		{
			if(CppObject != IntPtr.Zero) {
				return CKLBUIList_cmdAnimationAll(CppObject, __MarshallingUtils.NativeUtf8FromString(animationName), blendFlag);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

        public bool useScrollbar(uint order, bool side, int lineWeight, String image, int minSliderSize, uint colorNormal, uint colorSelect, bool active, bool hideMode = false, bool shortHide = true)
		{
            if(CppObject != IntPtr.Zero) {
                return CKLBUIList_useScrollBar(CppObject, order, side, lineWeight, __MarshallingUtils.NativeUtf8FromString(image), minSliderSize, colorNormal, colorSelect, active, hideMode, shortHide);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
		}
        public bool useScrollbar(uint order, bool side, int lineWeight, String image, int minSliderSize, uint colorNormal, uint colorSelect, bool active, ScrollBarCallBack callback, bool hideMode = false, bool shortHide = true)
		{
            if(CppObject != IntPtr.Zero) {
                m_scrollbarCallback = callback;
                return CKLBUIList_useScrollBar(CppObject, order, side, lineWeight, __MarshallingUtils.NativeUtf8FromString(image), minSliderSize, colorNormal, colorSelect, active, hideMode, shortHide);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
		}

		public void setItemID(int index, int id)
		{
			if(CppObject != IntPtr.Zero) {
				CKLBUIList_cmdSetItemID(CppObject, index, id);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public int  searchID(int index)
		{
			if(CppObject != IntPtr.Zero) {
				return CKLBUIList_cmdSearchID(CppObject, index);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
        
		public bool selectScrMgr(String managerName, int[] optParams = null)
		{
			if(CppObject != IntPtr.Zero) {
                if(optParams != null) {
				    return CKLBUIList_cmdSelectScrMgr(CppObject, __MarshallingUtils.NativeUtf8FromString(managerName), optParams, (uint)optParams.Length);
                } else {
                    return CKLBUIList_cmdSelectScrMgr(CppObject, __MarshallingUtils.NativeUtf8FromString(managerName), null, 0);
                }
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}
		
		public bool itemAnimSkip(int idx, String name)
		{
			if(CppObject != IntPtr.Zero) {
				return CKLBUIList_cmdItemAnimSkip(CppObject, idx, __MarshallingUtils.NativeUtf8FromString(name));
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public bool allAnimSkip(String groupName = null)
		{
			if(CppObject != IntPtr.Zero) {
				return CKLBUIList_cmdAllAnimSkip(CppObject, __MarshallingUtils.NativeUtf8FromString(groupName));
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public bool addRecords(int insIdx, String tpForm, String dbRecords, int step = 0)
		{
			if(CppObject != IntPtr.Zero) {
				return CKLBUIList_cmdAddRecords(CppObject, insIdx, __MarshallingUtils.NativeUtf8FromString(tpForm), __MarshallingUtils.NativeUtf8FromString(dbRecords), step);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public int setInitial(int pos)
		{
			if(CppObject != IntPtr.Zero) {
				return CKLBUIList_cmdSetInitial(CppObject, pos);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
		}

		public void fwModeConfig(int itemStep, int maxItems)
        {
            if(CppObject != IntPtr.Zero) {
				CKLBUIList_cmdFWModeConfig(CppObject, itemStep, maxItems);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
        }

        public void fwItemAdd()
        {
            throw new CKLBExceptionNotImplemented("Not implemented in C++ yet.");
        }

        public void fwItemInsertTop()
        {
            throw new CKLBExceptionNotImplemented("Not implemented in C++ yet.");
        }

        public bool setItemMode(EITEM_MODE mode) 
        {
            if(CppObject != IntPtr.Zero) {
				return CKLBUIList_cmdSetItemMode(CppObject, (int)mode);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
        }
        public bool setItemMode(EITEM_MODE mode, DynamicCallBack dynamicCallback) 
        {
            if(CppObject != IntPtr.Zero) {
                m_dynamicCallback = dynamicCallback;
				return CKLBUIList_cmdSetItemMode(CppObject, (int)mode);
			} else {
				throw new CKLBExceptionNullCppObject();
            }
        }

        public int setPosition(int pos, int dir = 0) 
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBUIList_cmdSetPosition(CppObject, pos, dir);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void setGroup(String groupName)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIList_cmdSetGroup(CppObject, __MarshallingUtils.NativeUtf8FromString(groupName));
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void setClip(uint orderBegin, uint orderEnd, short clipX, short clipY, short clipWidth, short clipHeight)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIList_cmdSetClip(CppObject, orderBegin, orderEnd, clipX, clipY, clipWidth, clipHeight);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void setDragRect(int left, int top, int right, int bottom)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUIList_setDragRect(CppObject, left, top, right, bottom);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
	}
}
