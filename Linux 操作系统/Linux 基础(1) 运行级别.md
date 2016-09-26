runlevel运行级就是操作系统当前正在运行的功能级别。

# Linux 的 run-level

| level | 含义                        | 说明                   |
| ----- | -------------------------- | ---------------------- |
| 0     | halt                       | 关机                   |
| 1     | single user mode           | 单用户模式              |
| 2     | multi-user without Network | 不支持网络的多用户模式    |
| 3     | full multi-user mode       | 完整的多用户模式(文本模式) |
| 4     | unused                     | 保留                   |
| 5     | X                          | x window模式(图形模式)   |
| 6     | reboot                     | 重新启动                |

对于Linux来说，时常会需要在runlevel:3（文本模式）和runlevel:5（图形模式）进行切换。

# runlevel的修改方法

1.通过配置修改
修改/etc/inittab

修改

id:5:initdefault

id:3:initdefault

2.使用命令 telinit

输入 telinit 3

立即生效的方法：比如重启系统

init 6
