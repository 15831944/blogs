# UIView 概述

1. 单从图形界面看，UIView 可以看作是基类来用, 视图对象属于"模型-视图-控制器"设计模式中的视图部分
2. UIWindow 相当于画板, UIview 相当于画布

## UIView 的视图层次

1. 子视图是指嵌入到另一视图对象边框内部的视图对象, 被嵌入的视图被称为父视图或超视图, 视图的这种布局方式被称为视图层次
2. 一个视图可以包含任意数量的子视图, 通过为子视图添加子视图的方式，视图可以实现任意深度的嵌套
3. 子视图总是被显示在其父视图的上方, 视图在视图层次中的组织方式决定了在屏幕上显示的内容, 视图如何响应事件和变化
4. 对于同一个父视图的各个子视图，后加入的子视图会覆盖先前加入的子视图
3. 子视图跟随父视图的层级
6. 正常遍历各个子视图是按照从底层到顶层的顺序
7. 当交换子视图的层级之后，对应的子视图的数组下标也会改变

# UIview 的作用

## 1 描画和动画

1. UIView 对象负责在屏幕上定义一个矩形区域, 负责渲染视图矩形区域中的内容
2. 某些视图属性变量可以以动画的形式过渡到新的值

## 2 布局和子视图管理

1. 视图管理着一个其直接的子视图列表
2. 子视图定义了自身相对于其父视图的尺寸调整行为(自适应)
3. 父视图可以通过代码调整其子视图的尺寸和位置
4. 视图可以将其坐标系统下的点转换为其它视图或窗口坐标系统下的点

## 3 事件处理

1. 视图可以接收触摸事件
2. 视图是响应者链的参与者, 父视图会响应子视图没有处理的事件

# UIview 的子类

1. UIView 类定义了视图的基本行为，但并不定义其视觉表示
2. UIKit 通过其子类来为像文本框, 按键及工具条这样的标准界面元素定义具体的外观和行为

# UIView 的类层次结构 class hierarchy

| Class                   | Subclass |
| ----------------------- | -------- |
| 窗口 UIWindow          |          |
| 显示 UILabel                 |          |
| UIPickerView            |          |
| 显示 UIProgressView          |          |
| 显示 UIActivityIndicatorView |          |
| 显示 UIImageView             |          |
| 标签条 UITabBar                |          |
| 容器 UIToolBar               |          |
| 导航条 UINavigationBar         |          |
| UITableViewCell         |          |
| 动作表单 UIActionSheet           |          |
| 警告 UIAlertView             |          |
| 容器 UIScrollView            | 容器 UITableView, 文本 UITextView |
| UISearchBar             |          |
| 文本 UIWebView               |          |
| 控件 UIControl               | UIButton, UIDatePicker, UIPageControl, UISegmentedControl, UITextField, UISlider, UISwitch |

## 1 容器

容器视图用于增强其它视图的功能, 或者为视图内容提供额外的视觉分隔

| Class        | Describe                                                                         |
| ------------ | -------------------------------------------------------------------------------- |
| UIScrollView | 用于显示因内容太大而无法显示在一个屏幕上的视图                                           |   
| UITableView  | 用于管理数据列表, 表格的行可以支持选择, 通常用于层次数据的导航, 比如用于挖掘一组有层次结构的对象 |
| UIToolbar    | 用于为屏幕底部的工具条中的按键提供视觉分组, 可以一直显示, 也可以根据需要显示                  |

## 2 控件

1. 控件视图用于创建大多数应用程序的用户界面, 继承自 UIControl 超类, 通常用于显示一个具体的值, 并处理修改这个值所需要的所有用户交互
2. 控件视图通常使用标准的系统范式(比如目标-动作模式和委托模式)来通知应用程序发生了用户交互

UIButton, UIDatePicker, UIPageControl, UISegmentedControl, UITextField, UISlider, UISwitch

## 3 显示视图

1. 显示视图用于简单地显示信息(没有交互行为)

UILabel, UIProgressView, UIActivityIndicatorView, UIImageView

## 4 文本和 Web 视图

1. 文本和 Web 视图为应用程序提供更为高级的显示多行文本的方法

| Class        | Describe                                             |
| ------------ | ---------------------------------------------------- |
| UITextView   | 类支持在滚动区域内显示和编辑多行文本                       |
| UIWebView    | 类用于将图形和高级的文本格式(如 HTML)以定制的方式进行布局显示 |

## 5 警告视图和动作表单

1. 警告视图和动作表单用于向用户显示一条消息, 即刻取得用户的注意, 同时还有一或多个可选的按键来响应消息

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
