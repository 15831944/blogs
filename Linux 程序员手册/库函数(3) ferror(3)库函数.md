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
