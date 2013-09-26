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
#include "CKLBUtility.h"
#include "CKLBNode.h"
#include "CKLBTextInputNode.h"
#include "CKLBWebViewNode.h"
#include "CompositeManagement.h"
#include "CKLBScriptEnv.h"
#include <string.h>

void
CKLBUtility::getNodePosition(CKLBNode * pNode, float * x, float * y)
{
	*x = pNode->m_composedMatrix.m_matrix[ MAT_TX ];
	*y = pNode->m_composedMatrix.m_matrix[ MAT_TY ];
}

void
CKLBUtility::getNodeInverseMatrix(CKLBNode* pNode, SMatrix2D& result) {
	/*

	detA	= ad - cb

	Matrix
	A' 	=  d / detA
	B' 	= -b / detA
	C' 	= -c / detA
	D' 	=  a / detA
	TX'	= (b*ty - tx*d) / detA
	TY'	= (tx*c - a*ty) / detA

	*/

	float* mat = pNode->m_composedMatrix.m_matrix;
	float invDetA = 1.0f / ((mat[MAT_A] * mat[MAT_D]) - (mat[MAT_C] * mat[MAT_B])); 

	result.m_matrix[MAT_A] =  mat[MAT_D] * invDetA;
	result.m_matrix[MAT_B] =(-mat[MAT_B])* invDetA;
	result.m_matrix[MAT_C] =(-mat[MAT_C])* invDetA;
	result.m_matrix[MAT_D] =  mat[MAT_A] * invDetA;

	result.m_matrix[MAT_TX] = ((mat[MAT_B]*mat[MAT_TY]) - (mat[MAT_D]*mat[MAT_TX])) * invDetA;
	result.m_matrix[MAT_TY] = ((mat[MAT_C]*mat[MAT_TX]) - (mat[MAT_A]*mat[MAT_TY])) * invDetA;

	result.m_type = MATRIX_TG;
}

void
CKLBUtility::transform(SMatrix2D* pMatrix, float x, float y, float& resx, float& resy) {
	resx = (pMatrix->m_matrix[MAT_A] * x) + (pMatrix->m_matrix[MAT_B] * y) + pMatrix->m_matrix[MAT_TX];
	resy = (pMatrix->m_matrix[MAT_C] * x) + (pMatrix->m_matrix[MAT_D] * y) + pMatrix->m_matrix[MAT_TY];
}

s32 CKLBUtility::charCountUtf8(const char *s)
{
	// Using this code, added null string support.
	// http://porg.es/blog/counting-characters-in-utf-8-strings-is-faster
	//
	// This one seems nicer
	// but didnt had time to make sure it is correct, as it is more complex
	// : http://www.daemonology.net/blog/2008-06-05-faster-utf8-strlen.html
	// Saved the gem in case the URL disappear.
	/**
		#define ONEMASK ((size_t)(-1) / 0xFF)

		static size_t
		cp_strlen_utf8(const char * _s)
		{
			const char * s;
			size_t count = 0;
			size_t u;
			unsigned char b;

			// Handle any initial misaligned bytes.
			for (s = _s; (uintptr_t)(s) & (sizeof(size_t) - 1); s++) {
				b = *s;

				// Exit if we hit a zero byte.
				if (b == '\0')
					goto done;

				// Is this byte NOT the first byte of a character?
				count += (b >> 7) & ((~b) >> 6);
			}

			// Handle complete blocks.
			for (; ; s += sizeof(size_t)) {
				// Prefetch 256 bytes ahead.
				// __builtin_prefetch(&s[256], 0, 0);

				// Grab 4 or 8 bytes of UTF-8 data.
				u = *(size_t *)(s);

				// Exit the loop if there are any zero bytes.
				if ((u - ONEMASK) & (~u) & (ONEMASK * 0x80))
					break;

				// Count bytes which are NOT the first byte of a character.
				u = ((u & (ONEMASK * 0x80)) >> 7) & ((~u) >> 6);
				count += (u * ONEMASK) >> ((sizeof(size_t) - 1) * 8);
			}

			// Take care of any left-over bytes.
			for (; ; s++) {
				b = *s;

				// Exit if we hit a zero byte.
				if (b == '\0')
					break;

				// Is this byte NOT the first byte of a character?
				count += (b >> 7) & ((~b) >> 6);
			}

		done:
			return ((s - _s) - count);
		}
	 */


    s32 count = 0;
	if (s) {
		s32 i = 0;
		s32 iBefore = 0;

		while (s[i] > 0)
				ascii:  i++;
 
		count += i-iBefore;
		while (s[i])
		{
				if (s[i] > 0)
				{
						iBefore = i;
						goto ascii;
				}
				else
				switch (0xF0 & s[i])
				{
						case 0xE0: i += 3; break;
						case 0xF0: i += 4; break;
						default:   i += 2; break;
				}
				++count;
		}
	}
    return count;
}

