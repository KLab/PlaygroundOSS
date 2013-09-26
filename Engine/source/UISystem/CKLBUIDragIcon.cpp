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
#include "CKLBUIDragIcon.h"
#include "CKLBDataHandler.h"
#include "CKLBAsset.h"
#include "CKLBTouchPad.h"
#include "CKLBDrawTask.h"
#include "CKLBLuaEnv.h"
#include "CKLBScriptEnv.h"
#include "CKLBUtility.h"
;

// Command Values
enum {
	UI_DRAGICON_ENABLE = 0,
	UI_DRAGICON_DRAGAREA,
};
// 状態値
enum {
	DRAGICON_DRAG,
	DRAGICON_RELEASE,
};
// 動作モード設定フラグ群
enum {
	F_DICON_BASEINVISIBLE = 0x00000001,
};
static IFactory::DEFCMD cmd[] = {
	{"UI_DRAGICON_ENABLE",		UI_DRAGICON_ENABLE},
	{"UI_DRAGICON_DRAGAREA",	UI_DRAGICON_DRAGAREA},

	{"DRAGICON_DRAG",			DRAGICON_DRAG},
	{"DRAGICON_RELEASE",		DRAGICON_RELEASE},

	{"F_DICON_BASEINVISIBLE",	F_DICON_BASEINVISIBLE },

	{0, 0}
};

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUIDragIcon::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",			R_UINTEGER,	NULL,										(getBoolT)&CKLBUIDragIcon::getOrder,		0		},
	{	"asset",			R_STRING,	NULL,										(getBoolT)&CKLBUIDragIcon::getAsset,		0		},
	{	"drag",				R_STRING,	NULL,										(getBoolT)&CKLBUIDragIcon::getDrag,			0		},
	{	"flags",			UINTEGER,	(setBoolT)&CKLBUIDragIcon::setFlags,		(getBoolT)&CKLBUIDragIcon::getFlags,		0		},
	{	"callback",			STRING,		(setBoolT)&CKLBUIDragIcon::setCallBack,		(getBoolT)&CKLBUIDragIcon::getCallBack,		0		},
	{	"drag_scaleX",		NUMERIC,	(setBoolT)&CKLBUIDragIcon::setDragScaleX,	(getBoolT)&CKLBUIDragIcon::getDragScaleX,	0		},
	{	"drag_scaleY",		NUMERIC,	(setBoolT)&CKLBUIDragIcon::setDragScaleY,	(getBoolT)&CKLBUIDragIcon::getDragScaleY,	0		}
	// TODO : setEnable / getEnable exist but no property for LUA
};

enum {
	ARG_PARENT = 1,

	ARG_ORDER,
	ARG_X,
	ARG_Y,

	ARG_AREA,

	ARG_ASSET,
	ARG_DRAG,

	ARG_ORDER_STEP,
	ARG_ALPHA,

	ARG_CENTER_X,
	ARG_CENTER_Y,

	ARG_CALLBACK,

	ARG_FLAGS,

	ARG_REQUIRE = ARG_DRAG,
	ARG_NUMS = ARG_FLAGS
};

static CKLBTaskFactory<CKLBUIDragIcon> factory("UI_DragIcon", CLS_KLBUIDRAGICON, cmd);


CKLBUIDragIcon::CKLBUIDragIcon()
: CKLBUITask	()
, m_modalStack	(false)
, m_asset		(NULL)
, m_dragAsset	(NULL)
, m_callBack	(NULL)
{
	setNotAlwaysActive();
	m_newScriptModel = true;
}

CKLBUIDragIcon::~CKLBUIDragIcon() 
{
	KLBDELETEA(m_asset);
	KLBDELETEA(m_dragAsset);
	KLBDELETEA(m_callBack);	
}

u32
CKLBUIDragIcon::getClassID()
{
	return CLS_KLBUIDRAGICON;
}

