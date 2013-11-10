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
#ifndef __DEBUG_SYSTEM__
#define __DEBUG_SYSTEM__
#include <stdlib.h>
#include "FileSystem.h"

class CKLBTask;

class CTracker
{
public:
    static void  Init			(const char * target, bool retry = false);
    static void  End			();
    
    static void  updateFrame	();

	static void  setStateName	(char* newState);
	static void* logNew			(void* ptr, size_t size, int line, const char* file);
	static void* logDelete		(void* ptr, int line, const char* file);
private:
    enum {
        CMD_END     = 1,

        CMD_ALLOC   = 2,
        CMD_FREE    = 3,
        CMD_SRCID   = 4,
        CMD_TASKTIME= 5,    // タスクの所要時間
        CMD_TASKID  = 6,    // タスクIDの新規追加
		CMD_FRAME	= 7,

		QUERY_SRCID		= 0x11,	// パフォーマンスモニタからのコマンド: SRCID の値から、ソース/行番号を得る
		QUERY_TASKID	= 0x12,	// パフォーマンスモニタからのコマンド: TASKIDの値からタスクラベルを得る

		QUERY_GAMESTOP	= 0x13,
		QUERY_GAMESTART	= 0x14,

		ACK_GAMESTOP	= 0x23,
		ACK_GAMESTART	= 0x24,
    };

    typedef struct srcList {
        struct srcList * p_next;
        const char * srcName;
        int    sid;
    } srcList;
	static bool			sendSrcID	(srcList * src);
	static srcList *	searchSrcID	(u16 srcID);
	static int			getSrcID	(const char * srcName);

	static srcList *	m_begin;
    static int          m_nextId;
    static int          ms_numCounter;

    
    typedef struct taskList {
        struct taskList * p_next;
        const char * taskName;
        int     tid;
    } taskList;
	static bool			sendTaskID	(taskList * task);
	static taskList *	searchTaskID(u16 taskID);
    static int			getTaskID	(const char * taskName);

    static taskList *	m_taskbegin;
    static int          m_taskId;
    static int          ms_taskCounter;

	static void writeBlock(u8* buf, u32 length);

    static inline void setArrU32(u8 * p, u32 v) {
        p[0] = (v >> 24) & 0xff;
        p[1] = (v >> 16) & 0xff;
        p[2] = (v >> 8) & 0xff;
        p[3] = v & 0xff;
    }

    static inline void setArrU16(u8 * p, u16 v) {
        p[0] = (v >> 8) & 0xff;
        p[1] = v & 0xff;
    }

    static IReadStream *	ms_pSockR;
    static IWriteStream *	ms_pSockW;


	static bool				m_initialized;
	static bool				m_retry;
	static const char *		m_targethost;
	static int				m_retrycount;

    static int				ms_numFrame;
};

#endif
