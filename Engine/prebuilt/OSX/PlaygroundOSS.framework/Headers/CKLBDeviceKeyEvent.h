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
//  CKLBDeviceKeyEvent.h
//

#ifndef CKLBDeviceKeyEvent_h
#define CKLBDeviceKeyEvent_h

#include "CKLBTask.h"
#include "CPFInterface.h"

// #define	LOG_EVENT

typedef struct {
    typedef enum {
        PRESS = 1,
        RELEASE = 2,
        CLICK = 3
    } TYPE;

    TYPE    type;
    int     id;
	void	* locker;	// 入力の使用者
} DEVICE_KEY_ITEM;

class CKLBDeviceKeyEventQueue
{
private:
    CKLBDeviceKeyEventQueue();
    ~CKLBDeviceKeyEventQueue();
public:
    static CKLBDeviceKeyEventQueue& getInstance();

    // キューに入力アイテムを追加(システム側からアイテムを追加する際に使用)
    void addQueue(int keyId, char eventType);
    
    // キューの取得限界を現在の点に固定
    inline void fixLimit() {
        m_read = m_begin;
        m_begin = m_rec;
    }

    // キューの参照点を読み出し先頭に指定する
    void startItem() {
        m_get = m_read;
    }

	inline void setProcessing(bool process) {
		m_bDoingProcess = process;
	}
    
    // キューのアイテムを参照する
    const DEVICE_KEY_ITEM * getItem() {
		const DEVICE_KEY_ITEM * ret;
		if(m_get == m_begin) return 0;  // no further event queued
		ret = m_itemQueue + m_get;
	    m_get = ++m_get % QUEUE_SIZE;
		
        return ret;
    }

private:
	bool			m_bDoingProcess;
    
    int             m_begin;        // 記録先頭
    int             m_rec;          // 記録点
    int             m_read;         // 読み出し先頭
    int             m_get;          // 取得点
    
    enum {
        QUEUE_SIZE = 64
    };
    
    DEVICE_KEY_ITEM    m_itemQueue[ QUEUE_SIZE ];
};

/*!
* \class CKLBDeviceKeyEvent
* \brief Touch Pad Events handler class
* 
* CKLBDeviceKeyEvent is similar to CKLBOSCtrlEvent, but only handles Touch Pad events.
* It owns a queue of Touch Pad events.
* This task is instanciated once when the game starts.
*/
class CKLBDeviceKeyEvent : public CKLBTask
{
private:
    CKLBDeviceKeyEvent();
    virtual ~CKLBDeviceKeyEvent();

	bool onPause(bool bPause);

public:
    static CKLBDeviceKeyEvent * create();

    void execute(u32 deltaT);
    void die();

	u32 getClassID();
};


#endif
