#import "AppDelegate.h"

#import "ViewController.h"
#include "CPFInterface.h"
#include "CiOSSysResource.h"
#include "CiOSAudioManager.h"

@implementation AppDelegate

@synthesize window = _window;
@synthesize viewController = _viewController;

- (void)dealloc
{
    [_window release];
    [_viewController release];
    [super dealloc];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    // Override point for customization after application launch.
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        self.viewController = [[[ViewController alloc] initWithNibName:@"ViewController_iPhone" bundle:nil] autorelease];
    } else {
        self.viewController = [[[ViewController alloc] initWithNibName:@"ViewController_iPad" bundle:nil] autorelease];
    }
    self.window.rootViewController = self.viewController;
    [self.window makeKeyAndVisible];

    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    [_viewController stopAnimation];
    CiOSAudioManager::GetInstance().AudioDidResignActive();
    if(CPFInterface::getInstance().isClient()) {
        IClientRequest& client = CPFInterface::getInstance().client();
        client.controlEvent(IClientRequest::E_PAUSE, 0, 0, 0, 0, 0);
        client.frameFlip(1);    // 1フレーム分まわす。経過時間は 1[ms] という扱い。
        CiOSAudioManager::GetInstance().Exec(); // サウンドの毎フレーム処理
    }
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
    /* バックグラウンドにいく */
    CiOSAudioManager::GetInstance().AudioDidEnterBackground();
    [_viewController clearUITouches];
    [_viewController stopAnimation];
    [_viewController viewRecovery]; // 
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
    /* フォアグラウンドに戻ってくる */
    CiOSAudioManager::GetInstance().AudioDidEnterForeground();
    [_viewController startAnimation];
    [_viewController viewRecovery];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    CiOSAudioManager::GetInstance().AudioDidBecomeActive();
    [_viewController startAnimation];
    if(CPFInterface::getInstance().isClient()) {
        CPFInterface::getInstance().client().controlEvent(IClientRequest::E_RESUME, 0, 0, 0, 0, 0);
    }
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    /*
     Called when the application is about to terminate.
     Save data if appropriate.
     See also applicationDidEnterBackground:.
     */
    // ゲーム終了処理を呼ぶ
//    CPFInterface::getInstance().client().finishGame();
}

- (void)application:(UIApplication *)app didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)devToken
{
    NSUInteger len = [devToken length];
    const void * devTokenBytes = (len > 0) ? [devToken bytes] : 0;
  
    CiOSSysResource& sysRes = CiOSSysResource::getInstance();
        
    if(devTokenBytes) {
        sysRes.setDevID(devTokenBytes);
    } else {
        sysRes.failedDevID();
    }
}

- (void)application:(UIApplication *)app didFailToRegisterForRemoteNotificationsWithError:(NSError *)error
{
    NSLog(@"Error in registration. Error: %@", error);
    CiOSSysResource& sysRes = CiOSSysResource::getInstance();
    sysRes.failedDevID();
}
@end

