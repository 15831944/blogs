# 概述

1. OC 由 GNU 接管, 可以用于 Linux 嵌入式开发和服务器端开发, Foundation 框架和 UIKit 框架由 OC 语言编写
2. OC 具有封装, 继承, 多态, 重用; 不具有重载, 模版, 多继承, 垃圾回收机制(Cocoa Touch 不支持垃圾回收), 优势是其动态能力
3. OC 文件扩展名为".m", 与 C++ 混编的文件扩展名为 ".mm"
4. OC 名称空间是程序代码与所有的库, 框架和插件共享的

# 常量和变量 Constant and Variables

1. 全局变量: 定义全局变量将引起存储空间分配, extern 声明则不会, 不建议用 extern 声明的同时进行定义和初始化, 如果只有少数方法要访问某全局变量, 可以在使用前单独进行 extern 声明, 外部全局变量会破坏封装性, 全局变量名称习惯用 g 开头
2. 局部变量: 初始值为0或 nil, 方法返回即失效, 方法的参数属于局部变量
3. 静态局部变量: 初始值为0或 nil, 只能在声明该变量的方法内访问, 类的各实例调用该方法时访问的是同一个变量
4. 静态常量和静态变量的定义是通过特定类型加上 global 关键字

# 字面值 Literals

1. 使用 0, 0x 前缀分别表示八进制和十六进制字面值
2. 使用 f, l, u, ll 前缀分别表示不同数据类型的字面值
3. nil 是 id 类型, 本质是空指针类型, 声明时没有星号
4. 复合字面量: (type) {initialize list} 可以用于初始化结构或数组

# 数据类型

程序为了性能优化, 如存储大量数据的数组, 可使用 C 语言的内置的底层数据类型, 而不是 Foundation 框架提供的值对象

1. 基本数据类型: 包括 int, float, double, char 可用类型修饰符 long, long long, short, signed, unsigned 修饰
2. 布尔类型: 本质是预处理机制, 使用预定义的值 YES 和 NO
3. 枚举类型: 在冒号后面接数据类型
4. id 类型: 通用指针类型, 可以强制类型转换为指定类型的对象, 是多态和动态绑定的基础, 不能对 id 类型变量使用点运算符
5. instancetype 类型: 决定了基于上下文的返回类型, 被继承时, 可以正确返回子类, instancetype 类型的方法返回消息接受者的类型或其子类类型

# 操作符

1. 条件运算符: 从右向左结合, OC 支持非 ANSI 扩展的语句:` condition ? : expression`

# 控制流

1. switch 语句: 支持整型和字符型, 赋值和枚举需分别使用编译器选项 `-W Conversion` 和 `-Wswitch` 提供类型检查

# isa 指针 (是一个的关系)

1. isa 指针是对象的隐藏数据, 也是对象的第一个实例变量, 每个对象都会继承这个保护成员, 从根对象获得, 用于确定对象所属的类
2. isa 指针指向一个类对象(class object), 类对象占用内存空间, 在编译的时候生成, 用来描述某个类的定义
3. 类对象包含了 OC 对象的一些信息, 包括 OC 对象的方法调度表，实现了什么协议等等, 这个包含信息就是 OC 动态能力的根源

isa 指针类型的数据结构

```
struct objc_class {
    Class						isa;			//指向元类对象(metaclass object)
    Class						super_class;	//指向父类的类对象
    const						char *name;
    long						version;
    long						info;
    long						instance_size;
    struct objc_ivar_list		*ivars;
    struct objc_method_list		**methodLists;
    struct objc_cache			*cache;
    struct objc_protocol_list	*protocols;
 }
 ```

# 合成对象 composite object (有一个的关系)

1. 定义一个类包含其他类的一个或多个对象(相当于 C++ 的类的组合, 有一个的关系)
2. 初始化合成对象时, 应初始化其包含的对象

# 参考

书籍

1. 《Objective-C 程序设计》

教程

1. [征战Objective-C](http://www.imooc.com/learn/218)
2. [Objective-C 面向对象初体验](http://www.imooc.com/learn/373)

博客

1. [Cocoa 基本原理指南 内省介绍](http://mobile.51cto.com/iphone-274246.htm)
2. [Cocoa 基本原理指南 Cocoa 对象的生命周期](http://mobile.51cto.com/iphone-274253.htm)
3. [Objective-C消息发送和消息转发机制](http://www.jianshu.com/p/01a19c64499c#)
4. [Objective-C 消息转发](http://blog.csdn.net/c395565746c/article/details/8507008)
5. [iOS之#pragma mark用法](https://my.oschina.net/u/615517/blog/90282)

stackoverflow

1. [What is the significance of #pragma marks? Why do we need #pragma marks?](http://stackoverflow.com/questions/6853821/what-is-the-significance-of-pragma-marks-why-do-we-need-pragma-marks)
