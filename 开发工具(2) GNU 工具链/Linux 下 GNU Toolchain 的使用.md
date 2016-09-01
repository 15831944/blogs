翻译自：

https://blackfin.uclinux.org/doku.php?id=toolchain:gcc_and_gas

上一篇：

[在 Linux 中安装 Blackfin 交叉编译工具链](http://blog.csdn.net/why19911024/article/details/51742865)

# GNU Toolchain 

GNU Toolchain 是多个项目的集合

### GCC : 

GCC 代表“GNU Compiler Collection”. GCC 几种主要编程语言的编译器的集成工具。这些语言目前包括 C, C++, Objective-C, Objective-C++, Java, Fortran, 和 Ada. 目前 Blackfin 支持  C, C++ and Fortran。有若干目标可以决定你的运行时环境。

### Binutils : 

GNU Binutils 是二进制工具的集合。主要有：
GNU linker (ld)；
GNU assembler (as).

### Debugger : 

GNU debugger 让你知道一个程序执行时，里面发生了什么，或者一个程序崩溃时正在做什么。

## gcc and gas

gcc 手册很庞大，我们要讨论它能做什么是不可能的，但是我们给出一些示例命令行请求，告诉你该去浏览什么：

To compile a source file file.c and create an executable named file.x

```
gcc file.c -o file.x
```

gcc -c file1.c	
编译file1.c，生成目标文件file1.o

gcc -o app1 main.o file1.o file3.o	
链接3个目标文件，生成可执行文件 app1

gcc -S file2.c 
将 files2.c 编译回汇编语言，创建名为 file2.s的汇编语言文件。注意参数是大写s，生成的文件后缀名是小写s

gcc -g file4.c -o file4	
编译源文件 file4.c 并传递适当的符号信息，使得在 gdb 的控制下运行得到的可执行文件(file4)

## Blackfin GCC Code-Size Benchmarks and Comparisons


CSiBE 是 GCC 的  code size benchmark。用于监视 GCC 生成的代码的大小。也测量编译时间和代码性能。
