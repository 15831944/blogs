7.1目录和路径
cd
shell builtin
/usr/bin/cd

特殊目录
. 当前目录
.. 上一层目录
- 上一个目录
~ 当前用户主目录
~account 指定用户主目录

例如：列出系统中所有用户主文件夹 cd ~[tab] [tab]

pwd
shell builtin
/bin/pwd

用到$PWD 环境变量
-l logical 连接文件的路径(默认)
-p physical 连接文件指向的实际文件的路径

mkdir

hashed
/bin/mkdir

-m mode 指定文件权限 优先于 umask 指定的默认权限
-p parents 一次性递归创建多级目录，补足缺失的父级目录

rmdir

-p parents

7.2文件与目录管理

ls

hashed
/bin/ls

-a all
-l long
-R recursion
-f 不排序
-F Format
-i inode
-n number
-S sort files by size
-s size 用 blocks 数目表示

cp
/bin/cp OS X

复制单个源文件到目标文件
复制多个源文件到目标目录
创建连接文件
比较两文件的新旧予以更新
复制整个目录

对源文件需要有读权限
普通的复制，文件创建时间会变成当前时间，文件所有者与用户组会变成命令操作者

-a archive 相当于 -pdr
-f force 若目标文件已存在且无法打开，则删除后再尝试一次
-i inquiry  若目标文件已存在，则覆盖前询问
-r recursion 递归复制，源文件可以是目录，源文件以”/"结尾，则复制目录中的全部内容，否则复制包括目录本身
-v verbose 显示详细过程
-p preserve 保留所有属性
-u update

follow symbolic links 意思是依照符号链接文件找到文件本体

rm

-r recursion 递归删除目录

hashed
/bin/rm

mv

移动一个文件为指定文件
移动一个或多个文件到指定目录
单一文件重命名

-f force
-i inquiry
-u update

basename

dirname

7.3文件内容查阅

cat concatenate
