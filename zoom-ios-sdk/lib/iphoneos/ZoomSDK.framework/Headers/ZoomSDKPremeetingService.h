//
//  ZoomSDKPremeetingService.h
//  ZoomSDK
//
//  Created by Robust Hu on 16/8/3.
//  Copyright © 2016年 Zoom Video Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ZoomSDKMeetingItem;
@protocol ZoomSDKPremeetingDelegate;

/**
 * This class provides support for schedule/edit/delete meeting Zoom SDK once login with work email.
 *
 * **Note**: Before using ZoomSDKPremeetingService, the Zoom SDK should be logged in with work email.
 */
@interface ZoomSDKPremeetingService : NSObject

/**
 * The object that acts as the delegate of the receiving schedule/edit/delete meeting events.
 */
@property (assign, nonatomic) id<ZoomSDKPremeetingDelegate> delegate;

/**
 * Designated for creating a meeting item which is used to edit meeting.
 *
 * @return an object of id<ZoomSDKMeetingItem>.
 *
 * *Note*: the created meeting item should be destroyed by method destroyMeetingItem finally.
 */
- (id<ZoomSDKMeetingItem>)createMeetingItem;

/**
 * Designated for deatroy a previous created meeting item.
 */
- (void)destroyMeetingItem:(id<ZoomSDKMeetingItem>)item;

/**
 * Designated for get a meeting item by a meeting number.
 *
 * @return an object of id<ZoomSDKMeetingItem>.
 *
 */
- (id<ZoomSDKMeetingItem>)getMeetingItemByNumber:(NSUInteger)meetingNumber;

/**
 * Designated for schudle a meeting with meeting item.
 */
- (BOOL)scheduleMeeting:(id<ZoomSDKMeetingItem>)meetingItem;

/**
 * Designated for edit a meeting with meeting item.
 */
- (BOOL)editMeeting:(id<ZoomSDKMeetingItem>)meetingItem;

/**
 * Designated for delete a meeting with meeting item.
 */
- (BOOL)deleteMeeting:(id<ZoomSDKMeetingItem>)meetingItem;

/**
 * Designated for list all of meetings which belong to the logged in user.
 */
- (BOOL)listMeeting;

@end

/**
 * ZoomSDKMeetingItem
 * which can be used to store the meeting information.
 */
@protocol ZoomSDKMeetingItem <NSObject>

/**
 * Meeting Topic
 */
- (void)setMeetingTopic:(NSString*)topic;
- (NSString*)getMeetingTopic;

/**
 * Meeting ID
 */
- (void)setMeetingID:(NSString*)mid;
- (NSString*)getMeetingID;

/**
 * Meeting Number
 */
- (void)setMeetingNumber:(unsigned long long)number;
- (unsigned long long)getMeetingNumber;

/**
 * Original Meeting Number
 */
- (void)setOriginalMeetingNumber:(unsigned long long)number;
- (long long)getOriginalMeetingNumber;

/**
 * Meeting Password
 */
- (void)setMeetingPassword:(NSString*)password;
- (NSString*)getMeetingPassword;

/**
 * Timezone ID
 */
- (void)setTimeZoneID:(NSString*)tzID;
- (NSString*)getTimeZoneID;

/**
 * Start Time
 */
- (void)setStartTime:(NSDate*)startTime;
- (NSDate*)getStartTime;

/**
 * Meeting Duration in minutes
 */
- (void)setDurationInMinutes:(NSUInteger)duration;
- (NSUInteger)getDurationInMinutes;

/**
 * Recurring Meeting
 */
- (void)setAsRecurringMeeting:(BOOL)recurring;
- (BOOL)isRecurringMeeting;

/**
 * Turn off host video
 */
- (void)turnOffVideoForHost:(BOOL)turnOff;
- (BOOL)isHostVideoOff;

/**
 * Turn off attendee video while joining meeting
 */
- (void)turnOffVideoForAttendee:(BOOL)turnOff;
- (BOOL)isAttendeeVideoOff;

/**
 * Allow to join a meeting before host
 */
- (void)setAllowJoinBeforeHost:(BOOL)allow;
- (BOOL)canJoinBeforeHost;

/**
 * The Meeting ID use PMI
 */
- (void)setUsePMIAsMeetingID:(BOOL)usePMI;
- (BOOL)isUsePMIAsMeetingID;

/**
 * The meeting is a personal meeting
 */
- (BOOL)isPersonalMeeting;

/**
 * The meeting is a Webinar meeting
 */
- (BOOL)isWebinarMeeting;

@end

/**
 * ZoomSDKPremeetingDelegate
 * which can be used to sink the event of schedule/edit/eidt/list meeting:
 */
@protocol ZoomSDKPremeetingDelegate <NSObject>

/**
 * Designated for sink the event of schedule meeting.
 */
- (void)sinkSchedultMeeting:(NSInteger)result;

/**
 * Designated for sink the event of edit meeting.
 */
- (void)sinkEditMeeting:(NSInteger)result;

/**
 * Designated for sink the event of delete meeting.
 */
- (void)sinkDeleteMeeting:(NSInteger)result;

/**
 * Designated for sink the event of list meeting.
 */
- (void)sinkListMeeting:(NSInteger)result withMeetingItems:(NSArray*)array;

@end