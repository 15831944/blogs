必须接口
	必须的头文件
可选接口
	40个功能分区, 用选项码标识, 依赖于特性选项的支持

# 1. 必须的头文件

| 头文件 | 说明 |
| - | - |
| aio.h |  |
| cpio.h |  |
| dirent.h | 目录项 |
| dlfcn.h |  |
| fcntl.h | 文件控制 |
| fnmatch.h |  |
| glob.h |  |
| grp.h |  |
| iconv.h | 代码集变换实用程序 |
| langinfo.h |  |
| monetary.h |  |
| netdb.h |  |
| nl_types.h |  |
| poll.h |  |
| pthread.h | 线程 |
| pwd.h | 口令文件 |
| regex.h | 正则表达式 |
| sched.h |  |
| semaphore.h | 信号量 |
| strings.h |  |
| tar.h |  |
| termios.h |  |
| unistd.h | 符号常量 |
| wordexp.h |  |
| - | - |
| arpa/inet.h |  |
| net/if.h |  |
| netinet/in.h |  |
| netient/tcp.h |  |
| - | - |
| sys/mman.h |  |
| sys/select.h | select 函数 |
| sys/socket.h | 套接字接口 |
| sys/stat.h |  |
| sys/statvfs.h |  |
| sys/times.h |  |
| sys/types.h |  |
| sys/un.h | UNIX 域套接字定义 |
| sys/utsname.h |  |
| sys/wait.h |  |

## fcntl.h

open openat create fcntl

O_RDONLY O_WRONLY O_RDWR

## unistd.h

close lseek read write dup dup2 sync fsync fdatasync

STDIN_FILENO STDOUT_FILENO STDERR_FILENO

## sys/ioctl.h

ioctl

# 2. 可选的头文件

## 1. XSI 可选头文件

## 2. 可选头文件

## 3. 可选接口组和选项码
