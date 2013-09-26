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
//  EAGLView.m
//
//  based on Hello Triangle sample created by Dan Ginsburg on 6/13/09.
//

#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>
#import <AVFoundation/AVFoundation.h>
#import "EAGLView.h"
#include <OpenGLES/ES2/gl.h>

#import "BaseType.h"

#include "CPFInterface.h"
#include "CiOSPlatform.h"
#include <sys/time.h>
#include "CiOSSysResource.h"
#include "CKLBTouchEventUI.h"

// A class extension to declare private methods
@interface EAGLView ()

@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, assign) NSTimer *animationTimer;

- (BOOL) createFramebuffer;
- (void) destroyFramebuffer;

@end


@implementation EAGLView

@synthesize context;
@synthesize animationTimer;
@synthesize animationInterval;

static float _mainScreenScale = -1.0f;

// You must implement this method
+ (Class)layerClass {
    return [CAEAGLLayer class];
}

+ (float)getScaleFactor {
    // 物理サイズを変動させる事は無い作りになっているので、キャッシュしておく
    if (_mainScreenScale < 0.0f) {
        CGFloat scale = 1.0f;
        if([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
            // iPhone/iPod Retinaの場合は従来通りの挙動にする
            scale = [UIScreen mainScreen].scale;
        } else{
            // iPad Retinaモデルでの拡大処理によるGPU負荷を下げるために、xibのサイズ以上はOS制御のアクセラレータに任せる
            // タッチ領域との整合性を取るために、scaleの値を使う各所で同じ処理を行う
            scale = MIN([UIScreen mainScreen].scale, 1.0);
        }
        _mainScreenScale = (float)scale;
    }

    return _mainScreenScale;
}

//The GL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id)initWithCoder:(NSCoder*)coder {
    
    if ((self = [super initWithCoder:coder])) {
        // Get the layer
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;

        eaglLayer.contentsScale = [EAGLView getScaleFactor];

        eaglLayer.opaque = IS_OPAQUE_VIEW;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking,
                                        kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
#ifdef OPENGL2
        context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
#else
        context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
#endif
        if([context API] == kEAGLRenderingAPIOpenGLES2) {
            NSLog(@"API OpenGL ES 2.0");
        } else {
            NSLog(@"API OpenGL ES 1.1");
        }
        if (!context || ![EAGLContext setCurrentContext:context]) {
            [self release];
            return nil;
        }
        
        self.backgroundColor = [UIColor colorWithWhite:0.0 alpha:0.0];
        self.multipleTouchEnabled = YES;
        self.userInteractionEnabled = YES;
        [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(onRotation:)
                                                     name:UIDeviceOrientationDidChangeNotification
                                                   object:nil];    

        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(keyboardDidShow:)
                                                     name:UIKeyboardWillShowNotification
                                                   object:nil];

        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(keyboardDidHide:)
                                                     name:UIKeyboardWillHideNotification 
                                                   object:nil];
        self.animationInterval = 1.0 / 60.0;
        isInitiated = false;
        {
            struct timeval tv;
            gettimeofday(&tv, NULL);
            timePrev = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        }
        for(int i = 0; i < CKLBTouchEventUIMgr::MAX_TOUCH_POINT; i++) {
            pTouch[i] = 0;
        }
#if ( DEBUG == 1 )
        for(int i = 0; i < FPS_AVERAGE; i++) {
            fpsArray[i] = timePrev;
        }
        fpsCnt = 0;
#endif
		touch_alloc_cursor = 0;
    }
    return self;
}

- (void)onRotation:(NSNotification *)notification {
    UIDeviceOrientation orientation = [[notification object] orientation];
    if (orientation == UIDeviceOrientationLandscapeLeft) {
        
    }
    else if (orientation == UIDeviceOrientationLandscapeRight) {
        
    }
    else if (orientation == UIDeviceOrientationPortrait) {
        
    }
    orientation = UIDeviceOrientationLandscapeLeft;
}

