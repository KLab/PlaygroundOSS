#import "PlaygroundAppDelegate.h"
#import "NSGLView.h"
#include "CiOSPlatform.h"

@implementation PlaygroundAppDelegate

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	CPFInterface& pfif = CPFInterface::getInstance();
	CiOSPlatform * pPlatform = new CiOSPlatform(nullptr, 1.0f);
    pfif.setPlatformRequest(pPlatform);
    
    GameSetup();
    
    NSLog(@"app launched");
}

@end
