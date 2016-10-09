# 1 操作符

1. 当两个运算符被用于同一个操作数时, 优先级和结核性规则才有效
2. 运算符重载 operator overloading, 如除法运算
3. 模运算符号规则: ( a / b ) * b + a % b = a

# 2 隐式类型转换 implicit conversion

## 1 初始化和赋值

值将被转换为接收变量的类型, 精度降低则四舍五入, 浮点数溢出则结果未定义, 浮点数赋给整数将丢弃小数部分, 整型将取低字节, 非0的 bool 值将被转换为 ture

## 2 列表初始化

不允许缩窄

## 3 表达式中的转换

### 1 整型提升 integral promotion

因为 int 是计算机最自然的类型, 整型提升后符号不变

bool, char, unsigned char, signed char, short 提升为 int

wchar_t 被提升为 int, unsigned int, long 或 unsigned long

### 2 操作符涉及不同类型的操作数

较小类型将被转换为较大类型, 详见 cpp primer plus p64-65

整型级别: long long, long, int, short, char, bool

wchar_t, char16_t, char32_t 的级别与其底层类型相同

## 4 传递参数时的转换

若取消函数原型对参数传递的控制, 则

char, short 提升为 int

float 提升为 double

# 3 强制类型转换 cast

(typename) value C 风格

typename (value) C++ 风格

## 强制类型转换运算符

static_cast<typename> (value)
