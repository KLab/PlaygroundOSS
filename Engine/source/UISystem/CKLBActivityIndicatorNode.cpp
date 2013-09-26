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
//
//  CKLBActivityIndicatorNode.cpp
//  GameEngine
//
//
//

#include "CKLBActivityIndicatorNode.h"
#include "CPFInterface.h"

#include "CKLBLanguageDatabase.h"
#include "CKLBDrawTask.h"

CKLBActivityIndicatorNode::CKLBActivityIndicatorNode(int show_type)
:nativeInputItem	(NULL)
,m_width			(0)
,m_height			(0)
,m_tx				(0)
,m_ty				(0)
{
	//
	//
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	IWidget::CONTROL control = IWidget::ACTIVITYINDICATOR;
	nativeInputItem = pForm.createControl(control , 0, "", 0, 0, 0, 0);
    
	klb_assert(nativeInputItem, "ActivityIndicator allocation failed");
    
    nativeInputItem->cmd(IWidget::ACT_SET_STYLE, show_type);
}

CKLBActivityIndicatorNode::~CKLBActivityIndicatorNode() {
	// Call Interface to release the input box
    
	if (nativeInputItem) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		pForm.destroyControl(nativeInputItem);
		nativeInputItem = NULL;
	}
}

/*virtual*/
void CKLBActivityIndicatorNode::recomputeCustom() {
	if (nativeInputItem) {
		const SMatrix2D* pMat = &m_composedMatrix;
        
		s32 x = (s32)pMat->m_matrix[MAT_TX];
		s32 y = (s32)pMat->m_matrix[MAT_TY];
        
		if ((m_tx != x) || (m_ty != y)) {
            
			int px, py;
			CKLBDrawResource& draw = CKLBDrawResource::getInstance();
            
			m_tx = x;
			m_ty = y;
            
			draw.toPhisicalPosition(x, y, px, py);
			nativeInputItem->move(px, py);
		}
	}
}

void CKLBActivityIndicatorNode::setWidth	(u32 width) {
	if (nativeInputItem && (width != m_width)) {
		CKLBDrawResource& draw = CKLBDrawResource::getInstance();
		int pw, ph;
        
		m_width = width;
        
		draw.toPhisicalSize(m_width, m_height, pw, ph);
		nativeInputItem->resize(pw, ph);
	}
}

void CKLBActivityIndicatorNode::setHeight	(u32 height) {
	if (nativeInputItem && (height != m_height)) {
		CKLBDrawResource& draw = CKLBDrawResource::getInstance();
		int pw, ph;
        
		m_height = height;
        
		draw.toPhisicalSize(m_width, m_height, pw, ph);
		nativeInputItem->resize(pw, ph);
	}
}

/*virtual*/
void CKLBActivityIndicatorNode::setEnabled(bool isEnabled) {
	CKLBUIElement::setEnabled(isEnabled);
    
	if (this->isEnabled()) {
		nativeInputItem->enable(true);
	} else {
		nativeInputItem->enable(false);
	}
}

/*virtual*/
void CKLBActivityIndicatorNode::setUpperEnabled(bool isEnabled) {
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
void CKLBActivityIndicatorNode::addRender() {
	CKLBUIElement::addRender();
	if (nativeInputItem) {
		nativeInputItem->visible(true);
	}
}

/*virtual*/
void CKLBActivityIndicatorNode::removeRender() {
	CKLBUIElement::removeRender();
	if (nativeInputItem) {
		nativeInputItem->visible(false);
	}
}

/*virtual*/
void CKLBActivityIndicatorNode::setAsset(CKLBAsset* /*pAsset*/, ASSET_TYPE /*mode*/) {
	// Do nothing, no asset display.
}

/*virtual*/
bool CKLBActivityIndicatorNode::processAction	(CKLBAction* /*pAction*/) {
	// Do nothing for now, may implement call back.
	return false;
}

void CKLBActivityIndicatorNode::setText(const char* text) {
	if (nativeInputItem) {
		text = CKLBLanguageDatabase::getInstance().getString(text);
		nativeInputItem->setText(text);
	}
}

const char*	CKLBActivityIndicatorNode::getText() {
	return NULL;
}
