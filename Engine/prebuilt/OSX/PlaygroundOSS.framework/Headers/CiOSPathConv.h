#ifndef CiOSPathConv_h
#define CiOSPathConv_h

#include "iOSFileLocation.h"

class CiOSPathConv
{
private:
	CiOSPathConv();
	virtual ~CiOSPathConv();
    
public:
	static CiOSPathConv& getInstance();
    
	const char *fullpath(const char *url, const char *suffix = 0, bool *isReadOnly = NULL);
    
	const char *install() {
		build(); return m_install;
	}
    
	const char *external() {
		build(); return m_external;
	}
    
private:
	const char *makePath(const char *path, const char *suffix, const char *base);
	bool checkExists(const char *path);
    
	void build();
	void create_external();
	void create_install();
    
private:
	bool m_build;
	const char *m_external;
	const char *m_install;
};

#endif
