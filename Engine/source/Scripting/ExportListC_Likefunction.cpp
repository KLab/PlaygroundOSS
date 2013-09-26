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
#ifndef DllExport
#define DllExport   __declspec( dllexport )
#endif

#include "ExportListC_Likefunction.h"

#include "CKLBScriptEnv.h"

extern "C" DllExport s32* CKLBScriptEnv_getCallBackCount() {
	return (s32*)CKLBScriptEnv::getInstance().getCallCounter();
}

extern "C" DllExport s32* CKLBScriptEnv_getErrorPtr() {
	return (s32*)CKLBScriptEnv::getInstance().getErrorReader();
}

extern "C" DllExport s32* CKLBScriptEnv_getErrorString() {
	return (s32*)CKLBScriptEnv::getInstance().getErrorString();
}

extern "C" DllExport void CKLBScriptEnv_resetError() {
	CKLBScriptEnv::getInstance().resetError();
}

//======================================================================================
#include "CKLBObject.h"
#include "CKLBLuaTask.h"
#include "CKLBLibRegistrator.h"


extern "C" DllExport u32 CKLBObject_getTypeID(s32* pCtx) {
	return ((CKLBObject*)pCtx)->getClassID();
}

extern "C" DllExport void CKLBObjectScriptable_setScriptContext(s32* pCtx, u32 handle) {
	((CKLBObjectScriptable*)pCtx)->setScriptHandle(handle);
}

extern "C" DllExport u32 CKLBObjectScriptable_getScriptContext(s32* pCtx) {
	return ((CKLBObjectScriptable*)pCtx)->getScriptHandle();
}

extern "C" DllExport u32 Cpp_getClassIDByName(s32* name) {
	u32 res = IFactory::getClassID((const char*)name, false);
	if(res == 0) {
		res = CKLBLibRegistrator::getInstance()->getClassID((const char*)name);
	}
	if(res == 0) {
		klb_assertAlways("Can not find class ID from name %s", (const char*)name);
	}

	return res;
}

//======================================================================================
#include "CKLBNode.h"
#include "CKLBUITask.h"
#include "CKLBDrawTask.h"
#include "AudioAsset.h"

extern "C" DllExport s32* node_getRoot() {
	CKLBDrawResource& res = CKLBDrawResource::getInstance();
	return (s32*)res.getRoot();
}

extern "C" DllExport s32* node_getChild(s32*  pNode) {
	return (s32*)((CKLBNode*)pNode)->getChild();
}

extern "C" DllExport s32* node_getParent(s32*  pNode) {
	return (s32*)((CKLBNode*)pNode)->getParent();
}

extern "C" DllExport s32* node_getBrother(s32*  pNode) {
	return (s32*)((CKLBNode*)pNode)->getBrother();
}

extern "C" DllExport s32* node_getNodeFromTask(s32* pTask) {
	return (s32*)((CKLBUITask*)pTask)->getNode();
}

extern "C" DllExport float node_getNodeScaleX(s32* pNode) { 
	return ((CKLBNode*)pNode)->getScaleX();
}

extern "C" DllExport float node_getNodeScaleY(s32* pNode) {
	return ((CKLBNode*)pNode)->getScaleY();
}

extern "C" DllExport float node_getRotation(s32* pNode) {
	return ((CKLBNode*)pNode)->getRotation();
}

extern "C" DllExport float node_getNodeTranslateX(s32*  pNode) {
	return ((CKLBNode*)pNode)->getTranslateX();
}

extern "C" DllExport float node_getNodeTranslateY(s32*  pNode) {
	return ((CKLBNode*)pNode)->getTranslateY();
}

extern "C" DllExport void node_setTranslate(s32*  pNode, float x, float y) {
	((CKLBNode*)pNode)->setTranslate(x,y);
}

extern "C" DllExport void node_setRotation(s32*  pNode, float deg) 
{
	((CKLBNode*)pNode)->setRotation(deg);
}

extern "C" DllExport void node_setScale(s32*  pNode, float scaleX, float scaleY)
{
	((CKLBNode*)pNode)->setScale(scaleX, scaleY);
}

extern "C" DllExport void node_getColorMatrixVec(s32*  pNode, float* dst) {
	SColorVector colorMat;
	((CKLBNode*)pNode)->getColorMatrix(colorMat);
	dst[0] = colorMat.m_vector[0];
	dst[1] = colorMat.m_vector[1];
	dst[2] = colorMat.m_vector[2];
	dst[3] = colorMat.m_vector[3];
}

extern "C" DllExport void node_setColorMatrixVec(s32*  pNode, float* src) {
	SColorVector colorMat;
	colorMat.m_type = 0;
	colorMat.m_vector[0] = src[0];
	colorMat.m_vector[1] = src[1];
	colorMat.m_vector[2] = src[2];
	colorMat.m_vector[3] = src[3];
	
	((CKLBNode*)pNode)->setColorMatrix(colorMat);
}

extern "C" DllExport u32 node_getColorMatrixUInt(s32*  pNode) {
	SColorVector colorMat;
	((CKLBNode*)pNode)->getColorMatrix(colorMat);
	u32 fr = (u32)(colorMat.m_vector[0] * 255.0f);
	u32 fg = (u32)(colorMat.m_vector[1] * 255.0f);
	u32 fb = (u32)(colorMat.m_vector[2] * 255.0f);
	u32 fa = (u32)(colorMat.m_vector[3] * 255.0f);
	if (fr > 255) { fr = 255; }
	if (fg > 255) { fg = 255; }
	if (fb > 255) { fr = 255; }
	if (fa > 255) { fr = 255; }
	
	return (fa << 24) | (fr <<16) | (fg << 8) | fb;
}

extern "C" DllExport void node_setColorMatrixUInt(s32*  pNode, u32 val) {
	SColorVector colorMat;
	colorMat.m_type = 0;
	colorMat.m_vector[0] = ((val >> 16) & 0xFF) / 255.0f;	// R
	colorMat.m_vector[1] = ((val >> 8) & 0xFF) / 255.0f;	// G
	colorMat.m_vector[2] = (val & 0xFF) / 255.0f;	// B
	colorMat.m_vector[3] = (val >> 24) / 255.0f;	// A
	
	((CKLBNode*)pNode)->setColorMatrix(colorMat);
}

extern "C" DllExport void node_setVisible(s32*  pNode, bool visible) {
	((CKLBNode*)pNode)->setVisible(visible);
}

extern "C" DllExport bool node_getVisible(s32*  pNode) {
	return ((CKLBNode*)pNode)->isVisible();
}

extern "C" DllExport s32*  node_asElement(s32*  pNode) {
	if (((CKLBNode*)pNode)->getClassID() == CLS_KLBUIELEMENT) {
		return pNode;
	} else {
		return NULL;
	}
}

extern "C" DllExport s32*  node_asContainer(s32*  pNode) {
	if (((CKLBNode*)pNode)->getClassID() == CLS_KLBUICONTAINER) {
		return pNode;
	} else {
		return NULL;
	}
}

extern "C" DllExport s32*  node_asSelectable(s32*  pNode) {
	if (((CKLBNode*)pNode)->getClassID() == CLS_KLBUISELECTABLE) {
		return pNode;
	} else {
		return NULL;
	}
}

extern "C" DllExport s32*  node_asAnimationNode(s32*  pNode) {
	if (((CKLBNode*)pNode)->getClassID() == CLS_KLBSPLINENODE) {
		return pNode;
	} else {
		return NULL;
	}
}

extern "C" DllExport s32* node_getName(s32*  pNode) {
	return (s32*)((CKLBNode*)pNode)->getName();
}

extern "C" DllExport void node_setName(s32* pNode, s32* name) {
	((CKLBNode*)pNode)->setName((const char*)name);
}

extern "C" DllExport s32*  node_getUITask(s32*  pNode) {
	return (s32*)((CKLBNode*)pNode)->getUITask();
}

extern "C" DllExport s32*  node_search(s32*  pNode, s32* name) {
	return (s32*)((CKLBNode*)pNode)->search((const char*)name);
}

extern "C" DllExport s32*  node_searchFirstByTypeID(s32*  pNode, u32 typeID) {
	return (s32*)((CKLBNode*)pNode)->searchFirstByTypeID(typeID);
}

//
// Element
//
#include "CKLBUISystem.h"

extern "C" DllExport void element_setEnabled(s32*  pElem, bool isEnabled) {
	((CKLBUIElement*)pElem)->setEnabled(isEnabled);
}

extern "C" DllExport bool element_isEnabled(s32*  pElem) {
	return ((CKLBUIElement*)pElem)->isEnabled();
}

extern "C" DllExport bool element_setAsset(s32*  pElem, u32 dest, s32* assetName) {
	CKLBAsset* pAsset = NULL;
	if((const char*)assetName) {
		CKLBAssetManager& pAssetMgr = CKLBAssetManager::getInstance();
		u16 assetID = pAssetMgr.getAssetIDFromName((const char*)assetName,0);
		CKLBAbstractAsset* pAbstractAsset= pAssetMgr.getAsset(assetID);
		if (pAbstractAsset && (pAbstractAsset->getAssetType() & HAS_CREATENODE)) {
			pAsset = (CKLBAsset*)pAbstractAsset;
		} else {
			return false;
		}
	}
		((CKLBUIElement*)pElem)->setAsset(pAsset,(CKLBUIElement::ASSET_TYPE)dest);
	return true;
}

extern "C" DllExport void element_setPriority(s32*  pElem, u32 renderPriority) {
	((CKLBUIElement*)pElem)->setPriority(renderPriority);
}

extern "C" DllExport u32 element_getPriority(s32*  pElem) {
	return ((CKLBUIElement*)pElem)->getPriority(); 
}

//
// Selectable
//

extern "C" DllExport void selectable_setClick		(s32*  pSelect, s32 coordinateX, s32 coordinateY, s32 width, s32 height) {
	((CKLBUISelectable*)pSelect)->setClickLeft(coordinateX);
	((CKLBUISelectable*)pSelect)->setClickWidth(width);
	((CKLBUISelectable*)pSelect)->setClickTop(coordinateY);
	((CKLBUISelectable*)pSelect)->setClickHeight(height);
}

extern "C" DllExport bool selectable_setAudio			(s32*  pSelect, s32* assetAudio, u32 mode, float volume) {
	CKLBAssetManager& pAssetMgr = CKLBAssetManager::getInstance();
	CKLBAbstractAsset* lAsset = pAssetMgr.loadAssetByFileName((const char*)assetAudio, pAssetMgr.getPlugin('A'), true);
	if (lAsset && (lAsset->getAssetType() == ASSET_AUDIO)) {
		CKLBAudioAsset* pAudio = (CKLBAudioAsset*)lAsset;
		if (!pAudio->preLoad()) {
			klb_assertAlways("Failed preloading audio");
		}
		lAsset->incrementRefCount();
		((CKLBUISelectable*)pSelect)->setAudio(pAudio, mode, volume, true);
		
		return true;
	}
	return false;
}

extern "C" DllExport void selectable_setStick			(s32*  pSelect,bool isStickable) {
	((CKLBUISelectable*)pSelect)->setStick(isStickable);
}

extern "C" DllExport bool selectable_isStickable			(s32*  pSelect)				
{	return ((CKLBUISelectable*)pSelect)->isStickable();	}

extern "C" DllExport void selectable_setSticked			(s32*  pSelect,bool isSticked) {
	((CKLBUISelectable*)pSelect)->setSticked(isSticked);
}

extern "C" DllExport bool selectable_isSticked			(s32*  pSelect)				
{ return ((CKLBUISelectable*)pSelect)->isSticked();	}

//
//	When clicked, all other stickable are modified / reset to unstick.
// 0 : Not radio, 1..n : Radio ID.
extern "C" DllExport void	selectable_setRadio			(s32*  pSelect,u32 radioID) {
	((CKLBUISelectable*)pSelect)->setRadio(radioID);
}

extern "C" DllExport u32		selectable_getRadioID			(s32*  pSelect)				
{ return ((CKLBUISelectable*)pSelect)->getRadioID(); }


//
// Container
//

extern "C" DllExport s32		container_getViewOffsetX		(s32*  pCont) { 
	return ((CKLBUIContainer*)pCont)->getViewOffsetX();
}
extern "C" DllExport void	container_setViewOffsetX		(s32*  pCont,s32 scrollX) {
	((CKLBUIContainer*)pCont)->setViewOffsetX(scrollX);
}

extern "C" DllExport s32		container_getViewOffsetY		(s32*  pCont) { 
	return ((CKLBUIContainer*)pCont)->getViewOffsetY();
}
extern "C" DllExport void	container_setViewOffsetY		(s32*  pCont,s32 scrollY) {
	((CKLBUIContainer*)pCont)->setViewOffsetY(scrollY);
}

// Allow to find the active radio button inside the container.
extern "C" DllExport u32		container_getRadioValue			(s32*  pCont) {
	return ((CKLBUIContainer*)pCont)->getRadioValue();
}


//======================================================================================
#include "CKLBGenericTask.h"

// "" is given instead of NULL because of the class specifications.
extern "C" DllExport s32* CKLBGenericTask_create(s32* pParentTask, s32 phase)
{ return (s32*)CKLBGenericTask::create((CKLBTask*)pParentTask, (CKLBTask::TASK_PHASE)phase, "", "", ""); }

//======================================================================================
#include "CKLBIntervalTimer.h"

// "" is given instead of NULL because of the class specifications.
// false is given as last arguement to prevent killing a timer if the timer interval has changed during the callback.
extern "C" DllExport s32* CKLBIntervalTimer_create(s32* pParent, u32 interval, bool repeat, u8 mode)
{	return (s32*)CKLBIntervalTimer::create((CKLBTask*)pParent, NULL, interval, repeat, "", mode, false);	}

extern "C" DllExport u32 CKLBIntervalTimer_getTimerID(s32* pCtx) 								
{	return ((CKLBIntervalTimer*)pCtx)->getTimerID();	}
extern "C" DllExport void CKLBIntervalTimer_setTimerID(s32* pCtx, u32 ID) 					
{	((CKLBIntervalTimer*)pCtx)->setTimerID(ID);			}

extern "C" DllExport bool CKLBIntervalTimer_getRepeat(s32* pCtx) 								
{	return ((CKLBIntervalTimer*)pCtx)->getRepeat();		}
extern "C" DllExport void CKLBIntervalTimer_setRepeat(s32* pCtx, bool boolean) 				
{	((CKLBIntervalTimer*)pCtx)->setRepeat(boolean);		}

extern "C" DllExport u32 CKLBIntervalTimer_getInterval(s32* pCtx)
{	return ((CKLBIntervalTimer*)pCtx)->getInterval();	}
extern "C" DllExport void CKLBIntervalTimer_setInterval(s32* pCtx, u32 interval)
{	((CKLBIntervalTimer*)pCtx)->setInterval(interval);	}

extern "C" DllExport u8 CKLBIntervalTimer_getMode(s32* pCtx)
{	return ((CKLBIntervalTimer*)pCtx)->getMode();		}

//======================================================================================
#include "CKLBUIProgressBar.h"

extern "C" DllExport s32* CKLBUIProgressBar_create(s32* pParent, 
							u32 order, float x, float y, float width, float height,
							s32* full_image, s32* empty_image,
							s32 start_pix, s32 end_pix, u32 anim, bool vert, s32* barfilterImage)
{	return (s32*)CKLBUIProgressBar::create(	(CKLBUITask*)pParent, NULL, 
										order, x, y, width, height, 
										(const char*)full_image, (const char*)empty_image, 
										start_pix, end_pix, anim, vert, (const char*)barfilterImage);
}

extern "C" DllExport u32 CKLBUIProgressBar_getOrder(s32* pCtx) 
{ return ((CKLBUIProgressBar*)pCtx)->getOrder(); }
extern "C" DllExport void CKLBUIProgressBar_setOrder(s32* pCtx, u32 order)
{ ((CKLBUIProgressBar*)pCtx)->setOrder(order); }

extern "C" DllExport float CKLBUIProgressBar_getWidth(s32* pCtx) 
{ return ((CKLBUIProgressBar*)pCtx)->getWidth(); }
extern "C" DllExport void CKLBUIProgressBar_setWidth(s32* pCtx, float width)
{ ((CKLBUIProgressBar*)pCtx)->setWidth(width); }

extern "C" DllExport float CKLBUIProgressBar_getHeight(s32* pCtx)
{ return ((CKLBUIProgressBar*)pCtx)->getHeight(); }
extern "C" DllExport void CKLBUIProgressBar_setHeight(s32* pCtx, float height)
{ ((CKLBUIProgressBar*)pCtx)->setHeight(height); }

extern "C" DllExport bool CKLBUIProgressBar_getVertical(s32* pCtx) 
{ return ((CKLBUIProgressBar*)pCtx)->getVertical(); }
extern "C" DllExport void CKLBUIProgressBar_setVertical(s32* pCtx, bool vertical)
{ ((CKLBUIProgressBar*)pCtx)->setVertical(vertical); }

