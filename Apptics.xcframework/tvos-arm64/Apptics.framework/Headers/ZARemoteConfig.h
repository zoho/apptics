//
//  ZARemoteConfig.h
//  JAnalytics
//
//  Created by Saravanan S on 06/05/19.
//  Copyright © 2019 zoho. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import "ZAEnums.h"
#import "ZARemoteConfigValue.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, ZARemoteConfigFetchStatus)  {
  ZARemoteConfigFetchStatusNotYetFetched=0,
  ZARemoteConfigFetchStatusSuccess,
  ZARemoteConfigFetchStatusFailure,
  ZARemoteConfigFetchStatusUpToDate,
  ZARemoteConfigFetchStatuThrottled
};

static NSString* ZARemoteConfigUpdateNotification = @"ZARemoteConfigUpdateNotification";

@interface ZARemoteConfig : NSObject

@property (readonly, strong, nonatomic, nullable) NSDate *lastFetchTime;
@property (readonly, assign, nonatomic) ZARemoteConfigFetchStatus lastFetchStatus;

/**
 * Returns a singleton instance of Remote Config.
 * @return ZARemoteConfig.
 */

+ (ZARemoteConfig *)shared;

/**
 * Enable remote config.
 * @param status BOOL.'
 */

- (void) enableRemoteConfig:(BOOL)status;

/**
 * Fetch configs with completion handler.
 * @param completion ZARemoteConfigFetchStatus.
 */

- (void) fetchRemoteConfigWithCompletion:(void(^)(ZARemoteConfigFetchStatus status))completion;

/**
 * Activates the most recently fetched configs, and returns true if activated successfully.
 * @return BOOL.
 */

- (BOOL) activateFetched;

/**
 * Asynchronously fetches and then activates the fetched configs.
 */

- (void) fetchAndActivate;

/**
 Use this method to set the current location of the user.
 
 @param location (code or name) String.
 */

-(void) setCurrentLocation : (NSString *) location;

- (nonnull ZARemoteConfigValue *)objectForKeyedSubscript:(nonnull NSString *)key;

- (nonnull ZARemoteConfigValue *)configValueForKey:(nullable NSString *)key;

-(void) addCustomCriteria : (NSString *) key value : (NSString*) value;

-(void) updateRemoteConfigWithData:(nullable NSDictionary*) rcInfo withCompletionHandler:(nullable void(^)(ZARemoteConfigFetchStatus status))completion;

@end

NS_ASSUME_NONNULL_END
