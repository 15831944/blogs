# 多态

1. 多态: 不同类之间或子类和父类之间可以定义名称相同的方法(接收者不同, 但发送相同消息), 程序在运行时, 先根据 isa 指针确定对象所属的类型(动态类型), 再根据接收者类型查找调用该对象的方法(动态绑定)
2. 动态类型: 对象在显式声明时, 其类型是静态的, 当将一个类实例赋给 id 类型的变量时, 或作为参数传递给一个函数时, 动态类型能够确定变量或参数当前的类型
3. 动态绑定: 如果函数的参数和返回类型是动态类型, 则有可能查找不到正确的方法
4. 动态加载: 运行时为程序加载新的模块
6. 动态解析方法: 
7. 静态类型检测: 若对象类型和消息类型均显式声明但不匹配, 编译时执行静态类型检查, 类型不同会触发编译时错误
8. 动态类型检查: 若对象类型未知(id 类型), 消息类型已知, 且类型不匹配, 动态类型检查则会触发运行时错误

1. 方法的覆写(override): 方法的名称, 参数和返回值类型均相同, 使用 super 将调用父类方法, 使用 self 将调用当前类方法(相当于递归调用), 使用父类指针指向子类对象, 将调用子类的重写的方法, 在分类中覆写方法会导致原方法无法访问
2. 方法重载(overload): 方法名相同的函数互为重载, OC 不支持方法重载, 因为方法的返回值类型和参数类型需要是静态类型, 才能查找到正确的方法

9. selector 是一个 SEL 类型的值, 使用 `@selector` 指令产生, 用于指定方法, 为指定方法生成一个 SEL 类型的值


# 消息发送

1. 动态绑定机制: 使用对象进行方法调用是一个消息发送的过程, 所要调用的方法直到运行期才能确定
1. 消息的发送者: 可以是界面对象, 即 方法中的 sender 参数, 20170125
2. 消息的接收者: 请求一个类或实例来执行某个操作时, 就是在向它发送一条消息, 方法执行的上下文环境就是接收到消息的对象
2. 消息的组成: 方法的调用者是消息的发送者, 对象是消息的接受者, 方法名是选择子(selector), 方法名及参数是消息
3. 消息的本质: 编译器看到消息后, 会将其转为一条标准的 C 语言函数调用
4. 方法的查找: objectMessageSend 会按选择子的名称(键)搜索消息接收者类中的方法列表, 如果能找到与选择子名称相符的方法, 则跳转至其实现代码, 如果找不到, 就沿着起继承体系向上查找父类方法, 如果最终还是没有找到相符的方法, 则执行消息转发

```
id returnValue = [someObject messageName: parameter];	// someObject 是消息的接收者, messageName 是选择子(selector)
void objectMessageSend (id self, SEL cmd, ...);			// self 是消息接受者, cmd 是选择子, 可变参数是消息的参数
```

# 尾部调用优化

1. 在方法内部调用另一个方法, 会把被调用方法的内部变量, 返回的地址等信息压入栈中, 以便调用结束后, 能够正确返回并处理
2. 如果方法A调用方法B, 方法B调用方法C, 方法C调用方法D, 等等, 就需要往栈中压入许多信息, 可能造成栈溢出
3. 为在一定程度上避免这种情况, 若是在方法内部的最后一条语句调用另外一个方法, 编译器会执行尾部调用优化
4. 尾部调用优化: 内层函数的返回地址即外层函数的调用位置? 外层函数的返回地址和局部变量不会再用到, 因此可不保留外层方法的信息, 直接用内层方法的调用记录取代外层方法的调用记录

# 消息转发 message forwarding

1. 当对象无法处理的接收到的消息时, 就会启动消息转发机制, 开发者可以在此过程中, 通过在 NSObject 的子类中覆写其方法, 处理未知的消息
2. 消息转发流程中, 接收者在每一步中均有机会处理消息, 步骤越往后处理消息的代价越大
3. 如果直到 NSObject, 继承体系中的其它类都无法处理这个消息转发, 就会由 NSObject 调用该方法, 并在该方法中调用 doesNotRecognizeSelector, 以抛出异常

消息转发流程

1. 动态方法解析 (dynamic/lazy method resolution): 向当前类发送 resolveInstanceMethod: (对于类方法则为 resolveClassMethod:)消息, 如果返回 YES, 则系统认为请求的方法已经加入到了, 则会重新发送消息
2. 快速转发路径 (fast forwarding path): 若果当前 target 实现了 forwardingTargetForSelector: 方法, 则调用此方法. 如果此方法返回除 nil 和 self 的其他对象, 则向返回对象重新发送消息
3. 慢速转发路径(normal forwarding path): 首先 runtime 发送 methodSignatureForSelector: 消息查看 Selector 对应的方法签名, 即参数与返回值的类型信息, 如果有方法签名返回, runtime 则根据方法签名创建描述该消息的 NSInvocation, 向当前对象发送 forwardInvocation: 消息, 以创建的 NSInvocation 对象作为参数, 若 methodSignatureForSelector: 无方法签名返回, 则向当前对象发送 doesNotRecognizeSelector: 消息, 程序抛出异常退出

```
/***************************************************
	消息转发第一步:
	若方法返回 YES, 则表示可以处理该消息, 否则进行下一步
***************************************************/
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

/***************************************************
	消息转发第二步:
	查找是否有其它的接收者, 返回一个可以处理该消息的对象, 若返回 nil, 则进行下一步
/**************************************************/
- (id)forwardingTargetForSelector:(SEL)aSelector {
    NSString	*selStr = NSStringFromSelector(aSelector);

    if ([selStr isEqualToString:@"companyName"]) {
        return self.companyModel;
    }
	else{
        return [super forwardingTargetForSelector:aSelector];
    }
}

/***************************************************
	消息转发第三步:
	这个方法实现得很简单。只需要改变调用目标，使消息在新目标上得以调用即可。不过，如果采用这种方式，实现的效果与第二步的消息转发是一致的。
	所以比较有用的实现方式是：先以某种方式改变消息内容，比如追加另外一个参数，或者改换选择子，等等
***************************************************/
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
