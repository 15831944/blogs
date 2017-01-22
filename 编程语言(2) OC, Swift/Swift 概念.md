# 概述

1. Swift 采用了 OC 命名参数(named parameters)的可读性(readability)
2. Swift 采用了 OC 的动态对象模型(dynamic object model)
3. Swift 统一了语言的过程性(procedural)和面向对象(object-oriented)部分
4. 全局作用域的代码被用作程序的入口, 不需要 main 函数
5. 使用 print 这样的函数不需要引用任何库
6. 强制类型转换也可以看做是构造函数
7. 语句后面不需要接分号, 除非一行中写多条语句
8. 使用空的小括号作为空语句, 而不是分号
9. 块注释可以嵌套

# 编程范式

1. 函数式编程
2. 面向对象编程
3. 过程性编程

# 安全编程模式 Safe Programming Patterns

1. 强类型语言, 表达式中不允许隐式类型转换, 操作数必须与要求类型一致, 例如, 条件表达式必须是 Bool 类型, 字符串不能和字符拼接
2. 没有初始化的变量不可以直接被引用, 不是像其他语言那样给一个随机值或默认值, 但可选型会被默认初始化为 nil
3. 在编译阶段就可判断变量是否溢出

# 下标 Subscripts

1. 可使用下标进行访问的内置的数据类型包括: 数组, 字典
2. 使用 subscript 关键字定义类, 枚举, 结构体数据类型的下标

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

# @autoclosure

1. 把一句表达式自动地封装成一个闭包

# 单词

semicolon 分号
colon 冒号
parentheses 小括号
backslash 反斜杠
brackets 方括号
Braces 大括号
comma 逗号
question mark 问号
exclamation mark 感叹号
backticks 反引号
asterisk 星号
underscores 下划线
double quotes 双引号

explicitly 显式地
implicitly 隐式地

clause 子句
iterate over 遍历

prefix
infix
suffix

# 参考

1. CSDN 上的 swift 知识库的练习资料: PKO_Sample_Element, XHNewsParsingSwift
