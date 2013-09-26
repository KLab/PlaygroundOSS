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
#include "CKLBScrollBarIF.h"
#include "CKLBDataHandler.h"
#include "CKLBUtility.h"
#include "CKLBLuaEnv.h"
#include "CKLBTouchPad.h"
;
// 共通インデックスバッファ
const u16 CKLBScrollBarIF::ms_indices[] = {
	0, 1, 3,
	1, 2, 3,
	4, 5, 7,
	5, 6, 7,
	8, 9, 11,
    9,10, 11,
};

CKLBScrollMgr::CKLBScrollMgr() 
: m_maxPos      (0)
, m_lenLoop     (0)
, m_data        (NULL)
, m_callback    (NULL)
, m_precallPos  (-1) 
{
}

CKLBScrollMgr::~CKLBScrollMgr()
{
	KLBDELETEA(m_callback);
}

bool
CKLBScrollMgr::setCallback(void * pData, const char * funcname)
{
	m_data = pData;
	const char * name = CKLBUtility::copyString(funcname);
    if(!name) { return false; }
	KLBDELETEA(m_callback);
	m_callback = name;
	return true;
}

void
CKLBScrollMgr::execCallback(int pos)
{
    if(m_precallPos == pos) { return; }
	m_precallPos = pos;

	CKLBScriptEnv::getInstance().call_eventScrollBarStop(m_callback, (CKLBObjectScriptable*)m_data, pos);
}

void
CKLBScrollMgr::setMaxPosition(int pos)
{
	m_maxPos = pos;
}

void
CKLBScrollMgr::setLoopArea(int lenLoop)
{
	m_lenLoop = lenLoop;
}

float
CKLBScrollMgr::loopRound(float pos)
{
    if(!m_lenLoop) { return pos; }
    while(pos < 0.0f)               { pos += (float)m_lenLoop; }
    while(pos >= (float)m_lenLoop)  { pos -= (float)m_lenLoop; }
	return pos;
}

// 2012.11.29  m_callbackの初期化漏れを修正
CKLBScrollBarIF::CKLBScrollBarIF(CKLBLuaTask * pOwner)
: m_pScrMgr     (NULL)
, m_maxPos      (0)
, m_minPos      (0)
, m_barPos      (0)
, m_lastPos     (0)
, m_texHandle   (0)
, m_mode        (0)
, m_first       (true)
, m_bReady      (false)
, m_pNode       (NULL)
, m_pBaseNode   (NULL)
, m_overScroll  (false)
, m_pOwner      (pOwner)
, m_margin_top  (0)
, m_margin_bottom   (0)
, m_minLoop     (0)
, m_maxLoop     (0)
, m_hide_mode   (false)
, m_hide        (false)
, m_timeHide    (0)
, m_bShortHide  (true)
, m_callback    (NULL)
{
}

CKLBScrollBarIF::~CKLBScrollBarIF()
{
    if(m_texHandle) { CKLBDataHandler::releaseHandle(m_texHandle); }
	if(m_callback) {
		KLBDELETEA(m_callback);	// 2012.11.29  解放漏れ修正
		m_callback = NULL;
	}
    if(m_pScrMgr) { KLBDELETE(m_pScrMgr); }
}

