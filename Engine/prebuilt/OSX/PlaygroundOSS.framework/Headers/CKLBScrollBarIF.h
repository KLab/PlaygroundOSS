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
#ifndef CKLBScrollBarIF_h
#define CKLBScrollBarIF_h


#include "CLuaState.h"
#include "CKLBNode.h"
#include "CKLBUISystem.h"
#include "CKLBLuaTask.h"
#include "CKLBLuaEnv.h"

//! スクロールマネージャインタフェース
class CKLBScrollMgr
{
public:
	CKLBScrollMgr();
	virtual ~CKLBScrollMgr();

	void setMaxPosition (int max);
	void setLoopArea    (int lenLoop = 0);

	// callbackの設定
	bool setCallback    (void * pData, const char * funcname);

	// 引数として位置を与え callback を呼び出す
	void execCallback   (int pos);

	inline void initPos (int pos) {
		setInitial(pos);
	}
	
	inline void setPos  (int pos, int dir) {
		setPosition(pos, dir);
	}

	inline int  getNowPos() {
		float pos = (float)getPosition();
		return (int)loopRound(pos);
	}
	inline int  getNowBar() {
		float pos = (float)getBarPosition();
		pos = loopRound(pos);
		if(pos > (float)m_maxPos) pos = (float)m_maxPos;
		return (int)pos;
	}

	virtual void setMargin      (int top, int bottom)   = 0;
	virtual void setInitial     (int pos)               = 0; 
	virtual void setPosition    (int pos, int dir)      = 0;
	virtual int  getPosition    ()                      = 0;
	virtual int  getBarPosition ()                      = 0;
	virtual void execute        (u32 deltaT)            = 0;
	virtual bool stillScrolling ()                      = 0;
protected:
	float loopRound(float pos);

	int				m_maxPos;
	int				m_lenLoop;

	void		*	m_data;			// data pointer for callback.
	const char	*	m_callback;		// callback function name
	int				m_precallPos;
};


//! スクロールバーインタフェース
/*!
	
*/
class CKLBScrollBarIF
{
public:
	enum {
		SCROLLBAR_DRAG		= 0,
		SCROLLBAR_RELEASE	= 1,
		SCROLLBAR_STOPPED	= 2,	// Use for C# callback of CKLBScrollMgr::execCallback
	};

	CKLBScrollBarIF(CKLBLuaTask * pOwner = 0);
	virtual ~CKLBScrollBarIF();

	void setScrollMgr(CKLBScrollMgr * mgr);
	inline bool setScrMgrCallback(void * pData, const char * funcname) {
		bool bResult = false;
		if(m_pScrMgr) {
			bResult = m_pScrMgr->setCallback(pData, funcname);
		}
		return bResult;
	}

	inline bool isScrolling() {
		if (m_pScrMgr) {
			return m_pScrMgr->stillScrolling();
		}
		return false;
	}

	bool init(
		CKLBNode * pNode,
		u32 order, float x, float y, float width, float height,
		s32 minValue, s32 maxValue, s32 pos, const char * image,
		s32 slider_size, s32 min_slider_size, 
		const char * callback,
		u32 colorNormal, u32 colorSelect, bool vert, bool active, bool hide_mode = false);

	void die                ();

	void setSliderSize      (s32 value);
	void setSliderSizeMin   (s32 value);
	void setColorMode       (u32 mode, u32 color);
	u32  getColorMode       (u32 mode);
	void setMode            (u32 mode);
	void setTouchActive     (bool active);

	inline void setOverScroll   (bool overscroll)   { m_overScroll = overscroll; }
	inline void setShortHide    (bool shortHide)    { m_bShortHide = shortHide;  }

	inline void setVisible      (bool visible) {
		m_visible = visible;
		if(m_pNode) {
			s32  size = m_vertical ? m_height : m_width;
			if(m_slider_size >= size && m_bShortHide) visible = false;
			m_pNode->setVisible(visible);
		}
	}

	inline void setEnable       (bool enable)       { m_enable = enable; }

	inline void setVertical     (bool vertical) {
		if (vertical != m_vertical) {
			m_vertical = vertical;
			m_bCmdUpdate = true;
		}
	}

	inline void setWidth        (s32 width) {
		if (width != m_width) {
			m_bCmdUpdate = false;
			m_width = width;
		}
	}

	inline void setHeight       (s32 height) {
		if (height != m_height) {
			m_bCmdUpdate = false;
			m_height = height;
		}
	}

	inline void setOrder        (u32 order) {
		if (m_order != order) {
			m_order = order;
			CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();
			m_pDynSprite->changeOrder(pRdrMgr, order);
		}
	}

	void setMaxPosition (int max);
	void setMinPosition (int min);
	void setLoopArea    (int min, int max);
	void setInitial     (int pos);
	void setPosition    (int pos, int dir = 0);	// dir = スクロール方向指定
	void setMargin      (int top, int bottom);
	void setCtrlStatus  (bool status);
	int getPosition     ();
	int getBarPosition  ();

	inline int getMinPosition   () { return m_minPos; }
	inline int getMaxPosition   () { return m_maxPos; }

	inline int getSliderSize    () { return m_slider_size;      }
	inline int getSliderSizeMin () { return m_slider_min_size;  }

	inline bool getTouchActive  () { return m_active; }

	void execute(u32 deltaT);

private:
	void procUserCtrl   ();
	void updateDisplay  ();
	void recompute      ();

private:
	CKLBScrollMgr	*	m_pScrMgr;
	int					m_maxPos;
	int					m_minPos;

	int					m_minLoop;
	int					m_maxLoop;

	int					m_lastPos;
	int					m_barPos;
	int					m_prePos;

	int					m_margin_top;
	int					m_margin_bottom;
	u32					m_order;

	bool				m_visible;
	bool				m_enable;
	bool				m_overScroll;
	bool				m_bShortHide;

	typedef enum {
		S_WAIT,				//!< 待機中
		S_DRAG,				//!< ドラッグ中
		S_DRAG_IGNORE,		//!< Sliderではないところのドラッグ
	} STATE;


	// 以下描画情報
	struct {
		float	x, y;
		float	u, v;
	} m_vertices[12];

	CKLBLuaTask		*	m_pOwner;		// オーナーとなるタスクのポインタ
	CKLBImageAsset	*	m_pTex;


	CKLBNode		*	m_pBaseNode;
	CKLBNode		*	m_pNode;
	CKLBDynSprite	*	m_pDynSprite;
	SMatrix2D			m_invTransf;

	u32					m_texHandle;
	u8					m_mode;
	bool				m_first;

	s32					bMiddle;
	s32					bLeft;
	s32					bRight;
	s32					bTotal;
	s32					m_dragStartPos;

	u32					m_state;
	float				m_ofs_x;
	float				m_ofs_y;
	int					m_tid;

	bool				bitmapHasBoth;


	int					m_x, m_y;
	int					m_width, m_height;
	bool				m_vertical;

	u32					m_col_normal;
	u32					m_col_select;

	s32					m_slider_min_size;
	s32					m_slider_size;

	bool				m_active;

	bool				m_bCmdUpdate;

	bool				m_bReady;

	bool				m_hide_mode;
	bool				m_hide;			// hide処理中ならtrue
	u32					m_timeHide;		// 表示を隠すまでの時間カウント

	const char *		m_callback;
	static const u16	ms_indices[];
};


#endif // CKLBScrollBarIF_h
