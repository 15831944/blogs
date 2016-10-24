# read

read: read [-ers] [-a 数组] [-d 分隔符] [-i 缓冲区文字] [-n 读取字符数] [-N 读取字符数] [-p 提示符] [-t 超时] [-u 文件描述符] [变量名称 ...]

# alias

给命令指定别名, 显示指定命令的别名, 该次登录期间有效, 可以将命令放到home目录下的.bash_prifle文件中,在使用source .bash_profile即可使用.

`alias [-p] [name[=value] ... ]`

# export

功能说明：

设置或显示环境变量。

语法：

export [-fn] [name[=value] ...]

export -p


补充说明：

在shell中执行程序时，shell会提供一组环境变量。 export可新增、修改或删除环境变量，供后续执行的程序使用。export 的效力仅及于该此登录操作。

参数：

-f  代表[变量名称]中为函数名称。

-n  删除指定的变量。变量实际上并未删除，只是不会输出到后续指令的执行环境中。

-p 　列出所有的shell赋予程序的环境变量。

一个变量创建时，它不会自动地为在它之后创建的shell进程所知。而命令export可以向后面的shell传递变量的值。

当一个shell脚本调用并执行时，它不会自动得到原为脚本（调用者）里定义的变量的访问权，除非这些变量已经被显式地设置为可用。

export命令可以用于传递一个或多个变量的值到任何后继脚本。

在 linux 里设置环境变量的方法 （ export PATH ）

一般来说，配置交叉编译工具链的时候需要指定编译工具的路径，此时就需要设置环境变量。

例如我的 mips-linux-gcc 编译器在“/opt/au1200_rm/build_tools/bin”目录下，build_tools 就是我的编译工具，则有如下三种方法来设置环境变量：

## 1. 直接用 export 命令：

`#export PATH=$PATH:/opt/au1200_rm/build_tools/bin`

## 2. 在 profile, .bashrc 或 /etc/re.local 文件中添加以下命令

`#export PATH="$PATH:/opt/au1200_rm/build_tools/bin"`

# 参考

[Linux export 命令](http://mymobile.iteye.com/blog/1407601)

eval arg1 [arg2] ... [argN]

Combines the arguments in an expression or list of expressions and evaluates them. Any variables within the expression are expanded. The net result is to convert a string into a command.

Tip

The eval command can be used for code generation from the command-line or within a script.

```
$ command_string="ps ax"
$ process="ps ax"
$ eval "$command_string" | grep "$process"
26973 pts/3    R+     0:00 grep --color ps ax
26974 pts/3    R+     0:00 ps ax
```

Each invocation of eval forces a re-evaluation of its arguments.

```
a='$b'
b='$c'
c=d

echo $a             # First level.
$b
eval echo $a        # Second level.
$c
eval eval echo $a   # Third level.
d
```

# 参考

[read命令手册](http://blog.chinaunix.net/uid-25324849-id-3199237.html)
