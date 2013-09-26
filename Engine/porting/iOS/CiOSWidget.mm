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
//
//  CiOSWidget.cpp
//  GameEngine
//
//

#include <iostream>
#include "CiOSWidget.h"
#include "CiOSPlatform.h"
#import <UIKit/UIKit.h>
#import "CiOSWebView.h"
#include "CiOSPathConv.h"
#import <CoreMedia/CoreMedia.h>

CiOSWidget::CiOSWidget(CiOSPlatform * pParent)
: m_x(0)
, m_y(0)
, m_width(0)
, m_height(0)
, m_pPlatform(pParent)
{
    m_scale = m_pPlatform->getScale();
}
CiOSWidget::~CiOSWidget() {}

void
CiOSWidget::cmd(int cmd, ...) {}

int
CiOSWidget::status() { return 0; }

bool
CiOSWidget::init(int id, int x, int y, int width, int height)
{
    m_id = id;
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    set_move(m_x, m_y, m_width, m_height);
    return true;
}

void
CiOSWidget::move(int x, int y)
{
    m_x = x;
    m_y = y;
    set_move(m_x, m_y, m_width, m_height);
}

void
CiOSWidget::resize(int width, int height)
{
    m_width = width;
    m_height = height;
    set_move(m_x, m_y, m_width, m_height);
}


CiOSTextWidget * CiOSTextWidget::ms_begin = 0;
CiOSTextWidget * CiOSTextWidget::ms_end = 0; 

CiOSTextWidget::CiOSTextWidget(CiOSPlatform * pParent, int maxlen)
: CiOSWidget(pParent)
, m_pTextBox(0)
, m_pTextView(0)
, m_prev(0)
, m_next(0)
, m_touched(false)
, m_bVisible(true)
, m_maxlen(maxlen)
, m_chartype(TXCH_7BIT_ASCII | TXCH_UTF8)
, m_consoleType(E_CONSOLE_TYPE_UITEXTVIEW)
, m_alignType(UITextAlignmentLeft)
{
    m_cols[0] = 0xffffffff;
    m_cols[1] = 0xff000000;
    m_cols[2] = 0xffffffff;
    m_cols[3] = 0xff000000;
    
    m_prev = ms_end;
    if(m_prev) {
        m_prev->m_next = this;
    } else {
        ms_begin = this;
    }
    ms_end = this;
    
}
CiOSTextWidget::~CiOSTextWidget()
{
    if(m_prev) {
        m_prev->m_next = m_next;
    } else {
        ms_begin = m_next;
    }
    if(m_next) {
        m_next->m_prev = m_prev;
    } else {
        ms_end = m_prev;
    }
    if(m_pTextBox) {
        [m_pTextBox resignFirstResponder];
        [m_pTextBox removeFromSuperview];
    }
    if(m_pTextView) {
        [m_pTextView resignFirstResponder];
        [m_pTextView removeFromSuperview];
    }
}

// テキストフィールドを検索してWidgetを取得
CiOSTextWidget *
CiOSTextWidget::searchWidgetField(UITextField *pTextBox)
{
    CiOSTextWidget * pWidget = ms_begin;
    while(pWidget) {
        if(pWidget->m_pTextBox == pTextBox) break;
        pWidget = pWidget->m_next;
    }
    return pWidget;
}

// テキストビューを検索してWidgetを取得
CiOSTextWidget *
CiOSTextWidget::searchWidgetView(UITextView * pTextView)
{
    CiOSTextWidget * pWidget = ms_begin;
    while(pWidget) {
        if(pWidget->m_pTextView == pTextView) break;
        pWidget = pWidget->m_next;
    }
    return pWidget;
}

void
CiOSTextWidget::setAllVisible(bool visible)
{
    CiOSTextWidget * pWidget = ms_begin;
    while(pWidget) {
        pWidget->m_pTextBox.hidden = (visible && pWidget->m_bVisible) ? NO : YES;
        pWidget->m_pTextView.hidden = (visible && pWidget->m_bVisible) ? NO : YES;
        pWidget = pWidget->m_next;
    }
}


