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
#ifndef CKLBUIList_h
#define CKLBUIList_h

#include "CKLBUITask.h"
#include "CKLBUISystem.h"
#include "CKLBNodeAnimPack.h"
#include "CKLBFormIF.h"
#include "CKLBModalStack.h"
#include "CKLBScrollBarIF.h"
#include "CompositeManagement.h"
#include "DataSet_JSonDB.h"
#include "CKLBTouchPad.h"
#include "CKLBPropertyBag.h"
#include "CKLBDragCallbackIF.h"

class CKLBUIList;

class CKLBListDrag : public CKLBDragCallbackIF
{
public:
	CKLBListDrag(CKLBUIList * parent, const char * funcname);
	virtual ~CKLBListDrag();
	void callback(PAD_ITEM::TYPE type, int tap_x, int tap_y, int mv_x, int mv_y);

private:
	CKLBUIList		*	m_pParent;
};

/*!
* \class CKLBUIList
* \brief List Task Class
* 
* CKLBUIList allows to create and manage lists of items.
* It comes with its own scrollbar.
* Items can be added dynamically and managed easily through
* the several developped APIs.
* 
*/
class CKLBUIList : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIList>;
	friend class CKLBListDrag;
private:
	CKLBUIList();
	virtual ~CKLBUIList();
public:
	virtual u32 getClassID();

	enum {
		LIST_FLAG_BOTTOM = 0x00000001,	// アイテムを並べる基準点を、水平リストならばクリッピングの下端、
										// 垂直リストならばクリッピングの右端に変更する

		LIST_FLAG_MODAL  = 0x00000002,	// リスト全体をモーダルコントロールとして表示する
	};

	// アイテム保持モード定数
	enum {
		LIST_ITEM_NORMAL,
		LIST_ITEM_DYNAMIC,
		LIST_ITEM_FLYWEIGHT,
	};



	static CKLBUIList * create(CKLBUITask * pParent, CKLBNode * pNode,
								u32 base_order, u32 max_order,
								float x, float y, float clip_width, float clip_height,
								int default_line_step, bool vertical = true,
								const char * callback = NULL, u32 optional_flags = 0);

	bool initUI     (CLuaState& lua);
	int commandUI   (CLuaState& lua, int argc, int cmd);

	void execute    (u32 deltaT);
	void dieUI      ();

	inline void setLoop(bool bLoop) {
		if(m_bLoop != bLoop) {
			m_posUpdate  = true;
			m_itemUpdate = true;
			m_scrBar.setOverScroll(bLoop || !m_chklimit);
		}
		m_bLoop = bLoop;	
	}

	bool setItemMode(int mode, const char * dynamicCallback = NULL);

	bool useScrollBar(u32 order, bool side, int lineWeight,
						const char * image, int min_slider_size,
						const char * callback,
						u32 colorNormal, u32 colorSelect, bool active, bool hide_mode = false, bool short_hide = true);

	bool useScrollBarByProperty(CKLBPropertyBag * pProp, u32 priorityOffset);

	bool selectScrollMgr(const char * manager_name, int argc = 0, int * params = NULL);
	bool selectScrollMgrByProperty(CKLBPropertyBag * pProp);


	void setSplineLayout(float* array_, u32 setupBitmask, u32 curveLengthPixel);

private:
	bool init(CKLBUITask * pParent, CKLBNode * pNode,
				u32 base_order, u32 max_order,
				float x, float y, float clip_width, float clip_height,
				int default_line_step, bool vertical,
				const char * callback, u32 optional_flags);

	bool initCore(
				u32 base_order, u32 max_order,
				float x, float y, float clip_width, float clip_height,
				int default_line_step, bool vertical,
				const char * callback, u32 optional_flags);

