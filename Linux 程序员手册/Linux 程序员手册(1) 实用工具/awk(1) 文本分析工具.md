# 功能

awk 样式扫描与文本分析工具

创建简短的程序，这些程序读取输入文件、为数据排序、处理数据、对输入执行计算以及生成报表，还有无数其他的功能。

简单来说awk就是把文件逐行的读入，以空格为默认分隔符将每行切片，切开的部分再进行各种分析处理。

# 版本

awk

nawk

gawk(GNU 版本，常用)

# 特性

样式装入

流控制

数学运算符

进程控制语句

内置的变量和函数

# awk 程序设计语言

样式扫描和文本处理语言(pattern scanning and text processing language)

# awk 脚本程序语法

awk {pattern + action} {filenames}

pattern 表示 AWK 在数据中查找的内容，即要表示的正则表达式，用斜杠括起来。

action 是在找到匹配内容时所执行的一系列命令

花括号（{}）不需要在程序中始终出现，但它们用于根据特定的模式对一系列指令进行分组。

awk语言的最基本功能是在文件或者字符串中基于指定规则浏览和抽取信息，awk抽取信息后，才能进行其他文本操作。

完整的awk脚本通常用来格式化文本文件中的信息。

通常，awk是以文件的一行为处理单位的。awk每接收文件的一行，然后执行相应的命令，来处理文本。

# 调用方法

## 1. 命令行方式

awk [-F  field-separator]  commands  input-file(s)

commands 是真正awk命令，

[-F 域分隔符]是可选的。

input-file(s) 是待处理的文件。

在awk中，文件的每一行中，由域分隔符分开的每一项称为一个域。通常，在不指名-F域分隔符的情况下，默认的域分隔符是空格。

也可以在 shell script 程序中引用 awk 命令行或者 awk 程序脚本

## 2. shell脚本(命令解释器)方式

将所有的awk命令插入一个文件，并使awk程序可执行，然后awk命令解释器作为脚本的首行，一遍通过键入脚本名称来调用。
相当于shell脚本首行的：

`#!/bin/sh`

可以换成：

`#!/bin/awk`

使用以下方式调用

$awk脚本文本名 待处理文件

## 3. 文本文件方式

将所有的awk命令插入一个单独文件，然后调用：

awk -f awk-script-file input-file(s)

其中，-f选项加载awk-script-file中的awk脚本，input-file(s)跟上面的是一样的。

# 命令行方式实例

假设last -n 5的输出如下

[root@www ~]#  -n  <==仅取出前五行
root    pts/  192.168.1.100  Tue Feb  :  still logged
root    pts/  192.168.1.100  Tue Feb  : - :  (:)
root    pts/  192.168.1.100  Mon Feb  : - :  (:)
dmtsai  pts/  192.168.1.100  Mon Feb  : - :  (:)
root    tty1                  Fri Sep  : - :  (:)

如果只是显示最近登录的5个帐号

#last -n  |  {print $1}'
root
root
root
dmtsai
root

awk工作流程是这样的：读入有'\n'换行符分割的一条记录，然后将记录按指定的域分隔符划分域，填充域，$0则表示所有域,$1表示第一个域,$n表示第n个域。默认域分隔符是"空白键" 或 "[tab]键",所以$1表示登录用户，$3表示登录用户ip,以此类推。

如果只是显示/etc/passwd的账户

# /etc/passwd |  -F  {print $1}
root
daemon
bin
sys

这种是awk+action的示例，每行都会执行action{print $1}。

-F指定域分隔符为':'。

如果只是显示/etc/passwd的账户和账户对应的shell,而账户与shell之间以tab键分割

# /etc/passwd |  -F  {print $1"\t"$7}/bin/bash
daemon  /bin//bin//bin/

如果只是显示/etc/passwd的账户和账户对应的shell,而账户与shell之间以逗号分割,而且在所有行添加列名name,shell,在最后一行添加"blue,/bin/nosh"。

/etc/passwd |  -F  BEGIN {print "name,shell"}  {print $1","$7} END {print "blue,/bin/nosh"}
name,shell
root,/bin/bash
daemon,/bin//bin//bin/
....
blue,/bin/nosh

awk工作流程是这样的：先执行BEGING，然后读取文件，读入有/n换行符分割的一条记录，然后将记录按指定的域分隔符划分域，填充域，$0则表示所有域,$1表示第一个域,$n表示第n个域,随后开始执行模式所对应的动作action。接着开始读入第二条记录······直到所有的记录都读完，最后执行END操作。

搜索/etc/passwd有root关键字的所有行

# -F: /root/ /etc/passwd
root:x:::root:/root:/bin/bash

这种是pattern的使用示例，匹配了pattern(这里是root)的行才会执行action(没有指定action，默认输出每行的内容)。

搜索支持正则，例如找root开头的: awk -F: '/^root/' /etc/passwd

搜索/etc/passwd有root关键字的所有行，并显示对应的shell

