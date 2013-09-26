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
#include "CKLBScoreNode.h"
#include "mem.h"

CKLBScoreNode::CKLBScoreNode()
:CKLBNode		()
,m_uiScore		(0xFFFFFFFF)
,m_newAnimated	(false)
,m_oldAnimated	(false)
,m_bScoreChange	(true)
,m_dotSprite	(NULL)
,m_dotNode		(NULL)
,m_widthDot		(0)
,m_heightDot	(0)
,m_DotPosition	(0)
,m_prevDotPosition	(0)
{
	m_deleteRender = false; // Force own management of sprite on destruction.
	memset32(m_scoreOldNode, NULL, __SCORE_LEN_MAX__ * sizeof(void*));
	memset32(m_scoreNewNode, NULL, __SCORE_LEN_MAX__ * sizeof(void*));
	memset32(m_font		   , NULL, 11 * sizeof(void*));
	m_animInfo[0].m_hasAnim = false;
	m_animInfo[1].m_hasAnim = false;
}

CKLBScoreNode::~CKLBScoreNode()
{
	CKLBRenderingManager& pMgr = CKLBRenderingManager::getInstance();
	for (int n=0; n < __SCORE_LEN_MAX__; n++) {
		if (m_scoreOldNode[n]) {
			// 1. Back up sprite.
			CKLBRenderCommand* pComm = m_scoreOldNode[n]->getRender();
			m_scoreOldNode[n]->setRender(NULL);
			// 2. Destroy node -> remove from render list if any.
			KLBDELETE(m_scoreOldNode[n]);
			// 3. Destroy sprite if any.
			if (pComm) { pMgr.releaseCommand(pComm); }
		}
		if (m_scoreNewNode[n]) {
			// Order important !
			CKLBRenderCommand* pComm = m_scoreNewNode[n]->getRender();
			m_scoreNewNode[n]->setRender(NULL);
			KLBDELETE(m_scoreNewNode[n]);
			if (pComm) { pMgr.releaseCommand(pComm); }
		}
	}

	if (m_dotNode) {
		m_dotNode->setRender(NULL);
		KLBDELETE(m_dotNode);
	}

	if (m_dotSprite) {
		pMgr.releaseCommand(m_dotSprite);
	}
}

void CKLBScoreNode::setDot(	CKLBImageAsset* dotAsset, s32 width, s32 height ) {
	m_dotSprite->switchImage(dotAsset);
	
	m_widthDot = (float)width;
	m_heightDot= (float)height;
	
	m_dotNode->markUpMatrix();
}

void CKLBScoreNode::setDotActive(u32 position) {
	m_prevDotPosition = position;
}

void CKLBScoreNode::setScore(u32 value, bool animFirstTime) {
	setDotActive(255); // Outside of range.
	setScoreInternal(value, animFirstTime);
}

void CKLBScoreNode::setScoreFloat(float value, u32 dotPosition, bool animFirstTime) {
	static float s_multiplier[10] = {
		1.0f,
		10.0f,
		100.0f,
		1000.0f,
		10000.0f,
		100000.0f,
		1000000.0f,
		10000000.0f,
		100000000.0f,
		1000000000.0f,
	};

	if (dotPosition >= 9) {
		dotPosition = 9;
	}

	value *= s_multiplier[dotPosition];
	
	dotPosition = m_scoreLength - dotPosition;

	// Float to int
	u32 score = (u32)value;
	setScoreInternal(score, animFirstTime);
	setDotActive(dotPosition);
}


