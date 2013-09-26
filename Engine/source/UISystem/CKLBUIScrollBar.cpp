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
#include "CKLBUIScrollBar.h"
#include "CKLBLuaEnv.h"
;
// Command Values
enum {
	UI_SCROLL_SET_MIN = 0,
	UI_SCROLL_GET_MIN,
	UI_SCROLL_SET_MAX,
	UI_SCROLL_GET_MAX,
	UI_SCROLL_SET_POS,
	UI_SCROLL_GET_POS,
	UI_SCROLL_SET_SLIDER_SIZE,
	UI_SCROLL_GET_SLIDER_SIZE,
	UI_SCROLL_SET_SLIDER_MIN_SIZE,
	UI_SCROLL_GET_SLIDER_MIN_SIZE,
	UI_SCROLL_SET_COLOR_NORMAL,
	UI_SCROLL_GET_COLOR_NORMAL,
	UI_SCROLL_SET_COLOR_SELECT,
	UI_SCROLL_GET_COLOR_SELECT,
	UI_SCROLL_SET_ALPHA_NORMAL,
	UI_SCROLL_GET_ALPHA_NORMAL,
	UI_SCROLL_SET_ALPHA_SELECT,
	UI_SCROLL_GET_ALPHA_SELECT,
	UI_SCROLL_SET_TOUCH_ACTIVE,
	UI_SCROLL_GET_TOUCH_ACTIVE,

	UI_SCROLL_SELECT_SCRMGR,
};

static IFactory::DEFCMD cmd[] = {
	{ "UI_SCROLL_SET_MIN",				UI_SCROLL_SET_MIN},
	{ "UI_SCROLL_GET_MIN",				UI_SCROLL_GET_MIN},
	{ "UI_SCROLL_SET_MAX",				UI_SCROLL_SET_MAX},
	{ "UI_SCROLL_GET_MAX",				UI_SCROLL_GET_MAX},
	{ "UI_SCROLL_SET_POS",				UI_SCROLL_SET_POS},
	{ "UI_SCROLL_GET_POS",				UI_SCROLL_GET_POS},
	{ "UI_SCROLL_SET_SLIDER_SIZE",		UI_SCROLL_SET_SLIDER_SIZE},
	{ "UI_SCROLL_GET_SLIDER_SIZE",		UI_SCROLL_GET_SLIDER_SIZE},
	{ "UI_SCROLL_SET_SLIDER_MIN_SIZE",	UI_SCROLL_SET_SLIDER_MIN_SIZE},
	{ "UI_SCROLL_GET_SLIDER_MIN_SIZE",	UI_SCROLL_GET_SLIDER_MIN_SIZE},
	{ "UI_SCROLL_SET_COLOR_NORMAL",		UI_SCROLL_SET_COLOR_NORMAL},
	{ "UI_SCROLL_GET_COLOR_NORMAL",		UI_SCROLL_GET_COLOR_NORMAL},
	{ "UI_SCROLL_SET_COLOR_SELECT",		UI_SCROLL_SET_COLOR_SELECT},
	{ "UI_SCROLL_GET_COLOR_SELECT",		UI_SCROLL_GET_COLOR_SELECT},
	{ "UI_SCROLL_SET_ALPHA_NORMAL",		UI_SCROLL_SET_ALPHA_NORMAL},
	{ "UI_SCROLL_GET_ALPHA_NORMAL",		UI_SCROLL_GET_ALPHA_NORMAL},
	{ "UI_SCROLL_SET_ALPHA_SELECT",		UI_SCROLL_SET_ALPHA_SELECT},
	{ "UI_SCROLL_GET_ALPHA_SELECT",		UI_SCROLL_GET_ALPHA_SELECT},
	{ "UI_SCROLL_SET_TOUCH_ACTIVE",		UI_SCROLL_SET_TOUCH_ACTIVE},
	{ "UI_SCROLL_GET_TOUCH_ACTIVE",		UI_SCROLL_GET_TOUCH_ACTIVE},

	{ "UI_SCROLL_SELECT_SCRMGR",		UI_SCROLL_SELECT_SCRMGR },
	{ 0, 0}
};
static CKLBTaskFactory<CKLBUIScrollBar> factory("UI_ScrollBar", CLB_KLBUISCROLLBAR, cmd);


