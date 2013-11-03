#include <sys/stat.h>
#include <errno.h>
#include "CiOSPathConv.h"
#include "CPFInterface.h"


CiOSPathConv::CiOSPathConv() : m_build(false), m_external(0), m_install(0) {
}

CiOSPathConv::~CiOSPathConv() {
	delete[] m_external;
	delete[] m_install;
}

CiOSPathConv&CiOSPathConv::getInstance() {
	static CiOSPathConv instance;
	return instance;
}

const char *CiOSPathConv::makePath(const char *path, const char *suffix, const char *base) {
	int extlen = (suffix) ? strlen(suffix) : 0;
	int len = strlen(path) + strlen(base) + extlen + 2;
	char *buf = new char[len];
	strcpy(buf, base);
	//strcat(buf, "/");
	strcat(buf, path);
	if (suffix) strcat(buf, suffix);
	//CPFInterface::getInstance().platform().logging("fullpath: %s", buf);
	return (const char *)buf;
}

bool CiOSPathConv::checkExists(const char *path) {
	bool bResult = true;
	struct stat st;
	int iRes = stat(path, &st);
	if ((iRes != 0) && (errno == ENOENT)) bResult = false;
	return bResult;
}

const char *CiOSPathConv::fullpath(const char *url, const char *suffix, bool *isReadOnly) {
	build();
	if (isReadOnly) {
		*isReadOnly = true;
	}
    
	// assets が指定されている場合、まずは external から探し、
	// 見つからなければ install から探す。どちらもなければ 0 を返す。
	if (!strncmp(url, "asset://", 8)) {
		const char *path;
		path = makePath(url + 8, suffix, m_external);
		if (checkExists(path)) {
			if (isReadOnly) {
				*isReadOnly = false;
			}
			return path;
		}
		delete[] path;
        
		path = makePath(url + 8, suffix, m_install);
		if (checkExists(path)) return path;
		delete[] path;
        
		// ファイルが見つからなかったのでログを出しとく
		CPFInterface::getInstance().platform().logging("[file]: not found '%s%s'", url, suffix);
        
		return 0;
	}
    
	if (!strncmp(url, "external/", 9)) {
		if (isReadOnly) {
			*isReadOnly = false;
		}
		return makePath(url + 9, suffix, m_external);
	}
	if (!strncmp(url, "install/", 8)) return makePath(url + 8, suffix, m_install);
	return 0;
}

void CiOSPathConv::create_external() {
	// file://external を作る
	NSString *nshome = NSHomeDirectory();
	const char *home = [nshome UTF8String];
	int length = strlen(home) + strlen(PATH_EXTERN);
	char *buf = new char[length + 1];
	strcpy(buf, home);
	strcat(buf, PATH_EXTERN);
	m_external = (const char *)buf;
	if (mkdir(m_external, 0755) == 0) {
		CPFInterface::getInstance().platform().excludePathFromBackup(m_external);
	}
}

void CiOSPathConv::create_install() {
	// file://install を作る
	NSString *nshome = [[NSBundle mainBundle] bundlePath];
	const char *home = [nshome UTF8String];
	int length = strlen(home) + strlen(PATH_INSTALL);
	char *buf = new char[length + 1];
	strcpy(buf, home);
	strcat(buf, PATH_INSTALL);
	m_install = (const char *)buf;
}

void CiOSPathConv::build() {
	if (m_build) return;
	create_install();
	create_external();
	m_build = true;
}
