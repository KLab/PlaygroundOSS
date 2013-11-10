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
//
// === Debugger System ===
//
//

#ifndef __KLB_DEBUGGER__
#define __KLB_DEBUGGER__

#include "CKLBObject.h"

class CKLBDebuggerContext;
class IKLBDebuggerCommunicator;

class CKLBDebuggerContext:public CKLBContext {
public:
	CKLBDebuggerContext(u32 size);
	~CKLBDebuggerContext();

	/**
		Available command for the debugger.
	 */
	enum COMMAND_TYPE {
		GET_ALL_OBJECT		= 0x01,
		GET_TYPE			= 0x02,
		GET_PROPCOUNT		= 0x03,
		GET_VALUE			= 0x04,
		GET_CLASSNAME		= 0x05,
		GET_PROPNAME		= 0x06,
		SET_VALUE			= 0x07,
		SCREEN_SHOT			= 0x08,
		SET_ASSET			= 0x09,
		GET_PROPID			= 0x0A,
		GET_FORMAT			= 0x0B,
		
		// 0xC,0xD,0xE,0xF,0x10,0x11,0x12 free to use.

		QUERY_GAMESTOP		= 0x13,
		QUERY_GAMESTART		= 0x14,
	};

	/**
		Possible error code return instead of size to the remote device.
	 */
	enum ERROR_TYPE {
		ERR_NOERROR			= 0,			//	No error, replace with correct size during transport.
		ERR_PROCESS			= 0xCAFEDE00,	// 	Impossible to process.
		ERR_INTERNAL		= 0xCAFEDE01,	//	Internal Error.
		ERR_ALLOCATION		= 0xCAFEDE02,	//	Allocation error.
		ERR_INVALIDREQ		= 0xCAFEDE03,	//	Malformed command or parameter.
	};
	
	enum CLASS_GROUP {
		CLSGRP_GAME			= 0x00000000,
		CLSGRP_ENGINE		= 0x40000000,
		CLSGRP_BASIC		= 0x80000000,
		CLSGRP_BASICPTR		= 0x81000000,
		CLSGRP_NULL			= 0xFFFFFFFF
	};

public:
	void setupReceiver			(IKLBDebuggerCommunicator* pCommunicator);
	void receiveCommand			(u32 commandID, COMMAND_TYPE commandType, u8* data, u32 dataSize);

private:
	IKLBDebuggerCommunicator*	m_pCommunicator;
	
	void returnResultString		(u32 commandID, const char* string);
	void returnResult4			(u32 commandID, u32 value);
	void returnResult12			(u32 commandID, u32 classID, void* value);
	void errResult				(u32 commandID, ERROR_TYPE error);
};
	
class IKLBDebuggerCommunicator {
public:
	/**
		Called by debugger when assigning the interface.
	 */
	virtual void assignDebugger	(CKLBDebuggerContext* pDebugger) = 0;

	/**
		Called by debugger to request memory for communicator to transmit result.
		Communicator can free the memory once data is transmitted.
		
		Note : In case of allocation failure, the debugger will NOT call sendResult
				Thus, a failure in allocate result should return an error message to the remote device waiting for results.
	 */
	virtual u8* allocateResult	(u32 commandID, u32 size) = 0;

	/**
		Called by debugger once data is setup and successfull.
	 */
	virtual void sendResult		(u32 commandID, CKLBDebuggerContext::ERROR_TYPE err) = 0;
};

#endif
