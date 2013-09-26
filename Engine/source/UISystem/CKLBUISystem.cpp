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
#include "CKLBUISystem.h"
#include "CKLBScriptEnv.h"
#include <string.h>
#include "AudioAsset.h"
#include "CKLBTouchEventUI.h"

// Init Touch System.
SFormCtrlList* CKLBUISystem::s_formList = NULL;
SClipRecord*   CKLBUISystem::s_clip_array[UI_SYS_MAXCLIP_ARRAY];
u16 CKLBUISystem::s_clip_arraySize = 0;

CKLBUISelectable* 
CKLBUISystem::hitTest(float screenX, float screenY) 
{
	CKLBUISelectable*   result      = NULL;
	SFormCtrlList*      pFormParse  = CKLBTouchEventUIMgr::getInstance().m_pFormBegin;
	u32 priorityResult = 0;

	while (pFormParse) {
		// Possible optimization here using form "state" information.
		// if (pFormParse->bEnable) { pFormParse = pFormParse->nextForm; continue; }

		CKLBUISelectable* elem      = pFormParse->pBegin;
		while (elem) {
			if (elem->isEnabled()) {		// Visible AND Enabled test.
				STouchSurface* list = &elem->m_touchSurface;

				if (list->isUpToDate == false) {
					//
					// Apply matrix computation.
					//
					float tx  = list->transform->m_matrix[MAT_TX];
					float ty  = list->transform->m_matrix[MAT_TY];
					float sx  = list->transform->m_matrix[MAT_A];
					float nsx = list->transform->m_matrix[MAT_B];
					float sy  = list->transform->m_matrix[MAT_D];
					float nsy = list->transform->m_matrix[MAT_C];

					for (int idx=0; idx<4; idx += 2) {
						float lx = (idx == 0) ? list->beforeTransform[0] :  list->beforeTransform[0] + list->beforeTransform[2];
						float ly = (idx == 0) ? list->beforeTransform[1] :  list->beforeTransform[1] + list->beforeTransform[3];

						list->afterTransform[0+idx] = (lx * sx) + (ly * nsx) + tx;
						list->afterTransform[1+idx] = (ly * sy) + (lx * nsy) + ty;
					}

					list->isUpToDate = true;
				}

				// 1.Check if list->touchSurfacePriorityEquiv belong to a clipping range.
				//	If so, clip afterTransformCoordinates
				int n = 0;
				while (n < s_clip_arraySize) {
					if ((list->touchSurfacePriorityEquiv >= s_clip_array[n]->pClipStartState->getOrder()) &&
						(list->touchSurfacePriorityEquiv <  s_clip_array[n]->pClipEndState->getOrder())) {
						//
						// Perform clipping
						//

						// Convert H,W -> X,Y
						float clip[4];
						float* src = s_clip_array[n]->pClipStartState->getPostScissor();

						clip[0] = src[0];
						clip[1] = src[1];
						clip[2] = src[2] + src[0];
						clip[3] = src[3] + src[1];

						if (list->afterTransform[0] < clip[0]) { list->afterTransform[0] = clip[0]; }
						if (list->afterTransform[1] < clip[1]) { list->afterTransform[1] = clip[1]; }
						if (list->afterTransform[0] > clip[2]) { list->afterTransform[0] = clip[2]; }
						if (list->afterTransform[1] > clip[3]) { list->afterTransform[1] = clip[3]; }
						if (list->afterTransform[2] < clip[0]) { list->afterTransform[2] = clip[0]; }
						if (list->afterTransform[3] < clip[1]) { list->afterTransform[3] = clip[1]; }
						if (list->afterTransform[2] > clip[2]) { list->afterTransform[2] = clip[2]; }
						if (list->afterTransform[3] > clip[3]) { list->afterTransform[3] = clip[3]; }

						// Little optimization, early stop.
						break;
					}
					n++;
				}

				if (    (screenX >= list->afterTransform[0]) && (screenY >= list->afterTransform[1])
					&&  (screenX <= list->afterTransform[2]) && (screenY <= list->afterTransform[3]))
				{
					if (list->touchSurfacePriorityEquiv >= priorityResult) {
						priorityResult = list->touchSurfacePriorityEquiv;
						result = elem;
					}
				}
			}

			elem = elem->m_pNextSelectable;
		}

		pFormParse = pFormParse->next;
	}
	printf("CLICK %p\n", result);
	return result;
}

