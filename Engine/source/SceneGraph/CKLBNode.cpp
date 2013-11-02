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
#include "string.h"
#include "CKLBUITask.h"

#ifdef DEBUG_PERFORMANCE
/*static*/ u32	CKLBNode::s_vertexRecomputeCount = 0;
/*static*/ u32	CKLBNode::s_matrixRecomputeCount = 0;
/*static*/ u32  CKLBNode::s_colorRecomputeCount  = 0;
#endif

/*static*/ float CKLBNode::s_fLeftBorder	=	-500.0f;
/*static*/ float CKLBNode::s_fRightBorder	=  +1500.0f;
/*static*/ float CKLBNode::s_fTopBorder		=	-400.0f;
/*static*/ float CKLBNode::s_fBottomBorder	=  +1200.0f;

SMatrix2D::SMatrix2D()
{
	m_matrix[0] = 1.0f;
	m_matrix[1] = 0.0f;
	m_matrix[2] = 0.0f;
	m_matrix[3] = 1.0f;
	m_matrix[4] = 0.0f;
	m_matrix[5] = 0.0f;
	m_type		= MATRIX_ID;
}

SColorVector::SColorVector()
{
	m_vector[0] = 1.0f;
	m_vector[1] = 1.0f;
	m_vector[2] = 1.0f;
	m_vector[3] = 1.0f;
	m_type		= MATRIX_ID;
}

CKLBNode::CKLBNode():
	CKLBObject			(),
	m_pBrother			(NULL),
	// Is visible but not connected = not visible from parent
	m_status			(ANY_CHANGE | MARKED | INVISIBLE_UPPER),	// Invisible from outside by def
	m_parent			(NULL),
	m_pChild			(NULL),
	m_useParentColor	(true),
	m_pColorMatrix		(NULL),
	m_pAnimationNext	(NULL),
	m_pAnimationPrev	(NULL),
	m_pRender			(NULL),
	m_renderSlot		(NULL),
	m_layer				(0),
	m_movieID			(0),
	m_renderCount		(1),
	m_deleteRender		(true),
	m_name				(NULL),
	m_uitask			(NULL),
	m_isAnimated		(false),
	m_nameLength		(0),
	m_rot				(0.0f),
	m_scaleX			(1.0f),
	m_scaleY			(1.0f),
	m_bInternalNode		(true),
	m_reject			(false)
{
	m_pColorMatrix	= &m_colorMatrix;
	m_pRender		= &m_renderSlot;
}

