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
#ifndef CKLBUIScore_h
#define CKLBUIScore_h

#include "CKLBUITask.h"
#include "CKLBScoreNode.h"

/*!
* \class CKLBUIScore
* \brief Score Task Class
* 
* CKLBUIScore is designed for managing Score.
* It handles 10 assets, one for each digit and uses it to display a score.
* It also manages the animation going with the two different scores transitions.
*/
class CKLBUIScore : public CKLBUITask
{
	friend class CKLBTaskFactory<CKLBUIScore>;
private:
	CKLBUIScore();
	virtual ~CKLBUIScore();
public:
	// プロパティのインデックス
	enum PROP_ID{
		PR_ORDER,
		PR_ODOFF,
		PR_STEP_X,
		PR_STEP_Y,
		PR_COLS,
		PR_FILLZERO,
		PR_ANIM,
		PR_VALUE,
		PR_ALIGN,
		PR_COUNTCLIP,


		PR_TEX_0,
		PR_TEX_1,
		PR_TEX_2,
		PR_TEX_3,
		PR_TEX_4,
		PR_TEX_5,
		PR_TEX_6,
		PR_TEX_7,
		PR_TEX_8,
		PR_TEX_9,
	};

	enum {
		// 以下の値を変更する場合は CompositeManagement.cpp 等、
		// 外部のツールから与えられる値との間で整合を取ること。
		ALIGN_RIGHT  = 0,
		ALIGN_CENTER = 1,
		ALIGN_LEFT   = 2,
	};

	static CKLBUIScore * create(CKLBUITask * pParent, CKLBNode * pNode,
								u32 order, s32 order_offset,
								float x, float y, const char ** tex_table,
								float stepX, float stepY, int column, 
								bool fillzero, bool anim_flags, u32 align = ALIGN_RIGHT,
								bool countclip = false);
	bool initUI     (CLuaState& lua);
	u32 getClassID  ();

	void execute    (u32 deltaT);
	void dieUI      ();

	int commandUI   (CLuaState& lua, int argc, int cmd);

	inline u32	getValue()				{ return m_value;		}
	inline void setValue(u32 value)     {
		if (value != m_value) {
			m_value = value;
			REFRESH_A;
		}
	}

	inline u32 getValueFloat()			{ return m_value;		}
	inline void setValueFloat(float value, u32 prec)	{
		if ((value != m_fValue) || (prec != m_fPrec)) {
			m_fValue = value;
			m_fPrec  = prec;
			REFRESH_B;
		}
	}
	
	inline u32	getOrder()				{ return m_order;		}
	inline void setOrder(u32 order)		{
		if(order != m_order) {
			m_order = order;
			REFRESH_A;
		}
	}

	inline u32	getOrderOffset()		{ return m_orderOffset;	}

	inline s32	getStepX()				{ return m_stepX;		}
	inline void setStepX(s32 stepX)		{
		if(stepX != m_stepX) {
			m_stepX = stepX;
			REFRESH_A;
		}
	}

	inline s32	getStepY()				{ return m_stepY;		}
	inline void setStepY(s32 stepY)		{
		if(stepY != m_stepY) {
			m_stepY = stepY;
			REFRESH_A;
		}
	}

	inline u32	getColumn()				{ return m_column;		}
	inline void setColumn(u32 cols)		{
		if(cols != m_column) {
			m_column = cols;
			REFRESH_A;
		}
	}

	inline bool getFillZero()			{ return m_bFillZero;	}
	inline void setFillZero(bool fZero)	{
		if(fZero != m_bFillZero) {
			m_bFillZero = fZero;
			REFRESH_A;
		}
	}

	inline bool getAnim()				{ return m_anim;		}

	inline u32	getAlign()				{ return m_align;		}
	inline void setAlign(u32 align)		{
		if(align != m_align) {
			m_align = align;
			REFRESH_A;
		}
	}

	inline bool getCountClip()			{ return m_bCountClip;	}
	inline void setCountClip(bool b)	{
		if(b != m_bCountClip) {
			m_bCountClip = b;
			REFRESH_A;
		}
	}
	
	inline const char*	getTex0     ()  { return m_asset[0]; }
	inline const char*	getTex1     ()  { return m_asset[1]; }
	inline const char*	getTex2     ()  { return m_asset[2]; }
	inline const char*	getTex3     ()  { return m_asset[3]; }
	inline const char*	getTex4     ()  { return m_asset[4]; }
	inline const char*	getTex5     ()  { return m_asset[5]; }
	inline const char*	getTex6     ()  { return m_asset[6]; }
	inline const char*	getTex7     ()  { return m_asset[7]; }
	inline const char*  getTex8     ()  { return m_asset[8]; }
	inline const char*  getTex9     ()  { return m_asset[9]; }
	inline const char** getTextures ()  { return m_asset; 	 }

	void setDot(const char* dotAsset, s32 width, s32 height);
	const char* getDot();

	inline void setEnterAnimation(s32 milliSecondsPlayTime, s32 timeShift, bool onlyChange, u32 type, u32 affected, const float* arrayParam) {
		m_pScoreNode->setEnterAnimation(milliSecondsPlayTime, timeShift, onlyChange, type, affected, arrayParam);
	}

	inline void setExitAnimation(s32 milliSecondsPlayTime, s32 timeShift, bool onlyChange, u32 type, u32 affected, const float* arrayParam) {
		m_pScoreNode->setExitAnimation(milliSecondsPlayTime, timeShift, onlyChange, type, affected, arrayParam);
	}
private:

bool init(CKLBUITask * pParent, CKLBNode * pNode,
					u32 order, s32 order_offset, float x, float y, 
					const char ** tex_table, float stepX, float stepY, int column, 
					bool fillzero, bool anim_flag, u32 align, bool countclip);
	bool initCore(  u32 order, s32 order_offset, float x, float y, 
					const char ** tex_table, float stepX, float stepY, int column, 
					bool fillzero, bool anim_flag, u32 align, bool countclip);

	int countColumn(u32 value);

	u32		m_value;
	float	m_fValue;
	s32		m_dotStepX;
	s32		m_dotStepY;
	u32		m_order;
	u32		m_orderOffset;
	s32		m_stepX;
	s32		m_stepY;
	u32		m_column;
	u32		m_align;
	bool	m_bFillZero;
	bool	m_anim;
	bool	m_bScoreUpdate;
	bool	m_bCountClip;
	u8		m_fPrec;

	const char *        m_asset[10];

	CKLBScoreNode	*	m_pScoreNode;
	CKLBImageAsset	*	m_numTex[10];
	u32					m_handle;

	int					m_width;
	int					m_height;

	int					m_maxvalue;
	
	static PROP_V2 		ms_propItems[];
};


#endif // CKLBUIScore_h
