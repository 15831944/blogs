# Framework

1. 框架: 框架就是一组由许多类, 方法, 函数和文档按照一定的逻辑组织起来的集合, 本质是一个目录, 包含: 共享库及其头文件, 图片和声音等资源文件
2. 框架的引用: 根据项目模板，相关的框架会被自动引入, 还可以手动添加, 将共享库添加到项目中, 即可使用该框架提供的方法和函数
3. 举例: Foundation, UIKit, Core Graphics

# Cocoa

1. Cocoa 是在 Mac OS X 系统上原生的一个编译环境, 支持多种编程语言, 是面向对象的接口
2. Cocoa 包含2个框架(类库): Foundation, AppKit, 还有 Core Data 第三方框架
3. Cocoa 程序是由一些对象组成, 而这些对象的类最后都是继承于它们的根类: NSObject, 而且都基于 OC 运行环境
4. AppKit 框架是 Mac OS X 上的用户图形包, 类名以 NS 开头

# Cocoa Touch

1. Cocoa Touch 是 Cocoa 的子类, 用于 iOS 设备
2. Cocoa Touch 包含2个框架(类库): Foundation, UIKit, 还有 Core Data 第三方框架
3. Cocoa Touch 不支持垃圾回收机制, 必须在代码里管理好内存
4. Foundation 框架提供了一系列基础数据类型, 以及枚举, 容器的支持, 类名以 NS 开头
5. UIKit 框架是 iOS 上的用户图形包, 类名以 UI 开头

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

# Cocoa 对象的生命周期

1. 对象的声明周期: 对象可以被创建(分配内存和初始化), 拷贝, 保持, 归档, 释放(release), 销毁(dealloc)

## 对象的管理机制

2. 对象的清理: OC 没有自动释放不再使用的对象的垃圾回收机制(开销大, 不灵活), 而是通过引用计数, 选择一种主动的, 策略驱动的例程来保持对象, 并在不再需要的时候进行清理
3. 对象的保持数: 一个 Cocoa 对象被创建后, 其他对象向它发送消息, 需要关心该对象的持久性, 即对象的保持数, 是每个 Cocoa 对象都具有的一个隐藏的实例变量
4. 对象的创建: 对象的 isa 指针指向对象的类, 将对象集成到类层次的运行时视图中; 对象的保持数设置为1(假定对象的创建者关心其持久性)
5. 对象的释放: 向对象发送 release 消息时, NSObject 会减少它的保持数, 如果保持数从1下降到0, 对象就会被销毁(自动调用 dealloc 方法(不可人工调用), 释放实例变量和动态分配内存, 操作系统销毁对象本身, 回收对象占用的内存)
5. 对象的保持: 向对象发送 retain 消息, 保持数+1, 对象的创建者发消息, 将对象传递给客户对象, 该对象在客户对象的作用域内总是正当的, 客户对象可以向该对象发送消息或将其传递给其他对象, 对象的发送者(这里即对象的创建者)不应在客户对象仍然拥有该对象的引用时将它过早释放. 对象的创建者不需要保持该对象, 但客户对象需要保持该对象. 向对象发送 retain 消息, 表示希望拥有该对象, 并有责任释放该对象. 子对象不能保持它的父对象(父对象是该子对象的创建者，或者将该子对象作为实例变量持有的对象), 以避免循环引用.
6. 对象的拷贝: 多数子类都封装了某种数据采纳方法, 或遵循这种协议, 拷贝不仅对对象进行复制, 而且将保持数设置为1, 客户对象对拷贝过来的对象是新的且唯一的拥有者, 可以修改该对象而无须考虑其原始对象, 对于可变的值对象, 一般进行拷贝而非保持, 对于不可变对象, 拷贝和保持等价, 其实现方法也类似.
7. 自动释放机制: 对象的创建者并不知道何时可以安全地释放对象, 因为在调用堆栈中可能存在多个该对象的引用, 某些引用可能来自创建者不知道的对象, 如果对象的创建者释放了该对象, 而其它对象向这个已经被销毁的对象发送消息, 程序就会崩溃. 自动释放机制通过自动释放池(由 NSAutoreleasePool 类定义)来实现, 是一种延迟对象释放的机制.
8. 自动释放池: 自动释放池是位于显式定义的作用域内的一个对象集合, 该作用域被标志为最后释放. 即自动释放池维护了一个对象集合, 程序在自动释放池中执行时, 池中的对象不会被释放. 自动释放池可以嵌套. Application Kit 会自动建立一个自动释放池, 其作用域为为应用程序的事件周期.
9. 自动释放消息: 向一个对象发送 autorelease 消息时, Cocoa 会将该对象的一个引用放入到最新的自动释放池. 它仍然是个正当的对象, 自动释放池定义的作用域内的其它对象可以向它发送消息. 当程序执行到自动释放池作用域结束位置时, 自动释放池就会被释放, 池中的所有对象也就被释放.

## 对象的所有权策略

对象的所有权策略决定了如何使用对象的管理机制.

1. 创建对象(分配内存和初始化或使用 NSObject 的 new 便利方法): 拥有该对象, 需要负责该对象的释放(向对象发送 release 消息进行释放 或 autorelease 消息添加到自动释放池)
2. 拷贝对象: 拥有拷贝的对象，需要负责该拷贝的对象的释放
3. 保持对象: 部分拥有该对象, 需要在不再使用时释放该对象
4. 接收对象: 不拥有该对象, 不应该释放它(有少数例外)

对象所有权策略的例外

1. 如果通过类工厂方法创建对象(如 NSMutableArray arrayWithCapacity:), 则可以假定通过该方法接收到的对象已经被放到自动释放池了
2. 对于该对象, 不应人工将它释放, 如果需要保持该对象, 则依然应该保持(调用 retain 方法)它

不遵循对象所有权策略的后果

1. 没有释放自己创建, 拷贝或保持的对象, 会导致程序发生内存泄露
2. 向已经销毁(dealloc)的对象发送消息, 会导致程序崩溃, 且难以调试

1. 对象的归档: 归档是将组成一个面向对象程序的相关对象形成的网状结构(对象图)转化为一种可持久的形式(通常是一个文件), 该文件可以保存对象图中对象的标识和对象彼此之间的关系
2. 对象的解档: 在解档时, 可以通过这个档案重新构造出程序的对象图
3. NSCoding 协议: 为了参与归档和解档, 对象必须支持通过 NSCoder 类定义的方法对实例变量进行编码和解码, 为此, NSObject 类采用 NSCoding 协议

# Push 消息推送机制

# 类工厂方法

用于快速创建对象的类方法，我们称之为类工厂方法, 主要用于给对象分配并初始化内存

# 参考

1. [Cocoa 基本原理指南 内省介绍](http://mobile.51cto.com/iphone-274246.htm)
2. [Cocoa 基本原理指南 Cocoa 对象的生命周期](http://mobile.51cto.com/iphone-274253.htm)
