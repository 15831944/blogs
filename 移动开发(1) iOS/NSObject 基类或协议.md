# NSObject 概述

1. NSObject 基类是大部分 Objective-C 类的根类, 没有父类
2. NSObject 协议指定了根类必须实现的接口
3. 继承 NSObject 的类可以访问 Objective-C 运行时系统的基本接口, 获得运行时的能力

# NSObject 根类的主要方法

## 1. 对象的初始化

| method        | describe      |
| ------------- | ------------- |
| alloc         | 对象的内存分配  |
| allocWithZone | 对象的内存分配  |
| init          | 对象初始化      |
| new           | 内存分配和初始化 |
| copy          | 内存拷贝        |
| copyWithZone  | 内存拷贝        |

## 2. 对象的保持和清理

| method      | describe                  |
| ----------- | ------------------------- |
| retain      | 增加对象的保持次数           |
| release     | 减少对象的保持次数           |
| autorelease | 减少对象的保持次数, 以推迟方式 |
| retainCount | 返回对当前的保持次数         |
| dealloc     | 由需要释放对象的实例变量以及释放动态分配的内存的类实现 |

## 3. 对象的内省和比较

内省方法: 查询对象的运行时信息, 找出对象在类层次中的位置, 确定对象是否实现特定的方法, 测试对象是否遵循某种协议

| method                      | describe                                |
| --------------------------- | --------------------------------------- |
| superclass                  | 类方法, 以 Class 对象的形式返回接收者的父类   |
| class                       | 对象方法, 以 Class 对象的形式返回接收者的类   |
| isKindOfClass:              | 确定对象属于哪个类                         |
| isMemberOfClass:            | 测试接收者是否为指定类的实例                 |
| isSubclassOfClass:          | 类方法, 用于测试类的继承性                   |
| respondsToSelector:         | 测试接收者是否实现由选择器参数标识的方法       |
| instancesRespondToSelector: | 类方法, 用于测试给定类的实例是否实现指定的方法  |
| conformsToProtocol:         | 用于测试接收者(对象或类)是否遵循给定的协议     |
| isEqual:                    | 用于对象的比较                             |
| hash                        | 用于对象的比较                             |
| description                 | 允许对象返回一个内容描述字符串, 其输出经常用于调试(“printobject”命令)，以及在格式化字符串中和“%@”指示符一起表示对象 |

## 4. 对象的编码和解码

作为归档过程的一部分

| method                      | describe                                                      |
| --------------------------- | ------------------------------------------------------------- |
| encodeWithCoder:            | NSCoding 协议仅有的方法, 使对象可以对其实例变量进行编码              |
| initWithCoder:              | NSCoding 协议仅有的方法, 使对象可以根据解码过的实例变量对自身进行初始化 |
| classForCoder:              |  |
| replacementObjectForCoder:  |  |
| awakeAfterUsingCoder:       |  |

## 5. 消息的转发和派发

| method                      | describe                                                            |
| --------------------------- | ------------------------------------------------------------------- |
| forwardInvocation:          | 允许一个对象将消息转发给另一个对象                                        |
| performSelector*            | 允许你延迟后派发指定消息，而且可以将消息(同步或异步的消息)从辅助线程派发到主线程 |
