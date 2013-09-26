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
#include "CKLBLabelNode.h"

#include "CPFInterface.h"

#include "CKLBLanguageDatabase.h"

const char * CKLBLabelNode::ms_default_font = NULL;

bool
CKLBLabelNode::setDefaultFont(const char * fontname)
{
	char * name = NULL;
	if(fontname) {
		name = KLBNEWA(char, strlen(fontname) + 1);
		strcpy(name, fontname);
		if(!name) return false;
	}
	KLBDELETEA(ms_default_font);
	ms_default_font = (const char *)name;
	return true;
}

void
CKLBLabelNode::release()
{
	KLBDELETEA(ms_default_font);
	ms_default_font = NULL;	// 2012.12.11  Reboot時に値が残ったままになり。↑のsetDefaultFont()で変なアドレスが解放される
}

CKLBLabelNode::CKLBLabelNode(int fontsize, const char * fontname, const char * text)
:m_pLabel			(NULL)
,m_fontname			(NULL)
,m_fontsize			(-1)
,m_width			(0)
,m_height			(0)
,m_textLen			(0)
,m_textBuf			(NULL)
,m_align			(0)
,m_alignX			(0.0f)
,m_alignY			(0.0f)
,m_tx				(0.0f)
,m_ty				(0.0f)
,m_lock				(false)
,m_changed			(false)
,m_useTextSize		(true)	// Must be true by default.
{
	// klb_assert(m_pLabel, "could not create label.");
	lock(true);
	setFont	(fontsize, fontname);
	setText	((char *)text);
	// Trick : do not force creation of object here.
	m_lock		= false;
	m_changed	= false;
	m_format	= TexturePacker::getCurrentModeTexture();
}

CKLBLabelNode::~CKLBLabelNode() {
	// 
	KLBDELETE(m_pLabel);

	// Call Interface to release the input box
	KLBDELETEA(m_textBuf);

	KLBDELETEA(m_fontname);
}

/*virtual*/	
void CKLBLabelNode::recomputeCustom() {
	CKLBUIElement::recomputeCustom();
}

/*virtual*/
void CKLBLabelNode::setAsset(CKLBAsset* /*pAsset*/, ASSET_TYPE /*mode*/) {
	// Do nothing, no asset display.
}

/*virtual*/
bool CKLBLabelNode::processAction	(CKLBAction* /*pAction*/) {
	// Do nothing for now, may implement call back.
	return false;
}

void CKLBLabelNode::lock		(bool stop) {
	if (stop != m_lock) {
		if (!stop) {
			if (m_changed) {
				updateLabel();
				m_changed = false;
			}
		}
		m_lock = stop;
	}
}

bool CKLBLabelNode::setFont		(int fontsize, const char * fontname) {
	if(!fontname) fontname = ms_default_font;
	bool allow = (fontsize != m_fontsize);
	if (fontname) {
		if (m_fontname) {
			allow |= (strcmp(m_fontname, fontname) != 0);
		}

		if (allow) {
			char * buf = KLBNEWA(char, strlen(fontname) + 1);
			if (buf) {
				KLBDELETEA(m_fontname);
				strcpy(buf, fontname);
				m_fontname = (const char *)buf;
				m_fontsize = fontsize;
				if (!m_lock) { updateLabel(); } else { m_changed = true; }
				return true;
			} else {
				return false;
			}
		} else {
			// No changes
			return true;
		}
	} else {
		if (m_fontname) {
			KLBDELETEA(m_fontname);
			allow = true;
		}

		if (allow) {
			m_fontname = NULL;
			m_fontsize = fontsize;
			if (!m_lock) { updateLabel(); } else { m_changed = true; }
		}
		return true;
	}
}

void CKLBLabelNode::setWidth	(u32 width) {
	if (width != m_width) {
		m_width = width;
		if (!m_lock) { updateLabel(); } else { m_changed = true; }
	}
}

void CKLBLabelNode::setHeight	(u32 height) {
	if (height != m_height) {
		m_height = height;
		if (!m_lock) { updateLabel(); } else { m_changed = true; }
	}
}

void CKLBLabelNode::setAlign(u32 align) {
	if (align != m_align) {
		m_align = align;
		if (!m_lock) { updateLabel(); } else { m_changed = true; }
	}
}

void CKLBLabelNode::setTextColor(u32 color) {
	if (color != m_color) {
		m_color = color;
		if (!m_lock) { updateLabel(); } else { m_changed = true; }
	}
}

void CKLBLabelNode::setText(const char* text) {
	if (text) {
		text = CKLBLanguageDatabase::getInstance().getString(text);
		size_t len = strlen(text);
		bool allow = len != m_textLen;
		
		if (m_textBuf) {
			allow |= (strcmp(text, m_textBuf) != 0);
		} else {
			allow = true;
		}

		if (allow) {
			KLBDELETEA(m_textBuf);
			m_textBuf = KLBNEWA(char, len + 1);
			m_textLen = len;

			strcpy(m_textBuf, text);
			if (!m_lock) {
				updateLabel();
			} else {
				m_changed = true;
			}
		}
	}
}

