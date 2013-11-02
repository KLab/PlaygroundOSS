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
#include <stdio.h>
#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#else
#include <Windows.h>
#endif

#include "BaseType.h"
#include "DebugTracker.h"
#include "FileSystem.h"
#include "CPFInterface.h"
#include "CKLBTask.h"
#include "CKLBLuaTask.h"

// BOMtest
bool                    CTracker::m_initialized     = false;
bool                    CTracker::m_retry           = false;
const char          *   CTracker::m_targethost      = NULL;
int                     CTracker::m_retrycount      = 0;

IReadStream         *   CTracker::ms_pSockR         = NULL;
IWriteStream        *   CTracker::ms_pSockW         = NULL; // 出力先socket
CTracker::srcList   *   CTracker::m_begin           = NULL; // sourceIdリスト先頭
int                     CTracker::m_nextId          = 0;    // 次に新規発行するsourceIdの値

CTracker::taskList  *   CTracker::m_taskbegin       = NULL; // sourceIdリスト先頭
int                     CTracker::m_taskId          = 0;    // 次に新規発行するsourceIdの値

int                     CTracker::ms_numFrame       = 0;
int                     CTracker::ms_numCounter     = 0;
int                     CTracker::ms_taskCounter    = 0;


void CTracker::writeBlock(u8* buf, u32 length) {
	if (ms_pSockW) {
		if (ms_pSockW->getStatus() == IWriteStream::NORMAL) {
			ms_pSockW->writeBlock(buf, length);
		} else {
			delete ms_pSockR;

			ms_pSockW = NULL;
			ms_pSockR = NULL;

			m_initialized = false;
		}
	}
}

// 指定項目のソースIDを通知する
bool
CTracker::sendSrcID(srcList * src)
{
	bool bResult = true;
    if(ms_pSockW) {
        u8 buf[256];
		int length = strlen(src->srcName) + 3;
        buf[0] = CMD_SRCID;    // SourceID send
        buf[1] = src->sid >> 8;
        buf[2] = src->sid & 0xff;
        strcpy((char*)(buf + 3), src->srcName);
        buf[ length ] = 0;
		writeBlock(buf, length + 1);
    }
	return bResult;
}

// 指定項目のタスクIDを通知する
bool
CTracker::sendTaskID(taskList * task)
{
	bool bResult = true;

    // 新タスク追加を通知(コネクションが成立していれば)
    if(ms_pSockW) {
        u8 buf[256];
        int length = strlen(task->taskName) + 3;
        buf[0] = CMD_TASKID;    // SourceID send
        buf[1] = task->tid >> 8;
        buf[2] = task->tid & 0xff;
        strcpy((char*)(buf + 3), task->taskName);
        buf[ length ] = 0;
		writeBlock(buf, length + 1);
    }
	return bResult;
}


// ソースIDから該当するソースID項目を検索し取得する
CTracker::srcList *
CTracker::searchSrcID(u16 srcID)
{
    srcList * pIt = m_begin;
    while(pIt) {
		if(pIt->sid == srcID) {
            return pIt;
        }
        pIt = pIt->p_next;
    }
	return NULL;
}

// タスクIDから該当するタスクID項目を検索し取得する
CTracker::taskList *
CTracker::searchTaskID(u16 taskID)
{
    taskList * pIt = m_taskbegin;
    while(pIt) {
		if(pIt->tid == taskID) {
            return pIt;
        }
        pIt = pIt->p_next;
    }
	return NULL;
}

int
CTracker::getSrcID(const char *srcName)
{
    srcList * pIt = m_begin;
    while(pIt) {
        if(!strcmp(srcName, pIt->srcName)) {
            return pIt->sid;
        }
        pIt = pIt->p_next;
    }
    // 見つからなかった
    pIt          = new srcList;
    pIt->srcName = srcName;
    pIt->sid     = ++m_nextId;
    pIt->p_next  = m_begin;
    m_begin      = pIt;
    
	sendSrcID(pIt);

	return pIt->sid;
}

void
CTracker::Init(const char * target, bool retry)
{
	m_retrycount = 0;
	m_retry      = retry;
    ms_pSockR    = CPFInterface::getInstance().platform().openReadStream(target, false);
	if(ms_pSockR->getStatus() != IReadStream::NORMAL) {
		// 接続に問題がある

		// ストリームを破棄
		delete ms_pSockR;
		ms_pSockR = NULL;

		if(!m_targethost) {
			char * buf = new char [ strlen(target) + 1 ];
			strcpy(buf, target);
			m_targethost = (const char *)buf;
		}
		m_initialized = false;	// 初期化されていない
		return;
	}

    if(ms_pSockR) ms_pSockW = ms_pSockR->getWriteStream();
    if(m_begin) {
        srcList * pIt;
        srcList * nxt;
        
        pIt = m_begin;
        while(pIt) {
            nxt = pIt->p_next;
            delete pIt;
            pIt = nxt;
        }
    }
    m_begin     = NULL;
    m_nextId    = 0;
    ms_numFrame = 0;
    ms_numCounter = 0;
	m_initialized = true;
}

