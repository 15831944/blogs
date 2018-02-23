#!/bin/bash

# 输入用户名, 密码, 用户数量
read -p "Please input the username: " -t 30 name
read -p "please input the password: " -t 30 passwd
read -p "Please input the total number: " -t 30 total

if [ -z "$name" -a -z "$total" -a -z "$passwd" ]; then		# 输入全部非空
	empty=$(echo $total | sed 's/[0-9]//g')
	if [ -z "$empty" ]; then								# 输入的数量只包含数字
		for (( i = 1; i <= $total; i = i + 1 ))				# 使用双括号做算术运算
			do
				/usr/sbin/useradd $name$i $ > /dev/null						# 添加用户
				echo $pass | /usr/bin/passwd --stdin $name$i & > /dev/null	# 初始密码
				/usr/sbin/userdel $name$i $ > /dev/null						# 删除用户
			done
	fi
fi
