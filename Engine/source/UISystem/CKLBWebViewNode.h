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
#ifndef __CKLB_UIWEBVIEW__
#define __CKLB_UIWEBVIEW__

#include "CKLBUISystem.h"

/*!
* \class CKLBUIWebView
* \brief UI Web View Specialized Node Class
* 
* CKLBUIWebView provides methods to manage a Web Viewer.
*/
class CKLBUIWebView : public CKLBUIElement {
public:
	CKLBUIWebView(bool isPageJump, const char * initialURL = NULL,
                  const char * token = NULL, const char * region = NULL, const char * client = NULL,
                  const char * consumerKey = NULL, const char * applicationID = NULL, const char * userID = NULL);
	~CKLBUIWebView();

	// KLBObject::
	virtual u32	getClassID	    ()					{ return CLS_KLBWEBVIEW; }

	// KLBNode::
	virtual	void recomputeCustom();

	//
	//	Can interact with selection or not.
	//
	virtual	void setEnabled		(bool isEnabled);

	virtual bool isSelectable   () { return true; }
	virtual void setAsset		(CKLBAsset*	pAsset, ASSET_TYPE mode);
	virtual	bool processAction	(CKLBAction* pAction);

	void		setText			(const char* text);
	const char*	getText			();
    
    void        setScalesPageToFit(bool scalesPageToFit) {
        nativeInputItem->cmd(IWidget::WEB_SET_SCALESPAGETOFIT, scalesPageToFit);
    }
    
    void        setBgColor      (u32 bgalpha, u32 bgcolor);
	void		setWidth		(u32 width);
	void		setHeight		(u32 heigth);
	u32			getWidth		()	{ return m_width;	}
	u32			getHeight		()	{ return m_height;	}
    
    inline IWidget *   getWidget() const { return nativeInputItem; }

protected:
	virtual void setUpperEnabled(bool isEnabled);

	//
	// Visible / Invisible related.
	//
	virtual void addRender		();
	virtual void removeRender	();

	IWidget *   nativeInputItem;
	u32		    m_width;
	u32		    m_height;
	s32		    m_tx;
	s32		    m_ty;
    u32         m_bgcolor;

	char	*	m_textBuf;
	size_t		m_textLen;
};

#endif
