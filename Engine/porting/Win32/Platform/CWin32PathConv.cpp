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
//  W32PathConv.cpp
//
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include "CWin32PathConv.h"
#include "CPFInterface.h"

CWin32PathConv::CWin32PathConv() : m_build(false), m_external(NULL), m_install(NULL) {}
CWin32PathConv::~CWin32PathConv() {
    delete [] m_external;
    delete [] m_install;
}

CWin32PathConv&
CWin32PathConv::getInstance()
{
    static CWin32PathConv instance;
    return instance;
}

void
CWin32PathConv::setPath(const char * pathInstall, const char * pathExtern)
{
	g_pathInstall = pathInstall;
	g_pathExtern  = pathExtern;
}

const char *
CWin32PathConv::makePath(const char * path, const char * suffix, const char * base)
{
    int extlen  = (suffix) ? strlen(suffix) : 0;
    int len     = strlen(path) + strlen(base) + extlen + 2;
    char * buf  = new char [ len ];

	strcpy(buf, base);
    //strcat(buf, "/");
    strcat(buf, path);
    if(suffix) { strcat(buf, suffix); }
    CPFInterface::getInstance().platform().logging("fullpath: %s", buf);
    return (const char *)buf;
}

bool
CWin32PathConv::checkExists(const char * path)
{
    bool bResult = true;
    struct stat st;
    int iRes = stat(path, &st);
    if((iRes != 0) && (errno == ENOENT)) { bResult = false; }
    return bResult;
}

const char *
CWin32PathConv::fullpath(const char * url, const char * suffix, bool* isReadOnly)
{
    build();
	// Default
	if (isReadOnly) { *isReadOnly = true; }

    if (!strncmp(url, "asset://", 8)) {
        const char * path;
        path = makePath(url + 8, suffix, m_external);
        if(checkExists(path)) {
			if (isReadOnly) { *isReadOnly = false; }
			return path;
		}
        delete [] path;
        
        path = makePath(url + 8, suffix, m_install);
        if(checkExists(path)) { return path; }
        delete [] path;

		CPFInterface::getInstance().platform().logging("[file]: not found '%s%s'", url, suffix);

        return NULL;
    }
	const char * path = url;
    if (!strncmp(path, "external/", 9)) {
		if (isReadOnly) { *isReadOnly = false; }
		return makePath(path + 9, suffix, m_external);
	}
    if (!strncmp(path, "install/", 8)) { return makePath(path + 8, suffix, m_install); }
    return NULL;
}

extern char* g_pathExtern;
extern char* g_pathInstall;

void
CWin32PathConv::create_external()
{
    int length = strlen(g_pathExtern);
    char * buf = new char [length + 1];
    strcpy(buf, g_pathExtern);
    m_external = (const char *)buf;
}

void
CWin32PathConv::create_install()
{
    int length = strlen(g_pathInstall);
    char * buf = new char [length + 1];
    strcpy(buf, g_pathInstall);
    m_install = (const char *)buf;
}

void
CWin32PathConv::build()
{
    if(m_build) return;
    create_install();
    create_external();
    m_build = true;
}