UIFont *
CiOSTextWidget::getFont()
{
    return (!m_pFont) ? [UIFont systemFontOfSize:16] : m_pFont->getFontScaled();
}
const char *
CiOSTextWidget::getFontName()
{
    return (!m_pFont) ? 0 : m_pFont->getFontname();
}

bool
CiOSTextWidget::create(CONTROL type, int id,
                     const char *caption, int x, int y, int width, int height)
{
    switch( m_consoleType )
    {
        case E_CONSOLE_TYPE_UITEXTVIEW:
            createTextView(type, caption);
            break;
        case E_CONSOLE_TYPE_UITEXTFIELD:
            createTextField(type, caption);
            break;
    }

    return init(id, x, y, width, height);
}

int
CiOSTextWidget::getTextLength()
{
    const char * pstr = NULL;
    switch( m_consoleType )
    {
        case E_CONSOLE_TYPE_UITEXTVIEW:
            pstr = [m_pTextView.text UTF8String];
            break;
        case E_CONSOLE_TYPE_UITEXTFIELD:
            pstr = [m_pTextBox.text UTF8String];
            break;
    }
    return strlen(pstr);
}

bool
CiOSTextWidget::getText(char * pBuf, int maxlen)
{
    const char * pstr = NULL;
    switch( m_consoleType )
    {
        case E_CONSOLE_TYPE_UITEXTVIEW:
            pstr = [m_pTextView.text UTF8String];
            break;
        case E_CONSOLE_TYPE_UITEXTFIELD:
            pstr = [m_pTextBox.text UTF8String];
            break;
    }
    int len = strlen(pstr);
    if(len >= maxlen) len = maxlen - 1;
    strncpy(pBuf, pstr, len);
    pBuf[len] = 0;
    return true;
}

bool
CiOSTextWidget::setText(const char * string)
{
    NSString *str = [[[NSString alloc] initWithUTF8String:string] autorelease];	// 2012.12.11  autorelease追加
    m_pTextView.text = str;
    switch( m_consoleType )
    {
        case E_CONSOLE_TYPE_UITEXTVIEW:
            m_pTextView.text = str;
            break;
        case E_CONSOLE_TYPE_UITEXTFIELD:
            m_pTextBox.text = str;
            break;
    }
    return true;
}

void
CiOSTextWidget::visible(bool bVisible)
{
    switch( m_consoleType )
    {
        case E_CONSOLE_TYPE_UITEXTVIEW:
            m_pTextView.hidden = (bVisible) ? NO : YES;
            break;
        case E_CONSOLE_TYPE_UITEXTFIELD:
            m_pTextBox.hidden = (bVisible) ? NO : YES;
            break;
    }
    m_bVisible = bVisible;
}

void
CiOSTextWidget::enable(bool bEnable)
{
    switch( m_consoleType )
    {
        case E_CONSOLE_TYPE_UITEXTVIEW:
            //m_pTextView.enabled = (bEnable) ? YES : NO;
            break;
        case E_CONSOLE_TYPE_UITEXTFIELD:
            m_pTextBox.enabled = (bEnable) ? YES : NO;
            break;
    }
}

