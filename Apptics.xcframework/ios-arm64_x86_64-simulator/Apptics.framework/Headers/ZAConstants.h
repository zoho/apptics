//
//  ZAConstants.h
//  JAnalytics
//
//  Created by Giridhar on 08/11/16.
//  Copyright Â© 2016 zoho. All rights reserved.
//

#ifndef ZAConstants_h
#define ZAConstants_h
#import "ZABundle.h"
#define UIAPPLICATION_ACCESS (defined(IS_IOS) || defined(IS_TVOS))

#define UIKIT_ACCESS (defined(IS_IOS) || defined(IS_TVOS) || defined(IS_WATCHOS))
//(!TARGET_OS_OSX && (TARGET_OS_IOS || TARGET_OS_TV || TARGET_OS_WATCH))

#define APP_LIFECYCLE_SUPPORT (defined(IS_IOS) || defined(IS_TVOS) || defined(IS_MACOS))

#define NSLocalizedStringForZAnalytics(key,comment,tbl) \
[[[ZABundle getInstance] getAnalyticLanguageBundle] localizedStringForKey:(key) value:@"" table:(tbl)]

#define ZAnalyticsLocalizedString(x) NSLocalizedStringForZAnalytics(x, @"", @"ZAnalyticsLocalizable")

#define AppticsLocalizedString(key, value) (value != nil && ![value isEqualToString:@""]) ? value : NSLocalizedStringForZAnalytics(key, @"", @"ZAnalyticsLocalizable")

static NSString *kJA_UserProperties = @"ja_userproperties";
static NSString *kJA_FirstTimeInstallation = @"kJA_FirstTimeInstallation";
static NSString * kJA_UserEmail = @"ja_userpropertyEmail";

static NSString  *kJA_DCLPrefix = @"ja-dclPfx";

static NSString * kJA_is_pfx = @"ja-is_pfx";

static NSString * kJA_dclBD = @"ja-dclBD";
static NSString * kJA_OsVersion = @"osVersion";
static NSString * kJA_updateVersion = @"updateVersion";

static NSString * kJA_SuccessStringInJSON = @"success";

static NSString *k_version_forFile = @"v2";

static NSString * kJA_BaseURLDomain = @"apptics";

static NSString * kJU_UpdateId         = @"kJU_UpdateId";
static NSString * kJU_PreviousAppVersion         = @"kJU_PreviousAppVersion";
static NSString * kJU_PreviousAppReleaseVersion         = @"kJU_PreviousAppReleaseVersion";
static NSString * kJU_SkipThisAppVersion         = @"kJU_SkipThisAppVersion";

static NSString * kJA_RegisteredDeviceId = @"kJA_RegisteredDeviceId";
static NSString * kJA_RegisteredApDeviceInfo = @"kJA_RegisteredApDeviceInfo";
//static NSString * kJA_RegisteredUpdatedTime = @"kJA_RegisteredUpdatedTime";

static NSString * kJA_AnalyticUserId = @"kJA_AnalyticUserId";
static NSString * kJA_Default = @"default";
static NSString * kJA_DefaultDc = @"com";
static NSString * kJA_MamDc = @"kJA_MamDc";
static NSString * kJA_Mam = @"kJA_Mam";
static NSString * kJA_OrgID = @"kJA_OrgID";
static NSString * kJA_MamKey = @"kJA_MamKey";
static NSString * kJA_MamInfo = @"kJA_MamInfo";
static NSString * kJA_UserIds = @"kJA_UserIds";
static NSString * kJA_MamPIIInfo = @"kJA_MamPIIInfo";
static NSString * kJA_MamDCInfo = @"kJA_MamDCInfo";
static NSString * kJA_MamTrackingInfo = @"kJA_MamTrackingInfo";
static NSString * kJA_MamCrashInfo = @"kJA_MamCrashInfo";
static NSString * kJA_CrashReportPermissionStatus = @"kJA_CrashReportPermissionStatus";
static NSString * kJA_CrashReportStatus = @"kJA_CrashReportStatus";

static NSString * kJA_SecretKey = @"1234567890123456";
static NSString * kJA_DeviceInfo = @"kJA_DeviceInfo";
static NSString * kJA_DeviceUUID = @"kJA_DeviceUUID";
static NSString * kJA_DebugMode = @"kJA_DebugMode";
static NSString * kJA_TrackingStatus = @"kJA_TrackingStatus";
static NSString * kJA_KeychainItems = @"kJA_KeychainItems";

// URL Paths
//The string over here is the same as the API ENDPOINT

static NSString * k_url_addScreens = @"addscreenviews";

static const NSUInteger k_ja_batchSize = 50;
static const NSUInteger k_ja_batchUpperLimit = 10;

static NSString * kJA_EventTypeApplicationLifeCycle = @"j_applifecycle";
static NSString * kJA_EventTypeUserLifeCycle = @"j_userlifecycle";
static NSString * kJA_EventTypeOpenUrl = @"j_openurl";
static NSString * kJA_EventTypeRemoteNotification= @"j_remotenotification";


static NSString * kJA_tracking = @"tracking";
static NSString * kJA_personalized = @"personalized";
static NSString * kJA_sendcrash = @"sendcrash";
static NSString * kJA_tracking_on = @"tracking_on";
static NSString * kJA_tracking_off = @"tracking_off";
static NSString * kJA_personalized_on = @"personalized_on";
static NSString * kJA_personalized_off = @"personalized_off";
static NSString * kJA_sendcrash_on = @"sendcrash_on";
static NSString * kJA_sendcrash_off = @"sendcrash_off";


static NSString * JUDefaultSkippedVersion         = @"JUDefaultSkippedVersion";
static NSString * JUDefaultReminderCheckDate = @"JUDefaultReminderCheckDate";
static NSString * JUDefaultRemindedCount = @"JUDefaultRemindedCount";
static NSString * JUDefaultPreviousOpt = @"JUDefaultPreviousOpt";

//static NSString * JUActionTitleDownload = @"Update Now";
//static NSString * JUActionTitleLater = @"Remind Me Later";
//static NSString * JUActionTitleIgnore = @"Skip";
static NSString * JUActionTitleFeedback = @"Feedback";

static NSString * JUActionContinue = @"continue";
static NSString * JUActionImpression = @"impression";
static NSString * JUActionDownload = @"download";
static NSString * JUActionLater = @"later";
static NSString * JUActionIgnore = @"ignore";
static NSString * JUActionUpdated = @"updated";

static NSString * kJA_sessionHit = @"kJA_sessionHit";
static NSString * kJA_eventHit = @"kJA_eventHit";
static NSString * kJA_screenHit = @"kJA_screenHit";

static NSString * kJA_autoReviewAttempt = @"kJA_autoReviewAttempt";
static NSString * kJA_autoReviewImpressionLimit = @"kJA_autoReviewImpressionLimit";
static NSString * kJA_autoPromptedDate = @"kJA_autoPromptedDate";
static NSString * kJA_promoted_apps = @"promotedApps";

extern unsigned long long const ZALogMaxFileSize;
extern NSUInteger         const ZALogMaxNumLogFiles;

typedef void (*ZACrashPostCrashSignalCallback)(void *context);

typedef struct ZACrashCallback {
  void *context;
  ZACrashPostCrashSignalCallback handleSignal;
} ZACrashCallback;

static ZACrashCallback zaCrashCallback = {.context = NULL, .handleSignal = NULL};

#endif /* ZAConstants_h */

