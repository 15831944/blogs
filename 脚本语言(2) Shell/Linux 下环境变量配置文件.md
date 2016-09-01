——观看慕课网 Tony 《shell编程之环境变量配置文件》的总结。

本文内容通过阅读各个配置文件中的 shell 程序即可明白。

使配置文件立即生效可以调用 source 命令或 . 命令(一个 dot)，命令后面直接接配置文件名称即可。

如果配置文件丢失，可以找到系统中配置文件的压缩包，解压回来。

# 1. 变量的类型

用户自定义变量（本地变量）
环境变量
预定义变量
位置参数变量

# 2. 环境变量配置文件

## 1. 与用户登录时相关的环境变量配置文件

	/etc/profile
	/etc/profile.d/*.sh
	/etc/bashrc
	~/.bashrc
	~/.bash_profile

### 1. /etc/profile 的作用

设置以下变量：

	USER 变量
	LOGNAME 变量
	MAIL 变量
	PATH 变量
	HOSTNAME 变量
	HISTSIZE 变量
	umask 变量

调用以下配置文件：

	~/.bash_profile
	/etc/profile.d/*.sh

### 1. /etc/profile.d/lang.sh 的作用

/etc/profile.d/lang.sh 调用 /etc/sysconfig/i18n 
作用是决定 shell 的语系

例如：
 /etc/sysconfig/i18n 文件的的内容为 LANG="zh_CN.UTF-8"

### 2. ~/.bash_profile 的作用

	调用 ~/.bashrc 
	将当前用户 bin 目录加入 PATH 变量

### 3. ~/.bashrc 的作用
	
	PS1 变量
	umask 变量
	PATH 变量
	
	别名配置
	
	调用 /etc/profile.d/*.sh 文件

### 4. etc/bashrc 的作用

若未登录 shell， 则直接从这个文件开始配置环境变量

若此前某个配置文件调用失败，则未执行到此配置文件中 PS1 变量的配置，会导致提示符变成 bash5.2# 的样式，为内核自带的单用户模式下的提示符。

## 2. 注销时生效的环境变量配置文件 

### 2.1 ~/.bash_logout 

默认是空的，可以添加自定义命令，例如使用 history -c 清空历史记录。例如 MySQL 使用明文密码。

## 3. 其他配置文件

### 3.1 ~/.bash_history

登录后，历史命令会记录在内存中，注销后，历史记录会写入该目录。

### 3.2 etc/issue

在本地终端登录时显示警告信息（远程登录并不会显示）。并支持转义字符。用于显示登录时间，内核版本，主机名称，终端号等。

### 3.3 etc/issue.net 

远程登录时显示的信息，不支持转义字符。远程欢迎信息由 ssh 决定。

### 3.4 etc/motd

在登录之前显示信息。不论是本地还是远程。

# 最终进入 shell 环境
