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
#ifndef CKLBFormIF_h
#define CKLBFormIF_h

#include "CLuaState.h"
#include "CKLBNode.h"
#include "CKLBUISystem.h"

/*
	UI_Form や UI_List の UPDATE_NODE コマンド用サブコマンド解釈クラス
 */
class CKLBFormIF
{
public:
	enum {
		// 標準ノードサブコマンド
		FORM_NODE_POINTER,		// ノードポインタ取得
		FORM_NODE_RECURSIVE,	// ノード再帰処理
		FORM_NODE_TRANS,		// 位置指定
		FORM_NODE_SCALE,		// 倍率指定(x, y)
		FORM_NODE_ROT,			// 回転角指定(deg)
		FORM_NODE_COLOR,		// RGBA指定
		FORM_NODE_VISIBLE,		// 表示/非表示指定
		FORM_NODE_ORDER,		// プライオリティ
		FORM_NODE_GET_ORDER,	// プライオリティ取得
		FORM_NODE_TASK,			// 対応するUIタスク取得


		// CKLBUIElement 対象コマンド
		FORM_UIE_SET_ENABLED,	// 有効/無効
		FORM_UIE_GET_ENABLED,	
		FORM_UIE_SET_ASSET,		// assetを変更

		// CKLBUISelectable 対象コマンド
		FORM_UIS_SET_CLICK,			// クリック反応領域を再設定
		FORM_UIS_SET_STICK,			// checkbox の状態を設定する
		FORM_UIS_SET_RADIO,
		FORM_UIS_GET_STICK,			// checkbox の状態を取得する
		FORM_UIS_SET_CALLBACK,

		// CKLBUIContainer 対象コマンド
		FORM_CONT_VIEWOFFSET,		// View offset
		FORM_CONT_GET_RADIO_VALUE,

		// CKLBUITextBox 対象コマンド
		FORM_TEXT_SET,
		FORM_TEXT_GET,

		// CKLBUIWebView 対象コマンド
		FORM_WEB_SET_URI,
		FORM_WEB_GET_URI,

		// CKLBLabelNode 対象コマンド
		FORM_LBL_SET_TEXT,		// ラベルのテキスト変更
		FORM_LBL_GET_TEXT,		// ラベルのテキスト取得
	};

	CKLBFormIF(CKLBTask * pOwner = 0);
	virtual ~CKLBFormIF();

	bool isExistNode        (CKLBNode * pParent, const char * name);
	int  updateNode         (CLuaState& lua, int argc, int base, CKLBNode * pParent, int nodeIndex, int subcmd, void * item = NULL, int index = 0);
	void removeAssetByHandle(void * item);
private:
	bool updateStandardNode (CLuaState& lua, int argc, int base, int subcmd, CKLBNode * pNode, int& ret, void * item, int index);
	bool updateUIElement    (CLuaState& lua, int argc, int base, int subcmd, CKLBNode * pNode, int& ret, void * item, int index);
	bool updateUISelectable (CLuaState& lua, int argc, int base, int subcmd, CKLBNode * pNode, int& ret, void * item, int index);
	bool updateUIContainer  (CLuaState& lua, int argc, int base, int subcmd, CKLBNode * pNode, int& ret, void * item, int index);
	bool updateUITextEdit   (CLuaState& lua, int argc, int base, int subcmd, CKLBNode * pNode, int& ret, void * item, int index);
	bool updateUIWebView    (CLuaState& lua, int argc, int base, int subcmd, CKLBNode * pNode, int& ret, void * item, int index);
	bool updateLabelNode    (CLuaState& lua, int argc, int base, int subcmd, CKLBNode * pNode, int& ret, void * item, int index);
private:
	CKLBAsset * updateAsset (CLuaState& lua, CKLBUIElement * pElement, const char * name, CKLBUIElement::ASSET_TYPE mode, void * item);

	bool nodeRecursive      (CLuaState& lua, const char * funcname, CKLBNode * pNode, int index = 0, int level = 0);

	// SET_ASSET コマンドによって差し替えた asset は、
	// refCount を管理するため、独自にハンドルを保持する必要がある。
	struct FORM_ASSET {
		FORM_ASSET				*	prev;
		FORM_ASSET				*	next;

		void					*	item;	// そのassetを設定したアイテム(Listの場合)
		CKLBUIElement			*	node;	// 対象ノード
		CKLBAsset				*	asset;	// 現在の保持asset
		u32							handle;	// 上記 asset の保持 handle
		CKLBUIElement::ASSET_TYPE	mode;	// 指定モード
	};

	FORM_ASSET		*	m_begin;
	FORM_ASSET		*	m_end;

	CKLBTask		*	m_pOwner;
};

#endif // CKLBFormIF_h
