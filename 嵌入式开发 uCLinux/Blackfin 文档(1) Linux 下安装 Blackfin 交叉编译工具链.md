### 翻译自：
https://blackfin.uclinux.org/doku.php?id=toolchain:installing#installing_the_blackfin_toolchain_in_windows

***以下是本人一个字一个字翻译的，交叉编译环境的搭建大致同理。***

### 需要安装什么

典型安装需要2个文件
a toolchain (gcc) version
a uClibc version

uClibc 是一个可配置的C函数库。可以选择使能或不使能特定的函数和函数组。也可以选择使能或不使能特定的函数特性，例如printf函数族成员是否支持GNU自定义格式扩展。还可以修改一些数值性参数，例如一个 FILE buffer 的大小。

我们有预生成的静态版本和共享版本的uClibc。前者有 full 字样（所有的uClinux兼容的特性都使能，且数值型参数采用默认值），后者有 normal 字样（不常用的选项被关闭）。这些版本是标准配置。

我们建议你使用预生成版本的 uClibc， 因为我们把他们当作发布过程的一部分进行过测试，并且它们同标准C++库可以正常工作。

然而，为了减少库的占用空间，你或许希望建立定制版本的 uClibc。如果你决定这么做，你必须从源码建立整个工具链。

你确切需要哪两个文件取决于：
1. 你的操作系统(linux, Windows, Mac OS X)
2. 你的发行版(tar, rpm or deb)
3. 你得主机(x86, PPC, ia64, etc)

### 从哪里获取

从 Blackfin Linux website 的  toolchain file release page 获取  Blackfin toolchain，你只需要确定你的架构（主机）和你需要的文件。

安装最新版本的工具链（看发行日期）前，确保先阅读 toolchain release notes.

依据工具链的版本，可能提供有不同类型的文件。这些文件归纳如下：
.tar.bz2 文件
这些文件是压缩的归档文件。必须用 bunzip2 解压并用 tar 解归档。
.tar.gz 文件
与前者的区别是用 gzip 解压。
.rpm 文件
Red Hat 包管理文件。

为使一切顺畅运行，你或许需要额外的包。可参考Linux配置获取更多信息。

还可能有一些可用的插件（用于像 bfin-elf 或其他版本GCC的其他工具链元组）。你通常不需要安装这些；提供他们只是以防你有代码需要用更老版本的gcc来开发。只有你需要在裸机（没有操作系统）上运行编译的代码时，你才会需要 bfin-elf 工具链。

 工具链的默认安装路径是 /opt/uClinux/.这不是必须的，只是默认路径，因此你可以在任意位置解压缩包。注意 RPMs 不能改变安装路径，需要安装后再移动到其他位置。

### 快速示例
用 tar ball 的方式安装 2012R2-RC2 版本的工具链，我们通常安装以下3个文件到同一个文件夹，然后挨着解压缩，我们需要的是生成的 /opt/uClinux 目录。

1. tar jxvf blackfin-toolchain-2012R2-RC2.i386.tar.bz2
2. tar jxvf blackfin-toolchain-elf-gcc-4.3-2012R2-RC2.i386.tar.bz2
3. tar jxvf blackfin-toolchain-uclibc-default-2012R2-RC2.i386.tar.bz2

然后需要设置路径。

### 压缩包安装

Toolchain Release Notes中可能有更详尽的安装指令。
安装rpms时，/opt目录必须可写。通常如果是本地主机，使用root身份即可，如果是网络挂载，你需要联系当地IT支持人员。如果不能实现，你应该使用 tar ball安装。

尽管以root用户安装工具链是必须的，但不要以root身份安装U-Boot源码或者 uClinux-dist 源码。用普通用户即可。

有些发行版中，双击RPM文件可能会弹出图形前端来安装RPM's。在SuSE Linux 9.0中，这个前端通过YaST2提供。

#### 手动安装RPM

对于 RPM文件，以root用户输入以下命令：

rpm -Uvh <filename>
(e.g. rpm -Uvh blackfin-toolchain-2012R1-RC2.i386.rpm)

#### 在非RPM发行版 (Debian/CoLinux)中安装RPMs

不要这么干。应使用提供的预编译的 tarballs(tar.gz 或者 .tar.bz2).一般都会存在tar这样一个文件。

许多发行版不采用RPM机制，因此安装可能很痛苦。要回避这个问题，我们提供了等同于二进制RPM的二进制tarballs。

用rpm2targz创建，不过你的发行版不存在此命令，找到他。

转换很简单：
$ rpm2targz <rpm>
(e.g. rpm2targz blackfin-toolchain-2012R1-RC2.i386.rpm)

