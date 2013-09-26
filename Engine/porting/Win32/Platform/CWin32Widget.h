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
#ifndef CWin32Widget_h
#define CWin32Widget_h

#include <Windows.h>
#include "OSWidget.h"

class CWin32Platform;

class CWin32Widget : public IWidget
{
	friend class CWin32Platform;
protected:
	CWin32Widget(CWin32Platform * pPlatform);
	virtual ~CWin32Widget();

public:

	virtual int  getTextLength	();
	virtual bool getText	(char * pBuf, int maxlen);
	virtual bool setText	(const char * string);
	virtual void move		(int x, int y);
	virtual void resize		(int width, int height);
	virtual void visible	(bool bVisible);
	virtual void enable		(bool bEnable);

	virtual void cmd		(int cmd, ...);
	virtual int  status		();

	// 全てのコントロールを再描画する
	static void ReDrawControls();

	// コントロールに対するイベント処理
	virtual LRESULT msgCommand		(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static  LRESULT ControlCommand	(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	const char* toShiftJIS	(const char * utf8);
	bool		init		(HWND hWnd, int id, int x, int y, int width, int height);
	inline HWND get_hWnd	() const { return m_hWnd; }
	inline CWin32Platform& getPlatform() { return *m_pPlatform; }

	virtual void redraw();

	int					m_uniqId;

//private:

	HWND				m_hWnd;	// HWND control
	int					m_x;
	int					m_y;
	int					m_width;
	int					m_height;
	int					m_id;

	CWin32Widget	*	m_prev;
	CWin32Widget	*	m_next;


	bool				m_bMove;	// 移動/リサイズした際にtrueになる

	bool				m_chgVisible;
	bool				m_bVisible;

	bool				m_chgEnable;
	bool				m_bEnable;

	CWin32Platform	*	m_pPlatform;

	static CWin32Widget * m_pBegin;
	static CWin32Widget * m_pEnd;

	static int			  m_uniqBase;
};


class CWin32TextWidget : public CWin32Widget
{
	friend class CWin32Platform;
private:
	CWin32TextWidget(CWin32Platform * pParent, int maxlen = 0);
	virtual ~CWin32TextWidget();

public:
	bool create(IWidget::CONTROL type, int id, const char * caption,
				int x, int y, int width, int height);

	void cmd(int cmd, ...);

	LRESULT msgCommand(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void redraw		();
	void set_color	();

	const char		*	m_placeholder;
	HFONT				m_hFont;

	bool				m_touched;
	int					m_maxlen;
	unsigned int		m_cols[4];
};

class CWin32WebWidget : public CWin32Widget
{
	friend class CWin32Platform;
private:
	CWin32WebWidget(CWin32Platform * pParent);
	virtual ~CWin32WebWidget();
public:
	bool create(IWidget::CONTROL type, int id, const char * caption,
				int x, int y, int width, int height,
				const char * token, const char * region, const char * client,
				const char * consumerKey, const char * applicationId, const char * userID);

private:
	// void redraw();
};

class CWin32MovieWidget : public CWin32Widget
{
	friend class CWin32Platform;
private:
	CWin32MovieWidget(CWin32Platform * pParent);
	virtual ~CWin32MovieWidget();
public:
	bool create(IWidget::CONTROL type, int id, const char * caption,
				int x, int y, int width, int height);

private:
};

class CWin32ActivityIndicator : public CWin32Widget
{
	friend class CWin32Platform;
private:
	CWin32ActivityIndicator(CWin32Platform * pParent);
	virtual ~CWin32ActivityIndicator();
public:
	bool create(IWidget::CONTROL type, int id, const char * caption,
				int x, int y, int width, int height);

private:
};

#endif // CWin32Widget_h