- (void)drawView {    
    [EAGLContext setCurrentContext:context];
    glBindFramebuffer(GL_FRAMEBUFFER, viewFramebuffer);

//    if(bContinue) {
        // frame の更新を呼び出す
        {
            struct timeval tv;
            gettimeofday(&tv, NULL);
            timeInt = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        }
        int deltaT = (timePrev) ? (timeInt - timePrev) : 1 ;   // 前回フレームからの経過時間
        timePrev = timeInt;

        // glViewport(0, 0, self.frame.size.width, self.frame.size.height);
        // プラットフォームインタフェースのreferenceを取得
        bContinue = (Boolean)CPFInterface::getInstance().client().frameFlip(deltaT);
    
        // サウンドの毎フレーム処理
        CiOSAudioManager::GetInstance().Exec();
 //   }
    
#if ( DEBUG == 1 )
    fpsArray[fpsCnt] = 1000.0 / deltaT;
    fpsCnt++;
    if( fpsCnt >= FPS_AVERAGE )
    {
        NSTimeInterval sum = 0.0;
        for(int i = 0; i < FPS_AVERAGE; i++) {
            sum += fpsArray[i];
        }
        sum = sum / FPS_AVERAGE;
//        NSLog(@"FPS:(%f)", sum);
        fpsCnt = 0;
    }
#endif
    
    glBindRenderbuffer(GL_RENDERBUFFER, viewRenderbuffer);
    [context presentRenderbuffer:GL_RENDERBUFFER];
}


- (void)layoutSubviews {
    [EAGLContext setCurrentContext:context];
    [self destroyFramebuffer];
    [self createFramebuffer];
//    [self Init];    // iOS ではフレームバッファ等を作った後でなければシェーダの作成に失敗するらしい。
    
    NSBundle* mainBundle;
    mainBundle = [NSBundle mainBundle];
    
    if(!isInitiated) {
        CiOSSysResource& sysRes = CiOSSysResource::getInstance();
        sysRes.requestDevID();
        
        // ゲーム初期化シーケンス
        // 起動関数を呼ぶ前に、インタフェースにStrategyを登録する必要がある。
        CiOSPlatform * pPlatform = new CiOSPlatform(viewCtrl, self, [EAGLView getScaleFactor]);
        CPFInterface& pfif = CPFInterface::getInstance();
        pfif.setPlatformRequest(pPlatform);
        
        // サウンド関係の初期化
        CiOSAudioManager::GetInstance().Initialize();
    
        // 起動関数を呼ぶ
        GameSetup();    // ゲーム起動関数。この中で CPFStrategy インスタンスの生成と登録を行う。
        pfif.client().setScreenInfo(false, backingWidth, backingHeight);
        pfif.client().setFilePath(/* mainBundle.bundlePath.UTF8String */ 0);      // CGame由来
        pfif.client().initGame();
        
        // FPS設定
//        NSTimeInterval fps = pfif.client().getFrameTime() / 1000.0f;
//        [self setAnimationInterval:fps];
        
        isInitiated = true;
        bContinue = TRUE;
    }
    [self drawView];
}


- (BOOL)createFramebuffer {
    
    glGenFramebuffers(1, &viewFramebuffer);
    glGenRenderbuffers(1, &viewRenderbuffer);
    
    glBindFramebuffer(GL_FRAMEBUFFER, viewFramebuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, viewRenderbuffer);
    [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*)self.layer];
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, viewRenderbuffer);
    
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &backingWidth);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &backingHeight);
    
    if (USE_DEPTH_BUFFER) {
        glGenRenderbuffers(1, &depthRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, backingWidth, backingHeight);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
    }
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
        return NO;
    }

    return YES;
}


- (void)destroyFramebuffer {
    
    glDeleteFramebuffers(1, &viewFramebuffer);
    viewFramebuffer = 0;
    glDeleteRenderbuffers(1, &viewRenderbuffer);
    viewRenderbuffer = 0;
    
    if(depthRenderbuffer) {
        glDeleteRenderbuffers(1, &depthRenderbuffer);
        depthRenderbuffer = 0;
    }
}

