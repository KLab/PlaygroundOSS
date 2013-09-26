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
#include "CKLBUILabel.h"
;
// Command Values
enum {
	UI_LABEL_SET_TEXT,
	UI_LABEL_SET_COLOR,
	UI_LABEL_SET_FONT,
	UI_LABEL_SET_POSITION,
	UI_LABEL_SET_ALIGNMENT
};

static IFactory::DEFCMD cmd[] = {
	{"UI_LABEL_SET_TEXT",		UI_LABEL_SET_TEXT },
	{"UI_LABEL_SET_COLOR",		UI_LABEL_SET_COLOR },
	{"UI_LABEL_SET_FONT",		UI_LABEL_SET_FONT },
	{"UI_LABEL_SET_POSITION",	UI_LABEL_SET_POSITION },
	{"UI_LABEL_SET_ALIGNMENT",	UI_LABEL_SET_ALIGNMENT },
	{0, 0}
};
static CKLBTaskFactory<CKLBUILabel> factory("UI_Label", CLS_KLBUILABEL, cmd);

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUILabel::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",			UINTEGER,	(setBoolT)&CKLBUILabel::setOrder,		(getBoolT)&CKLBUILabel::getOrder,		0		},
	{	"font",				STRING,		(setBoolT)&CKLBUILabel::setFont,		(getBoolT)&CKLBUILabel::getFont,		0		},
	{	"size",				UINTEGER,	(setBoolT)&CKLBUILabel::setFontSize,	(getBoolT)&CKLBUILabel::getFontSize,	0		},
	{	"txt_alpha",		UINTEGER,	(setBoolT)&CKLBUILabel::setAlpha,		(getBoolT)&CKLBUILabel::getAlpha,		0		},
	{	"txt_color",		UINTEGER,	(setBoolT)&CKLBUILabel::setU24Color,	(getBoolT)&CKLBUILabel::getU24Color,	0		},
	{	"text",				STRING,		(setBoolT)&CKLBUILabel::setText,		(getBoolT)&CKLBUILabel::getText,		0		},
	{	"align",			UINTEGER,	(setBoolT)&CKLBUILabel::setAlign,		(getBoolT)&CKLBUILabel::getAlign,		0		}
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

	ARG_ALIGN,

	ARG_REQUIRE = ARG_TEXT,
	ARG_NUMS = ARG_ALIGN
};
CKLBUILabel::CKLBUILabel()
: CKLBUITask()
, m_pLabel	(NULL)
, m_font	(NULL)
, m_text	(NULL)
{
	setNotAlwaysActive();
	m_newScriptModel = true;
}

CKLBUILabel::~CKLBUILabel() 
{
	KLBDELETEA(m_font);
	KLBDELETEA(m_text);
}

u32
CKLBUILabel::getClassID()
{
	return CLS_KLBUILABEL;
}

CKLBUILabel* CKLBUILabel::create(CKLBUITask* parent, CKLBNode* pNode, u32 order, float x, float y, u32 alpha, u32 color, const char* font, u32 size, const char* text, u32 align) {
	CKLBUILabel* pTask = KLBNEW(CKLBUILabel);
    if(!pTask) { return NULL; }
	if(!pTask->init(parent, pNode, order, x, y, alpha, color, font, size, text, align)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUILabel::init(CKLBUITask* pParent, CKLBNode* pNode, u32 order, float x, float y, u32 alpha, u32 color, const char* font, u32 size, const char* text,u32 align) {
	if (!setupNode()) return false;
	bool bResult = initCore(order, x, y,alpha, color, font, size, text,align);
	bResult = registUI(pParent, bResult);
	if (pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}
	return bResult;
}

bool
CKLBUILabel::initCore(u32 order, float x, float y, u32 alpha, u32 color, const char* font, u32 size, const char* text, u32 align)
{
	if (!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	setInitPos(x, y);

	klb_assert((((s32)order) >= 0), "Order Problem");

	m_order = order;
	m_alpha = alpha;
	m_color = color;
	setStrC(m_font,font);
	m_size  = size;
	setStrC(m_text,  text);
	m_align = align;
	m_update = false;
	return setup_node();
}

bool
CKLBUILabel::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();

    if(argc < ARG_REQUIRE || argc > ARG_NUMS) { return false; }

	return initCore(lua.getInt(ARG_ORDER),
                    lua.getFloat(ARG_X),
                    lua.getFloat(ARG_Y),
                    lua.getInt(ARG_ALPHA),
                    lua.getInt(ARG_COLOR),
                    lua.getString(ARG_FONT),
                    lua.getInt(ARG_SIZE),
                    lua.getString(ARG_TEXT),
                    (argc >= ARG_ALIGN) ? lua.getInt(ARG_ALIGN) : 0
                   );
}

int
CKLBUILabel::commandUI(CLuaState& lua, int argc, int cmd)
{
	int ret = 1;
	switch(cmd)
	{
	case UI_LABEL_SET_TEXT:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				return 1;
			}
			const char * text = lua.getString(3);

			setText(text);

			lua.retBoolean(true);
			ret = 1;
		}
		break;
	case UI_LABEL_SET_COLOR:
		{
			if(argc != 4) {
				lua.retBoolean(false);
				return 1;
			}
			u32 alpha = lua.getInt(3);
			u32 col = lua.getInt(4);

			setColor((alpha << 24) | col);

			lua.retBoolean(true);
			ret = 1;
		}
		break;
	case UI_LABEL_SET_FONT:
		{
			if(argc != 4) {
				lua.retBoolean(false);
				return 1;
			}
			const char * font = lua.getString(3);
			u32 size = lua.getInt(4);

			setFont(font);
			setFontSize(size);

			lua.retBoolean(true);
			ret = 1;
		}
		break;
	case UI_LABEL_SET_POSITION:
		{
			if(argc != 4) {
				lua.retBoolean(false);
				return 1;
			}
			float x = lua.getFloat(3);
			float y = lua.getFloat(4);

			setPosition(x,y);

			lua.retBoolean(true);
			ret = 1;
		}
		break;
	case UI_LABEL_SET_ALIGNMENT:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				return 1;
			}
			u32 align = lua.getInt(3);

			setAlign(align);

			lua.retBoolean(true);
			ret = 1;
		}
		break;
	}

	return ret;
}

void
CKLBUILabel::execute(u32 /*deltaT*/)
{
	setup_node();
	RESET_A;

	//m_pLabel->setViewPortPos(0, 0);
}

void
CKLBUILabel::dieUI()
{
	KLBDELETE(m_pLabel);
}

bool
CKLBUILabel::setup_node()
{
	if(!m_pLabel) {
		m_pLabel = KLBNEWC(CKLBLabelNode,(0,m_font,0));	// No text, No font
		if(m_pLabel) { 
			m_pLabel->setUseTextSize(true);
			getNode()->addNode(m_pLabel); 
			m_pLabel->setPriority(m_order);
		}
	}

	if(!m_pLabel) {
		return false;
	}

	m_pLabel->lock(true);

	m_pLabel->setFont   (m_size,m_font);
	m_pLabel->setAlign  (m_align);
	m_pLabel->setText   (m_text);

	u32 alpha = m_alpha;
	u32 col   = m_color;
	m_pLabel->setTextColor(col|(alpha << 24));

	m_pLabel->lock(false);
	m_pLabel->forceRefresh();

	//	DEBUG_PRINT("[%p] setup_node(): str = [%s] color=%08x (first)",
	//		this, getStr(PR_TEXT), col|(alpha << 24));
    return true;
}