extern "C" DllExport u32 CKLBUIProgressBar_getAnimTime(s32* pCtx)
{ return ((CKLBUIProgressBar*)pCtx)->getAnimTime(); }
extern "C" DllExport void CKLBUIProgressBar_setAnimTime(s32* pCtx, u32 time)
{ ((CKLBUIProgressBar*)pCtx)->setAnimTime(time); }

extern "C" DllExport float CKLBUIProgressBar_getStart(s32* pCtx)
{ return ((CKLBUIProgressBar*)pCtx)->getStart(); }
extern "C" DllExport void CKLBUIProgressBar_setStart(s32* pCtx, float start)
{ ((CKLBUIProgressBar*)pCtx)->setStart(start); }

extern "C" DllExport float CKLBUIProgressBar_getEnd(s32* pCtx)
{ return ((CKLBUIProgressBar*)pCtx)->getEnd(); }
extern "C" DllExport void CKLBUIProgressBar_setEnd(s32* pCtx, float end)
{ ((CKLBUIProgressBar*)pCtx)->setEnd(end); }

extern "C" DllExport float CKLBUIProgressBar_getValue(s32* pCtx)
{ return ((CKLBUIProgressBar*)pCtx)->getValue(); }
extern "C" DllExport void CKLBUIProgressBar_setValue(s32* pCtx, float value)
{ ((CKLBUIProgressBar*)pCtx)->setValue(value); }

extern "C" DllExport s32* CKLBUIProgressBar_getImgEmpty(s32* pCtx)
{ return (s32*)((CKLBUIProgressBar*)pCtx)->getImgEmpty(); }
extern "C" DllExport void CKLBUIProgressBar_setImgEmpty(s32* pCtx, s32* imgEmpty)
{ ((CKLBUIProgressBar*)pCtx)->setImgEmpty((const char*)imgEmpty); }

extern "C" DllExport s32* CKLBUIProgressBar_getImgFull(s32* pCtx)
{ return (s32*)((CKLBUIProgressBar*)pCtx)->getImgFull(); }
extern "C" DllExport void CKLBUIProgressBar_setImgFull(s32* pCtx, s32* imgFull)
{ ((CKLBUIProgressBar*)pCtx)->setImgFull((const char*)imgFull); }

extern "C" DllExport s32* CKLBUIProgressBar_getImgFilter(s32* pCtx)
{ return (s32*)((CKLBUIProgressBar*)pCtx)->getImgFilter(); }
extern "C" DllExport void CKLBUIProgressBar_setImgFilter(s32* pCtx, s32* imgFilter)
{ ((CKLBUIProgressBar*)pCtx)->setImgFilter((const char*)imgFilter); }

extern "C" DllExport void CKLBUIProgressBar_reset(s32* pCtx)
{ ((CKLBUIProgressBar*)pCtx)->reset(); }

extern "C" DllExport bool CKLBUIProgressBar_getFilterVisible(s32* pCtx)
{ return ((CKLBUIProgressBar*)pCtx)->getFilterVisible(); }
extern "C" DllExport void CKLBUIProgressBar_setFilterVisible(s32* pCtx, bool bFilter)
{ ((CKLBUIProgressBar*)pCtx)->setFilterVisible(bFilter); }

extern "C" DllExport u32 CKLBUIProgressBar_getFilterColor(s32* pCtx)
{ return ((CKLBUIProgressBar*)pCtx)->getFilterColor(); }
extern "C" DllExport void CKLBUIProgressBar_setFilterColor(s32* pCtx, u32 argb)
{ ((CKLBUIProgressBar*)pCtx)->setFilterColor(argb); }

extern "C" DllExport bool CKLBUIProgressBar_setFilterAnim(s32* pCtx, bool bColAnim, u32 argb1, u32 argb2, u32 freq)
{ return ((CKLBUIProgressBar*)pCtx)->setFilterAnim(bColAnim, argb1, argb2, freq); }

//======================================================================================
#include "CKLBUIScore.h"

extern "C" DllExport s32* CKLBUIScore_create(s32* pParent,
									u32 order, s32 order_offset,
									float x, float y, s32** tex_table,
									float stepX, float stepY, u32 column, 
									bool fillzero, bool anim_flag,
									u32 align, bool countclip)
{	return (s32*)CKLBUIScore::create((CKLBUITask*)pParent, NULL,
								order, order_offset,
								x, y, (const char**)tex_table, 
								stepX, stepY, column, fillzero, anim_flag);
}

extern "C" DllExport u32 CKLBUIScore_getValue(s32* pCtx) 										
{	return ((CKLBUIScore*)pCtx)->getValue();	}
extern "C" DllExport void CKLBUIScore_setValue(s32* pCtx, u32 value) 							
{	((CKLBUIScore*)pCtx)->setValue(value);		}

extern "C" DllExport u32 CKLBUIScore_getOrder(s32* pCtx)
{	return ((CKLBUIScore*)pCtx)->getOrder();	}
extern "C" DllExport void CKLBUIScore_setOrder(s32* pCtx, u32 value) 							
{	((CKLBUIScore*)pCtx)->setOrder(value);		}

extern "C" DllExport u32 CKLBUIScore_getOrderOffset(s32* pCtx)
{	return ((CKLBUIScore*)pCtx)->getOrderOffset();	}

extern "C" DllExport s32 CKLBUIScore_getStepX(s32* pCtx) 										
{	return ((CKLBUIScore*)pCtx)->getStepX();	}
extern "C" DllExport void CKLBUIScore_setStepX(s32* pCtx, s32 value) 							
{	((CKLBUIScore*)pCtx)->setStepX(value);		}

extern "C" DllExport s32 CKLBUIScore_getStepY(s32* pCtx) 										
{	return ((CKLBUIScore*)pCtx)->getStepY();	}
extern "C" DllExport void CKLBUIScore_setStepY(s32* pCtx, s32 value) 							
{	((CKLBUIScore*)pCtx)->setStepY(value);		}

extern "C" DllExport u32 CKLBUIScore_getColumn(s32* pCtx)
{	return ((CKLBUIScore*)pCtx)->getColumn();	}
extern "C" DllExport void CKLBUIScore_setColumn(s32* pCtx, u32 value) 							
{	((CKLBUIScore*)pCtx)->setColumn(value);		}

extern "C" DllExport bool CKLBUIScore_getFillZero(s32* pCtx)
{	return ((CKLBUIScore*)pCtx)->getFillZero();	}
extern "C" DllExport void CKLBUIScore_setFillZero(s32* pCtx, bool value) 							
{	((CKLBUIScore*)pCtx)->setFillZero(value);	}

extern "C" DllExport bool CKLBUIScore_getAnim(s32* pCtx)
{	return ((CKLBUIScore*)pCtx)->getAnim();	}

extern "C" DllExport u32 CKLBUIScore_getAlign(s32* pCtx)
{	return ((CKLBUIScore*)pCtx)->getAlign();	}
extern "C" DllExport void CKLBUIScore_setAlign(s32* pCtx, u32 value) 							
{	((CKLBUIScore*)pCtx)->setAlign(value);		}

extern "C" DllExport bool CKLBUIScore_getCountClip(s32* pCtx)
{	return ((CKLBUIScore*)pCtx)->getCountClip();	}
extern "C" DllExport void CKLBUIScore_setCountClip(s32* pCtx, bool value) 							
{	((CKLBUIScore*)pCtx)->setCountClip(value);	}

extern "C" DllExport s32* CKLBUIScore_getTextures(s32* pCtx)
{	return (s32*)((CKLBUIScore*)pCtx)->getTextures();	}

extern "C" DllExport void CKLBUIScore_setEnterAnimation(s32* pCtx, s32 milliSecondsPlayTime, s32 timeShift, u32 type, u32 affected, const float* arrayParam) 
{	((CKLBUIScore*)pCtx)->setEnterAnimation(milliSecondsPlayTime, timeShift, false, type, affected, arrayParam); }

extern "C" DllExport void CKLBUIScore_setExitAnimation(s32* pCtx, s32 milliSecondsPlayTime, s32 timeShift, u32 type, u32 affected, const float* arrayParam) 
{	((CKLBUIScore*)pCtx)->setExitAnimation(milliSecondsPlayTime, timeShift, false, type, affected, arrayParam); }

//======================================================================================
#include "CKLBUITask.h"

// No constructor for UI Task

extern "C" DllExport bool CKLBUITask_getVisible(s32* pCtx)
{	return ((CKLBUITask*)pCtx)->getVisible(); 	}
extern "C" DllExport void CKLBUITask_setVisible(s32* pCtx, bool isVisible)
{	((CKLBUITask*)pCtx)->setVisible(isVisible);	}

extern "C" DllExport float CKLBUITask_getScaleX(s32* pCtx)
{	return ((CKLBUITask*)pCtx)->getScaleX(); 	}
extern "C" DllExport void CKLBUITask_setScaleX(s32* pCtx, float scaleX)
{	((CKLBUITask*)pCtx)->setScaleX(scaleX);		}

extern "C" DllExport float CKLBUITask_getScaleY(s32* pCtx)
{	return ((CKLBUITask*)pCtx)->getScaleY(); 	}
extern "C" DllExport void CKLBUITask_setScaleY(s32* pCtx, float scaleY)
{	((CKLBUITask*)pCtx)->setScaleY(scaleY);		}

extern "C" DllExport float CKLBUITask_getX(s32* pCtx)
{	return ((CKLBUITask*)pCtx)->getX(); 		}
extern "C" DllExport void CKLBUITask_setX(s32* pCtx, float x)
{	((CKLBUITask*)pCtx)->setX(x);				}

extern "C" DllExport float CKLBUITask_getY(s32* pCtx)
{	return ((CKLBUITask*)pCtx)->getY(); 		}
extern "C" DllExport void CKLBUITask_setY(s32* pCtx, float y)
{	((CKLBUITask*)pCtx)->setY(y);				}

extern "C" DllExport float CKLBUITask_getRotation(s32* pCtx)
{	return ((CKLBUITask*)pCtx)->getRotation(); 	}
extern "C" DllExport void CKLBUITask_setRotation(s32* pCtx, float y)
{	((CKLBUITask*)pCtx)->setRotation(y);		}

extern "C" DllExport u32 CKLBUITask_getArgb(s32* pCtx)
{	return ((CKLBUITask*)pCtx)->getArgb(); 		}
extern "C" DllExport void CKLBUITask_setArgb(s32* pCtx, u32 argb)
{	((CKLBUITask*)pCtx)->setArgb(argb);			}

extern "C" DllExport bool CKLBUITask_isAnim(s32* pCtx)
{	return ((CKLBUITask*)pCtx)->isAnim(); 		}

extern "C" DllExport void CKLBUITask_play(s32* pCtx)
{	((CKLBUITask*)pCtx)->play();				}
extern "C" DllExport void CKLBUITask_stop(s32* pCtx)
{	((CKLBUITask*)pCtx)->stop();				}

extern "C" DllExport bool CKLBUITask_setParamCount(s32* pCtx, u32 splineCount, u32 maxKeyCount) 
{	return ((CKLBUITask*)pCtx)->setParamCount(splineCount, maxKeyCount); }

extern "C" DllExport void CKLBUITask_setTarget			(s32* pCtx, u32 splineIndex, u32 targetParameter) 
{	((CKLBUITask*)pCtx)->setTarget(splineIndex, targetParameter);				}

extern "C" DllExport void CKLBUITask_addKeys				(s32* pCtx, u32 splineIndex, u32 time, s32 value) 
{	((CKLBUITask*)pCtx)->addKeys(splineIndex, time, value); }

extern "C" DllExport void CKLBUITask_addKeysFixed		(s32* pCtx, u32 splineIndex, u32 time, s32 fixed16Value) 
{	((CKLBUITask*)pCtx)->addKeysFixed(splineIndex, time, fixed16Value); }

extern "C" DllExport void CKLBUITask_generateAnimation	(s32* pCtx) 
{	((CKLBUITask*)pCtx)->generateAnimation(); }

extern "C" DllExport bool CKLBUITask_reconnect(s32* pCtx, s32* nodeName)
{	return ((CKLBUITask*)pCtx)->reconnect((const char*)nodeName); }

//======================================================================================
#include "CKLBUISimpleItem.h"

extern "C" DllExport s32* CKLBUISimpleItem_create(s32* pParent, u32 order, float x, float y, s32* asset)
{	return (s32*)CKLBUISimpleItem::create((CKLBUITask*)pParent, NULL, order, x, y, (const char*)asset); }

extern "C" DllExport u32 CKLBUISimpleItem_getOrder(s32* pCtx)
{	return ((CKLBUISimpleItem*)pCtx)->getOrder(); 	}
extern "C" DllExport void CKLBUISimpleItem_setOrder(s32* pCtx, u32 order)
{	((CKLBUISimpleItem*)pCtx)->setOrder(order);		}

extern "C" DllExport s32* CKLBUISimpleItem_getAsset(s32* pCtx)
{	return (s32*)((CKLBUISimpleItem*)pCtx)->getAsset(); 	}

//======================================================================================
#include "CKLBUICanvas.h"

extern "C" DllExport s32* CKLBUICanvas_create(s32* pParent, u32 order, float x, float y, u32 vertexMax, u32 indexMax)
{	return (s32*)CKLBUICanvas::create((CKLBUITask*)pParent, NULL, order, x, y, vertexMax, indexMax, NULL); }

extern "C" DllExport u32 CKLBUICanvas_getOrder(s32* pCtx)									
{	return ((CKLBUICanvas*)pCtx)->getOrder(); 			}
extern "C" DllExport void CKLBUICanvas_setOrder(s32* pCtx, u32 order) 					
{	((CKLBUICanvas*)pCtx)->setOrder(order);				}

extern "C" DllExport u32 CKLBUICanvas_getIdxMax(s32* pCtx)
{	return ((CKLBUICanvas*)pCtx)->getIdxMax();			}

extern "C" DllExport void CKLBUICanvas_setFreeze(s32* pCtx, bool freeze) 				
{	((CKLBUICanvas*)pCtx)->setFreeze(freeze);			}

extern "C" DllExport bool CKLBUICanvas_addResource(s32* pCtx, s32* asset)
{	return ((CKLBUICanvas*)pCtx)->addAsset((const char*)asset); }

extern "C" DllExport void CKLBUICanvas_drawImage(s32* pCtx, float x, float y, u32 idx, u32 color)
{	((CKLBUICanvas*)pCtx)->drawImage(x,y,idx,color);	}

extern "C" DllExport void CKLBUICanvas_drawImageScale(s32* pCtx, float x, float y, float scale,u32 idx, u32 color)
{	((CKLBUICanvas*)pCtx)->drawImageScale(x,y,scale,idx,color);	}

extern "C" DllExport void CKLBUICanvas_fillRect(s32* pCtx, float x, float y, float w, float h, u32 color)
{	((CKLBUICanvas*)pCtx)->fillRect(x,y,w,h,color);		}

extern "C" DllExport void CKLBUICanvas_startDynamicSection(s32* pCtx, u32 idx)	
{	((CKLBUICanvas*)pCtx)->startDynamicSection(idx);	}

extern "C" DllExport void CKLBUICanvas_endDynamicSection(s32* pCtx, u32 idx)		
{	((CKLBUICanvas*)pCtx)->endDynamicSection(idx);		}
	
extern "C" DllExport void CKLBUICanvas_dynamicSectionTranslate(s32* pCtx, u32 idx, float deltaX, float deltaY)
{	((CKLBUICanvas*)pCtx)->dynamicSectionTranslate(idx, deltaX, deltaY); }

extern "C" DllExport void CKLBUICanvas_dynamicSectionColor(s32* pCtx, u32 idx, u32 color)
{	((CKLBUICanvas*)pCtx)->dynamicSectionColor(idx,color);	}

//======================================================================================
#include "CKLBUIScale9.h"

extern "C" DllExport s32* CKLBUIScale9_create(s32* pParent, u32 order, float x, float y, s32 width, s32 height, s32* SCALE9Asset)
{	return (s32*)CKLBUIScale9::create((CKLBUITask*)pParent, NULL, order, x, y, width, height, (const char*)SCALE9Asset); }

extern "C" DllExport void CKLBUIScale9_setWidth(s32* pCtx, s32 width)
{	((CKLBUIScale9*)pCtx)->setWidth(width);				}

extern "C" DllExport s32 CKLBUIScale9_getWidth(s32* pCtx)
{	return ((CKLBUIScale9*)pCtx)->getWidth(); 			}

extern "C" DllExport void CKLBUIScale9_setHeight(s32* pCtx, s32 height)
{	((CKLBUIScale9*)pCtx)->setHeight(height);			}

extern "C" DllExport s32 CKLBUIScale9_getHeight(s32* pCtx)
{	return ((CKLBUIScale9*)pCtx)->getHeight(); 			}

extern "C" DllExport void CKLBUIScale9_setOrder(s32* pCtx, u32 order)
{	((CKLBUIScale9*)pCtx)->setOrder(order);				}

