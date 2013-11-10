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
//  CKLBTouchPad.h
//

#ifndef CKLBTouchPad_h
#define CKLBTouchPad_h

#include "CKLBTask.h"
#include "CPFInterface.h"

// #define	LOG_EVENT

typedef struct {
    typedef enum {
        TAP,
        DRAG,
        RELEASE,
		CANCEL
    } TYPE;

    TYPE    type;
    int     id;     // 入力点ID(multi touch 対応)
    int     x;
    int     y;
	void	* locker;	// 入力の使用者
} PAD_ITEM;

// タッチパッドキュークラス。
// 基本的に、本体を正位置に構えた状態での座標のみを提供する。
// 本体を回転させて使う際の座標変換は、各ゲームの責任において行うものとする。
class CKLBTouchPadQueue
{
private:
    CKLBTouchPadQueue();
    ~CKLBTouchPadQueue();
public:
    static CKLBTouchPadQueue& getInstance();

    // キューに入力アイテムを追加(システム側からアイテムを追加する際に使用)
    void addQueue(int id, IClientRequest::INPUT_TYPE type, int x, int y);
    
    // 座標変換マトリクスを設定する
    void setConvertMatrix(float * matrix);
    
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
    const PAD_ITEM * getItem(bool bAll = false) {
		const PAD_ITEM * ret;
		do {
			if(m_get == m_begin) return 0;  // これ以上読んではいけない
			ret = m_itemQueue + m_get;
	        m_get = ++m_get % QUEUE_SIZE;
		} while(!bAll && ret->locker);	// 既に使用済アイテムであれば次を読む(bAll == false の場合)
		
		// bAll が true の場合、マークされたイベントであっても取得する。
        return ret;
    }

	// アイテムに使用済みマークをつける。
	inline bool useItem(const PAD_ITEM * item, void * pUser) {
		if(item->locker) return false;
		PAD_ITEM * val = (PAD_ITEM *)item;
		val->locker = pUser;
		return true;
	}

	void setIgnoreOutside(bool ignore) {
		m_ignoreOutScreen	= ignore;
		m_maskIgnoreFinger	= 0; // Reset all fingers.
	}

private:
	bool			m_bDoingProcess;
    float           m_matrix[6];    // 座標変換マトリクス
    
    int             m_begin;        // 記録先頭
    int             m_rec;          // 記録点
    int             m_read;         // 読み出し先頭
    int             m_get;          // 取得点
	u32				m_maskIgnoreFinger;
	bool			m_ignoreOutScreen;
    
    enum {
        QUEUE_SIZE = 1024
    };
    
    PAD_ITEM    m_itemQueue[ QUEUE_SIZE ];
};

/*!
* \class CKLBTouchPad
* \brief Touch Pad Events handler class
* 
* CKLBTouchPad is similar to CKLBOSCtrlEvent, but only handles Touch Pad events.
* It owns a queue of Touch Pad events.
* This task is instanciated once when the game starts.
*/
class CKLBTouchPad : public CKLBTask
{
private:
    CKLBTouchPad();
    virtual ~CKLBTouchPad();

	bool onPause(bool bPause);

public:
    static CKLBTouchPad * create();

    void execute(u32 deltaT);
    void die();

	u32 getClassID();
};


#endif
