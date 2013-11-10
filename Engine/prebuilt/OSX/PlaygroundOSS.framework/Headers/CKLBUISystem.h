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
// === UI System derived from scene graph ===
//

#ifndef __KLB_UISYSTEM__
#define __KLB_UISYSTEM__

#include "CKLBNode.h"
#include "CKLBAsset.h"
#include "CKLBTouchPad.h"

#include "CKLBDragCallbackIF.h"

class CKLBUIContainer;
class CKLBUISelectable;
class CKLBUISystem;

/**
	Each element will use a TouchSurface
 */
struct STouchSurface {
	friend class CKLBUISystem;
public:
	// Direct link to transform matrix in screen space.
	SMatrix2D*			transform;
	
	// Coordinate setup by user
	// x,y,w,h
	float				beforeTransform[4];

	// x0,y0,x1,y1
	float				afterTransform[4];	// Coordinate post-transform.

	u16					surfaceIndex;
	u32					touchSurfacePriorityEquiv;					
	bool				isUpToDate;			// Bit telling that user has modified the selection space OR matrix has been changed.
};

struct SClipRecord {
	CKLBRenderState*	pClipStartState;
	CKLBRenderState*	pClipEndState;
};

#define UI_SYS_MAXCLIP_ARRAY		(16)
struct SFormCtrlList;

/*!
* \class CKLBUISystem
* \brief UISystem Class
* 
* CKLBUISystem provides static methods to manage screen area using STouchSurface.
* It can be used to create/release touch surfaces and clips.
*/
class CKLBUISystem {
public:
	static CKLBUISelectable*	hitTest				(float screenX, float screenY);
	static CKLBUISelectable*	createTouchSurface	(CKLBUISelectable*	pSource , u32 priority);
	static void					releaseTouchSurface	(CKLBUISelectable*	pSurface);
	static void					releaseAll          ();
	static void					setFormList			(SFormCtrlList * pList);
	static void*				registerClip		(CKLBRenderState* startClip, CKLBRenderState* endClip);
	static void					unregisterClip		(void* clipHandle);
private:
	static bool					checkRange			(CKLBRenderState* startClip, CKLBRenderState* endClip);

	static SFormCtrlList*		s_formList;
	static SClipRecord*			s_clip_array[UI_SYS_MAXCLIP_ARRAY];
	static u16					s_clip_arraySize;
};

/*!
* \class CKLBUIElement
* \brief Element Node Class
* 
* CKLBUIElement is the most basic UI Node as it directly inherits CKLBNode.
* It adds Assets and asset management methods to the CKLBNode.
* A CKLBUIElement supports multiple assets association in order to change
* the asset if the CKLBUIElement is enable or not.
*/
class CKLBUIElement : public CKLBNode {
public:
	enum UI_STATE {
		NORMAL,
		DISABLED,
		FOCUSED,
		DOWN,
		NOT_ON_SCREEN
	};

	enum ASSET_TYPE {
		NORMAL_ASSET		= NORMAL,
		DISABLED_ASSET		= DISABLED,
		FOCUSED_ASSET		= FOCUSED,
		PUSHED_ASSET		= DOWN
	};

	CKLBUIElement();
	~CKLBUIElement();

	void	storeDoRefLock		(bool doRefCounting)	{ m_bDoRefCount = doRefCounting; }

	virtual
	u32		getClassID			()					    { return CLS_KLBUIELEMENT; }

	void	setLeft				(s32 coordinateX);
	void	setTop				(s32 coordinateY);

	//
	//	Can interact with selection or not.
	//
	virtual	void setEnabled		(bool isEnabled);
	bool	     isEnabled		();

	virtual	bool isSelectable	()		{ return false; }
	virtual bool isContainer	()		{ return false; }

	virtual void setAsset		(CKLBAsset*	pAsset, ASSET_TYPE mode);

	CKLBUIContainer* getParentUI();

	virtual	bool processAction	(CKLBAction* pAction);

	void	registerHandler		(CKLBActionHandler* pActionHandler);
	void	clearHandlers		();

	void	setScriptable		(CKLBObjectScriptable* pScriptable);

