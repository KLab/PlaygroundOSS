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
#include "CKLBUISWFPlayer.h"
#include "CKLBObject.h"
#include "CKLBLuaEnv.h"
#include "CKLBScriptEnv.h"
#include "Message.h"
#include "CKLBDataHandler.h"
#include "CKLBUtility.h"
;
// Command Values
enum {
	UI_SWF_PLAY = 0,
	UI_SWF_STOP,
	UI_SWF_GOTOFRAME,
	UI_SWF_REACHFRAME,
	UI_SWF_GETFRAME,
	UI_SWF_SETFRAMERATE,
	UI_SWF_SETFRAMERATE_SCALE,
	UI_SWF_SETIMAGE,

	//	UI_SWF_REPLACE_ASSETS,		// 廃止

	UI_SWF_IS_ANIM,
	UI_SWF_SETSEVOLUME,
};
static IFactory::DEFCMD cmd[] = {
	{"UI_SWF_PLAY",			UI_SWF_PLAY},
	{"UI_SWF_STOP",			UI_SWF_STOP},
	{"UI_SWF_GOTOFRAME",	UI_SWF_GOTOFRAME},
	{"UI_SWF_REACHFRAME",	UI_SWF_REACHFRAME},
//	{"UI_SWF_GETFRAME",		UI_SWF_GETFRAME},
	{"UI_SWF_SETFRAMERATE",	UI_SWF_SETFRAMERATE},
	{"UI_SWF_SETFRAMERATE_SCALE", UI_SWF_SETFRAMERATE_SCALE },
//	{"UI_SWF_SETIMAGE",		UI_SWF_SETIMAGE},

//	{"UI_SWF_REPLACE_ASSETS", UI_SWF_REPLACE_ASSETS },

	{"UI_SWF_IS_ANIM",		UI_SWF_IS_ANIM },
	{"UI_SWF_SETSEVOLUME",	UI_SWF_SETSEVOLUME },
	{0, 0}
};

static CKLBTaskFactory<CKLBUISWFPlayer> factory("UI_SWFPlayer", CLS_KLBUISWFPLAYER, cmd);

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUISWFPlayer::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",	UINTEGER,	(setBoolT)&CKLBUISWFPlayer::setOrder,	(getBoolT)&CKLBUISWFPlayer::getOrder,		0	},
	{	"asset",	R_STRING,	NULL,									(getBoolT)&CKLBUISWFPlayer::getAsset,		0	},
	{	"mvname",	R_STRING,	NULL,									(getBoolT)&CKLBUISWFPlayer::getMovieName,	0	},

	{	"callback",	STRING,		(setBoolT)&CKLBUISWFPlayer::setCallBack,(getBoolT)&CKLBUISWFPlayer::getCallBack,	0	},

	{	"play",		BOOLEANT,	(setBoolT)&CKLBUISWFPlayer::setPlay,	(getBoolT)&CKLBUISWFPlayer::getPlay,		0	}
};

enum {
	ARG_PARENT = 1,

	ARG_ORDER,
	ARG_X,
	ARG_Y,

	ARG_ASSET,
	ARG_MVNAME,
	ARG_CALLBACK,

	ARG_ASSET_REPLACE,

	ARG_REQUIRE = ARG_MVNAME,
	ARG_NUMS = ARG_ASSET_REPLACE
};


CKLBUISWFPlayer::CKLBUISWFPlayer()
: CKLBUITask    ()
, m_beginLabel  (NULL)
, m_flashHandle (0)
, m_callBack    (NULL)
, m_movieName   (NULL)
, m_asset       (NULL)
, m_play        (true)
{
	setNotAlwaysActive();
	m_newScriptModel = true;
}

CKLBUISWFPlayer::~CKLBUISWFPlayer() 
{
	KLBDELETEA(m_callBack);
	KLBDELETEA(m_movieName);
	KLBDELETEA(m_asset);
}

u32
CKLBUISWFPlayer::getClassID()
{
	return CLS_KLBUISWFPLAYER;
}

CKLBUISWFPlayer *
CKLBUISWFPlayer::create(CKLBUITask * pParent, CKLBNode * pNode,
                        u32 order, float x, float y, const char * asset,
                        const char * movie_name, const char * complete_callback,
                        const char ** replace_list, int asset_cnt)
{
	CKLBUISWFPlayer * pTask = KLBNEW(CKLBUISWFPlayer);
    if(!pTask) { return NULL; }

	if(!pTask->init(pParent, pNode, order, x, y, asset, movie_name, complete_callback,
					replace_list, asset_cnt)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUISWFPlayer::init(CKLBUITask * pParent, CKLBNode * pNode,
                      u32 order, float x, float y, const char * asset,
                      const char * movie_name, const char * complete_callback,
                      const char ** replace_list, int asset_cnt)
{
    if(!setupNode()) { return false; }

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(order, x, y, asset, movie_name, complete_callback, replace_list, asset_cnt);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}

	return bResult;
}

bool
CKLBUISWFPlayer::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
    if(argc < ARG_REQUIRE || argc > ARG_NUMS) { return false; }
	float x     = lua.getFloat(ARG_X);
	float y     = lua.getFloat(ARG_Y);
	u32   order = lua.getInt(ARG_ORDER);
	const char * asset      = lua.getString(ARG_ASSET);
	const char * mvname     = (lua.isNil(ARG_MVNAME)) ? NULL : lua.getString(ARG_MVNAME);
	const char * callback   = (argc >= ARG_CALLBACK)  ? lua.getString(ARG_CALLBACK) : NULL;

	int asset_cnt = 0;
	const char ** replace_list = (argc >= ARG_ASSET_REPLACE) ? replaceAssets(lua, ARG_ASSET_REPLACE, &asset_cnt) : NULL;
	bool bResult = initCore(order, x, y, asset, mvname, callback, replace_list, asset_cnt);
	removeReplaceList(replace_list, asset_cnt);
	return bResult;
}

