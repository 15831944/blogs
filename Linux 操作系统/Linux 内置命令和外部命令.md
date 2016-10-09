# 内部命令 Shell builtin

在系统启动时就调入内存，是常驻内存的，所以执行效率高。

使用 compgen -b 命令查看所有内置命令

# 外部命令

系统中的软件功能，用户需要时才从硬盘中读入内存。系统将会读取环境变量文件.bash_profile、/etc/profile去找PATH路径。

# type 命令

type 命令可以用来判断一个命令是否为内置命令

type [-afptP] name [name ...]

# enable 命令

enable 既可以查看内部命令，同时也可以判断是否为内部命令

enable [-a] [-dnps] [-f filename] [name ...]

-a 查看所有内部命令

# hash 命令

hash [-lr] [-p pathname] [-dt] [name ...]

-l 列出 hash 表

-r 清除 hash 表

有些历史命令使用过后，会存在在hash表中，当你再次输入该命令时，它的调用会是这样一个过程：

hash —> 内置命令 —> PATH

hash 表不存放系统内置命令

# 参考

[Linux下内置命令和外部命令详解](https://blog.linuxeye.com/416.html)