// テキストフィールド版を作成
bool
CiOSTextWidget::createTextField(CONTROL _type, const char *_caption)
{
    EAGLView * pView = getPlatform().getView();
    
    switch(_type)
    {
        default:
            return false;
        case IWidget::TEXTBOX:
            m_pTextBox = [[[UITextField alloc] init] autorelease];
            m_pTextBox.text = [NSString stringWithUTF8String:_caption];
            m_pTextBox.borderStyle = UITextBorderStyleRoundedRect;
            m_pFont = 0;
            m_pTextBox.font = [UIFont systemFontOfSize:16];
            m_pTextBox.keyboardType = UIKeyboardTypeDefault;
            m_pTextBox.returnKeyType = UIReturnKeyDone;
            m_pTextBox.clearButtonMode = UITextFieldViewModeWhileEditing; // クリアボタン
            m_pTextBox.delegate = pView;
            break;
        case IWidget::PASSWDBOX:
            m_pTextBox = [[[UITextField alloc] init] autorelease];
            m_pTextBox.text = [NSString stringWithUTF8String:_caption];
            m_pTextBox.secureTextEntry = YES;
            m_pTextBox.borderStyle = UITextBorderStyleRoundedRect;
            m_pFont = 0;
            m_pTextBox.font = [UIFont systemFontOfSize:16];
            m_pTextBox.keyboardType = UIKeyboardTypeDefault;
            m_pTextBox.returnKeyType = UIReturnKeyDone;
            m_pTextBox.clearButtonMode = UITextFieldViewModeWhileEditing; // クリアボタン
            m_pTextBox.delegate = pView;
            break;
    }
    
    [m_pTextBox addTarget:pView action:@selector(textTouchDown:)
    forControlEvents:UIControlEventTouchDown];
     
    [m_pTextBox addTarget:pView action:@selector(textTouchDown:)
    forControlEvents:UIControlEventEditingDidBegin];
     
    [m_pTextBox addTarget:pView action:@selector(textTouchUp:)
    forControlEvents:UIControlEventEditingDidEnd];
     
    [m_pTextBox addTarget:pView action:@selector(textTouchUp:)
    forControlEvents:UIControlEventTouchDragInside];
    
    set_color();
    
    [pView addSubview:m_pTextBox];
    
    return true;
}

// テキストビュー版を作成
bool
CiOSTextWidget::createTextView(CONTROL _type, const char *_caption)
{
    EAGLView * pView = getPlatform().getView();
    
    switch(_type)
    {
        default:
            return false;
        case IWidget::TEXTBOX:            
//            m_pTextView = [[[UITextView alloc] init] autorelease];
            m_pTextView = [[[CiOSTextView alloc] init] autorelease];
            m_pTextView.text = [NSString stringWithUTF8String:_caption];
            //m_pTextView.borderStyle = UITextBorderStyleRoundedRect;
            m_pTextView.layer.borderWidth = 1.0f;
            m_pTextView.layer.cornerRadius = 8.0f;
            m_pFont = 0;
            m_pTextView.font = [UIFont systemFontOfSize:16];
            m_pTextView.keyboardType = UIKeyboardTypeDefault;
            m_pTextView.returnKeyType = UIReturnKeyDone;
            m_pTextView.delegate = pView;
            break;
        case IWidget::PASSWDBOX:            
//            m_pTextView = [[[UITextView alloc] init] autorelease];
            m_pTextView = [[[CiOSTextView alloc] init] autorelease];
            m_pTextView.text = [NSString stringWithUTF8String:_caption];
            m_pTextView.secureTextEntry = YES;
            //m_pTextView.borderStyle = UITextBorderStyleRoundedRect;
            m_pTextView.layer.borderWidth = 1.0f;
            m_pTextView.layer.cornerRadius = 8.0f;
            m_pFont = 0;
            m_pTextView.font = [UIFont systemFontOfSize:16];
            m_pTextView.keyboardType = UIKeyboardTypeDefault;
            m_pTextView.returnKeyType = UIReturnKeyDone;
            m_pTextView.delegate = pView;
            break;
    }
    
    set_color();
    
    [pView addSubview:m_pTextView];
    
    return true;
}

void
CiOSTextWidget::set_move(int x, int y, int width, int height)
{
    float scale = getScale();
    
    switch( m_consoleType )
    {
        case E_CONSOLE_TYPE_UITEXTVIEW:
            m_pTextView.frame = CGRectMake(x / scale,
                                           y / scale,
                                           width /scale,
                                           height / scale);
            break;
            
        case E_CONSOLE_TYPE_UITEXTFIELD:
            m_pTextBox.frame = CGRectMake(x / scale,
                                          y / scale,
                                          width /scale,
                                          height / scale);
            break;
    }
}

