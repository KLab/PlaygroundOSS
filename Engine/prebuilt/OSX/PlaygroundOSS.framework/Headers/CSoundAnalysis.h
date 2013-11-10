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
 @file      CSoundAnalysis.h
 @brief     サウンドファイルの解析など
*/

#ifndef __SOUND_ANALYSIS_H__
#define __SOUND_ANALYSIS_H__

#include "BaseType.h"

/*
 @enum  eBITRATE_TYPE
 */
enum eBITRATE_TYPE
{
    eBITRATE_TYPE_NONE = -1,
    
    eBITRATE_TYPE_VBR = 0,  // 可変ビットレート
    eBITRATE_TYPE_CBR,      // 固定ビットレート
    eBITRATE_TYPE_ABR,      // 平均ビットレート
    
    eBITRATE_TYPE_MAX,
};

/*
 @struct sSoundAnalysisData
 */
typedef struct strSoundAnalysisData
{
    eBITRATE_TYPE   m_bitRateType;  //!< ビットレートのタイプ(固定,可変,平均)
    s16             m_bitRate;      //!< ビットレート(単位:kbps)
    u16             m_samplingRate; //!< サンプリングレート(単位:kHz)
    s32             m_totalFrame;   //!< サウンドの再生フレーム数
    s64             m_totalTime;    //!< サウンドの再生時間(ミリ秒)
} sSoundAnalysisData;


/*
 @brief  サウンドファイルのいろいろな情報を取得
 @param[in]     const char* _path          サウンドファイル名
 @param[out]    sSoundAnalysisData* _data  指定サウンドファイルのいろいろな情報格納用
 @return        void
 */
bool GetSoundAnalysisData( const char* _path, sSoundAnalysisData* _data );

/*
 @brief  サウンドファイルの演奏時間を取得
 @param[in]  const char* _path   サウンドファイル名
 @return     u32                 指定のサウンドファイルの演奏時間
 */
u32 GetSoundTotalTime( const char* _path );

#endif