	virtual void setPriority	(u32 renderPriority) {
		if (renderPriority != m_renderPrio) {
			m_renderPrio = renderPriority;
			CKLBNode::setPriority(m_renderPrio);
			if (m_currentAssetTree) {
				m_currentAssetTree->setPriority(m_renderPrio);
			}
		}
	}

	virtual u32	getPriority		() {
		return m_renderPrio;
	}

	bool	sendEvent			(ACTION_TYPE type, u32 param);	// Should be protected but access issue.
protected:
	virtual void visibleSelf	();
	
	virtual void invisibleSelf  ();
	
	void	resetAsset			(CKLBAsset** ppOldAsset, CKLBNode** ppOldNode, CKLBAsset* newAsset);

	bool	processListener		(CKLBAction* pAction);

	virtual void setUpperEnabled(bool isEnabled);
	void releaseAsset			(CKLBAsset* pAsset);
	void switchTo				(UI_STATE newState);

	//
	// Visible / Invisible related.
	//
	virtual void addRender		();
	virtual void removeRender	();

	CKLBAsset*			m_currentAsset;
	CKLBNode*			m_currentAssetTree;
	CKLBActionHandler*	m_pActionHandlerList;

	CKLBAsset*			m_pNormal;
	CKLBNode*			m_pNormalTree;

	CKLBAsset*			m_pDisabled;
	CKLBNode*			m_pDisabledTree;

	CKLBObjectScriptable*
						m_scriptable;

	u32					m_renderPrio;
	u32					m_listenerMask;
	UI_STATE			m_UIState;
	bool				m_bEnabled;
	bool				m_bUpperEnabled;
	bool				m_bDoRefCount;
	const char*			m_luaFunc;		// callback Lua function

private:
	CKLBAction			m_localAction;
};

class CKLBAudioAsset;

/*!
* \class CKLBUISelectable
* \brief Selectable Node Class
* 
* CKLBUISelectable represents a selectable item Node.
* A STouchSurface is allocated for each CKLBUISelectable and represents the 
* screen area associated with the object.
*/
class CKLBUISelectable : public CKLBUIElement {
	friend class CKLBUIElement;
	friend struct SFormCtrlList;
	friend class CKLBUISystem;
public:
	CKLBUISelectable();
	~CKLBUISelectable();

	// KLBObject::
	virtual
	u32		getClassID			()					{ return CLS_KLBUISELECTABLE; }

	// KLBNode::
	virtual		
	void		recomputeCustom	();

	// KLBUIElement::
	virtual
	bool	isSelectable		()		{ return true; }
	virtual
	void	setEnabled			(bool isEnabled);
	virtual
	void	setAsset			(CKLBAsset*	pAsset, ASSET_TYPE mode);

	void	setAudio			(CKLBAudioAsset* pAudioAsset, u32 mode, float volume, bool bOwner = false);
	void	setMultiplyVolume	(u32 mode, float factorVolume);

	virtual
	bool	processAction		(CKLBAction* pAction);

	bool	init				(u32 priority);

	//
	// Define rectangle for reaction to touch screen.
	//
	void	setClickLeft		(s32 coordinateX);
	void	setClickWidth		(u32 width);
	void	setClickTop			(s32 coordinateY);
	void	setClickHeight		(u32 height);

	void	setModalResult		(u32 modalResult);

	//
	//	When clicked, stay down after release or up again (=Check box / down button)
	//
	void	setStick			(bool isStickable);
	bool	isStickable			()				{ return m_bStick;	}
	void	setSticked			(bool isSticked);
	bool	isSticked			()				{ return m_bDown;	}

	//
	//	When clicked, all other stickable are modified / reset to unstick.
	// 0 : Not radio, 1..n : Radio ID.
	void	setRadio			(u32 radioID);
	u32		getRadioID			()				{ return m_radioID; }


	bool	setLuaFunction(const char * funcname);

	inline
	CKLBUISelectable*	getNextSelectable() { return m_pNextSelectable; }
protected:
	void	resetSticked		(CKLBUIElement* pElement);
	void	setStickedRecurse	(CKLBNode* pNode);

	virtual void setUpperEnabled(bool isEnabled);

