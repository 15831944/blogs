# UIKit 框架

| Class                           | Subclass                                |
| ------------------------------- | --------------------------------------- |
| UIAcceleration                  |                                         |
| UIAccelerometer                 |                                         |
| UIAccessibilityElement          |                                         |
| UIBarItem                       | UIBarButtonItem, UITabBarItem           |
| UIBezierPath                    |                                         |
| UIColor                         |                                         |
| UIDevice                        |                                         |
| UIDocumentInteractionController |                                         |
| UIEvent                         |                                         |
| UIFont                          |                                         |
| UIGestureRecognizer             |                                         |
| UIImage                         |                                         |
| UILocalizedIndexedCollation     |                                         |
| UILocalNotification             |                                         |
| UIMenuController                |                                         |
| UIMenuItem                      |                                         |
| UINavigationItem                |                                         |
| UINib                           |                                         |
| UIPasteboard                    |                                         |
| UIPopoverController             |                                         |
| UIPrintFormatter                |                                         |
| UIPrintInfo                     |                                         |
| UIPrintInteractionController    |                                         |
| UIPrintPageRenderer             |                                         |
| UIPrintPager                    |                                         |
| UIResponder                     | UIApplication, UIView, UIViewController |
| UIScreen                        |                                         |
| UIScreenMode                    |                                         |
| UISearchDisplayController       |                                         |
| UITextChecker                   |                                         |
| UITextInputStringTokenizer      |                                         |
| UITextPosition                  |                                         |
| UITextRange                     |                                         |
| UITouch                         |                                         |

UIGestureRecognizer 的子类有:

1. UILongPressGestureRecognizer
2. UIPanGestureRecognizer
3. UIPinchGestureRecognizer
4. UIRotationGestureRecognizer
5. UISwipeGestureRecognizer
6. UITapGestureRecognizer

UIPrintFormatter 的子类有:

1. UISimpleTextPrintFormatter
2. UIMarkupTextPrintFormatter
3. UIViewPrintFormatter

# UIView

| Class                   | Subclass                                                                                   |
| ----------------------- | ------------------------------------------------------------------------------------------ |
| UIWindow                |                                                                                            |
| UILabel                 |                                                                                            |
| UIPickerView            |                                                                                            |
| UIProgressView          |                                                                                            |
| UIActivityIndicatorView |                                                                                            |
| UIImageView             |                                                                                            |
| UITabBar                |                                                                                            |
| UIToolBar               |                                                                                            |
| UINavigationBar         |                                                                                            |
| UITableViewCell         |                                                                                            |
| UIActionSheet           |                                                                                            |
| UIAlertView             |                                                                                            |
| UIScrollView            | UITableView, UITextView                                                                    |
| UISearchBar             |                                                                                            |
| UIWebView               |                                                                                            |
| UIControl               | UIButton, UIDatePicker, UIPageControl, UISegmentedControl, UITextField, UISlider, UISwitch |

UIView 视图类层次 UIView class hierarchy

## 1 容器

1. 作用: 容器视图用于增强其它视图的功能, 或者为视图内容提供额外的视觉分隔
2. UIScrollView 类可以用于显示因内容太大而无法显示在一个屏幕上的视图
3. UITableView 类用于管理数据列表. 表格的行可以支持选择, 所以通常也用于层次数据的导航, 比如用于挖掘一组有层次结构的对象
4. UIToolbar 类用于为屏幕底部的工具条中的按键提供视觉分组. 工具条可以一直显示, 也可以根据需要进行显示

## 2 控件

1. 作用: 控件用于创建大多数应用程序的用户界面
2. 控件继承自UIControl超类，通常用于显示一个具体的值，并处理修改这个值所需要的所有用户交互
3. 控件通常使用标准的系统范式(比如目标-动作模式和委托模式)来通知应用程序发生了用户交互
4. 控件包括按键(UIButton), 文本框(UITextField), 滑块(UISlider), 切换开关(UISwitch)等

## 3 显示视图

1. 显示视图用于简单地显示信息(没有交互行为)
2. 显示视图包括: UILabel, UIProgressView, UIActivityIndicatorView, UIImageView

## 4 文本和web视图