bool
CKLBScrollBarIF::init(
		CKLBNode * pNode,
		u32 order, float x, float y, float width, float height,
		s32 minValue, s32 maxValue, s32 pos, const char * image,
		s32 slider_size, s32 min_slider_size, 
		const char * callback,
		u32 colorNormal, u32 colorSelect, bool vert, bool active, bool hide_mode)
{
	// 初期化前にCKLBScrollMgr が登録されている必要がある。
	// 登録されていない場合は初期化失敗。
	if(!m_pScrMgr) {
		klb_assert(m_pScrMgr, "Scroll Manager not found.");
		return false;
	}
	m_x         = (int)x;
	m_y         = (int)y;
	m_width     = (int)width;
	m_height    = (int)height;
	m_vertical  = vert;
	m_hide_mode = hide_mode;

	if(hide_mode) {
		m_hide      = true;
		m_timeHide  = 1300; // 初期はhide状態
	}

	m_col_normal = colorNormal;
	m_col_select = colorSelect;

	m_callback = (callback) ? CKLBUtility::copyString(callback) : NULL;

	// 必要とされるオブジェクトを生成する
	CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();

	// イメージの取得
	const char * imgname    = image;
	const char * asset_name = image;

	{
		const char * scheme[] = {
			"asset://",
			"file://install/",
			"file://external/",
			0
		};
		for(int j = 0; scheme[j]; j++) {
			int len = strlen(scheme[j]);
			if(!strncmp(imgname, scheme[j], len)) {
				imgname += len;
				break;
			}
		}
	}

	CKLBTextureAsset * pTexAsset;
	pTexAsset = (CKLBTextureAsset *)CKLBUtility::loadAssetScript(asset_name, &m_texHandle, 0, true);
	if(!pTexAsset) {
		return false;
	}

	m_pTex = pTexAsset->getImage(imgname);

	m_pDynSprite = pRdrMgr.allocateCommandDynSprite(6*3,6*3); // 三角形6個分のDynamicSprite
	if (!m_pDynSprite) {
		CKLBDataHandler::releaseHandle(m_texHandle);
		return false;
	}

	m_pDynSprite->setTexture(m_pTex);
	m_pDynSprite->changeOrder(pRdrMgr, order);
	m_order = order;

	m_pBaseNode = KLBNEW(CKLBNode);
	m_pBaseNode->setTranslate(0.0f, 0.0f);
	m_pNode = KLBNEW(CKLBNode);
	m_pNode->setRender(m_pDynSprite);
	m_pNode->setRenderOnDestroy(true);

	// 指定された親ノードにぶら下げる
	pNode->addNode(m_pBaseNode);
	m_pBaseNode->addNode(m_pNode);
	m_pNode->setTranslate((float)m_x, (float)m_y);

	// Set BEFORE slider size.
	s32 left;
	s32 right;
	s32 middle;
	s32 bothModeInt;
	s32 bitmapVertical;
	bool hasAttrib = true;

	hasAttrib &= m_pTex->getAttribute(ASSET_ATTRIB::zK1_SC_LEFT,        left);
	hasAttrib &= m_pTex->getAttribute(ASSET_ATTRIB::zK1_SC_MIDDLE,      middle);
	hasAttrib &= m_pTex->getAttribute(ASSET_ATTRIB::zK1_SC_RIGHT,       right);
	hasAttrib &= m_pTex->getAttribute(ASSET_ATTRIB::zK1_SC_HASBITMAP,   bothModeInt);
	hasAttrib &= m_pTex->getAttribute(ASSET_ATTRIB::zK1_SC_ISVERTICAL,  bitmapVertical);

	klb_assert(hasAttrib, "Image source for Scroll bar does not have attributes for scroll bar design");
	//klb_assert(bitmapVertical == (vert ? 1 : 0), "Bitmap and scroll bar have different orientation");

	bool bothMode = bothModeInt ? true : false;
	bitmapHasBoth = bothMode;

	bTotal  = left + right + middle;
	bLeft   = left;
	bRight  = right;
	bMiddle	= middle;
	
	setMinPosition(minValue);
	setMaxPosition(maxValue);
	setInitial(pos);

	setSliderSizeMin(min_slider_size);
	setSliderSize(slider_size);

	m_active = active;
	m_state  = S_WAIT;
	m_bReady = true;

	return true;
}

void
CKLBScrollBarIF::die()
{
	CKLBDataHandler::releaseHandle(m_texHandle);
	m_texHandle = 0;

	if(m_callback) {
		KLBDELETEA( m_callback );	// 2012.11.29  解放漏れ修正
		m_callback = NULL;
	}
    if(m_pScrMgr) { KLBDELETE(m_pScrMgr); }
	m_pScrMgr = NULL;
}

