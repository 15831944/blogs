# 1. 库的概述

库本质上是一种经过编译的可执行二进制代码，可以被操作系统载入内存执行。

由于 windows 和 linux 的平台不同（主要是编译器、汇编器和连接器的不同），因此二者库的二进制是不兼容的。

## 1. 静态库 Static Library

静态库文件的扩展名是.a

静态是指每个用到该库的应用程序都拥有一份自己的库拷贝

静态库在程序编译时会被连接到目标代码中，程序运行时将不再需要该静态库

应用程序运行的时候，即使将库删除也没有问题，因为应用程序自己已经有了自己的拷贝

静态库的代码在编译过程中已经被载入可执行程序，因此体积较大

使用 ar (archive)命令将 .o 文件转换成 .a 静态库文件

静态库的名字一般为libxxxx.a，其中xxxx是该lib的名称

### 1. 可执行程序在编译时如何定位库文件？

库文件一般放在 /usr/lib 和 /lib 下

如果创建的库安装在 /usr/lib 或者 /lib 下，那么 ld 默认能够找到，无需其他操作。

如果安装在其他目录，需要将其路径添加到 /etc/ld.so.cache 文件中，步骤如下

1. 编辑 /etc/ld.so.conf 文件，加入库文件所在目录的路径

2. 执行 ldconfig 命令重建 /etc/ld.so.cache 文件

## 2. 共享库 Shared library

共享库文件的扩展名是.so

共享库现在常常被叫做动态库，是由于很多人借用了MS Windows的DLL（Dynamic Linked Library）这个词。

动态库在程序编译时并不会被连接到目标代码中，而是在程序运行是才被载入，因此在程序运行时还需要动态库存在。

一个共享库有可能被多个所有应用程序共享。因此，对每个应用程序来说，即使不再使用某个共享库，也不应将其删除。

此外，应用程序需要正确的环境变量设置（LD_LIBRARY_PATH），从而找到共享库所在的位置，否则，应用程序运行时会报告找不到这个库。

共享库的代码是在可执行程序运行时才载入内存的，在编译过程中仅简单的引用，因此代码体积较小。

共享库的好处是，不同的应用程序如果调用相同的库，那么在内存里只需要有一份该共享库的实例。

动态库的名字一般为libxxxx.so.major.minor，xxxx是该lib的名称，major是主版本号， minor是副版本号
 
### 1. 可执行程序在执行的时候如何定位共享库文件？

当系统加载可执行代码时候，能够知道其所依赖的库的名字，但是还需要知道绝对路径。

此时就需要系统动态载入器(dynamic linker/loader)

对于elf格式的可执行程序，是由 ld-linux.so* 来完成的，它先后搜索

elf文件的 DT_RPATH 段

环境变量 LD_LIBRARY_PATH 

/etc/ld.so.cache文件列表 

/lib /usr/lib 目录

找到库文件后将其载入内存

如：export LD_LIBRARY_PATH=’pwd’

将当前文件目录添加为共享目录

# 查看可执行程序依赖的库

ldd 命令可以查看一个可执行程序依赖的共享库，list dependencies 的缩写

例如# ldd /bin/ln libc.so.6

=> /lib/libc.so.6 (0×40021000)/lib/ld-linux.so.2

=> /lib/ld- linux.so.2 (0×40000000)

可以看到ln命令依赖于libc库和ld-linux库

# 生成静态库

ar 命令

| 选项 | 作用 |
| - | - |
| r | 替换已存在的或添加新文件到库中 |
| s | 作为 ranlib |
| c | 如果库必须被创建，不要发出告警 |

# 生成动态库

动态库文件名命名规范和静态库文件名命名规范类似，也是在动态库名增加前缀 lib，但其文件扩展名为 .so。

例如：我们将创建的动态库名为 myhello，则动态库文件名就是 libmyhello.so。

用 gcc 来创建动态库。
 
在系统提示符下键入以下命令得到动态库文件 libmyhello.so。
 
`# gcc -shared -fPIC -o libmyhello.so hello.o`
 
“PIC”命令行标记告诉GCC产生的代码不要包含对函数和变量具体内存位置的引用，
 
这是因为现在还无法知道使用该消息代码的应用程序会将它连接到哪一段内存地址空间。

这样编译出的 hello.o 可以被用于建立共享链接库。

建立共享链接库只需要用 GCC 的 ”-shared” 标记即可。
 
我们照样使用ls命令看看动态库文件是否生成。
 
调用动态链接库编译目标文件。
 
在程序中使用动态库和使用静态库完全一样，也是在使用到这些公用函数的源程序中包含这些公用函数的原型声明，然后在用gcc命令生成目标文件时指明动态库名进行编译。