extern "C" DllExport u32 CKLBUIScale9_getOrder(s32* pCtx)
{	return ((CKLBUIScale9*)pCtx)->getOrder(); 			}

extern "C" DllExport s32* CKLBUIScale9_getAsset(s32* pCtx)
{	return (s32*)((CKLBUIScale9*)pCtx)->getAsset(); 	}

extern "C" DllExport bool CKLBUIScale9_setAsset(s32* pCtx, s32* asset)
{	return ((CKLBUIScale9*)pCtx)->setAsset((const char*)asset); 		}

//======================================================================================
#include "CKLBUIScrollBar.h"

extern "C" DllExport s32* CKLBUIScrollBar_create(
	s32* pParent,
	u32 order, float x, float y, float width, float height,
	s32 minValue, s32 maxValue, s32 pos,
	s32* image,
	s32 slider_size, s32 min_slider_size, 
	u32 colorNormal, u32 colorSelect, bool vert, bool active, bool hideMode)
{
	return (s32*)CKLBUIScrollBar::create(
		(CKLBUITask*)pParent, NULL, 
		order, x, y, width, height,
		minValue, maxValue, pos,
		(const char*)image,
		slider_size, min_slider_size,
		NULL,
		colorNormal, colorSelect, vert, active, hideMode);
}

extern "C" DllExport s32 CKLBUIScrollBar_getMin(s32* pCtx)
{	return ((CKLBUIScrollBar*)pCtx)->getMin(); 			}
extern "C" DllExport void CKLBUIScrollBar_setMin				(s32* pCtx, s32 value)
{	((CKLBUIScrollBar*)pCtx)->setMin(value);			}

extern "C" DllExport s32 CKLBUIScrollBar_getMax(s32* pCtx)
{	return ((CKLBUIScrollBar*)pCtx)->getMax(); 			}
extern "C" DllExport void CKLBUIScrollBar_setMax				(s32* pCtx, s32 value)
{	((CKLBUIScrollBar*)pCtx)->setMax(value);			}

extern "C" DllExport s32 CKLBUIScrollBar_getPos(s32* pCtx)
{	return ((CKLBUIScrollBar*)pCtx)->getPos(); 			}
extern "C" DllExport void CKLBUIScrollBar_setPos				(s32* pCtx, s32 value)
{	((CKLBUIScrollBar*)pCtx)->setPos(value);			}

extern "C" DllExport s32 CKLBUIScrollBar_getSliderSize(s32* pCtx)
{	return ((CKLBUIScrollBar*)pCtx)->getSliderSize(); 	}
extern "C" DllExport void CKLBUIScrollBar_setSliderSize		(s32* pCtx, s32 value)
{	((CKLBUIScrollBar*)pCtx)->setSliderSize(value);		}

extern "C" DllExport s32 CKLBUIScrollBar_getSliderSizeMin(s32* pCtx)
{	return ((CKLBUIScrollBar*)pCtx)->getSliderSizeMin(); }
extern "C" DllExport void CKLBUIScrollBar_setSliderSizeMin	(s32* pCtx, s32 value)
{	((CKLBUIScrollBar*)pCtx)->setSliderSizeMin(value);	}

extern "C" DllExport bool CKLBUIScrollBar_getTouchActive(s32* pCtx)
{	return ((CKLBUIScrollBar*)pCtx)->getTouchActive(); 	}
extern "C" DllExport void CKLBUIScrollBar_setTouchActive		(s32* pCtx, bool active)
{	((CKLBUIScrollBar*)pCtx)->setTouchActive(active);	}

extern "C" DllExport u32  CKLBUIScrollBar_getNormalColor		(s32* pCtx)
{	return ((CKLBUIScrollBar*)pCtx)->getColorMode(0); }
extern "C" DllExport void CKLBUIScrollBar_setNormalColor		(s32* pCtx, u32 color)
{	((CKLBUIScrollBar*)pCtx)->setColorMode(0,color); }

extern "C" DllExport u32  CKLBUIScrollBar_getActiveColor		(s32* pCtx)
{	return ((CKLBUIScrollBar*)pCtx)->getColorMode(1); }
extern "C" DllExport void CKLBUIScrollBar_setActiveColor		(s32* pCtx, u32 color)
{	((CKLBUIScrollBar*)pCtx)->setColorMode(1,color); }

extern "C" DllExport void CKLBUIScrollBar_setMode			(s32* pCtx, u32 mode)
{	((CKLBUIScrollBar*)pCtx)->setMode(mode);	}

extern "C" DllExport bool CKLBUIScrollBar_getVertical		(s32* pCtx)
{	return ((CKLBUIScrollBar*)pCtx)->getVertical(); }
extern "C" DllExport void CKLBUIScrollBar_setVertical		(s32* pCtx, bool vertical)
{	((CKLBUIScrollBar*)pCtx)->setVertical(vertical);	}

extern "C" DllExport u32 CKLBUIScrollBar_getWidth			(s32* pCtx)
{	return ((CKLBUIScrollBar*)pCtx)->getWidth(); } 
extern "C" DllExport void CKLBUIScrollBar_setWidth			(s32* pCtx, s32 width)
{	((CKLBUIScrollBar*)pCtx)->setWidth(width);	}

extern "C" DllExport u32 CKLBUIScrollBar_getHeight			(s32* pCtx)
{	return ((CKLBUIScrollBar*)pCtx)->getHeight(); } 
extern "C" DllExport void CKLBUIScrollBar_setHeight			(s32* pCtx, s32 height)
{	((CKLBUIScrollBar*)pCtx)->setHeight(height);	}

extern "C" DllExport u32 CKLBUIScrollBar_getOrder			(s32* pCtx)
{	return ((CKLBUIScrollBar*)pCtx)->getOrder(); } 
extern "C" DllExport void CKLBUIScrollBar_setOrder			(s32* pCtx, u32 order)
{	((CKLBUIScrollBar*)pCtx)->setOrder(order);	}

extern "C" DllExport s32* CKLBUIScrollBar_getImage	(s32* pCtx)
{	return (s32*)((CKLBUIScrollBar*)pCtx)->getImage(); }

extern "C" DllExport u32 CKLBUIScrollBar_getMode			(s32* pCtx)
{	return ((CKLBUIScrollBar*)pCtx)->getMode(); } 

extern "C" DllExport bool CKLBUIScrollBar_selectScrMgr		(s32* pCtx, s32* name, int len, int* args)
{	return ((CKLBUIScrollBar*)pCtx)->selectScrMgr((const char*)name, len, args); }

//======================================================================================
#include "CKLBUIWebArea.h"

extern "C" DllExport s32* CKLBUIWebArea_create(s32* pParent, bool mode, float x, float y, float width, float height, s32* url)
{	return (s32*)CKLBUIWebArea::create((CKLBUITask*)pParent, NULL, mode, x, y, width, height, (const char*)url, NULL); }

extern "C" DllExport void CKLBUIWebArea_setWidth(s32* pCtx, s32 width)
{	((CKLBUIWebArea*)pCtx)->setWidth(width);	}
extern "C" DllExport s32 CKLBUIWebArea_getWidth(s32* pCtx)
{	return ((CKLBUIWebArea*)pCtx)->getWidth(); }

extern "C" DllExport void CKLBUIWebArea_setHeight(s32* pCtx, s32 height)
{	((CKLBUIWebArea*)pCtx)->setHeight(height);	}
extern "C" DllExport s32 CKLBUIWebArea_getHeight(s32* pCtx)
{	return ((CKLBUIWebArea*)pCtx)->getHeight(); }

extern "C" DllExport void CKLBUIWebArea_setText(s32* pCtx, s32* text)
{	((CKLBUIWebArea*)pCtx)->setText((const char*)text);	}
extern "C" DllExport s32* CKLBUIWebArea_getText(s32* pCtx)
{	return (s32*)((CKLBUIWebArea*)pCtx)->getText(); }

extern "C" DllExport void CKLBUIWebArea_setScalesPageToFit(s32* pCtx, bool b)
{	((CKLBUIWebArea*)pCtx)->setScalesPageToFit(b);	}

extern "C" DllExport void CKLBUIWebArea_setBgColor(s32* pCtx, u32 argb) {	
	u32 alpha = argb >> 24;
	u32 color = argb & 0xFFFFFF;	
	((CKLBUIWebArea*)pCtx)->setBgColor(alpha, color);	
}

//======================================================================================
#include "CKLBUIVirtualDoc.h"

extern "C" DllExport s32* CKLBUIVirtualDoc_create(	s32* pParent,
											u32 order, float x, float y,
											u32 doc_width, u32 doc_height, 
											u32 view_width, u32 view_height,
											u32 max_command_nums, bool vertical)
{	return (s32*)CKLBUIVirtualDoc::create((CKLBUITask*)pParent, NULL, order, x, y, 
									doc_width, doc_height, view_width, view_height, max_command_nums, vertical); 
}

extern "C" DllExport void CKLBUIVirtualDoc_clear(s32* pCtx, u32 color) 
{ ((CKLBUIVirtualDoc*)pCtx)->clear(color); }

extern "C" DllExport void CKLBUIVirtualDoc_setFont(s32* pCtx, u32 idx, s32* fontName, u32 fontSize) 
{ ((CKLBUIVirtualDoc*)pCtx)->setFont(idx, (const char*)fontName, fontSize); }

extern "C" DllExport void CKLBUIVirtualDoc_setViewPortPos(s32* pCtx, s32 x, s32 y) 
{ ((CKLBUIVirtualDoc*)pCtx)->setViewPortPos(x, y); }

extern "C" DllExport void CKLBUIVirtualDoc_drawLine(s32* pCtx, s32 x0, s32 y0, s32 x1, s32 y1, u32 color)
{ ((CKLBUIVirtualDoc*)pCtx)->drawLine(x0, y0, x1, y1, color); }

extern "C" DllExport void CKLBUIVirtualDoc_drawImage(s32* pCtx, s32 x0, s32 y0, s32* image, u32 alpha) 
{	((CKLBUIVirtualDoc*)pCtx)->drawImage(x0, y0, (const char*)image, alpha);	}

extern "C" DllExport void CKLBUIVirtualDoc_fillRect(s32* pCtx, s32 x0, s32 y0, u32 width, u32 height, u32 color, bool fill)
{	((CKLBUIVirtualDoc*)pCtx)->fillRect(x0,y0,width,height,color,fill); }

extern "C" DllExport void CKLBUIVirtualDoc_drawText(s32* pCtx, s32 x0, s32 y0, s32* str, u32 color, u32 fontidx)
{	((CKLBUIVirtualDoc*)pCtx)->drawText(x0,y0,(const char*)str,color,fontidx); }

extern "C" DllExport void CKLBUIVirtualDoc_startDocument(s32* pCtx)
{	((CKLBUIVirtualDoc*)pCtx)->startDocument();	}

extern "C" DllExport void CKLBUIVirtualDoc_checkDocumentSize(s32* pCtx)
{	((CKLBUIVirtualDoc*)pCtx)->checkDocumentSize();	}

extern "C" DllExport void CKLBUIVirtualDoc_endDocument(s32* pCtx)
{	((CKLBUIVirtualDoc*)pCtx)->endDocument();	}

extern "C" DllExport u32 CKLBUIVirtualDoc_getCommandMax(s32* pCtx) 
{ return ((CKLBUIVirtualDoc*)pCtx)->getCommandMax(); }
extern "C" DllExport void CKLBUIVirtualDoc_setCommandMax(s32* pCtx, u32 command) 
{	((CKLBUIVirtualDoc*)pCtx)->setCommandMax(command);	}

extern "C" DllExport u32 CKLBUIVirtualDoc_getDocHeight(s32* pCtx) 
{ return ((CKLBUIVirtualDoc*)pCtx)->getDocHeight(); }
extern "C" DllExport void CKLBUIVirtualDoc_setDocHeight(s32* pCtx, u32 height) 
{	((CKLBUIVirtualDoc*)pCtx)->setDocHeight(height); }

extern "C" DllExport u32 CKLBUIVirtualDoc_getDocWidth(s32* pCtx) 
{ return ((CKLBUIVirtualDoc*)pCtx)->getDocWidth();	}
extern "C" DllExport void CKLBUIVirtualDoc_setDocWidth(s32* pCtx, u32 width) 
{	((CKLBUIVirtualDoc*)pCtx)->setDocWidth(width); }

extern "C" DllExport bool CKLBUIVirtualDoc_getVertical(s32* pCtx) 
{ return ((CKLBUIVirtualDoc*)pCtx)->getVertical(); }
extern "C" DllExport void CKLBUIVirtualDoc_setVertical(s32* pCtx, bool vertical) 
{	((CKLBUIVirtualDoc*)pCtx)->setVertical(vertical); }

extern "C" DllExport u32 CKLBUIVirtualDoc_getViewHeight(s32* pCtx) 
{ return ((CKLBUIVirtualDoc*)pCtx)->getViewHeight(); }
extern "C" DllExport void CKLBUIVirtualDoc_setViewHeight(s32* pCtx, u32 height) 
{	((CKLBUIVirtualDoc*)pCtx)->setViewHeight(height); }

extern "C" DllExport u32 CKLBUIVirtualDoc_getViewWidth(s32* pCtx) 
{ return ((CKLBUIVirtualDoc*)pCtx)->getViewWidth(); }
extern "C" DllExport void CKLBUIVirtualDoc_setViewWidth(s32* pCtx, u32 width) 
{	((CKLBUIVirtualDoc*)pCtx)->setViewWidth(width); }

extern "C" DllExport u32 CKLBUIVirtualDoc_getOrder(s32* pCtx)
{	return ((CKLBUIVirtualDoc*)pCtx)->getOrder(); }
extern "C" DllExport void CKLBUIVirtualDoc_setOrder(s32* pCtx, u32 order) 
{	((CKLBUIVirtualDoc*)pCtx)->setOrder(order); }

extern "C" DllExport void CKLBUIVirtualDoc_setAlign(s32* pCtx, u32 align, u32 alignWidth)
{	((CKLBUIVirtualDoc*)pCtx)->setAlign(align, alignWidth);	}

//======================================================================================
#include "CKLBUISWFPlayer.h"

extern "C" DllExport s32* CKLBUISWFPlayer_create(	s32* pParent, 
											u32 order, float x, float y, s32* asset,
											s32* movie_name, s32** replace_list, int asset_cnt)
{	return (s32*)CKLBUISWFPlayer::create((CKLBUITask*)pParent, NULL, order, x, y, (const char*)asset, (const char*)movie_name, NULL, (const char**)replace_list, asset_cnt); }

extern "C" DllExport bool CKLBUISWFPlayer_getPlay(s32* pCtx)			
{ return ((CKLBUISWFPlayer*)pCtx)->getPlay(); }
extern "C" DllExport void CKLBUISWFPlayer_setPlay(s32* pCtx,bool play)
{	((CKLBUISWFPlayer*)pCtx)->setPlay(play); }

extern "C" DllExport u32 CKLBUISWFPlayer_getOrder(s32* pCtx)			
{ return ((CKLBUISWFPlayer*)pCtx)->getOrder(); }
extern "C" DllExport void CKLBUISWFPlayer_setOrder(s32* pCtx,u32 order)
{	((CKLBUISWFPlayer*)pCtx)->setOrder(order); }

extern "C" DllExport void CKLBUISWFPlayer_gotoFrame(s32* pCtx,s32* label)
{	((CKLBUISWFPlayer*)pCtx)->gotoFrame((const char*)label); }

extern "C" DllExport u16 CKLBUISWFPlayer_getFrameRate(s32* pCtx)
{	return ((CKLBUISWFPlayer*)pCtx)->getFrameRate(); }
extern "C" DllExport void CKLBUISWFPlayer_setFrameRate(s32* pCtx,u32 fps)
{	((CKLBUISWFPlayer*)pCtx)->setFrameRate(fps); }

extern "C" DllExport bool CKLBUISWFPlayer_isAnimating(s32* pCtx) 
{ return ((CKLBUISWFPlayer*)pCtx)->isAnimating(); }

extern "C" DllExport void CKLBUISWFPlayer_setFrameRateScale(s32* pCtx,float scale)
{	((CKLBUISWFPlayer*)pCtx)->setFrameRateScale(scale); }

extern "C" DllExport s32* CKLBUISWFPlayer_getAsset(s32* pCtx)
{ return (s32*)((CKLBUISWFPlayer*)pCtx)->getAsset(); 		}

extern "C" DllExport s32* CKLBUISWFPlayer_getMovieName(s32* pCtx)
{ return (s32*)((CKLBUISWFPlayer*)pCtx)->getMovieName(); 	}

extern "C" DllExport float CKLBUISWFPlayer_getVolume(s32* pCtx)
{ return ((CKLBUISWFPlayer*)pCtx)->getVolume(); 	}
extern "C" DllExport void CKLBUISWFPlayer_setVolume(s32* pCtx,float volume)
{	((CKLBUISWFPlayer*)pCtx)->setVolume(volume); 	}
	
