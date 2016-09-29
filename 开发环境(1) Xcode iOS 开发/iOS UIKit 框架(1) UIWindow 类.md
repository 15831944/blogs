# 1. 手机界面

Mac OS X 中一般是多窗口应用，表示为 UIWindow 类的多个实例

iOS 中一般都是单窗口应用，表示为 UIWindow 类的一个实例

# 2. UIWindow 的作用

1. 可以看做是一个容器，用来放置标签，按钮等子控件，即为内容显示提供背景平台

2. 传递触摸消息，应用程序可以借助窗口对象来进行事件传递，窗口对象会持续跟踪当前的第一响应者对象，并在 UIApplication 对象提出请求时将事件传递它

3. 协同控件做出响应，例如旋转手机时横屏竖屏的切换

# 3. UIWindow 实例化

在 Mac OS X 中，NSWindow 的父类是 NSResponder

在 iOS 中，UIWindow 类继承自 UIView 类

因此，窗口在 iOS 中也是一个视图对象

通常不必直接操作 UIWindow 对象中与 UIView 视图有关的属性变量

窗口对象并没有像关闭框或标题栏这样的视觉装饰，用户不能直接对其进行关闭或其它操作

所有对窗口的操作都需要通过其编程接口来实现

应用程序在启动时创建这个窗口

也可以从 nib 文件或者 main.storyboard 进行装载

窗口显示出来之后，很少需要再次引用它

窗口中可以添加标签，按钮等不同的控件，或者说添加一或多个视图

视图通过窗口进行显示，同时刻显示的同一级别的 window 只能有一个

UIWindow 的初始的边框尺寸总是应设置为整个屏幕的大小

如果窗口从nib文件装载得到，Interface Builder 并不允许创建比屏幕尺寸小的窗口

如果窗口通过编程方式创建，则必须在创建时传入期望的边框矩形

除了屏幕矩形之外，没有理由传入其它边框矩形

```
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    _window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];	// 总是应该使用屏幕尺寸创建窗口
    _window.rootViewController = _navigationController;
    _window.backgroundColor = [UIColor redColor];
    [_window makeKeyWindow];
    return YES;
}
```

# 3. UIWindow 的属性

AppDelegate 类继承自 UIResponder 类, 遵循 UIApplicationDelegate 协议

`@interface AppDelegate : UIResponder <UIApplicationDelegate>`

UIwindow 属性

`@property (strong, nonatomic) UIWindow *window;`

UINavigationController 属性

`@property (strong,nonatomic)UINavigationController *navigationController;`

# 4. UIWindow 的方法

应用载入完成后

`- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions`

# 5. UIWindow 的级别

从高到低3个级别分别为：

| 窗口 | 作用 |
| - | - |
| UIwindowLevelAlert | 系统使用此窗口显示重要的警告 |
| UIwindowLevelStatusBar | 系统使用此窗口显示屏幕上方的状态栏 |
| UIwindowLevelNormal | 应用程序窗口 |

三个级别可以同时显示在屏幕上，同一个级别同一时刻只能显示一个

同一级别的 window 可以有多个实例化对象，但是同一时刻只能显示一个

# 6. main.storyboard 

main.storyboard 是一个可视化开发工具

在项目设置的 Deployment Info 中指定 main interface 为 main 则表示应用从 main.storyboard 启动

若要自定义启动窗口，应将此项不选

# 7. main 函数

对于命令行应用，程序总是从 main 函数执行，main.m 文件在项目文件夹中

对于图形界面应用，main.m 文件转移到 Supporting Files 文件夹下，直接调用用户界面的 main 函数

`UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));`


# 8. 参考

[iOS 基础教程之界面初体验](http://www.imooc.com/learn/486)

[UIWindow 与 UIView 深层解析](http://blog.csdn.net/gf771115/article/details/7761904)
