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
#include "CKLBUITextInput.h"
#include "CKLBLuaEnv.h"
#include "CKLBUtility.h"
;
enum {
	UI_TEXTBOX_SETTEXT,
	UI_TEXTBOX_GETTEXT,
    UI_TEXTBOX_SETPLACEHOLDER,
    UI_TEXTBOX_SETCOLOR,
    UI_TEXTBOX_SETFONT,
    UI_TEXTBOX_SETMAXLEN,
	UI_TEXTBOX_GETMAXLEN,
    UI_TEXTBOX_SETCHARTYPE,
	UI_TEXTBOX_GETCHARCOUNT,
    UI_TEXTBOX_SETALIGN
};
static IFactory::DEFCMD cmd[] = {
	{"UI_TEXTBOX_SETTEXT",          UI_TEXTBOX_SETTEXT },
	{"UI_TEXTBOX_GETTEXT",          UI_TEXTBOX_GETTEXT },
    {"UI_TEXTBOX_SETPLACEHOLDER",   UI_TEXTBOX_SETPLACEHOLDER },
    {"UI_TEXTBOX_SETCOLOR",         UI_TEXTBOX_SETCOLOR },
    {"UI_TEXTBOX_SETFONT",          UI_TEXTBOX_SETFONT },
    {"UI_TEXTBOX_SETMAXLEN",        UI_TEXTBOX_SETMAXLEN },
	{"UI_TEXTBOX_GETMAXLEN",		UI_TEXTBOX_GETMAXLEN },
    {"UI_TEXTBOX_SETCHARTYPE",      UI_TEXTBOX_SETCHARTYPE },
	{"UI_TEXTBOX_GETCHARCOUNT",		UI_TEXTBOX_GETCHARCOUNT },
	{"UI_TEXTBOX_SETALIGN",         UI_TEXTBOX_SETALIGN },
    
    {"TXCH_7BIT_ASCII",             IWidget::TXCH_7BIT_ASCII },
    {"TXCH_UTF8",                   IWidget::TXCH_UTF8 },
    
    {"TX_ALIGN_LEFT",               IWidget::TX_ALIGN_LEFT },
    {"TX_ALIGN_CENTER",             IWidget::TX_ALIGN_CENTER },
    {"TX_ALIGN_RIGHT",              IWidget::TX_ALIGN_RIGHT },
    
	{ 0, 0 }
};

static CKLBTaskFactory<CKLBUITextInput> factory("UI_TextInput", CLS_KLBUITEXTINPUT, cmd);

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUITextInput::ms_propItems[] = {
	UI_BASE_PROP,
	{	"width",	UINTEGER,	(setBoolT)&CKLBUITextInput::setWidth,	(getBoolT)&CKLBUITextInput::getWidth,	0	},
	{	"height",	UINTEGER,	(setBoolT)&CKLBUITextInput::setHeight,	(getBoolT)&CKLBUITextInput::getHeight,	0	},
	{	"value",	STRING,		(setBoolT)&CKLBUITextInput::setText,	(getBoolT)&CKLBUITextInput::getText,	0	}
};

enum {
	ARG_PARENT = 1,

	ARG_MODE,

	ARG_X,
	ARG_Y,

	ARG_WIDTH,
	ARG_HEIGHT,

	ARG_VALUE,

	ARG_CALLBACK,
	ARG_ID,
	ARG_MAXLEN,
    ARG_CHARTYPE,

	ARG_REQUIRE = ARG_HEIGHT,
	ARG_NUMS    = ARG_CHARTYPE
};


CKLBUITextInput::CKLBUITextInput() 
: CKLBUITask()
, m_pTextBox(NULL)
, m_text    (NULL) 
, m_width   (0)
, m_height  (0)
{
	m_newScriptModel = true;
}

CKLBUITextInput::~CKLBUITextInput() 
{
	KLBDELETEA(m_text);
}

u32
CKLBUITextInput::getClassID()
{
	return CLS_KLBUITEXTINPUT;
}


CKLBUITextInput *
CKLBUITextInput::create(CKLBUITask * pParent, CKLBNode * pNode,
                        bool passwdmode,
                        float x, float y, float width, float height,
                        const char * default_text,
                        const char * on_change_callback,
                        int widget_id, int maxlen, u32 chartype)
{
	CKLBUITextInput * pTask = KLBNEW(CKLBUITextInput);
    if(!pTask) { return NULL; }
	if(!pTask->init(pParent, pNode, passwdmode,
					x, y, width, height,
					default_text,
					on_change_callback, widget_id, maxlen, chartype)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

	
bool
CKLBUITextInput::init(CKLBUITask * pParent, CKLBNode * pNode,
                      bool passwdmode,
                      float x, float y, float width, float height,
                      const char * default_text,
                      const char * on_change_callback,
                      int widget_id, int maxlen, u32 chartype)
{
    if(!setupNode()) { return false; }

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(passwdmode,
							x, y, width, height,
							default_text,
							on_change_callback,
							widget_id, maxlen, chartype);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}

	return bResult;
}

bool
CKLBUITextInput::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
    if(argc < ARG_REQUIRE || argc > ARG_NUMS) { return false; }

	float x         = lua.getFloat(ARG_X);
	float y         = lua.getFloat(ARG_Y);
	bool passwdmode = lua.getBool(ARG_MODE);
	float width     = lua.getFloat(ARG_WIDTH);
	float height    = lua.getFloat(ARG_HEIGHT);
	const char * default_text       = (argc >= ARG_VALUE) ? lua.getString(ARG_VALUE) : "";
	const char * on_change_callback = (argc >= ARG_CALLBACK && !lua.isNil(ARG_CALLBACK)) ? lua.getString(ARG_CALLBACK) : NULL;
	int widget_id   = (argc >= ARG_ID)       ? lua.getInt(ARG_ID)       : 0;
	int maxlen      = (argc >= ARG_MAXLEN)   ? lua.getInt(ARG_MAXLEN)   : 0;
    int chartype    = (argc >= ARG_CHARTYPE) ? lua.getInt(ARG_CHARTYPE) : (IWidget::TXCH_7BIT_ASCII|IWidget::TXCH_UTF8);
	return initCore(passwdmode, x, y, width, height, default_text, on_change_callback, widget_id, maxlen, chartype);
}

