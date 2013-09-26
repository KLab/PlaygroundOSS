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
#include "CKLBLuaPropTask.h"
#include "CKLBLuaEnv.h"
#include "CKLBScriptEnv.h"
#include "CKLBUtility.h"

CKLBLuaPropTask::CKLBLuaPropTask()
: CKLBLuaTask   ()
, m_cntProp     (0)
, m_arrProp     (NULL)
, m_bUpdateByScript (false)
, m_newScriptModel  (false) 
{
}

CKLBLuaPropTask::~CKLBLuaPropTask()
{
	// 必ず破棄時にプロパティ領域を破棄する。
	if(m_arrProp) {
		for(int i = 0; i < m_cntProp; i++) {
			KLBDELETEA(m_arrProp[i].name);
            if(m_arrProp[i].type == STRING) { KLBDELETEA (m_arrProp[i].value.s); }
		}
	}
	KLBDELETEA(m_arrProp);
}

CKLBTask::TASKTYPE
CKLBLuaPropTask::getTaskType()
{
    return TASK_LUA_PROPERTY;
}

u32
CKLBLuaPropTask::getClassID()
{
    return CLS_KLBLUAPROPTASK;
}

bool
CKLBLuaPropTask::setupPropertyList(const char * name[], u32 length)
{
	if (m_newScriptModel) {
		m_arrPropV2		= (PROP_V2*)name;
		m_cntProp		= length;
		return true;
	} else {
		// 要素の数を数える
		int cnt = 0;
        while(name[cnt]) { cnt++; }

		PROP * arr = KLBNEWA( PROP, cnt );
        if(!arr) { return false; }

		for(int i = 0; i < cnt; i++) {
			arr[i].name = CKLBUtility::copyString(name[i]);
			arr[i].type = INTEGER;
			arr[i].value.i = 0;
		}
		for(int i = 0; i < m_cntProp; i++) {
			KLBDELETEA(m_arrProp[i].name);
		}
		KLBDELETEA(m_arrProp);
		m_cntProp = cnt;
		m_arrProp = arr;
		return true;
	}
}

bool
CKLBLuaPropTask::addPropertyList(const char * name[])
{
	int cnt = 0;
	while(name[cnt]) cnt++;

	// 追加分のポインタバッファを作る
	PROP * arr = KLBNEWA(PROP, cnt + m_cntProp);
    if(!arr) { return false; }
	for(int i = 0; i < m_cntProp; i++) {
		arr[i] = m_arrProp[i];	// 既存プロパティをコピー
	}
	for(int i = 0; i < cnt; i++) {
		arr[i + m_cntProp].name = CKLBUtility::copyString(name[i]);
		arr[i + m_cntProp].type = INTEGER;
		arr[i + m_cntProp].value.i = 0;
	}
	KLBDELETEA(m_arrProp);
	m_cntProp += cnt;
	m_arrProp = arr;
	return true;
}

int
CKLBLuaPropTask::findProperty(const char * name)
{
	if (m_newScriptModel) {
		for(int i = 0; i < m_cntProp; i++) {
            if(!strcmp(name, m_arrPropV2[i].name)) { return i; }
		}
	} else {
		for(int i = 0; i < m_cntProp; i++) {
            if(!strcmp(name, m_arrProp[i].name)) { return i; }
		}
	}
	return -1;
}

void
CKLBLuaPropTask::preGetProp() {}

