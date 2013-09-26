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
#include "CKLBModalStack.h"
;
CKLBModalStack * CKLBModalStack::ms_begin = 0;
CKLBModalStack * CKLBModalStack::ms_end   = 0;

CKLBModalStack::CKLBModalStack(bool bModal, bool bUrgent)
	: m_bEnable(true), m_bModal(bModal), m_bUrgent(bUrgent), m_prev(0), m_next(0)
{
	if(m_bUrgent) m_bModal = true;
}

CKLBModalStack::~CKLBModalStack()
{
	remove();
}

void
CKLBModalStack::push()
{
	// 既にスタック上にあれば一旦removeする
	if(m_prev || m_next || ms_begin == this || ms_end == this) remove();

	// 自身をスタックの上に積む。ただし、
	// bUrgent = true は最上位に、
	// そうでないものは bUrgent = true のものの下に
	// 積まれる。
    CKLBModalStack * begin = ms_begin;
	while(begin && begin->m_bUrgent) begin = begin->m_next;

	m_prev = (begin) ? begin->m_prev : 0;
	if(m_prev) {
		m_prev->m_next = this;
	} else {
		ms_begin = this;
	}
	m_next = begin;
	if(m_next) {
		m_next->m_prev = this;
	} else {
		ms_end = this;
	}

	// モーダルフォームのスタックであれば、
	// 自分の先に積まれていたすべてのフォームを disableにする
	if(m_bModal) {
		CKLBModalStack * pStack = m_next;
		while(pStack) {
			pStack->setEnable(false);
			pStack = pStack->m_next;
		}
	}

	// 自分自身は enable にする
	m_bEnable = true;
}

void
CKLBModalStack::pop()
{
	remove();
}

void
CKLBModalStack::remove()
{
	// 取り除かれようとしている自分が modal であり、
	// なおかつ自分より上にモーダルのタスクが無ければ、自身より下にあり、
	// 次のmodalであるフォームまでを enable にする
	if(m_bModal) {
		// 自分より上にmodalのタスクがあるか確認する
		bool existModal = false;
		CKLBModalStack * pStack = m_prev;
		while(pStack) {
			if(pStack->isModal()) existModal = true;
			pStack = pStack->m_prev;
		}
		// existModal がfalseならば、自身がもっとも上に積まれているmodalコントロールであるため、
		// 自身より下にある次の modalコントロールが見つかるまでのコントロールをすべて enable にする
		if(!existModal) {
			pStack = m_next;
			while(pStack) {
				pStack->setEnable(true);
				if(pStack->isModal()) break;
				pStack = pStack->m_next;
			}
		}
	}

	// 自身をスタックから取り除く
	if(m_prev) {
		m_prev->m_next = m_next;
	} else {
		if(ms_begin == this) ms_begin = m_next;
	}
	if(m_next) {
		m_next->m_prev = m_prev;
	} else {
		if(ms_end == this) ms_end = m_prev;
	}
	m_prev = m_next = 0;

	// 自分自身は disable にする
	m_bEnable = false;
}
