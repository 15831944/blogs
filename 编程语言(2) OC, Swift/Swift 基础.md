# 概述

1. Swift 采用了 OC 命名参数(named parameters)的可读性(readability)
2. Swift 采用了 OC 的动态对象模型(dynamic object model)
3. Swift 统一了语言的过程性(procedural)和面向对象(object-oriented)部分
4. 全局作用域的代码被用作程序的入口, 不需要 main 函数
6. 强制类型转换也可以看做是构造函数
7. 语句后面不需要接分号, 除非一行中写多条语句
8. 使用空的小括号作为空语句, 而不是分号
9. 块注释可以嵌套
1. 常量和变量的定义方式与其引用的定义方式想通过, 而不需要 "\*" 或 "&", 系统自动判断

# 编程范式

1. 函数式编程
2. 面向对象编程
3. 过程性编程

# 安全编程模式 Safe Programming Patterns

1. 强类型语言, 表达式中不允许隐式类型转换, 操作数必须与要求类型一致, 例如, 条件表达式必须是 Bool 类型, 字符串不能和字符拼接
2. 没有初始化的变量不可以直接被引用, 不是像其他语言那样给一个随机值或默认值, 但可选型会被默认初始化为 nil
3. 在编译阶段就可判断变量是否溢出

# 常量和变量 constant and variable

1. 数据声明: 使用 let 声明常量, 使用 var 声明变量, 值不会变的情况下应尽量使用常量(存储在常量区, 效率高)
2. 类型安全(Type Safety): 在编译时进行类型检查(Type-checking)
3. 类型推断(Type Inference): 根据初始值隐式地判断数据对象的类型, 减少代码书写量
4. 类型声明(Type Annotations): 使用 ": " 显式地声明的数据类型
5. 类型别名(Type Aliases): 使用 typealias 关键字
6. 常量的初始化: 声明时可以不赋初值, 因为编译时的常量值不需要被知道, 声明后的第一次赋值将作为该常量的值, 且只能赋值一次, 常量声明但未初始化期间不可以使用
7. 常量与变量名: 不能包含空字符(whitespace characters), 数学符号(mathematical symbols), 箭头, 保留的或者非法的 Unicode 码位(private-use or invalid Unicode code points), 连线与制表符(line- and box-drawing characters), 不能以数字开头, 将关键字放在反引号内则可用关键字作为变量名
8. 标识符: 使用 Unicode 编码, 而不是 ASCII 编码, 一个字符可能占用1个或多个字节, 支持中文以及特殊字符形式的变量名

# 字面值 literal

1. 字面值(literal value): 直接显示在源代码中的值, 例如 3.14, 整数和浮点数字面值均可使用下划线和数字0进行分割, 提高可读性
2. 数值型字面值(Numeric Literals): 使用 0b, 0o, 0x 前缀表示不同进制数, 适用于整数和浮点数, 10进制浮点数的指数是可选的, 16进制浮点数必须有指数, 本身没有类型, 因此 3 + 0.14 是可以的, 编译器对其进行计算后才能推断出类型
3. 数值类型转换(Numeric Type Conversion): 整数之间的转换使用 SomeType(ofInitialValue) 语法, 浮点数强制转换为整数将总是被截断(truncated), 字符串("123")可能被转换为整数, 返回可选型

# 值类型和引用类型 value type and inference type

1. 值类型: 基本类型(Int, Float, String), 集合类型(Array, Set, Dictionary)的实现都是结构体, 是值类型, 在函数调用中采用传值方式传递, 通过不同实体间的拷贝赋值, 存储在栈中
2. 引用类型: 类和对象是引用类型, 使用指针访问堆中的内存, Objective C 中的以 NS 开头的类型是 Fundation 框架提供的类, 所有数据类型均采用引用方式传递

# 下标 Subscripts

1. 使用下标进行访问的内置的数据类型包括: 数组(someArray[index]), 字典(someDictionary[key])
2. 使用 subscript 关键字定义类, 枚举, 结构体数据类型的下标
3. 下标是访问对象, 集合, 列表, 序列的快捷方式, 不需要再调用实例的特定赋值或访问方法, 在方括号中传入一个或多个索引值
4. 下标的重载: 一个类或结构体可以根据自身需要提供多个下标脚本实现，在定义下标脚本时通过入参个类型进行区分，使用下标脚本时会自动匹配合适的下标脚本实现运行

```
subscript(index: Int) -> Int {
	get {// 返回与入参匹配的Int类型的值}
	set(newValue) {// 执行赋值操作}
}
```

# 运算符重载 Operator Overloading

# 扩展 Extention

# 嵌套类型 Nested Type

# 泛型编程 Generic

# 协议 Protocol

# 委托 Delegation

# 异常处理 Error Handing

# 内存管理 Memory Management

# 类型转换 Type Casting

# 高阶函数

1. 高阶函数指向函数的指针变量作为参数的函数

# 柯里化 Currying

1. 把接受多个参数的方法进行一些变形，使其更加灵活的方法

# mutating

# @selector

# SequenceType 和 GeneratorType

1. Swift 的 for...in 可以用在所有实现了 SequenceType 的类型上

# 参考

1. CSDN 上的 swift 知识库的练习资料: PKO_Sample_Element, XHNewsParsingSwift
