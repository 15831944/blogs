# 1. 概述

文件模式字包含以下信息

1. 文件类型
2. 设置用户ID位
3. 设置组ID位
4. 粘着位
5. 文件访问权限

## 1. st_mode 宏

| macro              | value                              |
| ------------------ | ---------------------------------- |
| S_ISREG(st_mode)   | (((st_mode) & S_IFMT) == S_IFREG)  |
| S_ISDIR(st_mode)   | (((st_mode) & S_IFMT) == S_IFDIR)  |
| S_ISLINK(st_mode)  | (((st_mode) & S_IFMT) == S_IFLNK)  |
| S_ISBLK(st_mode)   | (((st_mode) & S_IFMT) == S_IFBLK)  |
| S_ISCHR(st_mode)   | (((st_mode) & S_IFMT) == S_IFCHR)  |
| S_ISSOCK(st_mode)  | (((st_mode) & S_IFMT) == S_IFSOCK) |
| S_ISFIFO(st_mode)  | (((st_mode) & S_IFMT) == S_IFIFO)  |

## 2. st_mode 屏蔽

| st_mode            | value | 说明 |
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
| S_ISVTX            | 1000H | 文件的sticky位 |
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

# 3. 设置ID位

设置用户 ID (set-user-ID)和设置组 ID(set-group-ID)

设置用户ID: 当执行此文件时, 将进程的有效用户 ID 设置为文件所有者的用户 ID(st_uid)

设置组 ID: 当执行此文件时, 将进程的有效组 ID 设置为文件的组所有者 ID

超级用户之所以能够访问其他用户的文件, 就是因为使用了设置用户 ID 功能

## ID 类型

于一个进程相关的 ID 有6个

| ID 类型 | 说明 |
| --------------- | -------------- |
| 实际用户 ID      | 我们登录的实际身份 |
| 实际组 ID        |  |
| 有效用户 ID      | 用于文件访问权限检查 |
| 有效组 ID        |  |
| 附属组 ID        |  |
| 保存的设置用户 ID | 执行 exec 函数时保存有效用户 ID 和有效组 ID 的副本 |
| 保存的设置组 ID   |  |

# 4. 文件权限

文件和目录的权限的含义

| 操作 | 含义 |
| ------- | ---------- |
| 读文件   | 读取文件内容 |
| 写文件   | 编辑文件内容（新增和修改文件内容，而不是文件本身）|
| 执行文件 | 执行二进制文件 |
| 读目录   | 读取目录结构列表（目录项，文件名），例如 ls 命令 |
| 写目录   | 更改目录结构列表（新建文件，删除文件，移动文件，修改文件名） |
| 执行目录 | 进入此目录，成为工作目录，例如 cd 命令 |

## 文件权限检查过程


# 5. 参考

《UNIX 环境高级编程》

《鸟哥的 Linux 私房菜》

《Linux C 函数库参考手册》
