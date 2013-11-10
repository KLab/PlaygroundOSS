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
// === 2D Scene Graph ===
//
/*
	Memo about FLAGS
	
	A: RenderCommand Flags (All Sprite)
	------------------------------------
	m_uiStatus
		FLAG_XYUPDATE		: Set  in Phase 2.1
		FLAG_COLORUPDATE	: Set  in Phase 2.3 but uselessly set in many sprite setup.
		FLAG_UVUPDATE		: Used in Phase 2.2 : => __Set in phase 0__ !
		FLAG_BUFFERSHIFT	: When item 
		
		
	B: Node Flags
	------------------------------------
		MATRIX_CHANGE		: Set when matrix       changes or sprite recomputation.
		CMATRIX_CHANGE		: Set when color vector changes or sprite recomputation.
		MARKED				: Sub Node has changed.

	C: Phases
	------------------------------------
	Phase 0 : [Modification : user code modify tree or geometry and perform marking]

	Phase 1 : Modify Matrix / Tree Marking
		-> MATRIX_CHANGE / CMATRIX_CHANGE / MARKED flags are consumed.
		-> FLAG_UVUPDATE is used.

	Phase 2 : Apply  Transform
		2.1	Pre  XY -> Post XY				: Transform coordinate from source image to sprite buffer.
											  FLAG_XYUPDATE Set.

		2.2	Copy UV 						: FLAG_UVUPDATE used, copy UV to sprite buffer.
		
		2.3 Apply Color if CMATRIX_CHANGE	: FLAG_COLORUPDATE update when color is applied.

	Phase 3 : Batch Render Call			:
		- Copy or Skip based on flags	FLAG_UVUPDATE, FLAG_XYUPDATE, FLAG_COLORUPDATE.
		- If FLAG_BUFFERSHIFT, all upper flags are forced to TRUE and copy is forced.
		
	D: What to do - Uses Cases
	------------------------------------
	- Add Sprite to node				: owner node::markUpMatrix()
	- Sprite Geometry changed			: owner node::markUpMatrix()
	- Sprite UV       changed			: FLAG_UVUPDATE + owner node::markUpMatrix()
										  --> Lot of waste for just an UV copy in the end.
	- Sprite Color    changed			: owner node::markUpColor()
	- Sprite Topology changed (ie vertex count change):
										: FLAG_BUFFERSHIFT set 
										+ FLAG_UVUPDATE
										+ owner node::markUpMatrixColor() (MATRIX_CHANGE | CMATRIX_CHANGE)
	- Sprite Added to render list		: FLAG_BUFFERSHIFT set
	- Sprite Removed from render list	: FLAG_BUFFERSHIFT on next rendering item.
	- Matrix transform has changed		: owner node::markUpMatrix()
	- Matrix color transform changed	: owner node::markUpColor()

	E: Notes
	------------------------------------
	- Added a RENDER_CHANGE flag instead of markUpMatrix -> markUpRender()
		Should have a RENDER_CHANGE_GEO, RENDER_CHANGE_COLOR, RENDER_CHANGE_UV
		-> Avoid matrix and sub matrix recomputation.

*/

#ifndef __NODE_BASE__
#define __NODE_BASE__

#include "CKLBObject.h"
#include "CKLBRendering.h"


#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <math.h>

class CKLBNode;
class CKLBUITask;

/*!
* \class CKLBSystem
* \brief Node System Class
* 
* CKLBSystem provides static methods to manage the Animation Node List.
* It allows to separate the Node System from the rest of the Game Engine.
*/
class CKLBSystem {
public:
	static void			removeFromAnimation		(CKLBNode* pNode);
	static void			addToAnimation			(CKLBNode* pNode);
	static CKLBNode*	getAnimationNodeList	();
	static void			performAnimationUpdate	(u32 milliSecDelta);
};

//
// Matrix Types
//

// Identity (color or coordinate matrix)
#define MATRIX_ID				(0)
// Translation
#define MATRIX_T				(1)
// Translation + Scale
#define MATRIX_TS				(2)
// Translation + General
#define MATRIX_TG				(3)
// Color
#define MATRIX_COL				(4)

//
// Matrix Indexes
//
#define MAT_A					(0)
#define MAT_B					(1)
#define MAT_C					(2)
#define MAT_D					(3)
#define MAT_TX					(4)
#define MAT_TY					(5)

