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
#ifndef CKLBGCTask_h
#define CKLBGCTask_h

#include "CKLBLuaPropTask.h"

/*!
* \class CKLBGCTask
* \brief Garbage Collection Task class
* 
* /!\ This task is only designed for the C# Scripting.
* /!\ This task has never been tested with a full game, just with basic samples.
* 
* CKLBGCTask processes regular Garbage Collections while the game is running.
* It must be used with the C++ C# Runtime.
*/
class CKLBGCTask : public CKLBLuaPropTask
{
	friend class CKLBTaskFactory<CKLBGCTask>;
private:
	CKLBGCTask();
	virtual ~CKLBGCTask();
	bool init(u32 size, u32 rootCount, u16 MultipleRefPageCount, u16 MarkAndSweepStackSize, u32 timeBetweenGC, float MSFrequency, float Gen1Frequency);
public:
	virtual u32         getClassID();
	static CKLBGCTask*  create(u32 size, u32 rootCount, u16 MultipleRefPageCount, u16 MarkAndSweepStackSize, u32 timeBetweenGC, float MSFrequency, float Gen1Frequency);

	void execute(u32 deltaT);
	void die    ();

	bool initScript(CLuaState& lua) { return true; }

private:
	u32     m_timeBetweenGC;
	u32     m_lastGC;
	u32     m_lastMS;
	u32     m_lastGen1;
	float   m_MSFrequency;
	float   m_Gen1Frequency;
	
};

#endif // CKLBGCTask_h
