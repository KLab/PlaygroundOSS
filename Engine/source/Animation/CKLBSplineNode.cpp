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
#include "CKLBSplineNode.h"
#include "Message.h"

#define		VECTORSIZE	(4)

// ##########################################
//
// --- Instance ---
//
// ##########################################

CKLBSplineNode::CKLBSplineNode()
: CKLBNode          ()
, m_uiLocalTime     (0)
, m_applyMask       (0)
, m_uiLooptime      (16384)
, m_timeMultiplier  (0)
, m_aKeyVector      (NULL)
, m_loop            (false)
, m_uiTotalKeyCount (2)
, m_uiLastLocalTime (0)
, m_uiLastKey       (0)
, m_uiSplineCount   (0)
, m_allKeys         (NULL)
, m_target          (NULL)
, m_splines         (NULL)
, m_splinesKeyCount (NULL)
, m_splineLastKey   (NULL)
, m_tag             (NULL)
, m_refCounter      (NULL)
, m_pingpong        (false)
, m_startTime       (0)
{
	// Is not animated UNTIL animation is set.
	// this->m_status |= ANIMATED;
}

CKLBSplineNode::~CKLBSplineNode() {
	cleanSplines();

	// If doing animation and ref counter linked.
	// Note : CKLBNode make Visible(false) -> remove from animation already done.
	if (m_refCounter) {
		*m_refCounter = *m_refCounter - 1;
		m_refCounter  = NULL;
	}
}


static s32 SplineTbl1[8] = {
	// ===============
	//   Sample Key : Linear (1)
	// ===============
	// Key 1
		// Time, Value, Right, Left
			0,		0,	65536,		0,
	// Key 2
		16384,	65536,	    0,	-65536,
};

static s32 SplineTbl2[8] = {
	// ===============
	//   Sample Key : Swing (2)
	// ===============
	// Key 1
		// Time, Value, Right, Left
			0,		0,	65536,		0,
	// Key 2
		16384,	65536,	    0,	    0,
};

static s32 SplineTbl3[8] = {
	// ===============
	//   Sample Key : easeInQuad (3)
	// ===============
	// Key 1
		// Time, Value, Right, Left
			0,		0,	    0,		0,
	// Key 2
		16384,	65536,	    0, -65536,
};

static s32 SplineTbl4[8] = {
	// ===============
	//   Sample Key : easeOutQuad (4)
	// ===============
	// Key 1
		// Time, Value, Right, Left
			0,		0,	 65536,		0,
	// Key 2
		16384,	65536,	    0,      0,
};

static s32 SplineTbl5[8] = {
	// ===============
	//   Sample Key : easeInOutQuad (5)
	// ===============
	// Key 1
		// Time, Value, Right, Left
			0,		0,	    0,		0,
	// Key 2
		16384,	65536,	    0,      0,
};

static s32 SplineTbl6[8] = {
	// ===============
	//   Sample Key : easeInCubic (6)
	// ===============
	// Key 1
		// Time, Value, Right, Left
			0,		0,	    0,		0,
	// Key 2
		16384,	65536,	    0, -128000,
};

static s32 SplineTbl7[8] = {
	// ===============
	//   Sample Key : easeOutQuad (7)
	// ===============
	// Key 1
		// Time, Value, Right, Left
			0,		0,	 128000,	0,
	// Key 2
		16384,	65536,	    0,      0,
};

	// ===============
	//   Sample Key : easeInOutQuad (8)
	// ===============
	//
	// Need Multi key
	//

static s32 SplineTbl9[8] = {
	// ===============
	//   Sample Key : (9)
	// ===============
	// Key 1
		// Time, Value, Right, Left
			0,		0,	    0,	0,
	// Key 2
		16384,	65536,	    0, -192000,
};

static s32 SplineTbl27[8] = {
	// ===============
	//   Sample Key : (27)
	// ===============
	// Key 1
		// Time, Value, Right, Left
			0,		0,	-32768,	0,
	// Key 2
		16384,	65536,	    0,  -192000,
};

static s32 SplineTbl28[8] = {
	// ===============
	//   Sample Key : (28)
	// ===============
	// Key 1
		// Time, Value, Right, Left
			0,		0,	256000,	0,
	// Key 2
		16384,	65536,	    0,  0,
};

	// ===============
	//   Sample Key : (29)
	// ===============
	/*
	// Key 1
		// Time, Value, Right, Left
			0,		0,	256000,	0,
	// Key 2
		16384,	65536,	    0,  0,

		//
		8192,   32768,  
	 */

static s32 SplineTbl29[8] = {
	// ===============
	//   Sample Key : (29)
	// ===============
	// Key 1
		// Time, Value, Right, Left
			0,		0,	-65536,	0,
	// Key 2
		16384,	65536,	    0,  65536,
};

#define NB_SPLINE		(32)
/* unused
 static s32 SplineTbl[2*4*NB_SPLINE] = {
	// ===============
	//   Sample Key : Smooth
	// ===============
	// Key 1
		// Time, Value, Right, Left
			0,		0,		0,		0,
	// Key 2
		16384,	65536,		0,		0,
	// ===============
	//   Sample Key : Overshoot
	// ===============
	// Key 1
		// Time, Value, Right, Left
			0,		0,		0,		0,
	// Key 2
		16384,	65536,		0,		0,
	// ===============
	//   Sample Key : UnderOvershoot
	// ===============
	// Key 1
		// Time, Value, Right, Left
			0,		0,		0,		0,
	// Key 2
		16384,	65536,		0,		0,
};
*/

void CKLBSplineNode::cleanSplines() {
	KLBDELETEA(m_allKeys);
	m_allKeys	= NULL;
	KLBDELETEA(m_target);
	m_target	= NULL;
	KLBDELETEA(m_splines);
	m_splines	= NULL;
	KLBDELETEA(m_splinesKeyCount);
	m_splinesKeyCount = NULL;
//	KLBDELETEA(m_splineLocalTime);
//	m_splineLocalTime = NULL;
	KLBDELETEA(m_splineLastKey);
	m_splineLastKey = NULL;
}

