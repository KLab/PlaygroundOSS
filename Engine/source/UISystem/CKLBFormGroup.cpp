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
#include "CKLBFormGroup.h"


CKLBFormGroup::CKLBFormGroup() : m_begin(NULL), m_end(NULL) {}
CKLBFormGroup::~CKLBFormGroup()
{
	release();
}

CKLBFormGroup&
CKLBFormGroup::getInstance()
{
	static CKLBFormGroup instance;
	return instance;
}

void
CKLBFormGroup::release()
{
	GROUP * pGrp = m_begin;

	while(pGrp) {
		GROUP * pNxt = pGrp->next;

		SFormCtrlList * pCtrl = pGrp->begin;
		while(pCtrl) {
			SFormCtrlList * pCtrlNext = pCtrl->pGrpNext;
			delForm(pCtrl);
			pCtrl = pCtrlNext;
		}
		pGrp = pNxt;
	}
}


bool
CKLBFormGroup::addForm(SFormCtrlList * list, const char * group_name)
{
	// 指定されたコントロールリストがすでにどこかのグループに属していれば、一旦除外する
	delForm(list);

	// 新たに所属させるべきグループを得る。
	GROUP * pGrp = createGroup(group_name);
	if(!pGrp) return false;

	// リストをグループに所属させる
	list->pGroup = (void *)pGrp;
	list->pGrpPrev = pGrp->end;
	list->pGrpNext = NULL;

	if(list->pGrpPrev) {
		list->pGrpPrev->pGrpNext = list;
	} else {
		pGrp->begin = list;
	}
	pGrp->end = list;

	return true;
}

bool
CKLBFormGroup::delForm(SFormCtrlList * list)
{
	GROUP * pGrp = (GROUP *)list->pGroup;
	if(!pGrp) return true;

	if(pGrp->worker == list && pGrp->working) {
		pGrp->working = false;
	}
	// フォームを完全にグループから除外する
	if(list->pGrpPrev) {
		list->pGrpPrev->pGrpNext = list->pGrpNext;
	} else {
		pGrp->begin = list->pGrpNext;
	}
	if(list->pGrpNext) {
		list->pGrpNext->pGrpPrev = list->pGrpPrev;
	} else {
		pGrp->end = list->pGrpPrev;
	}
	list->pGrpNext = NULL;
	list->pGrpPrev = NULL;
	list->pGroup = NULL;

	// 結果としてグループに所属するフォームが無くなることがあるので、
	// その場合はグループそのものを削除する
	checkGroup(pGrp);
	return true;
}

// 既存のグループから指定された名称のものを探す。
// なければ 0(NULL)を返す。
CKLBFormGroup::GROUP *
CKLBFormGroup::searchGroup(const char * group_name)
{
	GROUP * pGrp = m_begin;
	while(pGrp) {
		if(!CKLBUtility::safe_strcmp(pGrp->name, group_name)) return pGrp;
		pGrp = pGrp->next;
	}
	return NULL;
}

// 指定された名称のグループが無ければ生成する。
// 既に存在すれば既存のポインタを返す。
CKLBFormGroup::GROUP *
CKLBFormGroup::createGroup(const char * group_name)
{
	GROUP * pGrp = searchGroup(group_name);
	if(pGrp) return pGrp;	// 既にある場合は流用する

	pGrp = KLBNEW(GROUP);
	if(!pGrp) return NULL;

	pGrp->prev = m_end;
	pGrp->next = NULL;

	if(m_begin) {
		m_end->next = pGrp;
	} else {
		m_begin = pGrp;
	}
	m_end = pGrp;

	pGrp->name = CKLBUtility::copyString(group_name);
	pGrp->exclusive = true;
	pGrp->begin = NULL;
	pGrp->end = NULL;

	return pGrp;
}

void
CKLBFormGroup::checkGroup(GROUP * pGrp)
{
	// 登録されたフォームが一つもなければ、このグループ自体を削除する。
	if(pGrp->begin || pGrp->end) return;

	KLBDELETEA(pGrp->name);
	if(pGrp->prev) {
		pGrp->prev->next = pGrp->next;
	} else {
		m_begin = pGrp->next;
	}
	if(pGrp->next) {
		pGrp->next->prev = pGrp->prev;
	} else {
		m_end = pGrp->prev;
	}
	KLBDELETE(pGrp);
}