/*virtual*/
CKLBNode* CKLBNode::clone(CKLBNode* newItem, CKLBNode* parent, CKLBNode* brother, bool transferSpriteOwnership) {
	if (newItem == NULL) {
		newItem = KLBNEW(CKLBNode);
	}

	if (newItem) {
		//
		// Recursive parse tree.
		//
		CKLBNode* pChild	= m_pChild;
		CKLBNode* pBrother	= NULL;
		while (pChild) {
			pBrother = pChild->clone(NULL, newItem, pBrother, transferSpriteOwnership);
			newItem->addNode(pBrother,pBrother->getLayer());
			pChild		= pChild->m_pBrother;
		}
		newItem->m_parent					= parent;

		newItem->m_matrix					= m_matrix;
		newItem->m_localColorMatrix			= m_localColorMatrix;

	//	Disconnected by default : CTOR default.
	//  Recomputed when tree connect.
	//	SMatrix2D			m_composedMatrix;
	//	SColorVector		m_colorMatrix;

		if (m_name) {
			newItem->m_name = CKLBUtility::copyString(m_name);
		}
		newItem->m_uitask					= m_uitask;

	//	Disconnected by default : CTOR default
	//	CKLBNode*			m_pAnimationNext;
	//	CKLBNode*			m_pAnimationPrev;
	//	m_isAnimated;

		if (m_pColorMatrix != &m_colorMatrix) {
			if (parent) {
				newItem->m_pColorMatrix = parent->m_pColorMatrix;
			}
		}

		if (m_pRender != &m_renderSlot) {
			newItem->m_pRender = KLBNEWA(CKLBRenderCommand*,m_renderCount);
		}

		for (u32 n=0; n < m_renderCount; n++) {
			if (transferSpriteOwnership) {
				newItem->setRenderRef	(this->getRender(n),n);
			} else {
				newItem->setRender		(this->getRender(n),n);
			}
		}

		newItem->m_rot				= m_rot;
		newItem->m_scaleX			= m_scaleX;
		newItem->m_scaleY			= m_scaleY;
		newItem->m_renderCount		= m_renderCount;

		newItem->m_groupID			= m_groupID;
		newItem->m_status			= m_status | INVISIBLE_UPPER;

		if (parent == NULL) {
			newItem->m_status |= ANY_CHANGE | MARKED;
		}

		newItem->m_layer			= m_layer;
		newItem->m_movieID			= m_movieID;
		newItem->m_updateFrame		= m_updateFrame;
		newItem->m_nameLength		= m_nameLength;

		if (transferSpriteOwnership) {
			// Clone now own the sprite
			newItem->m_deleteRender		= true;
			this->m_deleteRender		= false;
		} else {
			// Original own the sprite
			newItem->m_deleteRender		= false;
		}

		newItem->m_bInternalNode	= m_bInternalNode;
		newItem->m_useParentColor	= m_useParentColor;
		newItem->m_reject			= m_reject;
	}

	return newItem;
}



CKLBNode::~CKLBNode() {
	// "Save the children" ;-)
	CKLBNode* pChildList = m_pChild;

	if (m_status & ANIMATED) {
		if (isAnimating()) {
			CKLBSystem::removeFromAnimation(this);
		}
		m_status &= ~ANIMATED;
	}

	// Clean list BEFORE, avoid recursion.
	m_pChild = NULL; setVisible(false);

	releaseSlots();

	CKLBNode* pChildListNext;
	while (pChildList) {
		pChildListNext = pChildList->m_pBrother;
		pChildList->m_parent = NULL;	// Avoid unlinking for all child.
		if (!pChildList->getUITask()) {
			KLBDELETE(pChildList);
		}
		pChildList = pChildListNext;
	}

	if (m_parent) {
		// Only top node will enter here.
		m_parent->removeNode(this);
	}

	KLBDELETEA(m_name);
}

