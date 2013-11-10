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
#ifndef ILuaFuncLib_h
#define ILuaFuncLib_h

#include "CLuaState.h"

class ILuaFuncLib
{
public:
	typedef struct {
		const char * name;
		int			 cmd;
	} DEFCONST;

	ILuaFuncLib();
	ILuaFuncLib(DEFCONST * arrCmdItem);
	virtual ~ILuaFuncLib();

	virtual bool exist				();

	static	bool registAllLibs		(lua_State * L);
	static	void destroyAllResources();

	void addFunction(const char * luaFuncName, int (*func)(lua_State * L));
protected:

	// 関数追加処理を記述する
	virtual void addLibrary() = 0;

	// その関数群で確保したリソースに残りがあればすべて破棄する
	virtual void destroyResources();

	// その関数群で生成したオブジェクトをダンプする必要があればダンプする
	virtual bool dumpObjects(IPlatformRequest& pForm);

private:
    void addLink	(DEFCONST * arrCmdItem);
	void registLib	(lua_State * L);
	void registConst();

	static int luaDumpObjects(lua_State * L);

    static ILuaFuncLib	*	m_begin;
	static ILuaFuncLib	*	m_end;

	ILuaFuncLib			*	m_pPrev;
    ILuaFuncLib			*   m_pNext;
	DEFCONST			*	m_arrCmdItem;
	lua_State			*	m_L;
};

#endif // ILuaFunkLib_h