bool 
CKLBUISystem::checkRange(CKLBRenderState* startClip, CKLBRenderState* endClip) 
{
	klb_assert(startClip->getOrder() < endClip->getOrder(), "Wrong clipping order (start >= end)");

	int n = 0;
	while (n < s_clip_arraySize) {
		CKLBRenderState* pStateS = s_clip_array[n]->pClipStartState;
		CKLBRenderState* pStateE = s_clip_array[n]->pClipEndState;

		if ((startClip->getOrder() >= pStateS->getOrder()) && (startClip->getOrder() <= pStateE->getOrder())) {
			return false;
		}

		if ((endClip->getOrder() >= pStateS->getOrder()) && (endClip->getOrder() <= pStateE->getOrder())) {
			return false;
		}

		n++;
	}
	return true;
}

void* 
CKLBUISystem::registerClip(CKLBRenderState* startClip, CKLBRenderState* endClip) 
{
	klb_assert(s_clip_arraySize < UI_SYS_MAXCLIP_ARRAY, "Reached max UI clipping stack");

	klb_assert(checkRange(startClip, endClip), "Overlapping clipping range");

	SClipRecord * pRec = KLBNEW(SClipRecord);
	pRec->pClipStartState = startClip;
	pRec->pClipEndState = endClip;
	s_clip_array[s_clip_arraySize++] = pRec; 
	return (void *)pRec;
}

void 
CKLBUISystem::unregisterClip(void* handle) 
{
	if (handle) {
		s32 n = 0;
		while (n < s_clip_arraySize) {
			if (s_clip_array[n] == handle) {
				//
				// Remove from list.
				//
				while (n < (s_clip_arraySize-1)) {
					s_clip_array[n] = s_clip_array[n+1];
					n++;
				}
				KLBDELETE((SClipRecord *)handle);
				handle = NULL;
				s_clip_arraySize--;

				return;
			}
			n++;
		}
	}

	// Do nothing.
}

CKLBUISelectable* 
CKLBUISystem::createTouchSurface(CKLBUISelectable* pSource, u32 priority) 
{
	klb_assert(s_formList, "Always have form assigned");
	klb_assert(pSource->m_pNextSelectable == NULL, "Must be null");

	STouchSurface*	pNew    = &pSource->m_touchSurface;
	pNew->isUpToDate        = false;
			
	pNew->beforeTransform[0] = 0.0f;
	pNew->beforeTransform[1] = 0.0f;
	pNew->beforeTransform[2] = 0.0f;
	pNew->beforeTransform[3] = 0.0f;

	pNew->surfaceIndex              = 0; // Not used for now.
	pNew->transform                 = &pSource->m_composedMatrix;
	pNew->touchSurfacePriorityEquiv	= priority;

	printf("FORM Add Ctrl : %p\n", pSource);

	pSource->m_pNextSelectable = s_formList->pBegin;
	s_formList->pBegin = pSource;
	
	return pSource;
}

void 
CKLBUISystem::releaseTouchSurface(CKLBUISelectable* pSurface) 
{
	SFormCtrlList* pFormParse		= CKLBTouchEventUIMgr::getInstance().m_pFormBegin;
	klb_assert(pSurface, "NULL PTR");

	while (pFormParse) {
		// Possible optimization here using form "state" information.
		// if (pFormParse->bEnable) { pFormParse = pFormParse->nextForm; continue; }

		CKLBUISelectable* elem = pFormParse->pBegin;
		CKLBUISelectable* prev = NULL;

		while (elem && elem != pSurface) {
			prev = elem;
			elem = elem->m_pNextSelectable;
		}

		if (elem) {
			printf("FORM Remove Ctrl : %p %p\n", pSurface, pFormParse);
			if (prev == NULL) {
				pFormParse->pBegin = elem->m_pNextSelectable;
			} else {
				prev->m_pNextSelectable = elem->m_pNextSelectable;
			}

			// Early return
			return;
		}

		pFormParse = pFormParse->next;
	}

	klb_assertAlways("Surface not found");
}

void 
CKLBUISystem::releaseAll() 
{
	/*
	klb_assert(!s_touchList, "Hit List should be empty");

	s_touchList = NULL;
	*/
}

void 
CKLBUISystem::setFormList(SFormCtrlList * pList)
{
	s_formList = pList;
}

// -----------------------------------------------------------------
//   CKLBUIElement
// -----------------------------------------------------------------

