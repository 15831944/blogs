# iOS 基本概念

## Framework

框架是一个目录。这个目录包含：

1. 共享库
2. 访问共享库里代码的头文件
3. 其它的图片和声音的资源文件

一个共享库定义的方法或函数可以被应用程序调用。

iOS提供了很多你可以在应用程序里调用的框架。

要使用一个框架，需要将它添加到你的项目中，你的项目才可以使用它。

许多应用程序都使用了如Foundation、UIKit、和Core Graphics这些框架。

根据你为应用程序选择的模版，相关的框架就已经被自动引入了。

如果默认加入的框架不能满足你的应用程序的需求，你也可以加入需要的框架。

## NSObject

所有类的基类。

NSObject 是大部分 Objective-C 类的根类，它没有父类。
其它类继承 NSObject，访问 Objective-C 运行时系统的基本接口，这样其他类的实例可以获得运行时的能力。

NSObject 不但是个类名，NSObject 也是个协议的名称

NSObject 协议指定了根类必须实现的接口。

根类的主要方法：

### 分配、初始化、和复制

分配

alloc 和 allocWithZone:方法用于从某内存区域中分配一个对象内存，并使对象指向其运行时的类定义。

初始化

init方法是对象初始化。

复制

new 是一个将简单的内存分配和初始化结合起来的方法。
copy 和 copyWithZone:
 
### 对象的保持和清理

retain方法增加对象的保持次数。

release方法减少对象的保持次数。

autorelease方法也是减少对象的保持次数，但是以推迟的方式。

retainCount方法返回对当前的保持次数。

dealloc方法由需要释放对象的实例变量以及释放动态分配的内存的类实现。

### 内省和比较
 
NSObjec有很多方法可以查询对象的运行时信息。

这些内省方法有助于找出对象在类层次中的位置，确定对象是否实现特定的方法，以及测试对象是否遵循某种协议。

下面是部分方法 

superclass和class方法（实现为类和实例方法）分别以Class对象的形式返回接收者的父类和类。

您可以通过isKindOfClass:和isMemberOfClass:方法来确定对象属于哪个类。后者用于测试接收者是否为指定类的实例。

isSubclassOfClass:类方法则用于测试类的继承性。

respondsToSelector:方法用于测试接收者是否实现由选择器参数标识的方法。

instancesRespondToSelector:类方法则用于测试给定类的实例是否实现指定的方法。

conformsToProtocol:方法用于测试接收者（对象或类）是否遵循给定的协议。

isEqual:和hash方法用于对象的比较。

description方法允许对象返回一个内容描述字符串；这个方法的输出经常用于调试（“printobject”命令），以及在格式化字符串中和“%@”指示符一起表示对象。

### 对象的编码和解码
 
下面的方法和对象的编解码（作为归档过程的一部分）有关：

encodeWithCoder:和initWithCoder:是NSCoding协议仅有的方法。前者使对象可以对其实例变量进行编码，后者则使对象可以根据解码过的实例变量对自身进行初始化。

NSObject类中声明了一些于对象编码有关的方法：

classForCoder:

replacementObjectForCoder:

awakeAfterUsingCoder:
 
### 消息的转发
 
forwardInvocation:允许一个对象将消息转发给另一个对象。

### 消息的派发 
 
在performSelector开头的一些方法允许你延迟后派发指定消息，而且可以将消息（同步或异步的消息）从辅助线程派发到主线程。

## Cocoa

Cocoa 是在 Mac OS X 系统上原生的一个编译环境。

他包含两个框架，其实就是一系列的类库，Foundation 和 AppKit。

是什么因素使一个程序成为 Cocoa 程序呢？

不是编程语言，因为在 Cocoa 开发中你可以使用各种语言；

也不是开发工具，你可以在命令行上就可以创建 Cocoa 程序。

Cocoa程序是由一些对象组成，而这些对象的类最后都是继承于它们的根类: NSObject。

