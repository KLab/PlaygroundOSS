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
#include <stdio.h>
#include <math.h>
#include "CKLBUIPieChart.h"
#include "CKLBLuaEnv.h"
#include "CKLBUtility.h"
;
enum {
	UI_PIE_SET_START,
	UI_PIE_SET_END,
	UI_PIE_SET_VALUE,
};

IFactory::DEFCMD cmd[] = {
	{ "UI_PIE_SET_START",	UI_PIE_SET_START	},
	{ "UI_PIE_SET_END",		UI_PIE_SET_END		},
	{ "UI_PIE_SET_VALUE",	UI_PIE_SET_VALUE	},

	{ 0, 0 }
};

static CKLBTaskFactory<CKLBUIPieChart> factory("UI_PieChart", CLS_KLBUIPIECHART, cmd);

const CKLBUIPieChart::VERTMAP CKLBUIPieChart::ms_vertMaster[] = {
	{  0.0f,  0.0f, 0.5f, 0.5f },	// 中心

	{  0.0f, -1.0f, 0.5f, 0.0f },	// 上辺中央
	{  1.0f, -1.0f, 1.0f, 0.0f },	// 上辺右 / 右辺上

	{  1.0f, -1.0f, 1.0f, 0.0f },	// 上辺右 / 右辺上
	{  1.0f,  0.0f, 1.0f, 0.5f },	// 右辺中央

	{  1.0f,  0.0f, 1.0f, 0.5f },	// 右辺中央
	{  1.0f,  1.0f, 1.0f, 1.0f },	// 右辺下 / 下辺右

	{  1.0f,  1.0f, 1.0f, 1.0f },	// 右辺下 / 下辺右
	{  0.0f,  1.0f, 0.5f, 1.0f },	// 下辺中央

	{  0.0f,  1.0f, 0.5f, 1.0f },	// 下辺中央
	{ -1.0f,  1.0f, 0.0f, 1.0f },	// 下辺左 / 左辺下

	{ -1.0f,  1.0f, 0.0f, 1.0f },	// 下辺左 / 左辺下
	{ -1.0f,  0.0f, 0.0f, 0.5f },	// 左辺中央

	{ -1.0f,  0.0f, 0.0f, 0.5f },	// 左辺中央
	{ -1.0f, -1.0f, 0.0f, 0.0f },	// 左辺上 / 上辺左

	{ -1.0f, -1.0f, 0.0f, 0.0f },	// 左辺上 / 上辺左
	{  0.0f, -1.0f, 0.5f, 0.0f },	// 上辺中央に戻ってくる
};

const int CKLBUIPieChart::ms_idxMaster[][3] = {
	{ 0, 1, 2 },
	{ 0, 3, 4 },
	{ 0, 5, 6 },
	{ 0, 7, 8 },

	{ 0, 9, 10 },
	{ 0, 11, 12 },
	{ 0, 13, 14 },
	{ 0, 15, 16 },
};

// property key list
CKLBLuaPropTask::PROP_V2 CKLBUIPieChart::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",	R_UINTEGER,	NULL,									(getBoolT)&CKLBUIPieChart::getOrder,	0	},
// Value never set in constructor
//	{	"asset",	R_STRING,	NULL,									(getBoolT)&CKLBUIPieChart::getAsset,	0	},
	{	"start",	NUMERIC,	(setBoolT)&CKLBUIPieChart::setStart,	(getBoolT)&CKLBUIPieChart::getStart,	0	},
	{	"end",		NUMERIC,	(setBoolT)&CKLBUIPieChart::setEnd,		(getBoolT)&CKLBUIPieChart::getEnd,		0	},
	{	"value",	NUMERIC,	(setBoolT)&CKLBUIPieChart::setValue,	(getBoolT)&CKLBUIPieChart::getValue,	0	},
	{	"anim",		R_INTEGER,	NULL,									(getBoolT)&CKLBUIPieChart::getAnim,		0	}
};

// argument indices
enum {
	ARG_PARENT	= 1,

	ARG_ORDER,		// プライオリティ
	ARG_X,			// 円グラフ中心の x座標
	ARG_Y,			// 円グラフ中心の y座標

