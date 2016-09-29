# 概述

记录锁 record locking

字节范围锁 byte-range locking

# 记录锁的形式

| 函数 | 说明 |
| - | - |
| flock | 只能对整个文件加锁 |
| fcntl | 可对文件任意字节数区域加锁, POSIX.1 标准的基础 |
| lockf | 简化了接口 |

# fcntl 功能

1. Duplicating a file descriptor                    复制文件描述符
3. File descriptor flags                            操作文件描述符标志 close_on_exec
3. File status flags                                操作文件状态标志 O_RDONLY, O_WRONLY, O_RDWR 等
4. Advisory locking                                 建议性锁
5. Mandatory locking                                强制性锁
6. Managing signals                                 管理信号
7. Leases                                           租借锁
8. File and directory change notification (dnotify) 文件和目录更改消息
9. Changing the capacity of a pipe                  改变管道大小

# 记录锁的种类

1. 建议性锁 Advisory locking
2. 强制性锁 Mandatory locking

To make use of mandatory locks, mandatory locking must be enabled both on the filesystem that contains the file to be locked, and on the file itself.

Mandatory locking is enabled on a filesystem using the "-o mand" option to mount(8), or the MS_MANDLOCK flag for mount(2).

Mandatory locking is enabled on a file by disabling group execute permission on the file and enabling the set-group-ID permission bit (see chmod(1) and chmod(2)).

这是说，要实现强制性锁则须将文件所在的文件系统用"-o　mand"参数来挂载，并且使用chmod函数将文件用户组的x权限去掉。代码与建议性锁相同。

# fcntl 记录锁

```
#include <fcntl.h>
int fcntl(int fd, int cmd, struct flock flockptr);
```

## 命令

| cmd      | 说明 |
| -------- | --- |
| F_GETLK  | 判断由 flockptr 所描述的锁是否会被另外一把锁排斥, 返回锁拥有者的进程 ID |
| F_SETLK  | 设置由 flockptr 所描述的锁 |
| F_SETLKW | 设置失败则阻塞(wait) |

### 加锁

先用 F_GETLK 测试能否建立一把锁, 新锁由 flockptr 描述, 若该区域已有锁, 则新锁会被已有锁排斥, 已有锁将覆盖 flockptr, 若该区域未被锁, 则 flockptr 结构的 l_type 成员设为 F_UNLCK;

然后用 F_SETLK 或 F_SETLKW 企图建立那把锁, 要设置的锁由 flockptr 描述为 F_RDLCK 或 F_WRLCK, 若使用 F_SETLK, 无法获取则立即出错返回,  errno 设置为 EAGAIN; 若使用 F_SETLKW, 无法获取则阻塞, 直到请求创建的锁已经可用或者收到信号中断休眠.

### 清除锁

使用 F_SETLK, 指定 flockptr 结构的 l_type 为 F_UNLCK.

## flock 结构体

| l_type  | 说明 |
| ------- | - |
| F_RDLCK | 共享读锁, 文件描述符必须是读打开 |
| F_WRLCK | 独占性写锁, 文件描述符必须是写打开 |
| F_UNLCK | 解锁一个区域(未上锁) |

## 不同进程提出锁请求的兼容性

1. 在一个给定的字节上任意多个进程可以各有一把共享的读锁
2. 在一个给定字节上只能有一个进程有一把独占写锁
3. 在一个给定字节上已经有一把或多把读锁, 则不能在该字节上再加写锁
4. 在一个给定字节上已经有一把独占性写锁, 则不能再对它加任何锁

## 单个进程锁请求的兼容性

新锁将替换已有的锁

# 加锁区

不同的加锁区变得相邻时会成为一个加锁区

# 疑问

不同进程是否需要有共同的父进程？

进程休眠是否会导致锁失效？

# 参考

[linux系统编程之struct flock 结构体](http://blog.csdn.net/wallwind/article/details/7816221)

[fcntl函数加文件锁](http://www.linuxidc.com/Linux/2015-04/115758.htm)
