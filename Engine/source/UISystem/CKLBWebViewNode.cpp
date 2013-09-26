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

#include "CKLBWebViewNode.h"

#include "CPFInterface.h"

#include "CKLBDrawTask.h"

CKLBUIWebView::CKLBUIWebView(bool isPageJump, const char * initialURL,
                            const char * token, const char * region, const char * client,
                            const char * consumerKey, const char * applicationId, const char * userID)
: nativeInputItem   (NULL)
, m_width           (0)
, m_height          (0)
, m_tx              (0)
, m_ty              (0)
, m_bgcolor         (0xffffffff)
, m_textLen         (0)
, m_textBuf         (0)
{
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	IWidget::CONTROL control = (isPageJump) ? IWidget::WEBVIEW : IWidget::WEBNOJUMP;
    const char * url = (initialURL) ? initialURL : "";
	CKLBDrawResource& draw = CKLBDrawResource::getInstance();
	int px,py;
	draw.toPhisicalPosition(m_tx, m_ty, px, py);
	nativeInputItem = pForm.createControl(control , 0, url, px, py, 0, 0, token, region, client, consumerKey, applicationId, userID);

	if (nativeInputItem) {
		nativeInputItem->visible(false);
	}

	klb_assert(nativeInputItem, "EditBox allocation failed");
}

CKLBUIWebView::~CKLBUIWebView() 
{
	// Call Interface to release the input box
	if (nativeInputItem) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		pForm.destroyControl(nativeInputItem);
		nativeInputItem = NULL;
	}
	KLBDELETEA(m_textBuf);
}

/*virtual*/	
void 
CKLBUIWebView::recomputeCustom() 
{
	if (nativeInputItem) {
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
CKLBUIWebView::setBgColor(u32 bgalpha, u32 bgcolor)
{
    if (nativeInputItem && (bgcolor != m_bgcolor)) {
		nativeInputItem->cmd(IWidget::WEB_BGCOLOR_NORMAL, bgalpha, bgcolor);
    }
}
 
void 
CKLBUIWebView::setWidth(u32 width) {
	if (nativeInputItem && (width != m_width)) {
		m_width = width;
		this->markUpMatrix(); // Force recomputeCustom()
	}
}

void 
CKLBUIWebView::setHeight(u32 height) 
{
	if (nativeInputItem && (height != m_height)) {
		m_height = height;
		this->markUpMatrix(); // Force recomputeCustom()
	}
}

/*virtual*/
void 
CKLBUIWebView::setEnabled(bool isEnabled) 
{
	CKLBUIElement::setEnabled(isEnabled);
	if (this->isEnabled()) {
		nativeInputItem->enable(true);
	} else {
		nativeInputItem->enable(false);
	}
}

/*virtual*/
void 
CKLBUIWebView::setUpperEnabled(bool isEnabled) 
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
CKLBUIWebView::addRender() 
{
	CKLBUIElement::addRender();
	if (nativeInputItem) {
		nativeInputItem->visible(true);
	}
}

/*virtual*/
void 
CKLBUIWebView::removeRender() 
{
	CKLBUIElement::removeRender();
	if (nativeInputItem) {
		nativeInputItem->visible(false);
	}
}

/*virtual*/
void 
CKLBUIWebView::setAsset(CKLBAsset* /*pAsset*/, ASSET_TYPE /*mode*/) 
{
	// Do nothing, no asset display.
}

/*virtual*/
bool 
CKLBUIWebView::processAction(CKLBAction* /*pAction*/) 
{
	// Do nothing for now, may implement call back.
	return false;
}

void 
CKLBUIWebView::setText(const char* text) 
{
	if (nativeInputItem) {
		nativeInputItem->setText(text);
	}
}

const char*	
CKLBUIWebView::getText() 
{
	if (nativeInputItem) {
		size_t len = nativeInputItem->getTextLength();
		if (!m_textBuf || len > m_textLen) {
			KLBDELETEA(m_textBuf);
			m_textLen = len;
			m_textBuf = KLBNEWA(char, m_textLen + 1);
		}
		nativeInputItem->getText(m_textBuf, m_textLen + 1);
		return m_textBuf;
	}
	return NULL;
}