bool CKLBSplineNode::setParamCount(u8 splineCount, u8 maxKeyCount) {
	m_uiTotalTime	= 0;
	m_uiMaxKeyCount	= maxKeyCount;

	stop();
	cleanSplines();

	m_allKeys		= KLBNEWA(s32, maxKeyCount * splineCount * 4 * sizeof(s32));	// Time, Left, Right, Value
	m_target		= KLBNEWA(u8 , splineCount);
	m_splinesKeyCount= KLBNEWA(u32 , splineCount);
	m_splines		= KLBNEWA(s32* , splineCount);
//	m_splineLocalTime= KLBNEWA(s32 , splineCount);
	m_splineLastKey	= KLBNEWA(u16, splineCount);

	if (m_allKeys	&& m_target 
					&& m_splinesKeyCount 
					&& m_splines 
					// && m_splineLocalTime 
					&& m_splineLastKey) {
		m_uiSplineCount	= splineCount;

		for (int n = 0; n < splineCount; n++) {
			m_splinesKeyCount[n]	= 0;
			m_splines[n]			= &m_allKeys[n * maxKeyCount * 4];
			m_target[n]				= 0;
			// m_splineLocalTime[n]	= 0;
			m_splineLastKey[n]		= 0;
		}

		return true;
	} else {
		return false;
	}
}

void CKLBSplineNode::setTarget(u8 splineIndex, u8 targetParameter) {
	klb_assert(splineIndex < m_uiSplineCount, "Invalid index");

	// Do not verify target used twice.
	m_target[splineIndex] = targetParameter;
}

void CKLBSplineNode::addKeys(u8 splineIndex, u32 time, s16 value) {
	addKeysFixed(splineIndex, time, ((s32)value) << 16);
}

void CKLBSplineNode::addKeysFixed(u8 splineIndex, u32 time, s32 fixedValue) {
	klb_assert(splineIndex < m_uiSplineCount, "Invalid index");

	// Find new key index and update key counter
	u32 idx = m_splinesKeyCount[splineIndex]++;

	// Get latest key memory storage
	s32* vector = m_splines[splineIndex];	// Select spline
	vector = &vector[idx * 4];				// Select vector in spline

	// Store time, value
	vector[0] = (s32)time;
	vector[1] = fixedValue;
	vector[2] = 0;
	vector[3] = 0;

	if (time > m_uiTotalTime) {
		m_uiTotalTime = time;
	}
}

void CKLBSplineNode::generateAnimation() {
	//
	// For now ignore mode and support only Catmull-Rom spline
	//
	for (u32 spIdx = 0; spIdx < m_uiSplineCount; spIdx++) {
		s32* vector     = m_splines[spIdx];
		u32  keyCount   = m_splinesKeyCount[spIdx];

		// From 1..keyCount-2
		for (u32 kIdx = 1; kIdx < keyCount-1; kIdx++) {
			s32 pm1		= vector[((kIdx-1) * 4) + 1];
			s32 pp1		= vector[((kIdx+1) * 4) + 1];

			s32 tangent	= (pp1 - pm1) >> 1;	// delta / 2

			vector[(kIdx * 4) + 2] = tangent;
			vector[(kIdx * 4) + 3] = tangent;
		}

		//
		vector[0 + 2]					= vector[6];					// P0 Right tangent
		vector[(keyCount-1) * 4 + 3]	= vector[(keyCount-2) * 4 + 2];	// Pn Left  tangent

	}
	m_loop				= false;
	m_timeMultiplier	= 256;
	m_mode				= 2;
}

