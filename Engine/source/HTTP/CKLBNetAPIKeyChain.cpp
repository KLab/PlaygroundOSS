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
//  CKLBNetAPIKeyChain.cpp
//  GameEngine
//

#include "CKLBNetAPIKeyChain.h"


CKLBNetAPIKeyChain::CKLBNetAPIKeyChain()
: m_token   (NULL)
, m_region  (NULL)
, m_client  (NULL)
, m_cKey    (NULL)
, m_appID   (NULL)
, m_userID  (NULL) 
{
}

CKLBNetAPIKeyChain::~CKLBNetAPIKeyChain()
{
	release();
}

CKLBNetAPIKeyChain&
CKLBNetAPIKeyChain::getInstance()
{
    static CKLBNetAPIKeyChain instance;
    return instance;
}

void 
CKLBNetAPIKeyChain::release() {
    KLBDELETEA(m_token);
	m_token		= NULL;
    KLBDELETEA(m_region);
	m_region	= NULL;
    KLBDELETEA(m_client);
	m_client	= NULL;
    KLBDELETEA(m_cKey);
	m_cKey		= NULL;
    KLBDELETEA(m_appID);
	m_appID		= NULL;
	KLBDELETEA(m_userID);
	m_userID	= NULL; // 2012.11.27  解放漏れがあったので修正
}
