//
//  ZoomSDKConstants.h
//  ZoomSDK
//
//  Created by Robust Hu on 8/7/14.
//  Copyright (c) 2016 Zoom Video Communications, Inc. All rights reserved.
//

//ZoomSDK Base Domain
#define kZoomSDKBaseDomain @"zoom.us"

//Client Key or Secret is empty
#define kSDKAuthKeyOrSecretEmpty        300
//Client Key or Secret is wrong
#define kSDKAuthKeyOrSecretWrong        3023
//Account does not support SDK feature
#define kSDKAuthAccountNotSupport       3024
//Account has not enabled SDK feature
#define kSDKAuthAccountNotEnableSDK     3025

/**
 * Design for enable BoxSDK in ZoomSDK.
 *
 * **Note**: Before using Zoom SDK, the client should setup App Key and Secret of BoxSDK by [[NSUserDefaults standardUserDefaults] setObject:@"xxx" forKey:kBoxSDKAppKey], [[NSUserDefaults standardUserDefaults] setObject:@"yyy" forKey:kBoxSDKAppSecret].
 */
#define kBoxSDKAppKey               @"BoxSDK.AppKey"
#define kBoxSDKAppSecret            @"BoxSDK.AppSecret"

/**
 * Design for enable BoxSDK in DropboxSDK.
 *
 * **Note**: Before using Zoom SDK, the client should setup App Key and Secret of DropboxSDK by [[NSUserDefaults standardUserDefaults] setObject:@"xxx" forKey:kDropboxSDKAppKey], [[NSUserDefaults standardUserDefaults] setObject:@"yyy" forKey:kDropboxSDKAppSecret].
 */
#define kDropboxSDKAppKey           @"DropboxSDK.AppKey"
#define kDropboxSDKAppSecret        @"DropboxSDK.AppSecret"


typedef enum {
    //Auth Success
    ZoomSDKAuthError_Success,
    //Key or Secret is empty
    ZoomSDKAuthError_KeyOrSecretEmpty,
    //Key or Secret is wrong
    ZoomSDKAuthError_KeyOrSecretWrong,
    //Client Account does not support
    ZoomSDKAuthError_AccountNotSupport,
    //Client account does not enable SDK
    ZoomSDKAuthError_AccountNotEnableSDK,
    //Auth Unknown error
    ZoomSDKAuthError_Unknown,
}ZoomSDKAuthError;

typedef enum {
    //Success
    ZoomSDKMeetError_Success                    = 0,
    //Incorrect meeting number
    ZoomSDKMeetError_IncorrectMeetingNumber     = 1,
    //Meeting Timeout
    ZoomSDKMeetError_MeetingTimeout             = 2,
    //Network Unavailable
    ZoomSDKMeetError_NetworkUnavailable         = 3,
    //Client Version Incompatible
    ZoomSDKMeetError_MeetingClientIncompatible  = 4,
    //User is Full
    ZoomSDKMeetError_UserFull                   = 5,
    //Meeting is over
    ZoomSDKMeetError_MeetingOver                = 6,
    //Meeting does not exist
    ZoomSDKMeetError_MeetingNotExist            = 7,
    //Meeting has been locked
    ZoomSDKMeetError_MeetingLocked              = 8,
    //Meeting Restricted
    ZoomSDKMeetError_MeetingRestricted          = 9,
    //JBH Meeting Restricted
    ZoomSDKMeetError_MeetingJBHRestricted       = 10,
    
    //Invalid Arguments
    ZoomSDKMeetError_InvalidArguments           = 99,
    //Invalid Arguments
    ZoomSDKMeetError_InvalidUserType            = 100,
    //Unknown error
    ZoomSDKMeetError_Unknown                    = 101,
    
}ZoomSDKMeetError;

typedef enum {
    //Idle
    ZoomSDKMeetingState_Idle        = 0,
    //Connecting
    ZoomSDKMeetingState_Connecting  = 1,
    //In Meeting
    ZoomSDKMeetingState_InMeeting   = 2,
    
}ZoomSDKMeetingState;

