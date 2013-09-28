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
#include "CAndroidFont.h"
#include "CPFInterface.h"

CAndroidFont::CAndroidFont(int size, const char * fontName)
{
//	fontName = NULL;	// ハングするので一旦 //
	// フォント管理クラスを取得(static class)
	jclass cls_fntManage = CJNI::getJNIEnv()->FindClass(JNI_FONTMANAGER_LOAD_PATH);

	// Paint作成函数ID取得
	jmethodID mtd_createPaint = getEnv()->GetStaticMethodID(cls_fntManage, "CreatePaint", "(Ljava/lang/String;)Landroid/graphics/Paint;");

	// エイリアスからフォント名を取得
	const char* fntName = NULL;
	for( int i=0; fontName && ms_fontlist[i].alias; i++ )
	{
		if( !strcmp(ms_fontlist[i].alias, fontName) )
		{
			fntName = ms_fontlist[i].fontname;
		}
	}

	jstring strj = NULL;
	if( fntName ) {
		strj = getEnv()->NewStringUTF(fntName);
	}

	// 指定フォント名でPaintを作成
	jobject local_font = CJNI::getJNIEnv()->CallStaticObjectMethod( cls_fntManage, mtd_createPaint, strj );

	// グローバル的な変数として設定
	m_paint = getEnv()->NewGlobalRef(local_font);

	m_getfontmetrics = getEnv()->GetStaticMethodID(cls_fntManage, "getFontMetrics", "(Landroid/graphics/Paint;)Landroid/graphics/Paint$FontMetrics;");
	m_settextsize	 = getEnv()->GetStaticMethodID(cls_fntManage, "setTextSize", "(Landroid/graphics/Paint;F)V");
	m_setantialias	 = getEnv()->GetStaticMethodID(cls_fntManage, "setAntiAlias", "(Landroid/graphics/Paint;Z)V");
	m_measuretext 	 = getEnv()->GetStaticMethodID(cls_fntManage, "measureText", "(Landroid/graphics/Paint;Ljava/lang/String;)F");
	/*
	{
		char buf[256];
		sprintf(buf, "m_getfontmetrics = %d, m_settextsize = %d, m_setantialias = %d", m_getfontmetrics, m_settextsize, m_setantialias);
		__android_log_write(ANDROID_LOG_DEBUG, "Cpp", buf);
	}
	 */

	// アンチエイリアス設定(PFInterface.javaのdrawTextでの描画時と、ただ文章幅を取得したい場合の幅値が異なるため)  2013/04/11  
	setAntiAlias(true);
	// テキストサイズを設定
	setTextSize(size);

	CJNI::getJNIEnv()->DeleteLocalRef(cls_fntManage);
	CJNI::getJNIEnv()->DeleteLocalRef(strj);
	CJNI::getJNIEnv()->DeleteLocalRef(local_font);
}

CAndroidFont::~CAndroidFont()
{
	// グローバル参照を解消
	getEnv()->DeleteGlobalRef(m_paint);
}

// フォントサイズが変更されるたび、フォントパラメータを変更する
void
CAndroidFont::setTextSize(float size)
{
	jclass cls_fntManage = CJNI::getJNIEnv()->FindClass(JNI_FONTMANAGER_LOAD_PATH);
	CJNI::getJNIEnv()->CallStaticVoidMethod( cls_fntManage, m_settextsize, (jobject)m_paint, (jfloat)size );

	// FontMetricsを取得
	jobject local_obj = getEnv()->CallStaticObjectMethod( cls_fntManage, m_getfontmetrics, (jobject)m_paint );

	// FontMetricsから詳細情報取得
	jclass clfontmetrics = getEnv()->FindClass("android/graphics/Paint$FontMetrics");
	m_ascent 	= getEnv()->GetFieldID(clfontmetrics, "ascent", "F");
	m_descent	= getEnv()->GetFieldID(clfontmetrics, "descent", "F");
	m_top 		= getEnv()->GetFieldID(clfontmetrics, "top", "F");
	m_bottom	= getEnv()->GetFieldID(clfontmetrics, "bottom", "F");

	// フィールドIDからフォント各値を得る
	m_f_ascent	= -(float)getEnv()->GetFloatField(local_obj, m_ascent);
	m_f_descent	= -(float)getEnv()->GetFloatField(local_obj, m_descent);
	m_f_top		= -(float)getEnv()->GetFloatField(local_obj, m_top);
	m_f_bottom	= -(float)getEnv()->GetFloatField(local_obj, m_bottom);

	DEBUG_PRINT("ascent:%f descent:%f top:%f bottom:%f", m_f_ascent, m_f_descent, m_f_top, m_f_bottom);
    
#if defined __LOVELIVE
	// Loveliveだけは既にあるヒント画面などの見た目維持のため小細工します  2013/05/07  
	// Lovelive Font Hack  2013/05/07  
	const float HEIGHT_CHANGE_HINT_SIZE = 32;
	const float HEIGHT_CHANGE_FRIEND_SIZE = 24;
	if(size == HEIGHT_CHANGE_HINT_SIZE)
	{
		// iOSと同じ値にしています
		m_f_ascent = 24.5391f;
		m_f_descent = -6.13333f;
		m_f_top = 24.9816f;
		m_f_bottom = -7.0184f;
        //	DEBUG_PRINT("LL Change  ascent:%f descent:%f top:%f bottom:%f", m_f_ascent, m_f_descent, m_f_top, m_f_bottom);
	}
	else if(size == HEIGHT_CHANGE_FRIEND_SIZE)
	{
		m_f_ascent = 18.4062f;
		m_f_descent = -4.6f;
		m_f_top = 18.7375f;
		m_f_bottom = -5.2625f;
	}
#endif

	CJNI::getJNIEnv()->DeleteLocalRef(cls_fntManage);
	CJNI::getJNIEnv()->DeleteLocalRef(local_obj);
    CJNI::getJNIEnv()->DeleteLocalRef(clfontmetrics);
}

void
CAndroidFont::setAntiAlias(bool aa)
{
	jclass cls_fntManage = CJNI::getJNIEnv()->FindClass(JNI_FONTMANAGER_LOAD_PATH);
	getEnv()->CallStaticVoidMethod( cls_fntManage, m_setantialias, (jobject)m_paint, (jboolean)aa );
	CJNI::getJNIEnv()->DeleteLocalRef(cls_fntManage);
}

float
CAndroidFont::stringWidth(const char * strText)
{
    jstring strj = getEnv()->NewStringUTF(strText);
    jclass cls_fntManage = CJNI::getJNIEnv()->FindClass(JNI_FONTMANAGER_LOAD_PATH);
    jfloat jresult = getEnv()->CallStaticFloatMethod( cls_fntManage, m_measuretext, (jobject)m_paint, strj );

    getEnv()->DeleteLocalRef( strj );
    getEnv()->DeleteLocalRef(cls_fntManage);
    return (float)jresult;
}

