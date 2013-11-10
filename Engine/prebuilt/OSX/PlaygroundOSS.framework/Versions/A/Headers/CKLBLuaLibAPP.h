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
#ifndef CKLBLuaLibAPP_h
#define CKLBLuaLibAPP_h


#include "ILuaFuncLib.h"

class CKLBLuaLibAPP : public ILuaFuncLib
{
private:
	CKLBLuaLibAPP();
public:
	CKLBLuaLibAPP(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibAPP();

	void addLibrary();

private:
	static int luaCallApplication	(lua_State * L);
	static int luaGetPhysicalMem	(lua_State * L);
public: // Lua-free
	static bool callApplication(IPlatformRequest::APP_TYPE type, const char* addr, const char* subject, const char* body);
};



#endif // CKLBLuaLibAPP_h
