# 运行时系统

1. 运行时系统用来执行编译好的代码, 类似于 OC 的操作系统, 负责完成对象生成, 释放对象时的内存管理, 为发来的消息查找对应的处理方法等
2. 程序无法直接使用运行时系统提供的功能, 根类方法提供了运行时系统的基本功能, 相当于运行时系统的接口, 继承了 NSObject 的所有类都可以自由地使用运行时系统的功能
3. 实例对象所属的类是类(class), 类对象所属的类是元类(metaclass)

# NSObject 基类

1. NSObject 基类是大部分 Objective-C 类的根类, 没有父类, 对象的初始化或拷贝, 保持和释放, 内省, 比较, 归档等功能
2. NSObject 协议指定了根类必须实现的接口
3. 继承 NSObject 的类可以访问 Objective-C 运行时系统的基本接口, 获得运行时的能力, 消息转发功能
2. NSObject 基类定义在 NSObject.h 文件中, Foundation.h 文件中包含 NSObject.h

# 对象的复制

1. 浅拷贝(shallow copy): 只复制对象的指针(代入), 复制对象的指针及对象本身(浅拷贝), 使用浅拷贝将一个对象赋值给另一个对象时, 仅仅创建了另一个对这个对象的引用
2. 深拷贝(deep copy): 递归地复制对象的指针, 对象本身及其引用的资源(实例变量是对象则可 retain, 是资源则需申请新的内存), 创建对象的内容(引用的资源)的副本, 而不仅是这些对象的引用的副本
3. 浅拷贝和深拷贝结合: 只复制一部分实例变量, 其他则通过指针来访问
4. 局部性原理: 程序代码和数据访问都趋于集中在内存上距离靠近的位置, 实现高效的内存访问, 称为局部性原理, 它构成了虚拟内存和缓存的基础
5. 区域(Zone): 动态分配的堆通常会使用地址空间中很大一片内存, 出于局部性原理和虚拟内存管理的考虑, 在堆内设定多个区块, 叫做区域, 在新的运行时环境中不再常用, NSZone* 参数可设为 NULL
6. 对象是否可变并不影响其副本是否可变
7. 对象的实例变量是另一个对象时, 其设值发方法和取值方法可以使用该对象副本来防止对象的更改影响原始对象
8. 对 copy 特性的属性赋值时, 只能调用 copy 方法生成不可变副本, 不存在 mutableCopy 特性
9. NSObject 基类自己不采用 NSCopying 协议,  copy 方法实际使用 copyWithZone 方法生成新实例, 默认是浅拷贝, 可变版本同理
0. NSCopying 协议: 复制数据模型对象, 创建一个同类的新实例, 类似于解码, 将新实例的所有属性设值为与该对象属性相同的值

# 对象的相等性

具有相同 id 值, 也就是同一个指针指向的对象会被认为是相等的

1. NSObject 协议中声明了 hash 和 isEqual 方法, 进行具体类的比较
2. hash 方法: 实现必须返回一个整型数, 作为哈希表结构中的表地址, 两个对象相等意味着它们有相同的哈希值, 如果对象可能被包含在像 NSSet 这样的集合中, 则需要定义 hash 方法, 并确保该方法在两个对象相等的时候返回相同的哈希值
3. isEqual 方法: 将接收消息的对象和通过参数传入的对象进行比较, 用于在运行时决定应该对对象做些什么, NSObject 类中缺省的 isEqual: 方法的实现只是简单地检查指针是否相等, 子类的比较可能需要重载 isEqual: 方法, 以进一步检查对象是否相等, 子类可能定义额外的属性, 当两个实例被认为相等时, 属性的值应相同

# 对象的内省 Introspection

1. 内省是对象向运行环境查询自己作为一个运行时对象的详细信息的一种能力, 有助于避免错误地进行消息派发, 错误地假设对象相等问题, 增强程序的健壮性
2. NSObject 协议和类定义了很多内省方法, 可以查询对象在继承树上的位置, 是否遵循指定协议, 是否可以响应指定消息等

