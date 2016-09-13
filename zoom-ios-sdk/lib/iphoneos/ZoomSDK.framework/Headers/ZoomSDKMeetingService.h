//
//  ZoomSDKMeetingService.h
//  ZoomSDK
//
//  Created by Robust Hu on 8/7/14.
//  Copyright (c) 2016 Zoom Video Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKConstants.h"

typedef enum {
    //API user type
    ZoomSDKUserType_APIUser     = 99,
    //Work email user type
    ZoomSDKUserType_ZoomUser    = 100,
    //Single-sign-on user type
    ZoomSDKUserType_SSOUser     = 101,
}ZoomSDKUserType;

typedef enum {
    //Leave meeting
    LeaveMeetingCmd_Leave,
    //End Meeting
    LeaveMeetingCmd_End,
}LeaveMeetingCmd;

typedef enum {
    //Show JBH waiting
    JBHCmd_Show,
    //Hide JBH waiting
    JBHCmd_Hide,
}JBHCmd;


/**
 * The key of dictionary for parameter of method "startMeetingWithDictionary".
 *
 * @key kMeetingParam_UserID, The userId for start meeting.
 * @key kMeetingParam_UserToken, The token for start meeting.
 * @key kMeetingParam_UserType, The user type for start meeting.
 * @key kMeetingParam_Username, The user name for start meeting.
 * @key kMeetingParam_MeetingNumber, The meeting number for start meeting.
 * @key kMeetingParam_MeetingPassword, The meeting password for join meeting.
 * @key kMeetingParam_ParticipantID, the key is optional, If set, user will use the participant ID to join meeting.
 * @key kMeetingParam_IsAppShare, the key is optional, If set @(YES), user will start a meeting for app share.
*/
extern NSString* kMeetingParam_UserID;
extern NSString* kMeetingParam_UserToken;
extern NSString* kMeetingParam_UserType;
extern NSString* kMeetingParam_Username;
extern NSString* kMeetingParam_MeetingNumber;
extern NSString* kMeetingParam_MeetingPassword;
extern NSString* kMeetingParam_ParticipantID;
extern NSString* kMeetingParam_IsAppShare;

@protocol ZoomSDKMeetingServiceDelegate;

/**
 * ZoomSDKMeetingService is an implementation for client to start/join Zoom Meetings.
 * This meeting service assumes there is only one concurrent operation at a time. This means
 * that at any given time, only one API call will be in progress.
 */
@interface ZoomSDKMeetingService : NSObject

/**
 * The object that acts as the delegate of the receiving meeting events.
 */
@property (assign, nonatomic) id<ZoomSDKMeetingServiceDelegate> delegate;

/**
 * This method is used to start a Zoom meeting with parameters in a dictionary.
 *
 * @param dict The dictionary which contains the meeting parameters.
 *
 * @return A ZoomSDKMeetError to tell client whether the meeting started or not.
 */
- (ZoomSDKMeetError)startMeetingWithDictionary:(NSDictionary*)dict;

/**
 * This method is used to join a Zoom meeting with parameters in a dictionary.
 *
 * @param dict The dictionary which contains the meeting parameters.
 *
 * @return A ZoomSDKMeetError to tell client whether can join the meeting or not.
 */
- (ZoomSDKMeetError)joinMeetingWithDictionary:(NSDictionary*)dict;

/**
 * This method is used to tell the client whether the meeting is ongoing or not.
 *
 * @return A ZoomSDKMeetingState to tell client the meeting state currently.
 */
- (ZoomSDKMeetingState)getMeetingState;

/**
 * This method is used to tell whether the current user is the host of the meeting or not.
 *
 * @return YES, the current user is the host of the meeting.
 */
- (BOOL)isMeetingHost;

/**
 * This method is used to tell whether the meeting is locked by host or not.
 *
 * @return YES, the meeting has been locked by host.
 */
- (BOOL)isMeetingLocked;

/**
 * This method is used to end/leave an ongoing meeting.
 *
 * @param cmd, leave meeting by the command type.
 */
- (void)leaveMeetingWithCmd:(LeaveMeetingCmd)cmd;

/**
 * This method is used to tell the client whether the meeting audio existed or not.
 *
 * @return YES if the meeting audio does not exist.
 */
- (BOOL)isNoMeetingAudio;

/**
 * This method is used to pause/resume audio in the meeting.
 *
 * @param pause, if YES to pause audio; if NO to resume audio.
 */
- (BOOL)pauseMeetingAudio:(BOOL)pause;

/**
 * This method is used to tell the client whether cloud record is enabled.
 *
 * @return YES if cloud record is enabled.
 */
- (BOOL)isCMREnabled;

/**
 * This method is used to tell the client whether cloud record is in progress.
 *
 * @return YES if cloud record is in progress.
 */
- (BOOL)isCMRInProgress;

/**
 * This method is used to turn on/off cloud record in the meeting.
 *
 * @param on, if YES to turn on cloud record; if NO to turn off cloud record.
 */
- (void)turnOnCMR:(BOOL)on;

