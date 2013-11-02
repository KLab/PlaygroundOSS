#import <Cocoa/Cocoa.h>
#import "NSGLView.h"

@class MainWindowController;

@interface PlaygroundAppDelegate : NSObject <NSApplicationDelegate> {
    NSGLView *glView;
}

@property (assign) IBOutlet NSWindow *window;

@end
