给命令指定别名

alias [-p] [name[=value] ... ]

为命令设置别名, 该次登录期间有效

显示指定命令的别名

```
$ alias ls
alias ls='ls --color=auto'
```

在linux系统中如果命令太长又不符合用户的习惯，那么我们可以为它指定一个别名。

虽然可以为命令建立“链接”解决长文件名的问题，但对于带命令行参数的命令，链接就无能为力了。而指定别名则可以解决此类所有问题。只要举一些例子就可以了：

```
$ alias l    = 'ls -l'                              用 l 代替 ls -l 命令(Xenix 下就有类似的 l 命令)
$ alias cd.. = 'cd ..'                              用 cd.. 代替 cd .. 命令(对在 DOS 下使用惯了 cd.. 的人帮助很大)
$ alias md   = 'mkdir'                              用 md 代替 mkdir 命令(对在 DOS 下…)
$ alias c:   = 'mount /dev/hda1/mnt/c & cd /mnt/c'  用 c: 命令代替命令序列：安装 DOS 分区，再进入。
$ alias goconfig=’cd /usr/X11/lib/X11’
```

通常我们可以将以上命令放到自己的home目录下的.bash_prifle文件中,在使用source .bash_profile 命令.即可使用.

如果键入不带任何参数的alias 命令，将显示所有已定义的别名。
