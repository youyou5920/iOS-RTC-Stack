//
//  SettingsViewController.m
//  ZoomSDKSample
//
//  Created by Robust Hu on 7/6/15.
//  Copyright (c) 2015 Zoom Video Communications, Inc. All rights reserved.
//

#import "SettingsViewController.h"
#import <ZoomSDK/ZoomSDK.h>

@interface SettingsViewController ()

@property (retain, nonatomic) UITableViewCell *autoConnectAudioCell;
@property (retain, nonatomic) UITableViewCell *muteAudioCell;
@property (retain, nonatomic) UITableViewCell *muteVideoCell;
@property (retain, nonatomic) UITableViewCell *driveModeCell;
@property (retain, nonatomic) UITableViewCell *callInCell;
@property (retain, nonatomic) UITableViewCell *callOutCell;

@property (retain, nonatomic) NSArray *itemArray;

@end

@implementation SettingsViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.title = NSLocalizedString(@"Settings", @"");
    
    UIBarButtonItem *closeItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(onDone:)];
    [self.navigationItem setLeftBarButtonItem:closeItem];
    [closeItem release];
    
    NSMutableArray *array = [NSMutableArray array];
    [array addObject:@[[self autoConnectAudioCell]]];
    [array addObject:@[[self muteAudioCell]]];
    [array addObject:@[[self muteVideoCell]]];
    if ([UIDevice currentDevice].userInterfaceIdiom != UIUserInterfaceIdiomPad)
        [array addObject:@[[self driveModeCell]]];
    [array addObject:@[[self callInCell]]];
    [array addObject:@[[self callOutCell]]];
    self.itemArray = array;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)onDone:(id)sender
{
    [self dismissViewControllerAnimated:YES completion:NULL];
}

#pragma mark - Table view cells

- (UITableViewCell*)autoConnectAudioCell
{
    ZoomSDKMeetingSettings *settings = [[ZoomSDK sharedSDK] getMeetingSettings];
    if (!settings)
        return nil;
    
    BOOL isAutoConnected = [settings autoConnectInternetAudio];

    if (!_autoConnectAudioCell)
    {
        _autoConnectAudioCell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:nil];
        _autoConnectAudioCell.selectionStyle = UITableViewCellSelectionStyleNone;
        _autoConnectAudioCell.textLabel.text = NSLocalizedString(@"Auto Connect Internet Audio", @"");
        
        UISwitch *sv = [[UISwitch alloc] initWithFrame:CGRectZero];
        [sv setOn:isAutoConnected animated:NO];
        [sv addTarget:self action:@selector(onAutoConnectAudio:) forControlEvents:UIControlEventValueChanged];
        _autoConnectAudioCell.accessoryView = sv;
    }
    
    return _autoConnectAudioCell;
}

- (UITableViewCell*)muteAudioCell
{
    ZoomSDKMeetingSettings *settings = [[ZoomSDK sharedSDK] getMeetingSettings];
    if (!settings)
        return nil;
    
    BOOL isMuted = [settings muteAudioWhenJoinMeeting];
    
    if (!_muteAudioCell)
    {
        _muteAudioCell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:nil];
        _muteAudioCell.selectionStyle = UITableViewCellSelectionStyleNone;
        _muteAudioCell.textLabel.text = NSLocalizedString(@"Always Mute My Microphone", @"");
        
        UISwitch *sv = [[UISwitch alloc] initWithFrame:CGRectZero];
        [sv setOn:isMuted animated:NO];
        [sv addTarget:self action:@selector(onMuteAudio:) forControlEvents:UIControlEventValueChanged];
        _muteAudioCell.accessoryView = sv;
    }
    
    return _muteAudioCell;
}

- (UITableViewCell*)muteVideoCell
{
    ZoomSDKMeetingSettings *settings = [[ZoomSDK sharedSDK] getMeetingSettings];
    if (!settings)
        return nil;
    
    BOOL isMuted = [settings muteVideoWhenJoinMeeting];
    
    if (!_muteVideoCell)
    {
        _muteVideoCell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:nil];
        _muteVideoCell.selectionStyle = UITableViewCellSelectionStyleNone;
        _muteVideoCell.textLabel.text = NSLocalizedString(@"Always Mute My Video", @"");
        
        UISwitch *sv = [[UISwitch alloc] initWithFrame:CGRectZero];
        [sv setOn:isMuted animated:NO];
        [sv addTarget:self action:@selector(onMuteVideo:) forControlEvents:UIControlEventValueChanged];
        _muteVideoCell.accessoryView = sv;
    }
    
    return _muteVideoCell;
}

