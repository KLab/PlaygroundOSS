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
//  CiOSWebView.h
//  GameEngine
//
//

#ifndef CiOSWebView_h
#define CiOSWebView_h

#import <UIKit/UIKit.h>

@interface CiOSWebView : UIWebView {

@private
    NSString * m_token;
    NSString * m_region;
    NSString * m_client;
    NSString * m_cKey;
    NSString * m_appID;
    NSString * m_userID;
    
    NSString * m_os;
    NSString * m_version;
    NSString * m_timezone;
}

- (void)setCustomHeaders:(const char *)token :(const char *)region :(const char *)client :(const char *)consumerKey :(const char *)applicationId :(const char *)userId :(const char *)env;
- (BOOL)hasCustomHeaders:(NSURLRequest *)request;

@end

#endif
