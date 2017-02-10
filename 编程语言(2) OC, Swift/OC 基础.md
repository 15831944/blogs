# 概述 Overview

1. OC 由 GNU 接管, 可以用于 Linux 嵌入式开发和服务器端开发, Foundation 框架和 UIKit 框架由 OC 语言编写
2. OC 具有封装(Encapsulation), 继承(Inheritance), 多态(Polymorphism), 重写(Override), 优势是其动态能力
3. OC 不具有重载(overload), 模版(Template), 多继承(MI), 垃圾回收机制(Garbage Collection, Cocoa Touch 不支持)
4. OC 源文件扩展名为".m"(module), 与 C++ 混编源文件扩展名为 ".mm"
5. OC 名称空间是程序代码与所有的库, 框架和插件共享的

# 常量和变量 Constant and Variables

1. 静态变量: 全局变量名称习惯用 g 开头, 外部全局变量会破坏封装性, 静态局部变量初始值为0或 nil, 只能在声明该变量的方法内访问, 所有对象共享同一个静态变量, 使用 global 关键字声明
2. 自动变量: 局部变量初始值为0或 nil, 方法返回即失效, 方法的参数属于局部变量

# 字面值 Literals

1. 使用 0, 0x 前缀分别表示八进制和十六进制字面值
2. 使用 f, l, u, ll 前缀分别表示不同数据类型的字面值
3. nil 是 id 类型, 本质是空指针类型, 声明时没有星号
4. 复合字面量: (type) {initialize list} 可以用于初始化结构或数组

# 数据类型 Data Type

程序为了性能优化, 如存储大量数据的数组, 可使用 C 语言的内置的底层数据类型, 而不是 Foundation 框架提供的值对象

1. 基本数据类型: 包括 int, float, double, char, 类型修饰符包括 long, long long, short, signed, unsigned
2. 布尔类型: 本质是预处理机制, 使用预定义的值 YES 和 NO
3. 枚举类型: 在冒号后面接数据类型
4. id 类型: 通用指针类型, 可以强制类型转换为指定类型的对象, 是多态和动态绑定的基础, 不能对 id 类型变量使用点运算符
5. instancetype 类型: 决定了基于上下文的返回类型, 被继承时, 可以正确返回子类, instancetype 类型的方法返回消息接受者的类型或其子类类型
6. Class 类型:

# 操作符 Operator

1. 条件运算符: 从右向左结合, OC 支持非 ANSI 扩展的语句:` condition ? : expression`
2. 消息表达式: 方括号

# 控制流 Control Flow

1. switch 语句: 支持整型和字符型, 赋值和枚举需分别使用编译器选项 `-W Conversion` 和 `-Wswitch` 提供类型检查

# 编译指令 Compiler Directive

1. 编译指令是以@字符开头的指令
2. @interface 指定类的接口部分
3. @implementation 指定类的实现部分
2. @class 声明当前类要用到的类, 可使用该类的属性, 提高效率, 但要使用该类的方法, 则需包含该类的整个头文件

# 参考

书籍

1. 《Objective-C 程序设计》
2. 《Objective-C 编程全解》

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
