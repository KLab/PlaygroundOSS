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
#include "CKLBUIFreeVertItem.h"
#include "CKLBDataHandler.h"
#include "CKLBUtility.h"
#include "mem.h"

// Command Values
enum {
	UI_FREEVERT_SET_VERTICES = 0,	// 頂点位置を指定
	UI_FREEVERT_SET_COLORS,			// 頂点カラー一括指定
	UI_FREEVERT_SET_VERT_COL,		// 頂点カラー個別指定
	UI_FREEVERT_SET_UV,				// 頂点UV指定
};

static IFactory::DEFCMD cmd[] = {
	{ "UI_FREEVERT_SET_VERTICES",	UI_FREEVERT_SET_VERTICES },
	{ "UI_FREEVERT_SET_COLORS",		UI_FREEVERT_SET_COLORS },
	{ "UI_FREEVERT_SET_VERT_COL",	UI_FREEVERT_SET_VERT_COL },
	{ "UI_FREEVERT_SET_UV",			UI_FREEVERT_SET_UV },
	{ 0, 0}
};
static CKLBTaskFactory<CKLBUIFreeVertItem> factory("UI_FreeVertItem", CLS_KLBUIFREEVERTITEM, cmd);

CKLBUIFreeVertItem::CKLBUIFreeVertItem()
: CKLBUITask    ()
, m_handle      (0)
, m_asset       (NULL)
{	
	setNotAlwaysActive();
	m_newScriptModel = true;
}

CKLBUIFreeVertItem::~CKLBUIFreeVertItem() 
{
	KLBDELETEA(m_asset);
}

u32
CKLBUIFreeVertItem::getClassID()
{
	return CLS_KLBUIFREEVERTITEM;
}


// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUIFreeVertItem::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",			UINTEGER,	(setBoolT)&CKLBUIFreeVertItem::setOrder,		(getBoolT)&CKLBUIFreeVertItem::getOrder,	0	},
	{	"asset",			R_STRING,	NULL,											(getBoolT)&CKLBUIFreeVertItem::getAsset,	0	},
};

const u16 CKLBUIFreeVertItem::ms_indices[] = {
	0, 1, 3,
	1, 2, 3
};


// 引数のインデックス定義
enum {
	ARG_PARENT = 1,

	ARG_ORDER,
	ARG_X,
	ARG_Y,
	ARG_ASSET,
	ARG_VERTICES,

	ARG_REQUIRE = ARG_VERTICES,
};

CKLBUIFreeVertItem* 
CKLBUIFreeVertItem::create(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, const char* asset, float* vertices) 
{
	CKLBUIFreeVertItem* pTask = KLBNEW(CKLBUIFreeVertItem);
    if(!pTask) { return NULL; }
	if(!pTask->init(pParent, pNode, order, x, y, asset, vertices)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUIFreeVertItem::init(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, const char* asset, float* vertices) 
{
    if(!setupNode()) { return false; }
	bool bResult = initCore(order, x, y, asset, vertices);
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}
	return bResult;
}

bool
CKLBUIFreeVertItem::initCore(u32 order, float x, float y, const char* asset, float* vertices)
{
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	// 読み込んだ頂点データと、座標値、orderで表示物を用意する。
	CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();


	klb_assert((((s32)order) >= 0), "Order Problem");

	m_order = order;

	// 初期RGBA値を設定しておく
    for(int i = 0; i < 4; i++) { m_arrColor[i] = 0xffffffff; }

	m_pDynSprite = pRdrMgr.allocateCommandDynSprite(4, 2*3);
	if(asset) {
		setStrC(m_asset, asset);
	} else {
		setStrC(m_asset, "");
	}
	setInitPos(x, y);

	m_pTex = NULL;
    if(asset) { m_pTex = (CKLBImageAsset *)CKLBUtility::loadAssetScript(asset, &m_handle); }
	if(m_pTex) {
		setUV(m_pTex);	// UV値を取り込んでおく
		m_pDynSprite->setTexture(m_pTex);
	}

	getNode()->setRender(m_pDynSprite);
	getNode()->setRenderOnDestroy(true);
	getNode()->setPriority(m_order);

	if(vertices) {
		setVertXY(vertices);
	} else {
		float f = 0.0f;
		int   i = *((int*)&f);
		memset32(m_arrVert, i, 8 * sizeof(float));
		assignVertices();
	}

	u16* pBuff = m_pDynSprite->getSrcIndexBuffer();
	memcpy(pBuff, ms_indices, 6*sizeof(u16));

	assignVertColors();
	assignUV();

	return true;
}

bool
CKLBUIFreeVertItem::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
    if(argc < ARG_REQUIRE) { return false; }

	// 基本プロパティの取り込み
	float x = lua.getFloat(ARG_X);
	float y = lua.getFloat(ARG_Y);
	const char * asset = NULL;
	if(!lua.isNil(ARG_ASSET)) {
		asset = lua.getString(ARG_ASSET);
	}
	// 初期頂点データの読み込み
	lua.retValue(ARG_VERTICES);
	float tmpVert[8];
	bool bResult = setVertices(lua,tmpVert);
	lua.pop(1);

	// 頂点データが正しく読めていなければタスク起動失敗
	if(!bResult) { 
		return false; 
	} else { 
		return initCore(lua.getInt(ARG_ORDER),x,y,asset,tmpVert); 
	}
}