CKLBUIElement::CKLBUIElement()
: CKLBNode              ()
, m_currentAsset        (NULL)
, m_currentAssetTree    (NULL)
, m_pActionHandlerList  (NULL)
, m_pNormal             (NULL)
, m_pDisabled           (NULL)
, m_pNormalTree         (NULL)
, m_pDisabledTree       (NULL)
, m_luaFunc             (NULL)
, m_scriptable          (NULL)
, m_UIState             (NORMAL)
, m_listenerMask        (0)
, m_renderPrio          (0)
, m_bEnabled            (true)
, m_bUpperEnabled       (true)
, m_bDoRefCount         (true)
{
	m_bInternalNode  = false;
	m_status        |= UI_TYPE;	// Node made it visible and marked for refresh.
}

CKLBUIElement::~CKLBUIElement() 
{
	releaseAsset(m_pNormal);
	releaseAsset(m_pDisabled);
	m_pNormal   = NULL;
	m_pDisabled	= NULL;

	KLBDELETE(m_pNormalTree);
	KLBDELETE(m_pDisabledTree);
	KLBDELETEA(m_luaFunc);
}

void 
CKLBUIElement::setScriptable(CKLBObjectScriptable* pScriptable) 
{
	m_scriptable = pScriptable;
}

/*virtual*/
void 
CKLBUIElement::addRender() 
{
	// Ancestor support.
	CKLBNode::addRender();

	// Visibility flag is up to date : call works.
	switchTo(m_UIState);
}

/*virtual*/
void 
CKLBUIElement::removeRender() 
{
	// Ancestor support.
	CKLBNode::removeRender();

	if (m_currentAssetTree) {
		this->removeNode(m_currentAssetTree);
		m_currentAsset = NULL; // No asset is displayed now.
	}
}


void 
CKLBUIElement::setLeft(s32 coordinateX) 
{
	this->m_matrix.m_matrix[MAT_TX] = (float)coordinateX;
	markUpMatrix();
}

void 
CKLBUIElement::setTop(s32 coordinateY) 
{
	this->m_matrix.m_matrix[MAT_TY] = (float)coordinateY;
	markUpMatrix();
}

void 
CKLBUIElement::releaseAsset(CKLBAsset* pAsset) 
{
	if (pAsset && m_bDoRefCount) {
		if (pAsset->getAssetType() != ASSET_IMAGE) {
			pAsset->decrementRefCount();
		} else {
			((CKLBImageAsset*)pAsset)->getTexture()->decrementRefCount();
		}
	}
}

void 
CKLBUIElement::resetAsset(CKLBAsset** ppOldAsset, CKLBNode** ppOldNode, CKLBAsset* newAsset) 
{
	if (*ppOldAsset != newAsset) {
		releaseAsset(*ppOldAsset);

		KLBDELETE((*ppOldNode));
		*ppOldAsset = newAsset;

		if (newAsset && m_bDoRefCount) {
			if (newAsset->getAssetType() != ASSET_IMAGE) {
				newAsset->incrementRefCount();
			} else {
				((CKLBImageAsset*)newAsset)->getTexture()->incrementRefCount();
			}
		}

		*ppOldNode	= NULL;

		switchTo(m_UIState);
	}
}

/*virtual*/ 
void 
CKLBUIElement::setAsset(CKLBAsset*	pAsset, CKLBUIElement::ASSET_TYPE mode) 
{
	switch (mode) {
	case CKLBUIElement::NORMAL_ASSET:
		resetAsset(&m_pNormal, &m_pNormalTree, pAsset);
		break;
	case CKLBUIElement::DISABLED_ASSET:
		resetAsset(&m_pDisabled, &m_pDisabledTree, pAsset);
		break;
	default:
		// Do nothing.
		break;
	}
}

void 
CKLBUIElement::visibleSelf() 
{
	CKLBNode::visibleSelf();
	// sendEvent(ACTION_STATECHANGE, this->m_UIState);
}

void 
CKLBUIElement::invisibleSelf() 
{
	CKLBNode::invisibleSelf();
	// sendEvent(ACTION_STATECHANGE, NOT_ON_SCREEN);
}

void 
CKLBUIElement::setUpperEnabled(bool isEnabled) 
{
	if ((isEnabled != m_bUpperEnabled) || (m_currentAsset == NULL)) {
		m_bUpperEnabled = isEnabled;
		if (isEnabled && m_bEnabled) {	// Both upper and current enabled.
			switchTo(NORMAL);
		} else {
			switchTo(DISABLED);
		}
	}
}