void CKLBNode::dump(u32 level, u32 mask) {
	FILE* pFile = CPFInterface::getInstance().client().getShellOutput();

	// 
	for (u32 n=0; n < level; n++) { printf("  "); }

	// Type
	switch (this->getClassID()) {
	case CLS_KLBNODE:
		if (this->m_parent == NULL) {
			fprintf(pFile,"Root");
		} else {
			fprintf(pFile,"Node");
		}
		break;
	case CLS_KLBUIELEMENT:
		fprintf(pFile,"Element");
		break;
	case CLS_KLBUISELECTABLE:
		fprintf(pFile,"Selectable");
		break;
	case CLS_KLBUICONTAINER:
		fprintf(pFile,"Container");
		break;
	case CLS_KLBSWFMOVIE:
		fprintf(pFile,"Flash Movie");
		break;
	case CLS_KLBSPLINENODE:
		fprintf(pFile,"Anim Node");
		break;
	case CLS_KLBNODEMAP:
		fprintf(pFile,"Map");
		break;
	case CLS_KLBSCORENODE:
		fprintf(pFile,"Score");
		break;
	case CLS_KLBCELLANIMNODE:
		fprintf(pFile,"Cell Anim");
		break;
	case CLS_KLBTEXTEDIT:
		fprintf(pFile,"Text Input");
		break;
	case CLS_KLBWEBVIEW:
		fprintf(pFile,"Web View");
		break;
	default:
		fprintf(pFile,"Other");
		break;
	}

	// Ptr
	fprintf(pFile," @%p ",this);

	// Name
	if (this->m_name) {
		fprintf(pFile,"(%s) ", this->m_name);
	}

	// Render object associated
	fprintf(pFile,"%i", this->m_renderCount);
	switch (this->m_composedMatrix.m_type) {
	case MATRIX_ID:
		fprintf(pFile," [ID]");
		break;
	case MATRIX_T:
		fprintf(pFile," [T]");
		break;
	case MATRIX_TS:
		fprintf(pFile," [TS]");
		break;
	case MATRIX_TG:
		fprintf(pFile," [TG]");
		break;
	}

	if (this->m_status & INVISIBLE) {
		fprintf(pFile," INVISIBLE");
	} else {
		fprintf(pFile," VISIBLE");
	}

	if (this->m_status & INVISIBLE_UPPER) {
		fprintf(pFile," PARENT-INVISIBLE");
	}

	if (mask & 4) {
		if (this->m_uitask) {
			fprintf(pFile," TASK:@%p",this->m_uitask);
		}
	}

	if (mask & 2) {
		for (u32 m=0; m < m_renderCount; m++) {
			fprintf(pFile,"\n    ");
			for (u32 n=0; n < level; n++) { fprintf(pFile,"  "); }

			if (this->getRender(m)) {
				fprintf(pFile," @%p (%i)",this->getRender(m),this->getRender(m)->getOrder());
			} else {
				fprintf(pFile," @NULL ");
			}
		}
	}

	if (mask & 1) {
		for (int m=0; m < 4; m++) {
			fprintf(pFile,"\n    ");
			for (u32 n=0; n < level; n++) { printf("  "); }
			fprintf(pFile,"%3i <- %3i",(int)(this->m_colorMatrix.m_vector[m] * 255), (int)(this->m_localColorMatrix.m_vector[m] * 255));
		}
	}

	fprintf(pFile,"\n");

	CKLBNode* pParse = this->m_pChild;
	level++;
	while (pParse) {
		pParse->dump(level, mask);
		pParse = pParse->m_pBrother;
	}
}

bool CKLBNode::setName(const char * name)
{
	char * buf;
	KLBDELETEA(m_name);

	if(name) {
		buf = KLBNEWA(char, strlen(name) + 1);
		if(!buf) return false;
		strcpy(buf, name);
	} else {
		buf = NULL;
	}
	m_name = buf;
	m_nameLength = m_name ? strlen(m_name) : 0;

	return true;
}

CKLBNode* CKLBNode::search(const char* name) {
	CKLBNode* res = NULL;

	if (m_name && (strncmp(m_name,name,m_nameLength)==0)) {
		if (name[m_nameLength] == 0) {
			return this;
		} else {
			// Get Next
			const char* next = name;
			while ((*next != 0) && (*next != '.')) {
				next++;
			}
			if (*next != 0) {
				next++; // Skip '.'
				res = search(next);
			}
		}
	}

	if (!res) {
		CKLBNode* pChild = this->m_pChild;
		while (pChild) {
			res = pChild->search(name);
			if (res) {
				return res;
			}
			pChild = pChild->m_pBrother;
		}
	}

	return res;

	/*
	if (m_name && (strcmp(name, m_name) == 0)) {
		return this;
	}

	CKLBNode* pChild = this->m_pChild;
	while (pChild) {
		CKLBNode* res = pChild->search(name);
		if (res) {
			return res;
		}
		pChild = pChild->m_pBrother;
	}

	return NULL;
	*/
}

CKLBNode* CKLBNode::searchFirstByTypeID(u32 typeID) {
	if (typeID == m_uitask->getClassID()) {
		return this;
	}

	CKLBNode* pChild = this->m_pChild;
	while (pChild) {
		CKLBNode* res = pChild->searchFirstByTypeID(typeID);
		if (res) {
			return res;
		}
		pChild = pChild->m_pBrother;
	}

	return NULL;
}

