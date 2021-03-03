//
//  ZAAPIManager.h
//  JAnalytics
//
//  Created by Saravanan S on 03/12/18.
//  Copyright © 2018 zoho. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ZAAPIManager : NSObject

+ (ZAAPIManager *)sharedInstance;
- (void) enableApiTrackingForSessionConfiguration : (NSURLSessionConfiguration*) config;
- (NSString*) getApiIdForUrl : (NSURLRequest*) request;

@end

NS_ASSUME_NONNULL_END
