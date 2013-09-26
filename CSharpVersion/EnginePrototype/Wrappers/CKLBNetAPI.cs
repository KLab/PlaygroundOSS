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
    public class CKLBNetAPI : CKLBTask
    {
        #region DllImports
        // pParent  : CKLBTask*
        // apiurl   : const char*
        // client_version   : const char*
        // consumer_key     : const char*
        // application_id   : const char*
        // region   : const char*
        // return   : CKLBNetAPI*
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private extern static IntPtr CKLBNetAPI_create( IntPtr pParent, IntPtr apiurl, IntPtr client_version, IntPtr consumerKey,
                                                        IntPtr applicationId, uint sessionMax, IntPtr region);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBNetAPI_startUp(IntPtr p, IntPtr loginID, IntPtr password, IntPtr invite, uint timeout, ref uint session);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBNetAPI_login(IntPtr p, IntPtr loginID, IntPtr password, uint timeout, ref uint session);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBNetAPI_cancel(IntPtr p, uint uniq);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBNetAPI_cancelAll(IntPtr p);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        private extern static bool CKLBNetAPI_watchMaintenance(IntPtr p, uint timeout, ref uint session);

        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CKLBNetAPI_debugHdr(IntPtr p, bool debugflag);

        // body     : const char*
        // buf      : char[512]
        [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private extern static void CKLBNetAPI_genCmdNumID(IntPtr p, IntPtr body, int serial, IntPtr buf);
		
        // apiURL   : const char*
        // json     : const char*
		[DllImport("__Internal", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        [return: MarshalAs(UnmanagedType.I1)]
		private extern static bool CKLBNetAPI_sendHTTP(IntPtr p, IntPtr apiURL, IntPtr json, uint timeout, bool passVersionCheck, ref uint session);
        #endregion

        #region Constructors
        static uint s_classID = __FrameworkUtils.RegisterClass("HTTP_API"/*, typeof(CKLBNetAPI)*/);

        public CKLBNetAPI(CKLBTask parent, String apiUrl, String clientVersion, String consumerKey, String applicationID, uint sessionMax = 1, String region = "840" /*America*/, CallBack callback = null, CallBackVersionUp versionUpCallback = null)
            : base(s_classID)
        {
            NativeManagement.resetCppError();
            IntPtr ptr = CKLBNetAPI_create( parent != null ? parent.CppObject : IntPtr.Zero,__MarshallingUtils.NativeUtf8FromString(apiUrl),__MarshallingUtils.NativeUtf8FromString(clientVersion),
                                            __MarshallingUtils.NativeUtf8FromString(consumerKey),__MarshallingUtils.NativeUtf8FromString(applicationID),sessionMax,__MarshallingUtils.NativeUtf8FromString(region));
            NativeManagement.intercepCppError();
            bind(ptr);

            m_callback          = callback;
            m_callbackVersionUp = versionUpCallback;
        }

        public CKLBNetAPI() : base(s_classID) { }
        #endregion

        #region CallBacks

        public delegate bool CallBack(CKLBNetAPI caller, int uniq, ESTATUS msg, int status, IntPtr pRoot);
        public delegate void CallBackVersionUp(CKLBNetAPI caller, String clientVer, String serverVer);
        
        private CallBack            m_callback;
        private CallBackVersionUp   m_callbackVersionUp;

        protected override void doSetupCallbacks()
        {
            registerCallBack(new NativeManagement.FunctionPointerIIIP_retB(callBackFunction),   0);
            registerCallBack(new NativeManagement.FunctionPointerSS(callBackVersionUpFunction), 1);
        }

        public override void setDelegate(Delegate anyDelegate, String delegateName)
        {
            if(delegateName == "versionUp") {
                m_callbackVersionUp = (CallBackVersionUp)anyDelegate;
            } else {
                m_callback = (CallBack)anyDelegate;
            }
        }

        public virtual bool callBackFunction(int uniq, int msg, int status, IntPtr pRoot)
        {
            if(m_callback != null) {
                return m_callback(this, uniq, (ESTATUS)msg, status, pRoot);
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }

        public virtual void callBackVersionUpFunction(IntPtr clientVer, IntPtr serverVer)
        {
            if(m_callbackVersionUp != null) {
                m_callbackVersionUp(this, __MarshallingUtils.StringFromNativeUtf8(clientVer), __MarshallingUtils.StringFromNativeUtf8(serverVer));
            } else {
                throw new CKLBException("Delegate NULL for this callback : Virtual function in subclass not implemented or delegate is null");
            }
        }
        #endregion

        public enum ESTATUS
        {
	        // メッセージ値定義
	        NETAPIMSG_SESSION_CANCELED  = -999,	// セッションはキャンセルされた
	        NETAPIMSG_CONNECTION_FAILED = -500,	// 接続に失敗した

	        NETAPIMSG_INVITE_FAILED     = -200,	// Invite status の処理に失敗
	        NETAPIMSG_STARTUP_FAILED    = -100,	// ユーザ登録失敗
	        NETAPIMSG_SERVER_TIMEOUT    = -4,	// サーバとの通信がタイムアウトした
	        NETAPIMSG_REQUEST_FAILED    = -3,	// サーバがリクエストに対しエラーを返した
	        NETAPIMSG_LOGIN_FAILED      = -2,	// ログイン失敗
	        NETAPIMSG_SERVER_ERROR      = -1,	// サーバにアクセスできない/サーバからのパケットを解釈できない
	        NETAPIMSG_UNKNOWN           = 0,

	        NETAPIMSG_LOGIN_SUCCESS     = 2,	// ログイン成功
	        NETAPIMSG_REQUEST_SUCCESS   = 3,	// リクエスト成功ステータス
	        NETAPIMSG_STARTUP_SUCCESS   = 100,	// ユーザ登録成功
	        NETAPIMSG_INVITE_SUCCESS    = 200	// Invite status の処理に成功
        }

        public bool startUp(ref uint session, String loginID, String password, String invite = null, uint timeout = 0)
        {
            if(CppObject != IntPtr.Zero) {
                bool res = CKLBNetAPI_startUp(CppObject, __MarshallingUtils.NativeUtf8FromString(loginID), __MarshallingUtils.NativeUtf8FromString(password), __MarshallingUtils.NativeUtf8FromString(invite), timeout, ref session);
                return res;
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public bool login(ref uint session, String loginID, String password, uint timeout = 0)
        {
            if(CppObject != IntPtr.Zero) {
                bool res = CKLBNetAPI_login(CppObject, __MarshallingUtils.NativeUtf8FromString(loginID), __MarshallingUtils.NativeUtf8FromString(password), timeout, ref session);
                return res;
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public bool cancel(uint session)
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBNetAPI_cancel(CppObject, session);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public bool send(ref uint session, String json, String apiURL = "/api", uint timeout = 0, bool pass_version_check = false)
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBNetAPI_sendHTTP(CppObject, __MarshallingUtils.NativeUtf8FromString(apiURL), __MarshallingUtils.NativeUtf8FromString(json), timeout, pass_version_check, ref session);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void cancelAll()
        {
            if(CppObject != IntPtr.Zero) {
                CKLBNetAPI_cancelAll(CppObject);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public bool watchMaintenance(ref uint session, uint timeout = 0)
        {
            if(CppObject != IntPtr.Zero) {
                return CKLBNetAPI_watchMaintenance(CppObject, timeout, ref session);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void debugHdr(bool debugflag)
        {
            if(CppObject != IntPtr.Zero) {
                CKLBNetAPI_debugHdr(CppObject, debugflag);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }

        public void genCmdNumID(ref String numID, String body, int serial)
        {
            if(CppObject != IntPtr.Zero) {
                IntPtr intPtr = __MarshallingUtils.NativeUtf8FromString(new String('0', 512));
                CKLBNetAPI_genCmdNumID(CppObject, __MarshallingUtils.NativeUtf8FromString(body), serial, intPtr);
                numID = __MarshallingUtils.StringFromNativeUtf8(intPtr);
            } else {
                throw new CKLBExceptionNullCppObject();
            }
        }
    }
}