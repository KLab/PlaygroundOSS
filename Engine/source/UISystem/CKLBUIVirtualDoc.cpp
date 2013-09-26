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
#include "CKLBUIVirtualDoc.h"
#include "CKLBTouchPad.h"
#include "CKLBScriptEnv.h"
#include "CKLBLuaEnv.h"
#include "CKLBLanguageDatabase.h"
;
// Command Values
enum {
	UI_VDOC_CLEAR = 0x01,
	UI_VDOC_FONT,
	UI_VDOC_VIEWPOS,
	UI_VDOC_DRAW,

	UI_VDOC_ALIGN,

	VD_DRAW_LINE = 0x10,
	VD_DRAW_TEXT,
	VD_FILL_RECT,
	VD_DRAW_IMAG,

	VD_ALIGN_LEFT = 0,
	VD_ALIGN_CENTER,
	VD_ALIGN_RIGHT,
};

static IFactory::DEFCMD cmd[] = {
	{ "UI_VDOC_CLEAR",		UI_VDOC_CLEAR   },
	{ "UI_VDOC_FONT",		UI_VDOC_FONT    },
	{ "UI_VDOC_DRAW",		UI_VDOC_DRAW    },
	{ "UI_VDOC_VIEWPOS",	UI_VDOC_VIEWPOS },
	{ "UI_VDOC_ALIGN",		UI_VDOC_ALIGN   },

	{ "VD_DRAW_LINE",		VD_DRAW_LINE    },
	{ "VD_DRAW_TEXT",		VD_DRAW_TEXT    },
	{ "VD_FILL_RECT",		VD_FILL_RECT    },
	{ "VD_DRAW_IMAG",		VD_DRAW_IMAG    },

	{ "VD_ALIGN_LEFT",		VD_ALIGN_LEFT   },
	{ "VD_ALIGN_CENTER",	VD_ALIGN_CENTER },
	{ "VD_ALIGN_RIGHT",		VD_ALIGN_RIGHT  },

	{ 0, 0}
};

static CKLBTaskFactory<CKLBUIVirtualDoc> factory("UI_VirtualDoc", CLS_KLBUIVIRTUALDOC, cmd);

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUIVirtualDoc::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",		UINTEGER,	(setBoolT)&CKLBUIVirtualDoc::setOrder,		(getBoolT)&CKLBUIVirtualDoc::getOrder,		0	},	// int:		表示プライオリティ
	{	"cmdmax",		UINTEGER,	(setBoolT)&CKLBUIVirtualDoc::setCommandMax,	(getBoolT)&CKLBUIVirtualDoc::getCommandMax,	0	},	// int:		描画コマンド数上限
	{	"vertical",		BOOLEANT,	(setBoolT)&CKLBUIVirtualDoc::setVertical,	(getBoolT)&CKLBUIVirtualDoc::getVertical,	0	},	// bool:	縦書きフラグ

	{	"doc_width",	UINTEGER,	(setBoolT)&CKLBUIVirtualDoc::setDocWidth,	(getBoolT)&CKLBUIVirtualDoc::getDocWidth,	0	},	// float:	ドキュメントのサイズ
	{	"doc_height",	UINTEGER,	(setBoolT)&CKLBUIVirtualDoc::setDocHeight,	(getBoolT)&CKLBUIVirtualDoc::getDocHeight,	0	},	// float:	ドキュメントのサイズ

	{	"view_width",	UINTEGER,	(setBoolT)&CKLBUIVirtualDoc::setViewWidth,	(getBoolT)&CKLBUIVirtualDoc::getViewWidth,	0	},	// float:	ViewPort のサイズ
	{	"view_height",	UINTEGER,	(setBoolT)&CKLBUIVirtualDoc::setViewHeight,	(getBoolT)&CKLBUIVirtualDoc::getViewHeight,	0	},	// float:	ViewPort のサイズ

	{	"callback",		STRING,		(setBoolT)&CKLBUIVirtualDoc::setCallBack,	(getBoolT)&CKLBUIVirtualDoc::getCallBack,	0	}	// string:	ポインティングデバイス操作時のコールバック
};

