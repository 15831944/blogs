# 背景

1. 贝尔实验室
2. Bjarne Stroustrup 本贾尼·斯特劳斯特卢普
3. 嵌入式, 游戏编程, 系统编程, 网络编程
4. Visual Studio 2010, Visual Assist X for Visual Studio

# 概念

1. 运行阶段决策: 可以在运行阶段确定数组的长度, 在运行时创建数组, 本质是使用 new 运算符动态申请内存
2. 静态联编( static binding ): 使用数组声明创建数组; 动态联编( dynamic binding ): 使用 new[] 创建数组
3. 左值: 原指可以放在赋值运算符左面的值, 现在指能通过地址访问的值, 因为 const 变量也是左值, 右值是不能通过地址访问的值

# C++ 语言的特点

1. C++ 将测试表达式(test-expression)的结果强制转换为 bool 类型 (C++ Primer Plus p127)
2. 任何值或任何有效的值和运算符的组合都是表达式, 每个表达式都有值, 赋值表达式的值定义为左侧操作数的值 (p128)
3. for 循环的初始化部分可以是声明语句表达式( declaration statement expression), 作用域在 for 循环中 (p130)
4. 副作用(side effect): 表达式中对操作数进行了修改
5. 顺序点(sequence point): 在进入下一条语句前, 对所有副作用进行评估, 语句末的分号, 逗号运算符, 逻辑或运算符, 均为顺序点( p134)
6. 基于范围的 for 循环, 在":"后面接数组作为范围 p152
7. 原始字符串(raw string) p87
8. 函数返回值不能是数组类型 p204
9. 使用 auto 自动类型推断只适用于单值初始化, 不能用于初始化列表 p245

# C++ 标准

1. C++98
2. C++03
3. C++11
4. C++14
5. C++17

# C++ 库

| libraries                   |     |
| --------------------------- | --- |
| Utilities library           |  |
| Strings library             |  |
| Containers library          |  |
| Algorithms library          |  |
| Iterators library           |  |
| Numerics library            |  |
| Input/Output library        |  |
| Localizations library       |  |
| Regular expressions library |  |
| Atomic operations library   |  |
| Thread support library      |  |
| Filesystem library          |  |

# C++ 编译器

1. GNU GCC
2. Clang
3. Microsoft Visual C++
4. Apple Xcode
5. EDG eccp
6. Intel C++
7. IBM XLC++
8. Sun/Oracle C++
9. Embarcadero C++ Builder
10. Cray
11. Portland Group (PGI)
12. HP aCC
13. Digital Mars C++
14. Open Watcom C++
15. Freescale CodeWarrior
16. Borland C++

# 标准 UNIX 编译器

| 语言 | 编译器 | 后缀名 |
| --- | --- | --- |
| c   | cc  | .c  |
| c++ | CC  | .C  |

# 启动代码 startup code

1. 链接程序将启动代码, 函数和库目标代码组合成可执行程序
2. 启动代码调用 main 函数

# 命名空间 namespace

1. 使用 namespace{} 指定任意函数或变量所属的命名空间

# using 编译指令

| 语法                    | 调用方式         | 命名空间作用域                    |
| ---------------------- | --------------- | ------------------------------- |
| using namespace std    | 函数定义前        | 文件作用域                       |
| using namespace std    | 函数定义中        | 函数作用域                       |
| using std::cout        | 使用指定元素前     | 仅将指定元素指定命名空间, 供下文使用 |
| std::cout << std::endl | 随用随指定空间前缀  | 当前语句                        |

# 域解析操作符 scope resolution operator

1. 语法: 在 id 表达式前面使用域解析操作符使不受限的表达式编程受限定的表达式, 并且可选地加枚举, 类名, 命名空间名, 类型声明表达式, 并使用域解析操作符分隔
2. 定义成员函数时, 使用域解析操作符表示该函数属于某个类, (全局函数可以随意调用)
3. 定义变量时, 使用域解析操作符表示该变量属于某个命名空间

