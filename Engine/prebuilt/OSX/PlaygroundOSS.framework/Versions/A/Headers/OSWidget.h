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
#ifndef OSWidget_h
#define OSWidget_h

#include <string.h>

class IWidget
{
public:
	enum CONTROL {
		TEXTBOX,
		PASSWDBOX,
        WEBVIEW,
        WEBNOJUMP,
        MOVIEPLAYER,
        BGMOVIEPLAYER,
        ACTIVITYINDICATOR,
	};
    
	// TEXTBOX で生成された Widget の操作コマンド(cmd()に渡して使用)
	enum TEXTCMD{
        TX_FONT,            // フォントおよびサイズ指定
		TX_PLACEHOLDER,		// プレースホルダ設定
        TX_MAXLEN,          // 最大長設定
        TX_CHARTYPE,        // 有効文字種設定(TEXTCHARTYPEの論理和で指定)

		TX_BGCOLOR_NORMAL,	// 通常時の背景色
		TX_FGCOLOR_NORMAL,	// 通常時の前景色

		TX_BGCOLOR_TOUCH,	// 触れた時の背景色
		TX_FGCOLOR_TOUCH,	// 触れた時の前景色
        
        TX_ALIGNMENTTYPE,   // テキストのアライメントタイプ
	};
    
    enum TEXTALIGNMENTTYPE {
        TX_ALIGN_LEFT = 0,     // 左揃え
        TX_ALIGN_CENTER,       // 中央揃え
        TX_ALIGN_RIGHT,        // 右揃え
    };

	enum TEXTCHARTYPE {
		TXCH_7BIT_ASCII = 0x0001,	// 7bit ASCII を許可
		TXCH_UTF8       = 0x0002,	// 最上位bitが1の文字を許可

		// それ以外の文字種を追加する際は 0x0004, 0x0008…と、bitmaskを追加する形で。
	};

    // WEBVIEW で生成された Widget の操作コマンド(cmd()に渡して使用)
    typedef enum {
        WEB_SET_SCALESPAGETOFIT,	// iOSの UIWebViewにおける scalePageToFit プロパティ設定
        WEB_BGCOLOR_NORMAL,			// webviewの背景色
    } WEBCMD;
    
    
    // MOVIEPLAYER で生成された Widget の操作コマンド(cmd()に渡して使用)
    enum MOVIECMD{
        MV_STOP,					// 動画再生停止
        MV_PLAY,					// 動画再生
        MV_PAUSE,					// 動画一時停止
        MV_RESUME,					// 動画再生再開
    };

	// 動画再生ステータス(現在未使用)
    enum MOVIESTAT {
        MV_FINISHED,				// 動画再生終了
    };
    
    // ACTIVITYINDICATOR　用コマンドと定数
    enum ACTIVITYINDICATORCMD {
        ACT_STARTANIM,				// アニメーション開始
        ACT_STOPANIM,				// アニメーション停止
        ACT_SET_STYLE,				// ActivityIndicatorの種類指定(定数ACTITYPEで指定)
    };
    
    enum ACTITYPE {
        ACTI_TYPE_WHITE,			// white
        ACTI_TYPE_GRAY,				// gray
        ACTI_TYPE_WHITELARGE,		// whitelarge
    };
    
	virtual ~IWidget();

	virtual int  getTextLength() = 0;
	virtual int  getTextMaxLength() { return 0; } // Default implementation for all classes.
	virtual bool getText(char * pBuf, int maxlen) = 0;
	virtual bool setText(const char * string) = 0;
	virtual void move(int x, int y) = 0;
	virtual void resize(int width, int height) = 0;
	virtual void visible(bool bVisible) = 0;
	virtual void enable(bool bEnable) = 0;
    
    virtual void cmd(int cmd, ...) = 0;
    virtual int status() = 0;
    
    inline void setTmpString(const char * string) { strcpy(m_buf, string); }
    inline const char * getTmpString() const { return (const char *)m_buf; }
private:
    char        m_buf[1024];
};

#endif // OSWidget_h
