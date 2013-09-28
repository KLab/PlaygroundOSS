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
#include "CAndroidWidget.h"
#include "CAndroidRequest.h"
#include "CAndroidPathConv.h"
#include "CJNI.h"
#include "../source/SystemTask/CKLBDrawTask.h"
#include "PackageDefine.h"

// Android は stdarg.h をサポートしない(そのかわりincludeしてもエラーを出さない)ため、
// va_start/va_arg/va_end が定義されない。gcc のビルトインを定義してやる。
#if !defined(va_start)
#define va_start(ap, last) __builtin_va_start(ap, last)
#endif
#if !defined(va_end)
#define va_end(ap) __builtin_va_end(ap)
#endif
#if !defined(va_arg)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#endif
#if !defined(va_list)
typedef __builtin_va_list va_list;
#endif


CAndroidWidget::CAndroidWidget(CAndroidRequest * pPlatform)
: m_id(0), m_hIndex(0), m_x(0), m_y(0), m_width(0), m_height(0)
, m_bVisible(true), m_bEnable(true), m_pParent(pPlatform) {}

CAndroidWidget::~CAndroidWidget() {}

void
CAndroidWidget::cmd(int cmd, ...) {}

int
CAndroidWidget::status() { return 0; }

bool
CAndroidWidget::init(int hIndex, int id, int x, int y, int width, int height)
{
	m_hIndex = hIndex;
	m_id = id;
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;

	return true;
}

void
CAndroidWidget::move(int x, int y)
{
	bool bUpdate = (m_x != x || m_y != y);
	m_x = x;
	m_y = y;
    set_move(m_x,m_y,m_width,m_height);
}

void
CAndroidWidget::resize(int width, int height)
{
	bool bUpdate = (m_width != width || m_height != height);
	m_width = width;
	m_height = height;
    set_move(m_x,m_y,m_width,m_height);
}

void
CAndroidWidget::visible(bool bVisible)
{
	if(bVisible != m_bVisible) {
		m_bVisible = bVisible;
		update();
	}
}

void
CAndroidWidget::enable(bool bEnable)
{
	if(bEnable != m_bEnable) {
		m_bEnable = bEnable;
		update();
	}
}

/////////////////////////////////////////////
// CAndroidTextWidget
/////////////////////////////////////////////
CAndroidTextWidget	*	CAndroidTextWidget::m_begin = 0;
CAndroidTextWidget	*	CAndroidTextWidget::m_end = 0;
CAndroidTextWidget::CAndroidTextWidget(CAndroidRequest * pParent)
: CAndroidWidget(pParent)
, m_prev(NULL)
, m_next(NULL)
, m_pFont(0)
{
	m_prev = m_end;
	if(m_prev) {
		m_prev->m_next = this;
	} else {
		m_begin = this;
	}
	m_end = this;
}
CAndroidTextWidget::~CAndroidTextWidget()
{
	jvalue val;
	m_pParent->callJavaMethod(val, "textbox_destroy", 'Z', "I", m_hIndex);

	if(m_prev) {
		m_prev->m_next = m_next;
	} else {
		m_begin = m_next;
	}
	if(m_next) {
		m_next->m_prev = m_prev;
	} else {
		m_end = m_prev;
	}
}

bool
CAndroidTextWidget::create(IWidget::CONTROL type, int id, const char * caption,
							int x, int y, int width, int height)
{
	jvalue jval;
	int hIndex = -1;
	bool passwd = false;
	m_id = id;

	switch(type)
	{
	default:
		return false;

	case PASSWDBOX:
		passwd = true;
	case TEXTBOX:
		DEBUG_PRINT("x:%d y:%d width:%d height:%d caption:%s passwd:%d", x, y, width, height, caption, passwd);
		m_pParent->callJavaMethod(jval, "textbox_create", 'I', "IIIISZ", x, y, width, height, caption, passwd);
		hIndex = jval.i;
		break;
	}

	DEBUG_PRINT("CAndroidTextWidget::create() hIndex = %d", hIndex);
	if(hIndex < 0) return false;

	return init(hIndex, id, x, y, width, height);
}

