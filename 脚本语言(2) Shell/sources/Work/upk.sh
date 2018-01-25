#!/bin/sh
# FangShanzhong 2011-11-16
# 用法: 开机情况下, 执行此 upk 命令, 参数1为操作系统文件名, 参数2为服务器IP地址
# 操作: 用于更新操作系统, 实际为复制操作系统镜像文件到设备目录

# 判断参数1为空, 则打印错误信息并退出, 注意参数2可选
if [ -z "$1" ]; then
    echo "Usage: put file to /tmp or tftp server"
    echo "then run upk FILE_NAME [TFTP_SERVER_IP]"
    exit 1
fi

# 读取命令参数
ip=$2
file="$1"

# 确认更新
read -n1 -p "UPDATE KERNEL ! DO YOU WANT TO CONTINUE? y/n?" ans
case $ans in
Y|y)
        echo "";;
*)
        echo "";
        exit 2;;
esac

# 打印信息
echo -n "current version: #"
cat /proc/version | awk -F# '{print $2}'
echo ""

cd /tmp
if [ -f "$file" ]; then
	echo "WRITE FLASH ..."
	echo "PLEASE WAIT FOR ABOUT 30 SECONDS!"
	echo ""
	flashcp $file /dev/mtd1
	echo "update image success, now sys will reboot!"
	sleep 5
	reboot
	exit 0
else
	if [ -z "$ip" ]; then
	    echo "Usage: put file to /tmp or tftp server. then run "
    	echo " upk FILE_NAME [TFTP_SERVER_IP]"
    	exit 1
	fi
	echo "get $file from $ip"
	echo ""
	cd /tmp
	cd /tmp
	tftp -g -r $file $ip
	if [ -f "$file" ]; then
		echo "WRITE FLASH ..."
		echo "PLEASE WAIT FOR ABOUT 30 SECONDS!"
		echo ""
		flashcp $file /dev/mtd1
		echo "update image success,now sys will reboot!"
		sleep 5
		reboot
		exit 0
	else
		echo "update err! $file not exist!"
		exit 1
	fi
fi