void
CiOSTextWidget::cmd(int cmd, ...)
{
    va_list ap;
    va_start(ap, cmd);
    
    switch(cmd)
    {
        case TX_PLACEHOLDER:
        {
            // プレースホルダに文字設定
            const char * placeholder = va_arg(ap, const char *);
            if( m_consoleType == E_CONSOLE_TYPE_UITEXTFIELD ) {
                m_pTextBox.placeholder = [NSString stringWithUTF8String:placeholder];
            } else if( m_consoleType == E_CONSOLE_TYPE_UITEXTVIEW ) {
                [m_pTextView setPlaceHolderString:[NSString stringWithUTF8String:placeholder]];
            }
            break;
        }
        case TX_FONT:
        {
            CiOSFont * pFont = (CiOSFont *)va_arg(ap, void *);
            m_pFont = pFont;
            if( m_consoleType == E_CONSOLE_TYPE_UITEXTFIELD ) {
                m_pTextBox.font = m_pFont->getFontScaled();
            } else if( m_consoleType == E_CONSOLE_TYPE_UITEXTVIEW ) {
                m_pTextView.font = m_pFont->getFontScaled();
            }
            break;
        }
        case TX_MAXLEN:
        {
            int maxlen = va_arg(ap, int);
            m_maxlen = maxlen;
            break;
        }
        case TX_CHARTYPE:
        {
            int chartype = va_arg(ap, int);
            m_chartype = chartype;
            break;
        }
        case TX_ALIGNMENTTYPE:
        {
            // テキストのアライメント設定
            int alignType = va_arg(ap, int);
            switch( alignType )
            {
                case TX_ALIGN_LEFT:
                    m_alignType = NSTextAlignmentLeft;
                    break;
                case TX_ALIGN_CENTER:
                    m_alignType = NSTextAlignmentCenter;
                    break;
                case TX_ALIGN_RIGHT:
                    m_alignType = NSTextAlignmentRight;
                    break;
            }
            if( m_consoleType == E_CONSOLE_TYPE_UITEXTFIELD ) {
                m_pTextBox.textAlignment = m_alignType;
            } else if( m_consoleType == E_CONSOLE_TYPE_UITEXTVIEW ) {
                m_pTextView.textAlignment = m_alignType;
            }
            break;
        }
        default:
        {
            unsigned int color = va_arg(ap, unsigned int);
            switch (cmd)
            {
                case TX_BGCOLOR_NORMAL: m_cols[0] = color; break;
                case TX_FGCOLOR_NORMAL: m_cols[1] = color; break;
                case TX_BGCOLOR_TOUCH:  m_cols[2] = color; break;
                case TX_FGCOLOR_TOUCH:  m_cols[3] = color; break;
            }
            set_color();    // カラー設定
            break;
        }
    }
    
    va_end(ap);
}

void
CiOSTextWidget::set_color()
{
    int base = (m_touched) ? 2 : 0;
    unsigned int bg = m_cols[base];
    unsigned int fg = m_cols[base + 1];
    int i;
    float bcol[4], fcol[4];
               
    // background の設定
    for(i = 0; i < 4; i++) {
        bcol[i] = ((bg >> (8 * i))& 0xff) / 255.0f;
        fcol[i] = ((fg >> (8 * i))& 0xff) / 255.0f;
    }
    UIColor * uibg = [UIColor colorWithRed:bcol[2] green:bcol[1] blue:bcol[0] alpha:bcol[3]];
    UIColor * uifg = [UIColor colorWithRed:fcol[2] green:fcol[1] blue:fcol[0] alpha:fcol[3]];

    switch( m_consoleType )
    {
        case E_CONSOLE_TYPE_UITEXTVIEW:
            m_pTextView.backgroundColor = uibg;
            m_pTextView.textColor = uifg;
            break;
        case E_CONSOLE_TYPE_UITEXTFIELD:
            m_pTextBox.backgroundColor = uibg;
            m_pTextBox.textColor = uifg;
            break;
    }
}


CiOSWebWidget * CiOSWebWidget::ms_begin = 0;
CiOSWebWidget * CiOSWebWidget::ms_end = 0; 


