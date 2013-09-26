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
#include "CKLBLuaLibUI.h"
#include "CKLBUITask.h"
#include "CKLBSplineNode.h"

enum {
	UIPOS_LEFT	   = 0x00000001,
	UIPOS_RIGHT    = 0x00000002,
	UIPOS_H_CENTER = (UIPOS_LEFT | UIPOS_RIGHT),

	UIPOS_TOP      = 0x00000004,
	UIPOS_BOTTOM   = 0x00000008,
	UIPOS_V_CENTER = (UIPOS_TOP | UIPOS_BOTTOM),

};
static ILuaFuncLib::DEFCONST defcmd[] = {
	{ "UI_GENERIC_NODE_RECONNECT",	CKLBUITask::UI_GENERIC_NODE_RECONNECT },
	{ "UI_GENERIC_SET_NAME",		CKLBUITask::UI_GENERIC_SET_NAME },
	{ "UI_GENERIC_ANIM_SET_SPLINE",	CKLBUITask::UI_GENERIC_ANIM_SET_SPLINE },
	{ "UI_GENERIC_ANIM_PLAY",		CKLBUITask::UI_GENERIC_ANIM_PLAY },
	{ "UI_GENERIC_ANIM_STOP",		CKLBUITask::UI_GENERIC_ANIM_STOP },
	{ "UI_GENERIC_IS_ANIM",			CKLBUITask::UI_GENERIC_IS_ANIM },

	{ "UI_GENERIC_SET_COLOR",		CKLBUITask::UI_GENERIC_SET_COLOR },
	{ "UI_GENERIC_SET_SCALE",		CKLBUITask::UI_GENERIC_SET_SCALE },
	{ "UI_GENERIC_SET_ROT",			CKLBUITask::UI_GENERIC_SET_ROT },
	{ "UI_GENERIC_SET_VISIBLE",		CKLBUITask::UI_GENERIC_SET_VISIBLE },

	{ "SPL_VALUE_INT",		CKLBUITask::SPL_VALUE_INT },
	{ "SPL_VALUE_NUM",		CKLBUITask::SPL_VALUE_NUM },

	{ "UIPOS_LEFT",		UIPOS_LEFT },
	{ "UIPOS_RIGHT",	UIPOS_RIGHT },
	{ "UIPOS_TOP",		UIPOS_TOP },
	{ "UIPOS_BOTTOM",	UIPOS_BOTTOM },

	{ "UIPOS_H_CENTER",	UIPOS_H_CENTER },
	{ "UIPOS_V_CENTER",	UIPOS_V_CENTER },

	{ "SPL_MODIFY_X",		CKLBSplineNode::MODIFY_X },
	{ "SPL_MODIFY_Y",		CKLBSplineNode::MODIFY_Y },
	{ "SPL_MODIFY_SCALE",	CKLBSplineNode::MODIFY_SCALE },
	{ "SPL_MODIFY_R",		CKLBSplineNode::MODIFY_R },
	{ "SPL_MODIFY_G",		CKLBSplineNode::MODIFY_G },
	{ "SPL_MODIFY_B",		CKLBSplineNode::MODIFY_B },
	{ "SPL_MODIFY_A",		CKLBSplineNode::MODIFY_A },
	{ "SPL_MODIFY_ROT",		CKLBSplineNode::MODIFY_ROT },

	{ 0, 0 }
};

static CKLBLuaLibUI libdef(defcmd);

CKLBLuaLibUI::CKLBLuaLibUI(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibUI::~CKLBLuaLibUI() {}

void CKLBLuaLibUI::addLibrary()
{
	addFunction("UIF_Position", CKLBLuaLibUI::luaCalcPosition);
}

int
CKLBLuaLibUI::luaCalcPosition(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 5) {
		lua.retNil();
		lua.retNil();
		return 2;
	}
	float x = lua.getDouble(1);
	float y = lua.getDouble(2);
	float w = lua.getDouble(3);
	float h = lua.getDouble(4);
	int mask = lua.getInt(5);

	float rx, ry;
	calcPosition(x,y,w,h,mask,&rx,&ry);

	lua.retDouble(rx);
	lua.retDouble(ry);
	return 2;
}

void CKLBLuaLibUI::calcPosition(float x, float y, float w, float h, int mask, float* out_rx, float* out_ry)
{
	switch(mask & UIPOS_H_CENTER)
	{
	default:
	case UIPOS_LEFT:		*out_rx = x;			break;	
	case UIPOS_RIGHT:		*out_rx = x + w;		break;
	case UIPOS_H_CENTER:	*out_rx = x + w/2;		break;
	}

	switch(mask & UIPOS_V_CENTER)
	{
	default:
	case UIPOS_TOP:			*out_ry = y;			break;
	case UIPOS_BOTTOM:		*out_ry = y + h;		break;
	case UIPOS_V_CENTER:	*out_ry = y + h/2;		break;
	}
}
