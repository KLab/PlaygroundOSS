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
 @file      CSoundAnalysisMP3.cpp
 @brief     MP3形式のサウンドファイルの解析など
 */

#include <string.h>
#include "CPFInterface.h"
#include "CSoundAnalysisMP3.h"
#include "encryptFile.h"

// ビットレート表
// MPEG1
static const short s_MPEG1_BitRateTbl[3][14] =
{
    { 32, 40, 48, 56,  64,  80,  96,  112, 128, 160, 192, 224, 256, 320 },  // layer3
    { 32, 48, 56, 64,  80,  96,  112, 128, 160, 192, 224, 256, 320, 384 },  // layer2
    { 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448 }   // layer1
};

// MPEG2
static const short s_MPEG2_BitRateTbl[3][14] =
{
    { 8,  16, 24, 32, 40, 48, 56,  64,  80,  96,  112, 128, 144, 160 }, // layer3
    { 8,  16, 24, 32, 40, 48, 56,  64,  80,  96,  112, 128, 144, 160 }, // layer2
    { 32, 48, 56, 64, 80, 96, 112, 128, 144, 160, 176, 192, 224, 256 }  // layer1
};

// MPEG2.5
static const short s_MPEG2_5_BitRateTbl[1][14] =
{
    { 8,  16, 24, 32, 40, 48, 56,  64,  80,  96,  112, 128, 144, 160 }  //
};

// サンプリングレート表
static const unsigned short s_SamplingTbl[3][3] =
{
    { 44100, 48000, 32000 }, // MPEG1
    { 22050, 24000, 16000 }, // MEPG2
    { 11025, 12000, 8000  }  // MPEG2.5
};

// フレームあたりのサンプル数テーブル
static const short s_SamplePerFrame[3][3] =
{
    // MPEG1, MPEG2, MPEG2.5
    { 1152, 576,  576  },  // layer3
    { 1152, 1152, 1152 },  // layer2
    { 384,  384,  384  }   // layer1
};

enum eMPEG_VER
{
    eMPEG_VER_NONE = -1,
    
    eMPEG_VER_1 = 0,    // MPEG1
    eMPEG_VER_2,        // MPEG2
    eMPEG_VER_2_5,      // MPEG2.5
    
    eMPEG_VER_MAX
};

// mp3フレームヘッダ情報
typedef union
{
    char mHeader[4];
    struct
    {
        unsigned int sinc1:     8;  // 同期ヘッダ(0xff)
        unsigned int err:       1;  // エラープロテクション
        unsigned int layer:     2;  // レイヤー
        unsigned int id:        2;  // ID
        unsigned int sinc2:     3;  // 同期ヘッダ(0xf)
        unsigned int ext:       1;  // エクステンション(個人識別フラグ)
        unsigned int padding:   1;  // パディング
        unsigned int sampling:  2;  // サンプリングレート
        unsigned int bitrate:   4;  // ビットレート
        unsigned int enfa:      2;  // エンファシス
        unsigned int original:  1;  // オリジナル/コピー
        unsigned int copyright: 1;  // 著作権
        unsigned int mode:      2;  // モードエクステンション
        unsigned int channel:   2;  // チャンネルモード
    } h;
} MP3FrameHeader;

// フレームヘッダの情報構造隊
typedef struct strFrameHeaderInfo
{
    s16 m_version;      // MPEGバージョン
    s16 m_layer;        // レイヤー番号
    s16 m_bitrate;      // ビットレート
    u16 m_samplerate;   // サンプリングレート(44100KHzがs16の範囲を超えるためu16)
    s16 m_padding;      // パディングバイトの有無
    s16 m_channel;      // チャンネル数
    s16 m_framesize;    // フレームサイズ
} sFrameHeaderInfo;

// フレームヘッダの平均結果
typedef struct strFrameHeaderAverageInfo
{
    eBITRATE_TYPE   m_bitRateType;          // ビットレートのタイプ(eBITRATE_TYPE参照)
    s16             m_bitRateAverage;       // ビットレート平均
    s32             m_frameCnt;             // フレーム数
    s64             m_dataSize;             // 音声データのトータルサイズ
} sFrameHeaderAverageInfo;

//===========================
//  ローカル関数
//===========================
bool CheckFrameHeader(const MP3FrameHeader* _header, sFrameHeaderInfo* _pInfo);
bool AverageFrameHeader(CDecryptBaseClass& decryptor, FILE* _fp, s32 _skip, sFrameHeaderAverageInfo* _pInfo);

