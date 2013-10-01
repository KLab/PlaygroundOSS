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
//====================================================================
/*
  パッケージ作成用define定義
 */
//====================================================================
#ifndef __PACKAGE_DEF_H__
#define __PACKAGE_DEF_H__

//#define __HAKONIWA
//#define __LOVELIVE

#define GET_XSTR(s) GET_STR(s)
#define GET_STR(s) #s

//====================================================================
/*
  javaとC,C++をつなげる部分用の定義
  ※ パッケージ名を変更した場合、ここも変更する事!!!
 */
//------------------------------------------------
#if defined __HAKONIWA
// 箱庭
#define JAVA_FUNC( func ) Java_klb_android_hakoniwa_PFInterface_##func
#define PROC_FUNC( func ) proc_app_klb_android_hakoniwa_PFInterface_##func
#define APP_FUNC( func )  app_klb_android_hakoniwa_PFInterface_##func

#define APP_LOAD_PATH "/data/data/klb.android.hakoniwa/lib/libGame.so"
#define JNI_LOAD_PATH "klb/android/hakoniwa/PFInterface"
#define JNI_FONTMANAGER_LOAD_PATH "klb/android/hakoniwa/FontManager"

//------------------------------------------------
#elif defined __LOVELIVE

#define JAVA_FUNC( func ) Java_klb_android_lovelive_PFInterface_##func
#define PROC_FUNC( func ) proc_app_klb_android_lovelive_PFInterface_##func
#define APP_FUNC( func )  app_klb_android_lovelive_PFInterface_##func

#define APP_LOAD_PATH "/data/data/klb.android.lovelive/lib/libGame.so"
#define JNI_LOAD_PATH "klb/android/lovelive/PFInterface"
#define JNI_FONTMANAGER_LOAD_PATH "klb/android/lovelive/FontManager"

//------------------------------------------------
#else
// デフォルト(GameEngine)
#define JAVA_FUNC( func ) Java_klb_android_GameEngine_PFInterface_##func
#define PROC_FUNC( func ) proc_app_klb_android_GameEngine_PFInterface_##func
#define APP_FUNC( func )  app_klb_android_GameEngine_PFInterface_##func

#define APP_LOAD_PATH "/data/data/klb.android.GameEngine/lib/libGame.so"
#define JNI_LOAD_PATH "klb/android/GameEngine/PFInterface"
#define JNI_FONTMANAGER_LOAD_PATH "klb/android/GameEngine/FontManager"

#endif

#endif //__PACKAGE_DEF_H__
