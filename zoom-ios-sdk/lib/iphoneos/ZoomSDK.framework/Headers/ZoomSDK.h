//
//  ZoomSDK.h
//  ZoomSDK
//
//  Created by Robust Hu on 8/7/14.
//  Copyright (c) 2016 Zoom Video Communications, Inc. All rights reserved.
//
#import <UIKit/UIKit.h>

//! Project version number for ZoomSDK.
FOUNDATION_EXPORT double ZoomSDKVersionNumber;

//! Project version string for ZoomSDK.
FOUNDATION_EXPORT const unsigned char ZoomSDKVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <ZoomSDK/PublicHeader.h>


#import <Foundation/Foundation.h>

//Zoom SDK Constants
#import <ZoomSDK/ZoomSDKConstants.h>

//Zoom SDK AuthService
#import <ZoomSDK/ZoomSDKAuthService.h>

//Zoom SDK MeetingService
#import <ZoomSDK/ZoomSDKMeetingService.h>

//Zoom SDK Meeting Settings
#import <ZoomSDK/ZoomSDKMeetingSettings.h>

//Zoom SDK Invite Helper
#import <ZoomSDK/ZoomSDKInviteHelper.h>

//Zoom SDK Pre-meeting Service
#import <ZoomSDK/ZoomSDKPremeetingService.h>

/**
 * The ZoomSDK class is a class that exposes a Zoom API Rest Client.
 *
 * Access to this class and all other components of the ZoomSDK can be granted by including `<ZoomSDK/ZoomSDK.h>`
 * in your source code.
 *
 * This class provides a class method sharedSDK which provides a preconfigured SDK client,
 * including a ZoomSDKMeetingService.
 *
 */
@interface ZoomSDK : NSObject
{
    NSString               *_zoomDomain;
    ZoomSDKMeetingService  *_meetingService;
    ZoomSDKMeetingSettings *_meetingSettings;
    
    ZoomSDKAuthService     *_authService;
    ZoomSDKPremeetingService *_premeetingService;
}

@property (retain, nonatomic) NSString *zoomDomain;

/**
 * Returns the ZoomSDK default SDK client
 *
 * This method is guaranteed to only instantiate one sharedSDK over the lifetime of an app.
 *
 * This client must be configured with your client key and client secret.
 *
 * *Note*: sharedSDK returns a ZoomSDK configured with a ZoomSDKMeetingService.
 *
 * @return a preconfigured SDK client
 */
+ (ZoomSDK*)sharedSDK;

/**
 * Sets the Zoom SDK client domain
 *
 * @param domain A domain which used as start/join zoom meeting
 *
 * *Note*: the domain should not include protocol "https" or "http", the format is just like "zoom.us" or "www.zoom.us".
 */
- (void)setZoomDomain:(NSString*)domain;

/**
 * Get the Zoom SDK client root navigation controller
 *
 * @return navController, A root navigation controller.
 */
- (UINavigationController*)zoomRootController;

/**
 * Sets the Zoom SDK client root navigation controller
 *
 * @param navController A root navigation controller for pushing Zoom meeting UI.
 */
- (void)setZoomRootController:(UINavigationController*)navController;

/**
 * Returns the ZoomSDK default Auth Service
 *
 * *Note*: Auth Service should be called at first, the Zoom SDK can be used after authorizing successfully.
 *
 * @return a preconfigured Auth Service
 */
- (ZoomSDKAuthService*)getAuthService;

/**
 * Returns the ZoomSDK default Pre-meeting Service
 *
 * *Note*: Pre-meeting Service should be called after signed in with work email, which is used to schedule/eidt/list/delete meeting etc.
 *
 * @return a preconfigured Pre-meeting Service
 */
- (ZoomSDKPremeetingService*)getPreMeetingService;

/**
 * Returns the ZoomSDK default Meeting Service
 *
 * @return a preconfigured Meeting Service
 */
- (ZoomSDKMeetingService*)getMeetingService;

/**
 * Returns the ZoomSDK default Meeting Settings
 *
 * @return a object of Meeting Settings
 */
- (ZoomSDKMeetingSettings*)getMeetingSettings;

/**
 * To get SDK supported languages
 *
 * @return SDK supported languages array
 */
- (NSArray *)supportedLanguages;

/**
 * Set the SDK language
 *
 * @param lang indicate language type base on SDK supported language.
 *
 * @return YES if success, Otherwise return NO.
 */
- (void)setLanguage:(NSString *)lang;

/**
 * Notify common layer that app will resign active
 */
- (void)appWillResignActive;

/**
 * Notify common layer that app did become active
 */
- (void)appDidBecomeActive;

/**
 * Notify common layer that app did enter backgroud
 */
- (void)appDidEnterBackgroud;

/**
 * Designated to open doc from Dropbox.
 *
 * @param url, the url of doc.
 *
 * *Note*: This method is optional, if client app wants to support Dropbox SDK in Zoom meeting.
 */
- (void)handleDropboxOpenURL:(NSURL *)url;

@end
