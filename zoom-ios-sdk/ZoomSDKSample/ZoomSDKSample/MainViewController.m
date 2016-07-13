//
//  MainViewController.m
//  ZoomSDKSample
//
//  Created by Robust Hu on 3/17/14.
//  Copyright (c) 2014 Zoom Video Communications, Inc. All rights reserved.
//

#import "MainViewController.h"
#import "SettingsViewController.h"
#import "UIImage+Additions.h"
#import "UIColor+Additions.h"
#import "MBProgressHUD.h"


#define kSDKUserID      @""
#define kSDKUserName    @""
#define kSDKUserToken   @""
#define kSDKMeetNumber  @""

@interface MainViewController ()<UIAlertViewDelegate>

@end

@implementation MainViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)dealloc
{
    [_logoImageView release];
    [_statusLabel release];
    [_meetNowButton release];
    [_joinMeetButton release];
    
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    self.title = @"ZoomSDK Sample";
     
    _statusLabel.text = NSLocalizedString(@"Hello Zoom SDK", @"");
    
    _logoImageView.image = [UIImage imageNamed:@"zoom_chat_placeholder"];
    
    [_settingsButton setImage:[UIImage imageNamed:@"icon_settings"] forState:UIControlStateNormal];
    
    UIColor *bgColor = [UIColor colorWithHex:0xF39C12];
    [self.meetNowButton setBackgroundImage:[UIImage imageWithColor:bgColor] forState:UIControlStateNormal];
    [self.joinMeetButton setBackgroundImage:[UIImage imageWithColor:bgColor] forState:UIControlStateNormal];
    
#if 0
    //For Customize Meeting Invitation
    [ZoomSDKInviteHelper sharedInstance].customizeInvite = YES;
    [ZoomSDKInviteHelper sharedInstance].inviteVCName = @"InviteViewController";
#endif
    
    //For Enable/Disable Copy URL
//    [ZoomSDKInviteHelper sharedInstance].disableCopyURL = YES;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    //for bug that there exist 20 pixels in the bottom while leaving meeting quickly
    [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationNone];
    [[UIApplication sharedApplication] setStatusBarHidden:NO withAnimation:UIStatusBarAnimationNone];
}

- (IBAction)onMeetNow:(id)sender
{
    ZoomSDKMeetingService *ms = [[ZoomSDK sharedSDK] getMeetingService];
    if (ms)
    {
        ms.delegate = self;
        
        //for scheduled meeting
        ZoomSDKMeetError ret = [ms startMeeting:kSDKUserID userToken:kSDKUserToken userType:ZoomSDKUserType_ZoomUser displayName:kSDKUserName meetingNumber:kSDKMeetNumber];
//        ZoomSDKMeetError ret = [ms startMeeting:kSDKUserID userToken:kSDKUserToken userType:ZoomSDKUserType_APIUser displayName:kSDKUserName meetingNumber:kSDKMeetNumber];
        
        //for instant meeting
//        ZoomSDKMeetError ret = [ms startInstantMeeting:kSDKUserID userToken:kSDKUserToken userType:ZoomSDKUserType_ZoomUser displayName:kSDKUserName];
        
        NSLog(@"onMeetNow ret:%d", ret);
    }
}

- (IBAction)onJoinaMeeting:(id)sender
{
    ZoomSDKMeetingService *ms = [[ZoomSDK sharedSDK] getMeetingService];
    if (ms)
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"" message:@"Please input the meeting number" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"OK", nil];
        
        alert.alertViewStyle = UIAlertViewStyleLoginAndPasswordInput;
        [alert textFieldAtIndex:0].placeholder = @"#########";
        [alert textFieldAtIndex:0].keyboardType = UIKeyboardTypeNumberPad;
        
        [alert show];
        [alert release];
    }
}

- (IBAction)onSettings:(id)sender
{
    ZoomSDKMeetingSettings *settings = [[ZoomSDK sharedSDK] getMeetingSettings];
    if (!settings)
        return;

    SettingsViewController *vc = [[SettingsViewController alloc] initWithStyle:UITableViewStyleGrouped];
    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:vc];
    nav.modalPresentationStyle = UIModalPresentationFormSheet;
    
    [self presentViewController:nav animated:YES completion:NULL];
    
    [nav release];
    [vc release];
}

#pragma mark - Meeting Service Delegate

- (void)onMeetingReturn:(ZoomSDKMeetError)error internalError:(NSInteger)internalError
{
    NSLog(@"onMeetingReturn:%d, internalError:%zd", error, internalError);
}

- (void)onMeetingStateChange:(ZoomSDKMeetingState)state
{
    NSLog(@"onMeetingStateChange:%d", state);
    
#if 1
    if (state == ZoomSDKMeetingState_InMeeting)
    {
        //For customizing the content of Invite by SMS
        NSString *meetingID = [[ZoomSDKInviteHelper sharedInstance] meetingID];
        NSString *smsMessage = [NSString stringWithFormat:NSLocalizedString(@"Please join meeting with ID: %@", @""), meetingID];
        [[ZoomSDKInviteHelper sharedInstance] setInviteSMS:smsMessage];
        
        //For customizing the content of Copy URL
        NSString *joinURL = [[ZoomSDKInviteHelper sharedInstance] joinMeetingURL];
        NSString *copyURLMsg = [NSString stringWithFormat:NSLocalizedString(@"Meeting URL: %@", @""), joinURL];
        [[ZoomSDKInviteHelper sharedInstance] setInviteCopyURL:copyURLMsg];
    }
#endif
    
#if 0
    //For adding customize view above the meeting view
    if (state == ZoomSDKMeetingState_InMeeting)
    {
        ZoomSDKMeetingService *ms = [[ZoomSDK sharedSDK] getMeetingService];
        UIView *v = [ms meetingView];
        
        UIView *sv = [[UIView alloc] initWithFrame:CGRectMake(30, 100, 50, 50)];
        sv.backgroundColor = [UIColor redColor];
        [v addSubview:sv];
        [sv release];
    }
    
#endif
}

#pragma mark - AlertView Delegate

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex != alertView.cancelButtonIndex)
    {
        NSString *text = [alertView textFieldAtIndex:0].text;
        ZoomSDKMeetingService *ms = [[ZoomSDK sharedSDK] getMeetingService];
        if ([text length] > 0 && ms)
        {
            ms.delegate = self;
            NSString *pwd = [alertView textFieldAtIndex:1].text;
            ZoomSDKMeetError ret = [ms joinMeeting:text displayName:kSDKUserName password:pwd];
            NSLog(@"onJoinaMeeting ret:%d", ret);
        }
    }
}

@end