//======================================================================================
#include "CKLBUIGroup.h"

extern "C" DllExport s32* CKLBUIGroup_create(s32* pParent, float x, float y)
{	return (s32*)CKLBUIGroup::create((CKLBUITask*)pParent, NULL, x, y); }

extern "C" DllExport bool CKLBUIGroup_setAnimCallback(s32* pCtx, s32* callback)
{	return ((CKLBUIGroup*)pCtx)->setAnimCallback((const char*)callback); }

extern "C" DllExport bool CKLBUIGroup_setAnimation(s32* pCtx, s32* name, bool blend)
{	return ((CKLBUIGroup*)pCtx)->setAnimation((const char*)name, blend); }

extern "C" DllExport bool CKLBUIGroup_isAnim(s32* pCtx, s32* name)
{	return ((CKLBUIGroup*)pCtx)->isAnim((const char*)name); }

extern "C" DllExport bool CKLBUIGroup_skipAnim(s32* pCtx, s32* name)
{	return ((CKLBUIGroup*)pCtx)->skipAnim((const char*)name); }

//======================================================================================
#include "CKLBUIPolyline.h"

extern "C" DllExport s32* CKLBUIPolyline_create(s32* pParent, u32 order, u32 maxPoint)
{	return (s32*)CKLBUIPolyline::create((CKLBUITask*)pParent, NULL, order, maxPoint); }

extern "C" DllExport u32 CKLBUIPolyline_getMaxPoint(s32* pCtx) 
{	return ((CKLBUIPolyline*)pCtx)->getMaxPoint();	}
extern "C" DllExport void CKLBUIPolyline_setMaxPoint(s32* pCtx,u32 maxpointcount)
{	((CKLBUIPolyline*)pCtx)->setMaxPoint(maxpointcount); }

extern "C" DllExport u32 CKLBUIPolyline_getOrder(s32* pCtx)
{	return ((CKLBUIPolyline*)pCtx)->getOrder();	}

extern "C" DllExport u32 CKLBUIPolyline_getPointCount(s32* pCtx) 
{	return ((CKLBUIPolyline*)pCtx)->getPointCount();	}
extern "C" DllExport void CKLBUIPolyline_setPointCount(s32* pCtx,u32 pointcount)
{	((CKLBUIPolyline*)pCtx)->setPointCount(pointcount); }

extern "C" DllExport void CKLBUIPolyline_setPoint(s32* pCtx,u32 idx, float x, float y)
{	((CKLBUIPolyline*)pCtx)->setPoint(idx,x,y); }

extern "C" DllExport u32 CKLBUIPolyline_getColor(s32* pCtx) 
{	return ((CKLBUIPolyline*)pCtx)->getColor();	}
extern "C" DllExport void CKLBUIPolyline_setColor(s32* pCtx,u32 color)
{	((CKLBUIPolyline*)pCtx)->setColor(color); }

//======================================================================================
#include "CKLBUIFreeVertItem.h"

extern "C" DllExport s32* CKLBUIFreeVertItem_create(s32* pParent, u32 order, float x, float y, s32* asset, float* vertices)
{	return (s32*)CKLBUIFreeVertItem::create((CKLBUITask*)pParent, NULL, order, x, y, (const char*)asset, vertices); }

extern "C" DllExport u32 CKLBUIFreeVertItem_getOrder(s32* pCtx)
{	return ((CKLBUIFreeVertItem*)pCtx)->getOrder(); }
extern "C" DllExport void CKLBUIFreeVertItem_setOrder(s32* pCtx,u32 order)
{	((CKLBUIFreeVertItem*)pCtx)->setOrder(order); }

extern "C" DllExport s32* CKLBUIFreeVertItem_getAsset(s32* pCtx)
{	return (s32*)((CKLBUIFreeVertItem*)pCtx)->getAsset(); }

extern "C" DllExport void CKLBUIFreeVertItem_setVertices(s32* pCtx, float* coord)
{	((CKLBUIFreeVertItem*)pCtx)->setVertXY(coord); }
	
extern "C" DllExport void CKLBUIFreeVertItem_setColors(s32* pCtx, u32* colors)
{	((CKLBUIFreeVertItem*)pCtx)->setVertColors(colors); }	

extern "C" DllExport void CKLBUIFreeVertItem_setVertCol(s32* pCtx, u32 idx, u32 argb)
{	return ((CKLBUIFreeVertItem*)pCtx)->setVertCol(idx, argb); }

extern "C" DllExport void CKLBUIFreeVertItem_setUV(s32* pCtx, float* uv)
{	((CKLBUIFreeVertItem*)pCtx)->setVertUV(uv); }

//======================================================================================
#include "CKLBUITextInput.h"

extern "C" DllExport s32* CKLBUITextInput_create(s32* pParent,
										bool passwdmode,
										float x, float y, float width, float height,
										s32* default_text,
										u32 widget_id, int maxlen, u32 chartype)
{	return (s32*)CKLBUITextInput::create((CKLBUITask*)pParent, NULL, passwdmode, x, y, width, height, (const char*)default_text, NULL, widget_id, maxlen, chartype); }

extern "C" DllExport u32  CKLBUITextInput_getWidth(s32* pCtx)
{	return ((CKLBUITextInput*)pCtx)->getWidth(); 	}
extern "C" DllExport void CKLBUITextInput_setWidth(s32* pCtx, u32 width)
{	((CKLBUITextInput*)pCtx)->setWidth(width); 		}

extern "C" DllExport u32 CKLBUITextInput_getHeight(s32* pCtx)
{	return ((CKLBUITextInput*)pCtx)->getHeight(); 	}
extern "C" DllExport void CKLBUITextInput_setHeight(s32* pCtx, u32 height)
{	((CKLBUITextInput*)pCtx)->setHeight(height); 	}

extern "C" DllExport s32* CKLBUITextInput_getText(s32* pCtx)
{	return (s32*)((CKLBUITextInput*)pCtx)->getText(); 	}
extern "C" DllExport void CKLBUITextInput_setText(s32* pCtx, s32* text)
{	((CKLBUITextInput*)pCtx)->setText((const char*)text); 		}

extern "C" DllExport void CKLBUITextInput_setPlaceHolder(s32* pCtx, s32* placeHolder)
{	((CKLBUITextInput*)pCtx)->setPlaceHolder((const char*)placeHolder);	}

extern "C" DllExport int CKLBUITextInput_getMaxLen(s32* pCtx)
{	return ((CKLBUITextInput*)pCtx)->getMaxLen(); 	}
extern "C" DllExport void CKLBUITextInput_setMaxLen(s32* pCtx, int maxLen)
{	((CKLBUITextInput*)pCtx)->setMaxLen(maxLen); 	}

extern "C" DllExport void CKLBUITextInput_setCharType(s32* pCtx, u32 charType)
{	((CKLBUITextInput*)pCtx)->setCharType(charType); }

extern "C" DllExport s32 CKLBUITextInput_getCharCount(s32* pCtx)
{	return ((CKLBUITextInput*)pCtx)->getCharCount(); }

extern "C" DllExport void CKLBUITextInput_setColor(s32* pCtx, bool bTouch, u32 fgRgb, u32 bgRgb)
{	((CKLBUITextInput*)pCtx)->setColor(bTouch, fgRgb, bgRgb); 	}

extern "C" DllExport void CKLBUITextInput_setFont(s32* pCtx, s32* fontName, float fontSize)
{	((CKLBUITextInput*)pCtx)->setFont((const char*)fontName, fontSize); 		}

//======================================================================================
#include "CKLBUIMultiImgItem.h"

extern "C" DllExport s32* CKLBUIMultiImgItem_create(s32* pParent, u32 order, float x, float y, u32 idx, s32** pArrayAsset,
												u32* pArrayIndexes, u32 assetCount)
{ return (s32*)CKLBUIMultiImgItem::create((CKLBUITask*)pParent,NULL,order,x,y,idx,(const char**)pArrayAsset,pArrayIndexes,assetCount); }

extern "C" DllExport u32 CKLBUIMultiImgItem_getIndexMax(s32* pCtx)
{	return ((CKLBUIMultiImgItem*)pCtx)->getIndexMax(); }
extern "C" DllExport void CKLBUIMultiImgItem_setIndexMax(s32* pCtx,u32 index)
{	((CKLBUIMultiImgItem*)pCtx)->setIndexMax(index); }

extern "C" DllExport u32 CKLBUIMultiImgItem_getOrder(s32* pCtx)
{	return ((CKLBUIMultiImgItem*)pCtx)->getOrder(); }
extern "C" DllExport void CKLBUIMultiImgItem_setOrder(s32* pCtx,u32 order)
{	((CKLBUIMultiImgItem*)pCtx)->setOrder(order); }

extern "C" DllExport u32 CKLBUIMultiImgItem_getIndex(s32* pCtx)
{	return ((CKLBUIMultiImgItem*)pCtx)->getIndex(); }
extern "C" DllExport void CKLBUIMultiImgItem_setIndex(s32* pCtx, u32 index)
{	((CKLBUIMultiImgItem*)pCtx)->setIndex(index); }

extern "C" DllExport bool CKLBUIMultiImgItem_changeAssets(s32* pCtx, s32** pArrayAsset, u32* pArrayIndexes, u32 assetCount)
{ return ((CKLBUIMultiImgItem*)pCtx)->changeAssets((const char**)pArrayAsset, pArrayIndexes, assetCount); }

//======================================================================================
#include "CKLBUIRubberBand.h"

extern "C" DllExport s32* CKLBUIRubberBand_create(s32* pParent, u32 order, float x, float y, u32 resolution, s32* origin, s32* joint,
											s32* point, u32 flags, u32 animTime, s32 joint_order_off, s32 point_order_off, bool rot_origin, bool rot_joint, bool rot_point)
{ return (s32*)CKLBUIRubberBand::create((CKLBUITask*)pParent,NULL,order,x,y,resolution,(const char*)origin,(const char*)joint,(const char*)point,flags,animTime,joint_order_off,point_order_off,rot_origin,rot_joint,rot_point); }

extern "C" DllExport float CKLBUIRubberBand_getOriginX(s32* pCtx)
{ return ((CKLBUIRubberBand*)pCtx)->getOriginX(); }
extern "C" DllExport void CKLBUIRubberBand_setOriginX(s32* pCtx,float x)
{ ((CKLBUIRubberBand*)pCtx)->setOriginX(x); }

extern "C" DllExport float CKLBUIRubberBand_getOriginY(s32* pCtx)
{ return ((CKLBUIRubberBand*)pCtx)->getOriginY(); }
extern "C" DllExport void CKLBUIRubberBand_setOriginY(s32* pCtx,float y)
{ ((CKLBUIRubberBand*)pCtx)->setOriginY(y); }

extern "C" DllExport float CKLBUIRubberBand_getPointX(s32* pCtx)
{ return ((CKLBUIRubberBand*)pCtx)->getPointX(); }
extern "C" DllExport void CKLBUIRubberBand_setPointX(s32* pCtx,float x)
{ ((CKLBUIRubberBand*)pCtx)->setPointX(x); }

extern "C" DllExport float CKLBUIRubberBand_getPointY(s32* pCtx)
{ return ((CKLBUIRubberBand*)pCtx)->getPointY(); }
extern "C" DllExport void CKLBUIRubberBand_setPointY(s32* pCtx,float y)
{ ((CKLBUIRubberBand*)pCtx)->setPointY(y); }

extern "C" DllExport bool CKLBUIRubberBand_getFAnim(s32* pCtx)
{ return ((CKLBUIRubberBand*)pCtx)->getFAnim(); }
extern "C" DllExport void CKLBUIRubberBand_setFAnim(s32* pCtx,bool fAnim)
{ ((CKLBUIRubberBand*)pCtx)->setFAnim(fAnim); }

extern "C" DllExport bool CKLBUIRubberBand_getFAnimRT(s32* pCtx)
{ return ((CKLBUIRubberBand*)pCtx)->getFAnimRT(); }
extern "C" DllExport void CKLBUIRubberBand_setFAnimRT(s32* pCtx,bool fAnimRT)
{ ((CKLBUIRubberBand*)pCtx)->setFAnimRT(fAnimRT); }

extern "C" DllExport u32 CKLBUIRubberBand_getAnimTime(s32* pCtx)
{ return ((CKLBUIRubberBand*)pCtx)->getAnimTime(); }
extern "C" DllExport void CKLBUIRubberBand_setAnimTime(s32* pCtx,u32 animTime)
{ ((CKLBUIRubberBand*)pCtx)->setAnimTime(animTime); }

extern "C" DllExport u32 CKLBUIRubberBand_getOrder(s32* pCtx)
{ return ((CKLBUIRubberBand*)pCtx)->getOrder(); }

extern "C" DllExport s32* CKLBUIRubberBand_getAssetOrigin(s32* pCtx)
{ return (s32*)((CKLBUIRubberBand*)pCtx)->getAssetOrigin(); }

extern "C" DllExport s32* CKLBUIRubberBand_getAssetJoint(s32* pCtx)
{ return (s32*)((CKLBUIRubberBand*)pCtx)->getAssetJoint(); }

extern "C" DllExport s32* CKLBUIRubberBand_getAssetPoint(s32* pCtx)
{ return (s32*)((CKLBUIRubberBand*)pCtx)->getAssetPoint(); }

extern "C" DllExport bool CKLBUIRubberBand_setOrder(s32* pCtx, u32 order_origin, u32 order_joint, u32 order_point)
{ return ((CKLBUIRubberBand*)pCtx)->setOrder(order_origin, order_joint, order_point); }

//======================================================================================
#include "CKLBUIPieChart.h"

extern "C" DllExport s32* CKLBUIPieChart_create(s32* pParent, u32 order, float x, float y, float width, float height, s32* asset, float start,
										float end, u32 anim, float initial)
{ return (s32*)CKLBUIPieChart::create((CKLBUITask*)pParent,NULL,order,x,y,width,height,(const char*)asset,start,end,anim,initial); }

extern "C" DllExport float CKLBUIPieChart_getStart(s32* pCtx)
{ return ((CKLBUIPieChart*)pCtx)->getStart(); }
extern "C" DllExport void CKLBUIPieChart_setStart(s32* pCtx,float start)
{ ((CKLBUIPieChart*)pCtx)->setStart(start); }

extern "C" DllExport float CKLBUIPieChart_getEnd(s32* pCtx)
{ return ((CKLBUIPieChart*)pCtx)->getEnd(); }
extern "C" DllExport void CKLBUIPieChart_setEnd(s32* pCtx,float end)
{ ((CKLBUIPieChart*)pCtx)->setEnd(end); }

extern "C" DllExport float CKLBUIPieChart_getValue(s32* pCtx)
{ return ((CKLBUIPieChart*)pCtx)->getValue(); }
extern "C" DllExport void CKLBUIPieChart_setValue(s32* pCtx,float value)
{ ((CKLBUIPieChart*)pCtx)->setValue(value); }

extern "C" DllExport s32 CKLBUIPieChart_getAnim(s32* pCtx)
{ return ((CKLBUIPieChart*)pCtx)->getAnim(); }

extern "C" DllExport u32 CKLBUIPieChart_getOrder(s32* pCtx)
{ return ((CKLBUIPieChart*)pCtx)->getOrder(); }

extern "C" DllExport bool CKLBUIPieChart_changeAsset(s32* pCtx, s32* assetName)
{ return ((CKLBUIPieChart*)pCtx)->changeAsset((const char*)assetName); }

//======================================================================================
#include "CKLBUIMoviePlayer.h"

extern "C" DllExport s32* CKLBUIMoviePlayer_create(s32* pParent, bool mode, float x, float y, float width, float height, s32* url)
{ return (s32*)CKLBUIMoviePlayer::create((CKLBUITask*)pParent,NULL,mode,x,y,width,height,(const char*)url,NULL); }

extern "C" DllExport void CKLBUIMoviePlayer_setWidth(s32* pCtx,u32 width)
{ ((CKLBUIMoviePlayer*)pCtx)->setWidth(width); }

extern "C" DllExport u32 CKLBUIMoviePlayer_getWidth(s32* pCtx)
{ return ((CKLBUIMoviePlayer*)pCtx)->getWidth(); }

extern "C" DllExport void CKLBUIMoviePlayer_setHeight(s32* pCtx,u32 height)
{ ((CKLBUIMoviePlayer*)pCtx)->setHeight(height); }

extern "C" DllExport u32 CKLBUIMoviePlayer_getHeight(s32* pCtx)
{ return ((CKLBUIMoviePlayer*)pCtx)->getHeight(); }

extern "C" DllExport void CKLBUIMoviePlayer_setText(s32* pCtx, s32* text)
{ ((CKLBUIMoviePlayer*)pCtx)->setText((const char*)text); }

extern "C" DllExport s32* CKLBUIMoviePlayer_getText(s32* pCtx)
{ return (s32*)((CKLBUIMoviePlayer*)pCtx)->getText(); }