void
CAndroidTextWidget::update()
{
	jvalue jval;
	m_pParent->callJavaMethod(jval, "textbox_update", 'V', "IIIIIZZ",
							m_hIndex, m_x, m_y, m_width, m_height, m_bEnable, m_bVisible);

}

int
CAndroidTextWidget::getTextLength()
{
	jvalue jval;
	m_pParent->callJavaMethod(jval, "textbox_getText", 'S', "I", m_hIndex);
	jstring jstr = (jstring)jval.l;
	// GetStringLengthではバイト数ではなくてUnicode文字のカウントだけするみたいなので変更  2013/03/25   //
	return CJNI::getJNIEnv()->GetStringUTFLength(jstr);
}

bool
CAndroidTextWidget::getText(char * pBuf, int maxlen)
{
	jvalue jval;
	m_pParent->callJavaMethod(jval, "textbox_getText", 'S', "I", m_hIndex);
	const char * str = CJNI::getJNIEnv()->GetStringUTFChars((jstring)jval.l, 0);

	int i = 0;
	for(i = 0; str[i] && i < maxlen - 1; i++) pBuf[i] = str[i];
	pBuf[i] = 0;

	CJNI::getJNIEnv()->ReleaseStringUTFChars((jstring)jval.l, str);
	return true;
}

bool
CAndroidTextWidget::setText(const char * string)
{
	jvalue jval;
	m_pParent->callJavaMethod(jval, "textbox_setText", 'Z', "IS", m_hIndex, string);
	return (bool)jval.z;
}

void
CAndroidTextWidget::setMaxlen(int maxlen)
{
  jvalue jval;
  m_pParent->callJavaMethod(jval, "textbox_setMaxlen", 'V', "II", m_hIndex, maxlen);
}


void
CAndroidTextWidget::set_move(int x,int y,int width,int height)
{
	// 非常に不本意ながらAndroidのTextEditの枠が一定以下のサイズの場合枠表示が変になってしまうため下限を設けました  2013/04/04  //
	if(height > 0)
	{
		CKLBDrawResource& draw = CKLBDrawResource::getInstance();
		float heightLogical = draw.toLogical(height);
//		m_pParent->logging("height : %d  org : %f\n", height, heightLogical);
		if(heightLogical < 56)
		{
			int tmpHeight = draw.toPhisical(56);
			m_height = tmpHeight;
//			m_pParent->logging("change height : %d\n", tmpHeight);
		}
	}
	
    jvalue jval;
	m_pParent->callJavaMethod(jval, "textbox_update", 'V', "IIIIIZZ",
							m_hIndex, m_x, m_y, m_width, m_height, m_bEnable, m_bVisible);
}

