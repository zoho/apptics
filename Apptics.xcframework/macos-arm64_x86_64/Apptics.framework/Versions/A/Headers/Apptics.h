//
//  Apptics.h
//  JAnalytics
//
//  Created by Giridhar on 22/02/17.
//  Copyright © 2017 zoho. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ZAEnums.h"
#import "APTheme.h"
#import "ZALog.h"
#import "Analytics.h"
#import "APCustomHandler.h"

#if ZA_REMOTE_CONFIG
#import "ZARemoteConfig.h"
#import "ZARemoteConfigValue.h"
#endif

#if ZA_API_TRACKER
#import "ZAAPIManager.h"
#endif

//#import "AppticsConfig.h"
//#import "FeedbackKit.h"
//#import "ZAAPIManager.h"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define trackError(args) ZATrackError(__FILENAME__,__LINE__,__func__,"error",args);

#define trackException(args) ZATrackException(__FILENAME__,__LINE__,__func__,"exception",args);

FOUNDATION_EXPORT double AppticsVersionNumber;

FOUNDATION_EXPORT const unsigned char AppticsVersionString[];
NS_ASSUME_NONNULL_BEGIN

/**
 *  Apptics is a library that enables your app to send usage reports and data securly to our servers. You get Session tracking, Screen tracking and Crash Reporting. Which means, with minimal setup of initializing the framework you can get these three features working without any other configuration.
 
    # Important:
    Make sure your build settings has the following when you ship your app so that you get proper symbolicated crashes.

    * Strip Build Symbols During Copy - **NO**
    * Strip Linked Product - **NO**
    * Strip Style - **Debugging Symbols**
 */
@interface Apptics : NSObject

#pragma mark — initialization

  /**
   *  This method call will perform initialisation of Apptics framework.
   *
   */
  
+ (void)initializeWithVerbose : (BOOL) verbose
#if TARGET_OS_IOS || TARGET_OS_OSX || TARGET_OS_TVOS
NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions")
#endif
;

#pragma mark — Config apis

/**
 
 For any configuration changes to get reflect in the App.

 */

+ (void) synchronizeConfig;

/**
 Enable automatic event tracking to track application lifecycle events.
 
 @param status boolean
 */

+ (void) setAutomaticEventTracking:(BOOL) status __deprecated_msg("Depricating this method");;

/**
 Sets custom information that gets attached with the crash report
 
 @param object any object that is conforms to JSON Encoding
 */

+ (void) setCrashCustomProperty:(nonnull NSDictionary*) object;

/**
 Set a custom User agent for the network calls
 
 @param userAgent useragent string
 */

+ (void) setUserAgent:(NSString*_Nonnull) userAgent;

/**
 Enable background task to send the analytics data to the server when your apps is in background.
 
 @param status  BOOL
 */

+ (void) setEnableBackgroundTask:(BOOL) status;


#pragma mark — Flush

/**
 *  Clears all stored data, without sending info to the server.
 */

+ (void) reset;

/**
 *  Flushes all events that's tracked so far to the server, right away. You might typically want to use this when the user is gonna log out, or pretty much, whenever you need it.
 */

+ (void) flushEvents;

/**
 *  Flushes all events,sessions and pretty much everything that's tracked so far to the server, right away. You might typically want to use this when the user is gonna log out, or pretty much, whenever you need it.
 */

+ (void) flush;

#pragma mark — Events apis

/**
 * An event is recorded when you call this method. Make sure you give meaningful names for your events. So that everyone, not just developers understand the event names.
 *  Call this when the event is completed. Put it in a success block if you have to, or put this line just below the line that calls the event, if blocks and closures aren't your thing.
 *
 *  @param eventName Name of the Occuring Event
 */

+ (void) trackEvent:(nonnull NSString *)eventName;


