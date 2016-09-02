# 1. 概述

文件模式字包含以下信息

1. 文件类型
2. 设置用户ID位
3. 设置组ID位
4. 粘着位
5. 文件访问权限

## 1.1 st_mode 宏

| st_mode macro      | value                              |
| ------------------ | ---------------------------------- |
| S_ISREG(st_mode)   | (((st_mode) & S_IFMT) == S_IFREG)  |
| S_ISDIR(st_mode)   | (((st_mode) & S_IFMT) == S_IFDIR)  |
| S_ISLINK(st_mode)  | (((st_mode) & S_IFMT) == S_IFLNK)  |
| S_ISBLK(st_mode)   | (((st_mode) & S_IFMT) == S_IFBLK)  |
| S_ISCHR(st_mode)   | (((st_mode) & S_IFMT) == S_IFCHR)  |
| S_ISSOCK(st_mode)  | (((st_mode) & S_IFMT) == S_IFSOCK) |
| S_ISFIFO(st_mode)  | (((st_mode) & S_IFMT) == S_IFIFO)  |

## 1.2 st_mode 屏蔽

`sys/stat.h`

| st_mode constant   | value | 说明 |
| ------------------ | ----- | --- |
| S_IFMT             | f000H | 文件类型遮罩位 |
| S_IFSOCK           | c000H | 套接字文件 |
| S_IFLNK            | a000H | 符号链接 |
| S_IFREG            | 8000H | 普通文件 |
| S_IFBLK            | 6000H | 块特殊文件 |
| S_IFDIR            | 4000H | 目录文件 |
| S_IFCHR            | 2000H | 字符特殊文件 |
| S_IFIFO            | 1000H | FIFO |
| S_ISUID            | 4000H | 文件的（set user-id on execution）位 |
| S_ISGID            | 2000H | 文件的（set group-id on execution）位 |
| S_ISVTX            | 1000H | 文件的sticky位, 保存正文常量 |
| S_IRWXU            | 0700H | 文件所有者的遮罩值 |
| S_IRUSR, S_IREAD   | 0400H | 文件所有者具可读取权限 |
| S_IWUSR, S_IWRITE  | 0200H | 文件所有者具可写入权限 |
| S_IXUSR, S_IEXEC   | 0100H | 文件所有者具可执行权限 |
| S_IRWXG            | 0070H | 用户组的遮罩值 |
| S_IRGRP            | 0040H | 用户组具可读取权限 |
| S_IWGRP            | 0020H | 用户组具可写入权限 |
| S_IXGRP            | 0010H | 用户组具可执行权限 |
| S_IRWXO            | 0007H | 其他用户的遮罩值 |
| S_IROTH            | 0004H | 其他用户具可读取权限 |
| S_IWOTH            | 0002H | 其他用户具可写入权限 |
| S_IXOTH            | 0001H | 其他用户具可执行权限 |

# 2. 文件类型

7种文件类型

| 文件类型 | 符号 | 说明 |
| --------------------------------- | --- | -------------------------- |
| 普通文件(regular file)              | - |  |
| 目录文件(directory file)            | d |  |
| 符号链接(symbolic link)             | l |   |
| 块特殊文件(block special file)       | b | 对设备带缓冲访问, 每次访问长度不变 |
| 字符特殊文件(character special file) | c | 对设备不带缓冲访问, 每次访问长度可变 |
| 套接字(socket)                      | s |  |
| 命名管道(named pipe, FIFO)          | p |  |

3个进程间通信(IPC)对象

| IPC 对象类型 | 宏 |
| ---------- | ------------------ |
| 消息队列    | S_TYPEISSMQ(stat*) |
| 信号量      | S_TYPEISSEM(stat*) |
| 共享存储对象 | S_TYPEISSHM(stat*) |

# 3. 设置用户ID位和设置组ID位

设置用户 ID (set-user-ID)