```
class						// 对象方法, 返回代表类的 Class 对象, 用于得到正确的消息接收者
superclass					// 类方法, 返回代表超类的 Class 对象
isKindOfClass				// 返回接收者是否为指定类或其继承类的实例, 用于检查对象的类从属关系, 知道是否可以向该对象发送其父类的一系列消息
isMemberOfClass				// 返回接收者是否为指定类的实例
respondsToSelector			// 指定对象是否实现指定方法, 用于在将消息或消息集合发送给某些潜在的匿名对象之前, 确定它们是否可以正确地进行响应, 避免由不能识别的选择器引起的运行时异常
instancesRespondToSelector:	// 类方法, 用于测试给定类的实例是否实现指定的方法
conformsToProtocol			// 指定对象是否遵循指定的正式协议(即该对象采纳该协议, 且实现该协议所有的方法)
description					// 允许对象返回一个内容描述字符串, 其输出经常用于调试(“printobject”命令)，以及在格式化字符串中和“%@”指示符一起表示对象
```

# 多态 Polymorphism

1. 多态: 不同类之间或子类和父类之间可以定义名称相同的方法(接收者不同, 但发送相同消息), 程序在运行时, 先根据 isa 指针确定对象所属的类型(动态类型), 再根据接收者类型查找和调用该对象的方法(动态绑定), 即同一操作作用于不同的类的实例将产生不同的执行结果, C++ 和 Java 的多态都只能基于类层次结构(继承关系)
2. 动态类型(Dynamic Typing): 对象在显式声明时, 其类型是静态的, 当将一个类实例赋给 id 类型的变量时, 或作为参数传递给一个函数时, 动态类型能够确定变量或参数当前的类型
3. 动态绑定(Dynamic Binding): 如果函数的参数和返回类型是动态类型, 则有可能查找不到正确的方法
4. 动态加载: 运行时为程序加载新的模块

1. 静态类型检测: 若对象类型和消息类型均显式声明但不匹配, 编译时执行静态类型检查, 类型不同会触发编译时错误
2. 动态类型检查: 若对象类型未知(id 类型), 消息类型已知, 且类型不匹配, 动态类型检查则会触发运行时错误

1. 方法覆写(override): 方法的名称, 参数和返回值类型均相同, 使用 super 将调用(直系)父类方法, 使用 self 将调用当前类方法(相当于递归调用), 使用父类指针指向子类对象, 将调用子类的重写的方法, 在分类中覆写方法会导致原方法无法访问
2. 方法重载(overload): 方法名相同的函数互为重载, OC 不支持方法重载, 因为方法的返回值类型和参数类型需要是静态类型, 才能查找到正确的方法

# 消息发送和转发 Message Sending and Forwarding

通过 SEL 类型来指定要执行的方法, 这就是 OC 发送消息的方式, 以实现 OC 的动态性

| method                      | describe                                                            |
| --------------------------- | ------------------------------------------------------------------- |
| forwardInvocation:          | 允许一个对象将消息转发给另一个对象                                        |
| performSelector*            | 允许你延迟后派发指定消息，而且可以将消息(同步或异步的消息)从辅助线程派发到主线程 |

1. 动态绑定机制: 使用对象进行方法调用是一个消息发送的过程, 所要调用的方法直到运行时才能确定
1. 消息的发送者: 可以是界面对象, 例如方法中的 sender 参数
2. 消息的接收者: 请求一个类或实例来执行某个操作时, 就是在向它发送一条消息, 方法执行的上下文环境就是接收到消息的对象
2. 消息的组成: 对象是消息的接受者, 方法名是选择子(selector), 方法名及参数是消息
3. 消息的本质: 编译器看到消息后, 会将其转为一条标准的 C 语言函数调用
4. 方法的查找: objectMessageSend 会按选择子的名称(键)搜索消息接收者类中的方法列表, 如果能找到与选择子名称相符的方法, 则跳转至其实现代码, 如果找不到, 就沿着起继承体系向上查找父类方法, 如果最终还是没有找到相符的方法, 则执行消息转发

```
id returnValue = [object msg: parameter];		// OC 函数形式: object 是消息接收者, msg 是选择子, parameter 是参数
void objectMessageSend(id self, SEL cmd, ...);	//  C 函数形式: self 是消息接收者, cmd 是选择子, 可变参数是消息的参数
```

1. 对象无法处理的接收到的消息时会启动消息转发机制, 通过在 NSObject 的子类中覆写其方法处理该未知消息, 转发流程中的接收者在每一步中均有机会处理消息, 步骤越往后处理消息的代价越大
2. 如果直到 NSObject, 继承体系中的其它类都无法处理这个消息转发, 就会由 NSObject 调用该方法, 并在该方法中调用 doesNotRecognizeSelector, 以抛出异常
3. 消息发送和转发流程: 动态方法解析, 快速转发路径, 快速转发路径

