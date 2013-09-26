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
#include "CKLBFormIF.h"
#include "CKLBUtility.h"
#include "CKLBTextInputNode.h"
#include "CKLBWebViewNode.h"
#include "CKLBLabelNode.h"
#include "CKLBUITextInput.h"
#include "CKLBUILabel.h"
#include "CKLBUIWebArea.h"
;
CKLBFormIF::CKLBFormIF(CKLBTask * pOwner) : m_begin(NULL), m_end(NULL), m_pOwner(pOwner) {}
CKLBFormIF::~CKLBFormIF()
{
	// 破棄されるまでに保持された asset は自前で破棄する
	/*
	FORM_ASSET * pItem = m_begin;
	while(pItem) {
		FORM_ASSET * next = pItem->next;
		CKLBDataHandler::releaseHandle(pItem->handle);
		KLBDELETE(pItem);
		pItem = next;
	}
	*/
}

CKLBAsset *
CKLBFormIF::updateAsset(CLuaState& /*lua*/, CKLBUIElement * pElement, const char * assetName, CKLBUIElement::ASSET_TYPE	mode, void * /*item*/)
{
	CKLBAsset * pAsset;
	if (assetName) {
		pAsset = CKLBUtility::loadAsset(assetName, NULL, NULL);
		if(!pAsset) return NULL;
	} else {
		pAsset = NULL;
	}

	/*
	// 同じAsset を同じ Element が持っていた場合は何もせず終了
	FORM_ASSET * pItem;
	for(pItem = m_begin; pItem != 0; pItem = pItem->next) {
		if(pItem->node != pElement) continue;
		if(pItem->asset == pAsset && pItem->mode == mode) {
			// 全く同じノードに全く同じ asset を設定しようとしたので、何もしない
			CKLBDataHandler::releaseHandle(handle);
			return pAsset;
		}
		// 今assetを指定しようとしているノードが別のassetを割り当てられているので、
		// まずはこれを解放する
		break;
	}*/

	pElement->setAsset(pAsset, mode);

	/*
	// 以前に同じ node/mode に asset を設定していた項目があれば破棄
	if(pItem) {
		if(pItem->prev) {
			pItem->prev->next = pItem->next;
		} else {
			m_begin = pItem->next;
		}
		if(pItem->next) {
			pItem->next->prev = pItem->prev;
		} else {
			m_end = pItem->prev;
		}
		CKLBDataHandler::releaseHandle(pItem->handle);
		KLBDELETE(pItem);
	}
	pItem = KLBNEW(FORM_ASSET);
	pItem->node = pElement;
	pItem->asset = pAsset;
	pItem->handle = handle;
	pItem->item = item;

	// 末尾に追加
	pItem->next = 0;
	pItem->prev = m_end;
	if(pItem->prev) {
		pItem->prev->next = pItem;
	} else {
		m_begin = pItem;
	}
	m_end = pItem;
	*/
	return pAsset;
}

// 指定されたアイテム向けに差し替えられたassetを破棄する(UI_Listで使用。タスクを生かしたままitemを削除することがあるため)
void
CKLBFormIF::removeAssetByHandle(void * /*item*/)
{
	/*
	FORM_ASSET * pItem = m_begin;
	while(pItem) {
		FORM_ASSET * pNext = pItem->next;
		if(pItem->item == item) {
			if(pItem->prev) {
				pItem->prev->next = pItem->next;
			} else {
				m_begin = pItem->next;
			}
			if(pItem->next) {
				pItem->next->prev = pItem->prev;
			} else {
				m_end = pItem->prev;
			}
			CKLBDataHandler::releaseHandle(pItem->handle);
			KLBDELETE(pItem);
		}
		pItem = pNext;
	}*/
}

bool
CKLBFormIF::isExistNode(CKLBNode * pParent, const char * name)
{
	CKLBNode * pNode = pParent->search(name);
	return (pNode) ? true : false;
}

