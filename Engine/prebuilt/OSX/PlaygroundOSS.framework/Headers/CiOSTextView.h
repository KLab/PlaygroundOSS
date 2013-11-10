#ifndef CiOSTextView_h
#define CiOSTextView_h

@interface CiOSTextView
{
	NSString *m_pFontName;              // フォント名
	NSString *m_placeHolder;            // プレースホルダ文字列
}

@property (nonatomic, retain) NSString *m_pFontName;
@property (nonatomic, retain) NSString *m_placeHolder;

- (id)init;
- (void)dealloc;
- (void)awakeFromNib;
- (id)initWithFrame:(CGRect)frame;
- (void)setText:(NSString *)text;
- (void)drawRect:(CGRect)rect;

// 文字の入力数を確認しプレースホルダの機能を仕様
- (void)changedPlaceHolder:(NSNotification *)_notfication;

// プレースホルダの文字列を設定
- (void)setPlaceHolderString:(NSString *)_string;

@end

#endif
