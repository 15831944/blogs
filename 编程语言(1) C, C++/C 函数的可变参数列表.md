# 函数参数传递方式

GCC 编译器在汇编过程中，调用 C 语言函数时，传递参数有两种方法：

1. 通过寄存器(默认)
2. 通过堆栈(使用 asmlinkage 宏)

# 可变参数列表必须保存在栈中

```
#define asmlinkage __attribute__((regparm(0)))
asmlinkage int printk(const char *fmt, ...)
```

1. 告诉 GCC 编译器该函数使用0个寄存器参数，即不需要通过任何寄存器来传递参数，参数只是通过堆栈来传递
2. 可变参数列表必须保存在栈中, 因为遍历各个可变参数时要按地址访问

# 可变参数列表的实现

1. 函数原型中具有确定的参数类型和数量，保证了函数调用时的准确性
2. 使用不同类型和数量的可变参数进行函数调用时，参数列表的数量和类型对于被调用函数是未知的, 因此需要在函数实现中确定各个可变参数的类型和地址, 使用上一个参数的类型确定下一个参数的地址
3. 头文件 `<stdarg.h>` 定义了 va_list 类型和用于逐个通过参数列表的3个宏 va_start(), va_arg() 和 va_end()
4. 被调函数必须声明一个 `va_list` 类型的对象, va_start(), va_arg() 和 va_end() 使用该指针指向这个可变参数列表的各个参数

# 函数调用时的栈结构

1. 栈由高地址(栈底)向低地址(栈顶)方向增长, 参数的入栈顺序为从右向左
2. 栈的先入后出特性, 函数调用时需保存现场进行压栈, 函数返回时则相反
3. 函数调用时, 实参的第1个参数到第n个参数被存放在地址递增的栈中
4. 函数返回时, 最后返回地址, 返回函数调用位置

函数的可变参数列表的地址 = 函数参数列表中最后一个固定参数的地址 + 第一个可变参数对其的偏移量

下一可变参数的地址 = 当前可变参数的地址 + 下一可变参数对其的偏移量

| 栈结构             | 说明 |
| ----------------- | --- |
| 栈底               | 高地址 |
| 函数返回地址        |  |
| 函数最后一个可变参数 | 函数参数的入栈顺序为从右向左 |
| 函数第一个可变参数   | 调用 va_start 后 ap 指向这里 |
| 函数最后一个固定参数 |  |
| 函数第一个固定参数   |  |
| 栈顶               | 低地址 |

# 获取可变参数列表的地址

要确定未知类型和数量的变量，先要有一个已知类型的变量作为基准, 以可变参数前面固定的那些参数中的最后一个，也即可变参数前面那个参数作为基准, 确定第一个可变参数的地址，方法是调用`void va_start(va_list ap, last);`, 基准是 last 指定的参数，然后由 last 计算指向第1个可变参数的指针 ap, 依据栈的内存的布局，参数地址是递增的，计算方法是加上第1个可变参数对 last 的地址偏移, 此时，ap 指向可变参数列表中的第一个参数，即得到了可变参数列表的地址

# 获取各个可变参数的值

需要指定参数的类型，以取得指向指定类型的指针，来获取各个可变参数, 方法是调用`va_arg(va_list ap, type);` 宏，它的作用是：返回强制转换成指向当前可变参数的类型的指针，间接访问即可获取其值, 并使 va_list 指向下一个可变参数，以便遍历所有可变参数, 最后，用 `va_end(ap)`，初始化 ap 可变参数指针，保持健壮性

# 宏的简要处理过程

对可变参数列表的处理过程一般为：

1. 用 va_list 定义一个可变参数列表
2. 用 va_start 获取函数可变参数列表首地址
3. 用 va_arg 循环处理可变参数列表中的各个可变参数
4. 用 va_end 结束对可变参数列表的处理

# 各个宏的语法

```
#include <stdarg.h>

void va_start(va_list ap, last);
type va_arg(va_list ap, type);
void va_end(va_list ap);
void va_copy(va_list dest, va_list src);
```

# 各个宏的定义

