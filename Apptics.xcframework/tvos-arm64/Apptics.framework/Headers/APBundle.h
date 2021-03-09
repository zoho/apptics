//
//  APBundle.h
//  Pods
//
//  Created by Saravanan S on 17/07/18.
//

#import <Foundation/Foundation.h>
#import "APEventsEnum.h"
NS_ASSUME_NONNULL_BEGIN
@interface APBundle : NSBundle

@property (nonatomic, retain) NSString * _Nullable lang;
@property (nonatomic, retain) NSString * _Nullable location;
@property (nonatomic, retain) Class<APEventsProtocol> _Nullable eventsProtocolClass;
@property (nonatomic, retain) Class<APAPIProtocol> _Nullable apiProtocolClass;

+(NSBundle * _Nonnull) getMainBundle;

+(APBundle * _Nonnull) getInstance;

-(NSBundle * _Nonnull) getAnalyticLanguageBundle;

-(NSBundle * _Nonnull) getBugSquashLanguageBundle;

-(NSBundle * _Nonnull) getAnalyticBundle;

-(NSBundle * _Nonnull) getBugSquashBundle;

@end
NS_ASSUME_NONNULL_END