void CKLBSplineNode::setAnimation(s32 milliSecondsPlayTime, s32 timeShift, u32 type, s32* keys, u32 keycount, u32 affected, float* arrayParam) {
	klb_assert(type <= NB_SPLINE, "Wrong spline type index");

	if (milliSecondsPlayTime == 0) {
		return;
	}

	timeShift			= (timeShift * 16384) / milliSecondsPlayTime;

	m_uiLocalTime		= timeShift;
	m_applyMask			= affected;
	m_uiLooptime		= 16384;	// Use time dilation.
	m_timeMultiplier	= ((16384<<8) / milliSecondsPlayTime);

	if (m_applyMask & ANM_X_COORD_0)		{  m_base[0] = arrayParam[0];  m_base[1] = arrayParam[1] - arrayParam[0]; arrayParam+=2; }
	if (m_applyMask & ANM_Y_COORD_1)		{  m_base[2] = arrayParam[0];  m_base[3] = arrayParam[1] - arrayParam[0]; arrayParam+=2; }
	if (m_applyMask & ANM_SCALE_COORD_2)	{  m_base[4] = arrayParam[0];  m_base[5] = arrayParam[1] - arrayParam[0];
											   m_base[6] = arrayParam[2];  m_base[7] = arrayParam[3] - arrayParam[2]; arrayParam+=4; }
	if (m_applyMask & ANM_R_COLOR_3)		{  m_base[8] = arrayParam[0];  m_base[9] = arrayParam[1] - arrayParam[0]; arrayParam+=2; }
	if (m_applyMask & ANM_G_COLOR_4)		{ m_base[10] = arrayParam[0]; m_base[11] = arrayParam[1] - arrayParam[0]; arrayParam+=2; }
	if (m_applyMask & ANM_B_COLOR_5)		{ m_base[12] = arrayParam[0]; m_base[13] = arrayParam[1] - arrayParam[0]; arrayParam+=2; }
	if (m_applyMask & ANM_A_COLOR_6)		{ m_base[14] = arrayParam[0]; m_base[15] = arrayParam[1] - arrayParam[0]; arrayParam+=2; }
	if (m_applyMask & ANM_SCALEX_COORD_7)	{  m_base[4] = arrayParam[0];  m_base[5] = arrayParam[1] - arrayParam[0]; arrayParam+=2; }
	if (m_applyMask & ANM_SCALEY_COORD_8)	{  m_base[6] = arrayParam[0];  m_base[7] = arrayParam[1] - arrayParam[0]; arrayParam+=2; }
	if (m_applyMask & ANM_ROTATION_COORD_9)	{ m_base[16] = arrayParam[0]; m_base[17] = arrayParam[1] - arrayParam[0]; }

	m_loop			= ((m_applyMask & ANM_LOOPBIT	) != 0);
	m_pingpong	    = ((m_applyMask & ANM_PING_PONG	) != 0);
	
	switch (type) {
	case 0:			
		m_aKeyVector        = keys;
		m_uiTotalKeyCount	= keycount;
		if (keys == NULL) {
			m_uiSplineCount = 0;	// Force node to do nothing.
			return;
		}
		break;
	case 1:			m_aKeyVector = SplineTbl1;
		m_uiTotalKeyCount	= 2;
		break;
	case 2:			m_aKeyVector = SplineTbl2;
		m_uiTotalKeyCount	= 2;
		break;
	case 3:			m_aKeyVector = SplineTbl3;
		m_uiTotalKeyCount	= 2;
		break;
	case 4:			m_aKeyVector = SplineTbl4;
		m_uiTotalKeyCount	= 2;
		break;
	case 5:			m_aKeyVector = SplineTbl5;
		m_uiTotalKeyCount	= 2;
		break;
	case 6:			m_aKeyVector = SplineTbl6;
		m_uiTotalKeyCount	= 2;
		break;
	case 7:			m_aKeyVector = SplineTbl7;
		m_uiTotalKeyCount	= 2;
		break;
	case 9:			m_aKeyVector = SplineTbl9;
		m_uiTotalKeyCount	= 2;
		break;
	case 27:		m_aKeyVector = SplineTbl27;
		m_uiTotalKeyCount	= 2;
		break;
	case 28:		m_aKeyVector = SplineTbl28;
		m_uiTotalKeyCount	= 2;
		break;
	case 29:		m_aKeyVector = SplineTbl29;
		m_uiTotalKeyCount	= 2;
		break;
	default:		m_aKeyVector = SplineTbl1;
		m_uiTotalKeyCount	= 2;
		break;
	}

	m_uiLastLocalTime	= -timeShift;
	m_uiLastKey			= 0;
	m_startTime			= m_uiLastLocalTime;
	m_uiTotalTime		= 16384;
	m_uiSplineCount		= 1;
	m_mode				= 1;
}

void CKLBSplineNode::endAnimation(s32* keys) {
	if ((keys == NULL) || (keys == m_aKeyVector)) {
		m_uiLastLocalTime	= m_uiTotalTime;
		m_loop				= false;
	}
}

void CKLBSplineNode::play() {
	// Reset counter.
	m_uiLocalTime		= m_startTime;
	m_uiLastLocalTime	= m_startTime;
	m_uiLastKey			= 0;

	if (!this->isAnimating()) {
		this->m_status |= ANIMATED;
		CKLBSystem::addToAnimation(this);
	}
}

void CKLBSplineNode::stop() {
	if (this->isAnimating()) {
		this->m_status &= ~ANIMATED;
		CKLBSystem::removeFromAnimation(this);
	}
}

