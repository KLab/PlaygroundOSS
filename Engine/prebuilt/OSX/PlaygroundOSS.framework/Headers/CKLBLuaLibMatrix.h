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
#ifndef CKLBLuaLibMatrix_h
#define CKLBLuaLibMatrix_h

#include "ILuaFuncLib.h"
#include "CKLBObject.h"


class CKLBLuaLibMatrix : public ILuaFuncLib
{
private:
	CKLBLuaLibMatrix();
public:
	CKLBLuaLibMatrix(DEFCONST * arrConstDef);
	virtual ~CKLBLuaLibMatrix();

	void addLibrary();
	void destroyResources();
	bool dumpObjects(IPlatformRequest& pForm);

	struct MATRIX {
		MATRIX	*	prev;
		MATRIX	*	next;

		const char * name;

		float m[16];

	};
	
	struct VECTOR {
		float v[4];
	};

	// Luaスタック最上位のLuaテーブルを、内部のmatrixとして取得する
	static void getMatrix(CLuaState& lua, MATRIX * ret);

	// MATRIXをLuaテーブルに変換し、Luaスタックに積む
	static void setMatrix(CLuaState& lua, MATRIX * mat);

	// 単品のvectorを取得する
	static void getVector(CLuaState& lua, VECTOR * vec);

	// 単品のvectorをLuaテーブルに変換し、Luaスタックに積む
	static void setVector(CLuaState& lua, VECTOR * vec);

	// Luaスタック最上位のLuaテーブルをvector配列とみなし、vectorの数を取得する
	static int getVectorNums(CLuaState& lua);

	// Luaスタック最上位のLuaテーブルを内部のvector配列として取得する
	static void getVectorArray(CLuaState& lua, VECTOR * vec, int nums);

	// VECTOR配列をLuaテーブルに変換し、Luaスタックに積む
	static void setVectorArray(CLuaState& lua, VECTOR * vec, int nums);

	// vector単品に matrix をかける
	static void mulMatVector(VECTOR * ret, VECTOR * arr, MATRIX * mat);

	// vector 配列に matrix をかける
	static void mulMatVecArray(int num, VECTOR * ret, VECTOR * arr, MATRIX * mat);

	// matrixの乗算
	static void mulMatrix(MATRIX * ans, MATRIX * a, MATRIX * b); 

	// inverce matrix に変換する
	static bool inverseMatrix(MATRIX * mat);

private:
	static int luaSetMatrixName		(lua_State * L);
	static int luaCreateMatrix		(lua_State * L);
	static int luaDeleteMatrix		(lua_State * L);
	static int luaRevertMatrix		(lua_State * L);
	static int luaCopyMatrix		(lua_State * L);
	static int luaInverseMatrix		(lua_State * L);
	static int luaOverwriteMatrix	(lua_State * L);
	static int luaDeleteAllMatrix	(lua_State * L);

	static int luaMulMatrix			(lua_State * L);
	static int luaMulMatVecArray	(lua_State * L);
	static int luaMulMatVector		(lua_State * L);
	static int luaTransposedMatrix	(lua_State * L);

	static MATRIX * newMatrix		();
	static void		delMatrix		(MATRIX * pMat);
	static int		delAllMatrix	();
	static MATRIX * getMatPointer	(CLuaState& lua, int index);

	// 生成されたmatrix objectはすべてlinkとして
	static MATRIX	*	m_pBegin;
	static MATRIX	*	m_pEnd;

};


#endif // CKLBLuaLibMatrix_h
