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
#include "CKLBLuaLibMatrix.h"
#include <math.h>
#include "CKLBUtility.h"
;
#define EPSILON (1e-5f)

// 大域変数としてインスタンスを作ることで、登録リストに追加される。
/* not used
static ILuaFuncLib::DEFCONST luaConst[] = {
	{ 0, 0 }
};
*/

static CKLBLuaLibMatrix libdef(0);


CKLBLuaLibMatrix::MATRIX	*	CKLBLuaLibMatrix::m_pBegin = NULL;
CKLBLuaLibMatrix::MATRIX	*	CKLBLuaLibMatrix::m_pEnd   = NULL;


CKLBLuaLibMatrix::CKLBLuaLibMatrix(DEFCONST * arrConstDef) : ILuaFuncLib(arrConstDef) {}
CKLBLuaLibMatrix::~CKLBLuaLibMatrix()
{
	delAllMatrix();
}

// LuaLib全破棄時にはすべてのMatrix objectを破棄する
void
CKLBLuaLibMatrix::destroyResources()
{
	delAllMatrix();
}

// 全てのmatrixオブジェクトをダンプする
bool
CKLBLuaLibMatrix::dumpObjects(IPlatformRequest& pForm)
{
	pForm.logging("[LuaLibMatrix]");

	MATRIX * pMat = m_pBegin;
	bool bResult = false;
	// 現存するすべてを破棄する
	while(pMat) {
		pForm.logging("[Matrix]<%p>: %s", pMat, (pMat->name) ? pMat->name : "(no name)");
		pMat = pMat->next;
		bResult = true;
	}
	return bResult;
}

// Lua関数の追加
void
CKLBLuaLibMatrix::addLibrary()
{
	// matrixに名前をつける
	addFunction("GEO_SetMatrixName", CKLBLuaLibMatrix::luaSetMatrixName);
	// matrixの生成/破棄/複製/変換/復元
	addFunction("GEO_CreateMatrix", CKLBLuaLibMatrix::luaCreateMatrix);
	addFunction("GEO_DeleteMatrix", CKLBLuaLibMatrix::luaDeleteMatrix);
	addFunction("GEO_RevertMatrix", CKLBLuaLibMatrix::luaRevertMatrix);
	addFunction("GEO_CopyMatrix", CKLBLuaLibMatrix::luaCopyMatrix);
	addFunction("GEO_OverwriteMatrix", CKLBLuaLibMatrix::luaOverwriteMatrix);
	addFunction("GEO_DeleteAllMatrix", CKLBLuaLibMatrix::luaDeleteAllMatrix);

	// 二つ以上のmatrixを順次掛け合わせ、結果を第一引数のmatrix objectに書き込む
	addFunction("GEO_MulMatrix", CKLBLuaLibMatrix::luaMulMatrix);

	// 逆行列を作る
	addFunction("GEO_InverseMatrix", CKLBLuaLibMatrix::luaInverseMatrix);

	// 転置行列を作る
	addFunction("GEO_TransposedMatrix", CKLBLuaLibMatrix::luaTransposedMatrix);

	// vectorにmatrixをかける
	addFunction("GEO_VecConv", CKLBLuaLibMatrix::luaMulMatVector);
	addFunction("GEO_VecArrayConv", CKLBLuaLibMatrix::luaMulMatVecArray);



}


void
CKLBLuaLibMatrix::getMatrix(CLuaState& lua, MATRIX * ret)
{
	// 最上位には対象の配列が積んである
	for(int idx = 0; idx < 16; idx++) {
		lua.retInt(idx + 1);			// Luaテーブル上のindexを積む
		lua.tableGet();					// 対応する値を取得する
		float val = lua.getFloat(-1);
		ret->m[idx] = val;
		lua.pop(1);
	}
}

void
CKLBLuaLibMatrix::setMatrix(CLuaState& lua, MATRIX * mat)
{
	// 最上位に対象の配列を作る
	lua.tableNew();
	for(int idx = 0; idx < 16; idx++) {
		// key として index 値を積む
		lua.retInt(idx + 1);
		// 値を積む
		lua.retDouble(mat->m[idx]);
		// 値を設定する
		lua.tableSet();
	}
}

void
CKLBLuaLibMatrix::getVector(CLuaState& lua, VECTOR * vec)
{
	// Luaスタックトップにはvectorテーブルが積んである
	for(int n = 0; n < 4; n++) {
		lua.retInt(n + 1); lua.tableGet(); vec->v[n] = lua.getFloat(-1); lua.pop(1);
	}
}

