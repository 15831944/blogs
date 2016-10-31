# GCC 概述

GCC 是 GNU 的 C 编译器，可用来编译 C, C++ 以及 Objective-C 源程序。

常规的 linux 下默认的 GCC 包含以下几类选项：

## Option Summary

1. Overall Options
2. C Language Options
3. C++ Language Options
4. Objective-C and Objective-C++ Language Options
5. Language Independent Options
6. Warning Options
7. C and Objective-C-only Warning Options
8. Debugging Options
9. Optimization Options
10. Preprocessor Options
11. Assembler Option
12. Linker Options
13. Directory Options

-Idir

14. Machine Dependent Options
15. Code Generation Options

## Options Controlling the Kind of Output

## Options Controlling dialect

## Compiling C++ Programs

## Options Controlling the Preprocessor

-I dir L6448

-iquote dir L6722

## Options for linking

-lm 搜索数学库
-lpthread 搜索线程库

-L dir

-l library

http://blog.sina.com.cn/s/blog_61b24b0c01012ggh.html

[谈谈GCC的-I，-L和-l选项](http://blog.initm.com/gcc-l-i-l/)

# 环境变量

| environment         | decribe |
| ------------------- | ------- |
| LANG                | 下2项的默认值 |
| LC_CTYPE            | 指定字符编码, 例如 en_GB.UTF-8, 识别多字节编码的字符串的边界 |
| LC_MESSAGES         | 指定诊断信息的语言 |
| LC_ALL              | 覆写上2项 |
| TMPDIR              | 临时文件存放目录 |
| GCC_COMPARE_DEBUG   | 同 -fcompare-debug |
| GCC_EXEC_PREFIX     | 编译器指定的子程序的名称的前缀 |
| COMPILER_PATH       | 子程序查找目录 |
| LIBRARY_PATH        | 链接文件和库查找路径 |
| CPATH               | 指定搜索的目录列表, 效果同 -I 选项, 3种 C 语言通用 |
| C_INCLUDE_PATH      | 指定搜索的目录列表, 效果同 -isystem 选项, 仅适用于 C 语言 |
| CPLUS_INCLUDE_PATH  | 同上, 仅适用于 C++ |
| OBJC_INCLUDE_PATH   | 同上, 仅适用于 Objective C |
| DEPENDENCIES_OUTPUT | 对基于非系统头文件的 make 输出依赖关系 |
| SUNPRO_DEPENDENCIES | 同上, 但不忽略系统头文件 |
| SOURCE_DATE_EPOCH   | 指定 UNIX 时间戳 |

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

# 参考

[GCC, the GNU Compiler Collection](https://gcc.gnu.org/)
