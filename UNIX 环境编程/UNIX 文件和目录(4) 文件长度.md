# 文件长度

| 文件类型 | 文件长度 |
| --- | --- |
| 普通文件 | 可以为0, 具有文件结束标志 |
| 目录文件 | 某个数(如16或512)整数倍 |
| 符号链接 | 所指向路径名的实际字节数 |

在 stat 结构成员 st_size 中以字节数表示

具有空洞的文件中，文件长度(字节数)会大于文件实际占用内存的字节数

# 文件截断

```
#include <unistd.h>
#include <sys/types.h>
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
```
