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
#include "CKLBUIList.h"
#include "CKLBUtility.h"
#include "CKLBUISystem.h"
#include "CKLBTouchPad.h"
#include "CKLBTouchEventUI.h"
#include "CompositeManagement.h"
#include "CKLBLuaEnv.h"
#include "CKLBScriptEnv.h"
#include "CKLBFormGroup.h"

#include "CKLBUIScrollBar.h"
#include "IMgrEntry.h"
;

// Command Values
enum {
	UI_LIST_ITEM_ADD,		// アイテムを下端に追加
	UI_LIST_ITEM_INSERT,	// アイテムを指定位置に追加
	UI_LIST_ITEM_REMOVE,	// アイテムを削除
	UI_LIST_ITEM_MOVE,		// アイテムを移動

	UI_LIST_FWMODE_CONFIG,	// FW動作パラメータを設定する(保持アイテム最大数,アイテムのステップ値)
	UI_LIST_FWITEM_ADD,			// 下端にアイテムを追加する
	UI_LIST_FWITEM_INSERTTOP,	// 上端にアイテムを追加する
	UI_LIST_SET_MARGIN,		// リスト先端/終端のスクロール幅マージンを指定
	UI_LIST_SET_OFFSET,		// 指定したposが表示上あわされるラインの位置を指定(default: 0)

	UI_LIST_SET_LOOPMODE,	// ループモードを指定
	UI_LIST_SET_ITEMMODE,	// アイテム保持モードを指定

	UI_LIST_ITEM_REMOVE_SELECTION,	// 複数アイテムの選択同時破棄

	UI_LIST_ADD_RECORDS,	// 複数アイテムを同一のテンプレートを使用して一括追加する

	UI_LIST_SET_ITEM_ID,	// 指定されたindexのアイテムにIDを与える
	UI_LIST_SEARCH_ID,		// 指定されたIDを持つアイテムのindexを得る

	UI_LIST_SET_POSITION,	// スクロール位置合わせ
	UI_LIST_SET_INITIAL,	// 初期スクロール位置の設定
	UI_LIST_SET_DRAGRECT,	// Set scroll draggable area
	UI_LIST_SET_ITEM_POS,	// スクロール位置をアイテム位置に合わせる
	UI_LIST_GET_POSITION,	// スクロール位置

	UI_LIST_GET_LIMIT,		// スクロール上限値を得る
	UI_LIST_SET_LIMITCLIP,	// 上限/下限でストップするか否かのモードを設定する
	UI_LIST_SET_LIMITAREA,	// 超過スクロール警告コールバックが呼ばれる条件となる範囲のサイズを設定する

	UI_LIST_CHANGE_STEP,	// 指定アイテムの占有する幅を変更する

	UI_LIST_EXIST_NODE,		// 指定されたindexアイテムに指定された名称のノードがあるかを確認する
	UI_LIST_UPDATE_NODE,	// 指定indexのアイテムをUI_Form同様に更新する

	UI_LIST_INPUT_ENABLE,	// リスト単位でのパネル入力許可/禁止
	UI_LIST_ITEM_ENABLE,	// アイテム単位での操作許可/禁止

	UI_LIST_ANIM_CALLBACK,	// リストアニメーションのコールバック設定
	UI_LIST_ANIMATION_ITEM,	// リストアイテム単独のアニメーション
	UI_LIST_ANIMATION_ALL,	// リストの全アイテムアニメーション
	UI_LIST_ITEM_ANIM_SKIP,	// リストアイテム単独のアニメーションをスキップし終了状態にする
	UI_LIST_ALL_ANIM_SKIP,	// リストの全アイテムアニメーションをスキップし終了状態にする

	UI_LIST_USE_SCROLLBAR,	// リストのスクロールバーを有効にする
	UI_LIST_SELECT_SCRMGR,	// スクロールマネージャを変更する
	UI_LIST_SCRMGR_CALLBACK,// スクロールマネージャレベルでのコールバック指定(動作停止時に呼ばれる)
	UI_LIST_SET_GROUP,		// リストのグループを指定する
	UI_LIST_SET_CLIP,		// Reset clip.
	UI_LIST_GET_ITEMCOUNT,	// Get Count List Item.
	UI_LIST_GET_ITEMFORM,	// Return a form object if exist for a given item.
	UI_LIST_SET_DRAGMINDISTANCE, //
};
// コントロール用値
enum {
	LIST_VIEW_TOP,			// UI_LIST_SET_ITEM_POS の際、指定アイテムをリスト上端に合わせる
	LIST_VIEW_CENTER,		// UI_LIST_SET_ITEM_POS の際、指定アイテムをリスト中央に合わせる
	LIST_VIEW_END,			// UI_LIST_SET_ITEM_POS の際、指定アイテムをリスト下端に合わせる
	LIST_VIEW_OFFSET,		// UI_LIST_SET_ITEM_POS の際、指定アイテムをリスト中の指定された位置に合わせる
};

// スクロールオーバー値
enum {
	LIST_SCROVER_TOP,		// 上端が近づいた
	LIST_SCROVER_BOTTOM,	// 下端が近づいた
	LIST_SCROVER_TAKEOFF,	// 端から離れた
};

static IFactory::DEFCMD cmd[] = {
	// リストアイテムの操作
	{ "UI_LIST_ITEM_ADD",				UI_LIST_ITEM_ADD },
	{ "UI_LIST_ITEM_INSERT",			UI_LIST_ITEM_INSERT },
	{ "UI_LIST_ITEM_REMOVE",			UI_LIST_ITEM_REMOVE },
	{ "UI_LIST_ITEM_MOVE",				UI_LIST_ITEM_MOVE },
	{ "UI_LIST_ITEM_REMOVE_SELECTION",	UI_LIST_ITEM_REMOVE_SELECTION },


	{ "UI_LIST_FWMODE_CONFIG",			UI_LIST_FWMODE_CONFIG },
	{ "UI_LIST_FWITEM_ADD",				UI_LIST_FWITEM_ADD },
	{ "UI_LIST_FWITEM_INSERTTOP",		UI_LIST_FWITEM_INSERTTOP },

	{ "UI_LIST_SET_MARGIN",				UI_LIST_SET_MARGIN },

	{ "UI_LIST_SET_LOOPMODE",			UI_LIST_SET_LOOPMODE },
	{ "UI_LIST_SET_ITEMMODE",			UI_LIST_SET_ITEMMODE },

	{ "UI_LIST_ADD_RECORDS",			UI_LIST_ADD_RECORDS },

	{ "UI_LIST_SET_ITEM_ID",			UI_LIST_SET_ITEM_ID },
	{ "UI_LIST_SEARCH_ID",				UI_LIST_SEARCH_ID },

	// 表示位置のジャンプ
	{ "UI_LIST_SET_POSITION",			UI_LIST_SET_POSITION },
	{ "UI_LIST_SET_INITIAL",			UI_LIST_SET_INITIAL },
	{ "UI_LIST_SET_DRAGRECT",			UI_LIST_SET_DRAGRECT },

	{ "UI_LIST_SET_ITEM_POS",			UI_LIST_SET_ITEM_POS },
	{ "UI_LIST_GET_POSITION",			UI_LIST_GET_POSITION },

	{ "UI_LIST_GET_LIMIT",				UI_LIST_GET_LIMIT },
	{ "UI_LIST_SET_LIMITCLIP",			UI_LIST_SET_LIMITCLIP },
	{ "UI_LIST_SET_LIMITAREA",			UI_LIST_SET_LIMITAREA },

	{ "UI_LIST_CHANGE_STEP",			UI_LIST_CHANGE_STEP },
	{ "UI_LIST_EXIST_NODE",				UI_LIST_EXIST_NODE },
	{ "UI_LIST_UPDATE_NODE",			UI_LIST_UPDATE_NODE },

	{ "UI_LIST_INPUT_ENABLE",			UI_LIST_INPUT_ENABLE },
	{ "UI_LIST_ITEM_ENABLE",			UI_LIST_ITEM_ENABLE },

	{ "UI_LIST_ANIM_CALLBACK",			UI_LIST_ANIM_CALLBACK },
	{ "UI_LIST_ANIMATION_ITEM",			UI_LIST_ANIMATION_ITEM },
	{ "UI_LIST_ANIMATION_ALL",			UI_LIST_ANIMATION_ALL },

	{ "UI_LIST_ITEM_ANIM_SKIP",			UI_LIST_ITEM_ANIM_SKIP },
	{ "UI_LIST_ALL_ANIM_SKIP",			UI_LIST_ALL_ANIM_SKIP },

	// スクロールバーを使用する
	{ "UI_LIST_USE_SCROLLBAR",			UI_LIST_USE_SCROLLBAR },
	{ "UI_LIST_SELECT_SCRMGR",			UI_LIST_SELECT_SCRMGR },	// スクロールマネージャ選択
	{ "UI_LIST_SCRMGR_CALLBACK",		UI_LIST_SCRMGR_CALLBACK },	// スクロールマネージャコールバック指定

	// グループ指定
	{ "UI_LIST_SET_GROUP",				UI_LIST_SET_GROUP },

	{ "UI_LIST_SET_CLIP",				UI_LIST_SET_CLIP },

	{ "UI_LIST_GET_ITEMCOUNT",			UI_LIST_GET_ITEMCOUNT },
	{ "UI_LIST_GET_ITEMFORM",			UI_LIST_GET_ITEMFORM },

	{ "UI_LIST_SET_DRAGMINDISTANCE",	UI_LIST_SET_DRAGMINDISTANCE },

	{ "LIST_VIEW_TOP",					LIST_VIEW_TOP },
	{ "LIST_VIEW_CENTER",				LIST_VIEW_CENTER },
	{ "LIST_VIEW_END",					LIST_VIEW_END },
	{ "LIST_VIEW_OFFSET",				LIST_VIEW_OFFSET },

	{ "LIST_SCROVER_TOP",				LIST_SCROVER_TOP },
	{ "LIST_SCROVER_BOTTOM",			LIST_SCROVER_BOTTOM },
	{ "LIST_SCROVER_TAKEOFF",			LIST_SCROVER_TAKEOFF },

	{ "LIST_FLAG_BOTTOM",				CKLBUIList::LIST_FLAG_BOTTOM },
	{ "LIST_FLAG_MODAL",				CKLBUIList::LIST_FLAG_MODAL },

	{ "LIST_ITEM_NORMAL",				CKLBUIList::LIST_ITEM_NORMAL },
	{ "LIST_ITEM_DYNAMIC",				CKLBUIList::LIST_ITEM_DYNAMIC },

	{0, 0}
};

static CKLBTaskFactory<CKLBUIList> factory("UI_List", CLS_KLBUILIST, cmd);

