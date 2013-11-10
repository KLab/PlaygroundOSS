#ifndef CiOSWebView_h
#define CiOSWebView_h

@interface CiOSWebView {
@private
	NSString *m_token;
	NSString *m_region;
	NSString *m_client;
	NSString *m_cKey;
	NSString *m_appID;
	NSString *m_userID;
    
	NSString *m_os;
	NSString *m_version;
	NSString *m_timezone;
}

- (void)setCustomHeaders:(const char *)token:(const char *)region:(const char *)client:(const char *)consumerKey:(const char *)applicationId:(const char *)userId:(const char *)env;

@end

#endif
