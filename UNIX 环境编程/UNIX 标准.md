# ISO C

ISO C 库可以分成24个区(头文件)

| num | header     |  describe                    |
| --- | ---------- | ---------------------------- |
| 1   | assert.h   |                              |
| 2   | complex.h  |                              |
| 3   | ctype.h    | 字符属性分类和转换              |
| 4   | errno.h    | 出错码                        |
| 5   | fenv.h     |                              |
| 6   | float.h    | 浮点常量及特性                 |
| 7   | inttypes.h |                              |
| 8   | iso646.h   |                              |
| 9   | limits.h   | 实现常量                      |
| 10  | locale.h   |                              |
| 11  | math.h     |                              |
| 12  | setjmp.h   |                              |
| 13  | signal.h   | 信号                         |
| 14  | stdarg.h   | 可变长度参数表                 |
| 15  | stdbool.h  |                              |
| 16  | stddef.h   | 标准定义                      |
| 17  | stdint.h   |                              |
| 18  | stdio.h    | 标准 I/O 库，其实现依赖于操作系统 |
| 19  | stdlib.h   | 实用函数                       |
| 20  | string.h   | 字符串操作                     |
| 21  | tgmath.h   |                              |
| 22  | time.h     | 时间和日期                     |
| 23  | wchar.h    |                              |
| 24  | wctype.h   | 宽字符属性分类和转换              |

## 3 ctype.h

标准属性判断函数

isalnum		isalpha		iscntrl		isdigit		
isxdigit	isgraph		isprint		ispunct
islower		isupper		isspace		isblank

标准属性转换函数

tolower		toupper

glibc 扩展的函数

isctype		isascii		toascii

## 18 stdio.h

FILE EOF NULL size_t

fopen fclose fflush frepoen fwide FOPEN_MAX FILENAME_MAX

setvbuf setbuf BUFSIZ \_IOFBF \_IOLBF \_IONBF

stdin stdout stderr

fseek ftell rewind fgetops fsetpos fpos_t SEEK_SET SEEK_CUR SEEK_END

fgetc fgetwc getc getwc getchar getwchar ungetc ungetwc

fgets fgetws gets

fscanf fwscanf scanf wscanf sscanf swscanf

fputc fputwc putc putwc putchar putwchar

fputs fputws puts

fprintf printf sprintf snprintf fwprintf wprintf swprintf

vfprintf vprintf vsprintf vfscanf vscanf vsscanf vfwprintf vwprintf vswprintf vfwscanf vwscanf vswscanf

fread fwrite

feof ferror clearerr

remove rename

tmpfile tmpnam L_tmpnam TMP_MAX

perror

# IEEE POSIX

必须接口头文件

| header        | describe |
| ------------- | -------- |
| aio.h         |  |
| cpio.h        |  |
| dirent.h      | 目录项 |
| dlfcn.h       |  |
| fcntl.h       | 文件控制 |
| fnmatch.h     |  |
| glob.h        |  |
| grp.h         |  |
| iconv.h       | 代码集变换实用程序 |
| langinfo.h    |  |
| monetary.h    |  |
| netdb.h       |  |
| nl_types.h    |  |
| poll.h        |  |
| pthread.h     | 线程 |
| pwd.h         | 口令文件 |
| regex.h       | 正则表达式 |
| sched.h       |  |
| semaphore.h   | 信号量 |
| strings.h     |  |
| tar.h         |  |
| termios.h     |  |
| unistd.h      | 符号常量 |
| wordexp.h     |  |
| -             |  |
| arpa/inet.h   |  |
| net/if.h      |  |
| netinet/in.h  |  |
| netient/tcp.h |  |
| -             |  |
| sys/mman.h    |  |
| sys/select.h  | select 函数 |
| sys/socket.h  | 套接字接口 |
| sys/stat.h    |  |
| sys/statvfs.h |  |
| sys/times.h   |  |
| sys/types.h   |  |
| sys/un.h      | UNIX 域套接字定义 |
| sys/utsname.h |  |
| sys/wait.h    |  |

## fcntl.h

open openat create fcntl

O_RDONLY O_WRONLY O_RDWR

## unistd.h

close lseek read write dup dup2 sync fsync fdatasync

STDIN_FILENO STDOUT_FILENO STDERR_FILENO

## sys/ioctl.h

ioctl

可选接口头文件: 40个功能分区, 用选项码标识, 依赖于特性选项的支持

## 1. XSI 可选头文件

## 2. 可选头文件

## 3. 可选接口组和选项码

# SUS

Open Group 拥有 UNIX 商标并出版 SUS

遵循 XSI 的实现才能成为 UNIX

| 选项组     | 标记 |
| --------- | ---- |
| 加密       | 由符号常量 _XOPEN_CRYPE 标记 |
| 实时       | 有符号常量 _XOPEN_REALTIME 标记 |
| 高级实时    |  |
| 实时线程    | 由符号常量 _XOPEN_REALTIME_TRREADS 标记 |
| 高级实时线程 | 无 |

# 参考

1. [C标准库源码解剖(1)：类型相关的定义](http://www.aspku.com/kaifa/net/31612.html)
2. [C标准库源码解剖(2)：错误报告errno.h](http://www.aspku.com/kaifa/net/31613.html)