int
CKLBFormIF::updateNode(CLuaState& lua, int argc, int base, CKLBNode * pParent, int nodeIndex, int subcmd, void * item, int index)
{
	CKLBNode * pNode = NULL;
	if(lua.isString(nodeIndex)) {
		const char * name = lua.getString(nodeIndex);
		if (name) {
			pNode = pParent->search(name);
		}
		klb_assert(pNode, "Node not found: name = \"%s\"", name);
	} else {
		pNode = (CKLBNode *)lua.getPointer(nodeIndex);
	}
	int ret = 0;

	if(base > argc) {
		lua.retBoolean(false);
		return 1;
	}

	if (!pNode) {
		lua.retNil();
		return 1;
	}

	CKLBUITask* pTask		= pNode->getUITask();
	u32 classID;
	if (pTask) {
		classID = pTask->getClassID();
	} else {
		classID = pNode->getClassID();
	}

	// 対象のノードによって、可能な操作が異なる。
	bool result;
	switch(classID)
	{
	default:					result = updateStandardNode(lua, argc, base, subcmd, pNode, ret, item, index);	break;
	case CLS_KLBUIELEMENT:		result = updateUIElement(lua, argc, base, subcmd, pNode, ret, item, index);		break;
	case CLS_KLBUISELECTABLE:	result = updateUISelectable(lua, argc, base, subcmd, pNode, ret, item, index);	break;
	case CLS_KLBUICONTAINER:	result = updateUIContainer(lua, argc, base, subcmd, pNode, ret, item, index);	break;
	case CLS_KLBUILABEL:
	case CLS_KLBLABEL:			result = updateLabelNode(lua, argc, base, subcmd, pNode, ret, item, index);		break;
	case CLS_KLBTEXTEDIT:
	case CLS_KLBUITEXTINPUT:	result = updateUITextEdit(lua, argc, base, subcmd, pNode, ret, item, index);	break;
	case CLS_KLBUIWEBVIEW:
	case CLS_KLBWEBVIEW:		result = updateUIWebView(lua, argc, base, subcmd, pNode, ret, item, index);	break;
	}
	// ここまでで処理されたコマンドが無い場合、標準コマンドを処理する。
	if(!result) {
		// コマンドとして解釈できなかったので、falseを返す。
		lua.retBoolean(false);
		ret = 1;
	}
	// 戻り値に相当するものはすでにLuaスタックに積んであるはずなので、戻り値の数を返す。
	return ret;
}