public:
	virtual void setVisible         (bool visible);

	inline u32	getWidth			()					{ return m_width;			}
	inline u32	getHeight			()					{ return m_height;			}
	inline int	getStepX			()					{ return m_stepX;			}
	inline int	getStepY			()					{ return m_stepY;			}
	inline u32	getOrder			()					{ return m_basePriority;	}
	inline u32	getMaxOrder			()					{ return m_endPriority;		}
	inline bool getVertical			()					{ return m_vertical;		}
	inline u32	getItems			()					{ return m_itemCnt;			}
	inline s32	getMarginTop		()					{ return m_marginTop;		}
	inline s32	getMarginBottom		()					{ return m_marginBottom;	}
	inline bool getDefaultScroll	()					{ return m_defScroll;		}
	
	inline void setWidth			(u32 width)			{ 
		if(m_width != width || m_clipWidth != width) {
			m_width = width;
			m_clipWidth = width;
			REFRESH_A;
		} 
	}
	inline void setHeight			(u32 height)		{ 
		if(m_height != height || m_clipHeight != height) {
			m_height = height;	
			m_clipHeight = height;	
			REFRESH_A; 
		}
	}
	inline void setStepX			(int x)				{ 
		if(m_stepX != x) {
			m_stepX = x;
			REFRESH_A; 
		}
	}
	inline void setStepY			(int y)				{ 
		if(m_stepY != y) {
			m_stepY = y;
			REFRESH_A; 
		}
	}
	inline void setOrder			(u32 order)			{ 
		if(m_basePriority != order) {
			m_basePriority = order;	
			REFRESH_A; 
		}
	}
	inline void setMaxOrder			(u32 order)			{ 
		if(m_endPriority != order) {
			m_endPriority = order;
			REFRESH_A; 
		}
	}
	inline void setVertical			(bool vertical)		{ 
		if(m_vertical != vertical) {
			m_vertical = vertical;
			REFRESH_A; 
		}
	}
	inline void setMarginTop		(s32 top)			{
		if (m_marginTop != top) {
			m_marginTop = top;
			REFRESH_A;
			REFRESH_B;
		}
	}
	inline void setMarginBottom		(s32 bottom)		{
		if (m_marginBottom != bottom) {
			m_marginBottom = bottom;
			REFRESH_A;
			REFRESH_B;
		}
	}
	inline void setDefaultScroll	(bool scroll)		{ 
		if(m_defScroll != scroll) {
			m_defScroll = scroll;	
			REFRESH_A; 
		}
	}

	void setDragRect    (s32 left, s32 top, s32 right, s32 bottom);

	int  cmdItemAdd     (CLuaState& lua, int argc);
	bool cmdItemAdd     (const char* assetName);
	bool cmdItemAdd     (const char* assetName, int step, int id = -1);
	int  cmdItemInsert  (CLuaState& lua, int argc);
	bool cmdItemInsert  (const char* assetName, int idx);
	bool cmdItemInsert  (const char* assetName, int idx, int step, int id);
	bool cmdItemRemove  (int idx);
	void cmdItemMove    (int src, int dst);
	int  cmdItemRemoveSelection (CLuaState& lua, int argc);
	bool cmdItemRemoveSelection (int* idxList, u32 nbItems);

	void cmdFWModeConfig(int itemStep, int maxItems);
	void cmdFWItemAdd   (/* TODO */);
	void cmdFWItemInsert(/* TODO */);

	void cmdSetMargin   (int top, int bottom);
	bool cmdSetItemMode (int mode, const char* dynamicCallback);

	bool cmdAddRecords  (int insIdx, const char* tpform, u32 sizeTemplate, const char* dbrecs, u32 sizeDBRec, int step);

	int  cmdSetPosition (int pos, int dir);
	int  cmdSetInitial  (int);
	int cmdSetDragRect  (CLuaState& lua, int argc);
	int  cmdGetPosition ();

	void cmdSetItemID   (int index, int id);
	int  cmdSearchID    (int id);

	void cmdSetItemPos  (int mode, int idx, int offset);

	void cmdChangeStep  (int index, int step);

	void cmdSetLimitClip(bool chklimit, const char* limitCallback);
	int  cmdGetLimit    ();
	bool cmdSetLimitArea(int limitArea);

	bool cmdExistNode   (int index, const char* name);
	int  cmdUpdateNode  (CLuaState& lua, int argc);
	void cmdInputEnable (bool enable);

	void cmdAnimCallback    (const char* callback);
	bool cmdAnimationItem   (int index, const char* name, bool blend);
	bool cmdAnimationAll    (const char* name, bool blend);
	bool cmdItemAnimSkip    (int index, const char* name);
	bool cmdAllAnimSkip     (const char* name);

	bool cmdSelectScrMgr    (const char* name, int* params, int nb);
	bool cmdScrMgrCallback  (const char* callback);
	void cmdSetGroup        (const char* group_name);
	void cmdSetClip         (u32 orderBegin, u32 orderEnd, s16 clipX, s16 clipY, s16 clipWidth, s16 clipHeight);
	int  cmdGetItemCount    (CLuaState& lua, int argc);
	int  cmdGetItemForm     (CLuaState& lua, int argc);

	int  setPosition        (int pos);
	void updateEnable       ();