/*virtual*/
void CKLBSplineNode::animate(u32 deltaTimeMilli) {
	s32 uiIdx;

	s32 uiDt;
	
	// Add delta to time
	m_uiLocalTime += (((s32)deltaTimeMilli * m_timeMultiplier)>>8);

	// If time is negative (offset) avoid modification the node as animation.
	s32 time = m_uiLocalTime;
	if (time < 0) {
		time = 0;
	}

	// Perform each spline.
	for (u32 n = 0; n < m_uiSplineCount; n++) {
		s32* pData;
		s32 uiMaxSize;

		if (m_mode == 1) {
			pData		= m_aKeyVector;
			uiMaxSize	= m_uiTotalKeyCount * VECTORSIZE;
		} else {
			pData		= (s32*)m_splines[n];
			uiMaxSize	= (m_splinesKeyCount[n] * VECTORSIZE);
		}

		if (time < m_uiLastLocalTime) {
			// First time, or time backward.
			uiIdx = VECTORSIZE;
		} else {
			if (m_mode == 1) {
				if (m_uiLastKey<VECTORSIZE) {
					m_uiLastKey = VECTORSIZE;
				}
				uiIdx = m_uiLastKey;
			} else {
				if (m_splineLastKey[n]<VECTORSIZE) {
					m_splineLastKey[n] = VECTORSIZE;
				}
				uiIdx = m_splineLastKey[n];
			}
		}

		//
		// Find Start Key
		//
		while ((uiIdx<uiMaxSize) && (pData[uiIdx] < (s32)time)) {
			uiIdx += VECTORSIZE;
		}

		bool isEnd = false;

		if (uiIdx>=uiMaxSize) {
			isEnd   = true;
			uiIdx   = uiMaxSize;
		}

		if (!isEnd) {
			// Compute the time % between 2 keys.
			s32 localTime	= /*m_uiLocalTime < 0 ? 0 : */time;
			s32 delta		= (pData[uiIdx] - pData[uiIdx-VECTORSIZE]);
			if (delta) {
				uiDt		= ((localTime - pData[uiIdx-VECTORSIZE])<<9) / delta;
			} else {
				uiDt		= 0;
			}
		} else {
			uiDt = 0;
		}

		// Go back to previous vector.
		uiIdx -= VECTORSIZE;

		// Save Last Key.
		if (m_mode == 1) {
			m_uiLastKey = uiIdx;
		} else {
			m_splineLastKey[n] = uiIdx;
		}

		// Go to first vector element.
		uiIdx++;

		//
		// Computation of vector and assignment to output.
		//
		s32 value    = interpolateKey(uiDt, &pData[uiIdx]);
		float fValue = value / 65535.0f;

		bool modColor = false;

		if (m_mode == 1) {
			bool modifCoord = ((m_applyMask & (ANM_X_COORD_0 | ANM_Y_COORD_1)) != 0); 
			if (modifCoord) {
				float tx = (m_applyMask & ANM_X_COORD_0) ? m_base[0] + (m_base[1] * fValue) : this->m_matrix.m_matrix[MAT_TX];
				float ty = (m_applyMask & ANM_Y_COORD_1) ? m_base[2] + (m_base[3] * fValue) : this->m_matrix.m_matrix[MAT_TY];

				this->setTranslate(tx,ty);
			}

			bool modifRot = (m_applyMask & ANM_ROTATION_COORD_9) != 0;
			if (m_applyMask & (ANM_SCALE_COORD_2 | ANM_SCALEX_COORD_7 | ANM_SCALEY_COORD_8)) {
				if (modifRot) {
					this->setScaleRotation(	m_base[4]  + (m_base[5]  * fValue),
											m_base[6]  + (m_base[7]  * fValue),
											m_base[16] + (m_base[17] * fValue)
										  );
				} else {
					this->setScale(	m_base[4] + (m_base[5] * fValue),
									m_base[6] + (m_base[7] * fValue));
				}
			} else {
				if (modifRot) {
					this->setRotation(m_base[16] + (m_base[17] * fValue));
				}
			}

			if (m_applyMask & (ANM_R_COLOR_3 | ANM_G_COLOR_4 | ANM_B_COLOR_5 | ANM_A_COLOR_6)) 
			{
				modColor = true;
				if (m_applyMask & ANM_R_COLOR_3) { m_localColorMatrix.m_vector[0] = m_base[8 ] + (m_base[9 ] * fValue); }
				if (m_applyMask & ANM_G_COLOR_4) { m_localColorMatrix.m_vector[1] = m_base[10] + (m_base[11] * fValue); }
				if (m_applyMask & ANM_B_COLOR_5) { m_localColorMatrix.m_vector[2] = m_base[12] + (m_base[13] * fValue); }
				if (m_applyMask & ANM_A_COLOR_6) { m_localColorMatrix.m_vector[3] = m_base[14] + (m_base[15] * fValue); }
			}

		} else {
			switch (m_target[n]) {
			case MODIFY_X:
				this->setTranslate(fValue,m_matrix.m_matrix[MAT_TY]);
				break;
			case MODIFY_Y:
				this->setTranslate(m_matrix.m_matrix[MAT_TX],fValue);
				break;
			case MODIFY_SCALE:
				this->setScale(fValue,fValue);
				break;
			case MODIFY_R:
				m_localColorMatrix.m_vector[0] = fValue;
				modColor = true;
				break;
			case MODIFY_G:
				m_localColorMatrix.m_vector[1] = fValue;
				modColor = true;
				break;
			case MODIFY_B:
				m_localColorMatrix.m_vector[2] = fValue;
				modColor = true;
				break;
			case MODIFY_A:
				m_localColorMatrix.m_vector[3] = fValue;
				modColor = true;
				break;
			case MODIFY_ROT:
				this->setRotation(fValue);
				break;
			}
		}

		if (modColor)
		{
			this->m_status |= CMATRIX_CHANGE;
			markUpTree();

			if (	(m_localColorMatrix.m_vector[0] != 1.0f) || 
					(m_localColorMatrix.m_vector[1] != 1.0f) || 
					(m_localColorMatrix.m_vector[2] != 1.0f) || 
					(m_localColorMatrix.m_vector[3] != 1.0f) ) {
				m_pColorMatrix		= &m_colorMatrix;
				m_useParentColor	= false;
			} else {
				m_pColorMatrix		= this->m_parent->m_pColorMatrix;
				m_useParentColor	= true;
			}
		}
	}

	m_uiLastLocalTime = m_uiLocalTime;

	// 1/ Animation Ends : loop = false, pingpong = false
	// 2/ 
	bool terminate = false;

	if (m_loop) {
		if (m_uiLocalTime >= m_uiTotalTime) {
			if (m_pingpong) {
				m_timeMultiplier = -m_timeMultiplier;
				m_uiLocalTime = (m_uiTotalTime<<1) - m_uiLocalTime; 
			} else {
				m_uiLocalTime -= m_uiTotalTime; // Loop
			}
		} else if ((m_pingpong) && (m_timeMultiplier < 0) && (time == 0)) {
			m_timeMultiplier = -m_timeMultiplier;
			m_uiLocalTime = -m_uiLocalTime;
		}
	} else {
		if (m_pingpong) {
			if ((m_timeMultiplier < 0) && (time == 0)) {
				terminate = true;
			} else
			if (m_uiLocalTime >= m_uiTotalTime) {
				// Go to negative direction.
				m_timeMultiplier = -m_timeMultiplier;
				// Local = Total - (Local - Total) = Total - Local + Total = 2*Total - Local
				m_uiLocalTime = (m_uiTotalTime<<1) - m_uiLocalTime; 
			}
		} else {
			if (m_uiLocalTime >= m_uiTotalTime) {
				terminate = true;
			}
		}
	}

	if (terminate) {
		if (m_refCounter) {
			*m_refCounter = *m_refCounter - 1;
			m_refCounter = NULL;
		}

		CKLBSystem::removeFromAnimation(this);
		// Trick : Avoid visible / unvisible to add/remove again to animation. Delete bit.
		this->m_status &= ~ANIMATED;

		if (m_applyMask & ANM_REMOVESCENE) {	// Before destruct in case both bit are set.
			this->m_parent->removeNode(this);
		}

		if (m_msgListener) {
			m_msgListener->receiveMsg(this, ANIMATION_COMPLETE, m_uiLocalTime);
		}
	}
}