CKLBLuaPropTask::PROP_V2 CKLBUIList::ms_propItems[] = {
	UI_BASE_PROP,
	{	"width",			UINTEGER,	(setBoolT)&CKLBUIList::setWidth,			(getBoolT)&CKLBUIList::getWidth,			0	},
	{	"height",			UINTEGER,	(setBoolT)&CKLBUIList::setHeight,			(getBoolT)&CKLBUIList::getHeight,			0	},
	{	"stepX",			INTEGER,	(setBoolT)&CKLBUIList::setStepX,			(getBoolT)&CKLBUIList::getStepX,			0	},
	{	"stepY",			INTEGER,	(setBoolT)&CKLBUIList::setStepY,			(getBoolT)&CKLBUIList::getStepY,			0	},
	{	"order",			UINTEGER,	(setBoolT)&CKLBUIList::setOrder,			(getBoolT)&CKLBUIList::getOrder,			0	},
	{	"maxodr",			UINTEGER,	(setBoolT)&CKLBUIList::setMaxOrder,			(getBoolT)&CKLBUIList::getMaxOrder,			0	},
	{	"vertical",			BOOLEANT,	(setBoolT)&CKLBUIList::setVertical,			(getBoolT)&CKLBUIList::getVertical,			0	},
	{	"items",			R_UINTEGER,	NULL,										(getBoolT)&CKLBUIList::getItems,			0	},
	{	"margin_top",		INTEGER,	(setBoolT)&CKLBUIList::setMarginTop,		(getBoolT)&CKLBUIList::getMarginTop,		0	},
	{	"margin_bottom",	INTEGER,	(setBoolT)&CKLBUIList::setMarginBottom,		(getBoolT)&CKLBUIList::getMarginBottom,		0	},
	{	"default_scroll",	BOOLEANT,	(setBoolT)&CKLBUIList::setDefaultScroll,	(getBoolT)&CKLBUIList::getDefaultScroll,	0	}
	// TODO : getTop, getBottom -> Added lately and was forgot in spec. (setMargin command)
};

enum {
	ARG_PARENT = 1,

	ARG_ORDER,
	ARG_MAXODR,

	ARG_X,
	ARG_Y,
	ARG_WIDTH,
	ARG_HEIGHT,

	ARG_STEP,
	ARG_VERTICAL,

	ARG_DRAGCALLBACK,
	ARG_OPTIONFLAGS,

	ARG_REQUIRE = ARG_STEP,
	ARG_NUMS    = ARG_OPTIONFLAGS
};

CKLBListDrag::CKLBListDrag(CKLBUIList * parent, const char * funcname)
: CKLBDragCallbackIF(funcname)
, m_pParent         (parent) 
{
}

CKLBListDrag::~CKLBListDrag() 
{
}

void
CKLBListDrag::callback(PAD_ITEM::TYPE type, int tap_x, int tap_y, int mv_x, int mv_y)
{
	m_pParent->m_scrBar.setCtrlStatus((type != PAD_ITEM::RELEASE) || (type != PAD_ITEM::CANCEL));
	execCallback((void *)m_pParent, type, tap_x, tap_y, mv_x, mv_y); 
}



CKLBUIList::CKLBUIList()
: CKLBUITask            (CKLBTask::P_UIAFTER)
, m_clipHandle          (NULL)
, m_listLength          (0)
, m_modalStack          (false)
, m_layoutTable         (NULL)
, m_layoutTableXY       (NULL)
, m_layoutTableScale    (NULL)
, m_layoutTableRotation (NULL)
, m_layoutTableAlpha    (NULL)
, m_layoutTableRGB      (NULL)
, m_layoutTablePriority (NULL)
, m_layoutTableLayout   (NULL)
, m_curveLength         (0)
, m_layoutInterlaceSize (0)
, m_dragCallback        (NULL)
, m_limitCallback       (NULL)
, m_dynamicCallback     (NULL)
, m_limitCalled         (false)
, m_limitAreaSize       (0)
, m_pCtrlNode           (NULL)
, m_pGroupName          (NULL)
, m_defaultPrePos       (-1)
, m_bTaped              (false)
, m_bLoop               (false)
, m_itemMode            (LIST_ITEM_NORMAL)
, m_scrOffset           (0)
, m_leftDrag            (0)
, m_rightDrag           (0)
, m_topDrag             (0)
, m_bottomDrag          (0)
, m_dragDistance        (0)
{
	m_scrBar = this;
	m_formIF = this;
	m_newScriptModel = true;
}

CKLBUIList::~CKLBUIList() 
{
}

u32
CKLBUIList::getClassID()
{
	return CLS_KLBUILIST;
}


CKLBUIList *
CKLBUIList::create(CKLBUITask * pParent, CKLBNode * pNode,
                   u32 base_order, u32 max_order,
                   float x, float y, float clip_width, float clip_height,
                   int default_line_step, bool vertical,
                   const char * callback, u32 optional_flags)
{
	CKLBUIList * pTask = KLBNEW(CKLBUIList);
    if(!pTask) { return NULL; }
	if(!pTask->init(pParent, pNode, base_order, max_order, 
					x, y, clip_width, clip_height, default_line_step,
					vertical, callback, optional_flags)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUIList::init(CKLBUITask * pParent, CKLBNode * pNode,
				 u32 base_order, u32 max_order,
				 float x, float y, float clip_width, float clip_height,
				 int default_line_step, bool vertical,
				 const char * callback, u32 optional_flags)
{
    if(!setupNode()) { return false; }

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(base_order, max_order,
							x, y, clip_width, clip_height,
							default_line_step, vertical, callback, optional_flags);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}

	return bResult;
}

bool
CKLBUIList::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < ARG_REQUIRE || argc > ARG_NUMS) return false;

	u32 base_order			= lua.getInt(ARG_ORDER);
	u32 max_order			= lua.getInt(ARG_MAXODR);

	float x					= lua.getFloat(ARG_X);
	float y 				= lua.getFloat(ARG_Y);
	float clip_width		= lua.getFloat(ARG_WIDTH);
	float clip_height		= lua.getFloat(ARG_HEIGHT);
	int	default_line_step	= lua.getInt(ARG_STEP);
	bool vertical			= (argc >= ARG_VERTICAL) ? lua.getBool(ARG_VERTICAL) : true;
	const char * callback	= (argc >= ARG_DRAGCALLBACK) ? ((lua.isString(ARG_DRAGCALLBACK)) ? lua.getString(ARG_DRAGCALLBACK): NULL) : NULL;
	u32 optional_flags		= (argc >= ARG_OPTIONFLAGS) ? lua.getInt(ARG_OPTIONFLAGS) : 0;

	return initCore(base_order, max_order, x, y, clip_width, clip_height, default_line_step, vertical, callback, optional_flags);
}

bool
CKLBUIList::initCore(u32 base_order, u32 max_order,
                     float x, float y, float clip_width, float clip_height,
                     int default_line_step, bool vertical,
                     const char * callback, u32 optional_flags)
{
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	klb_assert((((s32)base_order) >= 0), "Order Problem");
	klb_assert((((s32)max_order ) >= 0), "Order Problem");

	m_basePriority	= base_order;
	m_endPriority	= max_order;
	
	m_clipX			= x;
	m_clipY			= y;
	m_clipWidth		= (int)clip_width;
	m_clipHeight	= (int)clip_height;

	m_leftDrag		= 0;
	m_rightDrag		= m_clipWidth;
	m_topDrag		= 0;
	m_bottomDrag	= m_clipHeight;

	m_vertical		= vertical;
	m_chklimit		= true;
	m_touchenable	= true;
	m_bModalEnable	= true;

	if(callback) { m_dragCallback = KLBNEWC(CKLBListDrag, (this, callback)); }

	m_flags         = optional_flags;

	m_itemCnt		= 0;

	if(m_vertical) {
		m_stepX = 0;
		m_stepY = default_line_step;
	} else {
		m_stepX = default_line_step;
		m_stepY = 0;
	}

	setInitPos(m_clipX, m_clipY);
	m_width			= m_clipWidth;
	m_height		= m_clipHeight;
	m_marginTop		= 0;
	m_marginBottom	= 0;
	m_defScroll		= false;

	// リストアイテムをぶら下げるノードを作る。
	m_pCtrlNode = KLBNEW(CKLBNode);
	getNode()->addNode(m_pCtrlNode);

	m_ctrlX = m_ctrlY = 0;
	if(m_flags & LIST_FLAG_BOTTOM) {
		if(!m_vertical) {
			m_ctrlY = m_clipHeight;
		} else {
			m_ctrlX = m_clipWidth;
		}
	}
	m_scrollPos		= (m_vertical) ? m_ctrlY : m_ctrlX;
	m_enableEvents	= true;
	m_force			= true;

	m_clipSize  = (m_vertical) ? m_clipHeight : m_clipWidth;

	m_pCtrlNode->setTranslate(m_ctrlX, m_ctrlY);
	
	m_lstBegin	= m_lstEnd	= NULL;
	m_killBegin = m_killEnd = NULL;

	bool bResult = setClip(m_basePriority, m_endPriority, 0, 0, (s16)m_width, (s16)m_height);

	if(!bResult) {
		const char * msg = "Overlapping clipping range or Reached max UI clipping stack.";
		CKLBScriptEnv::getInstance().error(msg);
		klb_assertAlways(msg);
	}

	m_dragID = -1;
	m_dragX  = 0;
	m_dragY  = 0;

	bool modal = (m_flags & LIST_FLAG_MODAL) ? true : false;
	m_modalStack.setModal(modal);
	m_modalStack.push();

	// スクロールバーの準備
	m_scrBar.setScrollMgr(IMgrEntry::getMgr("default", 0));
	//useScrollBar(lua, max_order, true, 25, "", 25, 0, 0x80ffffff, 0xffffffff, true);
	m_scrBar.setVisible(false);

	m_itemUpdate = false;
	m_posUpdate  = false;

	REFRESH_A;
	REFRESH_B;

	return true;
}


bool
CKLBUIList::setItemMode(int mode, const char * dynamicCallback)
{
	bool bResult = false;

	// 既にアイテムが登録されており、異なるモードが設定されたらassertionで落とす
	klb_assert(!m_lstBegin && !m_lstEnd, "The list items are already registered. ");

	m_itemMode = mode;	// アイテム保持モードを設定する

	KLBDELETEA(m_dynamicCallback);
	m_dynamicCallback = NULL;

	switch(mode)
	{
	default:
		{
			// 未知の値。特に何もしない。
		}
		break;
	case LIST_ITEM_NORMAL:
		{
			// デフォルトの動作モード。
			bResult = true;
		}
		break;
	case LIST_ITEM_DYNAMIC:
		{
			// アイテムを通常は JSON 文字列で保持しておき、画面に出る時のみtree化する。
			m_dynamicCallback = CKLBUtility::copyString(dynamicCallback);
			bResult = true;
		}
		break;
	case LIST_ITEM_FLYWEIGHT:
		{
			// アイテムを一定数以上保持しない。既定の個数を超えたら
			bResult = true;
		}
		break;
	}
	return bResult;
}

int
CKLBUIList::cmdItemAdd(CLuaState& lua, int argc)
{
	bool bResult = false;
	if(argc >= 3 && argc <= 5) {
		int step = (m_vertical) ? m_stepY : m_stepX;
		if(argc >= 4) step = lua.getInt(4);
		int id = (argc >= 5) ? lua.getInt(5) : -1;
		bResult = itemInsertUniversal(0, step, lua, 3, id);	// 最後に追加するのでNULLを指定
	}
	lua.retBoolean(bResult);
	return 1;
}

bool
CKLBUIList::cmdItemAdd(const char* assetName)
{
	int step = (m_vertical) ? m_stepY : m_stepX;
	return itemAddInsert(NULL, assetName, step, -1);
}

bool
CKLBUIList::cmdItemAdd(const char* assetName, int step, int id)
{
	return itemAddInsert(NULL, assetName, step, id);
}

bool
CKLBUIList::itemAddInsert(LISTITEM * posItem, const char* assetName, int step, int id) 
{
	if(!assetName) { return false; }

	u32 size;
	const char* json = toJSON(assetName, size);

	itemInsert(posItem, step, json, size, id);
	KLBDELETEA(json);

	return true;
}

