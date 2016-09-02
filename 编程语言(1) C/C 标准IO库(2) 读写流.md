# 1. 打开和关闭流

```
#include <stdio.h>
FILE *fopen(const char *path, const char *mode);
FILE *fdopen(int fd, const char *mode);
FILE *freopen(const char *path, const char *mode, FILE *stream);
FILE *fclose(FILE *fp);
```

## 1.1 打开文件状态

| mode |  文件状态标志               | 说明 |
| ---- | ------------------------- | --- |
| r    | O_RDONLY                  | 只读打开 |
| w    | O_WRONLY O_CREAT O_TRUNC  | 截断后写 |
| a    | O_WRONLY O_CREAT O_APPEND | 在文件尾写 |
| r+   | O_RDWR                    | 读写打开 |
| w+   | O_RDWR O_CREAT O_TRUNC    | 截断后读写 |
| a+   | O_RDWR O_CREAT O_APPEND   | 在文件尾读写 |

对于 fdopen 函数 无法截断或创建

## 1.2 打开I/O流的限制

freopen 重新打开流并清除该流的定向, 将指定文件打开为一个预定的流(标准输入、标准输出、标准错误)

fdopen 使一个标准IO流与已有的文件描述符相结合, 使用创建管道和网络通信通道的函数返回的描述符

指定 w 或 a 类型创建一个文件时, 我们无法说明该文件的访问权限位

## 1.3 关闭I/O流

文件被关闭前

1. 冲洗缓冲中的输出数据
2. 丢弃缓冲中的输入数据
3. 释放缓冲区

# 2. 读写流

## 非格式化I/O

### 1. 每次一个字符的I/O

```
#include <stdio.h>
int		getc(FILE *stream);
int		fgetc(FILE *stream);
int		getchar(void);
int		putc(int c, FILE *stream);
int		fputc(int c, FILE *stream);
int		putchar(int c);
```

### 2. 每次一行的I/O

```
#include <stdio.h>
char *gets(char *s);
char *fgets(char *s, int size, FILE *stream);
int puts(const char *s);
int fputs(const char *s, FILE *stream);
```

fgets 保留换行符, gets 删除换行符

### 3. 直接I/O

fread fwrite

二进制I/O 一次一个对象I/O 面向记录的I/O 面向结构的I/O

## 格式化I/O

printf scanf

## 出错检查

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

## 将读取数据压回流缓冲区中

```
#include <stdio.h>
int ugetc(int c, FILE *fp);
```

读出字符顺序与回送顺序相反
一次只回送一个字符
回送的字符不一定是上次读到的字符
不能回送EOF
已经达到文件尾时仍可回送一个字符，因为成功调用 ugetc 函数将清楚该流的文件结束标志