// C -> lua (lua から見て "get")
int
CKLBLuaPropTask::getPropertyByScript(lua_State * L)
{
    // 前処理があれば実行する
    preGetProp();
    
	// luaから配列として取得できるよう戻り値を作る。
	lua_newtable(L);

	if (m_newScriptModel) {
		for(int i = 0; i < m_cntProp; i++) {
			PROP_V2* prop = &m_arrPropV2[i];
			lua_pushstring(L, prop->name);
			switch(prop->type)
			{
			case NIL:		lua_pushnil(L); break;
			case R_BOOLEANT:
			case BOOLEANT:	
				{
					bool v;
					if (prop->getter.b) {
						getBoolT fct = prop->getter.b;
						v = (*this.*fct)();
					} else {
						memcpy(&v,&(((u8*)this)[prop->offset]),sizeof(bool));
					}
					lua_pushboolean(L, v ? 1 : 0); 
				}
				break;
			case R_INTEGER:
			case INTEGER:	
				{
					s32 i;
					if (prop->getter.i) {
						getIntT fct = prop->getter.i;
						i = (*this.*fct)();
					} else {
						memcpy(&i,&(((u8*)this)[prop->offset]),sizeof(s32));
					}
					lua_pushinteger(L, i); 
				}
				break;
			case R_NUMERIC:
			case NUMERIC:
				{
					float f;
					if (prop->getter.f) {
						getFloatT fct = prop->getter.f;
						f = (*this.*fct)();
					} else {
						memcpy(&f,&(((u8*)this)[prop->offset]),sizeof(float));
					}
					lua_pushnumber(L, f);
				}
				break;
			case R_STRING:
			case STRING:
				{
					const char* s;
					if (prop->getter.s) {
						getStrT fct = prop->getter.s;
						s = (*this.*fct)();
					} else {
						memcpy(&s,&(((u8*)this)[prop->offset]),sizeof(const char*));
					}
					lua_pushstring(L, s);
				}
				break;
			case R_POINTER:
			case POINTER:   
				{
					void* p;
					if (prop->getter.p) {
						getPtrT fct = prop->getter.p;
						p = (*this.*fct)();
					} else {
						memcpy(&p,&(((u8*)this)[prop->offset]),sizeof(void*));
					}
					lua_pushlightuserdata(L, p);
				}
				break;
			case DYNAMIC_INT:
				{
					s32 i;
					if (prop->getter.g) {
						getGenIntT fct = prop->getter.g;
						i = (*this.*fct)(prop->offset);
					} else {
						klb_assertAlways("Dynamic type always work with getter/setter");
						i = 0; // Compiler Warning
					}
					lua_pushinteger(L, i); 
				}
				break;
			default:
				klb_assertAlways("Unknown property type");
				break;
			}
			lua_settable(L, -3);
		}
	} else {
		for(int i = 0; i < m_cntProp; i++) {
			lua_pushstring(L, m_arrProp[i].name);
			switch(m_arrProp[i].type)
			{
			case NIL:		lua_pushnil(L);                                         break;
			case BOOLEANT:	lua_pushboolean (L, (m_arrProp[i].value.b) ? 1 : 0);    break;
			case INTEGER:	lua_pushinteger (L, m_arrProp[i].value.i);              break;
			case NUMERIC:	lua_pushnumber  (L, m_arrProp[i].value.n);              break;
			case STRING:	lua_pushstring  (L, m_arrProp[i].value.s);              break;
			case POINTER:   lua_pushlightuserdata(L, m_arrProp[i].value.p);         break;
            
            case DYNAMIC_INT:   /* not handled */ break;
            case TYPE_MASK:     /* not handled */ break;
            case READ_ONLY:     /* not handled */ break;
            case R_BOOLEANT:    /* not handled */ break;
            case R_INTEGER:     /* not handled */ break;
            case R_NUMERIC:     /* not handled */ break;
            case R_STRING:      /* not handled */ break;
            case R_POINTER:     /* not handled */ break;
			}
			lua_settable(L, -3);
		}
	}
	return 1;
}

void
CKLBLuaPropTask::afterSetProp() 
{
}