void
CKLBUIFreeVertItem::dieUI()
{
	CKLBDataHandler::releaseHandle(m_handle);
}

void
CKLBUIFreeVertItem::execute(u32 /* deltaT */)
{

}

int
CKLBUIFreeVertItem::commandUI(CLuaState& lua, int argc, int cmd)
{
	int ret = 1;

	switch(cmd)
	{
	case UI_FREEVERT_SET_VERTICES:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}

			lua.retValue(3);
			bool bResult = setVertices(lua);	// Lua配列から頂点情報を取得
			lua.pop(1);
			if(bResult)	assignVertices();	// 取り込んだ頂点座標をDynSpriteに設定

			lua.retBoolean(bResult);
			ret = 1;
		}
		break;
	case UI_FREEVERT_SET_COLORS:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			lua.retValue(3);
			bool bResult = setVertColors(lua);	// Lua配列から頂点カラーを取得
			lua.pop(1);
			if(bResult) assignVertColors();		// 取り込んだ頂点カラーをDynSpriteに設定
			lua.retBoolean(bResult);
			ret = 1;
		}
		break;
	case UI_FREEVERT_SET_VERT_COL:
		{
			if(argc != 5) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			int idx   = lua.getInt(3);
			u32 alpha = lua.getInt(4);
			u32 rgb   = lua.getInt(5);
			u32 argb = (rgb & 0xffffff)|((alpha & 0xff)<<24);
			setVertCol(idx,argb);
			lua.retBoolean(true);
			ret = 1;
		}
		break;
	case UI_FREEVERT_SET_UV:
		{
			bool result = false;
			if(argc == 3) { 
				lua.retValue(3);
				bool bResult = setArrUV(lua);	// Lua配列から頂点情報を取得
				lua.pop(1);
				if(bResult)	assignUV();			// 取り込んだ頂点座標をDynSpriteに設定
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	}
	return ret;
}

void 
CKLBUIFreeVertItem::setVertColors(u32* colors) 
{
	memcpy(m_arrColor, colors, 4 * sizeof(u32));
	assignVertColors();
}

void CKLBUIFreeVertItem::setVertUV(float* uv) 
{
	/* 取り込んだ値をテクスチャ内ローカルの値から、
		テクスチャアトラスレベルの値に変換する */
	float width  = m_arrOriginalUV[2] - m_arrOriginalUV[0];
	float height = m_arrOriginalUV[5] - m_arrOriginalUV[1];
	float baseX  = m_arrOriginalUV[0];
	float baseY  = m_arrOriginalUV[1];

	for(int i = 0; i < 4; i++) {
		float u = uv[i* 2];
		float v = uv[i * 2 + 1];

		// 負の値が指定された場合に、隣のテクスチャに割り込まないようにする処理。
		// 指定された画像より左側にuvが動くとGLのテクスチャアトラス上で問題が生じることがある。

        if(u < 0.0f) { u = 1.0f - u; }
		if(v < 0.0f) { v = 1.0f - v; }

		m_arrUV[i * 2]      = u * width + baseX;
		m_arrUV[i * 2 + 1]  = v * height + baseY;
	}
	assignUV();
}

void 
CKLBUIFreeVertItem::setVertXY(float* coord) 
{
	memcpy(m_arrVert, coord, 8 * sizeof(float));
	assignVertices();
}

bool
CKLBUIFreeVertItem::setVertColors(CLuaState& lua)
{
	int i;
	bool bResult = true;
	u32 alpha, rgb;

	for(i = 0; i < 4; i++) {
		lua.retInt(i * 2 + 1);
		lua.tableGet();
		if(lua.isNil(-1)) {
			bResult = false;
			lua.pop(1);
			break;
		}
		alpha = lua.getInt(-1);
		lua.pop(1);
		lua.retInt(i * 2 + 2);
		lua.tableGet();
		if(lua.isNil(-1)) {
			bResult = false;
			lua.pop(1);
			break;
		}
		rgb = lua.getInt(-1);
		lua.pop(1);

		// alpha と rgb 値を組み合わせてRGBA値を作る
		m_arrColor[i] = (rgb & 0xffffff) | ((alpha & 0xff) << 24);
	}
	return bResult;
}