enum {
	ARG_PARENT = 1,

	ARG_ORDER,
	ARG_X,
	ARG_Y,

	ARG_DOC_WIDTH,
	ARG_DOC_HEIGHT,

	ARG_VIEW_WIDTH,
	ARG_VIEW_HEIGHT,

	ARG_CMDMAX,
	ARG_VERTICAL,

	ARG_CALLBACK,

	ARG_REQUIRE = ARG_VERTICAL,
	ARG_MAXNUM = ARG_CALLBACK
};

CKLBUIVirtualDoc::CKLBUIVirtualDoc()
: CKLBUITask    ()
, m_imgBegin    (NULL)
, m_imgEnd      (NULL)
, m_align       (VD_ALIGN_LEFT)
, m_callBack    (NULL)
, m_viewPosX    (0)
, m_viewPosY    (0)
, m_forceRefreshMode    (true)
, m_counter     (0)
{
	m_format = TexturePacker::getCurrentModeTexture();
	setNotAlwaysActive();
	m_newScriptModel = true;
}

CKLBUIVirtualDoc::~CKLBUIVirtualDoc() 
{
	KLBDELETEA(m_callBack);
}

u32
CKLBUIVirtualDoc::getClassID()
{
	return CLS_KLBUIVIRTUALDOC;
}

CKLBUIVirtualDoc *
CKLBUIVirtualDoc::create(CKLBUITask * pParent, CKLBNode * pNode,
                         u32 order, float x, float y,
                         u32 doc_width, u32 doc_height, 
                         u32 view_width, u32 view_height,
                         u32 max_command_nums, bool vertical, const char * callback)
{
	CKLBUIVirtualDoc * pTask = KLBNEW(CKLBUIVirtualDoc);
    if(!pTask) { return NULL; }
	if(!pTask->init(pParent, pNode,
					order, x, y,
					doc_width, doc_height,
					view_width, view_height,
					max_command_nums, vertical, callback)) {
		KLBDELETE(pTask);
		return NULL;
	}

	return pTask;
}

bool
CKLBUIVirtualDoc::init(CKLBUITask * pParent, CKLBNode * pNode,
                       u32 order, float x, float y,
                       u32 doc_width, u32 doc_height, 
                       u32 view_width, u32 view_height,
                       u32 max_command_nums, bool vertical, const char * callback)
{
    if(!setupNode()) { return false; }

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(order, x, y,
							doc_width, doc_height,
							view_width, view_height,
							max_command_nums, vertical, callback);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}

	return bResult;
}

bool
CKLBUIVirtualDoc::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < ARG_REQUIRE || argc > ARG_MAXNUM) return false;

	float x             = lua.getFloat(ARG_X);
	float y             = lua.getFloat(ARG_Y);
	u32   order         = lua.getInt(ARG_ORDER);
	float doc_width     = lua.getFloat(ARG_DOC_WIDTH);
	float doc_height    = lua.getFloat(ARG_DOC_HEIGHT);
	float view_width    = lua.getFloat(ARG_VIEW_WIDTH);
	float view_height   = lua.getFloat(ARG_VIEW_HEIGHT);
	u32   max_command_nums = lua.getInt(ARG_CMDMAX);
	bool  vertical       = lua.getBool(ARG_VERTICAL);
	const char * callback = (argc >= ARG_CALLBACK) ? lua.getString(ARG_CALLBACK) : NULL;

	return initCore(order, x, y,
                    doc_width, doc_height,
                    view_width, view_height,
                    max_command_nums, vertical, callback);
}