CKLBUIScrollBar::CKLBUIScrollBar() 
: CKLBUITask    ()
, m_callback    (NULL)
, m_image       (NULL)
, m_min         (0)
, m_max         (0)
, m_pos         (0)
{
	m_scrBar = this;
	m_newScriptModel = true;
}

CKLBUIScrollBar::~CKLBUIScrollBar() 
{
	KLBDELETEA(m_callback);
	KLBDELETEA(m_image);
}

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUIScrollBar::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",			UINTEGER,	(setBoolT)&CKLBUIScrollBar::setOrder,			(getBoolT)&CKLBUIScrollBar::getOrder,			0	},
	{	"width",			INTEGER,	(setBoolT)&CKLBUIScrollBar::setWidth,			(getBoolT)&CKLBUIScrollBar::getWidth,			0	},
	{	"height",			INTEGER,	(setBoolT)&CKLBUIScrollBar::setHeight,			(getBoolT)&CKLBUIScrollBar::getHeight,			0	},
	{	"min",				INTEGER,	(setBoolT)&CKLBUIScrollBar::setMin,				(getBoolT)&CKLBUIScrollBar::getMin,				0	},
	{	"max",				INTEGER,	(setBoolT)&CKLBUIScrollBar::setMax,				(getBoolT)&CKLBUIScrollBar::getMax,				0	},
	{	"pos",				INTEGER,	(setBoolT)&CKLBUIScrollBar::setPos,				(getBoolT)&CKLBUIScrollBar::getPos,				0	},
	{	"img",				R_STRING,	NULL,											(getBoolT)&CKLBUIScrollBar::getImage,			0	},
	{	"slider_size",		INTEGER,	(setBoolT)&CKLBUIScrollBar::setSliderSize,		(getBoolT)&CKLBUIScrollBar::getSliderSize,		0	},
	{	"slider_minsize",	INTEGER,	(setBoolT)&CKLBUIScrollBar::setSliderSizeMin,	(getBoolT)&CKLBUIScrollBar::getSliderSizeMin,	0	},
	{	"f_vert",			BOOLEANT,	(setBoolT)&CKLBUIScrollBar::setVertical,		(getBoolT)&CKLBUIScrollBar::getVertical,		0	},
	{	"callback",			R_STRING,	NULL,											(getBoolT)&CKLBUIScrollBar::getCallBack,		0	},
	{	"alpha_normal",		UINTEGER,	(setBoolT)&CKLBUIScrollBar::setAlphaNormal,		(getBoolT)&CKLBUIScrollBar::getAlphaNormal,		0	},
	{	"alpha_select",		UINTEGER,	(setBoolT)&CKLBUIScrollBar::setAlphaSelect,		(getBoolT)&CKLBUIScrollBar::getAlphaSelect,		0	},
	{	"color_normal",		UINTEGER,	(setBoolT)&CKLBUIScrollBar::setColorNormal,		(getBoolT)&CKLBUIScrollBar::getColorNormal,		0	},
	{	"color_select",		UINTEGER,	(setBoolT)&CKLBUIScrollBar::setColorSelect,		(getBoolT)&CKLBUIScrollBar::getColorSelect,		0	},
	{	"touch_active",		BOOLEANT,	(setBoolT)&CKLBUIScrollBar::setTouchActive,		(getBoolT)&CKLBUIScrollBar::getTouchActive,		0	}
};

// 引数のインデックス定義
enum {
	ARG_PARENT = 1,
	ARG_ORDER,

	ARG_X,
	ARG_Y,
	ARG_WIDTH,
	ARG_HEIGHT,

	ARG_VALMIN,
	ARG_VALMAX,
	ARG_POS,

	ARG_IMG,

