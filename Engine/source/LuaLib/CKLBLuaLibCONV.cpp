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
#include "CKLBLuaLibCONV.h"
#include "CKLBUtility.h"

static CKLBLuaLibCONV libdef(0);

CKLBLuaLibCONV::CKLBLuaLibCONV(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibCONV::~CKLBLuaLibCONV() {}

// Lua関数の追加
void
CKLBLuaLibCONV::addLibrary()
{
	addFunction("CONV_Lua2Json",     CKLBLuaLibCONV::lua2json);
	addFunction("CONV_Json2Lua",     CKLBLuaLibCONV::json2lua);
	addFunction("CONV_JsonFile2Lua", CKLBLuaLibCONV::jsonfile2lua);
}


int
CKLBLuaLibCONV::lua2json(lua_State * L)
{
	CLuaState lua(L);

	lua.retValue(1);
	u32 size; // Ignored here.
	const char * json = CKLBUtility::lua2json(lua,size);
	lua.pop(1);
	lua.retString(json);
	KLBDELETEA(json);
	return 1;
}

int
CKLBLuaLibCONV::json2lua(lua_State * L)
{
	CLuaState lua(L);
	const char * json = lua.getString(1);
	CKLBUtility::json2lua(lua, json, strlen(json));
	return 1;
}

int
CKLBLuaLibCONV::jsonfile2lua(lua_State * L)
{
	CLuaState lua(L);

	const char * asset = lua.getString(1);
	IReadStream * pStream;

	IPlatformRequest& pltf = CPFInterface::getInstance().platform();
	pStream = pltf.openReadStream(asset, pltf.useEncryption());
	if(!pStream || pStream->getStatus() != IReadStream::NORMAL) {
		delete pStream;
		lua.retNil();
		return 1;
	}
	int size = pStream->getSize();
	u8 * buf = KLBNEWA(u8, size + 1);
	if(!buf) {
		delete pStream;
		lua.retNil();
		return 1;
	}
	pStream->readBlock((void *)buf, size);
	delete pStream;

	buf[size] = 0;
	const char * json = (const char *)buf;

	CKLBUtility::json2lua(lua, json, size);
	KLBDELETEA(buf);

	return 1;
}
