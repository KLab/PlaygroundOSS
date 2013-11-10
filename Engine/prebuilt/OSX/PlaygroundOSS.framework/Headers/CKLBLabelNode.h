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
#ifndef __CKLB_LABELNODE__
#define __CKLB_LABELNODE__

#include "CKLBUISystem.h"
#include "CKLBNodeVirtualDocument.h"

/*!
* \class CKLBLabelNode
* \brief Text Specialized Node Class
* 
* CKLBLabelNode is a text specialized Node for Scene Graph.
* It provides methods to modify the apparence of the text label.
*/
class CKLBLabelNode : public CKLBUIElement {
public:
	CKLBLabelNode(int fontsize, const char * fontname = 0, const char * text = 0);
	~CKLBLabelNode();

	// KLBObject::
	virtual
	u32		getClassID			()					{ return CLS_KLBLABEL; }

	// KLBNode::
	virtual		
	void	recomputeCustom		();

	//
	//	Can interact with selection or not.
	//
	// virtual	void setEnabled		(bool isEnabled);

	virtual bool isSelectable   ()  { return true; }
	virtual void setAsset		(CKLBAsset*	pAsset, ASSET_TYPE mode);
	virtual	bool processAction	(CKLBAction* pAction);

	void		lock			(bool stop);
	void		setAlign		(u32 align);
	void		setText			(const char* text);
	const char*	getText			();

	void		setTextColor	(u32 color);
	void		setWidth		(u32 width);
	void		setHeight		(u32 heigth);
	u32			getWidth		()	{ return m_width;	}
	u32			getHeight		()	{ return m_height;	}
	bool		setFont			(int fontsize, const char * fontname);   

	void		setUseTextSize	(bool autoSize);
	void		setPriority		(u32 renderPriority);

	void		forceRefresh	()  { m_pLabel->forceRefresh(); }

	static bool setDefaultFont  (const char * fontname = 0);
	static void release         ();

protected:
	// virtual void setUpperEnabled(bool isEnabled);

	//
	// Visible / Invisible related.
	//
	// virtual void	addRender			();
	// virtual void	removeRender		();

	const char * m_fontname;
	int          m_fontsize;
	CKLBNodeVirtualDocument	*	m_pLabel;

	u32		m_width;
	u32		m_height;

	u32		m_color;

	char	*	m_textBuf;
	size_t		m_textLen;

	u32		m_align;
	float	m_tx;
	float	m_ty;
	float	m_alignX;
	float	m_alignY;
	u8		m_format;
	bool	m_lock;
	bool	m_changed;
	bool	m_useTextSize;

private:

	void updateLabel();

	static const char * ms_default_font;
};

#endif