- (int) getTouchID:(UITouch *)touch :(Boolean)is_alloc {
    int i;
	if (touch) {
		// 既に割りてられていたら、そのIDを返す
		for(i = 0; i < CKLBTouchEventUIMgr::MAX_TOUCH_POINT; i++) {
			if(pTouch[i] == touch) return i;
		}
		if(is_alloc) {
			// 割り当てられていなければ、開いている場所のIDを返す
			for(i = 0; i < CKLBTouchEventUIMgr::MAX_TOUCH_POINT; i++) {
				int cursor = (i + touch_alloc_cursor) % CKLBTouchEventUIMgr::MAX_TOUCH_POINT;
				if (pTouch[cursor] == 0) {
					touch_alloc_cursor = (cursor + 1) % CKLBTouchEventUIMgr::MAX_TOUCH_POINT;
					return cursor;
				}
            }
        }
    }
    // 割当に失敗
    return -1;
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    // use just first instance
    for (UITouch *touch in touches) {
        unsigned int id = [self getTouchID:touch:true];
		// 割当不可能な場合は無視 ( < 0 || >= MaxTouch with unsigned)
        if(id >= CKLBTouchEventUIMgr::MAX_TOUCH_POINT)
        {
            CPFInterface::getInstance().platform().logging("!!! touchesBegan : i>=MAX_TOUCH");
            continue;
        }
        pTouch[id] = touch;
        CGPoint location = [touch locationInView:self];
        CPFInterface::getInstance().client().inputPoint(id, IClientRequest::I_CLICK,
			location.x * [EAGLView getScaleFactor],
			location.y * [EAGLView getScaleFactor]);
    }
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    // use just first instance
    for (UITouch *touch in touches) {
        unsigned int id = [self getTouchID:touch:false];
		// 割当不可能な場合は無視 ( < 0 || >= MaxTouch with unsigned)
        if(id >= CKLBTouchEventUIMgr::MAX_TOUCH_POINT)
        {
            CPFInterface::getInstance().platform().logging("!!! touchesMoved : i>=MAX_TOUCH");
            continue;
        }
        CGPoint location = [touch locationInView:self];
		CPFInterface::getInstance().client().inputPoint(id, IClientRequest::I_DRAG,
														location.x * [EAGLView getScaleFactor],
														location.y * [EAGLView getScaleFactor]);
    }
}

- (void)releaseTouch:(unsigned int)id :(const char *)caller
{
	if(id >= CKLBTouchEventUIMgr::MAX_TOUCH_POINT) {
		CPFInterface::getInstance().platform().logging("!!! %s : (i=%du)>=MAX_TOUCH ", caller, id);
		return;
	}

	UITouch * touch = pTouch[id];

	if(!touch) return;

	CGPoint location = [touch locationInView:self];

	CPFInterface::getInstance().client().inputPoint(id, IClientRequest::I_RELEASE,
													location.x * [EAGLView getScaleFactor],
													location.y * [EAGLView getScaleFactor]);
	pTouch[id] = 0;
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    for (UITouch *touch in touches) {
        unsigned int id = [self getTouchID:touch:false];
		[self releaseTouch:id:"touchesEnded"];
    }
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    for (UITouch *touch in touches) {
        unsigned int id = [self getTouchID:touch:false];
		[self releaseTouch:id:"touchesCancelled"];
    }
}

- (void)clearUITouches {
	// 全てのタッチがキャンセルされたことをクライアントに通知する
	// lua側がタッチIDのステートをハンドリングしてる場合、ここで通知しないと浮いてしまうため
	for(int i = 0; i < CKLBTouchEventUIMgr::MAX_TOUCH_POINT; i++) {
		if (pTouch[i] != 0) {
			[self releaseTouch:i:"clearUiTouches"];
		}
	}
    memset(pTouch,
           0,
           sizeof(UITouch*) * CKLBTouchEventUIMgr::MAX_TOUCH_POINT);
}

- (void)startAnimation {
    
    self.animationTimer = [NSTimer scheduledTimerWithTimeInterval:animationInterval target:self selector:@selector(drawView) userInfo:nil repeats:YES];
}


- (void)stopAnimation {
    self.animationTimer = nil;
}


