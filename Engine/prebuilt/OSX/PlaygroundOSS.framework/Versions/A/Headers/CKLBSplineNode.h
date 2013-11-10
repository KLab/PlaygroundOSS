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

#ifndef __SPLINE_PLAYER__
#define __SPLINE_PLAYER__

#include "CKLBNode.h"

/*!
* \class CKLBSplineNode
* \brief Spline Node Class
* 
* CKLBSplineNode gives the possibility to easily associate a Spline Animation 
* with an UITask.
*/
class CKLBSplineNode : public CKLBNode {
public:
	static const u32 ANM_X_COORD_0			= 1<<1;
	static const u32 ANM_Y_COORD_1			= 1<<2;
	static const u32 ANM_SCALE_COORD_2		= 1<<3;
	static const u32 ANM_R_COLOR_3			= 1<<4;
	static const u32 ANM_G_COLOR_4			= 1<<5;
	static const u32 ANM_B_COLOR_5			= 1<<6;
	static const u32 ANM_A_COLOR_6			= 1<<7;
	static const u32 ANM_SCALEX_COORD_7		= 1<<8;
	static const u32 ANM_SCALEY_COORD_8		= 1<<9;
	static const u32 ANM_ROTATION_COORD_9	= 1<<10;

	static const u32 ANM_PING_PONG			= 0x10000000;
	static const u32 ANM_LOOPBIT			= 0x20000000;
	static const u32 ANM_REMOVESCENE		= 0x40000000;

	static const u32 MODIFY_X				= 0;
	static const u32 MODIFY_Y				= 1;
	static const u32 MODIFY_SCALE			= 2;
	static const u32 MODIFY_R				= 3;
	static const u32 MODIFY_G				= 4;
	static const u32 MODIFY_B				= 5;
	static const u32 MODIFY_A				= 6;
	static const u32 MODIFY_ROT				= 7;
	static const u32 MODIFY_PRIORITY		= 8;
	static const u32 MODIFY_LAYOUT			= 9; // Used in UI List only.
	static const u32 MODIFY_TOTALCOUNT		= MODIFY_LAYOUT + 1;

	static const u32 ANM_LINEAR				= 1;
	static const u32 ANM_SWING				= 2;
	static const u32 ANM_EASEINQUAD			= 3;
	static const u32 ANM_EASEOUTQUAD		= 4;
	static const u32 ANM_EASEINOUTQUAD		= 5;
	static const u32 ANM_EASEINCUBIC		= 6;
	static const u32 ANM_EASEOUTCUBIC		= 7;
	static const u32 ANM_EASEINOUTCUBIC		= 8;
	static const u32 ANM_EASEINQUART		= 9;
	static const u32 ANM_EASEINBACK			= 27;
	static const u32 ANM_EASEOUTBACK		= 28;
	static const u32 ANM_EASEINOUTBACK		= 29;

	CKLBSplineNode						();
	virtual ~CKLBSplineNode				();

	void			setCounter			(u32* refCounterPtr);
	void			play				();
	void			stop				();
	void			endAnimation		(s32* keys);

	void			setAnimation		(s32 milliSecondsPlayTime, s32 timeShift, u32 type, s32* keys, u32 keycount, u32 affected, float* arrayParam);

	bool			setParamCount		(u8 splineCount, u8 maxKeyCount);
	void			setTarget			(u8 splineIndex, u8 targetParameter);
	void			addKeys				(u8 splineIndex, u32 time, s16 value);
	void			addKeysFixed		(u8 splineIndex, u32 time, s32 fixed16Value);
	void			generateAnimation	();

	virtual
	void			animate				(u32 deltaTimeMilli);

	virtual u32		getClassID			()	{ return CLS_KLBSPLINENODE; }

	void			setTag				(void* tag) { m_tag = tag; }	
	void*			getTag				()	{ return m_tag; }

private:
	void			cleanSplines();

	s32 			interpolateKey		(s32 interpolation, s32* vectorData);
	s32*			m_aKeyVector;
	float			m_base[18];

	s32				m_startTime;

	u32				m_applyMask;
	s32				m_timeMultiplier;
	s32				m_uiLooptime;

	s32				m_uiLocalTime;

	s32				m_uiTotalKeyCount;
	s32				m_uiLastLocalTime;

	u32*			m_refCounter;

	u8*				m_target;
	s32*			m_allKeys;
	u32*			m_splinesKeyCount;
//	s32*			m_splineLocalTime;
	u16*			m_splineLastKey;
	s32**			m_splines;
	void*			m_tag;
	s32				m_uiTotalTime;
	u32				m_uiMaxKeyCount;
	u32				m_uiSplineCount;

	u16				m_uiLastKey;
	u8				m_mode;
	bool			m_loop;
	bool			m_pingpong;
};

#endif
