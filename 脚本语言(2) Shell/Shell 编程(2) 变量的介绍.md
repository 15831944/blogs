
# 1. 变量的基本规则

1. 变量的命名规则同其他编程语言，即以字母、下划线开头。

2. 变量的名称的长度不得超过255个字符。

3. 变量具有作用域，局部变量仅作用于当前 shell， 全局变量作用于当前 shell 及其子 shell。

4. 在 bash 中，变量的默认类型都是字符串类型。例如，你定义变量 a=123, 此时123被认为是字符串。 

# 2. 变量的类型

## 1. 本地变量

为用户自定义变量。
属于局部变量，只能在当前 shell 中有效。

### 1. 本地变量的定义和赋值

变量在定义时，变量名，赋值号，值之间不能含有空格。因为空格会被认为是命令和参数之间的间隔。

字符串需要用双引号(特殊符号依然发挥作用)或单引号(特殊符号当做普通字符处理)括起来。

### 2. 变量的调用

变量调用需要在变量前加 ‘$’ 符号(定义时不需要，PHP 语言中都需要)，例如 ：

```
echo $PTAH




```

### 3. 变量的叠加

有两种形式：

```
"$varname"
${varname}




```

举例：

```
x=1
y=2
z=x+y
echo $z

```

结果为 "1+2" 这个字符串。


### 4. set 命令

查询系统下所有生效的变量，包括自定义变量和环境变量。

默认情况下，若变量未被定义，则会显示空行。若使用 -u 选项，则在查看未声明的变量时会报错。

```
set -u
echo $a



```

### 5. unset 命令

用于删除变量。

## 2. 环境变量 

属于全局变量，可以在当前 shell 和子 shell 中有效。

用于保存和系统操作环境相关的变量，可以自定义，但不常用。

但是，对系统生效的环境变量名和其作用是固定的，例如 PATH, PS1等。

注意父 shell 中定义的变量不能在 子 shell 中删除。

### 1. 环境变量的定义

建议大写，用以区分命令，因为命令全是小写。

```
export a="123"




```

### 2. env 命令

用户查看环境变量(不包括自定义变量)。

### 3. PS1 变量

命令提示符样式，如果命令中使用续行符(反斜杠+回车)，会接着显示 PS2定义的样式。另外还有 PS4，但不常用。

### 4. 语系变量

系统默认语系配置文件，系统上电后会读取此配置赋值给 LANG 变量。

```
/etc/sysconfig/i18n




```

### 5. locale 命令

 用于查看语系

LANG=zh_CN.UTF-8
系统当前主语系，即时设置即时生效。

LC_ALL=
整体语系，不常用。


## 3. 预定义变量 

### 1. 预定义变量

bash 定义的变量，变量名不能改变，作用固定。只能改变其值。

	$? 

最后执行命令的返回状态，即进程的返回值，0表示成功，非0表示失败，常用。另外，脚本程序中的与或逻辑判断实际上判断的就是其的返回值。

	$$

当前正在运行的进程的 PID号

	$!

最后执行的后台进程的 PID号

### 2. read 命令

选项

```
-p 打印提示信息
-t 输入等待时间
-n 接受的字符个数
-s 输入时隐藏输入内容

```

实例

```
!/bin/bash
read -p "username : " -t 30 name
read -p "password : " -s password
echo -e "\n"
read -p "sex(m/f) : " -n 1 sex

```

-p 用于提示输入用户名，
-t 用于必须在30s 内输入，
-s 隐藏输入的密码， 
-n 只允许输入一个字母代表性别，

## 4. 位置参数变量

这里所说的位置指的是输入的命令及参数的位置。
属于预定义变量，用于向脚本传递参数和数据。

	$n 

表示脚本的第n个参数

	$* 

表示脚本的全部参数，并当做整体

	$@ 

表示脚本的全部参数，并区别对待

	$# 

表示脚本的参数个数

### 1. 加法实现

	#!bin/bash
	num1=$1
	num2=$2
	sum=$(($num1 + $num2))
	echo $sum

### 2. 循环打印参数

	#!bin/bash
	for i in "$*"
		do
			echo $i
		done
	for j in "$@"
		do
			echo $@
		done
若执行

	#cmdname arg1 arg2 arg3


则会打印  
	
	arg1 arg2 arg3
	
	arg1
	arg2
	arg3

前者当做整体，后者分别打印。


      

  
# 参考

Tony老师聊shell

1. [Linux达人养成计划 I](http://www.imooc.com/learn/175)
2. [Linux达人养成计划 II](http://www.imooc.com/learn/111)

1. [shell编程之变量](http://www.imooc.com/learn/336)
2. [shell编程之运算符](http://www.imooc.com/learn/355)
3. [shell编程之环境变量配置文件](http://www.imooc.com/learn/361)
4. [shell编程之正则表达式](http://www.imooc.com/learn/378)
5. [shell编程之条件判断与流程控制](http://www.imooc.com/learn/408)

1. [Linux网络管理](http://www.imooc.com/learn/258)
2. [Linux软件安装管理](http://www.imooc.com/learn/447)
3. [Linux权限管理之基本权限](http://www.imooc.com/learn/481)
4. [Linux权限管理之特殊权限](http://www.imooc.com/learn/499)
5. [Linux服务管理](http://www.imooc.com/learn/537)
6. [Linux系统管理](http://www.imooc.com/learn/583)
