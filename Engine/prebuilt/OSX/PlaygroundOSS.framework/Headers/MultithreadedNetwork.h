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
#ifndef MULTITHREADED_NETWORK_KLB
#define MULTITHREADED_NETWORK_KLB

#include "CKLBHTTPInterface.h"

#define LOCK(a)					CPFInterface::getInstance().platform().mutexLock(a)
#define UNLOCK(a)				CPFInterface::getInstance().platform().mutexUnlock(a)
#define ALLOC_LOCK()			CPFInterface::getInstance().platform().allocMutex()
#define FREE_LOCK(a)			CPFInterface::getInstance().platform().freeMutex(a)
#define ALLOCEVENT_LOCK()		CPFInterface::getInstance().platform().allocEventLock()
#define FREEEVENT_LOCK(a)		CPFInterface::getInstance().platform().freeEventLock(a)
#define CREATE_THREAD(a,b)		CPFInterface::getInstance().platform().createThread(a, b)
#define FREE_THREAD(a)			CPFInterface::getInstance().platform().deleteThread(a)
#define WAKE_THREAD(a)			CPFInterface::getInstance().platform().eventWakeup(a)
#define SLEEP_THREAD(a)			CPFInterface::getInstance().platform().eventSleep(a)

/*!
* \class ConnectionEntry
* \brief Connection Entry Class
* 
* 
*/
class ConnectionEntry {
public:
	ConnectionEntry();
	~ConnectionEntry();
	ConnectionEntry*	m_pNext;
	CKLBHTTPInterface	m_oConnection;
	bool				m_kill;
};

/*!
* \class NetworkManager
* \brief Network Manager
* 
* 
*/
class NetworkManager {
public:
	static bool 				startNetworkManager	();
	static void 				stopNetworkManager	();
	static CKLBHTTPInterface*	createConnection	();
	static void					releaseConnection	(CKLBHTTPInterface* connection);
private:
		   s32					workThread			();
	static s32					threadFunc			(void* pThread, void* data);
	static NetworkManager		s_manager;
	
	NetworkManager();
	~NetworkManager();
	
	void* 				m_lock;
	void*				m_eventLock;
	ConnectionEntry*	m_entries;
	volatile u32		m_killCount;
	ConnectionEntry*	m_killEntries[200];
	bool				m_bShutDown;
	void*				m_thread;
	
	volatile
	bool				m_bShutDownComplete;
	
};

#endif
