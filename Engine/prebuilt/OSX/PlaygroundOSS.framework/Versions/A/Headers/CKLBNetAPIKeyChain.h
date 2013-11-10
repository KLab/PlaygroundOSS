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
//  CKLBNetAPIKeyChain.h
//  GameEngine
//

#ifndef CKLBNetAPIKeyChain_h
#define CKLBNetAPIKeyChain_h

#include "CKLBUtility.h"

/*!
* \class CKLBNetAPIKeyChain
* \brief Net API Key Chain Class
* 
* 
*/
class CKLBNetAPIKeyChain
{
private:
    CKLBNetAPIKeyChain();
    virtual ~CKLBNetAPIKeyChain();
public:
    static CKLBNetAPIKeyChain& getInstance();
	void release();

    inline const char * setToken(const char * token) {
        KLBDELETEA(m_token);
		if (token) {
	        m_token = CKLBUtility::copyString(token);
		} else {
			m_token = NULL;
		}
        return m_token;
    }
    
    inline const char * setRegion(const char * region) {
        KLBDELETEA(m_region);
		if (region) {
	        m_region = CKLBUtility::copyString(region);
		} else {
			m_region = NULL;
		}
        return m_region;
    }
    
    inline const char * setClient(const char * client) {
        KLBDELETEA(m_client);
		if (client) {
	        m_client = CKLBUtility::copyString(client);
		} else {
			m_client = NULL;
		}
        return m_client;
    }
    
    inline const char * setConsumernKey(const char * cKey) {
        KLBDELETEA(m_cKey);
		if (cKey) {
	        m_cKey = CKLBUtility::copyString(cKey);
		} else {
			m_cKey = NULL;
		}
        return m_cKey;
    }

    inline const char * setAppID(const char * appID) {
        KLBDELETEA(m_appID);
		if (appID) {
	        m_appID = CKLBUtility::copyString(appID);
		} else {
			m_appID = NULL;
		}
        return m_appID;
    }

	inline const char * setUserID(const char * userID) {
		KLBDELETEA(m_userID);
		if (userID) {
			m_userID = CKLBUtility::copyString(userID);
		} else {
			m_userID = NULL;
		}
		return m_userID;
	}
    
    inline const char * getToken		() const { return m_token;	}
    inline const char * getRegion		() const { return m_region; }
    inline const char * getClient		() const { return m_client; }
    inline const char * getConsumerKey	() const { return m_cKey;	}
    inline const char * getAppID		() const { return m_appID;	}
	inline const char * getUserID		() const { return m_userID; }

	inline int genCmdNumID(char * retBuf, const char * body, time_t timeStamp, int serial) {
		sprintf(retBuf, "%s-%s.%d.%d",
				body, m_token,
				(int)timeStamp, serial);
		int len = strlen(retBuf);
		return len;
	}

private:
    const char      *   m_token;    // Authorized Token
    const char      *   m_region;   // region
    const char      *   m_client;   // client version
    const char      *   m_cKey;     // consumerKey
    const char      *   m_appID;    // Application ID
	const char		*	m_userID;	// User-ID
};

#endif
