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
#ifdef __CPP_VERSION__

#include "CKLBGCTask.h"
#include "RuntimeLibrary/CS_Memory.h"

static CKLBTaskFactory<CKLBGCTask> factory("GCTask", CLS_KLBGCTASK);

CKLBGCTask::CKLBGCTask()
: CKLBLuaPropTask		()
, m_timeBetweenGC		(0)
, m_lastGC				(0)
, m_lastMS				(0)
, m_lastGen1			(0)
, m_MSFrequency			(0.02f)
, m_Gen1Frequency		(0.05f)
{
	m_newScriptModel = true;
}

CKLBGCTask::~CKLBGCTask() 
{
}

u32 CKLBGCTask::getClassID() { return CLS_KLBGCTASK; }

CKLBGCTask* CKLBGCTask::create(u32 size, u32 rootCount, u16 multipleRefPageCount, u16 markAndSweepStackSize, u32 timeBetweenGC, float MSFrequency, float gen1Frequency) {
	CKLBGCTask* pTask = KLBNEW(CKLBGCTask);
	if (!pTask) { return NULL; }
	if (!pTask->init(size, rootCount, multipleRefPageCount, markAndSweepStackSize, timeBetweenGC, MSFrequency, gen1Frequency)) {
		KLBDELETE(pTask);
		return NULL;
	}
	return pTask;
}

bool
CKLBGCTask::init(u32 size, u32 rootCount, u16 multipleRefPageCount, u16 markAndSweepStackSize, u32 timeBetweenGC, float MSFrequency, float gen1Frequency) {
	if(!(System::Memory::setGlobalMemory(size, rootCount, multipleRefPageCount, markAndSweepStackSize))) {
		klb_assertAlways("GC initialization has failed.");
		return false;
	}

	m_timeBetweenGC	= timeBetweenGC;
	m_MSFrequency	= MSFrequency;
	m_Gen1Frequency	= gen1Frequency;

	return regist(NULL, CKLBTask::TASK_PHASE::P_GC);
}

void
CKLBGCTask::execute(u32 deltaT)
{
	m_lastGC	+= deltaT;
	m_lastMS	+= deltaT;
	m_lastGen1	+= deltaT;

	if(m_lastGC > m_timeBetweenGC) {
		u32 gcInfos = System::Memory::COMPACT_GEN0 | System::Memory::COMPACT_NOW;
		if(m_lastGen1 > m_timeBetweenGC / m_Gen1Frequency) {
			gcInfos |= System::Memory::COMPACT_GEN1;
			m_lastGen1 = 0;
		}

		if(m_lastMS > m_timeBetweenGC / m_MSFrequency) {
			CHECKMEM();
			System::Memory::compactionMS(gcInfos);
			CHECKMEM();
			m_lastMS = 0;
		} else {
			CHECKMEM();
			System::Memory::compactionSmall(gcInfos);
			CHECKMEM();
		}
		m_lastGC = 0;
	}
}

void 
CKLBGCTask::die() 
{

}

#endif