此操作得到一个同目录下同名的tarball，但是扩展名变成.tar.gz而非.rpm.然后解压到你想要存放的目录即可。

### 由源码安装

不使用预生成的二进制工具链有以下几个原因：

存在直接影响你的bug
你希望修改uClibc的默认配置
没有二进制文件适用于你的架构

通常这些不会发生，我们试图确保没有bugs，确保uClibc最通用的配置（我们通常提供两个版本的uClibc），并且为许多架构和系统创建二进制文件。如果可能，应使用预生成的二进制工具链。然而，如果发行版不满足你的需求，那你也没其他选择：

用SVN尝试最新的源码（先分支，后主干）
从发布的源码创建工具链
下载和创建最新版本的SVN工具链的具体指令可以在文档中的  Toolchain Build Script 这一节找到。或者你可以浏览how to build the src rpm这一页面。

### 设置PATH环境变量

安装 Blackfin toolchain 后，必须修改PATH环境变量来包含 Blackfin toolchain 的安装路径。使用 Blackfin toolchain 之前，你可以输入以下命令。假设Blackfin toolchain 二进制文件被安装到默认位置
 /opt/uClinux/bfin-uclinux/bin
 /opt/uClinux/bfin-linux-uclibc/bin
```
$ export PATH=$PATH:/opt/uClinux/bfin-uclinux/bin:/opt/uClinux/bfin-linux-uclibc/bin
```
或者，编辑~/.bashrc文件，包含以下指令，以自动设置 PTAH 变量：

```
export PATH=$PATH:/opt/uClinux/bfin-uclinux/bin:/opt/uClinux/bfin-linux-uclibc/bin
```
系统落地后，你可能想使输出为原生的英语或者当地语言，

```
export LANG=C
```
现在，当新的 bash shell 启动时，PATH 会自动被设置为包含工具链的路径。

现在你可以编译像 U‑Boot 或者 uClinux distribution 这样的程序了。C编译器默认使用 bfin-uclinux-gcc 这个名称（C++编译器使用bfin-uclinux-g++）。如果你想要执行某个特定的版本，追加像 bfin-uclinux-gcc-4.5.3这样的版本号即可。

一旦你编辑了你的路径，你应该这样检查：

```
$ which -a bfin-linux-uclibc-gcc
/home/rgetz/blackfin/trunk/gcc4-linux-uclibc/bin/bfin-linux-uclibc-gcc
/home/rgetz/blackfin/release/gcc4-linux-uclibc/bin/bfin-linux-uclibc-gcc
```
以上，路径中存在两个工具链（通常不对），要决定用那个：
```
$ which bfin-linux-uclibc-gcc
/home/rgetz/blackfin/trunk/gcc4-linux-uclibc/bin/bfin-linux-uclibc-gcc
```
如果这不是你想用的工具链，你可以编辑你得 PATH 变量。

```
$ echo $PATH
:/home/rgetz/bin:/usr/local/bin:/usr/bin:/usr/X11R6/bin:/bin:/usr/games:/opt/gnome/bin:/opt/kde3/bin:
/usr/lib/jvm/jre/bin:/usr/lib/mit/bin:/usr/lib/mit/sbin:/usr/lib/qt3/bin:/usr/sbin:/usr/sbin:/home/rg
etz/blackfin/trunk/gcc4-linux-uclibc/bin:/home/rgetz/blackfin/trunk/gcc4-uclinux/bin:/home/rgetz/blac
kfin/trunk/gcc4-elf/bin:/home/rgetz/blackfin/release/gcc4-linux-uclibc/bin:/home/rgetz/blackfin/trunk
/gcc4-uclinux/bin:/home/rgetz/blackfin/release/gcc4-elf/bin:
```

```
$ export PATH=:/home/rgetz/bin:/usr/local/bin:/usr/bin:/usr/X11R6/bin:/bin:/usr/games:/opt/gnome/bin:/opt/kde3/bin:\
/usr/lib/jvm/jre/bin:/usr/lib/mit/bin:/usr/lib/mit/sbin:/usr/lib/qt3/bin:/usr/sbin:/usr/sbin:/home/rgetz/blackfin/trunk/gcc4-linux-uclibc/bin:\
/home/rgetz/blackfin/trunk/gcc4-uclinux/bin:/home/rgetz/blackfin/trunk/gcc4-elf/bin:   
```
要移除你不想要的工具链，取决于你如何安装它。
包管理方式：
用rpm或apt-get
tar-ball方式
如果你用源码或二进制压缩包安装一些软件，移除安装目录即可。