1. 文本和web视图为应用程序提供更为高级的显示多行文本的方法
2. UITextView 类支持在滚动区域内显示和编辑多行文本
3. UIWebView 类用于将图形和高级的文本格式(如HTML)以定制的方式进行布局显示

## 5 警告视图和动作表单

1. 警告视图和动作表单用于向用户显示一条消息, 即刻取得用户的注意, 同时还有一或多个可选的按键来响应消息
2. UIAlertView 类在屏幕上弹出一个蓝色的警告框
3. UIActionSheet 类从屏幕的底部滑出动作框

## 6 导航视图

1. 导航视图为用户提供从一个屏幕到另一个屏幕的导航工具
2. 页签条(UITabBar)和导航条(UINavigationBar)和视图控制器(UIViewController)结合使用
3. 可通过恰当的控制器接口或 Interface Builder 来对其进行配置

## 7 窗口

1. 窗口提供一个描画内容的表面, 是所有其它视图的根容器
2. 每个应用程序通常都只有一个 UIWindow 窗口

# UIViewController

视图控制器，用于管理各视图对象

| Class                  | Class                                            |
| ---------------------- | ------------------------------------------------ |
| UISplitViewController  |                                                  |
| UITabBarController     |                                                  |
| UITableViewController  |                                                  |
| UINavigationController | UIImagePickerController, UIVideoEditorController |

除了 UIView 类和 UIControl 类，大多数视图都设计为可直接使用或者和委托对象结合使用

# UIWindow

1. Mac OS X 中一般是多窗口应用，表示为 UIWindow 类的多个实例
2. iOS 中一般都是单窗口应用，表示为 UIWindow 类的一个实例
3. 在 Mac OS X 中，NSWindow 继承自 NSResponder
4. 在 iOS 中，UIWindow 继承自 UIView(窗口也是视图对象) (UIView 继承自 UIResponder)
5. 通常不必直接操作 UIWindow 对象中与 UIView 视图有关的属性变量
6. 窗口对象并没有像关闭框或标题栏这样的视觉装饰，用户不能直接对其进行关闭或其它操作, 所有对窗口的操作都需要通过其编程接口来实现

UIWindow 的作用

1. 可以看做是一个容器，用来放置标签，按钮等子控件，即为内容显示提供背景平台
2. 传递触摸消息，应用程序可以借助窗口对象来进行事件传递，窗口对象会持续跟踪当前的第一响应者对象，并在 UIApplication 对象提出请求时将事件传递它
3. 协同控件做出响应，例如旋转手机时横屏竖屏的切换

UIWindow 实例化

1. 应用程序在启动时创建这个窗口, 也可以从 nib 文件或者 main.storyboard 进行装载
2. 窗口显示出来之后，很少需要再次引用它
3. 窗口中可以添加标签，按钮等不同的控件，或者说添加一或多个视图
4. 视图通过窗口进行显示，同时刻显示的同一级别的 window 只能有一个
5. UIWindow 的初始的边框尺寸总是应设置为整个屏幕的大小
6. 如果窗口从nib文件装载得到，Interface Builder 并不允许创建比屏幕尺寸小的窗口
7. 如果窗口通过编程方式创建，则必须在创建时传入期望的边框矩形
8. 除了屏幕矩形之外，没有理由传入其它边框矩形

UIWindow 的属性

1. AppDelegate 类继承自 UIResponder 类, 遵循 UIApplicationDelegate 协议

UIWindow 的方法

UIWindow 的级别

| Window                 | 作用                         |
| ---------------------- | ---------------------------- |
| UIwindowLevelAlert     | 系统使用此窗口显示重要的警告      |
| UIwindowLevelStatusBar | 系统使用此窗口显示屏幕上方的状态栏 |
| UIwindowLevelNormal    | 应用程序窗口                   |

1. 三个级别可以同时显示在屏幕上，同一个级别同一时刻只能显示一个
2. 同一级别的 window 可以有多个实例化对象，但是同一时刻只能显示一个

# main.storyboard

1. main.storyboard 是一个可视化开发工具
2. 在项目设置的 Deployment Info 中指定 main interface 为 main 则表示应用从 main.storyboard 启动
3. 若要自定义启动窗口，应将此项不选

