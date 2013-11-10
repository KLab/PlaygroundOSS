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
#ifndef CKLBIntervalTimer_h
#define CKLBIntervalTimer_h

#include "CKLBLuaPropTask.h"

/*!
* \class CKLBIntervalTimer
* \brief Timer Task Class
* 
* CKLBIntervalTimer is a basic timer class.
* It makes a call to the callback function when the timer reached the defined time limit.
* It can make this call just once and then die or be in a repeat mode and reset itself
* every time it reaches the defined time limit.
*/
class CKLBIntervalTimer : public CKLBLuaPropTask
{
	friend class CKLBTaskFactory<CKLBIntervalTimer>;
private:
	CKLBIntervalTimer();
	virtual ~CKLBIntervalTimer();

	bool init(CKLBTask* pTask, u32 timerID, u32 interval, bool repeat,const char* callback, u8 mode, bool killIfUpdate);
public:
	static CKLBIntervalTimer* create(CKLBTask* pParentTask, u32 timerID, u32 interval, bool repeat,const char* callback, u8 mode = 0, bool killIfUpdate = true);

	bool initScript(CLuaState& lua);

	void execute(u32 deltaT);
	void die();

	inline u32	getTimerID	()				{	return m_timerID;	}
	inline void	setTimerID	(u32 id)		{	m_timerID = id;		}

	inline bool	getRepeat	()				{	return m_repeat;	}
	inline void	setRepeat	(bool value)	{
		m_countup = 0;
		m_repeat = value;	
	}

	inline u32	getInterval	()				{	return m_interval;	}
	inline void	setInterval	(u32 value)		{
		m_countup = 0;
		m_interval = value;
	}

	inline u8	getMode		()				{	return m_mode;		}

	u32			getClassID	();

private:

	const char	*	m_callback;

	u32				m_timerID;
	u32				m_interval;
	u32				m_countup;
	u8				m_mode;
	bool			m_repeat;
	bool			m_killIfUpdate;

	static	PROP_V2	ms_propItems[];
};


#endif // CKLBIntervalTimer_h
