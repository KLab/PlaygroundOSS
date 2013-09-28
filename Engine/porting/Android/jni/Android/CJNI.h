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
 ¥brief	JNI環境のラッピング基底クラス
 ¥file	CJNI.h
 */
#ifndef CJNI_h
#define CJNI_h

#include <jni.h>

class CJNI
{
private:
	static JNIEnv	* p_jniEnv;
	static JavaVM   * p_javaVM;
protected:
	inline JNIEnv * getEnv() { return p_jniEnv; }
	void exceptionOccurred();
public:
	static void setJavaVM(JavaVM* vm);
	static JNIEnv * setJNIEnv(JNIEnv * pEnv);
	static JNIEnv * getJNIEnv();
	static JNIEnv * attachJNIEnv();
	static void detachJNIEnv();
};

#endif /* CJNI_h */
