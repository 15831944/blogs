# 1 函数库

1. 库本质上是一种经过编译的可执行二进制代码，可以被操作系统载入内存执行。
2. Linux 和 Windows 等不同平台编译环境不同, 函数库不兼容。

## 1.1 静态库 Static Library

1. 静态是指每个用到该库的应用程序都拥有一份自己的库拷贝
2. 静态库在程序编译时会被连接到目标代码中，可执行程序的体积较大, 程序运行时将不再需要该静态库, 可以删除库文件
3. 静态库生成: 使用 ar (archive)命令将 .o 文件转换成 .a 静态库文件
4. 静态库命名规则: 静态库的名字一般为 libxxxx.a, 其中 xxxx 是该库的名称, 后缀名是 .a

### 1.1.1 静态库查找

1. 静态库文件一般放在 `/lib`, `/usr/lib` 和 `/usr/local/lib` 下, ld 默认能够找到, 无需其他操作
2. 将静态库文件路径添加到 `/etc/ld.so.cache` 文件中, 执行 ldconfig 命令添加指定目录, 重建 `/etc/ld.so.cache` 文件, 使该函数库被系统共享

### 1.1.2 静态库的生成

使用 ar 命令创建静态库

| options |  explanation |
| ------- | ------------ |
| r       | 替换已存在的或添加新文件到库中 |
| s       | 作为 ranlib                |
| c       | 如果库必须被创建，不要发出告警 |

## 1.2 共享库 Shared library

1. 共享库现在常常被叫做动态库, 是由于很多人借用了 Windows 的 DLL (Dynamic Linked Library) 这个词
2. 共享库在程序编译时并不会被连接到目标代码中, 而是在程序运行是才被载入, 因此在程序运行时还需要动态库存在
3. 一个共享库有可能被多个所有应用程序共享。因此，对每个应用程序来说，即使不再使用某个共享库，也不应将其删除
4. 应用程序需要正确的环境变量设置（LD_LIBRARY_PATH），从而添加并找到共享库所在的位置，否则，应用程序运行时会报告找不到这个库
5. 共享库的代码是在可执行程序运行时才载入内存的，在编译过程中只是简单的引用，因此代码体积较小
6. 共享库的好处是，不同的应用程序如果调用相同的库，那么在内存里只需要有一份该共享库的实例
7. 共享库命名规则: 共享库的名字一般为 libxxxx.so.major.minor, 其中 xxxx 是该库的名称, major 是主版本号, minor 是副版本号, 后缀名是.so
8. 使用 ldd(list dependencies) 命令可以查看一个可执行程序依赖的共享库, 或者说程序调用共享库的过程
9. 使用 gcc 编译器的 -v 选项打印路径搜索过程
10. 当静态库和动态库同名时, gcc 命令将优先使用动态库

### 2.2.1 共享库查找

1. 当系统加载可执行代码时候, 能够知道其所依赖的共享库的名字
2. elf 格式的可执行程序通过系统动态载入器(dynamic linker/loader)获取共享库的绝对路径, 搜索到共享库将其载入内存
3. 动态载入器命名规则: ld-linux.so*
4. 共享库查找顺序: elf 文件的 DT_RPATH 段指定的路径->LD_LIBRARY_PATH 环境变量指定的路径->/etc/ld.so.cache 文件列表->/lib 和 /usr/lib 目录下的文件

### 2.2.2 共享库的生成

`# gcc -shared -fPIC -o libmyhello.so hello.o`

1. 使用 gcc 命令创建共享库 libmyhello.so
2. “PIC” 命令行标记告诉 gcc 产生的代码不要包含对函数和变量具体内存位置的引用，因为现在还无法知道使用该消息代码的应用程序会将它连接到哪一段内存地址空间。这样编译出的 hello.o 可以被用于建立共享链接库。
3. 建立共享链接库只需要用 gcc 的 ”-shared” 标记即可。

### 2.2.3 共享库的使用

`# gcc -o hello main.c -L. -lmyhello`

1. 在使用到这些库函数的源程序中包含这些库函数的原型声明
2. 在用 gcc 命令生成目标文件时指明动态库名进行编译。调用动态链接库编译目标文件。
3. 使用”-lmyhello”标记来告诉GCC驱动程序在连接阶段引用共享函数库libmyhello.so
4. 使用”-L.”标记告诉GCC函数库可能位于当前目录。否则GNU连接器会查找标准系统函数目录.

### 共享库查找相关环境变量

LIBRARY_PATH: 编译时使 gcc 能够找到编译时需要的动态链接库

LD_LIBRARY_PATH: 程序加载运行时能够自动找到需要的动态链接库

# 注意编译时指定共享库目录,可以编译通过,不代表运行时还能查找到这个库,因此编译时用-L指定,运行时要加入 ld.so.cache 文件

# 查考库函数所用的环境变量

LIBRARY_PATH 指明库搜索路径，此环境变量指明路径会在-L指定路径之后，系统默认路径之前被搜索。

# 内核态和用户层的共享库

.ko, .so 都是动态库

.ko   －－ kernel object，内核模块，可以在Linux内核起来之后动态的加载和卸载。
.so   －－ shared object，用户层的动态库 （于.a 对应），使用同一个.so的程序在运行时
只需要该.so的同一份拷贝。

关于.ko，上面有范例了。在Linux Device Driver 3rd那本书上也有说明。
至于.so，这里有例子：
http://blog.csdn.net/thinkerABC/archive/2006/03/11/621817.aspx

另外，如果你有 《C专家编程》这本书，也可以看看 “第五章 对链接的思考”

# 2 头文件概述

1. 使用双引号形式包含用户定义头文件, 使用尖括号形式包含系统头文件
2. 指定头文件目录影响的是预处理器的行为, 指定库文件路径影响的是连接器的行为

## 2.1 头文件查找过程

1. 双引号指定目录(程序中显式指定的目录)
2. 编译命令指定目录(gcc 编译器的 -iquote 和 -I 选项)
3. 环境变量指定目录(交叉编译工具链)
3. 标准系统包含目录(操作系统)

## 2.2 查找头文件所用的环境变量

gcc 编译器的环境变量

```
| variables          | describe |
| ------------------ | -------- |
| CPATH              | 指定搜索的目录列表, 效果同 -I 选项, 3种 C 语言通用 |
| C_INCLUDE_PATH     | 指定搜索的目录列表, 效果同 -isystem 选项, 仅适用于 C 语言 |
| CPLUS_INCLUDE_PATH | 同上, 仅适用于 C++ |
| OBJC_INCLUDE_PATH  | 同上, 仅适用于 Objective C |
```

## 2.3 标准系统目录 standard system include Directory

```
/usr/include
/usr/local/include
```

# 参考

1. [LIBRARY_PATH和LD_LIBRARY_PATH环境变量的区别](http://www.cnblogs.com/panfeng412/archive/2011/10/20/library_path-and-ld_library_path.html)
2. [Linux下Gcc生成和使用静态库和动态库详解（转）](http://www.cppblog.com/deane/articles/165216.html)
3. [C/C++ 头文件以及库的搜索路径](http://blog.csdn.net/crylearner/article/details/17013187)
4. [C语言头文件、库文件的查找路径 - c语言程序开发技术文章 - 红黑联盟](http://www.2cto.com/kf/201011/78886.html)
5. [动态链接库.ko与.so的区别？？？怎么生成制作.ko文件 ？？？ ](http://bbs.csdn.net/topics/250037388)
