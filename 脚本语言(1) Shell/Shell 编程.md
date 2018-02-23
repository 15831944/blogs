# 变量的基本规则

1. 变量的命名规则同其他编程语言，即以字母、下划线开头, 长度不得超过255个字符
2. 变量具有作用域: 局部变量仅作用于当前 shell， 全局变量作用于当前 shell 及其子 shell
3. 变量的默认类型都是字符串类型。例如，你定义变量 a=123, 此时123被认为是字符串

# 本地变量

1. 本地变量为用户自定义变量, 属于局部变量，只能在当前 shell 中有效
2. 量在定义时，变量名，赋值号，值之间不能含有空格。因为空格会被认为是命令和参数之间的间隔
3. 字符串需要用双引号(特殊符号依然发挥作用)或单引号(特殊符号当做普通字符处理)括起来
4. 变量调用需要在变量前加 ‘$’ 符号(定义时不需要，PHP 语言中都需要)，例如 ：
5. 变量的叠加有两种形式, ${variable}, "$variable"
6. 使用 set 命令查询系统下所有生效的变量，包括自定义变量和环境变量。默认情况下，若变量未被定义，则会显示空行。若使用 -u 选项，则在查看未声明的变量时会报错。
7. 使用 uset 命令删除变量

# 环境变量 

1. 环境变量属于全局变量，在当前 shell 和子 shell 中有效
2. 用于保存和系统操作环境相关的变量，可以自定义，但不常用, 对系统生效的环境变量名和其作用是固定的，例如 PATH, PS1等
3. 父 shell 中定义的变量不能在子 shell 中删除
4. 使用 export 命令定义环境变量
5. env 命令用户查看环境变量(不包括自定义变量)
5. PS1 变量: 命令提示符样式，如果命令中使用续行符(反斜杠+回车)，会接着显示 PS2定义的样式。另外还有 PS4，但不常用

## 语系变量

1. 系统默认语系配置文件'/etc/sysconfig/i18n'，系统上电后会读取此配置赋值给 LANG 变量
2. 使用 locale 命令查看语系
3. LANG=zh_CN.UTF-8: 设置系统当前主语系，即时设置即时生效
4. LC_ALL: 整体语系，不常用

# 预定义变量 

1. bash 定义的变量，变量名不能改变，作用固定。只能改变其值。
2. $?: 最后执行命令的返回状态，即进程的返回值，0表示成功，非0表示失败，常用。另外，脚本程序中的与或逻辑判断实际上判断的就是其的返回值。
3. $$: 当前正在运行的进程的 PID号
4. $!: 最后执行的后台进程的 PID号

## 位置参数变量

1. 位置指的是输入的命令及参数的位置。属于预定义变量，用于向脚本传递参数和数据。
2. $n: 表示脚本的第n个参数
3. $\*: 表示脚本的全部参数，并当做整体
4. $@: 表示脚本的全部参数，并区别对待
5. $#: 表示脚本的参数个数

# 环境变量配置文件

1. 使配置文件立即生效可以调用 source 命令或 . 命令(一个 dot)，命令后面直接接配置文件名称即可
2. 如果配置文件丢失，可以找到系统中配置文件的压缩包，解压回来

# 与用户登录时相关的环境变量配置文件

```
/etc/profile
/etc/profile.d/*.sh
/etc/bashrc
~/.bashrc
~/.bash_profile
```

# 注销时生效的环境变量配置文件

~/.bash_logout 默认是空的，可以添加自定义命令，例如使用 history -c 清空历史记录。例如 MySQL 使用明文密码。

# 其他配置文件

~/.bash_history 登录后，历史命令会记录在内存中，注销后，历史记录会写入该目录。
etc/issue       在本地终端登录时显示警告信息（远程登录并不会显示）。并支持转义字符。用于显示登录时间，内核版本，主机名称，终端号等。
etc/issue.net   远程登录时显示的信息，不支持转义字符。远程欢迎信息由 ssh 决定。
etc/motd        在登录之前显示信息。不论是本地还是远程

# 条件判断式 test

1. 使用 test 或 [ statement ] 进行判断, 中括号和条件判断式之间必须有空格, 使用命令返回值 $? 查看判断结果, 或使用逻辑与和逻辑或打印结果
2. 文件类型: 使用 -e (exist), -d (directory), -f (file), -l(link), -b(block) 等选项判断文件是否存在, [-e filename] && echo yes || echo no
3. 文件权限: 使用 -w, -r, -x, -u, -g, -k 选项判断文件权限, 不能判断该权限的所有者
4. 文件比较: -nt (new than), -ot (old than), -ef 通过i节点判断文件是否为同一文件, 用于判断硬链接
5. 整数比较: -eq (equal), -ne (not equal), -gt (greater than), -lt (less than), -ge, -le, 数值测试符号会把字符串型的操作数转换为整型进行比较
6. 字符串判断: -z(zero, 空), -n(非空), ==, !=
7. 多重条件: -a (and, 逻辑与), -o (or, 逻辑或), !

# if 分支语句

then 也可以另起一行

```
if [ test ]; then
	commamd
elif [ test ]; then
	commamd
else
	commamd
fi
```

# case 多分支语句

```
case $variable in
	"val1")
		commamd
		;;
	"val2")
		commamd
		;;
	*)
		commamd
		;;
esac
```

# for 固定循环

```
for variable in val1 val2 val3 ...
	do
		command
	done

for ((;;))
	do
		command
	done
```

# while 和 until 条件循环

```
while [ test ]
	do
		command
	done
	
until [ test ]
	do
		command
	done
```
# 参考

1. [Linux达人养成计划 I](http://www.imooc.com/learn/175)
2. [Linux达人养成计划 II](http://www.imooc.com/learn/111)

Tony老师聊shell

1. [shell编程之变量](http://www.imooc.com/learn/336)
2. [shell编程之运算符](http://www.imooc.com/learn/355)
3. [shell编程之环境变量配置文件](http://www.imooc.com/learn/361)
4. [shell编程之正则表达式](http://www.imooc.com/learn/378)
5. [shell编程之条件判断与流程控制](http://www.imooc.com/learn/408)

Linux 系统管理

1. [Linux网络管理](http://www.imooc.com/learn/258)
2. [Linux软件安装管理](http://www.imooc.com/learn/447)
3. [Linux权限管理之基本权限](http://www.imooc.com/learn/481)
4. [Linux权限管理之特殊权限](http://www.imooc.com/learn/499)
5. [Linux服务管理](http://www.imooc.com/learn/537)
6. [Linux系统管理](http://www.imooc.com/learn/583)
