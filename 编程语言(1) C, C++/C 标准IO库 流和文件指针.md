# 流的定向 stream's orientation

1. 字节定向: 使用单字节I/O函数时
2. 宽定向: 使用多字节I/O函数时
3. 使用 fwide 函数设置流的定向
4. 使用 freopen 函数清除流的定向

# FILE 对象

1. 用于实际IO的文件描述符
2. 指向用于该流缓冲区的指针
3. 缓冲区的长度
4. 当前在缓冲中的字符数
5. 出错标志

# 文件指针

1. 指向 FILE 对象的指针称为文件指针

# 缓冲区

1. 在一个流上执行第一次IO操作时，调用的标准IO函数调用 malloc 函数获得需使用的缓冲区
2. 全缓冲: 填满缓冲区后才进行实际的IO操作, 驻留在磁盘上的文件通常使用全缓冲
3. 行缓冲: 当在输入和输出中遇到换行符时，标准IO库执行IO操作, 可以使用 fputc 函数一次输出一个字符，但只有在写了一行之后才进行实际的IO操作, 在那之前只是程序和缓冲区之间的操作, 标准输入流、标准输出流通常使用行缓冲
4. 行缓冲中, 行缓冲区长度是固定有限的，如果填满行缓冲区而还没有写一个换行符，也要进行IO操作
5. 行缓冲输出中, 标准IO库例程需要从内核请求输入数据时，则会冲洗所有行缓冲输出流, 例如, 从一个不带缓冲的流中输入时或从一个行缓冲的流中输入且所需数据不完全在行缓冲区中时
6. 不带缓冲: 标准IO库不对字符进行缓冲存储, 标准错误流通常使用不带缓冲的IO
7. 缓冲区长度: stdio.h 中定义的 BUFSIZ 常量, stat 结构中 st_blksize 成员
8. 使用 setbuf 和 setvbuf 函数修改已打开的流的缓冲类型, 可指定为 \_IOFBF, \_IOLBF, \_IONBF
9. 输出需要缓冲, 但输入为什么需要缓冲?

# 冲洗 flush

1. 冲洗是指将缓冲区中的内容写到磁盘上
2. 缓冲区写满时，标准IO例程会自动冲洗
3. 调用 fflush 函数冲洗一个流, 将指定流或所有流中所有未写的数据都被传送至内核

# 文件描述符

1. 每个标准 I/O 流都有一个与其想关联的文件描述符
2. 使用 fileno 函数获取指定流的文件描述符

# 流的打开和关闭

1. 使用 fopen, fdopen, freopen 函数打开流
2. fdopen 函数使一个标准IO流与已有的文件描述符相结合, 一般使用创建管道和网络通信通道的函数返回的描述符, 另外它无法用于截断或创建文件
3. freopen 函数重新打开流并清除该流的定向, 可用于将指定文件打开为一个预定的流(标准输入、标准输出、标准错误)
4. 指定 w 或 a 类型创建一个文件时, 我们无法说明该文件的访问权限位
5. mode 参数可接字母 b 以二进制方式打开流, 但在 UNIX 环境下与文本方式并无区别
6. 使用 fclose 函数关闭流, 文件被关闭前, 会冲洗缓冲中的输出数据, 丢弃缓冲中的输入数据并释放缓冲区

# 打开文件状态(mode 参数)

| mode |  文件状态标志               | 说明 |
| ---- | ------------------------- | --- |
| r    | O_RDONLY                  | 只读打开 |
| w    | O_WRONLY O_CREAT O_TRUNC  | 截断后写 |
| a    | O_WRONLY O_CREAT O_APPEND | 在文件尾写 |
| r+   | O_RDWR                    | 读写打开 |
| w+   | O_RDWR O_CREAT O_TRUNC    | 截断后读写 |
| a+   | O_RDWR O_CREAT O_APPEND   | 在文件尾读写 |

# 非格式化I/O

