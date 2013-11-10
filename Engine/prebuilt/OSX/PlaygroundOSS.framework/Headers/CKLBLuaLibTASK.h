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
#ifndef CKLBLuaLibTASK_h
#define CKLBLuaLibTASK_h

#include "ILuaFuncLib.h"

class CKLBLuaLibTASK : public ILuaFuncLib
{
private:
	CKLBLuaLibTASK();
public:
	CKLBLuaLibTASK(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibTASK();

	void addLibrary();

private:

	static int getProperty		(lua_State * L);
	static int setProperty		(lua_State * L);
	static int killTask			(lua_State * L);
	static int isKill			(lua_State * L);
	static int registerKill		(lua_State * L);
	static int setStageTask		(lua_State * L);
	static int clearStageTask	(lua_State * L);
	static int setPause			(lua_State * L);
	static int setManagerPause	(lua_State * L);
};

#endif // CKLBLuaLIbTASK_h
