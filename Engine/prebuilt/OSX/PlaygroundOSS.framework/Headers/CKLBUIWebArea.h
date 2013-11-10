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
#ifndef CKLBUIWebArea_h
#define CKLBUIWebArea_h

#include "CKLBUITask.h"
#include "CKLBWebViewNode.h"

/*!
* \class CKLBUIWebArea
* \brief Web Area Task Class
* 
* CKLBUIWebArea is used to create a web viewer area.
*/
class CKLBUIWebArea : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIWebArea>;
private:
	CKLBUIWebArea();
	virtual ~CKLBUIWebArea();
public:
	static CKLBUIWebArea * create(CKLBUITask * pParent, CKLBNode * pNode,
									bool mode, float x, float y,
									float width, float height,
									const char * url, const char * callback);

	u32 getClassID  ();
	bool initUI     (CLuaState& lua);
	int commandUI   (CLuaState& lua, int argc, int cmd);

	void execute(u32 deltaT);
	void dieUI  ();

	inline s32  getWidth()          { return m_width; }
	inline void setWidth(s32 width) {
		if (width != m_width) {
			m_width = width;
			m_pWebView->setWidth(width);
		}
	}

	inline s32  getHeight()             { return m_height; }
	inline void setHeight(s32 height)   {
		if (height != m_height) {
			m_height = height;
			m_pWebView->setHeight(height);
		}
	}

	inline const char*  getText()                   {	return m_text; }
	inline void         setText(const char* text)   {
		setStrC(m_text, text);
		m_pWebView->setText(text);
	}
	
	inline void setScalesPageToFit(bool b)			{ m_pWebView->setScalesPageToFit(b);	}

	inline void setBgColor(u32 alpha, u32 color)	{ m_pWebView->setBgColor(alpha, color); }

private:
	const char*	m_text;
	s32			m_width;
	s32			m_height;

	bool init(CKLBUITask * pParent, CKLBNode * pNode,
			  bool mode, float x, float y,
			  float width, float height,
			  const char * url, const char * callback);

	bool initCore(
				bool mode, float x, float y,
				float width, float height,
				const char * url, const char * callback);

	CKLBUIWebView	*	m_pWebView;

    const char      *   m_cmdCallback;
    
	static PROP_V2      ms_propItems[];
};

#endif // CKLBUIWebArea_h
