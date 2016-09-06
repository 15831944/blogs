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
