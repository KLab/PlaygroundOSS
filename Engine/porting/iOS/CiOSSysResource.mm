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
//  CiOSSysResource.cpp
//  GameEngine
//
//

#import <UIKit/UIKit.h>
#import <UIKit/UIApplication.h>
#import <SystemConfiguration/SCNetworkReachability.h>
#include <iostream>
#include "CiOSSysResource.h"
#define PUSH_NOTIFICATION_TIMEOUT (10.0f)

;
CiOSSysResource::CiOSSysResource() : m_size_devId(0), m_devId_received(false) {}
CiOSSysResource::~CiOSSysResource() {}

CiOSSysResource&
CiOSSysResource::getInstance()
{
    static CiOSSysResource instance;
    return instance;
}

void
CiOSSysResource::requestDevID()
{
    m_devId_received = false;
    UIRemoteNotificationType types = (UIRemoteNotificationType)((int)UIRemoteNotificationTypeBadge |
                                                                (int)UIRemoteNotificationTypeSound |
                                                                (int)UIRemoteNotificationTypeAlert);
    [[UIApplication sharedApplication] registerForRemoteNotificationTypes:types];
	// avoid iOS 7's "no delegate called when user doesn't permit us push notification alerts" issue
    [NSTimer scheduledTimerWithTimeInterval:PUSH_NOTIFICATION_TIMEOUT
                                     target:[NSBlockOperation blockOperationWithBlock:^{ failedDevID(); }]
                                   selector:@selector(main)
                                   userInfo:nil
                                    repeats:NO];
}

bool
CiOSSysResource::failedDevID()
{
    // don't overwrite devID unless "received" flag is false (i.e. resetted by re-running requestDevID())
    if (m_devId_received) {
        return false;
    }
    m_devId_received = true;
    m_devId_succeed = false;
    return false;
}

bool
CiOSSysResource::setDevID(const void * devToken)
{
    // don't overwrite devID unless "received" flag is false (i.e. resetted by re-running requestDevID())
    if (m_devId_received) {
        return false;
    }
    unsigned char * ptr = (unsigned char *)devToken;
    for(int i = 0; i < 32; i++) {
        m_devId[i] = ptr[i];
    }
    m_size_devId = 32;
    m_devId_received = true;
    m_devId_succeed = true;
    return true;
}

int
CiOSSysResource::getDevID(char * retBuf, int maxlen)
{
    char * ptr = retBuf;
    for(int i = 0; i < 32 && i * 2 + 2 < maxlen; i++) {
        sprintf(ptr, "%02x", (int)m_devId[i]);
        ptr += strlen(ptr);
    }
    return strlen(retBuf);
}