bool CKLBScoreNode::init(	u32						basePriority,
							s32						oldNumberPriorityOffset,
							CKLBImageAsset*		 	char0_9[10],
							s32 					stepX,
							s32 					stepY,
							u32 					score_length,
							bool					fillWithZero,
							bool					animAll) {
	bool res = true;
	m_animAll		= animAll;	
	m_default		= (fillWithZero     ) ? 0 : 10;
	m_scoreLength	= (score_length > 9 ) ? 9 : (score_length < 1 ? 1 : score_length);
	m_oldNumberPriorityOffset	= oldNumberPriorityOffset;
	m_stepX			= stepX;
	m_stepY			= stepY;

	memcpy32(m_font, char0_9, 10 * sizeof(CKLBImageAsset*));

	CKLBRenderingManager& pMgr = CKLBRenderingManager::getInstance();

	for (int n = 0; n < __SCORE_LEN_MAX__; n++) {
		m_oldScore[n] = 30; // Only occurs the first time.
	}

	for (int n = 0; n < m_scoreLength; n++) {
		float	fStepX			= (float)(n*m_stepX);
		float	fStepY			= (float)(n*m_stepY);

		m_scoreOldNode[n] = KLBNEW(CKLBSplineNode);
		m_scoreNewNode[n] = KLBNEW(CKLBSplineNode);	
		CKLBSprite* pSpr0 = pMgr.allocateCommandSprite(4,6);
		CKLBSprite* pSpr1 = pMgr.allocateCommandSprite(4,6);

		if ((!m_scoreNewNode[n]) || (!m_scoreOldNode	[n]) || (!pSpr0) || (!pSpr1)) {
			res = false; break;
		}

		m_scoreOldNode[n]->setRender(pSpr0);
		m_scoreNewNode[n]->setRender(pSpr1);

		m_scoreOldNode[n]->setTranslate(fStepX, fStepY);

		((CKLBSprite*)m_scoreOldNode[n]->getRender())->changeOrder(pMgr, basePriority + n + oldNumberPriorityOffset);
		((CKLBSprite*)m_scoreNewNode[n]->getRender())->changeOrder(pMgr, basePriority + n);

		m_scoreNewNode[n]->setTranslate(fStepX, fStepY);
		this->addNode(m_scoreNewNode[n]);

	}

	m_dotSprite = pMgr.allocateCommandSprite(4,6);
	m_dotNode   = KLBNEW(CKLBNode);
	this->addNode(m_dotNode);

	return res && (m_dotSprite != NULL) && (m_dotNode != NULL);
}

void CKLBScoreNode::setPriority(u32 order)
{
	CKLBRenderingManager& pRdr = CKLBRenderingManager::getInstance();

	for (int n = 0; n < m_scoreLength; n++) {
		((CKLBSprite*)m_scoreOldNode[n]->getRender())->changeOrder(pRdr, order + n + m_oldNumberPriorityOffset);
		((CKLBSprite*)m_scoreNewNode[n]->getRender())->changeOrder(pRdr, order + n);
	}
	m_dotSprite->changeOrder(pRdr, order + m_DotPosition + m_oldNumberPriorityOffset);
}

void CKLBScoreNode::setAnimationInternal(	bool	isNew,
											s32		milliSecondsPlayTime,
											s32		timeShift,
											bool	/*onlyChange*/,
											u32		type,
											u32		affected,
											const float* arrayParam) {
	AnimInfo* pAnim = &m_animInfo[isNew ? 1 : 0];
	float* dst = pAnim->m_Anim;
	if (affected & CKLBSplineNode::ANM_X_COORD_0)		{   *dst++ = *arrayParam++;  *dst++ = *arrayParam++; }
	if (affected & CKLBSplineNode::ANM_Y_COORD_1)		{   *dst++ = *arrayParam++;  *dst++ = *arrayParam++; }
	if (affected & CKLBSplineNode::ANM_SCALE_COORD_2)	{   *dst++ = *arrayParam++;  *dst++ = *arrayParam++;
															*dst++ = *arrayParam++;  *dst++ = *arrayParam++; }
	if (affected & CKLBSplineNode::ANM_R_COLOR_3)		{   *dst++ = *arrayParam++;  *dst++ = *arrayParam++; }
	if (affected & CKLBSplineNode::ANM_G_COLOR_4)		{   *dst++ = *arrayParam++;  *dst++ = *arrayParam++; }
	if (affected & CKLBSplineNode::ANM_B_COLOR_5)		{   *dst++ = *arrayParam++;  *dst++ = *arrayParam++; }
	if (affected & CKLBSplineNode::ANM_A_COLOR_6)		{   *dst++ = *arrayParam++;  *dst++ = *arrayParam++; }

	pAnim->m_affected				= affected;
	pAnim->m_milliSecondsPlayTime	= milliSecondsPlayTime;
	pAnim->m_type					= type;
	pAnim->m_timeShift				= timeShift;
	pAnim->m_hasAnim				= affected != 0;
	reAssignAnim(isNew ? 1 : 0);
}

