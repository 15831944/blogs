# 语法

1. 在C中使用 `asm(“instruction [; instruction]”)` 关键字或 `__asm{instruction [; instruction]}` 标记, 即可内嵌汇编指令
2. 在C中使用 `extern` 关键字声明函数, 即可调用汇编语言实现的函数

1. 在汇编中使用 `IMPORT` 指令, 即可引用C全局变量或函数
2. 在汇编中使用 `EXPORT` 指令导出函数名, 即可定义汇编实现的函数

# 参考

1. [ARM中C和汇编混合编程及示例](http://blog.csdn.net/jamestaosh/article/details/4369223)
