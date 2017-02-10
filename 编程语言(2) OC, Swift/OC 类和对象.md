# 对象 Objects

1. 对象的本质是结构, 对象的实例变量是结构的成员, 继承自父类的实例变量和对象自身的实例变量将组成新的结构
2. 对象的引用本质是指向结构的指针, 因此才可以用"->"运算符访问以 `@public` 修饰的实例变量(不推荐)
3. 对象封装的作用是使具体实现不可见，只向用户提供方法调用的接口, 有利于更好的对事物进行抽象, 原则是不能在类外直接访问实例变量, 而是需要使用访问器方法
4. 对象是引用类型: 使用 alloc, init 方法或 new 方法实例化对象, 对象均通过对象指针进行引用, 即传址调用
5. OC 具有根类 NSObject, 定义了对象的基本功能, 新建的所有类都继承自 NSObject, Cocoa 环境还有一个根类 NSProxy

```
struct objc_class {
    Class						isa;			//isa 指针, 指向元类对象(metaclass object)
    Class						super_class;	//指向父类的类对象
    const						char *name;
    long						version;
    long						info;
    long						instance_size;
    struct objc_ivar_list		*ivars;
    struct objc_method_list		**methodLists;	// 方法列表
    struct objc_cache			*cache;
    struct objc_protocol_list	*protocols;		// 协议列表
 }
 ```

# 类对象 Class Objects

1. 类对象(工厂)占用内存空间, 在编译的时候生成, 用来描述某个类的定义, 包括 OC 对象的方法调度表，实现了什么协议等等, 包含的这些信息就是 OC 动态能力的根源

# isa 指针

1. isa 指针是对象的隐藏数据, 也是对象的第一个实例变量, 指向对象的类对象, 每个对象都会继承这个保护成员, 从根对象获得, 在对象创建时不会被初始化, 用于确定对象所属的类(是一个的关系, 表明子类是一个父类)

# 合成对象 Composite Object

1. 定义一个类包含其他类的一个或多个对象(相当于 C++ 的类的组合, 有一个的关系), 初始化合成对象时, 应初始化其包含的对象

# NSObject 基类

1. NSObject 基类是大部分 Objective-C 类的根类, 没有父类, 对象的初始化或拷贝, 保持和释放, 内省, 比较, 归档等功能
2. NSObject 协议指定了根类必须实现的接口
3. 继承 NSObject 的类可以访问 Objective-C 运行时系统的基本接口, 获得运行时的能力, 消息转发功能
2. NSObject 基类定义在 NSObject.h 文件中, Foundation.h 文件中包含 NSObject.h

# 对象的复制

1. 浅拷贝: 将一个对象赋值给另一个对象时, 仅仅创建了另一个对这个对象的引用
2. 深拷贝: 创建对象的内容(引用的资源)的副本, 而不仅是这些对象的引用的副本
3. 对象是否可变并不影响其副本是否可变
4. 对象的实例变量是对象时, 其设值发方法和取值方法可以使用对象副本来防止对象的更改影响原始对象
5. 对 copy 特性的属性赋值时, 只能调用 copy 方法生成不可变副本, 不存在 mutableCopy 特性
6. NSObject 基类的 copy 方法默认是浅拷贝

# 对象的相等性

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

# 参考

1. [Objective-C高级编程——KVC（一）](http://blog.csdn.net/chenyufeng1991/article/details/49308585)
2. [Objective-C高级编程——KVO（一）](http://blog.csdn.net/chenyufeng1991/article/details/49310241)
