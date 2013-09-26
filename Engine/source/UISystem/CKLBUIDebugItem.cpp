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
#include "CKLBUIDebugItem.h"
#include "CKLBTouchPad.h"
#include "CKLBUtility.h"
#include "CKLBLuaEnv.h"
#include "CKLBScriptEnv.h"
#include "CKLBTexturePacker.h"

static IFactory::DEFCMD cmd[] = {
	{0, 0}
};
static CKLBTaskFactory<CKLBUIDebugItem> factory("UI_DbgLabel", CLS_KLBUIDBGLABEL, cmd);

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUIDebugItem::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",	UINTEGER,	(setBoolT)&CKLBUIDebugItem::setOrder,		(getBoolT)&CKLBUIDebugItem::getOrder,			0	},
	{	"font",		STRING,		(setBoolT)&CKLBUIDebugItem::setFont,		(getBoolT)&CKLBUIDebugItem::getFont,			0	},
	{	"size",		UINTEGER,	(setBoolT)&CKLBUIDebugItem::setSize,		(getBoolT)&CKLBUIDebugItem::getSize,			0	},
	{	"alpha",	UINTEGER,	(setBoolT)&CKLBUIDebugItem::setAlpha,		(getBoolT)&CKLBUIDebugItem::getAlpha,			0	},
	{	"color",	UINTEGER,	(setBoolT)&CKLBUIDebugItem::setU24Color,	(getBoolT)&CKLBUIDebugItem::getU24Color,		0	},
	{	"text",		STRING,		(setBoolT)&CKLBUIDebugItem::setText,		(getBoolT)&CKLBUIDebugItem::getText,			0	},
};

enum {
	ARG_PARENT = 1,

	ARG_ORDER,
	ARG_X,
	ARG_Y,

	ARG_ALPHA,
	ARG_COLOR,

	ARG_FONT,
	ARG_SIZE,

	ARG_TEXT,

	ARG_ID,
	ARG_CALLBACK,

	ARG_REQUIRE = ARG_CALLBACK,
	ARG_NUMS    = ARG_CALLBACK
};

CKLBUIDebugItem::CKLBUIDebugItem()
: CKLBUITask	()
, m_pLabel		(NULL)
, m_font		(NULL)
, m_text		(NULL)
, m_callback	(NULL)
{
	m_newScriptModel = true;
	m_format = TexturePacker::getCurrentModeTexture();
}

CKLBUIDebugItem::~CKLBUIDebugItem() 
{
	KLBDELETEA(m_font);
	KLBDELETEA(m_text);
	KLBDELETEA(m_callback);
}

u32
CKLBUIDebugItem::getClassID()
{
	return CLS_KLBUIDBGLABEL;
}

CKLBUIDebugItem* 
CKLBUIDebugItem::create(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, u32 alpha, u32 color, 
                        const char* font, u32 size, const char* text, const char* callback,u32 id) 
{
	CKLBUIDebugItem* pTask = KLBNEW(CKLBUIDebugItem);
    if(!pTask) { return NULL; }
	if(!pTask->init(pParent, pNode, order, x,y,alpha,color,font,size,text,callback,id)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool 
CKLBUIDebugItem::init(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, u32 alpha, u32 color, 
                      const char* font, u32 size, const char* text, const char* callback,u32 id) 
{
    if(!setupNode()) { return false; }
	bool bResult = initCore(order, x,y,alpha,color,font,size,text,callback,id);
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}
	return bResult;
}

bool 
CKLBUIDebugItem::initCore(u32 order, float x, float y, u32 alpha, u32 color, 
                          const char* font, u32 size, const char* text, const char* callback,u32 id)
{
	// 保持プロパティを定義
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	setInitPos(x, y);

	klb_assert((((s32)order) >= 0), "Order Problem");

	m_order = order;
	m_alpha = alpha;
	m_color = color;
	setStrC(m_font,  font);
	m_size  = size;
	setStrC(m_text,  text);
	setStrC(m_callback, callback);
	m_ID    = id;

	m_padId = -1;

	m_update = false;
	return setup_node();
}

bool
CKLBUIDebugItem::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();

	if(argc < ARG_REQUIRE || argc > ARG_NUMS) return false;

	return initCore(lua.getInt(ARG_ORDER),
					lua.getFloat(ARG_X),
					lua.getFloat(ARG_Y),
					lua.getInt(ARG_ALPHA),
					lua.getInt(ARG_COLOR),
					lua.getString(ARG_FONT),
					lua.getInt(ARG_SIZE),
					lua.getString(ARG_TEXT),
					lua.getString(ARG_CALLBACK),
					lua.getInt(ARG_ID));
}

