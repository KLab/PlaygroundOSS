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
//  CKLBTouchPad.cpp
//

#include "CKLBTouchPad.h"
#include "CKLBDrawTask.h"

CKLBTouchPadQueue::CKLBTouchPadQueue()
	: m_begin(0), m_read(0), m_rec(0), m_get(0), m_bDoingProcess(false), m_ignoreOutScreen(false), m_maskIgnoreFinger(0)
{
    float matrix[6] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    setConvertMatrix(matrix);
}
CKLBTouchPadQueue::~CKLBTouchPadQueue() {}

CKLBTouchPadQueue&
CKLBTouchPadQueue::getInstance() {
    static CKLBTouchPadQueue instance;
    return instance;
}

void
CKLBTouchPadQueue::addQueue(int id, IClientRequest::INPUT_TYPE gtype, int x, int y)
{
	int next = m_rec+1;
	if (next >= QUEUE_SIZE) { next = 0; }

    // 一つ手前なので記録上限と看做す
    if(next == m_read) return;

    PAD_ITEM::TYPE type = (PAD_ITEM::TYPE)gtype;

    m_itemQueue[m_rec].id = id;
    m_itemQueue[m_rec].type = type;
	int xp = (int)(m_matrix[0] * x + m_matrix[3] * y + m_matrix[2]);
	int yp = (int)(m_matrix[1] * x + m_matrix[4] * y + m_matrix[5]);
	m_itemQueue[m_rec].locker = 0;

	if (m_ignoreOutScreen) {
		CKLBDrawResource& draw = CKLBDrawResource::getInstance();
		bool outsideScreen = (xp < 0) || (yp < 0) || (xp >= draw.width()) || (yp >= draw.height());

		switch (type) {
		case PAD_ITEM::TAP:
			if (outsideScreen) {
				m_maskIgnoreFinger |= 1<<id;
				next = m_rec; // Cancel current event.
			}
			break;
		case PAD_ITEM::DRAG:
			if (m_maskIgnoreFinger & (1<<id)) {
				next = m_rec; // Cancel drag event
			} else {
				if (xp < 0) {
					xp = 0;
				}
				if (xp >= draw.width()) {
					xp = draw.width() - 1;
				}
				if (yp < 0) {
					yp = 0;
				}
				if (yp >= draw.height()) {
					yp = draw.height() - 1;
				}
			}
			break;
		case PAD_ITEM::CANCEL:
		case PAD_ITEM::RELEASE:
			if (m_maskIgnoreFinger & (1<<id)) {
				next = m_rec; // Cancel release event and remove the flag.
			} else {
				if (xp < 0) {
					xp = 0;
				}
				if (xp >= draw.width()) {
					xp = draw.width() - 1;
				}
				if (yp < 0) {
					yp = 0;
				}
				if (yp >= draw.height()) {
					yp = draw.height() - 1;
				}
			}
			m_maskIgnoreFinger &= ~(1<<id);
			break;
		}
	}

	m_itemQueue[m_rec].x = xp;
    m_itemQueue[m_rec].y = yp;

#ifdef LOG_EVENT
	if (m_bDoingProcess) {
		DEBUG_PRINT("Event1:%i,%i,%i,%i", id, type, m_itemQueue[m_rec].x, m_itemQueue[m_rec].y);
	} else {
		DEBUG_PRINT("Event0:%i,%i,%i,%i", id, type, m_itemQueue[m_rec].x, m_itemQueue[m_rec].y);
	}
#endif
    m_rec = next;
}

void
CKLBTouchPadQueue::setConvertMatrix(float *matrix)
{
    int i;
    for(i = 0; i < 6; i++) m_matrix[i] = matrix[i];
}


CKLBTouchPad::CKLBTouchPad() : CKLBTask() {}
CKLBTouchPad::~CKLBTouchPad() {}

bool
CKLBTouchPad::onPause(bool /*bPause*/)
{
	return false;
}

CKLBTouchPad *
CKLBTouchPad::create()
{
    CKLBTouchPad * pTask = KLBNEW(CKLBTouchPad);
	if (pTask) {
		pTask->regist(NULL, P_INPUT);    // 入力タスクは必ず入力フェーズに指定する。
	}
    return pTask;
}

void
CKLBTouchPad::execute(u32)
{
    // そのフレームでどこからどこまでを取得できるか決定
    CKLBTouchPadQueue::getInstance().fixLimit();
}

void
CKLBTouchPad::die() {}

u32
CKLBTouchPad::getClassID()
{
	return CLS_KLBTASKTOUCHPAD;
}