CKLBUIDragIcon *
CKLBUIDragIcon::create(CKLBUITask * pParent, CKLBNode * pNode,
                       u32 order, float x, float y, AREA * tap_area,
                       const char * asset, const char * drag_asset,
                       s32 drag_order_offset, float drag_alpha, 
                       float center_x, float center_y, 
                       const char * callback, u32 flags)
{
	CKLBUIDragIcon * pTask = KLBNEW(CKLBUIDragIcon);
    if(!pTask) { return NULL; }
	if(!pTask->init(pParent, pNode, order, x, y,
					tap_area, asset, drag_asset, drag_order_offset,
					drag_alpha, center_x, center_y, callback, flags)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUIDragIcon::init(CKLBUITask * pParent, CKLBNode * pNode,
                     u32 order, float x, float y, AREA * tap_area,
                     const char * asset, const char * drag_asset,
                     s32 drag_order_offset, float drag_alpha, 
                     float center_x, float center_y, 
                     const char * callback, u32 flags)
{
    if(!setupNode()) { return false; }

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(order, x, y, tap_area,
							asset, drag_asset, drag_order_offset,
							drag_alpha, center_x, center_y, callback, flags);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}

	return bResult;
}

bool
CKLBUIDragIcon::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();

	// 引数の数が合わない
	if(argc < ARG_REQUIRE || argc > ARG_NUMS) return false;

	// 引数をプロパティ初期値として登録
	float x         = lua.getFloat(ARG_X);
	float y         = lua.getFloat(ARG_Y);
	u32 order       = lua.getInt(ARG_ORDER);
	const char * asset      = lua.getString(ARG_ASSET);
	const char * drag_asset = lua.getString(ARG_DRAG);
	int drag_order_offset   = lua.getInt(ARG_ORDER_STEP);
	float alpha     = lua.getFloat(ARG_ALPHA);
	float center_x  = lua.getFloat(ARG_CENTER_X);
	float center_y  = lua.getFloat(ARG_CENTER_Y);

	const char * callback = (argc >= ARG_CALLBACK) ? lua.getString(ARG_CALLBACK) : NULL;
	int flags = (argc >= ARG_FLAGS) ? lua.getInt(ARG_FLAGS) : 0;

	AREA tap_area;
    if(!get_area(lua, ARG_AREA, tap_area)) { return false; }

	return initCore(order, x, y, &tap_area,
					asset, drag_asset, drag_order_offset,
					alpha, center_x, center_y, callback, flags);
}

