# __attribute__

__attribute__ 是关键字，是gcc的C语言扩展。

__attribute__机制是GNU C的一大特色，它可以设置函数属性、变量属性和类型属性等。可以通过它们向编译器提供更多数据，帮助编译器执行优化等。
__attribute__((regparm(0)))：告诉gcc编译器该函数不需要通过任何寄存器来传递参数，参数只是通过堆栈来传递。
__attribute__((regparm(3)))：告诉gcc编译器这个函数可以通过寄存器传递多达3个的参数，这3个寄存器依次为EAX、EDX 和 ECX。更多的参数才通过堆栈传递。这样可以减少一些入栈出栈操作，因此调用比较快。

GCC使用__attribute__关键字来描述函数，变量和数据类型的属性，用于编译器对源代码的优化。

# 描述函数属性的几个重要的关键字

```
void noreturnfun() __attribute__((noreturn));		//函数不会返回
void centon() __attribute__((alias("__centon")));	//设置函数别名，函数是 __centon, 别名是 centon
void main_enter() __attribute__((constructor));		//main_enter 函数在进入 main 函数前调用
void main_exit() __attribute__((destructor));		//main_exit 函数在 main 函数返回后调用
void fun() __attribute__ ((noinline));				//fun 函数不能作为 inline 函数优化
void fun() __attribute__ ((section("specials”)));	//将函数放到 specials 段中，而不是通常的 text 段中
```

no_instrument_function、 constructor 和 destructor 关键字主要用于剖析(profiling)源代码的。

在调某个用函数之前和退出某个函数之后调用这些剖析函数，配合addr2line工具可以统计程序的运行状态。

__cyg_profile_func_enter 和 __cyg_profile_func_exit 是 GCC 指定的进入和返回调用的函数名。

配合 no_instrument_function 关键字属性可以使用它记录剖析数据，

在编译这样的代码的时候，需要在 gcc 的命令行中加入 -finstrument-functions 选项，

如果要使用 addr2line 工具分析源代码，则还要加上 -g 的 gcc 命令行选项使得源代码中的符号可以保留。

这2个函数需要2个参数，void *func_address 是将要调用的函数地址，void *call_site 是调用该函数的地址。

void __cyg_profile_func_enter( void *func_address, void *call_site )
                                __attribute__ ((no_instrument_function));
void __cyg_profile_func_exit ( void *func_address, void *call_site )
                                __attribute__ ((no_instrument_function));

constructor 和 destructor 是对 main 函数做上述剖析的关键字，不过这个函数的名称就可以不特定了，而且这样的函数没有参数。如下：

void __main_enter(void) __attribute__ ((constructor));
void __main_exit(void) __attribute__ ((destructor));

# 描述变量属性的几个重要的关键字

int alivalue __attribute__ ((aligned(32)));		//变量所存放的内存地址32字节边界对齐
struct zrecord {
char id;
int zar[32] __attribute__ ((packed));
};				//紧凑安排数据结构中的成员元素。如果不使用packed属性则将zar数组按最小的对齐方式在内存中安排空间，X86平台为4，这样在id和zar之间将会有3个字节的空洞存在。而使用了packed属性后，将不会存在这样的空洞。这次属性是依赖与硬件平台的。

struct domx __attribute__ ((section(“domx”))) = { 0 };
int trigger __attribute__ ((section(“MONLOG”))) = 0;		//不将全局变量放在默认的data或bss段中。而指定特定的段中。

# 描述数据类型属性的几个重要的关键字

struct blockm{
      char j[3];
}__attribute__((aligned(32)));		//此数据类型的变量的内存地址32字节边界对齐
复合声明返回值(Compound Statements Returning a Value):
在一对圆括号中的最后一个表达式所计算的值为返回值。如:
int rslt = ({
                    int a=5;
                    a+3;
             });//rslt所获得的返回值为8
这个特性的通常用处可书的P87(文档P112)参考。

# 函数参数构造（Function Argument Construction）

GCC内建了3个函数，用于对某一函数的参数构造，调用相关函数，获得相关函数的返回值。
void *__builtin_apply_args(void);	//构造调用此函数的父函数的参数，这些参数都是保存在函数栈（stack）中的。
void *__builtin_apply(void (*func)(), void *arguments, int size);	//调用相关函数，第一参数是相关函数的执政，第二个参数是刚才构造参数的函数的返回的指针，第三个参数是建立一个新的栈（stack）而从旧栈中复制数据的尺寸。
__builtin_return(void *result);		//获得相关函数的返回。参数是刚才调用相关函数的函数的返回指针。

如：
#include <stdio.h>
int passthrough();
int average();
int main(int argc,char *argv[])
{
   int result;
   result = passthrough();
   printf(“result=%d\n”,result);
   return (0);
}
int passthourgh(int a,int b,int c)
{
void *record;
void *playback;
void (* fn)() = (void (*) ()) average;
record = __builtin_apply_args();
playback = __builtin_apply(fn,record,128);
   __builtin_return(playback);
}
int average(int a,int b,int c)
{
   Return ((a+b+c)/3;
}