/**
 *  This methods allows you to set custom properties.
 *  Custom Properties are Dictionary/Hashmap/NSDictionary/Key value pair. Make sure the custom properties you send have meaningful keys for the values you send (duh!).
 *
 *  @param eventName  Name of the event
 *  @param properties A Key-Value pair NSDictionary for tracking custom properties
 */

+ (void) trackEvent:(nonnull NSString *)eventName withProperties:(nonnull NSDictionary *)properties;

/**
 Use this method to track events. Make sure you give meaningful names for events and their groups
 
 @param eventName Name of the Occuring Event
 @param group Name of the Group
 */

+ (void) trackEvent:(nonnull NSString *)eventName withGroupName:(nonnull NSString*)group;


/**
 *   Group your events if you have to, its a good practise. We recommend you to use const strings for groupName so that you don't, by mistake, send a wrong groupname.
 *
 *  @param eventName  Name of the event
 *  @param groupName  Name of the group
 *  @param properties Key-Value pair NSDictionary for tracking custom properties for the given event.Remember, the properties should be NSJSONSerializable, so use only data types that conforms the standard JSON protocol, like NSStrings, Integer, long etc.
 */

+ (void) trackEvent:(nonnull NSString *)eventName andGroupName : (nonnull NSString*) groupName withProperties:(nonnull NSDictionary *)properties;

/**
 *
 *  Starts a timed event with a specified name
 
 The duration of the event will be calculated added as a property when a
 corresponding endTimed event is called.
 
 This kind of method is used to track events that have duration.
 
 Usage : In a file upload task, call startTimedEvent method before upload and invoking the endTimedEvent at the end of the task, make sure you give the same event and group name for both methods.
 
 *
 *  @param eventName Name of the event
 */

+ (void) startTimedEvent:(nonnull NSString*)eventName;

/**
 *  Starts a timed event with an Event name and a group name. Use groupnames to group events.
 
 *  @param eventName Name of the event
 *  @param group Name of the group for the given event
 */

+ (void) startTimedEvent:(nonnull NSString*)eventName group:(nonnull NSString*)group;


/**
 *  Starts a timed event with an Event name, group name, and custom properties.
 *  Remember, the properties should be NSJSONSerializable, so use only data types that conforms the standard JSON protocol, like NSStrings, Integer, long etc.
 *
 *  @param eventName Name of the Event
 *  @param group Name of the Group
 *  @param properties Key-Value pair NSDictionary for tracking custom properties for the given event.Remember, the properties should be NSJSONSerializable, so use only data types that conforms the standard JSON protocol, like NSStrings, Integer, long etc
 */

+ (void) startTimedEvent:(nonnull NSString*)eventName group:(nonnull NSString*)group andProperties:(nonnull NSDictionary*)properties;

/**
 *  Ends the Timed event. Make sure you give the same name of the event.
 *
 *  - Warning:
 *  Calling this method will end all the timed events with the same event name.
 *
 *  @param eventName Name of the Timed Event.
 */

+ (void) endTimedEvent:(NSString *_Nonnull)eventName;

/**
 *  Ends the Timed event. Make sure you give the same event and group name.
 *
 *  - Warning:
 *  Calling this method will end all the timed events with the same event and group name.
 *
 *  @param eventName Name of the Timed Event.
 *  @param group Name of the Group
 */

+ (void) endTimedEvent:(NSString *_Nonnull)eventName withGroup:(NSString*_Nonnull)group;

#pragma mark — Non-fatals apis

/**
 Tracks an NSError

 @param error Error.
 */

void ZATrackError(const char *file, int lineNumber, const char *functionName,const char *type, NSError *error,...);

/**
 Tracks Non-fatal and handled exceptions
 
 @param exception A handled exception
 */

void ZATrackException(const char *file, int lineNumber, const char *functionName,const char *type, NSException *exception,...);

#pragma mark — User apis

/**
 Log a Signup event to see how many users have logged in your app in real-time.
 @param userID String
 */

