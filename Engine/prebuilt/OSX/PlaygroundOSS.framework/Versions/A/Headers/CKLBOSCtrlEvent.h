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
//  CKLBOSCtrlEvent.h
//  GameEngine
//
//

#ifndef CKLBOSCtrlEvent_h
#define CKLBOSCtrlEvent_h

#include "CKLBTask.h"
#include "CPFInterface.h"
#include "OSWidget.h"

struct OSCTRL {
	IClientRequest::EVENT_TYPE		type;
	IWidget						*	widget;

	u32								size1;
	void						*	data1;

	u32								size2;
	void						*	data2;
};

class CKLBOSCtrlQueue
{
private:
    CKLBOSCtrlQueue();
    virtual ~CKLBOSCtrlQueue();
public:
    static CKLBOSCtrlQueue& getInstance();

    void addQueue(IClientRequest::EVENT_TYPE type, IWidget * pWidget,
					u32 datasize1 = 0, void * pData1 = NULL,
					u32 datasize2 = 0, void * pData2 = NULL);

    // キューの取得限界を現在の点に固定
    inline void fixLimit() {
        m_read  = m_begin;
        m_begin = m_rec;
		m_optIdx = 1 - m_optIdx;			// 書き込み側 index の表裏を入れ替える
		m_optData[m_optIdx].topidx = 0;		// 書き込み先頭を初期化
    }
    
    // キューの参照点を読み出し先頭に指定する
    void startItem() {
        m_get = m_read;
    }
    
    // 特定のWidgetに関連したキューのアイテムを取得する
    const OSCTRL * getItem(IWidget * pWidget) {
		const OSCTRL * ret;
		do {
			if(m_get == m_begin) return 0;  // これ以上読んではいけない
			ret = m_ctrl + m_get;
	        m_get = ++m_get % MAX_EVENT;
		} while(ret->widget != pWidget);	// 異なるWidgetに対するものであればスキップする
        return ret;
    }

private:
	void * allocData(u32 size, void * pData, u32& retsize);

    enum {
        MAX_EVENT   = 1024,
		MAX_DATALEN = 4096 * 32,
    };
    int             m_begin;        // 記録先頭
    int             m_rec;          // 記録点
    int             m_read;         // 読み出し先頭
    int             m_get;          // 取得点
    

    OSCTRL          m_ctrl[ MAX_EVENT ];

	struct OPTDATA {
		int		topidx;
		char	strbuf[ MAX_DATALEN ];
	};

	int				m_optIdx;
	OPTDATA			m_optData[2];
};


/*!
* \class CKLBOSCtrlEvent
* \brief OS Control Event Task class.
* 
* CKLBOSCtrlEvent is the class in charge of handling the OS events.
* Each frame it allows some events to be visible for the Engine.
*/
class CKLBOSCtrlEvent : public CKLBTask
{
private:
    CKLBOSCtrlEvent();
    virtual ~CKLBOSCtrlEvent();
    
	bool onPause(bool bPause);
    
public:
    static CKLBOSCtrlEvent * create();
    
    void execute(u32 deltaT);
    void die    ();
    
	u32 getClassID();
};


#endif // CKLBOSCtrlEvent_h