/**
 * This method will return the view of meeting UI, which provide an access which allow customer to add their own view in the meeting UI.
 *
 * @return the view of meeting if the meeting is ongoing, or return nil.
 */
- (UIView*)meetingView;

/**
 * This method is used to tell the client is starting share or not.
 *
 * @return YES if the client is starting share.
 *
 */
- (BOOL)isStartingShare;

/**
 * This method is used to tell the client is viewing share or not.
 *
 * @return YES if the client is viewing share.
 *
 */
- (BOOL)isViewingShare;

/**
 * This method is used to tell the client whether the meeting is an app share meeting.
 *
 * @return YES if the meeting is an app share meeting.
 *
 * *Note*: This method is just for special customer.
 */
- (BOOL)isDirectAppShareMeeting;
/**
 * This method is used to change the view of share content.
 *
 * @param view, the view will be shared.
 *
 * *Note*: This method is just for special customer.
 */
- (void)appShareWithView:(UIView*)view;

/**
 * This method is used to show UI of zoom meeting.
 *
 * @param completion, can be used to do some action after showing zoom meeting UI.
 *
 * *Note*: This method is just for special customer.
 */
- (void)showZoomMeeting:(void (^)(void))completion;

/**
 * This method is used to hide UI of zoom meeting.
 *
 * @param completion, can be used to do some action after hiding zoom meeting UI.
 *
 * *Note*: This method is just for special customer.
 */
- (void)hideZoomMeeting:(void (^)(void))completion;

/**
 * This method is used to start app share.
 *
 * *Note*: This method is just for special customer.
 */
- (BOOL)startAppShare;

/**
 * This method is used to stop app share.
 *
 * *Note*: This method is just for special customer.
 */
- (void)stopAppShare;

@end

/**
 * ZoomSDKMeetingServiceDelegate
 * An Meeting Service will issue the following value when the meeting state changes:
 *
 * ZoomSDKMeetError
 * ============================
 * - ZoomSDKMeetError_Success: start/join meeting successfully.
 * - ZoomSDKMeetError_IncorrectMeetingNumber: the meeting number is incorrect.
 * - ZoomSDKMeetError_MeetingTimeout: start/join meeting timeout.
 * - ZoomSDKMeetError_NetworkUnavailable: start/join meeting failed for network issue.
 * - ZoomSDKMeetError_MeetingClientIncompatible: cannot start/join meeting for the client is too old.
 * - ZoomSDKMeetError_UserFull: cannot start/join meeting for the meeting has reached a maximum of participant.
 * - ZoomSDKMeetError_MeetingOver: cannot start/join meeting for the meeting is over.
 * - ZoomSDKMeetError_MeetingNotExist: cannot start/join meeting for the meeting doest not exist.
 * - ZoomSDKMeetError_MeetingLocked: cannot start/join meeting for the meeting was locked by host.
 * - ZoomSDKMeetError_MeetingRestricted: cannot start/join meeting for the meeting restricted.
 * - ZoomSDKMeetError_MeetingJBHRestricted: cannot start/join meeting for the meeting restricted for joining before host.
 * - ZoomSDKMeetError_InvalidArguments: cannot start/join meeting for invalid augument.
 * - ZoomSDKMeetError_Unknown: cannot start/join meeting for unknown reason.
 *
 * ZoomSDKMeetingState
 * ============================
 * - ZoomSDKMeetingState_Idle: idle now, client can start/join meeting if wanted.
 * - ZoomSDKMeetingState_Connecting: the client is starting/joining meeting.
 * - ZoomSDKMeetingState_InMeeting: the client is a meeting now.
 */
@protocol ZoomSDKMeetingServiceDelegate <NSObject>

@optional
/**
 * Designated for Zoom Meeting Response.
 *
 * @param error tell client related to this meeting event.
 * @param internalError Zoom internal error code
 *
 */
- (void)onMeetingReturn:(ZoomSDKMeetError)error internalError:(NSInteger)internalError;

/**
 * Designated for Zoom Meeting Error message.
 *
 * @param error Zoom internal error code.
 * @param message the message for meeting error
 *
 */
- (void)onMeetingError:(NSInteger)error message:(NSString*)message;

/**
 * Designated for Zoom Meeting State Change.
 *
 * @param state tell client meeting state chagne.
 *
 */
- (void)onMeetingStateChange:(ZoomSDKMeetingState)state;

/**
 * Designated for Zoom Meeting has been ready.
 *
 */
- (void)onMeetingReady;

/**
 * Designated for App share has started with default splash.
 *
 * *Note*: This method is just for special customer.
 */
- (void)onAppShareSplash;

/**
 * Designated for clicked the Share button in meeting.
 *
 * *Note*: This method is just for special customer.
 */
- (void)onClickedShareButton;

/**
 * Designated for notify that there does not exist ongoing share.
 *
 * *Note*: This method is just for special customer.
 */
- (void)onOngoingShareStopped;

/**
 * Designated for join a none-host meeting, Partner can show/hide a customized JBH waiting UI.
 *
 * *Note*: This method is just for special customer.
 */
- (void)onJBHWaitingWithCmd:(JBHCmd)cmd;


@end