u32 
CKLBUtility::nearest2Pow(u32 v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

int
CKLBUtility::safe_strcmp(const char* a, const char* b) 
{
	// Same string, same null : OK
	if (a == b) {
		return 0;
	}

	if (a && b) {
		// Both valid pointer
		return strcmp(a,b);
	} else {
		// One of the pointer is null.
		return -1;
	}
}

const char *
CKLBUtility::copyString(const char * string)
{
	klb_assert(string, "copy string is NULL.");
	char * buf = KLBNEWA(char, strlen(string) + 1);
    if(!buf) { return NULL; }
	strcpy(buf, string);
	return (const char *)buf;
}

const char *
CKLBUtility::copyMem(const char * src, u32 size)
{
	char * buf = KLBNEWA(char, size);
    if(!buf) { return NULL; }
	memcpy(buf, src, size);
	return (const char *)buf;
}

char *
CKLBUtility::numString64(char * buf, u64 value)
{
	u64 v = 1000000000000000000ULL;
	char * ptr = buf;
	while(v > 0) {
		int num = value / v;
		value = value % v;
		v = v / 10LL;
		if(num || ptr > buf) *ptr++ = num + '0';
	}
	if(ptr == buf) *ptr++ = '0';
	*ptr = 0;
	return buf;
}

s64
CKLBUtility::stringNum64(const char * string)
{
	s64 sign = 1;
	s64 val = 0;
	const char * p = string;
	while(*p) {
		if(p == string && *p == '-') {
			sign = -1;
			p++;
			continue;
		}
		val = val * 10LL;
		val += *p - '0';
		p++;
	}
	val = val * sign;
	return val;
}

char *
CKLBUtility::quoated(const char * string)
{
	int size = (!string) ? 5 : (strlen(string) + 3);
	char * buf = KLBNEWA(char, size);
    if(!buf) { return NULL; }
	if(!string) {
		strcpy(buf, "null");
	} else {
		sprintf(buf, "\"%s\"", string);
	}
	return buf;
}


const char **
CKLBUtility::splitString(const char * string, int delim)
{
	// pass-1: delim で分割される総数を得る
	int cnt = 1;
	for(const char * ptr = string; *ptr; ptr++) {
		if(*ptr == delim) cnt++;
	}

	// 外枠の配列生成
	const char ** arr = KLBNEWA(const char *, cnt + 1);
	arr[cnt] = 0;	// 終端は NULL

	const char * ptr = string;
	for(int i = 0; i < cnt; i++) {
		int len = 0;
        while(ptr[len] && ptr[len] != delim) { len++; }
		char * buf = KLBNEWA(char, len + 1);
		strncpy(buf, ptr, len);
		buf[len] = 0;
		arr[i] = (const char *)buf;
		ptr += len;
		if(*ptr == delim) ptr++;
	}

	return arr;
}

void
CKLBUtility::deleteSplitString(const char ** split_arr)
{
	for(int i = 0; split_arr[i]; i++) {
		const char * str = split_arr[i];
		KLBDELETEA(str);
	}
	KLBDELETEA(split_arr);
}

CKLBAsset *
CKLBUtility::loadAssetScript(const char * asset, u32 * handle, IKLBAssetPlugin* plugIn, bool bSimple)
{
	CKLBAsset * pAsset = loadAsset(asset, handle, plugIn, bSimple);
	if(!pAsset) {
		CKLBScriptEnv::getInstance().error("could not load asset: %s", asset);
	}
	return pAsset;
}

CKLBAsset *
CKLBUtility::readAsset(u8 * stream, u32 streamSize, u32 * handle, IKLBAssetPlugin * plugIn)
{
	CKLBAssetManager& pAssetManager = CKLBAssetManager::getInstance();
	CKLBAsset * pAsset;
	bool bResult = pAssetManager.loadAsset(stream, streamSize, (CKLBAbstractAsset **)&pAsset, plugIn);
    if(!bResult || !pAsset) { return NULL; }

	*handle = CKLBDataHandler::allocateHandle(pAsset);
	return pAsset;
}

CKLBAsset *
CKLBUtility::loadAsset(const char * asset, u32 * handle, IKLBAssetPlugin* plugIn, bool bSimple)
{
	CKLBAssetManager& pAssetManager = CKLBAssetManager::getInstance();
	// CPFInterface& pfif = CPFInterface::getInstance();
	CKLBAsset * pAsset;

	pAsset = (CKLBAsset *)pAssetManager.loadAssetByFileName(asset, plugIn);

	if(!pAsset) {
		return NULL;
	}
	if (handle) {
		*handle = CKLBDataHandler::allocateHandle(pAsset);
	}

	// bSimple が true のときは、texture であっても image の取得を行わない。
	// あくまで texture のみを必要とするケースもある。
	if(!bSimple && (pAsset->getAssetType() == ASSET_TEXTURE)) {
		// 画像asset名を与えると、帰ってくるのは texture asset であるため、
		// 改めてその中から画像 asset を取得する処理が必要となる。

		// 直接引数で与えられるasset名は、asset://foo.bar や file://install/foo.bar のように、
		// scheme がついているため、scheme に相当する部分を除去した名称(パス含む)を使用する。
		const char * scheme_pattern[] = {
			"file://install/",
			"file://external/",
			"asset://",
			0
		};
		const char * name = NULL;
		for(int i = 0; scheme_pattern[i]; i++) {
			const char * pattern = scheme_pattern[i];
			int len = strlen(pattern);
			if(!strncmp(asset, pattern, len)) {
				name = asset + len;
				break;
			}
		}
		if(!name) {
			if (handle) { CKLBDataHandler::releaseHandle(*handle); }
			return NULL;
		}
		pAsset = ((CKLBTextureAsset*)pAsset)->getImage(name);
		if(!pAsset) {
			if (handle) { CKLBDataHandler::releaseHandle(*handle); }
			return NULL;
		}
	}
	return pAsset;
}

CKLBNode *
CKLBUtility::createNode(const char * asset, u32 order, u32 * handle, IKLBAssetPlugin* plugIn)
{
	CKLBAsset * pAsset = loadAsset(asset, handle, plugIn);
    if(!pAsset) { return NULL; }
	CKLBNode * pNode = pAsset->createSubTree(order);
	return pNode;
}

CKLBNode *
CKLBUtility::createNodeScript(const char * asset, u32 order, u32 * handle, IKLBAssetPlugin* plugIn)
{
	CKLBAsset * pAsset = loadAssetScript(asset, handle, plugIn);
	if(!pAsset) { return NULL; }
	CKLBNode * pNode = pAsset->createSubTree(order);
	if(!pNode) {
		CKLBScriptEnv::getInstance().error("Node create failed. [asset: %s ]", asset);
	}
	return pNode;
}

CKLBNode *
CKLBUtility::createCompositeNodeScript(CKLBUITask * pTask, const char * asset, u32 order, u32 * handle, IKLBAssetPlugin* plugIn)
{
	CKLBAsset * pAsset = loadAssetScript(asset, handle, plugIn);
	if(!pAsset) { return NULL; }
	CKLBNode * pNode = ((CKLBCompositeAsset *)pAsset)->createSubTree(pTask, order);

	if(!pNode) {
		CKLBScriptEnv::getInstance().error("Node create failed. [asset: %s ]", asset);
	}
	return pNode;
}


void
CKLBUtility::deleteNode(CKLBNode * pNode, u32 handle)
{
	KLBDELETE(pNode);
	CKLBDataHandler::releaseHandle(handle);
}

const char *
CKLBUtility::lua2json(CLuaState&lua, u32& streamSize, JSON_REPLACE * arrReplace)
{
	JSON_BUF jsonBuf;	// 1 KB on stack.
	jsonBuf.max = JSON_BLOCK_SIZE;
	jsonBuf.buf = KLBNEWA(char, jsonBuf.max);
	if(!jsonBuf.buf) { return NULL; }
	jsonBuf.idx			= 0;
	jsonBuf.poolCount	= 0;
	jsonBuf.poolSize	= 0;
	jsonBuf.arr_replace = arrReplace;

	bool bResult = lua2json_rec(lua, &jsonBuf);
	if(!bResult) {
		KLBDELETEA(jsonBuf.buf);
		return NULL;
	}

	// End of string.
	streamSize = jsonBuf.idx;
	return (const char *)jsonBuf.buf;
}

const char *
CKLBUtility::escape(const char * string)
{
	int len = strlen(string);
	char * buf = KLBNEWA(char, len * 2 + 1);
	char * ptr = buf;
	for(int i = 0; string[i]; i++) {
		switch(string[i])
		{
		default:
			*ptr++ = string[i];
			break;
		case '"':
		case '\\':
		case '/':
			*ptr++ = '\\';
			*ptr++ = string[i];
			break;
		case '\t':
			*ptr++ = '\\';
			*ptr++ = 't';
			break;
		case '\n':
			*ptr++ = '\\';
			*ptr++ = 'n';
			break;
		case '\r':
			*ptr++ = '\\';
			*ptr++ = 'r';
			break;
		}
	}
	*ptr = 0;
	return (const char *)buf;
}

bool
CKLBUtility::JSON_BUF::add(const char * msg)
{
	int len = strlen(msg);

	// 現在のバッファが足りないなら、足りるようになるまで追加する
	
	while(idx + len >= max) {
		int size = max + (JSON_BLOCK_SIZE*2);
		char * n_buf = KLBNEWA(char, size);
        if(!n_buf) { return false; }
		memcpy(n_buf, buf, idx);
		KLBDELETEA(buf);
		buf = n_buf;
		max = size;
	}
	strcpy(buf + idx, msg);
	idx += len;

	return true;
}

bool
CKLBUtility::JSON_BUF::addU8(u8 byte)
{
	// 現在のバッファが足りないなら、足りるようになるまで追加する
	while(idx + 1 >= max) {
		int size = max + (JSON_BLOCK_SIZE*2);
		char * n_buf = KLBNEWA(char, size);
        if(!n_buf) { return false; }
		memcpy(n_buf, buf, idx);
		KLBDELETEA(buf);
		buf = n_buf;
		max = size;
	}
	buf[idx++] = byte;
	return true;
}

bool
CKLBUtility::JSON_BUF::addPool(const char* str, int& idx) 
{
	int strL = strlen(str);
	u32 cnt = 0;
	while (cnt < poolCount) {
		if (poolEntries[cnt].size == strL) {
			if (strcmp(str,poolEntries[cnt].string) == 0) {
				idx = cnt;
				return true;
			}
		}
		cnt++;
	}

	// Add new entry.
	poolEntries[poolCount].size = strL;
	poolEntries[poolCount].string = str;
	idx = poolCount++;
	klb_assert(poolCount < 100, "Max Reached");
	poolSize += strL;
	return true;
}

bool
CKLBUtility::JSON_BUF::addU32(u32 value) 
{
	// 現在のバッファが足りないなら、足りるようになるまで追加する
	while(idx + 4 >= max) {
		int size = max + (JSON_BLOCK_SIZE*2);
		char * n_buf = KLBNEWA(char, size);
        if(!n_buf) { return false; }
		memcpy(n_buf, buf, idx);
		KLBDELETEA(buf);
		buf = n_buf;
		max = size;
	}

	buf[idx++] = (value >> 24);
	buf[idx++] = (value >> 16);
	buf[idx++] = (value >> 8 );
	buf[idx++] = (value      );
	return true;
}

#include "../../libs/JSonParser/api/yajl_parse.h"

const char *
CKLBUtility::lua2BJson(CLuaState&lua, u32& streamSize, JSON_REPLACE * arrReplace)
{
	JSON_BUF jsonBuf;	// 1 KB on stack.
	jsonBuf.max = JSON_BLOCK_SIZE * 2;
	jsonBuf.buf = KLBNEWA(char, jsonBuf.max);
    if(!jsonBuf.buf) { return NULL; }
	jsonBuf.idx			= 0;
	jsonBuf.poolCount	= 0;
	jsonBuf.poolSize	= 0;
	jsonBuf.arr_replace = arrReplace;

	bool bResult = lua2BJson_rec(lua, &jsonBuf);
	bResult = jsonBuf.addU8(BJSN_END) && bResult;
	if(!bResult) {
		KLBDELETEA(jsonBuf.buf);
		return 0;
	}

	u32 headerAndCP = (2 + 4 + 4 + (4 * jsonBuf.poolCount) + jsonBuf.poolSize); // Pool size include size with zero.
	u8* block = KLBNEWA(u8, jsonBuf.idx + headerAndCP);
	if (block) {
		memcpy(&block[headerAndCP],jsonBuf.buf,jsonBuf.idx);

		// Header
		block[0] = 0xFF;
		block[1] = 0xFF;

		// Count
		block[2] = jsonBuf.poolCount >> 24;
		block[3] = jsonBuf.poolCount >> 16;
		block[4] = jsonBuf.poolCount >>  8;
		block[5] = jsonBuf.poolCount;

		// String Buf Size
		block[6] = jsonBuf.poolSize >> 24;
		block[7] = jsonBuf.poolSize >> 16;
		block[8] = jsonBuf.poolSize >>  8;
		block[9] = jsonBuf.poolSize;

		u8* wrt = &block[10];
		for (u32 n=0; n < jsonBuf.poolCount; n++) {
			// Size
			u32 size = jsonBuf.poolEntries[n].size;
			wrt[0] = size >> 24;
			wrt[1] = size >> 16;
			wrt[2] = size >>  8;
			wrt[3] = size;

			memcpy(&wrt[4], jsonBuf.poolEntries[n].string, size);
			wrt += size + 4;
		}

		KLBDELETEA(jsonBuf.buf);
	} else {
		KLBDELETEA(jsonBuf.buf);
		return NULL;
	}

	jsonBuf.buf = (char*)block;
	jsonBuf.idx += headerAndCP;

	// End of BJson stream.
	streamSize = jsonBuf.idx;
	return (const char *)jsonBuf.buf;
}

/*static*/
bool
CKLBUtility::lua2BJson_rec(CLuaState& lua, JSON_BUF * jsonBuf)
{
	switch(lua.getType(-1))
	{
	default:
		return false;
		break;
	case LUA_TNIL:
		{
			return jsonBuf->addU8(BJSN_CTE_NULL);
		}
		break;
	case LUA_TLIGHTUSERDATA:
		{
			const void * p = lua.getPointer(-1);
			if(!p) {
				return jsonBuf->addU8(BJSN_CTE_NULL);
			} 
			char buf[64];
			sprintf(buf, "%p", p);
			bool bResult  = jsonBuf->addU8(BJSN_STRING_DIRECT);
			bResult = bResult && jsonBuf->addU32(strlen(buf));
			bResult = bResult && jsonBuf->add(buf);
			return bResult;
		}
		break;
	case LUA_TNUMBER:
		{
			char buf[64];
			// 整数か実数か判定
			int num_i = lua.getInt(-1);
			double num_f = lua.getDouble(-1);

			double sub = fabs((double)num_i - num_f);
			bool result;
			if(sub < 0.00001) {	// 整数扱い
				sprintf(buf, "%d", num_i);
				result  = jsonBuf->addU8(BJSN_NUMBER_I32);
				result &= jsonBuf->addU32(num_i);
			} else {					// 実数扱い
				sprintf(buf, "%f", (float)num_f);
				float f = (float)num_f;
				int* pI = (int*)&f;
				result  = jsonBuf->addU8(BJSN_NUMBER_FLT);
				result &= jsonBuf->addU32(*pI);
			}
			return result;
		}
		break;
	case LUA_TBOOLEAN:
		{
			bool b = lua.getBool(-1);
			return jsonBuf->addU8((b) ? BJSN_CTE_TRUE:BJSN_CTE_FALSE);
		}
		break;
	case LUA_TSTRING:
		{
			const char * string = lua.getString(-1);
			//
			// DO NOT ESCAPE ENCODE THE STRING in BJSON !
			// --> Encode is made only inside std Json because Json itself is a string.
			// const char * escape_string = escape(string);
			//
			// int len = 0;
			bool bResult;
			bResult = jsonBuf->addU8(BJSN_STRING_DIRECT);
			bResult = bResult && jsonBuf->addU32(strlen(string));
			bResult = bResult && jsonBuf->add(string);
			return bResult;
		}
		break;
	case LUA_TTABLE:
		{
			// Lua table は JSON的に2種類の使用方法(map/array)があるため、
			// PASS-1: 登場した table がどちらの扱いになるかを確認する
			// PASS-2: 判定結果の方法で巡回する

			// PASS-1: 文字列index付きの値があるか確認する

			int min, max;
			bool bMap = false;
			min = -1;
			max = 0;
			bool bArrResult = true;

			lua.retNil();
			while(lua.tableNext()) {
				lua.retValue(-2);

				// この段階で、(-1) = index, (-2) = 値

				// 数値index配列の場合は array 扱い
				if(lua.isNum(-1)) {
					int idx = lua.getInt(-1);
                    if(min < 0 || idx < min) { min = idx; }
                    if(max < idx)            { max = idx; }
				} else {
					bMap = true;
				}
				lua.pop(2);
				if(bMap) {
					lua.pop(1);
					break;	// 結果が出たので PASS-2 へ
				}
			}

			// PASS-2: bMap の値によって、この配列をmapまたはarrayとして取り扱う。
			if(bMap) {
				// Map として扱う
				bArrResult = jsonBuf->addU8(BJSN_OPEN_OBJ);
				bArrResult = jsonBuf->addU32(0xFFFFFFFF) && bArrResult;

				lua.retNil();
				while(lua.tableNext()) {
					// キーを出力
					lua.retValue(-2);

					// IT/KEY/VAL/KEYCOPY
					const char * key = lua.getString(-1);
					bArrResult = jsonBuf->addU8(BJSN_MEMBER) && bArrResult;
					int idx;
					bArrResult = jsonBuf->addPool(key, idx) && bArrResult;
					bArrResult = jsonBuf->addU32(idx) && bArrResult;

					lua.pop(1);

					// 実際の Luaテーブル値を値として出力する前に、
					// JSON_REPLACEの配列を確認し、値を置き換えるべきキーは
					// 指定された値で置き換える。
					bool bReplaced = false;
					if(jsonBuf->arr_replace) {
						for(int i = 0; jsonBuf->arr_replace[i].key; i++) {
							if(!strcmp(key, jsonBuf->arr_replace[i].key)) {
								bArrResult = jsonBuf->add(jsonBuf->arr_replace[i].value) && bArrResult;

								bArrResult  = jsonBuf->addU8(BJSN_STRING_DIRECT);
								bArrResult &= jsonBuf->addU32(strlen(jsonBuf->arr_replace[i].value));
								bArrResult &= jsonBuf->add(jsonBuf->arr_replace[i].value);

								bReplaced = true;
								break;
							}
						}
					}

					if(!bReplaced) {
						// 値を出力する
						bArrResult = lua2BJson_rec(lua, jsonBuf) && bArrResult;
					}

					lua.pop(1);
				}
//				lua.pop(1);	// 巡回用indexを取り除く

				bArrResult = jsonBuf->addU8(BJSN_CLOSE_OBJ) && bArrResult;

			} else {
				// Array の扱い
				// lua.tableNext() による巡回はindexの順が保障されないので、
				// 取得した min ～ max にかけて値を取得し、出力する。

				bArrResult  = jsonBuf->addU8(BJSN_OPEN_ARR) && bArrResult;
				bArrResult &= jsonBuf->addU32(0xFFFFFFFF);
				bArrResult &= jsonBuf->addU32(0xFFFFFFFF); // Mask

				if(min != -1 || max) {
					for(int i = min; i <= max; i++) {
						lua.retInt(i);
	
						lua.tableGet();
		
						// 値を出力する
						bArrResult = lua2BJson_rec(lua, jsonBuf) && bArrResult;

						lua.pop(1);
					}
				}
				bArrResult = jsonBuf->addU8(BJSN_CLOSE_ARR) && bArrResult;
			}
			return bArrResult;
		}
		break;
	}
	//return false;	// Dead code.
}

bool
CKLBUtility::lua2json_rec(CLuaState& lua, JSON_BUF * jsonBuf)
{
	switch(lua.getType(-1))
	{
	default:
		return false;
		break;
	case LUA_TNIL:
		{
			const char * msg = "null";
			return jsonBuf->add(msg);
		}
		break;
	case LUA_TLIGHTUSERDATA:
		{
			const void * p = lua.getPointer(-1);
			if(!p) {
				const char * msg = "null";
				return jsonBuf->add(msg);
			} 
			char buf[64];
			sprintf(buf, "%p", p);
			return jsonBuf->add(buf);
		}
		break;
	case LUA_TNUMBER:
		{
			char buf[64];
			// 整数か実数か判定
			int     num_i   = lua.getInt(-1);
			double  num_f   = lua.getDouble(-1);
			double  sub     = fabs((double)num_i - num_f);
			if(sub < 0.00001) {	// 整数扱い
				sprintf(buf, "%d", num_i);
			} else {					// 実数扱い
				sprintf(buf, "%f", (float)num_f);
			}
			return jsonBuf->add(buf);
		}
		break;
	case LUA_TBOOLEAN:
		{
			bool b = lua.getBool(-1);
			return jsonBuf->add((b) ? "true":"false");
		}
		break;
	case LUA_TSTRING:
		{
			const char * string = lua.getString(-1);
			bool bResult = jsonBuf->add("\"");
			const char * escape_string = escape(string);
			bResult = jsonBuf->add(escape_string) && bResult;
			KLBDELETEA(escape_string);
			return  jsonBuf->add("\"") && bResult;
		}
		break;
	case LUA_TTABLE:
		{
			// Lua table は JSON的に2種類の使用方法(map/array)があるため、
			// PASS-1: 登場した table がどちらの扱いになるかを確認する
			// PASS-2: 判定結果の方法で巡回する

			// PASS-1: 文字列index付きの値があるか確認する

			int min, max;
			bool bMap = false;
			min = -1;
			max = 0;
			bool bArrResult = true;

			lua.retNil();
			while(lua.tableNext()) {
				lua.retValue(-2);

				// この段階で、(-1) = index, (-2) = 値

				// 数値index配列の場合は array 扱い
				if(lua.isNum(-1)) {
					int idx = lua.getInt(-1);
                    if(min < 0 || idx < min) { min = idx; }
                    if(max < idx)            { max = idx; }
				} else {
					bMap = true;
				}
				lua.pop(2);
				if(bMap) {
					lua.pop(1);
					break;	// 結果が出たので PASS-2 へ
				}
			}

			// PASS-2: bMap の値によって、この配列をmapまたはarrayとして取り扱う。
			if(bMap) {
				// Map として扱う
				jsonBuf->add("{");

				bool bFirst = false;

				lua.retNil();
				while(lua.tableNext()) {

					// 2番目以降の項目であれば、前の値との区切りとして ','を入れる
					if(bFirst) {
						bArrResult = jsonBuf->add(",") && bArrResult;
					}
					bFirst = true;

					// キーを出力
					lua.retValue(-2);

					// IT/KEY/VAL/KEYCOPY
					const char * key = lua.getString(-1);
					bArrResult = jsonBuf->add("\"") && bArrResult;
					bArrResult = jsonBuf->add(key) && bArrResult;
					bArrResult = jsonBuf->add("\":") && bArrResult;

					lua.pop(1);

					// 実際の Luaテーブル値を値として出力する前に、
					// JSON_REPLACEの配列を確認し、値を置き換えるべきキーは
					// 指定された値で置き換える。
					bool bReplaced = false;
					if(jsonBuf->arr_replace) {
						for(int i = 0; jsonBuf->arr_replace[i].key; i++) {
							if(!strcmp(key, jsonBuf->arr_replace[i].key)) {
								bArrResult = jsonBuf->add(jsonBuf->arr_replace[i].value) && bArrResult;
								bReplaced = true;
								break;
							}
						}
					}

					if(!bReplaced) {
						// 値を出力する
						bArrResult = lua2json_rec(lua, jsonBuf) && bArrResult;
					}

					lua.pop(1);
				}
//				lua.pop(1);	// 巡回用indexを取り除く

				bArrResult = jsonBuf->add("}") && bArrResult;

			} else {
				// Array の扱い
				// lua.tableNext() による巡回はindexの順が保障されないので、
				// 取得した min ～ max にかけて値を取得し、出力する。

				bArrResult = jsonBuf->add("[") && bArrResult;

				bool bFirst = false;
				
				if(min != -1 || max) {
					for(int i = min; i <= max; i++) {
						lua.retInt(i);
	
						// 2番目以降の項目であれば、前の値との区切りとして ','を入れる
						if(bFirst) jsonBuf->add(",");
						bFirst = true;

						lua.tableGet();
		
						// 値を出力する
						bArrResult = lua2json_rec(lua, jsonBuf) && bArrResult;

						lua.pop(1);
					}
				}
				bArrResult = jsonBuf->add("]") && bArrResult;
			}
			return bArrResult;
		}
		break;
	}
	//return false; // Dead code
}

// JSON文字列をLuaテーブルに変換し、Luaスタックに積む
void
CKLBUtility::json2lua(CLuaState& lua, const char * json, u32 json_size)
{
	CKLBJsonItem * pRoot = CKLBJsonItem::ReadJsonData(json, json_size);
	jsonItem2lua(lua, pRoot);
	KLBDELETE(pRoot);
}

// CKLBJsonItemのツリーをLuaテーブルに変換し、Luaスタックに積む
void
CKLBUtility::jsonItem2lua(CLuaState& lua, CKLBJsonItem * pRoot)
{
	if (pRoot) {
		json2lua_rec(lua, pRoot);
	}
}

void
CKLBUtility::json2lua_rec(CLuaState& lua, CKLBJsonItem * pItem)
{
	switch(pItem->getType())
	{
	case CKLBJsonItem::J_MAP:	// 文字列indexの連想配列
		{
			lua.tableNew();
			CKLBJsonItem * child = pItem->child();
			while(child) {
				lua.retString(child->key());
				json2lua_rec(lua, child);
				lua.tableSet();
				child = child->next();
			}
		}
		break;
	case CKLBJsonItem::J_ARRAY:	// 数値indexの連想配列
		{
			lua.tableNew();
			CKLBJsonItem * child = pItem->child();
			int index = 1;
			while(child) {
				lua.retInt(index);
				json2lua_rec(lua, child);
				lua.tableSet();
				child = child->next();
				index++;
			}
		}
		break;
	case CKLBJsonItem::J_BOOLEAN:
		{
			lua.retBoolean(pItem->getBool());
		}
		break;
	case CKLBJsonItem::J_INT:
		{
			lua.retInt(pItem->getInt());
		}
		break;
	case CKLBJsonItem::J_DOUBLE:
		{
			lua.retDouble(pItem->getDouble());
		}
		break;
	case CKLBJsonItem::J_STRING:
		{
			lua.retString(pItem->getString());
		}
		break;
	case CKLBJsonItem::J_NULL:
		{
			lua.retPointer(0);
//			lua.retNil();
		}
		break;
	}
}

/*static*/
char * 
CKLBUtility::URLencode(char * retbuf, int maxlen, const char ** postForm)
{
	// 指定された postForm から、POST文字列を生成する。
	// postForm は URLencodeされておらず、個々の項目が連結されていない状態。
	char * basebuf = retbuf;
	int now_size = maxlen;

    if(!basebuf) { return NULL; } 

	char * ptr = basebuf;
	for(int i = 0; postForm[i]; i++) {
		const char * formItem = postForm[i];

		if(i > 0) {
			*ptr++ = '&';
			if(ptr - basebuf >= now_size - 1) {
				// バッファが与えられている場合はエラー終了
				return 0;
			}
		}
		for(const char * src = formItem; *src; src++) {
			int reqsize = 1;
			char tmpbuf[10];
			const char * data = NULL;
			if(('0'<= *src && *src <= '9') ||
				('a'<= *src && *src <= 'z') ||
				('A'<= *src && *src <= 'Z') ||
				*src == '_' || *src == '-' ||
				*src == '.' || *src == '*' || *src == '=') {
	
				// そのままいける文字
				data = src;
			} else if(*src == ' ') {

				// 空白の置き換え
				data = "+";

			} else {
				reqsize = 3;
				sprintf(tmpbuf, "%%%02x", (int)*(unsigned char *)src);
				data = (const char *)tmpbuf;
			}
			if((ptr + reqsize) - basebuf >= now_size - 1) {
				// バッファが与えられている場合はエラー終了
				return 0;
			}
			memcpy(ptr, data, reqsize);
			ptr += reqsize;
		}
	}
	*ptr = 0;
	return basebuf;
}
