# 1. 功能测试宏的作用

Linux 系统下的库函数会有不同的标准的版本，例如 POSIX 或者 XOPEN，不同的标准可能定义相同的头文件。当程序被编译时，功能测试宏允许程序员控制编译时系统实际展开哪个标准的头文件的定义。

# 2. 对程序可移植性的影响

当创建可移植程序时：

1. 一些功能测试宏可以用于避免展开非标准定义

2. 另一些宏可以用于展开默认不会展开的非标准定义

# 3. 注意

为使宏定义生效，功能测试宏必须被定义在包含任意头文件以前。

有两种实现方式：

1. 在编译命令行中

2. 在包含任何头文件前使用源代码定义宏

# 4. 举例

若要使 fcntl.h 头文件包含 readahead 函数的声明，则必须定义 _GNU_SOURCE 宏，则使用以下两种方式的任意一种，可避免编译器报函数未声明错误

方式1

```
gcc -D_GNU_SOURCE source.c

```

方式2

```
#define _GNU_SOURCE
#include <fcntl.h>
```
# 5. 参考

man feature_test_macros

# 环境变量

ISO C 并没有定义任何环境变量，都是由 POSIX 和 SUS 定义的

# 环境表

# 环境变量

# 参考

UNIX 环境高级编程 7.5 7.9

# 系统数据文件

# 口令文件 password

/etc/passwd

passwd 结构

```
#include <pwd.h>
struct passwd *getpwuid(uid_t uid);
struct passwd *getpwnam(const char *name);
struct passwd *getpwent(void);
void setpwent(void);
void endpwent(void);
```

# 阴影口令 shadow password

/etc/shadow

spwd 结构

```
#include <shadow.h>
struct spwd *getspnam(const char *name);
struct spwd *getspent(void);
void setspent(void);
void endspent(void);
```

# 组文件 group

/etc/group

group 结构

```
#include <grp.h>
struct group *getgrgid(gid_t gid);
struct group *getgrnam(const char *name);
struct group *getgrent(void);
void setgrent(void);
void endgrent(void);
```

# 参考

UNIX 环境高级编程 6

# 日期和时间例程

# 1. 时间计量系统

时间计量系统有：世界时(UT)，国际原子时(TAI)，格林尼治标准时(GMT)，协调世界时(UTC)等等。

北京时间比 UTC 时间早8小时

UTC时间是1999年1月1日00:00

北京时间是1999年1月1日08:00

# 2. UNIX 系统时间值

UNIX 系统使用2种不同的时间值

## 1. 日历时间

1. 以协调世界时(UTC, Coordinated Universal Time)计量
2. 绝对时间，用于记录文件修改时间等
3. 系统基本数据类型 time_t

## 2. 进程时间

1. 又称 CPU 时间
2. 相对时间，用于度量进程使用 CPU 资源
3. 系统基本数据类型 clock_t

# 3. 时间和日期例程

参考 man page

```
#include <time.h>
void tzset(void);
time_t time(time_t *calptr);
time_t mktime(struct tm *tmptr);
struct tm *gmtime(const time_t *calptr);
struct tm *localtime(const time_t *calptr);
size_t strftime(char *restrict buf, size_t maxsize, const char *restrict format, const struct tm *restrict tmptr);
siet_t strftime_l(char *restrict buf, size_t maxsize, const char *restrict format, const struct tm *restrict tmptr, locale_t locale);

#include <sys/time.h>
int clock_gettime(clockid_t clock_id, struct timespec *tsp);
int clock_settime(clockid_t clock_id, const struct timespec *tsp);
int clock_getres(clockid_t clock_id, struct timespec *tsp);
int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
```

