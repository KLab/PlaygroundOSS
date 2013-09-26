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
#include "CKLBUIClip.h"
#include "CKLBLuaEnv.h"
#include "CKLBScriptEnv.h"
#include "CKLBUISystem.h"
;

// Command Values
enum {
	UI_CLIP_SET_POSITION,       // Change the clip position
	UI_CLIP_SET_SIZE,           // Change the clip size
};

static IFactory::DEFCMD cmd[] = {
	// Operations of the list of items
	{ "UI_CLIP_SET_POSITION",	UI_CLIP_SET_POSITION },
	{ "UI_CLIP_SET_SIZE",		UI_CLIP_SET_SIZE },
	{0, 0}
};

static CKLBTaskFactory<CKLBUIClip> factory("UI_Clip", CLS_KLBUICLIP, cmd);

CKLBLuaPropTask::PROP_V2 CKLBUIClip::ms_propItems[] = {
	UI_BASE_PROP,
	{	"width",	INTEGER,	(setBoolT)&CKLBUIClip::setWidth,	(getBoolT)&CKLBUIClip::getWidth,	0	},
	{	"height",	INTEGER,	(setBoolT)&CKLBUIClip::setHeight,	(getBoolT)&CKLBUIClip::getHeight,	0	},
	{	"order",	UINTEGER,	(setBoolT)&CKLBUIClip::setOrder,	(getBoolT)&CKLBUIClip::getOrder,	0	},
	{	"maxodr",	UINTEGER,	(setBoolT)&CKLBUIClip::setMaxOdr,	(getBoolT)&CKLBUIClip::getMaxOdr,	0	}
};

enum {
	ARG_PARENT = 1,

	ARG_ORDER,
	ARG_MAXODR,

	ARG_X,
	ARG_Y,
	ARG_WIDTH,
	ARG_HEIGHT,

	ARG_REQUIRE = ARG_HEIGHT,
	ARG_NUMS    = ARG_HEIGHT
};

CKLBUIClip::CKLBUIClip()
: CKLBUITask    (CKLBTask::P_UIAFTER)
, m_clipHandle  (NULL)
{
	m_newScriptModel = true;
}

CKLBUIClip::~CKLBUIClip() 
{
}

u32
CKLBUIClip::getClassID()
{
	return CLS_KLBUICLIP;
}

CKLBUIClip *
CKLBUIClip::create(CKLBUITask * pParent, CKLBNode * pNode,
                   u32 base_order, u32 max_order,
                   float x, float y, float clip_width, float clip_height)
{
	CKLBUIClip * pTask = KLBNEW(CKLBUIClip);
    if(!pTask) { return NULL; }
	if(!pTask->init(pParent, pNode, base_order, max_order, x, y, clip_width, clip_height)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUIClip::init(CKLBUITask * pParent, CKLBNode * pNode,
					u32 base_order, u32 max_order,
					float x, float y, float clip_width, float clip_height)
{
	if(!setupNode()) return false;

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(base_order, max_order,
							x, y, clip_width, clip_height);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}

	return bResult;
}

bool
CKLBUIClip::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < ARG_REQUIRE || argc > ARG_NUMS) return false;

	u32 base_order      = lua.getInt(ARG_ORDER);
	u32 max_order       = lua.getInt(ARG_MAXODR);

	float x             = lua.getFloat(ARG_X);
	float y             = lua.getFloat(ARG_Y);
	float clip_width    = lua.getFloat(ARG_WIDTH);
	float clip_height   = lua.getFloat(ARG_HEIGHT);

	return initCore(base_order, max_order, x, y, clip_width, clip_height);
}

bool
CKLBUIClip::initCore(u32 base_order, u32 max_order,
                     float x, float y, float clip_width, float clip_height)
{
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	klb_assert((((s32)base_order) >= 0), "Order Problem");
	klb_assert((((s32)max_order ) >= 0), "Order Problem");

	m_basePriority  = base_order;
	m_endPriority   = max_order;
	
	m_clipX         = x;
	m_clipY         = y;
	m_clipWidth     = (int)clip_width;
	m_clipHeight    = (int)clip_height;

	setInitPos(m_clipX, m_clipY);
	setWidth(m_clipWidth);
	setHeight(m_clipHeight);

	setOrder(m_basePriority);
	setMaxOdr(m_endPriority);

	bool bResult = setClip(m_uiOrder, m_uiMaxOdr, 0, 0, (s16)m_fWidth, (s16)m_fHeight);

	if(!bResult) {
		const char * msg = "Overlapping clipping range or Reached max UI clipping stack.";
		CKLBScriptEnv::getInstance().error(msg);
		klb_assertAlways(msg);
	}

	return true;
}


bool
CKLBUIClip::setClip(u32 orderBegin, u32 orderEnd,
                    s16 clipX, s16 clipY, s16 clipWidth, s16 clipHeight)
{
	CKLBRenderingManager& pMgr  = CKLBRenderingManager::getInstance();
	CKLBRenderState* pClipStart = pMgr.allocateCommandState();
	CKLBRenderState* pClipEnd   = pMgr.allocateCommandState();

	CKLBNode * pNode = getNode();
	if(pNode->setRenderSlotCount(2) && pClipStart && pClipEnd) {
		pClipStart->changeOrder(pMgr, orderBegin);
		pClipEnd->changeOrder(pMgr, orderEnd);

		pClipStart->setUse  (true,false,null);
		pClipEnd->setUse    (true,false,null);

		pClipStart->setScissor(true, clipX, clipY, clipWidth, clipHeight);
		pClipEnd->setScissor(false);
							
		pNode->setRender(pClipStart,0);
		pNode->setRender(pClipEnd  ,1);

		m_clipHandle = CKLBUISystem::registerClip(pClipStart, pClipEnd);
        if(!m_clipHandle) { return false; }
	} else {
		if(pClipEnd)    { pMgr.releaseCommand(pClipEnd);    }
		if(pClipStart)  { pMgr.releaseCommand(pClipStart);  }
		return false;
	}
	return true;
}

void
CKLBUIClip::execute(u32 /*deltaT*/)
{
	// 一旦現在のclip領域を破棄する
    if(m_clipHandle) { CKLBUISystem::unregisterClip(m_clipHandle); }

	// clip領域を再設定する
	setClip(m_basePriority, m_endPriority, 0, 0, (s16)m_clipWidth, (s16)m_clipHeight);
	RESET_A;
	RESET_B;
}

void
CKLBUIClip::dieUI()
{
	if (m_clipHandle) {
		CKLBUISystem::unregisterClip(m_clipHandle);
	}
}

int
CKLBUIClip::commandUI(CLuaState& lua, int argc, int cmd)
{
	int ret = 0;
	switch(cmd)
	{
	default:
		{
			lua.retBool(false);
			ret = 1;
		}
		break;
	case UI_CLIP_SET_POSITION:
		{
			bool bResult = false;
			if(argc == 4) {
				m_clipX = lua.getFloat(3);
				m_clipY = lua.getFloat(4);
				setPosition(m_clipX, m_clipY);
				bResult = true;
			}
			lua.retBool(bResult);
			ret = 1;
		}
		break;
	case UI_CLIP_SET_SIZE:
		{
			bool bResult = false;
			if(argc == 4) {
				m_clipWidth = lua.getInt(3);
				m_clipHeight = lua.getInt(4);
				setSize(m_clipWidth, m_clipHeight);
				bResult = true;
			}
			lua.retBool(bResult);
			ret = 1;
		}
		break;
	}
	return ret;
}
