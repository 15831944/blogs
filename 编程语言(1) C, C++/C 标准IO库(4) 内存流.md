# 概述

文件流是存在于底层的实际的文件, I/O 通过缓冲区和磁盘或终端之间传送

内存流没有底层文件, 所有的 I/O 都是通过在缓冲区和主存之间来回传送字节来完成的

# 创建内存流

```
#include <stdio.h>
FILE *fmemopen(void *restrict buf, size_t size, const char *restrict type);
```

追加方式通过第一个 NULL 字节确定数据的结尾
