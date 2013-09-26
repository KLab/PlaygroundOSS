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
//  CiOSWebView.cpp
//  GameEngine
//
//

#import "CiOSWebView.h"

static int nonceSeed = 0;

@implementation CiOSWebView


- (void)setCustomHeaders:(const char *)token :(const char *)region :(const char *)client :(const char *)consumerKey :(const char *)applicationId :(const char *)userId :(const char *)env
{
    [m_token release];
    [m_region release];
    [m_client release];
    [m_cKey release];
    [m_appID release];
    [m_userID release];
    [m_os release];
    [m_version release];
    [m_timezone release];

    if(token) m_token = [[NSString stringWithUTF8String:token] retain];
    if(region) m_region = [[NSString stringWithUTF8String:region] retain];
    if(client) m_client = [[NSString stringWithUTF8String:client] retain];
    if(consumerKey) m_cKey = [[NSString stringWithUTF8String:consumerKey] retain];
    if(applicationId) m_appID = [[NSString stringWithUTF8String:applicationId] retain];
    if(userId) m_userID = [[NSString stringWithUTF8String:userId] retain];
    
    NSString * nsenv = [NSString stringWithUTF8String:env];
    NSArray * arr = [nsenv componentsSeparatedByString:@";"];
    m_os = [[arr objectAtIndex:0] retain];
    m_version = [[arr objectAtIndex:1] retain];
    m_timezone = [[arr objectAtIndex:2] retain];
}

- (BOOL)hasCustomHeaders:(NSURLRequest *)request
{
    NSDictionary *headers = [request allHTTPHeaderFields];

    for(NSString *key in [headers allKeys]) {
        if([[key lowercaseString] isEqualToString:@"os"]) {
            return YES;
        }
    }

    return NO;
}

- (void)loadRequest:(NSURLRequest *)request
{
    NSMutableURLRequest * mutableRequest = (NSMutableURLRequest *)[request mutableCopy];

    if(m_client) [mutableRequest setValue:m_client forHTTPHeaderField:@"Client-Version"];
    if(m_version) [mutableRequest setValue:m_version forHTTPHeaderField:@"OS-Version"];
    if(m_os) [mutableRequest setValue:m_os forHTTPHeaderField:@"OS"];
    if(m_timezone) [mutableRequest setValue:m_timezone forHTTPHeaderField:@"Time-Zone"];
    if(m_region) [mutableRequest setValue:m_region forHTTPHeaderField:@"Region"];
    [mutableRequest setValue:@"straightforward" forHTTPHeaderField:@"API-Model"];
    if(m_appID) [mutableRequest setValue:m_appID forHTTPHeaderField:@"Application-ID"];
    if(m_userID) [mutableRequest setValue:m_userID forHTTPHeaderField:@"User-ID"];
	time_t now;
	time(&now);

    NSString * auth = [NSString stringWithFormat:@"consumerKey=%@&token=%@&version=1.1&timeStamp=%ld&nonce=WV%d", m_cKey, m_token, now, nonceSeed];
    nonceSeed++;
    [mutableRequest setValue:auth forHTTPHeaderField:@"Authorize"];
    
    [super loadRequest:mutableRequest];
}

- (void)dealloc
{
    [m_token release];
    [m_region release];
    [m_client release];
    [m_cKey release];
    [m_appID release];
    [m_userID release];
    [m_os release];
    [m_version release];
    [m_timezone release];
    
    [super dealloc];
}

@end
