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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CWin32KeyChain.h"

CWin32KeyChain::CWin32KeyChain() : m_begin(NULL), m_end(NULL) {}
CWin32KeyChain::~CWin32KeyChain()
{
	clean();
}

void
CWin32KeyChain::clean()
{
	// 値を保持するために確保していた領域をすべて破棄
	SERVICE * pServ = m_begin;
	while(pServ) {
		SERVICE * pNext = pServ->next;

		KEYVALUE * pVal = pServ->begin;
		while(pVal) {
			KEYVALUE * next = pVal->next;

			delete pVal->key;
			delete pVal->value;
			delete pVal;

			pVal = next;
		}

		delete pServ;
		pServ = pNext;
	}
	m_begin = NULL;
	m_end   = NULL;
}

const char *
CWin32KeyChain::getValue(const char * service_name, const char * key)
{
	// 指定された名称のサービスを検索
	SERVICE * pServ = m_begin;
	while(pServ) {
        if(!strcmp(pServ->service_name, service_name)) { break; }
		pServ = pServ->next;
	}
    if(!pServ) { return NULL; }

	// サービスがあれば、その中を key で検索
	KEYVALUE * pKey = pServ->begin;
	while(pKey) {
        if(!strcmp(pKey->key, key)) { break; }
		pKey = pKey->next;
	}
    if(!pKey) { return NULL; }

	return pKey->value;
}

bool
CWin32KeyChain::setValue(const char * service_name, const char * key, const char * value)
{
	// 指定された名称のサービスを検索
	SERVICE * pServ = m_begin;
	while(pServ) {
        if(!strcmp(pServ->service_name, service_name)) { break; }
		pServ = pServ->next;
	}
	if(!pServ) {
		// ない場合はこの場で作る。
		pServ = new SERVICE;
		char * name = new char [ strlen(service_name) + 1 ];
		strcpy(name, service_name);
		pServ->service_name = (const char *)name;
		pServ->begin        = pServ->end = NULL;
		pServ->next         = NULL;
		pServ->prev         = m_end;
		if(pServ->prev) {
			pServ->prev->next = pServ;
		} else {
			m_begin = pServ;
		}
		m_end = pServ;
	}

	// 該当するサービスの中で、指定されたkeyを検索する
	KEYVALUE * pKey = pServ->begin;
	while(pKey) {
        if(!strcmp(pKey->key, key)) { break; }
		pKey = pKey->next;
	}
	// 該当するキーが無ければ作成する
	if(!pKey) {
		pKey = new KEYVALUE;
		char * keystr = new char [ strlen(key) + 1 ];
		strcpy(keystr, key);
		pKey->key   = keystr;
		pKey->value = NULL;
		pKey->next  = NULL;
		pKey->prev  = pServ->end;
		if(pKey->prev) {
			pKey->prev->next = pKey;
		} else {
			pServ->begin = pKey;
		}
		pServ->end = pKey;
	}

	delete pKey->value;

	// 値を設定する
	char * valstr = new char [ strlen(value) + 1 ];
	strcpy(valstr, value);
	pKey->value = valstr;

	return true;
}

bool
CWin32KeyChain::delValue(const char * service_name, const char * key)
{
	// 指定された名称のサービスを検索
	SERVICE * pServ = m_begin;
	while(pServ) {
        if(!strcmp(pServ->service_name, service_name)) { break; }
		pServ = pServ->next;
	}
	// ない場合は指定のキーもあるわけがないのでそのまま終了。
	if(!pServ) return true;

	// 該当するサービスの中で、指定されたkeyを検索する
	KEYVALUE * pKey = pServ->begin;
	while(pKey) {
        if(!strcmp(pKey->key, key)) { break; }
		pKey = pKey->next;
	}
	// 該当するキーが無ければ目的は最初から達成されているのでそのまま終了
    if(!pKey) { return true; }

	// value 領域を破棄
	delete pKey->value;

	// key領域を破棄
	if(pKey->prev) {
		pKey->prev->next = pKey->next;
	} else {
		pServ->begin = pKey->next;
	}
	if(pKey->next) {
		pKey->next->prev = pKey->prev;
	} else {
		pServ->end = pKey->prev;
	}
	delete [] pKey->key;
	delete pKey;	// key領域そのものを削除する。

	// keyが属していた service が持つ key が一つもない状態になっていたら、
	// service を削除する。
	if(!pServ->begin && !pServ->end) {
		if(pServ->prev) {
			pServ->prev->next = pServ->next;
		} else {
			m_begin = pServ->prev;
		}
		if(pServ->next) {
			pServ->next->prev = pServ->prev;
		} else {
			m_end = pServ->prev;
		}
		delete [] pServ->service_name;
		delete pServ;
	}

	return true;
}


bool
CWin32KeyChain::loadKeyChain(const char * filename)
{
	FILE * rfp;
	rfp = fopen(filename, "r");
	if(!rfp) return false;

	clean();

	char line[4096];
	while(fgets(line, 4096, rfp)) {
		// 行をバラし、service_name : key : value に分割する
		char * ptr = line;
		const char * service_name = ptr;
		ptr = strstr(ptr, "::");
        if(!ptr) { goto failed_end; }

		*ptr = 0;
		ptr += 2;
		const char * key = ptr;

		ptr = strstr(ptr, "::");
		if(!ptr) goto failed_end;

		*ptr = 0;
		ptr += 2;
		const char * value = ptr;

		ptr = strstr(ptr, "\n");
		if(ptr) *ptr = 0;

		// バラした値を登録
		bool result = setValue(service_name, key, value);
        if(!result) { goto failed_end; }
	}
	fclose(rfp);

	return true;

failed_end:
	fclose(rfp);
	clean();
	return false;
}

bool
CWin32KeyChain::saveKeyChain(const char * filename)
{
	FILE * wfp;
	wfp = fopen(filename, "w");
    if(!wfp) { return false; }

	SERVICE * pServ = m_begin;
	while(pServ) {
		KEYVALUE * pKey = pServ->begin;
		while(pKey) {
			fprintf(wfp, "%s::%s::%s\n", pServ->service_name, pKey->key, pKey->value);
			pKey = pKey->next;
		}
		pServ = pServ->next;
	}

	fclose(wfp);

	return true;
}
