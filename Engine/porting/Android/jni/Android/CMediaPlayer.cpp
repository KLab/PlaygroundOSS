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
 * CMediaPlayer.cpp
 *
 */

#include "CPFInterface.h"
#include "CMediaPlayer.h"

CMediaPlayer::CMediaPlayer()
{
	jclass local_mp = getEnv()->FindClass("android/media/MediaPlayer");

	jmethodID cns = getEnv()->GetMethodID(local_mp, "<init>", "()V");
	jobject local_obj = getEnv()->NewObject(local_mp, cns);	// C++からアクセスするためのインスタンス作成
	m_obj = getEnv()->NewGlobalRef(local_obj);

	// サポートするメソッドのメソッドIDを取得しておく
	m_setDataSource = getEnv()->GetMethodID(local_mp, "setDataSource", "(Ljava/io/FileDescriptor;)V");

	m_prepare		= getEnv()->GetMethodID(local_mp, "prepare", "()V");
	m_start			= getEnv()->GetMethodID(local_mp, "start", "()V");
	m_stop			= getEnv()->GetMethodID(local_mp, "stop", "()V");
	m_pause			= getEnv()->GetMethodID(local_mp, "pause", "()V");
	m_release		= getEnv()->GetMethodID(local_mp, "release", "()V");
	m_reset			= getEnv()->GetMethodID(local_mp, "reset", "()V");
	m_getCurrentPos = getEnv()->GetMethodID(local_mp, "getCurrentPosition", "()I");

	m_isLooping		= getEnv()->GetMethodID(local_mp, "isLooping", "()Z");
	m_isPlaying		= getEnv()->GetMethodID(local_mp, "isPlaying", "()Z");
	m_setLooping	= getEnv()->GetMethodID(local_mp, "setLooping", "(Z)V");
	m_setVolume		= getEnv()->GetMethodID(local_mp, "setVolume", "(FF)V");

	CJNI::getJNIEnv()->DeleteLocalRef(local_mp);
	//CJNI::getJNIEnv()->DeleteLocalRef(cns);
	CJNI::getJNIEnv()->DeleteLocalRef(local_obj);
}

CMediaPlayer::~CMediaPlayer()
{
	stop();
	release();
	getEnv()->DeleteGlobalRef(m_obj);
}

void
CMediaPlayer::setDataSource(const char * path)
{
	DEBUG_PRINT("CMediaPlayer::setDataSource() in ... m_obj = %p", m_obj);
	jstring jpath = getEnv()->NewStringUTF(path);

	//
	jclass local_fs = getEnv()->FindClass("java/io/FileInputStream");
	jmethodID cns = getEnv()->GetMethodID(local_fs, "<init>", "(Ljava/lang/String;)V");
	jobject local_obj = getEnv()->NewObject(local_fs, cns, jpath);	// C++からアクセスするためのインスタンス作成
	jobject global_obj = getEnv()->NewGlobalRef(local_obj);
	jmethodID getFD = getEnv()->GetMethodID(local_fs, "getFD", "()Ljava/io/FileDescriptor;");

	getEnv()->CallVoidMethod( m_obj,
							  m_setDataSource,
			                  getEnv()->CallObjectMethod(global_obj, getFD) );

	getEnv()->DeleteGlobalRef(global_obj);
	CJNI::getJNIEnv()->DeleteLocalRef(local_fs);
	CJNI::getJNIEnv()->DeleteLocalRef(local_obj);
	CJNI::getJNIEnv()->DeleteLocalRef(jpath);
	exceptionOccurred();
	DEBUG_PRINT("CMediaPlayer::setDataSource(): path = %s", path);
}

void
CMediaPlayer::prepare()
{
	DEBUG_PRINT("CMediaPlayer::prepare() in...");
	getEnv()->CallVoidMethod(m_obj, m_prepare);
	exceptionOccurred();
	DEBUG_PRINT("CMediaPlayer::prepare() exit.");
}

void
CMediaPlayer::start()
{
	DEBUG_PRINT("CMediaPlayer::start() in...");
	getEnv()->CallVoidMethod(m_obj, m_start);
	exceptionOccurred();
	DEBUG_PRINT("CMediaPlayer::start() exit.");
}

void
CMediaPlayer::stop()
{
	DEBUG_PRINT("CMediaPlayer::stop() in...");
	getEnv()->CallVoidMethod(m_obj, m_stop);
	exceptionOccurred();
	DEBUG_PRINT("CMediaPlayer::stop() exit.");
}

void
CMediaPlayer::pause()
{
	DEBUG_PRINT("CMediaPlayer::pause() in...");
	getEnv()->CallVoidMethod(m_obj, m_pause);
	exceptionOccurred();
	DEBUG_PRINT("CMediaPlayer::pause() exit.");
}

void
CMediaPlayer::release()
{
	DEBUG_PRINT("CMediaPlayer::release() in...");
	getEnv()->CallVoidMethod(m_obj, m_release);
	exceptionOccurred();
	DEBUG_PRINT("CMediaPlayer::release() exit.");
}

void
CMediaPlayer::reset()
{
	DEBUG_PRINT("CMediaPlayer::reset() in...");
	getEnv()->CallVoidMethod(m_obj, m_reset);
	exceptionOccurred();
	DEBUG_PRINT("CMediaPlayer::reset() exit.");
}

s32
CMediaPlayer::getCurrentPos()
{
	s32 ret = 0;

	DEBUG_PRINT("CMediaPlayer::getCurrentPos() in...");
	ret = getEnv()->CallIntMethod(m_obj, m_getCurrentPos);
	exceptionOccurred();
	DEBUG_PRINT("CMediaPlayer::getCurrentPos() exit.");

	return ret;
}

bool
CMediaPlayer::isLooping()
{
	jboolean result = getEnv()->CallBooleanMethod(m_obj, m_isLooping);
	exceptionOccurred();
	return (result) ? true : false;
}

bool
CMediaPlayer::isPlaying()
{
	jboolean result = getEnv()->CallBooleanMethod(m_obj, m_isPlaying);
	exceptionOccurred();
	return (result) ? true : false;
}

void
CMediaPlayer::setLooping(bool looping)
{
	DEBUG_PRINT("CMediaPlayer::setLooping() in...");
	getEnv()->CallVoidMethod(m_obj, m_setLooping, (jboolean)looping);
	exceptionOccurred();
	DEBUG_PRINT("CMediaPlayer::setLooping() exit.");
}

void
CMediaPlayer::setVolume(float leftVolume, float rightVolume)
{
	getEnv()->CallVoidMethod(m_obj, m_setVolume, leftVolume, rightVolume);
	exceptionOccurred();
}