bool
CKLBUIVirtualDoc::initCore(u32 order, float x, float y,
                           u32 doc_width, u32 doc_height, 
                           u32 view_width, u32 view_height,
                           u32 max_command_nums, bool vertical, const char * callback)
{
	// 保持プロパティを定義
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}
	setInitPos(x, y);

	klb_assert((((s32)order) >= 0), "Order Problem");

	m_order = order;

	REFRESH_A;
	REFRESH_B;
	REFRESH_C;
	REFRESH_D;
	REFRESH_E;

	m_width         = doc_width;
	m_height        = doc_height;
	m_viewWidth     = view_width;
	m_viewHeight    = view_height;
	m_align_width   = m_viewWidth;
	m_commandMax    = max_command_nums;
	m_vertical	    = vertical;
	m_callBack      = NULL;
    if(callback) { setStrC(m_callBack, callback); }

	m_pDocNode = KLBNEW(CKLBNodeVirtualDocument);
    if(!m_pDocNode) { return false; }
	getNode()->addNode(m_pDocNode);

	/*
	bool bResult = setupView();
    if(!bResult) {
        KLBDELETE(m_pDocNode);
        return false;
    }*/
	m_pDocNode->markUpMatrix();

	m_dragID = -1;
	m_modalStack.setModal(false);
	m_modalStack.push();

	execute(0);

	return true;
}

void
CKLBUIVirtualDoc::checkDocumentSize() 
{
	if (CHANGE_A) {
		m_pDocNode->createDocument(m_commandMax,m_format);
		RESET_A;
	}
}

void
CKLBUIVirtualDoc::execute(u32 deltaT)
{
	bool change = false;
	deltaT = deltaT; // avoid warning.

	if(CHANGE_A) {
		change = true;
	}
	checkDocumentSize();

	if(CHANGE_B) {
		m_pDocNode->setDocumentSize(m_width, m_height, m_vertical);	// virtual size, vertical
		change = true;
		RESET_B;
		forceRefresh();
	}

	if(CHANGE_C) {
		m_pDocNode->setViewPortSize(m_viewWidth, m_viewHeight,
									0.0f, 0.0f,
									m_order, true);			// physical size
		m_pDocNode->setViewPortPos(m_viewPosX,m_viewPosY);
		change = true;
		RESET_C;
		forceRefresh();
	}

	if(CHANGE_D) {
		change = true;
		RESET_D;
	}

	if(m_forceRefreshMode) {
		REFRESH_E;
		if(change) {
			m_counter = 1;
		}

		if(m_counter) {
			forceRefresh();
		}

		if(m_counter > 0) {
			m_counter--;
		}
	}

	bool bModalEnable = m_modalStack.isEnable();

	// ポインティング操作のコールバックが指定されていなければ何もしない。
	if(m_callBack) {
		if(bModalEnable) {
			touchPadEvent();
		}
	} else {
		if(m_counter == 0) {
			RESET_E;
		}
	}
}

void 
CKLBUIVirtualDoc::forceRefresh() 
{
	m_pDocNode->forceRefresh();
}

void
CKLBUIVirtualDoc::dieUI()
{
	KLBDELETE(m_pDocNode);
	destroyImages();
}

