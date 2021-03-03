//
//  APTheme.h
//  JAnalytics
//
//  Created by Saravanan S on 19/07/18.
//

#import <Foundation/Foundation.h>
#if !TARGET_OS_OSX
#import <UIKit/UIKit.h>
#else
#import <Cocoa/Cocoa.h>
#endif
NS_ASSUME_NONNULL_BEGIN
typedef enum : NSInteger {
  Dark = 0,
  Light
} DropDownImage;

@protocol APTheme <NSObject>
#if !TARGET_OS_OSX
@optional
-(UIColor *)tintColor;
-(UIColor *)barTintColor;
-(BOOL) translucent;
-(NSDictionary *)titleTextAttributes;
-(NSDictionary *)barButtontitleTextAttributes;
- (void)za_traitCollectionDidChange:(UITraitCollection *)previousTraitCollection;
#endif
@end

@protocol APSettingsTheme <APTheme>
#if !TARGET_OS_OSX
@optional
-(UIColor *)viewBGColor;
-(UIColor *)cellBGColor;
-(UIColor *)cellTextColor;
-(UIColor *)footerTextColor;
-(UIColor *)switchOnTintColor;
-(UIColor *)switchOffTintColor;
-(UIColor *)switchThumbTintColor;
-(UIColor *)switchTintColor;
-(CGFloat) switchScale;
-(UIColor *)tableViewSeparatorColor;

-(UIFont *)cellTextFont;
-(UIFont *)footerTextFont;
#if !TARGET_OS_WATCH
-(UIButton *)backButton;
#endif
-(CGFloat) lineSpacing;
-(CGSize) preferredContentSize;

- (void)za_traitCollectionDidChange:(UITraitCollection *)previousTraitCollection;
#endif
-(NSString *)fontName;

@end

@protocol APFeedbackTheme <APTheme>
#if !TARGET_OS_OSX && !TARGET_OS_WATCH
@optional

-(UIColor *)viewBGColor;
-(UIColor *)contentBGColor;
-(UIColor *)switchOnTintColor;
-(UIColor *)switchOffTintColor;
-(UIColor *)switchThumbTintColor;
-(UIColor *)switchTintColor;
-(CGFloat) switchScale;

-(UIColor *)textFieldTextColor;
-(UIColor *)textFieldPlaceholderColor;
-(UIColor *)textViewTextColor;
-(UIColor *)textViewPlaceholderColor;

-(UIColor *)accessoryViewBGColor;
-(UIColor *)accessoryHeaderTextColor;
-(UIColor *)accessorySubHeaderTextColor;

-(UIColor *)collectionViewCellBorderColor;

-(UIColor *)separatorColor;

-(UIFont *)textFieldFont;
-(UIFont *)textViewFont;
-(UIFont *)keyboardAccessoryHeaderFont;
-(UIFont *)keyboardAccessorySubHeaderFont;

-(UIFont *)noImagePlaceholderFont;
-(CGSize)preferredContentSize;

-(UIColor *)attachmentTableHeaderTextColor;
-(UIColor *)attachmentTableCellFileNameTextColor;
-(UIColor *)attachmentTableCellSizeLabelTextColor;
-(UIColor *)attachmentTableCellXButtonColor;

-(UIFont *)attachmentTableHeaderTextFont;
-(UIFont *)attachmentTableCellFileNameTextFont;
-(UIFont *)attachmentTableCellSizeLabelTextFont;

-(UIKeyboardAppearance) keyboardAppearance;

-(UIColor *)pickerViewBGColor;
-(UIColor *)systemLogViewBGColor;
-(UIColor *)systemLogTextColor;
-(UIColor *)diagnosticInfoBGColor;
-(UIColor *)diagnosticInfoTextColor;

-(DropDownImage) dropDownImage;

- (void)za_traitCollectionDidChange:(UITraitCollection *)previousTraitCollection;

#endif
-(NSString *)fontName;
@end

@protocol APFeedbackPrivacyTheme <APTheme>
#if !TARGET_OS_OSX && !TARGET_OS_WATCH
@optional

-(UIColor *)viewBGColor;
-(UIColor *)switchOnTintColor;
-(UIColor *)switchOffTintColor;
-(UIColor *)switchThumbTintColor;
-(UIColor *)switchTintColor;
-(CGFloat) switchScale;