/*
 @brief  mp3形式のサウンドファイル解析
 @param[in] const char* _path                   サウンドファイルのパス
 @param[in] sSoundAnalysisData* _analysisData   サウンドファイルの解析結果渡す用
 @return    bool    true:解析完了, false:解析失敗
 */
bool SoundAnalysis_MP3( const char* _path, sSoundAnalysisData* _analysisData )
{
    if( _path == NULL || _analysisData == NULL ) return false;
    
    FILE* fp = NULL;
    char header[10];
    MP3FrameHeader frameHeader;
    sFrameHeaderInfo headerInfo;
    sFrameHeaderAverageInfo headerAverageInfo;
    int nSize = 0;
    s64 totalFileSize = 0;   // mp3のファイル全体サイズ
    int mp3DataSize = 0;     // mp3の音声データのサイズ
    int skipOffset = 0;      //
    
    // サウンドファイルをオープン
    fp = fopen( _path, "rb" );
    if( !fp ) return false;
    
	CDecryptBaseClass decryptor;
	IPlatformRequest& pltf = CPFInterface::getInstance().platform();
	if (pltf.useEncryption()) {
		u8 hdr[4];
		hdr[0] = 0;
		hdr[1] = 0;
		hdr[2] = 0;
		hdr[3] = 0;
		fread(hdr, 1,4,fp);
		decryptor.decryptSetup((const u8*)_path, hdr);
	}

    // ファイル全体のサイズを取得
    fseek( fp, 0, SEEK_END );
    fgetpos( fp, (fpos_t*)&totalFileSize );

	if (decryptor.m_useNew) {
		totalFileSize -= 4;
	    fseek( fp, 4, SEEK_SET );
	} else {
	    fseek( fp, 0, SEEK_SET );
	}

    // フレームヘッダのを検索します
    nSize = fread( header, 1, sizeof(header), fp );
    if( nSize < sizeof(header) )
    {
        fclose( fp );
        return false;
    }

	decryptor.decryptBlck(header, nSize);

    // フレームヘッダかどうかチェック
    if( CheckFrameHeader((MP3FrameHeader*)header, &headerInfo) )
    {
        // ID3v1
		decryptor.gotoOffset((u32)(totalFileSize - 128));
        fseek( fp, (long)((totalFileSize - 128) + (decryptor.m_useNew ? 4 : 0)), SEEK_SET );
        nSize = fread( header, 1, sizeof(header), fp );
        if( nSize < sizeof(header) )
        {
            fclose( fp );
            return false;
        }
        
		decryptor.decryptBlck(header, nSize);

        skipOffset = 0;
        if( !memcmp(header, "ID3", 3) ) {
            mp3DataSize = (int)totalFileSize - 128; // 128はID3タグサイズ(固定)
        } else {
            mp3DataSize = (int)totalFileSize; // ID3タグが無いのでファイルサイズがデータサイズ
        }
        
		decryptor.gotoOffset(skipOffset);
        fseek( fp, skipOffset + (decryptor.m_useNew ? 4 : 0), SEEK_SET );
        nSize = fread( &frameHeader, 1, sizeof(frameHeader), fp );

		decryptor.decryptBlck(&frameHeader, nSize);

        if( nSize < sizeof(frameHeader) )
        {
            fclose( fp );
            return false;
        }
    }
    else if( !memcmp(header, "ID3", 3) )
    {
        // ID3v2
        // ID3v2タグサイズ計算
        u32 tagSize = ((header[6]&0x7F)<<21) |
                      ((header[7]&0x7F)<<14) |
                      ((header[8]&0x7F)<<7) |
                      ((header[9]&0x7F));
        // 読み飛ばし位置,mp3データサイズ計算
        skipOffset  = tagSize + 10;
        mp3DataSize = (int)(totalFileSize - skipOffset);
        
        // フレームヘッダ読み込み
		decryptor.gotoOffset(skipOffset);
        fseek( fp, skipOffset + (decryptor.m_useNew ? 4 : 0), SEEK_SET );
        nSize = fread( &frameHeader, 1, sizeof(frameHeader), fp );
        if( nSize < sizeof(frameHeader) )
        {
            fclose( fp );
            return false;
        }
		decryptor.decryptBlck(&frameHeader, nSize);
		if( CheckFrameHeader(&frameHeader, &headerInfo) == false )
        {
            fclose( fp );
            return false;
        }
    }
    else
    {
        // フレームヘッダでもID3タグでもなかった場合はreturn
        fclose( fp );
        return false;
    }
    
    // フレームヘッダの平均情報を取得
    if( AverageFrameHeader(decryptor, fp, skipOffset, &headerAverageInfo) == false )
    {
        fclose( fp );
        return false;
    }
    
    // 必要な情報が集まったらsSoundAnalysisDataに代入
    // ここから先return falseしちゃダメ！
    {
        // TODO.
        // 本来可変ビットレートを考え対応しなければならない。
        
        //------------------------
        // 各種データを代入
        _analysisData->m_bitRateType    = headerAverageInfo.m_bitRateType;
        
        _analysisData->m_bitRate        = headerAverageInfo.m_bitRateAverage;
        _analysisData->m_samplingRate   = headerInfo.m_samplerate;
        
        // 再生フレーム数を計算
        _analysisData->m_totalFrame     = headerAverageInfo.m_frameCnt;
        
        // 演奏時間を計算
        _analysisData->m_totalTime      = headerAverageInfo.m_dataSize / (headerAverageInfo.m_bitRateAverage / 8);
    }
    
    // すべて終わったのでサウンドファイルをクローズ
    fclose( fp );
    return true;
}

