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
//

#ifndef __SCORE_NODE__
#define __SCORE_NODE__

#include "CKLBSplineNode.h"

/**
	- Animate previous character
	- Animate next character
	- Animate node itself
 */

/*!
* \class CKLBScoreNode
* \brief Score Specialized Node Class
* 
* CKLBScoreNode is in charge of animating a Score.
* First, it animates the previous digit.
* The is animates the next digt.
* Finnaly, it animates the node itself.
*/
class CKLBScoreNode : public CKLBNode {
public:
	CKLBScoreNode						();
	virtual ~CKLBScoreNode				();

	bool init							(	u32						basePriority,
											s32						oldNumberPriorityOffset,
											CKLBImageAsset* 		char0_9[10],
											s32 					stepX,
											s32 					stepY,
											u32 					score_length,
											bool					fillWithZero,
											bool					animAll);

	void setDot							(	CKLBImageAsset*			dotAsset, s32 width, s32 height );

	void setAnimationInternal			(	bool	isNew,
											s32		milliSecondsPlayTime,
											s32		timeShift,
											bool	onlyChange,
											u32		type,
											u32		affected,
											const float* arrayParam);

	void setEnterAnimation				(s32 milliSecondsPlayTime, s32 timeShift, bool onlyChange, u32 type, u32 affected, const float* arrayParam);
	void setExitAnimation				(s32 milliSecondsPlayTime, s32 timeShift, bool onlyChange, u32 type, u32 affected, const float* arrayParam);
	void setScore						(u32 value, bool animFirstTime);
	void setScoreFloat					(float value, u32 dotPosition, bool animFirstTime);
	void update							();
	inline u32		getScore			()	{ return m_uiScore; }
	virtual u32		getClassID			()	{ return CLS_KLBSCORENODE; }

	virtual	void	setPriority			(u32 order);
private:
	void setDotActive					(u32 position);
	void setScoreInternal				(u32 value, bool animFirstTime);
	void reAssignAnim					(u32 idx);

	#define __SCORE_LEN_MAX__	(10)
	CKLBImageAsset*			m_font			[11];
	CKLBSplineNode*			m_scoreOldNode	[__SCORE_LEN_MAX__];
	CKLBSplineNode*			m_scoreNewNode	[__SCORE_LEN_MAX__];

	CKLBSprite*				m_dotSprite;
	CKLBNode*				m_dotNode;
	float					m_widthDot;
	float					m_heightDot;

	struct AnimInfo {
		s32 m_milliSecondsPlayTime;
		s32 m_timeShift;
		u32 m_type;
		float m_Anim[16];		
		u32 m_affected;
		bool m_hasAnim;
	};

	AnimInfo				m_animInfo[2];

	s32						m_stepX;
	s32						m_stepY;
	u32						m_uiScore;
	s32						m_oldNumberPriorityOffset;
	u8						m_oldScore		[__SCORE_LEN_MAX__];
	u8						m_default;
	u8						m_scoreLength;
	u8						m_DotPosition;
	u8						m_prevDotPosition;
	bool					m_newAnimated;
	bool					m_oldAnimated;
	bool					m_animAll;
	bool					m_bScoreChange;
};

#endif
