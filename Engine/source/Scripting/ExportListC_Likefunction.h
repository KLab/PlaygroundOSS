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
#ifndef __EXPORT_LIST_H__
#define __EXPORT_LIST_H__

#ifndef DllExport
#define DllExport   __declspec( dllexport )
#endif

#include "BaseType.h"

//======================================================================================
//#include "CKLBScriptEnv.h"

extern "C" DllExport s32* CKLBScriptEnv_getCallBackCount(); 
extern "C" DllExport s32* CKLBScriptEnv_getErrorPtr();
extern "C" DllExport s32* CKLBScriptEnv_getErrorString();
extern "C" DllExport void CKLBScriptEnv_resetError();
//======================================================================================
//#include "CKLBObject.h"
//#include "CKLBLuaTask.h"
//#include "CKLBLibRegistrator.h"


extern "C" DllExport u32 CKLBObject_getTypeID(s32* pCtx);
extern "C" DllExport void CKLBObjectScriptable_setScriptContext(s32* pCtx, u32 handle);
extern "C" DllExport u32 CKLBObjectScriptable_getScriptContext(s32* pCtx);
extern "C" DllExport u32 Cpp_getClassIDByName(s32* name);
//======================================================================================
//#include "CKLBNode.h"
//#include "CKLBUITask.h"
//#include "CKLBDrawTask.h"
//#include "AudioAsset.h"

extern "C" DllExport s32* node_getRoot();
extern "C" DllExport s32* node_getChild(s32* pNode);
extern "C" DllExport s32* node_getParent(s32* pNode);
extern "C" DllExport s32* node_getBrother(s32* pNode);
extern "C" DllExport s32* node_getNodeFromTask(s32* pTask);
extern "C" DllExport float node_getNodeScaleX(s32* pNode);
extern "C" DllExport float node_getNodeScaleY(s32* pNode);
extern "C" DllExport float node_getRotation(s32* pNode);
extern "C" DllExport float node_getNodeTranslateX(s32* pNode);
extern "C" DllExport float node_getNodeTranslateY(s32* pNode);
extern "C" DllExport void node_setTranslate(s32* pNode, float x, float y);
extern "C" DllExport void node_setRotation(s32* pNode, float deg);

extern "C" DllExport void node_setScale(s32* pNode, float scaleX, float scaleY);

extern "C" DllExport void node_getColorMatrixVec(s32* pNode, float* dst);
extern "C" DllExport void node_setColorMatrixVec(s32* pNode, float* src);
extern "C" DllExport u32 node_getColorMatrixUInt(s32* pNode);
extern "C" DllExport void node_setColorMatrixUInt(s32* pNode, u32 val);
extern "C" DllExport void node_setVisible(s32* pNode, bool visible);
extern "C" DllExport bool node_getVisible(s32* pNode);
extern "C" DllExport s32* node_asElement(s32* pNode);
extern "C" DllExport s32* node_asContainer(s32* pNode);
extern "C" DllExport s32* node_asSelectable(s32* pNode);
extern "C" DllExport s32* node_asAnimationNode(s32* pNode);
extern "C" DllExport s32* node_getName(s32* pNode);
extern "C" DllExport void node_setName(s32* pNode, s32* name);
extern "C" DllExport s32* node_getUITask(s32* pNode);
extern "C" DllExport s32* node_search(s32* pNode, s32* name);
extern "C" DllExport s32* node_searchFirstByTypeID(s32* pNode, u32 typeID);
//
// Element
//

extern "C" DllExport void element_setEnabled(s32* pElem, bool isEnabled);
extern "C" DllExport bool element_isEnabled(s32* pElem);
extern "C" DllExport bool element_setAsset(s32* pElem, u32 dest, s32* assetName);
extern "C" DllExport void element_setPriority(s32* pElem, u32 renderPriority);
extern "C" DllExport u32 element_getPriority(s32* pElem);
//
// Selectable
//

extern "C" DllExport void selectable_setClick(s32* pSelect, s32 coordinateX, s32 coordinateY, s32 width, s32 height);
extern "C" DllExport bool selectable_setAudio(s32* pSelect, s32* assetAudio, u32 mode, float volume);
extern "C" DllExport void selectable_setStick(s32* pSelect,bool isStickable);
extern "C" DllExport bool selectable_isStickable(s32* pSelect);

extern "C" DllExport void selectable_setSticked(s32* pSelect,bool isSticked);
extern "C" DllExport bool selectable_isSticked(s32* pSelect);

//
//	When clicked, all other stickable are modified / reset to unstick.
// 0 : Not radio, 1..n : Radio ID.
extern "C" DllExport void selectable_setRadio(s32* pSelect,u32 radioID);
extern "C" DllExport u32 selectable_getRadioID(s32* pSelect);


//
// Container
//

extern "C" DllExport s32 container_getViewOffsetX(s32* pCont);
extern "C" DllExport void container_setViewOffsetX(s32* pCont,s32 scrollX);
extern "C" DllExport s32 container_getViewOffsetY(s32* pCont);
extern "C" DllExport void container_setViewOffsetY(s32*  pCont,s32 scrollY);
// Allow to find the active radio button inside the container.
extern "C" DllExport u32 container_getRadioValue(s32* pCont);

//======================================================================================
//#include "CKLBGenericTask.h"

// "" is given instead of NULL because of the class specifications.
extern "C" DllExport s32* CKLBGenericTask_create(s32* pParentTask, s32 phase);

//======================================================================================
//#include "CKLBIntervalTimer.h"

// "" is given instead of NULL because of the class specifications.
// false is given as last arguement to prevent killing a timer if the timer interval has changed during the callback.
extern "C" DllExport s32* CKLBIntervalTimer_create(s32* pParent, u32 interval, bool repeat, u8 mode);

extern "C" DllExport u32 CKLBIntervalTimer_getTimerID(s32* pCtx);
extern "C" DllExport void CKLBIntervalTimer_setTimerID(s32* pCtx, u32 ID);

extern "C" DllExport bool CKLBIntervalTimer_getRepeat(s32* pCtx);
extern "C" DllExport void CKLBIntervalTimer_setRepeat(s32* pCtx, bool boolean);

extern "C" DllExport u32 CKLBIntervalTimer_getInterval(s32* pCtx);
extern "C" DllExport void CKLBIntervalTimer_setInterval(s32* pCtx, u32 interval);

extern "C" DllExport u8 CKLBIntervalTimer_getMode(s32* pCtx);

//======================================================================================
//#include "CKLBUIProgressBar.h"

extern "C" DllExport s32* CKLBUIProgressBar_create(s32* pParent, u32 order, float x, float y, float width, float height,s32* full_image, s32* empty_image,s32 start_pix, s32 end_pix, u32 anim, bool vert, s32* barfilterImage);

extern "C" DllExport u32 CKLBUIProgressBar_getOrder(s32* pCtx);
extern "C" DllExport void CKLBUIProgressBar_setOrder(s32* pCtx, u32 order);

extern "C" DllExport float CKLBUIProgressBar_getWidth(s32* pCtx);
extern "C" DllExport void CKLBUIProgressBar_setWidth(s32* pCtx, float width);

extern "C" DllExport float CKLBUIProgressBar_getHeight(s32* pCtx);
extern "C" DllExport void CKLBUIProgressBar_setHeight(s32* pCtx, float height);

extern "C" DllExport bool CKLBUIProgressBar_getVertical(s32* pCtx);
extern "C" DllExport void CKLBUIProgressBar_setVertical(s32* pCtx, bool vertical);

extern "C" DllExport u32 CKLBUIProgressBar_getAnimTime(s32* pCtx);
extern "C" DllExport void CKLBUIProgressBar_setAnimTime(s32* pCtx, u32 time);

extern "C" DllExport float CKLBUIProgressBar_getStart(s32* pCtx);
extern "C" DllExport void CKLBUIProgressBar_setStart(s32* pCtx, float start);

extern "C" DllExport float CKLBUIProgressBar_getEnd(s32* pCtx);
extern "C" DllExport void CKLBUIProgressBar_setEnd(s32* pCtx, float end);

extern "C" DllExport float CKLBUIProgressBar_getValue(s32* pCtx);
extern "C" DllExport void CKLBUIProgressBar_setValue(s32* pCtx, float value);

extern "C" DllExport s32* CKLBUIProgressBar_getImgEmpty(s32* pCtx);
extern "C" DllExport void CKLBUIProgressBar_setImgEmpty(s32* pCtx, s32* imgEmpty);

extern "C" DllExport s32* CKLBUIProgressBar_getImgFull(s32* pCtx);
extern "C" DllExport void CKLBUIProgressBar_setImgFull(s32* pCtx, s32* imgFull);

extern "C" DllExport s32* CKLBUIProgressBar_getImgFilter(s32* pCtx);
extern "C" DllExport void CKLBUIProgressBar_setImgFilter(s32* pCtx, s32* imgFilter);

extern "C" DllExport void CKLBUIProgressBar_reset(s32* pCtx);

