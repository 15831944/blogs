# strtok, strtok_r

```
#include <string.h>
char *strtok(char *str, const char *delim);
char *strtok_r(char *str, const char *delim, char **saveptr);
```

strtok() 函数把字符串分为零个或多个非空标记的序列, 首次调用时, 将要被解析的字符串应该被指定在 str 参数中, 随后的解析同一个字符串的每个调用中，str 参数必须是 NULL
delim 参数指定了一组用于分割字符串中的标记的字节, 在连续的解析同一个字符串的调用中, 调用者可以在 delim 参数中指定不同的字符串
每次调用返回一个指向包含下一个标记的非结束字符串, 此字符串不包括分割字节, 若未找到更多标记，则函数返回 NULL
操作同一的字符串的对 strtok 函数的一系列调用维护了一个指针, 这个指针决定了从哪里开始搜索下一个标记的点, 对 strtok 函数的首次调用使这个指针指向字符串的第一个字节, 下一个标记的开始通过向前扫描得到字符串中下一个非分隔符字节来确定, 如果找到这样的字节，它就作为下一个标记开始, 如果没有找到这样的字节，那表示没有更多的标记，strtok 函数返回 NULL, 空字符串或者只包含分隔符的字符串会导致 strtok 在首次调用时就返回 NULL
找到标记的结束是通过向前扫描直到下一个分隔符被找到或者直到遇到字符串结束符, 如果找到分割字节，则该分割字节被空字节覆盖来终止当前标记，并且 strtok 函数保存指向下一个字节的指针, 这个指针将被用做搜索下一个标记时的起始点, 这种情况下，strtok 返回指向找到的标记的起始点的指针
从以上的描述中，它遵循：被解析的字符串中的两个或多个相连的分隔符字节序列被认为是一个单独的分隔符, 并且字符串开始或末尾的分隔符字节将被忽略, 换种方式说：strtok 函数返回的标记总是非空字符串, 如此，例如：给出"aaa;;bbb,"这样一个字符串, 连续调用指定";,"作为分隔符的 strtok 函数将会返回字符串"aaa", "bbb"和 NULL 指针

strtok_r 函数是 strtok 函数的可再入版本, saveptr 参数是字符型指针变量，用于 strtok_r 函数内部, 为了维护解析相同字符串的连续调用的上下文环境
首次调用 strtok 时，str 参数应该指向被解析字符串，并且 saveptr 参数的值被忽略。随后的调用中，str 参数应为 NULL，并且 saveptr子之前的调用后不应被改变。
对不同的字符串可以在使用一系列 strtok_r 函数调用并发进行解析时，指定不同的 saveptr 参数。

# 注意 NOTE

A common mistake is to do

一个常见的错误是像下面这样

```
if (somecall() == -1)
{
	printf("somecall() failed\n");
	if (errno == ...) { ... }
}
```

where errno no longer needs to have the value it had upon return from somecall() (i.e., it may have been changed by the printf(3)).  If the  value
of errno should be preserved across a library call, it must be saved:

errno 已经不再具有 somecall() 的返回值了，它的值已经被 printf(3) 改变。如果。要保留系统调用的错误码，则它必须被保存：

```
if (somecall() == -1) {
		int errsv = errno;
		printf("somecall() failed\n");
		if (errsv == ...) { ... }
	}
```

# 名称 NAME

errno - number of last error

# 语法 SYNOPSIS

/#include <errno.h>

# 描述 DESCRIPTION

The errno.h header file defines the integer variable errno, which is set by system calls and some library functions in the event of an error to
indicate what went wrong.  Its value is significant only when the return value of the call indicated an error (i.e., -1 from most system calls; -1
or NULL from most library functions); a function that succeeds is allowed to change errno.

头文件 errno.h 定义了整型变量出错值，这些值在系统调用和一些库函数出错情况下被赋值，用来指出发生了哪种错误。

只有当调用的返回值指明一个错误时，它的值才有意义。（例如，大多系统调用返回-1，大多库函数返回NULL）

