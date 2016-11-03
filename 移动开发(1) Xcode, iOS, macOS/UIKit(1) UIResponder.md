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

# UIView 视图类层次 UIView class hierarchy

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
