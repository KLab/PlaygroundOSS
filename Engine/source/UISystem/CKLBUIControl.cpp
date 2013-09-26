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
#include "CKLBUIControl.h"
#include "CKLBTouchPad.h"
#include "CKLBLuaEnv.h"
#include "CKLBScriptEnv.h"
#include "CKLBUtility.h"
#include "CKLBFormGroup.h"
#define _USE_MATH_DEFINES
#include <math.h>
;
// Command Values
enum {
	UI_CONTROL_ON_PINCH,
    UI_CONTROL_ON_DBLCLICK,
	UI_CONTROL_ON_LONGTAP,
	UI_CONTROL_ON_RAWEVENT,

	UI_CONTROL_SET_GROUP,
	UI_CONTROL_LOCK,

	UI_CONTROL_SET_MASK,
	UI_CONTROL_GET_ALL,
};
static IFactory::DEFCMD cmd[] = {
	{ "UI_CONTROL_ON_PINCH",    UI_CONTROL_ON_PINCH },
	{ "UI_CONTROL_ON_DBLCLICK", UI_CONTROL_ON_DBLCLICK },
	{ "UI_CONTROL_ON_LONGTAP",  UI_CONTROL_ON_LONGTAP },
	{ "UI_CONTROL_ON_RAWEVENT",	UI_CONTROL_ON_RAWEVENT },

	{ "UI_CONTROL_SET_GROUP",	UI_CONTROL_SET_GROUP },
	// { "UI_CONTROL_LOCK",		UI_CONTROL_LOCK },
	{ "UI_CONTROL_SET_MASK",	UI_CONTROL_SET_MASK },
	{ "UI_CONTROL_GET_ALL",		UI_CONTROL_GET_ALL },

	{ "CTRLMASK_CLICK",			CKLBUIControl::MASK_CLICK },
	{ "CTRLMASK_DRAG",			CKLBUIControl::MASK_DRAG },
	{ "CTRLMASK_PINCH",			CKLBUIControl::MASK_PINCH },
	{ "CTRLMASK_DBLCLICK",		CKLBUIControl::MASK_DBLCLICK },
	{ "CTRLMASK_LONGTAP",		CKLBUIControl::MASK_LONGTAP },

	{0, 0}
};

static CKLBTaskFactory<CKLBUIControl> factory("UI_Control", CLS_KLBUICONTROL, cmd);

CKLBUIControl::CKLBUIControl()
: CKLBLuaTask   ()
, m_onClick     (NULL)
, m_onDrag      (NULL)
, m_onDblClick  (NULL)
, m_onPinch     (NULL)
, m_onLongTap   (NULL)
, m_onEventRaw  (NULL)
, m_modalStack  (false)
, m_bModalEnable(true)
, m_callbackMask(0)
, m_lastClick   (0)
, m_bAll        (false) 
{
}

CKLBUIControl::~CKLBUIControl() 
{
}

u32
CKLBUIControl::getClassID()
{
	return CLS_KLBUICONTROL;
}

void
CKLBUIControl::calc_distance(float * dist, float * angle)
{
	float x = (float)(m_posX[1] - m_posX[0]);
	float y = (float)(m_posY[1] - m_posY[0]);
	*dist = sqrt(x * x + y * y);		// 2点間の距離
 
    // 正規化し、その線分の角度を得る
    x = x / *dist;
    y = y / *dist;

    *angle = acosf(x);
    if(y < 0.0f) { *angle = 2.0f * M_PI - *angle; }
}