void
CAndroidTextWidget::cmd(int cmd, ...)
{
	va_list ap;
	va_start(ap, cmd);

	switch(cmd)
	{
		case TX_PLACEHOLDER:
		{
			// プレースホルダに文字設定
			const char * placeholder = va_arg(ap, const char *);

			jvalue jval;
			m_pParent->callJavaMethod(jval, "textbox_sethint", 'V', "IS", GetIndex(), placeholder);

			break;
		}
		case TX_FONT:
		{
			CAndroidFont * pFont = (CAndroidFont *)va_arg(ap, void *);
			m_pFont = pFont;

			jmethodID methodID = 0;
			jclass cls_pfif = CJNI::getJNIEnv()->FindClass(JNI_LOAD_PATH);
			methodID = CJNI::getJNIEnv()->GetStaticMethodID(cls_pfif, "textbox_setpaint", "(ILandroid/graphics/Paint;)V");
			jint ret = CJNI::getJNIEnv()->CallStaticIntMethod(cls_pfif, methodID, GetIndex(), (jobject)m_pFont->getPaint());
			CJNI::getJNIEnv()->DeleteLocalRef(cls_pfif);

			break;
		}
		case TX_MAXLEN:
		{
			int maxlen = va_arg(ap, int);
			this->setMaxlen(maxlen);
			break;
		}
		case TX_CHARTYPE:
		{
#if 0
			int chartype = va_arg(ap, int);
			m_chartype = chartype;
#endif
			break;
		}
		case TX_ALIGNMENTTYPE:
		{
			// setup text alignment.
			// Android implements "normal / opposite" model instead of "left / right" model.
			// so, make sure to work properly with RTL languages
			int alignType = va_arg(ap, int);
			int m_alignType;
			switch( alignType )
			{
				case TX_ALIGN_LEFT:
					m_alignType = ALIGN_LEFT;
					break;
				case TX_ALIGN_CENTER:
					m_alignType = ALIGN_CENTER;
					break;
				case TX_ALIGN_RIGHT:
					m_alignType = ALIGN_RIGHT;
					break;
				default:
					m_alignType = ALIGN_LEFT;
			}
			jvalue jval;
			m_pParent->callJavaMethod(jval, "textbox_setAlignment", 'V', "II", GetIndex(), m_alignType);
			break;
		}
		default:
		{
#if 0
			unsigned int color = va_arg(ap, unsigned int);
			switch (cmd)
			{
				case TX_BGCOLOR_NORMAL: m_cols[0] = color; break;
				case TX_FGCOLOR_NORMAL: m_cols[1] = color; break;
				case TX_BGCOLOR_TOUCH:  m_cols[2] = color; break;
				case TX_FGCOLOR_TOUCH:  m_cols[3] = color; break;
			}
			set_color();    // カラー設定
#endif
			break;
		}
	}

	va_end(ap);
}

/////////////////////////////////////////////
// CAndroidWebWidget
/////////////////////////////////////////////
CAndroidWebWidget	*	CAndroidWebWidget::m_begin = 0;
CAndroidWebWidget	*	CAndroidWebWidget::m_end = 0;
CAndroidWebWidget::CAndroidWebWidget(CAndroidRequest * pParent)
: CAndroidWidget(pParent)
, m_bZoom(true)
, m_bgalpha(0)
, m_bgcolor(0xffffff)
, m_prev(NULL)
, m_next(NULL)
{
	m_prev = m_end;
	if(m_prev) {
		m_prev->m_next = this;
	} else {
		m_begin = this;
	}
	m_end = this;
}
CAndroidWebWidget::~CAndroidWebWidget()
{
	jvalue val;
	m_pParent->callJavaMethod(val, "webview_destroy", 'Z', "I", m_hIndex);

	if(m_prev) {
		m_prev->m_next = m_next;
	} else {
		m_begin = m_next;
	}
	if(m_next) {
		m_next->m_prev = m_prev;
	} else {
		m_end = m_prev;
	}
}

bool
CAndroidWebWidget::create(IWidget::CONTROL type, int id, const char * caption,
							int x, int y, int width, int height,
							const char * token, const char * region, const char * client,
							const char * consumerKey, const char * applicationId, const char * userID)
{
	jvalue jval;
	int hIndex = -1;
	bool nojump = false;
	m_id = id;

	switch(type)
	{
	default:
		return false;

	case WEBNOJUMP:
		nojump = true;
	case WEBVIEW:
		m_pParent->logging("WebView create!");
		m_pParent->callJavaMethod(jval, "webview_create", 'I', "IIIISSSSSSSZ",
				x, y, width, height,
				caption, token, region, client, consumerKey, applicationId, userID, nojump);
		hIndex = jval.i;

		// 背景色設定
		m_pParent->callJavaMethod(jval, "webview_setColor", 'V', "III", hIndex, m_bgalpha, m_bgcolor);

		// ズーム設定
		m_pParent->callJavaMethod(jval, "webview_setZoom", 'V', "IZ", m_hIndex, m_bZoom);

		m_pParent->logging("Create finished.: handle = %d", hIndex);
		break;
	}

	if(hIndex < 0) return false;

	return init(hIndex, id, x, y, width, height);
}