bool
CKLBUITextInput::initCore(bool passwdmode,
                          float x, float y, float width, float height,
                          const char * default_text,
                          const char * on_change_callback,
                          int widget_id, int maxlen, u32 chartype)
{
	if (!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}
	setInitPos(x, y);

	m_ID        = widget_id;
	m_callback  = (on_change_callback) ? CKLBUtility::copyString(on_change_callback) : NULL;

	m_pTextBox  = KLBNEWC( CKLBUITextBox,(passwdmode, maxlen));

	getNode()->addNode(m_pTextBox);
	setWidth(width);
	setHeight(height);
	setText(default_text);
    setCharType(chartype);
	return true;
}

void
CKLBUITextInput::execute(u32 /* deltaT */)
{
	const char * text = m_pTextBox->getText();
	bool bChange;
	if ((text && !m_text) || (!text && m_text)) {
		bChange = true;
	} else {
		if (text && m_text) {
			bChange = strcmp(text, m_text) ? true : false;
		} else {
			bChange = false;
		}
	}
	setStrC(m_text, text);

	if(m_callback && bChange) {
		CKLBScriptEnv::getInstance().call_textInput(m_callback, this, m_text, m_ID);
	}
}

void
CKLBUITextInput::dieUI()
{
	KLBDELETEA(m_callback);
	KLBDELETE(m_pTextBox);
}

int
CKLBUITextInput::commandUI(CLuaState& lua, int argc, int cmd)
{
	int ret = 1;
	switch(cmd)
	{
	default:
		{
			lua.retBoolean(false);
			ret = 1;
		}
		break;
	case UI_TEXTBOX_SETTEXT:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			const char * string = lua.getString(3);
			setText(string);
			lua.retBoolean(true);
			ret = 1;
		}
		break;
	case UI_TEXTBOX_GETTEXT:
		{
			if(argc != 2) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			const char * string = getText();
			lua.retString(string);
			ret = 1;
		}
		break;
	case UI_TEXTBOX_GETCHARCOUNT:
		{
			if(argc != 2) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			s32 count = getCharCount();
			lua.retInt(count);
			ret = 1;
		}
		break;
    case UI_TEXTBOX_SETPLACEHOLDER:
        {
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			const char * string = lua.getString(3);
			setPlaceHolder(string);
			lua.retBoolean(true);
			ret = 1;
        }
        break;
    case UI_TEXTBOX_SETCOLOR:
        {
			if(argc != 5) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
            bool bTouch = lua.getBool(3);
            u32  fg_rgb = lua.getInt(4);
            u32  bg_rgb = lua.getInt(5);

			setColor(bTouch, fg_rgb, bg_rgb);
			
			lua.retBoolean(true);
			ret = 1;            
        }
        break;
    case UI_TEXTBOX_SETFONT:
        {
            bool bResult = false;
            if(argc == 4) {
                const char * fontname = (!lua.isNil(3)) ? lua.getString(3) : NULL;
                float fontsize = lua.getFloat(4);
                
                setFont(fontname, fontsize);
                bResult = true;
            }
            lua.retBool(bResult);
            ret = 1;
        }
        break;
    case UI_TEXTBOX_SETMAXLEN:
        {
            bool bResult = false;
            if(argc == 3) {
                int maxlen = lua.getInt(3);
                setMaxLen(maxlen);
                bResult = true;
            }
            lua.retBool(bResult);
            ret = 1;
        }
        break;
	case UI_TEXTBOX_GETMAXLEN:
		{
			ret = 1;
            if(argc != 2) {
	            lua.retBool(false);
            } else {
				lua.retInt(getMaxLen());
			}
		}
		break;
    case UI_TEXTBOX_SETCHARTYPE:
        {
            bool bResult = false;
            if(argc == 3) {
                int chartype = lua.getInt(3);
                setCharType((IWidget::TEXTCHARTYPE)chartype);
                bResult = true;
            }
            lua.retBool(bResult);
            ret = 1;
        }
        break;
    case UI_TEXTBOX_SETALIGN:
        {
            bool bResult = false;
            if(argc == 3)
            {
                int alignType = lua.getInt(3);
                setAlign(alignType);
                bResult = true;
            }
            lua.retBool(bResult);
            ret = 1;
        }
        break;
	}
	return ret;
}
