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
#include "MultithreadedNetwork.h"

NetworkManager NetworkManager::s_manager;

ConnectionEntry::ConnectionEntry() 
{
	m_pNext = NULL;
	m_kill	= false;	
}

ConnectionEntry::~ConnectionEntry() 
{
}

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

// TODO : Task destruction will have task executed at a given frame
// and all task are killed AT THE END OF FRAME.
// Make sure that we kill the network manager AFTER that.

/*static*/
bool 
NetworkManager::startNetworkManager() 
{
	// 1. Start Thread
	s_manager.m_lock 				= ALLOC_LOCK();
	s_manager.m_eventLock			= ALLOCEVENT_LOCK();
	s_manager.m_bShutDownComplete	= false;
	s_manager.m_bShutDown			= false;
	s_manager.m_entries				= NULL;
	s_manager.m_thread				= NULL;
	s_manager.m_killCount			= 0;

	s_manager.m_thread = CREATE_THREAD(threadFunc,&s_manager);
	return s_manager.m_thread != 0;
}

/*static*/
void 
NetworkManager::stopNetworkManager() 
{
	s_manager.m_bShutDown = true;
	
	// May be asleep
	WAKE_THREAD(s_manager.m_eventLock);
	
	while (s_manager.m_bShutDownComplete == false) {
		// Wait other thread complete loop.
	}

	// TODO clear all entries.
	klb_assert(s_manager.m_entries == NULL, "Remaining connection !?");

	FREE_THREAD		(s_manager.m_thread);
	FREE_LOCK		(s_manager.m_lock);
	FREEEVENT_LOCK	(s_manager.m_eventLock);
}

int gTotal = 0;

/*static*/
CKLBHTTPInterface* 
NetworkManager::createConnection() 
{
	ConnectionEntry*	pEntry = KLBNEW(ConnectionEntry);
	if (pEntry) {
		pEntry->m_kill 	= false;
		
		LOCK(s_manager.m_lock);
		pEntry->m_pNext	= s_manager.m_entries;
		s_manager.m_entries = pEntry;
		gTotal++;
		DEBUG_PRINT("ALLOC CONNEXION : %8X(%i)\n", &pEntry->m_oConnection, gTotal);
		UNLOCK(s_manager.m_lock);
		return &pEntry->m_oConnection;
	} else {
		return NULL;
	}
}

/*static*/
void 
NetworkManager::releaseConnection(CKLBHTTPInterface* connection) 
{
	if (!connection) { return; }

	LOCK(s_manager.m_lock);
	gTotal--;
	DEBUG_PRINT("FREE CONNEXION : %8X(%i)\n", connection, gTotal);
	// 1. Find in link list the entry.
	ConnectionEntry* pEntry = s_manager.m_entries;
	ConnectionEntry* pPrev	= NULL;
	while (pEntry) {
		if ((&pEntry->m_oConnection) == connection) {
			// Between lock.
			if (pPrev) {
				pPrev->m_pNext		= pEntry->m_pNext;				
			} else {
				s_manager.m_entries = pEntry->m_pNext;
			}

			s_manager.m_killEntries[s_manager.m_killCount++] = pEntry;
			if (s_manager.m_killCount > 10) {
				DEBUG_PRINT("ASSERT : more than 10 FREE CONNEXION WAIT FOR KILL !!! \n");
			}
			break;
		}
		pPrev  = pEntry;
		pEntry = pEntry->m_pNext;
	}
	
	if (!pEntry) {
		klb_assertAlways("Error");
	}
	UNLOCK(s_manager.m_lock);
	
	// May be asleep
	WAKE_THREAD(s_manager.m_eventLock);
}

/*static*/ 
s32 
NetworkManager::threadFunc(void* /*pThread*/, void* data) 
{
	return ((NetworkManager*)data)->workThread();
}

s32 
NetworkManager::workThread() 
{
	SLEEP_THREAD(m_eventLock); // First time wait.
	
	while (!m_bShutDown) {
		while (m_killCount != 0) {
			ConnectionEntry* pList = NULL;
			LOCK(m_lock);
			if (m_killCount) {
				pList = m_killEntries[--m_killCount];
			}
			UNLOCK(m_lock);

			if (pList) {
				DEBUG_PRINT("REAL KILL CONNEXION : %8X\n", &pList->m_oConnection);
				// Consume code
				KLBDELETE(pList);
			}
		}
		SLEEP_THREAD(m_eventLock);
	}
	
	m_bShutDownComplete = true;
	return 1;
}