```
#ifndef va_arg

#ifndef _VALIST
#define _VALIST
typedef char *va_list;
#endif

/* Storage alignment properties */

#define _AUPBND (sizeof (acpi_native_int) - 1)
#define _ADNBND (sizeof (acpi_native_int) - 1)

/* Variable argument list macro definitions */

#define _bnd( x, bnd )	( ( ( sizeof ( x ) ) + ( bnd ) ) & ( ~ ( bnd ) ) )

#define va_start( ap, A )	( void )		( ( ap ) = ( ( ( va_list ) &( A ) ) + ( _bnd( A, _AUPBND ) ) ) )
#define va_arg( ap, T )		( * ( T * )		( ( ( ap ) += ( _bnd ( T, _AUPBND ) ) ) - ( _bnd( T, _ADNBND ) ) ) )
#define va_end( ap )		( ap = ( va_list ) 0 )

#endif
```

# 各个宏的详细说明

va_list

1. va_list 表示可变参数列表类型，实际上就是一个 char 指针，之所以使用此类型，是因为它的指针运算是一个字节一个字节的加减的

va_start( va_list ap, last )

1. va_start 用于获取函数参数列表中可变参数的首指针 ap, 供 va_arg() 和 va_end() 随后使用
2. last 必须是确定的栈中的地址并具有固定的类型(长度)，因此 last 不应被声明为寄存器变量, 函数或者数组

| parameter  | 作用 |
| ---------- | --- |
| va_list ap | 保存函数参数列表中可变参数的首指针, 即可变参数列表 |
| char *last | 函数参数列表中可变参数列表前最后一个固定参数的名字 |

va_arg( va_list ap, type )

1. va_arg 用于返回当前 ap 所指的可变参数, 并将 ap 指针移向下一可变参数, 以便下次调用能够返回下个参数, 循环调用则从第1个可变参数获取到最后1个
2. 参数 type 是当前可变参数的类型名，这样，指向特定类型对象的指针的类型可以简单的通过在参数指定的该类型后添加间接访问操作符得到
3. 如果没有下一个参数，或者如果类型和实际的下一个参数的类型不匹配（按照默认参数提升进行的提升），则会产生随机错误
4. 如果 ap 被传递给使用 va_arg(ap, type) 的函数，那么在这个函数返回后，ap 的值是未定义的, 即不可重入

| parameter  | 作用 |
| ---------- | --- |
| va_list ap | 指向当前正要处理的可变参数 |
| type       | 当前可变参数的类型 |
| 返回值      | 当前可变参数的值 |

va_end( va_list ap )

1. va_end 用于结束对可变参数的处理, 可实现为宏或者函数, 可被定义为空, 只实现与 va_start 配对(实现代码对称和"代码自注释"功能), 调用 va_end() 后，变量 ap 是未定义的
2. 列表的多重遍历是可能的，每个列表用 va_start() 和 va_end() 括起来

# 边界对齐的问题

## 为什么要边界对齐？

上面提到的偏移量并不一定等于参数所占的字节数, 而是为参数所占的字节数再扩展为机器字长(acpi_native_int)倍数后所占的字节数, 因为入栈操作针对的是一个机器字

## 如何实现按 int 的倍数进行字节对齐？

1. 在遍历可变参数列表时, 参数 x 的取值可能是最后一个固定参数的名字或各个可变参数的类型
2. 假设 sizeof(acpi_native_int) = 4，则，加操作保证中间结果至少为4，与操作会清除低2位，保证结果必为4的倍数，从而保证边界对齐

举例

1. 若 sizeof(x) = 1，则 (1 + 3) & ~3 = 4
2. 若 sizeof(x) = 2，则 (2 + 3) & ~3 = 4
3. 若 sizeof(x) = 4，则 (4 + 3) & ~3 = 4
4. 若 sizeof(x) = 8，则 (8 + 3) & ~3 = 8

# 参考

1. [C语言函数之可变参数原理:va_start、va_arg及va_end](http://blog.chinaunix.net/uid-23089249-id-34493.html)
2. [va_start va_arg va_end 的原理与实例](http://blog.csdn.net/sunboy_2050/article/details/6189072)
3. [printf,sprintf,vsprintf 区别](http://blog.csdn.net/anye3000/article/details/6593551)
4. [关于va_list的_INTSIZEOF(n)的疑问](http://bbs.csdn.net/topics/250015145)
5. [linux内核中的fastcall和asmlinkage宏](http://blog.csdn.net/ce123/article/details/8446520)