	ARG_SLIDER_SIZE,
	ARG_SLIDER_MIN_SIZE,
	
	ARG_VERT,
	ARG_CALLBACK,

	ARG_TOUCH_ACTIVE,
	ARG_ALPHA_NORMAL,
	ARG_ALPHA_SELECT,
	ARG_COLOR_NORMAL,
	ARG_COLOR_SELECT,

	ARG_HIDE_MODE,

	ARG_TOTAL   = ARG_HIDE_MODE,
	ARG_REQUIRE = ARG_VERT	// 最低限必要なパラメータ数
};

CKLBUIScrollBar *
CKLBUIScrollBar::create(CKLBUITask * pParent, CKLBNode * pNode,
                        u32 order, float x, float y, float width, float height,
                        s32 minValue, s32 maxValue, s32 pos,
                        const char * image,
                        s32 slider_size, s32 min_slider_size,
                        const char * callback,
                        u32 colorNormal, u32 colorSelect, bool vert, bool active,
                        bool hide_mode)
{
	CKLBUIScrollBar * pTask = KLBNEW(CKLBUIScrollBar);
    if(!pTask) { return NULL; }

	if(!pTask->init(pParent, pNode, 
                    order, x, y, width, height, 
                    minValue, maxValue, pos, 
                    image, 
                    slider_size, min_slider_size, 
                    callback,
                    colorNormal, colorSelect, vert, active, hide_mode)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUIScrollBar::init(CKLBUITask * pParent, CKLBNode * pNode,
                      u32 order, float x, float y, float width, float height,
                      s32 minValue, s32 maxValue, s32 pos,
                      const char * image,
                      s32 slider_size, s32 min_slider_size, 
                      const char * callback,
                      u32 colorNormal, u32 colorSelect, bool vert, bool active,
                      bool hide_mode)
{
    if(!setupNode()) { return false; }

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(order, x, y, width, height, minValue, maxValue, pos, image, 
                            slider_size, min_slider_size, 
                            callback,
                            colorNormal, colorSelect, vert, active, hide_mode);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}

	return bResult;
}


bool
CKLBUIScrollBar::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();

	if(argc > ARG_TOTAL || argc < ARG_REQUIRE) return false;

	u32 order				= lua.getInt(ARG_ORDER);
	float x					= lua.getFloat(ARG_X);
	float y					= lua.getFloat(ARG_Y);
	float width				= lua.getFloat(ARG_WIDTH);
	float height			= lua.getFloat(ARG_HEIGHT);

	s32 minValue			= lua.getInt(ARG_VALMIN);
	s32 maxValue			= lua.getInt(ARG_VALMAX);
	s32 pos					= lua.getInt(ARG_POS);
	const char * image		= lua.getString(ARG_IMG);
	s32 slider_size			= lua.getInt(ARG_SLIDER_SIZE);
	s32 min_slider_size		= lua.getInt(ARG_SLIDER_MIN_SIZE);
	bool vert				= (argc >= ARG_VERT			) ? lua.getBool(ARG_VERT		) : false;
	bool active				= (argc >= ARG_TOUCH_ACTIVE	) ? lua.getBool(ARG_TOUCH_ACTIVE) : false;
	const char * callback	= (argc >= ARG_CALLBACK)	  ? (lua.isNil(ARG_CALLBACK) ? NULL: lua.getString(ARG_CALLBACK)) : NULL;

	// 8 Bit A
	u32 alphaNormal			= (argc >= ARG_ALPHA_NORMAL	) ? lua.getInt(ARG_ALPHA_NORMAL)  : 0xFF;
	u32 alphaSelect			= (argc >= ARG_ALPHA_SELECT	) ? lua.getInt(ARG_ALPHA_SELECT)  : 0xFF;

	// 24 Bit RGB + 8 Bit A
	u32 colorNormal			= (alphaNormal << 24) | ((argc >= ARG_COLOR_NORMAL	) ? lua.getInt(ARG_COLOR_NORMAL)  : 0xFFFFFF);
	u32 colorSelect			= (alphaSelect << 24) | ((argc >= ARG_COLOR_SELECT	) ? lua.getInt(ARG_COLOR_SELECT)  : 0xFFFFFF);

	bool hide_mode			= (argc >= ARG_HIDE_MODE) ? lua.getBool(ARG_HIDE_MODE) : false;
	return initCore(order, x, y, width, height, minValue, maxValue, pos, image, 
                    slider_size, min_slider_size, 
                    callback,
                    colorNormal, colorSelect, vert, active, hide_mode );
}