void CKLBScoreNode::reAssignAnim(u32 idx) {
	float localFloat[16];

	AnimInfo* pAnim = &m_animInfo[idx];
	if (pAnim->m_hasAnim) {
		CKLBSplineNode** pNodeArr = (idx != 0) ? m_scoreNewNode : m_scoreOldNode;

		const float* backup = pAnim->m_Anim;
		memcpy(localFloat, backup, sizeof(float)*16);
		for (int n=0; n < m_scoreLength; n++) {
			float* backup = pAnim->m_Anim;
			float*	dst             = localFloat;
			int		m				= m_scoreLength - n;
			int		timeShiftLocal	= m*pAnim->m_timeShift;

			float   offsetX			= ((n >= m_DotPosition) ? m_widthDot : 0.0f);
			float   offsetY			= ((n >= m_DotPosition) ? m_heightDot: 0.0f);

			float	fStepX			= ((float)(n*m_stepX)) + offsetX;
			float	fStepY			= ((float)(n*m_stepY)) + offsetY;

			if (pAnim->m_affected & CKLBSplineNode::ANM_X_COORD_0)	{   *dst++ = (*backup++) + fStepX;  *dst++ = (*backup++) + fStepX; }
			if (pAnim->m_affected & CKLBSplineNode::ANM_Y_COORD_1)	{   *dst++ = (*backup++) + fStepY;  *dst++ = (*backup++) + fStepY; }

			pNodeArr[n]->setAnimation(pAnim->m_milliSecondsPlayTime, timeShiftLocal, pAnim->m_type, NULL, 0, pAnim->m_affected, localFloat);
		}
	}
}

/**
	No animation : affected = 0
 */
void CKLBScoreNode::setEnterAnimation	(s32 milliSecondsPlayTime, s32 timeShift, bool onlyChange, u32 type, u32 affected, const float* arrayParam)
{
	if (!arrayParam) { affected = 0; }

	//
	// Enter animation : never remove.
	//
	affected &= ~CKLBSplineNode::ANM_REMOVESCENE;

	setAnimationInternal(true, milliSecondsPlayTime, timeShift, onlyChange, type, affected, arrayParam);

	m_newAnimated = (affected != 0);
}

void CKLBScoreNode::setExitAnimation	(s32 milliSecondsPlayTime, s32 timeShift, bool onlyChange, u32 type, u32 affected, const float* arrayParam)
{
	if (!arrayParam) { affected = 0; }

	setAnimationInternal(false, milliSecondsPlayTime, timeShift, onlyChange, type, affected | CKLBSplineNode::ANM_REMOVESCENE, arrayParam);

	m_oldAnimated = (affected != 0);
}

void CKLBScoreNode::setScoreInternal	(u32 score, bool /*animFirstTime*/)
{
	if (score != m_uiScore) {	
		m_uiScore       = score;
		m_bScoreChange  = true;
	}
}

