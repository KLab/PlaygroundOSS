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
#ifndef CKLBLuaLibDATA_h
#define CKLBLuaLibDATA_h

#include "ILuaFuncLib.h"
#include "CKLBLibRegistrator.h"

class CKLBDataSet;

class CKLBLuaLibDATA : public ILuaFuncLib
{
private:
	CKLBLuaLibDATA();
	static CKLBLibRegistrator::LIBREGISTSTRUCT* ms_libRegStruct;
public:
	CKLBLuaLibDATA(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibDATA();

	void addLibrary();
	void destroyResources();

	static CKLBDataSet* cmdCreateData	(u32 dataSetID);
	static bool			cmdRegistData	(CKLBDataSet * pDataSet, const char* name_asset, const char* name_data, u32* pReturnHandle);
	inline static void	cmdDelete		(CKLBDataSet * pDataSet) {
		if(pDataSet) {
			CKLBDataHandler::destroySet(pDataSet);
		}
	}

private:
	static int createData	(lua_State * L);
	static int registData	(lua_State * L);
	static int registTable	(lua_State * L);
	static int deleteData	(lua_State * L);
};


#endif // CKLBLuaLibDATA_h
