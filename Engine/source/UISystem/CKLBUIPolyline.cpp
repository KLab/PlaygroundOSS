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
#include "CKLBUIPolyline.h"

enum {
	UI_POLYLINE_SET_POINTCOUNT,
	UI_POLYLINE_SET_POINT,
	UI_POLYLINE_SET_COLOR
};

static IFactory::DEFCMD cmd[] = {
	{"UI_POLYLINE_SET_POINTCOUNT",		UI_POLYLINE_SET_POINTCOUNT  },
	{"UI_POLYLINE_SET_POINT",			UI_POLYLINE_SET_POINT       },
	{"UI_POLYLINE_SET_COLOR",			UI_POLYLINE_SET_COLOR       },

	{0, 0 }
};

static CKLBTaskFactory<CKLBUIPolyline> factory("UI_Polyline", CLS_KLBUIPOLYLINE, cmd);

// Allowed Property Keys
CKLBLuaPropTask::PROP_V2 CKLBUIPolyline::ms_propItems[] = {
	UI_BASE_PROP,
	{	"order",			R_UINTEGER,	NULL,									(getBoolT)&CKLBUIPolyline::getOrder,	0	},
	{	"maxpointcount",	UINTEGER,	(setBoolT)&CKLBUIPolyline::setMaxPoint,	(getBoolT)&CKLBUIPolyline::getMaxPoint,	0	}
};

// 引数のインデックス定義
enum {
	ARG_PARENT = 1,
	ARG_ORDER,

	ARG_MAXPOINTCNT,
	
	ARG_NUMS    = ARG_MAXPOINTCNT,
	ARG_REQUIRE = ARG_MAXPOINTCNT	// 最低限必要なパラメータ数
};

CKLBUIPolyline::CKLBUIPolyline()
: CKLBUITask	()
, m_pPolyline	(NULL) 
{
	setNotAlwaysActive();
	m_newScriptModel = true;
}

CKLBUIPolyline::~CKLBUIPolyline() 
{
}

u32
CKLBUIPolyline::getClassID()
{
	return CLS_KLBUIPOLYLINE;
}

CKLBUIPolyline* 
CKLBUIPolyline::create(CKLBUITask* pParent, CKLBNode* pNode, u32 order, u32 maxPoint) 
{
	CKLBUIPolyline* pTask = KLBNEW(CKLBUIPolyline);
    if (!pTask) { return NULL; }
	if (!pTask->init(pParent, pNode, order, maxPoint)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool CKLBUIPolyline::init(CKLBUITask* pParent, CKLBNode* pNode, u32 order, u32 maxPoint) {
    if(!setupNode()) { return false; }
	bool bResult = initCore(order, maxPoint);
	bResult = registUI(pParent, bResult);
	if(pNode) {
		pParent->getNode()->removeNode(getNode());
		pNode->addNode(getNode());
	}
	return bResult;
}

bool 
CKLBUIPolyline::initCore(u32 order, u32 maxPoint)
{
	if(!setupPropertyList((const char**)ms_propItems,SizeOfArray(ms_propItems))) {
		return false;
	}

	m_maxpointcount = maxPoint;
	m_order         = order;

	// 必要とされるオブジェクトを生成する
	CKLBRenderingManager& pRdrMgr = CKLBRenderingManager::getInstance();

	m_pPolyline = pRdrMgr.allocateCommandPolyline(m_maxpointcount, order);
	if(!m_pPolyline) {
		return false;
	}

	// 二つのDynSpriteを自分のNodeに登録
	getNode()->setRender(m_pPolyline);
	getNode()->setRenderOnDestroy(true);

	getNode()->markUpMatrix();
	
	return true;
}

bool
CKLBUIPolyline::initUI(CLuaState& lua)
{
	int argc = lua.numArgs();
    if(argc > ARG_NUMS || argc < ARG_REQUIRE) { return false; }

	u32 order = lua.getInt(ARG_ORDER);
	u32 maxpoint = lua.getInt(ARG_MAXPOINTCNT);
	return initCore(order,maxpoint);
}

int
CKLBUIPolyline::commandUI(CLuaState& lua, int argc, int cmd)
{
	int ret = 0;
	switch(cmd)
	{
	case UI_POLYLINE_SET_POINTCOUNT:
		{
			bool result = false;
			if(argc == 3) {
				int ptsCount = lua.getInt(3);
				setPointCount(ptsCount);
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_POLYLINE_SET_POINT:
		{
			bool result = false;
			if(argc == 5) {
				int idx = lua.getInt(3);
				float x = lua.getFloat(4);
				float y = lua.getFloat(5);
				setPoint(idx,x,y);
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_POLYLINE_SET_COLOR:
		{
			bool result = false;
			if(argc == 4) {
				u32 alpha = lua.getInt(3);
				u32 rgb = lua.getInt(4);

				u32 color = (alpha << 24) | (rgb & 0xffffff);

				setColor(color);
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;

		}
		break;
	}
	return ret;
}

void
CKLBUIPolyline::execute(u32 /*deltaT*/)
{
	// Should never be executed.
	klb_assertAlways("Task execution is not necessary");
}

void
CKLBUIPolyline::dieUI()
{
}
