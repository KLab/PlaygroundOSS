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
package klb.android.GameEngine;

import android.content.Context;

/**
 * @class RClassReference
 * @breif R classを参照するためのclass.
 * Activityの最初(の方)で、
 * RClassReference.initialize(getApplicationContext())
 * とする事でApplicationのpackage名を取得しそこからR classの各要素をキャッシュ、
 * その後R classの要素が必要になるタイミングでget系Methodを使用する.
 *
 * @note
 * これを使用する事によって、package名の違いによって R class を参照する時に逐一renameしないといけなかった部分がなくなる.
 * ApplicationContextからApplicationのpackage名を取得して文字列を連結、そこからReflectionでclassのfieldを取得している.
 * Reflectionを使用しているので呼び出す度に計算取得し直すのではなく、Application起動時に必要な要素を滑て取得してキャッシュしておくようにしている.
 * @note
 * ApplicationContextのextendsとして専用ApplicationContextを作る方がよかったかもしれない.
 */
public class RClassReference {
    private static int gcm_sender_id; /** R$string sender_id */
    private static int app_name; /** R&string app_name */
    private static String gcm_sender_id_string; /** R$string sender_id をAppicationContext.getString()でString化したもの. */
    private static String app_name_string; /** R&string app_name をAppicationContext.getString()でString化したもの. */
    private static int install; /** R$layout install */
    private static int indicator; /** R$layout indicator */
    private static int ic_launcher; /** R$drawable ic_launcher */

    /**
     * @func initialize
     * @brief 初期化. Activityの最初(正確にはR classのFieldを使う前)にcallしておく必要がある.
     * @param appContext ApplicationContext
     */
    public static void initialize(Context appContext) {
        try
            {
                // Reflectionを利用してApplication package名からR classの各要素を取得する.
                // package.name.R$string
                // stringはマニフェストファイルにmeta-dataを追加してそれ経由で取得しても良いかもしれない.
                Class<?> stringClass = Class.forName(appContext.getPackageName() + ".R$string");
                java.lang.reflect.Field stringAppName = stringClass.getField("app_name");
                app_name = stringAppName.getInt(null);
                app_name_string = appContext.getString(app_name);
                java.lang.reflect.Field stringGCMSenderID = stringClass.getField("sender_id");
                gcm_sender_id = stringGCMSenderID.getInt(null);
                gcm_sender_id_string = appContext.getString(gcm_sender_id);

                // package.name.R$layout
                Class<?> layoutClass = Class.forName(appContext.getPackageName() + ".R$layout");
                java.lang.reflect.Field layoutInstall = layoutClass.getField("install");
                install = layoutInstall.getInt(null);

                java.lang.reflect.Field layoutIndicator = layoutClass.getField("indicator");
                indicator = layoutIndicator.getInt(null);

                // package.name.R$drawable
                Class<?> drawableClass = Class.forName(appContext.getPackageName() + ".R$drawable");
                java.lang.reflect.Field drawableICLauncher = drawableClass.getField("ic_launcher");
                ic_launcher = drawableICLauncher.getInt(null);
            }
          catch (ClassNotFoundException e)
              {
                  throw new RuntimeException(e);
              }
          catch (NoSuchFieldException e)
              {
                  throw new RuntimeException(e);
              }
          catch (IllegalAccessException e)
              {
                  throw new RuntimeException(e);
              }
    }

    /**
     * @func getAppName
     * @brief R.string.app_nameを返す.
     * @return R.string.app_nameの値
     */
    public static int getAppName() {
        return app_name;
    }

    /**
     * @func getGCMSenderID
     * @brief R.string.sender_idを返す.
     * @return R.string.sender_idの値
     */
    public static int getGCMSenderID() {
        return gcm_sender_id;
    }

    /**
     * @func getAppNameString
     * @brief R.string.app_nameの文字列を返す.
     * @return R.string.app_nameの値
     */
    public static String getAppNameString() {
        return app_name_string;
    }

    /**
     * @func getGCMSenderIDString
     * @brief R.string.sender_idの文字列を返す.
     * @return R.string.sender_idの値
     */
    public static String getGCMSenderIDString() {
        return gcm_sender_id_string;
    }

    /**
     * @func getInstall
     * @brief R.layout.installを返す.
     * @return R.layout.installの値
     */
    public static int getInstall() {
        return install;
    }

    /**
     * @func getIndicator
     * @brief R.layout.indicatorを返す.
     * @return R.layout.indicatorの値
     */
    public static int getIndicator() {
        return indicator;
    }

    /**
     * @func getICLauncher
     * @brief R.drawable.ic_launcherを返す.
     * @return R.drawable.ic_launcherの値
     */
    public static int getICLauncher() {
        return ic_launcher;
    }

    /**
     * @func getAppName
     * @brief R.string.app_nameをappContextを介してstring化した物を返す.
     * @param appContext ApplicationContext
     * @return app_nameの正式な文字列.
     */
    public static String getAppName(Context appContext) {
        return appContext.getString(app_name);
    }

    /**
     * @func getGCMSenderID
     * @brief R.string.sender_idをappContextを介してstring化した物を返す.
     * @param appContext ApplicationContext
     * @return sender_idの正式な文字列.
     */
    public static String getGCMSenderID(Context appContext) {
        return appContext.getString(gcm_sender_id);
    }
}
