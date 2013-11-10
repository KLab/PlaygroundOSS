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
#ifndef CKLBUIDragIcon_h
#define CKLBUIDragIcon_h

#include "CKLBUITask.h"
#include "CKLBModalStack.h"

/*!
* \class CKLBUIDragIcon
* \brief Drag Icon Task Class
* 
* CKLBUIDragIcon allows to create a Task owning an image and answering the Drag Events.
* The image can be scalled and/or moved while draging.
* A specific drag area can also be defined to limitate the DragIcon possible received events.
*/
class CKLBUIDragIcon : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIDragIcon>;
private:
	CKLBUIDragIcon();
	virtual ~CKLBUIDragIcon();
public:
	u32 getClassID();

	typedef struct {
		s32 x;
		s32 y;
		s32 width;
		s32 height;
	} AREA;

	static CKLBUIDragIcon * create(CKLBUITask * pParent, CKLBNode * pNode,
									u32 order, float x, float y, AREA * tap_area,
									const char * asset, const char * drag_asset,
									s32 drag_order_offset, float drag_alpha, 
									float center_x, float center_y, 
									const char * callback, u32 flags = 0);

	bool initUI (CLuaState& lua);
	void execute(u32 deltaT);
	void dieUI  ();

	int commandUI(CLuaState& lua, int argc, int cmd);

	inline void setEnable(bool enable) {
		if(m_enable != enable) {
			// 現在と異なる状態を設定した場合、
			// 許可/不許可にかかわらず一旦操作をリセットする
			m_state  = S_WAIT;
			m_enable = enable;
			if(enable) {
				REFRESH_A;
			} else {
				RESET_A;
			}
		}
	}

	float			m_dragScaleX;
	float			m_dragScaleY;
	u32				m_flags;
	u32				m_order;
	const char *	m_callBack;
	const char *	m_dragAsset;
	const char *	m_asset;

	inline u32	        getOrder    ()						{	return m_order;			}
	inline const char*  getAsset    ()					    {	return m_asset;			}
	inline const char*  getDrag     ()					    {	return m_dragAsset;		}
	inline u32	        getFlags    ()						{	return m_flags;			}
	inline void         setFlags    (u32 flag)				{	m_flags = flag;			}
	inline void         setCallBack (const char* callback)	{	setStrC(m_callBack, callback);	}
	inline const char*  getCallBack ()				        {	return m_callBack;		}
	inline bool         getEnable   ()						{	return m_enable;		}

	inline void         setDragScaleX(float scale)			{	
		m_dragScaleX = scale;
		m_pDragNode->setScale(m_dragScaleX, m_dragScaleY);
	}
	inline float        getDragScaleX()					    {	return m_dragScaleX;	}

	inline void         setDragScaleY(float scale)			{	
		m_dragScaleY = scale;	
		m_pDragNode->setScale(m_dragScaleX, m_dragScaleY);
	}
	inline float        getDragScaleY()					    {	return m_dragScaleY;	}

	inline void         setDragArea(AREA area)				{	m_clip = area;			}

private:
	bool init(CKLBUITask * pParent, CKLBNode * pNode,
				u32 order, float x, float y, AREA * tap_area,
				const char * asset, const char * drag_asset,
				s32 drag_order_offset, float drag_alpha, 
				float center_x, float center_y, 
				const char * callback, u32 flags = 0);

	bool initCore(
					u32 order, float x, float y, AREA * tap_area,
					const char * asset, const char * drag_asset,
					s32 drag_order_offset, float drag_alpha, 
					float center_x, float center_y, 
					const char * callback, u32 flags = 0);

	typedef enum {
		S_WAIT,	//!< 待機中
		S_DRAG,	//!< ドラッグ中
	} STATE;


	bool		is_tap      (int x, int y);
	bool		get_area    (CLuaState& lua, int argp, AREA& area);
	bool		drag_clip   (s32 drx, s32 dry, s32 * x, s32 * y);

	AREA					m_clip;		// ドラッグ可能範囲
	AREA					m_area;		// アイコン操作エリア

	// 相対座標から絶対座標を求めるためのオフセット位置
	int						m_ofs_x;
	int						m_ofs_y;

	// ドラッグ中表示される半透明アイコンの中心位置(タップ位置に相当する部分)
	float					m_center_x;
	float					m_center_y;

	int						m_tid;		// 操作に使用されるポイントのID
	STATE					m_state;

	bool					m_enable;			// false の間は操作を許可しない。
	//bool					m_bModalEnable;		// モーダルスタックによる許可状態

	CKLBNode			*	m_pIconNode;	// アイコンとしての表示
	CKLBNode			*	m_pDragNode;	// ドラッグ中指についてくる表示

	u32						m_iconHandle;
	u32						m_dragHandle;

	CKLBModalStack			m_modalStack;	// モーダルスタック

	static	PROP_V2			ms_propItems[];
};

#endif // CKLBUIDragIcon_h