# main 函数

1. 对于命令行应用，程序总是从 main 函数执行，main.m 文件在项目文件夹中
2. 对于图形界面应用，main.m 文件转移到 Supporting Files 文件夹下，直接调用用户界面的 main 函数

`UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));`

# UIView

UIview 的作用

1. 单从图形界面看，UIView 可以看作是基类来用
2. UIView 对象负责在屏幕上定义一个矩形区域
3. 视图在展示用户界面及响应用户界面交互方面发挥关键作用
4. 每个视图对象都要负责渲染视图矩形区域中的内容，并响应该区域中发生的触碰事件, 这一双重行为意味着视图是应用程序与用户交互的重要机制
5. 在一个基于模型-视图-控制器的应用程序中，视图对象明显属于视图部分
6. 除了显示内容和处理事件之外，视图还可以用于管理一或多个子视图
7. 子视图是指嵌入到另一视图对象边框内部的视图对象, 被嵌入的视图被称为父视图或超视图, 视图的这种布局方式被称为视图层次
8. 一个视图可以包含任意数量的子视图，通过为子视图添加子视图的方式，视图可以实现任意深度的嵌套
9. 视图在视图层次中的组织方式决定了在屏幕上显示的内容，原因是子视图总是被显示在其父视图的上方
10. 这个组织方法还决定了视图如何响应事件和变化，每个父视图都负责管理其直接的子视图，即根据需要调整它们的位置和尺寸，以及响应它们没有处理的事件

描画和动画

1. 视图负责对其所属的矩形区域进行描画
2. 某些视图属性变量可以以动画的形式过渡到新的值

布局和子视图管理

1. 视图管理着一个子视图列表
2. 视图定义了自身相对于其父视图的尺寸调整行为(自适应)
3. 必要时，视图可以通过代码调整其子视图的尺寸和位置
4. 视图可以将其坐标系统下的点转换为其它视图或窗口坐标系统下的点

事件处理

1. 视图可以接收触摸事件
2. 视图是响应者链的参与者

UIview 的子类

1. UIView类定义了视图的基本行为，但并不定义其视觉表示
2. UIKit通过其子类来为像文本框、按键及工具条这样的标准界面元素定义具体的外观和行为

# ViewController 视图控制器

视图和视图控制器紧密协作，管理若干方面的视图行为。
运行在 iOS 上的应用程序在如何组织内容和如何将内容呈现给用户方面有很多选择。
含有很多内容的应用程序可以将内容分为多个屏幕。
在运行时，每个屏幕的背后都是一组视图对象，负责显示该屏幕的数据。
一个屏幕的视图后面是一个视图控制器, 其作用是管理那些视图上显示的数据，并协调它们和应用程序其它部分的关系。
UIViewController 类负责创建其管理的视图及在低内存时将它们从内容中移出。
视图控制器还为某些标准的系统行为提供自动响应。比如，在响应设备方向变化时，如果应用程序支持该方向，视图控制器可以对其管理的视图进行尺寸调整，使其适应新的方向。
您也可以通过视图控制器来将新的视图以模式框的方式显示在当前视图的上方。
除了基础的UIViewController类之外，UIKit还包含很多高级子类，用于处理平台共有的某些高级接口。
特别需要提到的是，导航控制器用于显示多屏具有一定层次结构的内容；
而页签条控制器则支持用户在一组不同的屏幕之间切换，每个屏幕都代表应用程序的一种不同的操作模式。

ViewController 的作用

1. 处理视图的装载与卸载
2. 处理由于设备旋转导致的界面旋转
3. 用于构建复杂用户界面的高级导航对象进行交互

UIview 实例化

1. UIWindow 相当于画板, UIview 相当于画布

# 控件的位置

1. iPhone 屏幕的顶部的状态栏高度为20px
2. CGRect 结构体: bounds 和 frame 都是 CGRect 结构体类型, 使用 bounds 和 frame 获取控件的边框大小和画面大小, bounds 为边框大小，其 origin.x 和 origin.y 永远为0
3. CGPoint 结构体: center 是 CGPoint 结构体类型, 使用 center 属性获取控件的中心点的坐标
4. 图片的命名可以使用 name.png, name@2x.png name@3x.png 的形式, Retina 屏幕会自动选择带有 /@2x 的图片，这样布局只需要一套，只是图片需要两套

