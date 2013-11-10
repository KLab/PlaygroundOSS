#ifndef CiOSSysResource_h
#define CiOSSysResource_h

class CiOSSysResource
{
private:
	CiOSSysResource();
	virtual ~CiOSSysResource();
public:
	static CiOSSysResource& getInstance();
    
	void requestDevID();
	bool failedDevID();
	bool setDevID(const void *devToken);
	int getDevID(char *retBuf, int maxlen);
    
	inline bool isReceived() {
		return m_devId_received;
	}
    
	inline bool isSucceed() {
		return m_devId_succeed;
	}
    
private:
	unsigned char m_devId[32];
	int m_size_devId;
	bool m_devId_received;
	bool m_devId_succeed;
};

#endif