void CKLBNode::releaseSlots() {
	CKLBRenderingManager& pMgr = CKLBRenderingManager::getInstance();

	for (u32 n=0; n < m_renderCount; n++) {
		if (m_pRender[n]) {
			if (m_pRender[n]->isInRenderList()) {
				pMgr.removeFromRendering(m_pRender[n]);
			}
			if (m_deleteRender) {
				pMgr.releaseCommand(m_pRender[n]);
			}
			m_pRender[n] = NULL;
		}
	}

	if (m_renderCount != 1) {
		if (m_pRender)		{	KLBDELETEA(m_pRender);		}
		m_pRender			= NULL;
		m_renderCount		= 0;
	}
}

bool CKLBNode::setRenderSlotCount	(u32 slot) {
	bool res = true;
	releaseSlots();

	if (slot != 1) {
		CKLBRenderCommand**
				newComm	= KLBNEWA(CKLBRenderCommand*,	slot);

		if (newComm) {
			m_renderCount = slot;
			m_pRender	= newComm;
			memset(newComm, NULL, sizeof(CKLBRenderCommand*) * slot);
		} else {
			slot = 1;
			res = false;
		}
	}

	if (slot == 1) {
		m_pRender		= &m_renderSlot;
		m_renderCount = 1;
	}

	return res;
}

CKLBNode* CKLBNode::getNode(u16 layer) {
	CKLBNode* pList	= m_pChild;

	while (pList) {
		if (pList->m_layer == layer) {
			return pList;
		}
		pList = pList->m_pBrother;
	}

	return NULL;
}

void CKLBNode::addNode(CKLBNode* pNode, u16 layer) {
	klb_assertNull(pNode, "null node");
	klb_assert((pNode != this), "Impossible to do this node tree operation");

	//
	// Remove from previous parent.
	//
	if (pNode) {
		if (pNode->m_parent) {
			pNode->m_parent->removeNode(pNode);
		}

		//
		// Perform insertion.
		//
		CKLBNode* pList	= m_pChild;
		CKLBNode* pPrev	= NULL;

		while (pList) {
			if (pList->m_layer >= layer) {
				break;
			}
			pPrev = pList;
			pList = pList->m_pBrother;
		}

		if (pList != NULL) {
			if (pPrev != NULL) {
				// Force insertion with closest layer.
				pNode->m_pBrother = pPrev->m_pBrother;
				pPrev->m_pBrother = pNode;
			} else {
				// Beginning of list.
				m_pChild = pNode;
				pNode->m_pBrother = pList;
			}
		} else {
			if (pPrev != NULL) {
				// End of list
				pPrev->m_pBrother = pNode;
			} else {
				// Beginning of list.
				m_pChild = pNode;
			}
		}

		pNode->m_parent = this;
		pNode->m_layer	= layer;

		//
		// If parent node is visible and sub node is visible itself also -> Visible
		//
		if (m_status & (INVISIBLE | INVISIBLE_UPPER)) {
			// Node has already been disconnected from previous owner OR never been connected
			// pNode->m_status |= INVISIBLE_UPPER; already SET.
		} else {
			// Reset owner invisible flag
			pNode->m_status &= ~INVISIBLE_UPPER;

			// Item is visible
			if ((pNode->m_status & INVISIBLE)==0) {
				// Add to rendering list.
				pNode->visibleSelf();
				// Apply logic to child.
				pNode->visibleUpperRecursive();
			}
		}
	}
}

void CKLBNode::removeNode(CKLBNode* pChild) {
	CKLBNode* pList	= m_pChild;
	CKLBNode* pPrev	= NULL;

	while (pList) {
		if (pList == pChild) {
			// Beginning of list
			if (pPrev == NULL) {
				m_pChild = pChild->m_pBrother;
			// Middle / End of list
			} else {
				pPrev->m_pBrother = pChild->m_pBrother;
			}

			if (pList->isVisible()) {
				pList->invisibleSelf();
				pList->invisibleUpperRecursive();
			}

			// Force removal from animation and rendering system of whole sub tree.
			pList->m_status |= INVISIBLE_UPPER;	// Reset invisible upper as disconnected.

			// do NOT "delete pChild;"
			pChild->m_parent = NULL;

			// remove brother link
			pChild->m_pBrother = NULL;

			break;
		}
		pPrev = pList;
		pList = pList->m_pBrother;
	}
}