extern "C" DllExport void CKLBUIMoviePlayer_moviePlay(s32* pCtx)
{ ((CKLBUIMoviePlayer*)pCtx)->moviePlay(); }

extern "C" DllExport void CKLBUIMoviePlayer_movieStop(s32* pCtx)
{ ((CKLBUIMoviePlayer*)pCtx)->movieStop(); }

extern "C" DllExport void CKLBUIMoviePlayer_moviePause(s32* pCtx)
{ ((CKLBUIMoviePlayer*)pCtx)->moviePause(); }

extern "C" DllExport void CKLBUIMoviePlayer_movieResume(s32* pCtx)
{ ((CKLBUIMoviePlayer*)pCtx)->movieResume(); }

//======================================================================================
#include "CKLBUIDragIcon.h"

extern "C" DllExport s32* CKLBUIDragIcon_create(s32* pParent, u32 order, float x, float y, s32* tap_area, s32* asset, s32* drag_asset,
										s32 drag_order_offset, float drag_alpha, float center_x, float center_y, u32 flags)
{ return (s32*)CKLBUIDragIcon::create((CKLBUITask*)pParent,NULL,order,x,y,(CKLBUIDragIcon::AREA*)tap_area,(const char*)asset,(const char*)drag_asset,drag_order_offset,drag_alpha,center_x,center_y,NULL,flags); }

extern "C" DllExport u32	CKLBUIDragIcon_getOrder(s32* pCtx)
{ return ((CKLBUIDragIcon*)pCtx)->getOrder(); }

extern "C" DllExport s32* CKLBUIDragIcon_getAsset(s32* pCtx)
{ return (s32*)((CKLBUIDragIcon*)pCtx)->getAsset(); }

extern "C" DllExport s32* CKLBUIDragIcon_getDrag(s32* pCtx)
{ return (s32*)((CKLBUIDragIcon*)pCtx)->getDrag(); }

extern "C" DllExport u32	CKLBUIDragIcon_getFlags(s32* pCtx)
{ return ((CKLBUIDragIcon*)pCtx)->getFlags(); }
extern "C" DllExport void CKLBUIDragIcon_setFlags(s32* pCtx,u32 flag)
{ ((CKLBUIDragIcon*)pCtx)->setFlags(flag); }

extern "C" DllExport bool CKLBUIDragIcon_getEnable(s32* pCtx)
{ return ((CKLBUIDragIcon*)pCtx)->getEnable(); }
extern "C" DllExport void CKLBUIDragIcon_setEnable(s32* pCtx,bool enable)
{ ((CKLBUIDragIcon*)pCtx)->setEnable(enable); }

extern "C" DllExport float CKLBUIDragIcon_getDragScaleX(s32* pCtx)
{ return ((CKLBUIDragIcon*)pCtx)->getDragScaleX(); }
extern "C" DllExport void CKLBUIDragIcon_setDragScaleX(s32* pCtx,float scale)
{ ((CKLBUIDragIcon*)pCtx)->setDragScaleX(scale); }

extern "C" DllExport float CKLBUIDragIcon_getDragScaleY(s32* pCtx)
{ return ((CKLBUIDragIcon*)pCtx)->getDragScaleY(); }
extern "C" DllExport void CKLBUIDragIcon_setDragScaleY(s32* pCtx,float scale)
{ ((CKLBUIDragIcon*)pCtx)->setDragScaleY(scale); }

extern "C" DllExport void CKLBUIDragIcon_dragArea(s32* pCtx, s32* area)
{ ((CKLBUIDragIcon*)pCtx)->setDragArea(*(CKLBUIDragIcon::AREA*)area); }

//======================================================================================
#include "CKLBUIDebugItem.h"

extern "C" DllExport s32* CKLBUIDebugItem_create(s32* pParent, u32 order, float x, float y, u32 argb, s32* font, u32 size, s32* text, u32 id)
{
	u32 alpha = argb >> 24;
	u32 color = argb & 0xFFFFFF;
	return (s32*)CKLBUIDebugItem::create((CKLBUITask*)pParent,NULL,order,x,y,alpha,color,(const char*)font,size,(const char*)text,"",id);
}

extern "C" DllExport void CKLBUIDebugItem_setOrder(s32* pCtx,u32 order)
{ ((CKLBUIDebugItem*)pCtx)->setOrder(order); }
extern "C" DllExport u32 CKLBUIDebugItem_getOrder(s32* pCtx)
{ return ((CKLBUIDebugItem*)pCtx)->getOrder(); }

extern "C" DllExport void CKLBUIDebugItem_setColor(s32* pCtx,u32 color)
{ ((CKLBUIDebugItem*)pCtx)->setColor(color); }
extern "C" DllExport u32 CKLBUIDebugItem_getColor(s32* pCtx)
{ return ((CKLBUIDebugItem*)pCtx)->getColor(); }

extern "C" DllExport void CKLBUIDebugItem_setFont(s32* pCtx,s32* font)
{ ((CKLBUIDebugItem*)pCtx)->setFont((const char*)font); }
extern "C" DllExport s32* CKLBUIDebugItem_getFont(s32* pCtx)
{ return (s32*)((CKLBUIDebugItem*)pCtx)->getFont(); }

// Font size
extern "C" DllExport void CKLBUIDebugItem_setSize(s32* pCtx,u32 size)
{ ((CKLBUIDebugItem*)pCtx)->setSize(size); }
extern "C" DllExport u32 CKLBUIDebugItem_getSize(s32* pCtx)
{ return ((CKLBUIDebugItem*)pCtx)->getSize(); }

extern "C" DllExport void CKLBUIDebugItem_setText(s32* pCtx,s32* text)
{ ((CKLBUIDebugItem*)pCtx)->setText((const char*)text); }
extern "C" DllExport s32* CKLBUIDebugItem_getText(s32* pCtx)
{ return (s32*)((CKLBUIDebugItem*)pCtx)->getText(); }

//======================================================================================
#include "CKLBUILabel.h"

extern "C" DllExport s32* CKLBUILabel_create(s32* pParent, u32 order, float x, float y, u32 argb, s32* font, u32 size, s32* text, u32 align)
{ 
	u32 alpha = argb >> 24;
	u32 color = argb & 0xFFFFFF;
	return (s32*)CKLBUILabel::create((CKLBUITask*)pParent,NULL,order,x,y,alpha,color,(const char*)font,size,(const char*)text,align);
}

extern "C" DllExport u32 CKLBUILabel_getOrder(s32* pCtx)
{ return ((CKLBUILabel*)pCtx)->getOrder(); }
extern "C" DllExport void CKLBUILabel_setOrder(s32* pCtx,u32 order)
{ ((CKLBUILabel*)pCtx)->setOrder(order); }

extern "C" DllExport u32 CKLBUILabel_getAlign(s32* pCtx)
{ return ((CKLBUILabel*)pCtx)->getAlign(); }
extern "C" DllExport void CKLBUILabel_setAlign(s32* pCtx,u32 align)
{ ((CKLBUILabel*)pCtx)->setAlign(align); }

extern "C" DllExport s32* CKLBUILabel_getText(s32* pCtx)
{ return (s32*)((CKLBUILabel*)pCtx)->getText(); }
extern "C" DllExport void CKLBUILabel_setText(s32* pCtx,s32* txt)
{ ((CKLBUILabel*)pCtx)->setText((const char*)txt); }

extern "C" DllExport u32 CKLBUILabel_getColor(s32* pCtx)
{ return ((CKLBUILabel*)pCtx)->getColor(); }
extern "C" DllExport void CKLBUILabel_setColor(s32* pCtx,u32 color)
{ ((CKLBUILabel*)pCtx)->setColor(color); }

extern "C" DllExport s32* CKLBUILabel_getFont(s32* pCtx)
{ return (s32*)((CKLBUILabel*)pCtx)->getFont(); }
extern "C" DllExport void CKLBUILabel_setFont(s32* pCtx,s32* font)
{ ((CKLBUILabel*)pCtx)->setFont((const char*)font); }

extern "C" DllExport u32 CKLBUILabel_getFontSize(s32* pCtx)
{ return ((CKLBUILabel*)pCtx)->getFontSize(); }
extern "C" DllExport void CKLBUILabel_setFontSize(s32* pCtx,u32 size)
{ ((CKLBUILabel*)pCtx)->setFontSize(size); }

extern "C" DllExport void CKLBUILabel_setPosition(s32* pCtx, float x, float y)
{ ((CKLBUILabel*)pCtx)->setPosition(x,y); }

//======================================================================================
#include "CKLBUIList.h"
 
extern "C" DllExport  s32* CKLBUIList_create(s32* pParent, u32 base_order, u32 max_order, float x, float y, float clip_width, float clip_height,
													s32 default_line_step, bool vertical, u32 optional_flags)
{ return (s32*)CKLBUIList::create((CKLBUITask*)pParent,NULL,base_order,max_order,x,y,clip_width,clip_height,default_line_step,vertical,"",optional_flags); }
 
extern "C" DllExport u32 CKLBUIList_getWidth(s32* pCtx)
{ return ((CKLBUIList*)pCtx)->getWidth(); }
extern "C" DllExport void CKLBUIList_setWidth(s32* pCtx,u32 width)
{ ((CKLBUIList*)pCtx)->setWidth(width); }

extern "C" DllExport u32 CKLBUIList_getHeight(s32* pCtx)
{ return ((CKLBUIList*)pCtx)->getHeight(); }
extern "C" DllExport void CKLBUIList_setHeight(s32* pCtx,u32 height)
{ ((CKLBUIList*)pCtx)->setHeight(height); }

extern "C" DllExport s32 CKLBUIList_getStepX(s32* pCtx)
{ return ((CKLBUIList*)pCtx)->getStepX(); }
extern "C" DllExport void CKLBUIList_setStepX(s32* pCtx,s32 x)
{ ((CKLBUIList*)pCtx)->setStepX(x); }

extern "C" DllExport s32 CKLBUIList_getStepY(s32* pCtx)
{ return ((CKLBUIList*)pCtx)->getStepY(); }
extern "C" DllExport void CKLBUIList_setStepY(s32* pCtx,s32 x)
{ ((CKLBUIList*)pCtx)->setStepY(x); }

extern "C" DllExport u32 CKLBUIList_getOrder(s32* pCtx)
{ return ((CKLBUIList*)pCtx)->getOrder(); }
extern "C" DllExport void CKLBUIList_setOrder(s32* pCtx,u32 order)
{ ((CKLBUIList*)pCtx)->setOrder(order); }

extern "C" DllExport u32 CKLBUIList_getMaxOrder(s32* pCtx)
{ return ((CKLBUIList*)pCtx)->getMaxOrder(); }
extern "C" DllExport void CKLBUIList_setMaxOrder(s32* pCtx,u32 maxOrder)
{ ((CKLBUIList*)pCtx)->setMaxOrder(maxOrder); }

extern "C" DllExport bool CKLBUIList_getVertical(s32* pCtx)
{ return ((CKLBUIList*)pCtx)->getVertical(); }
extern "C" DllExport void CKLBUIList_setVertical(s32* pCtx,bool vertical)
{ ((CKLBUIList*)pCtx)->setVertical(vertical); }

extern "C" DllExport u32 CKLBUIList_getItems(s32* pCtx)
{ return ((CKLBUIList*)pCtx)->getItems(); }

extern "C" DllExport s32 CKLBUIList_getMarginTop(s32* pCtx)
{ return ((CKLBUIList*)pCtx)->getMarginTop(); }
extern "C" DllExport void CKLBUIList_setMarginTop(s32* pCtx,s32 top)
{ ((CKLBUIList*)pCtx)->setMarginTop(top); }

extern "C" DllExport s32 CKLBUIList_getMarginBottom(s32* pCtx)
{ return ((CKLBUIList*)pCtx)->getMarginBottom(); }
extern "C" DllExport void CKLBUIList_setMarginBottom(s32* pCtx,s32 bottom)
{ ((CKLBUIList*)pCtx)->setMarginBottom(bottom); }

extern "C" DllExport bool CKLBUIList_getDefaultScroll(s32* pCtx)
{ return ((CKLBUIList*)pCtx)->getDefaultScroll(); }
extern "C" DllExport void CKLBUIList_setDefaultScroll(s32* pCtx,bool scroll)
{ ((CKLBUIList*)pCtx)->setDefaultScroll(scroll); }
 
extern "C" DllExport bool CKLBUIList_cmdItemRemove(s32* pCtx,s32 idx)
{ return ((CKLBUIList*)pCtx)->cmdItemRemove(idx); }

extern "C" DllExport void CKLBUIList_cmdItemMove(s32* pCtx,s32 src, s32 dst)
{ ((CKLBUIList*)pCtx)->cmdItemMove(src,dst); }

extern "C" DllExport void CKLBUIList_cmdSetMargin(s32* pCtx,s32 top, s32 bottom)
{ ((CKLBUIList*)pCtx)->cmdSetMargin(top,bottom); }

extern "C" DllExport s32 CKLBUIList_cmdGetPosition(s32* pCtx)
{ return ((CKLBUIList*)pCtx)->cmdGetPosition(); }
extern "C" DllExport s32 CKLBUIList_cmdSetPosition(s32* pCtx, s32 pos, s32 dir)
{ return ((CKLBUIList*)pCtx)->cmdSetPosition(pos, dir); }

extern "C" DllExport s32 CKLBUIList_cmdSearchID(s32* pCtx,u32 id)	// Return a value ?
{ return ((CKLBUIList*)pCtx)->cmdSearchID(id); }

extern "C" DllExport void CKLBUIList_cmdSetItemPos(s32* pCtx,u32 mode, s32 idx, s32 offset)
{ ((CKLBUIList*)pCtx)->cmdSetItemPos(mode, idx, offset); }

extern "C" DllExport void CKLBUIList_cmdSetLimitClip(s32* pCtx,bool chklimit)
{ ((CKLBUIList*)pCtx)->cmdSetLimitClip(chklimit, NULL); }

extern "C" DllExport s32 CKLBUIList_cmdGetLimit(s32* pCtx)
{ return ((CKLBUIList*)pCtx)->cmdGetLimit(); }

extern "C" DllExport bool CKLBUIList_cmdSetLimitArea(s32* pCtx,s32 limitArea)
{ return ((CKLBUIList*)pCtx)->cmdSetLimitArea(limitArea); }

extern "C" DllExport void CKLBUIList_cmdChangeStep(s32* pCtx,s32 index, s32 step)
{ ((CKLBUIList*)pCtx)->cmdChangeStep(index, step); }

extern "C" DllExport void CKLBUIList_cmdInputEnable(s32* pCtx,bool enable)
{ ((CKLBUIList*)pCtx)->cmdInputEnable(enable); }

extern "C" DllExport bool CKLBUIList_cmdAnimationItem(s32* pCtx,s32 index, s32* name, bool blend)
{ return ((CKLBUIList*)pCtx)->cmdAnimationItem(index, (const char*)name, blend); }

extern "C" DllExport bool CKLBUIList_cmdAnimationAll(s32* pCtx, s32* name, bool blend)
{ return ((CKLBUIList*)pCtx)->cmdAnimationAll((const char*)name, blend); }

extern "C" DllExport bool CKLBUIList_cmdItemAnimSkip(s32* pCtx,s32 index, s32* name)
{ return ((CKLBUIList*)pCtx)->cmdItemAnimSkip(index, (const char*)name); }

extern "C" DllExport bool CKLBUIList_cmdAllAnimSkip(s32* pCtx, s32* name)
{ return ((CKLBUIList*)pCtx)->cmdAllAnimSkip((const char*)name); }

extern "C" DllExport void CKLBUIList_cmdSetGroup(s32* pCtx, s32* group_name)
{ ((CKLBUIList*)pCtx)->cmdSetGroup((const char*)group_name); }

extern "C" DllExport void CKLBUIList_cmdSetItemID(s32* pCtx, s32 index, u32 id)
{ ((CKLBUIList*)pCtx)->cmdSetItemID(index,id);	}

extern "C" DllExport void CKLBUIList_setLoop(s32* pCtx, bool mode)
{ ((CKLBUIList*)pCtx)->setLoop(mode);	}

extern "C" DllExport bool CKLBUIList_useScrollBar(s32* pCtx, u32 order, bool side, s32 lineWeight, s32* image, s32 min_slender_size, u32 colorNormal, u32 colorSelect, bool active, bool hideMode, bool shortHide)
{ return ((CKLBUIList*)pCtx)->useScrollBar(order,side,lineWeight,(const char*)image,min_slender_size,NULL,colorNormal,colorSelect,active,hideMode,shortHide); }

extern "C" DllExport void CKLBUIList_cmdFWModeConfig(s32* pCtx, int itemStep, int maxItems)
{ ((CKLBUIList*)pCtx)->cmdFWModeConfig(itemStep, maxItems);	}

extern "C" DllExport bool CKLBUIList_cmdSetItemMode(s32* pCtx, int itemMode)
{ return ((CKLBUIList*)pCtx)->cmdSetItemMode(itemMode, "");	}

