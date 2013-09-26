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
#include "CKLBJsonItem.h"
#include "CKLBUtility.h"
#include "../../libs/JSonParser/api/yajl_parse.h"
#include "../../libs/JSonParser/api/yajl_gen.h"

#include "CPFInterface.h"
#include <string.h>

CKLBJsonItem::CKLBJsonItem(CKLBJsonItem * pParent)
: m_pParent     (pParent)
, m_child_begin (NULL)
, m_child_end   (NULL)
, m_prev        (NULL)
, m_next        (NULL)
, m_key         (NULL)
{
	if(m_pParent) {
		m_prev = m_pParent->m_child_end;
		if(m_prev) {
			m_prev->m_next = this;
		} else {
			m_pParent->m_child_begin = this;
		}
		m_pParent->m_child_end = this;
	}
	memset(&m_value, 0, sizeof(union VAR));
}

CKLBJsonItem::~CKLBJsonItem()
{
	// 自身の子を削除する
	CKLBJsonItem * pItem = m_child_begin;
	CKLBJsonItem * pNext;
	while(pItem) {
		pNext = pItem->m_next;
		KLBDELETE(pItem);
		pItem = pNext;
	}

	// 兄弟から抜ける
	if(m_prev) {
		m_prev->m_next = m_next;
	} else {
		if(m_pParent) m_pParent->m_child_begin = m_next;
	}
	if(m_next) {
		m_next->m_prev = m_prev;
	} else {
		if(m_pParent) m_pParent->m_child_end = m_prev;
	}

	// キーを破棄する
	KLBDELETEA(m_key);

	// 自身のtypeがJ_STRINGであれば、その領域を破棄する
	if(m_type == J_STRING) {
		KLBDELETEA(m_value.s);
	}
}

bool
CKLBJsonItem::setKey(const char * keyname)
{
	m_key = CKLBUtility::copyString(keyname);
    if(!m_key) { return false; }
	return true;
}

CKLBJsonItem *
CKLBJsonItem::searchChild(const char * key)
{
	CKLBJsonItem * pItem = m_child_begin;
    while(pItem && strcmp(pItem->m_key, key)) { pItem = pItem->m_next; }
	return pItem;
}


CKLBJsonItem *
CKLBJsonItem::ReadJsonData(const char * json_string, u32 json_size)
{
	s64 start = CPFInterface::getInstance().platform().nanotime();

	static yajl_callbacks callbacks = { 
		CKLBJsonItem::read_null,  
		CKLBJsonItem::read_boolean,  
		CKLBJsonItem::read_int,  
		CKLBJsonItem::read_double,  
		null,  
		CKLBJsonItem::read_string,  
		CKLBJsonItem::read_start_map,  
		CKLBJsonItem::read_map_key,  
		CKLBJsonItem::read_end_map,  
		CKLBJsonItem::read_start_array,  
		CKLBJsonItem::read_end_array
	};
	yajl_handle hand;
    /* generator config */  
//    yajl_gen g;				    // My Context.2012.12.05  使用していなかったのでコメントアウト
    yajl_status stat;  
  
	
//    g = yajl_gen_alloc(NULL);		// 2012.12.05  使用していなかったのでコメントアウト

	JSON_State * pState = KLBNEW(JSON_State);
	pState->pCurrent = NULL;
	pState->pFirst   = NULL;
	pState->pParent  = NULL;

	/* ok.  open file.  let's read and parse */  
	hand = yajl_alloc(&callbacks, NULL, pState);

	if (hand) {
		/* and let's allow comments by default */  
		yajl_config(hand, yajl_allow_comments, 1);

		u32 size = (!json_size) ? strlen(json_string) : json_size;
		stat = yajl_parse(hand, (const unsigned char *)json_string, size);

		CKLBJsonItem * pRoot = pState->pFirst;
		KLBDELETE(pState);

		if (stat == yajl_status_ok) {
			stat = yajl_complete_parse(hand);
			if (stat == yajl_status_ok) {
				yajl_free(hand);
				s64 time = CPFInterface::getInstance().platform().nanotime() - start;
				DEBUG_PRINT("JSon -> Tree : %f ms",(float)(time / 1000000.0));
				return pRoot;
			}
		}
        if(pRoot) { KLBDELETE(pRoot); }     // 2012.12.12  NULLチェック追加
	}

	return NULL;
}


int
CKLBJsonItem::read_null(void * ctx)
{
	JSON_State * pState = (JSON_State *)ctx;

	CKLBJsonItem * pItem;
	if(pState->pCurrent) {
		pItem = pState->pCurrent;
	} else {
		pItem = KLBNEWC(CKLBJsonItem, (pState->pParent));
	}
	pItem->m_type    = J_NULL;
	pState->pCurrent = NULL;
	return 1;
}