private:
	u32                     m_width;
	u32                     m_height;
	s32                     m_marginTop;
	s32                     m_marginBottom;
	bool                    m_defScroll;

	CKLBNodeAnimPack		m_animpack;		// アニメーションパッケージ
	CKLBFormIF				m_formIF;		// Formパッケージ
	CKLBModalStack			m_modalStack;	// モーダルスタックパッケージ

	// リスト自体の操作許可情報
	bool					m_bModalEnable;

	// clip情報
	u32						m_basePriority;	// クリッピング基点プライオリティ
	u32						m_endPriority;	// クリッピング終了プライオリティ

	float					m_clipX;
	float					m_clipY;
	int						m_clipWidth;
	int						m_clipHeight;

	// list配置情報
	bool					m_vertical;		// 縦配置フラグ(true:縦スクロール/false:横スクロール)
	bool					m_chklimit;		// 上限/下限制約をつける
	bool					m_touchenable;	// 入力取得許可/禁止

	int						m_stepX;		// 横方向のアイテム原点間隔(縦配置のときは0)
	int						m_stepY;		// 縦方向のアイテム原点間隔(横配置のときは0)

	int						m_listLength;	// リストの長さ
	int						m_flags;		// 動作オプションフラグ

	// Listの親ノード
	// 全てのアイテムは、このノードの下にぶらさがる。
	CKLBNode			*	m_pCtrlNode;
	int						m_ctrlX;
	int						m_ctrlY;

	void*					m_clipHandle;

	float*					m_layoutTable;

	float*					m_layoutTableXY;
	float*					m_layoutTableScale;
	float*					m_layoutTableRotation;
	float*					m_layoutTableAlpha;
	float*					m_layoutTableRGB;
	float*					m_layoutTablePriority;
	float*					m_layoutTableLayout;

	u32						m_curveLength;
	u16						m_layoutInterlaceSize;

	const char			*	m_pGroupName;

	struct LISTITEM {

		LISTITEM		*	prev;	// 前の項目
		LISTITEM		*	next;	// 次の項目

		bool				enable;	// 項目操作の許可禁止

		const char		*	jsonp;	// dynamic モードで使用。アイテム生成フォームのJSON
		u32					jsonlen;

		CKLBNode		*	form;	// 項目フォームのノード
		u32					handle;	// フォームアセットのハンドル

		SFormCtrlList		ctrl;	// コントロールリスト

		int					step;	// 項目の占有する幅
		int					pos;	// アイテムが現在存在する場所
		int					index;	// アイテムのindex
		int					id;		// アイテムに与えられたID

		// このアイテムで起動されたタスクの一覧
		CKLBRegistedTaskList	taskList;

		LISTITEM()
			: prev  (NULL)
            , next  (NULL)
            , enable(false)
            , jsonp (NULL)
            , jsonlen   (0)
            , form  (NULL)
            , handle(0)
            , ctrl  ()
            , step  (0)
            , pos   (0)
            , index (0)
            , id    (0)
            , taskList  ()
		{}
	};

	LISTITEM		*	m_lstBegin;
	LISTITEM		*	m_lstEnd;

	LISTITEM		*	m_killBegin;
	LISTITEM		*	m_killEnd;

	int					m_itemCnt;			// 登録アイテム数
	int					m_scrollPos;		// スクロール位置
	bool				m_enableEvents;
	bool				m_force;

	int					m_scrOffset;		// スクロール位置オフセット
	int					m_clipSize;			// クリップサイズ

	bool				m_itemUpdate;		// アイテム更新フラグ
	bool				m_posUpdate;		// 表示位置更新フラグ

	bool				m_bLoop;			// ループ動作モード

	CKLBListDrag	*	m_dragCallback;		// ドラッグ時のコールバック関数名
	const char		*	m_limitCallback;	// 終端ページ入りコールバック関数名
	bool				m_limitCalled;		// 既に終端コールバックを呼んだか否か
	int					m_limitAreaSize;	// 両端超過コールバックを呼びだす領域のサイズ

	const char		*	m_dynamicCallback;	// ダイナミックモードでアイテムの再生が終了した後に呼び出すコールバック

	int					m_dragID;
	int					m_dragX;
	int					m_dragY;
	s32					m_leftDrag;
	s32					m_rightDrag;
	s32					m_topDrag;
	s32					m_bottomDrag;
	s32					m_dragDistance;

	CKLBScrollBarIF		m_scrBar;			// スクロールバー

	// デフォルトスクロールで使用する。
	int					m_defaultPrePos;
	int					m_defaultDragPos;
	bool				m_bTaped;

	// アイテム保持モード
	int					m_itemMode;

	struct FLYWEIGHT {
		int			maxitems;	// 最大保持アイテム数
		int			itemstep;	// 
	};
	FLYWEIGHT			m_flyweight;

	static PROP_V2		ms_propItems[];


