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
#include "CKLBLuaLibBIN.h"

static CKLBLuaLibBIN libdef(0);

CKLBLibRegistrator::LIBREGISTSTRUCT* CKLBLuaLibBIN::ms_libRegStruct = CKLBLibRegistrator::getInstance()->add("LibBIN", CLS_KLBBINARRAY);

CKLBLuaLibBIN::CKLBLuaLibBIN(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibBIN::~CKLBLuaLibBIN()
{
	CKLBBinArray::removeAll();
}

// LuaLib全破棄時に、生成されたままクローズされていないバイナリをクローズする
void
CKLBLuaLibBIN::destroyResources()
{
	CKLBBinArray::removeAll();
}

// バイナリオブジェクトをダンプする
bool
CKLBLuaLibBIN::dumpObjects(IPlatformRequest& pForm)
{
	pForm.logging("[LuaLibBIN]");
	return CKLBBinArray::dumpAll();
}

// Lua関数の追加
void
CKLBLuaLibBIN::addLibrary()
{
	addFunction("BIN_open",     CKLBLuaLibBIN::bin_open);
	addFunction("BIN_close",    CKLBLuaLibBIN::bin_close);
	addFunction("BIN_peek",		CKLBLuaLibBIN::bin_peek);
    addFunction("BIN_peekU16",  CKLBLuaLibBIN::bin_peek_u16);
    addFunction("BIN_peekU32",  CKLBLuaLibBIN::bin_peek_u32);
}

int
CKLBLuaLibBIN::bin_open(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retNil();
		return 1;
	}
	const char * bin_asset = lua.getString(1);
	CKLBBinArray * pBIN = KLBNEW(CKLBBinArray);
	if(!pBIN || !pBIN->loadAsset(bin_asset)) {
		lua.retNil();
		return 1;
	}
	lua.retPointer(pBIN);
	return 1;
}

int
CKLBLuaLibBIN::bin_close(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 1) {
		lua.retNil();
		return 1;
	}
	if(lua.isNil(1)) {	// ポインタとして積まれたものがnilだった
		lua.retNil();
		return 1;
	}
	CKLBBinArray * pBIN = (CKLBBinArray *)lua.getPointer(1);
	KLBDELETE(pBIN);
	lua.retNil();
	return 1;	// nilを返す
}

int
CKLBLuaLibBIN::bin_peek(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 2) {
		lua.retNil();
		return 1;
	}
	if(lua.isNil(1)) {	// ポインタとして積まれたものがnilだった
		lua.retNil();
		return 1;
	}
	CKLBBinArray * pBIN = (CKLBBinArray *)lua.getPointer(1);
	int offset = lua.getInt(2);

	if(offset < 0 || (int)pBIN->getSize() <= offset) {
		lua.retNil();
		return 1;
	}
	int value = pBIN->getByte(offset);
	lua.retInt(value);
	return 1;
}

int
CKLBLuaLibBIN::bin_peek_u16(lua_State *L)
{
    CLuaState lua(L);

    int argc = lua.numArgs();
	if(argc < 2 || argc > 3) {
		lua.retNil();
		return 1;
	}
	if(lua.isNil(1)) {	// ポインタとして積まれたものがnilだった
		lua.retNil();
		return 1;
	}
	CKLBBinArray * pBIN = (CKLBBinArray *)lua.getPointer(1);
	int offset = lua.getInt(2);

	if(offset < 0 || (int)pBIN->getSize() <= offset + 1) {
		lua.retNil();
		return 1;
	}

	bool f_bigendian = (argc >= 3) ? lua.getBool(3) : false;
    
	int value = (f_bigendian) ? pBIN->getWordBE(offset) : pBIN->getWordLE(offset);
	lua.retInt(value);
	return 1;
}

int
CKLBLuaLibBIN::bin_peek_u32(lua_State *L)
{
    CLuaState lua(L);

    int argc = lua.numArgs();
	if(argc < 2 || argc > 3) {
		lua.retNil();
		return 1;
	}
	if(lua.isNil(1)) {	// ポインタとして積まれたものがnilだった
		lua.retNil();
		return 1;
	}
	CKLBBinArray * pBIN = (CKLBBinArray *)lua.getPointer(1);
	int offset = lua.getInt(2);
    
	if(offset < 0 || (int)pBIN->getSize() <= offset + 3) {
		lua.retNil();
		return 1;
	}
	bool f_bigendian = (argc >= 3) ? lua.getBool(3) : false;
    
	u32 value = (f_bigendian) ? pBIN->getLongBE(offset) : pBIN->getLongLE(offset);
	lua.retInt(value);
	return 1;
}

CKLBBinArray* CKLBLuaLibBIN::bin_open(const char* bin_asset)
{
	CKLBBinArray * pBIN = KLBNEW(CKLBBinArray);
	if(!pBIN || !pBIN->loadAsset(bin_asset))
	{
		return NULL;
	}
	return pBIN;
}

void CKLBLuaLibBIN::bin_close(CKLBBinArray* pBIN)
{
	if(pBIN)
	{
		KLBDELETE(pBIN);
	}
}

bool CKLBLuaLibBIN::bin_peek(CKLBBinArray* pBIN, int offset, int* out_value)
{
	if(pBIN == NULL || offset < 0 || (int)pBIN->getSize() <= offset) {
		return false;
	}
	*out_value = pBIN->getByte(offset);
	return true;
}

bool CKLBLuaLibBIN::bin_peek_u16(CKLBBinArray* pBIN, int offset, u32* out_value, bool f_bigendian)
{
	if(pBIN == NULL || offset < 0 || (int)pBIN->getSize() <= offset + 1) {
		return false;
	}
	*out_value = (f_bigendian) ? pBIN->getWordBE(offset) : pBIN->getWordLE(offset);
	return true;
}

bool CKLBLuaLibBIN::bin_peek_u32(CKLBBinArray* pBIN, int offset, u32* out_value, bool f_bigendian)
{
	if(pBIN == NULL || offset < 0 || (int)pBIN->getSize() <= offset + 3) {
		return false;
	}
	*out_value = (f_bigendian) ? pBIN->getLongBE(offset) : pBIN->getLongLE(offset);
	return true;
}