CiOSWebWidget::CiOSWebWidget(CiOSPlatform * pParent)
    : CiOSWidget(pParent), m_pWebView(0), m_pNowURL(0), m_bgalpha(0), m_bgcolor(0xffffff), m_next(0), m_prev(0)
{
    m_prev = ms_end;
    if(m_prev) {
        m_prev->m_next = this;
    } else {
        ms_begin = this;
    }
    ms_end = this;
}

CiOSWebWidget::~CiOSWebWidget()
{
    if(m_prev) {
        m_prev->m_next = m_next;
    } else {
        ms_begin = m_next;
    }
    if(m_next) {
        m_next->m_prev = m_prev;
    } else {
        ms_end = m_prev;
    }
    
    if( m_pNowURL ) delete [] m_pNowURL;	// 2012.12.11  解放漏れ修正
    
    if(m_pWebView) {
        [m_pWebView removeFromSuperview];
    }
}

CiOSWebWidget *
CiOSWebWidget::searchWidget(UIWebView *pWebView)
{
    CiOSWebWidget * pWidget = ms_begin;
    while(pWidget) {
        if(pWidget->m_pWebView == pWebView) break;
        pWidget = pWidget->m_next;
    }
    return pWidget;
}

bool
CiOSWebWidget::create(CONTROL type, int id,
                      const char *caption, int x, int y, int width, int height,
                      const char * token,
                      const char * region,
                      const char * client,
                      const char * consumerKey,
                      const char * applicationId,
                      const char * userID)
{
    EAGLView * pView = getPlatform().getView();
    switch(type)
    {
        default:
            return false;
        case IWidget::WEBVIEW:
            m_bJump = true;
            break;

        case IWidget::WEBNOJUMP:
            m_bJump = false;
            break;
    }
    m_bFirst = true;
    m_pWebView = [[[CiOSWebView alloc] init] autorelease];
    
    const char * pform = CPFInterface::getInstance().platform().getPlatform();
    
    [m_pWebView setCustomHeaders:token:region:client:consumerKey:applicationId:userID:pform];
    
//    setText(caption);	// 2012.12.11  下でもやっているんのでコメントアウト
    set_bgcolor();
    m_pWebView.delegate = pView;
    m_pWebView.scalesPageToFit = YES;
    m_pWebView.autoresizingMask = UIViewAutoresizingFlexibleWidth;
    
    m_pWebView.opaque = NO;             // 不透明をNO状態にすることで透過が可能
    
    ((UIScrollView *)[[m_pWebView subviews] objectAtIndex:0]).bounces = NO;
    [pView addSubview:m_pWebView];
    bool result = init(id, x, y, width, height);
    return setText(caption) && result;
}

int
CiOSWebWidget::getTextLength()
{
    const char * pstr = m_pNowURL;
    return strlen(pstr);
}

bool
CiOSWebWidget::getText(char * pBuf, int maxlen)
{
    const char * pstr = m_pNowURL;
    int len = strlen(pstr);
    if(len >= maxlen) len = maxlen - 1;
    strncpy(pBuf, pstr, len);
    pBuf[len] = 0;
    return true;
}

bool
CiOSWebWidget::setText(const char * string)
{
    NSURL * url = [[NSURL alloc] initWithString:[NSString stringWithUTF8String:string]];
    NSURLRequest * req = [[NSURLRequest alloc] initWithURL:url];
    [m_pWebView loadRequest:req];
    [req release];
    [url release];

    char * buf = new char [ strlen(string) + 1 ];
    strcpy(buf, string);
    if(m_pNowURL) delete [] m_pNowURL;
    m_pNowURL = buf;
    return true;
}

void
CiOSWebWidget::set_bgcolor()
{
    int i = 0;
    unsigned int color = (m_bgalpha << 24) | m_bgcolor;
    float bgColor[4];
    
    for( i=0; i<4; ++i ) {
        bgColor[i] = ((color >> (8 * i)) & 0xff) / 255.0f;
    }
    
    UIColor * uibg = [UIColor colorWithRed:bgColor[2] green:bgColor[1] blue:bgColor[0] alpha:bgColor[3]];
    m_pWebView.backgroundColor = uibg;
}

