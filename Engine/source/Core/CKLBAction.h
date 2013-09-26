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
// === Structure used for transmitting events inside the game ===
//
//

#ifndef __KLB_ACTION__
#define __KLB_ACTION__

#include "CKLBObject.h"

enum ACTION_TYPE {
	ACTION_UNDEF			= 0,
	ACTION_PUSH				= 1,
	ACTION_RELEASE			= 2,	// Param 0 : Ok, 1 : Cancel
	ACTION_CLICK			= 3,
	ACTION_CHANGE			= 4,	// 1 : Select, 0 : Unselect
	ACTION_CLOSE			= 5,
	ACTION_ENDANIM			= 6,
	ACTION_FOCUS			= 7,
	ACTION_STATECHANGE		= 8,
	ACTION_CUSTOM			= 0x10
};

/**
	Action is an event class used by the application
	for transmitting events / asynchronously perform function call.
 */
class CKLBAction {
public:
	/**
		- Key Event
		- Touch Event
		- UI event forwarding	(close, focus, etc...)
		- Custom Game event forwarding	(attack, move, etc...)
	 */
	u32				m_actionType;
	u32				m_timeOffset;
	s32				m_parameter;
	CKLBObject*		m_pSource;
	CKLBObject*		m_pTarget;
};

#endif
