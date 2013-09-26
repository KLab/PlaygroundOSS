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
#include "CKLBUICanvas.h"
#include "CKLBUtility.h"
#include "CKLBLuaEnv.h"
#include "CKLBScriptEnv.h"
;
// Command Values
enum {
	UI_CANVAS_ADDRESOURCE       = 0,
	UI_CANVAS_DRAWIMAGE         = 1,
	UI_CANVAS_DRAWIMAGESCALE    = 2,
	UI_CANVAS_FILLRECT          = 3,
	UI_CANVAS_FREEZE            = 4,
	UI_CANVAS_STARTSECTION      = 5,
	UI_CANVAS_ENDSECTION        = 6,
	UI_CANVAS_SECTIONTRANSLATE  = 7,
	UI_CANVAS_SECTIONCOLOR      = 8
};

static IFactory::DEFCMD cmd[] = {
	{"UI_CANVAS_ADDRESOURCE",		UI_CANVAS_ADDRESOURCE		},
	{"UI_CANVAS_DRAWIMAGE",			UI_CANVAS_DRAWIMAGE			},
	{"UI_CANVAS_DRAWIMAGESCALE",	UI_CANVAS_DRAWIMAGESCALE	},
	{"UI_CANVAS_FILLRECT",			UI_CANVAS_FILLRECT			},
	{"UI_CANVAS_FREEZE",			UI_CANVAS_FREEZE			},
	{"UI_CANVAS_STARTSECTION",		UI_CANVAS_STARTSECTION		},
	{"UI_CANVAS_ENDSECTION",		UI_CANVAS_ENDSECTION		},
	{"UI_CANVAS_SECTIONTRANSLATE",	UI_CANVAS_SECTIONTRANSLATE	},
	{"UI_CANVAS_SECTIONCOLOR",		UI_CANVAS_SECTIONCOLOR		},
	{0, 0}
};

static CKLBTaskFactory<CKLBUICanvas> factory("UI_Canvas", CLS_KLBUICANVAS, cmd);

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUICanvas::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",	UINTEGER,	(setBoolT)&CKLBUICanvas::setOrder,		(getBoolT)&CKLBUICanvas::getOrder,		0	},
	{	"idxmax",	R_UINTEGER,	NULL,									(getBoolT)&CKLBUICanvas::getIdxMax,		0	},
	{	"callback",	STRING,		(setBoolT)&CKLBUICanvas::setCallBack,	(getBoolT)&CKLBUICanvas::getCallBack,	0	}
};

enum {
	ARG_PARENT = 1,

	ARG_ORDER,
	ARG_X,
	ARG_Y,
	ARG_VERTEX_MAX,
	ARG_INDEX_MAX,
	ARG_CALLBACK,

	ARG_REQUIRE = ARG_CALLBACK,
	ARG_NUMS = ARG_CALLBACK
};

CKLBUICanvas::CKLBUICanvas() : CKLBUITask()
, m_handle          (0)
, m_assetCount      (0)
, m_maxAssetCount   (0)
, m_texture         (NULL)
, m_assets          (NULL)
, m_pCanvas         (NULL)
, m_callback        (NULL)
{
	setNotAlwaysActive();
	m_newScriptModel = true;
}

CKLBUICanvas::~CKLBUICanvas() 
{
	KLBDELETEA(m_callback);
}

u32
CKLBUICanvas::getClassID()
{
	return CLS_KLBUICANVAS;
}

bool
CKLBUICanvas::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
    if(argc < ARG_REQUIRE || argc > ARG_NUMS) { return false; }

	u32 order = lua.getInt(ARG_ORDER);

	const char* cb  = lua.getString(ARG_CALLBACK);
	float x         = lua.getFloat(ARG_X);
	float y         = lua.getFloat(ARG_Y);

	return initCore(order, x,y, 
		lua.getInt(ARG_VERTEX_MAX),
		lua.getInt(ARG_INDEX_MAX),
		cb);
}