void
CiOSWebWidget::visible(bool bVisible)
{
    m_pWebView.hidden = (bVisible) ? NO : YES;
}

void
CiOSWebWidget::enable(bool bEnable)
{
}

void
CiOSWebWidget::set_move(int x, int y, int width, int height)
{
    float scale = getScale();
    m_pWebView.frame = CGRectMake(x / scale,
                                  y / scale,
                                  width /scale,
                                  height / scale);
}

void
CiOSWebWidget::cmd(int cmd, ...)
{
    va_list ap;
    va_start(ap, cmd);
    switch (cmd) {
        case WEB_SET_SCALESPAGETOFIT:
        {
            int pagetofit = va_arg(ap, int);
            m_pWebView.scalesPageToFit = (pagetofit) ? YES : NO;
            break;
        }
            
        case WEB_BGCOLOR_NORMAL:    // WebViewの背景色の設定
        {
            unsigned int bgalpha = va_arg(ap, unsigned int);
            unsigned int bgcolor = va_arg(ap, unsigned int);
            
            m_bgalpha = bgalpha;
            m_bgcolor = bgcolor;
            set_bgcolor();
            break;
        }
        default:
            break;
    }
}


CiOSMovieWidget * CiOSMovieWidget::ms_begin = 0;
CiOSMovieWidget * CiOSMovieWidget::ms_end = 0; 

CiOSMovieWidget::CiOSMovieWidget(CiOSPlatform * pParent)
: CiOSWidget(pParent), m_next(0), m_prev(0), m_pNowPATH(0), m_pMovieView(0), m_status(0)
{
    m_prev = ms_end;
    if(m_prev) {
        m_prev->m_next = this;
    } else {
        ms_begin = this;
    }
    ms_end = this;
}

CiOSMovieWidget::~CiOSMovieWidget()
{
    if(m_prev) {
        m_prev->m_next = m_next;
    } else {
        ms_begin = m_next;
    }
    if(m_next) {
        m_next->m_prev = m_prev;
    } else {
        ms_end = m_prev;
    }
    
    if( m_pNowPATH ) delete [] m_pNowPATH;	// 2012.12.11  解放漏れ修正
    
    if(m_pMovieView) {
        // イベント削除
        EAGLView * pView = getPlatform().getView();
        [[NSNotificationCenter defaultCenter]
         removeObserver:pView
         name:MPMoviePlayerPlaybackDidFinishNotification
         object:m_pMovieView];

        // 背景ムービーだとViewが破棄されないため、AVPlayerを破棄する
        AVPlayerLayer * playerLayer = (AVPlayerLayer *)m_pMovieView.layer;
        // AVPlayer * player = playerLayer.player;
        playerLayer.player = nil;
        
        if(m_type == IWidget::MOVIEPLAYER) {
            [m_pMovieView removeFromSuperview];
        }
    }
}

bool
CiOSMovieWidget::create(CONTROL type, int id,
                      const char *caption, int x, int y, int width, int height)
{
    
    EAGLView * pView = getPlatform().getView();
    switch(type)
    {
        default:
            return false;
        case IWidget::MOVIEPLAYER:
            m_pMovieView = [[[CiOSMovieView alloc] init] autorelease];            
            [pView addSubview:m_pMovieView];
            break;
        case IWidget::BGMOVIEPLAYER:
            m_pMovieView = (CiOSMovieView *)pView.superview; // GLviewの親がその背後に配置されている
            break;
    }
//    setText(caption);	// 2012.12.11  下でもやっているんのでコメントアウト
    m_type = type;
    bool result = init(id, x, y, width, height);
    return setText(caption) && result;
}

int
CiOSMovieWidget::getTextLength()
{
    const char * pstr = m_pNowPATH;
    return strlen(pstr);
}

bool
CiOSMovieWidget::getText(char * pBuf, int maxlen)
{
    const char * pstr = m_pNowPATH;
    int len = strlen(pstr);
    if(len >= maxlen) len = maxlen - 1;
    strncpy(pBuf, pstr, len);
    pBuf[len] = 0;
    return true;
}