| expression                  | describe                                                                                        |
| --------------------------- | ----------------------------------------------------------------------------------------------- |
| std::string::npos           | names the static member npos in the class string in namespace std.                              |
| ::tolower                   | names the function tolower in the global namespace.                                             |
| ::std::cout                 | names the global variable cout in namespace std, which is a top-level namespace.                |
| boost::signals2::connection | names the type connection declared in namespace signals2, which is declared in namespace boost. |

# 输入输出方式

1. 输入: 输入设备 -> 输入流缓冲区 -> scanf(cin) -> 变量
2. 输出: 变量 -> printf(cout) -> 输出流缓冲区 -> 输出设备
3. 流插入(输出)运算符 <<, 向 cout 对象发送消息
4. 流提取(输入)运算符 >>, 从输入流中提取信息

# C++ 数据类型

1. 基本类型: 整数, 浮点数, 布尔型(逻辑类型)
2. 复合类型: 数组, 字符串, 指针, 结构
3. 声明结构类型变量是可以省略 struct 关键字
4. 结构之间可以直接赋值, 称为成员赋值( memberwise assignment )
4. C++ 结构可以包含成员函数, 用于类

# 隐式类型转换 implicit conversion

1. 表达式类型与当前上下文类型不符时, 会将表达式类型转换为上下文接受的类型
2. 须转换为的类型有函数参数声明的类型, 操作符期望的操作数的类型, 初始化新对象的类型, 返回语句返回的函数类型, switch 语句接受的整型, if 语句接受的 bool 型
3. 转换顺序(Order of the conversions): 必须有无歧义的原类型到目标类型的隐式转换顺序(implicit conversion sequence)时才能进行转换
4. 如果存在多个重载的函数或操作符的调用, 则建立隐式转换顺序后, 重载解析规则(overload resolution rules)将决定哪个重载将被编译
5. 值变换(Value transformations): 包括左值转换为右值(Lvalue to rvalue conversion), 数组转换为指针(Array to pointer conversion), 函数转换为指针(Function to pointer)
6. 数值提升(Numeric promotions): 包括整型提升(Integral promotion)和浮点型提升(Floating-point promotion)
7. 数值转换(Numeric conversions)
8. 限定条件转换(Qualification conversions)

1. 初始化和赋值, 值将被转换为接收变量的类型, 精度降低则四舍五入, 浮点数溢出则结果未定义, 浮点数赋给整数将丢弃小数部分, 整型将取低字节, 非0的 bool 值将被转换为 ture

** 整型提升 integral promotion **

1. 表达式中, bool, char, short 提升为 int, wchar_t 被提升为 int, unsigned int, long 或 unsigned long, 因为 int 是计算机最自然的类型, 整型提升后符号不变
2. 表达式中, 操作符涉及不同类型的操作数时, 较小类型将被转换为较大类型, 整型级别顺序为: long long, long, int, short, char, bool. 另外, wchar_t, char16_t, char32_t 的级别与其底层类型相同, 详见 cpp primer plus p64-65
3. 传递参数时的转换: 若取消函数原型对参数传递的控制, 则 char, short 提升为 int, float 提升为 double

# cv限定符间转换 const_cast

# 静态类型转换 static_cast

# 强制类型转换 reinterpret_cast conversion

1. C 风格语法: (typename) value
2. C++ 风格语法: typename (value)
3. 强制类型转换运算符: static_cast<typename> (value)

# 动态类型转换 dynamic_cast conversion

# 显式类型转换 explicit type conversion

# 用户定义的转换 user-defined conversion

# 左值引用(lvalue reference)和右值引用(rvalue reference)

# C++ 语句

1. 声明语句
2. 赋值语句
3. 消息语句
4. 函数调用
5. 函数原型
6. 返回语句

# 参考

《C++ primer plus》
