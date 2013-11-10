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
#ifndef CKLBUITask_h
#define CKLBUITask_h

#include "CKLBLuaPropTask.h"
#include "CKLBSplineNode.h"

#define	UI_BASE_PROP \
	{	"alpha",			UINTEGER,	(setBoolT)&CKLBUITask::setAlpha,		(getBoolT)&CKLBUITask::getAlpha,		0	},\
	{	"color",			UINTEGER,	(setBoolT)&CKLBUITask::setColor,		(getBoolT)&CKLBUITask::getColor,		0	},\
	{	"scaleX",			NUMERIC,	(setBoolT)&CKLBUITask::setScaleX,		(getBoolT)&CKLBUITask::getScaleX,		0	},\
	{	"scaleY",			NUMERIC,	(setBoolT)&CKLBUITask::setScaleY,		(getBoolT)&CKLBUITask::getScaleY,		0	},\
	{	"rot",				NUMERIC,	(setBoolT)&CKLBUITask::setRotation,		(getBoolT)&CKLBUITask::getRotation,		0	},\
	{	"x",				NUMERIC,	(setBoolT)&CKLBUITask::setX,			(getBoolT)&CKLBUITask::getX,			0	},\
	{	"y",				NUMERIC,	(setBoolT)&CKLBUITask::setY,			(getBoolT)&CKLBUITask::getY,			0	},\
	{	"visible",			BOOLEANT,	(setBoolT)&CKLBUITask::setVisible,		(getBoolT)&CKLBUITask::getVisible,		0	}

#define UI_BASE_PROPCOUNT	(8)

/*!
* \class CKLBUITask
* \brief UI Task Class.
* 
* CKLBUITask is the root class for every UI Task Classes in the Engine.
* It defines some properties helpful for every subclasses (such as
* alpha, color, scale, rotation, position, visibility).
*
* Each UITask is linked with a Node of the SceneGraph to be rendered.
* Both objects point each other.
*
* You can also attach to a CKLBUITask some spline animations.
*/
class CKLBUITask : public CKLBLuaPropTask
{
protected:
	CKLBUITask(TASK_PHASE phase = P_UIPROC);
	virtual ~CKLBUITask();
public:
	bool initScript		(CLuaState& lua);
	void die			();
	int  commandScript	(CLuaState& lua);
	virtual TASKTYPE getTaskType();

	inline CKLBNode * getNode() { return m_pUINode; }

	inline void setOtherParent(CKLBTask * pTask) { m_pRegParent = pTask; }

	// Generic Command: Common for all UI Tasks.
	enum {
		UI_GENERIC_BASE = 0x10000,

		UI_GENERIC_NODE_RECONNECT = UI_GENERIC_BASE,
		UI_GENERIC_SET_NAME,
		UI_GENERIC_ANIM_SET_SPLINE,
		UI_GENERIC_ANIM_PLAY,
		UI_GENERIC_ANIM_STOP,
		UI_GENERIC_IS_ANIM,

		UI_GENERIC_SET_COLOR,
		UI_GENERIC_SET_SCALE,
		UI_GENERIC_SET_ROT,
		UI_GENERIC_SET_VISIBLE,

		SPL_VALUE_INT = 0,
		SPL_VALUE_NUM = 1
	};

	inline
	bool getVisible()	{ return m_visible; }

	inline virtual
	void setVisible(bool visible) {
		if(m_newScriptModel) {
			if(m_visible != visible) {
				m_visible = visible;
				m_pUINode->setVisible(visible);
			}
		} else {
			m_pUINode->setVisible(visible);
			setGenBool(PRG_VISIBLE, visible);
		}
	}

	inline void  setGenBool(int idx, bool val)	{ setBool(idx + m_beginIndex, val);						}
	inline void  setGenNum(int idx, float val)	{ setNum(idx + m_beginIndex, val);						}
	bool		 reconnect(const char* nodeName);

	inline void  setScaleX(float scale)		{ m_pUINode->setScale(scale, m_pUINode->getScaleY());		}
	inline float getScaleX()				{ return m_pUINode->getScaleX();							}

