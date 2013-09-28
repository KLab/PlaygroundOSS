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
/*!
 ¥brief Android SDK の android.media.MediaPlayer クラスをC++から使うためのサブセットラッピング
 */
#ifndef CMediaPlayer_h
#define CMediaPlayer_h

#include <jni.h>
#include "CJNI.h"

class CMediaPlayer : public CJNI
{
private:
	jclass			m_mp;
	jobject			m_obj;

	jmethodID		m_setDataSource;
	jmethodID		m_prepare;
	jmethodID		m_start;
	jmethodID		m_stop;
	jmethodID		m_pause;
	jmethodID		m_release;
	jmethodID		m_reset;
	jmethodID		m_isLooping;
	jmethodID		m_isPlaying;
	jmethodID		m_setLooping;
	jmethodID		m_setVolume;
	jmethodID		m_getCurrentPos;

	jobject			m_fileDescriptorObj;
	jmethodID		m_fileDescriptorFunc;
	jmethodID		m_getFDFunc;
public:
	CMediaPlayer();
	virtual ~CMediaPlayer();

	void setDataSource(const char * path);
	void prepare();
	void start();
	void stop();
	void pause();
	void release();
	void reset();
	s32  getCurrentPos();
	bool isLooping();
	bool isPlaying();
	void setLooping(bool looping);
	void setVolume(float leftVolume, float rightVolume);
};
#endif /* CMediaPlayer_h */