bool
CKLBFormIF::updateStandardNode(CLuaState& lua, int argc, int base, int subcmd, CKLBNode * pNode, int& ret, void * /*item*/, int index)
{
	bool result = true;
	switch(subcmd)
	{
	default:
		{
			result = false;
		}
		break;
	case FORM_NODE_POINTER:
		{
			if(argc != base) {
				lua.retNil();
				ret = 1;
				break;
			}
			lua.retPointer(pNode);
			ret = 1;
		}
		break;

	case FORM_NODE_RECURSIVE:
		{
			if(argc != base + 1) {
				result = false;
				break;
			}
			const char * funcname = lua.getString(base + 1);	// コールバック名の取得
			result = nodeRecursive(lua, funcname, pNode, index);
		}
		break;

	case FORM_NODE_TRANS:
		{
			if(argc != (base + 2)) {
				result = false;
				break;
			}
			float x = lua.getFloat(base + 1);
			float y = lua.getFloat(base + 2);

			CKLBUITask* pTask = pNode->getUITask();
			if (pTask) {
				// Change next frame or current frame.
				if(pTask->isNewScriptModel()) {
					pTask->setX(x);
					pTask->setY(y);
				} else {
					int idxX = pTask->findProperty("x");
					int idxY = idxX + 1;
					pTask->setNum(idxX, x);
					pTask->setNum(idxY, y);
				}
				// Trick: we modify directly the node AND change the property.
				// If another property is modified later, it will force the value to be used. 
				// ==> Do not execute pTask->setInnerUpdate();
			}
			// But changes also RIGHT AWAY
			pNode->setTranslate(x, y);
		}
		break;
	case FORM_NODE_SCALE:
		{
			if(argc != base + 2) {
				result = false;
				break;
			}
			float scaleX = lua.getFloat(base + 1);
			float scaleY = lua.getFloat(base + 2);

			CKLBUITask* pTask = pNode->getUITask();
			if (pTask) {
				if(pTask->isNewScriptModel()) {
					pTask->setScaleX(scaleX);
					pTask->setScaleY(scaleY);
				} else {
					int idxX = pTask->findProperty("scaleX");
					int idxY = idxX + 1;
					pTask->setNum(idxX, scaleX);
					pTask->setNum(idxY, scaleY);
				}
				// Trick: we modify directly the node AND change the property.
				// If another property is modified later, it will force the value to be used. 
				// ==> Do not execute pTask->setInnerUpdate();
			}
			pNode->setScale(scaleX, scaleY);
		}
		break;
	case FORM_NODE_ROT:
		{
			if(argc != base + 1) {
				result = false;
				break;
			}
			float rot = lua.getFloat(base + 1);

			CKLBUITask* pTask = pNode->getUITask();
			if (pTask) {
				if(pTask->isNewScriptModel()) {
					pTask->setRotation(rot);
				} else {
					int idxRot = pTask->findProperty("rot");
					pTask->setNum(idxRot, rot);
				}
				pTask->setInnerUpdate();
				// Trick: we modify directly the node AND change the property.
				// If another property is modified later, it will force the value to be used. 
				// ==> Do not execute pTask->setInnerUpdate();
			}
			pNode->setRotation(rot);
		}
		break;
	case FORM_NODE_COLOR:
		{
			if(argc != base + 2) {
				result = false;
				break;
			}

			u32 alpha = lua.getInt(base + 1);
			u32 rgb   = lua.getInt(base + 2);

			CKLBUITask* pTask = pNode->getUITask();
			if (pTask) {
				if(pTask->isNewScriptModel()) {
					pTask->setAlpha(alpha);
					pTask->setArgb(rgb);
				} else {
					int idxcol = pTask->findProperty("alpha");	// Color just after !
					pTask->setInt(idxcol, alpha);
					pTask->setInt(idxcol+1, rgb);
				}
				pTask->setInnerUpdate();
			}

			SColorVector color;
			color.m_type = 0;

			for(int i = 0; i < 3; i++) {
				int col = 0xff & (rgb >> (16 - 8 * i));
				color.m_vector[i] = col / 255.0f;
			}
			color.m_vector[3] = (alpha & 0xff) / 255.0f;
			pNode->setColorMatrix(color);
		}
		break;
	case FORM_NODE_VISIBLE:
		{
			if(argc != base + 1) {
				result = false;
				break;
			}
			bool visible = lua.getBool(base + 1);

			CKLBUITask* pTask = pNode->getUITask();
			if (pTask) {
				pTask->setVisible(visible);
			} else {
				pNode->setVisible(visible);
			}
		}
		break;
	case FORM_NODE_ORDER:
		{
			if(argc != base + 1) {
				result = false;
				break;
			}
			int order = lua.getInt(base + 1);
			CKLBUITask* pTask = pNode->getUITask();
			if (pTask) {
				if(pTask->isNewScriptModel()) {
					pTask->setOrder(order);
					pTask->setInnerUpdate();
				} else {
					int idx_order = pTask->findProperty("order");
					if (idx_order >= 0) {
						pTask->setInt(idx_order, order);
						pTask->setInnerUpdate();
					}
				}
			}
			pNode->setPriority(order);
			pNode->markUpMatrix();
		}
		break;
	case FORM_NODE_GET_ORDER:
		{
			if(argc != base) {
				result = false;
				break;
			}
			int order;
			CKLBUITask* pTask = pNode->getUITask();
			if (pTask) {
				if(pTask->isNewScriptModel()) {
					order = pTask->getOrder();
				} else {
					int idx_order = pTask->findProperty("order");
					if (idx_order >= 0) {
						order = pTask->getInt(idx_order);
					} else {
						order = 0;
					}
				}
			} else {
				order = pNode->getPriority();
			}
			lua.retInt(order);
			ret = 1;
		}
		break;

	case FORM_NODE_TASK:
		{
			if(argc != base) {
				result = false;
				break;
			}
			CKLBUITask * pTask = pNode->getUITask();
			if(!pTask) {
				lua.retNil();
			} else {
				lua.retPointer(pTask);
			}
			ret = 1;
		}
		break;
	}
	return result;
}

bool
CKLBFormIF::updateUIElement(CLuaState& lua, int argc, int base, int subcmd, CKLBNode * pNode, int& ret, void * item, int index)
{
	CKLBUIElement * pElement = (CKLBUIElement *)pNode;
	bool result = true;
	switch(subcmd)
	{
	default:
		{
			result = updateStandardNode(lua, argc, base, subcmd, pNode, ret, item, index);
		}
		break;
	case FORM_UIE_SET_ENABLED:
		{
			if(argc != base + 1) {
				result = false;
				break;
			}
			bool enable = lua.getBool(base + 1);
			pElement->setEnabled(enable);
		}
		break;
	case FORM_UIE_GET_ENABLED:
		{
			if(argc != base) {
				result = false;
				break;
			}
			bool enable = pElement->isEnabled();
			lua.retBoolean(enable);
			ret = 1;
		}
		break;
	case FORM_UIE_SET_ASSET:
		{
			if(argc != base + 2) {
				result = false;
				break;
			}
			const char * asset = (!lua.isNil(base + 1)) ? lua.getString(base + 1) : NULL;
			const int mode = lua.getInt(base + 2);
			CKLBAsset * pAsset = updateAsset(lua, pElement, asset, (CKLBUIElement::ASSET_TYPE)mode, item);
			bool result = (!pAsset) ? false : true;
			lua.retBoolean(result);
			ret = 1;
		}
		break;
	}
	return result;
}