- (void)setAnimationTimer:(NSTimer *)newTimer {
    [animationTimer invalidate];
    animationTimer = newTimer;
}


- (void)setAnimationInterval:(NSTimeInterval)interval {
    
    animationInterval = interval;
    if (animationTimer) {
        [self stopAnimation];
        [self startAnimation];
    }
}


- (void)dealloc {
    
    [self stopAnimation];
    
    CPFInterface::getInstance().client().finishGame();
    
    // サウンド関係の終了
    CiOSAudioManager::GetInstance().Termination();
    
    if ([EAGLContext currentContext] == context) {
        [EAGLContext setCurrentContext:nil];
    }
    
    [context release];  
    [super dealloc];
}

// WebViewによるロードが失敗した
- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error {
    
    CPFInterface::getInstance().platform().logging(">>>>>>>>> [web view] didFailLoadWithError %@", error);
    
    // URL更新がキャンセルされた際にもエラーとなる...なのでキャンセルはエラーとせずスルーするように変更 2013.3.8
    if( [error code] == NSURLErrorCancelled ) return;
    
    // 対象となるWidgetを検索する
    CiOSWebWidget * pWidget = CiOSWebWidget::searchWidget(webView);
    // native call の処理を記述。
    CPFInterface::getInstance().client().controlEvent(IClientRequest::E_FAILEDLOADWEB, pWidget, 0, 0, 0, 0);
}

// WebViewによるロードが開始された
- (void)webViewDidStartLoad:(UIWebView*)webView {
    // 対象となるWidgetを検索する
    CiOSWebWidget * pWidget = CiOSWebWidget::searchWidget(webView);
    // native call の処理を記述。
    CPFInterface::getInstance().client().controlEvent(IClientRequest::E_DIDSTARTLOADWEB, pWidget, 0, 0, 0, 0);
    CPFInterface::getInstance().platform().logging(">>>>>>>>> [web view] webViewDidStartLoad");
}

// WebViewによるロードが終わった
- (void)webViewDidFinishLoad:(UIWebView*)webView {
    // 対象となるWidgetを検索する
    CiOSWebWidget * pWidget = CiOSWebWidget::searchWidget(webView);
    // native call の処理を記述。
    CPFInterface::getInstance().client().controlEvent(IClientRequest::E_DIDLOADENDWEB, pWidget, 0, 0, 0, 0);
    CPFInterface::getInstance().platform().logging(">>>>>>>>> [web view] webViewDidFinishLoad");
}

- (BOOL)webView:(UIWebView *)webView
        shouldStartLoadWithRequest:(NSURLRequest *)request
        navigationType:(UIWebViewNavigationType)navigationType {
    // ページ内遷移でカスタムヘッダが削られる事があるので、
    // 無い場合は付け足して投げ直す
    // 出展: http://www.nomadplanet.fr/2010/09/custom-http-headers-for-every-request-made-in-uiwebviews/
    if ([webView respondsToSelector:@selector(hasCustomHeaders:)] &&
        ![webView hasCustomHeaders:request]) {
        
        [webView loadRequest:request];
        return NO;
    }

    // 対象となるWidgetを検索する
    CiOSWebWidget * pWidget = CiOSWebWidget::searchWidget(webView);
    NSString * requestString = [[request URL] absoluteString];

    if([requestString rangeOfString:@"native://"].location == NSNotFound) {
        // 通常の遷移の場合
        bool ret = (pWidget->getJump()) ? YES : NO;
        //pWidget->setFirst(); // 初回シグナルとジャンプフラグを見てるけど初回シグナルそもそも見る必要ない？
        if( ret==YES )
        {
            // linkへ飛ぶ時にloadRequestをしてやる必要がある
            if(navigationType == UIWebViewNavigationTypeLinkClicked)
            {
                [webView loadRequest:request];
            }
        }
        return ret;
    }

    // 要求された request String を、Widget の TmpString として記録する
    const char * keyString = [requestString UTF8String];
    pWidget->setTmpString(keyString + strlen("native://"));
    
    // native call の処理を記述。
    CPFInterface::getInstance().client().controlEvent(IClientRequest::E_URLJUMP, pWidget, 0, 0, 0, 0);

    // native call の時は遷移先が無いので NO を返す
    return NO;
}

