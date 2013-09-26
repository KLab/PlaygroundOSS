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
//  EAGLView.h
//
//  Base Created by Dan Ginsburg on 6/13/09.
//

// #define OPENGL2

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import <StoreKit/StoreKit.h>
#import <OpenGLES/EAGL.h>
#import <AVFoundation/AVFoundation.h>

#if defined(__APPLE__)
#ifdef OPENGL2
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#else
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#endif
#else
#ifdef OPENGL2
#include "GLES2/gl2.h"
#else
#include "GLES/gl.h"
#endif
#endif
#import "CKLBTouchEventUI.h"
#define FPS_AVERAGE ( 5 )   // FPS計測用
#define USE_DEPTH_BUFFER ( 1 ) // whether enable depth buffer or not
#define IS_OPAQUE_VIEW ( NO ) // whether base view is opaque or not (ObjC bool style; i.e. YES / NO)

/*
This class wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
The view content is basically an EAGL surface you render your OpenGL scene into.
Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
*/
@interface EAGLView : UIView<UITextFieldDelegate, UITextViewDelegate, UIWebViewDelegate> {
    
@private
    /* The pixel dimensions of the backbuffer */
    GLint backingWidth;
    GLint backingHeight;
    
    EAGLContext *context;
    
    /* OpenGL names for the renderbuffer and framebuffers used to render to this view */
    GLuint viewRenderbuffer, viewFramebuffer;
    
    /* OpenGL name for the depth buffer that is attached to viewFramebuffer, if it exists (0 if it does not exist) */
    GLuint depthRenderbuffer;
    GLuint program;

    NSTimer *animationTimer;
    NSTimeInterval animationInterval;
    CFTimeInterval timePrev;
    CFTimeInterval timeInt;
    int frame;
	int touch_alloc_cursor;

#if ( DEBUG == 1 )
    CFTimeInterval fpsArray[ FPS_AVERAGE ]; // FPS計測時に平均を出すための保存配列
    int fpsCnt;                             // FPS値を保存する配列のインデックス
#endif
    
    // マルチタッチのUITouch割当を
    UITouch * pTouch[ CKLBTouchEventUIMgr::MAX_TOUCH_POINT ];  // 押されたポイントごとにインスタンスが作られる

	// CGame game;
    Boolean isInitiated;
    
    // キーボードのサイズ
    CGRect keyboardFrameEnd;
    UITextField * targetTextField;
    UITextView  * targetTextView;
    
    Boolean bContinue;
    UIViewController<UIAlertViewDelegate,SKProductsRequestDelegate,SKPaymentTransactionObserver>   *   viewCtrl;
}

@property NSTimeInterval animationInterval;

- (void)startAnimation;
- (void)stopAnimation;
- (void)drawView;
- (void)setTimePrev:(CFTimeInterval)value;
- (void)setViewController:(UIViewController<SKProductsRequestDelegate> *)viewController;
- (void)textTouchDown:(id)sender;
- (void)textTouchUp:(id)sender;

- (void)clearUITouches;
- (void)releaseTouch:(unsigned int)id :(const char*)caller;

+ (float)getScaleFactor;
@end