int
CKLBUIVirtualDoc::commandUI(CLuaState& lua, int argc, int cmd)
{
	int ret = 0;
	switch(cmd)
	{
	default:
		klb_assertAlways("[UI_VirtualDoc] unknown command 0x%04x.\n", cmd);

	case UI_VDOC_CLEAR:
		{
			if(argc != 4) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}

			u32 alpha   = lua.getInt(3);
			u32 col     = lua.getInt(4);
			clear(col|(alpha << 24));
			forceRefresh();
			CHANGE_D;
		}
		break;

	case UI_VDOC_FONT:
		{
			if(argc != 5) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			int idx = lua.getInt(3);
			const char * name = lua.getString(4);
			int font_size = lua.getInt(5);
			setFont(idx,name,font_size);
			forceRefresh();
			CHANGE_D;
		}
		break;
	case UI_VDOC_VIEWPOS:
		{
			if(argc != 4) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			int x = lua.getInt(3);
			int y = lua.getInt(4);
			setViewPortPos(x, y);
			forceRefresh();
			CHANGE_D;
		}
		break;
	case UI_VDOC_ALIGN:
		{
			bool bResult = false;
			if(argc >= 3 && argc <= 4) {
				u8 align = lua.getInt(3);
				int align_width = (argc >= 4) ? lua.getInt(4) : m_viewWidth;
				setAlign(align, align_width);
				forceRefresh();
				CHANGE_D;
				bResult = true;
			}
			break;
		}
		break;
	case UI_VDOC_DRAW:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}

			checkDocumentSize();
			m_pDocNode->emptyDocument();
			m_pDocNode->setDocumentSize(m_width, m_height,m_vertical);
			m_pDocNode->lockDocument();
			klb_assert(lua.isTable(3), "[UI_VirtualDoc::UI_VDOC_DRAW] BAD command table format.");
			lua.retValue(3);
			lua.retNil();
			while(lua.tableNext()) {
				lua.retValue(-2);	// index

				klb_assert(lua.isTable(-2), "[UI_VirtualDoc::UI_VDOC_DRAW] BAD command table format.");

				lua.retValue(-2);	// array
				lua.retNil();

				lua.tableNext();	// 最初の値(描画コマンド)
				int dcmd = lua.getInt(-1);
				lua.pop(1);
				switch(dcmd)
				{
				default:	// 不明な描画コマンド値
					klb_assertAlways("[UI_VirtualDoc] unknown draw command 0x%04x.\n", cmd);
					break;
				case VD_DRAW_LINE:
					{
						int x0, y0, x1, y1;
						u32 col, alpha;
						lua.tableNext(); x0		= lua.getInt(-1); lua.pop(1);
						lua.tableNext(); y0		= lua.getInt(-1); lua.pop(1);
						lua.tableNext(); x1		= lua.getInt(-1); lua.pop(1);
						lua.tableNext(); y1		= lua.getInt(-1); lua.pop(1);
						lua.tableNext(); alpha  = lua.getInt(-1); lua.pop(1);
						lua.tableNext(); col	= lua.getInt(-1); lua.pop(1);
						drawLine(x0, y0, x1, y1, col|(alpha << 24));
					}
					break;
				case VD_DRAW_TEXT:
					{
						int x0, y0, fontidx;
						u32 col, alpha;
						char const * str;
						lua.tableNext(); x0      = lua.getInt(-1); lua.pop(1);
						lua.tableNext(); y0      = lua.getInt(-1); lua.pop(1);
						lua.tableNext(); str     = (char *)lua.getString(-1); lua.pop(1);
						lua.tableNext(); alpha   = lua.getInt(-1); lua.pop(1);
						lua.tableNext(); col     = lua.getInt(-1); lua.pop(1);
						lua.tableNext(); fontidx = lua.getInt(-1); lua.pop(1);
						str = CKLBLanguageDatabase::getInstance().getString(str);

						drawText(x0, y0, str, col|(alpha << 24), fontidx);
					}
					break;
				case VD_FILL_RECT:
					{
						int x0, y0, width, height;
						u32 col, alpha;
						bool fill;
						lua.tableNext(); x0      = lua.getInt(-1); lua.pop(1);
						lua.tableNext(); y0      = lua.getInt(-1); lua.pop(1);
						lua.tableNext(); width   = lua.getInt(-1); lua.pop(1);
						lua.tableNext(); height  = lua.getInt(-1); lua.pop(1);
						lua.tableNext(); alpha   = lua.getInt(-1); lua.pop(1);
						lua.tableNext(); col     = lua.getInt(-1); lua.pop(1);
						lua.tableNext(); fill    = lua.getBool(-1); lua.pop(1);
						fillRect(x0, y0, width, height, col|(alpha << 24), fill);
					}
					break;
				case VD_DRAW_IMAG:
					{
						int x0, y0;
						const char * image;
						int alpha;

						lua.tableNext(); x0    = lua.getInt(-1);    lua.pop(1);
						lua.tableNext(); y0    = lua.getInt(-1);    lua.pop(1);
						lua.tableNext(); image = lua.getString(-1); lua.pop(1);
						lua.tableNext(); alpha = lua.getInt(-1);    lua.pop(1);

						// image は後で破棄しなければならないので、使った分をリストとして保持しておく。
						drawImage(x0, y0, image, alpha);
					}
					break;
				}
				lua.pop(4);
			}
			lua.pop(1);
			m_pDocNode->unlockDocument();
			m_pDocNode->setViewPortPos(0, 0);
			forceRefresh();
			CHANGE_D;
		}
		break;
	}
	return ret;
}

