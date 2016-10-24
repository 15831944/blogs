# 框架 Framework

1. 框架是一个目录, 包含: 共享库及其头文件, 图片和声音等资源文件
2. 将共享库添加到项目中即可使用框架提供的方法和函数
3. 根据项目模板，相关的框架会被自动引入, 还可以手动添加
4. 举例: Foundation, UIKit, Core Graphics

# 基类 NSObject

1. NSObject 基类是大部分 Objective-C 类的根类, 它没有父类
2. NSObject 协议指定了根类必须实现的接口
3. 继承 NSObject 的类可以访问 Objective-C 运行时系统的基本接口, 获得运行时的能力

根类的主要方法

1. 对象的内存分配, 初始化, 复制

| method        | describe      |
| ------------- | ------------- |
| alloc         | 对象的内存分配  |
| allocWithZone | 对象的内存分配  |
| init          | 对象初始化      |
| new           | 内存分配和初始化 |
| copy          | 内存拷贝        |
| copyWithZone  | 内存拷贝        |

2. 对象的保持和清理

| method      | describe                  |
| ----------- | ------------------------- |
| retain      | 增加对象的保持次数           |
| release     | 减少对象的保持次数           |
| autorelease | 减少对象的保持次数, 以推迟方式 |
| retainCount | 返回对当前的保持次数         |
| dealloc     | 由需要释放对象的实例变量以及释放动态分配的内存的类实现 |

3. 内省和比较

内省方法: 查询对象的运行时信息, 找出对象在类层次中的位置, 确定对象是否实现特定的方法, 测试对象是否遵循某种协议

| method                      | describe                  |
| --------------------------- | ------------------------- |
| superclass                  | 类方法, 以Class对象的形式返回接收者的父类 |
| class                       | 对象方法, 以Class对象的形式返回接收者的类 |
| isKindOfClass:              | 确定对象属于哪个类 |
| isMemberOfClass:            | 测试接收者是否为指定类的实例 |
| isSubclassOfClass:          | 类方法, 用于测试类的继承性 |
| respondsToSelector:         | 测试接收者是否实现由选择器参数标识的方法 |
| instancesRespondToSelector: | 类方法, 用于测试给定类的实例是否实现指定的方法 |
| conformsToProtocol:         | 用于测试接收者（对象或类）是否遵循给定的协议 |
| isEqual:                    | 用于对象的比较 |
| hash                        | 用于对象的比较 |
| description                 | 允许对象返回一个内容描述字符串；这个方法的输出经常用于调试（“printobject”命令），以及在格式化字符串中和“%@”指示符一起表示对象 |

4. 对象的编码和解码(作为归档过程的一部分)

encodeWithCoder: NSCoding协议仅有的方法, 使对象可以对其实例变量进行编码
initWithCoder:   NSCoding协议仅有的方法, 使对象可以根据解码过的实例变量对自身进行初始化
classForCoder:
replacementObjectForCoder:
awakeAfterUsingCoder:

5. 消息的转发和派发

forwardInvocation: 允许一个对象将消息转发给另一个对象
performSelector*   允许你延迟后派发指定消息，而且可以将消息（同步或异步的消息）从辅助线程派发到主线程

# Cocoa

1. Cocoa 是在 Mac OS X 系统上原生的一个编译环境
2. 包含2个框架(类库): Foundation, AppKit
3. Cocoa 程序是由一些对象组成, 而这些对象的类最后都是继承于它们的根类: NSObject, 而且都基于 Objective-C 运行环境
4. AppKit 框架是 Mac OS X 上的用户图形包, 类名以NS开头

# Cocoa Touch

1. Cocoa Touch 是 Cocoa 的子类, 用于 iOS 设备
2. 包含2个框架(类库): Foundation, UIKit
3. 不支持垃圾回收机制, 必须在代码里管理好内存
4. Foundation 框架提供了一系列基础数据类型、以及枚举、容器的支持。Foundation 框架的类名以NS开头
5. UIKit 框架是 iOS 上的用户图形包。UI开头的类都来自于这个框架

# Cocoa 对象生命周期

对象的四种管理方式, 保持接收到的对象, 拷贝接收到的对象, 自动释放池

# Objective C

1. Foundation 框架和 UIKit 框架所用的编程语言
2. Objective-C 具有封装, 继承, 多态, 重用; 不具有重载, 模版, 多继承, 垃圾回收机制
3. Objective-C 的优势是它的动态能力
4. 动态类: 运行时确定类的对象
5. 动态绑定: 运行时确定要调用的方法
6. 动态加载: 运行时为程序加载新的模块

# isa 指针

1. isa 指针是对象的隐藏数据, 也是对象的第一个成员变量
2. isa 指针指向一个类对象(class object), 类对象占用内存空间, 在编译的时候生成, 用来描述某个类的定义
3. 类对象包含了 Objective-C 对象的一些信息, 包括 Objective-C 对象的方法调度表，实现了什么协议等等, 这个包含信息就是 Objective-C 动态能力的根源

isa 指针类型的数据结构

```
struct objc_class {
    Class isa;			//指向元类对象(metaclass object)
    Class super_class;	//指向父类的类对象
    const char *name;  
    long version;  
    long info;
    long instance_size;  
    struct objc_ivar_list *ivars;  
    struct objc_method_list **methodLists;   
    struct objc_cache *cache;  
    struct objc_protocol_list *protocols;     
 }  
 ```

# XCode

1. Interface Builder: 用于UI设计

# iOS 框架组织结构

在系统中的位置, 由上到下依次是:

1. Application
2. Cocoa Touch (UIKit)
3. Media (Core Graphics, OpenGL ES, Core Animation)
4. Core Services (Core Data, Foundation)
5. Core OS

# UIKit

1. UIKit 提供了在屏幕上绘制的机制，捕获事件和创建通用用户界面元素, 通过管理显示在屏幕上的组件来组织复杂的项目

UIKit 的功能

1. 构建和管理你的用户界面
2. 捕获触摸和基于移动的事件
3. 呈现文字和web内容
4. 优化你的多任务程序
5. 创建定制的用户界面元素

UIKit 的使用

1. 在用户界面工具（interface Buidler）从对象库里拖拽窗口，视图或者其他的对象使用
2. 用代码创建
3. 通过继承 UIView 类或间接继承 UIView 类实现自定义用户界面
4. UIResponder 为处理响应事件和响应链定义了界面和默认行为, 当用户用手指滚动列表或者在虚拟键盘上输入时，UIKit 就生成时间传送给 UIResponder 响应链，直到链中有对象处理这个事件

# Core Graphics

1. UIKit 框架提供的基于预渲染图形的视图和控件
3. Core Graphics 则提供了更底层的库创建复杂的图形

Core Graphics 的功能

1. 创建基于路径的绘图
2. 抗锯齿渲染
3. 添加梯度、图片和颜色
4. Use coordinate-space transformations.
5. 创建、显示和分析PDF文档

# OpenGL ES

1. OpenGL ES 提供绘图工具, 支持2D和3D绘图，Apple 的 OpenGL ES 实现通过硬件提供了高速的全屏游戏式的应用程序。

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
2. 提供基本的undo/redo
3. 自动验证属性值
4. 过滤、分组和优化内存中的数据
5. 用[NSFetchedResultsController]管理表视图中的结果
6. 支持基于文档的应用程序

# Foundation

1. Foundation 框架为所有的应用程序提供基本系统服务, 应用程序, UIKit和其它的框架都建立在Foundation框架上
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
