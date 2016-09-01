有几个命令可对程序源代码的各部分有选择地进行编译，该过程称为条件编译。

商业软件公司广泛应用条件编译来提供和维护某一程序的许多顾客版本。

# 1. #if，#else，#elif，#endif

#if 的一般含义是如果 #if 后面的常量表达式为 true，则编译它与#endif之间的代码，否则跳过这些代码。命令#endif标识一个#if块的结束。

```
#if constant-expression
statement sequence
#endif
```
Eg:

```
#define MAX 91
#include
using namespace std;
int main()
{
#if MAX > 99
       cout<<"MAX is bigger than 99"<
#elif MAX > 90
       cout<<"MAX is bigger than 90"<
#else
       cout<<"MAX is smaller than 90"<
#endif
       return 0;
}
```

跟在#if后面的表达式在编译时求值，因此它必须仅含常量及已定义过的标识符，不可使用变量。

表达式不许含有操作符 sizeof（sizeof也是编译时求值）。

#else命令的功能有点象C语言中的else；#else建立另一选择（在#if失败的情况下）。注意，#else属于#if块。
 
#elif命令意义与ELSE IF 相同，它形成一个if else-if阶梯状语句，可进行多种编译选择。

#elif 后跟一个常量表达式。如果表达式为true，则编译其后的代码块，不对其它#elif表达式进行测试。否则，顺序测试下一块。
 
```
#if expression
statement sequence
#elif expression1
statement sequence
#endif
```
 
在嵌套的条件编译中#endif、#else或#elif与最近#if或#elif匹配。


# 2. #ifdef 和# ifndef
 
条件编译的另一种方法是用#ifdef与#ifndef命令，它们分别表示"如果有定义"及"如果无定义"。# ifdef的一般形式是：
 
# ifdef macroname
statement sequence
#endif
 
#ifdef与#ifndef可以用于#if、#else，#elif语句中，但必须与一个#endif。
 
```
#define MAX 91
#include
using namespace std;
 
int main()
{
#ifdef MAX
       cout<<"hello,MAX!"<
#else
       cout<<"where is MAX?"<
#endif
#ifndef LEO
       cout<<"LEO is not defined"<
#endif
       return 0;
}
```

命令#undef 取消其后那个前面已定义过有宏名定义。一般形式为：
#undef macroname

# 3. #line

命令#line改变__LINE__与__FILE__的内容，它们是在编译程序中预先定义的标识符。命令的基本形式如下：
#line number["filename"]
其中的数字为任何正整数，可选的文件名为任意有效文件标识符。行号为源程序中当前行号，文件名为源文件的名字。

命令#line主要用于调试及其它特殊应用。

注意：在#line后面的数字标识从下一行开始的数字标识。

#line 100 "jia"
       cout<<"#line change line and filename!"<
       cout<<__LINE__<
       cout<<__FILE__<
