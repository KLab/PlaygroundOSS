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
#include "CKLBLuaConst.h"

void
CKLBLuaConst::removeLuaConst(CLuaState& lua, const char * grpName)
{
	lua.retNil();
	lua.setGlobal(grpName);
}

/*!
	\param lua		reference of target Lua state.
	\param grpName	Lua constant group(class) name.
	\param nums		define constants number.
	\param items	define constants item list.
*/
int
CKLBLuaConst::setLuaConst(CLuaState& lua, const char * grpName, int nums, ITEM * items)
{
	lua.tableNew();
	for(int i = 0; i < nums; i++) {
		ITEM * pItem = items + i;

		lua.retString(pItem->name);
		lua.retInt(pItem->value);
		lua.tableSet();
	}
	lua.setGlobal(grpName);
	return nums;
}

int
CKLBLuaConst::setLuaConstBy2Lists(CLuaState& lua, const char * grpName,
									int nums, const char ** nameList)
{
	lua.tableNew();
	for(int i = 0; i < nums; i++) {
		lua.retString(nameList[i]);
		lua.retInt(i);
		lua.tableSet();
	}
	lua.setGlobal(grpName);
	return nums;
}

int
CKLBLuaConst::setLuaConstBy2Lists(CLuaState& lua, const char * grpName,
									int nums, const char ** nameList, int * valueList)
{
	lua.tableNew();
	for(int i = 0; i < nums; i++) {
		lua.retString(nameList[i]);
		lua.retInt(valueList[i]);
		lua.tableSet();
	}
	lua.setGlobal(grpName);
	return nums;
}
