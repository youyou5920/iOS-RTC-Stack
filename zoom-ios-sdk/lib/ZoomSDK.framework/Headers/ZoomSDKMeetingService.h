//
//  ZoomSDKMeetingService.h
//  ZoomSDK
//
//  Created by Xiaojian Hu on 8/7/14.
//  Copyright (c) 2014 Zoom Video Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

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

/**
 * When meeting was started, Partner can customize to share special view to meeting participants by this notification.
 *
 * *Note*: This method is just for special customer.
 */
extern NSString* kNoti_AppShare_ShareView_Changed;

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
 * This method is used to start a Zoom meeting with meeting number.
 *
 * @param userId The userId received as a result client user account from Zoom site.
 * @param userToken The userToken received as a result client user account from Zoom site.
 * @param userType The userType depends on what the client account is.
 * @param username The username will be used as display name in the Zoom meeting.
 * @param meetingNumber The meetingNumber may be generated from a scheduled meeting or a Personal Meeting ID.
 *
 * @return A ZoomSDKMeetError to tell client whether the meeting started or not.
 */
- (ZoomSDKMeetError)startMeeting:(NSString*)userId userToken:(NSString*)userToken userType:(ZoomSDKUserType)userType displayName:(NSString*)username meetingNumber:(NSString*)meetingNumber;

/**
 * This method is used to start a instant Zoom meeting.
 *
 * @param userId The userId received as a result client user account from Zoom site.
 * @param userToken The userToken received as a result client user account from Zoom site.
 * @param userType The userType depends on what the client account is.
 * @param username The username will be used as display name in the Zoom meeting.
 *
 * @return A ZoomSDKMeetError to tell client whether a meeting started or not.
 */
- (ZoomSDKMeetError)startInstantMeeting:(NSString*)userId userToken:(NSString*)userToken userType:(ZoomSDKUserType)userType displayName:(NSString*)username;

/**
 * This method is used to join a Zoom meeting.
 *
 * @param meetingNumber The meetingNumber used to join the meeting.
 * @param username The username will be used as display name in the Zoom meeting.
 *
 * @return A ZoomSDKMeetError to tell client whether can join the meeting or not.
 */
- (ZoomSDKMeetError)joinMeeting:(NSString*)meetingNumber displayName:(NSString*)username;

/**
 * This method is used to join a Zoom meeting with password.
 *
 * @param meetingNumber The meetingNumber used to join the meeting.
 * @param username The username will be used as display name in the Zoom meeting.
 * @param pwd, The meeting password which used to join the meeting, if there does not exist meeting password, just set pwd to nil or @"".
 *
 * @return A ZoomSDKMeetError to tell client whether can join the meeting or not.
 */
- (ZoomSDKMeetError)joinMeeting:(NSString*)meetingNumber displayName:(NSString*)username password:(NSString*)pwd;

/**
 * This method is used to tell the client whether the meeting is ongoing or not.
 *
 * @return A ZoomSDKMeetingState to tell client the meeting state currently.
 */
- (ZoomSDKMeetingState)getMeetingState;

/**
 * This method is used to tell the customer who is the host of the meeting.
 *
 * @return YES, tell customer that current user is the host of the meeting.
 */
- (BOOL)isMeetingHost;

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
 * This method is used to change the view of share content.
 *
 * @param view, the view will be shared.
 *
 * *Note*: This method is just for special customer.
 */
- (void)appShareWithView:(UIView*)view;


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
 * Designated for Zoom Meeting State Change.
 *
 * @param state tell client meeting state chagne.
 *
 */
- (void)onMeetingStateChange:(ZoomSDKMeetingState)state;

@end

