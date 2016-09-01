# NAME

strtok, strtok_r - extract tokens from strings
strtok, strtok_r - 提取字符串中的标记

# SYNOPSIS

```
#include <string.h>

char *strtok(char *str, const char *delim);

char *strtok_r(char *str, const char *delim, char **saveptr);
```
Feature Test Macro Requirements for glibc (see feature_test_macros(7)):
对于C库的功能测试宏要求

`strtok_r(): _SVID_SOURCE || _BSD_SOURCE || _POSIX_C_SOURCE >= 1 || _XOPEN_SOURCE || _POSIX_SOURCE`

# DESCRIPTION

The  strtok()  function  breaks  a  string into a sequence of zero or more nonempty tokens.  
On the first call to strtok() the string to be parsed should be specified in str.  
In each subsequent call that should parse the same string, str must be NULL.
	   
strtok() 函数把字符串分为零个或多个非空标记的序列
首次调用时，将要被解析的字符串应该被指定在 str 参数中
随后的解析同一个字符串的每个调用中，str 参数必须是 NULL
	   
The delim argument specifies a set of bytes that delimit the tokens in the parsed string.  
The caller may specify different strings  in  delim  in successive calls that parse the same string.
	   
delim 参数指定了一组用于分割字符串中的标记的字节
在连续的解析同一个字符串的调用中，调用者可以在 delim 参数中指定不同的字符串

Each  call to strtok() returns a pointer to a null-terminated string containing the next token.  
This string does not include the delimiting byte.
If no more tokens are found, strtok() returns NULL.
	  
每次调用返回一个指向包含下一个标记的非结束字符串
此字符串不包括分割字节
若未找到更多标记，则函数返回 NULL

A sequence of calls to strtok() that operate on the same string maintains a pointer 
that determines the point from which to  start  searching  for the next token.  
The first call to strtok() sets this pointer to point to the first byte of the string.  
The start of the next token is determined by scanning forward for the next nondelimiter byte in str.  
If such a byte is found, it is taken as the start of the next token.  
If no such  byte is found, then there are no more tokens, and strtok() returns NULL.  
(A string that is empty or that contains only delimiters will thus cause strtok() to return NULL on the first call.)

操作同一的字符串的对 strtok 函数的一系列调用维护了一个指针
这个指针决定了从哪里开始搜索下一个标记的点
对 strtok 函数的首次调用使这个指针指向字符串的第一个字节
下一个标记的开始通过向前扫描得到字符串中下一个非分隔符字节来确定
如果找到这样的字节，它就作为下一个标记开始
如果没有找到这样的字节，那表示没有更多的标记，strtok 函数返回 NULL
空字符串或者只包含分隔符的字符串会导致 strtok 在首次调用时就返回 NULL

The end of each token is found by scanning forward until either the next delimiter byte is found or until the  terminating  null  byte  ('\0')  is encountered.  
If a delimiter byte is found, it is overwritten with a null byte to terminate the current token, and strtok() saves a pointer to the following byte; 
that pointer will be used as the starting point when searching for the next token.  
In this case, strtok() returns  a  pointer  to the start of the found token.

找到标记的结束是通过向前扫描直到下一个分隔符被找到或者直到遇到字符串结束符
如果找到分割字节，则该分割字节被空字节覆盖来终止当前标记，并且 strtok 函数保存指向下一个字节的指针
这个指针将被用做搜索下一个标记时的起始点
这种情况下，strtok 返回指向找到的标记的起始点的指针

From the above description, it follows that a sequence of two or more contiguous delimiter bytes in the parsed string is considered to be a single delimiter, 
and that delimiter bytes at the start or end of the string are ignored.  
Put another way: the tokens returned by  strtok()  are  always nonempty  strings.   
Thus,  for  example,  given the string "aaa;;bbb,", 
successive calls to strtok() that specify the delimiter string ";," would return the strings "aaa" and "bbb", and then a null pointer.

从以上的描述中，它遵循：被解析的字符串中的两个或多个相连的分隔符字节序列被认为是一个单独的分隔符
并且字符串开始或末尾的分隔符字节将被忽略
换种方式说：strtok 函数返回的标记总是非空字符串
如此，例如：给出"aaa;;bbb,"这样一个字符串
连续调用指定";,"作为分隔符的 strtok 函数将会返回字符串"aaa", "bbb"和 NULL 指针

The strtok_r() function is a reentrant version strtok().  
The saveptr argument is a pointer to a char * variable that is used internally  by  strtok_r() 
in order to maintain context between successive calls that parse the same string.

strtok_r 函数是 strtok 函数的可再入版本
saveptr 参数是字符型指针变量，用于 strtok_r 函数内部
为了维护解析相同字符串的连续调用的上下文环境

On  the  first  call  to  strtok_r(),  str should point to the string to be parsed, and the value of saveptr is ignored.  
In subsequent calls, str should be NULL, and saveptr should be unchanged since the previous call.

首次调用 strtok 时，str 参数应该指向被解析字符串，并且 saveptr 参数的值被忽略。
随后的调用中，str 参数应为 NULL，并且 saveptr子之前的调用后不应被改变。

Different strings may be parsed concurrently using sequences of calls to strtok_r() that specify different saveptr arguments.
对不同的字符串可以在使用一系列 strtok_r 函数调用并发进行解析时，指定不同的 saveptr 参数。

#RETURN VALUE

The strtok() and strtok_r() functions return a pointer to the next token, or NULL if there are no more tokens.

strtok() 和 strtok_r() 函数返回指向下一个标记的指针或者在没有更多的标记的情况下返回 NULL

# ATTRIBUTES

For an explanation of the terms used in this section, see attributes(7).

│Interface | Attribute | Value |
| - | - | - |
| strtok() | Thread safety | MT-Unsafe race:strtok |
| strtok_r() | Thread safety | MT-Safe |

# CONFORMING TO

strtok()
      POSIX.1-2001, POSIX.1-2008, C89, C99, SVr4, 4.3BSD.

strtok_r()
      POSIX.1-2001, POSIX.1-2008.

# BUGS

Be cautious when using these functions.  If you do use them, note that:

使用这些函数需要小心。如果你使用他们，注意以下：

* These functions modify their first argument.

* 这些函数修改他们的第一个参数。

* These functions cannot be used on constant strings.

* 这些函数不能被用于常量字符串。

* The identity of the delimiting byte is lost.

* 分隔符字节的一致性将丢失。

* The strtok() function uses a static buffer while parsing, so it's not thread safe.  Use strtok_r() if this matters to you.

* 在解析过程中，strtok 函数使用静态缓存，因此它不是线程安全的。如果这对你很重要，应使用 strtok_r 函数