void
CAndroidWebWidget::cmd(int cmd, ...)
{
	va_list ap;
	va_start(ap, cmd);
	switch (cmd) {
		case WEB_SET_SCALESPAGETOFIT:
		{
			int pagetofit = va_arg(ap, int);
			m_bZoom = (pagetofit) ? true : false;
			jvalue jval;
			m_pParent->callJavaMethod(jval, "webview_setZoom", 'V', "IZ", m_hIndex, m_bZoom);
			break;
		}

		case WEB_BGCOLOR_NORMAL:    // WebViewの背景色の設定
		{
			unsigned int bgalpha = va_arg(ap, unsigned int);
			unsigned int bgcolor = va_arg(ap, unsigned int);

			m_bgalpha = bgalpha;
			m_bgcolor = bgcolor;
			jvalue jval;
			m_pParent->callJavaMethod(jval, "webview_setColor", 'V', "III", m_hIndex, m_bgalpha, m_bgcolor);
			break;
		}
		default:
			break;
	}
}

void
CAndroidWebWidget::update()
{
	jvalue jval;
	m_pParent->callJavaMethod(jval, "webview_update", 'V', "IIIIIZZ",
							m_hIndex, m_x, m_y, m_width, m_height, m_bEnable, m_bVisible);

}

int
CAndroidWebWidget::getTextLength()
{
	jvalue jval;
	m_pParent->callJavaMethod(jval, "webview_getText", 'S', "I", m_hIndex);
	jstring jstr = (jstring)jval.l;
	return CJNI::getJNIEnv()->GetStringLength(jstr);
}

bool
CAndroidWebWidget::getText(char * pBuf, int maxlen)
{
	jvalue jval;
	m_pParent->callJavaMethod(jval, "webview_getText", 'S', "I", m_hIndex);
	const char * str = CJNI::getJNIEnv()->GetStringUTFChars((jstring)jval.l, 0);

	int i = 0;
	for(i = 0; str[i] && i < maxlen - 1; i++) pBuf[i] = str[i];
	pBuf[i] = 0;

	CJNI::getJNIEnv()->ReleaseStringUTFChars((jstring)jval.l, str);
	return true;
}

int
CAndroidWebWidget::getTmpTextLength()
{
	jvalue jval;
	m_pParent->callJavaMethod(jval, "webview_getTmpText", 'S', "I", m_hIndex);
	jstring jstr = (jstring)jval.l;

	return CJNI::getJNIEnv()->GetStringUTFLength(jstr);
}

bool
CAndroidWebWidget::getTmpText(char * pBuf, int maxlen)
{
	jvalue jval;
	m_pParent->callJavaMethod(jval, "webview_getTmpText", 'S', "I", m_hIndex);
	const char * str = CJNI::getJNIEnv()->GetStringUTFChars((jstring)jval.l, 0);

	int i = 0;
	for(i = 0; str[i] && i < maxlen - 1; i++) pBuf[i] = str[i];
	pBuf[i] = 0;

	CJNI::getJNIEnv()->ReleaseStringUTFChars((jstring)jval.l, str);
	return true;
}

bool
CAndroidWebWidget::setText(const char * string)
{
	jvalue jval;
	m_pParent->callJavaMethod(jval, "webview_setText", 'Z', "IS", m_hIndex, string);
	return (bool)jval.z;
}

void
CAndroidWebWidget::set_move(int x,int y,int width,int height)
{
	jvalue jval;
	m_pParent->callJavaMethod(jval, "webview_update", 'V', "IIIIIZZ",
							m_hIndex, m_x, m_y, m_width, m_height, m_bEnable, m_bVisible);
}