const char*	CKLBLabelNode::getText() {
	return m_textBuf;
}

void CKLBLabelNode::setUseTextSize(bool autoSize) {
	m_useTextSize = autoSize;
}

void CKLBLabelNode::updateLabel()
{
	if(!m_textBuf || ((!m_width || !m_height) && !m_useTextSize)) {
		KLBDELETE(m_pLabel);
		m_pLabel = NULL;
		return;
	}

	// 本来VDocは動作中にプロパティを変更するような作りになっていないため、
	// プロパティ変更が生じたときは改めて VDOCを作り直す。
	if (!m_pLabel) {
		CKLBNodeVirtualDocument * pNewNode = KLBNEW(CKLBNodeVirtualDocument);
		if(!pNewNode) return;

		if(m_pLabel) KLBDELETE(m_pLabel);
		m_pLabel = pNewNode;

		this->addNode(m_pLabel);
	}

	// 描画コマンド数は固定。文字列一つだけの表示なので。
	m_pLabel->createDocument(1,m_format);

	IPlatformRequest& pForm = CPFInterface::getInstance().platform();


	// 指定されている文字列とフォント、フォントサイズでの表示に必要な幅と高さを取得する。
	void * pFont = pForm.getFont(m_fontsize, m_fontname);
	STextInfo txinfo;
	pForm.getTextInfo(m_textBuf ? m_textBuf : " ",pFont, &txinfo);

	// CKLBLabelNode の場合は、実際に文字列描画が必要とする面積がどうあれ、
	// 指定された幅と高さで VirtualDocumentを生成する
	u32 width	= m_useTextSize ? txinfo.width  : m_width;
	u32 height	= m_useTextSize ? txinfo.height : m_height;

	m_pLabel->setDocumentSize(width, height);

	float x;
	float y;

	// X align
	switch(m_align & 3) {
	default:
	case 0:	x = 0.0f;						break;
	case 1: x = -(txinfo.width / 2.0f);		break;
	case 2: x = -txinfo.width;				break;
	}

	// Y align
	switch(m_align >> 2) {
	default:
	case 0:	y = 0.0f;						break;
	case 1: y = -(txinfo.height / 2.0f);	break;
	case 2: y = -txinfo.height;				break;
	}

	m_alignX = x;
	m_alignY = y;

	m_pLabel->setViewPortSize(width, height, x, y,m_renderPrio, false);

	// font index = 0 で、指定されている文字列を描画
	m_pLabel->setFont(0, m_fontname, m_fontsize);	// 指定フォントをindex=0に指定
	m_pLabel->clear(0);

	m_pLabel->lockDocument();
	if (m_textBuf) {
		m_pLabel->drawText(0, txinfo.top, m_textBuf, m_color, 0);
	}
	m_pLabel->unlockDocument();

	// Optimize font cache by deleting after.
	pForm.deleteFont(pFont);

	/*
	//
	// Update translation here directly.
	// ----------------------------------
	m_status |= MATRIX_CHANGE;
	markUpTree();
	m_matrix.m_matrix[MAT_TX] = m_tx + m_alignX;
	m_matrix.m_matrix[MAT_TY] = m_ty + m_alignY;
	if (m_matrix.m_type == MATRIX_ID) {
		m_matrix.m_type = MATRIX_T;
	}
	// ----------------------------------

	m_pLabel->setViewPortPos(0, 0);	// ViewPort とDocumentのサイズが同じで、かつ表示位置を(0,0)で固定
	m_pLabel->markUpMatrix();
	*/
	m_status |= MATRIX_CHANGE;
	m_pLabel->setViewPortPos(0, 0);
	m_pLabel->setPriority(m_renderPrio);
	markUpTree();
}

void	CKLBLabelNode::setPriority(u32 renderPriority)
{
	m_renderPrio = renderPriority;
	if(m_pLabel) m_pLabel->setPriority(renderPriority);
}

/*
void CKLBLabelNode::setTranslateVirtual	(float x, float y)  {
	// --> Not possible anymore : if ((x != m_matrix.m_matrix[MAT_TX]) || (y != m_matrix.m_matrix[MAT_TY])) {

	m_status |= MATRIX_CHANGE;
	markUpTree();
	m_tx = x;
	m_ty = y;
	m_matrix.m_matrix[MAT_TX] = m_tx + m_alignX;
	m_matrix.m_matrix[MAT_TY] = m_ty + m_alignY;
	if (m_matrix.m_type == MATRIX_ID) {
		m_matrix.m_type = MATRIX_T;
	}

	// }
}
*/
