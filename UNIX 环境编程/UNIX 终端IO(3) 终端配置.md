# 命令提示符设置

在 `~/.bashrc` 文件中修改

`PS1='${debian_chroot:+($debian_chroot)}\u@\h:\W\$ '`

用户名、主机名、当前目录名称、命令提示符

# PATH 环境变量设置

在 `~/.bashrc` 文件末尾添加

`export PATH=$PATH:/opt/uClinux/bfin-uclinux/bin:/opt/uClinux/bfin-linux-uclibc/bin`

# 终端颜色配置

用于 ls 命令的输出

## 修改其他人可写权限目录颜色

### 方法1：修改环境变量

1. 打开 `~/.bashrc` 文件

2. 在文件尾添加以下命令`LS_COLORS='ow=40;31:'`

3. 使用 `source ~/.bashrc` 命令使设置生效

4. 使用 `dircolors -p` 命令查看颜色配置

### 方法2：创建自己的颜色配置文件

1. 使用 `vi ~./my_dir_colors` 命令新建颜色配置文件

2. 输入内容 `OTHER_WRITABLE 40;31;01`，分别表示前景色，背景色和粗体

3. 打开 `~/.bashrc` 文件

4. 在文件尾添加以下命令 `eval dircolors $HOME/.my_dir_colors`

5. 使用 `source ~/.bashrc` 命令使设置生效

# 参考

[xshell如何去掉目录背景颜色](https://segmentfault.com/q/1010000002791196?_ea=209284)
