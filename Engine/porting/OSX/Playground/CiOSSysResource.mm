#import <SystemConfiguration/SCNetworkReachability.h>
#include <iostream>
#include "CiOSSysResource.h"
;
CiOSSysResource::CiOSSysResource() : m_size_devId(0), m_devId_received(false) {
}

CiOSSysResource::~CiOSSysResource() {
}

CiOSSysResource&CiOSSysResource::getInstance() {
	static CiOSSysResource instance;
	return instance;
}

void CiOSSysResource::requestDevID() {
}

bool CiOSSysResource::failedDevID() {
	m_devId_received = true;
	m_devId_succeed = false;
	return false;
}

bool CiOSSysResource::setDevID(const void *devToken) {
	unsigned char *ptr = (unsigned char *)devToken;
	for (int i = 0; i < 32; i++) {
		m_devId[i] = ptr[i];
	}
	m_size_devId = 32;
	m_devId_received = true;
	m_devId_succeed = true;
	return true;
}

int CiOSSysResource::getDevID(char *retBuf, int maxlen) {
	char *ptr = retBuf;
	for (int i = 0; i < 32 && i * 2 + 2 < maxlen; i++) {
		sprintf(ptr, "%02x", (int)m_devId[i]);
		ptr += strlen(ptr);
	}
	return strlen(retBuf);
}
