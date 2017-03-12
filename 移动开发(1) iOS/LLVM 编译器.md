# 编译器和调试器

1. GCC 更换为 LLVM(Low Level Virtual Machine, 底层虚拟机)编译器, 不再需要为属性声明相应的实例变量
2. 静态分析器( static analyzer)

# 静态代码分析器

Product -> Analyze


# clang 编译器

1. 需要让 \_\_clang\_\_ 宏有效, .c 和 .m 可以一起编译

```
clang -fobj-arc main.m -o program
clang -fobj-arc -framework Foundation main.m classname.m -o program
clang -fobjc -arc -D MACRO program.m -	// 定义宏 MACRO
```

选项

1. -framework Foundation 引用 Foundation 框架
2. -Wmost 隐藏大部分警告
3. -Wall 隐藏所有警告

6. -fobj-arc 使用 ARC
7. -fno-obj-arc 不使用 ARC