int
CKLBUIList::cmdItemInsert(CLuaState& lua, int argc)
{
	bool bResult = false;
	if(argc >= 4 && argc <= 5) {
		int idx = lua.getInt(4);
		int id = (argc >= 5) ? lua.getInt(5) : -1;
		int step = (m_vertical) ? m_stepY : m_stepX;
		LISTITEM * posItem = getItemByIndex(idx);
		// Safe against NULL posItem
		bResult = itemInsertUniversal(posItem, step, lua, 3, id);
	}
	lua.retBoolean(bResult);
	
	return 1;
}

bool
CKLBUIList::cmdItemInsert(const char* assetName, int idx)
{
	int step = (m_vertical) ? m_stepY : m_stepX;

	LISTITEM * posItem = getItemByIndex(idx);
	return itemAddInsert(posItem, assetName, step, -1);
}

bool
CKLBUIList::cmdItemInsert(const char* assetName, int idx, int step, int id)
{
	LISTITEM * posItem = getItemByIndex(idx);
	return itemAddInsert(posItem, assetName, step, id);
}

bool
CKLBUIList::cmdItemRemove(int idx)
{
	LISTITEM * posItem = getItemByIndex(idx);
	if (posItem) { itemDelete(posItem); }
	return ((posItem) != NULL);
}

void
CKLBUIList::cmdItemMove(int src, int dst)
{
	if(src != dst) {
		LISTITEM * posItem = getItemByIndex(src);

		// 挿入先indexのアイテムを取得し、その位置に挿入する
		LISTITEM * dstItem = getItemByIndex(dst);

		if (posItem && dstItem) {
			// 一回アイテムを抜き取る
			if(posItem->prev) {
				posItem->prev->next = posItem->next;
			} else {
				m_lstBegin = posItem->next;
			}
			if(posItem->next) {
				posItem->next->prev = posItem->prev;
			} else {
				m_lstEnd = posItem->prev;
			}

			posItem->next = dstItem;
			if(dstItem) {
				posItem->prev = dstItem->prev;
				posItem->next = dstItem;
				dstItem->prev = posItem;
			} else {
				posItem->prev = m_lstEnd;
				posItem->next = NULL;
				m_lstEnd = posItem;
			}
			if(posItem->prev) {
				posItem->prev->next = posItem;
			} else {
				m_lstBegin = posItem;
			}
			m_posUpdate = true;
			m_itemUpdate = true;
		}
	}
}

int
CKLBUIList::cmdItemRemoveSelection(CLuaState& lua, int argc)
{
	bool result = true;
	if(argc != 3) {
		lua.retBoolean(false);
		return 1;
	}

	// pass-1: 現在のアイテム数をカウントする
	int count = 0;
	LISTITEM * posItem = m_lstBegin;
	while(posItem) {
		count++;
		posItem = posItem->next;
	}
	if(!count) {
		// アイテムが無い場合は何もしない
		lua.retBoolean(result);
		return 1;
	}
	// pass-2: 現在のアイテムポインタの配列を作り、各ポインタを格納する。
	LISTITEM ** arrItem = KLBNEWA(LISTITEM *, count);
	if(!arrItem) {
		lua.retBoolean(false);
		return 1;
	}
	posItem = m_lstBegin;
	int index = 0;
	while(posItem) {
		arrItem[index] = posItem;
		index++;
		posItem = posItem->next;
	}

	// pass-3: lua配列で指定されたindexに該当するアイテムを破棄する。
	lua.retValue(3);
	lua.retNil();
	while(lua.tableNext()) {
		index = lua.getInt(-1);	// index を取得
		if(index >= 0 && index < count) {
			posItem = arrItem[index];
			if(posItem) itemDelete(posItem);
			arrItem[index] = 0;
		} else {
			result = false;	// 存在しないindexが指定されている。
		}
		lua.pop(1);
	}
	lua.pop(1);

	// ポインタ配列として確保したバッファを破棄する
	KLBDELETEA(arrItem);

	lua.retBoolean(result);
	return 1;
}

bool
CKLBUIList::cmdItemRemoveSelection(int* idxList, u32 nbItems)
{
	bool result = true;
	LISTITEM ** arrItem = KLBNEWA(LISTITEM *, m_itemCnt);
	if(!arrItem) {
		return false;
	}
	LISTITEM * posItem = m_lstBegin;
	int index = 0;
	while(posItem) {
		arrItem[index] = posItem;
		index++;
		posItem = posItem->next;
	}

	for(u32 i = 0; i < nbItems; ++i) {
		if(idxList[i] && idxList[i] < m_itemCnt) {
			posItem = arrItem[idxList[i]];
			if(posItem) { itemDelete(posItem); }
			arrItem[idxList[i]] = 0;
		} else {
			result = false;
		}
	}

	KLBDELETEA(arrItem);

	return result;
}

void
CKLBUIList::cmdFWModeConfig(int itemStep, int maxItems)
{
	m_flyweight.itemstep = itemStep;	// アイテム一個あたりが占有する幅
	m_flyweight.maxitems = maxItems;	// 保持し続けるアイテムの最大数
}

void
CKLBUIList::cmdFWItemAdd()
{
	// TODO
}

void
CKLBUIList::cmdFWItemInsert()
{
	// TODO
}

void
CKLBUIList::cmdSetMargin(int top, int bottom)
{
	setMarginTop(top);
	setMarginBottom(bottom);

	// スクロールバー経由でスクロールマネージャにも通知する
	m_scrBar.setMargin(top, bottom);

	m_itemUpdate = true;	// 配置が変更される。
}

bool
CKLBUIList::cmdSetItemMode(int mode, const char* dynamicCallback)
{
	bool bResult = false;

	if(mode != LIST_ITEM_DYNAMIC) { dynamicCallback = NULL; }
	bResult = setItemMode(mode, dynamicCallback);

	return bResult;
}


bool
CKLBUIList::cmdAddRecords(int insIdx, const char* tpform, u32 sizeTemplate, const char* dbrecs, u32 sizeDBRec, int step)
{
	u32 handle          = 0;
	LISTITEM * posItem  = getItemByIndex(insIdx);
	int itemPos         = posItem ? posItem->pos : 0;
	 
	// pNode と handle を作る
	CKLBAssetManager& pAssetManager = CKLBAssetManager::getInstance();
	CKLBCompositeAsset * pAsset = (CKLBCompositeAsset *)CKLBUtility::readAsset((u8 *)tpform, sizeTemplate, &handle, pAssetManager.getPlugin('P'));
	if(!pAsset) {
		return false;
	}
	if(!step) { step = (m_vertical) ? pAsset->get_height() : pAsset->get_width(); }

	IDataSource * pSource = JSonDB::openDB((const u8 *)dbrecs, sizeDBRec);
	pSource->moveTo(0);	// 先頭にジャンプ

	bool bResult = true;
	int addLen = 0;
	do {
		addLen += step;
		bResult = bResult && itemInsert(posItem, step, tpform, sizeTemplate,-1, pAsset, pSource);
	} while (pSource->moveNext() != MOVE_EOF);

	KLBDELETE(pSource);
	if(-m_scrollPos >= itemPos) {
		m_scrollPos -= addLen;
	}

	return bResult;
}

int
CKLBUIList::cmdSetPosition(int pos, int dir)
{
	int retPos = setPosition(pos);	// その値に「なったとき」の位置を取得

	// 実際の表示はスクロールバーのスクロールマネージャ経由
	m_scrBar.setPosition(pos, dir);
	pos = m_scrBar.getPosition();
	setPosition(pos);
	return retPos;
}

int
CKLBUIList::cmdSetInitial(int pos)
{
	m_itemUpdate = true;
	itemRealloc();	// アイテム配置を行う(リストの長さを求める)
	
	int retPos = setPosition(pos);	// その値に「なったとき」の位置を取得

	// 実際の表示はスクロールバーのスクロールマネージャ経由
	m_scrBar.setInitial(pos);
	pos = m_scrBar.getPosition();
	setPosition(pos);

	return retPos;
}

int
CKLBUIList::cmdGetPosition()
{
	return -m_scrollPos;
}

void
CKLBUIList::cmdSetItemID(int index, int id)
{
	LISTITEM * posItem = getItemByIndex(index);
	if (posItem) {
		set_item_id(posItem, id);
	}
}

int
CKLBUIList::cmdSearchID(int id)
{
	return get_item_index_by_id(id);
}

void
CKLBUIList::cmdSetItemPos(int mode, int idx, int offset)
{
    if(idx < 0)         { idx = 0;         }
	if(idx > m_itemCnt) { idx = m_itemCnt; }

	// まだ位置が確定していないアイテムが存在する可能性があるため、
	// 位置を確定させる。
	itemRealloc();

	LISTITEM * posItem = getItemByIndex(idx);

	if (posItem) {
		int pos     = posItem->pos;
		int step    = posItem->step;
		int mergin  = m_clipSize;

		switch(mode) {
		case LIST_VIEW_TOP:		break;
		case LIST_VIEW_CENTER:	pos = pos - (mergin - step) / 2;    break;
		case LIST_VIEW_END:		pos = pos - (mergin - step);        break;
		case LIST_VIEW_OFFSET:	pos = pos - offset;                 break;
		}

		//itemRealloc();
		setPosition(pos);
	}
}

void
CKLBUIList::cmdChangeStep(int idx, int step)
{
    if(idx < 0)         { idx = 0;         }
	if(idx > m_itemCnt) { idx = m_itemCnt; }

	LISTITEM * posItem = getItemByIndex(idx);
	if (posItem) {
		// step 値を再設定
		posItem->step = step;
		m_itemUpdate = true;
		// itemRealloc();	// 再設定したSTEP値で位置を再計算
	}
}

void
CKLBUIList::cmdSetLimitClip(bool chklimit, const char* limitCallback)
{
	m_chklimit = chklimit;
	m_scrBar.setOverScroll(m_bLoop || !m_chklimit);
	if(limitCallback) { setStrC(m_limitCallback, limitCallback); }
}

bool
CKLBUIList::cmdSetLimitArea(int limitArea)
{
	if(limitArea >= 0) {
		m_limitAreaSize = limitArea;
		return true;
	}
	return false;
}

int
CKLBUIList::cmdGetLimit()
{
	if(m_itemUpdate) { 
		itemRealloc(); 
	}
	return m_listLength - ((m_vertical) ? m_clipHeight : m_clipWidth);
}

bool
CKLBUIList::cmdExistNode(int index, const char* name)
{
	if(m_itemMode == LIST_ITEM_DYNAMIC) { CKLBScriptEnv::getInstance().error("[UI_List] could not update node on DYNAMIC item mode."); }
	LISTITEM * posItem = getItemByIndex(index);
	if (posItem) {
		CKLBNode * pParent = posItem->form;
		return m_formIF.isExistNode(pParent, name);
	} else {
		return false;
	}
}

int
CKLBUIList::cmdUpdateNode(CLuaState& lua, int argc)
{
	if(argc < 5) {
		lua.retBoolean(false);
		return 1;
	}
	int index = lua.getInt(3);
	// const char * name = lua.getString(4);
	int subcmd = lua.getInt(5);
	LISTITEM * posItem = getItemByIndex(index);
	if (posItem) {
		if(m_itemMode == LIST_ITEM_DYNAMIC && !posItem->form) {
			CKLBScriptEnv::getInstance().error("[UI_List] could not update node on DYNAMIC item mode.");
		}
		CKLBNode * pParent = posItem->form;
		return m_formIF.updateNode(lua, argc, 5, pParent, 4, subcmd, posItem, index);
	} else {
		lua.retBoolean(false);
		return 1;
	}
}