void
CKLBLuaLibMatrix::setVector(CLuaState& lua, VECTOR * vec)
{
	lua.tableNew();		// ベクトル用のテーブル
	for(int n = 0; n < 4; n++) {
		lua.retInt(n + 1); lua.retDouble(vec->v[n]); lua.tableSet();
	}
}

int
CKLBLuaLibMatrix::getVectorNums(CLuaState& lua)
{
	int idx = 0;
	lua.retNil();
	while(lua.tableNext()) {
		lua.retValue(-2);
		int v = lua.getInt(-1);
		if(v > idx) idx = v;
		lua.pop(2);
	}
	return idx;	// 最大のindex値
}

void
CKLBLuaLibMatrix::getVectorArray(CLuaState& lua, VECTOR * vec, int /*nums*/)
{
	lua.retNil();
	while(lua.tableNext()) {
		lua.retValue(-2);
		int idx = lua.getInt(-1) - 1;

		lua.retValue(-2);
		getVector(lua, &vec[idx]);

		lua.pop(3);
	}
}

void
CKLBLuaLibMatrix::setVectorArray(CLuaState& lua, VECTOR * vec, int nums)
{
	lua.tableNew();		// ベクトル配列用のテーブル

	for(int idx = 0; idx < nums; idx++) {
		lua.retInt(idx + 1);	// ベクトル配列中のindexを指定する

		// ベクトルの値をスタック上に積む
		setVector(lua, &vec[idx]);

		// この時点で、ベクトル配列のindexと、ベクトルがスタックに積まれている
		lua.tableSet();	// ベクトル配列にベクトルを設定する
	}
	// 一通りの設定が終わり、ベクトル配列テーブルがスタック上に積まれた状態になる。
}

// matrix同士を乗算する
void
CKLBLuaLibMatrix::mulMatrix(MATRIX * ret, MATRIX * a, MATRIX * b)
{
	for(int y = 0; y < 4; y++) {
		for(int x = 0; x < 4; x++) {
			ret->m[y*4+x] = 0.0f;
			for(int n = 0; n < 4; n++) {
				ret->m[y*4+x] += a->m[y*4+n] * b->m[n*4+x];
			}
		}
	}
}

// vector単品にmatrixを乗算する
void
CKLBLuaLibMatrix::mulMatVector(VECTOR * ret, VECTOR * vec, MATRIX * mat)
{
	for(int n = 0; n < 4; n++) {
		ret->v[n] = 0.0f;
		for(int m = 0; m < 4; m++) {
			ret->v[n] += vec->v[m] * mat->m[m*4+n];
		}
	}
}

// vectorの配列にmatrixを乗算する
void
CKLBLuaLibMatrix::mulMatVecArray(int nums, VECTOR * ret, VECTOR * arr, MATRIX * mat)
{
	for(int idx = 0; idx < nums; idx++) {
		mulMatVector(&ret[idx], &arr[idx], mat);
	}
}

// matrix を inverse matrix に変換する
bool
CKLBLuaLibMatrix::inverseMatrix(MATRIX * mat)
{
	float * A = mat->m;
	float B[16];
	int x, y, z;	

	for(x = 0; x < 16; x++) B[x] = (x % 5) ? 0.0f : 1.0f;

	for(y = 0; y < 4; y++) {

		float n = A[4 * y + y];
		if(fabs(n) < EPSILON) return false;

		for(x = 0; x < 4; x++) {
			A[4*y+x] /= n;
			B[4*y+x] /= n;
		}
		for(x = 0; x < 4; x++) {
			if(x == y) continue;
			n = A[4*x+y];
			for(z = 0; z < 4; z++) {
				A[4*x+z] -= A[4*y+z] * n;
				B[4*x+z] -= B[4*y+z] * n;
			}
		}
	}

	// 問題がなければ
	for(int i = 0; i < 16; i++) {
		mat->m[i] = B[i];
	}
	return true;
}

CKLBLuaLibMatrix::MATRIX *
CKLBLuaLibMatrix::newMatrix()
{
	MATRIX * pMat = KLBNEW(MATRIX);
	if(!pMat) return NULL;
	pMat->name = NULL;
	pMat->prev = m_pEnd;
	pMat->next = NULL;
	if(pMat->prev) {
		pMat->prev->next = pMat;
	} else {
		m_pBegin = pMat;
	}
	m_pEnd = pMat;
	return pMat;
}