+ (void) trackSignUp:(NSString* _Nullable)userID NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Log a Signup event, along with send BD Base domain.
 
 @param userID String, BD String.
 */

+ (void) trackSignUp:(NSString* _Nullable)userID withBaseDomain:(NSString*_Nonnull)BD NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Use this method to avoid user consent, Log a signup event to see how many users have signed in your app in real-time.
 @param userID String and shouldShowConsent bool
 */

+ (void) trackSignUp:(NSString* _Nullable)userID showConsent : (BOOL) shouldShowConsent NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Log a Signup event without asking for user consent, along with send BD Base domain.
 
 @param userID String, JAUserStatus enum, BD String.
 */

+ (void) trackSignUp:(NSString* _Nullable)userID showConsent : (BOOL) shouldShowConsent baseDomain:(NSString*_Nonnull)BD NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
  Log a Login event to see how many users have logged in your app in real-time.
 @param userID String
 */

+ (void) trackLogIn:(NSString* _Nullable)userID NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Log a Login event, along with send BD Base domain.
 
 @param userID String, BD String.
 */

+ (void) trackLogIn:(NSString* _Nullable)userID withBaseDomain:(NSString*_Nonnull)BD NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Use this method to avoid user consent, Log a Login event to see how many users have logged in your app in real-time.
 @param userID String and JAUserStatus enum
 */

+ (void) trackLogIn:(NSString* _Nullable)userID showConsent : (BOOL) shouldShowConsent NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Log a Login event without asking for user consent, along with send BD Base domain.
 
 @param userID String, JAUserStatus enum, BD String.
 */

+ (void) trackLogIn:(NSString* _Nullable)userID showConsent : (BOOL) shouldShowConsent baseDomain:(NSString*_Nonnull)BD NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Log a Logout event.
 
 @param userID String.
 */

+ (void) trackLogOut:(NSString* _Nullable)userID NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Log a Logout event, along with send BD Base domain.
 
 @param userID String, dclpfx String, dclBD String and is_pfx bool.
 */

+ (void) trackLogOut:(NSString* _Nullable)userID withBaseDomain:(NSString*_Nonnull)BD NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");


/**
 Log a Signup event to see how many users have logged in your app in real-time.
 @param userID String, groupID String
 */

+ (void) trackSignUp:(NSString* _Nullable)userID groupId : (NSString*_Nullable)groupID NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Log a Signup event, along with send BD Base domain.
 
 @param userID String, groupID String, BD String.
 */

+ (void) trackSignUp:(NSString* _Nullable)userID groupId : (NSString*_Nullable)groupID withBaseDomain:(NSString*_Nonnull)BD NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Use this method to avoid user consent, Log a signup event to see how many users have signed in your app in real-time.
 @param userID String, groupID String and JAUserStatus enum
 */

+ (void) trackSignUp:(NSString* _Nullable)userID groupId : (NSString*_Nullable)groupID showConsent : (BOOL) shouldShowConsent NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Log a Signup event without asking for user consent, along with send BD Base domain.
 
 @param userID String, groupID String. JAUserStatus enum, BD String.
 */

+ (void) trackSignUp:(NSString* _Nullable)userID groupId : (NSString*_Nullable)groupID showConsent : (BOOL) shouldShowConsent baseDomain:(NSString*_Nonnull)BD NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
  Log a Login event to see how many users have logged in your app in real-time.
 @param userID String, groupID String
 */

+ (void) trackLogIn:(NSString* _Nullable)userID groupId : (NSString*_Nullable)groupID NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Log a Login event, along with send BD Base domain.
 
 @param userID String, groupID String, BD String.
 */

+ (void) trackLogIn:(NSString* _Nullable)userID groupId : (NSString*_Nullable)groupID withBaseDomain:(NSString*_Nonnull)BD NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Use this method to avoid user consent, Log a Login event to see how many users have logged in your app in real-time.
 @param userID String, groupID String and JAUserStatus enum
 */