# 4. 示例

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char const *argv[])
{
	time_t         cal_time;	// 日历时间(s)
	struct timeval val_time;	// 日历时间(ns)
	struct tm     *brk_time;	// 分解时间
	struct timespec tsp;
	char buf[128];
	int rtn;

	time(&cal_time);
	printf("cal_time = %lds\n", cal_time);

	gettimeofday(&val_time, NULL);
	printf("val_time = %lds, %dns\n", val_time.tv_sec, val_time.tv_usec);

	brk_time = gmtime(&cal_time);
	printf("UTC_time =  %d-%d-%d %d:%d:%d\n", \
		brk_time->tm_year + 1900, brk_time->tm_mon + 1, brk_time->tm_mday, \
		brk_time->tm_hour, brk_time->tm_min, brk_time->tm_sec);

	printf("cal_time1 = %lds\n", mktime(brk_time));

	brk_time = localtime(&cal_time);
	printf("Local_time =  %d-%d-%d %d:%d:%d\n", \
		brk_time->tm_year + 1900, brk_time->tm_mon + 1, brk_time->tm_mday, \
		brk_time->tm_hour, brk_time->tm_min, brk_time->tm_sec);

	printf("cal_time2 = %lds\n", mktime(brk_time));

	rtn = strftime(buf, 128, "year = %Y month = %B day = %d week = %A", brk_time);
	printf("rtn =%d %s\n",rtn, buf);

	strcpy(buf,"2001-02-03 4:5:6");
	strptime(buf, "%F %T", brk_time);
	printf("str_time =  %d-%d-%d %d:%d:%d\n", \
		brk_time->tm_year + 1900, brk_time->tm_mon + 1, brk_time->tm_mday, \
		brk_time->tm_hour, brk_time->tm_min, brk_time->tm_sec);
	return 0;
}
```

## 1. 输出结果

```
cal_time = 1468111161s
val_time = 1468111161s, 719666ns
UTC_time =  2016-7-10 0:39:21
cal_time1 = 1468082361s
Local_time =  2016-7-10 8:39:21
cal_time2 = 1468111161s
rtn =47 year = 2016 month = July day = 10 week = Sunday
str_time =  2001-2-3 4:5:6
```

## 2. 分析

1. time 函数打印1970年至今的秒数，且是以本地时间计算的
2. gettimeofday 函数同理，但是具有更高的精度，纳秒级
3. 从分解时间可以看到，当地时间比标准时间快了8个小时
4. 可以用指定的字符串格式设置时间


# 5. 参考

UNIX 环境高级编程 1.10 6.10

# 系统实现限制

# 1. 操作系统实现限制

标准定义了操作系统在实现时的限制

1. 规定某些最大值最小（至少）是多少，实际实现中可以更大，严格符合此标准的应用则应小于这个最小值

2. 规定某些最小值最大（最多）是多少，实际实现中可以更小，严格符合此标准的应用则应大于这个最大值

3. 即实际的实现范围应比标准规定的范围更广，这样可以满足更大的需求

4. 即严格符合标准的应用应在标准规定的范围内，这样比较具有可移植性

5. 标准定义的限制值往往加了 \_POSIX\_ 或 \_XOPEN\_ 前缀，系统的具体实现值去掉这些前缀，获取限制值时函数中限制值名称参数再加上 \_SC\_ 或\_PC\_ 前缀


# 2. 限制的种类

## 1. 编译时限制

在头文件中定义

例如，短整型的最大值是什么

## 2. 运行时限制

要求进程调用相关函数来获得限制值

例如，文件名最多多少个字符（依赖于运行的文件系统）

### 1. 操作系统相关的运行时限制

sysconf 函数

### 2. 文件系统相关的运行时限制

pathconf 函数

fpathconf 函数

例如，文件名有多少个字符

# 3. ISO C 限制

所有编译时限制都列在limits.h 中

1. 整型值的编译时限制列在 limits.h 中

2. 浮点数的限制列在 float.h 中

3. 文件相关的限制

文件相关限制举例

| 限制 | 包含文件 | 含义 |
| - | - | - |
| FOPEN_MAX | stdio.h | 可以同时打开的标准 I/O 流的最小个数 |
| TMP_MAX | stdio.h | 由 tmpnam 函数产生的唯一文件名的最大个数 |
| FILENAME_MAX |  |  |

# 4. POSIX 限制

文件相关限制举例

| 限制 | 包含文件 | 含义 |
| - | - | - |
| STREAM_MAX |  | 同 FOPEN_MAX |
| NAME_MAX |  | 替代 FILENAME_MAX |
| PATH_MAX |  | 替代 FILENAME_MAX |

## 1. 编译时限制分类（常量）

### 1. 数值限制

LONG_BIT, SSIZE_MAX 和 WORD_BIT

### 2. 最小值

在 limits.h 中定义了25个可接受最小值的常量

_POSIX_OPEN_MAX

_POSIX_PATH_MAX

实现值为去掉\_POSIX_前缀

### 3. 最大值

_POSIX_CLOCKERS_MIN

## 2. 运行时限制分类（函数调用）

### 1. 运行时可增加值

CHARCLASS_NAME_MAX

COLL_WEIGHTS_MAX

LINE_MAX

NGROUPS_MAX

RE_DUP_MAX

### 2. 运行时不变值（可能不确定）

可能定义在给定系统的头文件中，也可能需要调用函数

ARG_MAX

ATEXIT_MAX

在 limits.h 中定义了17个常量

### 3. 其他不变值

NL_ARGMAX

NL_MSGMAX

NL_SETMAX

NL_TEXTMAX

### 4. 路径名可变值

即在不同的路径下，限制值是不同的

FILESIZEBITS

LINK_MAX

MAX_CANON

MAX_INPUT

NAME_MAX

PATH_MAX

PIPE_BUF

SYMLINK_MAX


# 5. XSI 限制

## 1. 最小值

NL_LANGMAX

NZERO

_XOPEN_IOV_MAX

_XOPEN_NAME_MAX

_XOPEN_PATH_MAX

在 limits.h 中定义

## 2. 运行时不变值

IOV_MAX

PAGE_SIZE5
# 6. 获取运行时限制的实现值

## 1. 操作系统相关的运行时限制

```
#include <unistd.h>
long sysconf(int name);
```
name 参数以 `_SC_` 开头

## 2. 文件系统相关的运行时限制

```
#include <unistd.h>
long pathconf(const char *pathname, int name);
long fpathconf(int fd, int name);
```
name 参数以 `_PC_` 开头

## 3. 限制文件

pathconf.sym

sysconfig.sym

这两个文件包含了用制表符分隔的限制名和符号列表（即实现值，用幻数表示）

# 7. 不确定的运行时限制

对于编译时限制，这些限制值可能没有在头文件中定义

对于运行时限制，这些限制值可能是未定义的

例如

路径名最大长度

最大打开文件数

# 出错处理