bool
CKLBFormIF::updateUISelectable(CLuaState& lua, int argc, int base, int subcmd, CKLBNode * pNode, int& ret, void * item, int index)
{
	CKLBUISelectable * pSelectable = (CKLBUISelectable *)pNode;
	bool result = true;
	switch(subcmd)
	{
	default:
		{
			// selectable専用コマンドに該当しなければ Element として処理する
			result = updateUIElement(lua, argc, base, subcmd, pNode, ret, item, index);
		}
		break;
	case FORM_UIS_SET_CLICK:
		{
			if(argc != 8) {
				result = false;
				break;
			}
			s32 x = lua.getInt(base + 1);
			s32 y = lua.getInt(base + 2);
			s32 width = lua.getInt(base + 3);
			s32 height = lua.getInt(base + 4);
			pSelectable->setClickLeft(x);
			pSelectable->setClickTop(y);
			pSelectable->setClickWidth(width);
			pSelectable->setClickHeight(height);
		}
		break;
	case FORM_UIS_SET_STICK:
		{
			if(argc != base + 1) {
				result = false;
				break;
			}
			bool stick = lua.getBool(base + 1);
			pSelectable->setSticked(stick);
		}
		break;
	case FORM_UIS_SET_RADIO:
		{
			if(argc != base + 1) {
				result = false;
				break;
			}
			int radioID = lua.getInt(base + 1);
			pSelectable->setRadio(radioID);
		}
		break;
	case FORM_UIS_GET_STICK:
		{
			if(argc != base) {
				result = false;
				break;
			}
			bool sticked = pSelectable->isSticked();
			lua.retBoolean(sticked);
			ret = 1;
		}
		break;
	case FORM_UIS_SET_CALLBACK:
		{
			if(argc != base + 1) {
				result = false;
				break;
			}

			const char* newFct = NULL;
			if (lua.isString(base+1)) {
				newFct = lua.getString(base + 1);
			}
			pSelectable->setLuaFunction(newFct);
		}
		break;
	}
	return result;
}

bool
CKLBFormIF::updateUIContainer(CLuaState& lua, int argc, int base, int subcmd, CKLBNode * pNode, int& ret, void * item, int index)
{
	CKLBUIContainer * pCont = (CKLBUIContainer *)pNode;
	bool result = true;
	switch(subcmd)
	{
	default:
		{
			result = updateUIElement(lua, argc, base, subcmd, pNode, ret, item, index);
		}
		break;
	case FORM_CONT_VIEWOFFSET:
		{
			if(argc != base + 2) {
				result = false;
				break;
			}
			s32 offX = lua.getInt(base + 1);
			s32 offY = lua.getInt(base + 2);
			pCont->setViewOffsetX(offX);
			pCont->setViewOffsetY(offY);
		}
		break;
	case FORM_CONT_GET_RADIO_VALUE:
		{
			if(argc != base) {
				result = false;
				break;
			}
			u32 value = pCont->getRadioValue();
			lua.retInt(value);
			ret = 1;
		}
		break;
	}
	return result;
}

bool
CKLBFormIF::updateUITextEdit(CLuaState& lua, int argc, int base, int subcmd, CKLBNode * pNode, int& ret, void * item, int index)
{
	CKLBUITask* pTask		= pNode->getUITask();
	CKLBUITextBox * pText	= (CKLBUITextBox *)pNode;

    // 2012-12-3(Mon)
    // pTaskが存在していない可能性が高いのでpTaskのNULLチェックを追加しました
	if ((pTask) && (pTask->getClassID() != CLS_KLBUITEXTINPUT)) {
		// Not valid
		pTask = NULL;
	}

	bool result = true;
	switch(subcmd)
	{
	default:
		{
			result = updateUIElement(lua, argc, base, subcmd, pNode, ret, item, index);
		}
		break;
	case FORM_LBL_GET_TEXT:	// Trick : label & text command backward compatible.
	case FORM_TEXT_GET:
		{
			/* Do not understand why return false for now.
			if(argc != base) {
				result = false;
				break;
			}*/
			const char * text;

			if (pTask) {
				text = ((CKLBUITextInput*)pTask)->getText();
			} else {
				text = pText->getText();
			}

			lua.retString(text);
			ret = 1;
		}
		break;
	case FORM_TEXT_SET:	// Trick : label & text command backward compatible.
	case FORM_LBL_SET_TEXT:
		{
			if(argc != base + 1) {
				result = false;
				break;
			}
			const char * text = lua.getString(base + 1);
			
			if (pTask) {
				((CKLBUITextInput*)pTask)->setText(text);
			} else {
				pText->setText((char *)text);
			}
		}
		break;
	}
	return result;
}