void CKLBNode::addRender() {
	for (u32 n = 0; n<this->m_renderCount; n++) {
		if (m_pRender[n]) {
			CKLBRenderingManager::getInstance().addToRendering(m_pRender[n], m_pRender[n]->m_uiOrder);
		}
	}
}

void CKLBNode::removeRender() {
	for (u32 n = 0; n<this->m_renderCount; n++) {
		if (m_pRender[n]) {
			CKLBRenderingManager::getInstance().removeFromRendering(m_pRender[n]);
		}
	}
}

/*inline*/ void CKLBNode::visibleSelf() {
	markUpTree();
	m_status |= ANY_CHANGE;

	/* Animation system is independent of visual aspect.

	// Is animated and not connected ?
	if ((m_status & ANIMATED) && (!isAnimating())) {
		CKLBSystem::addToAnimation(this);
	}
	*/
	addRender();	// Virtual function.
}

/*inline*/ void CKLBNode::invisibleSelf() {
	/* Animation system is independent of visual aspect.
	if ((m_status & ANIMATED) && (isAnimating())) {
		CKLBSystem::removeFromAnimation	(this);
	}
	*/
	removeRender();	// Virtual function.
}

void CKLBNode::visibleUpperRecursive() {
	CKLBNode* p = m_pChild;
	while (p) {
		if (p->m_status & INVISIBLE_UPPER) {
			p->m_status &= ~INVISIBLE_UPPER; // Clear flag
			if ((p->m_status & INVISIBLE) == 0) {
				// Item has visible flag -> Make it really visible.
				p->visibleSelf();
				p->visibleUpperRecursive();
			}
		} 
		// else : NO UPPER +   VISIBLE : Already visible,do nothing.
		// else : NO UPPER + INVISIBLE : Stay hidden,    do nothing.
		p = p->m_pBrother;
	}
}

void CKLBNode::invisibleUpperRecursive() {
	CKLBNode* p = m_pChild;
	while (p) {
		// No upper set
		if ((p->m_status & INVISIBLE_UPPER) == 0) {
			p->m_status |= INVISIBLE_UPPER; // Set flag
			// Is Visible -> becomes invisible
			if ((p->m_status & INVISIBLE) == 0) {
				p->invisibleSelf();
				p->invisibleUpperRecursive();
			}
			// else Invisible	: already invisible : do nothing.
		} // else UPPER is already set, change nothing to all items.
		p = p->m_pBrother;
	}
}

void CKLBNode::setVisible(bool isVisible) {

	if (isVisible) {
		if (m_status & INVISIBLE_UPPER) {
			// Still invisible from upper object.
			m_status &= ~INVISIBLE;	// Reset flag only.
		} else {
			if (m_status & INVISIBLE) {
				m_status &= ~INVISIBLE;	// Reset flag.
				visibleSelf();
				visibleUpperRecursive();
			} else {
				// No changes.
			}
		}
	} else {
		if ((m_status & INVISIBLE_UPPER) == 0) {
			if (m_status & INVISIBLE) {
				// No Changes
			} else {
				m_status |= INVISIBLE;
				invisibleSelf();
				invisibleUpperRecursive();
			}
		} else {
			m_status |= INVISIBLE;
		}
	}
}

void CKLBNode::clearSubTree() {
	CKLBNode* pList	= m_pChild;

	while (pList) {
		CKLBNode* pNext = pList->m_pBrother;

		pList->m_parent = NULL; // Avoid recursive stupid calls.

		KLBDELETE(pList);
		pList = pNext;
	}

	m_pChild = NULL;
}