struct SMatrix2D {
	u8		m_type;	// T, TS, TG, Identity
	float	m_matrix[6];

	SMatrix2D();
};

struct SColorVector {
	u8		m_type;	// color / identity
	float	m_vector[4];
	SColorVector();
};

class CKLBController;

/**
	
 */

/*!
* \class CKLBNode
* \brief Scene Graphe Node Root Class
* 
* CKLBNode is the root class for the Scene Graph.
* Every Element of the Scene Graph is a CKLBNode or a derivated class.
* Each CKLBNode owns a list of render objects to apply the transformations to.
* The transformations are defined by matrices also owned by the CKLBNode.
*
* A CKLBNode can be linked with a CKLBUITask and in that case, they will point
* each other. Moreover, the CKLBNode will be protected from destruction untill 
* the CKLBUITask is destroyed.
* 
* Important points about the Scene Graph System :
* - add/remove do also add/remove to the animation and rendering if associated 
*	bit or object are set.
* - add takes in account the fact that upper node of new_ node is visible to perform 
*	the modification in animation and rendering.
* - node destruction also destroy all the sub system and includes render object associated.
*/
class CKLBNode : public CKLBObject {
	friend class CKLBSWFPlayer;
	friend class CKLBSystem;
public:
	static float	s_fLeftBorder;
	static float	s_fRightBorder;
	static float	s_fTopBorder;
	static float	s_fBottomBorder;

	bool		setName				(const char * name);
	CKLBNode*	search				(const char* name);
	CKLBNode*	searchFirstByTypeID	(u32 typeID);

	inline const char * getName() const { return m_name; }

	CKLBNode();
	virtual ~CKLBNode();

	virtual
	CKLBNode*	clone				(CKLBNode* newItem, CKLBNode* parent, CKLBNode* brother, bool transferSpriteOwnership);

	inline
	void		setUITask			(CKLBUITask* ptr) { m_uitask = ptr;	}

	inline
	void		resetAsInternalNode	()	{ m_bInternalNode = false; }

	inline
	bool		isInternalNode		()	{ return m_bInternalNode; }

	inline
	CKLBUITask* getUITask			()	{ return m_uitask;		}

	virtual u32	getClassID			()	{ return CLS_KLBNODE;	}

	void		kickAnimation		(const char* animName,u32* refCounterPtr, bool doBlend);
	void		skipAnimation		(const char* animName);

	void		asRoot				()	{	m_status = 0;	// No upper invisible.
											m_pColorMatrix		= &m_colorMatrix;
											m_useParentColor	= false;			} 

	void		dump				(u32 level, u32 dumpMask = 0);

	void		removeNode			(CKLBNode* pChild);
	void		addNode				(CKLBNode* pChild, u16 layer = 0);

	inline
	CKLBNode*	getNextAnimation	()	{ return m_pAnimationNext; }

	virtual
	void		animate				(u32 deltaTimeMilli)	{ deltaTimeMilli = deltaTimeMilli; /*avoid warning*/ /* Default implementation do nothing */ }

	void		recompute			();

	virtual		
	void		recomputeCustom		()	{ /* Do nothing default*/ }

	virtual
	void		setPriority			(u32 order);

	void		setPriorityL		(u32 order);

	virtual
	u32			getPriority			();

	void		markUpTree			();

	inline		
	void		markUpRender		() {	m_status |= RENDER_CHANGE;	markUpTree();	}

	inline
	void		markUpMatrix		() {	m_status |= MATRIX_CHANGE;	markUpTree();	}

	inline
	void		markUpCustom		() {	m_status |= CUSTOM_CHANGE;	markUpTree();	}

	inline
	void		markUpColor			() {	m_status |= CMATRIX_CHANGE; markUpTree();   }

	inline
	void		markUpMatrixAndColor() {	m_status |= MATRIX_CHANGE | CMATRIX_CHANGE; markUpTree(); }

	void		setVisible			(bool isVisible);
	
	inline 
	bool		isVisible			()	{ return (m_status & (INVISIBLE_UPPER | INVISIBLE)) == 0; }

	inline
	CKLBNode*	getChild			()	{ return m_pChild;	}

	inline
	CKLBNode*	getBrother			()	{ return m_pBrother; }

