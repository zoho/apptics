# Apptics 
Apptics is a library that enables your app to send usage reports and data securly to our servers. You get Session tracking, Screen tracking and Crash Reporting. Which means, with minimal setup of initializing the framework you can get these three features working without any other configuration.

## Development Requirements: 

The minimum support is for iOS 9.0, macOS 10.9, tvOS 9.0 and watchOS 3.0. 
Supported Swift version - 4.0.
Supported devices - iPhone, iPod, iPad, Mac, Apple watch and Apple tv.
min Pod version - 1.5.3 
min Xcode version 9.0
 
## Getting Started

* Visit this [link](https://apptics.zoho.com/ui/setup) to create a new project. This is the only thing you will need to get things started. 

* You can use cocoapods to install Apptics in your project. 

* Your Podfile will look something like this
    
          target '[TARGET NAME]' do
            pod 'Apptics'
          end

          post_install do |installer|
            puts system("sh ./Pods/Apptics/native/scripts/postinstall --prefix=\"AP\" --target-name=\"Main_Target_Name\"")    
          end
          
     Parameters:
     * `--project-name`       String - Provide the name of the project
     * `--target-name`         String - Provide the name of the target
     * `--project-file`            String - Provide the path of the xcproject file
     * `--prefix`                    String - **AppticsExtension.* will be prefixed by this value
     * `--use-swift`              Void - Generate class for swift
     * `--help`                      Show help banner of specified command
     
     The script `postinstall` will add **AppticsExtension file(s) to your project, the class will have the events meta data.  
     
* Run `pod install` and make sure you are connected to the Zoho-corp lan or wifi to access the Git repo. 

* Create new or select an existing application from quickstart page of your project to download  the `apptics-config.plist`, Once the download is complete, move the `apptics-config.plist` file to the root of your Xcode project and add it to the necessary targets.


* In your `Appdelegate` class make sure you call initialize method in app launch.

        Apptics.initialize(withVerbose: true)

* For AppExtensions call `Apptics.startExtensionSession("APP_GROUP_IDENTIFIER")` on start and `Apptics.stopExtensionSession()` at the end. 

***Note : The analytic data of App-Extensions will be sent by the main application based on the network availability.***  


## **Important**:
Make sure your build settings has the following when you ship your app so that you get proper symbolicated crashes.
 
* Strip Build Symbols During Copy - **NO**
* Strip Linked Product - **NO**
* Strip Style - **Debugging Symbols**
* Debug information format - **Dwarf with dSYM file**

Create run script 
* Add these lines to your Podfile 

        target '[TARGET NAME]' do
            
            pod 'Apptics' 
            
            script_phase :name => 'Apptics pre build', :script => 'sh "$PODS_ROOT/Apptics/native/scripts/regappversion" --debug-mode=[INT DEBUG MODE] --target-name="[STRING TARGET NAME]"', :execution_position => :before_compile   
            
            script_phase :name => 'Apptics post build', :script => 'bash "$PODS_ROOT/Apptics/native/scripts/run" --upload-symbols=[BOOL] --release-configurations="[STRING CONFIGURATION NAMES]"', :execution_position => :after_compile
            
        end        

* `--debug-mode` 0 for development / 1 for production / 2 for testing 
* `--upload-symbols` based on this parameter we decide to upload dsym to the server. 
* `--release-configurations` is a optional param, pass your configuration name Debug, Release or your custom name with comma separated for which the dSYMs will be uploaded without any prompt during App store submission process via CI, CT and CD.


# Features

## Session Tracking:

Session tracking is out of the box, one foreground to background is considered a session. 

## Event Tracking: 

Tracking events is easy, you can group them, send custom properties and you can even time them. Check out the api to see what you can do. 

## Screen Tracking: 

Screens are automatically tracked and the time spent on each screen is noted in iOS and tvOS. You can track screens manually using our [apis](https://prezoho.zohocorp.com/apptics/resources/iOS/screens.html)    
***Note: Viewcontrollers aren't tracked properly if you use third party containment controllers like DDMenuController, IIViewdeckController etc. To ensure to get a proper tracking of viewcontroller override `viewDidAppear` and `viewWillDisappear` in all your viewcontrollers.***

## Crash Reporting: 

Crashes are automatically tracked and symbolicated in the server side. To get proper symbolicated reports please make sure to configure your build settings properly. 

The crashes will not be captured if the debugger is attached at the launch, so we suggest you to follow the below steps. 

  * Run your app from Xcode and install it on your simulator or device.
  * Quit the app using the stop button.
  * Launch the app from home screen and try to crash the app by invoking our readymade method `Apptics.crash()`.
  * Run the app again in order to push the crash to the server and get symbolicated.

Check the web console, you should find the crash.

#### Missing dSYM? 

Apptics includes a script to upload your project's dSYM automatically. The script is executed through the run-script in your projects build phases during the on-boarding process. There are some cases where dSYM upload fails because of network interruptions or if you have enabled bit code in your project. Missing dSYMs can be uploaded by following the below steps. 

#### Finding your dSYM 

While archiving your project build dSYMs are placed inside the xarchive directory. To view, open Xcode organizer window, ctrl+click or right click on the list to go to the dir in Finder. ctrl+click to view its content, inside the content you will find a dir called "dSYMs" which will contain dSYMs files, also that is the location where dSYMs are placed when you hit "download dSYM" in Xcode organizer. 

For Bitcode enabled applications the first step would be to check in iTunes connect whether you have enabled bit-code for your application. For bit-code enabled builds Apple generates new dSYMs. You will have to download the dsyms from ituneconnect or from the Xcode's organizer and upload to Apptics server. 

#### To download the dSYM files from iTunes Connect: 
* Log in to Apple [iTunes Connect](https://itunesconnect.apple.com/login).
* Select My Apps > (selected app) > Activity.
* From the list of builds for your application, select the build number you need for the dSYM.
* Select Download dSYM.

#### Uploading dSYMs 

On "Manage dSYM page" (Left menu -> Quality -> dSYM), upload the dSYMs .zip that you have downloaded from the iTunes connect for bitcode enabled or the one you find in xarchive directory.

## Theme 

You can use our protocols to customize the Analytics Settings, App updates and Feedback screens. Just create a swift/Obj class in the name of ThemeManager and extend those protocols to implement required methods [link]().

## Callbacks 

Get callbacks for all the events at a single point by extending `ZACustomHandler`. It deals with user consent , crash consent, feedback, and ratings & reviews.

## Feedback and BugReporting
We have a seperate module that does "Shake to Feedback" , please check it out if it suits your needs [here](https://prezoho.zohocorp.com/apptics/resources/iOS/inapp-feedback.html).
        
## App Updates 
Now you can prompt user to update the latest version of your app from the App Store.  

Please check this guide before you start [here](https://prezoho.zohocorp.com/apptics/resources/iOS/inapp-updates.html).

## Ratings and Reviews
Engage With The Users To Learn About Their Experience using our tool. 

Check how to configure automatic ratings [here](https://prezoho.zohocorp.com/apptics/resources/iOS/inapp-ratings.html).

    
