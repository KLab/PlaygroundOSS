#import "CiOSMovieView.h"
#include "CiOSWidget.h"
@implementation CiOSMovieView

+ (Class)layerClass {
	return [AVPlayerLayer class];
}

- (void)playerItemDidReachEnd:(NSNotification *)notification {
	AVPlayerItem *p = [notification object];
	CiOSMovieWidget *pWidget = NULL;
    
	if (!pWidget) return;
	pWidget->setStatus(1);  // 終了ステータスを書き込む
	// movie play end
}

@end