	ARG_WIDTH,		// 円グラフ表示サイズ
	ARG_HEIGHT,		// 円グラフ表示サイズ

	ARG_ASSET,		// asset名

	ARG_START,		// グラフの開始点(degree)
	ARG_END,		// グラフの終了点(degree)

	ARG_ANIM,		// アニメーション時間

	ARG_INITIAL,	// 初期値

	ARG_REQUIRE = ARG_END,
	ARG_MAXNUM  = ARG_INITIAL
};

CKLBUIPieChart::CKLBUIPieChart() 
: CKLBUITask()
{
	setNotAlwaysActive();
	m_newScriptModel = true;
}

CKLBUIPieChart::~CKLBUIPieChart() 
{
}

u32
CKLBUIPieChart::getClassID()
{
	return CLS_KLBUIPIECHART;
}

CKLBUIPieChart *
CKLBUIPieChart::create(CKLBUITask * pParent, CKLBNode * pNode,
                       u32 order, float x, float y, float width, float height,
                       const char * asset, float start, float end, int anim, float initial)
{
	CKLBUIPieChart * pTask = KLBNEW(CKLBUIPieChart);
    if(!pTask) { return NULL; }
	if(!pTask->init(pParent, pNode,
					order, x, y, width, height,
					asset, start, end, anim, initial)) {
		KLBDELETE(pTask);
		return NULL;
	}

	return pTask;
}

bool
CKLBUIPieChart::init(CKLBUITask * pParent, CKLBNode * pNode,
                     u32 order, float x, float y, float width, float height,
                     const char * asset, float start, float end, int anim, float initial)
{
	if(!setupNode()) return false;

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(order, x, y, width, height, asset, start, end, anim, initial);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}

	return bResult;
}

bool
CKLBUIPieChart::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < ARG_REQUIRE || argc > ARG_MAXNUM) return false;

	u32   order     = lua.getInt(ARG_ORDER);
	float x         = lua.getFloat(ARG_X);
	float y         = lua.getFloat(ARG_Y);
	float width     = lua.getFloat(ARG_WIDTH);
	float height    = lua.getFloat(ARG_HEIGHT);
	const char * asset = lua.getString(ARG_ASSET);
	float start     = lua.getFloat(ARG_START);
	float end       = lua.getFloat(ARG_END);
	int   anim      = (argc >= ARG_ANIM)    ? lua.getInt(ARG_ANIM)      : 0;
	float initial   = (argc >= ARG_INITIAL) ? lua.getFloat(ARG_INITIAL) : 0.0f;

	return initCore(order, x, y, width, height, asset, start, end, anim, initial);
}

bool
CKLBUIPieChart::initCore(u32 order, float x, float y, float width, float height,
                         const char * asset, float start, float end, int anim, float initial)
{
	// 保持プロパティを定義
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}
	setInitPos(x, y);

	klb_assert((((s32)order) >= 0), "Order Problem");

	m_order = order;
	m_start = start;
	m_end   = end;
	m_anim  = anim;

	m_texWidth  = width;
	m_texHeight = height;

	// asset の取得
	m_pImgAsset = (CKLBImageAsset *)CKLBUtility::loadAssetScript(asset, &m_texHandle);
	if(!m_pImgAsset) {
		return false;
	}

	// 必要とされるオブジェクトを生成する
	CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();

	m_pDynSprite = pRdrMgr.allocateCommandDynSprite(8*3,8*3);	// 中央から8分割(45度ごと)

	m_pNode = KLBNEW(CKLBNode);
	if((!m_pDynSprite) || (!m_pNode)) {
		CKLBDataHandler::releaseHandle(m_texHandle);
		KLBDELETE(m_pNode);
		KLBDELETE(m_pDynSprite);
		return false;
	}

	klb_assert(m_pImgAsset->hasStandardAttribute(CKLBImageAsset::IS_STANDARD_RECT), "Must use a standard rectangular image in PieChart task.");
	m_pDynSprite->setTexture(m_pImgAsset);
	m_pNode->setRender(m_pDynSprite);
	m_pNode->setRenderOnDestroy(true);
	m_pNode->setPriority(order);

	// 自身の持つノードに追加
	getNode()->addNode(m_pNode);

	// 初期状態の頂点を設定する
	m_value     = initial;
	m_prevRate  = m_value;
	m_bAnim     = false;
	REFRESH_A;

	setVertices(initial);

	return true;
}