void 
CKLBUIElement::setEnabled(bool isEnabled) 
{
	if ((isEnabled != m_bEnabled) || (m_currentAsset == NULL)) {
		m_bEnabled = isEnabled;
		if (isEnabled && m_bUpperEnabled) {	// Both current and upper enabled.
			switchTo(NORMAL);
		} else {
			switchTo(DISABLED);
		}
	}
}

bool 
CKLBUIElement::isEnabled() 
{
	return m_bEnabled && m_bUpperEnabled && isVisible();
}

void 
CKLBUIElement::switchTo(UI_STATE newState) 
{
	if (isVisible()) {
		CKLBAsset*  pCurrAsset  = NULL;
		CKLBNode*   pCurrNode   = NULL;
		bool create = false;

		//
		// Select Graphical state : asset and create cached node tree if not present.
		//
		switch (newState) {
		case CKLBUIElement::NORMAL_ASSET:
			pCurrAsset = m_pNormal;
			if (m_pNormal && (m_pNormalTree == NULL)) {
				m_pNormalTree	= m_pNormal->createSubTree(m_renderPrio);
				create = true;
			}
			pCurrNode		= m_pNormalTree;
			break;
		case CKLBUIElement::DISABLED_ASSET:
			pCurrAsset = m_pDisabled;
			if (m_pDisabled && (m_pDisabledTree == NULL)) {
				m_pDisabledTree = m_pDisabled->createSubTree(m_renderPrio);
				create = true;
			}
			pCurrNode		= m_pDisabledTree;
			break;
		case CKLBUIElement::FOCUSED_ASSET:
			if (isSelectable()) {
				CKLBUISelectable* pSelect = (CKLBUISelectable*)this;
				pCurrAsset = pSelect->m_pFocus;
				if (pSelect->m_pFocus && (pSelect->m_pFocusTree == NULL)) {
					pSelect->m_pFocusTree = pCurrNode = pSelect->m_pFocus->createSubTree(m_renderPrio);
				}
				pCurrNode	= pSelect->m_pFocusTree;
				create = true;
			}
			break;
		case CKLBUIElement::PUSHED_ASSET:
			if (isSelectable()) {
				CKLBUISelectable* pSelect = (CKLBUISelectable*)this;
				pCurrAsset = pSelect->m_pPushed;
				if (pSelect->m_pPushed && (pSelect->m_pPushedTree == NULL)) {
					pCurrNode = pSelect->m_pPushedTree = pSelect->m_pPushed->createSubTree(m_renderPrio);
				}
				pCurrNode	= pSelect->m_pPushedTree;
				create = true;
			}
			break;
        case CKLBUIElement::NOT_ON_SCREEN:
            /* not handled */
            break;
		}

		//
		// Apply new Graphical state.
		//
		if ((m_currentAsset != pCurrAsset) || create) {
			//
			// Remove old visual
			//
			if (m_currentAssetTree) {
				this->removeNode(m_currentAssetTree);
				m_currentAssetTree = NULL;
			}

			//
			// Add new visual
			//
			if (pCurrNode) {
				this->addNode(pCurrNode);
			}

			m_currentAsset		= pCurrAsset;
			m_currentAssetTree	= pCurrNode;
		}
		
		/* Temporary comment out.
		if (m_UIState != newState) {
			sendEvent(ACTION_STATECHANGE, newState);
		}*/
	} // else do not modify the scene graph

	// Still, state must change.
	m_UIState = newState;
}

CKLBUIContainer* 
CKLBUIElement::getParentUI() 
{
	CKLBNode* pNode = this->getParent();
	while (pNode) {
		u32 clID = pNode->getClassID();
		if (clID & CLS_KLBUICORECLASS) {
			if (((CKLBUIElement*)pNode)->isContainer()) {
				return (CKLBUIContainer*)pNode;
			}
		}
		pNode = pNode->getParent();
	}
	return NULL;
}

bool 
CKLBUIElement::processListener(CKLBAction* pAction) 
{
	bool forwardEvent = true;
	CKLBActionHandler* pHandler = this->m_pActionHandlerList;
	while (pHandler) {
		if (pHandler->m_actionType == pAction->m_actionType) {
			forwardEvent &= pHandler->handler(pAction);
		}
	}
	return forwardEvent;
}

