# 功能

查找内容包含指定的范本样式的文件.

如果发现某文件的内容符合所指定的范本样式，预设grep指令会把含有范本样式的那一列显示出来。

若不指定任何文件名称，或是所给予的文件名为“-”，则grep指令会从标准输入设备读取数据。

# 语法

grep

[-abcEFGhHilLnqrsvVwxy]

[-A<显示列数>]

[-B<显示列数>]

[-C<显示列数>]

[-d<进行动作>]

[-e<范本样式>]

[-f<范本文件>]

[--help]

[范本样式]

[文件或目录...]

# 参数

-a或--text   不要忽略二进制的数据。

-A<显示列数>或--after-context=<显示列数>   

除了显示符合范本样式的那一列之外，并显示该列之后的内容。

-b或--byte-offset   

在显示符合范本样式的那一列之前，标示出该列第一个字符的位编号。

-B<显示列数>或--before-context=<显示列数>   

除了显示符合范本样式的那一列之外，并显示该列之前的内容。

-c或--count   计算符合范本样式的列数。

-C<显示列数>或--context=<显示列数>或-<显示列数>   

除了显示符合范本样式的那一列之外，并显示该列之前后的内容。

-d<进行动作>或--directories=<进行动作>   

当指定要查找的是目录而非文件时，必须使用这项参数，否则grep指令将回报信息并停止动作。

-e<范本样式>或--regexp=<范本样式>   

指定字符串做为查找文件内容的范本样式。

-E或--extended-regexp   

将范本样式为延伸的普通表示法来使用。

-f<范本文件>或--file=<范本文件>   

指定范本文件，其内容含有一个或多个范本样式，让grep查找符合范本条件的文件内容，格式为每列一个范本样式。

-F或--fixed-regexp   

将范本样式视为固定字符串的列表。

-G或--basic-regexp   

将范本样式视为普通的表示法来使用。

-h或--no-filename   

在显示符合范本样式的那一列之前，不标示该列所属的文件名称。

-H或--with-filename   

在显示符合范本样式的那一列之前，表示该列所属的文件名称。
-i或--ignore-case   忽略字符大小写的差别。
-l或--file-with-matches   列出文件内容符合指定的范本样式的文件名称。
-L或--files-without-match   列出文件内容不符合指定的范本样式的文件名称。
-n或--line-number   在显示符合范本样式的那一列之前，标示出该列的列数编号。
-q或--quiet或--silent   不显示任何信息。
-r或--recursive   此参数的效果和指定“-d recurse”参数相同。
-s或--no-messages   不显示错误信息。
-v或--revert-match   反转查找。
-V或--version   显示版本信息。
-w或--word-regexp   只显示全字符合的列。
-x或--line-regexp   只显示全列符合的列。
-y   此参数的效果和指定“-i”参数相同。
--help   在线帮助。

linux grep命令的使用

用grep命令 搜索文本文件 来自www.linuxso.com