CAndroidWebWidget*
CAndroidWebWidget::get_webViewItem(jobject _obj)
{
	jmethodID methodID = 0;
	jclass cls_pfif = CJNI::getJNIEnv()->FindClass(JNI_LOAD_PATH);
	methodID = CJNI::getJNIEnv()->GetStaticMethodID(cls_pfif, "webview_getWebViewItem", "(Landroid/webkit/WebView;)I");
	jint ret = CJNI::getJNIEnv()->CallStaticIntMethod(cls_pfif, methodID, _obj);

	CAndroidWebWidget* pWeb = m_begin;
	for( ; pWeb; pWeb = pWeb->m_next )
	{
		if( pWeb->m_hIndex >= 0 && pWeb->m_hIndex == (int)ret ) {
			break;
		}
	}

	CJNI::getJNIEnv()->DeleteLocalRef(cls_pfif);
	return pWeb;
}

/////////////////////////////////////////////
// CAndroidMovieWidget
/////////////////////////////////////////////
CAndroidMovieWidget	*	CAndroidMovieWidget::m_begin = 0;
CAndroidMovieWidget	*	CAndroidMovieWidget::m_end = 0;
CAndroidMovieWidget::CAndroidMovieWidget(CAndroidRequest * pParent)
: CAndroidWidget(pParent)
, m_asset(0)
, m_prev(0)
, m_next(0)
, m_status(0)
{
	m_prev = m_end;
	if(m_prev) {
		m_prev->m_next = this;
	} else {
		m_begin = this;
	}
	m_end = this;
}
CAndroidMovieWidget::~CAndroidMovieWidget()
{
	jvalue val;
	m_pParent->callJavaMethod(val, "movieview_destroy", 'Z', "I", m_hIndex);

	if(m_prev) {
		m_prev->m_next = m_next;
	} else {
		m_begin = m_next;
	}
	if(m_next) {
		m_next->m_prev = m_prev;
	} else {
		m_end = m_prev;
	}
}

bool
CAndroidMovieWidget::create(IWidget::CONTROL type, int id, const char * caption,
							int x, int y, int width, int height)
{
	jvalue jval;
	int hIndex = -1;
	m_id = id;
	m_status = 0;

	switch(type)
	{
	default:
		return false;

	case MOVIEPLAYER:
		m_pParent->logging("MovieView create!");
		int len = strlen(caption);
		char * buf = new char [ len + 1 ];
		strcpy(buf, caption);
		m_asset = buf;
		CAndroidPathConv& pathconv = CAndroidPathConv::getInstance();
		const char * fullpath = pathconv.fullpath(caption);

		m_pParent->callJavaMethod(jval, "movieview_create", 'I', "IIIISZ",
				x, y, width, height, fullpath, true);
		hIndex = jval.i;
		m_pParent->logging("Create finished.: handle = %d", hIndex);
		break;
	}
	if(hIndex < 0) return false;
	return init(hIndex, id, x, y, width, height);
}

void
CAndroidMovieWidget::update()
{
	jvalue jval;
	m_pParent->callJavaMethod(jval, "movieview_update", 'V', "IIIIIZZ",
							m_hIndex, m_x, m_y, m_width, m_height, m_bEnable, m_bVisible);

}

int
CAndroidMovieWidget::getTextLength()
{
	int len = strlen(m_asset);
	return len;
}

bool
CAndroidMovieWidget::getText(char * pBuf, int maxlen)
{
	int i = 0;
	for(i = 0; m_asset[i] && i < maxlen - 1; i++) pBuf[i] = m_asset[i];
	pBuf[i] = 0;
	return true;
}

bool
CAndroidMovieWidget::setText(const char * string)
{
	int len = strlen(string);
	char * buf = new char [ len + 1 ];
	if(!buf) return false;
	strcpy(buf, string);
	if(m_asset) delete [] m_asset;
	m_asset = buf;

	CAndroidPathConv& pathconv = CAndroidPathConv::getInstance();
	const char * fullpath = pathconv.fullpath(string);

	jvalue jval;
	m_pParent->callJavaMethod(jval, "movieview_setText", 'Z', "IS", m_hIndex, fullpath);
	return (bool)jval.z;
}

