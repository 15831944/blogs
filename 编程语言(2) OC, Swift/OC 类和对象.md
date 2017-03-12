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


1. 类对象(工厂): 类不只作为类型的定义, 类本身也作为一个对象存在, 叫做类对象, 占用内存空间, 在编译的时候自动生成, 每个类只有一个类对象(或动态加载在执行文件以外的别的文件中放置的类的代码), 用来描述某个类的定义, 包括 OC 对象的方法调度表，实现了什么协议等等, 包含的这些信息就是 OC 动态能力的根源, OC 有类方法, 但没有类变量的概念

2. C++ 不存在类对象, 类只作为类型的定义

类对象是 Class 类型, id 类型可以表示任意对象, 因此也可表示类对象, 使用 class 方法返回类对象


# isa 指针

1. isa 指针是对象的隐藏数据, 也是对象的第一个实例变量, 指向对象的类对象, 每个对象都会继承这个保护成员, 从根对象获得, 在对象创建时不会被初始化, 用于确定对象所属的类(是一个的关系, 表明子类是一个父类)

# 合成对象 Composite Object

1. 定义一个类包含其他类的一个或多个对象(相当于 C++ 的类的组合, 有一个的关系), 初始化合成对象时, 应初始化其包含的对象

# 参考

1. [Objective-C高级编程——KVC（一）](http://blog.csdn.net/chenyufeng1991/article/details/49308585)
2. [Objective-C高级编程——KVO（一）](http://blog.csdn.net/chenyufeng1991/article/details/49310241)