extern "C" DllExport bool CKLBUIList_cmdAddRecords(s32* pCtx, s32 insIdx, s32* form, s32* db, s32 step)
{ 
	u32 sizeTemplate;
	u32 sizeDBRec;
	const char * tpform = CKLBUIList::toJSON((const char*)form, sizeTemplate);
	const char * dbrecs = CKLBUIList::toJSON((const char*)db, sizeDBRec);
	
	return ((CKLBUIList*)pCtx)->cmdAddRecords(insIdx, tpform, sizeTemplate, dbrecs, sizeDBRec, step);
}

extern "C" DllExport s32 CKLBUIList_cmdSetInitial(s32* pCtx, s32 pos)
{ return ((CKLBUIList*)pCtx)->cmdSetInitial(pos);	}

extern "C" DllExport bool CKLBUIList_cmdSelectScrMgr(s32* pCtx, s32* name, s32* optParams, u32 nb)
{ return ((CKLBUIList*)pCtx)->cmdSelectScrMgr((const char*)name, optParams, nb);	}

extern "C" DllExport void CKLBUIList_cmdSetClip(s32* pCtx, u32 orderBegin, u32 orderEnd, s16 clipX, s16 clipY, s16 clipWidth, s16 clipHeight)
{ return ((CKLBUIList*)pCtx)->cmdSetClip(orderBegin, orderEnd, clipX, clipY, clipWidth, clipHeight);	}

extern "C" DllExport s32 CKLBUIList_cmdItemAdd(s32* pCtx, s32* asset)
{ return ((CKLBUIList*)pCtx)->cmdItemAdd((const char*)asset);	}
extern "C" DllExport s32 CKLBUIList_cmdItemAdd2(s32* pCtx, s32* asset, s32 step, s32 id)
{ return ((CKLBUIList*)pCtx)->cmdItemAdd((const char*)asset, step, id);	}

extern "C" DllExport s32 CKLBUIList_cmdInsertItem(s32* pCtx, s32* asset, s32 index)
{ return ((CKLBUIList*)pCtx)->cmdItemInsert((const char*)asset, index);	}
extern "C" DllExport s32 CKLBUIList_cmdInsertItem2(s32* pCtx, s32* asset, s32 index, s32 step, s32 id)
{ return ((CKLBUIList*)pCtx)->cmdItemInsert((const char*)asset, index, step, id);	}

extern "C" DllExport s32 CKLBUIList_cmdRemoveSelection(s32* pCtx, s32* indexes, u32 nb)
{ return ((CKLBUIList*)pCtx)->cmdItemRemoveSelection(indexes, nb);		}

extern "C" DllExport void CKLBUIList_setDragRect(s32* pCtx, s32 left, s32 top, s32 right, s32 bottom)
{ return ((CKLBUIList*)pCtx)->setDragRect(left, top, right, bottom);	}

extern "C" DllExport bool CKLBUIList_cmdExistNode(s32* pCtx, s32 index, s32* name)
{ return ((CKLBUIList*)pCtx)->cmdExistNode(index, (const char*)name);	}

//======================================================================================
#include "CKLBUIForm.h"

extern "C" DllExport s32* CKLBUIForm_create(s32* pParent, u32 order, float x, float y, bool bAssetFile, s32* asset, bool bExclusive, bool modal, bool urgent)
{ return (s32*)CKLBUIForm::create((CKLBUITask*)pParent, NULL, order, x, y, bAssetFile, (const char*)asset, bExclusive, modal, urgent); }

extern "C" DllExport s32* CKLBUIForm_getAsset(s32* pCtx)
{ return (s32*)((CKLBUIForm*)pCtx)->getAsset(); }

extern "C" DllExport u32 CKLBUIForm_getOrder(s32* pCtx)
{ return ((CKLBUIForm*)pCtx)->getOrder(); }

extern "C" DllExport bool CKLBUIForm_getExclusive(s32* pCtx)
{ return ((CKLBUIForm*)pCtx)->getExclusive(); }	
extern "C" DllExport void CKLBUIForm_setExclusive(s32* pCtx, bool exclusive)
{ ((CKLBUIForm*)pCtx)->setExclusive(exclusive); }

extern "C" DllExport bool CKLBUIForm_getIsFile(s32* pCtx)
{ return ((CKLBUIForm*)pCtx)->getAssetFile(); }

extern "C" DllExport void CKLBUIForm_setEnable(s32* pCtx, bool isEnabled)
{ ((CKLBUIForm*)pCtx)->setEnable(isEnabled); }

extern "C" DllExport bool CKLBUIForm_existNode(s32* pCtx, s32* name)
{ return ((CKLBUIForm*)pCtx)->existNode((const char*)name);	}

extern "C" DllExport void CKLBUIForm_inputEnable(s32* pCtx, bool bEnable)
{ ((CKLBUIForm*)pCtx)->inputEnable(bEnable); }

extern "C" DllExport bool CKLBUIForm_animation(s32* pCtx, s32* animname, bool blend)
{ return ((CKLBUIForm*)pCtx)->animation((const char*)animname, blend); }

extern "C" DllExport bool CKLBUIForm_isAnim(s32* pCtx, s32* name)
{ return ((CKLBUIForm*)pCtx)->isAnim((const char*)name); }

extern "C" DllExport bool CKLBUIForm_skipAnim(s32* pCtx, s32* name)
{ return ((CKLBUIForm*)pCtx)->skipAnim((const char*)name); }

extern "C" DllExport bool CKLBUIForm_animEnter(s32* pCtx)
{ return ((CKLBUIForm*)pCtx)->animEnter();	}

extern "C" DllExport bool CKLBUIForm_animLeave(s32* pCtx)
{ return ((CKLBUIForm*)pCtx)->animLeave();	}

extern "C" DllExport bool CKLBUIForm_setGroup(s32* pCtx, s32* group_name)
{ return ((CKLBUIForm*)pCtx)->setGroup((const char*)group_name); }

extern "C" DllExport void CKLBUIForm_setGlobalVolume(s32* pCtx, float volume)
{ return ((CKLBUIForm*)pCtx)->setGlobalVolume(volume); }

//======================================================================================
#include "CKLBUIControl.h"

// "" is given instead of NULL because of the class specifications.
extern "C" DllExport s32* CKLBUIControl_create(s32* pParentTask)
{ return (s32*)CKLBUIControl::create((CKLBTask*)pParentTask, "", ""); }

extern "C" DllExport void CKLBUIControl_lock(s32* pCtx, bool lockMode)
{ ((CKLBUIControl*)pCtx)->lock(lockMode); }

extern "C" DllExport bool CKLBUIControl_setGroup(s32* pCtx, s32* groupName)
{ return ((CKLBUIControl*)pCtx)->setGroup((const char*)groupName); }

extern "C" DllExport void CKLBUIControl_setMask(s32* pCtx, u16 mask)
{ ((CKLBUIControl*)pCtx)->setMask(mask); }

//======================================================================================
#include "CKLBUITouchPad.h"

// "" is given instead of NULL because of the class specifications.
extern "C" DllExport s32* CKLBUITouchPad_create(s32* pParent, bool modal)
{ return (s32*)CKLBUITouchPad::create((CKLBTask*)pParent, "", modal); }

extern "C" DllExport bool CKLBUITouchPad_setGroup(s32* pCtx, s32* group_name)
{ return ((CKLBUITouchPad*)pCtx)->setGroup((const char*)group_name); }

extern "C" DllExport void CKLBUITouchPad_setLock(s32* pCtx, bool lock_mode)
{ ((CKLBUITouchPad*)pCtx)->lock(lock_mode); }

extern "C" DllExport void CKLBUITouchPad_setGetAll(s32* pCtx, bool b)
{ ((CKLBUITouchPad*)pCtx)->setGetAll(b); }

//======================================================================================
#include "CKLBUIClip.h"

extern "C" DllExport s32* CKLBUIClip_create(s32* pParent, u32 baseOrder, u32 maxOrder, float x, float y, float clipWidth, float clipHeight)
{ return (s32*)CKLBUIClip::create((CKLBUITask*)pParent, NULL, baseOrder, maxOrder, x, y, clipWidth, clipHeight); }

extern "C" DllExport u32 CKLBUIClip_getOrder(s32* pCtx)
{ return ((CKLBUIClip*)pCtx)->getOrder(); }
extern "C" DllExport void CKLBUIClip_setOrder(s32* pCtx, u32 order)
{ ((CKLBUIClip*)pCtx)->setOrder(order); }

extern "C" DllExport u32 CKLBUIClip_getMaxOdr(s32* pCtx)
{ return ((CKLBUIClip*)pCtx)->getMaxOdr(); }
extern "C" DllExport void CKLBUIClip_setMaxOdr(s32* pCtx, u32 maxodr)
{ ((CKLBUIClip*)pCtx)->setMaxOdr(maxodr); }

extern "C" DllExport float CKLBUIClip_getWidth(s32* pCtx)
{ return ((CKLBUIClip*)pCtx)->getWidth(); }
extern "C" DllExport void CKLBUIClip_setWidth(s32* pCtx, float width)
{ ((CKLBUIClip*)pCtx)->setWidth(width); }

extern "C" DllExport float CKLBUIClip_getHeight(s32* pCtx)
{ return ((CKLBUIClip*)pCtx)->getHeight(); }
extern "C" DllExport void CKLBUIClip_setHeight(s32* pCtx, float height)
{ ((CKLBUIClip*)pCtx)->setHeight(height); }

extern "C" DllExport void CKLBUIClip_setPosition(s32* pCtx, float x, float y)
{ ((CKLBUIClip*)pCtx)->setPosition(x,y); }

extern "C" DllExport void CKLBUIClip_setSize(s32* pCtx, float width, float height)
{ ((CKLBUIClip*)pCtx)->setSize(width, height); }

//======================================================================================
/*
#include "CKLBMapTask.h"

extern "C" DllExport s32* CKLBMapTask_create(s32* pParent, u32 allocSize, s32* asset)
{ return (s32*)CKLBMapTask::create((CKLBTask*)pParent, allocSize, (const char*)asset); }

extern "C" DllExport s32 CKLBMapTask_getX(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getX(); }

extern "C" DllExport s32 CKLBMapTask_getY(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getY(); }

extern "C" DllExport u32 CKLBMapTask_getOrder(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getOrder(); }

extern "C" DllExport u32 CKLBMapTask_getOffsetLayer(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getOffsetLayer(); }

extern "C" DllExport u32 CKLBMapTask_getOffsetPerLine(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getOffsetPerLine(); }

extern "C" DllExport u32 CKLBMapTask_getWidth(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getWidth(); }

extern "C" DllExport u32 CKLBMapTask_getHeight(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getHeight(); }

extern "C" DllExport s32 CKLBMapTask_getCoordX(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getCoordX(); }

extern "C" DllExport s32 CKLBMapTask_getCoordY(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getCoordY(); }

extern "C" DllExport u32 CKLBMapTask_getMode(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getMode(); }

extern "C" DllExport s32* CKLBMapTask_getAsset(s32* pCtx)
{ return (s32*)((CKLBMapTask*)pCtx)->getAsset(); }

extern "C" DllExport s32 CKLBMapTask_getCenterX(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getCenterX(); }

extern "C" DllExport s32 CKLBMapTask_getCenterY(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getCenterY(); }

extern "C" DllExport float CKLBMapTask_getScale(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getScale(); }

extern "C" DllExport s32 CKLBMapTask_getTileWidth(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getTileWidth(); }

extern "C" DllExport s32 CKLBMapTask_getHalfTileHeight(s32* pCtx)
{ return ((CKLBMapTask*)pCtx)->getHalfTileHeight(); }

extern "C" DllExport void CKLBMapTask_cmdMapSetViewPort(s32* pCtx, u32 width, u32 height, s32 x, s32 y, u32 baseRenderPriority, u32 priorityOffsetPerLayer, u32 priorityOffsetPerLine)
{ ((CKLBMapTask*)pCtx)->cmdMapSetViewPort(width, height, x, y, baseRenderPriority, priorityOffsetPerLayer, priorityOffsetPerLine); }

extern "C" DllExport void CKLBMapTask_cmdMapSetCoordinate(s32* pCtx, float x, float y, s32 mode)
{ ((CKLBMapTask*)pCtx)->cmdMapSetCoordinate(x, y, mode); }

extern "C" DllExport void CKLBMapTask_cmdMapSetCenterView(s32* pCtx, float fx, float fy)
{ ((CKLBMapTask*)pCtx)->cmdMapSetCenterView(fx, fy); }

extern "C" DllExport void CKLBMapTask_cmdMapSetDefaultTile(s32* pCtx, u32 layer, s32* asset, u32 argb)
{
	u32 alpha = argb >> 24;
	u32 color = argb & 0xFFFFFF;
	((CKLBMapTask*)pCtx)->cmdMapSetDefaultTile(layer, (const char*)asset, alpha, color);
}

extern "C" DllExport void CKLBMapTask_cmdMapSetZoom(s32* pCtx, float scale)
{ ((CKLBMapTask*)pCtx)->cmdMapSetZoom(scale); }

extern "C" DllExport void CKLBMapTask_getScrCoord(s32* pCtx, float fx, float fy, float* resX, float* resY)
{ ((CKLBMapTask*)pCtx)->cmdMapGetScrCoord(fx, fy, resX, resY); }

extern "C" DllExport void CKLBMapTask_getLogCoord(s32* pCtx, float fx, float fy, float* resX, float* resY)
{ ((CKLBMapTask*)pCtx)->cmdMapGetLogCoord(fx, fy, resX, resY); }

extern "C" DllExport void CKLBMapTask_cmdMapSetTileID(s32* pCtx, u32 layer, u32 tileX, u32 tileY, u32 tileID)
{ ((CKLBMapTask*)pCtx)->cmdMapSetTileID(layer, tileX, tileY, tileID); }

extern "C" DllExport void CKLBMapTask_cmdMapSetAreaID(s32* pCtx, u32 layer, u32 tileID, u32 x1, u32 y1, u32 x2, u32 y2)
{ ((CKLBMapTask*)pCtx)->cmdMapSetAreaID(layer, tileID, x1, y1, x2, y2); }

// Camera methods
extern "C" DllExport s32* CKLBMapTask_cameraCreate(s32* pCtx)
{ return (s32*)((CKLBMapTask*)pCtx)->cameraCreate(); }

extern "C" DllExport void CKLBMapTask_cameraDelete(s32* pCtx, s32* pLuaCam)
{ ((CKLBMapTask*)pCtx)->cameraDelete((CKLBMapTask::LUACAMERA*)pLuaCam); }

extern "C" DllExport void CKLBMapTask_cameraMove(s32* pCtx, s32* pLuaCam, s32 x, s32 y)
{ ((CKLBMapTask*)pCtx)->cameraMove((CKLBMapTask::LUACAMERA*)pLuaCam,x,y); }

extern "C" DllExport void CKLBMapTask_cameraMoveWithCoord(s32* pCtx, s32* pLuaCam, s32 x, s32 y, s32 mode)
{ ((CKLBMapTask*)pCtx)->cameraMove((CKLBMapTask::LUACAMERA*)pLuaCam,x,y,(CKLBMapNode::COORD_MODE)mode); }

extern "C" DllExport void CKLBMapTask_cameraSet(s32* pCtx, s32* pLuaCam)
{ ((CKLBMapTask*)pCtx)->cameraSet((CKLBMapTask::LUACAMERA*)pLuaCam); }
*/
//======================================================================================
#include "CKLBNetAPI.h"

extern "C" DllExport s32* CKLBNetAPI_create(s32* pParent, s32* apiurl, s32* client_version, s32* consumer_key, s32* application_id,
								u32 session_max, s32* region)
{ return (s32*)CKLBNetAPI::create((CKLBTask*)pParent, (const char*)apiurl, (const char*)client_version, (const char*)consumer_key, (const char*)application_id, NULL, session_max, (const char*)region, NULL); }

extern "C" DllExport bool CKLBNetAPI_startUp(s32* pCtx, s32* loginID, s32* password, s32* invite, u32 timeout, u32* session)
{ return ((CKLBNetAPI*)pCtx)->startUp((const char*)loginID, (const char*)password, (const char*)invite, timeout, session); }

extern "C" DllExport bool CKLBNetAPI_login(s32* pCtx, s32* loginID, s32* password, u32 timeout, u32* session)
{ return ((CKLBNetAPI*)pCtx)->login((const char*)loginID,(const char*)password,timeout,session); }

extern "C" DllExport bool CKLBNetAPI_cancel(s32* pCtx, u32 uniq)
{ return ((CKLBNetAPI*)pCtx)->cancel(uniq); }

extern "C" DllExport void CKLBNetAPI_cancelAll(s32* pCtx)
{ return ((CKLBNetAPI*)pCtx)->cancelAll(); }

extern "C" DllExport void CKLBNetAPI_debugHdr(s32* pCtx, bool debugflag)
{ return ((CKLBNetAPI*)pCtx)->debugHdr(debugflag); }