//===========================
//  ローカル関数
//===========================
/*
 @brief     フレームヘッダかどうかのチェック
 @param[in]     MP3FrameHeader* _header     チェック対象のフレームヘッダー
 @param[out]    sFrameHeaderInfo* _pInfo    フレームヘッダ情報保存先(NULLの場合はスルー)
 @return        bool    true:フレームヘッダである, false:フレームヘッダでない
 */
bool CheckFrameHeader(const MP3FrameHeader* _header, sFrameHeaderInfo* _pInfo)
{
    if( _header == NULL ) return false;
    
    // 先頭から11ビットは常に1であるはずのなのでそうでないならreturn
    if( (_header->mHeader[0] & 0xFF) != 0xFF ) return false;
    if( (_header->mHeader[1] & 0xE0) != 0xE0 ) return false;
    
    // MPEGのバージョンチェック(1の場合は予約idなのでreturn)
    if( _header->h.id == 1 ) return false;
    
    // レイヤーチェック(0の場合は予約idなのでreturn)
    if( _header->h.layer == 0 ) return false;
    
    // ビットレートチェック(0以下と15以上だと割当がないのでreturn)
    if( _header->h.bitrate < 0 && _header->h.bitrate >= 15 ) return false;
    
    // サンプリングレートチェック(3の場合は予約idなのでreturn)
    if( _header->h.sampling == 3 ) return false;
    
    // フレームヘッダ情報を保存
    if( _pInfo )
    {
        int version = eMPEG_VER_NONE;
        int bitrate = 0;
        int samplingrate = 0;
        int framesize = 0;
        int layer = _header->h.layer - 1;
        int bit = _header->h.bitrate - 1;
        int sampling = _header->h.sampling;
        switch( _header->h.id )
        {
            case 0: // MPEG2.5
                version = eMPEG_VER_2_5;
                bitrate = s_MPEG2_5_BitRateTbl[0][bit];
                samplingrate = s_SamplingTbl[2][sampling];
                framesize = (s_SamplePerFrame[layer][2] / 8 * bitrate * 1000) / samplingrate + _header->h.padding;
                break;
            case 2: // MPEG2
                version = eMPEG_VER_2;
                bitrate = s_MPEG2_BitRateTbl[layer][bit];
                samplingrate = s_SamplingTbl[1][sampling];
                framesize = (s_SamplePerFrame[layer][1] / 8 * bitrate * 1000) / samplingrate + _header->h.padding;
                break;
            case 3: // MPEG1
                version = eMPEG_VER_1;
                bitrate = s_MPEG1_BitRateTbl[layer][bit];
                samplingrate = s_SamplingTbl[0][sampling];
                framesize = (s_SamplePerFrame[layer][0] / 8 * bitrate * 1000) / samplingrate + _header->h.padding;
                break;
        }
        
        _pInfo->m_version       = version;
        _pInfo->m_layer         = 3 - layer;
        _pInfo->m_bitrate       = bitrate;
        _pInfo->m_samplerate    = samplingrate;
        _pInfo->m_padding       = _header->h.padding;
        _pInfo->m_channel       = _header->h.channel;
        _pInfo->m_framesize     = framesize;
    }
    
    return true;
}

/*
 @brief     フレームヘッダの平均を計算
 @param[in]     FILE* _fp   対象のファイルポインタ
 @param[in]     s32 _skip   データ先頭へのシークサイズ
 @param[out]    sFrameHeaderAverageInfo* _pInfo    フレームヘッダ平均情報保存先(NULLの場合はスルー)
 @return        bool    true:フレームヘッダである, false:フレームヘッダでない
 */
