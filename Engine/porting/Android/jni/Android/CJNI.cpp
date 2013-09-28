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
/*
 * CJNI.cpp
 *
 */
#include "CJNI.h"
#include <cstddef>
#include <jni.h>
#include <android/log.h>

JNIEnv * CJNI::p_jniEnv = NULL;
JavaVM * CJNI::p_javaVM = NULL;

void
CJNI::setJavaVM(JavaVM* vm)
{
	p_javaVM = vm;
}

JNIEnv *
CJNI::setJNIEnv(JNIEnv * pEnv)
{
	p_jniEnv = pEnv;
	return p_jniEnv;
}

JNIEnv *
CJNI::getJNIEnv()
{
	if (p_javaVM != NULL) {
		JNIEnv *env;
		jint ret = p_javaVM->GetEnv((void**)&env, JNI_VERSION_1_6);
		if(ret != JNI_OK) {
			return  NULL;
		}
		return env;
	}
	return NULL;
}

JNIEnv *
CJNI::attachJNIEnv()
{
	if (p_javaVM != NULL) {
		JNIEnv *env;
		jint ret = p_javaVM->AttachCurrentThread(&env, NULL);
		if(ret != JNI_OK) {
			return  NULL;
		}
		return env;
	}
	return NULL;
}

void
CJNI::detachJNIEnv()
{
	if (p_javaVM != NULL) {
		p_javaVM->DetachCurrentThread();
	}
}

void
CJNI::exceptionOccurred()
{
	jthrowable throwObj;
	throwObj = p_jniEnv->ExceptionOccurred();
	if(throwObj) {
		p_jniEnv->ExceptionDescribe();
		p_jniEnv->ExceptionClear();
	}
}
