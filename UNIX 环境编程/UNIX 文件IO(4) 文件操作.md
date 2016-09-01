# 1. 打开文件

```
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int open(const char *pathname, int flags /* , mode_t mode */);
```

## 1. 文件状态标志 file status flags

1. 内核结构: 文件表项
2. 定义: fcntl.h

前5个为方式位, 必须选择且仅选择其中一个, 用屏蔽字 O_ACCMODE(0x0011) 取得

| macro       | value    | meaning |
| ----------- | -------- | ------- |
| O_RDONLY    | 0H       | 只读打开 |
| O_WRONLY    | 1H       | 只写打开 |
| O_RDWR      | 2H       | 读写打开 |
| O_EXEC      | N/A      | 只执行打开 |
| O_SEARCH    | N/A      | 只搜索打开(应用于目录, 验证搜索权限) |
| O_NONBLOCK  | 4H       | 非阻塞方式 |
| O_APPEND    | 8H       | 追加写, 修改当前文件偏移量 |
| O_SYNC      | 80H      | 每次 write 等待物理 I/O 操作完成, 数据和属性同步更新 |
| O_NOFOLLOW  | 100H     | 不可引用符号链接, path 引用符号链接则报错 |
| O_CREAT     | 200H     | 若文件不存在则创建它, 若已存在则看 O_EXCL 标志 |
| O_TRUNC     | 400H     | 截断 |
| O_EXCL      | 800H     | 若文件已存在则出错 |
| O_NOCTTY    | 20000H   | 若引用终端设备, 则不作为控制终端 |
| O_DIRECTORY | 100000H  | 必须引用目录, path 引用不是目录则报错 |
| O_DSYNC     | 400000H  | 每次 write 等待物理 I/O 操作完成, 数据同步更新, 不需等待属性更新 |
| O_CLOEXEC   | 1000000H | 文件描述符标志, 执行 exec 时关闭 |

## 2. 文件访问权限

1. 内核结构: v 节点表项
2. 定义: fcnlt.h

| macro   | value    | meaning |
| ------- | -------- | ---------------------------------- |
| S_ISUID            | 04000 | 文件的（set user-id on execution）位 |
| S_ISGID            | 02000 | 文件的（set group-id on execution）位 |
| S_ISVTX            | 01000 | 文件的sticky位 |
| S_IRUSR (S_IREAD)  | 00400 | 文件所有者具可读取权限 |
| S_IWUSR (S_IWRITE) | 00200 | 文件所有者具可写入权限 |
| S_IXUSR (S_IEXEC)  | 00100 | 文件所有者具可执行权限 |
| S_IRGRP            | 00040 | 用户组具可读取权限 |
| S_IWGRP            | 00020 | 用户组具可写入权限 |
| S_IXGRP            | 00010 | 用户组具可执行权限 |
| S_IROTH            | 00004 | 其他用户具可读取权限 |
| S_IWOTH            | 00002 | 其他用户具可写入权限 |
| S_IXOTH            | 00001 | 其他用户具可执行权限 |

# 2. 文件偏移

```
#include <sys/types.h>
#include <unistd.h>
off_t lseek(int fd, off_t offset, int whence);
```

## 1. 文件偏移量基准

1. 内核结构: 文件表项
2. 定义: unistd.h

| 宏 | 值 | 含义 |
| - | - | - |
| SEEK_SET | 0 | 文件起始处 |
| SEEK_CUR | 1 | 当前文件偏移量 |
| SEEK_END | 2 | 文件末尾(文件长度) |

lseek 函数并不引起任何 I/O 操作, 仅将当前的文件偏移量记录在内核中, 用于下次读写操作

# 3. fcntl 函数

```
#include <unistd.h>
#include <fcntl.h>
int fcntl(int fd, int cmd, ...);
```

文件描述符标志在进程表项中

文件状态标志在文件表项中

## 1. fcntl 命令参数

| 命令 | 值 | 作用 |
| --------------- | - | - |
| F_DUPFD         |  | 复制已有文件描述符, 共享同一文件表项, 新文件描述符标志的 FD_CLOEXEC 被清除, 返回新的文件描述符 |
| F_DUPFD_CLOEXEC |  | 复制已有文件描述符, 设置与新文件描述符关联的 FD_CLOEXEC 文件描述符标志的值, 返回新的文件描述符 |
| F_GETFD         |  | 获取文件描述符标志 FD_CLOEXEC, 返回该标志|
| F_SETFD         |  | 设置文件描述符标志, 由第3个参数指定 |
| F_GETFL         |  | 获取文件状态标志, 返回相应标志 |
| F_SETFL         |  | 设置文件状态标志 |
| F_GETOWN        |  | 获取异步 I/O 所有权, 返回正的进程 ID 或负的进程组 ID |
| F_SETOWN        |  | 设置异步 I/O 所有权 |
| F_GETLK         |  | 获取记录锁 |
| F_SETLK         |  | 设置记录锁 |
| F_SETLKW        |  | 设置记录锁 |

# 4. ioctl 函数

```
#include <unistd.h>		/* System V */
#include <sys/ioctl.h>	/* BSD and Linux */
int ioctl(int fd, int request, ...);
```

用于杂项设备操作

## 1. ioctl 命令参数

| 类别 | 常量名 | 头文件 | ioctl 数 |
| --------- | ------- | ----------------- | - |
| 盘标号     | DIOxxx  | sys/disklabel.h   | 4 |
| 文件 I/O   | FIOxxx  | sys/filio.h      | 14 |
| 磁带 I/O   | MTIOxxx | sys/mtio.h       | 11 |
| 套接字 I/O | SIOxxx  | sys/sockio.h     | 73 |
| 终端 I/O   | TIOxxx  | sys/ttycom.h     | 43 |

# 总结

1. 若文件已存在，则调用 create 函数会将该文件清空
2. 写失败的可能情况有: 磁盘空间已满

# 参考

[chmod 函数改变文件的权限](http://www.iteedu.com/os/linux/linuxprgm/linuxcfunctions/filepermission/chmod.php)