bool
CiOSMovieWidget::setText(const char * string)
{
    int len = strlen(string);
    char * buf = new char [ len + 1 ];
    if(!buf) return false;

    strcpy(buf, string);    
    if(m_pNowPATH) delete [] m_pNowPATH;
    m_pNowPATH = (const char *)buf;

    CiOSPathConv& pathconv = CiOSPathConv::getInstance();
    const char * path = pathconv.fullpath(m_pNowPATH);

    if( path )
    {
        NSString * urlpath = [NSString stringWithUTF8String:path];
        //[@"file://" stringByAppendingString:[NSString stringWithUTF8String:path]];
        NSURL * url = [[NSURL alloc] initFileURLWithPath:urlpath];
    
        AVPlayerItem * playerItem = [AVPlayerItem playerItemWithURL:url];
        //AVPlayer * player = [AVPlayer playerWithURL:url];
        AVPlayer * player = [AVPlayer playerWithPlayerItem: playerItem];
        AVPlayerLayer * playerLayer = (AVPlayerLayer *)m_pMovieView.layer;
        playerLayer.player = player;

    
        [[NSNotificationCenter defaultCenter] addObserver:m_pMovieView selector:@selector(playerItemDidReachEnd:) name:AVPlayerItemDidPlayToEndTimeNotification object:[player currentItem]];
    
        // 2012.12.11  解放漏れ修正
        if( path ) delete path;
        [url release];
    }
    else
    {
        // Movieファイルが見つからないのでエラー
        return false;
    }
    
    return true;
}

void
CiOSMovieWidget::visible(bool bVisible)
{
    m_pMovieView.hidden = (bVisible) ? NO : YES;    
}

void
CiOSMovieWidget::enable(bool bEnable)
{
}

void
CiOSMovieWidget::set_move(int x, int y, int width, int height)
{
    if(m_type == IWidget::BGMOVIEPLAYER) return;
    float scale = getScale();
    m_pMovieView.frame = CGRectMake(x / scale,
                                    y / scale,
                                    width /scale,
                                    height / scale);
}

void
CiOSMovieWidget::cmd(int cmd, ...)
{
#if 1
    AVPlayerLayer * playerlayer = (AVPlayerLayer *)m_pMovieView.layer;
    AVPlayer * player = playerlayer.player;
#endif
    switch(cmd)
    {
        case MV_STOP:
        {
            [player pause];
        }
            break;
        case MV_PLAY:
        {
            m_status = 0;
            [player seekToTime:kCMTimeZero];
            [player play];
        }
            break;
        case MV_PAUSE:
        {
            [player pause];
        }
            break;
        case MV_RESUME:
        {
            [player play];
        }
            break;
    }
}

int
CiOSMovieWidget::status()
{
    return m_status;
}

CiOSMovieWidget *
CiOSMovieWidget::getWidget(void * p)
{
    CiOSMovieWidget * pWidget = ms_begin;
    while(pWidget) {
        AVPlayerLayer * playerlayer = (AVPlayerLayer *)pWidget->m_pMovieView.layer;
        AVPlayer * player = playerlayer.player;
        if([player currentItem] == p) break;
        pWidget = pWidget->m_next;
    }
    return pWidget;
}

CiOSActivityIndicator   *   CiOSActivityIndicator::ms_begin = 0;
CiOSActivityIndicator   *   CiOSActivityIndicator::ms_end   = 0;

CiOSActivityIndicator::CiOSActivityIndicator(CiOSPlatform * pParent)
: CiOSWidget(pParent), m_prev(0), m_next(0)
{
    m_prev = ms_end;
    if(m_prev) {
        m_prev->m_next = this;
    } else {
        ms_begin = this;
    }
    ms_end = this;
}

CiOSActivityIndicator::~CiOSActivityIndicator()
{
    if(m_prev) {
        m_prev->m_next = m_next;
    } else {
        ms_begin = m_next;
    }
    if(m_next) {
        m_next->m_prev = m_prev;
    } else {
        ms_end = m_prev;
    }
    if(m_pActView) {
        [m_pActView removeFromSuperview];
    }
}

