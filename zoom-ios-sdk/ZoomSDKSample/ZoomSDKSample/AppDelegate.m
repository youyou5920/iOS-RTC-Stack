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

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    // Override point for customization after application launch.
    
    MainViewController *mainVC = [[[MainViewController alloc] init] autorelease];
    UINavigationController *navVC = [[[UINavigationController alloc] initWithRootViewController:mainVC] autorelease];
    navVC.navigationBarHidden = YES;
    
    //self.window.rootViewController = mainVC;
    self.window.rootViewController = navVC;
    
    self.window.backgroundColor = [UIColor whiteColor];
    [self.window makeKeyAndVisible];
    
    //1. Set ZoomSDK Domain
    [[ZoomSDK sharedSDK] setZoomDomain:kZoomSDKDomain];
    //2. Set Root Navigation Controller
    [[ZoomSDK sharedSDK] setZoomRootController:navVC];
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
}

#pragma mark - AlertView Delegate

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex
{
    if (buttonIndex != alertView.cancelButtonIndex)
    {
        [self performSelector:@selector(sdkAuth) withObject:nil afterDelay:0.f];
    }
}

@end
