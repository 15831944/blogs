# 对象 Objects

1. 对象的本质是结构, 对象的实例变量是结构的成员, 继承自父类的实例变量和对象自身的实例变量将组成新的结构
2. 对象的引用本质是指向结构的指针, 因此才可以用"->"运算符访问以 `@public` 修饰的实例变量(不推荐)
3. 对象封装的作用是使具体实现不可见，只向用户提供方法调用的接口, 有利于更好的对事物进行抽象, 原则是不能在类外直接访问实例变量, 而是需要使用访问器方法
4. 对象是引用类型: 使用 alloc, init 方法或 new 方法实例化对象, 对象均通过对象指针进行引用, 即传址调用
5. OC 具有根类 NSObject, 定义了对象的基本功能, 新建的所有类都继承自 NSObject, Cocoa 环境还有一个根类 NSProxy
6. iOS 中有两种对象, OC 对象(例如 id 类型)和 Core Foundation 对象(例如 void* 类型), 后者不在 ARC 管理范畴内

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


1. 类对象(工厂): 类不只作为类型的定义, 类本身也作为一个对象存在, 叫做类对象, 占用内存空间, 在编译的时候自动生成, 每个类只有一个类对象(或动态加载在执行文件以外的别的文件中放置的类的代码), 用来描述某个类的定义, 包括 OC 对象的方法调度表，实现了什么协议等等, 包含的这些信息就是 OC 动态能力的根源, OC 有类方法, 但没有类变量的概念

2. C++ 不存在类对象, 类只作为类型的定义

类对象是 Class 类型, id 类型可以表示任意对象, 因此也可表示类对象, 使用 class 方法返回类对象

# 抽象类 Abstract Class

1. 抽象类自身不生成实例, 给所有继承它的子类提供统一的接口

# 类簇 Class Cluster

1. 类簇: 类簇就是定义相同的接口并提供相同功能的一组类(公共类)的集合, 基于 Abstract Factory design pattern 设计模式
2. 公共类(public class): 仅公开接口的抽象类称为类簇的公共类
3. 私有子类: 各个具体类的接口由公共类的接口抽象化, 并被隐藏在类的内部, 不能被直接使用, 一般会被作为公共类的子类实现, 这样的具体类称为私有子类
4. 类簇的实现机制: 定义公共类时, 实际上被生成的是隐藏在类簇中的某个私有子类的实例, 所使用的初始化方法决定返回哪种实例, 初始化方法有时会返回和接收者不同的对象
5. Foundation 框架的基本数据类型对象使用类簇实现, 使用范畴扩展 Foundation 框架的公共类的功能, 可以被私有子类所继承
6. 基本方法(primitive method): 私有子类中不同的实现细节隐藏在基本方法中

# isa 指针

1. isa 指针是对象的隐藏数据, 也是对象的第一个实例变量, 指向对象的类对象, 每个对象都会继承这个保护成员, 从 NSObject 根对象获得, 是 NSObject 唯一的实例变量, 在对象创建时不会被初始化, 用于确定对象所属的类(是一个的关系, 表明子类是一个父类), 子类不可修改 isa 的值, 也不能直接访问 isa, 而要通过 class 方法, 返回类对象

# 合成对象 Composite Object

1. 定义一个类包含其他类的一个或多个对象(相当于 C++ 的类的组合, 有一个的关系), 初始化合成对象时, 应初始化其包含的对象

# 参考

1. [Objective-C高级编程——KVC（一）](http://blog.csdn.net/chenyufeng1991/article/details/49308585)
2. [Objective-C高级编程——KVO（一）](http://blog.csdn.net/chenyufeng1991/article/details/49310241)