void
CKLBScrollBarIF::setSliderSize(s32 value)
{
	s32  size = m_vertical ? m_height : m_width;

	if (value > size) {
		value = size;	
	}

	s32 minSize  = m_slider_min_size;
	if (value < minSize) {
		value = minSize;
	}

	s32 currSize = m_slider_size;
	if (value != currSize) {
		m_slider_size = value;
		m_bCmdUpdate = true;
	}
	// m_barPos = m_pScrMgr->getBarPosition();
	m_barPos = m_pScrMgr->getNowBar();
    if(m_barPos < 0)                    { m_barPos = m_minPos; }
    if(m_barPos > m_maxPos - m_minPos)  { m_barPos = m_maxPos - m_minPos; }
    if(m_bReady)                        { updateDisplay(); }

	// 変更後のスライダサイズで表示状態を変更する
	setVisible(m_visible);
}

void
CKLBScrollBarIF::setSliderSizeMin(s32 value)
{
	if (value < (bLeft + bRight)) {
		value = bLeft + bRight;
	}

	s32  size = m_vertical ? m_height : m_width;
	if (value > size) {
		value = size;
	}

	s32 minSize  = m_slider_min_size;
	if (value != minSize) {
		m_slider_min_size = value;
		m_bCmdUpdate = true;
	}
}

void
CKLBScrollBarIF::setColorMode(u32 mode, u32 color) 
{
	// OPTIMIZE : Can optimize on value change

	if (mode == 0) {
		m_col_normal = color;
	} else {
		m_col_select = color;
	}

	m_bCmdUpdate = true;
}

u32
CKLBScrollBarIF::getColorMode(u32 mode) 
{
	return (mode ? m_col_select : m_col_normal);
}

void
CKLBScrollBarIF::setMode(u32 mode) 
{
	if (mode != m_mode) {
		m_mode          = (u8)mode;
		m_first         = true;
		m_bCmdUpdate    = true;

		if(m_mode) {
			SColorVector vec;
            for(int i = 0; i < 4; i++) { vec.m_vector[i] = 1.0f; }
            if(m_pBaseNode) { m_pBaseNode->setColorMatrix(vec); }
			m_hide = false;
		} else {
			m_timeHide = 0;
			m_hide = true;
		}
	}
}

void 
CKLBScrollBarIF::setTouchActive(bool active) 
{
	m_active = active;
}

void
CKLBScrollBarIF::setScrollMgr(CKLBScrollMgr * mgr)
{
	KLBDELETE(m_pScrMgr);
	m_pScrMgr = mgr;
	m_pScrMgr->setMargin(m_margin_top, m_margin_bottom);
	m_pScrMgr->setMaxPosition(m_maxPos);
}

void
CKLBScrollBarIF::setCtrlStatus(bool status)
{
	setMode((status) ? 1 : 0);
}

void
CKLBScrollBarIF::setMaxPosition(int maxPos)
{
	m_maxPos = maxPos;
	if(m_pScrMgr) {
		m_pScrMgr->setMaxPosition(m_maxPos - m_minPos);
		// m_barPos = m_pScrMgr->getBarPosition();
		m_barPos = m_pScrMgr->getNowBar();
        if(m_barPos < 0)                    { m_barPos = m_minPos;              }
		if(m_barPos > m_maxPos - m_minPos)  { m_barPos = m_maxPos - m_minPos;   }
	}
}

void
CKLBScrollBarIF::setMinPosition(int minPos)
{
	m_minPos = minPos;
	if(m_pScrMgr) {
		m_pScrMgr->setMaxPosition(m_maxPos - m_minPos);
		//m_barPos = m_pScrMgr->getBarPosition();
		m_barPos = m_pScrMgr->getNowBar();
        if(m_barPos < 0)                    { m_barPos = m_minPos;              }
		if(m_barPos > m_maxPos - m_minPos)  { m_barPos = m_maxPos - m_minPos;   }
	}
}

