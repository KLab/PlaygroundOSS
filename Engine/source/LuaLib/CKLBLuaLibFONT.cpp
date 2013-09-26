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
#include "CKLBLuaLibFONT.h"
#include "CPFInterface.h"
#include "CLuaState.h"
#include "CKLBLabelNode.h"
;
static ILuaFuncLib::DEFCONST luaConst[] = {
//	{ "DBG_M_SWITCH",	DBG_MENU::M_SWITCH },
	{ 0, 0 }
};

CKLBLuaLibFONT::FONTOBJ	*	CKLBLuaLibFONT::ms_begin	= 0;
CKLBLuaLibFONT::FONTOBJ	*	CKLBLuaLibFONT::ms_end		= 0;


static CKLBLuaLibFONT libdef(luaConst);

CKLBLibRegistrator::LIBREGISTSTRUCT* CKLBLuaLibFONT::ms_libRegStruct = CKLBLibRegistrator::getInstance()->add("LibFont", CLS_KLBFONTOBJ);

u32
CKLBLuaLibFONT::FONTOBJ::getClassID()
{
	return CLS_KLBFONTOBJ;
}

CKLBLuaLibFONT::CKLBLuaLibFONT(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibFONT::~CKLBLuaLibFONT() 
{
	remove_all_font();
}

// 残りのFONTOBJをすべて破棄
void
CKLBLuaLibFONT::destroyResources()
{
	remove_all_font();
}

// 現在存在するフォントオブジェクトのダンプ
bool
CKLBLuaLibFONT::dumpObjects(IPlatformRequest& pForm)
{
	pForm.logging("[LuaLibFONT]");

	FONTOBJ * fontobj = ms_begin;
	bool bResult = false;
	while(fontobj) {
		pForm.logging("[FONT]<%p>: size=%d", fontobj, fontobj->size);
		fontobj = fontobj->next;
		bResult = true;
	}
	return bResult;
}

// Lua関数の追加
void
CKLBLuaLibFONT::addLibrary()
{
	addFunction("FONT_load", CKLBLuaLibFONT::luaFontLoad);
	addFunction("FONT_create", CKLBLuaLibFONT::luaFontCreate);
	addFunction("FONT_release", CKLBLuaLibFONT::luaFontRelease);
	addFunction("FONT_getTextInfo", CKLBLuaLibFONT::luaGetTextInfo);
	addFunction("FONT_setDefaultFont", CKLBLuaLibFONT::luaSetDefaultLabelFont);
}
CKLBLuaLibFONT::FONTOBJ *
CKLBLuaLibFONT::create_font(int size, const char * fontname)
{
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	void * font = pForm.getFont(size, fontname);
	FONTOBJ * fontobj = (!font) ? NULL : KLBNEW(FONTOBJ);
	if(fontobj) {
		fontobj->font = font;
		fontobj->size = size;
		fontobj->prev = ms_end;
		fontobj->next = NULL;
		if(fontobj->prev) {
			fontobj->prev->next = fontobj;
		} else {
			ms_begin = fontobj;
		}
		ms_end = fontobj;
	}
	return fontobj;
}

void
CKLBLuaLibFONT::remove_font(FONTOBJ * fontobj)
{
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();
	pForm.deleteFont(fontobj->font);
	if(fontobj->prev) {
		fontobj->prev->next = fontobj->next;
	} else {
		ms_begin = fontobj->next;
	}
	if(fontobj->next) {
		fontobj->next->prev = fontobj->prev;
	} else {
		ms_end = fontobj->prev;
	}
	KLBDELETE(fontobj);
}

int
CKLBLuaLibFONT::remove_all_font()
{
	FONTOBJ * fontobj = ms_begin;
	int cnt = 0;
	while(fontobj) {
		FONTOBJ * next = fontobj->next;
		remove_font(fontobj);
		fontobj = next;
		cnt++;
	}
	return cnt;
}

int
CKLBLuaLibFONT::luaFontCreate(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 2) {
		lua.retBoolean(false);
		return 1;
	}
	
	int size = lua.getInt(1);
	const char * fontname = lua.getString(2);
	FONTOBJ * fontobj = create_font(size, fontname);

	lua.retPointer(fontobj);
	return 1;
}

int
CKLBLuaLibFONT::luaFontRelease(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	for(int i = 1; i <= argc; i++) {
		FONTOBJ * fontobj = (FONTOBJ *)lua.getPointer(i);
		remove_font(fontobj);
		lua.retNil();
	}
	return argc;
}


int CKLBLuaLibFONT::luaFontLoad(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	bool res = false;
	if (argc == 2) {
		const char* fontName = lua.getString(1);
		const char* fontFile = lua.getString(2);
		CPFInterface& pfif = CPFInterface::getInstance();
		
		res = pfif.platform().registerFont(fontName,fontFile,true);
	}

	lua.retBool(res);
	return 1;
}

int
CKLBLuaLibFONT::luaGetTextInfo(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 2) {
		lua.retNil();
		return 1;
	}
	IPlatformRequest& pForm = CPFInterface::getInstance().platform();

	FONTOBJ * fontobj = (FONTOBJ *)lua.getPointer(1);
	void * font = fontobj->font;
	const char * string = lua.getString(2);
	STextInfo info;
	pForm.getTextInfo(string, font, &info);

	lua.tableNew();

	lua.retString("width");
	lua.retDouble(info.width);
	lua.tableSet();

	lua.retString("height");
	lua.retDouble(info.height);
	lua.tableSet();

	lua.retString("ascent");
	lua.retDouble(info.ascent);
	lua.tableSet();

	lua.retString("descent");
	lua.retDouble(info.descent);
	lua.tableSet();

	lua.retString("top");
	lua.retDouble(info.top);
	lua.tableSet();

	lua.retString("bottom");
	lua.retDouble(info.bottom);
	lua.tableSet();

	return 1;
}

int
CKLBLuaLibFONT::luaSetDefaultLabelFont(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retBool(false);
		return 1;
	}
	const char * fontname = (lua.isNil(1)) ? NULL : lua.getString(1);
	bool bResult = CKLBLabelNode::setDefaultFont(fontname);
	lua.retBool(bResult);
	return 1;
}
