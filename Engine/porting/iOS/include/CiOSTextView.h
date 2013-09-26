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
//  CiOSTextView.h
//  GameEngine
//
//

#ifndef CiOSTextView_h
#define CiOSTextView_h

#import <UIKit/UIKit.h>

@interface CiOSTextView : UITextView
{
    NSString    *   m_pFontName;        // フォント名
    NSString    *   m_placeHolder;      // プレースホルダ文字列
    UIColor     *   m_placeHolderColor; // プレースホルダカラー
    NSTextAlignment textAlignment_; // label alignment
}

@property (nonatomic, retain) NSString  * m_pFontName;
@property (nonatomic, retain) NSString  * m_placeHolder;
@property (nonatomic, retain) UIColor   * m_placeHolderColor;
@property (nonatomic) NSTextAlignment textAlignment;

- (id)init;
- (void)dealloc;
- (void)awakeFromNib;
- (id)initWithFrame:(CGRect)frame;
- (void)setText:(NSString *)text;
- (void)drawRect:(CGRect)rect;
- (void)setFont:(UIFont*)font;

// 文字の入力数を確認しプレースホルダの機能を仕様
- (void)changedPlaceHolder:(NSNotification*)_notfication;

// プレースホルダの文字列を設定
- (void)setPlaceHolderString:(NSString *)_string;

@end

#endif