extern "C" DllExport bool CKLBNetAPI_sendHTTP(s32* pCtx, s32* apiURL, s32* json, u32 timeout, bool passVersionCheck, u32* session) 
{ return ((CKLBNetAPI*)pCtx)->sendHTTP((const char*)apiURL, (const char*)json, timeout, passVersionCheck, session); }

extern "C" DllExport bool CKLBNetAPI_watchMaintenance(s32* pCtx, u32 timeout, u32* session)
{ return ((CKLBNetAPI*)pCtx)->watchMaintenance(timeout, session); }

extern "C" DllExport void CKLBNetAPI_genCmdNumID(s32* pCtx, s32* body, int serial, s32* buf)
{ ((CKLBNetAPI*)pCtx)->genCmdNumID((const char*)body, serial, (char*)buf); }

//======================================================================================
/*
#include "CKLBMapGroup.h"

extern "C" DllExport s32* CKLBMapGroup_create(s32* pParent, u32 order, float x, float y, float z, bool scaleEnable)
{ return (s32*)CKLBMapGroup::create((CKLBUITask*)pParent, NULL, order, x, y, z, scaleEnable); }

extern "C" DllExport u32 CKLBMapGroup_getOrder(s32* pCtx)
{ return ((CKLBMapGroup*)pCtx)->getOrder(); }

extern "C" DllExport float CKLBMapGroup_getMapX(s32* pCtx)
{ return ((CKLBMapGroup*)pCtx)->getMapX(); }
extern "C" DllExport void CKLBMapGroup_setMapX(s32* pCtx, float x)
{ return ((CKLBMapGroup*)pCtx)->setMapX(x); }

extern "C" DllExport float CKLBMapGroup_getMapY(s32* pCtx)
{ return ((CKLBMapGroup*)pCtx)->getMapY(); }
extern "C" DllExport void CKLBMapGroup_setMapY(s32* pCtx, float y)
{ return ((CKLBMapGroup*)pCtx)->setMapY(y); }

extern "C" DllExport float CKLBMapGroup_getMapZ(s32* pCtx)
{ return ((CKLBMapGroup*)pCtx)->getMapZ(); }
extern "C" DllExport void CKLBMapGroup_setMapZ(s32* pCtx, float z)
{ return ((CKLBMapGroup*)pCtx)->setMapZ(z); }

extern "C" DllExport void CKLBMapGroup_setPosition(s32* pCtx, float x, float y, float z)
{ ((CKLBMapGroup*)pCtx)->setPosition(x,y,z); }
*/
//======================================================================================
/*
#include "CKLBUnitTask.h"

extern "C" DllExport s32* CKLBUnitTask_create(s32* pParent, s32* unitname, bool bMove)
{ return (s32*)CKLBUnitTask::create((CKLBUITask*)pParent,(const char*)unitname,bMove); }

extern "C" DllExport void CKLBUnitTask_getPosition(s32* pCtx, s32* x, s32* y, s32* z, u32* dir)
{ ((CKLBUnitTask*)pCtx)->getPosition(x,y,z,dir); }

extern "C" DllExport s32* CKLBUnitTask_getClass(s32* pCtx)
{ return (s32*)((CKLBUnitTask*)pCtx)->getClass(); }

extern "C" DllExport u32 CKLBUnitTask_getType(s32* pCtx)
{ return ((CKLBUnitTask*)pCtx)->getType(); }
extern "C" DllExport void CKLBUnitTask_setType(s32* pCtx, u32 type)
{ ((CKLBUnitTask*)pCtx)->setType(type); }

extern "C" DllExport u64 CKLBUnitTask_getDbId(s32* pCtx)
{ return ((CKLBUnitTask*)pCtx)->getDbId(); }

extern "C" DllExport u32 CKLBUnitTask_getOrder(s32* pCtx)
{ return ((CKLBUnitTask*)pCtx)->getOrder(); }

extern "C" DllExport bool CKLBUnitTask_getVisible(s32* pCtx)
{ return ((CKLBUnitTask*)pCtx)->getVisible(); }
extern "C" DllExport void CKLBUnitTask_setVisible(s32* pCtx, bool visible)
{ ((CKLBUnitTask*)pCtx)->setVisible(visible); }

extern "C" DllExport void CKLBUnitTask_cmdSetLogicalPosition(s32* pCtx, float x, float y, float z, u32 dir, s32* optJSON)
{ ((CKLBUnitTask*)pCtx)->cmdSetLogicalPosition(x,y,z,dir,(const char*)optJSON); }

extern "C" DllExport void CKLBUnitTask_cmdRealize(s32* pCtx, s32* optJSON) 
{ ((CKLBUnitTask*)pCtx)->cmdRealize((const char*)optJSON); }

extern "C" DllExport s32* CKLBUnitTask_cmdExecuteQuery(s32* pCtx, s32*  pQuery , float* pDistance)
{ return (s32*)((CKLBUnitTask*)pCtx)->cmdExecuteQuery((CKLBUnitQuery*)pQuery, *pDistance); }

extern "C" DllExport	bool CKLBUnitTask_assignAI(s32* pCtx, u32 aiDefinition)
{ return false; // TODO after merging : ((CKLBUnitTask*)pCtx)->unitAssignAI(aiDefinition);
}

extern "C" DllExport s32* CKLBUnitTask_getAIObject(s32* pCtx)
{ return (s32*)((CKLBUnitTask*)pCtx)->getAIobject(); }
*/
//======================================================================================
#include "CKLBUIVariableItem.h"

extern "C" DllExport s32* CKLBUIVariableItem_create(s32* pParent, u32 order, float x, float y, float width, float height, s32* asset)
{ return (s32*)CKLBUIVariableItem::create((CKLBUITask*)pParent, NULL, order, x, y, width, height, (const char*)asset); }

extern "C" DllExport u32 CKLBUIVariableItem_getOrder(s32* pCtx)
{ return ((CKLBUIVariableItem*)pCtx)->getOrder(); }
extern "C" DllExport void CKLBUIVariableItem_setOrder(s32* pCtx, u32 order)
{ ((CKLBUIVariableItem*)pCtx)->setOrder(order); }

extern "C" DllExport s32* CKLBUIVariableItem_getAsset(s32* pCtx)
{ return (s32*)((CKLBUIVariableItem*)pCtx)->getAsset(); }

extern "C" DllExport float CKLBUIVariableItem_getWidth(s32* pCtx)
{ return ((CKLBUIVariableItem*)pCtx)->getWidth(); }
extern "C" DllExport void CKLBUIVariableItem_setWidth(s32* pCtx, float width)
{ ((CKLBUIVariableItem*)pCtx)->setWidth(width); }

extern "C" DllExport float CKLBUIVariableItem_getHeight(s32* pCtx)
{ return ((CKLBUIVariableItem*)pCtx)->getHeight(); }
extern "C" DllExport void CKLBUIVariableItem_setHeight(s32* pCtx, float height)
{ ((CKLBUIVariableItem*)pCtx)->setHeight(height); }

extern "C" DllExport bool CKLBUIVariableItem_changeAsset(s32* pCtx, s32* assetName)
{ return ((CKLBUIVariableItem*)pCtx)->changeAsset((const char*)assetName); }

extern "C" DllExport void CKLBUIVariableItem_changeUV(s32* pCtx, float x, float y, float width, float height)
{ ((CKLBUIVariableItem*)pCtx)->changeUV(x, y, width, height); }

/*
extern "C" DllExport void CKLBUIVariableItem_resetUV(s32* pCtx)
{ ((CKLBUIVariableItem*)pCtx)->resetUV(); }
*/

extern "C" DllExport bool CKLBUIVariableItem_setMaskAsset(s32* pCtx, s32* asset)
{ return ((CKLBUIVariableItem*)pCtx)->setMaskAsset((const char*)asset); }

//======================================================================================
#include "CKLBStoreService.h"

extern "C" DllExport s32* CKLBStoreService_create()
{ return (s32*)CKLBStoreService::create(NULL); }

extern "C" DllExport void CKLBStoreService_buyItems(s32* pCtx, s32* item)
{ ((CKLBStoreService*)pCtx)->buyItems((const char*)item); }

extern "C" DllExport void CKLBStoreService_getProducts(s32* pCtx, s32* json, bool currency)
{ ((CKLBStoreService*)pCtx)->getProducts((const char*)json, currency); }

//======================================================================================
/*
#include "CKLBWorld.h"

class CSharpWorldCallback : public IWorldRequestCallback
{
public:
	CSharpWorldCallback()  {}
	~CSharpWorldCallback() {}
	void callbackWorld(int serial, int msg, int status, void * data = 0) {
		const char * funcname = (const char *)data;
		CKLBScriptEnv::getInstance().call_eventWorld(funcname, NULL, serial, msg, status);
	}
};

static CSharpWorldCallback s_worldCallback;

extern "C" DllExport s32* CKLBWorld_getPointUnit(s32 x, s32 y) { 
	return (s32*)CKLBWorld::getInstance().pointUnit(x, y);
}

extern "C" DllExport s32* CKLBWorld_getUnitByID(s32* dbID) { 
	return (s32*)CKLBWorld::getInstance().searchUnitByID(CKLBUtility::stringNum64((const char*)dbID));
}

extern "C" DllExport bool CKLBWorld_doEvent(s32* pSrcTask, s32* pDstTask, s32* pUserTask, s32* pOppoTask, u32 eventID, s32* additionalParams, u32 additionalParamsCount) { 
	CKLBUnitInstanceBase * pSrc		= (pSrcTask)  ? ((CKLBUnitTask*)pSrcTask)->getUnitInstance()  : NULL;
	CKLBUnitInstanceBase * pDst		= (pDstTask)  ? ((CKLBUnitTask*)pDstTask)->getUnitInstance()  : NULL;
	CKLBUnitInstanceBase * pUser	= (pUserTask) ? ((CKLBUnitTask*)pUserTask)->getUnitInstance() : NULL;
	CKLBUnitInstanceBase * pOppo	= (pOppoTask) ? ((CKLBUnitTask*)pOppoTask)->getUnitInstance() : NULL;

	bool bResult = true;
	bResult = bResult && (!pSrc  || (pSrc->getClassID()  == CLS_GAMEUNIT));
	bResult = bResult && (!pDst  || (pDst->getClassID()  == CLS_GAMEUNIT));
	bResult = bResult && (!pUser || (pUser->getClassID() == CLS_GAMEUNIT));
	bResult = bResult && (!pOppo || (pOppo->getClassID() == CLS_GAMEUNIT));
	
	if(!bResult) {
		return false;
	}
	
	CKLBUnitInstance::doEvent(	(CKLBUnitInstance *)pSrc,
								(CKLBUnitInstance *)pDst,
								(CKLBUnitInstance *)pUser,
								(CKLBUnitInstance *)pOppo,
								eventID, additionalParamsCount, additionalParams);
	
	return true;
}

extern "C" DllExport void CKLBWorld_killAllUnit() { 
	CKLBWorld::getInstance().killAllUnit();
}

extern "C" DllExport u32 CKLBWorld_getUnitListByClass(s32* unitClass, s32** pIds, s32** pTasks, u32 maxLength) { 
	CKLBWorld& world = CKLBWorld::getInstance();
	CKLBUnitTask* pTask = world.getFirstUnit();
	
	u32 idx = 0;
	while(pTask && idx < maxLength) {
		CKLBUnitInstanceBase * base = pTask->getUnitInstance();
		if((base->getClassID() != CLS_GAMEUNIT) && (base->getClassID() != CLS_GAMEUNITBASE)) {
			pTask = world.getNextUnit(pTask);
			continue;
		}

		const char * unitType = base->getDefinition()->m_name;
		if(strcmp(unitType, (const char*)unitClass) != 0) {
			pTask = world.getNextUnit(pTask);
			continue;
		}

		u64 dbID = 0;
		if(base->getClassID() == CLS_GAMEUNIT) {
			CKLBUnitInstance * pInstance = (CKLBUnitInstance *)base;
			dbID = pInstance->m_dbID;
		}

		idx++;

		char buf[256];
		CKLBUtility::numString64(buf, dbID);
		((const char**)pIds)[idx] 	= buf;
		((CKLBUnitTask**)pTasks)[idx] 	= pTask;

		pTask = world.getNextUnit(pTask);
	}
	
	return idx;
}

extern "C" DllExport s32 CKLBWorld_getUnitAll(s32* targetUser, s32*  battleId, s32 callbackIndex) { 
	return CKLBWorld::getInstance().sincGetAll((void *)callbackIndex, &s_worldCallback, (const char*)targetUser, (const char*)battleId);
}

extern "C" DllExport s32 CKLBWorld_getUnitClass(s32* unitClass, s32* strId, s32* targetUser, s32 callbackIndex) {
	u64 dbID = CKLBUtility::stringNum64((const char*)strId);
	return CKLBWorld::getInstance().sincGetClass((const char*)unitClass, dbID, (s32* )callbackIndex, &s_worldCallback, (const char*)targetUser);
}

extern "C" DllExport s32 CKLBWorld_getUnitTableAll(s32* unitTable, s32 callbackIndex) { 
	return CKLBWorld::getInstance().sincGetTableAll((const char*)unitTable, (s32* )callbackIndex, &s_worldCallback);
}

extern "C" DllExport void CKLBWorld_setOrderParam(u32 baseOrder, float orderReso) { 
	CKLBWorld::getInstance().setNoMapParameter(baseOrder, orderReso);
}

extern "C" DllExport void CKLBWorld_unitFreeze(bool bFreeze) { 
	CKLBWorld::getInstance().setFreeze(bFreeze);
}
*/
//======================================================================================
#include "CKLBAsyncLoader.h"

extern "C" DllExport s32* CKLBAsyncLoader_create(s32* pParentTask, s32** assets, u32 count, u32 datasetID)
{ return (s32*)CKLBAsyncLoader::create((CKLBTask*)pParentTask, (const char**)assets, count, datasetID, ""); }

extern "C" DllExport u32 CKLBAsyncLoader_getTotalCount(s32* pCtx)
{ return ((CKLBAsyncLoader*)pCtx)->getTotalCount(); }

extern "C" DllExport u32 CKLBAsyncLoader_getProcessCount(s32* pCtx)
{ return ((CKLBAsyncLoader*)pCtx)->getProcessCount(); }

//======================================================================================
//======================================================================================
//======================================================================================
//======================================================================================
//======================================================================================
//======================================================================================
#include "CKLBLuaLibKEY.h"

extern "C" DllExport int CKLBLuaLibKEY_genUserID(s32* buf, u32 size)
{ return CKLBLuaLibKEY::genUserID((char*)buf,size); }

extern "C" DllExport int CKLBLuaLibKEY_genUserPW(s32* user_id, s32* buf, u32 size)
{ return CKLBLuaLibKEY::genUserPW((const char*)user_id, (char*)buf,size); }

extern "C" DllExport bool CKLBLuaLibKEY_setSecureID(s32* service_name, s32* user_id)
{ return CKLBLuaLibKEY::setSecureID((const char*)service_name, (const char*)user_id); }

extern "C" DllExport bool CKLBLuaLibKEY_setSecurePW(s32* service_name, s32* passwd)
{ return CKLBLuaLibKEY::setSecurePW((const char*)service_name, (const char*)passwd); }

extern "C" DllExport int CKLBLuaLibKEY_getSecureID(s32* service_name, s32* buf, u32 size)
{ return CKLBLuaLibKEY::getSecureID((const char*)service_name, (char*)buf, size); }

extern "C" DllExport int CKLBLuaLibKEY_getSecurePW(s32* service_name, s32* buf, u32 size)
{ return CKLBLuaLibKEY::getSecurePW((const char*)service_name, (char*)buf, size); }

extern "C" DllExport bool CKLBLuaLibKEY_delSecureID(s32* service_name)
{ return CKLBLuaLibKEY::delSecureID((const char*)service_name); }

extern "C" DllExport bool CKLBLuaLibKEY_delSecurePW(s32* service_name)
{ return CKLBLuaLibKEY::delSecurePW((const char*)service_name); }

//======================================================================================
#include "CKLBLuaLibRES.h"

extern "C" DllExport void CKLBLuaLibRES_dumpSceneGraph(s32*  ptr)
{ CKLBLuaLibRES::dumpSceneGraph(ptr); }

extern "C" DllExport void CKLBLuaLibRES_dumpRendering(bool detailed)
{ CKLBLuaLibRES::dumpRendering(detailed); }

extern "C" DllExport void CKLBLuaLibRES_dumpAssets()
{ CKLBLuaLibRES::dumpAssets(); }

extern "C" DllExport void CKLBLuaLibRES_dumpDataSet()
{ CKLBLuaLibRES::dumpDataSet(); }

extern "C" DllExport void CKLBLuaLibRES_dumpTexturePacker(bool detailed)
{ CKLBLuaLibRES::dumpTexturePacker(detailed); }

extern "C" DllExport void CKLBLuaLibRES_dumpGeometryCost(bool detailed)
{ CKLBLuaLibRES::dumpGeometryCost(detailed); }