bool
CKLBUISWFPlayer::initCore(u32 order,
                          float x, float y, const char * asset,
                          const char * movie_name, const char * complete_callback,
                          const char ** replace_list, int asset_cnt)
{
	// 保持プロパティの定義
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	setInitPos(x, y);

	REFRESH_A;

	klb_assert((((s32)order) >= 0), "Order Problem");

	m_order = order;
	setStrC(m_asset, asset);

	if(!movie_name) {
		m_movieName = NULL;
	} else {
		setStrC(m_movieName, movie_name);
	}

	if(complete_callback) { setStrC(m_callBack, complete_callback); }

	// Asset をロードし、CKLBSWFAssetを作る。
	CKLBSWFAsset* pSWFAsset;
	pSWFAsset = (CKLBSWFAsset *)CKLBUtility::loadAssetScript(m_asset, &m_flashHandle);
    if(!pSWFAsset) { return false; }

	// CKLBSWFAsset から、addMovie でCKLBSWFMovieを作る。
	SMatrix2D mat;
	m_pSWFNode = (CKLBSWFMovie*)pSWFAsset->addMovieA((char *)m_movieName, 0, &mat, 0, replace_list, asset_cnt);
	if(!m_pSWFNode) {
		klb_assertAlways("SWF could not create instance of movie %s. Is ASLinkage setup correctly ? Movie Name correct ?", m_movieName);
		CKLBDataHandler::releaseHandle(m_flashHandle);
		return false;
	}
	getNode()->addNode(m_pSWFNode);

	// 初期パラメータを与える
	m_pSWFNode->setPriority(m_order);

	// メッセージcallbackを登録する
	m_pSWFNode->setListener(this);

	// 初期状態のフレームレートを取得する(単位:[ms])
	m_defaultRate = m_pSWFNode->getFrameRate();

	return true;
}

void
CKLBUISWFPlayer::execute(u32)
{
	if(CHANGE_A) {
		// スクリプトからプロパティが変更されたら反映させる
		m_pSWFNode->setPlay(m_play);
		m_pSWFNode->setPriority(m_order);
		RESET_A;
	}
}

void
CKLBUISWFPlayer::dieUI()
{
	LABEL * pLabel = m_beginLabel;
	LABEL * nxt;
	while(pLabel) {
		nxt = pLabel->next;
		KLBDELETEA(pLabel->label);
		KLBDELETEA(pLabel->callback);
		KLBDELETE(pLabel);
		pLabel = nxt;
	}
	m_pSWFNode->setPlay(false);
	CKLBUtility::deleteNode(m_pSWFNode, m_flashHandle);
}

void CKLBUISWFPlayer::reachFrame(const char* label, const char* callBack) {
	LABEL * pLabel;
	for(pLabel = m_beginLabel; pLabel; pLabel = pLabel->next) {
		if(!CKLBUtility::safe_strcmp(label, pLabel->label)) {
            if(pLabel->callback) { KLBDELETEA(pLabel->callback); }
			pLabel->callback = CKLBUtility::copyString(callBack);
			return;
		}
	}
	if(!pLabel) {
		pLabel = KLBNEW(LABEL);
		if(!pLabel) {
			return;
		}
		pLabel->label = CKLBUtility::copyString(label);
		pLabel->callback = CKLBUtility::copyString(callBack);
		if(!pLabel->label || !pLabel->callback) {
			KLBDELETEA(pLabel->label);
			KLBDELETEA(pLabel->callback);
			KLBDELETE(pLabel);
			return;
		}
		pLabel->index = 0xFFFF;
		pLabel->next  = m_beginLabel;
		m_beginLabel  = pLabel;
	}
}

