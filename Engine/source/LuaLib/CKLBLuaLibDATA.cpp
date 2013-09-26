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

#include "CKLBLuaLibDATA.h"
#include "CKLBDataHandler.h"
#include "CKLBLuaEnv.h"
#include "CKLBUtility.h"

static CKLBLuaLibDATA libdef(0);

CKLBLibRegistrator::LIBREGISTSTRUCT* CKLBLuaLibDATA::ms_libRegStruct = CKLBLibRegistrator::getInstance()->add("LibDATA", CLS_KLBDATASET);

CKLBLuaLibDATA::CKLBLuaLibDATA(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibDATA::~CKLBLuaLibDATA() {}

void
CKLBLuaLibDATA::destroyResources()
{
	 CKLBDataHandler::clearAllSet();
}

// Lua関数の追加
void
CKLBLuaLibDATA::addLibrary()
{
	addFunction("DATA_create",   CKLBLuaLibDATA::createData);
	addFunction("DATA_register", CKLBLuaLibDATA::registData);
	addFunction("DATA_regtable", CKLBLuaLibDATA::registTable);
	addFunction("DATA_delete",	 CKLBLuaLibDATA::deleteData);
}

int
CKLBLuaLibDATA::createData(lua_State * L)
{
	CLuaState lua(L);
	if(lua.numArgs() != 1) {
		CKLBLuaEnv::getInstance().errMsg("ID is not given to DATA_create().");
		return 0;
	}

	u32 dataSetID = lua.getInt(1);
	CKLBDataSet * pDataSet = CKLBDataHandler::createSet(dataSetID);

	// 戻り値は CKLBDataSet のポインタ
	lua.retPointer(pDataSet);
	return 1;
}

int
CKLBLuaLibDATA::registTable(lua_State *L)
{
    CLuaState lua(L);
    int count = 0;
    bool result = true;
    int argc = lua.numArgs();
    if(argc != 2) {
        lua.retBoolean(false);
        return 1;
    }
    
    CKLBDataSet * pDataSet = (CKLBDataSet *)lua.getPointer(1);
    if(!pDataSet) {
        lua.retBoolean(false);
        return 1;        
    }
    // CPFInterface& pfif = CPFInterface::getInstance();
    // CKLBAssetManager& pAssetManager = CKLBAssetManager::getInstance();
    CKLBAbstractAsset * pAsset;
    u32 handle;
    
    lua.retValue(2);
    lua.retNil();
    while (lua.tableNext()) {
        lua.retValue(-2);
        
        lua.retValue(-2);
        lua.retNil();
        const char * str[2];
        int idx = 0;
        while(lua.tableNext()) {
            if(idx < 2) str[idx++] = lua.getString(-1);
            lua.pop(1);
        }
        lua.pop(1);

        const char * asset = str[0];
        const char * name = str[1];

		handle = 0;
		pAsset = CKLBUtility::loadAsset(asset, 0, 0, true);
		handle = pDataSet->allocateHandle(pAsset, (char *)name);
		if(handle) {
			count++;
		}
        lua.pop(2);
    }
    lua.pop(1);
        
    if(result) {
        lua.retInt(count);
    } else {
        lua.retBoolean(false);
    }
    return 1;
}

int
CKLBLuaLibDATA::registData(lua_State * L)
{
	CLuaState lua(L);

    if(lua.numArgs() != 3) {
        lua.retBoolean(false);
        return 1;
    }
	CKLBDataSet * pDataSet = (CKLBDataSet *)lua.getPointer(1);
	const char * name_asset = lua.getString(2);
	const char * name_data  = lua.getString(3);
    
    if(!pDataSet) {
        lua.retBoolean(false);
        return 1;
    }

	// CPFInterface& pfif = CPFInterface::getInstance();
	// CKLBAssetManager& pAssetManager = CKLBAssetManager::getInstance();
	CKLBAbstractAsset * pAsset;
	u32 handle;

	handle = 0;
	pAsset = CKLBUtility::loadAsset(name_asset, 0, 0, true);
	handle = pDataSet->allocateHandle(pAsset, (char *)name_data);
	lua.retInt(handle);
	return 1;
}

int
CKLBLuaLibDATA::deleteData(lua_State * L)
{
	CLuaState lua(L);

	CKLBDataSet * pDataSet = (CKLBDataSet *)lua.getPointer(1);
    if(pDataSet) {
		CKLBDataHandler::destroySet(pDataSet);
    }
	return 0;
}

CKLBDataSet*
CKLBLuaLibDATA::cmdCreateData(u32 dataSetID)
{
	CKLBDataSet * pDataSet = CKLBDataHandler::createSet(dataSetID);
	return pDataSet;
}

bool
CKLBLuaLibDATA::cmdRegistData(CKLBDataSet * pDataSet, const char* name_asset, const char* name_data, u32* pReturnHandle)
{
	if(pDataSet) {
		// CPFInterface& pfif = CPFInterface::getInstance();
		// CKLBAssetManager& pAssetManager = CKLBAssetManager::getInstance();
		CKLBAbstractAsset * pAsset;

		u32 handle = 0;
		pAsset = CKLBUtility::loadAsset(name_asset, NULL, NULL, true);
		handle = pDataSet->allocateHandle(pAsset, (char *)name_data);

		*pReturnHandle = handle;
		return true;
	}
	
	return false;
}