-(UIColor *)separatorColor;

-(NSDictionary *)titleTextAttributes;
-(NSDictionary *)descriptionTextAttributes;

-(NSDictionary *)consoleLogButtonTitleTextAttributes;
-(NSDictionary *)diagnosticInfoButtonTitleTextAttributes;

- (void)za_traitCollectionDidChange:(UITraitCollection *)previousTraitCollection;

#endif
-(NSString *)fontName;
@end

@protocol APCustomAlertTheme <NSObject>
#if !TARGET_OS_OSX
@optional
-(UIColor *)viewBGColor;
-(UIColor *)primaryColor;
-(UIColor *)secondaryColor;

-(NSDictionary *)titleTextAttributes;
-(NSDictionary *)descriptionTextAttributes;

-(CGFloat) buttonCornerRadius;

- (void)za_traitCollectionDidChange:(UITraitCollection *)previousTraitCollection;

#endif

@end

@protocol APUserConsentTheme <APCustomAlertTheme>
#if !TARGET_OS_OSX
@optional
-(NSDictionary *)buttonTitleTextAttributes;
-(NSDictionary *)privacyTextAttributes;
-(UIImage *)logoImage;
#endif
@end

@protocol APAppUpdateConsentTheme <APCustomAlertTheme>
#if !TARGET_OS_OSX
@optional
//APCustomAlertTheme's Primary color will be applied to 'Update now' button background and title text color of other two buttons
//APCustomAlertTheme's Secondary color will be applied as title text color of 'Update now' button and background color of other two buttons
//APCustomAlertTheme's titleTextAttributes will be used to customise the title font and color
//APCustomAlertTheme's descriptionTextAttributes will be used to customise the description font and color
//APCustomAlertTheme's buttonCornerRadius will be used to change the button radius using this method
-(UIImage *)logoImage;
-(NSDictionary *)updateButtonTitleTextAttributes;
-(NSDictionary *)remindButtonTitleTextAttributes;
-(NSDictionary *)skipButtonTitleTextAttributes;
-(NSDictionary *)versionTextAttributes;
-(NSDictionary *)readMoreTextAttributes;
-(UIColor *)windowBGColor;
#endif
@end

@interface APThemeManager : NSObject
+(id <APTheme>)sharedThemeManager;
+(id <APSettingsTheme>)sharedSettingsThemeManager;
+(id <APFeedbackTheme>)sharedFeedbackThemeManager;
+(id <APFeedbackPrivacyTheme>)sharedFeedbackPrivacyThemeManager;
+(id <APCustomAlertTheme>)sharedCustomAlertThemeManager;
+(id <APUserConsentTheme>)sharedUserConsentThemeManager;
+(id <APAppUpdateConsentTheme>)sharedAppUpdateConsentThemeManager;

+(void) setTheme:(id <APTheme>) theme;
+(void) setSettingsTheme:(id <APSettingsTheme>) settingsTheme;
+(void) setFeedbackTheme:(id <APFeedbackTheme>) feedbackTheme;
+(void) setFeedbackPrivacyTheme:(id <APFeedbackPrivacyTheme>) feedbackPrivacyTheme;
+(void) setCustomAlertTheme:(id <APCustomAlertTheme>) customAlertTheme;
+(void) setUserConsentTheme:(id <APUserConsentTheme>) userConsentTheme;
+(void) setAppUpdateConsentTheme:(id <APAppUpdateConsentTheme>) appUpdateConsentTheme;
@end

@interface APDefaultTheme : NSObject <APTheme>
@end

@interface APDefaultSettingsTheme : NSObject <APSettingsTheme>
@end

@interface APDefaultFeedbackTheme : NSObject <APFeedbackTheme>
@end

@interface APDefaultFeedbackPrivacyTheme : NSObject <APFeedbackPrivacyTheme>
@end

@interface APDefaultCustomAlertTheme : NSObject <APCustomAlertTheme>
@end

@interface APDefaultUserConsentTheme : NSObject <APUserConsentTheme>
@end

@interface APDefaultAppUpdateConsentTheme : NSObject <APAppUpdateConsentTheme>
@end
NS_ASSUME_NONNULL_END
