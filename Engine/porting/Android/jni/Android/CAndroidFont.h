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
#pragma once

#include "CJNI.h"
#include "PackageDefine.h"

// フォント対応表。抽象化されたaliasと、実際iOSに渡すフォント名の対応をとる。
static struct FONTLIST {
	const char * alias;
	const char * fontname;
} ms_fontlist[] = {
    // alias        Android-name
    { "Georgia",    "Georgia.TTF" },
    { "ヒラギノ角ゴ pro", "MTLmr3m.ttf" },
    { 0, 0 }
};

class CAndroidFont : public CJNI
{
public:
	CAndroidFont(int size, const char * fontName = 0);
	virtual ~CAndroidFont();

	void setAntiAlias(bool aa);
	void setTextSize(float size);

	float stringWidth(const char * strText);

	// フォント各値取得
	inline float		ascent() { return m_f_ascent; }
	inline float		descent() { return m_f_descent; }
	inline float		top() { return m_f_top; }
	inline float		bottom() { return m_f_bottom; }

	inline jobject&		getPaint() { return m_paint; }

private:
	jobject		m_paint;		// Paintオブジェクト
	jmethodID	m_getfontmetrics;	// getFontMetrics() method ID
	jmethodID	m_setantialias;		// setAntiAlias(boolean) method ID
	jmethodID	m_settextsize;		// setTextSize() method ID
	jmethodID	m_measuretext;		// measureText() method ID

	jfieldID	m_ascent;
	jfieldID	m_descent;
	jfieldID	m_top;
	jfieldID	m_bottom;
	jmethodID	m_stringwidth;

	float		m_f_ascent;
	float		m_f_descent;
	float		m_f_top;
	float		m_f_bottom;
};