+ (void) trackLogIn:(NSString* _Nullable)userID groupId : (NSString*_Nullable)groupID showConsent : (BOOL) shouldShowConsent NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Log a Login event without asking for user consent, along with send BD Base domain.
 
 @param userID String, groupID String, JAUserStatus enum, BD String.
 */

+ (void) trackLogIn:(NSString* _Nullable)userID groupId : (NSString*_Nullable)groupID showConsent : (BOOL) shouldShowConsent baseDomain:(NSString*_Nonnull)BD NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Log a Logout event.
 
 @param userID String, groupID String
 */

+ (void) trackLogOut:(NSString* _Nullable)userID groupId : (NSString*_Nullable)groupID NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Log a Logout event, along with send BD Base domain.
 
 @param userID String, groupID String, dclpfx String, dclBD String and is_pfx bool.
 */

+ (void) trackLogOut:(NSString* _Nullable)userID groupId : (NSString*_Nullable)groupID withBaseDomain:(NSString*_Nonnull)BD NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
  Specify a user identifier which will be used to identify user in future.
  We recommand you to use unique userID.
 
 @param userID String
 */

+ (void) setCurrentUser:(NSString * _Nullable)userID NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Use this method to avoid user consent,  Specify a user identifier which will be used to identify user in future. use option (JAUserStatus) to set user preference (include userID/track Anonymously/don’t track).
 We recommand you to use unique userID.
 
 @param userID String and JAUserStatus enum
 */

+ (void) setCurrentUser:(NSString * _Nullable)userID showConsent : (BOOL) shouldShowConsent NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Use this method to set current user for product which has more than one Data Center, along with send BD Base domain.
 
 @param userID String, BD String.
 */

+ (void) setCurrentUser:(NSString * _Nullable)userID withBaseDomain:(NSString*_Nonnull)BD NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
  This method will not ask for user consent while setting current user for product which has more than one data center, along with send BD Base domain.
 
 @param userID String, JAUserStatus enum, BD String.
 */

+ (void) setCurrentUser:(NSString * _Nullable)userID showConsent : (BOOL) shouldShowConsent baseDomain:(NSString*_Nonnull)BD NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
  Specify a user identifier which will be used to identify user in future.
  We recommand you to use unique userID.
 
 @param userID String
 @param groupID String
 */

+ (void) setCurrentUser:(NSString * _Nullable)userID groupId : (NSString*_Nullable)groupID NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Use this method to avoid user consent,  Specify a user identifier which will be used to identify user in future. use option (JAUserStatus) to set user preference (include userID/track Anonymously/don’t track).
 We recommand you to use unique userID.
 
 @param userID String, groupID String and JAUserStatus enum
 */

+ (void) setCurrentUser:(NSString * _Nullable)userID groupId : (NSString*_Nullable)groupID showConsent : (BOOL) shouldShowConsent NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
 Use this method to set current user for product which has more than one Data Center, along with send BD Base domain.
 
 @param userID String, groupID String and BD String.
 */

+ (void) setCurrentUser:(NSString * _Nullable)userID groupId : (NSString*_Nullable)groupID withBaseDomain:(NSString*_Nonnull)BD NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

/**
  This method will not ask for user consent while setting current user for product which has more than one data center, along with send BD Base domain.
 
 @param userID String, groupID String, JAUserStatus enum, BD String.
 */

+ (void) setCurrentUser:(NSString * _Nullable)userID groupId : (NSString*_Nullable)groupID showConsent : (BOOL) shouldShowConsent baseDomain:(NSString*_Nonnull)BD NS_EXTENSION_UNAVAILABLE("don't use this method in your extensions");

#pragma mark — View tracking apis

#if (TARGET_OS_OSX || TARGET_OS_WATCH)
/**
 Track screen entry manually.
 
 @param screenName String.
 */

+(void) trackViewEnter:(NSString*_Nullable) screenName;