extern "C" DllExport bool CKLBUIProgressBar_getFilterVisible(s32* pCtx);
extern "C" DllExport void CKLBUIProgressBar_setFilterVisible(s32* pCtx, bool bFilter);
extern "C" DllExport u32 CKLBUIProgressBar_getFilterColor(s32* pCtx);
extern "C" DllExport void CKLBUIProgressBar_setFilterColor(s32* pCtx, u32 argb);

extern "C" DllExport bool CKLBUIProgressBar_setFilterAnim(s32* pCtx, bool bColAnim, u32 argb1, u32 argb2, u32 freq);

//======================================================================================
//#include "CKLBUIScore.h"

extern "C" DllExport s32* CKLBUIScore_create(s32* pParent,u32 order, s32 order_offset,float x, float y,  s32** tex_table,float stepX, float stepY, u32 column, bool fillzero, bool anim_flag,u32 align, bool countclip);

extern "C" DllExport u32 CKLBUIScore_getValue(s32* pCtx);
extern "C" DllExport void CKLBUIScore_setValue(s32* pCtx, u32 value);

extern "C" DllExport u32 CKLBUIScore_getOrder(s32* pCtx);
extern "C" DllExport void CKLBUIScore_setOrder(s32* pCtx, u32 value);

extern "C" DllExport u32 CKLBUIScore_getOrderOffset(s32* pCtx);

extern "C" DllExport s32 CKLBUIScore_getStepX(s32* pCtx);
extern "C" DllExport void CKLBUIScore_setStepX(s32* pCtx, s32 value);

extern "C" DllExport s32 CKLBUIScore_getStepY(s32* pCtx);
extern "C" DllExport void CKLBUIScore_setStepY(s32* pCtx, s32 value);

extern "C" DllExport u32 CKLBUIScore_getColumn(s32* pCtx);
extern "C" DllExport void CKLBUIScore_setColumn(s32* pCtx, u32 value);

extern "C" DllExport bool CKLBUIScore_getFillZero(s32* pCtx);
extern "C" DllExport void CKLBUIScore_setFillZero(s32* pCtx, bool value);

extern "C" DllExport bool CKLBUIScore_getAnim(s32* pCtx);

extern "C" DllExport u32 CKLBUIScore_getAlign(s32* pCtx);
extern "C" DllExport void CKLBUIScore_setAlign(s32* pCtx, u32 value);

extern "C" DllExport bool CKLBUIScore_getCountClip(s32* pCtx);
extern "C" DllExport void CKLBUIScore_setCountClip(s32* pCtx, bool value);

extern "C" DllExport s32* CKLBUIScore_getTextures(s32* pCtx);

extern "C" DllExport void CKLBUIScore_setEnterAnimation(s32* pCtx, s32 milliSecondsPlayTime, s32 timeShift, u32 type, u32 affected, const float* arrayParam);

extern "C" DllExport void CKLBUIScore_setExitAnimation(s32* pCtx, s32 milliSecondsPlayTime, s32 timeShift, u32 type, u32 affected, const float* arrayParam);

//======================================================================================
//#include "CKLBUITask.h"

// No constructor for UI Task

extern "C" DllExport bool CKLBUITask_getVisible(s32* pCtx);
extern "C" DllExport void CKLBUITask_setVisible(s32* pCtx, bool isVisible);

extern "C" DllExport float CKLBUITask_getScaleX(s32* pCtx);
extern "C" DllExport void CKLBUITask_setScaleX(s32* pCtx, float scaleX);

extern "C" DllExport float CKLBUITask_getScaleY(s32* pCtx);
extern "C" DllExport void CKLBUITask_setScaleY(s32* pCtx, float scaleY);

extern "C" DllExport float CKLBUITask_getX(s32* pCtx);
extern "C" DllExport void CKLBUITask_setX(s32* pCtx, float x);

extern "C" DllExport float CKLBUITask_getY(s32* pCtx);
extern "C" DllExport void CKLBUITask_setY(s32* pCtx, float y);

extern "C" DllExport float CKLBUITask_getRotation(s32* pCtx);
extern "C" DllExport void CKLBUITask_setRotation(s32* pCtx, float y);

extern "C" DllExport u32 CKLBUITask_getArgb(s32* pCtx);
extern "C" DllExport void CKLBUITask_setArgb(s32* pCtx, u32 argb);

extern "C" DllExport bool CKLBUITask_isAnim(s32* pCtx);

extern "C" DllExport void CKLBUITask_play(s32* pCtx);
extern "C" DllExport void CKLBUITask_stop(s32* pCtx);

extern "C" DllExport bool CKLBUITask_setParamCount(s32* pCtx, u32 splineCount, u32 maxKeyCount);

extern "C" DllExport void CKLBUITask_setTarget(s32* pCtx, u32 splineIndex, u32 targetParameter);

extern "C" DllExport void CKLBUITask_addKeys(s32* pCtx, u32 splineIndex, u32 time, s32 value);

extern "C" DllExport void CKLBUITask_addKeysFixed(s32* pCtx, u32 splineIndex, u32 time, s32 fixed16Value);

extern "C" DllExport void CKLBUITask_generateAnimation(s32* pCtx);

extern "C" DllExport bool CKLBUITask_reconnect(s32* pCtx, s32* nodeName);

//======================================================================================
//#include "CKLBUISimpleItem.h"

extern "C" DllExport s32* CKLBUISimpleItem_create(s32* pParent, u32 order, float x, float y, s32* asset);

extern "C" DllExport u32 CKLBUISimpleItem_getOrder(s32* pCtx);
extern "C" DllExport void CKLBUISimpleItem_setOrder(s32* pCtx, u32 order);

extern "C" DllExport s32* CKLBUISimpleItem_getAsset(s32* pCtx);

//======================================================================================
//#include "CKLBUICanvas.h"

extern "C" DllExport s32* CKLBUICanvas_create(s32* pParent, u32 order, float x, float y, u32 vertexMax, u32 indexMax);

extern "C" DllExport u32 CKLBUICanvas_getOrder(s32* pCtx);
extern "C" DllExport void CKLBUICanvas_setOrder(s32* pCtx, u32 order);

extern "C" DllExport u32 CKLBUICanvas_getIdxMax(s32* pCtx);

extern "C" DllExport void CKLBUICanvas_setFreeze(s32* pCtx, bool freeze);

extern "C" DllExport bool CKLBUICanvas_addResource(s32* pCtx, s32* asset);

extern "C" DllExport void CKLBUICanvas_drawImage(s32* pCtx, float x, float y, u32 idx, u32 color);

extern "C" DllExport void CKLBUICanvas_drawImageScale(s32* pCtx, float x, float y, float scale,u32 idx, u32 color);

extern "C" DllExport void CKLBUICanvas_fillRect(s32* pCtx, float x, float y, float w, float h, u32 color);

extern "C" DllExport void CKLBUICanvas_startDynamicSection(s32* pCtx, u32 idx);

extern "C" DllExport void CKLBUICanvas_endDynamicSection(s32* pCtx, u32 idx);
extern "C" DllExport void CKLBUICanvas_dynamicSectionTranslate(s32* pCtx, u32 idx, float deltaX, float deltaY);

extern "C" DllExport void CKLBUICanvas_dynamicSectionColor(s32* pCtx, u32 idx, u32 color);

//======================================================================================
//#include "CKLBUIScale9.h"

extern "C" DllExport s32* CKLBUIScale9_create(s32* pParent, u32 order, float x, float y, s32 width, s32 height, s32* SCALE9Asset);

extern "C" DllExport void CKLBUIScale9_setWidth(s32* pCtx, s32 width);

extern "C" DllExport s32 CKLBUIScale9_getWidth(s32* pCtx);

extern "C" DllExport void CKLBUIScale9_setHeight(s32* pCtx, s32 height);

extern "C" DllExport s32 CKLBUIScale9_getHeight(s32* pCtx);

extern "C" DllExport void CKLBUIScale9_setOrder(s32* pCtx, u32 order);

extern "C" DllExport u32 CKLBUIScale9_getOrder(s32* pCtx);

extern "C" DllExport s32* CKLBUIScale9_getAsset(s32* pCtx);

extern "C" DllExport bool CKLBUIScale9_setAsset(s32* pCtx, s32* asset);

//======================================================================================
//#include "CKLBUIScrollBar.h"

extern "C" DllExport s32* CKLBUIScrollBar_create(s32* pParent,u32 order, float x, float y, float width, float height,s32 minValue, s32 maxValue, s32 pos, s32* image,s32 slider_size, s32 min_slider_size, u32 colorNormal, u32 colorSelect, bool vert, bool active, bool hideMode);

extern "C" DllExport s32 CKLBUIScrollBar_getMin(s32* pCtx);
extern "C" DllExport void CKLBUIScrollBar_setMin(s32* pCtx, s32 value);

extern "C" DllExport s32 CKLBUIScrollBar_getMax(s32* pCtx);
extern "C" DllExport void CKLBUIScrollBar_setMax(s32* pCtx, s32 value);

extern "C" DllExport s32 CKLBUIScrollBar_getPos(s32* pCtx);
extern "C" DllExport void CKLBUIScrollBar_setPos(s32* pCtx, s32 value);

