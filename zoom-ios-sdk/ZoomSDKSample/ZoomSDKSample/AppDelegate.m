//
//  AppDelegate.m
//  ZoomSDKSample
//
//  Created by Robust Hu on 3/17/14.
//  Copyright (c) 2014 Zoom Video Communications, Inc. All rights reserved.
//

#import "AppDelegate.h"
#import "MainViewController.h"

#define kZoomSDKAppKey      @""
#define kZoomSDKAppSecret   @""
#define kZoomSDKDomain      @""

#define kZoomSDKEmail       @""
#define kZoomSDKPassword    @""

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    
    //init boxsdk, dropbox sdk, the method should be called before init ZoomSDK
    [self initCloudDrive];
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSLog(@"%@", paths[0]);
    
    MainViewController *mainVC = [[[MainViewController alloc] init] autorelease];
    UINavigationController *navVC = [[[UINavigationController alloc] initWithRootViewController:mainVC] autorelease];
    navVC.navigationBarHidden = YES;
    
    self.window.rootViewController = mainVC;
//    self.window.rootViewController = navVC;
    
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    
    //1. Set ZoomSDK Domain
    [[ZoomSDK sharedSDK] setZoomDomain:kZoomSDKDomain];
    //2. Set Root Navigation Controller
//    [[ZoomSDK sharedSDK] setZoomRootController:navVC];
    //3. ZoomSDK Authorize
    [self sdkAuth];
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
    
    [[ZoomSDK sharedSDK] appWillResignActive];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    [[ZoomSDK sharedSDK] appDidEnterBackgroud];
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    
    [[ZoomSDK sharedSDK] appDidBecomeActive];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

// For iOS 4.2+ support
- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url
  sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
//    if ([[url scheme] isEqualToString: @"db-zecq6smsyshct83"])
//    {
//        [[ZoomSDKCloudShareHelper sharedHelper] handleDropboxOpenURL:url];
//    }
    
    return YES;
}

- (void)initCloudDrive
{
//#define kAppKeyBoxSDK           @""
//#define kAppSecetBoxSDK         @""
//#define kAppKeyDropboxSDK       @""
//#define kAppSecetDropboxSDK     @""
//    
//    [[NSUserDefaults standardUserDefaults] setObject:kAppKeyBoxSDK forKey:kBoxSDKAppKey];
//    [[NSUserDefaults standardUserDefaults] setObject:kAppSecetBoxSDK forKey:kBoxSDKAppSecret];
//    
//    [[NSUserDefaults standardUserDefaults] setObject:kAppKeyDropboxSDK forKey:kDropboxSDKAppKey];
//    [[NSUserDefaults standardUserDefaults] setObject:kAppSecetDropboxSDK forKey:kDropboxSDKAppSecret];
//    
//    [[NSUserDefaults standardUserDefaults] synchronize];
}

#pragma mark - Auth Delegate

- (void)sdkAuth
{
    ZoomSDKAuthService *authService = [[ZoomSDK sharedSDK] getAuthService];
    if (authService)
    {
        authService.delegate = self;
        
        authService.clientKey = kZoomSDKAppKey;
        authService.clientSecret = kZoomSDKAppSecret;
        
        [authService sdkAuth];
    }
}

- (void)onZoomSDKAuthReturn:(ZoomSDKAuthError)returnValue
{
    NSLog(@"onZoomSDKAuthReturn %d", returnValue);
    
    if (returnValue != ZoomSDKAuthError_Success)
    {
        NSString *message = [NSString stringWithFormat:NSLocalizedString(@"SDK authentication failed, error code: %zd", @""), returnValue];
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"" message:message delegate:self cancelButtonTitle:NSLocalizedString(@"OK", @"") otherButtonTitles:NSLocalizedString(@"Retry", @""), nil];
        [alert show];
    }
    else
    {
//        ZoomSDKAuthService *authService = [[ZoomSDK sharedSDK] getAuthService];
//        if (authService)
//        {
//            [authService loginWithZoom:kZoomSDKEmail password:kZoomSDKPassword];
//        }
    }
}

- (void)onZoomSDKLoginReturn:(NSInteger)returnValue
{
    NSLog(@"onZoomSDKLoginReturn result=%zd", returnValue);
    
    ZoomSDKPremeetingService *service = [[ZoomSDK sharedSDK] getPreMeetingService];
    if (service)
    {
        service.delegate = self;
    }
}

- (void)onZoomSDKLogoutReturn:(NSInteger)returnValue
{
    NSLog(@"onZoomSDKLogoutReturn result=%zd", returnValue);
}

#pragma mark - AlertView Delegate

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex
{
    if (buttonIndex != alertView.cancelButtonIndex)
    {
        [self performSelector:@selector(sdkAuth) withObject:nil afterDelay:0.f];
    }
}

#pragma mark - Premeeting Delegate


- (void)sinkSchedultMeeting:(NSInteger)result
{
    NSLog(@"sinkSchedultMeeting result: %zd", result);
}

- (void)sinkEditMeeting:(NSInteger)result
{
    NSLog(@"sinkEditMeeting result: %zd", result);
}

- (void)sinkDeleteMeeting:(NSInteger)result
{
    NSLog(@"sinkDeleteMeeting result: %zd", result);
}

- (void)sinkListMeeting:(NSInteger)result withMeetingItems:(NSArray*)array
{
    NSLog(@"sinkSchedultMeeting result: %zd  items: %@", result, array);
}


@end
