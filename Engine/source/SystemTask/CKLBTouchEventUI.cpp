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
#include "CKLBTouchEventUI.h"
#include "CKLBTouchPad.h"
#include "CKLBUISystem.h"
#include "CKLBLuaEnv.h"
#include "CKLBFormGroup.h"

CKLBTouchEventUIMgr::CKLBTouchEventUIMgr() : m_pFormBegin(NULL)
{
	for(int i = 0; i < MAX_TOUCH_POINT; i++) m_pTarget[i] = 0;
}
CKLBTouchEventUIMgr::~CKLBTouchEventUIMgr() {}

CKLBTouchEventUIMgr&
CKLBTouchEventUIMgr::getInstance()
{
	static CKLBTouchEventUIMgr instance;
	return instance;
}

void
CKLBTouchEventUIMgr::registForm(SFormCtrlList * pList)
{
	// 既に登録されているかもしれないので、一旦おなじポインタでremoveを試みる
	removeForm(pList);
	pList->next = m_pFormBegin;
	m_pFormBegin = pList;
}

void
CKLBTouchEventUIMgr::removeForm(SFormCtrlList * pList)
{
	SFormCtrlList * pPrev = m_pFormBegin;

    if(pPrev == pList) {
        m_pFormBegin = pList->next;
        return;
    }
	while(pPrev) {
		if(pPrev->next == pList) {
			pPrev->next = pList->next;	// 対象をリストから除外する
			pList->next = NULL;
			return;
		}
		pPrev = pPrev->next;
	}
}

SFormCtrlList *
CKLBTouchEventUIMgr::searchCtrl(CKLBUISelectable * pCtrl)
{
	// 対象のコントロールが含まれるフォームの単位を検索する
	SFormCtrlList * pList = m_pFormBegin;

	while(pList) {

		CKLBUISelectable * pItem = pList->pBegin;
		while(pItem) {
			if(pItem == pCtrl) {
				// このリストに含まれているので、リストのポインタを返す
				return pList;
			}
			pItem = pItem->getNextSelectable();
		}
		pList = pList->next;
	}

	// 含まれるリストは見つからない
	return NULL;
}

void
CKLBTouchEventUIMgr::resetSelectable(CKLBUISelectable * pSelectable)
{
	for(int i = 0; i < MAX_TOUCH_POINT; i++) {
		if(m_pTarget[i] == pSelectable) {
			m_pTarget[i] = 0;
			break;
		}
	}
}