extern "C" DllExport s32 CKLBUIScrollBar_getSliderSize(s32* pCtx);
extern "C" DllExport void CKLBUIScrollBar_setSliderSize(s32* pCtx, s32 value);

extern "C" DllExport s32 CKLBUIScrollBar_getSliderSizeMin(s32* pCtx);
extern "C" DllExport void CKLBUIScrollBar_setSliderSizeMin(s32* pCtx, s32 value);

extern "C" DllExport bool CKLBUIScrollBar_getTouchActive(s32* pCtx);
extern "C" DllExport void CKLBUIScrollBar_setTouchActive(s32* pCtx, bool active);

extern "C" DllExport u32  CKLBUIScrollBar_getNormalColor(s32* pCtx);
extern "C" DllExport void CKLBUIScrollBar_setNormalColor(s32* pCtx, u32 color);

extern "C" DllExport u32  CKLBUIScrollBar_getActiveColor(s32* pCtx);
extern "C" DllExport void CKLBUIScrollBar_setActiveColor(s32* pCtx, u32 color);

extern "C" DllExport void CKLBUIScrollBar_setMode(s32* pCtx, u32 mode);

extern "C" DllExport bool CKLBUIScrollBar_getVertical(s32* pCtx);
extern "C" DllExport void CKLBUIScrollBar_setVertical(s32* pCtx, bool vertical);

extern "C" DllExport u32 CKLBUIScrollBar_getWidth(s32* pCtx); 
extern "C" DllExport void CKLBUIScrollBar_setWidth(s32* pCtx, s32 width);

extern "C" DllExport u32 CKLBUIScrollBar_getHeight(s32* pCtx); 
extern "C" DllExport void CKLBUIScrollBar_setHeight(s32* pCtx, s32 height);

extern "C" DllExport u32 CKLBUIScrollBar_getOrder(s32* pCtx); 
extern "C" DllExport void CKLBUIScrollBar_setOrder(s32* pCtx, u32 order);

extern "C" DllExport s32* CKLBUIScrollBar_getImage(s32* pCtx);

extern "C" DllExport u32 CKLBUIScrollBar_getMode(s32* pCtx); 

extern "C" DllExport bool CKLBUIScrollBar_selectScrMgr(s32* pCtx, s32* name, int len, int* args);

//======================================================================================
//#include "CKLBUIWebArea.h"

extern "C" DllExport s32* CKLBUIWebArea_create(s32* pParent, bool mode, float x, float y, float width, float height, s32* url);

extern "C" DllExport void CKLBUIWebArea_setWidth(s32* pCtx, s32 width);
extern "C" DllExport s32 CKLBUIWebArea_getWidth(s32* pCtx);

extern "C" DllExport void CKLBUIWebArea_setHeight(s32* pCtx, s32 height);
extern "C" DllExport s32 CKLBUIWebArea_getHeight(s32* pCtx);

extern "C" DllExport void CKLBUIWebArea_setText(s32* pCtx, s32* text);
extern "C" DllExport s32* CKLBUIWebArea_getText(s32* pCtx);

extern "C" DllExport void CKLBUIWebArea_setScalesPageToFit(s32* pCtx, bool b);

extern "C" DllExport void CKLBUIWebArea_setBgColor(s32* pCtx, u32 argb);
//======================================================================================
//#include "CKLBUIVirtualDoc.h"

extern "C" DllExport s32* CKLBUIVirtualDoc_create(s32* pParent,u32 order, float x, float y,u32 doc_width, u32 doc_height, u32 view_width, u32 view_height,u32 max_command_nums, bool vertical); 

extern "C" DllExport void CKLBUIVirtualDoc_clear(s32* pCtx, u32 color);

extern "C" DllExport void CKLBUIVirtualDoc_setFont(s32* pCtx, u32 idx, s32* fontName, u32 fontSize);

extern "C" DllExport void CKLBUIVirtualDoc_setViewPortPos(s32* pCtx, s32 x, s32 y);

extern "C" DllExport void CKLBUIVirtualDoc_drawLine(s32* pCtx, s32 x0, s32 y0, s32 x1, s32 y1, u32 color);

extern "C" DllExport void CKLBUIVirtualDoc_drawImage(s32* pCtx, s32 x0, s32 y0, s32* image, u32 alpha);

extern "C" DllExport void CKLBUIVirtualDoc_fillRect(s32* pCtx, s32 x0, s32 y0, u32 width, u32 height, u32 color, bool fill);

extern "C" DllExport void CKLBUIVirtualDoc_drawText(s32* pCtx, s32 x0, s32 y0, s32* str, u32 color, u32 fontidx);

extern "C" DllExport void CKLBUIVirtualDoc_startDocument(s32* pCtx);

extern "C" DllExport void CKLBUIVirtualDoc_checkDocumentSize(s32* pCtx);

extern "C" DllExport void CKLBUIVirtualDoc_endDocument(s32* pCtx);

extern "C" DllExport u32 CKLBUIVirtualDoc_getCommandMax(s32* pCtx);
extern "C" DllExport void CKLBUIVirtualDoc_setCommandMax(s32* pCtx, u32 command);

extern "C" DllExport u32 CKLBUIVirtualDoc_getDocHeight(s32* pCtx);
extern "C" DllExport void CKLBUIVirtualDoc_setDocHeight(s32* pCtx, u32 height);

extern "C" DllExport u32 CKLBUIVirtualDoc_getDocWidth(s32* pCtx);
extern "C" DllExport void CKLBUIVirtualDoc_setDocWidth(s32* pCtx, u32 width);

extern "C" DllExport bool CKLBUIVirtualDoc_getVertical(s32* pCtx);
extern "C" DllExport void CKLBUIVirtualDoc_setVertical(s32* pCtx, bool vertical);

extern "C" DllExport u32 CKLBUIVirtualDoc_getViewHeight(s32* pCtx);
extern "C" DllExport void CKLBUIVirtualDoc_setViewHeight(s32* pCtx, u32 height);

extern "C" DllExport u32 CKLBUIVirtualDoc_getViewWidth(s32* pCtx);
extern "C" DllExport void CKLBUIVirtualDoc_setViewWidth(s32* pCtx, u32 width);

extern "C" DllExport u32 CKLBUIVirtualDoc_getOrder(s32* pCtx);
extern "C" DllExport void CKLBUIVirtualDoc_setOrder(s32* pCtx, u32 order);

extern "C" DllExport void CKLBUIVirtualDoc_setAlign(s32* pCtx, u32 align, u32 alignWidth);

//======================================================================================
//#include "CKLBUICellAnim.h"

extern "C" DllExport s32* CKLBUICellAnim_create(s32* pParent, u32 order, float x, float y, s32* asset, u32 index);

extern "C" DllExport void CKLBUICellAnim_play(s32* pCtx);

extern "C" DllExport void CKLBUICellAnim_stop(s32* pCtx);

extern "C" DllExport void CKLBUICellAnim_setPlayMode(s32* pCtx, u32 mode);

extern "C" DllExport u32 CKLBUICellAnim_getOrder(s32* pCtx);

extern "C" DllExport u32 CKLBUICellAnim_getAnimIndex(s32* pCtx);
extern "C" DllExport void CKLBUICellAnim_setAnimIndex(s32* pCtx, u32 index);

extern "C" DllExport s32* CKLBUICellAnim_getAsset(s32* pCtx);

//======================================================================================
//#include "CKLBUISWFPlayer.h"

extern "C" DllExport s32* CKLBUISWFPlayer_create(s32* pParent, u32 order, float x, float y, s32* asset,s32* movie_name, s32** replace_list, int asset_cnt);

extern "C" DllExport bool CKLBUISWFPlayer_getPlay(s32* pCtx);
extern "C" DllExport void CKLBUISWFPlayer_setPlay(s32* pCtx,bool play);

extern "C" DllExport u32 CKLBUISWFPlayer_getOrder(s32* pCtx);
extern "C" DllExport void CKLBUISWFPlayer_setOrder(s32* pCtx,u32 order);

extern "C" DllExport void CKLBUISWFPlayer_gotoFrame(s32* pCtx,s32* label);

extern "C" DllExport u16 CKLBUISWFPlayer_getFrameRate(s32* pCtx);
extern "C" DllExport void CKLBUISWFPlayer_setFrameRate(s32* pCtx,u32 fps);

extern "C" DllExport bool CKLBUISWFPlayer_isAnimating(s32* pCtx);

extern "C" DllExport void CKLBUISWFPlayer_setFrameRateScale(s32* pCtx,float scale);

extern "C" DllExport s32* CKLBUISWFPlayer_getAsset(s32* pCtx);

extern "C" DllExport s32* CKLBUISWFPlayer_getMovieName(s32* pCtx);

extern "C" DllExport float CKLBUISWFPlayer_getVolume(s32* pCtx);
extern "C" DllExport void CKLBUISWFPlayer_setVolume(s32* pCtx,float volume);
//======================================================================================
//#include "CKLBUIGroup.h"

extern "C" DllExport s32* CKLBUIGroup_create(s32* pParent, float x, float y);

