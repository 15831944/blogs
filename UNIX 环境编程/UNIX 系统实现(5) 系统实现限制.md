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





