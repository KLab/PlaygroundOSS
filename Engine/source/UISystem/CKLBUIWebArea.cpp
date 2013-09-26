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
#include "CKLBUIWebArea.h"
#include "CKLBLuaEnv.h"
#include "CKLBScriptEnv.h"
#include "CKLBOSCtrlEvent.h"
#include "CKLBNetAPIKeyChain.h"
;
enum {
	UI_WEBVIEW_SETURL,
	UI_WEBVIEW_GETURL,
    UI_WEBVIEW_SCALESPAGETOFIT,
    UI_WEBVIEW_SETBGCOLOR,      // 背景色の設定
	UI_WEBVIEW_RESETCALLBACK,
    
    WEBVIEW_LOCALLINK = 0,
    WEBVIEW_DIDSTARTLOAD,
    WEBVIEW_DIDENDLOAD,
    WEBVIEW_FAILEDLOAD,
};

static IFactory::DEFCMD cmd[] = {
	{"UI_WEBVIEW_SETURL",           UI_WEBVIEW_SETURL           },
	{"UI_WEBVIEW_GETURL",           UI_WEBVIEW_GETURL           },
    {"UI_WEBVIEW_SCALESPAGETOFIT",	UI_WEBVIEW_SCALESPAGETOFIT  },
    {"UI_WEBVIEW_SETBGCOLOR",		UI_WEBVIEW_SETBGCOLOR       },
	{"UI_WEBVIEW_RESETCALLBACK",	UI_WEBVIEW_RESETCALLBACK    },
    
    {"WEBVIEW_LOCALLINK",       WEBVIEW_LOCALLINK       },
    {"WEBVIEW_DIDSTARTLOAD",    WEBVIEW_DIDSTARTLOAD    },
    {"WEBVIEW_DIDENDLOAD",      WEBVIEW_DIDENDLOAD      },
    {"WEBVIEW_FAILEDLOAD",      WEBVIEW_FAILEDLOAD      },

	{ 0, 0 }
};

static CKLBTaskFactory<CKLBUIWebArea> factory("UI_WebView", CLS_KLBUIWEBVIEW, cmd);

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUIWebArea::ms_propItems[] = {
	UI_BASE_PROP,
	{	"width",	INTEGER,	(setBoolT)&CKLBUIWebArea::setWidth,		(getBoolT)&CKLBUIWebArea::getWidth,		0	},
	{	"height",	INTEGER,	(setBoolT)&CKLBUIWebArea::setHeight,	(getBoolT)&CKLBUIWebArea::getHeight,	0	},
	{	"value",	STRING,		(setBoolT)&CKLBUIWebArea::setText,		(getBoolT)&CKLBUIWebArea::getText,		0	}
};

enum {
	ARG_PARENT = 1,

	ARG_MODE,

	ARG_X,
	ARG_Y,

	ARG_WIDTH,
	ARG_HEIGHT,

	ARG_VALUE,	// 初期表示URL
    
    ARG_CALLBACK,   // command-URIを受け付ける場合は、その受付callbackを指定する

	ARG_REQUIRE = ARG_HEIGHT,
	ARG_NUMS    = ARG_CALLBACK
};

CKLBUIWebArea::CKLBUIWebArea() 
: CKLBUITask    ()
, m_pWebView    (NULL)
, m_cmdCallback (NULL)
, m_text        (NULL)
{
	m_newScriptModel = true;
}

CKLBUIWebArea::~CKLBUIWebArea()
{
	KLBDELETEA(m_text);
	KLBDELETEA(m_cmdCallback);
}

u32 
CKLBUIWebArea::getClassID() 
{ 
    return CLS_KLBUIWEBVIEW; 
}

CKLBUIWebArea *
CKLBUIWebArea::create(CKLBUITask * pParent, CKLBNode * pNode,
                      bool mode, float x, float y,
                      float width, float height,
                      const char * url, const char * callback)
{
	CKLBUIWebArea * pTask = KLBNEW(CKLBUIWebArea);
    if(!pTask) { return NULL; }
	if(!pTask->init(pParent, pNode, mode, x, y, width, height, url, callback)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUIWebArea::init(CKLBUITask * pParent, CKLBNode * pNode,
                    bool mode, float x, float y,
                    float width, float height,
                    const char * url, const char * callback)
{
    if(!setupNode()) { return false; }

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(mode, x, y, width, height, url, callback);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}

	return bResult;
}

bool
CKLBUIWebArea::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < ARG_REQUIRE || argc > ARG_NUMS) return false;

	float x         = lua.getFloat(ARG_X);
	float y         = lua.getFloat(ARG_Y);
	bool  mode      = lua.getBool(ARG_MODE);
	float width     = lua.getFloat(ARG_WIDTH);
	float height    = lua.getFloat(ARG_HEIGHT);
	const char * url        = (argc >= ARG_VALUE)    ? lua.getString(ARG_VALUE)     : NULL;
    const char * callback   = (argc >= ARG_CALLBACK) ? lua.getString(ARG_CALLBACK)  : NULL;

	return initCore(mode, x, y, width, height, url, callback);
}