void
CTracker::End()
{
    srcList * pIt;
    srcList * nxt;
    
    pIt = m_begin;
    while(pIt) {
        nxt = pIt->p_next;
        delete pIt;
        pIt = nxt;
    }

	taskList * pTIt;
	taskList * tnxt;
    pTIt = m_taskbegin;
    while(pIt) {
        tnxt = pTIt->p_next;
		delete[] pTIt->taskName;
        delete pTIt;
        pTIt = tnxt;
    }

	if(ms_pSockW) ms_pSockW->writeU8(CMD_END);
#ifndef _WIN32
	sleep(1000);  // waiting for client receive CMD_END.
#else
	Sleep(1000);
#endif
    delete ms_pSockR;
    m_initialized = false;
	m_retrycount = 0;
//    CPFInterface::getInstance().platform().closeWriteStream(ms_pSockW);
//    CPFInterface::getInstance().platform().closeReadStream(ms_pSockR);
}

void
CTracker::updateFrame()
{
	// 接続が成立していなければ、再接続を試みる。
	if(m_retry && !m_initialized && m_targethost) {
		if(++m_retrycount < 60) return; 

		Init(m_targethost, m_retry);
	}

	if(!m_initialized) return;
    ms_taskCounter = 0;
    ms_numFrame++;

	// モニタからのコマンドがあれば処理する。
	{
		u8 cmdbuf[3];
		bool bResult;

		srcList dummySrc;
		dummySrc.p_next  = NULL;
		dummySrc.srcName = "[ERROR] unknown srcID";

		taskList dummyTask;
		dummyTask.p_next  = NULL;
		dummyTask.taskName = "[ERROR] unknown taskID";

		// コマンドが到着している回数だけ処理する
		while((bResult = ms_pSockR->readBlock((void *)cmdbuf, 3))) {
			u8 cmd = cmdbuf[0];
			u16 id = ((u16)cmdbuf[1] << 8) | (u16)cmdbuf[2];
			switch(cmd)
			{
			case QUERY_SRCID:
				{
					dummySrc.sid = id;
					srcList * pSrc = searchSrcID(id);
					if(!pSrc) pSrc = &dummySrc;
					sendSrcID(pSrc);
				}
				break;
			case QUERY_TASKID:
				{
					dummyTask.tid = id;

					taskList * pTask = searchTaskID(id);
					if(!pTask) pTask = &dummyTask;
					sendTaskID(pTask);
				}
				break;
			case QUERY_GAMESTOP:
				{
					// does not support command anymore.
					klb_assertAlways("Not supported by engine anymore");
					ms_pSockW->writeU8(ACK_GAMESTOP);
				}
				break;
			case QUERY_GAMESTART:
				{
					// does not support command anymore.
					klb_assertAlways("Not supported by engine anymore");
					ms_pSockW->writeU8(ACK_GAMESTART);
				}
				break;
			}
		}
	}
	// New Frame.
	u8 buf[5];
    buf[0] = CMD_FRAME;
    setArrU32(buf + 1, (u32)ms_numFrame);
	writeBlock(buf, 5);
}


void *
CTracker::logNew(void* ptr, size_t size, int line, const char* file)
{
	if (ptr) {
		u8 buf[25];
		int id = getSrcID(file);
    
		buf[0] = CMD_ALLOC;
		setArrU32(buf + 1, static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ptr)));
		setArrU32(buf + 5, (u32)size);
		setArrU32(buf + 9, ms_numFrame);  // frame
		setArrU32(buf + 13, ms_numCounter); // counter
		setArrU16(buf + 17, (u16)line); // line
		setArrU16(buf + 19, (u16)id);   // sourceID
		CKLBTask* pTask = CKLBTaskMgr::getInstance().getCurrentTask();
		u32 classID = pTask ? pTask->getClassID() : 0;
		setArrU32(buf + 21, classID);
		writeBlock(buf, 25);

		ms_numCounter++;    
		// printf("Alloc:%p s:%i l.%i in %s %8x %s \n",ptr,size,line,file,classID, classID ? IFactory::getClassName(classID) : NULL);
	}
	return ptr;
}

void *
CTracker::logDelete(void* ptr, int line, const char* file)
{
	if (ptr) {
		u8 buf[21];
		int id = getSrcID(file);
    
		buf[0] = CMD_FREE;
		setArrU32(buf + 1, static_cast<uint32_t>(reinterpret_cast<uintptr_t>(ptr)));
		setArrU32(buf + 5, ms_numFrame);  // frame
		setArrU32(buf + 9, ms_numCounter); // counter
		setArrU16(buf + 13, (u16)line); // line
		setArrU16(buf + 15, (u16)id);   // sourceID
		CKLBTask* pTask = CKLBTaskMgr::getInstance().getCurrentTask();
		u32 classID = pTask ? pTask->getClassID() : 0;
		setArrU32(buf + 17, classID);
		writeBlock(buf, 21);
    
		ms_numCounter++;
		// printf("Delete:%p l.%i in %s (Class %8x %s)\n",ptr,line,file,classID, classID ? IFactory::getClassName(classID) : NULL);
	}
    
	return ptr;
}

int
CTracker::getTaskID(const char * taskName)
{
    taskList * pIt = m_taskbegin;
    while(pIt) {
        if(!strcmp(taskName, pIt->taskName)) {
            return pIt->tid;
        }
        pIt = pIt->p_next;
    }
    // 見つからなかった
    pIt = new taskList;
	char * buf = new char [ strlen(taskName) + 1 ];
	strcpy(buf, taskName);
    pIt->taskName = (const char *)buf;
    pIt->tid    = ++m_taskId;
    pIt->p_next = m_taskbegin;
    m_taskbegin = pIt;
    
	sendTaskID(pIt);

    return pIt->tid;
}
