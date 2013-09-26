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
    public static class CSDebug
    {
        #region DllImports
        // caption & key : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibDEBUG_startMenu(uint maxCount, IntPtr caption, IntPtr key);

        // caption & key : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibDEBUG_addItem(uint mode, IntPtr caption, IntPtr key, int min, int max, int value, IntPtr[] items, uint itemsCount);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibDEBUG_endMenu();

        // key : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBLuaLibDEBUG_removeMenu(IntPtr key);
        #endregion

        #region CallBacks
        // TODO static Callback
        /*
        public delegate void CallBack();
        
        private static CallBack s_callback;

        public override void setDelegate(Delegate anyDelegate, String delegateName = null)
        {
            s_callback = (CallBack)anyDelegate;
        }

        public virtual void callBackFunction()
        {
            if(s_callback != null) {
                s_callback();
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }
        */
        #endregion

        private enum ESECTION_TYPE
        {
            M_SWITCH = 0,
            M_NUMBER = 1,
            M_SELECT = 2,
        }
        private static bool s_isBuildingMenu = false;

        public static void setCallback() { throw new CKLBExceptionNotImplemented(); }

        public static void startMenu(uint maxCount, String caption, String key)
        {
            if(s_isBuildingMenu) { throw new CKLBException("A Menu is already being built at the moment."); }
            s_isBuildingMenu = true;
            CKLBLuaLibDEBUG_startMenu(maxCount, __MarshallingUtils.NativeUtf8FromString(caption), __MarshallingUtils.NativeUtf8FromString(key));
        }

        public static void addItemSwitch(String itemName, String itemKey, bool defaultValue) 
        {
            if(!s_isBuildingMenu) { throw new CKLBException("There is no Menu building. Please use startMenu before."); }
            CKLBLuaLibDEBUG_addItem((uint)ESECTION_TYPE.M_SWITCH, __MarshallingUtils.NativeUtf8FromString(itemName), __MarshallingUtils.NativeUtf8FromString(itemKey), 0, 0, (defaultValue) ? 1:0, null, 0);
        }

        public static void addItemSelect(String itemName, String itemKey, String defaultValue, String[] items) 
        {
            if(!s_isBuildingMenu) { throw new CKLBException("There is no Menu building. Please use startMenu before."); }
            CKLBLuaLibDEBUG_addItem((uint)ESECTION_TYPE.M_SELECT, __MarshallingUtils.NativeUtf8FromString(itemName), __MarshallingUtils.NativeUtf8FromString(itemKey), 0, 0, Array.IndexOf(items, defaultValue), __MarshallingUtils.NativeUtf8ArrayFromStringArray(items, items.Length), (uint)items.Length);
        }

        public static void addItemNumber(String itemName, String itemKey, int lowerLimit, int upperLimit, int defaultValue) 
        {
            if(!s_isBuildingMenu) { throw new CKLBException("There is no Menu building. Please use startMenu before."); }
            CKLBLuaLibDEBUG_addItem((uint)ESECTION_TYPE.M_NUMBER, __MarshallingUtils.NativeUtf8FromString(itemName), __MarshallingUtils.NativeUtf8FromString(itemKey), lowerLimit, upperLimit, defaultValue, null, 0);
        }

        public static void endMenu()
        {
            if(!s_isBuildingMenu) { throw new CKLBException("There is no Menu building. Please use startMenu before."); }
            CKLBLuaLibDEBUG_endMenu();
            s_isBuildingMenu = false;
        }

        public static void removeMenu(String key) 
        { 
            CKLBLuaLibDEBUG_removeMenu(__MarshallingUtils.NativeUtf8FromString(key)); 
        }
    }
}