extern "C" DllExport bool CKLBUIGroup_setAnimCallback(s32* pCtx, s32* callback);

extern "C" DllExport bool CKLBUIGroup_setAnimation(s32* pCtx, s32* name, bool blend);

extern "C" DllExport bool CKLBUIGroup_isAnim(s32* pCtx, s32* name);

extern "C" DllExport bool CKLBUIGroup_skipAnim(s32* pCtx, s32* name);

//======================================================================================
//#include "CKLBUIPolyline.h"

extern "C" DllExport s32* CKLBUIPolyline_create(s32* pParent, u32 order, u32 maxPoint);

extern "C" DllExport u32 CKLBUIPolyline_getMaxPoint(s32* pCtx);
extern "C" DllExport void CKLBUIPolyline_setMaxPoint(s32* pCtx,u32 maxpointcount);

extern "C" DllExport u32 CKLBUIPolyline_getOrder(s32* pCtx);

extern "C" DllExport u32 CKLBUIPolyline_getPointCount(s32* pCtx);
extern "C" DllExport void CKLBUIPolyline_setPointCount(s32* pCtx,u32 pointcount);

extern "C" DllExport void CKLBUIPolyline_setPoint(s32* pCtx,u32 idx, float x, float y);

extern "C" DllExport u32 CKLBUIPolyline_getColor(s32* pCtx);
extern "C" DllExport void CKLBUIPolyline_setColor(s32* pCtx,u32 color);

//======================================================================================
//#include "CKLBUIFreeVertItem.h"

extern "C" DllExport s32* CKLBUIFreeVertItem_create(s32* pParent, u32 order, float x, float y, s32* asset, float* vertices);

extern "C" DllExport u32 CKLBUIFreeVertItem_getOrder(s32* pCtx);
extern "C" DllExport void CKLBUIFreeVertItem_setOrder(s32* pCtx,u32 order);

extern "C" DllExport s32* CKLBUIFreeVertItem_getAsset(s32* pCtx);

extern "C" DllExport void CKLBUIFreeVertItem_setVertices(s32* pCtx, float* coord);
extern "C" DllExport void CKLBUIFreeVertItem_setColors(s32* pCtx, u32* colors);

extern "C" DllExport void CKLBUIFreeVertItem_setVertCol(s32* pCtx, u32 idx, u32 argb);

extern "C" DllExport void CKLBUIFreeVertItem_setUV(s32* pCtx, float* uv);

//======================================================================================
//#include "CKLBUITextInput.h"

extern "C" DllExport s32* CKLBUITextInput_create(s32* pParent,bool passwdmode,float x, float y, float width, float height, s32* default_text,u32 widget_id, int maxlen, u32 chartype);

extern "C" DllExport u32  CKLBUITextInput_getWidth(s32* pCtx);
extern "C" DllExport void CKLBUITextInput_setWidth(s32* pCtx, u32 width);

extern "C" DllExport u32 CKLBUITextInput_getHeight(s32* pCtx);
extern "C" DllExport void CKLBUITextInput_setHeight(s32* pCtx, u32 height);

extern "C" DllExport s32* CKLBUITextInput_getText(s32* pCtx);
extern "C" DllExport void CKLBUITextInput_setText(s32* pCtx, s32* text);

extern "C" DllExport void CKLBUITextInput_setPlaceHolder(s32* pCtx, s32* placeHolder);

extern "C" DllExport int CKLBUITextInput_getMaxLen(s32* pCtx);
extern "C" DllExport void CKLBUITextInput_setMaxLen(s32* pCtx, int maxLen);

extern "C" DllExport void CKLBUITextInput_setCharType(s32* pCtx, u32 charType);

extern "C" DllExport s32 CKLBUITextInput_getCharCount(s32* pCtx);

extern "C" DllExport void CKLBUITextInput_setColor(s32* pCtx, bool bTouch, u32 fgRgb, u32 bgRgb);

extern "C" DllExport void CKLBUITextInput_setFont(s32* pCtx, s32* fontName, float fontSize);

//======================================================================================
//#include "CKLBUIMultiImgItem.h"

extern "C" DllExport s32* CKLBUIMultiImgItem_create(s32* pParent, u32 order, float x, float y, u32 idx, s32** pArrayAsset,u32* pArrayIndexes, u32 assetCount);

extern "C" DllExport u32 CKLBUIMultiImgItem_getIndexMax(s32* pCtx);
extern "C" DllExport void CKLBUIMultiImgItem_setIndexMax(s32* pCtx,u32 index);

extern "C" DllExport u32 CKLBUIMultiImgItem_getOrder(s32* pCtx);
extern "C" DllExport void CKLBUIMultiImgItem_setOrder(s32* pCtx,u32 order);

extern "C" DllExport u32 CKLBUIMultiImgItem_getIndex(s32* pCtx);
extern "C" DllExport void CKLBUIMultiImgItem_setIndex(s32* pCtx, u32 index);

extern "C" DllExport bool CKLBUIMultiImgItem_changeAssets(s32* pCtx, s32** pArrayAsset, u32* pArrayIndexes, u32 assetCount);

//======================================================================================
//#include "CKLBUIRubberBand.h"

extern "C" DllExport s32* CKLBUIRubberBand_create(s32* pParent, u32 order, float x, float y, u32 resolution, s32* origin, s32* joint,s32* point, u32 flags, u32 animTime, s32 joint_order_off, s32 point_order_off, bool rot_origin, bool rot_joint, bool rot_point);

extern "C" DllExport float CKLBUIRubberBand_getOriginX(s32* pCtx);
extern "C" DllExport void CKLBUIRubberBand_setOriginX(s32* pCtx,float x);

extern "C" DllExport float CKLBUIRubberBand_getOriginY(s32* pCtx);
extern "C" DllExport void CKLBUIRubberBand_setOriginY(s32* pCtx,float y);

extern "C" DllExport float CKLBUIRubberBand_getPointX(s32* pCtx);
extern "C" DllExport void CKLBUIRubberBand_setPointX(s32* pCtx,float x);

extern "C" DllExport float CKLBUIRubberBand_getPointY(s32* pCtx);
extern "C" DllExport void CKLBUIRubberBand_setPointY(s32* pCtx,float y);

extern "C" DllExport bool CKLBUIRubberBand_getFAnim(s32* pCtx);
extern "C" DllExport void CKLBUIRubberBand_setFAnim(s32* pCtx,bool fAnim);

extern "C" DllExport bool CKLBUIRubberBand_getFAnimRT(s32* pCtx);
extern "C" DllExport void CKLBUIRubberBand_setFAnimRT(s32* pCtx,bool fAnimRT);

extern "C" DllExport u32 CKLBUIRubberBand_getAnimTime(s32* pCtx);
extern "C" DllExport void CKLBUIRubberBand_setAnimTime(s32* pCtx,u32 animTime);

extern "C" DllExport u32 CKLBUIRubberBand_getOrder(s32* pCtx);

extern "C" DllExport s32* CKLBUIRubberBand_getAssetOrigin(s32* pCtx);

extern "C" DllExport s32* CKLBUIRubberBand_getAssetJoint(s32* pCtx);

extern "C" DllExport s32* CKLBUIRubberBand_getAssetPoint(s32* pCtx);

extern "C" DllExport bool CKLBUIRubberBand_setOrder(s32* pCtx, u32 order_origin, u32 order_joint, u32 order_point);

//======================================================================================
//#include "CKLBUIPieChart.h"

extern "C" DllExport s32* CKLBUIPieChart_create(s32* pParent, u32 order, float x, float y, float width, float height, s32* asset, float start,float end, u32 anim, float initial);

extern "C" DllExport float CKLBUIPieChart_getStart(s32* pCtx);
extern "C" DllExport void CKLBUIPieChart_setStart(s32* pCtx,float start);

extern "C" DllExport float CKLBUIPieChart_getEnd(s32* pCtx);
extern "C" DllExport void CKLBUIPieChart_setEnd(s32* pCtx,float end);

extern "C" DllExport float CKLBUIPieChart_getValue(s32* pCtx);
extern "C" DllExport void CKLBUIPieChart_setValue(s32* pCtx,float value);

extern "C" DllExport s32 CKLBUIPieChart_getAnim(s32* pCtx);

extern "C" DllExport u32 CKLBUIPieChart_getOrder(s32* pCtx);

extern "C" DllExport bool CKLBUIPieChart_changeAsset(s32* pCtx, s32* assetName);

//======================================================================================
//#include "CKLBUIMoviePlayer.h"

extern "C" DllExport s32* CKLBUIMoviePlayer_create(s32* pParent, bool mode, float x, float y, float width, float height, s32* url);

extern "C" DllExport void CKLBUIMoviePlayer_setWidth(s32* pCtx,u32 width);

extern "C" DllExport u32 CKLBUIMoviePlayer_getWidth(s32* pCtx);

extern "C" DllExport void CKLBUIMoviePlayer_setHeight(s32* pCtx,u32 height);

extern "C" DllExport u32 CKLBUIMoviePlayer_getHeight(s32* pCtx);

