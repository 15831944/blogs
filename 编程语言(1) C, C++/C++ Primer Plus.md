# 编程范式

1. 面向过程编程 procedure oriented programming, C, 结构化编程 structured programming, 自顶向下 top-down, 算法
2. 面向过程编程 object oriented programming, OOP, 对象, 类, 封装, 数据隐藏, 多态, 继承, 自下向上 bottom-up, 数据
3. 泛型编程 generic programming, 模板, 独立于特定数据类型

# C++ 标准

1. C++98, 异常, 运行阶段类型识别(RTTI), 模板, 标准模板库(STL), C++标准类库
2. C++11

# C++ 实现

1. Microsoft Visual C++
2. Embarcadero C++ Builder
3. Apple Xcode
4. Open Watcom C++
5. Digital Mars C++
6. Freescale CodeWarrior
7. GNU C++
8. Borland C++

# 标准 UNIX 编译器

| 语言 | 编译器 | 后缀名 |
| --- | --- | --- |
| c   | cc  | .c  |
| c++ | CC  | .C  |

# 启动代码 startup code

1. 链接程序将启动代码, 函数和库目标代码组合成可执行程序
2. 启动代码调用 main 函数

# using 编译指令

1. 函数定义前, 文件作用域, using namespace std
2. 函数定义中, 函数作用域, using namespace std
3. 指定元素, 如 using std::cout
4. 使用前缀, 如 std::cout << std::endl

# 输入输出方式

1. 输入: 输入设备 -> 输入流 -> scanf(cin) -> 变量
2. 输出: 变量 -> printf(cout) -> 输出流 -> 输出设备

# 命名空间

整个函数都要写在命名空间中

# 域解析操作符

1. 成员函数与普通函数的区别在于成员函数是属于某个类的，不能随意调用
2. 定义成员函数时，使用::域解析操作符表示该函数是属于某个类的

# C++ 数据类型

1. 基本类型, 包括: 整数, 浮点数
2. 复合类型, 包括: 数组, 字符串, 指针, 结构

# C++ 操作符

1. 插入运算符 <<, 向 cout 对象发送消息
2. 抽取运算符 >>, 从输入流中抽取信息
3. 当两个运算符被用于同一个操作数时, 优先级和结核性规则才有效
4. 运算符重载 operator overloading, 如除法运算
5. 模运算符号规则: ( a / b ) * b + a % b = a

# 隐式类型转换 implicit conversion

1. 初始化和赋值, 值将被转换为接收变量的类型, 精度降低则四舍五入, 浮点数溢出则结果未定义, 浮点数赋给整数将丢弃小数部分, 整型将取低字节, 非0的 bool 值将被转换为 ture
2. 列表初始化 list-initiallization, 不允许缩窄 narrowing p64

# 整型提升 integral promotion

1. 表达式中, bool, char, unsigned char, signed char, short 提升为 int, wchar_t 被提升为 int, unsigned int, long 或 unsigned long, 因为 int 是计算机最自然的类型, 整型提升后符号不变
2. 表达式中, 操作符涉及不同类型的操作数时, 较小类型将被转换为较大类型, 整型级别顺序为: long long, long, int, short, char, bool. 另外, wchar_t, char16_t, char32_t 的级别与其底层类型相同, 详见 cpp primer plus p64-65
3. 传递参数时的转换: 若取消函数原型对参数传递的控制, 则 char, short 提升为 int, float 提升为 double

# 强制类型转换 cast

1. C 风格语法: (typename) value
2. C++ 风格语法: typename (value)
3. 强制类型转换运算符: static_cast<typename> (value)

# C++ 语句

1. 声明语句
2. 赋值语句
3. 消息语句
4. 函数调用
5. 函数原型
6. 返回语句
