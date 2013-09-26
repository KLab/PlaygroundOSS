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
#include "CKLBUIGroup.h"
#include "CKLBLuaEnv.h"

// Command Values
enum {
	UI_GROUP_ANIM_CALLBACK = 0,
	UI_GROUP_ANIMATION,
	UI_GROUP_GET_ANIM_NODE,
	UI_GROUP_SKIP_ANIM,
	UI_GROUP_IS_ANIM,
};
static IFactory::DEFCMD cmd[] = {
	{ "UI_GROUP_ANIM_CALLBACK", UI_GROUP_ANIM_CALLBACK },
	{ "UI_GROUP_ANIMATION",		UI_GROUP_ANIMATION },
// 	{ "UI_GROUP_GET_ANIM_NODE",	UI_GROUP_GET_ANIM_NODE },

	{ "UI_GROUP_IS_ANIM",		UI_GROUP_IS_ANIM },
	{ "UI_GROUP_SKIP_ANIM",		UI_GROUP_SKIP_ANIM },

	{0, 0}
};

static CKLBTaskFactory<CKLBUIGroup> factory("UI_Group", CLS_KLBUIGROUP, cmd);

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUIGroup::ms_propItems[] = {
	UI_BASE_PROP
//	"order"
};

enum {
	ARG_PARENT = 1,

	ARG_ORDER,	// TODO :Useless property
	ARG_X,
	ARG_Y,

	ARG_REQUIRE = ARG_Y,
	ARG_NUMS    = ARG_Y
};

CKLBUIGroup::CKLBUIGroup()
: CKLBUITask() 
{
	m_newScriptModel = true;
}

CKLBUIGroup::~CKLBUIGroup() 
{
}

u32
CKLBUIGroup::getClassID()
{
	return CLS_KLBUIGROUP;
}

CKLBUIGroup*
CKLBUIGroup::create(CKLBUITask* pParent, CKLBNode* pNode, float x, float y) {
	CKLBUIGroup* pTask = KLBNEW(CKLBUIGroup);
    if(!pTask) { return NULL; }
	if(!pTask->init(pParent, pNode, x, y)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBUIGroup::init(CKLBUITask* pParent, CKLBNode* pNode, float x, float y) {
	if(!setupNode()) return false;

	// ユーザ定義初期化を呼び、初期化に失敗したら終了。
	bool bResult = initCore(x, y);

	// 初期化処理終了後の登録。失敗時の処理も適切に行う。
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}
	return bResult;
}

bool
CKLBUIGroup::initCore(float x, float y)
{
	if (!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	setInitPos(x, y);
	return true;
}

bool
CKLBUIGroup::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < ARG_REQUIRE || argc > ARG_NUMS) return false;

	float x = lua.getFloat(ARG_X);
	float y = lua.getFloat(ARG_Y);

	// getNode()->setTranslate(getNum(PR_X), getNum(PR_Y));
	return initCore(x,y);
}

void
CKLBUIGroup::execute(u32 /*deltaT*/)
{
	// TODO OPTIMIZE : possible to sleep task if no anim.
	// アニメーションの終了を監視する
	m_animpack.watchFinishedAnim(this);
}

void
CKLBUIGroup::dieUI()
{
	// 破棄と同時に m_animpack も破棄されるため、特にここで何かを行う必要はない。
}

int
CKLBUIGroup::commandUI(CLuaState& lua, int argc, int cmd)
{
	int ret = 1;

	switch(cmd)
	{
	default:
		{
			lua.retBoolean(ret?true:false);
			ret = 1;
		}
		break;
	case UI_GROUP_ANIM_CALLBACK:
		{
			bool result = false;
			if(argc == 3) {
				const char * callback = (lua.isNil(3)) ? NULL : lua.getString(3);
				result = setAnimCallback(callback);
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_GROUP_ANIMATION:
		{
			bool result = false;
			if(argc >= 3 && argc <= 4) {
				const char * animname = lua.getString(3);
				bool blend = (argc >= 4) ? lua.getBool(4) : false;
				result = setAnimation(animname, blend);
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_GROUP_IS_ANIM:
		{
			bool result = false;
			if(argc >= 2 && argc <= 3) {
				const char * name = NULL;
				if(argc >= 3 && !lua.isNil(3)) name = lua.getString(3);
				result = isAnim(name);
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_GROUP_SKIP_ANIM:
		{
			bool result = false;
			if(argc >= 2 || argc <= 3) {
				const char * name = NULL;
				if(argc >= 3 && !lua.isNil(3)) name = lua.getString(3);
				result = skipAnim(name);
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	}
	return ret;
}
