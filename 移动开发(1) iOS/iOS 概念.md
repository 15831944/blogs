# 框架 Framework

1. 框架就是一组从逻辑上组合在一起的类和例程, 本质是一个目录, 包含: 共享库及其头文件, 图片和声音等资源文件
2. 框架是由许多类, 方法, 函数和文档按照一定的逻辑组织起来的集合
2. 将共享库添加到项目中即可使用框架提供的方法和函数
3. 根据项目模板，相关的框架会被自动引入, 还可以手动添加
4. 举例: Foundation, UIKit, Core Graphics

# Cocoa

1. Cocoa 是在 Mac OS X 系统上原生的一个编译环境, 支持多种编程语言, 是面向对象的接口
2. 包含2个框架(类库): Foundation, AppKit, Core Data(第三方)
3. Cocoa 程序是由一些对象组成, 而这些对象的类最后都是继承于它们的根类: NSObject, 而且都基于 Objective-C 运行环境
4. AppKit 框架是 Mac OS X 上的用户图形包, 类名以NS开头

# Cocoa Touch

1. Cocoa Touch 是 Cocoa 的子类, 用于 iOS 设备
2. 包含2个框架(类库): Foundation, UIKit, Core Data(第三方)
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

# Push 消息推送机制



# ARC 内存管理机制



# GCD

1. GCD (Grand Central Dispatch) 是 Apple 开发的一个多核编程的解决方法, 在 Mac OS X 10.6 雪豹中首次推出, 随后被引入 iOS4.0
2. GCD 是一个替代诸如 NSThread, NSOperationQueue, NSInvocationOperation 等技术的很高效和强大的技术, 它看起来就像其它语言的闭包(Closure)一样, 但苹果把它叫做 blocks