int
CKLBUISWFPlayer::commandUI(CLuaState& lua, int argc, int cmd)
{
	int ret = 0;
	switch(cmd)
	{
	case UI_SWF_PLAY:
		{
			setPlay(true);
		}
		break;
	case UI_SWF_STOP:
		{
			setPlay(false);
		}
		break;
	case UI_SWF_GOTOFRAME:
		{
			const char * label = lua.getString(3);
			//u16 fnum;
			gotoFrame(label);
		}
		break;
	case UI_SWF_REACHFRAME:
		{
			const char * label		= lua.getString(3);
			const char * luafunc	= lua.getString(4);

			reachFrame(label, luafunc);
		}
		break;
	case UI_SWF_GETFRAME:
		{
		}
		break;
	case UI_SWF_SETFRAMERATE:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			// fps で与える
			u16 fps = lua.getInt(3);
			setFrameRate(fps);
			lua.retBoolean(true);
			ret = 1;
		}
		break;
	case UI_SWF_SETFRAMERATE_SCALE:
		{
			if(argc != 3) {
				lua.retBoolean(false);
				ret = 1;
				break;
			}
			float scale = lua.getFloat(3);
			setFrameRateScale(scale);
			lua.retBoolean(true);
			ret = 1;
		}
		break;
	case UI_SWF_SETIMAGE:
		{
		}
		break;
	case UI_SWF_IS_ANIM:
		{
			bool result = isAnimating();
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_SWF_SETSEVOLUME:
		{
			if (argc != 3) {
				lua.retBoolean(false);
				ret = 1;
			}
			
			setVolume(lua.getFloat(3));
		}
		break;
/*
	case UI_SWF_REPLACE_ASSETS:
		{
			bool result = false;
			if(argc == 3) {
				int asset_cnt = 0;
				const char ** replace_list = replaceAssets(lua, 3, &asset_cnt);
				m_pSWFNode->replaceAsTemplate(replace_list, asset_cnt);
				removeReplaceList(replace_list, asset_cnt);
				result = true;
			}
			lua.retBool(result);
			ret = 1;
		}
		break;
*/
	}
	return ret;
}

const char **
CKLBUISWFPlayer::replaceAssets(CLuaState& lua, int pos, int * retcnt)
{
	const char ** list = KLBNEWA(const char *, REPLACE_BLOCK);
	int max     = REPLACE_BLOCK;
	int cnt     = 0;
	int cntmax  = 0;
	lua.retValue(pos);
	lua.retNil();
	while(lua.tableNext()) {
		const char * string = lua.getString(-1);

		// lua配列の indexは nextでとると順不同になる可能性があるため、
		// 実際のindex値を取得しておく
		lua.retValue(-2);
		int index = lua.getInt(-1);
		lua.pop(1);

		// 現在のバッファが index を収容しきれないようであれば、
		// 収容できるサイズまで拡張する
		cnt = index - 1;
        if(cntmax < cnt) { cntmax = cnt; }
		while(cnt >= max) {
			const char ** tmplist = KLBNEWA(const char *, max + REPLACE_BLOCK);
            for(int i = 0; i < max; i++) { tmplist[i] = list[i]; }
			KLBDELETEA(list);
			list = tmplist;
			max += REPLACE_BLOCK;
		}
		list[cnt] = CKLBUtility::copyString(string);
		lua.pop(1);
	}
	lua.pop(1);

	*retcnt = (cntmax + 1) / 2;
	return list;
}

bool
CKLBUISWFPlayer::removeReplaceList(const char ** list, int cnt)
{
    if(!list) { return true; }

	bool result = false;

    for(int i = 0; i < cnt * 2; i++) { KLBDELETEA(list[i]); }
	KLBDELETEA(list);

	return result;
}

void
CKLBUISWFPlayer::receiveMsg(CKLBObject* /*emitter*/, u32 msgID, u32 msgParam)
{
	switch(msgID)
	{
	case LABEL_REACHED:
		{
			// 既に既知のindexであれば、それで飛ぶ。
			LABEL * pLabel;
			for(pLabel = m_beginLabel; pLabel; pLabel = pLabel->next) {
				if(pLabel->index == msgParam) {
					CKLBScriptEnv::getInstance().call_eventSwf(pLabel->callback, this, pLabel->label);
					return;
				}
			}
	
			// 未知の index であれば、ラベルから検索する。

			const char * label = ((CKLBSWFAsset*)CKLBDataHandler::getPointer(m_flashHandle))->getConstantString(msgParam);
			for(pLabel = m_beginLabel; pLabel; pLabel = pLabel->next) {
				if(!CKLBUtility::safe_strcmp(pLabel->label, label)) {
					pLabel->index = msgParam;	// 次回以降indexでの検索を可能にする。
					CKLBScriptEnv::getInstance().call_eventSwf(pLabel->callback, this, pLabel->label);
					return;
				}
			}

			// 該当するものがなければ、次回からの文字列比較を不要にするため、
			// 項目を作成する。
			pLabel = KLBNEW(LABEL);
            if(!pLabel) { break; }
			pLabel->callback = NULL;
			pLabel->label = CKLBUtility::copyString(label);
            if(!pLabel->label) {
                KLBDELETEA(pLabel->label);
                KLBDELETE(pLabel);
                break;
            }
			pLabel->index = msgParam;
			pLabel->next  = m_beginLabel;
			m_beginLabel  = pLabel;
		}
		break;
	case ANIMATION_COMPLETE:
		{
			CKLBScriptEnv::getInstance().call_eventSwf(m_callBack, this, "");
		}
		break;
	default:
		break;
	}
}