# iPhone 的尺寸

| model        | size | resolution | times | size        |
| ------------ | ---- | ---------- | ----- | ----------- |
| 3GS          | 3.5  | 320 * 480  | @1x   | 320 * 480   |
| 4/4s         | 3.5  | 320 * 480  | @2x   | 640 * 960   |
| 5/5s/5c      | 4.0  | 320 * 568  | @2x   | 640 * 1136  |
| 6/6s         | 4.7  | 375 * 667  | @2x   | 750 * 1334  |
| 6plus/6splus | 5.5  | 414 * 736  | @3x   | 1242 * 2208 |

# UIScreen

获取屏幕大小

`float width = [[UIScreen mainScreen] bounds].size.width;`

`float height = [[UIScreen mainScreen] bounds].size.height;`

# 子视图的层级

1. 对于同一个父视图的各个子视图，后加入的子视图会覆盖先前加入的子视图
2. 子视图跟随父视图的层级
3. 正常遍历各个子视图是按照从底层到顶层的顺序
4. 当交换子视图的层级之后，对应的子视图的数组下标也会改变

UIview 的属性

| property            | describe |
| ------------------- | -------- |
| superview           |  |
| subviews            |  |
| tag                 | 允许相同 |
| frame               |  |
| center              |  |
| backgroundColor     |  |
| superview           |  |
| subviews            |  |
| autoresizesSubviews |  |
| autoresizingMask    |  |

UIview 的方法

| method              | describe |
| ------------------- | -------- |
| bounds              |  |
| addSubview          |  |
| bringSubviewToFront |  |
| sendSubviewToBack   |  |

UIview 的自适应

1. 子视图跟随父视图自动变化, 目前已不再用 UIView 的自适应做适配, 而用 autolayout

# UILabel

1. UILabel 默认是透明的

UILabel 属性

| property      | meaning |
| ------------- | ------- |
| text          | 文本内容 |
| textColor     | 文本颜色 |
| textAlignment | 文本布局 |
| alpha         | 透明度，整个 Label，而非只是本文或控件 |
| font          | 字体及字号(斜体对中文无效) |
| shadowColor   | 文本阴影颜色 |
| shadowOffset  | 文本阴影偏移位置 |
| lineBreakMode | 断行模式 |
| numberOfLines | 行数(设置为0或-1表示不限制行数) |

# UIImage

图片的加载

1. 每次都重新加载，耗费加载时间，适合大图片
2. 加载到内存，耗费内存资源，适合频繁使用的小图片

```
UIImage *image1 = [[UIImage alloc] initWithContentsOfFile:imagePath];
UIImage *image2 = [UIImage imageNamed:@"101"];
```

# UIImageView

1. UIImageView 是图片的载体, 图片需要载体才能显示在屏幕上
2. 载体可以是 UIImageView，可以是 Button 等
3. 载体控制屏幕上显示的图片的大小，默认的内容模式是拉伸

| Content Mode                     | meaning |
| -------------------------------- | ------- |
| UIViewContentModeScaleToFill     | 拉伸(默认) |
| UIViewContentModeCenter          | 居中      |
| UIViewContentModeScaleAspectFit  | 按短边填充 |
| UIViewContentModeScaleAspectFill | 按长边填充 |

# 序列图

1. 将图片对象存入数组，进行动画播放

# UIColor

UIColor 的方法

| method                            | meaning        |
| --------------------------------- | -------------- |
| clearColor                        | 透明色          |
| redColor                          | 红色            |
| colorWithRed: green: blue: alpha: | RGB 颜色及透明度 |

# 参考

教程

[iOS 基础教程之界面初体验](http://www.imooc.com/learn/486)

博客

1. [OC学习之UIKit的类层次结构图](http://blog.csdn.net/heyddo/article/details/9631919)
2. [IOS UIKIT框架类之窗口和视图架构介绍！](http://blog.csdn.net/qq_31082775/article/details/50424454)
3. [UIWindow 与 UIView 深层解析](http://blog.csdn.net/gf771115/article/details/7761904)
