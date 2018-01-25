emacs文本编辑器
C编译器gcc
GNU自由软件项目
禁用ipv6减少不必要的系统开销
GNU命令
管道机制以及less或more命令
sudo或#为超级用户命令
$为普通用户命令
使用“--help”选项查询命令的简单说明
使用man命令联机查询系统参考手册
空格显示余下内容
q键退出当前命令
文件系统层次组织标准（filesystem hierarchy standard，FHS）
系统命令 内部命令 用户命令
man联机文档（nroff格式）位于/usr/share/man目录中
col命令：剔除格式控制字符
find命令说明文件

使用info命令（基于菜单选择的超文本帮助工具）查询命令的相关信息
命令所属的软件包

1.4
intelx86系列处理器及其兼容机
powerPC处理器
64位intel/AMD处理器

硬件要求：
桌面系统本身需4GB
交换分区为两倍内存容量
用户数据空间

磁盘分区：
/文件系统（其中包括/bin，/dev，/etc，/lib，/root，/sbin）
交换分区（提供虚拟内存）
ext2文件系统需要周期地执行完整性检测

划分多个磁盘分区，在每个磁盘分区中创建单独的文件系统
/usr
/var
/home（用户数量，用户应用与数据）
/boot（BIOS无法直接访问1023以外的柱面时）
/tmp（最好不创建单独的文件系统分区）

GRUB引导程序