CKLBNode* CKLBNode::searchCommand(CKLBRenderCommand* comm) {
	for (u32 n=0; n<this->m_renderCount; n++) {
		if (m_pRender[n] == comm) {
			return this;
		}
	}

	CKLBNode* pList = m_pChild;
	while (pList) {
		CKLBNode* result = pList->searchCommand(comm);
		if (result) {
			return result;
		}
		pList = pList->m_pBrother;
	}

	return NULL;
}

void CKLBNode::setRender(CKLBRenderCommand* pRender, u32 indexRender) {
	klb_assert((indexRender < m_renderCount), "wrong indexRender");
	CKLBRenderingManager& pMgr = CKLBRenderingManager::getInstance();
	if (m_pRender[indexRender] != NULL) {
		m_pRender[indexRender]->decrementCount();
		if (m_pRender[indexRender]->isInRenderList()) {
			pMgr.removeFromRendering(m_pRender[indexRender]);
		}
	}

	m_pRender[indexRender] = pRender;
	markUpColor();	// Force sprite to recompute color.

	if (pRender) {
		pRender->incrementCount();
		if (this->isVisible()) {
			pMgr.addToRendering(pRender, pRender->m_uiOrder);
		}
	}
}

void CKLBNode::setRenderRef(CKLBRenderCommand* pRender, u32 indexRender) {
	klb_assert((indexRender < m_renderCount), "wrong indexRender");
	m_pRender[indexRender] = pRender;
	if (pRender) {
		pRender->incrementCount();
	}
}

/*
void CKLBNode::rejectSub() {
	for (u32 n=0; n<this->m_renderCount; n++) {
		if (m_pRender[n]) {
			m_pRender[n]->m_uiStatus |= FLAG_IGNORERENDER;
		}
	}
}*/

void CKLBNode::recompute() {
	if (isVisible()) {
		if (m_parent) {
			m_status |= m_parent->m_status & ANY_CHANGE; // If parent changed -> force myself to change.
		}

		bool force = ((m_status & (MATRIX_CHANGE | CMATRIX_CHANGE)) != 0);
		if (force) {
			updateMatrices();
		}

		if (force) {									// TODO Optimize using RENDER_CHANGE
			// Apply tranform/color to each vertex.
			for (u32 n=0; n<this->m_renderCount; n++) {
				if (m_pRender[n]) {
					if (m_status & MATRIX_CHANGE) {		// TODO remove when use RENDER_CHANGE
						if (!m_reject) {
							m_pRender[n]->m_commandType &= ~RENDERCOMMAND_IGNORE;
							m_pRender[n]->m_uiStatus	|= FLAG_BUFFERSHIFT | FLAG_UVUPDATE;
							m_pRender[n]->applyNode(this);
						} else {
							m_pRender[n]->m_commandType |= RENDERCOMMAND_IGNORE;
							m_pRender[n]->m_uiStatus	|= FLAG_BUFFERSHIFT;
						}
					}
					if (m_status & CMATRIX_CHANGE) {	// TODO remove when use RENDER_CHANGE
						//
						// Get Sprite Color
						//
						applyColor(m_pRender[n]);
					}
				}
			}
		}

		for (u32 n=0; n<this->m_renderCount; n++) {
			if (m_pRender[n]) {
				if (!this->m_reject) {
					m_pRender[n]->m_uiStatus &= ~FLAG_IGNORERENDER;
					m_pRender[n]->applyNode(this);
				} else {
					m_pRender[n]->m_uiStatus |= ~FLAG_IGNORERENDER;
				}
			}
		}

		if (m_status & ANY_CHANGE) {
			recomputeCustom();
		}

		//
		// Once node is locally completly updated, update child.
		// (We avoid testing flags of child and do it in the recursion instead, avoid testing twice at the cost of a call)
		if ((m_status & MARKED) || force) {	// Sub item need computation
			CKLBNode* pChild = m_pChild;

			while (pChild) {
				pChild->recompute();
				pChild = pChild->m_pBrother;
			}
		}
		// Reset all flags
		m_status &= ~(ANY_CHANGE | MARKED);
	}
}