CKLBUICanvas *
CKLBUICanvas::create(CKLBUITask * pParent, CKLBNode * pNode,
                     u32 order, float x, float y, u32 vertexMax, u32 indexMax,
                     const char * callback)
{
	CKLBUICanvas * pTask = KLBNEW(CKLBUICanvas);
    if(!pTask) { return NULL; }

	if(!pTask->init(pParent, pNode, order, x, y, vertexMax, indexMax, callback)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUICanvas::init(CKLBUITask * pParent, CKLBNode * pNode,
                   u32 order, float x, float y, u32 vertexMax, u32 indexMax,
                   const char * callback)
{
    if(!setupNode()) { return false; }

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(order, x, y, vertexMax, indexMax, callback);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}

	return bResult;
}

bool
CKLBUICanvas::initCore(u32 order, float x, float y, u32 vertexMax, u32 indexMax, const char * callback)
{
	// 対応するプロパティリストを規定する。
	if (!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	m_pCanvas = CKLBRenderingManager::getInstance().allocateCommandCanvasSprite(vertexMax, indexMax, order);

	if (!m_pCanvas) {
		return false;
	}

	klb_assert((((s32)order) >= 0), "Order Problem");

	m_order = order;
	if(callback) {
		setStrC(m_callback, callback);
	} else {
		m_callback = NULL;
	}

	getNode()->setRender(m_pCanvas);
	setInitPos(x, y);
	return true;
}

bool 
CKLBUICanvas::addAsset(const char* asset) 
{
	u32 handle;
	CKLBAsset* pAsset = CKLBUtility::loadAssetScript(asset,&handle);
	if(pAsset && (pAsset->getAssetType() == ASSET_IMAGE)) {
		CKLBImageAsset* pImgAsset   = (CKLBImageAsset*)pAsset;
		CKLBTextureAsset* pTex      = (CKLBTextureAsset*)pImgAsset->getTexture();

		// We store only ONE handle at a time as we force the texture to be the same anyway.
		if(m_handle) { CKLBDataHandler::releaseHandle(m_handle); }
		m_handle = handle;

		if(m_assetCount == 0) {
			m_texture	= pTex;
			m_pCanvas->setupTexture(pTex);
			//
			// Patch Texture
			//
			u32 colArray[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
			pTex->m_pTexture->updateTexture(pTex->m_width - 2, pTex->m_height - 2,2,2,colArray, pTex->m_bytePerPix * 4);

			m_pCanvas->setFillUV(1.0f - (1.0f / (pTex->m_width)) , 1.0f - (1.0f / (pTex->m_height)));
		} else {
			if(pTex != m_texture) {
				klb_assertAlways("UI Canvas must have all images in same texture !");
				return false;
			}
		}

		if(m_assetCount >= m_maxAssetCount) {
			CKLBImageAsset** pArray = KLBNEWA(CKLBImageAsset*, m_maxAssetCount + 16);
			if(pArray) {
				memcpy(pArray, m_assets, sizeof(CKLBImageAsset*) * m_assetCount);
				KLBDELETEA(m_assets);
				m_assets = pArray;
				m_maxAssetCount += 16;
			} else {
				klb_assertAlways("Allocation failure");
				return false;
			}
		}
		m_assets[m_assetCount++] = pImgAsset;
		return true;
	}
	return false;
}

void 
CKLBUICanvas::setTiledRect(u32 width, u32 height, const char* asset, u32 alpha) 
{
	if(addAsset(asset)) {
		u32 idx = m_assetCount - 1; // Loaded Asset
		setTiledRect(width,height,idx,alpha);
	}
}

void 
CKLBUICanvas::freeze(bool freeze) 
{
	m_pCanvas->freeze(freeze);
}

void 
CKLBUICanvas::setTiledRect(u32 width, u32 height, u32 idx, u32 alpha) 
{
	m_pCanvas->clear();
	
	if((width == 0) || (height == 0)) {
		return;
	}

	SKLBRect* pSize = m_assets[0]->getSize();

	// Image Size
	float imgW = pSize->getWidth();
	float imgH = pSize->getHeight();

	// Number of tile in the rectangle (non integer !)
	float tilew = ((float)width  / imgW);
	float tileh = ((float)height / imgH);
	float modW  = tilew - floor(tilew);
	float modH  = tileh - floor(tileh);

	// Number of tile to be drawn.
	int tilewI  = (int)(floor(tilew));
	int tilehI  = (int)(floor(tileh));

	s32 cx;
	s32 cy;
	m_assets[idx]->getCenter(cx,cy);
	CKLBImageAsset* pTLAsset = m_assets[idx]->getAsTopLeftImage(cx,cy);

	for(int y = 0; y < tilehI; y++) {
		for (int x=0; x < tilewI; x++) {
			m_pCanvas->drawImage(
				x * imgW,
				y * imgH,
				pTLAsset,
				0xFFFFFF | (alpha<<24));				
		}
	}

	// int tileIntegerW = width  / pSize->getWidth();
	if(modW > 0.0000001f) {	// epsilon
		float lx = tilewI * imgW;
		// Get remaining part.
		for(int y=0; y < tilehI; y++) {
			m_pCanvas->drawImageClip(
				lx,
				y * imgH,
				pTLAsset,
				modW,
				1.0f,
				0xFFFFFF | (alpha<<24));				
		}
	}

	// int tileIntegerH = height / pSize->getHeight();
	if(modH > 0.0000001f) {	// epsilon
		float ly = tilehI * imgH;
		// Get remaining part.
		for(int x=0; x < tilewI; x++) {
			m_pCanvas->drawImageClip(
				x * imgW,
				ly,
				pTLAsset,
				1.0f,
				modH,
				0xFFFFFF | (alpha<<24));				
		}
	}

	if((modW > 0.0000001f)
	&& (modH > 0.0000001f)) {
		m_pCanvas->drawImageClip(
			tilewI * imgW,
			tilehI * imgH,
			pTLAsset,
			modW,
			modH,
			0xFFFFFF | (alpha<<24));				
	}

	getNode()->markUpMatrixAndColor();
}

int
CKLBUICanvas::commandUI(CLuaState& lua, int argc, int cmd)
{
	bool result = false;
	int ret = 0;
	switch(cmd)
	{
	case UI_CANVAS_ADDRESOURCE:
		if (argc == 3 && addAsset(lua.getString(3))) {
			ret		= 1;
			result	= true;
		}
		break;
	case UI_CANVAS_DRAWIMAGE:
		if(argc == 7) {
			ret		= 1;
			result	= true;

			drawImage(
				lua.getFloat(3),	// X 
				lua.getFloat(4),	// Y
				lua.getInt(5),		// Asset Index
				lua.getInt(6) |		// Color + Alpha
				(lua.getInt(7) << 24)
			);
		}
		break;
	case UI_CANVAS_DRAWIMAGESCALE:
		if(argc == 8) {
			ret		= 1;
			result	= true;

			drawImageScale(
				lua.getFloat(3),	// X 
				lua.getFloat(4),	// Y
				lua.getFloat(5),	// Scale 
				lua.getInt(6),		// Asset Index
				lua.getInt(7) |		// Color + Alpha
				(lua.getInt(8) << 24)
			);
		}
		break;
	case UI_CANVAS_FILLRECT:
		if(argc == 8) {
			ret		= 1;
			result	= true;

			fillRect(
				lua.getFloat(3),	// X 
				lua.getFloat(4),	// Y
				lua.getFloat(5),	// W
				lua.getFloat(6),	// H
				lua.getInt(7) |		// Color + Alpha
				(lua.getInt(8) << 24)
			);
		}
		break;
	case UI_CANVAS_FREEZE:
		if(argc == 3) {
			ret		= 1;
			result	= true;

			setFreeze(lua.getBool(3));
		}
		break;
	case UI_CANVAS_STARTSECTION:
		if(argc == 3) {
			ret		= 1;
			result	= true;
			startDynamicSection(lua.getInt(3));
		}
		break;
	case UI_CANVAS_ENDSECTION:
		if(argc == 3) {
			ret		= 1;
			result	= true;
			endDynamicSection(lua.getInt(3));
		}
		break;
	case UI_CANVAS_SECTIONTRANSLATE:
		if(argc == 5) {
			ret		= 1;
			result	= true;
			dynamicSectionTranslate(lua.getInt(3),lua.getFloat(4),lua.getFloat(5));
		}
		break;
	case UI_CANVAS_SECTIONCOLOR:
		if(argc == 5) {
			ret		= 1;
			result	= true;
			dynamicSectionColor(lua.getInt(3), 
				lua.getInt(4) |		// Color + Alpha
				(lua.getInt(5) << 24)
			);
		}
		break;
	default:
		{
			result = false;
		}
		break;
	}

	lua.retBoolean(result);
	return ret;
}

void
CKLBUICanvas::execute(u32 /* deltaT */)
{
	if(!m_pCanvas->isFreeze()) {
		m_pCanvas->clear();
		CKLBScriptEnv::getInstance().call_canvasOnDraw(m_callback, this);
	}
}

void
CKLBUICanvas::dieUI()
{
	CKLBUtility::deleteNode(NULL, m_handle);
}
