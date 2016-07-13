//
//  ZoomSDKErrors.h
//  ZoomSDK
//
//  Created by Robust Hu on 8/7/14.
//  Copyright (c) 2014 Zoom Video Communications, Inc. All rights reserved.
//

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
    //Unknown error
    ZoomSDKMeetError_Unknown                    = 100,

}ZoomSDKMeetError;

typedef enum {
    //Idle
    ZoomSDKMeetingState_Idle        = 0,
    //Connecting
    ZoomSDKMeetingState_Connecting  = 1,
    //In Meeting
    ZoomSDKMeetingState_InMeeting   = 2,
    
}ZoomSDKMeetingState;

