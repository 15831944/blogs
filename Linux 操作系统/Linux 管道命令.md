管道命令接在“｜”后面，命令的输入是上一条命令的标准输出
或者命令后面接要处理的文件

选取命令

cut 取出数据行中需要的部分
grep 找到指定样式的行
global search regular expression and print out the line

排序命令

sort
wc
uniq

双向重定向

tee

管道符号，是unix一个很强大的功能,符号为一条竖线:"|"。
用法: command 1 | command 2 他的功能是把第一个命令command 1执行的结果作为command 2的输入传给command 2，例如:

$ls -s|sort -nr (请注意不要复制$符号进去哦)

-s 是file size，-n是numeric-sort，-r是reverse，反转
该命令列出当前目录中的文档(含size)，并把输出送给sort命令作为输入，sort命令按数字递减的顺序把ls的输出排序。

$ls -s|sort -n

按从小到大的顺序输出。
当然还可进行多次操作，如下面的功能为先去除纯数字，再由sed将竖线(这里不是管道符号)替换为空格，再将结果取出来排序，再进行结果的选择显示，不明白可查看 排序和分页。

cat filename |grep -v '^[0-9]*$' | sed 's/|/ /g' |sort -nrk 8 -nrk 9 |tail -n +1 |head -n 10
