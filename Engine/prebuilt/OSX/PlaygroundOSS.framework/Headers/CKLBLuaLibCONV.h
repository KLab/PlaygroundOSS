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
#ifndef CKLBLuaLibCONV_h
#define CKLBLuaLibCONV_h

#include "ILuaFuncLib.h"

class CKLBLuaLibCONV : public ILuaFuncLib
{
private:
	CKLBLuaLibCONV();
public:
	CKLBLuaLibCONV(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibCONV();

	void addLibrary();

private:
	static int lua2json		(lua_State * L);
	static int json2lua		(lua_State * L);
	static int jsonfile2lua	(lua_State * L);
};


#endif // CKLBLuaLibCONV_h