int
CKLBJsonItem::read_boolean(void * ctx, int boolean)
{
	JSON_State * pState = (JSON_State *)ctx;

	CKLBJsonItem * pItem;
	if(pState->pCurrent) {
		pItem = pState->pCurrent;
	} else {
		pItem = KLBNEWC(CKLBJsonItem, (pState->pParent));
	}
	pItem->m_type    = J_BOOLEAN;
	pItem->m_value.b = (boolean != 0) ? true : false;
	pState->pCurrent = NULL;
	return 1;
}

int
CKLBJsonItem::read_int(void * ctx, long long integerVal)
{
	JSON_State * pState = (JSON_State *)ctx;

	CKLBJsonItem * pItem;
	if(pState->pCurrent) {
		pItem = pState->pCurrent;
	} else {
		pItem = KLBNEWC(CKLBJsonItem, (pState->pParent));
	}
	pItem->m_type    = J_INT;
	pItem->m_value.i = integerVal;
	pState->pCurrent = NULL;
	return 1;
}

int
CKLBJsonItem::read_double(void * ctx, double doubleVal)
{
	JSON_State * pState = (JSON_State *)ctx;

	CKLBJsonItem * pItem;
	if(pState->pCurrent) {
		pItem = pState->pCurrent;
	} else {
		pItem = KLBNEWC(CKLBJsonItem, (pState->pParent));
	}
	pItem->m_type    = J_DOUBLE;
	pItem->m_value.d = doubleVal;
	pState->pCurrent = NULL;

	return 1;
}

int
CKLBJsonItem::read_string(void * ctx, const unsigned char * stringVal, size_t stringLen, int /*cte_pool*/)
{
	JSON_State * pState = (JSON_State *)ctx;

	char * buf = KLBNEWA(char, stringLen + 1);
	strncpy(buf, (const char *)stringVal, stringLen);
	buf[stringLen] = 0;

	CKLBJsonItem * pItem;
	if(pState->pCurrent) {
		pItem = pState->pCurrent;
		pItem->m_type    = J_STRING;
		pItem->m_value.s = buf;
	} else {
		pItem = KLBNEWC(CKLBJsonItem, (pState->pParent));
	}
	pItem->m_type    = J_STRING;
	pItem->m_value.s = buf;
	pState->pCurrent = NULL;
	return 1;
}

int
CKLBJsonItem::read_start_map(void * ctx, unsigned int /*size*/)
{
	JSON_State * pState = (JSON_State *)ctx;

	if(!pState->pCurrent) {
		CKLBJsonItem * pItem = KLBNEWC(CKLBJsonItem, (pState->pParent));
		pState->pCurrent = pItem;
		if(!pState->pFirst) pState->pFirst = pItem;
	}
	pState->pCurrent->m_type = J_MAP;

	pState->pParent  = pState->pCurrent;
	pState->pCurrent = NULL;

	return 1;
}

int
CKLBJsonItem::read_map_key(void * ctx, const unsigned char * stringVal, size_t stringLen, int /*cte_pool*/)
{
	JSON_State * pState = (JSON_State *)ctx;

	CKLBJsonItem * pItem = KLBNEWC(CKLBJsonItem, (pState->pParent));
	pState->pCurrent = pItem;
	if(!pState->pFirst) pState->pFirst = pItem;

	char buf[256];
	strncpy(buf, (const char *)stringVal, stringLen);
	buf[stringLen] = 0;
	pItem->setKey((const char *)buf);

	return 1;
}

int
CKLBJsonItem::read_end_map(void * ctx)
{
	JSON_State * pState = (JSON_State *)ctx;

	pState->pCurrent = pState->pParent;
	pState->pParent  = pState->pCurrent->m_pParent;
	pState->pCurrent = NULL;

	return 1;
}

int
CKLBJsonItem::read_start_array(void * ctx, unsigned int /*size*/)
{
	JSON_State * pState = (JSON_State *)ctx;

	if(!pState->pCurrent) {
		CKLBJsonItem * pItem = KLBNEWC(CKLBJsonItem, (pState->pParent));
		pState->pCurrent = pItem;
		if(!pState->pFirst) pState->pFirst = pItem;
	}

	pState->pCurrent->m_type = J_ARRAY;

	pState->pParent  = pState->pCurrent;
	pState->pCurrent = NULL;

	return 1;
}

int
CKLBJsonItem::read_end_array(void * ctx)
{
	JSON_State * pState = (JSON_State *)ctx;

	pState->pCurrent = pState->pParent;
	pState->pParent  = pState->pCurrent->m_pParent;
	pState->pCurrent = NULL;

	return 1;
}
