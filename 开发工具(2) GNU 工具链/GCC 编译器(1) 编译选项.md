网址：https://gcc.gnu.org/
GNU的C编译器，可用来编译C, C++以及Objective-C源程序。

常规的linux下默认的GCC包含以下几类选项：
Overall Options
C Language Options
C++ Language Options
Objective-C and Objective-C++ Language Options
Language Independent Options
Warning Options
C and Objective-C-only Warning Options
Debugging Options
Optimization Options
Preprocessor Options
Assembler Option
Linker Options
Directory Options
Machine Dependent Options
Code Generation Options

**AD公司Blackfin处理器GCC选项示例**

**Linker Options**

object-file-name
-l library
-Wl, option 
把选项option传递给连接器 .如果 option中含有逗号 ,就在逗号处分割成多个选项 .

**Machine Dependent Options**

Blackfin Options

-mcpu=cpu[-sirevision]
指定处理器名称，硅片版本，主版本号，次版本号

-mfast-fp
用快速浮点库连接，出于性能目的

**Optimization Options**

-03 
高的优化级别

**cc 的指定**
bfin-uclinux-gcc

下面是摘录的官方介绍
The Blackfin GCC toolchain comes with three categories:
bfin-elf-*
bfin-linux-uclibc-*
bfin-uclinux-*
bfin-uclinux-gcc and bfin-linux-uclibc-gcc are used to compile programs that run on the Linux operating system. They automatically link the application with the the Linux run time libraries, which in turn call the Linux operating system when required (for example, to print a string to the console).
The bfin-elf-gcc compiler is used to compile the Linux kernel and standalone programs as it uses a different set of libraries.
  