extern "C" DllExport void CKLBUIMoviePlayer_setText(s32* pCtx,s32* text);

extern "C" DllExport s32* CKLBUIMoviePlayer_getText(s32* pCtx);

extern "C" DllExport void CKLBUIMoviePlayer_moviePlay(s32* pCtx);

extern "C" DllExport void CKLBUIMoviePlayer_movieStop(s32* pCtx);

extern "C" DllExport void CKLBUIMoviePlayer_moviePause(s32* pCtx);

extern "C" DllExport void CKLBUIMoviePlayer_movieResume(s32* pCtx);

//======================================================================================
//#include "CKLBUIDragIcon.h"

extern "C" DllExport s32* CKLBUIDragIcon_create(s32* pParent, u32 order, float x, float y, s32* tap_area, s32* asset, s32* drag_asset,s32 drag_order_offset, float drag_alpha, float center_x, float center_y, u32 flags);

extern "C" DllExport u32 CKLBUIDragIcon_getOrder(s32* pCtx);

extern "C" DllExport s32* CKLBUIDragIcon_getAsset(s32* pCtx);

extern "C" DllExport s32* CKLBUIDragIcon_getDrag(s32* pCtx);

extern "C" DllExport u32 CKLBUIDragIcon_getFlags(s32* pCtx);
extern "C" DllExport void CKLBUIDragIcon_setFlags(s32* pCtx,u32 flag);

extern "C" DllExport bool CKLBUIDragIcon_getEnable(s32* pCtx);
extern "C" DllExport void CKLBUIDragIcon_setEnable(s32* pCtx,bool enable);

extern "C" DllExport float CKLBUIDragIcon_getDragScaleX(s32* pCtx);
extern "C" DllExport void CKLBUIDragIcon_setDragScaleX(s32* pCtx,float scale);

extern "C" DllExport float CKLBUIDragIcon_getDragScaleY(s32* pCtx);
extern "C" DllExport void CKLBUIDragIcon_setDragScaleY(s32* pCtx,float scale);

extern "C" DllExport void CKLBUIDragIcon_dragArea(s32* pCtx, s32* area);

//======================================================================================
//#include "CKLBUIDebugItem.h"

extern "C" DllExport s32* CKLBUIDebugItem_create(s32* pParent, u32 order, float x, float y, u32 argb, s32* font, u32 size, s32* text, u32 id);

extern "C" DllExport void CKLBUIDebugItem_setOrder(s32* pCtx,u32 order);
extern "C" DllExport u32 CKLBUIDebugItem_getOrder(s32* pCtx);

extern "C" DllExport void CKLBUIDebugItem_setColor(s32* pCtx,u32 color);
extern "C" DllExport u32 CKLBUIDebugItem_getColor(s32* pCtx);

extern "C" DllExport void CKLBUIDebugItem_setFont(s32* pCtx,s32* font);
extern "C" DllExport s32* CKLBUIDebugItem_getFont(s32* pCtx);

// Font size
extern "C" DllExport void CKLBUIDebugItem_setSize(s32* pCtx,u32 size);
extern "C" DllExport u32 CKLBUIDebugItem_getSize(s32* pCtx);

extern "C" DllExport void CKLBUIDebugItem_setText(s32* pCtx,s32* text);
extern "C" DllExport s32* CKLBUIDebugItem_getText(s32* pCtx);

//======================================================================================
//#include "CKLBUILabel.h"

extern "C" DllExport s32* CKLBUILabel_create(s32* pParent, u32 order, float x, float y, u32 argb, s32* font, u32 size, s32* text, u32 align);

extern "C" DllExport u32 CKLBUILabel_getOrder(s32* pCtx);
extern "C" DllExport void CKLBUILabel_setOrder(s32* pCtx,u32 order);

extern "C" DllExport u32 CKLBUILabel_getAlign(s32* pCtx);
extern "C" DllExport void CKLBUILabel_setAlign(s32* pCtx,u32 align);

extern "C" DllExport s32* CKLBUILabel_getText(s32* pCtx);
extern "C" DllExport void CKLBUILabel_setText(s32* pCtx,s32* txt);

extern "C" DllExport u32 CKLBUILabel_getColor(s32* pCtx);
extern "C" DllExport void CKLBUILabel_setColor(s32* pCtx,u32 color);

extern "C" DllExport s32* CKLBUILabel_getFont(s32* pCtx);
extern "C" DllExport void CKLBUILabel_setFont(s32* pCtx,s32* font);

extern "C" DllExport u32 CKLBUILabel_getFontSize(s32* pCtx);
extern "C" DllExport void CKLBUILabel_setFontSize(s32* pCtx,u32 size);

extern "C" DllExport void CKLBUILabel_setPosition(s32* pCtx, float x, float y);

//======================================================================================
//#include "CKLBUIList.h"
extern "C" DllExport  s32* CKLBUIList_create(s32* pParent, u32 base_order, u32 max_order, float x, float y, float clip_width, float clip_height,s32 default_line_step, bool vertical, u32 optional_flags);
extern "C" DllExport u32 CKLBUIList_getWidth(s32* pCtx);
extern "C" DllExport void CKLBUIList_setWidth(s32* pCtx,u32 width);

extern "C" DllExport u32 CKLBUIList_getHeight(s32* pCtx);
extern "C" DllExport void CKLBUIList_setHeight(s32* pCtx,u32 height);

extern "C" DllExport s32 CKLBUIList_getStepX(s32* pCtx);
extern "C" DllExport void CKLBUIList_setStepX(s32* pCtx,s32 x);

extern "C" DllExport s32 CKLBUIList_getStepY(s32* pCtx);
extern "C" DllExport void CKLBUIList_setStepY(s32* pCtx,s32 x);

extern "C" DllExport u32 CKLBUIList_getOrder(s32* pCtx);
extern "C" DllExport void CKLBUIList_setOrder(s32* pCtx,u32 order);

extern "C" DllExport u32 CKLBUIList_getMaxOrder(s32* pCtx);
extern "C" DllExport void CKLBUIList_setMaxOrder(s32* pCtx,u32 maxOrder);

extern "C" DllExport bool CKLBUIList_getVertical(s32* pCtx);
extern "C" DllExport void CKLBUIList_setVertical(s32* pCtx,bool vertical);

extern "C" DllExport u32 CKLBUIList_getItems(s32* pCtx);

extern "C" DllExport s32 CKLBUIList_getMarginTop(s32* pCtx);
extern "C" DllExport void CKLBUIList_setMarginTop(s32* pCtx,s32 top);

extern "C" DllExport s32 CKLBUIList_getMarginBottom(s32* pCtx);
extern "C" DllExport void CKLBUIList_setMarginBottom(s32* pCtx,s32 bottom);

extern "C" DllExport bool CKLBUIList_getDefaultScroll(s32* pCtx);
extern "C" DllExport void CKLBUIList_setDefaultScroll(s32* pCtx,bool scroll);
extern "C" DllExport bool CKLBUIList_cmdItemRemove(s32* pCtx,s32 idx);

extern "C" DllExport void CKLBUIList_cmdItemMove(s32* pCtx,s32 src, s32 dst);

extern "C" DllExport void CKLBUIList_cmdSetMargin(s32* pCtx,s32 top, s32 bottom);

extern "C" DllExport s32 CKLBUIList_cmdGetPosition(s32* pCtx);
extern "C" DllExport s32 CKLBUIList_cmdSetPosition(s32* pCtx, s32 pos, s32 dir);

extern "C" DllExport s32 CKLBUIList_cmdSearchID(s32* pCtx,u32 id);

extern "C" DllExport void CKLBUIList_cmdSetItemPos(s32* pCtx,u32 mode, s32 idx, s32 offset);

extern "C" DllExport void CKLBUIList_cmdSetLimitClip(s32* pCtx,bool chklimit);

extern "C" DllExport s32 CKLBUIList_cmdGetLimit(s32* pCtx);

extern "C" DllExport bool CKLBUIList_cmdSetLimitArea(s32* pCtx,s32 limitArea);

extern "C" DllExport void CKLBUIList_cmdChangeStep(s32* pCtx,s32 index, s32 step);

extern "C" DllExport void CKLBUIList_cmdInputEnable(s32* pCtx,bool enable);

extern "C" DllExport bool CKLBUIList_cmdAnimationItem(s32* pCtx,s32 index, s32* name, bool blend);

extern "C" DllExport bool CKLBUIList_cmdAnimationAll(s32* pCtx,s32* name, bool blend);

extern "C" DllExport bool CKLBUIList_cmdItemAnimSkip(s32* pCtx,s32 index, s32* name);

extern "C" DllExport bool CKLBUIList_cmdAllAnimSkip(s32* pCtx, s32* name);

extern "C" DllExport void CKLBUIList_cmdSetGroup(s32* pCtx, s32* group_name);

extern "C" DllExport void CKLBUIList_cmdSetItemID(s32* pCtx, s32 index, u32 id);

extern "C" DllExport void CKLBUIList_setLoop(s32* pCtx, bool mode);

