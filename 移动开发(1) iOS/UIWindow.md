# UIApplicationMain 方法

1. 命令行程序总是从 main 函数执行，main.m 文件在项目文件夹中, iOS 项目用，main.m 文件转移到 Supporting Files 文件夹下，直接调用 UIKit 的 UIApplicationMain 方法
2. UIApplicationMain 方法的第1个参数没有作用, 只是为了与 ANSI C 标准保持一致, 第2个参数是一个字符串指针, 是应用程序的路径
3. UIApplicationMain 方法的第3个参数指定程序的主要类(principal class), 是 UIApplication 类(或子类)的字符串, 用于初始化一个 UIApplication 或其子类的对象并开始接收事件, 若传入 nil, 将从 Info.plist 中对应的 key 获取, 若不存在, 则使用默认的 UIApplication 类, 等价于 NSStringFromClass([UIApplication class]), UIApplication 类是单例模式, 一个应用程序只有一个 UIApplication 对象或子对象
4. UIApplicationMain 方法的第4个参数指定程序的代理类(delegate class), 是 AppDelegate 类的字符串, AppDelegate 类作为应用的委托被用来接收类似 didFinishLaunching 或者 didEnterBackground 这样的与应用生命周期相关的委托方法, 如果代理类为 nil, 则将在新建工程时创建
5. UIApplicationMain 方法返回一个 int, 但并不会真正返回, 方法内部是一个消息循环(相当于一个死循环), 会一直存在于内存中, 直到用户或者系统将其强制终止

# UIApplicationMain 方法的作用

创建 app 的几个核心对象来处理以下过程：

1. 从可用的 Storyboard 文件加载用户界面
2. 调用 AppDelegate 自定义代码来做一些初始化设置
3. 将 app 放入 Main Run Loop 环境中来响应和处理与用户交互产生的事件

# Swift 中的 UIApplicationMain 方法

1. Swift 的 mac 项目中包含一个 main.swift 文件, 作为程序入口
2. Swift 的 iOS app 项目不存在任何 main 函数, 在默认的 AppDelegate 类的声明中有一个 `@UIApplicationMain` 标签, 将被标注的 AppDelegate 类作为委托, 去创建一个 UIApplication 并启动整个程序
3. 编译器在编译时将寻找 `@UIApplicationMain` 标记的类, 并自动插入像 main 函数这样的模板代码, 合成一个 app 入口

# 自定义 UIApplication 的子类

1. 若要创建 UIApplication 的子类而不是它本身的话, 则需要自定义 UIApplicationMain 函数, 若不使用 `@UIApplicationMain` 标签, 则需要在项目中添加 main.swift 文件, 在其中声明 UIApplicationMain 函数
2. UIApplicationMain 方法的 Process.unsafeArgv 参数是一串十六进制数字, 代表应用程序的地址

`UIApplicationMain(Process.argc, Process.unsafeArgv, NSStringFromClass(MyApplication), NSStringFromClass(AppDelegate))`

# AppDelegate

1. AppDelegate 类继承自 UIResponder 类, 遵循 UIApplicationDelegate 协议
2. AppDelegate 类具有默认属性: UIWindow \*window
3. AppDelegate 相当于 app 的根类, 同 UIApplication 一样, 都是单例模式

# UIWindow

1. macOS 中一般是多窗口应用，表示为 NSWindow 类的多个实例, NSWindow 继承自 NSResponder
2. iOS 中一般都是单窗口应用，表示为 UIWindow 类的单个实例, UIWindow 继承自 UIView 继承自 UIResponder, 窗口也是视图对象
3. UIWindow 对象并没有像关闭框或标题栏这样的视觉装饰，用户不能直接对其进行关闭或其它操作, 所有对窗口的操作都需要通过其编程接口来实现, 通常不必直接操作 UIWindow 对象中与 UIView 视图有关的属性变量

# info.plist

An information property list is a specialized type of property list that contains configuration data for a bundle.

1. Core Foundation Keys
2. Launch Services Keys
3. Cocoa Keys
4. macOS Keys
5. iOS Keys
6. watchOS Keys
7. App Extension Keys 

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

# 参考

1. [UIWindow 与 UIView 深层解析](http://blog.csdn.net/gf771115/article/details/7761904)
2. [@UIAPPLICATIONMAIN](http://swifter.tips/uiapplicationmain/)
3. [iOS生命周期 - Main函数](http://istian.cc/2016/08/24/iOS%E7%94%9F%E5%91%BD%E5%91%A8%E6%9C%9F%20-%20Main%E5%87%BD%E6%95%B0/)
4. [About Info.plist Keys and Values](https://developer.apple.com/library/prerelease/content/documentation/General/Reference/InfoPlistKeyReference/Introduction/Introduction.html)
