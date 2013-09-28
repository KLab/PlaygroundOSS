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
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include "CJNI.h"
#include "CAndroidPathConv.h"
#include "CPFInterface.h"
#include "PackageDefine.h"

CAndroidPathConv::CAndroidPathConv() : m_build(false), m_external(0), m_install(0) {}
CAndroidPathConv::~CAndroidPathConv() {
    delete [] m_external;
    delete [] m_install;
}

CAndroidPathConv&
CAndroidPathConv::getInstance()
{
    static CAndroidPathConv instance;
    return instance;
}

const char *
CAndroidPathConv::makePath(const char * path, const char * suffix, const char * base)
{
    int extlen = (suffix) ? strlen(suffix) : 0;
    int len = strlen(path) + strlen(base) + extlen + 2;
    char * buf = new char [ len ];
    strcpy(buf, base);
    //strcat(buf, "/");
    strcat(buf, path);
    if(suffix) strcat(buf, suffix);
    //DEBUG_PRINT("fullpath: %s", buf);
    return (const char *)buf;
}

bool
CAndroidPathConv::checkExists(const char * path)
{
    bool bResult = true;
    struct stat st;
    int iRes = stat(path, &st);
    if((iRes != 0) && (errno == ENOENT)) bResult = false;
    return bResult;
}

const char *
CAndroidPathConv::fullpath(const char * url, const char * suffix, bool* isReadOnly)
{
    build();

	// Default
	if( isReadOnly ) *isReadOnly = true;

    // assets が指定されている場合、まずは external から探し、
    // 見つからなければ install から探す。どちらもなければ 0 を返す。
    if (!strncmp(url, "asset://", 8)) {
        const char * path;
        path = makePath(url + 8, suffix, m_external);
        if(checkExists(path))
		{
			if( isReadOnly ) { *isReadOnly = false; }
			return path;
		}
        delete [] path;

        path = makePath(url + 8, suffix, m_install);
        if(checkExists(path)) return path;
        delete [] path;
        return 0;
    }

	const char* path = url;
	if( !strncmp(url, "external/", 9) )
	{
		if( isReadOnly ) { *isReadOnly = false; }
		return makePath(url + 9, suffix, m_external);
	}
    if (!strncmp(url, "install/", 8)) return makePath(url + 8, suffix, m_install);
    return 0;
}

void
CAndroidPathConv::create_external()
{
    // Java 側で生成した、file://external に相当するpathを初回のみ取得し、以後保持する。
	jclass cls_pfif = CJNI::getJNIEnv()->FindClass(JNI_LOAD_PATH);
	jfieldID id_external = CJNI::getJNIEnv()->GetStaticFieldID(cls_pfif, "m_path_external", "Ljava/lang/String;");
	jstring obj_external = (jstring)CJNI::getJNIEnv()->GetStaticObjectField(cls_pfif, id_external);
	const char* str1 = CJNI::getJNIEnv()->GetStringUTFChars(obj_external, 0);
	char * buf = new char [ strlen(str1) + 1 ];
	strcpy(buf, str1);
	m_external = (const char *)buf;

	CJNI::getJNIEnv()->DeleteLocalRef(cls_pfif);
	//CJNI::getJNIEnv()->DeleteLocalRef(id_external);
	CJNI::getJNIEnv()->DeleteLocalRef(obj_external);
}

void
CAndroidPathConv::create_install()
{
    // Java 側で生成した、file://install に相当するpathを初回のみ取得し、以後保持する。
	jclass cls_pfif = CJNI::getJNIEnv()->FindClass(JNI_LOAD_PATH);
	jfieldID id_install = CJNI::getJNIEnv()->GetStaticFieldID(cls_pfif, "m_path_install", "Ljava/lang/String;");
	jstring obj_install = (jstring)CJNI::getJNIEnv()->GetStaticObjectField(cls_pfif, id_install);
	const char* str1 = CJNI::getJNIEnv()->GetStringUTFChars(obj_install, 0);
	char * buf = new char [ strlen(str1) + 1 ];
	strcpy(buf, str1);
	m_install = (const char *)buf;

	CJNI::getJNIEnv()->DeleteLocalRef(cls_pfif);
	//CJNI::getJNIEnv()->DeleteLocalRef(id_install);
	CJNI::getJNIEnv()->DeleteLocalRef(obj_install);
}

void
CAndroidPathConv::build()
{
    if(m_build) return;
    CPFInterface::getInstance().platform().logging("build base path.");
    create_install();
    create_external();
    CPFInterface::getInstance().platform().logging("install: %s, external: %s", m_install, m_external);
    m_build = true;
}