void
CKLBLuaLibMatrix::delMatrix(MATRIX * pMat)
{
	if(!pMat) return;

	if(pMat->prev) {
		pMat->prev->next = pMat->next;
	} else {
		m_pBegin = pMat->next;
	}
	if(pMat->next) {
		pMat->next->prev = pMat->prev;
	} else {
		m_pEnd = pMat->prev;
	}
	KLBDELETEA(pMat->name);
	KLBDELETE(pMat);
}

int
CKLBLuaLibMatrix::delAllMatrix()
{
	MATRIX * pMat = m_pBegin;
	MATRIX * pNext;
	int cnt = 0;
	// 現存するすべてを破棄する
	while(pMat) {
		pNext = pMat->next;
		delMatrix(pMat);
		cnt++;
		pMat = pNext;
	}
	return cnt;
}

CKLBLuaLibMatrix::MATRIX *
CKLBLuaLibMatrix::getMatPointer(CLuaState& lua, int index)
{
	if(lua.isNil(index)) return NULL;
	return (MATRIX *)lua.getPointer(index);
}

// matrix object に名前を与える
int
CKLBLuaLibMatrix::luaSetMatrixName(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc != 2) {
		lua.retBool(false);
		return 1;
	}
	MATRIX * pMatrix = (MATRIX *)lua.getPointer(1);
	const char * name = (lua.isNil(2)) ? NULL : lua.getString(2);
	const char * newname = (name) ? CKLBUtility::copyString(name) : NULL;
	bool bResult = false;
	if(newname || (!newname && !name)) {
		if(pMatrix->name) KLBDELETEA(pMatrix->name);
		pMatrix->name = newname;
		bResult = true;
	}
	lua.retBool(bResult);
	return 1;
}


// matrix object を作る
int
CKLBLuaLibMatrix::luaCreateMatrix(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();

	// 引数が無い場合、単位行列を一つ生成して返す。
	if(argc == 0) {
		MATRIX * pMatrix = newMatrix();
		// 初期値として単位行列を生成する
		for(int i = 0; i < 16; i++) {
			pMatrix->m[i] = ((i % 4) == (i / 4)) ? 1.0f : 0.0f;
		}
		lua.retPointer(pMatrix);
		return 1;
	}

	for(int i = 1; i <= argc; i++) {
		MATRIX * pMatrix = newMatrix();
		// matrix object が作れなければ nil を返す
		if(!pMatrix) {
			lua.retNil();
		} else {
			if(lua.isNil(i)) {
				// 積まれたものがnilだったら単位行列を生成
				for(int i = 0; i < 16; i++) {
					pMatrix->m[i] = (!(i % 5)) ? 1.0f : 0.0f;
				}
			} else {	
				// Luaテーブルとみなし、初期値を設定する
				lua.retValue(i);
				getMatrix(lua, pMatrix);
				lua.pop(1);
			}
			// 生成したmatrix objectのポインタを返す
			lua.retPointer(pMatrix);
		}
	}
	return argc;
}

// matrix object を破棄する
int
CKLBLuaLibMatrix::luaDeleteMatrix(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	for(int i = 1; i <=  argc; i++) {
		MATRIX * pMat = getMatPointer(lua, i);
		delMatrix(pMat);
		lua.retNil();
	}
	return argc;
}

// matrix object をLuaテーブルに変換する
int
CKLBLuaLibMatrix::luaRevertMatrix(lua_State * L)
{
	CLuaState lua(L);
	MATRIX * pMat = getMatPointer(lua, 1);
	if(!pMat) {
		lua.retNil();
		return 1;
	}
	setMatrix(lua, pMat);

	return 1;
}

// matrix object を複製し、新たなmatrix object を生成する
int
CKLBLuaLibMatrix::luaCopyMatrix(lua_State * L)
{
	CLuaState lua(L);
	MATRIX * pMat = getMatPointer(lua, 1);
	MATRIX * pNew = newMatrix();

	for(int i = 0; i < 16; i++) pNew->m[i] = pMat->m[i];
	lua.retPointer(pNew);
	return 1;
}

int
CKLBLuaLibMatrix::luaInverseMatrix(lua_State * L)
{
	CLuaState lua(L);
	MATRIX * pMat = getMatPointer(lua, 1);
	bool bResult = inverseMatrix(pMat);
	lua.retBoolean(bResult);
	return 1;
}


// 指定された matrix object の内容に、Luaテーブルの値を設定する
int
CKLBLuaLibMatrix::luaOverwriteMatrix(lua_State * L)
{
	CLuaState lua(L);
	MATRIX * pMat = getMatPointer(lua, 1);
	if(!pMat) {
		lua.retNil();
		return 1;
	}
	lua.retValue(2);
	getMatrix(lua, pMat);
	lua.pop(1);

	lua.retPointer(pMat);
	return 1;
}

