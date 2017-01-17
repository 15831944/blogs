# 消息发送和消息转发机制

1. 动态绑定机制: 使用对象进行方法调用是一个消息发送的过程, 所要调用的方法直到运行期才能确定
1. 消息的发送者:
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

# 参考

1. [Objective-C消息发送和消息转发机制](http://www.jianshu.com/p/01a19c64499c#)
1. [Objective-C消息发送和消息转发机制](http://www.jianshu.com/p/01a19c64499c)
1. [Objective-C 消息转发](http://blog.csdn.net/c395565746c/article/details/8507008)
