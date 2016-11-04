# main

1. 对于命令行应用，程序总是从 main 函数执行，main.m 文件在项目文件夹中
2. 对于图形界面应用，main.m 文件转移到 Supporting Files 文件夹下，直接调用用户界面的 UIApplicationMain 函数, 转到 AppDelegate 类
3. 实现细节?

# AppDelegate

1. AppDelegate 类继承自 UIResponder 类, 遵循 UIApplicationDelegate 协议
2. AppDelegate 类的默认属性: UIWindow \*window

# UIWindow

1. macOS 中一般是多窗口应用，表示为 NSWindow 类的多个实例, NSWindow 继承自 NSResponder
2. iOS 中一般都是单窗口应用，表示为 UIWindow 类的单个实例, UIWindow 继承自 UIView 继承自 UIResponder, 窗口也是视图对象
3. UIWindow 对象并没有像关闭框或标题栏这样的视觉装饰，用户不能直接对其进行关闭或其它操作, 所有对窗口的操作都需要通过其编程接口来实现, 通常不必直接操作 UIWindow 对象中与 UIView 视图有关的属性变量
4. 旧版本中, 在 AppDelegate 类的 didFinishLaunchingWithOptions: 函数中初始化 UIWindow

# xib

1. 较新版本中, 应用程序在启动后, 默认从 xib 文件创建窗口

# Main.storyboard

1. 最新版本中, 默认使用 main.storyboard(可视化开发工具) 初始化 UIWindow, 将 Deployment Info 中的 main interface 指定为空, 则可以在上述函数中手动进行初始化 UIWindow

# LaunchScreen.storyboard



# info.plist



# UIWindow 的作用

1. 作为容器，用来放置标签，按钮等子控件，或者说添加一或多个视图, 即为内容显示提供背景平台, 窗口显示出来之后，很少需要再次引用它
2. 传递触摸消息，应用程序可以借助窗口对象来进行事件传递，窗口对象会持续跟踪当前的第一响应者对象，并在 UIApplication 对象提出请求时将事件传递它
3. 协同控件做出响应，例如旋转手机时横屏竖屏的切换
4. UIWindow 的初始的边框尺寸总是应设置为整个屏幕的大小, 除了屏幕矩形之外，没有理由传入其它边框矩形
5. 如果窗口从 xib 文件装载得到，Interface Builder 并不允许创建比屏幕尺寸小的窗口, 如果窗口通过编程方式创建, 则必须在创建时传入期望的边框矩形

# UIWindow 的属性

1. backgroundColor
2. windowLevel

# UIWindow 的级别

1. 视图通过窗口进行显示, 3个级别可以同时显示在屏幕上，同一个级别的 window 可以有多个实例化对象, 单同一时刻只能显示一个

| level                  | 作用                  |
| ---------------------- | -------------------- |
| UIwindowLevelAlert     | 用于显示重要的警告      |
| UIwindowLevelStatusBar | 用于显示屏幕上方的状态栏 |
| UIwindowLevelNormal    | 应用程序窗口           |

# UIWindow 的实例化

```
_window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
_window.backgroundColor = [UIColor whiteColor];
[_window makeKeyAndVisible];
UIViewController* vc = [[UIViewController alloc]initWithNibName:nil bundle:nil];
[_window setRootViewController:vc];
```
