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
#include "CWin32Widget.h"
#include "CWin32Platform.h"
#include <ADSIid.h>

CWin32Widget *  CWin32Widget::m_pBegin   = NULL;
CWin32Widget *  CWin32Widget::m_pEnd     = NULL;
int             CWin32Widget::m_uniqBase = 0;

CWin32Widget::CWin32Widget(CWin32Platform * pPlatform)
: m_id      (0)
, m_hWnd    (0)
, m_prev    (NULL)
, m_next    (NULL)
, m_x       (0)
, m_y       (0)
, m_width   (0)
, m_height  (0)
, m_bVisible(true)
, m_bEnable (true)
, m_bMove   (false)
, m_chgVisible  (false)
, m_chgEnable   (false)
, m_pPlatform   (pPlatform)
, m_uniqId      (++m_uniqBase)
{
	// 自身をリンクに追加する
	m_prev = m_pEnd;
	m_pEnd = this;
	if(m_prev) {
		m_prev->m_next = this;
	} else {
		m_pBegin = this;
	}
}

CWin32Widget::~CWin32Widget()
{
	// コントロールを破棄する
	if(m_hWnd) DestroyWindow(m_hWnd);

	// 自身をリンクから外す
	if(m_prev) {
		m_prev->m_next = m_next;
	} else {
		m_pBegin = m_next;
	}
	if(m_next) {
		m_next->m_prev = m_prev;
	} else {
		m_pEnd = m_prev;
	}
}

void
CWin32Widget::cmd(int /*cmd*/, ...)
{
}

int
CWin32Widget::status()
{
	return 0; 
}

bool
CWin32Widget::init(HWND hWnd, int id, int x, int y, int width, int height)
{
	m_id     = id;
	m_hWnd   = hWnd;
	m_x      = x;
	m_y      = y;
	m_width  = width;
	m_height = height;
	return true;
}

int
CWin32Widget::getTextLength()
{
	int length  = GetWindowTextLength(m_hWnd);
	char * pBuf = new char [length + 1];
	GetWindowText(m_hWnd, (LPSTR)pBuf, length + 1);

	// control から取得した文字列は ShiftJISなので、
	// Engineが使用する UTF-8 文字列に変換したものの長さを計測する。
	const char * utf8Str = m_pPlatform->SJIStoUTF8(pBuf);
	length = strlen(utf8Str);
	delete [] utf8Str;
	delete [] pBuf;

	return length;
}

bool
CWin32Widget::getText(char * pBuf, int maxlen)
{
	int result = GetWindowText(m_hWnd, (LPSTR)pBuf, maxlen);
	// 受けた文字列はShiftJISなので、EngineとしてはUTF8に変換する
	const char * utf8Str = m_pPlatform->SJIStoUTF8(pBuf);
	int len = strlen(utf8Str);
	if(len > maxlen) len = maxlen;
	strncpy(pBuf, utf8Str, len);	// utf8に変換したものをバッファにコピー
	pBuf[len] = 0;
	delete [] utf8Str;
	return (!result) ? false : true;
}

bool
CWin32Widget::setText(const char * string)
{
	// 渡された文字列はutf8なので、OSのコントロールに渡す前に ShiftJISに変換する
	const char * sjisStr = m_pPlatform->utf8toSJIS(string);
	int result = SetWindowText(m_hWnd, (LPSTR)sjisStr);
	delete [] sjisStr;
	return (!result) ? false : true;
}

const char *
CWin32Widget::toShiftJIS(const char * utf8)
{
	return m_pPlatform->utf8toSJIS(utf8);
}

void
CWin32Widget::move(int x, int y)
{
	m_x = x;
	m_y = y;
	m_bMove = true;
}

void
CWin32Widget::resize(int width, int height)
{
	m_width  = width;
	m_height = height;
	m_bMove  = true;
}

void
CWin32Widget::visible(bool bVisible)
{
	m_bVisible   = bVisible;
	m_chgVisible = true;
}

void
CWin32Widget::enable(bool bEnable)
{
	m_bEnable   = bEnable;
	m_chgEnable = true;
}

void
CWin32Widget::redraw()

{
    if(!m_hWnd) { return; }

	if(m_chgVisible) {
		m_chgVisible = false;
		ShowWindow(m_hWnd, (m_bVisible) ? SW_SHOW : SW_HIDE);
	}
	if(m_chgEnable) {
		m_chgEnable = false;
		EnableWindow(m_hWnd, (m_bEnable) ? TRUE : FALSE);
	}
	if(m_bMove) {
		m_bMove = false;
		MoveWindow(m_hWnd, m_x, m_y, m_width, m_height, true);
	} else {
		InvalidateRect(m_hWnd, NULL, FALSE);
	}
	RedrawWindow(m_hWnd, NULL, 0, RDW_UPDATENOW);
}

