# UIView 概述

1. 单从图形界面看, UIView 视图对象可以看作是基类来用, 属于"模型-视图-控制器"设计模式中的视图部分
2. 大多数视图可直接使用或者和委托对象结合使用, 除了 UIView 类和 UIControl 类, 因为要使用它们的子类
3. UIView 类定义了视图的基本行为, 但并不定义其视觉表示, 需要通过其子类来为像文本框(UITextView), 按键(UIButton)及工具条(UIToolBar)这样的标准界面元素定义具体的外观和行为
4. UIWindow 相当于画板, UIview 相当于画布， UIWindow 继承自 UIview
5. 屏幕适配: 子视图跟随父视图自动变化, 目前已不再用 UIView 的自适应做适配, 而用 autolayout
1. iPhone 屏幕的顶部的状态栏高度为20px


# UIview 的作用

1. 描画: UIView 对象负责在屏幕上定义一个矩形区域, 渲染矩形区域中的内容
2. 动画: 某些视图属性变量可以以动画(animation)的形式过渡到新的值
3. 子视图管理: 父视图管理着一个其直接的子视图列表, 可以通过代码调整其子视图的尺寸和位置
4. 布局: 子视图定义了自身相对于其父视图的尺寸调整行为(自适应), 视图可以将其坐标系统下的点转换为其它视图或窗口坐标系统下的点
5. 事件处理: 视图可以接收触摸事件, 是响应者链的参与者, 父视图会响应子视图没有处理的事件

# UIView 视图层次

1. 子视图是指嵌入到另一视图对象边框内部的视图对象, 被嵌入的视图被称为父视图或超视图, 视图的这种布局方式被称为视图层次
2. 一个视图可以包含任意数量的子视图, 通过为子视图添加子视图的方式, 视图可以实现任意深度的嵌套
3. 子视图总是被显示在其父视图的上方, 视图在视图层次中的组织方式决定了在屏幕上显示的内容, 以及视图如何响应事件和变化
4. 对于同一个父视图的各个子视图, 后加入的子视图在视觉上会覆盖先前加入的子视图
5. 子视图跟随父视图的层级, 层级是跟随父视图的, 父视图的层级低, 其子视图的层级也就低, 即使后加入, 也会被覆盖, 属于不同父视图的子视图之间无关
6. 正常遍历各个子视图是按照从底层到顶层的顺序
7. 子视图存放在数组中, 层级顺序即为数组元素顺序, 当交换子视图的层级之后, 对应的子视图的数组下标也会改变
8. 父视图对象只有一个, 子视图可以有多个

# UIView 的属性

1. frame: 画面大小, CGRect 结构体, 具有 size(width，height) 和 origin(x, y), 分别表示大小和位置，子视图的 frame 是相对于其直接的父视图的
2. bounds: 边界大小, CGRect 结构体, 具有 size(width，height), origin 为 0， 取值方法名同属性名
3. center: 中心点坐标, CGPoint 结构体, 具有 center(x, y)
4. backgroundColor: 背景色
5. tag: 唯一标识, 子视图的 tag 值可以相同, 但会导致无法区分
6. superview: 父视图对象, 只有一个
7. subviews: 子视图数组对象, 有多个, 即使只有一个, 也返回数组
8. autoresizesSubviews
9. autoresizingMask

# UIView 的方法

```
[self.view addSubView: subView];
UIView subView = [view viewWithTag: 2];					// 通过 tag 值获取子视图
[view exchangeSubviewAtIndex: 0 withSubviewAtIndex:1];	// 交换子视图的层级, 根据索引值直接交换数组元素位置即可
[view insertSubview: subView atIndex: 1];
[view insertSubview: subView aboveSubview: subView1];
[view insertSubview: subView belowSubview: subView1];
[view bringSubviewToFront: subView];
[view sendSubviewToBack: subView];
```

# UIView 类层次结构 class hierarchy

## 1 容器

容器视图用于增强其它视图的功能, 或者为视图内容提供额外的视觉分隔

| Class        | Describe                                                                         |
| ------------ | -------------------------------------------------------------------------------- |
| UIScrollView | 用于显示因内容太大而无法显示在一个屏幕上的视图                                           |   
| UITableView  | 用于管理数据列表, 表格的行可以支持选择, 通常用于层次数据的导航, 比如用于挖掘一组有层次结构的对象 |
| UIToolbar    | 用于为屏幕底部的工具条中的按键提供视觉分组, 可以一直显示, 也可以根据需要显示                  |

## 2 控件

1. 控件视图用于创建大多数应用程序的用户界面, 继承自 UIControl 类, 通常用于显示一个具体的值, 并处理修改这个值所需要的所有用户交互
2. 控件视图通常使用标准的系统范式(比如目标-动作模式和委托模式)来通知应用程序发生了用户交互

UIButton, UIDatePicker, UIPageControl, UISegmentedControl, UITextField, UISlider, UISwitch

## 3 显示视图

1. 显示视图用于简单地显示信息(没有交互行为)

UILabel, UIProgressView, UIActivityIndicatorView, UIImageView

## 4 文本和 Web 视图

1. 文本和 Web 视图为应用程序提供更为高级的显示多行文本的方法

| Class        | Describe                                             |
| ------------ | ---------------------------------------------------- |
| UITextView   | 支持在滚动区域内显示和编辑多行文本                        |
| UIWebView    | 用于将图形和高级的文本格式(如 HTML)以定制的方式进行布局显示  |

## 5 模态视图 modal view

1. 要求用户必须先做出选择, 然后才能继续使用应用的视图成为模态视图
1. 警告视图和动作表单用于向用户显示一条消息, 即刻取得用户的注意, 同时还有一或多个可选的按键来响应消息
1. 操作表单 action sheet 常用于向用户确认有潜在危险或无法撤销的操作
2. 警告视图 alert 用于通知用户发生了一些重要的或不寻常的事情

| Class         | Describe                  |
| ------------- | ------------------------- |
| UIAlertView   | 类在屏幕上弹出一个蓝色的警告框 |
| UIActionSheet | 类从屏幕的底部滑出动作框      |

## 6 导航视图

1. 导航视图为用户提供从一个屏幕到另一个屏幕的导航工具
2. 页签条(UITabBar)和导航条(UINavigationBar)和视图控制器(UIViewController)结合使用
3. 可通过恰当的控制器接口或 Interface Builder 来对其进行配置

## 7 窗口

1. 窗口提供一个描画内容的表面, 是所有其它视图的根容器
2. 每个应用程序通常都只有一个 UIWindow 窗口

## 8 其他

UIPickerView, UITableViewCell, UISearchBar
