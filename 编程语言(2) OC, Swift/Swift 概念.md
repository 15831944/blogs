# Swift 语言的特点

1. 标识符使用 Unicode 编码(而不是 ASCII 编码), 一个字符可能占用1个或多个字节, 支持中文以及特殊字符形式的变量名
2. 块注释可以嵌套
3. 语句后面不需要接分号, 除非是在一行中写多条语句
4. 强制类型转换也可以看做是构造函数
5. 不支持自增/自减运算符, 原因也是编码问题?
6. Swift adopts the readability of Objective-C’s named parameters and the power of Objective-C’s dynamic object model
7. Swift unifies the procedural and object-oriented portions of the language
8. Code written at global scope is used as the entry point for the program, so you don’t need a main() function
9. 使用 print 函数打印这样的语句不需要引用任何库
1. 使用空的小括号作为空语句, 而不能是分号

# Swift 语言的安全性

1. 强类型语言, 表达式中不允许隐式类型转换, 操作数必须与要求类型一致, 例如条件表达式必须是 Bool 类型, 字符串不能和字符拼接
2. 在编译阶段就可判断变量是否溢出
3. 没有初始化的变量不可以直接被引用, 不是像其他语言那样给一个随机值或默认值, 但可选型会被默认初始化为 nil
4. Swift adopts safe programming patterns

# 解包 unwrap

1. 当被解包的数据是常量时, 使用强制解包则是安全的, 因为可以确保不会为空

# 下标 Subscripts

1. 使用下标进行访问的内置的数据类型: 数组, 字典
2. 使用 subscript 关键字定义类, 枚举, 结构体数据类型的下标
3. set 的类型和下标返回的类型一致

# 运算符重载 Operator Overloading

# 扩展 Extention

# Nested Type

# 泛型编程 Generic

# 协议 Protocol

# Delegation

# Error Handing

# 内存管理 Memory Management

# Type Casting


# 疑问

1. 最自然的数据类型(Int)执行的访问最快, 因为数据的位数和操作系统的位宽相同, 存取速度快
2. 使用常量比变量更高效, 常量存储在内存的常量区, 存取速度快

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
