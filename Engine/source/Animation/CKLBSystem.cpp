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
#include "CKLBNode.h"

//
// Just some wrapping code to avoid dependancy between the game framework class and node system.
//

CKLBNode* gm_animatedList = NULL;

/*static*/void CKLBSystem::removeFromAnimation	(CKLBNode* pNode) {
	klb_assert(pNode,"null pointer");
//	klb_assert(((pNode->m_pAnimationNext != NULL) ||
//			(pNode->m_pAnimationPrev != NULL) || (gm_animatedList == pNode)), "already removed from animation list");

	klb_assert(pNode->isAnimating(), "already removed");

	pNode->m_isAnimated = false;

	//
	// Removed from animation.
	//
	if (pNode->m_pAnimationPrev) {
		pNode->m_pAnimationPrev->m_pAnimationNext	= pNode->m_pAnimationNext;
	} else {
		gm_animatedList								= pNode->m_pAnimationNext;
	}

	if (pNode->m_pAnimationNext) {
		pNode->m_pAnimationNext->m_pAnimationPrev = pNode->m_pAnimationPrev;
	}

	//
	// OPTIMIZE : Clean object optimize (remove setup) + assert in addToAnimation.
	//
	pNode->m_pAnimationNext = NULL;
	pNode->m_pAnimationPrev = NULL;
}

/*static*/void CKLBSystem::addToAnimation		(CKLBNode* pNode) {
	klb_assert(pNode, "null pointer");
	klb_assert(!pNode->isAnimating(), "already added");

	pNode->m_isAnimated = true;

//	klb_assert(((pNode->m_pAnimationNext == NULL) &&
//			(pNode->m_pAnimationPrev == NULL)), "alread in animation list");

	// Head insertion, watch dog garantee pointer exists.
	pNode->m_pAnimationPrev				= NULL;
	pNode->m_pAnimationNext				= gm_animatedList;
	if (gm_animatedList != NULL) {	// OPTIMIZE : Use watchdog instead, remove IF.
		gm_animatedList->m_pAnimationPrev	= pNode;
	}
	gm_animatedList						= pNode;
}

/*static*/CKLBNode* CKLBSystem::getAnimationNodeList() {
	return gm_animatedList;
}

#include "CPFInterface.h"

/*static*/void CKLBSystem::performAnimationUpdate(u32 milliSecDelta) {

	CKLBNode* pNode = gm_animatedList;
	
//	int count = 0;
//	int countSWF = 0;
//	s64 start = CPFInterface::getInstance().platform().nanotime();

	while (pNode) {
		CKLBNode* pNextNode = pNode->m_pAnimationNext;	// Delete can occur inside animate, backup next.
		pNode->animate(milliSecDelta);
//		if (pNode->getClassID() == CLS_KLBSWFMOVIE) {
//			countSWF++;
//		}
//		count++;
		pNode = pNextNode;
	}

//	s64 end = CPFInterface::getInstance().platform().nanotime();
//	end -= start;
//	end /= 1000; // To nano -> uSec
//	CPFInterface::getInstance().platform().logging("Anim : %i, Count : %i, SWF : %i\n",(s32)end, count, countSWF);
}