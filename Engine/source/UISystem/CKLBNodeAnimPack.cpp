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
#include "CKLBNodeAnimPack.h"
#include "CKLBUtility.h"
#include "CKLBLuaEnv.h"
;
const char * CKLBNodeAnimPack::ms_labelEnter = "enter";
const char * CKLBNodeAnimPack::ms_labelLeave = "leave";

CKLBNodeAnimPack::CKLBNodeAnimPack() 
: m_begin       (NULL)
, m_end         (NULL)
, m_callback    (NULL)
, m_enterBlend  (false) 
{
}

CKLBNodeAnimPack::~CKLBNodeAnimPack()
{
	// アニメーション監視領域が残っていたら破棄する
	ANIMCOUNT * anim = m_begin;
	while(anim) {
		ANIMCOUNT * next = anim->next;
		KLBDELETEA(anim->name);
		KLBDELETE(anim);
		anim = next;
	}
	// 2012.11.27  解放漏れがあったので修正
	if( m_callback ) {
		KLBDELETEA(m_callback);
		m_callback = NULL;
	}
}

bool
CKLBNodeAnimPack::setCallback(const char * callback)
{
	const char * str = NULL;
	if(callback) {
		str = CKLBUtility::copyString(callback);
        if(!str) { return false; }
	}
    if(m_callback) { KLBDELETEA(m_callback); }
	m_callback = str;
	return true;
}

bool
CKLBNodeAnimPack::skipAnim(CKLBNode * pNode, const char * name)
{
	pNode->skipAnimation(name);
	return true;
}

bool
CKLBNodeAnimPack::kickAnim(CKLBNode * pNode, const char * name, bool doBlend, int id, bool kill)
{
	ANIMCOUNT * anim = KLBNEW(ANIMCOUNT);
    if(!anim) { return false; }
	anim->name = CKLBUtility::copyString(name);
	if(!anim->name) {
		KLBDELETE(anim);
		return false;
	}
	// 念のため0クリアする
	anim->count = 0;

	// animation を kick する
	pNode->kickAnimation(name, &anim->count, doBlend);

	// Add to list if only kicked.
	if (anim->count) {
		anim->node = pNode;
		anim->id = id;
		anim->kill = kill;

		// 再生中アニメリストに追加する
		anim->prev = m_end;
		anim->next = NULL;
		if(anim->prev) {
			anim->prev->next = anim;
		} else {
			m_begin = anim;
		}
		m_end = anim;
	} else {
		// Delete Name first.
		KLBDELETEA(anim->name);
		// Then delete animation.
		KLBDELETE(anim);
	}

	return true;
}

void
CKLBNodeAnimPack::watchFinishedAnim(CKLBLuaTask * pTask)
{
	// アニメーションの終了を監視する
	ANIMCOUNT * anim = m_begin;
	while(anim) {
		if(anim->count) {
			// カウンタが残っていればアニメーションは終了していない。
			// 次の監視対象に移る。
			anim = anim->next;
			continue;
		}
		// カウンタが0なので、そのアニメーションは終了したと認識
		// リストからはずす
		if(anim->prev) {
			anim->prev->next = anim->next;
		} else {
			m_begin = anim->next;
		}
		if(anim->next) {
			anim->next->prev = anim->prev;
		} else {
			m_end = anim->prev;
		}

		ANIMCOUNT * next = anim->next;
		const char * name = anim->name;
		int id = anim->id;
		bool bKill = anim->kill;
		KLBDELETE(anim);

		CKLBScriptEnv::getInstance().call_eventNodeAnimPack(m_callback, pTask, name, id);

		// kill が true の時アニメーションが終了したならば指定されたタスクのkill()を呼ぶ
		if(bKill) pTask->kill();
		KLBDELETEA(name);

		anim = next;
	}
}

bool
CKLBNodeAnimPack::kickEnter(CKLBNode * pNode)
{
	bool result = kickAnim(pNode, ms_labelEnter, m_enterBlend);
	m_enterBlend = true;
	return result;
}

bool
CKLBNodeAnimPack::kickLeave(CKLBNode * pNode)
{
	return kickAnim(pNode, ms_labelLeave, true, 0, true);
}

int
CKLBNodeAnimPack::getAnimCounter(const char * name)
{
	u32 cntSum = 0;
	// 現在実行中のアニメーションのなかから該当する名称を持つものを探し、
	// そのリファレンスカウンタ値を返す。
	ANIMCOUNT * anim = m_begin;
	while(anim) {
		cntSum += anim->count;
		// 名前が指定されていて、その名前に合致するカウンタならばその値を返す。
		if(name && !strcmp(anim->name, name)) return anim->count;
		anim = anim->next;
	}
	// 見つからない場合:
	// 名前が指定されていない場合(NULL)は、すべてのカウンタの合計を返す
	// 名前が指定されていた場合は0を返す
	return (!name) ? cntSum : 0;
}
