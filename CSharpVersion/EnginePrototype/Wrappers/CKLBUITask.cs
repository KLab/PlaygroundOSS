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
using System.Collections.Generic;

namespace EnginePrototype
{
    /// <summary>
    /// Base class used for all task that are related to displaying something on the screen.
    /// Graphics properties, animation features are available to all tasks derived from this class.
    /// </summary>
	public class CKLBUITask : CKLBTask
	{
        #region DllImports

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUITask_getVisible(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUITask_setVisible(IntPtr p, bool isVisible);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static float CKLBUITask_getScaleX(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUITask_setScaleX(IntPtr p, float scaleX);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static float CKLBUITask_getScaleY(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUITask_setScaleY(IntPtr p, float scaleY);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static float CKLBUITask_getX(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUITask_setX(IntPtr p, float x);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static float CKLBUITask_getY(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUITask_setY(IntPtr p, float y);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static float CKLBUITask_getRotation(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUITask_setRotation(IntPtr p, float rotation);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint CKLBUITask_getArgb(IntPtr p);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUITask_setArgb(IntPtr p, uint argb);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBUITask_isAnim(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUITask_play(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBUITask_stop(IntPtr p);
		
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBUITask_setParamCount(IntPtr p, uint splineCount, uint maxKeyCount);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUITask_setTarget			(IntPtr p, uint splineIndex, ETARGET_TYPE targetParameter);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUITask_addKeys			(IntPtr p, uint splineIndex, uint time, int value);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUITask_addKeysFixed		(IntPtr p, uint splineIndex, uint time, int fixed16Value);
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
		private extern static void CKLBUITask_generateAnimation	(IntPtr p);

        // nodeName : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static bool CKLBUITask_reconnect(IntPtr p, IntPtr nodeName);
		
        #endregion

        #region Constructors

        // Just throws the classID to GameObject
        internal CKLBUITask(uint classID) : base(classID) { }

        #endregion

        /// <summary>
        /// Type of properties modified by the animation spline.
        /// See IntSpline
        /// See FloatSpline
        /// </summary>
        public enum ETARGET_TYPE
        {
            MODIFY_X        = 1 /* Value in pixels related to node coordinate system*/,
            MODIFY_Y        = 2 /* Value in pixels related to node coordinate system*/,
            MODIFY_SCALE    = 3 /* Scale for X and Y axis, 1.0f is 100% */, 
            MODIFY_R        = 4 /* Red color component value between 0 and 255*/,
            MODIFY_G        = 5 /* Green color component value between 0 and 255*/,
            MODIFY_B        = 6 /* Blue color component value between 0 and 255*/,
            MODIFY_A        = 7 /* Alpha color component value between 0 and 255*/,
            MODIFY_ROT      = 8 /* Rotation in degree, 360.0f is a full rotation*/
        }

        /// <summary>
        /// Type of the spline to be used.
        /// </summary>
        public enum ESPLINE_TYPE
        {
            INT_SPLINE,
            FLOAT_SPLINE
        }

        /// <summary>
        /// Abstract Class owning one animation spline for one target property.
        /// </summary>
        public abstract class Spline
        {
            protected ETARGET_TYPE m_targetType;
            public ETARGET_TYPE TargetType
            {
                get { return m_targetType; }
            }

            /// <summary>
            /// Number of keys inside the spline.
            /// </summary>
            public abstract uint KeyCount
            {
                get;
            }

            protected Spline(ETARGET_TYPE targetType)
            {
                m_targetType = targetType;
            }

            abstract public void addKeyInt(uint time, int value);
            abstract public void addKeyFloat(uint time, float value);

            internal abstract void addKeys(IntPtr p, uint splineIndex);
        }

        /// <summary>
        /// Class used to define a spline using integer values.
        /// </summary>
        private class IntSpline : Spline
        {
            class IntPoint
            {
                private uint m_time;
                public uint Time
                {
                    get { return m_time; }
                }

                private short m_value;
                public short Value
                {
                    get { return m_value; }
                }

                internal IntPoint(uint time, short value)
                {
                    m_time = time;
                    m_value = value;
                }
            }

            private List<IntPoint> m_points;

            internal IntSpline(ETARGET_TYPE targetType) : base(targetType)
            {
                m_points = new List<IntPoint>();
            }

            //Allows the user to add a key with an int value to a spline
            override public void addKeyInt(uint time, int value)
            {
                if(value <= 32767)	//short.MaxValue
                {
                    m_points.Add(new IntPoint(time, (short)value));
                } else {
                    throw new CKLBException("The value of a spline point cannot be greater than 32767");
                }
            }
            public override void addKeyFloat(uint time, float value)
            {
                throw new CKLBExceptionForbiddenMethod();
            }

            public override uint KeyCount
            {
                get { return (uint)m_points.Count; }
            }

            //Used internally to generate the animation
            internal override void addKeys(IntPtr p, uint splineIndex)
            {
                for(int i = 0; i < m_points.Count; ++i) {
                    CKLBUITask_addKeys(p, splineIndex, m_points[i].Time, m_points[i].Value);
                }
            }
        }

        private class FloatSpline : Spline
        {
            public class FloatPoint
            {
                private uint m_time;
                public uint Time
                {
                    get { return m_time; }
                }

                private float m_value;
                public float Value
                {
                    get { return m_value; }
                }

                internal FloatPoint(uint time, float value)
                {
                    m_time = time;
                    m_value = value;
                }
            }

            private List<FloatPoint> m_points;

            internal FloatSpline(ETARGET_TYPE targetType) : base(targetType)
            {
                m_points = new List<FloatPoint>();
            }

            //Allows the user to add a key with a float value to a spline
            override public void addKeyFloat(uint time, float value)
            {
                m_points.Add(new FloatPoint(time,value));
            }

            public override void addKeyInt(uint time, int value)
            {
                throw new CKLBExceptionForbiddenMethod();
            }

            public override uint KeyCount
            {
                get { return (uint)m_points.Count; }
            }

            //Used internally to generate the animation
            internal override void addKeys(IntPtr p, uint splineIndex)
            {
                for(int i = 0; i < m_points.Count; ++i) {
                    CKLBUITask_addKeysFixed(p, splineIndex, m_points[i].Time, (int)(m_points[i].Value*65536.0));
                }
            }
        }

        public class AnimSpline
        {
            private List<Spline> m_splines;
            public List<Spline> Splines
            {
                get { return m_splines; }
            }

            public AnimSpline()
            {
                m_splines = new List<Spline>();
            }

            public Spline addNewSpline(ETARGET_TYPE targetType, ESPLINE_TYPE splineType)
            {
                switch (splineType) {
                    case ESPLINE_TYPE.INT_SPLINE:
                    {      
                        IntSpline spline = new IntSpline(targetType);
                        m_splines.Add(spline);
                        return spline;
                    }

                    case ESPLINE_TYPE.FLOAT_SPLINE:
                    {
                        FloatSpline spline = new FloatSpline(targetType);
                        m_splines.Add(spline);
                        return spline;
                    }

                    default: return null;
                }
            }
            public void reset()
            {
                m_splines.Clear();
            }
        }

        /// <summary>
        /// Scale property on the X axis of the graphic task.
        /// 1.0f means 100%
        /// </summary>
        public float ScaleX
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUITask_getScaleX(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUITask_setScaleX(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }

        /// <summary>
        /// Scale property on the Y axis of the graphic task.
        /// 1.0f means 100%
        /// </summary>
        public float ScaleY
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUITask_getScaleY(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUITask_setScaleY(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        /// <summary>
        /// Scale property on the X axis of the graphic task.
        /// Scale is in degree, so 360.0f is a complete rotation.
        /// </summary>
        public float Rotation
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUITask_getRotation(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUITask_setRotation(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        /// <summary>
        /// X coordinate related to graphic parent task, or related to screen left coordinate if no owner set. 
        /// 1.0f means 1 pixels in logical screen coordinate.
        /// </summary>
        public float X
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUITask_getX(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUITask_setX(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        /// <summary>
        /// Y coordinate related to graphic parent task, or related to screen top coordinate if no owner set. 
        /// 1.0f means 1 pixels in logical screen coordinate.
        /// </summary>
        public float Y
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUITask_getY(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUITask_setY(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        /// <summary>
        /// Allows a graphic task to be visible or invisible.
        /// As an example a blinking object could be made easily.
        /// Hiding useless objects improve the engine performance and is recommended instead of putting them outside of the screen viewport.
        /// </summary>
        public bool IsVisible
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUITask_getVisible(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUITask_setVisible(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }
        /// <summary>
        /// It is possible to have a global color multiplied to the graphic task.
        /// As an example, alpha blending is the most easy use case to understand.
        /// ARGB values are stored on 32 bit with 8 bit per component ARGB
        /// B is LSB and A the MSB in the following order ARGB
        /// As an example : 0xFF000000 turn the object shape fully black
        ///                 0x80FFFFFF turn the object with 50% alpha blending.
        /// Basically every color in the object in modified in the following fashion :
        /// Alpha blending with screen = A Task pixel * A color.
        /// R on screen before alpha blending = R Task pixel * R Color
        /// G on screen before alpha blending = G Task pixel * G Color
        /// B on screen before alpha blending = B Task pixel * B Color
        /// </summary>
        public uint Argb
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUITask_getArgb(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            set
            {
                if(CppObject != IntPtr.Zero) {
                    CKLBUITask_setArgb(CppObject, value);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
        }

        /// <summary>
        /// Indicate if the task is already performing an animation.
        /// </summary>
        public bool IsNodeAnim
        {
            get
            {
                if(CppObject != IntPtr.Zero) {
                    return CKLBUITask_isAnim(CppObject);
                } else {
                    throw new CKLBExceptionNullCppObject();
                }
            }
            //set { throw new CKLBExceptionForbiddenMethod(); }
        }

        /// <summary>
        /// Get a node iterator, allowing to navigate through the scenegraph and manipulate nodes inside a task.
		/// Return the node passed as parameter.
        /// </summary>
        /// <param name="nodeIterator">Return a </param>
        /// <returns></returns>
        public NodeIterator getIterator(out NodeIterator nodeIterator)
        {
            uint counter    = NativeManagement.getContextCounter();
            IntPtr node     = NodeIterator.getNodeFromTask(this);

            nodeIterator = new NodeIterator(counter, node);
            return nodeIterator;
        }

        /// <summary>
        /// Get a node iterator already positionned on a node named "name".
        /// </summary>
        /// <param name="name">iterator default position, if name is null or not found, ?</param>
        /// <param name="nodeIterator">returned iterator</param>
        /// <returns>? not void</returns>
        public NodeIterator getIteratorFromName(String name, out NodeIterator nodeIterator)
        {
            nodeIterator = getIterator(out nodeIterator);
            if(!nodeIterator.find(name)) {
                nodeIterator = null;
            }
            return nodeIterator;
        }

        /// <summary>
        /// Use to move a part of the scene graph tree to another part, only within this task.
        /// Basically, it is mainly used for forms, but any task can benefit from such feature.
        /// </summary>
        /// <param name="nodeName"></param>
        public void nodeReconnect(String nodeName)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUITask_reconnect(CppObject, __MarshallingUtils.NativeUtf8FromString(nodeName));
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        /// <summary>
        /// Start an animation, ? what happen if already animating ?
        /// See setAnimSpline()
        /// </summary>
        public void animationPlay()
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUITask_play(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        /// <summary>
        /// Stop an animation, does nothing is no animation is executing.
        /// See setAnimSpline()
        /// </summary>
        public void animationStop()
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUITask_stop(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }  

        /// <summary>
        /// Helper function to set both X and Y scale in an atomic fashion, faster than setting scale seperatly.
        /// </summary>
        /// <param name="scaleX">X Scale, 1.0f is 100%</param>
        /// <param name="scaleY">Y Scale, 1.0f is 100%</param>
        public void setScale(float scaleX, float scaleY)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBUITask_setScaleX(CppObject, scaleX);
                CKLBUITask_setScaleY(CppObject, scaleY);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        /// <summary>
        /// Link an animation information to the root node of this task.
        /// See animationPlay()
        /// See animationStop()
        /// ? Rename as setAnimationSpline
        /// </summary>
        /// <param name="splineArray"></param>
        public void setAnimSpline(AnimSpline splineArray)
        {
            uint maxKeyCount = 0;
            for(int i = 0; i < splineArray.Splines.Count; ++i) {
                if(splineArray.Splines[i].KeyCount > maxKeyCount) {
                    maxKeyCount = splineArray.Splines[i].KeyCount;
                }
            }
            if(CKLBUITask_setParamCount(CppObject, (uint)splineArray.Splines.Count, maxKeyCount)) {
                uint splineIndex = 0;
                for(int i = 0; i < splineArray.Splines.Count; ++i) {
                    CKLBUITask_setTarget(CppObject, splineIndex, splineArray.Splines[i].TargetType);
                    splineArray.Splines[i].addKeys(CppObject, splineIndex++);
                }
                CKLBUITask_generateAnimation(CppObject);
            }
        }
	}
}