如果您要在几个文本文件中查找一字符串，可以使用&lsquo;grep’命令。‘grep’在文本中搜索指定的字符串。
假设您正在‘/usr/src/linux/Documentation’目录下搜索带字符串‘magic’的文件：
$ grep magic /usr/src/linux/Documentation/*
sysrq.txt:* How do I enable the magic SysRQ key?
sysrq.txt:* How do I use the magic SysRQ key?
其中文件‘sysrp.txt’包含该字符串，讨论的是 SysRQ 的功能。
默认情况下，‘grep’只搜索当前目录。如果此目录下有许多子目录，‘grep’会以如下形式列出：
grep: sound: Is a directory
这可能会使‘grep’的输出难于阅读。这里有两种解决的办法：
明确要求搜索子目录：grep -r
或忽略子目录：grep -d skip
当然，如果预料到有许多输出，您可以通过 管道 将其转到‘less’上阅读
$ grep magic /usr/src/linux/Documentation/* | less
这样，您就可以更方便地阅读。
有一点要注意，您必需提供一个文件过滤方式（搜索全部文件的话用 *）。如果您忘了，‘grep’会一直等着，直到该程序被中断。如果您遇到了这样的情况，按 <CTRL c> ，然后再试。
下面是一些有意思的命令行参数：
grep -i pattern files ：不区分大小写地搜索。默认情况区分大小写，
grep -l pattern files ：只列出匹配的文件名，
grep -L pattern files ：列出不匹配的文件名，
grep -w pattern files ：只匹配整个单词，而不是字符串的一部分（如匹配‘magic’，而不是‘magical’），
grep -C number pattern files ：匹配的上下文分别显示[number]行，
grep pattern1 | pattern2 files ：显示匹配 pattern1 或 pattern2 的行，
grep pattern1 files | grep pattern2 ：显示既匹配 pattern1 又匹配 pattern2 的行。
这里还有些用于搜索的特殊符号：
< 和 > 分别标注单词的开始与结尾。
例如：
grep man * 会匹配 ‘Batman’、‘manic’、‘man’等，
grep \'<man\' * 匹配‘manic’和‘man’，但不是‘Batman’，
grep \'<man>\' 只匹配‘man’，而不是‘Batman’或‘manic’等其他的字符串。
\'^\'：指匹配的字符串在行首，
\'$\'：指匹配的字符串在行尾，
如果您不习惯命令行参数，可以试试图形界面的‘grep’，如 reXgrep 。这个软件提供 AND、OR、NOT 等语法，还有漂亮的按钮 :-) 。如果您只是需要更清楚的输出，不妨试试 fungrep 。
.grep 搜索字符串
命令格式:
grep string filename
寻找字串的方法很多，比如说我想找所有以M开头的行.此时必须引进pattern的观
念.以下是一些简单的□例，以及说明：
^M 以M开头的行，^表示开始的意思
M$ 以M结尾的行，$表示结束的意思
^[0-9] 以数字开始的行，[]内可列举字母
^[124ab] 以1,2,4,a,或b开头的行
^b.503 句点表示任一字母
* 星号表示0个以上的字母(可以没有)
+ 加号表示1个以上的字母
. 斜线可以去掉特殊意义
<eg> cat passwd | grep ^b 列出大学部有申请帐号者名单
cat passwd | grep ^s 列出交换学生申请帐号者名单
cat passwd | grep \'^b.503\' 列出电机系各年级...
grep \'^.\' myfile.txt 列出所有以句点开头的行
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1. grep简介
grep （global search regular expression(RE) and print out the line）

grep 是一种强大的文本搜索工具，它能使用正则表达式搜索文本，并把匹配的行打印出来。

Unix的grep家族包 括grep、egrep和fgrep。

egrep和fgrep的命令只跟grep有很小不同。

egrep是grep的扩展，支持更多的re元字符，

fgrep就是fixed grep或fast grep，它们把所有的字母都看作单词，也就是说，正则表达式中的元字符表示回其自身的字面意义，不再特殊。

linux使用GNU版本的grep。它功能 更强，可以通过-G、-E、-F命令行选项来使用egrep和fgrep的功能。

grep的工作方式是这样的，

它在一个或多个文件中搜索字符串模板。

如果模板包括空格，则必须被引用，模板后的所有字符串被看作文件名。

搜索的结果被送到屏幕，不影响原文件内容。

grep可用于shell脚本，因为grep通过返回一个状态值来说明搜索的状态，

如果模板搜索成功，则返回0，

如果搜索不成功，则返回1，

如果搜索的文件不存在，则返回2。

我们利用这些返回值就可进行一些自动化的文本处理工作。


2. grep正则表达式元字符集（基本集）

锚定行的开始 如：\'^grep\'匹配所有以grep开头的行。
锚定行的结束 如：\'grep$\'匹配所有以grep结尾的行。
匹配一个非换行符的字符 如：\'gr.p\'匹配gr后接一个任意字符，然后是p。
匹配零个或多个先前字符 如：\'*grep\'匹配所有一个或多个空格后紧跟grep的行。 .*一起用代表任意字符。
匹配一个指定范围内的字符，如\'[Gg]rep\'匹配Grep和grep。
匹配一个不在指定范围内的字符，如：\'[^A-FH-Z]rep\'匹配不包含A-R和T-Z的一个字母开头，紧跟rep的行。
标记匹配字符，如\'(love)\'，love被标记为1。
锚定单词的开始，如:\'
锚定单词的结束，如\'grep>\'匹配包含以grep结尾的单词的行。
重复字符x，m次，如：\'0{5}\'匹配包含5个o的行。
x{m,}
重复字符x,至少m次，如：\'o{5,}\'匹配至少有5个o的行。
x{m,n}
重复字符x，至少m次，不多于n次，如：\'o{5,10}\'匹配5--10个o的行。
匹配文字和数字字符，也就是[A-Za-z0-9]，如：\'Gw*p\'匹配以G后跟零个或多个文字或数字字符，然后是p。
w的反置形式，匹配一个或多个非单词字符，如点号句号等。
单词锁定符，如: \'bgrepb\'只匹配grep。
3. 用于egrep和 grep -E的元字符扩展集
匹配一个或多个先前的字符。如：\'[a-z]+able\'，匹配一个或多个小写字母后跟able的串，如loveable,enable,disable等。
匹配零个或多个先前的字符。如：\'gr?p\'匹配gr后跟一个或没有字符，然后是p的行。
a|b|c
匹配a或b或c。如：grep|sed匹配grep或sed
分组符号，如：love(able|rs)ov+匹配loveable或lovers，匹配一个或多个ov。
x{m},x{m,},x{m,n}
作用同x{m},x{m,},x{m,n}
4. POSIX字符类
为了在不同国家的字符编码中保持一至，POSIX(The Portable Operating System Interface)增加了特殊的字符类，如[:alnum:]是A-Za-z0-9的另一个写法。要把它们放到[]号内才能成为正则表达式，如[A- Za-z0-9]或[[:alnum:]]。在linux下的grep除fgrep外，都支持POSIX的字符类。
[:alnum:]
文字数字字符
[:alpha:]
[:digit:]
[:graph:]
非空字符（非空格、控制字符）
[:lower:]
[:cntrl:]
[:print:]
非空字符（包括空格）
[:punct:]
[:space:]
所有空白字符（新行，空格，制表符）
[:upper:]
[:xdigit:]
十六进制数字（0-9，a-f，A-F）
5. Grep命令选项
同时显示匹配行上下的？行，如：grep -2 pattern filename同时显示匹配行的上下2行。
-b，--byte-offset
打印匹配行前面打印该行所在的块号码。
-c,--count
只打印匹配的行数，不显示匹配的内容。
-f File，--file=File
从文件中提取模板。空文件中包含0个模板，所以什么都不匹配。
-h，--no-filename
当搜索多个文件时，不显示匹配文件名前缀。
-i，--ignore-case
忽略大小写差别。
-q，--quiet
取消显示，只返回退出状态。0则表示找到了匹配的行。
-l，--files-with-matches
打印匹配模板的文件清单。
-L，--files-without-match
打印不匹配模板的文件清单。
-n，--line-number
在匹配的行前面打印行号。
-s，--silent
不显示关于不存在或者无法读取文件的错误信息。
-v，--revert-match
反检索，只显示不匹配的行。
-w，--word-regexp
如果被<和>引用，就把表达式做为一个单词搜索。
-V，--version
显示软件版本信息。
要用好grep这个工具，其实就是要写好正则表达式，所以这里不对grep的所有功能进行实例讲解，只列几个例子，讲解一个正则表达式的写法。
$ ls -l | grep \'^a\'
通过管道过滤ls -l输出的内容，只显示以a开头的行。
$ grep \'test\' d*
显示所有以d开头的文件中包含test的行。
$ grep \'test\' aa bb cc
显示在aa，bb，cc文件中匹配test的行。
$ grep \'[a-z]{5}\' aa
显示所有包含每个字符串至少有5个连续小写字符的字符串的行。
$ grep \'w(es)t.*1\' aa
如果west被匹配，则es就被存储到内存中，并标记为1，然后搜索任意个字符（.*），这些字符后面紧跟着另外一个es（1），找到就显示该行。如果用egrep或grep -E，就不用""号进行转义，直接写成\'w(es)t.*1\'就可以了。
原文链接：http://www.linuxso.com/command/grep.html
