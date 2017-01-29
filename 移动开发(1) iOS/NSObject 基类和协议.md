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

# 内省 Introspection

1. 内省是对象揭示自己作为一个运行时对象的详细信息的一种能力. 这些信息包括: 对象在继承树上的位置, 对象是否遵循特定的协议, 对象是否可以响应特定的消息
2. NSObject 协议和类定义了很多内省方法, 用于查询运行时信息, 以便根据对象的特征进行识别
3. 内省的使用有助于避免错误地进行消息派发, 错误地假设对象相等以及类似的问题, 增强程序的健壮性
4. hash 方法和 isEqual: 方法不是严格的内省方法, 并不向运行环境查询对象信息, 而是依赖于具体类的比较逻辑, 均在 NSObject 协议中声明
5. hash 方法的实现必须返回一个整型数, 作为哈希表结构中的表地址. 两个对象相等意味着它们有相同的哈希值.
6. 如果对象可能被包含在像 NSSet 这样的集合中, 则需要定义 hash 方法, 并确保该方法在两个对象相等的时候返回相同的哈希值
7. NSObject 类中缺省的 isEqual: 方法的实现只是简单地检查指针是否相等
8. 如果您正在创建子类, 则可能需要重载 isEqual: 方法, 以进一步检查对象是否相等. 子类可能定义额外的属性, 当两个实例被认为相等时, 属性的值应相同

```
class				// 返回代表类的 Class 对象, 可用于得到正确的类消息接收者
superclass			// 返回代表超类的 Class 对象
isKindOfClass		// 返回接收者是否为指定类或其继承类的实例, 用于检查对象的类从属关系, 知道是否可以向该对象发送其父类的一系列消息
isMemberOfClass		// 返回接收者是否为指定类的实例
respondsToSelector	// 指定对象是否实现指定方法, 用于在将消息或消息集合发送给某些潜在的匿名对象之前, 确定它们是否可以正确地进行响应, 避免由不能识别的选择器引起的运行时例外
conformsToProtocol	// 指定对象是否遵循指定的正式协议(即该对象采纳该协议, 且实现该协议所有的方法)
hash				//
isEqual: 			// 将接收消息的对象和通过参数传入的对象进行比较, 用于在运行时决定应该对对象做些什么

while (id anObject = [objectEnumerator nextObject]) {
    if ([self class] == [anObject superclass]) {	// 当前对象是指定对象的父类
        // do something appropriate ...
    }
}

if ([item isKindOfClass:[NSData class]]) {
    const unsigned	char *bytes = [item bytes];		// 安全地调用父类方法
    unsigned int	length = [item length];
    // do something appropriate ...
}

- (void)doCommandBySelector:(SEL)aSelector {
    if ([self respondsToSelector:aSelector]) {
        [self performSelector:aSelector withObject:nil];
    }
	else {
    	[_client doCommandBySelector:aSelector];
    }
}

if (![(id)testObject conformsToProtocol:@protocol(NSMenuItem)]) {
    NSLog(@"Custom MenuItem '%@' not loaded, it must conform to the 'NSMenuItem' protocol.\n", [testObject class]);
    [testObject release];
    testObject = nil;
}

- (void)saveDefaults {
    NSDictionary	*prefs = [self preferences];		// 获取当前配置

    if (![origValues isEqual:prefs])					// 是否保存被修改了的预置信息
        [Preferences savePreferencesToDefaults:prefs];	// 更新配置
}

- (BOOL)isEqual:(id)other {								// 重载 isEqual: 方法
    if (other == self)									// 检查指针的相等性
        return YES;
    if (!other || ![other isKindOfClass:[self class]])	// 类的相等性
        return NO;
    return [self isEqualToWidget:other];				// 对象的相等性
}   

- (BOOL)isEqualToWidget:(MyWidget *)aWidget {			// 需对传入的对象进行强制类型检查
    if (self == aWidget)
        return YES;   
    if (![(id)[self name] isEqual:[aWidget name]])		// 实例变量的相等性
        return NO;
    if (![[self data] isEqualToData:[aWidget data]])
        return NO;
    return YES;
}
```

# 键值编码

1. 键值编码是一个用于间接访问对象属性的机制，使用该机制不需要调用存取方法和变量实例就可访问对象属性。
2. 键值编码方法在OC非正式协议（类目）NSKeyValueCoding中被声明，默认的实现方法由NSObject提供。
3. 键值编码支持带有对象值的属性，同时也支持纯数值类型和结构。非对象参数和返回类型会被识别并自动封装/解封。

# 键值观察 observe

1. 键值观察是一种使对象获取其他对象特定属性变化的通知机制
2. 控制器层的绑定技术就是严重依赖键值观察获得模型层和控制器层的变化通知的。对于不依赖控制器层类的应用程序，键值观察提供了一种简化的方法来实现检查器并更新用户界面值。
3. 与 NSNotification 不同，键值观察并没有所谓的中心对象来为所有观察者提供变化通知。取而代之的，当有变化发生时，通知被直接发送至处于观察状态的对象。
4. NSObject提供这种基础的键值观察实现方法，你几乎不用重写该方法。
5. 你可以观察任意对象属性，包括简单属性，对一或是对多关系。对多关系的观察者将会被告知发生变化的类型-也就是任意发生变化的对象。键值观察为所有对象提供自动观察兼容性。
6. 你可以通过禁用自动观察通知并实现手动通知来筛选通知。

# 注册观察者

为了正确接收属性的变更通知，观察者必须首先发送一个addObserver:forKeyPath:options:context:消息至被观察对象，用以传送观察对象和需要观察的属性的关键路径，以便与其注册。
选项参数指定了发送变更通知时提供给观察者的信息。使用NSKeyValueObservingOptionOld选项可以将初始对象值以变更字典中的一个项的形式提供给观察者。指定NSKeyValueObservingOptionNew选项可以将新的值以一个项的形式添加至变更字典。你可以使用逐位“|”这两个常量来指定接受上述两种类型的值。

# 参考

1. [Objective-C高级编程——KVC（一）](http://blog.csdn.net/chenyufeng1991/article/details/49308585)
2. [Objective-C高级编程——KVO（一）](http://blog.csdn.net/chenyufeng1991/article/details/49310241)
