//
//  ZoomSDKAuthService.h
//  ZoomSDK
//
//  Created by Xiaojian Hu on 8/8/14.
//  Copyright (c) 2014 Zoom Video Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZoomSDKErrors.h"

@protocol ZoomSDKAuthDelegate;

/**
 * This class provides support for authorizing Zoom SDK.
 *
 * The Authorization Code Grant requires HTTP request to allow the user to authenticate with Zoom SDK and Authorize your
 * application. Upon successful authorization, the ZoomSDKAuthDelegate will give ZoomSDKAuthError_Success to user by method onZoomSDKAuthReturn.
 *
 * **Note**: Before using Zoom SDK, the client should authorize the Zoom SDK at first. or the function in Zoom
 *   SDK cannot work correctly.
 */
@interface ZoomSDKAuthService : NSObject

@property (assign, nonatomic) id<ZoomSDKAuthDelegate> delegate;

/**
 * The key value is used during the authorization code grant. This key value is generated from Zoom Web site.
 * This value should be a secret. DO NOT publish this value.
 *
 */
@property (retain, nonatomic) NSString *clientKey;

/**
 * The secret value is used during the authorization code grant. This secret value is generated from Zoom Web site.
 * This value should be a secret. DO NOT publish this value.
 *
 */
@property (retain, nonatomic) NSString *clientSecret;

/**
 * Designated initializer. Returns a ZoomSDKAuthService capable of authorizing Zoom SDK.
 *
 * @param key your client key, also known as API key.
 * @param secret your client secret. DO NOT publish this secret.
 *
 * @return A ZoomSDKAuthService capable of authorizing Zoom SDK.
 */
- (id)initWithAppKey:(NSString*)key appSecret:(NSString*)secret;

/**
 * Designated authorizing Zoom SDK.
 *
 * If the client key or secret is empty, user will get error:ZoomSDKAuthError_KeyOrSecretEmpty in method onZoomSDKAuthReturn from ZoomSDKAuthDelegate
 */
- (void)sdkAuth;

/**
 * @return A BOOL indicating whether the zoom sdk auth may be valid.
 */
- (BOOL)isAuthorized;

@end

/**
 * ZoomSDKAuthDelegate
 * An Auth Service will issue the following value when the authorization state changes:
 *
 * - ZoomSDKAuthError_Success: Zoom SDK authorizs successfully.
 * - ZoomSDKAuthError_KeyOrSecretEmpty: the client key or secret for SDK Auth is empty.
 * - ZoomSDKAuthError_KeyOrSecretWrong: the client key or secret for SDK Auth is wrong.
 * - ZoomSDKAuthError_AccountNotSupport: this client account cannot support Zoom SDK.
 * - ZoomSDKAuthError_AccountNotEnableSDK: this client account does not enable Zoom SDK.
 */
@protocol ZoomSDKAuthDelegate <NSObject>

@required
/**
 * Designated for Zoom SDK Auth response.
 *
 * @param returnValue tell user when the auth state changed.
 *
 */
- (void)onZoomSDKAuthReturn:(ZoomSDKAuthError)returnValue;

@end