extern "C" DllExport bool CKLBUIList_useScrollBar(s32* pCtx, u32 order, bool side, s32 lineWeight, s32* image, s32 min_slender_size, u32 colorNormal, u32 colorSelect, bool active, bool hideMode, bool shortHide);

extern "C" DllExport void CKLBUIList_cmdFWModeConfig(s32* pCtx, int itemStep, int maxItems);

extern "C" DllExport bool CKLBUIList_cmdSetItemMode(s32* pCtx, int itemMode);

extern "C" DllExport bool CKLBUIList_cmdAddRecords(s32* pCtx, s32 insIdx, s32* form, s32* db, s32 step);

extern "C" DllExport s32 CKLBUIList_cmdSetInitial(s32* pCtx, s32 pos);

extern "C" DllExport bool CKLBUIList_cmdSelectScrMgr(s32* pCtx, s32* name, s32* optParams, u32 nb);

extern "C" DllExport void CKLBUIList_cmdSetClip(s32* pCtx, u32 orderBegin, u32 orderEnd, s16 clipX, s16 clipY, s16 clipWidth, s16 clipHeight);

extern "C" DllExport s32 CKLBUIList_cmdItemAdd(s32* pCtx, s32* asset);
extern "C" DllExport s32 CKLBUIList_cmdItemAdd2(s32* pCtx, s32* asset, s32 step, s32 id);

extern "C" DllExport s32 CKLBUIList_cmdInsertItem(s32* pCtx, s32* asset, s32 index);
extern "C" DllExport s32 CKLBUIList_cmdInsertItem2(s32* pCtx, s32* asset, s32 index, s32 step, s32 id);

extern "C" DllExport s32 CKLBUIList_cmdRemoveSelection(s32* pCtx, s32* indexes, u32 nb);

extern "C" DllExport void CKLBUIList_setDragRect(s32* pCtx, s32 left, s32 top, s32 right, s32 bottom);

extern "C" DllExport bool CKLBUIList_cmdExistNode(s32* pCtx, s32 index, s32* name);

//======================================================================================
//#include "CKLBUIForm.h"

extern "C" DllExport s32* CKLBUIForm_create(s32* pParent, u32 order, float x, float y, bool bAssetFile, s32* asset, bool bExclusive, bool modal, bool urgent);

extern "C" DllExport s32* CKLBUIForm_getAsset(s32* pCtx);

extern "C" DllExport u32 CKLBUIForm_getOrder(s32* pCtx);

extern "C" DllExport bool CKLBUIForm_getExclusive(s32* pCtx);
extern "C" DllExport void CKLBUIForm_setExclusive(s32* pCtx, bool exclusive);

extern "C" DllExport bool CKLBUIForm_getIsFile(s32* pCtx);

extern "C" DllExport void CKLBUIForm_setEnable(s32* pCtx, bool isEnabled);

extern "C" DllExport bool CKLBUIForm_existNode(s32* pCtx, s32* name);

extern "C" DllExport void CKLBUIForm_inputEnable(s32* pCtx, bool bEnable);

extern "C" DllExport bool CKLBUIForm_animation(s32* pCtx, s32* animname, bool blend);

extern "C" DllExport bool CKLBUIForm_isAnim(s32* pCtx, s32* name);

extern "C" DllExport bool CKLBUIForm_skipAnim(s32* pCtx, s32* name);

extern "C" DllExport bool CKLBUIForm_animEnter(s32* pCtx);

extern "C" DllExport bool CKLBUIForm_animLeave(s32* pCtx);

extern "C" DllExport bool CKLBUIForm_setGroup(s32* pCtx, s32* group_name);

extern "C" DllExport void CKLBUIForm_setGlobalVolume(s32* pCtx, float volume);

//======================================================================================
//#include "CKLBUIControl.h"

// "" is given instead of NULL because of the class specifications.
extern "C" DllExport s32* CKLBUIControl_create(s32* pParentTask);

extern "C" DllExport void CKLBUIControl_lock(s32* pCtx, bool lockMode);

extern "C" DllExport bool CKLBUIControl_setGroup(s32* pCtx, s32* groupName);

extern "C" DllExport void CKLBUIControl_setMask(s32* pCtx, u16 mask);

//======================================================================================
//#include "CKLBUITouchPad.h"

// "" is given instead of NULL because of the class specifications.
extern "C" DllExport s32* CKLBUITouchPad_create(s32* pParent, bool modal);

extern "C" DllExport bool CKLBUITouchPad_setGroup(s32* pCtx, s32* group_name);

extern "C" DllExport void CKLBUITouchPad_setLock(s32* pCtx, bool lock_mode);

extern "C" DllExport void CKLBUITouchPad_setGetAll(s32* pCtx, bool b);

//======================================================================================
//#include "CKLBUIClip.h"

extern "C" DllExport s32* CKLBUIClip_create(s32* pParent, u32 baseOrder, u32 maxOrder, float x, float y, float clipWidth, float clipHeight);

extern "C" DllExport u32 CKLBUIClip_getOrder(s32* pCtx);
extern "C" DllExport void CKLBUIClip_setOrder(s32* pCtx, u32 order);

extern "C" DllExport u32 CKLBUIClip_getMaxOdr(s32* pCtx);
extern "C" DllExport void CKLBUIClip_setMaxOdr(s32* pCtx, u32 maxodr);

extern "C" DllExport float CKLBUIClip_getWidth(s32* pCtx);
extern "C" DllExport void CKLBUIClip_setWidth(s32* pCtx, float width);

extern "C" DllExport float CKLBUIClip_getHeight(s32* pCtx);
extern "C" DllExport void CKLBUIClip_setHeight(s32* pCtx, float height);

extern "C" DllExport void CKLBUIClip_setPosition(s32* pCtx, float x, float y);

extern "C" DllExport void CKLBUIClip_setSize(s32* pCtx, float width, float height);

//======================================================================================
//#include "CKLBMapTask.h"

extern "C" DllExport s32* CKLBMapTask_create(s32* pParent, u32 allocSize, s32* asset);

extern "C" DllExport s32 CKLBMapTask_getX(s32* pCtx);

extern "C" DllExport s32 CKLBMapTask_getY(s32* pCtx);

extern "C" DllExport u32 CKLBMapTask_getOrder(s32* pCtx);

extern "C" DllExport u32 CKLBMapTask_getOffsetLayer(s32* pCtx);

extern "C" DllExport u32 CKLBMapTask_getOffsetPerLine(s32* pCtx);

extern "C" DllExport u32 CKLBMapTask_getWidth(s32* pCtx);

extern "C" DllExport u32 CKLBMapTask_getHeight(s32* pCtx);

extern "C" DllExport s32 CKLBMapTask_getCoordX(s32* pCtx);

extern "C" DllExport s32 CKLBMapTask_getCoordY(s32* pCtx);

extern "C" DllExport u32 CKLBMapTask_getMode(s32* pCtx);

extern "C" DllExport s32* CKLBMapTask_getAsset(s32* pCtx);

extern "C" DllExport s32 CKLBMapTask_getCenterX(s32* pCtx);

extern "C" DllExport s32 CKLBMapTask_getCenterY(s32* pCtx);

extern "C" DllExport float CKLBMapTask_getScale(s32* pCtx);

extern "C" DllExport s32 CKLBMapTask_getTileWidth(s32* pCtx);

extern "C" DllExport s32 CKLBMapTask_getHalfTileHeight(s32* pCtx);

extern "C" DllExport void CKLBMapTask_cmdMapSetViewPort(s32* pCtx, u32 width, u32 height, s32 x, s32 y, u32 baseRenderPriority, u32 priorityOffsetPerLayer, u32 priorityOffsetPerLine);

extern "C" DllExport void CKLBMapTask_cmdMapSetCoordinate(s32* pCtx, float x, float y, s32 mode);

extern "C" DllExport void CKLBMapTask_cmdMapSetCenterView(s32* pCtx, float fx, float fy);

extern "C" DllExport void CKLBMapTask_cmdMapSetDefaultTile(s32* pCtx, u32 layer, s32* asset, u32 argb);

extern "C" DllExport void CKLBMapTask_cmdMapSetZoom(s32* pCtx, float scale);

extern "C" DllExport void CKLBMapTask_getScrCoord(s32* pCtx, float fx, float fy, float* resX, float* resY);

extern "C" DllExport void CKLBMapTask_getLogCoord(s32* pCtx, float fx, float fy, float* resX, float* resY);

extern "C" DllExport void CKLBMapTask_cmdMapSetTileID(s32* pCtx, u32 layer, u32 tileX, u32 tileY, u32 tileID);

extern "C" DllExport void CKLBMapTask_cmdMapSetAreaID(s32* pCtx, u32 layer, u32 tileID, u32 x1, u32 y1, u32 x2, u32 y2);

// Camera methods
extern "C" DllExport s32* CKLBMapTask_cameraCreate(s32* pCtx);

extern "C" DllExport void CKLBMapTask_cameraDelete(s32* pCtx, s32* pLuaCam);

extern "C" DllExport void CKLBMapTask_cameraMove(s32* pCtx, s32* pLuaCam, s32 x, s32 y);