void
CKLBUIList::cmdInputEnable(bool bEnable)
{
	m_touchenable = bEnable;
	updateEnable();
	// DEBUG_PRINT("InputEnable: %p = %s", this, (bEnable) ? "true" : "false");
}

void
CKLBUIList::cmdAnimCallback(const char* callback)
{
	m_animpack.setCallback(callback);
}

bool
CKLBUIList::cmdAnimationItem(int idx, const char* name, bool blend)
{
	// idx の値から、アイテムのnodeを取得する
	LISTITEM * item = getItemByIndex(idx);
	if (item) {
		return m_animpack.kickAnim(item->form, name, blend, idx);
	} else {
		return false;
	}
}

bool
CKLBUIList::cmdAnimationAll(const char* name, bool blend)
{
	return m_animpack.kickAnim(getNode(), name, blend, -1);
}

bool
CKLBUIList::cmdItemAnimSkip(int index, const char* name)
{
	// idx の値から、アイテムのnodeを取得する
	LISTITEM * item = getItemByIndex(index);
	if (item) {
		return m_animpack.skipAnim(item->form, name);
	} else {
		return false;
	}
}

bool
CKLBUIList::cmdAllAnimSkip(const char* name)
{
	return m_animpack.skipAnim(getNode(), name);
}

bool
CKLBUIList::cmdSelectScrMgr(const char* name, int* params, int nb)
{
	CKLBScrollMgr * pMgr = IMgrEntry::getMgrByArray(name, nb, params); 
    if(pMgr) { m_scrBar.setScrollMgr(pMgr); }

	m_scrBar.setInitial(-m_scrollPos);
	int pos = m_scrBar.getPosition();
	setPosition(pos);
	return (pMgr != NULL) ? true : false;
}

bool
CKLBUIList::cmdScrMgrCallback(const char* callback)
{
	return m_scrBar.setScrMgrCallback(this, callback);
}

void
CKLBUIList::cmdSetGroup(const char* group_name)
{	
	setStrC(m_pGroupName, group_name);

	if(m_pGroupName) {
		CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();
		// 既存のアイテムをすべてそのグループに所属させる
		LISTITEM * pItem = m_lstBegin;
		while(pItem) {
			fGrp.addForm(&(pItem->ctrl), m_pGroupName);
			pItem = pItem->next;
		}
	}
}

void
CKLBUIList::cmdSetClip(u32 orderBegin, u32 orderEnd, s16 clipX, s16 clipY, s16 clipWidth, s16 clipHeight) 
{
	resetClip(orderBegin, orderEnd, clipX, clipY, clipWidth, clipHeight, false);
}

int
CKLBUIList::cmdGetItemCount(CLuaState& lua, int /*argc*/) 
{
	lua.retInt(m_itemCnt);
	return 1;
}

int
CKLBUIList::cmdGetItemForm(CLuaState& lua, int argc) 
{
	void* ptr = NULL;

	if(argc == 3) {
		int idx = lua.getInt(3);
		if((idx >= 0) && (idx < m_itemCnt)) {
			LISTITEM * pItem = NULL;
			CKLBNode* pNode = NULL;

			switch(m_itemMode)
			{
			case LIST_ITEM_NORMAL:
			case LIST_ITEM_DYNAMIC:
				{
					// Same logic for both.
					// int item_index = 0;
					for(pItem = m_lstBegin; pItem; pItem = pItem->next) {
						if (pItem->index == idx) { pNode = pItem->form; break; }
					}

					if (pNode) {
						CKLBUITask* pTask = pNode->getUITask();
						if (pTask->getClassID() == CLS_KLBUIFORM) {
							ptr = pTask;
						}
					}
				}
				break;
			}
			if(ptr) {
				lua.retPointer(ptr);
				return 1;
			}
		}
		lua.retNil();
	} else {
		lua.retBool(false);
	}
	return 1;
}

int 
CKLBUIList::cmdSetDragRect(CLuaState& lua, int argc) 
{
	if(argc == 6) {
		setDragRect(lua.getInt(3),lua.getInt(4),lua.getInt(5),lua.getInt(6));
	} else {
		lua.retBool(false);
	}
	return 1;
}

void 
CKLBUIList::setDragRect(s32 left, s32 top, s32 right, s32 bottom) {
	m_leftDrag   = left;
	m_rightDrag  = right;
	m_topDrag    = top;
	m_bottomDrag = bottom;
}

// 物理位置を設定するだけの関数
int
CKLBUIList::setPosition(int pos)
{
	if(m_chklimit && !m_bLoop) {
		if(pos >= m_listLength - m_clipSize)    { pos = m_listLength - m_clipSize; }
        if(pos < 0)                             { pos = 0;                         }
	}

	m_scrollPos = -pos;

	// itemRealloc();
	m_posUpdate = true;
	return -m_scrollPos;
}

bool
CKLBUIList::useScrollBar(u32 order, bool side, int lineWeight,
						const char * image, int min_slider_size, const char * callback,
						u32 colorNormal, u32 colorSelect, bool active, bool hide_mode, bool short_hide)
{
	int x       = 0;
	int y       = 0;
	int width   = m_clipWidth;
	int height  = m_clipHeight;
	int pos     = 0;
	if(m_vertical) {
		x       = (side) ? (m_clipWidth - lineWeight) : 0;
		width   = lineWeight;
	} else {
		y       = (side) ? (m_clipHeight - lineWeight) : 0;
		height  = lineWeight;
	}
	pos = -m_scrollPos;
	int limit       = (int)(m_listLength - m_clipSize);
	int slider_size = m_clipSize * m_clipSize / limit;
	//CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	bool bResult    = m_scrBar.init(getNode(),
                                    order, (float)x, (float)y, (float)width, (float)height,
                                    0, limit,
                                    pos,
                                    image,
                                    slider_size, min_slider_size,
                                    callback,
                                    colorNormal, colorSelect, m_vertical, active, hide_mode);
	m_scrBar.setShortHide(short_hide);
	m_scrBar.setVisible(bResult);
	return bResult;
}

bool
CKLBUIList::useScrollBarByProperty(CKLBPropertyBag * pProp, u32 priorityOffset)
{
	u32				order			= pProp->getPropertyInt("order");
	bool			side			= pProp->getPropertyBool("side");
	int				lineWeight		= pProp->getPropertyInt("line_weight");
	const char	*	image			= pProp->getPropertyString("slider_image");
	int				min_slider_size = pProp->getPropertyInt("min_slider_size");
	const char	*	callback		= (pProp->getIndex("callback") >= 0) ? pProp->getPropertyString("callback") : NULL;
	u32				colorNormal		= pProp->getPropertyInt("normal_RGBA");
	u32				colorSelect		= pProp->getPropertyInt("select_RGBA");
	bool			active			= pProp->getPropertyBool("active");

	bool			hide_mode		= (pProp->getIndex("hide_mode") >= 0) ? pProp->getPropertyBool("hide_mode") : false;
	bool			default_scroll	= (pProp->getIndex("default_scroll") >= 0) ? pProp->getPropertyBool("default_scroll") : false;

	setDefaultScroll(default_scroll);

	char * path = KLBNEWA(char, strlen(image) + 9);
	strcpy(path, "asset://");
	strcat(path, image);
	
	bool bResult = useScrollBar(priorityOffset + order, side, lineWeight, path, min_slider_size, callback, colorNormal, colorSelect, active, hide_mode);

	KLBDELETEA(path);

	return bResult;
}

bool
CKLBUIList::selectScrollMgr(const char * manager_name, int argc, int * params)
{
	CKLBScrollMgr * pMgr = IMgrEntry::getMgrByArray(manager_name, argc, params); 
    if(pMgr) { m_scrBar.setScrollMgr(pMgr); }
	KLBDELETE(params);
	bool bResult = (pMgr != 0) ? true : false;
	return bResult;
}

bool
CKLBUIList::selectScrollMgrByProperty(CKLBPropertyBag * pProp)
{
	CKLBScrollMgr * pMgr = IMgrEntry::getMgrByProperty(pProp); 
	if(pMgr) m_scrBar.setScrollMgr(pMgr);
	bool bResult = (pMgr != 0) ? true : false;
	return bResult;
}