- (void)setTimePrev:(CFTimeInterval)value
{
    timePrev = value;
}

- (void)setViewController:(UIViewController<UIAlertViewDelegate,SKProductsRequestDelegate,SKPaymentTransactionObserver> *)viewController {
    viewCtrl = viewController;
}

- (void)textTouchDown:(id)sender {
    UITextField *theField = (UITextField *)sender;
    CiOSTextWidget * pWidget = CiOSTextWidget::searchWidgetField(theField);
    if(pWidget) pWidget->setTouch(true);    // TouchDown
    
    UITextView *theView = (UITextView *)sender;
    pWidget = CiOSTextWidget::searchWidgetView(theView);
    if(pWidget) pWidget->setTouch(true);    // TouchDown
}

- (void)textTouchUp:(id)sender {
    UITextField *theField = (UITextField *)sender;
    CiOSTextWidget * pWidget = CiOSTextWidget::searchWidgetField(theField);
    if(pWidget) pWidget->setTouch(false);    // TouchUp
    
    UITextView *theView = (UITextView *)sender;
    pWidget = CiOSTextWidget::searchWidgetView(theView);
    if(pWidget) pWidget->setTouch(false);    // TouchUp
}

// テキストフィールドを編集する直後に呼ばれる
- (void)textFieldDidBeginEditing:(UITextField *)textField {
    targetTextField = textField;
}

// テキストフィールドが編集終了する直後に呼ばれる
- (void)textFieldDidEndEditing:(UITextField *)textField {
    CiOSTextWidget * pWidget = CiOSTextWidget::searchWidgetField(textField);
    CiOSTextWidget::setAllVisible(true);
    if(pWidget) {
        textField.font = pWidget->getFont();
        pWidget->size_recovery();
    }
    targetTextField = nil;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string {
    CiOSTextWidget * pWidget = CiOSTextWidget::searchWidgetField(textField);
    int maxlen = pWidget->getMax();
    NSMutableString * text = [[ textField.text mutableCopy] autorelease];
    [text replaceCharactersInRange:range withString:string];
    const char * utf8string = [string UTF8String];

    // 基本的に7bitASCIIは常に許可するが、IWidget::TXCH_UTF8が0の場合は最上位bitが1の文字が含まれていないことをチェックする
    int chartype = pWidget->getCharType();
    if(!(chartype & IWidget::TXCH_UTF8)) {
        for (const char * ptr = utf8string; *ptr; ptr++) {
            if(*ptr & 0x80) return NO;
        }
    }
   
    return (!maxlen) || ([text length] <= maxlen);
}

// textfieldでdoneが入力されたらキーボードを終了
- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    return YES;
}

// 編集終了時に呼ばれる
- (void)textViewDidEndEditing: (UITextView*) textView {
    // pause解除
    CPFInterface::getInstance().client().pauseGame(false);
}

// テキストビューを編集する直後に呼ばれれる
-(BOOL)textViewShouldBeginEditing:(UITextView*)textView {
    targetTextView = textView;
    return YES;
}

// テキストビューが編集終了する直後に呼ばれる
-(BOOL)textViewShouldEndEditing:(UITextView*)textView {
    CiOSTextWidget * pWidget = CiOSTextWidget::searchWidgetView(textView);
    CiOSTextWidget::setAllVisible(true);
    if(pWidget) {
        //textView.font = pWidget->getFont();
        const char * c_fontname = pWidget->getFontName();
        NSString * fontname = (c_fontname) ? [[NSString alloc] initWithUTF8String:c_fontname] : nil;
        if(targetTextField)
        {
            if( pWidget->getFont() ) {
                targetTextField.font = pWidget->getFont();
            } else {
                targetTextField.font = (fontname) ? [UIFont fontWithName:fontname size:16] : [UIFont systemFontOfSize:16];
            }
        }
        else if( targetTextView )
        {
            if( pWidget->getFont() ) {
                targetTextView.font = pWidget->getFont();
            } else {
                targetTextView.font = (fontname) ? [UIFont fontWithName:fontname size:16] : [UIFont systemFontOfSize:16];
            }
        }
        pWidget->size_recovery();
    }
    targetTextView = nil;
    return YES;
}

