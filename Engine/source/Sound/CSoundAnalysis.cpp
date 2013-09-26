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
 @file   CSoundAnalysis.cpp
 @brief  サウンドファイルの解析など
*/

#include <string.h>
#include "CSoundAnalysis.h"
#include "CSoundAnalysisMP3.h"

/*
 @brief  サウンドファイルのいろいろな情報を取得
 @param[in]     const char* _path          サウンドファイル名
 @param[out]    sSoundAnalysisData* _data  指定サウンドファイルのいろいろな情報格納用
 @return        void
 */
bool GetSoundAnalysisData( const char* _path, sSoundAnalysisData* _data )
{
    if( _path == NULL || _data == NULL ) return false;
    
    bool bAnalysis = false;
    
    // 拡張子をチェックしてそれぞれの解析を行う
    if( strstr(_path, ".mp3") )
    {
        // MP3
        bAnalysis = SoundAnalysis_MP3( _path, _data );
    }
    else if( strstr(_path, ".ogg") )
    {
        // OGG
    }
    
    return bAnalysis;
}

/*
 @brief  サウンドファイルの演奏時間を取得
 @param[in] const char* _path   サウンドファイル名
 @return    u32                 指定のサウンドファイルの演奏時間
 */
u32 GetSoundTotalTime( const char* _path )
{
    sSoundAnalysisData data;
    bool bAnalysis = false;
    
    bAnalysis = GetSoundAnalysisData( _path, &data );
    
    if( bAnalysis ) {
        return (u32)data.m_totalTime;
    }
    return 0;
}




