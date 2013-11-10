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
#ifndef CKLBDebugMenu_h
#define CKLBDebugMenu_h

#include "CKLBTask.h"
#include "CKLBNode.h"
#include "CLuaState.h"
#include "CKLBNodeVirtualDocument.h"
#include "CKLBTextInputNode.h"
#include "CKLBTouchEventUI.h"
#define DBG_FONTSIZE 32
#define DBG_FONTNAME "fixed"


struct DBG_MENU {
	const char * caption;
	const char * key;
	enum MODE {
		M_SWITCH,	// ON/OFF
		M_NUMBER,	// 数値
		M_SELECT,	// 選択メニュー
	};
	MODE			mode;
	int				min;
	int				max;
	int				value;
	const char **	items;
};

class CKLBDebugMenu;

/*!
* \class CKLBDebugSign
* \brief 
* Internal task created by CKLBDebugMenu for controlling the appearance or disappearance of debug menu.
* It detect a specific sign made by moving the finger on the screen.
*
* 1x          x3
*   xx      xx  x
*     xx  xx    x
*       xx      x
*     xx  xx    x
*   xx      xx  x
* 4x          x2
*
* Following the 1,2,3,4 order.
*
*/
class CKLBDebugSign : public CKLBTask
{
private:
	CKLBDebugSign();
	virtual ~CKLBDebugSign();
public:
	static CKLBDebugSign * create(CKLBDebugMenu * pMenu);

	bool init(CKLBDebugMenu * pMenu);
	void execute(u32 deltaT);
	void die();
private:
	int checkPoint(int x, int y);

	CKLBDebugMenu	*	m_pMenu;

	int					m_width;
	int					m_height;
	int					m_cmdStep;
	int					m_cmdID;
};

/*!
* \class CKLBDebugMenu
* \brief Debug Menu
* 
* CKLBDebugMenu allows to create a debug menu task for your game.
* Several items can be used in the Menu : 
* - Switch between 2 values.
* - Numbers.
* - Select between several values.
*
* Compile option DEBUG_MENU must be set to be able to use it.
*/
class CKLBDebugMenu : public CKLBTask
{
private:
	CKLBDebugMenu();
	virtual ~CKLBDebugMenu();
public:
	static CKLBDebugMenu * create();

	bool init   ();
	void execute(u32 deltaT);
	void die    ();

	void menu_switch    (bool bSwitch);

private:
	void execute_active (u32 deltaT);

private:
	enum STATE {
		E_WAIT,
		E_ACTIVE
	};
	STATE			m_state;	// 現在の状態
	int				m_step;

	struct PAD {
		bool	enable;
		int		x, y;	// TAP位置
	};
	int				m_dispY;
	PAD				m_pad[CKLBTouchEventUIMgr::MAX_TOUCH_POINT];
};

class CKLBDebugResource
{
private:
	CKLBDebugResource();
	virtual ~CKLBDebugResource();
public:
	static CKLBDebugResource& getInstance();

	void    init   ();
	void    clear  ();

	void    release();

	void    addDebugItem    (const char * caption, const char * key, DBG_MENU * pItem);

	void    dispEnable      (bool enable);
	bool    tapItem         (int x, int y);

	void    setGroupLua     (const char * caption, const char * key, CLuaState& lua);
	void    removeGroup     (const char * key);

	void    createLuaTable  (CLuaState& lua);

	void    setCallback     (const char * callback);
	void    finishReport    ();

	int     setScroll       (int dispY) {
		if(dispY > m_lastY - m_scrnHeight) dispY = m_lastY - m_scrnHeight;
		if(dispY < 0) dispY = 0;
		m_dispY = -dispY;
		m_pNode->setTranslate(0, (float)m_dispY);
		return dispY;
	}
	inline void setBright   (float bright) {
		SColorVector vec;
		for(int i = 0; i < 3; i++) vec.m_vector[i] = bright;
		m_pNode->setColorMatrix(vec);
	}
private:
	CKLBNode *  addLabel    (int x, int y, const char * label, int * width, int * height);
	CKLBNodeVirtualDocument * createLabelItem(const char * label, int * width, int * height);

	CKLBNode	*	m_pNode;

	struct SWITCH {
		CKLBNode	*	label;
		CKLBNode	*	pNode;
		union {
			CKLBNodeVirtualDocument * pVDoc;
			CKLBUITextBox			* pText;
		} obj;

		DBG_MENU::MODE	mode;
		int				min;	// MODEがM_NUMBERのときのみ有効
		int				max;	// 最大値
		int				val;	// 現在の値
		const char	*	key;	// Lua配列化する際のキー文字列
		const char **	disp;	// 表示値(M_SWITCH/M_SELECTのときに使用、M_NUMBERでは0)
		struct {
			int x, y;
			int w, h;
		} rect;					// switch/select で使用するhitboxの相対位置とサイズ
	};

	struct GROUP {
		GROUP		*	prev;
		GROUP		*	next;

		const char	*	key;
		CKLBNode	*	node;	// グループラベルのnode
		int				cnt;	// 項目数
		SWITCH		*	menu;	// 1項目あたりの領域
	};

	GROUP		*	m_begin;
	GROUP		*	m_end;

	int				m_dispY;	// スクロール用

	int				m_lastY;	// 項目追加用
	u32				m_order;

	int				m_exitWidth;
	int				m_exitHeight;

	int				m_scrnHeight;

	const char	*	m_callback;

	u8				m_format;

	static const char * ms_labelSwitch[];
};

#endif // CKLBDebugMenu_h