//======================================================================================
#include "CKLBLuaLibENG.h"

extern "C" DllExport bool CKLBLuaLibENG_isRelease()
{ return CKLBLuaLibENG::isRelease(); }

extern "C" DllExport s32* CKLBLuaLibENG_getPlatform()
{ return (s32*)CKLBLuaLibENG::getPlatform(); }

extern "C" DllExport void CKLBLuaLibENG_getNanoTime(s32* milli, s32* nano)
{ CKLBLuaLibENG::getNanoTime(milli, nano); }

extern "C" DllExport void CKLBLuaLibENG_startNanoTime(u32 idx)
{ CKLBLuaLibENG::startNanoTime(idx); }

extern "C" DllExport void CKLBLuaLibENG_endNanoTime(u32 idx, s32* milli, s32* nano)
{ CKLBLuaLibENG::endNanoTime(idx, milli, nano); }

extern "C" DllExport u32 CKLBLuaLibENG_getFrameID()
{ return CKLBLuaLibENG::getFrameID(); }


//======================================================================================
#include "CKLBLuaEnv.h"

extern "C" DllExport void CKLBLuaEnv_cmdLogging(s32* msg)
{ CKLBLuaEnv::cmdLogging((const char*)msg); }

extern "C" DllExport void CKLBLuaEnv_cmdExit()
{ CKLBLuaEnv::cmdExit(); }

extern "C" DllExport void CKLBLuaEnv_cmdSystemInfo(s32* width, s32* height)
{ CKLBLuaEnv::cmdSystemInfo(width, height); }

extern "C" DllExport void CKLBLuaEnv_cmdSystemReboot()
{ CPFInterface::getInstance().client().reboot(); }

//======================================================================================
#include "CKLBLuaLibFONT.h"

extern "C" DllExport s32* CKLBLuaLibFONT_createFont(s32 size, s32* fontname)
{ return (s32*)CKLBLuaLibFONT::create_font(size, (const char*)fontname); }

extern "C" DllExport void CKLBLuaLibFONT_removeFont(s32* fontobj)
{ CKLBLuaLibFONT::remove_font((CKLBLuaLibFONT::FONTOBJ *)fontobj); }

extern "C" DllExport void CKLBLuaLibFONT_cmdGetTextInfo(s32* str, s32*  font, s32* pReturnInfo)
{ CKLBLuaLibFONT::cmdGetTextInfo((const char*)str, font, (STextInfo*)pReturnInfo); }


//======================================================================================
#include "CKLBLuaLibASSET.h"

extern "C" DllExport void CKLBLuaLibASSET_getImageSize(s32* asset_name, s32* pReturnWidth, s32* pReturnHeight)
{ CKLBLuaLibASSET::cmdGetImageSize((const char*)asset_name, pReturnWidth, pReturnHeight); }

extern "C" DllExport void CKLBLuaLibASSET_getBoundSize(s32* asset_name, float* pReturnWidth, float* pReturnHeight)
{ CKLBLuaLibASSET::cmdGetBoundSize((const char*)asset_name, pReturnWidth, pReturnHeight); }

extern "C" DllExport void CKLBLuaLibASSET_getAssetInfo(s32* asset_name, s32* pReturnImgWidth, s32* pReturnImgHeight, float* pReturnBoundWidth, float* pReturnBoundHeight)
{ CKLBLuaLibASSET::cmdGetAssetInfo((const char*)asset_name, pReturnImgWidth, pReturnImgHeight, pReturnBoundWidth, pReturnBoundHeight); }

//======================================================================================
#include "CKLBLuaLibDATA.h"

extern "C" DllExport s32* CKLBLuaLibDATA_cmdCreateData(u32 dataSetID)
{ return (s32*)CKLBLuaLibDATA::cmdCreateData(dataSetID); }

extern "C" DllExport bool CKLBLuaLibDATA_cmdRegistData(s32* pDataSet, s32* name_asset, u32* pReturnHandle)
{ return CKLBLuaLibDATA::cmdRegistData((CKLBDataSet*)pDataSet, (const char*)name_asset, NULL, (u32*)pReturnHandle); }

extern "C" DllExport void CKLBLuaLibDATA_cmdDelete(s32* pDataSet)
{ CKLBLuaLibDATA::cmdDelete((CKLBDataSet*)pDataSet); }

//======================================================================================
#include "CKLBLuaLibGL.h"

extern "C" DllExport bool CKLBLuaLibGL_GLClearColor(float r, float g, float b, float a)
{ return CKLBLuaLibGL::GLClearColor(r,g,b,a); }

extern "C" DllExport void CKLBLuaLibGL_GLSetResolution(int width, int height)
{ return CKLBLuaLibGL::GLSetResolution(width, height); }

extern "C" DllExport void CKLBLuaLibGL_SGGetGuardBand(float* leftBorder, float* rightBorder, float* topBorder, float* bottomBorder)
{ return CKLBLuaLibGL::SGGetGuardBand(leftBorder, rightBorder, topBorder, bottomBorder); }

extern "C" DllExport void CKLBLuaLibGL_SGSetGuardBand(float leftBorder, float rightBorder, float topBorder, float bottomBorder)
{ return CKLBLuaLibGL::SGSetGuardBand(leftBorder, rightBorder, topBorder, bottomBorder); }

extern "C" DllExport bool CKLBLuaLibGL_GLCreateScreenAsset(s32* name) 
{ return CKLBLuaLibGL::GLCreateScreenAsset((const char*)name); }

extern "C" DllExport bool CKLBLuaLibGL_GLDoScreenShot(s32* name) 
{ return CKLBLuaLibGL::GLDoScreenShot((const char*)name); }

extern "C" DllExport void CKLBLuaLibGL_GLFreeScreenAsset(s32* name) 
{ CKLBLuaLibGL::GLFreeScreenAsset((const char*)name); }

//======================================================================================
#include "CKLBLuaLibUI.h"

extern "C" DllExport void CKLBLuaLibUI_calcPosition(float x, float y, float w, float h, u32 mask, float* out_rx, float* out_ry)
{ CKLBLuaLibUI::calcPosition(x,y,w,h,mask,out_rx,out_ry); }

//======================================================================================
#include "CKLBLuaLibBIN.h"

extern "C" DllExport s32* CKLBLuaLibBIN_open(s32* bin_asset)
{ return (s32*)CKLBLuaLibBIN::bin_open((const char*)bin_asset); }
extern "C" DllExport void CKLBLuaLibBIN_close(s32* pBIN)
{ CKLBLuaLibBIN::bin_close((CKLBBinArray*)pBIN); }

extern "C" DllExport bool CKLBLuaLibBIN_peek(s32* pBIN, s32 offset, s32* out_value)
{ return CKLBLuaLibBIN::bin_peek((CKLBBinArray*)pBIN,offset,out_value); }
extern "C" DllExport bool CKLBLuaLibBIN_peek_u16(s32* pBIN, s32 offset, u32* out_value, bool f_bigendian)
{ return CKLBLuaLibBIN::bin_peek_u16((CKLBBinArray*)pBIN,offset,out_value,f_bigendian); }
extern "C" DllExport bool CKLBLuaLibBIN_peek_u32(s32* pBIN, s32 offset, u32* out_value, bool f_bigendian)
{ return CKLBLuaLibBIN::bin_peek_u32((CKLBBinArray*)pBIN,offset,out_value,f_bigendian); }

//======================================================================================
#include "CKLBLuaLibTASK.h"
#include "CKLBTask.h"

extern "C" DllExport void Task_kill(s32* pTask)
{ ((CKLBLuaTask*)pTask)->kill(); }

extern "C" DllExport bool Task_isKill(s32* pTask)
{ return CKLBTaskMgr::getInstance().is_remove((CKLBLuaTask*)pTask); }

extern "C" DllExport void Task_setStageTask(s32* pTask)
{ CKLBTaskMgr::getInstance().registStageTask((CKLBLuaTask*)pTask); }

extern "C" DllExport void Task_clearStageTask()
{ CKLBTaskMgr::getInstance().clearStageTask(); }

extern "C" DllExport void Task_setPause(s32* pTask, bool bPause, bool bRecursive)
{ ((CKLBLuaTask*)pTask)->setPause(bPause, bRecursive); }

extern "C" DllExport void Task_setManagerPause(bool bPause) {	
	CKLBTaskMgr& mgr = CKLBTaskMgr::getInstance();
	mgr.setPause(bPause); 
}

extern "C" DllExport void Task_interposeTimer(s32* pTask, s32* pTimer) {
	((CKLBLuaTask*)pTask)->interposeTimer((CKLBTask*)pTimer);
}

//======================================================================================
#include "CKLBLuaLibSOUND.h"

extern "C" DllExport s32* CKLBLuaLibSOUND_cmdSoundOpen(s32* snd_asset, bool f_bgm)
{ return (s32*)CKLBLuaLibSOUND::cmdSoundOpen((const char*)snd_asset, f_bgm); }

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundClose(s32* pSnd)
{ CKLBLuaLibSOUND::removeSound((CKLBLuaLibSOUND::SOUND*)pSnd); }

extern "C" DllExport u32 CKLBLuaLibSOUND_removeSoundAll()
{ return CKLBLuaLibSOUND::removeSoundAll(); }

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundPlay(s32* pSnd, u32 fade_msec, float tgtVol, float globalVol)
{ CKLBLuaLibSOUND::cmdSoundPlay((CKLBLuaLibSOUND::SOUND*)pSnd, fade_msec, tgtVol, globalVol); }

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundStop(s32* pSnd, u32 fade_msec, float tgtVol)
{ CKLBLuaLibSOUND::cmdSoundStop((CKLBLuaLibSOUND::SOUND*)pSnd, fade_msec, tgtVol); }

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundVolume(s32* pSnd, float volume)
{ CKLBLuaLibSOUND::cmdSoundVolume((CKLBLuaLibSOUND::SOUND*)pSnd, volume); }

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundPan(s32* pSnd, float pan)
{ CKLBLuaLibSOUND::cmdSoundPan((CKLBLuaLibSOUND::SOUND*)pSnd, pan); }

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundPause(s32* pSnd)
{ CKLBLuaLibSOUND::cmdSoundPause((CKLBLuaLibSOUND::SOUND*)pSnd); }

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundResume(s32* pSnd)
{ CKLBLuaLibSOUND::cmdSoundResume((CKLBLuaLibSOUND::SOUND*)pSnd); }

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundSeek(s32* pSnd, s32 millisec)
{ CKLBLuaLibSOUND::cmdSoundSeek((CKLBLuaLibSOUND::SOUND*)pSnd, millisec); }

extern "C" DllExport s32  CKLBLuaLibSOUND_cmdSoundTell(s32* pSnd)
{ return CKLBLuaLibSOUND::cmdSoundTell((CKLBLuaLibSOUND::SOUND*)pSnd); }

extern "C" DllExport s32  CKLBLuaLibSOUND_cmdSoundState(s32* pSnd)
{ return CKLBLuaLibSOUND::cmdSoundState((CKLBLuaLibSOUND::SOUND*)pSnd); }

extern "C" DllExport void CKLBLuaLibSOUND_cmdVolumeBGM(float volume)
{ CKLBLuaLibSOUND::cmdVolumeBGM(volume); }

extern "C" DllExport void CKLBLuaLibSOUND_cmdVolumeSE(float volume)
{ CKLBLuaLibSOUND::cmdVolumeSE(volume); }

extern "C" DllExport s32 CKLBLuaLibSOUND_cmdGetLength(s32* pSnd)
{ return CKLBLuaLibSOUND::cmdGetLength((CKLBLuaLibSOUND::SOUND*)pSnd); }

extern "C" DllExport void CKLBLuaLibSOUND_cmdSetFade(s32* pSnd, s32 millisec, float tgtVol)
{ CKLBLuaLibSOUND::cmdSetFade((CKLBLuaLibSOUND::SOUND*)pSnd, millisec, tgtVol); }

extern "C" DllExport bool CKLBLuaLibSOUND_cmdSoundSetBufSize(s32* pSnd, s32 value)
{ return CKLBLuaLibSOUND::cmdSoundSetBufSize((CKLBLuaLibSOUND::SOUND*)pSnd, value); }

//======================================================================================
#include "CKLBLuaLibDB.h"

extern "C" DllExport s32* CKLBLuaLibDB_dbopen(s32* db_asset, bool b_write, bool b_create)
{ return (s32*)CKLBLuaLibDB::dbopen((const char*)db_asset,b_write,b_create); }

extern "C" DllExport void CKLBLuaLibDB_dbclose(s32* pDB)
{ CKLBLuaLibDB::dbclose((CKLBLuaDB*)pDB); }

extern "C" DllExport void CKLBLuaLibDB_closeAll()
{ CKLBLuaDB::closeAll(); }

extern "C" DllExport s32* CKLBLuaLibDB_query(s32* pDB, s32* sqlQuery, int* nbEntries)
{
	const char** strArray = ((CKLBLuaDB*)pDB)->query((const char*)sqlQuery);
	if(!strArray) { return NULL; }
	*nbEntries = (int)strArray[0];
	return (s32*)(++strArray);
}

//======================================================================================
/*
#include "CKLBLuaLibAI.h"

extern "C" DllExport void CKLBLuaLibAI_setActive(s32*  pAIobj, bool active)
{ CKLBLuaLibAI::setActive(pAIobj,active); }

extern "C" DllExport void CKLBLuaLibAI_resetRule(s32*  pAIobj)
{ CKLBLuaLibAI::resetRule(pAIobj); }

extern "C" DllExport s32 CKLBLuaLibAI_getProp(s32*  pAIobj, u32 index)
{ return CKLBLuaLibAI::getAIprop(pAIobj,index); }
extern "C" DllExport void CKLBLuaLibAI_setProp(s32*  pAIobj, u32 index, s32 value)
{ CKLBLuaLibAI::setAIprop(pAIobj,index,value); }

extern "C" DllExport void CKLBLuaLibAI_delQuery(s32* pQuery)
{ CKLBLuaLibAI::delExpression((CKLBUnitQuery*)pQuery); }
extern "C" DllExport void CKLBLuaLibAI_delQueryAll()
{ CKLBUnitQuery::removeAll(); }
*/
//======================================================================================
#include "CKLBLuaLibAPP.h"

extern "C" DllExport bool CKLBLuaLibAPP_callApplication(s32 type, s32* addr, s32* subject, s32* body)
{ return CKLBLuaLibAPP::callApplication((IPlatformRequest::APP_TYPE)type,(const char*)addr,(const char*)subject,(const char*)body); }

//======================================================================================
#include "CKLBPauseCtrl.h"

extern "C" DllExport s32* CKLBPauseCtrl_create(s32* pParent)
{ return (s32*)CKLBPauseCtrl::create((CKLBTask*)pParent,NULL,NULL); }

//======================================================================================
#include "CKLBLuaLibLANG.h"

extern "C" DllExport bool CKLBLuaLibLANG_addString(s32* id, s32* str)
{ return CKLBLuaLibLANG::addString((const char*)id, (const char*)str); }

extern "C" DllExport s32* CKLBLuaLibLANG_getString(s32* id)
{ return (s32*)CKLBLuaLibLANG::getString((const char*)id); }

extern "C" DllExport void CKLBLuaLibLANG_removeString(s32* id)
{ return CKLBLuaLibLANG::removeString((const char*)id); }

extern "C" DllExport bool CKLBLuaLibLANG_useDB(s32* dbFile, s32* table, s32* keyF, s32* valueF, s32* groupF)
{ return CKLBLuaLibLANG::useDB((const char*)dbFile, (const char*)table, (const char*)keyF, (const char*)valueF, (const char*)groupF); }

extern "C" DllExport bool CKLBLuaLibLANG_loadGroup(s32* groupId)
{ return CKLBLuaLibLANG::loadGroup((const char*)groupId); }


//======================================================================================
#include "CKLBLuaLibDEBUG.h"

extern "C" DllExport void CKLBLuaLibDEBUG_startMenu(u32 maxCount, s32* caption, s32* key) { 
	CKLBLuaLibDEBUG::startMenu(maxCount, (const char*)caption, (const char*)key);
}

extern "C" DllExport void CKLBLuaLibDEBUG_addItem(u32 mode, s32* caption, s32* key, s32 min, s32 max, s32 value, s32** items, u32 itemsCount) {
	CKLBLuaLibDEBUG::addItem(mode, (const char*)caption, (const char*)key, min, max, value, (const char**)items, itemsCount);
}

extern "C" DllExport void CKLBLuaLibDEBUG_endMenu() {
	CKLBLuaLibDEBUG::endMenu();
}

extern "C" DllExport void CKLBLuaLibDEBUG_removeMenu(s32* key) { 
	CKLBLuaLibDEBUG::removeMenu((const char*)key);
}

/*
//======================================================================================
#include ".h"

//======================================================================================
#include ".h"

//======================================================================================
#include ".h"

//======================================================================================
#include ".h"

//======================================================================================
#include ".h"

//======================================================================================
#include ".h"
*/