- (UITableViewCell*)driveModeCell
{
    ZoomSDKMeetingSettings *settings = [[ZoomSDK sharedSDK] getMeetingSettings];
    if (!settings)
        return nil;
    
    BOOL disabled = [settings driveModeDisabled];
    
    if (!_driveModeCell)
    {
        _driveModeCell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:nil];
        _driveModeCell.selectionStyle = UITableViewCellSelectionStyleNone;
        _driveModeCell.textLabel.text = NSLocalizedString(@"Disable Driving Mode", @"");
        
        UISwitch *sv = [[UISwitch alloc] initWithFrame:CGRectZero];
        [sv setOn:disabled animated:NO];
        [sv addTarget:self action:@selector(onDisableDriveMode:) forControlEvents:UIControlEventValueChanged];
        _driveModeCell.accessoryView = sv;
    }
    
    return _driveModeCell;
}

- (UITableViewCell*)callInCell
{
    ZoomSDKMeetingSettings *settings = [[ZoomSDK sharedSDK] getMeetingSettings];
    if (!settings)
        return nil;
    
    BOOL disabled = [settings callInDisabled];
    
    if (!_callInCell)
    {
        _callInCell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:nil];
        _callInCell.selectionStyle = UITableViewCellSelectionStyleNone;
        _callInCell.textLabel.text = NSLocalizedString(@"Disable Call in", @"");
        
        UISwitch *sv = [[UISwitch alloc] initWithFrame:CGRectZero];
        [sv setOn:disabled animated:NO];
        [sv addTarget:self action:@selector(onDisableCallIn:) forControlEvents:UIControlEventValueChanged];
        _callInCell.accessoryView = sv;
    }
    
    return _callInCell;
}

- (UITableViewCell*)callOutCell
{
    ZoomSDKMeetingSettings *settings = [[ZoomSDK sharedSDK] getMeetingSettings];
    if (!settings)
        return nil;
    
    BOOL disabled = [settings callOutDisabled];
    
    if (!_callOutCell)
    {
        _callOutCell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:nil];
        _callOutCell.selectionStyle = UITableViewCellSelectionStyleNone;
        _callOutCell.textLabel.text = NSLocalizedString(@"Disable Call Out", @"");
        
        UISwitch *sv = [[UISwitch alloc] initWithFrame:CGRectZero];
        [sv setOn:disabled animated:NO];
        [sv addTarget:self action:@selector(onDisableCallOut:) forControlEvents:UIControlEventValueChanged];
        _callOutCell.accessoryView = sv;
    }
    
    return _callOutCell;
}

- (void)onAutoConnectAudio:(id)sender
{
    UISwitch *sv = (UISwitch*)sender;
    [[[ZoomSDK sharedSDK] getMeetingSettings] setAutoConnectInternetAudio:sv.on];
}

- (void)onMuteAudio:(id)sender
{
    UISwitch *sv = (UISwitch*)sender;
    [[[ZoomSDK sharedSDK] getMeetingSettings] setMuteAudioWhenJoinMeeting:sv.on];
}

- (void)onMuteVideo:(id)sender
{
    UISwitch *sv = (UISwitch*)sender;
    [[[ZoomSDK sharedSDK] getMeetingSettings] setMuteVideoWhenJoinMeeting:sv.on];
}

- (void)onDisableDriveMode:(id)sender
{
    UISwitch *sv = (UISwitch*)sender;
    [[[ZoomSDK sharedSDK] getMeetingSettings] disableDriveMode:sv.on];
}

- (void)onDisableCallIn:(id)sender
{
    UISwitch *sv = (UISwitch*)sender;
    [[[ZoomSDK sharedSDK] getMeetingSettings] disableCallIn:sv.on];
}

- (void)onDisableCallOut:(id)sender
{
    UISwitch *sv = (UISwitch*)sender;
    [[[ZoomSDK sharedSDK] getMeetingSettings] disableCallOut:sv.on];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return [self.itemArray count];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 1;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = self.itemArray[indexPath.section][indexPath.row];
    return cell;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section
{
    if (section == 0)
    {
        return NSLocalizedString(@"Auto Connect Internet Audio Setting", @"");
    }
    
    if (section == 1)
    {
        return NSLocalizedString(@"Always mute my microphone when joining others' meeting", @"");
    }
    
    if (section == 2)
    {
        return NSLocalizedString(@"Always mute my video when joining others' meeting", @"");
    }
    
    if (section == 3 && [UIDevice currentDevice].userInterfaceIdiom != UIUserInterfaceIdiomPad)
    {
        return NSLocalizedString(@"Driving Mode Setting", @"");
    }
    
    return nil;
}

@end