bool
CKLBUIDebugItem::setup_node()
{
	// 本来VDocは動作中にプロパティを変更するような作りになっていないため、
	// プロパティ変更が生じたときは改めて VDOCを作り直す。
	CKLBNodeVirtualDocument * pNewNode = KLBNEW(CKLBNodeVirtualDocument);
    if(!pNewNode) { return false; }

    if(m_pLabel) { KLBDELETE(m_pLabel); }
	m_pLabel = pNewNode;

	getNode()->addNode(m_pLabel);

	// 描画コマンド数は固定。文字列一つだけの表示なので。
	m_pLabel->createDocument(1,m_format);

	CPFInterface& pfif = CPFInterface::getInstance();

	// 指定されている文字列とフォント、フォントサイズでの表示に必要な幅と高さを取得する。
	void * pFont = pfif.platform().getFont(m_size, m_font);
	pfif.platform().getTextInfo(m_text,pFont, &m_txinfo);

	// 必要な幅と高さが取得できたので、そのサイズで VDoc を作る
	m_pLabel->setDocumentSize(m_txinfo.width, m_txinfo.height);
	m_pLabel->setViewPortSize(m_txinfo.width, m_txinfo.height, 0.0f, 0.0f, m_order, false);

	// 親ノードで表示位置を指定
	// getNode()->setTranslate(getNum(PR_X), getNum(PR_Y));	// generic property で対応

	// font index = 0 で、指定されている文字列を描画
	m_pLabel->setFont(0, m_font, m_size);	// 指定フォントをindex=0に指定
	m_pLabel->clear(0);

	m_pLabel->lockDocument();
	m_pLabel->drawText(0, m_txinfo.top, m_text, m_color|(m_alpha << 24), 0);
	m_pLabel->unlockDocument();

	m_pLabel->setViewPortPos(0, 0);	// ViewPort とDocumentのサイズが同じで、かつ表示位置を(0,0)で固定

	// Moved to optimize font cache.
	pfif.platform().deleteFont(pFont);

	// 表示位置を指定
	// getNode()->setTranslate(getNum(PR_X), getNum(PR_Y));
	m_pLabel->markUpMatrix();
    return true;
}

void
CKLBUIDebugItem::execute(u32 /*deltaT*/)
{
	if(m_update) {
		setup_node();
		m_update = false;
	}
	//m_pLabel->setViewPortPos(0, 0);

	CKLBTouchPadQueue& tpq = CKLBTouchPadQueue::getInstance();
	tpq.startItem();
	const PAD_ITEM * item;
	while(NULL != (item = tpq.getItem())) {
		switch(item->type) {
		case PAD_ITEM::TAP:
			{
                if(m_padId >= 0) { continue; }
				float fx, fy;
				CKLBUtility::getNodePosition(getNode(), &fx, &fy);
				if(item->x >= fx && item->y >= fy &&
					item->x - fx < m_txinfo.width && item->y - fy < m_txinfo.height) {
					m_padId = item->id;
				}
			}
			break;
		case PAD_ITEM::DRAG:
			break;
		case PAD_ITEM::RELEASE:
		case PAD_ITEM::CANCEL:
			{
                if(item->id != m_padId) { break; }
				m_padId = -1;
				CKLBScriptEnv::getInstance().call_eventDebugItem(m_callback, this, m_ID);
			}
			break;
		}
	}
}

void
CKLBUIDebugItem::dieUI()
{
	KLBDELETE(m_pLabel);
}
