# 1 . 概述

awk 样式扫描与文本分析工具

样式扫描和文本处理语言(pattern scanning and text processing language)

## 1.1 功能

awk 脚本通常用来格式化文本文件中的信息

## 1.2 版本

1. awk
2. nawk
3. gawk(GNU 版本，常用)

# 2. 概念

## 2.1 记录 record

每一个输入行定义为一个记录, 每次处理一行

## 2.2 域 field

记录中的每个字符串定义为一个域(段)

## 2.3 分隔符 separator

域和域之间使用分割符分割, 默认是空格, 存在 FS 变量中

# 3. 语法

## 3.1 内建变量

| 变量 | 存储内容 |
| ----------- | --- |
| $n          | 当前记录的第n个字段, $0 表示整个当前记录 |
| RS          | 记录分隔符, 默认为换行符 |
| FS          | 字段分隔符, 默认为空格或TAB |
| NR          | 已读记录数 |
| NF          | 当前记录的字段数 |
| ORS         | 输出记录分隔符 |
| OFS         | 输出字段分隔符 |
| ARGC        | 命令行参数个数 |
| ARGV        | 命令行参数数组 |
| FILENAME    | 当前输入文件名 |
| IGNORECASE  | 样式匹配忽略大小写 |
| ARGIND      | 当前被处理文件的ARGV标志符 |
| CONVFMT     | 数字转换格式 %.6g |
| ENVIRON     | UNIX环境变量 |
| ERRNO       | UNIX系统错误消息 |
| FIELDWIDTHS | 输入字段宽度的空白分隔字符串 |
| FNR         | 当前记录数 |
| OFMT        | 数字的输出格式 %.6g |
| RSTART      | 被匹配函数匹配的字符串首 |
| RLENGTH     | 被匹配函数匹配的字符串长度 |

OFS(output field separator)

## 3.2 自定义变量

-v varname=value

## 3.3 操作符

| 操作符 | 说明 |
| --- | --- |
| ~ | 样式匹配运算符 |
| > < == != >= <= | 关系运算符 |
| && ! | 逻辑运算符 |
| + - * / %（取模(余数)） ^（幂运算）| 算术运算符 |

## 3.4 关键字

### 1. BEGIN

作用是执行一些初始化操作, 任何在BEGIN之后列出的操作（在{}内）将在Unix awk开始扫描输入之前执行, 通常使用BEGIN来显示变量和预置（初始化）变量

### 2. END

作用是程序结束后执行扫尾的工作, END之后列出的操作将在扫描完全部的输入之后执行, 使用END来输出最终结果。

## 3.5 流控制和循环

条件判断

if 判断

while 循环

for 循环

awk 数组

## 3.6 函数

| 函数 | 功能 |
| ---------------- | --- |
| split            | 字符串切割 |
| toupper          | 大小写转换 |
| sub              | 全局替换 |
| length           | 字符串长度 |
| sin,cos,int,sqrt | 数学计算 |

# 调用方式

## 2.1. 命令行方式

awk [ -F field-separator ] [ -v var=value ] [ 'prog' | -f progfile ] [ file ...  ]

awk [ -F field-separator ] '  operator /pattern/ { commands } ' { inputfiles }

1. [-F 域分隔符]是可选的。
2. pattern 表示 AWK 在数据中查找的内容，即要表示的正则表达式，用斜杠括起来。
3. commands 是在找到匹配内容时真正执行的一系列 awk 命令，
4. input-file(s) 是待处理的文件。

花括号（{}）不需要在程序中始终出现，但它们用于根据特定的模式对一系列指令进行分组。

在awk中，文件的每一行中，由域分隔符分开的每一项称为一个域。通常，在不指名-F域分隔符的情况下，默认的域分隔符是空格。

也可以在 shell script 程序中引用 awk 命令行或者 awk 程序脚本

## 2.2. shell脚本方式

将所有的awk命令插入一个文件，并使awk程序可执行，然后awk命令解释器作为脚本的首行，一遍通过键入脚本名称来调用。
相当于shell脚本首行的：

`#!/bin/sh`

可以换成：

`#!/bin/awk`

使用以下方式调用

$awk脚本文本名 待处理文件

## 2.3. 文本文件方式

将所有的awk命令插入一个单独文件，然后调用：

awk -f awk-script-file input-file(s)

其中，-f选项加载awk-script-file中的awk脚本，input-file(s)跟上面的是一样的。

# 参考

http://www.cnblogs.com/dong008259/archive/2011/12/06/2277287.html

http://www.cnblogs.com/ggjucheng/archive/2013/01/13/2858470.html

http://www.jianshu.com/p/15c92e9602df