int
CKLBUIList::commandUI(CLuaState& lua, int argc, int cmd)
{
	bool result = false;
	int  ret    = 1;	// Default.
	switch(cmd)
	{
	default:
		{
			lua.retBoolean(false);
		}
		break;
	case UI_LIST_ITEM_ADD:				ret = cmdItemAdd(lua, argc);			break;
	case UI_LIST_ITEM_INSERT:			ret = cmdItemInsert(lua, argc);         break;	
	case UI_LIST_ITEM_REMOVE:
		if(argc == 3) {
			int idx = lua.getInt(3);
			result = cmdItemRemove(idx);
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_ITEM_MOVE:
		if(argc == 4) {
			int src = lua.getInt(3);
			int dst = lua.getInt(4);
			cmdItemMove(src,dst);
			result = true;
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_ITEM_REMOVE_SELECTION: ret = cmdItemRemoveSelection(lua, argc);    break;
	case UI_LIST_SET_ITEM_ID:
		if(argc == 4) {
			int index	= lua.getInt(3);
			int id		= lua.getInt(4);
			cmdSetItemID(index,id);
			result = true;
		}
		lua.retBool(result);
		break;
	case UI_LIST_SEARCH_ID:
		if(argc == 3) {
			int id = lua.getInt(3);
			int idx = cmdSearchID(id);
			if(idx < 0) {
				lua.retNil();
			} else {
				lua.retInt(idx);
			}
		} else {
			lua.retNil();
		}
		break;
	case UI_LIST_FWMODE_CONFIG:
		if(argc == 4) {
			int itemStep = lua.getInt(3);
			int maxItems = lua.getInt(4);
			cmdFWModeConfig(itemStep, maxItems);
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_FWITEM_ADD:
		ret = 0;
		break;
	case UI_LIST_FWITEM_INSERTTOP:
		ret = 0;
		break;
	case UI_LIST_SET_MARGIN:
		if(argc == 4) {
			int top		= lua.getInt(3);
			int bottom	= lua.getInt(4);
			cmdSetMargin(top, bottom);
		}
		lua.retBool(result);
		break;
	case UI_LIST_SET_LOOPMODE:
		if (argc == 3) {
			bool bLoop = lua.getBool(3);
			setLoop(bLoop);
			result = true;
		}
		lua.retBool(result);
		break;
	case UI_LIST_SET_ITEMMODE: 
		if(argc >= 3 && argc <= 4) {
			int mode = lua.getInt(3);
			const char * dynamicCallback = (argc >= 4) ? lua.getString(4) : NULL;
			result = cmdSetItemMode(mode, dynamicCallback);
		}
		lua.retBool(result);
		break;
	case UI_LIST_ADD_RECORDS:
		if(argc >= 5 && argc <= 6) {
			int insIdx = lua.getInt(3);				// 挿入位置index
			u32 sizeTemplate;
			u32 sizeDBRec;
			const char * tpform = toJSON(lua, 4, sizeTemplate);	// テンプレートフォーム
			const char * dbrecs = toJSON(lua, 5, sizeDBRec);	// DBデータ群
			int step = (argc >= 6) ? lua.getInt(6) : 0;
	
			result = cmdAddRecords(insIdx, tpform, sizeTemplate, dbrecs, sizeDBRec, step);

			KLBDELETEA(tpform);
			KLBDELETEA(dbrecs);
		}
		lua.retBool(result);
		break;
	case UI_LIST_SET_POSITION:
		if(argc >= 3 && argc <= 4) {
			int pos		= lua.getInt(3);
			int dir		= (argc >= 4) ? lua.getInt(4) : 0;
			int retPos	= cmdSetPosition(pos, dir);
			lua.retInt(retPos);
		} else {
			lua.retBool(result);
		}
		break;
	case UI_LIST_SET_INITIAL:
		if(argc == 3) {
			int pos = lua.getInt(3);
			int retPos = cmdSetInitial(pos);
			lua.retInt(retPos);
		} else {
			lua.retBool(result);
		}
	case UI_LIST_SET_DRAGRECT:			ret = cmdSetDragRect(lua, argc);		break;
	case UI_LIST_GET_POSITION:
		if(argc != 2) {
			lua.retBool(false);
		} else {
			s32 val = cmdGetPosition();
			lua.retInt(val);
		}
		break;
	case UI_LIST_SET_ITEM_POS:
		if(argc >= 4 && argc <= 5) {
			int mode    = lua.getInt(3);
			int idx     = lua.getInt(4);
			int offset  = (mode == LIST_VIEW_OFFSET) ? 0 : lua.getInt(5);

			if (!(mode != LIST_VIEW_OFFSET && argc == 5)) {
				cmdSetItemPos(mode, idx, offset);
				result = true;
			}
		}
		lua.retBool(result);
		break;
	case UI_LIST_CHANGE_STEP:
		if(argc == 4) {
			int idx 	= lua.getInt(3);
			int step 	= lua.getInt(4);
			cmdChangeStep(idx, step);
			result = true;
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_SET_LIMITCLIP:
		if(argc >= 3 && argc <= 4) {
			bool chklimit = lua.getBool(3);
			const char* limitCallback = NULL;
			if(argc == 4) {
				// 終端越えコールバックを設定
				if(lua.isString(4)) limitCallback = lua.getString(4);
			}

			cmdSetLimitClip(chklimit, limitCallback);
			result = true;
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_SET_LIMITAREA:
		if(argc == 3) {
			int limitArea = lua.getInt(3);
			result = cmdSetLimitArea(limitArea);
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_GET_LIMIT:
		if(argc != 2) {
			lua.retBoolean(false);
		} else {
			lua.retInt(cmdGetLimit());
		}
		break;
	case UI_LIST_INPUT_ENABLE:
		if(argc == 3) {
			bool bEnable = lua.getBool(3);
			cmdInputEnable(bEnable);
			result = true;
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_EXIST_NODE:
		if(argc == 4) {
			int index			= lua.getInt(3);
			const char * name	= lua.getString(4);
			
			result = cmdExistNode(index, name);
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_UPDATE_NODE:			ret = cmdUpdateNode(lua, argc);			break;
	case UI_LIST_ANIM_CALLBACK:
		if(argc == 3) {
			const char * callback = (lua.isNil(3)) ? NULL : lua.getString(3);
			cmdAnimCallback(callback);
			result = true;
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_ANIMATION_ITEM:
		if(argc >= 4 && argc <= 5) {
			int idx = lua.getInt(3);
			const char * name = lua.getString(4);
			bool blend = (argc >= 5) ? lua.getBool(5) : false;
			result = cmdAnimationItem(idx, name, blend);
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_ANIMATION_ALL:
		if (argc >= 3 && argc <= 4) {
			const char * name = lua.getString(3);
			bool blend = (argc >= 4) ? lua.getBool(4) : false;
			result = cmdAnimationAll(name, blend);
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_ITEM_ANIM_SKIP:
		if(argc >= 3 && argc <= 4) {
			int idx = lua.getInt(3);
			const char * name = NULL;
            if(argc >= 4 && !lua.isNil(4)) { name = lua.getString(4); }
			result = cmdItemAnimSkip(idx, name);
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_ALL_ANIM_SKIP:
		if(argc >= 2 && argc <= 3) {
			const char * name = NULL;
            if(argc >= 3 && !lua.isNil(3)) { name = lua.getString(3); }
			result = cmdAllAnimSkip(name);
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_SET_DRAGMINDISTANCE:
		if(argc == 3) {
			int v = lua.getInt(3);
			// Return only positive value, else scroll would become impossible.
			m_dragDistance = (v < 0) ? 0 : v;	
		}
		break;
	case UI_LIST_USE_SCROLLBAR:
		if(argc >= 13 && argc <= 15) {
			u32 order			= lua.getInt(3);
			bool side			= lua.getBoolean(4);
			int lineWeight		= lua.getInt(5);
			const char * image	= lua.getString(6);
			int min_slider_size = lua.getInt(7);
			const char * callback = (lua.isNil(8)) ? NULL : lua.getString(8);
			u32 alphaNormal		= lua.getInt(9);
			u32 colorNormal		= (lua.getInt(10) & 0xffffff) | (alphaNormal << 24);
			u32 alphaSelect		= lua.getInt(11);
			u32 colorSelect		= (lua.getInt(12) & 0xffffff) | (alphaSelect << 24);
			bool active			= lua.getBool(13);
			bool hide_mode		= (argc >= 14) ? lua.getBool(14) : false;
			bool short_hide		= (argc >= 15) ? lua.getBool(15) : true;

			// リストに合わせてスクロールバーを呼び出す
			result = useScrollBar(	order, side, lineWeight,
									image, min_slider_size, callback,
									colorNormal, colorSelect, active, hide_mode, short_hide);
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_SELECT_SCRMGR:
		if(argc >= 3) {
			const char * name = lua.getString(3);
			int ac = argc - 3;
			int * params = NULL;
			if(ac > 0) {
				params = KLBNEWA(int, ac);
				for(int i = 0; i < ac; i++) {
					params[i] = lua.getInt(4 + i);
				}
			}

			cmdSelectScrMgr(name, params, ac);

			KLBDELETEA(params);
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_SCRMGR_CALLBACK:
		if(argc == 3) {
			const char * callback = lua.getString(3);
			result = cmdScrMgrCallback(callback);
		}
		lua.retBoolean(result);
		break;
	case UI_LIST_SET_GROUP:				
		if(argc == 3) {
			const char * name = lua.getString(3);
			if(name) {
				cmdSetGroup(name);
				result = true;
			}
		}
		lua.retBool(result);
		break;
	case UI_LIST_SET_CLIP:
		if(argc == 8) {
			u32 orderBegin	= lua.getInt(3);
			u32 orderEnd	= lua.getInt(4);
			s16 clipX		= lua.getInt(5);
			s16 clipY		= lua.getInt(6);
			s16 clipWidth	= lua.getInt(7);
			s16 clipHeight	= lua.getInt(8);

			cmdSetClip(orderBegin, orderEnd, clipX, clipY, clipWidth, clipHeight);
			result = true;
		}
		lua.retBool(result);
		break;
	case UI_LIST_GET_ITEMCOUNT:			ret = cmdGetItemCount(lua,argc);		break;
	case UI_LIST_GET_ITEMFORM:			ret = cmdGetItemForm(lua,argc);			break;
	}
	return ret;
}

void
CKLBUIList::updateEnable()
{
	// モーダル状態による操作許可と、
	// リスト全体の操作許可から、現在リストが操作されるべきかの値を作る
	bool totalEnable = m_bModalEnable && m_touchenable;

	// リスト個別の許可情報と併せて、現在それぞれのリストが操作されるべきかを決める。
	LISTITEM * pItem;
	for(pItem = m_lstBegin; pItem; pItem = pItem->next) {
		pItem->ctrl.bEnable = pItem->enable && totalEnable;
	}
}

void CKLBUIList::setVisible(bool visible) {
	//
	// Do not comment out : some scripters used the setup of setVisible to force
	// refresh --> Was not pushed to modalstack even if visible.
	//
	//if (visible != getVisible()) {
		if(visible) {
			m_modalStack.push();
		} else {
			m_modalStack.remove();
		}
		m_scrBar.setVisible(visible);
		CKLBUITask::setVisible(visible);
	//}
}

void
CKLBUIList::execute(u32 deltaT)
{
	if(CHANGE_A) {
		bool visible = getVisible();
		if(visible) {
			m_modalStack.push();
		} else {
			m_modalStack.remove();
		}
		m_scrBar.setVisible(visible);

		if(CHANGE_B) {
			m_clipX = getX();
			m_clipY = getY();

			// マージンをスクロールバー経由でスクロールマネージャに通知する
			m_scrBar.setMargin(m_marginTop, m_marginBottom);
			m_itemUpdate = true;
			RESET_B;
		}

		RESET_A;
	}
	
	// 削除予約されたアイテムがあれば真っ先に処理する。
	itemCleanUp();

	m_bModalEnable = m_modalStack.isEnable();
	updateEnable();
	m_scrBar.setEnable(m_bModalEnable);

	m_scrBar.execute(deltaT);
	setPosition(m_scrBar.getPosition());
	if((m_scrBar.isScrolling()) || (m_force)) {
		// Disable list item click / events...
		if((m_enableEvents) || (m_force)) {
			m_enableEvents	= false;
			m_force			= false;

			LISTITEM*	parse = m_lstBegin;
			while(parse) {
				parse->ctrl.bWorking = true;
				// Do not : fGrp.setWorking(&parse->ctrl, true);
				parse = parse->next;
			}
		}
	} else {
		// Enable list item click / events...
		if((!m_enableEvents) || (m_force)) {
			m_enableEvents = true;
			m_force			= false;

			LISTITEM*	parse = m_lstBegin;
			while(parse) {
				parse->ctrl.bWorking = false;
				// Do not : fGrp.setWorking(&parse->ctrl, false);
				parse = parse->next;
			}
		}
	}

	bool visible = getVisible();
	if(visible) { itemRealloc(); }

	m_animpack.watchFinishedAnim(this);
	if(m_bModalEnable && m_touchenable && visible && m_pUINode->isVisible()) { touchpadEvent(); }
}

void
CKLBUIList::dieUI()
{
	m_modalStack.remove();

	// 削除予約リストにアイテムが残っていれば、先に破棄する。
	// 子タスクのkillは行わずともよい。
	itemCleanUp(false);

	LISTITEM * pItem = m_lstBegin;
	LISTITEM * next;

	// 現在抱えているリストアイテムの破棄
	while(pItem) {
		next = pItem->next;
		// dieUIが呼ばれるころにはすべての子タスクが削除済みなので、
		// kill()処理を行わずdelete する。
		delete_item(pItem, false);
		pItem = next;
	}

	// スクロールコントロールノードの破棄
	KLBDELETE(m_pCtrlNode);

	KLBDELETE(m_dragCallback);
	KLBDELETEA(m_dynamicCallback);

	KLBDELETEA(m_limitCallback);	// 2012.11.27  解放漏れがあったので修正
	KLBDELETEA(m_pGroupName);		// 2012.11.27  解放漏れがあったので修正

	if(m_clipHandle) {
		CKLBUISystem::unregisterClip(m_clipHandle);
	}
}


bool
CKLBUIList::load_itemform(CKLBUIList::LISTITEM * pItem, const char * json, u32 jsonLength, CKLBCompositeAsset * pOrgAsset, IDataSource * pSource)
{
	// 既に form がロードされている場合は何もしない
	if(pItem->form && pItem->handle) return true;

	u32 handle = 0;

	// グループ化情報を初期化
	pItem->ctrl.pGrpPrev    = NULL;
	pItem->ctrl.pGrpNext    = NULL;
	pItem->ctrl.pGroup      = NULL;

	pItem->ctrl.pBegin      = NULL;
	pItem->ctrl.next        = NULL;
	pItem->ctrl.bEnable     = m_bModalEnable && m_touchenable;
	pItem->ctrl.bExclusive  = true;
	pItem->ctrl.bWorking    = false;
	pItem->ctrl.pCallbackIF = m_dragCallback;
	pItem->ctrl.nativeCallback = (!m_dragCallback) ? (CKLBUIList::defaultScroll) : NULL;
	pItem->ctrl.pID         = this;

	// pNode と handle を作る
	CKLBCompositeAsset * pAsset = pOrgAsset;
	if(!pAsset) {
		CKLBAssetManager& pAssetManager = CKLBAssetManager::getInstance();
		pAsset = (CKLBCompositeAsset *)CKLBUtility::readAsset((u8 *)json, jsonLength, &handle, pAssetManager.getPlugin('P'));
	}
	if(!pAsset) {
		KLBDELETE(pItem);
		return false;
	}

	// アイテムによって生成されたコントロールノードの記録を取る。
	CKLBUISystem::setFormList(&pItem->ctrl);

	// compositeを生成する際、起動されたタスクの記録をとっておく。
	CKLBTaskMgr& mgr = CKLBTaskMgr::getInstance();
	mgr.setRegistedTaskList(&pItem->taskList);

	// DEBUG_PRINT(" LIST:ctrl: %p", &pItem->ctrl);

	if(pSource) pAsset->setRecord(pSource, pSource->getRecord());
	CKLBNode * pNode = pAsset->createSubTree(this,m_basePriority);
	pNode->setVisible(false);	// 生成直後は invisible にしておく

	// タスク記録終了
	mgr.setRegistedTaskList(NULL);

	// コントロールノード記録終了
	CKLBUISystem::setFormList(NULL);

	// グループ名が指定されていたら、自動的にグループに所属させる。
	if(m_pGroupName) {
		CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();
		fGrp.addForm(&(pItem->ctrl), m_pGroupName);
	}

	if(!pNode && !pOrgAsset) {
		CKLBDataHandler::releaseHandle(handle);
		return false;
	}
	m_pCtrlNode->addNode(pNode);

	// この段階で、composit の node tree と handle が出来上がっている

	// その node と handle を抱えたLISTITEMを作る
	pItem->form   = pNode;
	pItem->handle = handle;

	CKLBTouchEventUIMgr::getInstance().registForm(&pItem->ctrl);

	// アイテムの再生が終わったので、コールバックが指定されていたら呼び出す。
	
	CKLBScriptEnv::getInstance().call_eventUIListDynamic(m_dynamicCallback,this, pItem->index, pItem->id);

	return true;
}

bool
CKLBUIList::unload_itemform(CKLBUIList::LISTITEM * pItem, bool kill_child)
{
	// フォームコントロールリストをグループから削除する
	CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();
	fGrp.delForm(&(pItem->ctrl));

	// 既にフォームが破棄されている場合は何もしない
	if(!pItem->form && !pItem->handle) return true;

	pItem->form->setVisible(false);

	// ctrl を処理する
	CKLBTouchEventUIMgr& mgr = CKLBTouchEventUIMgr::getInstance();

	CKLBUISelectable * pCtrl = pItem->ctrl.pBegin;
	CKLBUISelectable * pNext;
	while(pCtrl) {
		pNext = pCtrl->getNextSelectable();
		// フォームのコントロールが操作中であれば、操作中ステータスをリセットする
		mgr.resetSelectable(pCtrl);
		pCtrl = pNext;
	}

	// このアイテム向けに差し替えられたassetがあれば破棄する
	m_formIF.removeAssetByHandle(pItem);

	// このアイテム用に起動されたタスクがあれば破棄する
	pItem->taskList.killTaskList(kill_child);

	// node と handle を処理する
	CKLBUtility::deleteNode(pItem->form, pItem->handle);

	// フォームのコントロールリストを破棄
	// AFTER pItem->form destruction.
	mgr.removeForm(&pItem->ctrl);

	pItem->form   = NULL;
	pItem->handle = 0;

	return true;
}

CKLBUIList::LISTITEM *
CKLBUIList::create_item(const char * json, u32 size, int id, CKLBCompositeAsset * pOrgAsset, IDataSource * pSource)
{
	//u32 handle = 0;

	// LISTITEMを作る
	LISTITEM * pItem = KLBNEW(LISTITEM);
    if(!pItem) { return NULL; }

	pItem->enable = true;
	pItem->id = id;

	switch(m_itemMode)
	{
	case LIST_ITEM_NORMAL:
	case LIST_ITEM_FLYWEIGHT:
		{
			pItem->jsonp    = NULL;
			pItem->jsonlen  = 0;
			pItem->handle   = 0;
			pItem->form     = NULL;
			load_itemform(pItem, json, size, pOrgAsset, pSource);
		}
		break;
	case LIST_ITEM_DYNAMIC:
		{
			pItem->jsonp    = CKLBUtility::copyMem(json, size);
			pItem->jsonlen  = size;
			pItem->handle   = 0;
			pItem->form     = NULL;
		}
		break;
	}

	pItem->prev = pItem->next = NULL;

	return pItem;
}

void
CKLBUIList::delete_item(LISTITEM * pItem, bool kill_child)
{
	// フォームがロードされていたら破棄する
	// if(pItem->form && pItem->handle) { <-- Test done in un_load
	unload_itemform(pItem, kill_child);

	// JSONがあれば破棄する
	KLBDELETEA(pItem->jsonp);

	KLBDELETE(pItem);	// インスタンス本体を破棄
}

int
CKLBUIList::get_item_index_by_id(int id)
{
	LISTITEM * pItem;
	int idx = 0;
	for(pItem = m_lstBegin; pItem; pItem = pItem->next) {
		if(pItem->id == id) return idx;
		idx++;
	}
	return -1;
}

CKLBUIList::LISTITEM *
CKLBUIList::getItemByID(int id)
{
	LISTITEM * pItem;
	for(pItem = m_lstBegin; pItem; pItem = pItem->next) {
		if(pItem->id == id) return pItem;
	}
	return NULL;
}

CKLBUIList::LISTITEM *
CKLBUIList::getItemByIndex(int index)
{
	LISTITEM * pItem;
	int idx = 0;
	for(pItem = m_lstBegin; pItem; pItem = pItem->next) {
		if(idx == index) return pItem;
		idx++;
	}
	return NULL;
}
bool
CKLBUIList::itemInsertUniversal(LISTITEM * posItem, int step, CLuaState& lua, int index, int id)
{
	u32 size;
	const char * json = toJSON(lua, index, size);	// 対応している型ならすべてJSON文字列になる。
	bool bResult = itemInsert(posItem, step, json, size, id);
	KLBDELETEA(json);

	return bResult;
}

//
// 現在Luaスタックの指定indexに積まれている値をJSON文字列化する。
// JSON-assetパス、JSON文字列、Luaテーブルに対応。
//
const char *
CKLBUIList::toJSON(CLuaState& lua, int index, u32& size)
{
	if(lua.isString(index)) {
		// 文字列である場合、先頭が "asset://" "file://" であれば asset file、それ以外なたJSON string
		// と判断して処理する。
		const char * param  = lua.getString(index);
		const char * string = NULL;
		if(!strncmp(param, "asset://", 8) || !strncmp(param, "file://", 7)) {
			IPlatformRequest& pltf = CPFInterface::getInstance().platform();
			IReadStream * pStream = pltf.openReadStream(param, pltf.useEncryption());
			if(!pStream || pStream->getStatus() != IReadStream::NORMAL) {
				delete pStream;
				return NULL;
			}
			int ssize = pStream->getSize();
			char * buf = KLBNEWA(char, ssize + 1);
			pStream->readBlock(buf, ssize);
			delete pStream;
			buf[ssize] = 0;
			string = (const char *)buf;
			size = ssize;
		} else {
			size = strlen(param);
			string = CKLBUtility::copyString(param);
		}
		return string;
	}
	// 文字列ではない場合、Luaテーブルとして処理する
	lua.retValue(index);
	const char * json = CKLBUtility::lua2BJson(lua, size);
	lua.pop(1);

	return json;
}

/*static*/
const char *
CKLBUIList::toJSON(const char* param, u32& size)
{
	// 文字列である場合、先頭が "asset://" "file://" であれば asset file、それ以外なたJSON string
	// と判断して処理する。
	const char * string = NULL;
	if(!strncmp(param, "asset://", 8) || !strncmp(param, "file://", 7)) {
		IPlatformRequest& pltf = CPFInterface::getInstance().platform();
		IReadStream * pStream = pltf.openReadStream(param, pltf.useEncryption());
		if(!pStream || pStream->getStatus() != IReadStream::NORMAL) {
			delete pStream;
			return NULL;
		}
		int ssize = pStream->getSize();
		char * buf = KLBNEWA(char, ssize + 1);
		pStream->readBlock(buf, ssize);
		delete pStream;
		buf[ssize] = 0;
		string = (const char *)buf;
		size = ssize;
	} else {
		size = strlen(param);
		string = CKLBUtility::copyString(param);
	}
	return string;
}

// JSONから生成したcompositをリストの項目として追加する
bool
CKLBUIList::itemInsert(LISTITEM * posItem, int step, const char * json, u32 size, int id, 
						CKLBCompositeAsset * pAsset, IDataSource * pSource)
{
	// ノードを作る

	LISTITEM * pItem = create_item(json, size, id, pAsset, pSource);
    if(!pItem) { return false; }

	m_force = true; // Will be added to the list.

	pItem->step = step;

	if(posItem) {
		pItem->prev = posItem->prev;
		posItem->prev = pItem;
	} else {
		pItem->prev = m_lstEnd;
		m_lstEnd = pItem;
	}
	if(pItem->prev) {
		pItem->prev->next = pItem;
	} else {
		m_lstBegin = pItem;
	}
	pItem->next = posItem;

	// アイテムが加わったので再配置
	m_itemUpdate = true;
	// itemRealloc();

	m_itemCnt++;

	return true;
}

void
CKLBUIList::itemDelete(LISTITEM * posItem)
{
	// アイテムをメインリストから取り外す
	if(posItem->prev) {
		posItem->prev->next = posItem->next;
	} else {
		m_lstBegin = posItem->next;
	}
	if(posItem->next) {
		posItem->next->prev = posItem->prev;
	} else {
		m_lstEnd = posItem->prev;
	}

	// 取り外したアイテムを killリストに付け替える
	posItem->prev = m_killEnd;
	posItem->next = NULL;
	if(posItem->prev) {
		posItem->prev->next = posItem;
	} else {
		m_killBegin = posItem;
	}
	m_killEnd = posItem;

	// この時点での物理的削除は行わない。
	// アイテムの持つボタン等からのLuaコールバック内で削除が指示されるケースもあるため、
	// コールバックから戻ってきた時点でinstanceが無くなっていることは避けねばならない。
	// メインリスト中からは消えているため、従来通り削除と同時にindexが振りなおされる仕様は保たれる。
	// 以下は旧コード。
	// // アイテムを削除する
	// delete_item(posItem);

	// アイテムが減ったので再配置
	m_itemUpdate = true;
	// itemRealloc();
	m_itemCnt--;
}

void
CKLBUIList::itemCleanUp(bool kill_child)
{
	LISTITEM * pItem = m_killBegin;
	while(pItem) {
		LISTITEM * pNext = pItem->next;
		delete_item(pItem, kill_child);
		pItem = pNext;
	}
	m_killBegin = m_killEnd = NULL;
}

void 
CKLBUIList::setSplineLayout(float* array_, u32 setupBitmask, u32 curveLengthPixel) 
{
	m_layoutTableXY			= array_; array_ += 4;
	m_layoutInterlaceSize	= 4;
	m_curveLength			= curveLengthPixel;

	if (setupBitmask & (1<<CKLBSplineNode::MODIFY_SCALE)) {
		m_layoutTableScale		= array_; array_ += 4;	// Scale X & Y
		m_layoutInterlaceSize	+= 4;
	} else {
		m_layoutTableScale		= NULL;
	}

	if (setupBitmask & ((1<<CKLBSplineNode::MODIFY_R) | (1<<CKLBSplineNode::MODIFY_G) | (1<<CKLBSplineNode::MODIFY_B))) {
		m_layoutTableRGB		= array_; array_ += 6;	// RGB
		m_layoutInterlaceSize  += 6;
	} else {
		m_layoutTableRGB		= NULL;
	}

	if (setupBitmask & (1<<CKLBSplineNode::MODIFY_A)) {
		m_layoutTableAlpha		= array_; array_ += 2;	// Alpha
		m_layoutInterlaceSize  += 2;
	} else {
		m_layoutTableAlpha	    = NULL;
	}

	if (setupBitmask & (1<<CKLBSplineNode::MODIFY_ROT)) {
		m_layoutTableRotation	= array_; array_ += 2;	// Rotation
		m_layoutInterlaceSize  +=2;
	} else {
		m_layoutTableRotation	= NULL;
	}

	if (setupBitmask & (1<<CKLBSplineNode::MODIFY_PRIORITY)) {
		m_layoutTablePriority	= array_; array_ += 2;
		m_layoutInterlaceSize  +=2;
	} else {
		m_layoutTablePriority	= NULL;
	}

	if (setupBitmask & (1<<CKLBSplineNode::MODIFY_LAYOUT)) {
		m_layoutTableLayout		= array_; array_ += 2;
		m_layoutInterlaceSize  +=2;
	} else {
		m_layoutTableLayout		= NULL;
	}

	m_layoutTable = array_;
}

s32 
CKLBUIList::fromScreenDistanceToSplineDistance(s32 posPixelSpace) 
{
	return (posPixelSpace << 12) / m_curveLength;
}

inline 
void 
CKLBUIList::interpolate1(float* array_, float sub, float& res) 
{
	res  = *array_ + (array_[1] * sub); // Export .4 fixed
}

inline 
void 
CKLBUIList::interpolate2(float* array_, float sub, float& resA, float& resB) 
{
	resA = array_[0] + (array_[1] * sub);
	resB = array_[2] + (array_[3] * sub);
}

inline 
void 
CKLBUIList::interpolate3(float* array_, float sub, float& resA, float& resB, float& resC) 
{
	resA = array_[0] + (array_[1] * sub);
	resB = array_[2] + (array_[3] * sub);
	resC = array_[4] + (array_[5] * sub);
}

// アイテムの表示位置関係を再設定する
void
CKLBUIList::itemRealloc()
{
	LISTITEM * pItem;
	bool posUpdate = m_posUpdate;
	bool itemUpdate = m_itemUpdate;
	m_posUpdate = m_itemUpdate = false;

	// それぞれのフォーム表示位置を再設定する
	if(itemUpdate || m_bLoop) {	// loop のときは必ず処理
		int pos = (m_bLoop) ? 0 : m_marginTop;
		m_itemCnt = 0;
		for(pItem = m_lstBegin; pItem; pItem = pItem->next) {
			pItem->pos = pos;
			pos += pItem->step;
			m_itemCnt++;
		}

		m_listLength = pos + ((m_bLoop) ? 0 : m_marginBottom);	// 終端値
	}

	// ループ可能な最小クリップサイズの計算。
	// m_listLength + index[0] の step サイズ以下の場合、
	// スクロールによって最初のアイテムがクリップ領域中の二か所以上に
	// 表示されなければならない状況が生じるため、
	// ループには少なくとも最初のアイテムが二重に必要とされないサイズが必須。

	int loopMinSize = m_listLength - ((m_lstBegin) ? m_lstBegin->step : 0);

	if(m_bLoop && (loopMinSize >= m_clipSize)) {
		m_scrBar.setOverScroll(m_bLoop || !m_chklimit);
		m_scrBar.setLoopArea(0, m_listLength);
	} else {
		m_scrBar.setOverScroll(!m_chklimit);
		m_scrBar.setLoopArea(0, 0);	// ループなし
	}

	if(posUpdate) {
		if(m_chklimit && !m_bLoop) {
			// クリッピング処理ありかつループなし
			if(m_scrollPos + m_listLength < m_clipSize) m_scrollPos = m_clipSize - m_listLength;
			if(m_scrollPos > 0) m_scrollPos = 0;
			bool call = false;
			if(m_scrollPos == 0) {
				call = true;
				if(!m_limitCalled) {
					CKLBScriptEnv::getInstance().call_eventUIList(m_limitCallback, 
						this, LIST_SCROVER_TOP, m_itemCnt, m_listLength, -m_scrollPos);
				}
			}
			if(m_scrollPos + m_listLength <= m_clipSize) {
				call = true;
				if(!m_limitCalled) {
					CKLBScriptEnv::getInstance().call_eventUIList(m_limitCallback,
						this, LIST_SCROVER_BOTTOM, m_itemCnt, m_listLength, -m_scrollPos);
				}
			}
			// 前回コール条件を満たしていたが、今回コール条件を満たしていない場合は、領域を離れた旨の呼び出しを行う。
			if(m_limitCalled && !call) {
				CKLBScriptEnv::getInstance().call_eventUIList(m_limitCallback,
					this, LIST_SCROVER_TAKEOFF, m_itemCnt, m_listLength, -m_scrollPos);
			}
			m_limitCalled = call;	// 次回にコール済みか否かの記録を残す。
		} else {
			//
			// クリッピング処理なしもしくはループあり
			//
			bool call = false;
			int pos = -m_scrollPos;	// 表示用の m_scrollPos は符号が反転しているため。
			int limitArea = (m_limitAreaSize > 0) ? m_limitAreaSize : m_clipSize;

			// スクロール結果、画面下端が最後の「ページ(= 画面と同サイズの領域)」にかかったら、
			// 下端オーバーコールバックを呼ぶ(設定されている場合)
			if(!m_bLoop && (pos >= m_listLength - (limitArea + m_clipSize)) ) {
				call = true;
				if(!m_limitCalled) {
					CKLBScriptEnv::getInstance().call_eventUIList(m_limitCallback, 
								this, LIST_SCROVER_BOTTOM, m_itemCnt, m_listLength, pos);
				}
			}
			// スクロール結果、画面上端が最初の「ページ(= 画面と同サイズの領域)」にかかったら、
			// 上端オーバーコールバックを呼ぶ(設定されている場合)
			if(!m_bLoop && (pos <= limitArea)) {
				call = true;
				if(!m_limitCalled) {
					CKLBScriptEnv::getInstance().call_eventUIList(m_limitCallback,
								this, LIST_SCROVER_TOP, m_itemCnt, m_listLength, pos);
				}
			}
			// 前回コール条件を満たしていたが、今回コール条件を満たしていない場合は、領域を離れた旨の呼び出しを行う。
			if(!m_bLoop && m_limitCalled && !call) {
				CKLBScriptEnv::getInstance().call_eventUIList(m_limitCallback,
					this, LIST_SCROVER_TAKEOFF, m_itemCnt, m_listLength, pos);
			}
			m_limitCalled = call;	// 次回にコール済みか否かの記録を残す。

			if(m_bLoop && (loopMinSize >= m_clipSize)) {
				// ループありのとき、スクロール位置が下端に近く、境界が表示域内に入るならば
				// 上端部の表示位置を下端から継続するように再配置する。
				// ただし、リスト全体の長さがクリップサイズ未満である場合はこの処理は行わない。
				if(m_scrollPos + m_listLength < m_clipSize) {
					pItem = m_lstBegin;
					if(pItem) {
						while(pItem->pos + m_scrollPos + m_listLength < m_clipSize) {
							pItem->pos += m_listLength;
							pItem = pItem->next;
						}
					}
				}
			}
		}
	}

	// 各アイテムの表示位置を反映させる
	if(posUpdate || itemUpdate) {
		if(m_layoutTable) {
			setSplinePosition();
		} else {
			setStraightPosition();
		}
		// 設定されたリストの最大長を利用して、スクロールバーの最大値を設定する。
		int maxPos = m_listLength - m_clipSize;
		if(maxPos < 0) {
			// リスト全体の長さがクリッピング領域に満たない場合
			maxPos = 0;
		}
		m_scrBar.setMaxPosition(maxPos);

		// スライダのサイズを変動させる
		if(maxPos > 0) {
			int slider_size = m_clipSize * m_clipSize / m_listLength;
			m_scrBar.setSliderSize(slider_size);
		} else {
			m_scrBar.setSliderSize(m_clipSize);
		}
	}
}

void
CKLBUIList::setStraightPosition()
{
	LISTITEM * pItem;

	// それぞれのフォーム表示位置を再設定する
	int x, y;
	x = y = 0;
	switch(m_itemMode)
	{
	case LIST_ITEM_NORMAL:
		{
			int item_index = 0;
			for(pItem = m_lstBegin; pItem; pItem = pItem->next) {
				// index を再設定する
				pItem->index = item_index;
				item_index++;

				x = (m_vertical)  ? 0 : (pItem->pos);
				y = (!m_vertical) ? 0 : (pItem->pos);
				pItem->form->setTranslate((float)x, (float)y);
				pItem->form->setVisible(true);
			}
		}
		break;
	case LIST_ITEM_DYNAMIC:
		{
			int item_index = 0;
			for(pItem = m_lstBegin; pItem; pItem = pItem->next) {
				// index を再設定する
				pItem->index = item_index;
				item_index++;

				// このアイテムが画面内に入っていれば、アイテムツリーを生成
				// 入っていなければアイテムツリーを破棄
				int pos = pItem->pos + m_scrollPos;
				if((pos + pItem->step) > 0 && pos < m_clipSize) {
					// アイテムがクリップ領域内にある
					load_itemform(pItem, pItem->jsonp, pItem->jsonlen);
					x = (m_vertical)  ? 0 : pItem->pos;
					y = (!m_vertical) ? 0 : pItem->pos;
					pItem->form->setTranslate((float)x, (float)y);
					pItem->form->setVisible(true);
				} else {
					// アイテムはクリップ領域外にある
					unload_itemform(pItem);
				}
			}
		}
		break;
	}

	// m_scrollPos はクリッピング済み
	if(m_vertical) {
		m_ctrlY = m_scrollPos;
	} else {
		m_ctrlX = m_scrollPos;
	}

	m_pCtrlNode->setTranslate(m_ctrlX, m_ctrlY);
}

void
CKLBUIList::setSplinePosition()
{
	LISTITEM * pItem;

	bool isDynamic = m_itemMode == LIST_ITEM_DYNAMIC;

	// scrollOffset Range = 0..((Item Count * (Item Size << 12)) / curveLengthPixel)
	// m_ctrlX or m_ctrlY based on bool vert.  <-- Scroll position.

	// それぞれのフォーム表示位置を再設定する
	int item_index = 0;
	int	offsetPos  = 0;

	for(pItem = m_lstBegin; pItem; pItem = pItem->next) {
			
		pItem->index = item_index;
		item_index++;

		if(m_layoutTableLayout) {
			int splinePos	= fromScreenDistanceToSplineDistance(pItem->pos + m_scrollPos);
			if((splinePos < 0) || (splinePos >= 4096)) {
				offsetPos = 0;
			} else {
				u32 idx			= (splinePos >> 4) * m_layoutInterlaceSize;
				float sub		= (splinePos & 0xF) * (1.0f/16.0f);
				float layoutStepF;
				interpolate1(&m_layoutTableLayout[idx], sub, layoutStepF);
				offsetPos = (s32)(layoutStepF * 4096);
			}
		}

		int splinePos	= fromScreenDistanceToSplineDistance(pItem->pos + offsetPos + m_scrollPos);

		if((splinePos < 0) || (splinePos >= 4096)) {
			if (!isDynamic) {
				pItem->form->setVisible(false);
			} else {
				// アイテムはクリップ領域外にある
				unload_itemform(pItem);
			}
		} else {
			CKLBNode* pNode = NULL;
			// アイテムがクリップ領域内にある
			if(isDynamic) {
				if(load_itemform(pItem, pItem->jsonp, pItem->jsonlen)) {
					pNode = pItem->form;
				}
			} else {
				pNode = pItem->form;
			}

			if(pNode) {
				pNode->setVisible(true);
				float x,y;
				u32 idx     = (splinePos >> 4) * m_layoutInterlaceSize;
				float sub   = (splinePos & 0xF) * (1.0f/16.0f);

				// X,Y
				interpolate2(&m_layoutTableXY[idx], sub, x, y);
				pNode->setTranslate(x,y);

				// Scale
				if(m_layoutTableScale || m_layoutTableRotation) {
					if(m_layoutTableScale && !m_layoutTableRotation) {
						interpolate2(&m_layoutTableScale[idx], sub, x, y);
						pNode->setScale(x,y);
					}
					else
					// Rotation
					if(m_layoutTableRotation && !m_layoutTableScale) {
						float rot;
						interpolate1(&m_layoutTableRotation[idx], sub, rot);
						pNode->setRotation(rot);
					}
					else
					// Rotation & Scale
					if(m_layoutTableRotation && m_layoutTableScale) {
						float rot;
						interpolate1(&m_layoutTableRotation[idx], sub, rot);
						interpolate2(&m_layoutTableScale[idx], sub, x, y);
						pNode->setScaleRotation(x,y,rot);
					}
				}


				// Alpha
				if(m_layoutTableAlpha) {
					SColorVector col;
					pNode->getColorMatrix(col);
					interpolate1(&m_layoutTableAlpha[idx], sub, col.m_vector[3]); // Can probably avoid interpolation here.
					pNode->setColorMatrix(col);
				}

				// R,G,B
				if(m_layoutTableRGB) {
					SColorVector col;
					pNode->getColorMatrix(col);
					interpolate3(&m_layoutTableRGB[idx], sub, col.m_vector[0], col.m_vector[1], col.m_vector[2]); // Can probably avoid interpolation here.
					pNode->setColorMatrix(col);
				}

				if(m_layoutTablePriority) {
					float priority;
					interpolate1(&m_layoutTablePriority[idx], sub, priority);
					pNode->setPriorityL(priority);
				}
			}
		}
	}

	// ### TODO CLIPPING ###
}


bool
CKLBUIList::setClip(u32 orderBegin, u32 orderEnd,
                    s16 clipX, s16 clipY, s16 clipWidth, s16 clipHeight)
{
	CKLBRenderingManager& pMgr = CKLBRenderingManager::getInstance();
	CKLBRenderState* pClipStart = pMgr.allocateCommandState();
	CKLBRenderState* pClipEnd   = pMgr.allocateCommandState();

	CKLBNode * pNode = getNode();
	if(pNode->setRenderSlotCount(2) && pClipStart && pClipEnd) {
		pNode->setRender(pClipStart,0);
		pNode->setRender(pClipEnd  ,1);

		pClipStart->setUse	(true,false,null);
		pClipEnd->setUse	(true,false,null);

		return resetClip(orderBegin, orderEnd, clipX, clipY, clipWidth, clipHeight, true);
	} else {
		if (pClipEnd)	{ pMgr.releaseCommand(pClipEnd);	}
		if (pClipStart) { pMgr.releaseCommand(pClipStart);	}
		return false;
	}
	//return true;
}

bool 
CKLBUIList::resetClip(u32 orderBegin, u32 orderEnd, s16 clipX, s16 clipY, s16 clipWidth, s16 clipHeight, bool forceClip) 
{
	CKLBRenderingManager& pMgr = CKLBRenderingManager::getInstance();
	CKLBNode*        pNode      = getNode();
	CKLBRenderState* pClipStart = (CKLBRenderState*)pNode->getRender(0);
	CKLBRenderState* pClipEnd	= (CKLBRenderState*)pNode->getRender(1);
	
	if(orderBegin != 0xFFFFFFFF) {
		pClipStart->changeOrder(pMgr, orderBegin);
	}

	if(orderBegin != 0xFFFFFFFF) {
		pClipEnd->changeOrder(pMgr, orderEnd);
	}

	bool enabled = true;
	if(forceClip || (clipWidth != 0) || (clipHeight != 0)) {
		pClipStart->setScissor(true, clipX, clipY, clipWidth, clipHeight);
	} else {
		enabled = false;
		pClipStart->setScissor(false, 0, 0, 0, 0);
	}
	pClipEnd->setScissor(false);

	if(enabled) {
		if(m_clipHandle == NULL) {
			m_clipHandle = CKLBUISystem::registerClip(pClipStart, pClipEnd);
			return m_clipHandle != NULL;
		}
	} else {
		if(m_clipHandle != NULL) {
			CKLBUISystem::unregisterClip(m_clipHandle);
			m_clipHandle = NULL;
		}
	}
	return true;
}

void
CKLBUIList::touchpadEvent()
{
	CKLBTouchPadQueue& tpq = CKLBTouchPadQueue::getInstance();
	float fx, fy;
	CKLBUtility::getNodePosition(getNode(), &fx, &fy);
	int x, y, rx, ry;
	x = (int)fx;
	y = (int)fy;
	
	float scaleX = getScaleX();
	float scaleY = getScaleY();

	int left   = (int)(m_leftDrag   * scaleX);
	int right  = (int)(m_rightDrag  * scaleX);
	int top    = (int)(m_topDrag    * scaleY);
	int bottom = (int)(m_bottomDrag * scaleY);

	const PAD_ITEM * item;
	tpq.startItem();
	while(NULL != (item = tpq.getItem())) {
		switch(item->type)
		{
		case PAD_ITEM::TAP:
			{
				// タップ位置がリストの範囲内に入っていれば自身に対する操作とみなす。
				rx = item->x - x;
				ry = item->y - y;
				if((rx < left) || (rx >= right) || ry < top || ry >= bottom) {
					// クリップ外なのであずかり知らぬイベント。
					break;
				}
				m_dragID = item->id;
				m_dragX = item->x;
				m_dragY = item->y;
				tpq.useItem(item, this);
				if(m_dragCallback) {
					m_dragCallback->callback(item->type, item->x, item->y, 0, 0);
				} else {
					defaultScroll(this, item->type, item->x, item->y, 0, 0);
				}
			}
			break;

		case PAD_ITEM::DRAG:
			{
				if(item->id != m_dragID) break;
				int mv_x = item->x - m_dragX;
				int mv_y = item->y - m_dragY;
				tpq.useItem(item, this);
				if(m_dragCallback) {
					// DEBUG_PRINT("  EVENT: %p (drag)", this);
					m_dragCallback->callback(item->type, m_dragX, m_dragY, mv_x, mv_y);
				} else {
					defaultScroll(this, item->type, m_dragX, m_dragY, mv_x, mv_y);
				}
			}
			break;

		case PAD_ITEM::RELEASE:
		case PAD_ITEM::CANCEL:
			{
				if(item->id != m_dragID) break;
				int mv_x = item->x - m_dragX;
				int mv_y = item->y - m_dragY;
				tpq.useItem(item, this);
				if(m_dragCallback) {
					m_dragCallback->callback(item->type, m_dragX, m_dragY, mv_x, mv_y);
					// DEBUG_PRINT("  EVENT: %p (release)", this);
				} else {
					defaultScroll(this, item->type, m_dragX, m_dragY, mv_x, mv_y);
				}
				m_dragID = -1;
			}
			break;
		}
	}
}

// デフォルトでドラッグ操作に追従させてスクロールさせる場合
void
CKLBUIList::defaultScroll(void * pData, PAD_ITEM::TYPE type, int dragX, int dragY, int mvX, int mvY)
{
	CKLBUIList * pList = (CKLBUIList *)pData;
	if(!pList->m_defScroll) return;	// デフォルトスクロールが禁止なら処理しない。
	switch(type)
	{
	case PAD_ITEM::TAP:
		{
			pList->m_defaultPrePos  = -pList->m_scrollPos;
			pList->m_defaultDragPos = -pList->m_scrollPos;
			pList->m_dragX          = dragX;
			pList->m_dragY          = dragY;
			pList->m_bTaped         = true;
			pList->m_scrBar.setCtrlStatus(true);
		}
		break;
	case PAD_ITEM::DRAG:
		{
			if ((abs(mvX) + abs(mvY)) >= pList->m_dragDistance) {
				if(!pList->m_bTaped) {
					pList->m_defaultPrePos  = -pList->m_scrollPos;
					pList->m_defaultDragPos = -pList->m_scrollPos;
					pList->m_bTaped = true;
					pList->m_scrBar.setCtrlStatus(true);
				}
				s32 pos = pList->m_defaultPrePos;
				if(pList->m_vertical) {
					pos -= mvY;
				} else {
					pos -= mvX;
				}
				int dir = (pos > pList->m_defaultDragPos) ? 1 : -1;
				pList->m_defaultDragPos = pos;	// 前回のpos指定からどちらにドラッグしたかで変わるため。
				pList->m_scrBar.setPosition(pos, dir);
				pos = pList->m_scrBar.getPosition();
				pList->setPosition(pos);
			}
		}
		break;
	case PAD_ITEM::RELEASE:
	case PAD_ITEM::CANCEL:
		{
			s32 pos = pList->m_defaultPrePos;
			if(pList->m_vertical) {
				pos -= mvY;
			} else {
				pos -= mvX;
			}
			int dir = (pos > pList->m_defaultDragPos) ? 1 : -1;
			pList->m_scrBar.setPosition(pos, dir);
			pos = pList->m_scrBar.getPosition();
			pList->setPosition(pos);
			pList->m_bTaped = false;
			pList->m_scrBar.setCtrlStatus(false);
		}
		break;
	}
}
