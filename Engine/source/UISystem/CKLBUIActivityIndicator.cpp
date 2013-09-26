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
//  CKLBUIActivityIndicator.cpp
//  GameEngine
//
//
//

#include "CKLBUIActivityIndicator.h"
#include "CKLBLuaEnv.h"
#include "CKLBUtility.h"
;
enum {
    UI_ACTI_ANIM_START,
    UI_ACTI_ANIM_STOP,
    UI_ACTI_IS_ANIM,
};
static IFactory::DEFCMD cmd[] = {
    { "UI_ACTI_ANIM_START", UI_ACTI_ANIM_START },
    { "UI_ACTI_ANIM_STOP",  UI_ACTI_ANIM_STOP },
    { "UI_ACTI_IS_ANIM",    UI_ACTI_IS_ANIM },

    { "ACTI_TYPE_WHITE",        IWidget::ACTI_TYPE_WHITE },
    { "ACTI_TYPE_GRAY",         IWidget::ACTI_TYPE_GRAY },
    { "ACTI_TYPE_WHITELARGE",   IWidget::ACTI_TYPE_WHITELARGE },
	{ 0, 0 }
};

static CKLBTaskFactory<CKLBUIActivityIndicator> factory("UI_ActivityIndicator", CLS_KLBUIACTIVITYINDICATOR, cmd);

// Allowed Property Keys
const char * CKLBUIActivityIndicator::ms_propItems[] = {
	"width",
	"height",
	0
};

enum PROP_ID{
	PR_WIDTH,
	PR_HEIGHT,
};
enum {
	ARG_PARENT = 1,
    
	ARG_TYPE,
    
	ARG_X,
	ARG_Y,
    
	ARG_WIDTH,
	ARG_HEIGHT,
    ARG_ID,
    
	ARG_REQUIRE = ARG_HEIGHT,
	ARG_NUMS    = ARG_ID
};


CKLBUIActivityIndicator::CKLBUIActivityIndicator() 
: CKLBUITask    ()
, m_pActivityIndicator  (NULL) 
{
}

CKLBUIActivityIndicator::~CKLBUIActivityIndicator() 
{
}

u32
CKLBUIActivityIndicator::getClassID()
{
	return CLS_KLBUIACTIVITYINDICATOR;
}

CKLBUIActivityIndicator *
CKLBUIActivityIndicator::create(CKLBUITask * pParent, CKLBNode * pNode,
                                int show_type,
                                float x, float y, float width, float height,
                                int widget_id)
{
	CKLBUIActivityIndicator * pTask = KLBNEW(CKLBUIActivityIndicator);
    if(!pTask) { return NULL; }
	if(!pTask->init(pParent, pNode, show_type, x, y, width, height, widget_id)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUIActivityIndicator::init(CKLBUITask * pParent, CKLBNode * pNode,
                      int show_type,
                      float x, float y, float width, float height,
                      int widget_id)
{
    if(!setupNode()) { return false; }
    
	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(show_type, x, y, width, height, widget_id);
    
	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}
    
	return bResult;
}

bool
CKLBUIActivityIndicator::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < ARG_REQUIRE || argc > ARG_NUMS) return false;
    
	float x         = lua.getFloat(ARG_X);
	float y         = lua.getFloat(ARG_Y);
	int show_type   = lua.getInt(ARG_TYPE);
	float width     = lua.getFloat(ARG_WIDTH);
	float height    = lua.getFloat(ARG_HEIGHT);
	int widget_id   = (argc >= ARG_ID) ? lua.getInt(ARG_ID) : 0;
    
	return initCore(show_type, x, y, width, height, widget_id);
}

bool
CKLBUIActivityIndicator::initCore(
                          int show_type,
                          float x, float y, float width, float height,
                          int widget_id)
{
	if(!setupPropertyList(ms_propItems)) {
		return false;
	}
	setInitPos(x, y);
	setNum(PR_WIDTH, width);
	setNum(PR_HEIGHT, height);

	m_ID = widget_id;
    
	m_pActivityIndicator = KLBNEWC( CKLBActivityIndicatorNode,(show_type));
    
	getNode()->addNode(m_pActivityIndicator);
	m_pActivityIndicator->setWidth(getInt(PR_WIDTH));
	m_pActivityIndicator->setHeight(getInt(PR_HEIGHT));
    
	return true;
}

void
CKLBUIActivityIndicator::execute(u32 /* deltaT */)
{
	updateUIProperty();
	if(getUpdateFlag()) {
		m_pActivityIndicator->setWidth(getInt(PR_WIDTH));
		m_pActivityIndicator->setHeight(getInt(PR_HEIGHT));
		clearUpdateFlag();
	}
}

void
CKLBUIActivityIndicator::dieUI()
{
	KLBDELETE(m_pActivityIndicator);
}

int
CKLBUIActivityIndicator::commandUI(CLuaState& lua, int argc, int cmd)
{
	int ret = 1;
	switch(cmd)
	{
        default:
		{
			lua.retBoolean(false);
			ret = 1;
		}
        case UI_ACTI_ANIM_START:
        {
            bool bResult = false;
            if(argc == 2) {
                IWidget * pActI = m_pActivityIndicator->getWidget();
                pActI->cmd(IWidget::ACT_STARTANIM);
                bResult = true;
            }
            lua.retBool(bResult);
            ret = 1;
        }
            break;
        case UI_ACTI_ANIM_STOP:
        {
            bool bResult = false;
            if(argc == 2) {
                IWidget * pActI = m_pActivityIndicator->getWidget();
                pActI->cmd(IWidget::ACT_STOPANIM);
                bResult = true;
            }
            lua.retBool(bResult);
            ret = 1;
        }
            break;
        case UI_ACTI_IS_ANIM:
        {
            bool bResult = false;
            if(argc == 2) {
                IWidget * pActI = m_pActivityIndicator->getWidget();
                bResult = pActI->status() != 0;
            }
            lua.retBool(bResult);
            ret = 1;
        }
            break;
	}
	return ret;
}
