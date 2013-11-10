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
#ifndef CKLBUIProgressBar_h
#define CKLBUIProgressBar_h

#include "CKLBUITask.h"

/*!
* \class CKLBUIProgressBar
* \brief Progress Bar Task Class
* 
* CKLBUIProgressBar allows to create dynamic Progress Bars.
*/
class CKLBUIProgressBar : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIProgressBar>;
private:
	CKLBUIProgressBar();
	virtual ~CKLBUIProgressBar();
public:
	// プロパティのインデックス
	enum PROP_ID{
		P_WIDTH,
		P_HEIGHT,
		P_ORDER,
		P_VERT,
		P_ANIM,
		P_START,
		P_END_POS,
		P_IMG_EMPTY,
		P_IMG_FULL,
		P_VALUE,
		P_IMG_FILTER,
		P_FILTER_VISIBLE,
		P_FILTER_COLOR,
	};

	static CKLBUIProgressBar *
		create(CKLBUITask * pParent, CKLBNode * pNode,
							u32 order, float x, float y, float width, float height,
							const char * full_image, const char * empty_image,
							s32 start_pix = -1, s32 end_pix = -1, int anim = 0, bool vert = false,
							const char * barfilter_image = NULL);

	bool initUI  (CLuaState& lua);
	int commandUI(CLuaState& lua, int argc, int cmd);

	void execute(u32 deltaT);
	void dieUI  ();

	bool setFilterAnim(bool bFilterAnim, u32 col1, u32 col2, u32 freq);
	
	// A : Perform animation
	// B : Perform geometry

	inline u32  getOrder()				{ return m_uiOrder;		}
	inline void	setOrder(u32 order)		{
		if (order != m_uiOrder) {
			m_uiOrder = order;
			REFRESH_A;
		}
	}

	inline float getWidth()				{ return m_fWidth;		}
	inline void	 setWidth(float width)	{
		if (width != m_fWidth) {
			if(!m_isVertical) {
				if(m_startPixelF <= m_endPixelF) {
					m_endPixelF += width - m_fWidth;
				} else {
					m_startPixelF += width - m_fWidth;
				}
			}
			m_fWidth = width;
			REFRESH_D;
		}
	}

	inline float getHeight()             { return m_fHeight;		}
	inline void	 setHeight(float height) {
		if (height != m_fHeight) {
			if(m_isVertical) {
				if(m_startPixelF <= m_endPixelF) {
					m_endPixelF += height - m_fHeight;
				} else {
					m_startPixelF += height - m_fHeight;
				}
			}
			m_fHeight = height;
			REFRESH_D;
		}
	}

	inline bool	getVertical()			    { return m_isVertical;	}
	inline void	setVertical(bool vertical)  {
		if (m_isVertical != vertical) {
			m_isVertical = vertical;
			REFRESH_D;
		}
	}

	inline u32	getAnimTime()			{ return m_anim_length; }
	inline void	setAnimTime(u32 time)	{
		if (time != m_anim_length) {
			m_anim_length = time;
			REFRESH_B;
		}
	}

	inline float getStart()				{ return m_fStart;		}
	inline void	 setStart(float start)	{
		if (start != m_fStart) {
			m_fStart = start;
			m_fNormValue = (m_fValue - m_fStart) / (m_fEnd - m_fStart); 
			REFRESH_B;
		}
	}

	inline float getEnd()				{ return m_fEnd;		}
	inline void	 setEnd(float end)		{
		if (end != m_fEnd) {
			m_fEnd = end;
			m_fNormValue = (m_fValue - m_fStart) / (m_fEnd - m_fStart); 
			REFRESH_B;
		}
	}

	inline const char*  getImgEmpty()	{ return m_emptyImage;	}
	inline void         setImgEmpty(const char* empty_image)	{ 
		setStrC(m_emptyImage, empty_image); 
		setImg(true, empty_image); 
	}

	inline const char*  getImgFull()	{ return m_fullImage;	}
	inline void         setImgFull(const char* full_image)		{ 
		setStrC(m_fullImage, full_image); 
		setImg(false, full_image); 
	}

	inline float getValue()				{ return m_fValue;		}
	inline void	 setValue(float value)	{
		if (value != m_fValue) {
			m_fValue = value;
			m_fNormValue = (value - m_fStart) / (m_fEnd - m_fStart); 
			REFRESH_B;
		}
	}

	inline float getValueNormalized()	{ return m_fNormValue;	}
	
	inline const char*  getImgFilter()	{ return m_filterImage; }
	inline void         setImgFilter(const char* img_filter)	{ setStrC(m_filterImage, img_filter); /*TODO*/ }

	inline bool getFilterVisible()		{ return m_bFilterSW;	}
	void        setFilterVisible(bool visible);

	inline u32	getFilterColor()		{ return m_FilterCol; }
	void        setFilterColor(u32 argb);

	inline void reset()	{
		setValue(m_fStart);
		m_iTimeCnt = 0;
		m_nowRate = m_prevRate = m_fStart;
		m_lastValue = m_fStart;
		setBorder(m_fStart);
	}

	u32 getClassID();
private:
	bool setImg(bool isEmpty, const char* imageName);

	bool init(CKLBUITask * pParent, CKLBNode * pNode,
				u32 order, float x, float y, float width, float height,
				const char * full_image, const char * empty_image,
				s32 start_pix, s32 end_pix, int anim, bool vert,
				const char * barfilter_image);

	bool initCore(  u32 order, float x, float y, float width, float height,
					const char * full_image, const char * empty_image,
					s32 start_pix, s32 end_pix, int anim, bool vert,
					const char * barfilter_image);

	void setBorder					(float value);
	void setupProgressBarConstant	();

	enum {
		E_full,
		E_empty,
		E_filter,
	};
	CKLBImageAsset	*	m_pTex[3];		// [0]full / [1]empty / [2]filter

	CKLBDynSprite	*	m_pDynSprite;
	CKLBNode		*	m_pNode;

	CKLBTextureAsset *	m_pTexAsset;
	u32					m_texHandle;
	u32					m_uiOrder;
	float				m_fWidth;
	float				m_fHeight;
	u32					m_anim_length;
	float				m_fStart;
	float				m_fEnd;
	float				m_startPixelF;
	float				m_endPixelF;
	float				m_fValue;
	float				m_fNormValue;
	bool				m_isVertical;

	float				m_lastValue;
	float				m_prevRate;
	u32					m_iTimeCnt;		// アニメ用タイムカウンタ
	float				m_nowRate;		// アニメーション中の表示レート
	//GG//bool			m_bAnim;		// アニメーション中のフラグ
	u8					m_idx_a;
	u8					m_idx_b;
	u8					m_idx_c;		// filter用

	int					m_vertices;		// 頂点の数
	int					m_indices;		// インデックスの数
	

	bool				m_bFilterSW;	// フィルタ表示の ON/OFF
	u32					m_FilterCol;	// フィルタ用RGBA値
	float				m_filterXY[8];	// フィルタ表示用頂点

	bool				m_bColAnim;			// フィルタカラーアニメーション有効
	u32					m_animfreq;			// RGBAアニメーションの周期([ms])
	u32					m_animcol[2];		// RGBAアニメーションで補間する二つのカラー
	u32					m_animTime;			// タイムカウンタ

	bool				m_bCmdUpdate;

	const char		*	m_emptyImage;
	const char		*	m_fullImage;
	const char		*	m_filterImage;
	static PROP_V2		ms_propItems[];
	static const u16	ms_indices[];
};

#endif // CKLBUIProgressBar_h