/*virtual*/
bool 
CKLBUIElement::processAction(CKLBAction* pAction) 
{
	bool forwardEvent = true;
	/*
	if (m_listenerMask & (1 << pAction->m_actionType)) {
		forwardEvent &= processListener(pAction);
	}*/

	if (forwardEvent) {
		CKLBUIContainer* pParent = this->getParentUI();
		if (pParent) {
			pParent->processAction(pAction);
		}
	}

	return forwardEvent;
}

// -----------------------------------------------------------------
//   CKLBUISelectable
// -----------------------------------------------------------------

#define NO_RADIO_VALUE  (0xFFFFFFFF)

CKLBUISelectable::CKLBUISelectable()
: CKLBUIElement         ()
, m_pNextSelectable     (NULL)
, m_pPushed             (NULL)
, m_pFocus              (NULL)
, m_pPushedTree         (NULL)
, m_pFocusTree          (NULL)
, m_modalResult         (0)
, m_radioID             (NO_RADIO_VALUE)
, m_bStick              (false)
, m_bDown               (false)
, m_bLocked             (false)
, m_pDownAudio          (NULL)
, m_pUpAudio            (NULL)
, m_pDownVolumeOriginal (1.0f)
, m_pUpVolumeOriginal   (1.0f)
, m_pDownVolumeFactor   (1.0f)
, m_pUpVolumeFactor     (1.0f)
, m_pDownVolume         (1.0f)
, m_pUpVolume           (1.0f)
, m_groupID             (0)
, m_lastClick           (0)
, m_bOwnerDownAudio     (false)
, m_bOwnerUpAudio       (false)
{
}

bool 
CKLBUISelectable::init(u32 priority) 
{
	CKLBUISystem::createTouchSurface(this,priority);
	return true;
}

/*virtual*/
void 
CKLBUISelectable::recomputeCustom() 
{
	//
	// Refresh surface computation if a click occurs.
	//
	if (m_status & MATRIX_CHANGE) {
		m_touchSurface.isUpToDate = false;
	}
}


CKLBUISelectable::~CKLBUISelectable() 
{
	releaseAsset(m_pPushed);
	releaseAsset(m_pFocus);
	m_pPushed   = NULL;
	m_pFocus    = NULL;

	KLBDELETE(m_pPushedTree);
	KLBDELETE(m_pFocusTree);

	CKLBUISystem::releaseTouchSurface(this);
}

void 
CKLBUISelectable::setClickLeft(s32 coordinateX) 
{
	m_touchSurface.beforeTransform[0]   = (float)coordinateX;
	m_touchSurface.isUpToDate           = false;
}

void 
CKLBUISelectable::setClickWidth(u32 width) 
{
	m_touchSurface.beforeTransform[2]   = (float)width;
	m_touchSurface.isUpToDate           = false;
}

void 
CKLBUISelectable::setClickTop(s32 coordinateY) 
{
	m_touchSurface.beforeTransform[1]   = (float)coordinateY;
	m_touchSurface.isUpToDate           = false;
}

void 
CKLBUISelectable::setClickHeight(u32 height) 
{
	m_touchSurface.beforeTransform[3]   = (float)height;
	m_touchSurface.isUpToDate           = false;
}

void 
CKLBUISelectable::setModalResult(u32 modalResult) 
{
	m_modalResult = modalResult;
}

void 
CKLBUISelectable::setStick(bool isStickable) 
{
	m_bStick = isStickable;
}

void 
CKLBUISelectable::setSticked(bool isSticked) 
{
	if (isSticked == true) {
		// 1. Get Parent Container.
		CKLBUIContainer* pParent = this->getParentUI();

		if (pParent) {
			// 2. Parse all the children : reset
			CKLBUIElement* pElement = pParent->getChildUI();
			while (pElement) {
				u32 clID = pElement->getClassID();
				if (clID & CLS_KLBUICORECLASS) {
					resetSticked(pElement);
				} else {
					setStickedRecurse(pElement);
				}
				pElement = (CKLBUIElement*)(((CKLBUISelectable*)pElement)->m_pBrother);
			}
		}
	}
	this->setStickedInternal(isSticked);
}

void 
CKLBUISelectable::setStickedRecurse(CKLBNode* pNode) 
{
    pNode = pNode->getChild();
    while (pNode) {
	    u32 clID = pNode->getClassID();
	    if (clID & CLS_KLBUICORECLASS) {
		    if (clID == CLS_KLBUISELECTABLE) {
			    resetSticked((CKLBUIElement*)pNode);
		    }
	    } else {
		    setStickedRecurse(pNode);
	    }
	    pNode = (((CKLBUISelectable*)pNode)->m_pBrother);
    }
}

