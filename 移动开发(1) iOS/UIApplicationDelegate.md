# AppDelegate

# 方法

```
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions	// 当程序载入后执行, 告诉应用启动的原因
- (void)applicationWillResignActive:(UIApplication *)application	// 当应用程序将要退出活动状态时执行，在此期间，应用程序不接收消息或事件, 比如来电话了
- (void)applicationDidEnterBackground:(UIApplication *)application	// 当程序将要被推送到后台时执行, 在此函数中设置后台继续运行
- (void)applicationWillEnterForeground:(UIApplication *)application	// 当程序从后台将要重新回到前台时执行
- (void)applicationDidBecomeActive:(UIApplication *)application		// 当应用程序已经进入活动状态时执行
- (void)applicationWillTerminate:(UIApplication *)application	// 当程序将要退出是被调用，通常是用来保存数据和一些退出前的清理工作。这个需要要设置 UIApplicationExitsOnSuspend 的键值

- (void)applicationDidFinishLaunching:(UIApplication*)application		// 不建议使用
- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application	// 操作系统会终止占内存太多的程序, 在终止前会执行这个方法, 通常可以在这里进行内存清理工作, 防止程序被终止
- (void)applicationSignificantTimeChange:(UIApplication*)application	// 当系统时间发生改变时执行
- (BOOL)application:(UIApplication*)application handleOpenURL:(NSURL*)url	// 当通过url执行
- (void)application:(UIApplication)application willChangeStatusBarFrame:(CGRect)newStatusBarFrame		// 当 StatusBar 框将要变化时执行
- (void)application:(UIApplication*)application didChangeSetStatusBarFrame:(CGRect)oldStatusBarFrame	// 当 StatusBar 框变化完成后执行
- (void)application:(UIApplication*)application willChangeStatusBarOrientation:(UIInterfaceOrientation)newStatusBarOrientation duration:(NSTimeInterval)duration
- (void)application:(UIApplication*)application didChangeStatusBarOrientation:(UIInterfaceOrientation)oldStatusBarOrientation	// 当 StatusBar 框方向变化完成后执行
```

# App 的启动方式

# 参考

stackoverflow

1. [Difference between AppDelegate.m and View Controller.m](http://stackoverflow.com/questions/6062569/difference-between-appdelegate-m-and-view-controller-m)
2. [Where is the applicationDidFinishLaunching function?](http://stackoverflow.com/questions/7151378/where-is-the-applicationdidfinishlaunching-function)

Apple developer Documentation

1. [UIApplicationDelegate - UIKit | Apple Developer Documentation](https://developer.apple.com/reference/uikit/uiapplicationdelegate?language=objc)
