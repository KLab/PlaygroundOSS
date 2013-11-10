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
#ifndef CKLBLuaLibBIN_h
#define CKLBLuaLibBIN_h

#include "ILuaFuncLib.h"
#include "CKLBBinArray.h"
#include "CKLBLibRegistrator.h"

class CKLBLuaLibBIN : public ILuaFuncLib
{
private:
	CKLBLuaLibBIN();

	static int bin_open		(lua_State * L);
	static int bin_close	(lua_State * L);
	static int bin_peek		(lua_State * L);
    static int bin_peek_u16	(lua_State * L);
    static int bin_peek_u32	(lua_State * L);

	static CKLBLibRegistrator::LIBREGISTSTRUCT* ms_libRegStruct;
public:
	CKLBLuaLibBIN(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibBIN();

	void addLibrary			();
	void destroyResources	();
	bool dumpObjects		(IPlatformRequest& pForm);

	// -- lua free
	static CKLBBinArray* bin_open(const char* bin_asset);
	static void bin_close	(CKLBBinArray* pBIN);
	static bool bin_peek	(CKLBBinArray* pBIN, int offset, s32* out_value);
	static bool bin_peek_u16(CKLBBinArray* pBIN, int offset, u32* out_value, bool f_bigendian);
	static bool bin_peek_u32(CKLBBinArray* pBIN, int offset, u32* out_value, bool f_bigendian);
};

#endif // CKLBLuaLibBIN_h
