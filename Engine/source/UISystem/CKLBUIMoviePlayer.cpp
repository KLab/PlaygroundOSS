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
//
//  CKLBUIMoviePlayer.cpp
//  GameEngine
//
//

#include "CKLBUIMoviePlayer.h"
#include "CKLBLuaEnv.h"
#include "CKLBScriptEnv.h"
#include "CKLBOSCtrlEvent.h"

enum {
	UI_MOVIE_SETPATH,
	UI_MOVIE_GETPATH,
    
    UI_MOVIE_PLAY,
    UI_MOVIE_STOP,
    UI_MOVIE_PAUSE,
    UI_MOVIE_RESUME,
};

static IFactory::DEFCMD cmd[] = {
	{"UI_MOVIE_SETPATH", UI_MOVIE_SETPATH },
	{"UI_MOVIE_GETPATH", UI_MOVIE_GETPATH },

    {"UI_MOVIE_PLAY",   UI_MOVIE_PLAY },
	{"UI_MOVIE_STOP",   UI_MOVIE_STOP },
	{"UI_MOVIE_PAUSE",  UI_MOVIE_PAUSE },
	{"UI_MOVIE_RESUME", UI_MOVIE_RESUME },
    { 0, 0 }
};

static CKLBTaskFactory<CKLBUIMoviePlayer> factory("UI_MoviePlayer", CLS_KLBUIMOVIEPLAYER, cmd);

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUIMoviePlayer::ms_propItems[] = {
	UI_BASE_PROP,
	{	"width",		UINTEGER,	(setBoolT)&CKLBUIMoviePlayer::setWidth,		(getBoolT)&CKLBUIMoviePlayer::getWidth,		0	},
	{	"height",		UINTEGER,	(setBoolT)&CKLBUIMoviePlayer::setHeight,	(getBoolT)&CKLBUIMoviePlayer::getHeight,	0	},
	{	"value",		STRING,		(setBoolT)&CKLBUIMoviePlayer::setText,		(getBoolT)&CKLBUIMoviePlayer::getText,		0	}
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


CKLBUIMoviePlayer::CKLBUIMoviePlayer() 
: CKLBUITask    ()
, m_pMovieNode  (NULL)
, m_cmdCallback (NULL)
, m_url         (NULL) 
{
	m_newScriptModel = true;
}


CKLBUIMoviePlayer::~CKLBUIMoviePlayer() 
{
	KLBDELETEA(m_url);
}

u32
CKLBUIMoviePlayer::getClassID()
{
	return CLS_KLBUIMOVIEPLAYER;
}


CKLBUIMoviePlayer *
CKLBUIMoviePlayer::create(CKLBUITask * pParent, CKLBNode * pNode,
                          bool mode, float x, float y,
                          float width, float height,
                          const char * url, const char * callback)
{
	CKLBUIMoviePlayer * pTask = KLBNEW(CKLBUIMoviePlayer);
    if(!pTask) { return NULL; }
	if(!pTask->init(pParent, pNode, mode, x, y, width, height, url, callback)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUIMoviePlayer::init(CKLBUITask * pParent, CKLBNode * pNode,
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
CKLBUIMoviePlayer::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
    if(argc < ARG_REQUIRE || argc > ARG_NUMS) { return false; }
    
	float x         = lua.getFloat(ARG_X);
	float y         = lua.getFloat(ARG_Y);
	bool mode       = lua.getBool(ARG_MODE);
	float width     = lua.getFloat(ARG_WIDTH);
	float height    = lua.getFloat(ARG_HEIGHT);
	const char * url        = (argc >= ARG_VALUE)    ? lua.getString(ARG_VALUE)     : NULL;
    const char * callback   = (argc >= ARG_CALLBACK) ? lua.getString(ARG_CALLBACK)  : NULL;
    
	return initCore(mode, x, y, width, height, url, callback);
}

bool
CKLBUIMoviePlayer::initCore(bool mode, float x, float y,
                            float width, float height,
                            const char * url, const char * callback)
{
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}
	setInitPos(x, y);
	m_width  = width;
	m_height = height;

	const char * str = (url) ? url : "";
    bool background = mode;
	setStrC(m_url, str);
    m_cmdCallback = (!callback) ? NULL : CKLBUtility::copyString(callback);
        
	m_pMovieNode = KLBNEWC( CKLBMovieNode, (str, background) );
    getNode()->addNode(m_pMovieNode);
	m_pMovieNode->setWidth(m_width);
	m_pMovieNode->setHeight(m_height);
    
	return true;
}

void
CKLBUIMoviePlayer::execute(u32 /* deltaT */)
{
	if(CHANGE_A) {
		m_pMovieNode->setWidth(m_width);
		m_pMovieNode->setHeight(m_height);
		RESET_A;
	}

	if(CHANGE_B) {
		m_pMovieNode->setText(m_url);
		RESET_B;
	}
    
    // 再生が終了したら、設定されているコールバックを呼び出す
    if(m_pMovieNode->getWidget()) {
        if(m_pMovieNode->getWidget()->status()) {
            CKLBScriptEnv::getInstance().call_eventMovie(m_cmdCallback, this);
        }
    }
}

void
CKLBUIMoviePlayer::dieUI()
{
	KLBDELETE(m_pMovieNode);
    KLBDELETEA(m_cmdCallback);
}

int
CKLBUIMoviePlayer::commandUI(CLuaState& lua, int argc, int cmd)
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
        case UI_MOVIE_SETPATH:
        {
            bool result = false;
            if(argc == 3) {
                const char * path = lua.getString(3);
				setText(path);
                result = true;                                                  
            }
            lua.retBool(result);
            ret = 1;
        }
            break;
        case UI_MOVIE_GETPATH:
        {
            if(argc == 2) {
                const char * path = getText();
                lua.retString(path);
            } else {
                lua.retNil();
            }
            ret = 1;
        }
            break;
            
        case UI_MOVIE_PLAY:
        {
            bool result = false;
            if(argc == 2) {
				moviePlay();
                result = true;
            }
            lua.retBool(result);
            ret = 1;
        }
            break;
        case UI_MOVIE_STOP:
        {
            bool result = false;
            if(argc == 2) {
				movieStop();
                result = true;
            }
            lua.retBool(result);
            ret = 1;
        }
            break;
        case UI_MOVIE_PAUSE:
        {
            bool result = false;
            if(argc == 2) {
				moviePause();
                result = true;
            }
            lua.retBool(result);
            ret = 1;
        }
            break;
        case UI_MOVIE_RESUME:
        {
            bool result = false;
            if(argc == 2) {
				movieResume();
                result = true;
            }
            lua.retBool(result);
            ret = 1;            
        }
            break;
    }
	return ret;
}