我们先运行gcc命令生成目标文件，再运行它看看结果。
 
如果直接用如下方法进行编译，并连接：

`# gcc -o hello main.c -L. -lmyhello`

使用”-lmyhello”标记来告诉GCC驱动程序在连接阶段引用共享函数库libmyhello.so。

”-L.”标记告诉GCC函数库可能位于当前目录。

否则GNU连接器会查找标准系统函数目录:

它先后搜索1.elf文件的 DT_RPATH段

环境变量LD_LIBRARY_PATH

/etc/ld.so.cache文件列表

/lib/,/usr/lib目录找到库文件后将其载入内存

但是我们生成的共享库在当前文件夹下，并没有加到上述的4个路径的任何一个中，因此，执行后会出现错误
 
# ./hello
 
./hello: error while loading shared libraries: libmyhello.so: cannot open shared object file: No such file or directory
 
#
错误提示，找不到动态库文件libmyhello.so。程序在运行时，会在/usr/lib和/lib等目录中查找需要的动态库文件。若找到，则载入动态库，否则将提示类似上述错误而终止程序运行。有多种方法可以解决，
（1）我们将文件 libmyhello.so复制到目录/usr/lib中，再试试。
 
# mv libmyhello.so /usr/lib
 
# ./hello
成功！
（2）既然连接器会搜寻LD_LIBRARY_PATH所指定的目录，那么我们可以将这个环境变量设置成当前目录：
先执行：
export LD_LIBRARY_PATH=$(pwd)
再执行：
./hello
成功！
（3）
执行：  
ldconfig   /usr/zhsoft/lib     
       
      
  注:   当用户在某个目录下面创建或拷贝了一个动态链接库,若想使其被系统共享,可以执行一下"ldconfig   目录名"这个命令.此命令的功能在于让ldconfig将指定目录下的动态链接库被系统共享起来,意即:在缓存文件/etc/ld.so.cache中追加进指定目录下的共享库.本例让系统共享了/usr/zhsoft/lib目录下的动态链接库.该命令会重建/etc/ld.so.cache文件
 
成功！
￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥
下面的这个错误我没有遇到，不过也记录下，给遇到的人：
 {  这步后我没有成功,报错内容如下：/hello: error while loading shared libraries: /usr/lib/libmyhello.so: cannot restore segment prot after reloc: Permission denied
google了一下，发现是SELinux搞的鬼，解决办法有两个：
1.
    chcon -t texrel_shlib_t   /usr/lib/libmyhello.so
    (chcon -t texrel_shlib_t "你不能share的库的绝对路径")
2.
    #vi /etc/sysconfig/selinux file
    或者用
    #gedit /etc/sysconfig/selinux file
    修改SELINUX=disabled
    重启
}
#
￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥￥
这也进一步说明了动态库在程序运行时是需要的。
 
可以查看程序执行时调用动态库的过程：
# ldd hello
执行 test,可以看到它是如何调用动态库中的函数的。
[pin@localhost 20090505]$ ldd hello
        linux-gate.so.1 => (0x00110000)
        libmyhello.so => /usr/lib/libmyhello.so (0x00111000)
        libc.so.6 => /lib/libc.so.6 (0x00859000)
        /lib/ld-linux.so.2 (0x0083a000)
我们回过头看看，发现使用静态库和使用动态库编译成目标程序使用的gcc命令完全一样，
那当静态库和动态库同名时，gcc命令会使用哪个库文件呢？抱着对问题必究到底的心情，
来试试看。
先删除除.c和.h外的所有文件，恢复成我们刚刚编辑完举例程序状态。
# rm -f hello hello.o /usr/lib/libmyhello.so
# ls
hello.c hello.h main.c
#
在来创建静态库文件libmyhello.a和动态库文件libmyhello.so。
# gcc -c hello.c
# ar rcs libmyhello.a hello.o
# gcc -shared -fPCI -o libmyhello.so hello.o
# ls
hello.c hello.h hello.o libmyhello.a libmyhello.so main.c
#
通过上述最后一条ls命令，可以发现静态库文件libmyhello.a和动态库文件libmyhello.so都已经生成，并都在当前目录中。然后，我们运行gcc命令来使用函数库myhello生成目标文件hello，并运行程序 hello。
# gcc -o hello main.c -L. -lmyhello
# ./hello
./hello: error while loading shared libraries: libmyhello.so: cannot open shar
ed object file: No such file or directory
#
从程序hello运行的结果中很容易知道，当静态库和动态库同名时， gcc命令将优先使用动态库。

[](http://www.cppblog.com/deane/articles/165216.html)
[](http://blog.csdn.net/ast_224/article/details/3988244)
