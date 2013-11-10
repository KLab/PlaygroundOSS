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
#ifndef __CKLB_UITEXTBOX__
#define __CKLB_UITEXTBOX__

#include "CKLBUISystem.h"

/*!
* \class CKLBUITextBox
* \brief Text Box Specialized Node Class
* 
* CKLBUITextBox is a UITextBox specialized Node.
* It provides methodss to manage a TextBox.
*/
class CKLBUITextBox : public CKLBUIElement {
public:
	CKLBUITextBox(bool isPassword, int maxlen = 0);
	~CKLBUITextBox();

	// KLBObject::
	virtual u32	 getClassID     ()					{ return CLS_KLBTEXTEDIT; }

	// KLBNode::
	virtual	void recomputeCustom();

	//
	//	Can interact with selection or not.
	//
	virtual	void setEnabled		(bool isEnabled);

	virtual bool isSelectable   ()  { return true; }
	virtual void setAsset		(CKLBAsset*	pAsset, ASSET_TYPE mode);
	virtual	bool processAction	(CKLBAction* pAction);

	void		setText			(const char* text);
	const char*	getText			();
    
    void        setFont         (const char* fontname, float fontsize);
    void        setPlaceHolder  (const char* placeholder);
    void        setAlign        (IWidget::TEXTALIGNMENTTYPE _alignType);
    void        setMaxlen       (int maxlen);
	int			getMaxlen		();
    void        setCharType     (IWidget::TEXTCHARTYPE chartype);
    void        setColor        (bool bTouch, u32 foreground, u32 background);
	void		setWidth		(u32 width);
	void		setHeight		(u32 heigth);
	u32			getWidth		()	{ return m_width;	}
	u32			getHeight		()	{ return m_height;	}

    inline IWidget * getWidget  () const { return nativeInputItem; }
    
protected:
	virtual void setUpperEnabled(bool isEnabled);

	//
	// Visible / Invisible related.
	//
	virtual void addRender      ();
	virtual void removeRender   ();

	IWidget *   nativeInputItem;
    void    *   m_pFont;
	u32		    m_width;
	u32		    m_height;
	s32		    m_tx;
	s32		    m_ty;

	char	*	m_textBuf;
	size_t		m_textLen;
};

#endif