/**
 Track screen exit manually.
 
 @param screenName String.
 */

+(void) trackViewExit:(NSString*_Nullable) screenName;

#endif

#pragma mark — Settings apis

#if !TARGET_OS_OSX && !TARGET_OS_WATCH

/**
 Pushes the screen which allows the user to change their analytic privacy settings.
 */

+ (void) openAnalyticSettingsController;

/**
 Pushes the screen which allows the user to change their analytic privacy settings with navigation controller.
 */

+ (void) openAnalyticSettingsControllerWithNavigationController : (UINavigationController * _Nullable) _navigationController ;

/**
 @return the analytic settings view controller.
 */

+(id _Nonnull) getAnalyticSettingsController;

#endif

#if TARGET_OS_OSX

/**
 Present the screen which allows the user to change their analytic privacy settings.
 */

+ (void) openPIIManagerController_macOS;

#endif

/**
 Get the status of data tracking for current user.
 
 @return YES if enabled else NO.
 */

+ (BOOL) trackingStatus;

/**
 Enable or disable data tracking for current user.
 
 @param status boolean
 */

+ (void) enableTracking : (BOOL) status;

/**
 Get the status of auto sending crash report.
 
 @return YES if enabled else NO.
 */

+ (BOOL) crashReportStatus;

/**
 Set crash report status true to send crash report automatically to the server even when the tracking is disabled.
 
 @param status boolean
 */

+ (void) setCrashReportStatus : (BOOL) status;

/**
 Get the status of sending personalized data which includes userID with the usage data for current user.
 
 @return YES if enabled else NO.
 */

+ (BOOL) pIITrackingStatus;

/**
 Set personalized data with usage tracking which includes userID for current user.
 
 @param status boolean
 */

+ (void) trackWithPII : (BOOL) status;

/**
 Get if the user is logged in, use this value to show or hide 'include userID' in analytic settings.
 
 @return YES if logged in else NO.
 */

+ (BOOL) isUserLoggedIn;

/**
 Get PII status for a given user.
 
 @param email String
 
 @return JAPIIStatus enum.
 */
+ (JAPIIStatus) getPIIStatusForEmail : (NSString* _Nonnull) email __deprecated_msg("use getPrivacyStatusOfUser: method instead.");


/**
 Get privacy status for a given user.
 
 @param userID String
 
 @return JAPIIStatus enum.
 */
+ (JAPIIStatus) getPrivacyStatusOfUser : (NSString* _Nonnull) userID;

/**
 Get PII status for a given user.
 
 @param email String, BD String.
 
 @return JAPIIStatus enum.
 */

+ (JAPIIStatus) getPIIStatusForEmail : (NSString* _Nonnull) email withBaseDomain:(NSString*_Nonnull)BD __deprecated_msg("use getPrivacyStatusOfUser: withBaseDomain: method instead.");

/**
 Get privacy status for a given user.
 
 @param userID String, BD String.
 
 @return JAPIIStatus enum.
 */

+ (JAPIIStatus) getPrivacyStatusOfUser : (NSString* _Nonnull) userID withBaseDomain:(NSString*_Nonnull)BD;

#pragma mark — Callbacks

/**
 Get callback when user consent prompt is been presented.
 
 @param userConsentPresentCompletionBlock userConsentPresentCompletionBlock.
 */

+(void) setUserConsentPresentCompletionHandler : (UserConsentPresentCompletionBlock _Nullable ) userConsentPresentCompletionBlock;

/**
 Get callback for user consent prompt dismiss action.
 
 @param userConsentDismissCompletionBlock userConsentDismissCompletionBlock.
 */

+(void) setUserConsentDismissCompletionHandler : (UserConsentDismissCompletionBlock _Nullable ) userConsentDismissCompletionBlock;

/**
 Get callback for crash consent prompt dismiss action.
 
 @param crashConsentDismissCompletionBlock crashConsentDismissCompletionBlock.
 */