void
CWin32Widget::ReDrawControls()
{
	CWin32Widget * pCtrl = m_pBegin;
	while(pCtrl) {
		pCtrl->redraw();
		pCtrl = pCtrl->m_next;
	}
}

LRESULT
CWin32Widget::msgCommand(HWND /*hWnd*/, UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return 0;
}

LRESULT
CWin32Widget::ControlCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = 0;
	int id = LOWORD(wParam);
	CWin32Widget * pCtrl = m_pBegin;
	while(pCtrl) {
		if(pCtrl->m_uniqId == id) {
			lResult = pCtrl->msgCommand(hWnd, message, wParam, lParam);
			break;
		}
		pCtrl = pCtrl->m_next;
	}
	return lResult;
}


CWin32TextWidget::CWin32TextWidget(CWin32Platform * pParent, int maxlen)
: CWin32Widget  (pParent)
, m_placeholder (NULL)
, m_touched     (false)
, m_maxlen      (maxlen)
, m_hFont       (0)
{
	m_cols[0] = 0xffffffff;
	m_cols[1] = 0xff000000;
	m_cols[2] = 0xffffffff;
	m_cols[3] = 0xff000000;
}
CWin32TextWidget::~CWin32TextWidget()
{
	delete [] m_placeholder;
}

bool
CWin32TextWidget::create(IWidget::CONTROL type, int id, const char * caption,
							int x, int y, int width, int height)
{
	HWND hWnd = 0;

	switch(type)
	{
	default:
		// unknown control.
		return false;
	case TEXTBOX:
		{
			hWnd = CreateWindow(
								TEXT("EDIT"),
								caption,
								WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT,
								x, y, width, height,
								getPlatform().get_hWnd(),
								(HMENU)(INT_PTR)m_uniqId,
								(HINSTANCE)GetModuleHandle(NULL),
								0);
		}
		break;
	case PASSWDBOX:
		{
			hWnd = CreateWindow(TEXT("EDIT"),
								caption,
								WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT|ES_PASSWORD,
								x, y, width, height,
								getPlatform().get_hWnd(),
								(HMENU)(INT_PTR)m_uniqId,
								(HINSTANCE)GetModuleHandle(NULL),
								0);
		}
		break;
	}
    if(m_maxlen > 0) { SendMessage(hWnd, EM_SETLIMITTEXT, (WPARAM)m_maxlen, 0); }

	return init(hWnd, id, x, y, width, height);
}

void
CWin32TextWidget::cmd(int cmd, ...)
{
	va_list ap;
	va_start(ap, cmd);

	switch(cmd)
	{
	case TX_PLACEHOLDER:
		{
			const char * placeholder = va_arg(ap, const char *);
			// 文字列を Shift_JIS に変換
			m_placeholder = toShiftJIS(placeholder);
		}
		break;
	case TX_FONT:
		{
			// フォントオブジェクト取得
			/*
			CWin32Font * fontobj = (CWin32Font *)va_arg(ap, void *);
			HDC hDC = GetDC( get_hWnd() );
			m_hFont = fontobj->get_hFont();
			SelectObject( hDC, m_hFont );
			*/
		}
		break;
	default:
		{
			unsigned int color = va_arg(ap, unsigned int);
			color = (color & 0x00ff00) | ((color&0xff) << 16) | ((color>>16) & 0xff);
			switch(cmd)
			{
			case TX_BGCOLOR_NORMAL: m_cols[0] = color; break;
			case TX_FGCOLOR_NORMAL: m_cols[1] = color; break;
			case TX_BGCOLOR_TOUCH : m_cols[2] = color; break;
			case TX_FGCOLOR_TOUCH : m_cols[3] = color; break;
			}
			set_color();
		}
		break;
	}
	va_end(ap);
}

void
CWin32TextWidget::set_color()
{
	int base = (m_touched) ? 2 : 0;
	unsigned int bg = m_cols[base];
	unsigned int fg = m_cols[base + 1];

	HDC hDC = GetDC( m_hWnd );
	SetTextColor(hDC, fg);
	SetBkColor(hDC, bg);
	ReleaseDC(m_hWnd, hDC);
}