	inline void  setScaleY(float scale)		{ m_pUINode->setScale(m_pUINode->getScaleX(), scale);		}
	inline float getScaleY()				{ return m_pUINode->getScaleY();							}

	inline void  setX(float x)				{ m_pUINode->setTranslate(x,m_pUINode->getTranslateY());	}
	inline float getX()						{ return m_pUINode->getTranslateX();						}

	inline void  setY(float y)				{ m_pUINode->setTranslate(m_pUINode->getTranslateX(),y);	}
	inline float getY()						{ return m_pUINode->getTranslateY();						}

	inline void  setRotation(float rot)		{ m_pUINode->setRotation(rot);								}
	inline float getRotation()				{ return m_pUINode->getRotation();							}

	inline bool	setParamCount(u32 splineCount, u32 maxKeyCount) 
	{ return m_pUINode->setParamCount(splineCount, maxKeyCount); }

	inline void setTarget(u32 splineIndex, u32 targetParameter) 
	{ m_pUINode->setTarget(splineIndex,targetParameter); }

	inline void addKeys(u32 splineIndex, u32 time, s32 value) 
	{ m_pUINode->addKeys(splineIndex, time, value); }

	inline void addKeysFixed(u32 splineIndex, u32 time, s32 fixed16Value) 
	{ m_pUINode->addKeysFixed(splineIndex, time, fixed16Value); }

	inline void generateAnimation() 
	{ m_pUINode->generateAnimation(); }

	void setColor(u32 color);
	u32  getColor();
	void setAlpha(u32 alpha);
	u32  getAlpha();

	inline void setArgb(u32 alpha, u32 color) {
		setAlpha(alpha);
		setColor(color);
	}
	inline void setArgb(u32 argb) {
		u32 color = argb & 0x00ffffff;
		u32 alpha = (argb >> 24) & 0xff;
		setAlpha(alpha);
		setColor(color);
	}
	inline u32  getArgb()					{ return getAlpha()<<24 | getColor();	}

	virtual u32  getOrder()					{ return 0;								}
	virtual void setOrder(u32 /*order*/)	{ /* Do nothing */						}

	inline bool isAnim()					{ return m_pUINode->isAnimating();		}

	inline void play()						{ m_pUINode->play();					}
	inline void stop()						{ m_pUINode->stop();					}
	inline void setInnerUpdate()			{	m_bInnerUpdate = true;
												setUpdateFlag();					}

protected:
	inline bool  getGenBool	(int idx)		{ return getBool(idx + m_beginIndex);	}
	inline float getGenNum	(int idx)		{ return getNum(idx + m_beginIndex);	}
	inline void  setInitPos	(float x, float y) {
		m_initX = x;
		m_initY = y;
	}
	inline void  set_phase	(TASK_PHASE phase = P_NORMAL) { m_phase = phase; }
	virtual bool initUI		(CLuaState& lua) = 0;
	virtual int  commandUI	(CLuaState& lua, int argc, int cmd);
	virtual void execute	(u32 deltaT) = 0;
	virtual void dieUI		() = 0;

	bool updateUIProperty();

	bool setupNode();
	bool registUI(CKLBUITask * pParent, bool result, CKLBTask * pRegParent = 0);

	enum {
		PRG_ALPHA,
		PRG_COLOR,
		PRG_SCALE_X,
		PRG_SCALE_Y,
		PRG_ROT,
		PRG_X,
		PRG_Y,
		PRG_VISIBLE,
	};

	CKLBSplineNode	*	m_pUINode;
private:
	bool setGenericProperty	();
	bool setSplineAnim		(CLuaState& lua, int pos);
	int  getSplineKeyCount	(CLuaState& lua, int pos);
	bool setSplineAnimTarget(CLuaState& lua, int pos, int spline_index, int max_key_count);

	TASK_PHASE			m_phase;


	int					m_beginIndex;	// UI property start index

	float				m_initX;
	float				m_initY;
	u32					m_color;
	u32					m_alpha;
	bool				m_visible;

	bool				m_bInnerUpdate;

	CKLBTask		*	m_pRegParent;

	static const char	*	ms_propList[];
};

#endif // CKLBUITask_h
