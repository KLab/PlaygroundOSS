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
#include "hash_sha1.h"
#include "CKLBLuaLibHASH.h"
#include "CKLBUtility.h"

static CKLBLuaLibHASH libdef(0);

CKLBLuaLibHASH::CKLBLuaLibHASH(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibHASH::~CKLBLuaLibHASH() {}

// Lua関数の追加
	void
CKLBLuaLibHASH::addLibrary()
{
	addFunction("HASH_SHA1",     CKLBLuaLibHASH::luaHashSha1);
}


	int
CKLBLuaLibHASH::luaHashSha1(lua_State * L)
{
	CLuaState lua(L);

	const char * src = lua.getString(1);
	char hash_buf[41];
	SHA1Context sha;
	SHA1Reset(&sha);
	SHA1Input(&sha, reinterpret_cast<unsigned char const*>(src), strlen(src));
	if (!SHA1Result(&sha)) {
		return 0;
	}
	sprintf(hash_buf, "%08X%08X%08X%08X%08X", sha.Message_Digest[0], sha.Message_Digest[1], sha.Message_Digest[2], sha.Message_Digest[3], sha.Message_Digest[4]);
	lua.retString(hash_buf);
	return 1;
}
