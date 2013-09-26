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
using System.Text;
using System.Runtime.InteropServices;

namespace EnginePrototype
{
    public struct Size
    {
        public int width;
        public int height;
    }

    public struct USize
    {
        public uint width;
        public uint height;
    }

    public struct FSize
    {
        public float width;
        public float height;
    }

    public class IClientRequest 
    {
        public enum EVENT_TYPE {
		    E_PAUSE,		// プロセスがポーズ状態になった
		    E_RESUME,		// プロセスがレジュームされた
            E_TEXTCHANGE,   // TextBox の文字列が変更された
            E_URLJUMP,      // Webのコマンドリンクが指定された
        
            E_DIDSTARTLOADWEB,  // Webのロードが開始された
		    E_DIDLOADENDWEB,	// Webのロードが終了した
            E_FAILEDLOADWEB,    // Webのロードが失敗した
        
            E_STORE_BAD_ITEMID,         // アイテムIDが無効
            E_STORE_PURCHASHING,        // 購入処理中
            E_STORE_PURCHASHED,         // 購入処理終了
            E_STORE_FAILED,             // 購入処理失敗

            E_STORE_RESTORE,            // リストア終了
            E_STORE_RESTORE_FAILED,     // リストア失敗
            E_STORE_RESTORE_COMPLETED,  // 全リストア終了

            E_STORE_GET_PRODUCTS,       // ProductListの取得.

		    E_SOUND_STATE_PLAY,             // サウンド再生中
            E_SOUND_STATE_STOP,             // サウンド停止中
            E_SOUND_STATE_PAUSE,            // サウンド一時停止中
            E_SOUND_STATE_INVALID_HANDLE,   // サウンドハンドル無効
         };
    }

	public static class __FrameworkUtils
    {
        #region DllImports
        // name : const char*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static uint Cpp_getClassIDByName(IntPtr name);
        #endregion

        // = 0 <-- Fail
        // Implementation sample below
        public static uint GetClassIDByName(String className)
        {
            Console.WriteLine("[C#] Utils.GetClassIDByName(" + className + ") = " + Cpp_getClassIDByName(__MarshallingUtils.NativeUtf8FromString(className)));
            return Cpp_getClassIDByName(__MarshallingUtils.NativeUtf8FromString(className));
        }

        public static uint RegisterClass(String className/*, Type t*/) 
        {
            // GameObjectFactory.registerType(className, t); // Not used at the moment.
            return GetClassIDByName(className);
        }
/*	
 * implementation in classes
 * 
	class CKLBUIProgressBar {
		static private engineID = getClassIDByName("CKLBUIProgressBar");
	}
*/
	}

}

namespace System {
    public static class __MarshallingUtils
    {
        public static IntPtr NativeUtf8FromString(String managedString)
        {
            if(managedString != null) {
                int len = Encoding.UTF8.GetByteCount(managedString);
                byte[] buffer = new byte[len + 1];
                Encoding.Default.GetBytes(managedString, 0, managedString.Length, buffer, 0);
                IntPtr nativeUtf8 = Marshal.AllocHGlobal(buffer.Length);
                Marshal.Copy(buffer, 0, nativeUtf8, buffer.Length);
                return nativeUtf8;
            } else {
                return IntPtr.Zero;
            }
        }

        public static String StringFromNativeUtf8(IntPtr nativeUtf8)
        {
            if(nativeUtf8 != IntPtr.Zero) {
                int len = 0;
                while(Marshal.ReadByte(nativeUtf8, len) != 0) ++len;
                if(len == 0) return string.Empty;
                byte[] buffer = new byte[len];
                Marshal.Copy(nativeUtf8, buffer, 0, buffer.Length);
                return Encoding.Default.GetString(buffer);
            } else {
                return null;
            }
        }

        public static String[] StringArrayFromNativeUtf8IntPtr(IntPtr nativeUtf8, int size)
        {
            if(nativeUtf8 != IntPtr.Zero) {
                String[] strArr = new String[size];
                for(int i = 0; i < size; ++i) {
                    IntPtr strPtr = (IntPtr)Marshal.PtrToStructure(nativeUtf8, typeof(IntPtr));
                    strArr[i] = StringFromNativeUtf8(strPtr);
                    nativeUtf8 = (IntPtr)((long)nativeUtf8 + IntPtr.Size);
                }

                return strArr;
            } else {
                return null;
            }
        }

        /*
        public static String[] StringArrayFromNativeUtf8IntPtrArray(IntPtr[] nativeUtf8Array, int size)
        {
            if(nativeUtf8Array != null) {
                String[] strArr = new String[size];
                for(int i = 0; i < size; ++i) {
                    strArr[i] = __MarshallingUtils.StringFromNativeUtf8(nativeUtf8Array[i]);
                }
                return strArr;
            } else {
                return null;
            }
        }
         */

        public static IntPtr[] NativeUtf8ArrayFromStringArray(String[] stringArray, int size)
        {
            if(stringArray != null) {
                IntPtr[] intPtrArr = new IntPtr[size];
                for(int i = 0; i < size; ++i) {
                    intPtrArr[i] = NativeUtf8FromString(stringArray[i]);
                }
                return intPtrArr;
            } else {
                return null;
            }
        }

        public static int[] IntArrayFromIntPtr(IntPtr ptr, int size)
        {
            if(ptr != IntPtr.Zero) {
                int[] result = new int[size];
                Marshal.Copy(ptr, result, 0, size);
                return result;
            } else {
                return null;
            }
        }
    }
}