bool
CKLBUIDragIcon::initCore(u32 order, float x, float y, AREA * tap_area,
                         const char * asset, const char * drag_asset,
                         s32 drag_order_offset, float drag_alpha, 
                         float center_x, float center_y, 
                         const char * callback, u32 flags)
{
	// プロパティの種類を定義
	if (!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	// 引数をプロパティ初期値として登録
	setInitPos(x, y);
	m_order = order;
	setStrC(m_asset, asset);

	// ドラッグアイコン関係
	setStrC(m_dragAsset, drag_asset);
	int order_step  = drag_order_offset;
	float alpha     = drag_alpha;
	m_center_x  = center_x;
	m_center_y  = center_y;

	if(callback) { setStrC(m_callBack, callback); }

	m_flags         = flags;
	m_dragScaleX    = 1.0f;
	m_dragScaleY    = 1.0f;

	// 操作対象エリアを取得
	memcpy(&m_area, tap_area, sizeof(AREA));

	// モーダルスタック情報を初期化
	// UI_DragIcon 自体は決してモーダルにはならない。
	// ただし、モーダルスタックの影響をうける。
	m_modalStack.setModal(false);
	m_modalStack.push();

	// assetをロードして、アイコン用、ドラッグ用のNodeを作る
	m_pIconNode = CKLBUtility::createNodeScript(asset, order, &m_iconHandle);
	m_pDragNode = CKLBUtility::createNodeScript(drag_asset, order_step + order, &m_dragHandle);

	// この段階でUIノードが出来上がっているので、位置とプライオリティを設定
	// m_pIconNode->setTranslate(getNum(PR_X), getNum(PR_Y));
	m_pIconNode->setPriority(order);

	// 親nodeにつなぐ
	getNode()->addNode(m_pIconNode);

	// ドラッグアイコンは絶対位置で使用されなければならないため、
	// root ノードに接続して、必要になるまで invisible にしておく
	CKLBDrawResource& res = CKLBDrawResource::getInstance();
	res.getRoot()->addNode(m_pDragNode);
	SColorVector color;
	color.m_vector[3] = alpha;
	m_pDragNode->setColorMatrix(color);
	m_pDragNode->setVisible(false);

	// ドラッグ領域制限は初期状態で画面全域
	m_clip.x        = 0;
	m_clip.y        = 0;
	m_clip.width    = res.width();
	m_clip.height   = res.height();

	// 待機中
	m_state = S_WAIT;

	// 操作の許可
	m_enable=false; setEnable(true);	// Force flag change.

	//m_bModalEnable = true;
	m_ofs_x = 0;
	m_ofs_y = 0;
	return true;
}

void
CKLBUIDragIcon::execute(u32 /*deltaT*/)
{
	// 操作が許可されていない場合、TouchPadを確認しない
	//if(!m_enable) return; // useless thanks to A Flag. (Guillaume).

	// モーダルスタックによって操作が禁止されている場合
    if(!m_modalStack.isEnable()) { return; }

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
					float fx, fy;
					CKLBNode * pNode = getNode();
					CKLBUtility::getNodePosition(pNode, &fx, &fy);
					m_ofs_x = fx;
					m_ofs_y = fy;
				}

				// 自身のアイコンに対する操作ならば、状態をドラッグ中に切り替える。
				if(is_tap(item->x, item->y)) {
					m_state = S_DRAG;	// 状態をドラッグ中のstateに変更
					m_tid = item->id;	// 操作に使われたポイントIDを記録する
					m_pDragNode->setVisible(true);

					// scale が指定された場合、親アイコンは基礎Nodeに繋がっているためscaleが有効になるが、
					// ドラッグ中のアイコンは独立Nodeであるためscaleが有効にならない。
					float scaleX = m_dragScaleX;
					float scaleY = m_dragScaleY;
					m_pDragNode->setScale(scaleX, scaleY);

					int flags = m_flags;
					if(flags & F_DICON_BASEINVISIBLE) {
						m_pIconNode->setVisible(false);
					}

					m_pDragNode->setTranslate(item->x - m_center_x, item->y - m_center_y);
					tpq.useItem(item, this);
				}
			}
			break;
		case PAD_ITEM::DRAG:
			{
				// このタスクのステートがドラッグ中でない限り、
				// そのドラッグは他の用途のためのドラッグ操作。
				// また、タップ時に確定した操作ポイントIDが異なる場合も異なる操作。
				if(m_state != S_DRAG || m_tid != item->id) break;

				s32 x, y;
				drag_clip(item->x, item->y, &x, &y);

				m_pDragNode->setTranslate(x - m_center_x, y - m_center_y);

				// ドラッグ座標をコールバックに通知する。
				tpq.useItem(item, this);
				CKLBScriptEnv::getInstance().call_eventDragIcon(m_callBack, this, DRAGICON_DRAG, x, y);
			}
			break;
		case PAD_ITEM::RELEASE:
		case PAD_ITEM::CANCEL:
			{
				// このタスクのステートがドラッグ中でない限り
				// そのドラッグは他の用途のためのドラッグ操作。
				// また、タップ時に確定した操作ポイントIDが異なる場合も異なる操作。
				if(m_state != S_DRAG || m_tid != item->id) break;

				s32 x, y;
				drag_clip(item->x, item->y, &x, &y);

				m_pDragNode->setVisible(false);
				int flags = m_flags;
				if (flags & F_DICON_BASEINVISIBLE) {
					m_pIconNode->setVisible(true);
				}

				// リリースされた座標をコールバックに通知する。
				tpq.useItem(item, this);
				m_state = S_WAIT;
				CKLBScriptEnv::getInstance().call_eventDragIcon(m_callBack, this, DRAGICON_RELEASE, x, y);
			}
			break;
		}
	}
}

void
CKLBUIDragIcon::dieUI()
{
	CKLBUtility::deleteNode(m_pIconNode, m_iconHandle);
	CKLBUtility::deleteNode(m_pDragNode, m_dragHandle);
}

int
CKLBUIDragIcon::commandUI(CLuaState& lua, int argc, int cmd)
{
	int ret = 0;

	switch(cmd)
	{
	case UI_DRAGICON_ENABLE:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			bool enable = lua.getBool(3);
			setEnable(enable);
			lua.retBoolean(true);
			ret = 1;
		}
		break;
	case UI_DRAGICON_DRAGAREA:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			AREA clip;
			if(!get_area(lua, 3, clip)) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			m_clip = clip;
			lua.retBoolean(true);
			ret = 1;
		}
		break;
	default:
		lua.retBoolean(false);
		ret = 1;
		break;
	}

	return ret;
}