void
CKLBUIPieChart::dieUI()
{
	CKLBUtility::deleteNode(m_pNode, m_texHandle);
}

int
CKLBUIPieChart::commandUI(CLuaState& lua, int argc, int cmd)
{
	int ret = 0;
	switch(cmd)
	{
	default:
		{
			klb_assertAlways("unknown command: %d", cmd);
			lua.retBoolean(false);
			ret = 1;
		}
		break;
	case UI_PIE_SET_START:
		{
			bool result = false;
			if(argc == 3) {
				float start = lua.getFloat(3);
				setStart(start);
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_PIE_SET_END:
		{
			bool result = false;
			if(argc == 3) {
				float end = lua.getFloat(3);
				setEnd(end);
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_PIE_SET_VALUE:
		{
			bool result = false;
			if(argc == 3) {
				float value = lua.getFloat(3);
				setValue(value);
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	}

	return ret;
}

void
CKLBUIPieChart::execute(u32 deltaT)
{
	if(CHANGE_A) {
		if (!m_bAnim) {
			m_bAnim     = true;
			m_iTimeCnt  = 0;
			m_nowRate   = m_prevRate;
		}
	} else {
		m_prevRate = m_value;
	}

	if(m_bAnim) {
		int p_anim = m_anim;
		m_iTimeCnt += deltaT;

		float rate = (!p_anim) ? 1.0f : ((float)m_iTimeCnt/p_anim);
		if(rate > 1.0f) rate = 1.0f;

		float value = m_nowRate + (m_value - m_nowRate) * rate;

		// アニメーション中に書き換える
		setVertices(value);

		if(rate >= 1.0f) {
			m_bAnim     = false;
			m_prevRate  = m_value;
			RESET_A;
		}
	}
}

void
CKLBUIPieChart::setVertices(float value)
{
	// 描画開始角と終了角の値を整理する
	float start = m_start;
	float end 	= m_end;
	float theta = (end - start) * value + start;
	float min, max;
	if(start <= theta) {
		min = start;
		max = theta;
	} else {
		min = theta;
		max = start;
	}
	// 値が一周以上している場合は明らかに全部描画する
	if((max - min) >= 360.0f) {
		min = 0.0f;
		max = 360.0f;
	}

	// 値の差が一定以上であれば 0 とみなし、表示しない。
	bool visible = ((max - min) < 0.001f) ? false : true;
	m_pNode->setVisible(visible);

	// 表示しない場合
    if(!visible) { return; }

	float half_w, half_h, ub, vb, uw, vh;
	half_w = m_texWidth / 2.0f;
	half_h = m_texHeight / 2.0f;
	m_pImgAsset->getUV(0, &ub, &vb);
	m_pImgAsset->getUV(2, &uw, &vh);
	uw -= ub;
	vh -= vb;

	// とりあえず頂点データをフルで作る
	for(int i = 0; i < 17; i++) {
		m_vertices[i].x = half_w * ms_vertMaster[i].x;
		m_vertices[i].y = half_h * ms_vertMaster[i].y;
		m_vertices[i].u = ub + uw * ms_vertMaster[i].u;
		m_vertices[i].v = vb + vh * ms_vertMaster[i].v;
	}

	// min, max に合わせて必要な三角形の頂点をいじる
	int min_idx = (int)(min / 45.0f);
	int max_idx = (int)(max / 45.0f);
	float min45 = min - 45.0f * min_idx;
	float max45 = max - 45.0f * max_idx;
	if(max_idx > 0 && max45 < 0.0001f) {
		max45 = 45.0f;
		max_idx--;
	}

    if(min_idx & 1) { min45 = 45.0f - min45; }
	if(max_idx & 1) { max45 = 45.0f - max45; }

	float min_n = tan(min45 * M_PI / 180.0f);
	float max_n = tan(max45 * M_PI / 180.0f);

    if(min_idx & 1) { min_n = 1.0f - min_n; }
	if(max_idx & 1) { max_n = 1.0f - max_n; }

	float min_x, min_y, min_u, min_v;
	float max_x, max_y, max_u, max_v;
	getPoint(min_idx, min_n, min_x, min_y, min_u, min_v);
	getPoint(max_idx, max_n, max_x, max_y, max_u, max_v);

	int min_i = ms_idxMaster[min_idx & 7][1];
	int max_i = ms_idxMaster[max_idx & 7][2];
	m_vertices[min_i].x = min_x;
	m_vertices[min_i].y = min_y;
	m_vertices[min_i].u = min_u;
	m_vertices[min_i].v = min_v;

	m_vertices[max_i].x = max_x;
	m_vertices[max_i].y = max_y;
	m_vertices[max_i].u = max_u;
	m_vertices[max_i].v = max_v;

	for(int i = 0; i < 8; i++) {
		// 描画する条件
		if((i >= min_idx && i <= max_idx) || (max_idx >= 8 && (i <= (max_idx & 7)))) {
			for(int j = 0; j < 3; j++) {
				int idx = ms_idxMaster[i][j];
				m_pDynSprite->setVertexXY(i * 3 + j, m_vertices[idx].x, m_vertices[idx].y);
				m_pDynSprite->setVertexUV(i * 3 + j, m_vertices[idx].u, m_vertices[idx].v);
			}
		} else {
			// 頂点を中央に寄せて表示させない。
			for(int j = 0; j < 3; j++) {
				m_pDynSprite->setVertexXY(i * 3 + j, m_vertices[0].x, m_vertices[0].y);
				m_pDynSprite->setVertexUV(i * 3 + j, m_vertices[0].u, m_vertices[0].v);
			}
		}
	}
	m_pNode->markUpMatrix();
}

void
CKLBUIPieChart::getPoint(int idx, float n, float& x, float& y, float& u, float& v)
{
	float base_x, base_y, len_x, len_y;
	float base_u, base_v, len_u, len_v;
	int v1, v2;

	v1 = ms_idxMaster[idx & 7][1];
	v2 = ms_idxMaster[idx & 7][2];

	base_x = m_vertices[v1].x;
	base_y = m_vertices[v1].y;
	len_x  = m_vertices[v2].x - base_x;
	len_y  = m_vertices[v2].y - base_y;

	base_u = m_vertices[v1].u;
	base_v = m_vertices[v1].v;
	len_u  = m_vertices[v2].u - base_u;
	len_v  = m_vertices[v2].v - base_v;

	x = base_x + len_x * n;
	y = base_y + len_y * n;
	u = base_u + len_u * n;
	v = base_v + len_v * n;
}

bool 
CKLBUIPieChart::changeAsset(const char* asset)
{
	u32 newTextHandle;
	CKLBImageAsset* newImgAsset = (CKLBImageAsset *)CKLBUtility::loadAssetScript(asset, &newTextHandle);
	if(!newImgAsset) {
		return false;
	}

	CKLBUtility::deleteNode(m_pNode, m_texHandle);

	m_pImgAsset = newImgAsset;
	m_texHandle = newTextHandle;

	// 必要とされるオブジェクトを生成する
	CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();

	m_pDynSprite = pRdrMgr.allocateCommandDynSprite(8*3,8*3);	// 中央から8分割(45度ごと)

	m_pNode = KLBNEW(CKLBNode);
	if((!m_pDynSprite) || (!m_pNode)) {
		CKLBDataHandler::releaseHandle(m_texHandle);
		KLBDELETE(m_pNode);
		KLBDELETE(m_pDynSprite);
		return false;
	}

	klb_assert(m_pImgAsset->hasStandardAttribute(CKLBImageAsset::IS_STANDARD_RECT), "Must use a standard rectangular image in PieChart task.");
	m_pDynSprite->setTexture(m_pImgAsset);
	m_pNode->setRender(m_pDynSprite);
	m_pNode->setRenderOnDestroy(true);
	m_pNode->setPriority(m_order);

	// 自身の持つノードに追加
	getNode()->addNode(m_pNode);
	setVertices(m_value);

	return true;
}