# 动态方法解析 Dynamic/Lazy Method Resolution

1. 向当前类发送以下消息(由基类定义), 如果返回 YES, 则系统认为请求的方法已经加入到了, 则会重新发送消息, 否则进行下一步

```
resolveInstanceMethod:	// 实例方法
resolveClassMethod:		// 类方法

+ (BOOL)resolveInstanceMethod:(SEL)sel {
    NSString	*selStr = NSStringFromSelector(sel);

	/* 当前消息接受者可以处理该方法 */
    if ([selStr isEqualToString:@"name"]) {
        class_addMethod(self, sel, (IMP)nameGetter, "@@:");
        return YES;
    }
	/* 动态地给消息增加方法 */
    if ([selStr isEqualToString:@"setName:"]) {
        class_addMethod(self, sel, (IMP)nameSetter, "v@:@");
        return YES;
    }
	/* 沿消息接受者的继承链, 判断父类是否可以处理该方法 */
    return [super resolveInstanceMethod:sel];
 }

 void nameSetter(id self, SEL cmd, id value) {
    NSString	*fullName = value;
    NSArray		*nameArray = [fullName componentsSeparatedByString:@" "];
    PersonModel	*model = (PersonModel *)self;

    model.firstName = nameArray[0];
    model.lastName  = nameArray[1];
}

id nameGetter(id self, SEL cmd) {
    PersonModel		*model = (PersonModel *)self;
    NSMutableString	*name = [[NSMutableString alloc] init];

    if (nil != model.firstName) {
        [name appendString:model.firstName];
        [name appendString:@" "];
    }
    if (nil != model.lastName) {
        [name appendString:model.lastName];
    }
    return name;
}
```

# 快速转发路径 Fast Forwarding Path

1. 若果当前 target 实现了 forwardingTargetForSelector: 方法, 则调用此方法. 查找是否有其它的接收者, 如果此方法返回除 nil 和 self 的其他对象, 则向返回对象重新发送消息, 否则进行下一步

```

- (id)forwardingTargetForSelector:(SEL)aSelector {
    NSString	*selStr = NSStringFromSelector(aSelector);

    if ([selStr isEqualToString:@"companyName"]) {
        return self.companyModel;
    }
	else{
        return [super forwardingTargetForSelector:aSelector];
    }
}
```

# 慢速转发路径 Normal Forwarding Path

1. 首先 runtime 发送 methodSignatureForSelector: 消息查看 Selector 对应的方法签名, 即参数与返回值的类型信息,
1. 如果有方法签名返回, runtime 则根据方法签名创建描述该消息的 NSInvocation, 向当前对象发送 forwardInvocation: 消息, 以创建的 NSInvocation 对象作为参数,
3. 若 methodSignatureForSelector: 无方法签名返回, 则向当前对象发送 doesNotRecognizeSelector: 消息, 程序抛出异常退出

这个方法实现得很简单。只需要改变调用目标，使消息在新目标上得以调用即可。不过，如果采用这种方式，实现的效果与第二步的消息转发是一致的。
所以比较有用的实现方式是：先以某种方式改变消息内容，比如追加另外一个参数，或者改换选择子，等等

```
- (NSMethodSignature *)methodSignatureForSelector:(SEL)aSelector {                          
    NSMethodSignature	*sig = nil;
    NSString			*selStr = NSStringFromSelector(aSelector);

    if ([selStr isEqualToString:@"deptName"]) {
        sig = [self.companyModel methodSignatureForSelector:@selector(deptName:)];
    }else{
        sig = [super methodSignatureForSelector:aSelector];
    }
    return sig;	// 返回 forwardInvocation 方法的参数 anInvocation 中的 methodSignature
}

- (void)forwardInvocation:(NSInvocation *)anInvocation {
    NSString	*selStr = NSStringFromSelector(anInvocation.selector);

    if ([selStr isEqualToString:@"deptName"]) {
        [anInvocation setTarget:self.companyModel];
        [anInvocation setSelector:@selector(deptName:)];

        BOOL hasCompanyName = YES;
        //第一个和第一个参数是target和sel
        [anInvocation setArgument:&hasCompanyName atIndex:2];
        [anInvocation retainArguments];
        [anInvocation invoke];
    }
	else {
        [super forwardInvocation:anInvocation];
    }
}
```

# 目标-动作模式 targer-action paradigm

1. 动作方法(action method)
2. 输出口(outlet)
