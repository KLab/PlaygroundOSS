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
#include "CKLBAppProperty.h"
#include "CPFInterface.h"

static IFactory::DEFCMD cmd[] = {
	// プロパティインデックス値
	{ "APP_SCRN_TYPE", (int)CKLBAppProperty::SCRN_TYPE },	// 画面の使い方

	// プロパティに与える値: APP_SCRN_TYPE 用
	{ "LANDSCAPE",	IClientRequest::LANDSCAPE },
	{ "PORTRAIT",	IClientRequest::PORTRAIT },

	{0, 0}
};

static CKLBAppScriptIF factory("APP_Property", CLS_KLBAPPPROP, cmd);


CKLBAppProperty::CKLBAppProperty()
{
	for(int i = 0; i < PIDX_MAX; i++) { 
        m_value[i] = -1;
    }
}

CKLBAppProperty::~CKLBAppProperty() {}

CKLBAppProperty&
CKLBAppProperty::getInstance()
{
	static CKLBAppProperty instance;
	return instance;
}

int
CKLBAppProperty::getValue(PIDX idx)
{
	return m_value[ idx ];
}

bool
CKLBAppProperty::setValue(PIDX idx, int value)
{
	if(idx < 0 || idx >= PIDX_MAX) return false;
	m_value[idx] = value;
	return true;
}


CKLBAppScriptIF::CKLBAppScriptIF(const char * funcname, u32 classID, DEFCMD * arrCmdItem)
{
	addLink(funcname, setValue, arrCmdItem, classID);
}

CKLBAppScriptIF::~CKLBAppScriptIF() {}

int
CKLBAppScriptIF::setValue(lua_State * L)
{
	CKLBAppProperty::PIDX pidx = (CKLBAppProperty::PIDX)lua_tointeger(L, 1);
	int value = lua_tointeger(L, 2);

	int result = CKLBAppProperty::getInstance().setValue(pidx, value);

	lua_pushboolean(L, result);
	return 1;
}
