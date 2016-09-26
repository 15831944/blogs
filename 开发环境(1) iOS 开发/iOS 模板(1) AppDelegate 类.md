AppDelegate and ViewController both define classes, but the classes are used for different things. 

# ViewController

ViewController.h/m define a view controller class that manages a hierarchy of views -- basically, one screen of an application. 

You might have multiple screens that each have their own view controller.

# AppDelegate

AppDelegate.h/m define a class that manages the application overall. 

The app will create one instance of that class and send that object messages that let the delegate influence the app's behavior at well-defined times. 

For example, -application:didFinishLaunchingWithOptions: is sent when the app has finished launching and is ready to do something interesting. 

Take a look at the UIApplicationDelegate reference page for a list of messages that the app delegate can implement to modify the behavior of the application.

If care is not taken, the AppDelegate could easily become one of the most accessed objects in the application.

I usually refrain from calling methods in the AppDelegate from any of my ViewControllers. 
 
Unless, something needs to be reported to the AppDelegate that would influence the behaviour of the whole application.

I keep my AppDelegate for the following:

1. initialization: whatever needs to be done on the very first launch (after an install or an update)

2. data migration from version to version (e.g. if you use CoreData and migrations)

3. configuration of objects linked via IBOutlets from MainWindow.xib

4. determining the initial orientation to launch in

5. saving uncommitted data / state prior to the application being terminated or entering background mode

6. registering for the Apple Push Notification Service and sending the device token to our server

7. opening one of the supported application URLs (e.g. maps://)

For other use case scenarios and a more thourough description of the AppDelegate, see the iOS Application Programming Guide.

+1 for pointing out the peril of the app delegate. Some people use it to do all kinds of things, mainly because it's a singleton and therefore easy to access globally. I don't think that's a good approach.

The view-controller. h/m is responsible of controlling the connection between your model and your view.

AppDelegate. h/m is responsible for the life-cycle of your application. What to do when the user press the home button and exit your app, what to do when the app enter background. Things like this.

Speaking about the life-cycle, declaring global variables that the app need to use in different viewcontrollers must be on the AppDelegate file.

协议中定义的这些需要实现的方法的作用：

`- (void)applicationWillResignActive:(UIApplication *)application`

说明：当应用程序将要退出活动状态时执行，在此期间，应用程序不接收消息或事件

举例：比如来电话了

`- (void)applicationDidBecomeActive:(UIApplication *)application`

说明：当应用程序入活动状态执行，这个刚好跟上面那个方法相反

`- (void)applicationDidEnterBackground:(UIApplication *)application`

说明：当程序被推送到后台的时候调用。

举例：设置后台继续运行，则在这个函数里面设置即可

`- (void)applicationWillEnterForeground:(UIApplication *)application`

说明：当程序从后台将要重新回到前台时候调用，这个刚好跟上面的那个方法相反。

`- (void)applicationWillTerminate:(UIApplication *)application`

说明：当程序将要退出是被调用，通常是用来保存数据和一些退出前的清理工作。这个需要要设置
UIApplicationExitsOnSuspend的键值。

`- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application`

说明：iPhone设备只有有限的内存，如果为应用程序分配了太多内存操作系统会终止应用程序的运行，在终止前会执行这个方法，通常可以在这里进行内存清理工作防止程序被终止

`- (void)applicationSignificantTimeChange:(UIApplication*)application`

说明：当系统时间发生改变时执行

`- (void)applicationDidFinishLaunching:(UIApplication*)application`

说明：当程序载入后执行

`- (void)application:(UIApplication)application willChangeStatusBarFrame:(CGRect)newStatusBarFrame`

说明：当StatusBar框将要变化时执行

`- (void)application:(UIApplication*)application willChangeStatusBarOrientation:

(UIInterfaceOrientation)newStatusBarOrientation

duration:(NSTimeInterval)duration`

说明：当StatusBar框方向将要变化时执行

`- (BOOL)application:(UIApplication*)application handleOpenURL:(NSURL*)url`

说明：当通过url执行

`- (void)application:(UIApplication*)application 
didChangeStatusBarOrientation:(UIInterfaceOrientation)oldStatusBarOrientation`

说明：当StatusBar框方向变化完成后执行

`- (void)application:(UIApplication*)application 
didChangeSetStatusBarFrame:(CGRect)oldStatusBarFrame`

说明：当StatusBar框变化完成后执行
