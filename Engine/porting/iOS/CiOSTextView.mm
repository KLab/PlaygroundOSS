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
//  CiOSTextView.mm
//  GameEngine
//
//

#import "CiOSTextView.h"

#define CIOS_TEXTVIEW_TAG   (999)

@implementation CiOSTextView

@synthesize m_pFontName;
@synthesize m_placeHolder;
@synthesize m_placeHolderColor;
@synthesize textAlignment=textAlignment_;

- (id)init
{
    self = [super init];
    
    if( self != nil )
    {
        self.m_placeHolderColor = [UIColor grayColor]; // 初期値灰色
    }
    
    return self;
}

- (void)dealloc
{
    [m_placeHolder release];
    m_placeHolder = nil;
    
    [m_placeHolderColor release];
    m_placeHolderColor = nil;
    
    [super dealloc];
}

- (void)awakeFromNib
{
    [super awakeFromNib];
    [self setPlaceHolderString:m_placeHolder];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(changedPlaceHolder:) name:UITextViewTextDidChangeNotification object:nil];
}

- (id)initWithFrame:(CGRect)frame
{
    if( (self = [super initWithFrame:frame]) )
    {
        // UITextViewで上寄せが上端まで行かないためマージンをマイナスで設定(-8は固定値だけどフォントによっては違うかも)
        self.contentInset = UIEdgeInsetsMake(-8,0,0,0);
        
        [self setPlaceHolderString:m_placeHolder];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(changedPlaceHolder:) name:UITextViewTextDidChangeNotification object:nil];
    }
    return self;
}

- (void)setText:(NSString *)text
{
    [super setText:text];
    [self changedPlaceHolder:nil];
}

float rectMargin = 8.0f;
- (void)drawRect:(CGRect)rect
{
    if([[self text] length] == 0 && [[self m_placeHolder] length] > 0)
    {
        [m_placeHolderColor set];
        [m_placeHolder drawInRect:CGRectMake(rectMargin,
                                             rectMargin,
                                             self.frame.size.width - (rectMargin * 2),
                                             self.frame.size.height - (rectMargin * 2))
                         withFont:self.font
                    lineBreakMode:UILineBreakModeClip
                        alignment:self.textAlignment];
    }
    
    // 表示
    [super drawRect:rect];
}

- (void)setFont:(UIFont*)font
{
    [super setFont:font];
    
    /*
    // フォントサイズをもとにマージンサイズを調べる
    CGFloat size = [self.font lineHeight];
    self.contentInset = UIEdgeInsetsMake(-8,0,0,0);
    CGFloat size = [self.font lineHeight];
     */
    
    return;
}

/*
    @brief  プレースホルダの表示切り替え
 */
- (void)changedPlaceHolder:(NSNotification*)_notfication
{
    // プレースホルダの文字列が無ければreturn
    if( [[self m_placeHolder] length] == 0 ) {
        return;
    }
    
    // 再描画
    [self setNeedsDisplay];
}

/*
    @brief  プレースホルダ文字列設定
 */
- (void)setPlaceHolderString:(NSString*)_string
{    
    // プレースホルダの文字が以前と同じならそもそも設定の必要なし
    if( [_string isEqual:m_placeHolder] ) {
        return;
    }

    [m_placeHolder release];
    m_placeHolder = [_string retain];
}

@end