- (BOOL)textView:(UITextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text {
    CiOSTextWidget * pWidget = CiOSTextWidget::searchWidgetView(textView);
    int maxlen = pWidget->getMax();
    NSMutableString * string = [[ textView.text mutableCopy] autorelease];
    [string replaceCharactersInRange:range withString:text];
    const char * utf8string = [text UTF8String];
    
    // 基本的に7bitASCIIは常に許可するが、IWidget::TXCH_UTF8が0の場合は最上位bitが1の文字が含まれていないことをチェックする
    int chartype = pWidget->getCharType();
    if(!(chartype & IWidget::TXCH_UTF8)) {
        for (const char * ptr = utf8string; *ptr; ptr++) {
            if(*ptr & 0x80) return NO;
        }
    }
    
    // textviewで改行コードが入力された場合はキーボードを終了
    if ([text isEqualToString:@"\n"]) {
        [textView resignFirstResponder];
        return NO;
    }
    
    return (!maxlen) || ([string length] <= maxlen);
}

// 編集終了時に呼ばれる
// サードパーティがTextViewのdelegateを再登録した場合はtextViewDidEndEditingが呼ばれない事があるので、
// 通知センターでもポーズを解除する。
- (void)keyboardDidHide:(NSNotification*)note {
    CPFInterface::getInstance().client().pauseGame(false);
}

- (void)keyboardDidShow:(NSNotification*)note {
    // pause開始
    CPFInterface::getInstance().client().pauseGame(true);
    keyboardFrameEnd = [[note.userInfo objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue];
    if(targetTextField)
    {
        // テキストフィールドの場合
        CiOSTextWidget * pWidget = CiOSTextWidget::searchWidgetField(targetTextField);
        CiOSTextWidget::setAllVisible(false);
        targetTextField.hidden = NO;

        float scale = [EAGLView getScaleFactor];
        const char * c_fontname = pWidget->getFontName();
        NSString * fontname = (c_fontname) ? [[NSString alloc] initWithUTF8String:c_fontname] : nil;
        targetTextField.font = (fontname) ? [UIFont fontWithName:fontname size:32] : [UIFont systemFontOfSize:32];
        // 本来なら回転をみるべきだが・・・キーボードって画面の半部以上占領しないはず(あくまではず)なのでちっちゃい方を画面サイズから引く
        CGFloat min = (keyboardFrameEnd.size.width > keyboardFrameEnd.size.height) ? keyboardFrameEnd.size.height : keyboardFrameEnd.size.width;
        targetTextField.frame = CGRectMake(0,
                                           0,
                                           (backingWidth / scale),
                                           (backingHeight / scale) - min);
    }
    else if(targetTextView)
    {
        // テキストビューの場合
        CiOSTextWidget * pWidget = CiOSTextWidget::searchWidgetView(targetTextView);
        CiOSTextWidget::setAllVisible(false);
        targetTextView.hidden = NO;
        
        float scale = [EAGLView getScaleFactor];
        const char * c_fontname = pWidget->getFontName();
        NSString * fontname = (c_fontname) ? [[NSString alloc] initWithUTF8String:c_fontname] : nil;
        targetTextView.font = (fontname) ? [UIFont fontWithName:fontname size:32] : [UIFont systemFontOfSize:32];
        // 本来なら回転をみるべきだが・・・キーボードって画面の半部以上占領しないはず(あくまではず)なのでちっちゃい方を画面サイズから引く
        CGFloat min = (keyboardFrameEnd.size.width > keyboardFrameEnd.size.height) ? keyboardFrameEnd.size.height : keyboardFrameEnd.size.width;
        targetTextView.frame = CGRectMake(0,
                                          0,
                                          (backingWidth / scale),
                                          (backingHeight / scale) - min);
    }
}


@end
