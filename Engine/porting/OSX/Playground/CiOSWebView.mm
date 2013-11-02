#import "CiOSWebView.h"

static int nonceSeed = 0;

@implementation CiOSWebView

- (void)setCustomHeaders:(const char *)token:(const char *)region:(const char *)client:(const char *)consumerKey:(const char *)applicationId:(const char *)userId:(const char *)env {
	[m_token release];
	[m_region release];
	[m_client release];
	[m_cKey release];
	[m_appID release];
	[m_userID release];
	[m_os release];
	[m_version release];
	[m_timezone release];
    
	if (token) m_token = [[NSString stringWithUTF8String:token] retain];
	if (region) m_region = [[NSString stringWithUTF8String:region] retain];
	if (client) m_client = [[NSString stringWithUTF8String:client] retain];
	if (consumerKey) m_cKey = [[NSString stringWithUTF8String:consumerKey] retain];
	if (applicationId) m_appID = [[NSString stringWithUTF8String:applicationId] retain];
	if (userId) m_userID = [[NSString stringWithUTF8String:userId] retain];
    
	NSString *nsenv = [NSString stringWithUTF8String:env];
	NSArray *arr = [nsenv componentsSeparatedByString:@";"];
	m_os = [[arr objectAtIndex:0] retain];
	m_version = [[arr objectAtIndex:1] retain];
	m_timezone = [[arr objectAtIndex:2] retain];
}

- (void)loadRequest:(NSURLRequest *)request {
	NSMutableURLRequest *mutableRequest = (NSMutableURLRequest *)[request mutableCopy];
    
	if (m_client) [mutableRequest setValue:m_client forHTTPHeaderField:@"Client-Version"];
	if (m_version) [mutableRequest setValue:m_version forHTTPHeaderField:@"OS-Version"];
	if (m_os) [mutableRequest setValue:m_os forHTTPHeaderField:@"OS"];
	if (m_timezone) [mutableRequest setValue:m_timezone forHTTPHeaderField:@"Time-Zone"];
	if (m_region) [mutableRequest setValue:m_region forHTTPHeaderField:@"Region"];
	[mutableRequest setValue:@"straightforward" forHTTPHeaderField:@"API-Model"];
	if (m_appID) [mutableRequest setValue:m_appID forHTTPHeaderField:@"Application-ID"];
	if (m_userID) [mutableRequest setValue:m_userID forHTTPHeaderField:@"User-ID"];
	time_t now;
	time(&now);
    
	NSString *auth = [NSString stringWithFormat:@"consumerKey=%@&token=%@&version=1.1&timeStamp=%ld&nonce=WV%d", m_cKey, m_token, now, nonceSeed];
	nonceSeed++;
	[mutableRequest setValue:auth forHTTPHeaderField:@"Authorize"];
}

- (void)dealloc {
	[m_token release];
	[m_region release];
	[m_client release];
	[m_cKey release];
	[m_appID release];
	[m_userID release];
	[m_os release];
	[m_version release];
	[m_timezone release];
}

@end