void
CAndroidMovieWidget::cmd(int cmd, ...)
{
	jvalue jval;
	if(cmd == IWidget::MV_PLAY) m_status = 0;
	m_pParent->callJavaMethod(jval, "movieview_cmd", 'V', "II", m_hIndex, cmd);
}

CAndroidMovieWidget *
CAndroidMovieWidget::getWidget(int index)
{
	CAndroidMovieWidget * pWidget = m_begin;
	while(pWidget) {
		if(pWidget->m_hIndex == index) break;
		pWidget = pWidget->m_next;
	}
	return pWidget;
}

int
CAndroidMovieWidget::status()
{
	return m_status;
}


void
CAndroidMovieWidget::set_move(int x,int y,int width,int height)
{
	jvalue jval;
	m_pParent->callJavaMethod(jval, "movieview_update", 'V', "IIIIIZZ",
							m_hIndex, m_x, m_y, m_width, m_height, m_bEnable, m_bVisible);
}


CAndroidActivityIndicator	*	CAndroidActivityIndicator::m_begin = 0;
CAndroidActivityIndicator	*	CAndroidActivityIndicator::m_end = 0;

CAndroidActivityIndicator::CAndroidActivityIndicator(CAndroidRequest * pParent)
: CAndroidWidget(pParent), m_prev(0), m_next(0)
{
    m_bVisible = false;
    m_status = 0;
    m_size = 0.0f;

	m_prev = m_end;
	if(m_prev) {
		m_prev->m_next = this;
	} else {
		m_begin = this;
	}
	m_end = this;
}
CAndroidActivityIndicator::~CAndroidActivityIndicator()
{
    jvalue jval;
    m_pParent->callJavaMethod(jval, "indicator_destroy", 'Z', "I",0);

	if(m_prev) {
		m_prev->m_next = m_next;
	} else {
		m_begin = m_next;
	}
	if(m_next) {
		m_next->m_prev = m_prev;
	} else {
		m_end = m_prev;
	}
}

bool
CAndroidActivityIndicator::create(IWidget::CONTROL type, int id, const char * caption,
							int x, int y, int width, int height)
{
	jvalue jval;
	int hIndex = -1;
	m_id = id;

	switch(type)
	{
	default:
		return false;

	case ACTIVITYINDICATOR:
		m_pParent->logging("Indicator create!");

        m_pParent->callJavaMethod(jval, "indicator_create", 'I', "IIIIZ",x, y, width, height, true);
		m_pParent->logging("Indicator Create finished.");
		break;
	}
	return init(hIndex, id, x, y, width, height);
}

void
CAndroidActivityIndicator::set_move(int x, int y, int width, int height)
{
	m_pParent->logging("Indicator set move");
    jvalue jval;
	m_pParent->callJavaMethod(jval, "indicator_update", 'V', "IIIIIZZ",
							m_hIndex, x, y, width, height, m_bEnable, m_bVisible);
}

void
CAndroidActivityIndicator::update()
{
}

int
CAndroidActivityIndicator::getTextLength()
{
	return 0;
}

bool
CAndroidActivityIndicator::getText(char * pBuf, int maxlen)
{
	pBuf[0] = 0;
	return true;
}

bool
CAndroidActivityIndicator::setText(const char * string)
{
	return (bool)true;
}

void
CAndroidActivityIndicator::cmd(int cmd, ...)
{
	m_pParent->logging("Indicator cmd");

    va_list ap;
    va_start(ap,cmd);
    switch( cmd )
    {
    case ACT_STARTANIM:
    case ACT_STOPANIM:
    default:
        break;

    case ACT_SET_STYLE:
        {
            int style = va_arg(ap,int);
            m_size = 21.0f;
            switch( style )
            {
            case 0:
            case 1:
            case 2:
                m_size = 36.0f;
                break;
            default:
                break;
            }
        }
        break;
    }

    va_end(ap);

}

int
CAndroidActivityIndicator::status()
{
	return 0;
}

void
CAndroidActivityIndicator::visible(bool bVisible)
{
	m_pParent->logging("Indicator visible");
    //    m_bVisible = bVisible;
}