bool AverageFrameHeader(CDecryptBaseClass& decryptor, FILE* _fp, s32 _skip, sFrameHeaderAverageInfo* _pInfo)
{
    s32 frameCnt = 0;
    s32 ofs = _skip;
    MP3FrameHeader frameHeader;
    sFrameHeaderInfo headerInfo;
    s32 nSize = 0;
    
    eBITRATE_TYPE bitRateType = eBITRATE_TYPE_CBR;    // ビットレートタイプ(とりあえずCBRを初期値)
    s16 bitRate = -1;
    float totalBitRate = 0.0f;  // ビットレートのトータル
    s64 totalDataSize = 0;      // 音声データ部分のトータルサイズ
    
    // Xingヘッダー用変数
    s16 xingFrameCnt = 0;
    s64 xingDataSize = 0;
    // s16 xingQuality = 0;
    
    if( _fp == NULL || _skip < 0 ) {
        return false;
    }
    
    bool bFind = false;
    // bool bXingCheck = false;
    ofs = _skip;
    while( 1 )
    {
        // 読み飛ばし位置に移動してから４byte読み込み
		decryptor.gotoOffset(ofs);
        fseek( _fp, ofs + (decryptor.m_useNew ? 4 : 0), SEEK_SET );
        nSize = fread( &frameHeader, 1, sizeof(frameHeader), _fp );
        decryptor.decryptBlck(&frameHeader, nSize);

        // 読み込みサイズが４byte以下の場合はファイル終端に到達したので抜ける
        if( nSize < 4 ) {
            break;
        }
        
        // フレームヘッダのチェック
        if( CheckFrameHeader(&frameHeader, &headerInfo) )
        {
            if( bFind == false ) {
                bFind = true;
            }
/*
            // TODO. Xingヘッダ対応
            // Xingヘッダーを検索
            if( (bitRateType == eBITRATE_TYPE_CBR) && (bXingCheck == false) )
            {
                bXingCheck = true;
                char header[4];
                s32 xingOfs = 0;
                if( frameHeader.h.id == 3 )
                {
                    // MPEG1の場合
                    xingOfs = (frameHeader.h.channel == 1) ? (17) : (32);
                }
                else
                {
                    // MPEG2, MPEG2.5
                    xingOfs = (frameHeader.h.channel == 1) ? (9) : (17);
                }
                
                fseek( _fp, ofs + xingOfs + sizeof(frameHeader), SEEK_SET );
                nSize = fread( header, 1, sizeof(header), _fp );
				decryptor.decryptBlck(header, nSize);
				if( nSize == sizeof(header) )
                {
                    if( memcmp(header, "Xing", sizeof(header)) == 0 ||
                        memcmp(header, "Info", sizeof(header)) == 0 )
                    {
                        bitRateType = eBITRATE_TYPE_VBR;
                    }
                }
            }
 */
            
            // ビットレートの可変チェック
            if( bitRate < 0 )
            {
                // 最初のフレームはただ保存
                bitRate = headerInfo.m_bitrate;
            }
            else
            {
                // 現在のビットレートタイプがCBRで、
                // なおかつ最初のフレームのビットレートと違う場合は平均ビットレートタイプ
                if( (bitRateType == eBITRATE_TYPE_CBR) && (bitRate != headerInfo.m_bitrate) )
                {
                    bitRateType = eBITRATE_TYPE_ABR;
                }
            }
            
            totalBitRate    += headerInfo.m_bitrate;
            totalDataSize   += headerInfo.m_framesize;
            ofs             += headerInfo.m_framesize;
            
            frameCnt++;
        }
        else
        {
            // 見つからない場合はファイルポインタを１つ進めもう一度
            ofs++;
        }
    }
    
    // フレームヘッダが見つかっらなかったら
    if( bFind == false ) {
        return false;
    }
    
    // 平均情報を保存
    if( _pInfo )
    {
        _pInfo->m_bitRateType       = bitRateType;
        _pInfo->m_bitRateAverage    = (s16)(totalBitRate/(float)frameCnt);
        _pInfo->m_dataSize          = (xingDataSize) ? (xingDataSize) : (totalDataSize);
        _pInfo->m_frameCnt          = (xingFrameCnt) ? (xingFrameCnt) : (frameCnt);
    }
    
    // 正常終了
    return true;
}