设置组 ID (set-group-ID)

## 3.1 ID 类型

与一个进程相关的 ID 有6个

| ID 类型         | 说明 |
| --------------- | -------------- |
| 实际用户 ID      | 我们登录的实际身份 |
| 实际组 ID        |                 |
| 有效用户 ID      | 用于文件访问权限检查 |
| 有效组 ID        |                  |
| 附属组 ID        |                  |
| 保存的设置用户 ID | 执行 exec 函数时保存有效用户 ID 和有效组 ID 的副本 |
| 保存的设置组 ID   |                                             |

## 3.2 含义

设置用户 ID: 当执行此文件时, 将进程的有效用户 ID 设置为文件所有者的用户 ID(st_uid)

设置组 ID: 当执行此文件时, 将进程的有效组 ID 设置为文件的组所有者 ID(st_gid)

## 3.3 使用

设置用户ID位作用在可执行文件上

进程a原本并不拥有文件1，此时以root身份将该进程的可执行文件的权限添加设置用户ID位，再以该进程原本身份执行进程a，就可以拥有文件1所有者的权限了

# 4. 粘着位 sticky bit

## 4.1 可执行文件的粘着位

若可执行文件设置了粘着位，此文件被首次执行并终止时，程序正文(机器指令部分)的副本已然保存在交换区中，使得下次执行时能较快的装入内存

UNIX 系统称之为保存正文位 saved-text bit, 也是 S_SVTX 常量的名称由来

虚拟存储系统和快速文件系统已代替可执行文件的粘着位功能

## 4.2 目录的粘着位

对于普通的目录，只要对该目录有写权限，就可删除该目录或其中的文件

对于具有粘着位的目录，则必须是该目录或文件的所有者

例如以下两个目录，任何人对这两个目录都有读写执行权限(drwxrwxrwt)，但用户不能够删除其他人的文件

```
/tmp
/var/tmp
```

# 5. 文件访问权限

## 5.1 文件和目录的权限的含义

目录的执行权限位常被称为搜索位

| 操作 | 含义 |
| ------- | ---------- |
| 读文件   | 读取文件内容 |
| 写文件   | 编辑文件内容（新增和修改文件内容，而不是文件本身）|
| 执行文件 | 执行二进制文件 |
| 读目录   | 读取目录结构列表（目录项，文件名），例如 ls 命令 |
| 写目录   | 更改目录结构列表（新建文件，删除文件，移动文件，修改文件名） |
| 执行目录 | 进入此目录，成为工作目录，例如 cd 命令 |

## 5.2 文件权限检查顺序

### 1. 进程访问文件时的权限测试

1. 进程的有效 ID 是0(超级用户), 则允许访问;
2. 进程有效 ID 等于文件所有者 ID(进程拥有此文件), 则根据用户权限位访问;
3. 进程有效或附属组 ID 等于文件组 ID, 则根据组权限位访问;
4. 根据文件的其他用户权限访问;

一旦检查出允许访问, 则不再进行后续测试

### 2. 使用实际用户 ID 测试访问权限

```
#include <unistd.h>
int access(const char *pathname, int mode);
int faccessat(int fd, const char *pathname, int mode, int flag);
```

| mode | value | 说明 |
| ---- | ----- | ---- |
| F_OK | 0000H | 文件存在 |
| R_OK | 0004H | 测试读权限屏蔽位 |
| W_OK | 0002H | 测试写权限屏蔽位 |
| X_OK | 0001H | 测试执行权限屏蔽位 |

### 3. 文件模式创建屏蔽字

```
#include <sys/stat.h>
mode_t umask(mode_t cmask);
```

### 4. 修改现有文件的访问权限

```
#include <sys/stat.h>
int chmod(const char *pathname, mode_t mode);
```

# 6. 参考

《UNIX 环境高级编程》

《鸟哥的 Linux 私房菜》

《Linux C 函数库参考手册》
