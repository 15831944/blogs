# gcc 扩展关键字

## \_\_attribute\_\_

1. 设置函数属性, 变量属性, 数据类型属性等, 向编译器提供更多数据, 帮助编译器执行优化

### 描述函数属性

1. 使用 addr2line 工具分析源代码, 统计程序的运行状态

```
void fun()         __attribute__ ((regparm(0)));			//不需要通过任何寄存器来传递参数, 参数只是通过堆栈来传递
void fun()         __attribute__ ((regparm(3)));			//通过寄存器传递多达3个的参数(EAX, EDX, ECX), 更多的参数才通过堆栈传递, 减少一些入栈出栈操作, 调用更快
void noreturnfun() __attribute__ ((noreturn));				//函数不会返回
void centon()      __attribute__ ((alias("__centon")));		//设置函数别名，函数是 __centon, 别名是 centon
void main_enter()  __attribute__ ((constructor));			//main_enter 函数在进入 main 函数前调用
void main_exit()   __attribute__ ((destructor));			//main_exit 函数在 main 函数返回后调用
void fun()         __attribute__ ((noinline));				//fun 函数不能作为 inline 函数优化
void fun()         __attribute__ ((section("specials”)));	//将函数放到 specials 段中，而不是通常的 text 段中
```

### 描述变量属性

1. 如果不使用packed属性, 则数组按最小的对齐方式在内存中安排空间, X86平台为4, 结构成员间会有空洞存在

```
int		alivalue __attribute__ ((aligned(32)));				//变量所存放的内存地址32字节边界对齐
struct	domx  __attribute__ ((section(“domx”))) = { 0 };
int		trigger  __attribute__ ((section(“MONLOG”))) = 0;	//不将全局变量放在默认的data或bss段中, 而指定特定的段中
struct	zrecord {
	char id;
	int zar[32] __attribute__ ((packed));					//紧凑安排数据结构中的成员元素
};
```

### 描述数据类型属性

```
struct blockm{
      char j[3];
}__attribute__((aligned(32)));		//此数据类型的变量的内存地址32字节边界对齐
int rslt = ({
    int a=5;
    a+3;
});				//复合声明返回值(Compound Statements Returning a Value):在一对圆括号中的最后一个表达式所计算的值为返回值, rslt所获得的返回值为8
```

# 参考

1. [GNU C中不为人知的特色：__attribute__机制](http://blog.csdn.net/juana1/article/details/6849120)
2. [linux内核 asmlinkage宏-wqfhenanxc-ChinaUnix博客](http://blog.chinaunix.net/uid-7390305-id-2057287.html)
