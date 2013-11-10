#ifndef CiOSTmpFile_h
#define CiOSTmpFile_h

#include <iostream>
#include "ITmpFile.h"

class CiOSTmpFile : public ITmpFile
{
public:
	CiOSTmpFile(const char *tmpPath);
	virtual ~CiOSTmpFile();
    
	size_t writeTmp(void *ptr, size_t size);
    
	inline bool isReady() {
		return (m_fd > 0) ? true : false;
	}
    
private:
	const char *m_fullpath;
	int m_fd;
};


#endif
