#import <StoreKit/StoreKit.h>
#import "EAGLView.h"
#import "CiOSMovieView.h"

@interface ViewController {
	IBOutlet CiOSMovieView *viewBase;
	IBOutlet EAGLView *viewGL;
}



- (void)viewRecovery;
- (void)stopAnimation;
- (void)startAnimation;
- (void)finishStoreTransaction:(NSString *)receipt;
- (void)clearUITouches;



@end
