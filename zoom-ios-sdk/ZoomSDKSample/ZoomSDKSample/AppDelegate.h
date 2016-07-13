//
//  AppDelegate.h
//  ZoomSDKSample
//
//  Created by Xiaojian Hu on 3/17/14.
//  Copyright (c) 2014 Zoom Video Communications, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <ZoomSDK/ZoomSDK.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate, ZoomSDKAuthDelegate, UIAlertViewDelegate>

@property (strong, nonatomic) UIWindow *window;

@end