extern "C" DllExport void CKLBMapTask_cameraMoveWithCoord(s32* pCtx, s32* pLuaCam, s32 x, s32 y, s32 mode);

extern "C" DllExport void CKLBMapTask_cameraSet(s32* pCtx, s32* pLuaCam);

//======================================================================================
//#include "CKLBNetAPI.h"

extern "C" DllExport s32* CKLBNetAPI_create(s32* pParent, s32* apiurl, s32* client_version, s32* consumer_key, s32* application_id,u32 session_max, s32* region);

extern "C" DllExport bool CKLBNetAPI_startUp(s32* pCtx, s32* loginID, s32* password, s32* invite, u32 timeout, u32* session);

extern "C" DllExport bool CKLBNetAPI_login(s32* pCtx, s32* loginID, s32* password, u32 timeout, u32* session);

extern "C" DllExport bool CKLBNetAPI_cancel(s32* pCtx, u32 uniq);

extern "C" DllExport void CKLBNetAPI_cancelAll(s32* pCtx);

extern "C" DllExport void CKLBNetAPI_debugHdr(s32* pCtx, bool debugflag);

extern "C" DllExport bool CKLBNetAPI_sendHTTP(s32* pCtx, s32* apiURL, s32* json, u32 timeout, bool passVersionCheck, u32* session);

extern "C" DllExport bool CKLBNetAPI_watchMaintenance(s32* pCtx, u32 timeout, u32* session);

extern "C" DllExport void CKLBNetAPI_genCmdNumID(s32* pCtx, s32* body, int serial, s32* buf);

//======================================================================================
//#include "CKLBMapGroup.h"

extern "C" DllExport s32* CKLBMapGroup_create(s32* pParent, u32 order, float x, float y, float z, bool scaleEnable);

extern "C" DllExport u32 CKLBMapGroup_getOrder(s32* pCtx);

extern "C" DllExport float CKLBMapGroup_getMapX(s32* pCtx);
extern "C" DllExport void CKLBMapGroup_setMapX(s32* pCtx, float x);

extern "C" DllExport float CKLBMapGroup_getMapY(s32* pCtx);
extern "C" DllExport void CKLBMapGroup_setMapY(s32* pCtx, float y);

extern "C" DllExport float CKLBMapGroup_getMapZ(s32* pCtx);
extern "C" DllExport void CKLBMapGroup_setMapZ(s32* pCtx, float z);

extern "C" DllExport void CKLBMapGroup_setPosition(s32* pCtx, float x, float y, float z);

//======================================================================================
//#include "CKLBUnitTask.h"

extern "C" DllExport s32* CKLBUnitTask_create(s32* pParent, s32* unitname, bool bMove);

extern "C" DllExport void CKLBUnitTask_getPosition(s32* pCtx, s32* x, s32* y, s32* z, u32* dir);

extern "C" DllExport s32* CKLBUnitTask_getClass(s32* pCtx);

extern "C" DllExport u32 CKLBUnitTask_getType(s32* pCtx);
extern "C" DllExport void CKLBUnitTask_setType(s32* pCtx, u32 type);

extern "C" DllExport u64 CKLBUnitTask_getDbId(s32* pCtx);

extern "C" DllExport u32 CKLBUnitTask_getOrder(s32* pCtx);

extern "C" DllExport bool CKLBUnitTask_getVisible(s32* pCtx);
extern "C" DllExport void CKLBUnitTask_setVisible(s32* pCtx, bool visible);

extern "C" DllExport void CKLBUnitTask_cmdSetLogicalPosition(s32* pCtx, float x, float y, float z, u32 dir, s32* optJSON);

extern "C" DllExport void CKLBUnitTask_cmdRealize(s32* pCtx, s32* optJSON);

extern "C" DllExport s32* CKLBUnitTask_cmdExecuteQuery(s32* pCtx, s32* pQuery , float* pDistance);

extern "C" DllExport bool CKLBUnitTask_assignAI(s32* pCtx, u32 aiDefinition);

extern "C" DllExport s32* CKLBUnitTask_getAIObject(s32* pCtx);

//======================================================================================
//#include "CKLBUIVariableItem.h"

extern "C" DllExport s32* CKLBUIVariableItem_create(s32* pParent, u32 order, float x, float y, float width, float height, s32* asset);

extern "C" DllExport u32 CKLBUIVariableItem_getOrder(s32* pCtx);
extern "C" DllExport void CKLBUIVariableItem_setOrder(s32* pCtx, u32 order);

extern "C" DllExport s32* CKLBUIVariableItem_getAsset(s32* pCtx);

extern "C" DllExport float CKLBUIVariableItem_getWidth(s32* pCtx);
extern "C" DllExport void CKLBUIVariableItem_setWidth(s32* pCtx, float width);

extern "C" DllExport float CKLBUIVariableItem_getHeight(s32* pCtx);
extern "C" DllExport void CKLBUIVariableItem_setHeight(s32* pCtx, float height);

extern "C" DllExport bool CKLBUIVariableItem_changeAsset(s32* pCtx, s32* assetName);

extern "C" DllExport void CKLBUIVariableItem_changeUV(s32* pCtx, float x, float y, float width, float height);

extern "C" DllExport void CKLBUIVariableItem_resetUV(s32* pCtx);

extern "C" DllExport bool CKLBUIVariableItem_setMaskAsset(s32* pCtx, s32* asset);

//======================================================================================
//#include "CKLBStoreService.h"

extern "C" DllExport s32* CKLBStoreService_create();

extern "C" DllExport void CKLBStoreService_buyItems(s32* pCtx, s32* item);

extern "C" DllExport void CKLBStoreService_getProducts(s32* pCtx, s32* json, bool currency);

//======================================================================================
//#include "CKLBWorld.h"

extern "C" DllExport s32* CKLBWorld_getPointUnit(s32 x, s32 y);
extern "C" DllExport s32* CKLBWorld_getUnitByID(s32* dbID);
extern "C" DllExport bool CKLBWorld_doEvent(s32* pSrcTask, s32* pDstTask, s32* pUserTask, s32* pOppoTask, u32 eventID, s32* additionalParams, u32 additionalParamsCount);
extern "C" DllExport void CKLBWorld_killAllUnit();
extern "C" DllExport u32 CKLBWorld_getUnitListByClass(s32* unitClass, s32** pIds, s32** pTasks, u32 maxLength);
extern "C" DllExport s32 CKLBWorld_getUnitAll(s32* targetUser, s32*  battleId, s32 callbackIndex);
extern "C" DllExport s32 CKLBWorld_getUnitClass(s32* unitClass, s32* strId, s32* targetUser, s32 callbackIndex);
extern "C" DllExport s32 CKLBWorld_getUnitTableAll(s32* unitTable, s32 callbackIndex);
extern "C" DllExport void CKLBWorld_setOrderParam(u32 baseOrder, float orderReso);
extern "C" DllExport void CKLBWorld_unitFreeze(bool bFreeze);
//======================================================================================
//#include "CKLBAsyncLoader.h"

extern "C" DllExport s32* CKLBAsyncLoader_create(s32* pParentTask, s32** assets, u32 count, u32 datasetID);

extern "C" DllExport u32 CKLBAsyncLoader_getTotalCount(s32* pCtx);

extern "C" DllExport u32 CKLBAsyncLoader_getProcessCount(s32* pCtx);

//======================================================================================
//======================================================================================
//======================================================================================
//======================================================================================
//======================================================================================
//======================================================================================
//#include "CKLBLuaLibKEY.h"

extern "C" DllExport int CKLBLuaLibKEY_genUserID(s32* buf, u32 size);

extern "C" DllExport int CKLBLuaLibKEY_genUserPW(s32* user_id, s32* buf, u32 size);

extern "C" DllExport bool CKLBLuaLibKEY_setSecureID(s32* service_name, s32* user_id);

extern "C" DllExport bool CKLBLuaLibKEY_setSecurePW(s32* service_name, s32* passwd);

extern "C" DllExport int CKLBLuaLibKEY_getSecureID(s32* service_name, s32* buf, u32 size);

extern "C" DllExport int CKLBLuaLibKEY_getSecurePW(s32* service_name, s32* buf, u32 size);

extern "C" DllExport bool CKLBLuaLibKEY_delSecureID(s32* service_name);

extern "C" DllExport bool CKLBLuaLibKEY_delSecurePW(s32* service_name);

//======================================================================================
//#include "CKLBLuaLibRES.h"

extern "C" DllExport void CKLBLuaLibRES_dumpSceneGraph(s32* ptr);

extern "C" DllExport void CKLBLuaLibRES_dumpRendering(bool detailed);

extern "C" DllExport void CKLBLuaLibRES_dumpAssets();

extern "C" DllExport void CKLBLuaLibRES_dumpDataSet();

extern "C" DllExport void CKLBLuaLibRES_dumpTexturePacker(bool detailed);

extern "C" DllExport void CKLBLuaLibRES_dumpGeometryCost(bool detailed);

//======================================================================================
//#include "CKLBLuaLibENG.h"

extern "C" DllExport bool CKLBLuaLibENG_isRelease();

