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
#ifndef CKLBLuaConst_h
#define CKLBLuaConst_h

#include "CLuaState.h"

class CKLBLuaConst
{
public:
	struct ITEM {
		const char * name;
		int value;
	};
	static void removeLuaConst(CLuaState& lua, const char * grpName);

	static int setLuaConst(CLuaState& lua, const char * grpName, int num, ITEM * items);

	static int setLuaConstBy2Lists(CLuaState& lua, const char * grpName,
									int nums, const char ** nameList, int * valueList);
	static int setLuaConstBy2Lists(CLuaState& lua, const char * grpName,
									int nums, const char ** nameList);
};
/*
　【使用例】

	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	CKLBLuaConst::ITEM list[] = {
		{ "str", 1 },
		{ "int", 20 },
		{ "dex", 300 }
	};
	CKLBLuaConst::setLuaConst(lua, "PARAM", 3, items);

	上記のコードで、Lua側に

	PARAM.str = 1
	PARAM.int = 20
	PARAM.dex = 300

	の定数が定義されます。あるいは、

	CLuaState& lua = CKLBLuaEnv::getInstance().getState();
	const char * nameList[] = { "str", "int", "dex" };
	int valueList[] = { 1, 20, 300 };
	CKLBLuaConst::setLuaConstBy2Lists(lua, "PARAM", 3, nameList, valueList);

	でも同様です。
*/
#endif // CKLBLuaConst_h