bool
CKLBUIFreeVertItem::setVertices(CLuaState& lua, float* tmpDst)
{
	int i;
	bool bResult = true;

	// 頂点情報配列には、x,y,x,y,... のような形式で
	// 頂点が格納されているので、それを読み取り内部の配列に格納する。
	for(i = 0; i < 8; i++) {
		lua.retInt(i + 1);
		lua.tableGet();
		if(lua.isNil(-1)) {
			bResult = false;
			lua.pop(1);
			break;
		}
		float f = lua.getFloat(-1);
		if(tmpDst) {
			tmpDst[i] = f;
		} else {
			m_arrVert[i] = f;
		}
		lua.pop(1);
	}
	return bResult;
}

void
CKLBUIFreeVertItem::setUV(CKLBImageAsset * pTex)
{
	klb_assert(pTex->hasStandardAttribute(CKLBImageAsset::IS_STANDARD_RECT), "Must use a standard rectangular image in FreeVertItem task.");

	for(int i = 0; i < 4; i++) {
		pTex->getUV(i, &m_arrUV[i * 2], &m_arrUV[i * 2 + 1]);
		m_arrOriginalUV[i * 2]      = m_arrUV[i * 2];
		m_arrOriginalUV[i * 2 + 1]  = m_arrUV[i * 2 + 1];
	}
}

void
CKLBUIFreeVertItem::setVertColors()
{
	for(int i = 0; i < 6; i++) {
		int idx = ms_indices[i];
		u32 col;
		u32 color = m_arrColor[idx];
		u8* pCol = (u8*)&col;
		// Memory order cast to 'col'
		pCol[0] = color >> 16;	// R
		pCol[1] = color >> 8;	// G
		pCol[2] = color;		// B
		pCol[3] = color >> 24;  // A
		m_pDynSprite->setVertexColor(getNode(),i, col);
	}
}

void
CKLBUIFreeVertItem::setVertices()
{
	// 4頂点分の座標値が頂点配列に格納されているので、
	// それをDynSpriteに設定する。

	// DynSpriteは三角形二つ分なので、合計6頂点。
	for(int i = 0; i < 6; i++) {
		int idx = ms_indices[i];
		m_pDynSprite->setVertexXY(i, m_arrVert[idx * 2], m_arrVert[idx * 2 + 1]);
	}
}

void
CKLBUIFreeVertItem::setUV()
{
	// 4頂点分の座標値が頂点配列に格納されているので、
	// それをDynSpriteに設定する。

	// DynSpriteは三角形二つ分なので、合計6頂点。
	for(int i = 0; i < 6; i++) {
		int idx = ms_indices[i];
		m_pDynSprite->setVertexUV(i, m_arrUV[idx * 2], m_arrUV[idx * 2 + 1]);
	}
	getNode()->markUpMatrix();
}

bool
CKLBUIFreeVertItem::setArrUV(CLuaState& lua)
{
	int i;
	bool bResult = true;

	// 頂点情報配列には、x,y,x,y,... のような形式で
	// 頂点が格納されているので、それを読み取り内部の配列に格納する。
	for(i = 0; i < 8; i++) {
		lua.retInt(i + 1);
		lua.tableGet();
		if(lua.isNil(-1)) {
			bResult = false;
			lua.pop(1);
			break;
		}
		m_arrUV[i] = lua.getFloat(-1);
		lua.pop(1);
	}
	/* 取り込んだ値をテクスチャ内ローカルの値から、
		テクスチャアトラスレベルの値に変換する */
	float width  = m_arrOriginalUV[2] - m_arrOriginalUV[0];
	float height = m_arrOriginalUV[5] - m_arrOriginalUV[1];
	float baseX  = m_arrOriginalUV[0];
	float baseY  = m_arrOriginalUV[1];

	for(int i = 0; i < 4; i++) {
		float u = m_arrUV[i* 2];
		float v = m_arrUV[i * 2 + 1];

		// 負の値が指定された場合に、隣のテクスチャに割り込まないようにする処理。
		// 指定された画像より左側にuvが動くとGLのテクスチャアトラス上で問題が生じることがある。

		if(u < 0.0f) u = 1.0f - u;
		if(v < 0.0f) v = 1.0f - v;

		m_arrUV[i * 2] = u * width + baseX;
		m_arrUV[i * 2 + 1] = v * height + baseY;
	}
	return bResult;
}