#define TBLRESOLUTIONBIT	(15)

static const u16 HermiteTbl[513*4] = {
	32768,	0,		0,		0,	 
	32767,	63,		1,		0,	 
	32766,	127,	2,		0,	 
	32764,	189,	4,		1,	 
	32762,	252,	6,		1,	 
	32758,	313,	10,		3,	 
	32754,	375,	14,		4,	 
	32749,	435,	19,		6,	 
	32744,	496,	24,		7,	 
	32737,	555,	31,		9,	 
	32730,	615,	38,		12,	 
	32723,	674,	45,		14,	 
	32714,	732,	54,		17,	 
	32705,	790,	63,		20,	 
	32695,	847,	73,		23,	 
	32685,	904,	83,		27,	 
	32674,	961,	94,		31,	 
	32662,	1016,	106,	34,	 
	32649,	1072,	119,	39,	 
	32635,	1127,	133,	43,	 
	32621,	1181,	147,	48,	 
	32607,	1236,	161,	52,	 
	32591,	1289,	177,	57,	 
	32575,	1342,	193,	63,	 
	32558,	1395,	210,	68,	 
	32541,	1447,	227,	74,	 
	32523,	1499,	245,	80,	 
	32504,	1550,	264,	86,	 
	32484,	1601,	284,	92,	 
	32464,	1651,	304,	99,	 
	32443,	1701,	325,	105,	
	32422,	1751,	346,	112,	
	32400,	1800,	368,	120,	
	32377,	1848,	391,	127,	
	32353,	1896,	415,	134,	
	32329,	1944,	439,	142,	
	32304,	1991,	464,	150,	
	32279,	2038,	489,	158,	
	32253,	2084,	515,	167,	
	32226,	2130,	542,	175,	
	32199,	2175,	569,	184,	
	32171,	2220,	597,	193,	
	32142,	2265,	626,	202,	
	32113,	2309,	655,	211,	
	32083,	2352,	685,	221,	
	32053,	2395,	715,	230,	
	32022,	2438,	746,	240,	
	31990,	2481,	778,	250,	
	31958,	2523,	810,	261,	
	31925,	2564,	843,	271,	
	31891,	2605,	877,	281,	
	31857,	2646,	911,	292,	
	31822,	2686,	946,	303,	
	31787,	2726,	981,	314,	
	31751,	2765,	1017,	326,	
	31714,	2804,	1054,	337,	
	31677,	2842,	1091,	349,	
	31640,	2880,	1128,	360,	
	31601,	2918,	1167,	372,	
	31562,	2955,	1206,	384,	
	31523,	2992,	1245,	397,	
	31483,	3029,	1285,	409,	
	31442,	3065,	1326,	422,	
	31401,	3100,	1367,	435,	
	31360,	3136,	1408,	448,	
	31317,	3170,	1451,	461,	
	31274,	3205,	1494,	474,	
	31231,	3239,	1537,	487,	
	31187,	3272,	1581,	501,	
	31143,	3305,	1625,	514,	
	31097,	3338,	1671,	528,	
	31052,	3371,	1716,	542,	
	31006,	3403,	1762,	556,	
	30959,	3434,	1809,	571,	
	30912,	3465,	1856,	585,	
	30864,	3496,	1904,	600,	
	30816,	3527,	1952,	614,	
	30767,	3557,	2001,	629,	
	30718,	3586,	2050,	644,	
	30668,	3616,	2100,	659,	
	30618,	3645,	2150,	675,	
	30567,	3673,	2201,	690,	
	30515,	3701,	2253,	705,	
	30463,	3729,	2305,	721,	
	30411,	3756,	2357,	737,	
	30358,	3783,	2410,	753,	
	30305,	3810,	2463,	769,	
	30251,	3836,	2517,	785,	
	30196,	3862,	2572,	801,	
	30141,	3887,	2627,	818,	
	30086,	3912,	2682,	834,	
	30030,	3937,	2738,	851,	
	29974,	3962,	2794,	867,	
	29917,	3986,	2851,	884,	
	29860,	4009,	2908,	901,	
	29802,	4033,	2966,	918,	
	29744,	4056,	3024,	936,	
	29685,	4078,	3083,	953,	
	29626,	4100,	3142,	970,	
	29566,	4122,	3202,	988,	
	29506,	4144,	3262,	1005,	
	29445,	4165,	3323,	1023,	
	29384,	4186,	3384,	1041,	
	29323,	4206,	3445,	1059,	
	29261,	4226,	3507,	1077,	
	29198,	4246,	3570,	1095,	
	29136,	4265,	3632,	1113,	
	29072,	4284,	3696,	1132,	
	29009,	4303,	3759,	1150,	
	28944,	4321,	3824,	1168,	
	28880,	4339,	3888,	1187,	
	28815,	4357,	3953,	1206,	
	28750,	4375,	4018,	1225,	
	28684,	4392,	4084,	1243,	
	28617,	4408,	4151,	1262,	
	28551,	4425,	4217,	1281,	
	28484,	4441,	4284,	1300,	
	28416,	4456,	4352,	1320,	
	28348,	4472,	4420,	1339,	
	28280,	4487,	4488,	1358,	
	28211,	4501,	4557,	1378,	
	28142,	4516,	4626,	1397,	
	28073,	4530,	4695,	1417,	
	28003,	4544,	4765,	1436,	
	27932,	4557,	4836,	1456,	
	27862,	4570,	4906,	1476,	
	27791,	4583,	4977,	1496,	
	27719,	4595,	5049,	1516,	
	27648,	4608,	5120,	1536,	
	27575,	4619,	5193,	1556,	
	27503,	4631,	5265,	1576,	
	27430,	4642,	5338,	1596,	
	27357,	4653,	5411,	1616,	
	27283,	4664,	5485,	1636,	
	27209,	4674,	5559,	1657,	
	27134,	4684,	5634,	1677,	
	27060,	4694,	5708,	1697,	
	26985,	4703,	5783,	1718,	
	26909,	4712,	5859,	1738,	
	26833,	4721,	5935,	1759,	
	26757,	4729,	6011,	1780,	
	26681,	4738,	6087,	1800,	
	26604,	4746,	6164,	1821,	
	26527,	4753,	6241,	1842,	
	26450,	4761,	6318,	1863,	
	26372,	4768,	6396,	1883,	
	26294,	4774,	6474,	1904,	
	26215,	4781,	6553,	1925,	
	26136,	4787,	6632,	1946,	
	26057,	4793,	6711,	1967,	
	25978,	4798,	6790,	1988,	
	25898,	4804,	6870,	2009,	
	25818,	4809,	6950,	2030,	
	25738,	4814,	7030,	2051,	
	25657,	4818,	7111,	2072,	
	25576,	4822,	7192,	2093,	
	25495,	4826,	7273,	2115,	
	25414,	4830,	7354,	2136,	
	25332,	4833,	7436,	2157,	
	25250,	4837,	7518,	2178,	
	25168,	4840,	7600,	2200,	
	25085,	4842,	7683,	2221,	
	25002,	4844,	7766,	2242,	
	24919,	4847,	7849,	2263,	
	24835,	4848,	7933,	2285,	
	24752,	4850,	8016,	2306,	
	24668,	4851,	8100,	2327,	
	24583,	4852,	8185,	2349,	
	24499,	4853,	8269,	2370,	
	24414,	4854,	8354,	2391,	
	24329,	4854,	8439,	2413,	
	24244,	4854,	8524,	2434,	
	24158,	4854,	8610,	2455,	
	24072,	4853,	8696,	2477,	
	23986,	4853,	8782,	2498,	
	23900,	4852,	8868,	2519,	
	23814,	4851,	8954,	2541,	
	23727,	4849,	9041,	2562,	
	23640,	4847,	9128,	2583,	
	23553,	4845,	9215,	2604,	
	23465,	4843,	9303,	2626,	
	23378,	4841,	9390,	2647,	
	23290,	4838,	9478,	2668,	
	23202,	4835,	9566,	2689,	
	23113,	4832,	9655,	2711,	
	23025,	4829,	9743,	2732,	
	22936,	4826,	9832,	2753,	
	22847,	4822,	9921,	2774,	
	22758,	4818,	10010,	2795,	
	22669,	4814,	10099,	2816,	
	22579,	4809,	10189,	2837,	
	22489,	4804,	10279,	2858,	
	22400,	4800,	10368,	2880,	
	22309,	4794,	10459,	2900,	
	22219,	4789,	10549,	2921,	
	22129,	4784,	10639,	2942,	
	22038,	4778,	10730,	2963,	
	21947,	4772,	10821,	2984,	
	21856,	4766,	10912,	3005,	
	21765,	4759,	11003,	3026,	
	21674,	4753,	11094,	3046,	
	21582,	4746,	11186,	3067,	
	21491,	4739,	11277,	3088,	
	21399,	4732,	11369,	3108,	
	21307,	4724,	11461,	3129,	
	21215,	4717,	11553,	3149,	
	21122,	4709,	11646,	3170,	
	21030,	4701,	11738,	3190,	
	20938,	4693,	11830,	3211,	
	20845,	4684,	11923,	3231,	
	20752,	4675,	12016,	3251,	
	20659,	4667,	12109,	3271,	
	20566,	4658,	12202,	3291,	
	20473,	4649,	12295,	3311,	
	20379,	4639,	12389,	3331,	
	20286,	4630,	12482,	3351,	
	20192,	4620,	12576,	3371,	
	20099,	4610,	12669,	3391,	
	20005,	4600,	12763,	3411,	
	19911,	4590,	12857,	3430,	
	19817,	4579,	12951,	3450,	
	19723,	4568,	13045,	3469,	
	19628,	4558,	13140,	3489,	
	19534,	4547,	13234,	3508,	
	19440,	4536,	13328,	3528,	
	19345,	4524,	13423,	3547,	
	19250,	4513,	13518,	3566,	
	19156,	4501,	13612,	3585,	
	19061,	4489,	13707,	3604,	
	18966,	4477,	13802,	3623,	
	18871,	4465,	13897,	3642,	
	18776,	4453,	13992,	3660,	
	18681,	4440,	14087,	3679,	
	18586,	4427,	14182,	3697,	
	18490,	4415,	14278,	3716,	
	18395,	4402,	14373,	3734,	
	18300,	4389,	14468,	3752,	
	18204,	4375,	14564,	3771,	
	18109,	4362,	14659,	3789,	
	18013,	4348,	14755,	3807,	
	17918,	4335,	14850,	3825,	
	17822,	4321,	14946,	3842,	
	17726,	4307,	15042,	3860,	
	17630,	4292,	15138,	3877,	
	17535,	4278,	15233,	3895,	
	17439,	4264,	15329,	3912,	
	17343,	4249,	15425,	3929,	
	17247,	4234,	15521,	3947,	
	17151,	4219,	15617,	3964,	
	17055,	4204,	15713,	3981,	
	16959,	4189,	15809,	3997,	
	16863,	4174,	15905,	4014,	
	16767,	4158,	16001,	4031,	
	16671,	4143,	16097,	4047,	
	16575,	4127,	16193,	4063,	
	16479,	4111,	16289,	4079,	
	16384,	4096,	16384,	4096,	
	16288,	4079,	16480,	4111,	
	16192,	4063,	16576,	4127,	
	16096,	4047,	16672,	4143,	
	16000,	4031,	16768,	4158,	
	15904,	4014,	16864,	4174,	
	15808,	3997,	16960,	4189,	
	15712,	3981,	17056,	4204,	
	15616,	3964,	17152,	4219,	
	15520,	3947,	17248,	4234,	
	15424,	3929,	17344,	4249,	
	15328,	3912,	17440,	4264,	
	15232,	3895,	17536,	4278,	
	15137,	3877,	17631,	4292,	
	15041,	3860,	17727,	4307,	
	14945,	3842,	17823,	4321,	
	14850,	3825,	17918,	4335,	
	14754,	3807,	18014,	4348,	
	14658,	3789,	18110,	4362,	
	14563,	3771,	18205,	4375,	
	14467,	3752,	18301,	4389,	
	14372,	3734,	18396,	4402,	
	14277,	3716,	18491,	4415,	
	14181,	3697,	18587,	4427,	
	14086,	3679,	18682,	4440,	
	13991,	3660,	18777,	4453,	
	13896,	3642,	18872,	4465,	
	13801,	3623,	18967,	4477,	
	13706,	3604,	19062,	4489,	
	13611,	3585,	19157,	4501,	
	13517,	3566,	19251,	4513,	
	13422,	3547,	19346,	4524,	
	13328,	3528,	19440,	4536,	
	13233,	3508,	19535,	4547,	
	13139,	3489,	19629,	4558,	
	13044,	3469,	19724,	4568,	
	12950,	3450,	19818,	4579,	
	12856,	3430,	19912,	4590,	
	12762,	3411,	20006,	4600,	
	12668,	3391,	20100,	4610,	
	12575,	3371,	20193,	4620,	
	12481,	3351,	20287,	4630,	
	12388,	3331,	20380,	4639,	
	12294,	3311,	20474,	4649,	
	12201,	3291,	20567,	4658,	
	12108,	3271,	20660,	4667,	
	12015,	3251,	20753,	4675,	
	11922,	3231,	20846,	4684,	
	11830,	3211,	20938,	4693,	
	11737,	3190,	21031,	4701,	
	11645,	3170,	21123,	4709,	
	11552,	3149,	21216,	4717,	
	11460,	3129,	21308,	4724,	
	11368,	3108,	21400,	4732,	
	11276,	3088,	21492,	4739,	
	11185,	3067,	21583,	4746,	
	11093,	3046,	21675,	4753,	
	11002,	3026,	21766,	4759,	
	10911,	3005,	21857,	4766,	
	10820,	2984,	21948,	4772,	
	10729,	2963,	22039,	4778,	
	10638,	2942,	22130,	4784,	
	10548,	2921,	22220,	4789,	
	10458,	2900,	22310,	4794,	
	10368,	2880,	22400,	4800,	
	10278,	2858,	22490,	4804,	
	10188,	2837,	22580,	4809,	
	10098,	2816,	22670,	4814,	
	10009,	2795,	22759,	4818,	
	9920,	2774,	22848,	4822,	
	9831,	2753,	22937,	4826,	
	9742,	2732,	23026,	4829,	
	9654,	2711,	23114,	4832,	
	9565,	2689,	23203,	4835,	
	9477,	2668,	23291,	4838,	
	9389,	2647,	23379,	4841,	
	9302,	2626,	23466,	4843,	
	9214,	2604,	23554,	4845,	
	9127,	2583,	23641,	4847,	
	9040,	2562,	23728,	4849,	
	8954,	2541,	23814,	4851,	
	8867,	2519,	23901,	4852,	
	8781,	2498,	23987,	4853,	
	8695,	2477,	24073,	4853,	
	8609,	2455,	24159,	4854,	
	8523,	2434,	24245,	4854,	
	8438,	2413,	24330,	4854,	
	8353,	2391,	24415,	4854,	
	8268,	2370,	24500,	4853,	
	8184,	2349,	24584,	4852,	
	8099,	2327,	24669,	4851,	
	8015,	2306,	24753,	4850,	
	7932,	2285,	24836,	4848,	
	7848,	2263,	24920,	4847,	
	7765,	2242,	25003,	4844,	
	7682,	2221,	25086,	4842,	
	7600,	2200,	25168,	4840,	
	7517,	2178,	25251,	4837,	
	7435,	2157,	25333,	4833,	
	7353,	2136,	25415,	4830,	
	7272,	2115,	25496,	4826,	
	7191,	2093,	25577,	4822,	
	7110,	2072,	25658,	4818,	
	7029,	2051,	25739,	4814,	
	6949,	2030,	25819,	4809,	
	6869,	2009,	25899,	4804,	
	6789,	1988,	25979,	4798,	
	6710,	1967,	26058,	4793,	
	6631,	1946,	26137,	4787,	
	6552,	1925,	26216,	4781,	
	6473,	1904,	26295,	4774,	
	6395,	1883,	26373,	4768,	
	6318,	1863,	26450,	4761,	
	6240,	1842,	26528,	4753,	
	6163,	1821,	26605,	4746,	
	6086,	1800,	26682,	4738,	
	6010,	1780,	26758,	4729,	
	5934,	1759,	26834,	4721,	
	5858,	1738,	26910,	4712,	
	5782,	1718,	26986,	4703,	
	5707,	1697,	27061,	4694,	
	5633,	1677,	27135,	4684,	
	5558,	1657,	27210,	4674,	
	5484,	1636,	27284,	4664,	
	5410,	1616,	27358,	4653,	
	5337,	1596,	27431,	4642,	
	5264,	1576,	27504,	4631,	
	5192,	1556,	27576,	4619,	
	5120,	1536,	27648,	4608,	
	5048,	1516,	27720,	4595,	
	4976,	1496,	27792,	4583,	
	4905,	1476,	27863,	4570,	
	4835,	1456,	27933,	4557,	
	4764,	1436,	28004,	4544,	
	4694,	1417,	28074,	4530,	
	4625,	1397,	28143,	4516,	
	4556,	1378,	28212,	4501,	
	4487,	1358,	28281,	4487,	
	4419,	1339,	28349,	4472,	
	4351,	1320,	28417,	4456,	
	4283,	1300,	28485,	4441,	
	4216,	1281,	28552,	4425,	
	4150,	1262,	28618,	4408,	
	4083,	1243,	28685,	4392,	
	4018,	1225,	28750,	4375,	
	3952,	1206,	28816,	4357,	
	3887,	1187,	28881,	4339,	
	3823,	1168,	28945,	4321,	
	3758,	1150,	29010,	4303,	
	3695,	1132,	29073,	4284,	
	3631,	1113,	29137,	4265,	
	3569,	1095,	29199,	4246,	
	3506,	1077,	29262,	4226,	
	3444,	1059,	29324,	4206,	
	3383,	1041,	29385,	4186,	
	3322,	1023,	29446,	4165,	
	3261,	1005,	29507,	4144,	
	3201,	988,	29567,	4122,	
	3141,	970,	29627,	4100,	
	3082,	953,	29686,	4078,	
	3024,	936,	29744,	4056,	
	2965,	918,	29803,	4033,	
	2907,	901,	29861,	4009,	
	2850,	884,	29918,	3986,	
	2793,	867,	29975,	3962,	
	2737,	851,	30031,	3937,	
	2681,	834,	30087,	3912,	
	2626,	818,	30142,	3887,	
	2571,	801,	30197,	3862,	
	2516,	785,	30252,	3836,	
	2462,	769,	30306,	3810,	
	2409,	753,	30359,	3783,	
	2356,	737,	30412,	3756,	
	2304,	721,	30464,	3729,	
	2252,	705,	30516,	3701,	
	2200,	690,	30568,	3673,	
	2150,	675,	30618,	3645,	
	2099,	659,	30669,	3616,	
	2049,	644,	30719,	3586,	
	2000,	629,	30768,	3557,	
	1951,	614,	30817,	3527,	
	1903,	600,	30865,	3496,	
	1855,	585,	30913,	3465,	
	1808,	571,	30960,	3434,	
	1761,	556,	31007,	3403,	
	1715,	542,	31053,	3371,	
	1670,	528,	31098,	3338,	
	1624,	514,	31144,	3305,	
	1580,	501,	31188,	3272,	
	1536,	487,	31232,	3239,	
	1493,	474,	31275,	3205,	
	1450,	461,	31318,	3170,	
	1408,	448,	31360,	3136,	
	1366,	435,	31402,	3100,	
	1325,	422,	31443,	3065,	
	1284,	409,	31484,	3029,	
	1244,	397,	31524,	2992,	
	1205,	384,	31563,	2955,	
	1166,	372,	31602,	2918,	
	1127,	360,	31641,	2880,	
	1090,	349,	31678,	2842,	
	1053,	337,	31715,	2804,	
	1016,	326,	31752,	2765,	
	980,	314,	31788,	2726,	
	945,	303,	31823,	2686,	
	910,	292,	31858,	2646,	
	876,	281,	31892,	2605,	
	842,	271,	31926,	2564,	
	810,	261,	31958,	2523,	
	777,	250,	31991,	2481,	
	745,	240,	32023,	2438,	
	714,	230,	32054,	2395,	
	684,	221,	32084,	2352,	
	654,	211,	32114,	2309,	
	625,	202,	32143,	2265,	
	596,	193,	32172,	2220,	
	568,	184,	32200,	2175,	
	541,	175,	32227,	2130,	
	514,	167,	32254,	2084,	
	488,	158,	32280,	2038,	
	463,	150,	32305,	1991,	
	438,	142,	32330,	1944,	
	414,	134,	32354,	1896,	
	390,	127,	32378,	1848,	
	368,	120,	32400,	1800,	
	345,	112,	32423,	1751,	
	324,	105,	32444,	1701,	
	303,	99,		32465,	1651,	
	283,	92,		32485,	1601,	
	263,	86,		32505,	1550,	
	244,	80,		32524,	1499,	
	226,	74,		32542,	1447,	
	209,	68,		32559,	1395,	
	192,	63,		32576,	1342,	
	176,	57,		32592,	1289,	
	160,	52,		32608,	1236,	
	146,	48,		32622,	1181,	
	132,	43,		32636,	1127,	
	118,	39,		32650,	1072,	
	105,	34,		32663,	1016,	
	94,		31,		32674,	961,	
	82,		27,		32686,	904,	
	72,		23,		32696,	847,	
	62,		20,		32706,	790,	
	53,		17,		32715,	732,	
	44,		14,		32724,	674,	
	37,		12,		32731,	615,	
	30,		9,		32738,	555,	
	23,		7,		32745,	496,	
	18,		6,		32750,	435,	
	13,		4,		32755,	375,	
	9,		3,		32759,	313,	
	5,		1,		32763,	252,	
	3,		1,		32765,	189,	
	1,		0,		32767,	127,
	0,		0,		32768,	63,
	0,		0,		32768,	0,
};

//
// Compute Core
//
s32 CKLBSplineNode::interpolateKey(s32 interpolation, s32* vectorData) {
	//
	// Compute Hermite Spline for each component of the vector.
	//
	const u16* pTbl = &HermiteTbl[interpolation<<2];
	
	s32 p0 = vectorData[0];
	s32 p1 = vectorData[VECTORSIZE];
	s32 t0 = vectorData[1];					// Start Tangent Current key.
	s32 t1 = vectorData[VECTORSIZE + 2];	// End Tangent next key.

	// Value as is, Tangent as 16.16 format.
	return ( ( (((s64)p0)*pTbl[0]) + ((((s64)t0)*pTbl[1])) + (((s64)p1)*pTbl[2]) + ((((s64)t1)*pTbl[3])) )>>TBLRESOLUTIONBIT);
}
