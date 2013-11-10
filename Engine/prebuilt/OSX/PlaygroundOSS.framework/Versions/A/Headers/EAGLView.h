// #define OPENGL2

#import <GLKit/GLKit.h>
#import <StoreKit/StoreKit.h>
#import <AVFoundation/AVFoundation.h>

//#import "CuttingGame.h"

#define MAX_TOUCH 20     // 最大タッチ数
#define FPS_AVERAGE (5)     // FPS計測用

/*
 This class wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
 The view content is basically an EAGL surface you render your OpenGL scene into.
 Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
 */
@interface EAGLView {
@private
	/* The pixel dimensions of the backbuffer */
	GLint backingWidth;
	GLint backingHeight;
    
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
    
#if (DEBUG == 1)
	CFTimeInterval fpsArray[FPS_AVERAGE];   // FPS計測時に平均を出すための保存配列
	int fpsCnt;                             // FPS値を保存する配列のインデックス
#endif
    
	// CGame game;
	Boolean isInitiated;
    
	// キーボードのサイズ
	CGRect keyboardFrameEnd;
    
	Boolean bContinue;
}

@property NSTimeInterval animationInterval;

- (void)startAnimation;
- (void)stopAnimation;
- (void)drawView;
- (void)setTimePrev:(CFTimeInterval)value;
- (void)textTouchDown:(id)sender;
- (void)textTouchUp:(id)sender;

- (void)clearUITouches;

@end