+(void) setCrashConsentDismissCompletionHandler : (CrashConsentDismissCompletionBlock _Nullable ) crashConsentDismissCompletionBlock;

/**
 Use this method to get the duration since the last time app crashed.
 
 */

+(NSTimeInterval) activeDurationSinceLastCrash;

/**
 Use this method to get the no of sessions since the last time app crashed.
 
 */

+(int) sessionsSinceLastCrash;

/**
 Use this method to get the no of times the app launched since the last time app crashed.
 
 */

+(int) launchesSinceLastCrash;


#pragma mark — Localization apis
/**
 Use this method to get localizable string for given key. Get the keys from AppticsLocalizable.strings file.
 
 @param key String.
 */

+ (NSString*_Nullable) getLocalizableStringForKey : (NSString*_Nonnull) key;

/**
 Use this method to set the language that Analytics SDK should use. If the language is not found in the resource bundle, then default language will be selected.
 
 @param lang (code) String.
 */

+ (void) setDefaultLanguage : (NSString*_Nonnull) lang;


/**
 Use this method to set the current location of the user.
 
 @param location (code or name) String.
 */

+ (void) setCurrentLocation : (NSString*_Nonnull) location;

#pragma mark — App extension apis
/**
 Use this method to start tracking extension session.
 
 @param appGroup String.
 */

+(void) startExtensionSession : (NSString* _Nonnull) appGroup;

/**
 Use this method to stop extension session.
 
 */

+(void) stopExtensionSession;

#pragma mark — Themes api
#if !TARGET_OS_WATCH
/**
 Set theme color (nav bar, view bg color and title text color)
 */

+(void) setTheme : (id <APTheme> _Nonnull) theme;

/**
 Customize Analytics settings screen using this method.
 */

+(void) setSettingsTheme : (id <APSettingsTheme> _Nonnull) settingsTheme;

/**
 Customize Feedback settings screen using this method.
 */
+(void) setFeedbackTheme : (id <APFeedbackTheme> _Nonnull) feedbackTheme;

/**
 Customize Feedback privacy settings screen using this method.
 */
+(void) setFeedbackPrivacyTheme : (id <APFeedbackPrivacyTheme> _Nonnull) feedbackPrivacyTheme;

/**
 Customize our user consent screen using this method.
 */

+(void) setUserConsentTheme : (id <APUserConsentTheme> _Nonnull) userConsentTheme;

/**
 Customize our app update alert screen using this method.
 */

+(void) setAppUpdateConsentTheme : (id <APAppUpdateConsentTheme> _Nonnull) appUpdateConsentTheme;

/**
 Get all types of completion handler in single place by extending our protocol.
 */

+(void) setCustomHandler:(id <APCustomHandler> _Nonnull) handler;

/**
 Choose our privacy consent screen which suits your app better.
 */

+ (void) setPrivacyConsentType:(ZAPrivacyConsentType)privacyConsentType;

#endif 
#pragma mark — App Update apis

/**

Enable auto check for update by calling this method after initialising Apptics.
@param status BOOL
*/

+ (void) enableAutoCheckForAppUpdate : (BOOL) status;

/**
 
 Check update available on AppStore within your application.
 
 - Note :
 You should configure the update details in the [ZAnalytic web](https://apptics.zoho.com) and conform openURL protocol by extending APCustomHandler and set back to us.

 */

+ (void)checkForAppUpdate:(void(^_Nullable)(NSDictionary *_Nullable updateInfo))completionHandler;

/**
 Set back the actions for custom app update.
 @param type ZAUpdateAction
 */

+ (void) setAppUpdateAction : (ZAUpdateAction) type updateInfo : (NSDictionary *_Nullable) updateInfo;

#pragma mark — In-App Ratings and Reviews apis
#if !TARGET_OS_WATCH
/**
 Enable or disable rate us and review for your application.
 
 @param status boolean
 */

