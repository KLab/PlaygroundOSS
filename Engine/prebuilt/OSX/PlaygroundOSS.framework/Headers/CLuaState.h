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
//  CLuaState.h
//

#ifndef CLuaState_h
#define CLuaState_h

#include "lua.hpp"
#include "CPFInterface.h"
class CLuaState
{
	friend class CKLBScriptEnv;
	friend class CKLBLuaEnv;
public:
    CLuaState(lua_State * L);
    virtual ~CLuaState();
    
    // 引数の数を取得
    inline int numArgs() {
        return lua_gettop(m_L);
    }
    
    // 引数取得メソッド
	inline bool isNil	(int pos) { return lua_isnil(m_L, pos)		? true : false; }
	inline bool isNum	(int pos) { return lua_isnumber(m_L, pos)	? true : false; }
	inline bool isString(int pos) { return lua_isstring(m_L, pos)	? true : false; }
	inline bool isTable	(int pos) { return lua_istable(m_L, pos)	? true : false; }

    inline bool getBool(int pos) {
        if(!lua_isboolean(m_L, pos)) {
            // boolean と解釈できない
            errorMsg("boolean", pos);            
            return false;
        }
        return (lua_toboolean(m_L, pos)) ? true : false;
    }
    inline bool getBoolean(int pos) {
        if(!lua_isboolean(m_L, pos)) {
            // boolean と解釈できない
            errorMsg("boolean", pos);            
            return false;
        }
        return (lua_toboolean(m_L, pos)) ? true : false;
    }
    inline int  getInt(int pos) {
        lua_Integer ret;
		if(!lua_isnumber(m_L, pos)) {
            // 数値ではない
            errorMsg("integer", pos);
            return 0;
        }
        ret = lua_tointeger(m_L, pos);
        return (int)ret;
    }
    inline float getFloat(int pos) {
        lua_Number ret;
		if(!lua_isnumber(m_L, pos)) {
            // 数値ではない
            errorMsg("float", pos);
            return 0.0;
        }
        ret = lua_tonumber(m_L, pos);
        return (float)ret;
    }
    inline double getDouble(int pos) {
        lua_Number ret;
		if(!lua_isnumber(m_L, pos)) {
            // 数値ではない
            errorMsg("double", pos);
            return 0.0;
        }
        ret = lua_tonumber(m_L, pos);
        return (double)ret;
    }
    inline const char * getString(int pos) {
        if(!lua_isstring(m_L, pos)) {
            // 文字列ではない
            errorMsg("string", pos);
            return 0;
        }
        const char * ret = lua_tostring(m_L, pos);
        return ret;
    }
    inline const void * getPointer(int pos) {
        if(!lua_islightuserdata(m_L, pos)) {
            // ポインタとは解釈できない
            errorMsg("internal object", pos);
            return 0;
        }
        const void * ret = lua_topointer(m_L, pos);
        return ret;
    }
    inline const char * getTable(int pos) {
        if(!lua_istable(m_L, pos)) {
            // ポインタとは解釈できない
            errorMsg("TABLE", pos);
            return 0;
        }
        const char * ret = lua_tostring(m_L, pos);
        return ret;
    }

    // 戻り値を返すための関数
    inline void retNil		()					{ lua_pushnil(m_L);							}
    inline void retBool     (bool val)			{ lua_pushboolean(m_L, (val) ? 1 : 0);		}
    inline void retBoolean	(bool val)			{ lua_pushboolean(m_L, (val) ? 1 : 0);		}
    inline void retInt		(int val)			{ lua_pushinteger(m_L, (lua_Integer)val);	}
    inline void retFloat	(float val)			{ lua_pushnumber(m_L, (lua_Number)val);		}
    inline void retDouble	(double val)		{ lua_pushnumber(m_L, (lua_Number)val);		}
    inline void retString	(const char * val)	{ lua_pushstring(m_L, val);					}
    inline void retPointer	(void * ptr)		{ lua_pushlightuserdata(m_L, ptr);			}
    inline void retGlobal	(const char * val)	{ lua_getglobal(m_L, val);					}

	inline void retValue	(int pos)			{ lua_pushvalue(m_L, pos);					}

	inline void tableNew	()					{ lua_newtable(m_L);						}
	inline void tableSet	(int pos = -3)		{ lua_settable(m_L, pos);					}
	inline void tableGet	(int pos = -2)		{ lua_gettable(m_L, pos);					}
	inline int  tableNext	(int pos = -2)		{ return lua_next(m_L, pos);				}
	inline void pop			(int num)			{ lua_pop(m_L, num);						}
	inline void setGlobal	(const char * name) { lua_setglobal(m_L, name);					}
	inline void getGlobal	(const char * name) { lua_getglobal(m_L, name);					}
	inline int  getType		(int pos = -1)		{ return lua_type(m_L, pos);				}

    // 現在実行されている行番号とファイル名を得る
	const char * getScriptName();

    inline int getNumLine() {
        lua_Debug dbg;
        if(lua_getstack(m_L, 1, &dbg)) {
            lua_getinfo(m_L, "Sl", &dbg);
        }
        return dbg.currentline;
    }


protected:
    // Lua 側の関数を呼び出すメソッド
    // 呼び出す際の引数の数と型を、argform で文字列として指定する。
    // B:boolean / I:integer / N:number / S:string / P:lightuserdata
    // 例)
    //  lua.callback("CallBackFunc", "PIIBS", pTask, 100, 200, true, "return");
    //
	virtual bool callback			(const char * func, const char * argform, ...);
	virtual bool call_luafunction	(int retnum, const char * func, const char * argform, va_list ap);
	virtual bool retcall			(int retnum, const char * func, const char * argform, ...);
	virtual bool call				(int args,   const char * func, int nresults = 0);
private:
	int error		(const char * fmt, ...); // Only from CKLBScriptEnv
    void errorMsg	(const char * type_name, int argnum);
    
    lua_State       *   m_L;
};

class CLua_Only_State : public CLuaState {
private:	
	CLua_Only_State(lua_State * L) : CLuaState(L) {}; // declared to avoid warnings
public:
	bool callback			(const char * func, const char * argform, ...);
	bool call_luafunction	(int retnum, const char * func, const char * argform, va_list ap);
	bool retcall			(int retnum, const char * func, const char * argform, ...);
	bool call				(int args,   const char * func, int nresults = 0);
};

#endif