	CKLBUISelectable*	m_pNextSelectable;

	CKLBAsset*	m_pFocus;
	CKLBNode*	m_pFocusTree;
	CKLBAsset*	m_pPushed;
	CKLBNode*	m_pPushedTree;
	CKLBAudioAsset*	m_pDownAudio;
	CKLBAudioAsset* m_pUpAudio;
	float		m_pDownVolumeOriginal;
	float		m_pUpVolumeOriginal;
    float       m_pDownVolumeFactor;
    float       m_pUpVolumeFactor;
	float		m_pDownVolume;
	float		m_pUpVolume;
	bool		m_bOwnerDownAudio;
	bool		m_bOwnerUpAudio;

	u32			m_modalResult;
	u32			m_radioID;
public:
	u16			m_groupID;
protected:
	STouchSurface	m_touchSurface;

	bool	m_bStick;		// Stay down even if current state is "up".
	bool	m_bDown;		// Current State.
	bool	m_bLocked;		// Used for canceling an event. (drag)
	int		m_lastClick;	// last click frameID

	void setStickedInternal(bool isSticked);
};

struct SFormCtrlList {
	SFormCtrlList		*	next;
	CKLBUISelectable	*	pBegin;

	void				*	pGroup;		// Formが所属するグループのポインタ
	SFormCtrlList		*	pGrpPrev;	// グループ内リンク用
	SFormCtrlList		*	pGrpNext;	// グループ内リンク用

	bool					bExclusive;
	bool					bWorking;
	bool					bEnable;

	SFormCtrlList(void)
		: next      (NULL)
        , pBegin    (NULL)
        , pGroup    (NULL)
        , pGrpPrev  (NULL)
        , pGrpNext  (NULL)
        , bExclusive(false)
        , bWorking  (false)
        , bEnable   (false)
	{}

	CKLBDragCallbackIF	*	pCallbackIF;
	void (*nativeCallback)(void * pData, PAD_ITEM::TYPE type, int dragX, int dragY, int mvX, int mvY);
	CKLBObjectScriptable*	pID;
};

/*!
* \class CKLBUIContainer
* \brief Container Node Class
* 
* CKLBUIContainer allows to regroup sub items and manage them like one.
*/
class CKLBUIContainer : public CKLBUIElement {
public:
	CKLBUIContainer ();
	~CKLBUIContainer();

	bool	init				();

	// KLBObject::
	virtual
	u32		getClassID			()		{ return CLS_KLBUICONTAINER; }

	// KLBUIElement::
	virtual
	bool	isContainer			()		{ return true; }
	virtual
	void	setEnabled			(bool isEnabled);

	CKLBUIElement* getChildUI	(bool external = false);

	void	setViewOffsetX		(s32 scrollX);
	void	setViewOffsetY		(s32 scrollY);

	inline
	s32		getViewOffsetX		() { return (s32)m_innerNode->m_matrix.m_matrix[4]; }
	inline
	s32		getViewOffsetY		() { return (s32)m_innerNode->m_matrix.m_matrix[5]; }

	//
	// Allow to connect sub UI component to the container.
	//
	void	addElement			(CKLBUIElement*	pElement, bool external = false);
	void	removeElement		(CKLBUIElement* pElement, bool external = false);

	//
	// Allow to find the active radio button inside the container.
	//
	u32		getRadioValue		();

	void	showModal			(CKLBNode* pNode);

	inline
	CKLBNode*	getInnerNode	()	{ return m_innerNode; }

	inline
	void		setClipHandle	(void* clipHandle) { m_clipHandle = clipHandle; }

protected:
	virtual 
    void        setUpperEnabled (bool isEnabled);
	u32			getRadioValueRecurse	(CKLBNode* pNode);

private:
	CKLBNode*	m_innerNode;
	CKLBNode*	m_outerNode;
	void*		m_clipHandle;

	u32			m_viewPortWidth;
	u32			m_viewPortHeight;
	s32			m_viewScrollX;
	s32			m_viewScrollY;
	bool		m_bAsModal;	// Just to avoid compile error.
public:
	bool		isModal() { return m_bAsModal; }
};

#endif
