# 控制 shell 的运行方式

Bash 有一些特殊变量，能控制 shell 以不同的方式工作。

例如，变量 noclobber 能防止在重定向输出时意外地覆盖一个文件。

通过 set 命令可以设置 noclobber 变量的有效或无效。

set命令有两个参数：

一个是指定变量开（on）或关（off）的选项，一个是特殊变量的变量名。

要使某一特殊变量开（有效），用-o选项，要使其关（无效），用+o选项。

例如：

```
$ set –o noclobber // 使 noclobber 变量开
$ set +o noclobber // 使 noclobber 变量关
```

三个最常用的 shell 特殊变量有

## 1 ignoreeof 忽略文件结束符

ignoreeof 变量用来禁止使用ctrl+d来退出shell（ctrl+d不仅用来退出shell，而且可以终止用户直接输往标准输出上的输入。

该操作经常在一些shell实用命令中使用，例如实用命令cat。在这些实用程序操作中，非常容易误操作而意外地退出shell。

ignoreeof 特殊变量正是用来防止这种意外的退出。

例如：

`$ set –o ignoreeof`

之后，用户只能用 logout 或 exit 命令退出shell。

## 2 noclobber 不要狠击

noclobber 变量可以在重定向输出时保护已存在的文件，防止被意外地覆盖。

在下例中，用户设置 noclobber 为有效，在重定向时，用户试图去覆盖已经存在的文件 myfile，此时系统将返回一个错误信息。

```
$ set –o noclobber
$ cat preface > myfile
bash: myfile: cannot overwrite existing file
```

## 3 noglob 不要展开通配符

设置 noglob 变量后，shell 将不扩展文件名中一些特殊的字符或字符串。

如字符*、?、［ ］等将不再作为通配符。

如果用户希望列出结尾为?的文件名answer?，可通过如下步骤：

首先，用户使noglob变量为有效，然后再列出文件名。

可以看到，目前命令行上的问号?被认为是文件名中的一个字符，而不再被看作通配符。

```
$ set –o noglob
$ ls answer?
answer?
```