private:
	void        updateIndex ();

	bool        setClip     (u32 orderBegin, u32 orderEnd,
					         s16 clipX, s16 clipY, s16 clipWidth, s16 clipHeight);

	bool        resetClip   (u32 orderBegin, u32 orderEnd, s16 clipX, s16 clipY, s16 clipWidth, s16 clipHeight, bool forceClip);

	LISTITEM *  create_item (const char * json, u32 jsonLen, int id = -1, CKLBCompositeAsset * pAsset = NULL, IDataSource * pSource = NULL);
	void        delete_item (LISTITEM * pItem, bool kill_child = true);

	bool        load_itemform   (LISTITEM * pItem, const char * json, u32 jsonLen, CKLBCompositeAsset * pOrgAsset = NULL, IDataSource * pSource = NULL);
	bool        unload_itemform (LISTITEM * pItem, bool kill_child = true);
	
	inline void set_item_id (LISTITEM * pItem, int id = -1) { pItem->id = id; }

	int         get_item_index_by_id(int id);

	LISTITEM *  getItemByID (int id);

	LISTITEM *  getItemByIndex(int index);

	// 指定されたLuaスタック上のパラメータをJSON文字列に変換する
	const char * toJSON(CLuaState& lua, int index, u32& size);

	// 指定されたLuaスタック上のパラメータを元に、テーブルにぶら下げるアイテムツリーを生成する。
	bool itemInsertUniversal(LISTITEM * posItem, int step, CLuaState& lua, int index, int id = -1);

	// JSONをもとにアイテムツリーを作り、
	// posItem とその直前のアイテムの間に挟む
	bool itemInsert(LISTITEM * posItem, int step, const char * json, u32 jsonLen, int id = -1,
					CKLBCompositeAsset * pAsset = 0, IDataSource * pSource = 0);

	// 指定されたアイテムを削除し、間を詰める
	void itemDelete(LISTITEM * posItem);

	// 削除予約されたアイテムインスタンスをすべて削除する
	void itemCleanUp(bool kill_child = true);

	// アイテムを挿入/破棄した後の処理として、各アイテムの配置を再計算する。
	void itemRealloc();

	// 直線型リストの表示位置再設定
	void setStraightPosition();

	// スプライン型リストの表示位置再設定
	void setSplinePosition();

	// タッチパッドイベント処理
	void touchpadEvent();

	
	s32 fromScreenDistanceToSplineDistance(s32 posPixelSpace);

	// Interpolation from spline lookup table for vec1,vec2,vec3
	void interpolate1(float* array_, float sub, float& res);
	void interpolate2(float* array_, float sub, float& resA, float& resB);
	void interpolate3(float* array_, float sub, float& resA, float& resB, float& resC);

	// デフォルトスクロール処理
	static void defaultScroll(void * pData, PAD_ITEM::TYPE type, int dragX, int dragY, int mvX, int mvY);

public:
	bool itemAddInsert(LISTITEM * posItem, const char* assetName, int step, int id);
	
	static const char * toJSON(const char* param, u32& size);
};


#endif // CKLBUIList_h