而且它们都是基于Objective-C运行环境的。


## Cocoa Touch

Cocoa Touch 是 Cocoa 的子类，用于 iOS 设备。

他所支持的 Foundation 框架与 Cocoa 相同，但他的用户图形类库为 UIKit，它是为掌上设备特殊设计，提供了你设备上的界面。

Cocoa Touch与 Cocoa 一个比较鲜明的区别就是 Cocoa Touch 并不支持垃圾回收机制，这就意味着你必须在你的代码里管理好你的内存。

## Cocoa 对象生命周期

对象的四种管理方式

保持接收到的对象

拷贝接收到的对象

自动释放池

## Foundation

Foundation 框架提供了一系列基础数据类型、以及枚举、容器的支持。

来自于这个框架的类名以NS开头。

 
## UIKit

iOS上的用户图形包。UI开头的类都来自于这个框架。

于Mac OS X上的用户图形包不同，那上面的图形类来自AppKit，类名以NS开头。

 
## Objective C

一门iOS和MAC OS X上应用程序开发的语言，同时也是Foundation和UIKit框架所用的变成于洋。

它是C语言的超集，面向对象。

Objective-C 和 Java, C++ 一样，有封装，继承，多态，重用。但是它不像C++那样有重载操作法、模版和多继承，也没有Java的垃圾回收机制。

Objective-C 语言有 C++, Java 等面向对象的特点，那是远远不能体现它的优点的。

Objective-C的优点是它是动态的。动态能力有三种：

动态类-运行时确定类的对象

动态绑定-运行时确定要调用的方法

动态加载--运行时为程序加载新的模块

## isa 指针

每个 Objective-C 对象都有一个隐藏的数据结构，这个数据结构是 Objective-C 对象的第一个成员变量，它就是 isa 指针。

这个指针指向哪呢？

它指向一个类对象(class object), 记住类对象是个对象，是占用内存空间的一个变量，这个对象在编译的时候编译器就生成了，专门来描述某个类的定义.

这个类对象包含了 Objective-C 对象的一些信息（为了区分两个对象，我把前面提到的对象叫Objective-C对象），包括Objective-C对象的方法调度表，实现了什么协议等等。

这个包含信息就是 Objective-C 动态能力的根源了。

### isa 指针类型的数据结构

objc_class 结构

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

## XCode

在MAC OS X上的一个IDE，主要用于代码的编写。

 

## Interface Builder

XCode的一部分，主要用于UI设计。

# iOS 框架组织结构

在你开发程序时，主要使用框架就是Foundation和UIKit，因为它们包含了你需要的大部分东西。

## 1. Application

略

## 2. Cocoa Touch

### 1. UIKit

所有的 iOS 应用程序都基于UIKit，你不能使应用程序脱离这个框架。

UIKit 提供了在屏幕上绘制的机制，捕获事件和创建通用用户界面元素。

UIKit也通过管理显示在屏幕上的组件来组织复杂的项目。

使用UIKit可以：

1. 构建和管理你的用户界面
2. 捕获触摸和基于移动的事件
3. 呈现文字和web内容
4. 优化你的多任务程序
5. 创建定制的用户界面元素

应用程序可以通过三种方式使用UIKit创建界面

1. 在用户界面工具（interface Buidler）从对象库里拖拽窗口，视图或者其他的对象使用
2. 用代码创建
3. 通过继承 UIView 类或间接继承 UIView 类实现自定义用户界面

UIResponder 类是最大分支的根类，

UIResponder 为处理响应事件和响应链定义了界面和默认行为。

当用户用手指滚动列表或者在虚拟键盘上输入时，UIKit 就生成时间传送给 UIResponder 响应链，直到链中有对象处理这个事件。

相应的核心对象，比如：UIApplication, UIWindow, UIView 都直接或间接的从UIResponder继承。


## 3. Media

### 1. Core Graphics

Core Graphics 框架帮助你创建图形

