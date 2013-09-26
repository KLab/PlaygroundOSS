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
#include <string.h>
#include "CKLBDebugger.h"
#include "CKLBAsset.h"
#include "CKLBDataHandler.h"
#include "CKLBTask.h"

// ----------------------------
//   Local helper function
// ----------------------------

static void writeU32(u8* pDst, u32 value) {
	pDst[0] = value >> 24;
	pDst[1] = value >> 16;
	pDst[2] = value >> 8;
	pDst[3] = value;
}


static u32 readU32(u8** ppSrc) {
	u8* pSrc	= *ppSrc;
	u32 value	= (pSrc[0] << 24) | (pSrc[1]<<16) | (pSrc[2]<<8) | (pSrc[3]);
	*ppSrc		= &pSrc[4];
	return value;
}

// ----------------------------
//   Debugger Implementation
// ----------------------------

CKLBDebuggerContext::CKLBDebuggerContext(u32 /*size*/)
: CKLBContext       ()
, m_pCommunicator   (NULL)
{
}

CKLBDebuggerContext::~CKLBDebuggerContext() {
}

void CKLBDebuggerContext::setupReceiver(IKLBDebuggerCommunicator* pCommunicator) {
	klb_assert(pCommunicator, "NULL POINTER");
	m_pCommunicator = pCommunicator;
	pCommunicator->assignDebugger(this);
}

void CKLBDebuggerContext::receiveCommand(u32 /*commandID*/, COMMAND_TYPE /*commandType*/, u8* /*data*/, u32 /*dataSize*/) {
	klb_assert(m_pCommunicator, "Call setupReceiver first.");

	//switch (commandType) {
	// case xxxx:
	//	if (dataSize == 0) {
	//		returnResult12(commandID, sizeof(void*), (void*)0x00000001);
	//	or	m_pCommunicator->sendResult(commandID, ERR_NOERROR);
	//	} else {
	//		errResult(commandID, ERR_INVALIDREQ);
	//	}
	//	break;
	//}
}

void CKLBDebuggerContext::returnResult4(u32 commandID, u32 value) {
	u8* pRes = m_pCommunicator->allocateResult(commandID, 4);
	if (pRes) {
		writeU32(pRes, value);
		m_pCommunicator->sendResult(commandID, ERR_NOERROR);
	} else {
		m_pCommunicator->sendResult(commandID, ERR_ALLOCATION);
	}
}

void CKLBDebuggerContext::returnResultString(u32 commandID, const char* string) {
	int length = strlen(string) + 1;
	u8* pRes = m_pCommunicator->allocateResult(commandID, 4 + length);
	if (pRes) {
		writeU32(pRes, length); pRes += 4;
		memcpy(pRes, string, length); pRes += length;	// Src is 0 at end also.
		m_pCommunicator->sendResult(commandID, ERR_NOERROR);
	} else {
		m_pCommunicator->sendResult(commandID, ERR_ALLOCATION);
	}
}

void CKLBDebuggerContext::returnResult12(u32 commandID, u32 classID, void* value) {
	u8* pRes = m_pCommunicator->allocateResult(commandID, 12);
	if (pRes) {
		writeU32(pRes, classID); pRes += 4;
		// Clear buffer
		memset(pRes, 0, 8);
		// Copy of pointer size.
		memcpy(pRes, &value, sizeof(void*));
		m_pCommunicator->sendResult(commandID, ERR_NOERROR);
	} else {
		m_pCommunicator->sendResult(commandID, ERR_ALLOCATION);
	}
}

void CKLBDebuggerContext::errResult(u32 commandID, ERROR_TYPE error) {
	u8* pRes = m_pCommunicator->allocateResult(commandID, 0);		// TODO : should have a system : not failed alloc for error return.
	if (pRes) {
		// Return error.
		m_pCommunicator->sendResult(commandID, error);
	}
}