extern "C" DllExport s32* CKLBLuaLibENG_getPlatform();

extern "C" DllExport void CKLBLuaLibENG_getNanoTime(s32* milli, s32* nano);

extern "C" DllExport void CKLBLuaLibENG_startNanoTime(u32 idx);

extern "C" DllExport void CKLBLuaLibENG_endNanoTime(u32 idx, s32* milli, s32* nano);

extern "C" DllExport u32 CKLBLuaLibENG_getFrameID();


//======================================================================================
//#include "CKLBLuaEnv.h"

extern "C" DllExport void CKLBLuaEnv_cmdLogging(s32* msg);

extern "C" DllExport void CKLBLuaEnv_cmdExit();

extern "C" DllExport void CKLBLuaEnv_cmdSystemInfo(s32* width, s32* height);

extern "C" DllExport void CKLBLuaEnv_cmdSystemReboot();

//======================================================================================
//#include "CKLBLuaLibFONT.h"

extern "C" DllExport s32* CKLBLuaLibFONT_createFont(s32 size, s32* fontname);

extern "C" DllExport void CKLBLuaLibFONT_removeFont(s32* fontobj);

extern "C" DllExport void CKLBLuaLibFONT_cmdGetTextInfo(s32* str, s32* font, s32* pReturnInfo);


//======================================================================================
//#include "CKLBLuaLibASSET.h"

extern "C" DllExport void CKLBLuaLibASSET_getImageSize(s32* asset_name, s32* pReturnWidth, s32* pReturnHeight);

extern "C" DllExport void CKLBLuaLibASSET_getBoundSize(s32* asset_name, float* pReturnWidth, float* pReturnHeight);

extern "C" DllExport void CKLBLuaLibASSET_getAssetInfo(s32* asset_name, s32* pReturnImgWidth, s32* pReturnImgHeight, float* pReturnBoundWidth, float* pReturnBoundHeight);

//======================================================================================
//#include "CKLBLuaLibDATA.h"

extern "C" DllExport s32* CKLBLuaLibDATA_cmdCreateData(u32 dataSetID);

extern "C" DllExport bool CKLBLuaLibDATA_cmdRegistData(s32* pDataSet, s32* name_asset, u32* pReturnHandle);

extern "C" DllExport void CKLBLuaLibDATA_cmdDelete(s32* pDataSet);

//======================================================================================
//#include "CKLBLuaLibGL.h"

extern "C" DllExport bool CKLBLuaLibGL_GLClearColor(float r, float g, float b, float a);

extern "C" DllExport void CKLBLuaLibGL_GLSetResolution(int width, int height);

extern "C" DllExport void CKLBLuaLibGL_SGGetGuardBand(float* leftBorder, float* rightBorder, float* topBorder, float* bottomBorder);

extern "C" DllExport void CKLBLuaLibGL_SGSetGuardBand(float leftBorder, float rightBorder, float topBorder, float bottomBorder);

extern "C" DllExport bool CKLBLuaLibGL_GLCreateScreenAsset(s32* name);

extern "C" DllExport bool CKLBLuaLibGL_GLDoScreenShot(s32* name);

extern "C" DllExport void CKLBLuaLibGL_GLFreeScreenAsset(s32* name);

//======================================================================================
//#include "CKLBLuaLibUI.h"

extern "C" DllExport void CKLBLuaLibUI_calcPosition(float x, float y, float w, float h, u32 mask, float* out_rx, float* out_ry);

//======================================================================================
//#include "CKLBLuaLibBIN.h"

extern "C" DllExport s32* CKLBLuaLibBIN_open(s32* bin_asset);
extern "C" DllExport void CKLBLuaLibBIN_close(s32* pBIN);

extern "C" DllExport bool CKLBLuaLibBIN_peek(s32* pBIN, s32 offset, s32* out_value);
extern "C" DllExport bool CKLBLuaLibBIN_peek_u16(s32* pBIN, s32 offset, u32* out_value, bool f_bigendian);
extern "C" DllExport bool CKLBLuaLibBIN_peek_u32(s32* pBIN, s32 offset, u32* out_value, bool f_bigendian);

//======================================================================================
//#include "CKLBLuaLibTASK.h"
//#include "CKLBTask.h"

extern "C" DllExport void Task_kill(s32* pTask);

extern "C" DllExport bool Task_isKill(s32* pTask);

extern "C" DllExport void Task_setStageTask(s32* pTask);

extern "C" DllExport void Task_clearStageTask();

extern "C" DllExport void Task_setPause(s32* pTask, bool bPause, bool bRecursive);

extern "C" DllExport void Task_setManagerPause(bool bPause);
extern "C" DllExport void Task_interposeTimer(s32* pTask, s32* pTimer);
//======================================================================================
//#include "CKLBLuaLibSOUND.h"

extern "C" DllExport s32* CKLBLuaLibSOUND_cmdSoundOpen(s32* snd_asset, bool f_bgm);

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundClose(s32* pSnd);

extern "C" DllExport u32 CKLBLuaLibSOUND_removeSoundAll();

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundPlay(s32* pSnd, u32 fade_msec, float tgtVol, float globalVol);

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundStop(s32* pSnd, u32 fade_msec, float tgtVol);

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundVolume(s32* pSnd, float volume);

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundPan(s32* pSnd, float pan);

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundPause(s32* pSnd);

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundResume(s32* pSnd);

extern "C" DllExport void CKLBLuaLibSOUND_cmdSoundSeek(s32* pSnd, s32 millisec);

extern "C" DllExport s32  CKLBLuaLibSOUND_cmdSoundTell(s32* pSnd);

extern "C" DllExport s32  CKLBLuaLibSOUND_cmdSoundState(s32* pSnd);

extern "C" DllExport void CKLBLuaLibSOUND_cmdVolumeBGM(float volume);

extern "C" DllExport void CKLBLuaLibSOUND_cmdVolumeSE(float volume);

extern "C" DllExport s32 CKLBLuaLibSOUND_cmdGetLength(s32* pSnd);

extern "C" DllExport void CKLBLuaLibSOUND_cmdSetFade(s32* pSnd, s32 millisec, float tgtVol);

extern "C" DllExport bool CKLBLuaLibSOUND_cmdSoundSetBufSize(s32* pSnd, s32 value);

//======================================================================================
//#include "CKLBLuaLibDB.h"

extern "C" DllExport s32* CKLBLuaLibDB_dbopen(s32* db_asset, bool b_write, bool b_create);

extern "C" DllExport void CKLBLuaLibDB_dbclose(s32* pDB);

extern "C" DllExport void CKLBLuaLibDB_closeAll();

extern "C" DllExport s32* CKLBLuaLibDB_query(s32* pDB, s32* sqlQuery, int* nbEntries);

//======================================================================================
//#include "CKLBLuaLibAI.h"

extern "C" DllExport void CKLBLuaLibAI_setActive(s32* pAIobj, bool active);

extern "C" DllExport void CKLBLuaLibAI_resetRule(s32* pAIobj);

extern "C" DllExport s32 CKLBLuaLibAI_getProp(s32* pAIobj, u32 index);
extern "C" DllExport void CKLBLuaLibAI_setProp(s32* pAIobj, u32 index, s32 value);

extern "C" DllExport void CKLBLuaLibAI_delQuery(s32* pQuery);
extern "C" DllExport void CKLBLuaLibAI_delQueryAll();

//======================================================================================
//#include "CKLBLuaLibAPP.h"

extern "C" DllExport bool CKLBLuaLibAPP_callApplication(s32 type, s32* addr, s32* subject, s32* body);

//======================================================================================
//#include "CKLBPauseCtrl.h"

extern "C" DllExport s32* CKLBPauseCtrl_create(s32* pParent);

//======================================================================================
//#include "CKLBLuaLibLANG.h"

extern "C" DllExport bool CKLBLuaLibLANG_addString(s32* id, s32* str);

extern "C" DllExport s32* CKLBLuaLibLANG_getString(s32* id);

extern "C" DllExport void CKLBLuaLibLANG_removeString(s32* id);

extern "C" DllExport bool CKLBLuaLibLANG_useDB(s32* dbFile, s32* table, s32* keyF, s32* valueF, s32* groupF);

extern "C" DllExport bool CKLBLuaLibLANG_loadGroup(s32* groupId);


//======================================================================================
//#include "CKLBLuaLibDEBUG.h"

extern "C" DllExport void CKLBLuaLibDEBUG_startMenu(u32 maxCount, s32* caption, s32* key);
extern "C" DllExport void CKLBLuaLibDEBUG_addItem(u32 mode, s32* caption, s32* key, s32 min, s32 max, s32 value, s32** items, u32 itemsCount);
extern "C" DllExport void CKLBLuaLibDEBUG_endMenu();
extern "C" DllExport void CKLBLuaLibDEBUG_removeMenu(s32* key);
/*
//======================================================================================
//#include ".h"

//======================================================================================
//#include ".h"

//======================================================================================
//#include ".h"

//======================================================================================
//#include ".h"

//======================================================================================
//#include ".h"

//======================================================================================
//#include ".h"
*/

#endif //__EXPORT_LIST_H__