CKLBUIControl* 
CKLBUIControl::create(CKLBTask* pParentTask, const char* onClick, const char* onDrag) {
	CKLBUIControl* pTask = KLBNEW(CKLBUIControl);
    if(!pTask) { return NULL; }

	if(!pTask->init(pParentTask, onClick, onDrag)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool 
CKLBUIControl::init(CKLBTask* /*pTask*/, const char* onClick, const char* onDrag) {
	if(onClick) m_onClick = CKLBUtility::copyString(onClick);
	if(onDrag)  m_onDrag  = CKLBUtility::copyString(onDrag);

	if(!m_onClick || !m_onDrag) {
		KLBDELETEA(m_onClick);
		KLBDELETEA(m_onDrag);
		return false;
	}

    m_bClick    = false;
	m_bControl  = false;
	m_usePt     = 0;

	m_ctrlList.pGroup   = NULL;
	m_ctrlList.pGrpPrev = NULL;
	m_ctrlList.pGrpNext = NULL;

	m_ctrlList.pBegin   = NULL;
	m_ctrlList.next     = NULL;
	m_ctrlList.bEnable  = true;
	m_ctrlList.bExclusive       = false;
	m_ctrlList.bWorking         = false;
	m_ctrlList.pCallbackIF      = NULL;
	m_ctrlList.nativeCallback   = NULL;
	m_ctrlList.pID      = NULL;

	if(regist(0, P_AFTER)) {
		m_modalStack.setModal(false);
		m_modalStack.setEnable(true);
		m_modalStack.push();
		m_bModalEnable = true;
		return true;
	}
	// regist に失敗した場合
	return false;
}

bool
CKLBUIControl::initScript(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc != 2) return false;

	const char * onClick = lua.getString(1);
	const char * onDrag  = lua.getString(2);

	return init(NULL, onClick, onDrag);
}

int
CKLBUIControl::commandScript(CLuaState& lua)
{
	int argc = lua.numArgs();
	if(argc < 2) {
		lua.retBoolean(false);
		return 1;
	}
	int ret = 1;
	int cmd = lua.getInt(2);
	switch(cmd)
	{
	default:
		{
			ret = 1;
			lua.retBoolean(false);
		}
		break;
	case UI_CONTROL_ON_PINCH:
		{
			ret = 1;
			if(argc != 3) {
				lua.retBoolean(false);
				break;
			}
			const char * onPinch = lua.getString(3);
			if(!onPinch) {
				lua.retBoolean(false);
				break;
			}
			m_onPinch = CKLBUtility::copyString(onPinch);
			if(!onPinch) {
				lua.retBoolean(false);
				break;
			}
			lua.retBoolean(true);
		}
		break;
    case UI_CONTROL_ON_DBLCLICK:
		{
			ret = 1;
			if(argc != 3) {
				lua.retBoolean(false);
				break;
			}
			const char * onDblClick = lua.getString(3);
			if(!onDblClick) {
				lua.retBoolean(false);
				break;
			}
			setOnDblClick(onDblClick);
			if(!onDblClick) {
				lua.retBoolean(false);
				break;
			}
			lua.retBoolean(true);
		}
        break;
	case UI_CONTROL_ON_LONGTAP:
		{
			ret = 1;
			if(argc != 3) {
				lua.retBoolean(false);
				break;
			}
			const char * onLongTap = lua.getString(3);
			setOnLongTap(onLongTap);
			if(!onLongTap) {
				lua.retBoolean(false);
				break;
			}
			lua.retBoolean(true);
		}
		break;
	case UI_CONTROL_ON_RAWEVENT:
		{
			ret = 1;
			if(argc != 3) {
				lua.retBoolean(false);
				break;
			}
			const char * onRawEvent = lua.getString(3);
			setOnEventRaw(onRawEvent);
			if(!onRawEvent) {
				lua.retBoolean(false);
				break;
			}
			lua.retBoolean(true);
		}
		break;
	case UI_CONTROL_SET_GROUP:
		{
			bool result = false;
			if(argc == 3) {
				const char * group_name = lua.getString(3);
				ret = setGroup(group_name);
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
		/*
	case UI_CONTROL_LOCK:
		{
			bool result = false;
			if(argc == 3) {
				bool lock_mode = lua.getBool(3);
				lock(lock_mode);
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
		*/
	case UI_CONTROL_SET_MASK:
		{
			bool result = false;
			if(argc == 3) {
				u16 mask = lua.getInt(3);
				m_callbackMask = mask;
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	case UI_CONTROL_GET_ALL:
		{
			bool result = false;
			if(argc == 3) {
				setGetAll(lua.getBool(3));
				result = true;
			}
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	}
	return ret;
}

void
CKLBUIControl::execute(u32 deltaT)
{
	m_bModalEnable = m_modalStack.isEnable();

	if(!m_bModalEnable) {
		// 呼び出したcallback中などにmodal form等が表示されると、
		// その後のexecuteが処理されないことにより、あるtapのreleaseが検知できないことがある。
		// このため、modal状態によって操作をブロックされている間は操作状態を完全にリセットする。
		m_bControl  = false;        // 操作終了
		m_usePt     = 0;            // どちらか一方でもreleaseされたら操作を終了する
		m_bClick    = false;

		return;
	}

	int frameID = CKLBTaskMgr::getInstance().getFrameID();	
	CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();
	CKLBTouchPadQueue& tpq = CKLBTouchPadQueue::getInstance();
	const PAD_ITEM * item;

	if(m_onEventRaw) {
		tpq.startItem();
		// 通知すべきイベントがあるので、Lua配列を生成する。													
		CLuaState& lua = CKLBLuaEnv::getInstance().getState();
		lua.retGlobal(m_onEventRaw);
		lua.tableNew();
		int index = 1;

		while((item = tpq.getItem(m_bAll))) {
			lua.retInt(index);

			lua.tableNew();

			lua.retString("type");
			lua.retInt(item->type);
			lua.tableSet();

			lua.retString("id");
			lua.retInt(item->id);
			lua.tableSet();

			lua.retString("x");
			lua.retDouble(item->x);
			lua.tableSet();

			lua.retString("y");
			lua.retDouble(item->y);
			lua.tableSet();

			lua.tableSet();

			index++;
		}

		// 引数とすべき値は、すでにLuaスタックに積まれている。
		CKLBScriptEnv::getInstance().call_touchPad(m_onEventRaw, this);
	}

	tpq.startItem();
	while((item = tpq.getItem(m_bAll))) {
		switch(item->type)
		{
		case PAD_ITEM::TAP:
			{
				// 操作対象点以上は操作に用いない
				if(m_usePt >= POINT_NUMS) break;

				// 最初の一点目の操作であれば、group の working 状態を確認し、
				// working 状態であれば reject する
                if((m_usePt == 0) && fGrp.isWorking(&m_ctrlList, this)) { break; }
				fGrp.setWorking(&m_ctrlList, true, this);		// working 状態にする

				m_id[m_usePt]       = item->id;
				m_f_move[m_usePt]   = false;
				m_tcnt[m_usePt]     = 0;
				if(m_usePt == 0) {
					m_tapX  = item->x;
					m_tapY  = item->y;
					m_moveX = m_moveY = 0;
                    m_maxX  = m_maxY  = 0;
				}
				m_posX[m_usePt] = item->x;
				m_posY[m_usePt] = item->y;

				// 2点目のタップであれば、1点目との距離と角度を求めておく
				if(m_usePt == 1) {
                    calc_distance(&m_orgLen, &m_orgAngle);
                }
				m_usePt++;
				m_bControl = true;
				tpq.useItem(item, this);	// アイテムに使用済みマークをつける
			}
			break;
		case PAD_ITEM::DRAG:
			{
				// 自身の操作中でなければ、アイテムがあってもそれは自身への操作ではない。
                if(!m_bControl) { break; }

				int pos = -1;
				for(int i = 0; i < m_usePt; i++) {
					if(m_id[i] == item->id) pos = i;
				}
                if(pos < 0) { break; }

				if(m_usePt == 1) {  // 1点のみの操作中
                    if(m_id[0] != item->id) { break; }  // 違うポイントでの操作なら反応しない
					m_moveX = item->x - m_tapX;
					m_moveY = item->y - m_tapY;
                    
                    // 移動量絶対値
                    s32 mvX = (m_moveX < 0) ? -m_moveX : m_moveX;
                    s32 mvY = (m_moveY < 0) ? -m_moveY : m_moveY;
                    
                    // その操作における最大移動距離を記録する
                    if(mvX > m_maxX) { m_maxX = mvX; } 
                    if(mvY > m_maxY) { m_maxY = mvY; }
                    
					tpq.useItem(item, this);

					// onDrag は、その時点での座標値とドラッグ移動量を返す。
                    // 人間の指には遊びがあるので、最大移動距離がしきい値を超えたらドラッグを通知。
                    if(m_maxX >= CALIB || m_maxY >= CALIB) {
						m_f_move[pos] = true;
						if(!fGrp.isWorking(&m_ctrlList, this) && !(m_callbackMask & MASK_DRAG)) {
							CKLBScriptEnv::getInstance().call_eventUIControlDrag(m_onDrag, this, item->type, item->x, item->y, m_moveX, m_moveY);
						}
                    }
				} else if(m_usePt == 2) {
					// 操作対象点のどちらかでなければ反応しない

					// 操作点座標更新
					m_posX[pos] = item->x;
					m_posY[pos] = item->y;

					// 更新後の座標で、2点間の距離を求める。
					float dist, angle;
                    calc_distance(&dist, &angle);

					// 初期の距離との比率を求める
					float pinch = dist / m_orgLen;
                    float rot   = angle - m_orgAngle;

					// アイテムをマーク済みにする
					tpq.useItem(item, this);

					// onPinch が指定されていれば呼ぶ
					if(!fGrp.isWorking(&m_ctrlList, this) && !(m_callbackMask & MASK_PINCH)) {
						CKLBScriptEnv::getInstance().call_eventUIControlPinch(m_onPinch, this, item->type, pinch, rot);
					}
				}
			}
			break;
		case PAD_ITEM::RELEASE:
		case PAD_ITEM::CANCEL:
			{
				// 自身の操作中でなければ、アイテムがあってもそれは自身への操作ではない。
				if(!m_bControl) break;
				if(m_usePt == 1) {	// 1点のみの操作中
					if(m_id[0] != item->id) break;	// 違うポイントでの操作なら反応しない

					m_moveX = item->x - m_tapX;
					m_moveY = item->y - m_tapY;

					tpq.useItem(item, this);

					// マップ上クリック操作時
					// TAP->RELEASEの間にDRAGが無く、移動量が0の場合は click とみなす。
					if(m_maxX < CALIB && m_maxY < CALIB) {
                        if(!m_bClick) {
                            m_bClick  = true;
                            m_timeCnt = 0;
                            m_clickX  = m_tapX;
                            m_clickY  = m_tapY;
                        } else {
                            if(m_timeCnt < CLICKTIME) {
                                // 時間内にダブルクリックが成立
                                m_bClick  = false;
                                m_timeCnt = 0;
                                if(m_onDblClick) {
									if(!fGrp.isWorking(&m_ctrlList, this) && !(m_callbackMask & MASK_DBLCLICK)) {
										CKLBScriptEnv::getInstance().call_eventUIControlDblClick(
											m_onDblClick, this, m_clickX, m_clickY);
									}
                                } else {
                                    // ダブルクリックハンドラがない場合はクリックと同じ動作
									if(!fGrp.isWorking(&m_ctrlList, this) && !(m_callbackMask & MASK_CLICK)) {
										if(m_lastClick != frameID) {
											m_lastClick = frameID;
											CKLBScriptEnv::getInstance().call_eventUIControlClick(
												m_onClick, this, m_clickX, m_clickY);
										}
									}
                                }
								fGrp.setWorking(&m_ctrlList, false, this);	// 確定なのでworking解除
							}
                        }
					} else {
						// onDrag は、その時点での座標値とドラッグ移動量を返す。
						if(!fGrp.isWorking(&m_ctrlList, this) && !(m_callbackMask & MASK_DRAG)) {
							CKLBScriptEnv::getInstance().call_eventUIControlDrag(
								m_onDrag, this, item->type, item->x, item->y, m_moveX, m_moveY);
							fGrp.setWorking(&m_ctrlList, false, this);	// 確定なのでworking解除
						}
					}
				} else if(m_usePt == 2) {
					// 操作対象点のどちらかでなければ反応しない
					int pos = -1;
					for(int i = 0; i < m_usePt; i++) {
						if(m_id[i] == item->id) pos = i;
					}
                    if(pos < 0) { break; }

					// 操作点座標更新
					m_posX[pos] = item->x;
					m_posY[pos] = item->y;

					// 更新後の座標で、2点間の距離を求める。
					float dist, angle;
                    calc_distance(&dist, &angle);
                    
					// 初期の距離との比率を求める
					float pinch = dist / m_orgLen;
                    float rot = angle - m_orgAngle;

					// アイテムをマーク済みにする
					tpq.useItem(item, this);

					// onPinch が指定されていれば呼ぶ
					if(!fGrp.isWorking(&m_ctrlList, this) && !(m_callbackMask & MASK_PINCH)) {
						CKLBScriptEnv::getInstance().call_eventUIControlPinch(m_onPinch, this, item->type, pinch, rot);
					}
					fGrp.setWorking(&m_ctrlList, false, this);	// 確定なのでworking解除
				}
				m_bControl = false;		// 操作終了
				m_usePt    = 0;			// どちらか一方でもreleaseされたら操作を終了する
			}
			break;
		}
	}

	// 1点のみの操作中で、まだ概念上DRAGが始まっておらず、
	// TAP操作からの経過時間が0より大きければcallbackを呼ぶ
	if(m_usePt == 1 && !m_f_move[0]) {
		if(m_tcnt[0] > 0 && m_onLongTap && !fGrp.isWorking(&m_ctrlList, this) && !(m_callbackMask & MASK_LONGTAP)) {
			CKLBScriptEnv::getInstance().call_eventUIControlLongTap(m_onLongTap, this, m_tcnt[0], m_tapX, m_tapY);
			fGrp.setWorking(&m_ctrlList, false, this); // Need to cancel if UI changes or something.
		}
		m_tcnt[0] += deltaT;
	}

	if(m_bClick) {
        m_timeCnt += deltaT;
        if(m_timeCnt >= CLICKTIME) {
            m_timeCnt = 0;
            m_bClick = false;
			if(!fGrp.isWorking(&m_ctrlList, this) && !(m_callbackMask & MASK_CLICK)) {
				if(m_lastClick != frameID) {
					m_lastClick = frameID;
					CKLBScriptEnv::getInstance().call_eventUIControlClick(m_onClick, this, m_clickX, m_clickY);
				}
			}
			fGrp.setWorking(&m_ctrlList, false, this);	// 確定なのでworking解除
        }
    }
}

void
CKLBUIControl::die()
{
	CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();
	fGrp.delForm(&m_ctrlList);

	m_modalStack.remove();
	KLBDELETEA(m_onPinch);
	KLBDELETEA(m_onLongTap);
	KLBDELETEA(m_onDblClick);
	KLBDELETEA(m_onClick);
	KLBDELETEA(m_onDrag);
}
