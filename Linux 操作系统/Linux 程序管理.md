# 例行性工作调度

cron 命令 字面上就是百万年执行一次的意思
crontab 服务

# 单一工作调度

at 字面上就是在某一时刻的意思
atq   at queue
atrm at remove

batch 命令 实际上也是调用 at 命令，并且可以用 atq 和 atrm 来进行管理


# 17.1 什么是进程

crontab进程 工作调度 p508

/etc/crontab p509
/etc/inittab p510

daemon 系统服务

系统服务：crond atd syslog
网络服务：Apache named postfix vsftpd

# 17.2 工作管理 job control

新建进程在后台运行 &
前台进程在后台暂停 ctrl+z 挂起 见 stty
后台进程在后台运行 bg
后台进程拿前台运行 fg

前台进程不能直接拿到后台运行，需要先暂停，在后台运行
新建进程可以直接在后台运行

# 17.3 进程管理

进程状态 precess status

-l long
a 打印终端相关的所有进程
x 打印属于你的所有进程
ax 打印所有进程
u 显示面向用户的格式

| F     | process flags | 进程的权限  | 4:root 1:fork |
| S     | status        | 进程的状态  | R: running S: sleep D T: stop Z: Zombie |
| C     | CPU           | CPU的使用率 | |
| PRI   | priority      |            | |
| NI    | nice          |            | |
| ADDR  | address       | 内存地址    | - 表示进程正在运行 |
| SZ    | size          | 内存容量    | |
| WCHAN |               |            | -表示进程正在运行 |
| TTY   |               |            | 登录者的终端机位置 |
| TIME  |               | CPU运行时间 | |
| CMD   | command       |            | 造成此进程触发的命令 |
