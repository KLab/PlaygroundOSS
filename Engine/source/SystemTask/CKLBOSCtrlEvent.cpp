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
//  CKLBOSCtrlEvent.cpp
//  GameEngine
//
//
#include "BaseType.h"
#include "CKLBOSCtrlEvent.h"

CKLBOSCtrlQueue::CKLBOSCtrlQueue()
: m_begin(0), m_read(0), m_rec(0), m_get(0), m_optIdx(0) {}
CKLBOSCtrlQueue::~CKLBOSCtrlQueue() {}

CKLBOSCtrlQueue&
CKLBOSCtrlQueue::getInstance() {
    static CKLBOSCtrlQueue instance;
    return instance;
}

void *
CKLBOSCtrlQueue::allocData(u32 size, void * pData, u32& retsize)
{
	klb_assert((m_optData[m_optIdx].topidx + size) < MAX_DATALEN, "OSEvent queue data buffer overflow.");

	char * dataTop = m_optData[m_optIdx].strbuf + m_optData[m_optIdx].topidx;
	void * data = dataTop;
	memcpy(dataTop, pData, (size_t)size);
	retsize = size;
    m_optData[m_optIdx].topidx += size;
	return data;
}

void
CKLBOSCtrlQueue::addQueue(IClientRequest::EVENT_TYPE type, IWidget * pWidget,
							u32 datasize1, void * pData1, u32 datasize2, void * pData2)
{
	// 一つ手前なので記録上限と看做す
	int next = (m_rec+1);
	if (next >= MAX_EVENT) { next = 0; }

	if (next == m_read) return;

	// datasize が 1以上のときは指定されたサイズを確保し、pDataからそのサイズをコピーする
	m_ctrl[m_rec].type = type;
	m_ctrl[m_rec].widget = pWidget;

	m_ctrl[m_rec].size1 = 0;
	m_ctrl[m_rec].data1 = NULL;

	m_ctrl[m_rec].size2 = 0;
	m_ctrl[m_rec].data2 = NULL;

	// オプションデータは最大2種
    if(datasize1 > 0 && pData1) m_ctrl[m_rec].data1 = allocData(datasize1, pData1, m_ctrl[m_rec].size1);
    if(datasize2 > 0 && pData2) m_ctrl[m_rec].data2 = allocData(datasize2, pData2, m_ctrl[m_rec].size2);

	m_rec = next;
}


CKLBOSCtrlEvent::CKLBOSCtrlEvent() : CKLBTask(){}
CKLBOSCtrlEvent::~CKLBOSCtrlEvent() {}

bool
CKLBOSCtrlEvent::onPause(bool /*bPause*/)
{
	return false;
}

CKLBOSCtrlEvent *
CKLBOSCtrlEvent::create()
{
    CKLBOSCtrlEvent * pTask = KLBNEW(CKLBOSCtrlEvent);
	if (pTask) {
		pTask->regist(NULL, P_INPUT);    // 入力タスクは必ず入力フェーズに指定する。
	}
    return pTask;
}

void
CKLBOSCtrlEvent::execute(u32)
{
    // そのフレームでどこからどこまでを取得できるか決定
    CKLBOSCtrlQueue::getInstance().fixLimit();
}

void
CKLBOSCtrlEvent::die() {}

u32
CKLBOSCtrlEvent::getClassID()
{
	return CLS_KLBTASKOSCTRLEVENT;
}