void
CKLBTouchEventUIMgr::processUI()
{
	// bool started = false;
	CKLBTouchPadQueue& tpq = CKLBTouchPadQueue::getInstance();

#ifdef LOG_EVENT
	tpq.setProcessing(true);
#endif
	tpq.startItem();

	const PAD_ITEM * item;
	float xf;
	float yf;

	CKLBFormGroup& fGrp = CKLBFormGroup::getInstance();

	u32 tapMask = 0;

	while ((item = tpq.getItem()) != NULL)
	{
#ifdef LOG_EVENT
		if (!started) {
			started = true;
			DEBUG_PRINT("EventS");
		}
		DEBUG_PRINT("EventP:%i,%i,%i,%i",item->id, item->type, item->x, item->y);
#endif

//		if ((item->type == PAD_ITEM::RELEASE) || (item->type == PAD_ITEM::TAP)) {
			xf = (float)item->x;
			yf = (float)item->y;

			u32 msk = 1 << item->id;

			switch(item->type)
			{
			case PAD_ITEM::TAP:
				{
					if ((tapMask & msk) != 0) {  
						break;
					}
					CKLBUISelectable * hitObj = CKLBUISystem::hitTest(xf, yf);
					if(hitObj) {
						// そのコントロールが含まれるフォーム情報を得る
						SFormCtrlList * pList = searchCtrl(hitObj);
						if(pList) {
							// そのコントロールが操作禁止状態にあれば、
							// 操作イベントを無視する。
							if(!pList->bEnable) {
								break;
							}

							// そのフォームが排他コントロールフォームであり、
							// なおかつ同じフォームに含まれる他のコントロールが操作中であるならば
							// その操作はなかったことにする。
							if(fGrp.isWorking(pList)) break;
							fGrp.setWorking(pList, true);
						}
						CKLBAction action;
						if (hitObj->isVisible()) {
							m_pTarget[item->id] = hitObj;
							m_tapPos[item->id].x = item->x;
							m_tapPos[item->id].y = item->y;

							if (hitObj->isEnabled()) {
								action.m_actionType = ACTION_PUSH;
								hitObj->processAction(&action);
							}

							tpq.useItem(item, hitObj);
						}
					}
				}
				break;
			case PAD_ITEM::DRAG:
				{
					if ((tapMask & msk) != 0) {  
						break;
					}
					// そのドラッグに使用されているポイントのIDがこのタスクで補足中の
					// ポイントである場合、その位置をタップ時の位置と比較し、
					// 移動量が一定の閾値以上であれば、そのコントロールへの操作を
					// キャンセル扱いにする
					if(m_pTarget[item->id]) {

						// 現在補足中のドラッグ操作であるので、イベントをマークする
						CKLBUISelectable * hitObj = m_pTarget[item->id];
						tpq.useItem(item, hitObj);

						// 補足中のID:タップ位置からの移動量を求める。
						int mv_x = item->x - m_tapPos[item->id].x;
						int mv_y = item->y - m_tapPos[item->id].y;
						int ax = (mv_x < 0) ? -mv_x : mv_x;
						int ay = (mv_y < 0) ? -mv_y : mv_y;

						// 移動量が閾値を超えていれば、もはやクリック操作ではない。
						if(ax > MV_BORDER || ay > MV_BORDER) {
							// タップされていたターゲットのフォーム情報を得る
							SFormCtrlList * pList = searchCtrl(hitObj);

							CKLBAction action;
							action.m_actionType = ACTION_UNDEF;
							if (hitObj->isEnabled()) {
								hitObj->processAction(&action);							
							}

							// ターゲットのリストが無ければ補足中のIDをキャンセルする
							// あるいは、すでに対象フォームが disable にされていたらキャンセル。
							if(!pList || !pList->bEnable) {
								if(pList) fGrp.setWorking(pList, false);
								m_pTarget[item->id] = 0;
								// その他、キャンセル処理があればここに書く。
	
							
							
							} else {
								// DRAGのコールバックが指定されていたら基点と移動量を与えて呼び出す
								if(pList->pCallbackIF) {
									pList->pCallbackIF->callback(item->type, 
																	m_tapPos[item->id].x,
																	m_tapPos[item->id].y,
																	mv_x, mv_y);
								} else if(pList->nativeCallback) {
									pList->nativeCallback(pList->pID,
															item->type,
															m_tapPos[item->id].x,
															m_tapPos[item->id].y,
															mv_x, mv_y);
								}
							}
						}
					}
				}
				break;
			case PAD_ITEM::RELEASE:
			case PAD_ITEM::CANCEL:
				{
					if ((tapMask & msk) != 0) {  
						break;
					} else {
						tapMask |= msk;
					}

					CKLBUISelectable * hitObj = 0; // CKLBUISystem::hitTest(xf, yf);
					if(m_pTarget[item->id]) hitObj = m_pTarget[item->id];

					if(hitObj) {
						// そのコントロールが含まれるフォーム情報を得る
						SFormCtrlList * pList = searchCtrl(hitObj);
						if(pList) fGrp.setWorking(pList, false);

						int mv_x = item->x - m_tapPos[item->id].x;
						int mv_y = item->y - m_tapPos[item->id].y;
						int ax = (mv_x < 0) ? -mv_x : mv_x;
						int ay = (mv_y < 0) ? -mv_y : mv_y;

						// 移動量が閾値を超えていれば、もはやクリック操作ではない。
						if(ax > MV_BORDER || ay > MV_BORDER) {
							CKLBAction action;
							action.m_actionType = ACTION_UNDEF;
							if (hitObj->isEnabled()) {
								hitObj->processAction(&action);							
							}								

							// DRAGのコールバックが指定されていたら基点と移動量を与えて呼び出す
							if(pList && pList->pCallbackIF) {
								pList->pCallbackIF->callback(item->type, 
																m_tapPos[item->id].x,
																m_tapPos[item->id].y,
																mv_x, mv_y);
							} else if(pList->nativeCallback) {
								pList->nativeCallback(pList->pID,
														item->type,
														m_tapPos[item->id].x,
														m_tapPos[item->id].y,
														mv_x, mv_y);
							}
						} else {
							// あまり動かずにリリースされたので、
							// クリック操作とみなす。
							if(!pList || pList->bEnable) {
								// その時点で操作が禁止されていたら、リリースも発行しない。
								CKLBAction action;
								action.m_actionType = ACTION_RELEASE;
								if (hitObj->isEnabled()) {
									hitObj->processAction(&action);
								}
							}
						}
						tpq.useItem(item, hitObj);
						m_pTarget[item->id] = 0;
					}
				}
				break;
			}
			/*
			CKLBUISelectable* hitObj = CKLBUISystem::hitTest(xf, yf);

			if (hitObj) {
				CKLBAction action;
				if (item->type == PAD_ITEM::RELEASE) {
					action.m_actionType	= ACTION_RELEASE;
				} else if (item->type == PAD_ITEM::TAP) {
					action.m_actionType = ACTION_PUSH;
				} else {
					action.m_actionType	= ACTION_UNDEF;
				}

				hitObj->processAction(&action);
				tpq.useItem(item, hitObj);
			}
			*/
//		}
	}

#ifdef LOG_EVENT
	if (started) {
		DEBUG_PRINT("EventE");
	} else {
		DEBUG_PRINT("EventF");
	}
	tpq.setProcessing(false);
#endif
}


CKLBTouchEventUITask::CKLBTouchEventUITask() : CKLBTask() {}
CKLBTouchEventUITask::~CKLBTouchEventUITask() {}

CKLBTouchEventUITask *
CKLBTouchEventUITask::create()
{
	CKLBTouchEventUITask * pTask = KLBNEW(CKLBTouchEventUITask);
	if(!pTask) return NULL;
	if(!pTask->init()) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

void
CKLBTouchEventUITask::execute(u32 /*deltaT*/)
{
	CKLBTouchEventUIMgr& mgr = CKLBTouchEventUIMgr::getInstance();

	mgr.processUI();
}

void
CKLBTouchEventUITask::die()
{
	// Do nothing for now.
}

u32
CKLBTouchEventUITask::getClassID()
{
	return CLS_KLBTASKUIEVENT;
}

bool
CKLBTouchEventUITask::init()
{
	return regist(NULL, P_UIPREV);
}