void
CKLBScrollBarIF::setInitial(int pos)
{
	if(!m_overScroll) {
        if(pos < m_minPos) { pos = m_minPos; }
		if(pos > m_maxPos) { pos = m_maxPos; }
	}
	// バーの位置は overScroll を問わずクリッピングする
	m_barPos = pos - m_minPos;
	int setPos = m_barPos;
	if((m_maxLoop - m_minLoop) == 0) {
        if(m_barPos < 0)                    { m_barPos = 0;                     }
        if(m_barPos > m_maxPos - m_minPos)  { m_barPos = m_maxPos - m_minPos;   }
	} else {
        if(m_barPos < 0)                    { m_barPos += m_maxPos - m_minPos;  }
        if(m_barPos > m_maxPos - m_minPos)  { m_barPos -= m_maxPos - m_minPos;  }
	}
	if(m_pScrMgr) {
		m_pScrMgr->initPos(setPos);
	}
}

void
CKLBScrollBarIF::setPosition(int pos, int dir)
{
	if(!m_overScroll) {
        if(pos < m_minPos) { pos = m_minPos; }
		if(pos > m_maxPos) { pos = m_maxPos; }
	}
	// バーの位置は overScroll を問わずクリッピングする
	m_barPos = pos - m_minPos;
	int setPos = m_barPos;
	if((m_maxLoop - m_minLoop) == 0) {
        if(m_barPos < 0)                    { m_barPos = 0;                     }
        if(m_barPos > m_maxPos - m_minPos)  { m_barPos = m_maxPos - m_minPos;   }
	} else {
        if(m_barPos < 0)                    { m_barPos += m_maxPos - m_minPos;  }
		if(m_barPos > m_maxPos - m_minPos)  { m_barPos -= m_maxPos - m_minPos;  }
	}
	if(m_pScrMgr) {
		m_pScrMgr->setPos(setPos, dir);
	}
}

void
CKLBScrollBarIF::setMargin(int top, int bottom)
{
	m_margin_top = top;
	m_margin_bottom = bottom;
	if(m_pScrMgr) {
		m_pScrMgr->setMargin(top, bottom);
	}
}

void
CKLBScrollBarIF::setLoopArea(int min, int max)
{
	m_minLoop = min;
	m_maxLoop = max;
	if(m_pScrMgr) m_pScrMgr->setLoopArea(max - min);
}

int
CKLBScrollBarIF::getPosition()
{
	if(m_pScrMgr) {
		// m_lastPos = m_pScrMgr->getPosition();
		m_lastPos = m_pScrMgr->getNowPos();
	}
	if(!m_overScroll && !(m_maxLoop - m_minLoop)) {
        if(m_lastPos < 0)                   { m_lastPos = 0;                    }
		if(m_lastPos > m_maxPos - m_minPos) { m_lastPos = m_maxPos - m_minPos;  }
	}
	return m_lastPos + m_minPos;
}

int
CKLBScrollBarIF::getBarPosition()
{
	return m_barPos;
}

