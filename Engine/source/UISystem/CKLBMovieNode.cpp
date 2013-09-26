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

#include "CKLBMovieNode.h"

#include "CPFInterface.h"

#include "CKLBDrawTask.h"

CKLBMovieNode::CKLBMovieNode(const char * path, bool background)
:nativeInputItem	(NULL)
,m_width			(0)
,m_height			(0)
,m_tx				(0)
,m_ty				(0)
,m_textLen			(0)
,m_textBuf			(0)
{
	//
	//
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
    IWidget::CONTROL type = (background) ? IWidget::BGMOVIEPLAYER : IWidget::MOVIEPLAYER;
	CKLBDrawResource& draw = CKLBDrawResource::getInstance();
	int px,py;
	draw.toPhisicalPosition(m_tx, m_ty, px, py);	// OSコントロールの配置は物理座標系で行う
	nativeInputItem = pForm.createControl(type, 0, path, px, py, 0, 0);
	if (nativeInputItem) {
		nativeInputItem->visible(false);
	}

	klb_assert(nativeInputItem, "MoviePlayer allocation failed");
}

CKLBMovieNode::~CKLBMovieNode() {
	// Call Interface to release the input box

	if (nativeInputItem) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		pForm.destroyControl(nativeInputItem);
		nativeInputItem = NULL;
	}
	KLBDELETEA(m_textBuf);
}

/*virtual*/	
void CKLBMovieNode::recomputeCustom() {
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

		// OSコントロールの配置は物理座標系で行う
		draw.toPhisicalPosition(x, y, px, py);	
		draw.toPhisicalSize(transWidth, transHeight, width, height);
		nativeInputItem->move(px, py);
		nativeInputItem->resize(width, height);
	}
}

void CKLBMovieNode::setWidth	(u32 width) {
	if (nativeInputItem && (width != m_width)) {
		m_width = width;
		this->markUpMatrix(); // Force recomputeCustom()
	}
}

void CKLBMovieNode::setHeight	(u32 height) {
	if (nativeInputItem && (height != m_height)) {
		m_height = height;
		this->markUpMatrix(); // Force recomputeCustom()
	}
}

/*virtual*/
void CKLBMovieNode::setEnabled(bool isEnabled) {
//	IPlatformRequest& pForm = CPFInterface::getInstance().platform();

	CKLBUIElement::setEnabled(isEnabled);

	if (this->isEnabled()) {
		nativeInputItem->enable(true);
	} else {
		nativeInputItem->enable(false);
	}
}

/*virtual*/
void CKLBMovieNode::setUpperEnabled(bool isEnabled) {
//	IPlatformRequest& pForm = CPFInterface::getInstance().platform();

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
void CKLBMovieNode::addRender() {
	CKLBUIElement::addRender();
	if (nativeInputItem) {
//		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		nativeInputItem->visible(true);
	}
}

/*virtual*/
void CKLBMovieNode::removeRender() {
	CKLBUIElement::removeRender();
	if (nativeInputItem) {
//		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		nativeInputItem->visible(false);
	}
}

/*virtual*/
void CKLBMovieNode::setAsset(CKLBAsset* /*pAsset*/, ASSET_TYPE /*mode*/) {
	// Do nothing, no asset display.
}

/*virtual*/
bool CKLBMovieNode::processAction	(CKLBAction* /*pAction*/) {
	// Do nothing for now, may implement call back.
	return false;
}

void CKLBMovieNode::setText(const char* text) {
	if (nativeInputItem) {
//		IPlatformRequest& pForm = CPFInterface::getInstance().platform();

		nativeInputItem->setText(text);
	}
}

const char*	CKLBMovieNode::getText() {
	if (nativeInputItem) {
//		IPlatformRequest& pForm = CPFInterface::getInstance().platform();

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
CKLBMovieNode::command(IWidget::MOVIECMD cmd)
{
    nativeInputItem->cmd(cmd);
}