void 
CKLBUISelectable::resetSticked(CKLBUIElement* pElement) 
{
	if (pElement->isSelectable()) {
		CKLBUISelectable* pSelect = (CKLBUISelectable*)pElement;
		if (pSelect->isStickable() && (pSelect->getRadioID() != 0xFFFFFFFF)) {
			if (pElement->isEnabled()) {	// Should not be needed but programmatically could occur.		<-- Reset even disabled item
				if (pSelect != this) {
					pSelect->setStickedInternal(false);
				}
			}
		}
	}
}

void 
CKLBUISelectable::setUpperEnabled(bool isEnabled) 
{
	if ((isEnabled != m_bUpperEnabled) || (m_currentAsset == NULL)) {
		m_bUpperEnabled = isEnabled;
		if (isEnabled && m_bEnabled) {	// Both upper and current enabled.
			if ((m_bStick) && (m_bDown)) {
				switchTo(DOWN);
			} else {
				m_bDown = false;
				switchTo(NORMAL);
			}
		} else {
			switchTo(DISABLED);
		}
	}
}

void 
CKLBUISelectable::setEnabled(bool isEnabled) 
{
	if ((isEnabled != m_bEnabled) || (m_currentAsset == NULL)) {
		m_bEnabled = isEnabled;
		if (isEnabled && m_bUpperEnabled) {	// Both current and upper enabled.
			if ((m_bStick) && (m_bDown)) {
				switchTo(DOWN);
			} else {
				m_bDown = false;
				switchTo(NORMAL);
			}
		} else {
			switchTo(DISABLED);
		}
	}
}

void 
CKLBUISelectable::setStickedInternal(bool isSticked) 
{
	bool tmp = (isSticked != m_bDown); 
	if (tmp || (m_currentAsset == NULL)) {
		m_bDown = isSticked;

		if (m_UIState != DISABLED) {
			if (isSticked) {
				switchTo(DOWN);
			} else {
				switchTo(NORMAL);
				m_bLocked = false;
			}
		} else {
			// Do nothing, stay DISABLED view
		}
	}
}

void 
CKLBUISelectable::setRadio(u32 radioID) 
{
	m_radioID = radioID;
}

/*virtual*/
bool 
CKLBUISelectable::processAction	(CKLBAction* pAction) 
{
	bool down = this->m_bDown;

	if (pAction->m_actionType == ACTION_PUSH) {
		if (!down && m_pDownAudio) {
			m_pDownAudio->play(m_pDownVolume);
		}

		if (this->m_bStick == false) {	// If button : down on push.
			this->setSticked(true);
			if (m_bStick) {
				m_bLocked = !m_bLocked;
			}
		}
	} else if (pAction->m_actionType == ACTION_RELEASE) {
		if (this->m_bStick && down == false) {
			this->setSticked(true);
			/* locked desactive
			if (m_bStick) {
				m_bLocked = !m_bLocked;
			}*/
		}
		else
		if ((this->m_bStick == false) || (m_bLocked == false)) {
			if (down && m_pUpAudio) {
				m_pUpAudio->play(m_pUpVolume);
			}
			this->setSticked(false);
			m_bLocked = false;
		}

		if (m_bDown && (m_modalResult != 0)) {
			CKLBUIContainer* pParent = this->getParentUI();
			while (pParent) {
				if (pParent->isModal()) {
					pParent->sendEvent(ACTION_CLOSE, m_modalResult);
					pParent->getParent()->removeNode(pParent);
					break;
				}
				pParent = pParent->getParentUI();
			}
		}

		// Only check box deliver change event.
		if ((down != this->m_bDown) && (this->m_bStick == true)) {
			sendEvent(ACTION_CHANGE, m_bDown ? 1 : 0);
		}
	} else if (pAction->m_actionType == ACTION_UNDEF) {
		// Cancel action on a checkbox.
		if (this->m_bStick) {
			// Do nothing, change on release.
		} else {
		// Cancel button pushed.
			this->setSticked(false);
		}
	}

	switch (pAction->m_actionType) {
	case ACTION_PUSH:
		sendEvent((ACTION_TYPE)pAction->m_actionType, 0);
		break;
	case ACTION_RELEASE:
		{
			sendEvent((ACTION_TYPE)pAction->m_actionType, 0);	// Release
			int fid = CKLBTaskMgr::getInstance().getFrameID();
			if(fid != m_lastClick) {
				m_lastClick = fid;
				sendEvent(ACTION_CLICK,0);
			}
		}
		break;
	case ACTION_UNDEF:
		sendEvent(ACTION_RELEASE, 1);
		break;
	}

	return CKLBUIElement::processAction(pAction);
}