高质量的图形对于所有的 iOS 应用程序都是很重要的。

在 iOS 中最简单且最快捷的创建图形的方式是使用 UIKit 框架提供的基于预渲染图形的视图和控件，然后让UIKit和iOS完成绘制。

但是当你需要创建复杂的图形时，Core Graphics 则提供了更底层的库来帮助你。

使用Core Graphics可以：

1. 创建基于路径的绘图
2. 抗锯齿渲染
3. 添加梯度、图片和颜色
4. Use coordinate-space transformations.
5. 创建、显示和分析PDF文档

### 2. OpenGL ES

OpenGL ES 框架提供2D和3D绘图工具
OpenGL ES 支持2D和3D绘图，Apple 的 OpenGL ES 实现通过硬件提供了高速的全屏游戏式的应用程序。

使用OpenGL ES可以：

1. 创建2D和3D图形
2. 创建更复杂的图形，比如数据虚拟化、模拟飞行，或者视频游戏
3. 访问底层图形设备

### 3. Core Animation

Core Animation 允许你创建高级的动画和虚拟效果

UIKit 提供建立在 Core Animation 之上的动画。

如果你需要比 UIKit 能力更高级的功能，可以直接使用 Core Animation。

Core Animation 接口包含在 Quartz Core 框架里。

使用 Core Animation 可以创建嵌套的对象，并且可以对它们操作、旋转、缩放和转换。

使用 Core animation，你可以创建动态的用户界面而不用使用更底层的图形API，如OpenGL ES。

使用Core Animation可以：

1. 创建定制动画
2. 添加定时函数和图形
3. 支持帧动画
4. Specify graphical layout constraints.
5. Group multiple-layer changes into anatomic update.


## 4. Core Services

### 1. Core Data

Core Data 框架管着理应用程序数据模型

Core Data 提供对象的管理，使用 Core Data，你可以创建模型对象，并管理这些对象。

你管理着这些对象间的联系并修改数据。

Core Data 提供的内建 SQLlite 技术可以高效的管理数据。

使用 Core Data 可以：

1. 在库里存储和接收对象
2. 提供基本的undo/redo
3. 自动验证属性值
4. 过滤、分组和优化内存中的数据
5. 用[NSFetchedResultsController]管理表视图中的结果
6. 支持基于文档的应用程序

### 2. Foundation

Foundation 框架为所有的应用程序提供基本系统服务

你的应用程序，UIKit和其它的框架都是建立在Foundation框架上面的。

Foundation 框架是用 Object-C 对 Core Foundation 框架里许多特性的封装。

使用Foundation可以:

1. 创建和管理集合，比如数组和字典
2. 访问存储在应用程序里的图片和其它资源
3. 创建和管理字符串
4. 提交和接收通知
5. 创建日期和时间对象
6. 自动发现IP网络上的设备
7. 操作URL流
8. 执行异步代码

将 Foundation 框架中的类进行逻辑分类如下：

#### 1. 值对象 Value Objects

#### 2. 字符串 strings

#### 3. 集合 Collections

数组

字典

枚举器

#### 4. Predicate

#### 5. 通知 Notifications

#### 6. 归档和序列化 Archiving and Serialization

#### 7. Objective-C 语言服务 Objective-C Language Services

#### 8. 操作系统服务 Operating-System Services

##### 1. 文件系统 File System

##### 2. URL

##### 3. 进程间通讯 Interprocess Communication

这个范畴中的大部分类代表不同的系统端口、套接字和名字服务器，对实现底层的IPC很有用。

NSPipe代表一个BSD管道，即一种进程间的单向通讯通道。   

##### 4. 线程和子任务 Locking/Threading

NSThread 类使您可以创建多线程的程序

各种锁（lock）类则为彼此竞争的线程在访问进程资源时提供各种控制机制。

通过 NSTask，您的程序可以分出一个子进程来执行其它工作或进行进度监控。



#### 6. 表达式和条件判断





## 5. Core OS













