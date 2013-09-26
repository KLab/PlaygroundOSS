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

#include "CKLBTextInputNode.h"

#include "CPFInterface.h"

#include "CKLBLanguageDatabase.h"
#include "CKLBDrawTask.h"

CKLBUITextBox::CKLBUITextBox(bool isPassword, int maxlen)
: nativeInputItem   (NULL)
, m_pFont           (NULL)
, m_width           (0)
, m_height          (0)
, m_tx              (0)
, m_ty              (0)
, m_textLen         (0)
, m_textBuf         (NULL)
{
	IPlatformRequest& pForm  = CPFInterface::getInstance().platform();
	IWidget::CONTROL control = (isPassword) ? IWidget::PASSWDBOX : IWidget::TEXTBOX;
	CKLBDrawResource& draw   = CKLBDrawResource::getInstance();
	int px,py;
	draw.toPhisicalPosition(m_tx, m_ty, px, py);
	nativeInputItem = pForm.createControl(control , 0, "", px, py, 0, 0, maxlen);
	if(nativeInputItem) {
		nativeInputItem->visible(false);
	}
	klb_assert(nativeInputItem, "EditBox allocation failed");
}

CKLBUITextBox::~CKLBUITextBox() {
	// Call Interface to release the input box

    IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	if(nativeInputItem) {
		pForm.destroyControl(nativeInputItem);
		nativeInputItem = NULL;
	}
    if(m_pFont) {
        pForm.deleteFontSystem(m_pFont);
    }
	KLBDELETEA(m_textBuf);
}

/*virtual*/	
void 
CKLBUITextBox::recomputeCustom() 
{
	if(nativeInputItem) {
		const SMatrix2D* pMat = &m_composedMatrix;

		s32 x = (s32)pMat->m_matrix[MAT_TX];
		s32 y = (s32)pMat->m_matrix[MAT_TY];

		int px, py;
		int width, height;
		CKLBDrawResource& draw = CKLBDrawResource::getInstance();

		m_tx = x;
		m_ty = y;

		int transWidth  = m_width  * pMat->m_matrix[MAT_A];
		int transHeight = m_height * pMat->m_matrix[MAT_D];

		draw.toPhisicalPosition(x, y, px, py);	
		draw.toPhisicalSize(transWidth, transHeight, width, height);
		nativeInputItem->move(px, py);
		nativeInputItem->resize(width, height);
	}
}

void 
CKLBUITextBox::setWidth(u32 width) 
{
	if(nativeInputItem && (width != m_width)) {
		m_width = width;
		this->markUpMatrix(); // Force recomputeCustom()
	}
}

void 
CKLBUITextBox::setHeight(u32 height) 
{
	if(nativeInputItem && (height != m_height)) {
		m_height = height;
		this->markUpMatrix(); // Force recomputeCustom()
	}
}

/*virtual*/
void 
CKLBUITextBox::setEnabled(bool isEnabled) 
{
	CKLBUIElement::setEnabled(isEnabled);

	if(this->isEnabled()) {
		nativeInputItem->enable(true);
	} else {
		nativeInputItem->enable(false);
	}
}

/*virtual*/
void 
CKLBUITextBox::setUpperEnabled(bool isEnabled) 
{
	CKLBUIElement::setUpperEnabled(isEnabled);

	if (this->isEnabled()) {
		nativeInputItem->enable(true);
	} else {
		nativeInputItem->enable(false);
	}
}

//
// Visible / Invisible related.
//
/*virtual*/
void 
CKLBUITextBox::addRender() 
{
	CKLBUIElement::addRender();
	if (nativeInputItem) {
		nativeInputItem->visible(true);
	}
}

/*virtual*/
void 
CKLBUITextBox::removeRender() 
{
	CKLBUIElement::removeRender();
	if (nativeInputItem) {
		nativeInputItem->visible(false);
	}
}

/*virtual*/
void 
CKLBUITextBox::setAsset(CKLBAsset* /*pAsset*/, ASSET_TYPE /*mode*/) 
{
	// Do nothing, no asset display.
}

/*virtual*/
bool 
CKLBUITextBox::processAction(CKLBAction* /*pAction*/) 
{
	// Do nothing for now, may implement call back.
	return false;
}

void 
CKLBUITextBox::setText(const char* text) 
{
	if (nativeInputItem) {
		text = CKLBLanguageDatabase::getInstance().getString(text);
		nativeInputItem->setText(text ? text : "");
	}
}

const char*	
CKLBUITextBox::getText() 
{
	if (nativeInputItem) {
		size_t len = nativeInputItem->getTextLength();
		if(!m_textBuf || len > m_textLen) {
			KLBDELETEA(m_textBuf);
			m_textLen = len;
			m_textBuf = KLBNEWA(char, m_textLen + 1);
		}
		nativeInputItem->getText(m_textBuf, m_textLen + 1);

		return m_textBuf;
	}
	return NULL;
}

void 
CKLBUITextBox::setFont(const char *fontname, float fontsize) 
{
    if(nativeInputItem) {
        IPlatformRequest& pForm = CPFInterface::getInstance().platform();
        if(m_pFont) {
            pForm.deleteFontSystem(m_pFont);
            m_pFont = NULL;
        }
        fontsize = CKLBDrawResource::getInstance().toPhisical(fontsize);
        m_pFont = pForm.getFontSystem(fontsize, fontname);
        nativeInputItem->cmd(IWidget::TX_FONT, m_pFont);
    }
}

void 
CKLBUITextBox::setPlaceHolder(const char *placeholder) 
{
    if(nativeInputItem) {
        placeholder = CKLBLanguageDatabase::getInstance().getString(placeholder);
        nativeInputItem->cmd(IWidget::TX_PLACEHOLDER, placeholder);
    }
}

void 
CKLBUITextBox::setAlign(IWidget::TEXTALIGNMENTTYPE _alignType)
{
    if(nativeInputItem) {
        nativeInputItem->cmd(IWidget::TX_ALIGNMENTTYPE, _alignType);
    }
}

void 
CKLBUITextBox::setColor(bool bTouch, u32 foreground, u32 background) 
{
    if(!nativeInputItem) { return; }
    if(!bTouch) {
        nativeInputItem->cmd(IWidget::TX_BGCOLOR_NORMAL, background);
        nativeInputItem->cmd(IWidget::TX_FGCOLOR_NORMAL, foreground);
    } else {
        nativeInputItem->cmd(IWidget::TX_BGCOLOR_TOUCH, background);
        nativeInputItem->cmd(IWidget::TX_FGCOLOR_TOUCH, foreground);        
    }
}

void 
CKLBUITextBox::setMaxlen(int maxlen)
{
    if(nativeInputItem) {
        nativeInputItem->cmd(IWidget::TX_MAXLEN, maxlen);
    }
}

int 
CKLBUITextBox::getMaxlen()
{
	if(nativeInputItem) {
		return nativeInputItem->getTextMaxLength();
	}
	return 0;
}

void 
CKLBUITextBox::setCharType(IWidget::TEXTCHARTYPE chartype)
{
    if(nativeInputItem) {
        nativeInputItem->cmd(IWidget::TX_CHARTYPE, (int)chartype);
    }
}
