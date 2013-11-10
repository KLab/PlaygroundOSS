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
 @file      CSoundAnalysisMP3.h
 @brief     MP3形式のサウンドファイルの解析など
 */

#ifndef __SOUND_ANALYSIS_MP3_H__
#define __SOUND_ANALYSIS_MP3_H__

#include "CSoundAnalysis.h"

/*
 @brief  mp3形式のサウンドファイル解析
 @param[in] const char* _path                   サウンドファイルのパス
 @param[in] sSoundAnalysisData* _analysisData   サウンドファイルの解析結果渡す用
 @return    bool    true:解析完了, false:解析失敗
 */
bool SoundAnalysis_MP3( const char* _path, sSoundAnalysisData* _analysisData );


#endif