bool
CiOSActivityIndicator::create(CONTROL type, int id,
                       const char *caption, int x, int y, int width, int height)
{
    
    EAGLView * pView = getPlatform().getView();
    
    // キーボードの上につけるViewを生成
    /*
     UIView * accessoryView = [[[UIView alloc] init] autorelease];
     accessoryView.backgroundColor = [UIColor whiteColor];
     UITextField * tmpField = [[[UITextField alloc] init] autorelease];
     //[accessoryView addSubview:tmpField];
     accessoryView.frame = CGRectMake(0.0, 0.0, 960.0, 100);
     [tmpField sizeToFit];
     */
    switch(type)
    {
        default:
            return false;
        case IWidget::ACTIVITYINDICATOR:
            m_pActView = [[[UIActivityIndicatorView alloc] init] autorelease];
            m_pActView.hidesWhenStopped = NO;
            m_pActView.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
            m_size = 21.0f;
            break;
    }
    
    [pView addSubview:m_pActView];
    
    return init(id, x, y, width, height);
}

void
CiOSActivityIndicator::set_move(int x, int y, int width, int height)
{
    float version = [[[UIDevice currentDevice] systemVersion] floatValue];
    float scale = getScale();
    m_pActView.frame = CGRectMake(x / scale,
                                  y / scale,
                                  width /scale,
                                  height / scale);
    if(version >= 5) {
        // iOS 5.0以降
        float base = (m_width > m_height) ? m_height : m_width;
        float ind_scale = base / (scale * m_size);
        if(ind_scale > 0) [m_pActView setTransform:CGAffineTransformMakeScale(ind_scale, ind_scale)];

        //[m_pActView.layer setValue:[NSNumber numberWithFloat:ind_scale] forKeyPath:@"transform.scale"];
    }
}


int
CiOSActivityIndicator::getTextLength()
{
    return 0;
}

bool
CiOSActivityIndicator::getText(char * pBuf, int maxlen)
{
    if(maxlen > 0) *pBuf = 0;  // length 0;
    return true;
}
bool
CiOSActivityIndicator::setText(const char * string)
{
    return false;
}

void
CiOSActivityIndicator::visible(bool bVisible)
{
    m_pActView.hidden = (bVisible) ? NO : YES;
    m_bVisible = bVisible;
}
    
void
CiOSActivityIndicator::enable(bool bEnable)
{
}

void
CiOSActivityIndicator::cmd(int cmd, ...)
{
    va_list ap;
    va_start(ap, cmd);
    switch(cmd)
    {
        default: break;
        case ACT_STARTANIM: [m_pActView startAnimating];    break;
        case ACT_STOPANIM:  [m_pActView stopAnimating];     break;
        case ACT_SET_STYLE:
        {
            int style = va_arg(ap, int);
            m_size = 21.0f;
            switch(style)
            {
                case 0:
                {
                    m_pActView.activityIndicatorViewStyle = UIActivityIndicatorViewStyleWhite;
                    break;
                }
                case 1:
                {
                    m_pActView.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
                    break;
                }
                case 2:
                {
                    m_pActView.activityIndicatorViewStyle = UIActivityIndicatorViewStyleWhiteLarge;
                    m_size = 36.0f;
                    break;
                }
            }
            float version = [[[UIDevice currentDevice] systemVersion] floatValue];
            if(version > 5) {
                float scale = getScale();
                float base = (m_width > m_height) ? m_height : m_width;
                float ind_scale = base / (scale * m_size);
                if(ind_scale > 0)[m_pActView setTransform:CGAffineTransformMakeScale(ind_scale, ind_scale)];
                //[m_pActView.layer setValue:[NSNumber numberWithFloat:ind_scale] forKeyPath:@"transform.scale"];
            }
            break;
        }
    }
    va_end(ap);
}
int
CiOSActivityIndicator::status()
{
    BOOL isAnim = [m_pActView isAnimating];
    return isAnim ? 1 : 0;
}