bool
CKLBUIScrollBar::initCore(u32 order, float x, float y, float width, float height,
                          s32 minValue, s32 maxValue, s32 pos,
                          const char * image,
                          s32 slider_size, s32 min_slider_size, 
                          const char * callback,
                          u32 colorNormal, u32 colorSelect, bool vert, bool active,
                          bool hide_mode)
{
	// 対応するプロパティリストを規定する。
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	// スクロールバーインタフェースにスクロールマネージャを登録する
	// m_scrBar.die() あるいは破棄と同時に delete されるので、この場でnewする
	m_scrBar.setScrollMgr(IMgrEntry::getMgr("solid", 10));

	// 起動関数のパラメータとして初期値を受け取る
	setInitPos(x, y);
	if(callback) {
		setStrC(m_callback, callback);
	}

	// スクロールバーインタフェースを初期化する
	bool res = m_scrBar.init(getNode(), order, 0, 0, width, height,
		minValue, maxValue,	// ScrollBarIF では0〜maxなので、minも含めた幅を持つbarを作る
		pos, image, slider_size, min_slider_size, callback, colorNormal, colorSelect, vert, active, hide_mode);
	
	if(res) {
		setOrder    (order);
		setWidth    (width);
		setHeight   (height);

		setMin(minValue);
		setMax(maxValue);

		setSliderSize(slider_size);
		setSliderSizeMin(min_slider_size);
		setStrC(m_image, image);
		setTouchActive(active);

		// Set right away because other setter depends on it.
		setVertical(vert);

		setAlphaNormal(colorNormal >> 24);
		setAlphaSelect(colorSelect >> 24);
		setColorNormal(colorNormal & 0xFFFFFF);
		setColorSelect(colorSelect & 0xFFFFFF);
	}

	return res;
}

u32
CKLBUIScrollBar::getClassID()
{
	return CLB_KLBUISCROLLBAR;
}

void
CKLBUIScrollBar::setMin(s32 value) 
{
	if(value != m_min) {
		if(value > m_max) { setMax(value); }
		if(value > m_pos) { setPos(value); }
		
		m_min = value;

		m_scrBar.setMinPosition(value);
	}
}

void
CKLBUIScrollBar::setMax(s32 value) 
{
	if(value != m_max) {
		if(value < m_min) { setMin(value); }
		if(value < m_pos) { setPos(value); }
		
		m_max = value;

		m_scrBar.setMaxPosition(value);
	}
}

void 
CKLBUIScrollBar::setPos(s32 value) 
{
	s32 iValue = getPos();

	if(value != iValue) {
		if(value < m_min) { value = m_min; }
		if(value > m_max) { value = m_max; }
		
		m_scrBar.setPosition(value);
		m_pos = value;
	}
}

void 
CKLBUIScrollBar::setColorMode(u32 mode, u32 color) 
{
	// OPTIMIZE : Can optimize on value change
	if(mode == 0) {
		m_alphaNormal = color >> 24;
		m_colorNormal = color & 0xFFFFFF;
	} else {
		m_alphaSelect = color >> 24;
		m_colorSelect = color & 0xFFFFFF;
	}
	m_scrBar.setColorMode(mode, color);
}