成功执行的函数也可以改变 erno 的值。

Valid error numbers are all nonzero; errno is never set to zero by any system call or library function.

有效的错误码都是非零的；errno 不会被任何系统调用或库函数设置为0.

For  some  system  calls and library functions (e.g., getpriority(2)), -1 is a valid return on success.  In such cases, a successful return can be
distinguished from an error return by setting errno to zero before the call, and then, if the call returns a status that indicates that  an  error
may have occurred, checking to see if errno has a nonzero value.

对于有些系统调用和库函数，-1 可以是执行成功的有效的返回值。这些情况中，成功的发返回和出错的返回值可以通过以下方式解决：
在调用前将 errno 设置为0，然后，如果调用返回状态指出可能有错误发生，可以检查 errno 是否为非零值即可。

errno is defined by the ISO C standard to be a modifiable lvalue of type int, and must not be explicitly declared; errno may be a macro.  errno is
thread-local; setting it in one thread does not affect its value in any other thread.

errno 由 ISO C 标准定义为一个可变的整型的左值，并且不可以被明确声明；errno 可能是宏。errno 是线程局部变量；在一个线程中修改它的值并不影响它在另一个线程中的值。

All the error names specified by POSIX.1 must have distinct values, with the exception of EAGAIN and EWOULDBLOCK, which may be the same.

POSIX.1 指定的错误名称必须有唯一值，除了 EAGAIN 和 EWOULDBLOCK，这俩是相同的。

Below is a list of the symbolic error names that are defined on Linux.  Some of these are marked POSIX.1, indicating that the name is  defined  by
POSIX.1-2001, or C99, indicating that the name is defined by C99.

以下是 Linux 下定义的符号错误名称列表。有些被 POSIX.2标记，指明其是由 POSIX.1-2001 定义的，C99同理。

# 常量

| 名称 | 含义 |
| - | - |
| E2BIG |  Argument list too long (POSIX.1) |
| EACCES | Permission denied (POSIX.1) |
| EADDRINUSE | Address already in use (POSIX.1) |
| EADDRNOTAVAIL | Address not available (POSIX.1) |
| 自行查阅即可 | 自行查阅即可 |

# 注意 NOTES

It  was  common  in traditional C to declare errno manually (i.e., extern int errno) instead of including <errno.h>.  Do not do this.  It will not work with modern versions of the C library.  However, on (very) old UNIX systems, there may be no <errno.h> and the declaration is needed.

在传统的 C 中，手动声明 errno 而不是包含 <errno.h> 是很常见的。但不要这样做。这对于现代版本的 C 库是无效的。然而，在非常老的 NUIX 系统中，可能没有 <errno.h> 头文件，则需要声明

# 参考 SEE ALSO

       errno(1), err(3), error(3), perror(3), strerror(3)

	   # 类型

	   标准 C 库函数
	   Standard C Library (libc, -lc)

	   # 声明

	   ```
	   #include <stdio.h>
	   int ferror(FILE *stream);



	   ```

	   # 功能

	    The function ferror() tests the error indicator for the stream pointed to by stream, returning non-zero if it is set.
	   函数参数为文件指针。
	   在调用各种输入输出函数时，如果出现错误，除了函数返回值有所反映外，还可以用ferror函数检查。
	   如果返回一个非零值，表示出错。
	   应该注意，对同一个文件（文件指针或文件描述符）每一次调用输入输出函数，均产生一个新的ferror函数值，因此，应当在调用一个输入输出函数后立即检查ferror函数的值，否则信息会丢失。
	   在执行fopen函数时，ferror函数的初始值自动置为0。

	   # 相关函数

	   ```
	   #include <stdio.h>

	   void clearerr(FILE *stream);
	   void clearerr_unlocked(FILE *stream);

	   int feof(FILE *stream);
	   int feof_unlocked(FILE *stream);

	   int ferror(FILE *stream);
	   int ferror_unlocked(FILE *stream);

	   int fileno(FILE *stream);
	   int fileno_unlocked(FILE *stream);
	   ```