void
CWin32TextWidget::redraw()
{
	CWin32Widget::redraw();

	if(m_placeholder && getTextLength() == 0) {
		RECT rc;
		HDC hDC = GetDC( m_hWnd );
		int savedDC = SaveDC(hDC);

		int base = (m_touched) ? 2 : 0;

		SetTextColor(hDC , 0x999999);
		SetRect( &rc, 0, 0, m_width, m_height );
		DrawText(hDC, m_placeholder, -1, &rc, 0); 
		RestoreDC(hDC, savedDC);
		ReleaseDC( m_hWnd, hDC );
	}
}


LRESULT
CWin32TextWidget::msgCommand(HWND /*hWnd*/, UINT /*message*/, WPARAM wParam, LPARAM /*lParam*/)
{
	int code = HIWORD(wParam);
	switch(code)
	{
	case EN_SETFOCUS:
		m_touched = true;
		set_color();
		break;
	case EN_KILLFOCUS:
		m_touched = false;
		set_color();
		break;
	default:
		break;
	}
	return 0;
}








CWin32WebWidget::CWin32WebWidget(CWin32Platform * pParent) : CWin32Widget(pParent) {}
CWin32WebWidget::~CWin32WebWidget() {}

bool
CWin32WebWidget::create(IWidget::CONTROL type, int id, const char * /*caption*/,
							int x, int y, int width, int height,
							const char * /*token*/, const char * /*region*/, const char * /*client*/,
							const char * /*consumerKey*/, const char * /*applicationId*/, const char * /*userID*/)
{

	HWND hWnd = 0;
	void (*AtlAxWinInit)();
	HRESULT (*AtlAxGetControl)(HWND,IUnknown **);
	HMODULE hAtl = LoadLibrary("atl");
	AtlAxWinInit = (void (*)())GetProcAddress(hAtl ,"AtlAxWinInit");
	AtlAxGetControl = (HRESULT (*)(HWND, IUnknown **))GetProcAddress(hAtl, "AtlAxGetControl");
	AtlAxWinInit();

	switch(type)
	{
	default:
		// unknown control.
		return false;
	case WEBVIEW:
	case WEBNOJUMP:
		{
			hWnd = 0;
			/*
			CreateWindow("AtlAxWin", "Shell.Explorer.2",
								WS_CHILD|WS_VISIBLE, x, y, width, height, 
								getPlatform().get_hWnd(),
								(HMENU)0, (HINSTANCE)GetModuleHandle(NULL), NULL);
//			IUnknown * hUnknown;
//			if(AtlAxGetControl(hWnd, &hUnknown) == S_OK) {
				
//			}
			*/
		}
		break;
	}
	return init(hWnd, id, x, y, width, height);
}




CWin32MovieWidget::CWin32MovieWidget(CWin32Platform * pParent) : CWin32Widget(pParent) {}
CWin32MovieWidget::~CWin32MovieWidget() {}

bool
CWin32MovieWidget::create(IWidget::CONTROL type, int id, const char * /*caption*/,
							int x, int y, int width, int height)
{
	HWND hWnd = 0;

	switch(type)
	{
	default:
		// unknown control.
		return false;
	case MOVIEPLAYER:
		{
			hWnd = 0;
					/*CreateWindow(TEXT("MovieArea"),
								caption,
								WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT,
								x, y, width, height,
								getPlatform().get_hWnd(),
								(HMENU)(INT_PTR)id,
								(HINSTANCE)GetModuleHandle(NULL),
								0);
								*/

		}
		break;
	case BGMOVIEPLAYER:
		{
			hWnd = 0;
		}
		break;
	}
	return init(hWnd, id, x, y, width, height);
}



CWin32ActivityIndicator::CWin32ActivityIndicator(CWin32Platform * pParent) : CWin32Widget(pParent) {}
CWin32ActivityIndicator::~CWin32ActivityIndicator() {}

bool
CWin32ActivityIndicator::create(IWidget::CONTROL type, int id, const char * /*caption*/,
								int x, int y, int width, int height)
{
	HWND hWnd = 0;

	switch(type)
	{
	default:
		// unknown control.
		return false;
	case ACTIVITYINDICATOR:
		{
			hWnd = 0;
					/*CreateWindow(TEXT("MovieArea"),
								caption,
								WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_LEFT,
								x, y, width, height,
								getPlatform().get_hWnd(),
								(HMENU)(INT_PTR)id,
								(HINSTANCE)GetModuleHandle(NULL),
								0);
								*/

		}
		break;
	}
	return init(hWnd, id, x, y, width, height);
}