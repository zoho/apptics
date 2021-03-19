//
//  AppticsConfig.h
//  JAnalytics
//
//  Created by Saravanan S on 08/06/20.
//  Copyright © 2020 zoho. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AppticsConfig : NSObject

@property (nonatomic) bool enableBackgroundTask API_AVAILABLE(ios(13.0), tvos(13.0)) API_UNAVAILABLE(macos, watchos);
@property (nonatomic) bool enableAutoCheckForAppUpdate;
@property (nonatomic) bool enableCrossPromotionAppsList API_UNAVAILABLE(macos, tvos, watchos);

@property (nonatomic) bool enableFeedbackKit API_UNAVAILABLE(macos, tvos, watchos);
@property (nonatomic) int maxToleranceForShakeToFeedback API_UNAVAILABLE(macos, tvos, watchos);

@property (nonatomic) bool enableRemoteConfig;
@property (nonatomic) bool enableRateUs API_UNAVAILABLE(macos, watchos);
@property (nonatomic) bool trackOnByDefault;
@property (nonatomic) bool sendDataOnMobileNetworkByDefault;

@property (class) AppticsConfig *defaultConfig;

@end

NS_ASSUME_NONNULL_END