	inline
	CKLBNode*	getParent			()	{ return m_parent;	}

	inline
	u16			getLayer			()	{ return m_layer;	}

	void		setRender			(CKLBRenderCommand* pRender, u32 index = 0);

	void		setRenderOnDestroy	(bool delete_) { this->m_deleteRender = delete_; }

	CKLBNode*	searchCommand		(CKLBRenderCommand* comm);

	inline
	CKLBRenderCommand*	getRender	(u32 index = 0)	{
		klb_assert(index < m_renderCount, "invalid render index");
		return m_pRender[index];
	}

	void		setTranslate		(float x, float y)	{
		if ((x != m_matrix.m_matrix[MAT_TX]) || (y != m_matrix.m_matrix[MAT_TY])) {
			m_status |= MATRIX_CHANGE;
			markUpTree();
			m_matrix.m_matrix[MAT_TX] = x;
			m_matrix.m_matrix[MAT_TY] = y;
			if (m_matrix.m_type == MATRIX_ID) {
				m_matrix.m_type = MATRIX_T;
			}
		}
	}

	void		setRotation			(float deg) {
		float rot = (deg * ((float)((M_PI) / 180.0)));
		if (rot != m_rot) {
			m_rot = rot;
			recMatrix();
		}
	}

	void		setScale			(float scaleX, float scaleY) {
		if ((m_scaleX != scaleX) || (m_scaleY != scaleY)) {
			m_scaleX	= scaleX;
			m_scaleY	= scaleY;
			recMatrix();
		}
	}

	void		setScaleRotation	(float scaleX, float scaleY, float deg) {
		float rot = (deg * ((float)((M_PI) / 180.0)));
		if ((m_scaleX != scaleX) || (m_scaleY != scaleY) || (rot != m_rot)) {
			m_scaleX	= scaleX;
			m_scaleY	= scaleY;
			m_rot = rot;
			recMatrix();
		}
	}

	#define _epsilon		(0.00001f)

	void		recMatrix			() {
		if (fabs(m_rot) < _epsilon) {
			m_status |= MATRIX_CHANGE;
			markUpTree();
			m_matrix.m_matrix[MAT_A] = m_scaleX;
			m_matrix.m_matrix[MAT_D] = m_scaleY;
			m_matrix.m_matrix[MAT_B] = 0.0f;
			m_matrix.m_matrix[MAT_C] = 0.0f;
			if (m_matrix.m_type < MATRIX_TS) {
				m_matrix.m_type = MATRIX_TS;
			} else {
				if ((m_scaleX <= (1.0f+_epsilon)) && (m_scaleX >= (1.0f-_epsilon)) && (m_scaleY >= (1.0f-_epsilon)) && (m_scaleY <= (1.0f+_epsilon))) {
					m_matrix.m_type = MATRIX_T;
				}
			}
		} else {
			m_status |= MATRIX_CHANGE;
			markUpTree();

			float cosT = cos(m_rot);
			float sinT = sin(m_rot);

			m_matrix.m_matrix[MAT_A] =   cosT  * m_scaleX;
			m_matrix.m_matrix[MAT_B] = (-sinT) * m_scaleY;	// or X / Y ?

			m_matrix.m_matrix[MAT_C] =   sinT  * m_scaleX;
			m_matrix.m_matrix[MAT_D] =   cosT  * m_scaleY;

			m_matrix.m_type = MATRIX_TG;
		}
	}

	float*		setMatrix			() {
		m_status |= MATRIX_CHANGE;
		m_matrix.m_type = MATRIX_TG;
		markUpTree();
		return m_matrix.m_matrix;
	}

	inline	void getColorMatrix		(SColorVector& color) {
		color = this->m_localColorMatrix;
	}

	void		setColorMatrix		(SColorVector color) {
		m_status |= CMATRIX_CHANGE;
		m_localColorMatrix = color;

		if (	(m_localColorMatrix.m_vector[0] != 1.0f) || 
				(m_localColorMatrix.m_vector[1] != 1.0f) || 
				(m_localColorMatrix.m_vector[2] != 1.0f) || 
				(m_localColorMatrix.m_vector[3] != 1.0f) ) {
			m_pColorMatrix		= &m_colorMatrix;
			m_useParentColor	= false;
		} else {
			m_pColorMatrix		= this->m_parent->m_pColorMatrix;
			m_useParentColor	= true;
		}

		markUpTree();
	}

