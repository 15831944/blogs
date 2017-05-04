# GCC 概述

1. GCC 是 GNU 的 C 编译器, 可用来编译 C, C++ 以及 Objective-C 源程序

# 环境变量

```
LANG                // 下2项的默认值
LC_CTYPE            // 指定字符编码, 例如 en_GB.UTF-8, 识别多字节编码的字符串的边界
LC_MESSAGES         // 指定诊断信息的语言
LC_ALL              // 覆写上2项
TMPDIR              // 临时文件存放目录
GCC_COMPARE_DEBUG   // 同 -fcompare-debug 选项
GCC_EXEC_PREFIX     // 编译器指定的子程序的名称的前缀
COMPILER_PATH       // 子程序查找目录
LIBRARY_PATH        // 链接文件和库查找路径
CPATH               // 指定搜索的目录列表, 效果同 -I 选项, 3种 C 语言通用
C_INCLUDE_PATH      // 指定搜索的目录列表, 效果同 -isystem 选项, 仅适用于 C 语言
CPLUS_INCLUDE_PATH  // 同上, 仅适用于 C++
OBJC_INCLUDE_PATH   // 同上, 仅适用于 Objective C
DEPENDENCIES_OUTPUT // 对基于非系统头文件的 make 输出依赖关系
SUNPRO_DEPENDENCIES // 同上, 但不忽略系统头文件
SOURCE_DATE_EPOCH   // 指定 UNIX 时间戳
```

# 编译命令辨析

1. cc: Unix 系统的 C 编译器, 是商业软件
2. CC: Makefile 的内建变量, 符号链接, 宏定义, 默认指向 gcc, 可以通过 `$ls –l /usr/bin/cc` 查看, 变量的使用可增强代码可移植性
3. gcc: GUN 的 C 编译器, 可以编译 C++ 程序, 但无法链接 C++ 程序使用的库, 使用 `-lstdc++` 选项链接 C++ 标准库
4. g++: GUN 的 C++ 编译器, 编译 C 程序时会调用 gcc, c 和 cpp 文件都被认为是 C++ 程序

# 宏定义

1. \_\_cplusplus 宏决定编译器将会把代码按 C 还是 C++ 语法来解释

# 参考

1. [GCC, the GNU Compiler Collection](https://gcc.gnu.org/)
1. [gcc与g++的区别](http://blog.chinaunix.net/uid-23023613-id-88201.html)
