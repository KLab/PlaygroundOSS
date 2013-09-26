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
#include "CKLBLuaLibRES.h"

//
// Module for DUMP function.
//
#include "CKLBAsset.h"
#include "CKLBDrawTask.h"

static ILuaFuncLib::DEFCONST luaConst[] = {
	{ 0, 0 }
};

static CKLBLuaLibRES libdef(luaConst);

CKLBLuaLibRES::CKLBLuaLibRES(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibRES::~CKLBLuaLibRES() {}

// Adding Lua functions
void
CKLBLuaLibRES::addLibrary()
{
	addFunction("RES_DumpSceneGraph",		CKLBLuaLibRES::luaRESDumpSceneGraph);
	addFunction("RES_DumpRendering",		CKLBLuaLibRES::luaRESDumpRendering);
	addFunction("RES_DumpAsset",			CKLBLuaLibRES::luaRESDumpAssets);
	addFunction("RES_DumpTexturePacker",	CKLBLuaLibRES::luaRESDumpTexturePacker);
	addFunction("RES_DumpGeometryCost",		CKLBLuaLibRES::luaRESDumpGeometryCost);
	addFunction("RES_DumpDataSet",			CKLBLuaLibRES::luaRESDumpDataSet);
	addFunction("RES_DumpRenderCost",		CKLBLuaLibRES::luaRESDumpRenderCost);
	addFunction("RES_DumpTaskList",			CKLBLuaLibRES::luaRESDumpTaskList);
}

int
CKLBLuaLibRES::luaRESDumpTaskList(lua_State * /*L*/) 
{
	CKLBTaskMgr::getInstance().dump();
	// Return nothing.
	return 0;
}

int
CKLBLuaLibRES::luaRESDumpSceneGraph(lua_State * L) 
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	const void* ptr = NULL;	// Summary by default
	if(argc >= 1) {
		ptr = lua.getPointer(1);
	}

	dumpSceneGraph(ptr);

	// Return nothing.
	return 0;
}

int
CKLBLuaLibRES::luaRESDumpRendering(lua_State * L) 
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	bool detailed = false;	// Summary by default
	if(argc >= 1) {
		detailed = lua.getBool(1);
	}

	dumpRendering(detailed);

	// Return nothing.
	return 0;
}

int
CKLBLuaLibRES::luaRESDumpAssets(lua_State * /*L*/) 
{
	dumpAssets();
	return 0;
}

int
CKLBLuaLibRES::luaRESDumpDataSet(lua_State * /*L*/) 
{
	dumpDataSet();
	return 0;
}

#include "CKLBDrawTask.h"
int
CKLBLuaLibRES::luaRESDumpRenderCost(lua_State * L) {
	CLuaState lua(L);
	int argc = lua.numArgs();
	if (argc >= 1) {
		bool active = lua.getBool(1);
		CKLBDrawResource::getInstance().setLog(active);
	}
	return 0;
}

int
CKLBLuaLibRES::luaRESDumpTexturePacker(lua_State * L) 
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	bool detailed = false;	// Summary by default
	if(argc >= 1) {
		detailed = lua.getBool(1);
	}

	dumpTexturePacker(detailed);
	// Return nothing.
	return 0;
}

int
CKLBLuaLibRES::luaRESDumpGeometryCost(lua_State * L) 
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	bool detailed = false;	// Summary by default
	if(argc >= 1) {
		detailed = lua.getBool(1);
	}
	
	dumpGeometryCost(detailed);

	// Return nothing.
	return 0;
}

void CKLBLuaLibRES::dumpSceneGraph(const void* ptr)
{
	if (ptr == NULL) {
		CKLBDrawResource& res = CKLBDrawResource::getInstance();
		res.getRoot()->dump(0, 0xFFFFFFFF);
	} else {
		CKLBTask* tsk = (CKLBTask*)ptr;
		if (tsk->getTaskType() == CKLBTask::TASK_LUA_UI) {
			CKLBUITask* pUI = (CKLBUITask*)tsk;
			pUI->getNode()->dump(0, 0xFFFFFFFF);
		}
	}
}

void CKLBLuaLibRES::dumpGeometryCost(bool /*detailed*/) {
	IPlatformRequest& pfif = CPFInterface::getInstance().platform();
	#ifdef DEBUG_PERFORMANCE
		pfif.logging("\n=== Geometry cost ===\n");
		pfif.logging("Matrix Composition Count : %i\n", CKLBNode::s_matrixRecomputeCount);
		pfif.logging("Vertex Transform   Count : %i\n", CKLBNode::s_vertexRecomputeCount);
		pfif.logging("Color  Transform   Count : %i\n", CKLBNode::s_colorRecomputeCount );
		pfif.logging("=== End Geometry ===\n");
	#else
		pfif.logging("DEBUG_DumpGeometryCost only available with DEBUG_PERFORMANCE build.\n");
	#endif
}