+ (void) enableRateUsAndReview : (BOOL) status;

/**
 Call this method to reset all numbers during development.
 
 - Warning:
 Don't call this method in App Store build.
*/

+ (void) storeReviewMasterReset;

/**
 This method should be called initially, to stop SDK from showing the review prompt on fulfilling criteria.
 
 @param status boolean
 */

+(void) disableAutoPromptOnFulfillingCriteria : (bool) status;

/**
 This method should be called manually where you want to show the review prompt.
 */

+(void) showPromptOnFulfillingCriteria;


#pragma mark Apis to customise In-App Ratings and Reviews

/**
 Call this method in the callback method 'willDisplayReviewPrompt' of APCustomHandler class.
 */

+ (void) showCustomReviewPrompt;

/**
This method will take you to the App store.
 
- Note:
 Call this method in the completion of custom review prompt when user taps on 'Rate in App Store' button.
*/

+ (void) takeToAppStoreReviewScreen;

/**
This method will open Feedback screen.
 
- Note:
 Call this method in the completion of custom review prompt when user taps on 'Send Feedback' button.
*/

+ (void) takeToFeedbackScreen;

/**
Set this true to mask the text detected in a screenshot by default. Setting to False will not mask by default but the user can still mask by tapping on individual text or By tapping on mask-all/unmask-all button.
*/

+ (void) setMaskTextByDefault:(BOOL)AlwaysOn;

/**
Call this method to update user action for App Store Review Screen when you open the Store Review on your own.
*/

+ (void) updateActionForAppStoreReview;

/**
Call this method to update user action for feedback when you open your custom feedback screen.
*/

+ (void) updateActionForFeedback;

/**
 This method will mark review prompt shown for the current version of the app. Note: Call this method if you have used custom review prompt.
 
 - Note:
 This should be called only if you show your custom prompt in 'willDisplayReviewPrompt' callback. Also the hitcount of sessions, events and screens will be reset.
 */

+(void) updateAppRatingShownForCurrentVersion;

/**
This method will prompt ratings alert which will take you to the store.
 */

+ (void) za_rateUsOnStore __deprecated_msg("use staticStoreReviewPrompt method instead.");

/**
This method will prompt ratings alert which will show the option to rate in appstore or send feedback, call this method in you apps' settings page.
 */

+ (void) staticStoreReviewPrompt;

#endif

#pragma mark — Crash

/**
 Use this method to crash the app for testing crash module.
 */

+ (void) crash;


#pragma mark - Remote config

/**
 Enable remote configure.
 */

+ (void) enableRemoteConfig:(BOOL)status;

#pragma mark - Cross Promotional Apps

//#if APPTICS_SWIFT
+(void) enableCrossPromotionalAppsList : (bool) status;

/**
 Enable Promotional apps with this method.
*/

+(id)getPromotionalAppsViewController : (NSString* _Nullable)sectionHeader1 : (NSString* _Nullable)sectionHeader2;
/**
    Will return a UIViewController with data. You can present this ViewController.
 
 
 Table of apps by default have two sections. One is "Apps that you may like" and other is "More apps from us"
 
 sectionHeader1 : Title of the Apps being shown in the screen for first section. Replacement of "Apps that you may like"
 sectionHeader2 : Title of the Apps being shown in the screen for second section. Replacement of "More apps from us"
*/

+(void)presentPromotionalAppsControllerWith: (NSString* _Nullable)sectionHeader1 : (NSString* _Nullable)sectionHeader2;
/**
    Will present the Promoted apps ViewController directly.
 
 
 Table of apps by default have two sections. One is "Apps that you may like" and other is "More apps from us"
 
 sectionHeader1 : Title of the Apps being shown in the screen for first section. Replacement of "Apps that you may like"
 sectionHeader2 : Title of the Apps being shown in the screen for second section. Replacement of "More apps from us"
*/
//#endif
@end
NS_ASSUME_NONNULL_END