bool 
CKLBUIElement::sendEvent(ACTION_TYPE type, u32 param) 
{
    if(!m_luaFunc) { return false; } // do not have Lua function name.

	const char * name = (!m_name) ? "" : m_name;
    if(m_luaFunc) { 
        CKLBScriptEnv::getInstance().call_eventSelectable(m_luaFunc, m_scriptable, name, (int)type, param); 
    }

	return false;
}

bool 
CKLBUISelectable::setLuaFunction(const char * name)
{
	char * buf;
	if(name) {
		buf = KLBNEWA(char, strlen(name) + 1);
		if(!buf) return false;
		strcpy(buf, name);
	} else {
		buf = NULL;
	}
	if(m_luaFunc) KLBDELETEA(m_luaFunc);
	m_luaFunc = buf;
	return true;
}

/*virtual*/ 
void 
CKLBUISelectable::setAsset(CKLBAsset*	pAsset, CKLBUIElement::ASSET_TYPE mode) 
{
	switch (mode) {
	case CKLBUIElement::PUSHED_ASSET:
		resetAsset(&m_pPushed, &m_pPushedTree, pAsset);
		break;
	case CKLBUIElement::FOCUSED_ASSET:
		resetAsset(&m_pPushed, &m_pPushedTree, pAsset);
		break;
	default:
		CKLBUIElement::setAsset(pAsset, mode);
		break;
	}
}

void 
CKLBUISelectable::setAudio(CKLBAudioAsset* pAudioAsset, u32 mode, float volume, bool bOwner) 
{
	if (mode == 0) {
		// Down
		if(m_bOwnerDownAudio && m_pDownAudio) {
			m_pDownAudio->decrementRefCount();
		}
		m_pDownAudio        = pAudioAsset;
		m_bOwnerDownAudio   = bOwner;
		m_pDownVolumeOriginal = volume;
		m_pDownVolume       = m_pDownVolumeOriginal * m_pDownVolumeFactor;
	} else {
		// Up
		if(m_bOwnerUpAudio && m_pUpAudio) {
			m_pUpAudio->decrementRefCount();
		}
		m_pUpAudio          = pAudioAsset;
		m_bOwnerUpAudio     = bOwner;
		m_pUpVolumeOriginal = volume;
		m_pUpVolume         = m_pUpVolumeOriginal * m_pUpVolumeFactor;
	}
}

void CKLBUISelectable::setMultiplyVolume(u32 mode, float factorVolume) {
	if (mode == 0) {
        m_pDownVolumeFactor = factorVolume;
		m_pDownVolume       = m_pDownVolumeOriginal * m_pDownVolumeFactor;
	} else {
		// Up
        m_pUpVolumeFactor   = factorVolume;
		m_pUpVolume         = m_pUpVolumeOriginal * m_pUpVolumeFactor;
	}
}

// -----------------------------------------------------------------
//   CKLBUIContainer
// -----------------------------------------------------------------

CKLBUIContainer::CKLBUIContainer()
: CKLBUIElement     ()
, m_viewPortWidth   (0)
, m_viewPortHeight  (0)
, m_viewScrollX     (0)
, m_viewScrollY     (0)
, m_innerNode       (NULL)
, m_bAsModal        (false)
, m_clipHandle      (NULL)
{
    m_outerNode = this; // Should not be used in initializer. (Compiler Warning)
}

CKLBUIContainer::~CKLBUIContainer() 
{
	if (m_clipHandle) {
		CKLBUISystem::unregisterClip(m_clipHandle);
		m_clipHandle = NULL;
	}
	KLBDELETE(m_innerNode);
}

bool CKLBUIContainer::init() 
{
	m_innerNode = KLBNEW(CKLBNode);
	if (m_innerNode) {
		this->addNode(m_innerNode);
	}

	return (m_innerNode != NULL);
}

