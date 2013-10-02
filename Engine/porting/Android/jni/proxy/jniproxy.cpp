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
 * jniproxy.cpp
 *
 */

// jniproxy.cpp

#include <stdio.h>
#include    <jni.h>
#include    <android/log.h>
#include    <dlfcn.h>
#include "klb_android_GameEngine_PFInterface.h"
#include "../Android/PackageDefine.h"

JavaVM  *javaVm = NULL;

/*
template<typename T>
void auto_load( T& a, void* ptr ,  const char * func_name )
{
 	if(!ptr) {
 		char buf[256];
 		sprintf(buf, "symbol not found in DLL: %s", func_name);
 	   __android_log_write(ANDROID_LOG_DEBUG, "Proxy", (const char *)buf);
 	}
    a= reinterpret_cast<T>( ptr );
}
#define get_proc_0( image, proc_func , app_func )  auto_load( proc_func , dlsym( image , #app_name ) , #app_func )
#define get_proc( proc_func , app_func )   get_proc_0( LoadApplication, proc_func , app_func )
*/
template<typename T>
void auto_load( T& a, void* image ,  const char * func_name )
{
    void* ptr = dlsym( image , func_name );
 	if(!ptr) {
 		char buf[256];
 		sprintf(buf, "symbol not found in DLL: %s", func_name);
 	   __android_log_write(ANDROID_LOG_DEBUG, "Proxy", (const char *)buf);
 	}
    a= reinterpret_cast<T>( ptr );
}


//-----------------------------------------------------------------------------
static jboolean JNICALL (*PROC_FUNC(initSequence))(JNIEnv *, jobject, jint, jint, jstring, jstring, jstring, jstring, jstring, jstring);
static void     JNICALL (*PROC_FUNC(frameFlip))(JNIEnv *, jobject, jint);
static void     JNICALL (*PROC_FUNC(finishGame))(JNIEnv *, jobject);
static void     JNICALL (*PROC_FUNC(inputPoint))(JNIEnv *, jobject, jint, jint, jint, jint);
static void     JNICALL (*PROC_FUNC(inputDeviceKey))(JNIEnv *, jobject, jint, jchar);
static void     JNICALL (*PROC_FUNC(rotateScreenOrientation))(JNIEnv *, jobject, jint, jint, jint);
static void     JNICALL (*PROC_FUNC(toNativeSignal))(JNIEnv *, jobject, jint, jint);
static jint     JNICALL (*PROC_FUNC(getGLVersion))(JNIEnv *, jobject);
static void     JNICALL (*PROC_FUNC(resetViewport))(JNIEnv *, jobject);
static void     JNICALL (*PROC_FUNC(onActivityPause))( void );
static void     JNICALL (*PROC_FUNC(onActivityResume))( void );
static void		JNICALL (*PROC_FUNC(clientControlEvent))(JNIEnv *, jobject, jint, jint, jstring, jstring);
static void     JNICALL (*PROC_FUNC(WebViewControlEvent))( JNIEnv *, jobject, jobject, jint );
static void		JNICALL (*PROC_FUNC(clientResumeGame))( void );
static void		JNICALL (*PROC_FUNC(jniOnLoad))( JavaVM*, void* );

//-----------------------------------------------------------------------------

static void*   LoadApplication= NULL;

static int InitializeApplication()
{
#if DEBUG
	__android_log_write(ANDROID_LOG_DEBUG, "Proxy", "Initialize application DLL.");
#endif

    // lib 読み込み
    LoadApplication= dlopen( APP_LOAD_PATH , RTLD_LAZY );
    if( !LoadApplication ){
    	return -1;
    }

    // API 取り出し
    auto_load( PROC_FUNC(getGLVersion)            , LoadApplication , GET_XSTR( APP_FUNC(getGLVersion) ) );
    auto_load( PROC_FUNC(initSequence)            , LoadApplication , GET_XSTR( APP_FUNC(initSequence) ) );
    auto_load( PROC_FUNC(frameFlip)               , LoadApplication , GET_XSTR( APP_FUNC(frameFlip) ) );
    auto_load( PROC_FUNC(finishGame)              , LoadApplication , GET_XSTR( APP_FUNC(finishGame) ) );
    auto_load( PROC_FUNC(inputPoint)              , LoadApplication , GET_XSTR( APP_FUNC(inputPoint) ) );
    auto_load( PROC_FUNC(inputDeviceKey)          , LoadApplication , GET_XSTR( APP_FUNC(inputDeviceKey) ) );
    auto_load( PROC_FUNC(rotateScreenOrientation) , LoadApplication , GET_XSTR( APP_FUNC(rotateScreenOrientation) ) );
    auto_load( PROC_FUNC(toNativeSignal)          , LoadApplication , GET_XSTR( APP_FUNC(toNativeSignal) ) );
    auto_load( PROC_FUNC(resetViewport)           , LoadApplication , GET_XSTR( APP_FUNC(resetViewport) ) );
    auto_load( PROC_FUNC(onActivityPause)         , LoadApplication , GET_XSTR( APP_FUNC(onActivityPause) ) );
    auto_load( PROC_FUNC(onActivityResume)        , LoadApplication , GET_XSTR( APP_FUNC(onActivityResume) ) );
	auto_load( PROC_FUNC(clientControlEvent)      , LoadApplication , GET_XSTR( APP_FUNC(clientControlEvent) ) );
    auto_load( PROC_FUNC(WebViewControlEvent)     , LoadApplication , GET_XSTR( APP_FUNC(WebViewControlEvent) ) );
    auto_load( PROC_FUNC(clientResumeGame)         , LoadApplication , GET_XSTR( APP_FUNC(clientResumeGame) ) );
    auto_load( PROC_FUNC(jniOnLoad)               , LoadApplication , GET_XSTR( APP_FUNC(jniOnLoad) ) );

	if (javaVm != NULL) {
		PROC_FUNC(jniOnLoad)(javaVm, NULL);
	}
    return 0;
}


