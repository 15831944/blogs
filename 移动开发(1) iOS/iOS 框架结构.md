# iOS 框架结构

在系统中的位置, 由上到下依次是:

| Framework     | Sub Framework                            |
| ------------- | ---------------------------------------- |
| Application   |                                          |
| Cocoa Touch   | UIKit                                    |
| Media         | Core Graphics, OpenGL ES, Core Animation |
| Core Services | Core Data, Foundation                    |
| Core OS       |                                          |

# UIKit

UIKit 提供基于预渲染图形的视图和控件, 在屏幕上绘制的机制, 捕获事件和创建通用用户界面元素, 通过管理显示在屏幕上的组件来组织复杂的项目

UIKit 的功能

1. 构建和管理你的用户界面
2. 捕获触摸和基于移动的事件
3. 呈现文字和web内容
4. 优化你的多任务程序
5. 创建定制的用户界面元素

UIKit 的使用

1. 在用户界面工具(interface Buidler)从对象库里拖拽窗口, 视图或者其他的对象使用
2. 用代码创建
3. 通过继承 UIView 类或间接继承 UIView 类实现自定义用户界面
4. UIResponder 为处理响应事件和响应链定义了界面和默认行为, 当用户用手指滚动列表或者在虚拟键盘上输入时, UIKit 就生成时间传送给 UIResponder 响应链, 直到链中有对象处理这个事件

# Core Graphics

Core Graphics 提供了更底层的库创建复杂的图形

Core Graphics 的功能

1. 创建基于路径的绘图
2. 抗锯齿渲染
3. 添加梯度、图片和颜色
4. Use coordinate-space transformations.
5. 创建、显示和分析PDF文档

# OpenGL ES

OpenGL ES 提供绘图工具, 支持2D和3D绘图，Apple 的 OpenGL ES 实现通过硬件提供了高速的全屏游戏式的应用程序

OpenGL ES 的功能

1. 创建2D和3D图形
2. 创建更复杂的图形，比如数据虚拟化、模拟飞行，或者视频游戏
3. 访问底层图形设备

# Core Animation

1. Core Animation 接口包含在 Quartz Core 框架里, 允许你创建高级的动画和虚拟效果, UIKit 提供建立在 Core Animation 之上的动画。
2. Core Animation 可以创建嵌套的对象，并且可以对它们操作、旋转、缩放和转换, 创建动态的用户界面而不用使用更底层的图形API，如OpenGL ES。

Core Animation 的功能

1. 创建定制动画
2. 添加定时函数和图形
3. 支持帧动画
4. Specify graphical layout constraints.
5. Group multiple-layer changes into anatomic update.

# Core Data

1. Core Data 框架管着理应用程序数据模型, 创建模型对象，并管理这些对象间的联系并修改数据
2. Core Data 提供的内建 SQLlite 技术可以高效的管理数据

Core Data 的功能

1. 在库里存储和接收对象
2. 提供基本的 undo/redo
3. 自动验证属性值
4. 过滤、分组和优化内存中的数据
5. 用[NSFetchedResultsController]管理表视图中的结果
6. 支持基于文档的应用程序

# Foundation

1. Foundation 框架为所有的应用程序提供基本系统服务, 应用程序, UIKit 和其它的框架都建立在Foundation框架上
2. Foundation 框架是用 Object-C 对 Core Foundation 框架里许多特性的封装

Foundation 的功能

1. 创建和管理集合，比如数组和字典
2. 访问存储在应用程序里的图片和其它资源
3. 创建和管理字符串
4. 提交和接收通知
5. 创建日期和时间对象
6. 自动发现IP网络上的设备
7. 操作URL流
8. 执行异步代码
