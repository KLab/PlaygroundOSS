#import <QuartzCore/QuartzCore.h>
#import <AVFoundation/AVFoundation.h>
#import "EAGLView.h"

#define USE_DEPTH_BUFFER 1
#import "BaseType.h"

#include "CPFInterface.h"
#include "CiOSPlatform.h"
#include <sys/time.h>
#include "CiOSSysResource.h"

// A class extension to declare private methods
@interface EAGLView ()

@property (nonatomic, assign) NSTimer *animationTimer;

- (BOOL)createFramebuffer;
- (void)destroyFramebuffer;

@end


@implementation EAGLView

@synthesize animationTimer;
@synthesize animationInterval;

//The GL view is stored in the nib file. When it's unarchived it's sent -initWithCoder:
- (id)initWithCoder:(NSCoder *)coder {
	return self;
}

- (void)destroyFramebuffer {
	glDeleteFramebuffers(1, &viewFramebuffer);
	viewFramebuffer = 0;
	glDeleteRenderbuffers(1, &viewRenderbuffer);
	viewRenderbuffer = 0;
    
	if (depthRenderbuffer) {
		glDeleteRenderbuffers(1, &depthRenderbuffer);
		depthRenderbuffer = 0;
	}
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
}

- (void)setTimePrev:(CFTimeInterval)value {
	timePrev = value;
}

@end
