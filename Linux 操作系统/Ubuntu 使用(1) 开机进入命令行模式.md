# 方法1 修改启动界面

输入命令：

sudo gedit /etc/default/grub

找到下行：

GRUB_CMDLINE_LINUX_DEFAULT="quiet splash"

改成：

GRUB_CMDLINE_LINUX_DEFAULT="quiet splash text"

输入命令：

sudo update-grub

开机后就自动进入tty1了。

# 方法2 修改启动菜单入口

给配置文件增加写权限：

sudo chmod +w /boot/grub/grub.cfg

编辑配置文件：

sudo gedit /boot/grub/grub.cfg

依照下面这段文字：

menuentry 'Ubuntu，Linux 3.2.0-24-generic-pae' --class ubuntu --class gnu-linux --class gnu --class os {
    recordfail
    gfxmode $linux_gfx_mode
    insmod gzio
    insmod part_msdos
    insmod ext2
    set root='(hd0,msdos8)'
    search --no-floppy --fs-uuid --set=root 689a61a1-06fd-4ffe-95d7-8671e97bbe81
    linux    /boot/vmlinuz-3.2.0-24-generic-pae root=UUID=689a61a1-06fd-4ffe-95d7-8671e97bbe81 ro   quiet splash $vt_handoff
    initrd    /boot/initrd.img-3.2.0-24-generic-pae
}

在文件末尾添加新入口：

menuentry 'Ubuntu，Linux 3.2.0-24-generic-pae(command mode)' --class ubuntu --class gnu-linux --class gnu --class os {
    recordfail
    gfxmode $linux_gfx_mode
    insmod gzio
    insmod part_msdos
    insmod ext2
    set root='(hd0,msdos8)'
    search --no-floppy --fs-uuid --set=root 689a61a1-06fd-4ffe-95d7-8671e97bbe81
    linux    /boot/vmlinuz-3.2.0-24-generic-pae root=UUID=689a61a1-06fd-4ffe-95d7-8671e97bbe81 ro text
    initrd    /boot/initrd.img-3.2.0-24-generic-pae
}

则新菜单入口名称为：

Ubuntu，Linux 3.2.0-24-generic-pae(command mode)

解决虚拟机开机无菜单选项问题：

开机启动时，grub菜单 系统默认是隐藏的，去掉隐藏需要做如下操作

修改 /etc/default/grub 文件如下行

GRUB_HIDDEN_TIMEOUT=0

默认是0，修要修改成大于0的值，比如10

sudo update-grub
