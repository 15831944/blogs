# C reserved keywords

## 存储类型说明符 storage-class specifier

| keywords | meaning                                                                                                   |
| -------- | --------------------------------------------------------------------------------------------------------- |
| auto     | automatic duration storage-class specifier with no linkage                                                |
| extern   | static duration storage-class specifier with either internal or more usually external linkage             |
| register | automatic duration storage-class specifier with no linkage. Hints that the variable will be used heavily  |
| static   | static duration storage-class specifier with internal linkage at file scope and no linkage at block scope |
|          | static array indices in function parameter declarations (since C99)                                       |

## 跳转, 条件, 循环语句声明符 statement declarator

| keywords | meaning                             |
| -------- | ----------------------------------- |
| break    |                                     |
| continue |                                     |
| goto     |                                     |
| return   |                                     |
| if       | if statement                        |
| else     | if statement: alternative branch    |
| switch   | switch statement                    |
| case     | switch statement: case labels       |
| default  | switch statement: efault case label |
|          | type-generic expression: as the declaration of the default generic association(since C11) |
| do       | do-while loop                       |
| for      | for loop                            |
| while    | while loop                          |
|          | do-while loop: terminating condition of the loop |

## 类型声明符 type declarator

| keywords | meaning                   |
| -------- | ------------------------- |
| char     |                           |
| int      |                           |
| double   |                           |
| enum     | enumeration type          |
| float    |                           |
| inline   | inline function specifier |
| struct   | compound type             |
| union    |                           |
| typedef  |                           |
| void     | incomplete type           |
|          | in a function with no parameter or no return value |

## 类型修饰符 type modifier

| keywords | meaning                   |
| -------- | ------------------------- |
| long     | long type modifier        |
| short    | short type modifier       |
| signed   | signed type modifier      |
| unsigned | unsigned type modifier    |

## 类型限定符 type qualifier

cv限定符

| keywords | meaning                   |
| -------- | ------------------------- |
| const    | const type qualifier      |
| restrict | restrict type qualifier   |
| volatile | volatile type qualifier   |

## 操作符 operator

| keywords | meaning         |
| -------- | --------------- |
| sizeof   | sizeof operator |

# inline

1. 使用 inline 关键字声明内联函数 Inline function, 内联函数在某些情况下类似于宏, 直接将代码内嵌到调用它的父函数中
2. 编译时需要指定优化等级为 -O3 才能被内嵌, 也可以指定内嵌函数属性 #pragma always_inline 强制内嵌
3. 使用 ISO C 标准的时候，可以使用 \_\_inline\_\_ 关键字代替 inline 关键字

有几种情况将不内嵌，而作为普通函数调用：

1. 可变参数的函数
2. 调用 alloca 类库的函数
3. 有可变尺寸数组声明的函数
4. 非本地 goto 的函数
5. 嵌套调用的函数

# const

1. 使用 const 限定符修饰形参可以防止函数修改传入的参数
2. 使用 const 限定符修饰指针和引用

# volatile

1. volatile 关键字会影响编译器的编译结果, 它指出其修饰的变量是随时可能发生变化的, 变量可能在程序外被改变
2. 与 volatile 变量有关的运算将不进行编译优化, 每次使用 volatile 变量时必须从内存中其原始地址中读取, 不会去假设这个变量的值, 不会去重复使用保存在 cache 或寄存器里的备份, 例如向某个设备地址连续写入两条指令, 则指向设备地址的指针应声明为 volatile, 保证每条指令都被写入, 否则编译器可能将其优化为只写入为最后一条指令
3. 一个参数可以同时既是 const 又是 volatile, 例如只读的状态寄存器, 它是 volatile 因为它可能被意想不到地改变, 它是 const 因为程序不应该试图去修改它
4. 指针可以是 volatile, 例如当一个中断服务子程序修该一个指向一个 buffer 的指针时

举例

1. 并行设备的硬件寄存器(如状态寄存器)
2. 一个中断服务子程序中会访问到的非自动变量(Non-automatic variables)
3. 多线程应用中被几个任务共享的变量

```
// 返指针 *ptr 指向值的平方, 错误示例
int square(volatile int *ptr)
{
	return *ptr * *ptr;
}
// 上述错误示例相当于如下函数实现
int square(volatile int *ptr)
{
	int a, b;

	/* 由于 *ptr 的值可能被意想不到地该变, 因此a和b可能是不同的 */
	a = *ptr;
	b = *ptr;

	return a * b;
}
// 正确的实现
long square(volatile int *ptr)
{
	int a;

	a = *ptr;
	return a * a;
}

// 错误示例
int	*ip = ...;	// 设备地址
*ip = 1;		// 向该设备地址传入第一个指令
*ip = 2;		// 向该设备地址传入第二个指令
// 以上程序可能被编译器优化为如下代码, 丢失第一个指令
int	*ip = ...;
*ip = 2;
// 用 volatile 修饰指针, 不允许做任何优化, 保证命令被依次写入
volatile int	*ip = ...;
*ip = 1;
*ip = 2;
```

# 参考

1. [cppreference](http://en.cppreference.com/w/c/keyword)
2. [C中的volatile用法](http://www.cnblogs.com/chio/archive/2007/11/24/970632.html)
