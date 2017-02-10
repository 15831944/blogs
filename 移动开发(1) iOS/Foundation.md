# Foundation

1. Foundation 框架为所有的应用程序提供基本系统服务, 应用程序, UIKit 和其它的框架都建立在Foundation框架上
2. Foundation 框架是用 Object-C 对 Core Foundation 框架里许多特性的封装
3. Foundation 框架对于 macOS 和 iOS 两个平台均适用

Foundation 的功能

1. 创建和管理集合，比如数组和字典
2. 访问存储在应用程序里的图片和其它资源
3. 创建和管理字符串
4. 提交和接收通知
5. 创建日期和时间对象
6. 自动发现IP网络上的设备
7. 操作URL流
8. 执行异步代码

Foundation 的内容

1. 值对象 Value Objects
2. XML
3. 字符串 Strings
4. 集合 Collections
5. 谓词 Predicates
6. 操作系统服务 Operating-System Services
7. 文件系统 File System
8. URL
9. 进程间通信 Interprocess Communication
1. 线程和子任务 Locking/Threading
2. 消息 Notifications
3. 归档和序列化 archiving and Serialization
4. OC语言服务 Objective-C Language Services
5. 脚本 Scripting
6. 分布式对象 Distributed Objects

# 值对象 Value

1. NSValue
2. NSNumber 类会依据基本数据的类型创建并初始化对象
3. NSDecimalNumber

# 字符串 String

NSString

1. NSString 对字符串的各种操作往往返回一个新建的字符串, 而不是修改原字符串
2. C 风格的字符串称为 UTF8String, 由 char 字符组成, NSString 对象由 unichar 字符(Unicode 标准的多字节字符)组成
3. 范围 Range 的实现为结构体, 成员为位置和长度
4. 网络路径和本地路径虽然都是 NSURL 类, 但获取的方法不同, 不能混用
5. 字符串比较较为复杂, 涉及读音等
6. 使用字符串字字面值定义和初始化对象在栈中, 不需要手动管理内存, 使用 alloc 方法初始化在堆中, 需要人工释放内存

NSMutableString

1. NSMutableString 在实例化可变字符串时指定长度(Capacity)可以提升性能
2. 用 NSString 对象初始化 NSMutableString 对象会报类型不匹配
3. 对字符串的操作将修改原字符串, 返回的是引用
4. NSMutableString 继承自 NSString, 即可变字符串可以使用普通字符串的方法
5. 字符串替换只能按范围进行替换

NSConstantString

NSAttributedString

1. 属性字符串

# 集合 Collection

集合数据类型包括: 数组, 字典

NSArray

1. 数组的元素只能是对象指针, 由于都是指针类型, 同一个数组可以存储不同类型的对象, 数组的内存空间依然连续
2. 不可变数组在实例化时必须指定长度, 声明后不能修改长度
3. 对数组进行快速枚举需要数组元素类型一致, 对于不一致元素会打印其地址, 因为依然是对象
4. 数组打印输出时为小括号

NSMultableArray

1. 可以实例化空的可变数组
2. 下标访问越界会报运行时错误

NSDictionary

1. 字典对象的存储内存空间不连续, 使用键值对(KVC, key value coding, 键值编码)进行访问, 是无序的
2. 添加或删除数组或字典的元素时，count 会随之变化
3. 对象释放后，每个值对象都会释放, MRC 需要注意内存管理, ARC 则不用
4. 字典打印输出时为大括号

NSMutbaleDictionary

枚举器

5. 可以使用枚举器遍历数组, 字典等

# 操作系统服务

1. NSTimer 倒计时

# 进程间通信

1. 代表不同的系统端口, 套接字, 名字服务器，用于实现底层的 IPC
2. NSPipe 代表一个 BSD 管道，即一种进程间的单向通讯通道