1. 每次一个字符的I/O包括 getc, putc, fgetc, fputc, getchar, putchar 函数
2. 每次一行的I/O包括 \*gets, puts, \*fgets, fputs 函数
3. fgets 函数保留换行符, gets 函数删除换行符, 类似于C++中的 get() 和 getline() 方法
4. 直接I/O又称二进制I/O, 一次一个对象I/O, 面向记录的I/O, 面向结构的I/O, 常用于读写一个二进制数组或读写一个结构
5. 直接I/O包括 fread, fwrite 函数

# fread, fwrite 函数为什么一般以二进制方式打开文件

1. 可能会丢失精度，1.0/3的结果用文本存和用二进制存，再次读取出来的结果会不一样
2. 二进制能存数组和结构一类的数据
3. fread 和 fwrite 是按数据块的长度来处理输入输出的，在字符发生转换的情况下很可能出现与原设想的情况不同的结果

## 2.4 出错检查

```
#include <stdio.h>
int ferror(FILE *stream);
int feof(FILE *stream);
void clearerr(FILE *stream);
```

FILE 对象中维护的2个标志

1. 出错标志
2. 文件结束标志 EOF -1

clearerr H函数清除这2个标志

# 2.5 将读取数据压回流缓冲区中

```
#include <stdio.h>
int ugetc(int c, FILE *fp);
```

读出字符顺序与回送顺序相反
一次只回送一个字符
回送的字符不一定是上次读到的字符
不能回送EOF
已经达到文件尾时仍可回送一个字符，因为成功调用 ugetc 函数将清楚该流的文件结束标志


# 3. 格式化I/O

```
#include <stdio.h>
#include <stdarg.h>

int printf(const char *restrict format, ...);
int fprintf(FILE *restrict fp, const char *restrict format, ...);
int dprintf(int fd, const char *restrict format, ...);
int sprintf(char *restrict buf, const char *restrict format, ...);
int snprintf(char *restrict bur, size_t n, cosnt char *restrict format, ...);

int vprintf(const char *restrict format, va_list arg);
int vfprintf(FILE *restrict fp, const char *restrict format, va_list arg);
int vdprintf(int fd, const char *restrict format, va_list arg);
int vsprintf(char *restrict buf, const char *restrict format, va_list arg);
int vsnprintf(char *restrict bur, size_t n, const char *restrict format, va_list arg);

int scanf(const char *restrict format, ...);
int fscanf(FILE *restrict fp, const char *restrict format, ...);
int sscanf(const char *restrict buf, const char *restrict format, ...);

int vscanf(const char *restrict format, va_list arg);
int vfscanf(FILE *restrict fp, const char *restrict format, va_list arg);
int vsscanf(const char *restrict buf, const char *restrict format, va_list arg);
```

## 3.1 格式化输出转换说明

%\[flags\]\[fldwidth\]\[precision\]\[lenmodifier\]convtype

### 1. 标志 flag

| flag  | 说明 |
| ----- | --- |
| '     | 将整数按千位分组字符 |
| -     | 在字段内左对齐输出 |
| +     | 总是显示带符号转换的正负号 |
| space | 如果第一个字符不是正负号,则在其前面加上一个空格 |
| #     | 指定另一种转换格式 |
| 0     | 添加前导0进行填充 |

### 2. 宽度 fldwidth

非负十进制数

星号

### 3. 精度 precision

1. 整型转换后最少输出数字位数
2. 浮点数转换后小数点后的最少位数
3. 字符串转换后最大字节数

点加非负十进制数

点加星号

### 4. 长度修饰符 lenmodifier

| lenmodifier | 说明 |
| --- | --- |
| hh  | char |
| h   | short |
| l   | long |
| ll  | long long |
| j   | intmax_t uintmax_t |
| z   | size_t |
| t   | ptrdiff_t |
| L   | long double |

### 5. 转换类型符 convtype

| convtype | 说明 |
| -------- | --- |
| d i      | 十进制 |
| o        | 八进制 |
| u        | 十进制(无符号) |
| x        | 十六进制 |
| f        | 双精度浮点数 |
| e        | 双精度浮点数(指数格式) |
| g        | 根据转换后的值解释为 f F e E |
| a        | 双精度浮点数(十六进制指数格式) |
| c        | 字符 |
| s        | 字符串 |
| p        | void 指针 |
| n        |  |
| %        | % |
| C        | 宽字符 |
| S        | 宽字符串 |