	inline void applyColor(CKLBRenderCommand* pRender) {
		const float* pVec = m_pColorMatrix->m_vector;
		pRender->setColor(pVec);
	}

	inline float getScaleX      ()	{ return m_scaleX;	}
	inline float getScaleY      ()	{ return m_scaleY;	}
	inline float getRotation    ()	{ return m_rot;		}
	inline float getTranslateX  ()	{ return m_matrix.m_matrix[MAT_TX]; }
	inline float getTranslateY  ()	{ return m_matrix.m_matrix[MAT_TY]; }

	bool	setRenderSlotCount	(u32 slot);

#ifdef DEBUG_PERFORMANCE
	static u32	s_vertexRecomputeCount;
	static u32	s_matrixRecomputeCount;
	static u32  s_colorRecomputeCount;
#endif
protected:

	// Should be visible from friend class.... but it is not !
	enum FLAGS_STATE {
		//
		// Change Flags
		//
		MATRIX_CHANGE	= 0x0001,
		CMATRIX_CHANGE	= 0x0002,
		CUSTOM_CHANGE	= 0x0004,
		RENDER_CHANGE	= 0x0008,
		ANY_CHANGE		= MATRIX_CHANGE | CMATRIX_CHANGE | CUSTOM_CHANGE | RENDER_CHANGE,	// Force all recomputation
		MARKED			= 0x0010,
		// 0x0020		: Free
		// 0x0040		: Free

		//
		// State Flags
		//
		INVISIBLE		= 0x0100,
		INVISIBLE_UPPER	= 0x0200,

		//
		// Various flags.
		//
		UNSET			= 0x2000,	// Used for recursion param
		UI_TYPE			= 0x0080,	// Exit just casting purpose.
		ANIMATED		= 0x4000
	};

	// ------------------------------------------------------------------------
	//   Tree Management.
	// ------------------------------------------------------------------------
protected:

	// TODO LATER RP : Node can support its own render surface.

	//
	// Tree Management
	//
	CKLBNode*
			getNode				(u16 layer);
	void	updateMatrices		();
	void	clearSubTree		();

	void	visibleUpperRecursive();
	void	invisibleUpperRecursive();


	virtual
	void	visibleSelf			();

	virtual
	void	invisibleSelf		();

	virtual
	void	addRender		();

	virtual
	void	removeRender	();

	void	setRenderRef(CKLBRenderCommand* pRender, u32 indexRender);

	// ------------------------------------------------------------------------
	//	Animation Management.
	// ------------------------------------------------------------------------
public:	// Public for now...
	// Inside Animation Update
	inline bool			isAnimating()		{ return m_isAnimated; }
	// Animation Complete or not
	inline bool			isStillAnimating()	{ return (m_status & ANIMATED) ? true : false; }

protected:
	void				releaseSlots();

// Refactored for more compact class.
public:		SMatrix2D 			m_matrix;
public:		SMatrix2D			m_composedMatrix;
public:		SColorVector		m_colorMatrix;
public:		SColorVector		m_localColorMatrix;

protected:	const char*			m_name;			// form name
protected:	CKLBUITask*			m_uitask;
protected:	CKLBNode*			m_pChild;
protected:	CKLBNode*			m_pBrother;
protected:	CKLBNode*			m_parent;

protected:	CKLBNode*			m_pAnimationNext;
protected:	CKLBNode*			m_pAnimationPrev;

public:		SColorVector*		m_pColorMatrix;
protected:	CKLBRenderCommand**	m_pRender;
protected:	CKLBRenderCommand*	m_renderSlot;

public:		float				m_rot;
public:		float				m_scaleX;
public:		float				m_scaleY;
protected:	u32					m_renderCount;

protected:	u16					m_groupID;
public:		u16					m_status;
protected:	u16					m_layer;
	// Was necessary in flash and necessary for flash leaf too.
	// Can reuse in other systems. 
public:		u16					m_movieID;
public:		u16					m_updateFrame;
private:	u16					m_nameLength;

protected:	bool				m_isAnimated;
protected:	bool				m_deleteRender;
protected:	bool				m_bInternalNode;
public:		bool				m_useParentColor;
protected:  bool				m_reject;

};

#endif