// VDoc で使用する画像をロードし、使った分だけイメージのハンドルを握っておく
CKLBImageAsset *
CKLBUIVirtualDoc::loadImage(const char * image)
{
	u32 handle;

	CKLBAssetManager& pAssetManager = CKLBAssetManager::getInstance();
	KLBTextureAssetPlugin* pPlug = (KLBTextureAssetPlugin*)pAssetManager.getPlugin('T'); // Texture

	pPlug->setLoadingMode(TEX_LOAD_GPUCPU);

	CKLBImageAsset * pImage = (CKLBImageAsset *)CKLBUtility::loadAssetScript(image, &handle);
	if(pImage) {
		// assetがロードできたらリスト項目を作る。
		VDIMG * pImg = KLBNEW(VDIMG);
		if(!pImg) {
			CKLBDataHandler::releaseHandle(handle);
			return NULL;
		}
		u8* pix		= pImage->m_pTextureAsset->m_softTexture;
		if (pix == NULL) {
			klb_assertAlways("TEXTURE IS ALREADY USED. To use bitmap, virtual doc must be the first to lock the resource or create a small special texture.");
		}
		pImg->handle = handle;
		pImg->pImage = pImage;
		pImg->next   = NULL;
		pImg->prev   = m_imgEnd;
		if(pImg->prev) {
			pImg->prev->next = pImg;
		} else {
			m_imgBegin = pImg;
		}
		m_imgEnd = pImg;
	}

	pPlug->setLoadingMode(TEX_LOAD_GPU);

	return pImage;
}

// VDoc で使用した画像をすべて解放する
void
CKLBUIVirtualDoc::destroyImages()
{
	VDIMG * pImg = m_imgBegin;
	while(pImg) {
		VDIMG * pNxt = pImg->next;
		CKLBDataHandler::releaseHandle(pImg->handle);
		KLBDELETE(pImg);
		pImg = pNxt;
	}
}

void
CKLBUIVirtualDoc::touchPadEvent()
{
	CKLBTouchPadQueue& tpq = CKLBTouchPadQueue::getInstance();
	float fx, fy;
	CKLBUtility::getNodePosition(getNode(), &fx, &fy);
	int x, y, rx, ry;
	x = fx;
	y = fy;

	int width   = m_viewWidth  * getScaleX();
	int height  = m_viewHeight * getScaleY();
	const char * func_callback = m_callBack;

	const PAD_ITEM * item;
	tpq.startItem();
	while((item = tpq.getItem())) {
		switch(item->type)
		{
		case PAD_ITEM::TAP:
			{
				// タップ位置がリストの範囲内に入っていれば自身に対する操作とみなす。
				rx = item->x - x;
				ry = item->y - y;
				if(rx < 0 || rx >= width || ry < 0 || ry >= height) {
					// クリップ外なのであずかり知らぬイベント。
					break;
				}
				m_dragID = item->id;
				m_dragX = item->x;
				m_dragY = item->y;
				tpq.useItem(item, this);
				if(func_callback) {
					CKLBScriptEnv::getInstance().call_eventVirtualDoc(func_callback, this, item->type, item->x, item->y, 0, 0);
				}
			}
			break;

		case PAD_ITEM::DRAG:
			{
				if(item->id != m_dragID) break;
				int mv_x = item->x - m_dragX;
				int mv_y = item->y - m_dragY;
				tpq.useItem(item, this);
				if(func_callback) {
					// DEBUG_PRINT("  EVENT: %p (drag)", this);
					CKLBScriptEnv::getInstance().call_eventVirtualDoc(func_callback, this, item->type, m_dragX, m_dragY, mv_x, mv_y);
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
				if(func_callback) {
					CKLBScriptEnv::getInstance().call_eventVirtualDoc(func_callback, this, item->type, m_dragX, m_dragY, mv_x, mv_y);
				}
				m_dragID = -1;
			}
			break;
		}
	}
}