/*virtual*/
void 
CKLBUIContainer::setUpperEnabled(bool isEnabled) 
{
	if ((isEnabled != m_bUpperEnabled) || (m_currentAsset == NULL)) {
		m_bUpperEnabled = isEnabled;
		if (isEnabled && m_bEnabled) {	// Both upper and current enabled.
			switchTo(NORMAL);
		} else {
			switchTo(DISABLED);
		}

		//
		// Modify all sub tree.
		//
		CKLBNode* pElement = this->getChildUI();
		while (pElement) {
			//
			// Dirty cast (CKLBUIContainer*) because protected inheritance C++ spec are stupid.
			//
			switch (pElement->getClassID()) {
			case CLS_KLBUIELEMENT:
			case CLS_KLBUISELECTABLE:
			case CLS_KLBUICONTAINER:
				((CKLBUIContainer*)pElement)->setUpperEnabled(isEnabled);	
				break;
			}
			pElement = ((CKLBUIContainer*)pElement)->m_pBrother;
		}
	}
}

/*virtual*/
void 
CKLBUIContainer::setEnabled(bool isEnabled) 
{
	if ((isEnabled != m_bEnabled) || (m_currentAsset == NULL)) {
		m_bEnabled = isEnabled;
		if (isEnabled && m_bUpperEnabled) {	// Both current and upper enabled.
			switchTo(NORMAL);
		} else {
			switchTo(DISABLED);
		}

		//
		// Modify all sub tree.
		//
		CKLBNode* pElement = this->getChildUI();
		while (pElement) {
			//
			// Dirty cast (CKLBUIContainer*) because protected inheritance C++ spec are stupid.
			//
			switch (pElement->getClassID()) {
			case CLS_KLBUIELEMENT:
			case CLS_KLBUISELECTABLE:
			case CLS_KLBUICONTAINER:
				((CKLBUIContainer*)pElement)->setUpperEnabled(isEnabled);	
				break;
			}
			pElement = ((CKLBUIContainer*)pElement)->m_pBrother;
		}
	}
}

CKLBUIElement* 
CKLBUIContainer::getChildUI(bool external) 
{
	CKLBNode* pNode;
	
	if (external) {
		pNode = m_outerNode; 
	} else {
		pNode = m_innerNode;
	}

	return (CKLBUIElement*)pNode->getChild();
}

void 
CKLBUIContainer::setViewOffsetX(s32 scrollX) 
{
	this->m_innerNode->setTranslate((float)scrollX,m_innerNode->m_matrix.m_matrix[5]);
}

void 
CKLBUIContainer::setViewOffsetY(s32 scrollY) 
{
	this->m_innerNode->setTranslate(m_innerNode->m_matrix.m_matrix[4],(float)scrollY);
}

void 
CKLBUIContainer::addElement(CKLBUIElement*	pElement, bool external) 
{
	CKLBNode* pNode;
	if (external) {
		pNode = m_outerNode; 
	} else {
		pNode = m_innerNode;
	}

	pNode->addNode(pElement);
}

void 
CKLBUIContainer::removeElement(CKLBUIElement* pElement, bool external) 
{
	CKLBNode* pNode;
	if (external) {
		pNode = m_outerNode; 
	} else {
		pNode = m_innerNode;
	}

	pNode->removeNode(pElement);
}

u32 
CKLBUIContainer::getRadioValue() 
{
	return getRadioValueRecurse(m_innerNode);
}

u32 
CKLBUIContainer::getRadioValueRecurse(CKLBNode* pNode) 
{
	pNode = pNode->getChild();
	while (pNode) {
		u32 res = NO_RADIO_VALUE;
		if (pNode->m_status & UI_TYPE) {
			u32 clID = pNode->getClassID(); 
			if (clID == CLS_KLBUISELECTABLE) {
				CKLBUISelectable* pSelect = (CKLBUISelectable*)pNode;
				if (pSelect->isStickable()) {
					if (pSelect->isEnabled()) {
						if (pSelect->isSticked()) {
							u32 radioID = pSelect->getRadioID();
							if (radioID != NO_RADIO_VALUE) {
								return radioID;
							}
						}
					}
				}
			}
			// Element / Container DO NOTHING.
		} else {
			res = getRadioValueRecurse(pNode);
		}

		if (res != NO_RADIO_VALUE) {
			return res;
		}
		pNode = (((CKLBUIContainer*)pNode)->m_pBrother);
	}

	return NO_RADIO_VALUE;
}

void 
CKLBUIContainer::showModal(CKLBNode* pNode) 
{
	this->m_bAsModal = true;
	pNode->addNode(this);
}