bool
CKLBFormIF::updateUIWebView(CLuaState& lua, int argc, int base, int subcmd, CKLBNode * pNode, int& ret, void * item, int index)
{
	CKLBUITask* pTask		= pNode->getUITask();
	bool result = true;
	switch(subcmd)
	{
	default:
		{
			result = updateUIElement(lua, argc, base, subcmd, pNode, ret, item, index);
		}
		break;
	case FORM_WEB_SET_URI:
		{
			if(argc != base + 1) {
				result = false;
				break;
			}
			const char * uri = lua.getString(base + 1);
			if (pTask) {
				CKLBUIWebArea* pWebTask = (CKLBUIWebArea*)pTask;
				pWebTask->setText(uri);
			} else {
				CKLBUIWebView * pWeb = (CKLBUIWebView *)pNode;
				pWeb->setText((char *)uri);
			}
		}
		break;
	case FORM_WEB_GET_URI:
		{
			if(argc != base) {
				result = false;
				break;
			}
			const char * uri;
			if (pTask) {
				CKLBUIWebArea* pWebTask = (CKLBUIWebArea*)pTask;
				uri = pWebTask->getText();
			} else {
				CKLBUIWebView * pWeb = (CKLBUIWebView *)pNode;
				uri = pWeb->getText();
			}

			lua.retString(uri);
			ret = 1;
		}
		break;
	}
	return result;
}

bool
CKLBFormIF::updateLabelNode(CLuaState& lua, int argc, int base, int subcmd, CKLBNode * pNode, int& ret, void * item, int index)
{
	CKLBLabelNode * pLabel = (CKLBLabelNode *)pNode;
	CKLBUITask* pTask		= pNode->getUITask();

    // pTaskが存在していない可能性が高いのでpTaskのNULLチェックを追加しました
	if ((pTask) && (pTask->getClassID() != CLS_KLBUILABEL)) {
		// Not valid
		pTask = NULL;
	}

	bool result = true;
	switch(subcmd)
	{
	default:
		{
			result = updateUIElement(lua, argc, base, subcmd, pNode, ret, item, index);
		}
		break;
	case FORM_TEXT_SET:	// Trick : label & text command backward compatible.
	case FORM_LBL_SET_TEXT:
		{
			if(argc != base + 1) {
				result = false;
				break;
			}
			const char * text = lua.getString(base + 1);
			if (pTask) {
				((CKLBUILabel*)pTask)->setText(text);
			} else {
				pLabel->setText((char *)text);
			}
		}
		break;
	case FORM_LBL_GET_TEXT:	// Trick : label & text command backward compatible.
	case FORM_TEXT_GET:
		{
			/*
			if(argc != base) {
				result = false;
				break;
			}*/
			const char * uri;
			if (pTask) {
				uri = ((CKLBUILabel*)pTask)->getText();
			} else {
				uri = pLabel->getText();
			}
			lua.retString(uri);
			ret = 1;
		}
		break;
	}
	return result;
}

bool
CKLBFormIF::nodeRecursive(CLuaState& lua, const char * funcname, CKLBNode * pNode, int index, int level)
{
	// タスクノードには適用されない
	if(pNode->getUITask()) return true;

	// 内部ノードについては lua の callback を呼ばない。
	if(pNode->isInternalNode()) return true;

	// LUA Specific feature
	CLua_Only_State& luaSpecific = (CLua_Only_State&)lua;
	luaSpecific.callback(funcname, "PPII", m_pOwner, pNode, index, level);

	// 子を走査
	CKLBNode * pChild = pNode->getChild();
	while(pChild) {
		nodeRecursive(lua, funcname, pChild, index, level + 1);
		pChild = pChild->getBrother();
	}
	return true;
}
