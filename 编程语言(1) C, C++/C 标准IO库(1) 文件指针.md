# 1. 流 stream

## 1.1 流的定向 stream's orientation

### 1. 字节定向

使用单字节I/O函数时

### 2. 宽定向

使用多字节I/O函数时

## 1.2 清除流的定向

freopen 函数

## 1.3 设置流的定向

```
#include <stdio.h>
#include <wchar.h>
fwide(FILE *fp, int mode);	// 宽定向返回正数，未定向返回0，字节定向返回负数
```

# 2. FILE 对象

## 2.1 FILE 结构内容

1. 用于实际IO的文件描述符
2. 指向用于该流缓冲区的指针
3. 缓冲区的长度
4. 当前在缓冲中的字符数
5. 出错标志

## 2.2 文件指针

指向FILE对象的指针称为文件指针

# 3. 缓冲

## 3.1 缓冲区的获得

在一个流上执行第一次IO操作时，相关的标准IO函数调用 malloc 函数获得需使用的缓冲区

## 3.2 缓冲类型

### 1. 全缓冲

填满缓冲区后才进行实际的IO操作

驻留在磁盘上的文件通常使用全缓冲

### 2. 行缓冲

当在输入和输出中遇到换行符时，标准IO库执行IO操作

可以使用 fputc 函数一次输出一个字符，但只有在写了一行之后才进行实际的IO操作

标准输入流、标准输出流通常使用行缓冲

**注意**

1. 行缓冲区长度是固定有限的，如果填满行缓冲区而还没有写一个换行符，也要进行IO操作
2. 标准IO库例程需要从内核请求输入数据时，则会冲洗所有行缓冲输出流

**何时需要从内核读数据？**

1. 从一个不带缓冲的流中输入时
2. 从一个行缓冲的流中输入且所需数据不完全在行缓冲区中时

### 3. 不带缓冲

标准IO库不对字符进行缓冲存储

标准错误流通常使用不带缓冲的IO

## 3.3 修改已打开流的缓冲类型

```
#include <stdio.h>
void setbuf(FILE *restrict fp, char *restrict buf);
int setvbuf(FILE *restrict fp, char *restrict buf, int mode, size_t size);
```

mode 参数指定缓冲类型

| 常量 | 说明 |
| --- | --- |
| _IOFBF | 全缓冲 |
| _IOLBF | 行缓冲 |
| _IONBF | 不带缓冲 |

buf 非空, size 才有意义;

buf 为NULL, 则由系统分配缓冲区长度

## 3.4 缓冲区长度

stdio.h 中定义的 BUFSIZ 常量

stat 结构中 st_blksize 成员

# 4. 冲洗 flush

冲洗是指将缓冲区中的内容写到磁盘上

缓冲区写满时，标准IO例程会自动冲洗

调用 fflush 函数冲洗一个流

```
#include <stdio.h>
int fflush(FILE *fp);
```

1. 若 fp 非空，使该流所有未写的数据都被传送至内核
2. 若 fp 为空，使所有输出流被冲洗

# 5. 文件描述符

每个标准 I/O 流都有一个与其想关联的文件描述符

```
#include <stdio.h>
int fileno(FILE *fp);
```