void CKLBNode::updateMatrices() {
	//
	// 2. Matrix update
	//
	if (m_status & MATRIX_CHANGE) {	// if root do nothing.
		if (m_parent) {
			SMatrix2D* pParMat = &m_parent->m_composedMatrix;
			if (pParMat->m_type != MATRIX_ID) {
				SMatrix2D* pCurMat = &m_matrix;
				SMatrix2D* pCompMat = &m_composedMatrix;

				// OPTIMIZE RP Optimize based on matrix type from stream (need to locally update type also)

				//
				// Matrix Composition.
				//

				//
				// Load Matrix from local matrix.
				//
#ifdef DEBUG_PERFORMANCE
				s_matrixRecomputeCount++;
#endif

				#define M2(a)		(pCurMat->m_matrix[a])
				#define M1(a)		(pParMat->m_matrix[a])
				#define M(a,b)		a->m_matrix[b]
				float tx;
				float ty;
				if ((pParMat->m_type < MATRIX_TS)) {
					// If parent is Identity or translation. -> Copy local matrix directly to compose, just translate.
					tx	= M2(MAT_TX) + M1(MAT_TX);
					ty	= M2(MAT_TY) + M1(MAT_TY);
					M(pCompMat,MAT_TX)	= tx;
					M(pCompMat,MAT_TY)	= ty;
					M(pCompMat,MAT_A)	= M2(MAT_A);
					M(pCompMat,MAT_B)	= M2(MAT_B);
					M(pCompMat,MAT_C)	= M2(MAT_C);
					M(pCompMat,MAT_D)	= M2(MAT_D);
				} else {
					float a	= (M1(MAT_A)*M2(MAT_A)) + (M1(MAT_B)*M2(MAT_C));
					float b	= (M1(MAT_A)*M2(MAT_B)) + (M1(MAT_B)*M2(MAT_D));
					float c	= (M1(MAT_C)*M2(MAT_A)) + (M1(MAT_D)*M2(MAT_C));
					float d	= (M1(MAT_C)*M2(MAT_B)) + (M1(MAT_D)*M2(MAT_D));
					tx	= (M1(MAT_A)*M2(MAT_TX)) + (M1(MAT_B)*M2(MAT_TY)) + M1(MAT_TX);
					ty	= (M1(MAT_C)*M2(MAT_TX)) + (M1(MAT_D)*M2(MAT_TY)) + M1(MAT_TY);

					M(pCompMat,MAT_A)	= a;
					M(pCompMat,MAT_B)	= b;
					M(pCompMat,MAT_C)	= c;
					M(pCompMat,MAT_D)	= d;
					M(pCompMat,MAT_TX)	= tx;
					M(pCompMat,MAT_TY)	= ty;
				}

				switch (pParMat->m_type) {
				case MATRIX_T	:
					switch (pCurMat->m_type) {
					case MATRIX_ID	:
					case MATRIX_T	:	pCompMat->m_type = MATRIX_T;		break;
					default:			pCompMat->m_type = pCurMat->m_type; break;
					}
					break;
				case MATRIX_TS	:
					switch (pCurMat->m_type) {
					case MATRIX_ID	:
					case MATRIX_TS	:
					case MATRIX_T	:	pCompMat->m_type = MATRIX_TS;		break;
					default:			pCompMat->m_type = pCurMat->m_type; break;
					}
					break;
				case MATRIX_TG	:	pCompMat->m_type = MATRIX_TG; break;
				/* Case done with lower else 
				case MATRIX_ID	:
					break;
				 */
				}
			} else {
				m_composedMatrix = m_matrix;
			}

			if (   (m_composedMatrix.m_matrix[MAT_TX] >= s_fLeftBorder) && (m_composedMatrix.m_matrix[MAT_TX] <= s_fRightBorder)
				&& (m_composedMatrix.m_matrix[MAT_TY] >= s_fTopBorder ) && (m_composedMatrix.m_matrix[MAT_TY] <= s_fBottomBorder)
			   )
			{
				m_reject = false;
			} else {
				m_reject = true;
			}

		} else {
			// Root : Copy matrix to composed matrix.
			m_composedMatrix = m_matrix;
			m_reject = false;
		}
	}
	
	if (m_useParentColor) {
		// Propagate matrix.
		if (m_parent) {
			m_pColorMatrix = m_parent->m_pColorMatrix;
		}
	} else {
		// Use self color
		if (m_status & CMATRIX_CHANGE) {
			// OPTIMIZE RP : Can use type from stream and avoid testing all components.
			if ((this->m_localColorMatrix.m_vector[0] == 1.0f) &&
				(this->m_localColorMatrix.m_vector[1] == 1.0f) &&
				(this->m_localColorMatrix.m_vector[2] == 1.0f) &&
				(this->m_localColorMatrix.m_vector[3] == 1.0f)) {
				if (m_parent) {
					m_pColorMatrix = m_parent->m_pColorMatrix; // Identity use parent directly.
				} else {
					m_pColorMatrix = &m_colorMatrix;
					m_colorMatrix.m_vector[0] = m_localColorMatrix.m_vector[0];
					m_colorMatrix.m_vector[1] = m_localColorMatrix.m_vector[1];
					m_colorMatrix.m_vector[2] = m_localColorMatrix.m_vector[2];
					m_colorMatrix.m_vector[3] = m_localColorMatrix.m_vector[3];
				}
			} else {
				m_pColorMatrix = &this->m_colorMatrix; // Used local composed color matrix.
				m_colorMatrix.m_vector[0] = m_parent->m_pColorMatrix->m_vector[0] * m_localColorMatrix.m_vector[0];
				m_colorMatrix.m_vector[1] = m_parent->m_pColorMatrix->m_vector[1] * m_localColorMatrix.m_vector[1];
				m_colorMatrix.m_vector[2] = m_parent->m_pColorMatrix->m_vector[2] * m_localColorMatrix.m_vector[2];
				m_colorMatrix.m_vector[3] = m_parent->m_pColorMatrix->m_vector[3] * m_localColorMatrix.m_vector[3];
			}
		}
	}
}

