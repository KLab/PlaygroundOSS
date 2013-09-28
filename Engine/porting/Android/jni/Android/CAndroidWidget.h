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
#ifndef CAndroidWidget_h
#define CAndroidWidget_h

#include "CAndroidRequest.h"
#include "CAndroidFont.h"
#include "OSWidget.h"
#include "jni.h"

class CAndroidRequest;

class CAndroidWidget : public IWidget
{
	friend class CAndroidRequest;
protected:
	CAndroidWidget(CAndroidRequest * pRequest);
	virtual ~CAndroidWidget();

public:
	virtual int getTextLength() = 0;
	virtual bool getText(char * pBuf, int maxlen) = 0;
	virtual bool setText(const char * string) = 0;

	virtual void move(int x, int y);
	virtual void resize(int width, int height);
	virtual void visible(bool bVisible);
	virtual void enable(bool bEnable);

	virtual void cmd(int cmd, ...);
	virtual int status();

	inline int GetIndex() { return m_hIndex; }

protected:
	bool init(int hIndex, int id, int x, int y, int width, int height);
	virtual void update() = 0;

    virtual void set_move(int x,int y,int width,int height) = 0;

	int				m_hIndex;
	int				m_x;
	int				m_y;
	int				m_width;
	int				m_height;
	int				m_id;

	bool			m_bEnable;
	bool			m_bVisible;

	CAndroidRequest	*	m_pParent;
};

class CAndroidTextWidget : public CAndroidWidget
{
	friend class CAndroidRequest;
private:
	CAndroidTextWidget(CAndroidRequest * pParent);
	virtual ~CAndroidTextWidget();
public:
	int getTextLength();
	bool getText(char * pBuf, int maxlen);
	bool setText(const char * string);
	void setMaxlen(int maxlen);
	bool create(IWidget::CONTROL type, int id, const char * caption,
					int x, int y, int width, int height);

	void cmd(int cmd, ...);
private:
	void update();
    void set_move(int x,int y,int width,int height);

    CAndroidTextWidget	*	m_prev;
    CAndroidTextWidget	*	m_next;

	static CAndroidTextWidget	*	m_begin;
	static CAndroidTextWidget	*	m_end;

    CAndroidFont*	m_pFont;
	enum {
		ALIGN_LEFT,
		ALIGN_CENTER,
		ALIGN_RIGHT
	};
};

class CAndroidWebWidget : public CAndroidWidget
{
	friend class CAndroidRequest;
private:
	CAndroidWebWidget(CAndroidRequest * pParent);
	virtual ~CAndroidWebWidget();
public:
	int getTextLength();
	bool getText(char * pBuf, int maxlen);
	int getTmpTextLength();
	bool getTmpText(char * pBuf, int maxlen);
	bool setText(const char * string);

	bool create(IWidget::CONTROL type, int id, const char * caption,
					int x, int y, int width, int height,
					const char * token, const char * region, const char * client,
					const char * consumerKey, const char * applicationId, const char * userID);

	void cmd(int cmd, ...);

	static CAndroidWebWidget* get_webViewItem(jobject _obj);
private:
	void update();
    void set_move(int x,int y,int width,int height);

    bool			m_bZoom;		// ズームの可否
    unsigned int    m_bgalpha;      // 背景色のアルファ値
    unsigned int    m_bgcolor;      // 背景色

    CAndroidWebWidget	*	m_prev;
    CAndroidWebWidget	*	m_next;

    static CAndroidWebWidget	*	m_begin;
   	static CAndroidWebWidget	*	m_end;
};

class CAndroidMovieWidget : public CAndroidWidget
{
	friend class CAndroidRequest;
private:
	CAndroidMovieWidget(CAndroidRequest * pParent);
	virtual ~CAndroidMovieWidget();
public:
	int getTextLength();
	bool getText(char * pBuf, int maxlen);
	bool setText(const char * string);

	bool create(IWidget::CONTROL type, int id, const char * caption,
				int x, int y, int width, int height);

	void cmd(int cmd, ...);
	int status();

	static CAndroidMovieWidget * getWidget(int index);

private:
	void update();
    void set_move(int x,int y,int width,int height);

	const char			*	m_asset;
	int						m_status;
	CAndroidMovieWidget	*	m_prev;
	CAndroidMovieWidget	*	m_next;

	static CAndroidMovieWidget	*	m_begin;
	static CAndroidMovieWidget	*	m_end;
};

class CAndroidActivityIndicator : public CAndroidWidget
{
	friend class CAndroidRequest;
private:
	CAndroidActivityIndicator(CAndroidRequest * pParent);
	virtual ~CAndroidActivityIndicator();
public:
	int getTextLength();
	bool getText(char * pBuf, int maxlen);
	bool setText(const char * string);

	bool create(IWidget::CONTROL type, int id, const char * caption,
				int x, int y, int width, int height);

	void cmd(int cmd, ...);
	int status();

    void visible(bool bVisible);

private:
	void set_move(int x, int y, int width, int height);
    void update();

    bool  m_bVisible;
    int   m_status;
    float m_size;

	CAndroidActivityIndicator	*	m_prev;
	CAndroidActivityIndicator	*	m_next;

	static CAndroidActivityIndicator	*	m_begin;
	static CAndroidActivityIndicator	*	m_end;

};
#endif // CAndroidWidget_h