void
CKLBScrollBarIF::execute(u32 deltaT)
{
	if(m_hide_mode && m_hide) {
		m_timeHide += deltaT;
		if(m_timeHide >= 1000 && !m_mode) {	// 操作終了から1秒を超えていたら、0.3秒でフェードアウトさせる。
			u32 fadeTime = m_timeHide - 1000;
			if(fadeTime >= 300) {
				fadeTime = 300;
				m_hide = false;
			}
			float alpha = (300 - fadeTime) / 300.0f;
			SColorVector vec;
            for(int i = 0; i < 3; i++) { vec.m_vector[i] = 1.0f; }
			vec.m_vector[3] = alpha;
			m_pBaseNode->setColorMatrix(vec);
		}
	}
	// 無効にされていたら何もしない。
    if(!m_enable) { return; }
		
	// 表示されていて操作が許可されている場合は操作を受け付ける
    if(m_bReady && m_visible && m_active) { procUserCtrl(); }

	// 操作結果をスクロールマネージャに通し、最終的なバーの表示位置を取得する
	if(m_pScrMgr) {
		m_pScrMgr->execute(deltaT);

		//m_barPos = m_pScrMgr->getBarPosition();
		m_barPos = m_pScrMgr->getNowBar();
	} else {
		m_barPos = m_lastPos;
	}
    if(m_barPos < 0)                    { m_barPos = 0;                     }
	if(m_barPos > m_maxPos - m_minPos)  { m_barPos = m_maxPos - m_minPos;   }

	// そもそも初期化されていない場合は何も処理しない
    if(!m_bReady) { return; }

	// バー位置が変更されていたら表示の変更処理を行う
	if(m_prePos != m_barPos || m_bCmdUpdate) {
		updateDisplay();
		m_bCmdUpdate = false;
	}
}

void
CKLBScrollBarIF::procUserCtrl()
{
    CKLBTouchPadQueue& tpq = CKLBTouchPadQueue::getInstance();
    const PAD_ITEM * item;

    tpq.startItem();

    bool bFirst = true;

    while((item = tpq.getItem())) {

	    switch(item->type)
	    {
	    case PAD_ITEM::TAP:
		    {
			    // そのフレームで最初にみつけたTAPならば、
			    // 現在DragIconのある位置から、絶対座標上のヒットボックスを計算する
			    if(bFirst) {
				    bFirst = false;
				    CKLBNode * pNode = m_pNode;
				    CKLBUtility::getNodeInverseMatrix(pNode, m_invTransf);
				    CKLBUtility::transform(&m_invTransf, item->x, item->y, m_ofs_x, m_ofs_y);
			    }

			    if(	   (m_ofs_x >= 0.0f    ) 
				    && (m_ofs_x <= (float)m_width) 
				    && (m_ofs_y >=0.0f     ) 
				    && (m_ofs_y <= (float)m_height) ) {

				    bool isSliderDrag = false;

				    s32 deltaTotal  = m_maxPos - m_minPos;
				    s32 pos         = m_barPos;
				    s32 sliderSize  = m_slider_size;

				    if (m_vertical) {
					    // Vertical
					    s32 sliderPos	= m_height - sliderSize;	
					    s32 posY		= deltaTotal ? (sliderPos * pos) / deltaTotal : 0;

					    isSliderDrag	= (m_ofs_y >= posY && m_ofs_y <= (posY + sliderSize));
				    } else {
					    // Horizontal
					    s32 sliderPos	= m_width  - sliderSize;	
					    s32 posX		= deltaTotal ? (sliderPos * pos) / deltaTotal : 0;

					    isSliderDrag	= (m_ofs_x >= posX && m_ofs_x <= (posX + sliderSize));
				    }

				    if (isSliderDrag) {
					    setMode(1); // Selected Mode
					    m_dragStartPos = m_barPos + m_minPos;
					    m_state = S_DRAG;	// 状態をドラッグ中のstateに変更
				    } else {
					    m_state = S_DRAG_IGNORE;
				    }
				    m_tid = item->id;	// 操作に使われたポイントIDを記録する
				    tpq.useItem(item, this);
			    }
		    }
		    break;
	    case PAD_ITEM::DRAG:
		    {
			    // このタスクのステートがドラッグ中でない限り、
			    // そのドラッグは他の用途のためのドラッグ操作。
			    // また、タップ時に確定した操作ポイントIDが異なる場合も異なる操作。
			    if(m_state == S_WAIT || m_tid != item->id) break;

			    if (m_state == S_DRAG) {
				    setMode(1); // Selected Mode

				    float drag_x,drag_y,delta;
				    s32 lengthScr;
				    s32 lengthValue;

				    CKLBUtility::transform(&m_invTransf, item->x, item->y, drag_x, drag_y);

				    lengthValue = m_maxPos - m_minPos;
				    if (m_vertical) {
					    delta       = drag_y - m_ofs_y;
					    lengthScr   = m_height - m_slider_size;
				    } else {
					    delta       = drag_x - m_ofs_x;
					    lengthScr   = m_width - m_slider_size;
				    }

				    s32 scrollAmount = (lengthValue * delta) / lengthScr;	// Pixel Delta => Scroll Delta
				    s32 oldPos       = m_barPos + m_minPos;
				    setPosition(m_dragStartPos + scrollAmount);

				    s32 nowPos = getPosition();
				    if(oldPos != nowPos) {
					    CKLBScriptEnv::getInstance().call_eventScrollBar(m_callback, m_pOwner, SCROLLBAR_DRAG, nowPos);
				    }
			    }

			    // ドラッグ座標をコールバックに通知する。
			    tpq.useItem(item, this);
		    }
		    break;
	    case PAD_ITEM::RELEASE:
	    case PAD_ITEM::CANCEL:
		    {					
			    // このタスクのステートがドラッグ中でない限り
			    // そのドラッグは他の用途のためのドラッグ操作。
			    // また、タップ時に確定した操作ポイントIDが異なる場合も異なる操作。
                if(m_state == S_WAIT || m_tid != item->id) { break; }
					
			    if (m_state == S_DRAG) {
				    setMode(0); // Selected Mode

				    CKLBScriptEnv::getInstance().call_eventScrollBar(m_callback, m_pOwner, SCROLLBAR_RELEASE, getPosition());
			    }

			    // リリースされた座標をコールバックに通知する。
			    tpq.useItem(item, this);
			    m_state = S_WAIT;
			    m_tid = -1;	// そのIDはリリースされたので、操作が行われていない状態に戻す
		    }
		    break;
	    }
    }
}

