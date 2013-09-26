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
//  CKLBDeviceKeyEvent.cpp
//

#include "CKLBDeviceKeyEvent.h"
#include "CKLBDrawTask.h"

CKLBDeviceKeyEventQueue::CKLBDeviceKeyEventQueue()
	: m_begin(0), m_read(0), m_rec(0), m_get(0), m_bDoingProcess(false)
{
}
CKLBDeviceKeyEventQueue::~CKLBDeviceKeyEventQueue() {}

CKLBDeviceKeyEventQueue&
CKLBDeviceKeyEventQueue::getInstance() {
    static CKLBDeviceKeyEventQueue instance;
    return instance;
}

void
CKLBDeviceKeyEventQueue::addQueue(int keyId, char eventType)
{
	int next = m_rec+1;
	if (next >= QUEUE_SIZE) { next = 0; }

    // judge quque hit its limit (drop event)
    if(next == m_read) return;

    DEVICE_KEY_ITEM::TYPE type = (DEVICE_KEY_ITEM::TYPE)eventType;

    m_itemQueue[m_rec].id = keyId;
    m_itemQueue[m_rec].type = type;

    m_rec = next;
}

CKLBDeviceKeyEvent::CKLBDeviceKeyEvent() : CKLBTask() {}
CKLBDeviceKeyEvent::~CKLBDeviceKeyEvent() {}

bool
CKLBDeviceKeyEvent::onPause(bool /*bPause*/)
{
	return false;
}

CKLBDeviceKeyEvent *
CKLBDeviceKeyEvent::create()
{
    CKLBDeviceKeyEvent * pTask = KLBNEW(CKLBDeviceKeyEvent);
	if (pTask) {
		pTask->regist(0, P_INPUT);    // 入力タスクは必ず入力フェーズに指定する。
	}
    return pTask;
}

void
CKLBDeviceKeyEvent::execute(u32)
{
    // そのフレームでどこからどこまでを取得できるか決定
    CKLBDeviceKeyEventQueue::getInstance().fixLimit();
}

void
CKLBDeviceKeyEvent::die() {}

u32
CKLBDeviceKeyEvent::getClassID()
{
	return CLS_KLBTASKTOUCHPAD;
}