bool
CKLBUIWebArea::initCore(bool mode, float x, float y,
						float width, float height,
						const char * url, const char * callback)
{
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}
	setInitPos(x, y);
	const char * str = (url) ? url : "";
	if(callback) {
		m_cmdCallback = CKLBUtility::copyString(callback);
	}

    // 起動時点でauthorized tokenとregionが登録されていたら、それをWebViewに与える。
    CKLBNetAPIKeyChain& keychain = CKLBNetAPIKeyChain::getInstance();
    const char * token  = keychain.getToken();
    const char * region = keychain.getRegion();
    const char * client = keychain.getClient();
    const char * consumerKey = keychain.getConsumerKey();
    const char * appID  = keychain.getAppID();
	const char * userID = keychain.getUserID();
    
	m_pWebView = KLBNEWC( CKLBUIWebView,(mode, str, token, region, client, consumerKey, appID, userID));
	getNode()->addNode(m_pWebView);

	setText(str);
	setWidth((int)width);
	setHeight((int)height);

	return true;
}

void
CKLBUIWebArea::execute(u32 /* deltaT */)
{
    const char * text = m_pWebView->getText();
	if(text) {
		setStrC(m_text, text);
	}

    // WebView がイベントを起こしていたら処理する
    CKLBOSCtrlQueue& osctrl = CKLBOSCtrlQueue::getInstance();
    const OSCTRL * item;
    IWidget * pWidget = m_pWebView->getWidget();
    
    osctrl.startItem();
    // CLuaState& lua = CKLBLuaEnv::getInstance().getState();
    while(NULL != (item = osctrl.getItem(pWidget))) {
        switch(item->type) {
            case IClientRequest::E_URLJUMP:
            {
                // そのWebViewでcommand-URL遷移のイベントが発生していたら、Luaのcallbackに遷移先URLを丸ごと渡す
                const char * url = pWidget->getTmpString();
                if(m_cmdCallback) { CKLBScriptEnv::getInstance().call_webTask(m_cmdCallback, this, WEBVIEW_LOCALLINK, url); }
                break;
            }
            case IClientRequest::E_DIDSTARTLOADWEB:
            {
                // Webのロードが開始された
                if(m_cmdCallback) { CKLBScriptEnv::getInstance().call_webTask(m_cmdCallback, this, WEBVIEW_DIDSTARTLOAD, ""); }
                break;
            }
            case IClientRequest::E_DIDLOADENDWEB:
            {
                if(m_cmdCallback) { CKLBScriptEnv::getInstance().call_webTask(m_cmdCallback, this, WEBVIEW_DIDENDLOAD, ""); }
                break;
            }
            case IClientRequest::E_FAILEDLOADWEB:
            {
                if(m_cmdCallback) { CKLBScriptEnv::getInstance().call_webTask(m_cmdCallback, this, WEBVIEW_FAILEDLOAD, ""); }
                break;
            }
            default:
                break;
        }
    }
}

void
CKLBUIWebArea::dieUI()
{
	KLBDELETE(m_pWebView);
}

int
CKLBUIWebArea::commandUI(CLuaState& lua, int argc, int cmd)
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
	case UI_WEBVIEW_SETURL:
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
	case UI_WEBVIEW_GETURL:
		{
			if(argc != 2) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			const char * string = m_pWebView->getText();
			lua.retString(string);
			ret = 1;
		}
		break;
    case UI_WEBVIEW_SCALESPAGETOFIT:
        {
            bool bResult = false;
            if(argc == 3) {
                bResult = true;
                bool scalesPageToFit = lua.getBool(3);
                setScalesPageToFit(scalesPageToFit);
            }
            lua.retBool(bResult);
            ret = 1;
        }
        break;
    case UI_WEBVIEW_SETBGCOLOR:
        {
            if(argc != 4) {
                lua.retBoolean(false);
                ret = 1;
                break;
            }
            u32 alpha = lua.getInt(3);
            u32 color = lua.getInt(4);
            setBgColor(alpha, color);
            lua.retBoolean(true);
            ret = 1;
        }
        break;
	case UI_WEBVIEW_RESETCALLBACK:
		{
			if (argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			const char * string = lua.getString(3);
			if (string) {
				const char * copy   = CKLBUtility::copyString(string);
				if (copy) {
					KLBDELETEA(m_cmdCallback);
					m_cmdCallback = copy;
				}
			}
		}
		break;
	}
	return ret;
}
