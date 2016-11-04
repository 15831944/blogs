# 进程

1. 系统服务：crond atd syslog
2. 网络服务：Apache named postfix vsftpd
3. 系统后台进程: at 命令执行的单一工作调度是交给系统的 atd 程序接管的, 是系统后台程序, 脱机不丢失
4. 用户后台进程: bash 本身就是一个进程, 在 bash 中执行的子进程是在 bash 环境中的后台程序, 脱机会丢失

# 工作管理 job control

1. 新建进程在后台运行 & (新建进程可以直接在后台运行)
2. 前台进程在后台暂停 ctrl+z 挂起(见 stty 命令)
3. 挂起进程调到后台运行 bg (前台进程不能直接拿到后台运行，需要先暂停，再后台运行)
4. 后台进程调到前台运行 fg

# 运行级别 runlevel

1. 运行级别是操作系统当前正在运行的功能级别, 时常会需要在 3(文本模式)和 5(图形模式)进行切换
2. 通过配置文件 /etc/inittab 修改运行级别, 如 id:5:initdefault, 也可使用 telinit 命令

| level | 含义                        | 说明                   |
| ----- | -------------------------- | ---------------------- |
| 0     | halt                       | 关机                   |
| 1     | single user mode           | 单用户模式              |
| 2     | multi-user without Network | 不支持网络的多用户模式    |
| 3     | full multi-user mode       | 完整的多用户模式(文本模式) |
| 4     | unused                     | 保留                   |
| 5     | X                          | x window模式(图形模式)   |
| 6     | reboot                     | 重新启动                |

# 系统服务

例行性工作调度

1. cron 命令, 字面上就是百万年执行一次的意思
2. crontab 服务

单一工作调度

1. at 命令, 字面上就是在某一时刻的意思
2. batch 命令, 实际上也是调用 at 命令，并且可以用 atq (at queue) 和 atrm (at remove) 来进行管理

stand_alone

| daemon | service      | port |
| ------ | ------------ | ---- |
| httpd  | WWW          | 80   |
| vsftpd | FTP          | 21   |
|        | SSH          | 22   |
| crond  | 例行性工作调度 |      |
| atd    | 单一工作调度   |      |
| syslog |              |      |

super_daemon (xinetd)     

| daemon | service |
| ------ | ------- |
| telnet |         |

# 命令提示符

第1级提示符默认是"$", 修改 PS1 变量
第2级提示符默认是">", 改变 PS2 变量

| character | 说明                                   |
| --------- | ------------------------------------- |
| !         | 显示该命令的历史编号                      |
| #         | 显示shell激活后，当前命令的历史编号         |
| $         | 显示一个$符号，如果当前用户是root则显示#符号 |
| /         | 显示一个反斜杠                           |
| d         | 显示当前日期                             |
| t         | 显示当前时间                             |
| h         | 显示运行该shell的计算机主机名              |
| n         | 打印一个换行符，这将导致提示符跨行           |
| s         | 显示正在运行的Shell的名称                 |
| u         | 显示当前用户的用户名                      |
| W         | 显示当前工作目录基准名                    |
| w         | 显示当前工作目录                         |

# 环境变量的设置

环境变量内容的修改（关键字紧跟在变量名后面）：

| 命令 | 作用 |
| --- | --- |
| #  | 删除从左至右数的匹配样式的最短的字符串 |
| ## | 删除从左至右数的匹配样式的最长的字符串 |
| %  | 删除从后往前数的匹配样式的最短的字符串 |
| %% | 删除从后往前数的匹配样式的最长的字符串 |
| /  | 将首个第一个 / 后面的字符串替换为第二个 / 后面的字符串 |
| // | 将第一个 // 后面的字符串全部替换为第二个 / 后面的字符串 |

将 express 赋值给 varible 变量的测试条件：

| 命令 | 表达式 | 作用 |
| --- | --- | --- |
| - | variable=${string-express} | 若string不存在则成功设置新值expression，否则取string的值 |
| + | variable=${string+express} | 若string存在则成功设置新值expression，否则取空字符串 |
| = | variable=${string=express} | 若string不存在则成功设置新值expression，否则取string的值; 若strig不存在则string也设置新值expression，否则sting值不变 |
| ? | variable=${string?express} | 若string存在则成功设置为string，否则输出错误expression |

# 子 shell 与 export 命令

1. 运行 shell 脚本程序时, 系统将创建一个子 shell, 脚本程序结束时, 子 shell 将终止, 返回父 shell
2. 在子 shell 中定义的变量只在该子 shell 内有效, 因此在 shell 脚本程序中定义的变量只是该脚本的局部变量
3. 要使某个变量的值可以在其他 shell 中访问, 可以使用 export 命令对已定义的变量进行输出, 使系统在创建每一个新的 shell 时定义这个变量的一个拷贝, 称之为变量输出

# 内置(builtin)命令和外部命令

1. 内置命令在系统启动时就调入内存, 常驻内存, 执行效率高
2. 外部命令是系统中软件的功能, 执行时读入内存, 读取 PATH 变量查找命令路径
3. 命令使用过后, 会存在 hash 表中, 再次输入该命令时, 查找顺序为 hash —> 内置命令 —> $PATH, hash 表不存放系统内置命令
4. compgen 命令查看所有内置命令
5. type 命令可以用来判断一个命令是否为内置命令
6. enable 既可以查看内部命令, 同时也可以判断是否为内部命令

# 软件包管理

| 软件管理机制 | 在线更新模式 | 操作系统 |
| ---------- | ---------- | ------- |
| RPM        | yum        | Red Hat |
| dpkg       | apt        | Debian  |

# 软件源配置文件

/etc/apt/sources.list

# 软件体系 Architecture

| Architecture | describe                                            |
| ------------ | --------------------------------------------------- |
| main         | Canonical-supported free and open-source software   |
| universe     | Community-maintained fredd and open-source software |
| restricted   | Proprietary dirvers for devices                     |
| multiverse   | Software restricted by copyright or legal issues    |
| Source code  |                                                     |

# 软件形式

| form    | describe    |
| ------- | ----------- |
| deb     | 已编译的软件包 |
| deb-src | 源码         |

# 软件包发行版 Distribution

yakkety -> xenial -> wily -> vivid -> trusty -> precise

# 环境变量配置文件

系统级

1. /etc/profile: 设定所有用户可使用的全局变量, 登录系统时执行, 并从 /etc/profile.d 目录的配置文件中搜集 shell 的设置
2. /etc/bashrc: 为每一个运行 bash 的用户执行此文件, bash 打开时读取该文件

用户级

1. ~/.bash_profile: 用户登录时, 该文件仅仅执行一次, 设置一些环境变量, 执行用户的 .bashrc 文件, 若存在多种文件, 执行的顺序是: ~/.bash_profile, ~/.bash_login, ~/.profile
2. ~/.bashrc: 用户登录时执行
3. ~/.bash_logout: 退出系统时执行

# 参考

书籍

《鸟哥的 Linux 私房菜》

博客

1. [Linux下内置命令和外部命令详解](https://blog.linuxeye.com/416.html)
2. [Linux中环境变量配置文件详解](http://www.dns001.com/tech/content-44-8099-1.html)