int
CKLBUIScrollBar::commandUI(CLuaState& lua, int argc, int cmd)
{
    if(argc < 2 || 3 < argc) { return 0; }
	int ret = 0;
	switch(cmd)
	{
	case UI_SCROLL_SET_MIN:
		setMin(lua.getInt(3));
		break;
	case UI_SCROLL_GET_MIN:
		lua.retInt(getMin()); ret = 1;
		break;
	case UI_SCROLL_SET_MAX:
		setMax(lua.getInt(3));
		break;
	case UI_SCROLL_GET_MAX:
		lua.retInt(getMax()); ret = 1;
		break;
	case UI_SCROLL_SET_POS:
		setPos(lua.getInt(3));
		break;
	case UI_SCROLL_GET_POS:
		lua.retInt(getPos()); ret = 1;
		break;
	case UI_SCROLL_SET_SLIDER_SIZE:
		setSliderSize(lua.getInt(3));
		break;
	case UI_SCROLL_GET_SLIDER_SIZE:
		lua.retInt(getSliderSize()); ret = 1;
		break;
	case UI_SCROLL_SET_SLIDER_MIN_SIZE:
		setSliderSizeMin(lua.getInt(3));
		break;
	case UI_SCROLL_GET_SLIDER_MIN_SIZE:
		lua.retInt(getSliderSizeMin()); ret = 1;
		break;
	case UI_SCROLL_SET_COLOR_NORMAL:
		setColorMode(0, lua.getInt(3) | (getColorMode(0) & 0xFF000000));
		break;
	case UI_SCROLL_GET_COLOR_NORMAL:
		lua.retInt(getColorMode(0) & 0xFFFFFF); ret = 1;
		break;
	case UI_SCROLL_SET_COLOR_SELECT:
		setColorMode(1, lua.getInt(3) | (getColorMode(1) & 0xFF000000));
		break;
	case UI_SCROLL_GET_COLOR_SELECT:
		lua.retInt(getColorMode(1) & 0xFFFFFF); ret = 1;
		break;
	case UI_SCROLL_SET_ALPHA_NORMAL:
		setColorMode(0, (lua.getInt(3)<<24) | (getColorMode(0) & 0xFFFFFF));
		break;
	case UI_SCROLL_GET_ALPHA_NORMAL:
		lua.retInt((getColorMode(0) >> 24) & 0xFF); ret = 1;
		break;
	case UI_SCROLL_SET_ALPHA_SELECT:
		setColorMode(1, (lua.getInt(3)<<24) | (getColorMode(1) & 0xFFFFFF));
		break;
	case UI_SCROLL_GET_ALPHA_SELECT:
		lua.retInt((getColorMode(1) >> 24) & 0xFF); ret = 1;
		break;
	case UI_SCROLL_SET_TOUCH_ACTIVE:
		setTouchActive(lua.getBool(3));
		break;
	case UI_SCROLL_GET_TOUCH_ACTIVE:
		lua.retInt(getTouchActive()); ret = 1;
		break;
	case UI_SCROLL_SELECT_SCRMGR:
		{
			bool bResult = false;
			if(argc >= 3) {
				const char * name = lua.getString(3);
				int ac = argc - 3;
				int * params = 0;
				if(ac > 0) {
					params = KLBNEWA(int, ac);
					for(int i = 0; i < ac; i++) {
						params[i] = lua.getInt(4 + i);
					}
				}
				bResult = selectScrMgr(name, ac, params);
				KLBDELETE(params);
			}
			lua.retBool(bResult);
			ret = 1;
		}
		break;
	}
	return ret;
}

void
CKLBUIScrollBar::dieUI()
{
	m_scrBar.die();
}

void
CKLBUIScrollBar::execute(u32 deltaT)
{
	// モーダルスタック中で動作が有効になっていればm_scrBarの処理を行う
	bool enable  = m_modalStack.isEnable();
	bool visible = getVisible();

	// scrollbar の挙動は、タスクの modal 状態と visible に同期させる
	m_scrBar.setEnable(enable);
	m_scrBar.setVisible(visible);

	// scrollbarのフレーム処理(enableとvisibleを与えた上で必ず呼び出す)
	m_scrBar.execute(deltaT);

	// 現在のバー位置をプロパティに反映する
	m_pos = m_scrBar.getBarPosition();
}
