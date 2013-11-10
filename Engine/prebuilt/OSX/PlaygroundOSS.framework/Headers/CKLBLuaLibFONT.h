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
#ifndef CKLBLuaLibFONT_h
#define CKLBLuaLibFONT_h

#include "ILuaFuncLib.h"
#include "CKLBObject.h"
#include "CKLBLibRegistrator.h"

class CKLBLuaLibFONT : public ILuaFuncLib
{
private:
	CKLBLuaLibFONT();
public:
	struct FONTOBJ : public CKLBObjectScriptable {
		FONTOBJ	*	prev;
		FONTOBJ	*	next;
		int			size;
		void	*	font;

		u32 getClassID();
	};
	static FONTOBJ * create_font(int size, const char * fontname);

	CKLBLuaLibFONT(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibFONT();

	void addLibrary			();
	void destroyResources	();
	bool dumpObjects		(IPlatformRequest& pForm);

	static void remove_font		(FONTOBJ * fontobj);
	static void cmdGetTextInfo	(const char* str, void* font, STextInfo* pReturnInfo) {
		IPlatformRequest& pForm = CPFInterface::getInstance().platform();
		pForm.getTextInfo(str, font, pReturnInfo);
	}
private:

	static int remove_all_font	();

	static int luaFontLoad		(lua_State * L);
	static int luaFontCreate	(lua_State * L);
	static int luaFontRelease	(lua_State * L);
	static int luaGetTextInfo	(lua_State * L);
	static int luaSetDefaultLabelFont(lua_State * L);

	static FONTOBJ	*	ms_begin;
	static FONTOBJ	*	ms_end;

	static CKLBLibRegistrator::LIBREGISTSTRUCT* ms_libRegStruct;
};


#endif // CKLBLuaLibFONT_h