#  -F: /root/{print $7} /etc/passwd           
/bin/bash

 这里指定了action{print $7}

awk内置变量

awk有许多内置变量用来设置环境信息，这些变量可以被改变，下面给出了最常用的一些变量。

ARGC              命令行参数个数
ARGV              命令行参数排列
ENVIRON            支持队列中系统环境变量的使用
FILENAME          awk浏览的文件名
FNR                浏览文件的记录数
FS                设置输入域分隔符，等价于命令行 -F选项
NF                浏览记录的域的个数
NR                已读的记录数
OFS                输出域分隔符
ORS                输出记录分隔符
RS                控制记录分隔符

 此外,$0变量是指整条记录。$1表示当前行的第一个域,$2表示当前行的第二个域,......以此类推。

统计/etc/passwd:文件名，每行的行号，每行的列数，对应的完整行内容:

  -F  {print "filename:" FILENAME ",linenumber:" NR ",columns:" NF ",linecontent:"$0} /etc/passwd
filename:/etc/passwd,linenumber:,columns:,linecontent:root:x:::root:/root:/bin/bash
filename:/etc/passwd,linenumber:,columns:,linecontent:daemon:x:::daemon:/usr/sbin:/bin/
filename:/etc/passwd,linenumber:,columns:,linecontent:bin:x:::bin:/bin:/bin/
filename:/etc/passwd,linenumber:,columns:,linecontent:sys:x:::sys:/dev:/bin/

使用printf替代print,可以让代码更加简洁，易读

  -F  {printf("filename:%10s,linenumber:%s,columns:%s,linecontent:%s\n",FILENAME,NR,NF,$0)} /etc/passwd

print和printf

awk中同时提供了print和printf两种打印输出的函数。

其中print函数的参数可以是变量、数值或者字符串。字符串必须用双引号引用，参数用逗号分隔。如果没有逗号，参数就串联在一起而无法区分。这里，逗号的作用与输出文件的分隔符的作用是一样的，只是后者是空格而已。

printf函数，其用法和c语言中printf基本相似,可以格式化字符串,输出复杂时，printf更加好用，代码更易懂。

 awk编程

 变量和赋值

除了awk的内置变量，awk还可以自定义变量。

下面统计/etc/passwd的账户人数

{count++;print $0;} END{print "user count is ", count} /etc/passwd
root:x:::root:/root:/bin/bash
......
user count is  40

count是自定义变量。之前的action{}里都是只有一个print,其实print只是一个语句，而action{}可以有多个语句，以;号隔开。

这里没有初始化count，虽然默认是0，但是妥当的做法还是初始化为0:

BEGIN {count=0;print "[start]user count is ", count} {count=count+1;print $0;} END{print "[end]user count is ", count} /etc/passwd
[start]user count is
root:x:::root:/root:/bin/bash
...
[end]user count is

统计某个文件夹下的文件占用的字节数

-l | BEGIN {size=0;} {size=size+$5;} END{print "[end]size is ", size}'
[end]size is  8657198

如果以M为单位显示:

-l | BEGIN {size=0;} {size=size+$5;} END{print "[end]size is ", size/1024/1024,"M"}
[end]size is  8.25889 M

注意，统计不包括文件夹的子目录。

条件语句

 awk中的条件语句是从C语言中借鉴来的，见如下声明方式：

(expression) {
    statement;
    statement;
    ... ...
}

(expression) {
    statement;
}  {
    statement2;
}

(expression) {
    statement1;
}  (expression1) {
    statement2;
}  {
    statement3;
}

统计某个文件夹下的文件占用的字节数,过滤4096大小的文件(一般都是文件夹):

-l | BEGIN {size=0;print "[start]size is ", size} {if($5!=4096){size=size+$5;}} END{print "[end]size is ", size/1024/1024,"M"}
[end]size is  8.22339 M

循环语句

awk中的循环语句同样借鉴于C语言，支持while、do/while、for、break、continue，这些关键字的语义和C语言中的语义完全相同。

数组

  因为awk中数组的下标可以是数字和字母，数组的下标通常被称为关键字(key)。值和关键字都存储在内部的一张针对key/value应用hash的表格里。由于hash不是顺序存储，因此在显示数组内容时会发现，它们并不是按照你预料的顺序显示出来的。数组和变量一样，都是在使用时自动创建的，awk也同样会自动判断其存储的是数字还是字符串。一般而言，awk中的数组用来从记录中收集信息，可以用于计算总和、统计单词以及跟踪模板被匹配的次数等等。

显示/etc/passwd的账户

-F  BEGIN {count=0;} {name[count] = $1;count++;}; END{for (i = 0; i < NR; i++) print i, name[i]} /etc/passwd
daemon

games
......

这里使用for循环遍历数组

awk编程的内容极多，这里只罗列简单常用的用法，更多请参考 http://www.gnu.org/software/gawk/manual/gawk.html
