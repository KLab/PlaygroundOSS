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
#ifndef CKLBLuaLibRES_h
#define CKLBLuaLibRES_h


#include "ILuaFuncLib.h"
#include "CKLBRendering.h"
#include "CKLBTexturePacker.h"
#include "CKLBUITask.h"

class CKLBLuaLibRES : public ILuaFuncLib
{
private:
	CKLBLuaLibRES();
public:
	CKLBLuaLibRES(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibRES();

	void addLibrary();

	static void dumpSceneGraph(const void* ptr);

	inline 
	static void dumpRendering(bool detailed) {
		if(detailed) {
			CKLBRenderingManager::getInstance().dump(0xFFFFFFFF);
		}
		CKLBRenderingManager::getInstance().dumpMetrics();
	}

	inline
	static void dumpAssets() {
		CKLBAssetManager::getInstance().dump();
	}

	inline 
	static void dumpDataSet() {
		CKLBDataHandler::dumpDataSet();
	}

	inline
	static void dumpTexturePacker(bool detailed) {
		TexturePacker::getInstance().dump(detailed);
	}

	static void dumpGeometryCost(bool detailed);


private:
	static int luaRESDumpTaskList		(lua_State * L);
	static int luaRESDumpSceneGraph		(lua_State * L);
	static int luaRESDumpRendering		(lua_State * L);
	static int luaRESDumpAssets			(lua_State * L);
	static int luaRESDumpDataSet		(lua_State * L);
	static int luaRESDumpTexturePacker	(lua_State * L);
	static int luaRESDumpGeometryCost	(lua_State * L);
	static int luaRESDumpRenderCost		(lua_State * L);
};


#endif // CKLBLuaLibRES_h