void
CKLBScrollBarIF::updateDisplay()
{
	recompute();
	m_prePos = m_barPos;
}

void
CKLBScrollBarIF::recompute() 
{
	// Compute new UV,XY

	/*
		0---1
		|	|
		|	|
		3---2
	 */

	SColorVector col;

	// OPTIMIZE : Could store internally as float also to avoid this conversion
	u32 color = getColorMode(m_mode);	// ARGB
	col.m_vector[0]	= ((color >> 16) & 0xFF) / 255.0f;	// R
	col.m_vector[1]	= ((color >> 8 ) & 0xFF) / 255.0f;	// G
	col.m_vector[2]	= ((color      ) & 0xFF) / 255.0f;	// B
	col.m_vector[3]	= ((color >> 24) & 0xFF) / 255.0f;	// A

	m_pNode->setColorMatrix(col);

	if (m_first) {
		//
		float u0,u1,u2,u3;
		float v0,v1,v2,v3;

		// Bitmap including all sub bitmaps.
		m_pTex->getUV(0, &u0, &v0);
		m_pTex->getUV(1, &u1, &v1);
		m_pTex->getUV(2, &u2, &v2);
		m_pTex->getUV(3, &u3, &v3);

		float du0 = u1 - u0;
		float dv0 = v1 - v0;
		// float du1 = u3 - u0;
		// float dv1 = v3 - v0;

		// Find if texture is oriented
		bool texHoriz = true;
		if (du0 < dv0) {
			texHoriz = false;
		}

		// Swap UV
		if (!texHoriz) {
			float t;
			t = u0; u0 = v0; v0=t;	
			t = u1; u1 = v1; v1=t;	
			t = u2; u2 = v2; v2=t;	
			t = u3; u3 = v3; v3=t;	
		}

		if (bitmapHasBoth) {
			if (!m_vertical) {
				float step = (u1-u0)/2.0f;
				u0 += step * m_mode;
				u3 += step * m_mode;
				u1 = u0 + step;
				u2 = u3 + step;
			} else {
				float step = (v2-v0)/2.0f;
				v0 += step * m_mode;
				v1 += step * m_mode;
				v2 = v0 + step;
				v3 = v1 + step;
			}
		} else {
			// Do not change UV
		}

		// Can optimize :
		// - u1-u0 and u2-u3 should be the same.
		// - can factorize u1-u0 / bTotal for all expressions.
		// - factorize all
		// - bLeft, etc... can be store as float to avoid conv each time.
		// - Most of this could be computed

		if (!m_vertical) {
			// Left   Item
			m_vertices[0 ].u = u0;													m_vertices[0 ].v = v0;
			m_vertices[1 ].u = u0 + (((u1 - u0)*bLeft) / bTotal);					m_vertices[1 ].v = v1;
			m_vertices[2 ].u = u3 + (((u2 - u3)*bLeft) / bTotal);					m_vertices[2 ].v = v2;
			m_vertices[3 ].u = u3;													m_vertices[3 ].v = v3;

			// Middle Item
			m_vertices[4 ].u = m_vertices[1].u;										m_vertices[4 ].v = v0;
			m_vertices[5 ].u = m_vertices[1].u + (((u1 - u0)*bMiddle) / bTotal);	m_vertices[5 ].v = v1;
			m_vertices[6 ].u = m_vertices[2].u + (((u1 - u0)*bMiddle) / bTotal);	m_vertices[6 ].v = v2;
			m_vertices[7 ].u = m_vertices[2].u;										m_vertices[7 ].v = v3;

			// Right  Item
			m_vertices[8 ].u = m_vertices[5].u;										m_vertices[8 ].v = v0;
			m_vertices[9 ].u = m_vertices[5].u + (((u1 - u0)*bRight) / bTotal);		m_vertices[9 ].v = v1;
			m_vertices[10].u = m_vertices[6].u + (((u1 - u0)*bRight) / bTotal);		m_vertices[10].v = v2;
			m_vertices[11].u = m_vertices[6].u;										m_vertices[11].v = v3;
		} else {
			m_vertices[0 ].u = u0;
			m_vertices[1 ].u = u1;
			m_vertices[2 ].u = u2;
			m_vertices[3 ].u = u3;

			m_vertices[4 ].u = u0;
			m_vertices[5 ].u = u1;
			m_vertices[6 ].u = u2;
			m_vertices[7 ].u = u3;

			m_vertices[8 ].u = u0;
			m_vertices[9 ].u = u1;
			m_vertices[10].u = u2;
			m_vertices[11].u = u3;


			// Left   Item
			m_vertices[0 ].v = v0;													
			m_vertices[1 ].v = v1;
			m_vertices[2 ].v = v1 + (((v2 - v1)*bLeft) / bTotal);					
			m_vertices[3 ].v = v0 + (((v3 - v0)*bLeft) / bTotal);													

			// Middle Item
			m_vertices[4 ].v = m_vertices[3].v;										
			m_vertices[5 ].v = m_vertices[2].v;
			m_vertices[6 ].v = m_vertices[2].v + (((v2 - v1)*bMiddle) / bTotal);
			m_vertices[7 ].v = m_vertices[3].v + (((v2 - v1)*bMiddle) / bTotal);

			// Right  Item
			m_vertices[8 ].v = m_vertices[7].v;										
			m_vertices[9 ].v = m_vertices[6].v;
			m_vertices[10].v = m_vertices[6].v + (((v2 - v1)*bRight) / bTotal);
			m_vertices[11].v = m_vertices[7].v + (((v2 - v1)*bRight) / bTotal);
		}

		if (!texHoriz) {
			// Swap back U & V.
			for(int i = 0; i < 12; i++) {
				float t = m_vertices[i].u;
				m_vertices[i].u = m_vertices[i].v;
				m_vertices[i].v = t;
			}
		}

		m_first = false;
	}


	// ### OPTIMIZE Expressions ### (factorization, convertion cast)

	s32 deltaTotal  = m_maxPos - m_minPos;
	s32 pos         = m_barPos;
	s32 sliderSize  = m_slider_size;

	s32 bMiddleScr	= sliderSize - (bLeft + bRight);

	if (m_vertical) {
		// Vertical
		s32 sliderPos   = m_height - sliderSize;	
		s32 posY        = s32(deltaTotal ? (((s64)sliderPos * pos)) / deltaTotal : 0);

		// ==== Coordinate ====
		float width = (float)m_width;

		// Left   Item
		m_vertices[0 ].x = 0.0f;							m_vertices[0 ].y = posY;								
		m_vertices[1 ].x = width;							m_vertices[1 ].y = posY;						
		m_vertices[2 ].x = width;							m_vertices[2 ].y = posY + bLeft;						
		m_vertices[3 ].x = 0.0f;							m_vertices[3 ].y = posY + bLeft;

		// Middle Item
		m_vertices[4 ].x = 0.0f;							m_vertices[4 ].y = m_vertices[3].y;
		m_vertices[5 ].x = width;							m_vertices[5 ].y = m_vertices[2].y;		
		m_vertices[6 ].x = width;							m_vertices[6 ].y = m_vertices[2].y + bMiddleScr;		
		m_vertices[7 ].x = 0.0f;							m_vertices[7 ].y = m_vertices[3].y + bMiddleScr;					

		// Right  Item
		m_vertices[8 ].x = 0.0f;							m_vertices[8 ].y = m_vertices[7].y;					
		m_vertices[9 ].x = width;							m_vertices[9 ].y = m_vertices[6].y;
		m_vertices[10].x = width;							m_vertices[10].y = m_vertices[6].y + bRight;		
		m_vertices[11].x = 0.0f;							m_vertices[11].y = m_vertices[7].y + bRight;
	} else {
		// Horizontal
		s32 sliderPos	= m_width  - sliderSize;	
		s32 posX		= (s32)(deltaTotal ? (((s64)sliderPos * pos)) / deltaTotal : 0);

		// ==== Coordinate ====
		float height = (float)m_height;

		// Left   Item
		m_vertices[0 ].x = posX;							m_vertices[0].y = 0.0f;
		m_vertices[1 ].x = posX + bLeft;					m_vertices[1].y = 0.0f;
		m_vertices[2 ].x = posX + bLeft;					m_vertices[2].y = height;
		m_vertices[3 ].x = posX;							m_vertices[3].y = height;

		// Middle Item
		m_vertices[4 ].x = m_vertices[1].x;					m_vertices[4].y = 0.0f;
		m_vertices[5 ].x = m_vertices[1].x + bMiddleScr;	m_vertices[5].y = 0.0f;
		m_vertices[6 ].x = m_vertices[2].x + bMiddleScr;	m_vertices[6].y = height;
		m_vertices[7 ].x = m_vertices[2].x;					m_vertices[7].y = height;

		// Right  Item
		m_vertices[8 ].x = m_vertices[5].x;					m_vertices[8 ].y = 0.0f;
		m_vertices[9 ].x = m_vertices[5].x + bRight;		m_vertices[9 ].y = 0.0f;
		m_vertices[10].x = m_vertices[6].x + bRight;		m_vertices[10].y = height;
		m_vertices[11].x = m_vertices[6].x;					m_vertices[11].y = height;
	}

	for(int i = 0; i < 18; i++) {
		int idx = ms_indices[i];
		m_pDynSprite->setVertexXY(i, m_vertices[idx].x, m_vertices[idx].y);
		m_pDynSprite->setVertexUV(i, m_vertices[idx].u, m_vertices[idx].v);
	}

	m_pNode->markUpMatrix();
}
