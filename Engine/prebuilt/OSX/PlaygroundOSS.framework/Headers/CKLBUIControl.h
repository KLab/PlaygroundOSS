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
#ifndef CKLBUIControl_h
#define CKLBUIControl_h

#include "CKLBLuaTask.h"
#include "CKLBModalStack.h"
#include "CKLBUISystem.h"
#include "CKLBFormGroup.h"

/*!
* \class CKLBUIControl
* \brief UI Control Task class.
* 
* CKLBUIControl is a high level Touch Pad Events handler.
* Events (Tap, Drag, Release) are interpreted into higher level events such as 
* Click, Double Click, Drag, Long Tap, Pinch).
* It provides a few callbacks that are called when some actions are processed.
* Events can be masked to select only the ones you want.
*/
class CKLBUIControl : public CKLBLuaTask
{
	friend class CKLBTaskFactory<CKLBUIControl>;
private:
	CKLBUIControl();
	virtual ~CKLBUIControl();

	bool init(CKLBTask* pTask, const char* onClick, const char* onDrag);
public:
	static CKLBUIControl* create(CKLBTask* pParentTask, const char* onClick, const char* onDrag);

	u32 getClassID();

	bool initScript  (CLuaState& lua);
	int commandScript(CLuaState& lua);

	inline void setMask			(u16 mask)					{ m_callbackMask = mask;				}
	inline void setOnPinch		(const char* onPinch)		{ setStrC(m_onPinch, onPinch);			}
	inline void setOnDblClick	(const char* onDblClick)	{ setStrC(m_onDblClick, onDblClick);	}
	inline void setOnLongTap	(const char* onLongTap)		{ setStrC(m_onLongTap, onLongTap);		}
	inline void setOnEventRaw	(const char* onRawEvent)	{ setStrC(m_onEventRaw, onRawEvent);	}
	inline bool setGroup		(const char* group_name)	{
		CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();
		return fGrp.addForm(&m_ctrlList, group_name);
	}

	inline void lock            (bool lock_mode)            {
		CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();
		fGrp.setWorking(&m_ctrlList, lock_mode, this);
	}

	void execute(u32 deltaT);
	void die    ();

	enum {
		MASK_CLICK     = 0x0001,	// クリックcallbackを禁止する
		MASK_DRAG      = 0x0002,	// ドラッグcallbackを禁止する
		MASK_PINCH     = 0x0004,	// ピンチイン/アウト/ローテーションcallbackを禁止する
		MASK_DBLCLICK  = 0x0008,	// ダブルクリックcallbackを禁止する
		MASK_LONGTAP   = 0x0010		// ロングタップcallbackを禁止する
	};
private:
	inline void setGetAll(bool b) { m_bAll = b; }

	void calc_distance(float * dist, float * angle);

	enum {
		POINT_NUMS = 2,
        CALIB = 16,
        CLICKTIME = 300
	};


	// 操作が始まったとき、タップされた位置(第一ポイントのみ)
	s32			m_tapX;
	s32			m_tapY;

	// タップ位置からドラッグされた差分位置(ドラッグ操作用)
	s32			m_moveX;
	s32			m_moveY;

    // タップ時から動いた最大距離の絶対値
    s32         m_maxX;
    s32         m_maxY;

	// それぞれの操作点座標
	s32			m_posX[ POINT_NUMS ];
	s32			m_posY[ POINT_NUMS ];
	float		m_orgLen;	// 最初に2点タップされた時点の、2点間の距離
    float       m_orgAngle; // 最初に2点タップされた時点の、2点間を結ぶ線分の角度
	// 操作中フラグ
	// TAPでtrue
	// DRAG/RELEASEが来てもtrueでなければ自身への操作として受け付けない
	// RELEASE時にfalseになる。
	bool		m_bAll;
	bool		m_bControl;	// 何らかの操作中にtrueとなる
	int			m_id[ POINT_NUMS ];	// 操作ID(マルチタッチ用)2点までを認識する
	bool		m_f_move[ POINT_NUMS ];	// 閾値以上移動したらtrue
	int			m_tcnt[ POINT_NUMS ];
	int			m_usePt;	// 操作に使用しているポイントの数(最大2)
    
    bool        m_bClick;   // クリック成立
    s32         m_clickX;   // クリック成立時の座標
    s32         m_clickY;   // クリック成立時の座標
    u32         m_timeCnt;  // クリック成立からの経過時間
    
	SFormCtrlList	m_ctrlList;		// UI_Form / UI_List と同様のグループ制御を行うためのメンバ
	CKLBModalStack	m_modalStack;
	bool			m_bModalEnable;

	int				m_lastClick;	// 最後にクリックイベントを発生させたフレーム

	u16				m_callbackMask;	// コールバックマスク

	const char	*	m_onClick;      // クリック時のコールバック
	const char	*	m_onDrag;       // ドラッグ自のコールバック
	const char	*	m_onPinch;      // ピンチ操作のコールバック
    const char  *   m_onDblClick;   // ダブルクリック時のコールバック
	const char	*	m_onLongTap;	// ロングタップ(長押し)時のコールバック
	const char  *   m_onEventRaw;	// Low Level Raw event.
};

#endif // CKLBMapControl_h