// 生成されているすべての matrix object を破棄する
int
CKLBLuaLibMatrix::luaDeleteAllMatrix(lua_State * L)
{
	CLuaState lua(L);
	int cnt = delAllMatrix();
	lua.retInt(cnt);
	return 1;
}

// マトリクス乗算
int
CKLBLuaLibMatrix::luaMulMatrix(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();
	if(argc < 3) {	// 対象となるmatrixが二つ以上なければnilを返す
		lua.retBoolean(false);
		return 1;
	}
	MATRIX * ans = getMatPointer(lua, 1);;
	MATRIX * a = getMatPointer(lua, 2);
	MATRIX * b = getMatPointer(lua, 3);
	if(!ans || !a || !b) {
		lua.retBoolean(false);
		return 1;
	}

	//
	// 指定された二つ以上のmatrixを、コピーを行わずに順次掛け合わせていく
	//
	// matrixが3つ以上ある場合
	MATRIX tmp[2];	// どこともつながらないテンポラリ
	int idx = 0;

	// 最初の二つを乗算する
	mulMatrix(&tmp[idx], a, b);

	// その結果に対し、残りがあれば最後の一つ手前まで順に掛け合わせていく
	for(int i = 4; i <= argc; i++) {
		idx = 1 - idx;
		a = getMatPointer(lua, i);
		if(!a) {
			lua.retBoolean(false);
			return 1;
		}
		mulMatrix(&tmp[idx], &tmp[1 - idx], a);
	}

	// tmp[idx]に最後の一つをかけた結果をansに書き出す
	for(int i = 0; i < 16; i++) {
		ans->m[i] = tmp[idx].m[i];
	}
	lua.retBoolean(true);
	return 1;
}

// ベクトル単品にマトリクスをかける
int
CKLBLuaLibMatrix::luaMulMatVector(lua_State * L)
{
	CLuaState lua(L);
	MATRIX * mat = getMatPointer(lua, 1);
	if(!mat) {
		lua.retNil();
		return 1;
	}
	VECTOR vec;
	VECTOR ret;

	// vector を取得
	lua.retValue(2);
	getVector(lua, &vec);
	lua.pop(1);

	// vectorにmatrixをかけて、その結果を受け取る
	mulMatVector(&ret, &vec, mat);

	// 結果のvectorをLuaテーブルに変換しスタックに積む
	setVector(lua, &ret);

	return 1;
}

// ベクトル配列にマトリクスをかける
int
CKLBLuaLibMatrix::luaMulMatVecArray(lua_State * L)
{
	CLuaState lua(L);
	int nums;
	MATRIX * mat = getMatPointer(lua, 1);
	if(!mat) {
		lua.retNil();
		return 1;
	}
	VECTOR * arrVec;
	VECTOR * retVec;

	// Luaのvector配列要素数を取得
	lua.retValue(2);
	nums = getVectorNums(lua);

	// 取得した数だけの要素を持つvector配列を、
	// 取得用と結果用の二つ作る。
	arrVec = KLBNEWA(VECTOR, nums);
	retVec = KLBNEWA(VECTOR, nums);

	// 取得用の側に、vector配列の内容を取得する
	getVectorArray(lua, arrVec, nums);
	lua.pop(1);

	// 取得したvector群にマトリクスをかける
	mulMatVecArray(nums, retVec, arrVec, mat);

	// 計算結果のベクトル配列をLuaテーブルに変換し、Luaスタックに積む
	setVectorArray(lua, retVec, nums);

	// バッファはもう用済み
	KLBDELETEA(retVec);
	KLBDELETEA(arrVec);

	// 積んだベクトル配列を戻り値とする。
	return 1;
}

int
CKLBLuaLibMatrix::luaTransposedMatrix(lua_State * L)
{
	CLuaState lua(L);
	int argc = lua.numArgs();

	if(argc != 1) {
		lua.retBoolean(false);
		return 1;
	}
	if(lua.isNil(1)) {
		lua.retBoolean(false);
		return 1;
	}
	MATRIX * pMat = getMatPointer(lua, 1);

	for(int y = 0; y < 4; y++) {
		for(int x = 0; x < 4; x++) {
			if(y <= x) continue;
			float tmp = pMat->m[4*y+x];
			pMat->m[4*y+x] = pMat->m[4*x+y];
			pMat->m[4*x+y] = tmp;
		}
	}

	lua.retBoolean(true);
	return 1;
}
