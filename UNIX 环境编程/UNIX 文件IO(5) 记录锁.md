# 记录锁的形式

| 函数 | 说明 |
| - | - |
| flock | 只能对整个文件加锁 |
| fcntl | 可对文件任意字节数区域加锁 |
| lockf | 简化了接口 |

# 记录锁的种类

建议性锁

强制性锁

# fcntl 记录锁

`int fcntl(int fd, int cmd, struct flock lk);`

fcntl 记录锁是 POSIX 标准的基础

| 命令 | 说明 |
| - | - |
| F_GETLK  | 判断由 flockptr 所描述的锁是否会被另外一把锁排斥 |
| F_SETLK  | 设置由 flockptr 所描述的锁 |
| F_SETLKW | 设置失败则阻塞(wait) |

flock 结构体

| l_type  | 说明 |
| ------- | - |
| F_RDLCK | 共享读锁 |
| F_WRLCK | 独占性写锁 |
| F_UNLCK | 解锁一个区域(未上锁) |

# 参考

[linux系统编程之struct flock 结构体](http://blog.csdn.net/wallwind/article/details/7816221)