## 3.2 格式化输入转换说明

%\[\*\]\[fldwidth\]\[m\]\[lenmodifier\]convtype

### 1. 星号

用于抑制转换

### 2. 宽度

最大字符数

### 3. 长度修饰符

说明要用转换结果赋值的参数大小

### 4. 转换类型符

| convtype | 说明 |
| -------- | --- |
| d        | 十进制, 基数为10 |
| i        | 十进制, 基数由输入格式决定 |
| o        | 八进制(无符号) |
| u        | 十进制(无符号) |
| x        | 十六进制(无符号) |
| f        | 双精度浮点数 |
| e        | 双精度浮点数(指数格式) |
| g        | 根据转换后的值解释为 f F e E |
| a        | 双精度浮点数(十六进制指数格式) |
| c        | 字符 |
| s        | 字符串 |
| [        | 匹配列出的字符序列, 以 ] 终止 |
| [^       | 匹配除列出的字符外的所有字符, 以 ] 终止 |
| p        | void 指针 |
| n        |  |
| %        | % |
| C        | 宽字符 |
| S        | 宽字符串 |

# 4 定位流

# 4.1 函数接口

```
#include <stdio.h>

/* 文件偏移量存放在 long 类型中 */
long	ftell(FILE *fp);
int		fseek(FILE *fp, long offset, int whence);

void	rewind(FILE *fp);

/* 文件偏移量存放在 off_t 类型中 */
off_t	ftello(FILE *fp);
int		fseeko(FILE *fp, off_t offset, int whence);

/* 文件偏移量存放在 fpos_t 类型中 */
int		fgetpos(FILE *restrict fp, fpos_t *restrict pos);
int		fsetpos(FILE *fp, const fpos_t *pos);
```

# 4.2 二进制文件

whence 取 SEEK_SET SEEK_CUR SEEK_END

offset 取任意整数表示的字节数

# 4.3 文本文件

不同的系统可能以不同的格式存放文本文件

whence 只能取 SEEK_SET

offset 只能取 0 或对该文件的 ftell 的返回值

# 5 流的实现

## 1 实现1

### 1.1 FILE 对象成员

| 成员 | 说明 |
| ------------ | --- |
| _flags       | 缓冲类型标志 |
| _IO_buf_end  | 缓冲区结束 |
| _IO_buf_base | 缓冲区开始 |

### 1.2 常量

| flag 屏蔽 | 说明 |
| -------------- | --- |
| _IO_UNBUFFERED | 无缓冲 |
| _IO_LINE_BUF   | 行缓冲 |

## 2. OS X 实现

### 2.1 FILE 对象成员

| 成员 | 说明 |
| ------------ | --- |
| _flags       | 缓冲类型标志 |
| _size        | 缓冲区长度 |

### 2.2 常量

| flag 屏蔽 | 说明 |
| -------------- | --- |
| __SNBF | 无缓冲 |
| __SLBF | 行缓冲 |

## 3. 实现3

### 3.1 FILE 对象成员

| 成员 | 说明 |
| ------------ | --- |
| _flags       | 缓冲类型标志 |
| _base        | 缓冲区结束 |
| _ptr         | 缓冲区开始 |

### 3.2 常量

| flag 屏蔽 | 说明 |
| -------------- | --- |
| _IONBF | 无缓冲 |
| _IOLBF | 行缓冲 |

# 6 内存流

文件流是存在于底层的实际的文件, I/O 通过缓冲区和磁盘或终端之间传送

内存流没有底层文件, 所有的 I/O 都是通过在缓冲区和主存之间来回传送字节来完成的

## 创建内存流

```
#include <stdio.h>
FILE *fmemopen(void *restrict buf, size_t size, const char *restrict type);
```

追加方式通过第一个 NULL 字节确定数据的结尾

# 参考

《UNIX环境高级编程》