// lua -> C (lua から見て "set")
int
CKLBLuaPropTask::setPropertyByScript(lua_State * L)
{
	if(lua_gettop(L) != 2) {	
		lua_pushboolean(L, 0);
		return 1;
	}

	if (m_newScriptModel) {
		for(int i = 0; i < m_cntProp; i++) {
            m_arrPropV2[i].checked = false;
        }

		lua_pushvalue(L, 2);
		lua_pushnil(L);
		while(0 != lua_next(L, -2)) {
			lua_pushvalue(L, -2);
			const char *    key     = lua_tostring(L, -1);	// key
			PROP_V2 *       prop    = NULL;

			// keyから対応する領域を検索
			for(int i = 0; i < m_cntProp; i++) {
                if(m_arrPropV2[i].checked) { continue; }
				if(!strcmp(m_arrPropV2[i].name, key)) {
					prop = &m_arrPropV2[i];
					prop->checked = true;
					break;
				}
			}
			// Lua配列の key の値が、プロパティとして定義されている key の中に無い値だったとき
			if(!prop) {
				CKLBScriptEnv::getInstance().error("unknown property \"%s\"", key);
			}

			switch (prop->type) {
			case NIL:
				klb_assertAlways("Should not be a property type");
				break;
			case BOOLEANT:
				{
					bool v = lua_toboolean(L,-2) ? true : false;
					klb_assert(prop->setter.b != NULL, "Must have setter !");
					setBoolT fct = prop->setter.b;
					(*this.*fct)(v);
				}
				break;
			case INTEGER:
				{
					s32 i = lua_tointeger(L, -2);
					klb_assert(prop->setter.i != NULL, "Must have setter !");
					setIntT fct = prop->setter.i;
					(*this.*fct)(i);
				}
				break;
			case NUMERIC:
				{
					float f = (float)lua_tonumber(L, -2);
					klb_assert(prop->setter.f != NULL, "Must have setter !");
					setFloatT fct = prop->setter.f;
					(*this.*fct)(f);
				}
				break;
			case STRING:
				{
					const char* str = lua_tostring(L, -2);
					klb_assert(prop->setter.s != NULL, "Must have setter !");
					setStrT fct = prop->setter.s;
					(*this.*fct)(str);
				}
				break;
			case POINTER:
				{
					void* ptr = (void *)lua_touserdata(L, -2);
					klb_assert(prop->setter.s != NULL, "Must have setter !");
					setPtrT fct = prop->setter.p;
					(*this.*fct)(ptr);
				}
				break;
			case DYNAMIC_INT:
				{
					s32 i = lua_tointeger(L, -2);
					setGenIntT fct = prop->setter.g;
					(*this.*fct)((u32)prop->offset ,i);
				}
				break;
			case R_INTEGER:
			// Same value case R_UINTEGER:
			case R_STRING:
			case R_BOOLEANT:
			case R_NUMERIC:
			case R_POINTER:
				{
					// klb_assertAlways("Read only property %s", prop->name);
				}
				break;
			default:
				klb_assertAlways("Unknown property type");
				break;
			}
			lua_pop(L, 2);
		}
	} else {
        for(int i = 0; i < m_cntProp; i++) { m_arrProp[i].checked = false; }

		lua_pushvalue(L, 2);
		lua_pushnil(L);
		while(0 != lua_next(L, -2)) {
			lua_pushvalue(L, -2);
			const char *    key     = lua_tostring(L, -1);	// key
			PROP *          prop    = NULL;

			// keyから対応する領域を検索
			for(int i = 0; i < m_cntProp; i++) {
				if(m_arrProp[i].checked) continue;
				if(!strcmp(m_arrProp[i].name, key)) {
					prop = &m_arrProp[i];
					prop->checked = true;
					break;
				}
			}
			// Lua配列の key の値が、プロパティとして定義されている key の中に無い値だったとき
			if(!prop) {
				CKLBScriptEnv::getInstance().error("unknown property \"%s\"", key);
			}
			switch(lua_type(L, -2))
			{
			case LUA_TNIL:
				prop->type = NIL;
				break;
			case LUA_TNUMBER:
				{
					int val_i = lua_tointeger(L, -2);
					float val_f = (float)lua_tonumber(L, -2);
					if((float)val_i == val_f) {
						prop->type = INTEGER;
						prop->value.i = val_i;
					} else {
						prop->type = NUMERIC;
						prop->value.n = val_f;
					}
				}
				break;
			case LUA_TBOOLEAN:
				prop->type = BOOLEANT;
				prop->value.b = (0 != lua_toboolean(L, -2));
				break;
			case LUA_TSTRING: 
				{
					const char * str = lua_tostring(L, -2);
					prop->type = STRING;
					if( prop->value.s ) KLBDELETEA( prop->value.s );	// 2012.11.29  リークの可能性があったので修正
					prop->value.s = (char *)CKLBUtility::copyString(str);
					if(!prop->value.s) prop->type = NIL;
				}
				break;
			case LUA_TLIGHTUSERDATA:
				prop->type = POINTER;
				prop->value.p = (void *)lua_touserdata(L, -2);
				break;
			}

			lua_pop(L, 2);
		}
	}

	lua_pop(L, 1);

	// スクリプトから更新されたので、フラグをセットする
	m_bUpdateByScript = true;
    
    // 後処理があれば実行する
    afterSetProp();

	// lua に対する戻り値は無し。
	return 0;
}

void
CKLBLuaPropTask::setNil(int idx)
{
	klb_assert(!m_newScriptModel, "Old Scripting model only");
    if(m_arrProp[idx].type == STRING) { KLBDELETEA(m_arrProp[idx].value.s); }
	m_arrProp[idx].type     = NIL;
	m_arrProp[idx].value.p  = NULL;
}

void
CKLBLuaPropTask::setBool(int idx, bool val)
{
	klb_assert(!m_newScriptModel, "Old Scripting model only");
    if(m_arrProp[idx].type == STRING) { KLBDELETEA(m_arrProp[idx].value.s); }
	m_arrProp[idx].type     = BOOLEANT;
	m_arrProp[idx].value.b  = val;
}

void
CKLBLuaPropTask::setInt(int idx, int val)
{
	klb_assert(!m_newScriptModel, "Old Scripting model only");
    if(m_arrProp[idx].type == STRING) { KLBDELETEA(m_arrProp[idx].value.s); }
	m_arrProp[idx].type     = INTEGER;
	m_arrProp[idx].value.i  = val;
}

void
CKLBLuaPropTask::setNum(int idx, float val)
{
	klb_assert(!m_newScriptModel, "Old Scripting model only");
    if(m_arrProp[idx].type == STRING) { KLBDELETEA(m_arrProp[idx].value.s); }
	m_arrProp[idx].type     = NUMERIC;
	m_arrProp[idx].value.n  = val;
} 

bool
CKLBLuaPropTask::setStr(int idx, const char * val)
{
	klb_assert(!m_newScriptModel, "Old Scripting model only");

	const char * str = (val) ? CKLBUtility::copyString(val) : NULL;
	if(val && !str) return false;
    if(m_arrProp[idx].type == STRING) { KLBDELETEA(m_arrProp[idx].value.s); }
	m_arrProp[idx].type     = STRING;
	m_arrProp[idx].value.s  = (char *)str;
	return true;
}

bool
CKLBLuaPropTask::setMem(int idx, const char * val, u32 size )
{
	const char * str = (val) ? CKLBUtility::copyMem(val,size) : NULL;
	if(val && !str) return false;
    if(m_arrProp[idx].type == STRING) { KLBDELETEA(m_arrProp[idx].value.s); }
	m_arrProp[idx].type     = STRING;
	m_arrProp[idx].value.s  = (char *)str;
	return true;
}