static void FinalizeApplication()
{
    if( LoadApplication ){
        dlclose( LoadApplication );
        LoadApplication= NULL;
    }
}


extern "C" {
//-----------------------------------------------------------------------------

JNIEXPORT jboolean JNICALL JAVA_FUNC(initSequence)
  (JNIEnv *env, jobject obj, jint j_width, jint j_height, jstring j_strPath,
		  jstring j_model, jstring j_brand, jstring j_board, jstring j_version, jstring j_tz)
{
    if( !LoadApplication ){
        if(InitializeApplication()) return 0;
    }
    return PROC_FUNC(initSequence)( env, obj, j_width, j_height, j_strPath, j_model, j_brand, j_board, j_version, j_tz );
    return 0;
}

/*
 * Class:     klb_android_GameEngine_PFInterface
 * Method:    frameFlip
 * Signature: (I)V
 */
JNIEXPORT void JNICALL JAVA_FUNC(frameFlip)
  (JNIEnv *env, jobject obj, jint j_deltaT)
{
  if(LoadApplication) PROC_FUNC(frameFlip)( env, obj, j_deltaT );
}

/*
 * Class:     klb_android_GameEngine_PFInterface
 * Method:    finishGame
 * Signature: ()V
 */
JNIEXPORT void JNICALL JAVA_FUNC(finishGame)
  (JNIEnv *env, jobject obj)
{
    if( LoadApplication ){
      PROC_FUNC(finishGame)( env, obj );
        FinalizeApplication();
    }
}

JNIEXPORT void JNICALL JAVA_FUNC(inputPoint)
  (JNIEnv *env, jobject obj, jint j_id, jint j_type, jint j_x, jint j_y)
{
  if(LoadApplication) PROC_FUNC(inputPoint)( env, obj, j_id, j_type, j_x, j_y );
}

JNIEXPORT void JNICALL JAVA_FUNC(inputDeviceKey)
  (JNIEnv *env, jobject obj, jint keyId, jchar eventType)
{
  if(LoadApplication) PROC_FUNC(inputDeviceKey)( env, obj, keyId, eventType );
}

JNIEXPORT void JNICALL JAVA_FUNC(rotateScreenOrientation)
  (JNIEnv *env, jobject obj, jint j_origin, jint j_width, jint j_height)
{
  if(LoadApplication) PROC_FUNC(rotateScreenOrientation)( env, obj, j_origin, j_width, j_height );
}

JNIEXPORT void JNICALL JAVA_FUNC(toNativeSignal)
  (JNIEnv *env, jobject obj, jint j_cmd, jint j_param)
{
  if(LoadApplication) PROC_FUNC(toNativeSignal)( env, obj, j_cmd, j_param );
}

JNIEXPORT jint JNICALL JAVA_FUNC(getGLVersion)
  (JNIEnv * env, jobject obj)
{
	jint ret = 0;
	if(!LoadApplication) {
        if(InitializeApplication()) return -1;
	}
	char buf[256];
	if(PROC_FUNC(getGLVersion)) ret = PROC_FUNC(getGLVersion)( env, obj );
	return ret;
}

JNIEXPORT void JNICALL JAVA_FUNC(resetViewport)
  (JNIEnv * env, jobject obj)
{
  if(LoadApplication) PROC_FUNC(resetViewport)( env, obj);
}

// アプリにおけるバックグラウンドに行った際の動作
JNIEXPORT void  JNICALL JAVA_FUNC(onActivityPause) (void)
{
	if(LoadApplication) PROC_FUNC(onActivityPause)();
}

// アプリに置けるフォアグラウンドに行った際の動作
JNIEXPORT void  JNICALL JAVA_FUNC(onActivityResume) (void)
{
	if(LoadApplication) PROC_FUNC(onActivityResume)();
}

JNIEXPORT void JNICALL JAVA_FUNC(clientControlEvent)
	(JNIEnv * env, jobject obj, jint j_type, jint j_widget, jstring j_data_1, jstring j_data_2)
{
	// j_widgetはちょっとどう扱っていいかわからないので、null渡しておきます //
	if(LoadApplication) PROC_FUNC(clientControlEvent)( env, obj, j_type, 0, j_data_1, j_data_2 );
}

// WebViewのコントロールイベント
JNIEXPORT void JNICALL JAVA_FUNC(WebViewControlEvent) ( JNIEnv * env, jobject obj, jobject _pWeb, jint _int )
{
	if(LoadApplication) PROC_FUNC(WebViewControlEvent)( env, obj, _pWeb, _int );
}

JNIEXPORT void  JNICALL JAVA_FUNC(clientResumeGame) (void)
{
	if(LoadApplication) PROC_FUNC(clientResumeGame)();
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	javaVm = vm;
	if(LoadApplication) {
		PROC_FUNC(jniOnLoad)(vm, reserved);
	}
	return JNI_VERSION_1_6;
}
//-----------------------------------------------------------------------------
};
