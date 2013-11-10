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
//
//  CKLBLuaLibKEY.h
//  GameEngine
//

#ifndef CKLBLuaLibKEY_h
#define CKLBLuaLibKEY_h

#include "ILuaFuncLib.h"

class CKLBLuaLibKEY : public ILuaFuncLib
{
private:
	CKLBLuaLibKEY();
public:
    
	CKLBLuaLibKEY(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibKEY();
    
	void addLibrary();

	inline static 
	int genUserID(char* buf, u32 bufSize) {
		return CPFInterface::getInstance().platform().genUserID(buf, bufSize);
	}

	inline static
	int genUserPW(const char* user_id, char* buf, u32 bufSize) {
		return CPFInterface::getInstance().platform().genUserPW(user_id, buf, bufSize);
	}

	inline static 
	bool setSecureID(const char* service_name, const char* user_id) {
		return CPFInterface::getInstance().platform().setSecureDataID(service_name, user_id);
	}

	inline static
	bool setSecurePW(const char* service_name, const char* passwd) {
		return CPFInterface::getInstance().platform().setSecureDataPW(service_name, passwd);
	}

	inline static
	int getSecureID(const char* service_name, char* buf, u32 bufSize) {
		return CPFInterface::getInstance().platform().getSecureDataID(service_name, buf, bufSize);
	}

	inline static 
	int getSecurePW(const char* service_name, char* buf, u32 bufSize) {
		return CPFInterface::getInstance().platform().getSecureDataPW(service_name, buf, bufSize);
	}
    
	inline static
	bool delSecureID(const char * service_name) {
		return CPFInterface::getInstance().platform().delSecureDataID(service_name);
	}

	inline static
	bool delSecurePW(const char * service_name) {
		return CPFInterface::getInstance().platform().delSecureDataPW(service_name);
	}

private:
    static int luaGenUserID		(lua_State * L);
    static int luaGenUserPW		(lua_State * L);

    static int luaSetKeyChainID	(lua_State * L);
    static int luaSetKeyChainPW	(lua_State * L);

    static int luaGetKeyChainID	(lua_State * L);
    static int luaGetKeyChainPW	(lua_State * L);

	static int luaDelKeyChainID	(lua_State * L);
	static int luaDelKeyChainPW	(lua_State * L);
};



#endif
