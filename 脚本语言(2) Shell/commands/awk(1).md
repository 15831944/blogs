# 概念

1. awk 是样式扫描与文本分析工具, 使用样式扫描和文本处理语言(pattern scanning and text processing language)
2. awk 脚本通常用来格式化文本文件中的信息
3. 记录(record), 每一个输入行定义为一个记录, 每次处理一行
4. 域(field), 记录中(每一行)的每个字符串定义为一个域(段)
5. 分隔符(separator), 域和域之间使用分割符分割, 默认是空格, 存于 FS 变量中

# 内建变量

| variable    | 存储内容 |
| ----------- | --- |
| $n          | 当前记录的第n个字段, $0 表示整个当前记录 |
| RS          | 记录分隔符, 默认为换行符 |
| FS          | 字段分隔符, 默认为空格或TAB |
| NR          | 已读记录数 |
| NF          | 当前记录的字段数 |
| ORS         | 输出记录分隔符 |
| OFS         | 输出字段分隔符(output field separator) |
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

# 自定义变量

-v varname=value

# 操作符

| operator        | 说明 |
| --------------- | --- |
| ~               | 样式匹配运算符 |
| > < == != >= <= | 关系运算符 |
| && !            | 逻辑运算符 |
| + - * / % ^     | 算术运算符 |

# 关键字

1. BEGIN, 作用是执行一些初始化操作, 任何在BEGIN之后列出的操作（在{}内）将在Unix awk开始扫描输入之前执行, 通常使用BEGIN来显示变量和预置（初始化）变量
2. END, 作用是程序结束后执行扫尾的工作, END之后列出的操作将在扫描完全部的输入之后执行, 使用END来输出最终结果

# 流控制和循环

条件判断, if 判断, while 循环, for 循环, awk 数组

# 函数

| funtion          | 功能 |
| ---------------- | --- |
| split            | 字符串切割 |
| toupper          | 大小写转换 |
| sub              | 全局替换 |
| length           | 字符串长度 |
| sin,cos,int,sqrt | 数学计算 |

# 命令行方式调用

awk [ -F field-separator ] [ -v var=value ] [ 'prog' | -f progfile ] [ file ...  ]
awk [ -F field-separator ] '  operator /pattern/ { commands } ' { inputfiles }

1. pattern 使用正则表达式表示的匹配样式, 用斜杠括起来
2. commands 是在找到匹配内容时执行的一系列 awk 命令
3. input-file(s) 是待处理的文件
4. 花括号用于根据特定的模式对一系列指令进行分组

awk 命令行或者 awk 程序脚本

# shell脚本方式调用

`$ 以#!/bin/awk开头的awk可执行脚本文本名 待处理文件`

1. 其中, `#!/bin/awk` 表示awk命令解释器

# 文本文件方式调用 

`awk -f awk-script-file input-file(s)`

1. 其中，-f选项加载awk-script-file中的awk脚本，input-file(s)跟上面的是一样的。

# 参考

1. [linux之awk用法](http://www.cnblogs.com/dong008259/archive/2011/12/06/2277287.html)
2. [linux awk命令详解](http://www.cnblogs.com/ggjucheng/archive/2013/01/13/2858470.html)
3. [Shell脚本之awk详解](http://www.jianshu.com/p/15c92e9602df)