void CKLBScoreNode::update() {
	if (m_prevDotPosition != m_DotPosition) {
		m_DotPosition = m_prevDotPosition;
		if (m_DotPosition >= m_scoreLength) {
			
			m_dotNode->setRender(NULL,0);

			reAssignAnim(0);
			reAssignAnim(1);

			for (int n = 0; n < m_scoreLength; n++) {
				float	fStepX			= (float)(n*m_stepX);
				float	fStepY			= (float)(n*m_stepY);

				m_scoreOldNode[n]->setTranslate(fStepX, fStepY);
				m_scoreNewNode[n]->setTranslate(fStepX, fStepY);
			}
		} else {

			m_dotNode->setRender(m_dotSprite);

			reAssignAnim(0);
			reAssignAnim(1);

			for (int n = 0; n < m_scoreLength; n++) {
				float offsetX = ((n >= m_DotPosition) ? m_widthDot : 0.0f);
				float offsetY = ((n >= m_DotPosition) ? m_heightDot : 0.0f);

				float	fStepX			= ((float)(n*m_stepX)) + offsetX;
				float	fStepY			= ((float)(n*m_stepY)) + offsetY;

				if (n == m_DotPosition) {
					m_dotNode->setTranslate(fStepX - offsetX, fStepY - offsetY);
				}

				m_scoreOldNode[n]->setTranslate(fStepX, fStepY);
				m_scoreNewNode[n]->setTranslate(fStepX, fStepY);
			}
		}
	}

	if (m_bScoreChange) {
		u32 score = m_uiScore;
		u8 newScore[10];
		m_bScoreChange = false;
		// Reset.
		newScore[0 ] = 0;  //m_default; // 0fill���Ȃ��ꍇ�ł�A1���ڂ�0�͕\������B
		newScore[1 ] = m_default;
		newScore[2 ] = m_default;
		newScore[3 ] = m_default;
		newScore[4 ] = m_default;
		newScore[5 ] = m_default;
		newScore[6 ] = m_default;
		newScore[7 ] = m_default;
		newScore[8 ] = m_default;
		newScore[9 ] = m_default;

		// Convert int into units.
		while (score >=1000000000) {	score -=1000000000;	newScore[9]++;	}
		while (score >= 100000000) {	score -= 100000000;	newScore[8]++;	}
		while (score >=  10000000) {	score -=  10000000;	newScore[7]++;	}
		while (score >=   1000000) {	score -=   1000000;	newScore[6]++;	}
		while (score >=    100000) {	score -=    100000;	newScore[5]++;	}
		while (score >=     10000) {	score -=     10000;	newScore[4]++;	}
		while (score >=      1000) {	score -=      1000;	newScore[3]++;	}
		while (score >=       100) {	score -=       100;	newScore[2]++;	}
		while (score >=        10) {	score -=        10;	newScore[1]++;	}
		while (score >=         1) {	score -=         1;	newScore[0]++;	}

		//
		// Manage to handle that fill 0 with empty space works only for the BEGINNING of the score
		// ie : 000010000 -> ____10000
		//
		if (m_default != 0) {
			bool resetFill = false;
			for (int n = m_scoreLength; n>=0; n--) {
				if (newScore[n] != 10) {
					resetFill = true;
					if (newScore[n] > 10) {
						newScore[n] -= 10;
					}
				} else {
					if (n <= m_scoreLength - m_DotPosition) {
						resetFill = true;
					}
					if (resetFill) {
						newScore[n] = 0;
					}
				}
			}
		}

		//
		// Perform display switch.
		//
		for (int n = 0; n < m_scoreLength; n++) {
			// From higher to lower.
			int m = ((m_scoreLength-1) - n);
			if ((m_oldScore[n] != newScore[n]) || m_animAll) {
				// New score graphic setup
				CKLBImageAsset* pAsset = m_font[newScore[n]];

				// ---- Atomic Operation ----
				((CKLBSprite*)m_scoreNewNode[m]->getRender())->switchImage(pAsset);

				// Changed only UV but node recompute use matrix changes.
				m_scoreNewNode[m]->markUpMatrixAndColor();
				// --------------------------

				// Set animation if needed.
				if (m_newAnimated) {
					// Set new font item.
					m_scoreNewNode[m]->play();	// Reset time. (add to animation system is also done by the function)
				}

				// If old animation is needed.
				if (m_oldAnimated) {
					//
					// Put back in scene graph if animation is already complete.
					//
					if (m_scoreOldNode[m]->getParent() == NULL) {
						this->addNode(m_scoreOldNode[m], 0);
					}

					// Assign bitmap
					CKLBImageAsset* pAsset = m_font[m_oldScore[n]];
					
					// ---- Atomic Operation ----
					((CKLBSprite*)m_scoreOldNode[m]->getRender())->switchImage(pAsset);
					// Changed only UV but node recompute use matrix changes.
					m_scoreOldNode[m]->markUpMatrixAndColor();
					// --------------------------

					// Restart animation.
					m_scoreOldNode[m]->play();	// Reset time. (add to animation system is also done by the function)
				}
			}
			m_oldScore[n] = newScore[n];
		}
	}
}