// Luaの配列で渡された操作エリア情報を取得する
bool
CKLBUIDragIcon::get_area(CLuaState& lua, int argp, AREA& area)
{
	bool bResult = true;

	lua.retValue(argp);
	lua.retNil();

	while(lua.tableNext()) {
		lua.retValue(-2);	// index

		const char * index = lua.getString(-1);
		int          value = lua.getInt(-2);

		if(!strcmp(index, "x")) {
			area.x = value;
		} else if(!strcmp(index, "y")) {
			area.y = value;
		} else if(!strcmp(index, "width")) {
			area.width = value;
		} else if(!strcmp(index, "height")) {
			area.height = value;
		} else {
			// 未知のメンバが存在する
			klb_assertAlways("unknown member in area structure: [%s]", index);
			bResult = false;
		}
		lua.pop(2);
	}
	lua.pop(1);
	return bResult;
}

bool
CKLBUIDragIcon::is_tap(int x, int y)
{
	int sx = m_area.x + m_ofs_x;
	int sy = m_area.y + m_ofs_y;
	if(x < sx || y < sy) return false;
	x -= sx;
	y -= sy;
	if(x >= m_area.width || y >= m_area.height) return false;
	return true;
}


bool
CKLBUIDragIcon::drag_clip(s32 drx, s32 dry, s32 * x, s32 * y)
{
	// 座標が指定範囲内であればそのまま返す。
	if(drx >= m_clip.x  && dry >= m_clip.y &&
		(drx - m_clip.x) < m_clip.width && (dry - m_clip.y) < m_clip.height) {
			*x = drx;
			*y = dry;
			return true;
	}

	if(drx < m_clip.x) { drx = m_clip.x; }
	if(dry < m_clip.y) { dry = m_clip.y; }
	if(drx >= m_clip.x + m_clip.width ) { drx = m_clip.x + m_clip.width  - 1; }
	if(dry >= m_clip.y + m_clip.height) { dry = m_clip.y + m_clip.height - 1; }

	*x = drx;
	*y = dry;
	return false;

	// 指定座標が範囲制限の外側にある場合、
	// - 反応エリアの左上から (m_center_x, m_center_y) の位置にある座標と、
	// - 現在の指定座標を結んだ線分が
	// - 指定範囲矩形の辺と交差する点
	// を、クリップ後の座標とする。

	// 基点座標:
	/* Direction calculation of the intersection between clipping border and line from center to drag coordinate
	   Releaved to be unstable
	// 傾きを求めるためのx,y各軸の差分
	float bx = m_area.x + m_ofs_x + m_center_x;
	float by = m_area.y + m_ofs_y + m_center_y;
	float fx = (float)drx;
	float fy = (float)dry;
	float dx = (float)(drx - bx);
	float dy = (float)(dry - by);
	float b = fy - (fx * dy / dx);	// y = ax + b の b

	// 上下の辺との交点を求める。
	float ly = (float)(m_clip.y + ((dy > 0) ? m_clip.height - 1 : 0));
	float lx = dx * (ly - b) / dy;
	if(lx >= (float)m_clip.x && lx < (float)(m_clip.x + m_clip.width)) {
		// クリップ幅以内に収まっていれば、上限辺上の点をクリップ後の座標として返す。
		*x = (s32)lx;
		*y = (s32)ly;
		return false;
	}


	// 交点が左右の枠外であれば、左右の辺との交点を求める。
	lx = (float)(m_clip.x + ((dx > 0) ? m_clip.width - 1 : 0));
	ly = b + lx * dy / dx;
	*x = (s32)lx;
	*y = (s32)ly;

	return false;
	*/

	/*	Variation using subdivision -> got same bug as the upper routine
		
	float sx = m_area.x + m_ofs_x + m_center_x;
	float sy = m_area.y + m_ofs_y + m_center_y;

	float dx = drx;
	float dy = dry;
	float prec = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

	float mx = sx;
	float my = sy;

	while (prec > 0.25f) {
		float deltaX = dx - sx;
		float deltaY = dy - sy;
		mx = sx + (deltaX * 0.5f);
		my = sy + (deltaY * 0.5f);

		if (mx >= m_clip.x  && mx >= m_clip.y &&
			(mx - m_clip.x) < m_clip.width && (my - m_clip.y) < m_clip.height) {
			sx = mx;
			sy = my;
		} else {
			dx = mx;
			dy = my;
		}
		prec *= 0.5f;
	}

	*x = mx;
	*y = my;

	return false;
	*/
}