void CKLBNode::markUpTree() {
	CKLBNode* pParent = this->m_parent;
	while (pParent) {
		if (pParent->m_status & MARKED) {
			break;
		} else {
			pParent->m_status |= MARKED;
			pParent = pParent->m_parent;
		}
	}
}

void CKLBNode::setPriority(u32 order)
{
	CKLBRenderingManager& pRdr = CKLBRenderingManager::getInstance();
	for(u32 idx = 0; idx < m_renderCount; idx++) {
		CKLBRenderCommand * pRender = m_pRender[idx];
		if (pRender) {
			pRender->changeOrder(pRdr, order);
		}
	}
}

void CKLBNode::setPriorityL(u32 order) {
	setPriority(order);

	CKLBNode* pNode = m_pChild;
	while (pNode) {
		u32 clID = pNode->getClassID();
		if ((clID == CLS_KLBNODE) || (clID == CLS_KLBSPLINENODE)) {
			// Perform recursion
			pNode->setPriorityL(order);
		} else {
			// Stop and let the object handle it.
			pNode->setPriority(order);
		}
		pNode = pNode->m_pBrother;
	}
}


u32 CKLBNode::getPriority()
{
	klb_assert(m_renderCount == 1, "The node has two or more commands. ");

	CKLBRenderCommand * pRender = m_pRender[0];
	if (pRender) {
		return pRender->getOrder();
	} else {
		return 0;
	}
}
