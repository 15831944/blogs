# undefined reference

1. 未链接引用(变量或函数)的实现(定义)所在的目标文件(.o)或库文件(.a)
2. 在链接命令中给出所依赖的库时，需要注意库之间的依赖顺序，依赖其他库的库一定要放到被依赖库的前面, 即调用在前, 定义在后
3. C++ 代码引用 C 函数库时, 需要在引用的文件前添加 extern "C" 声明

# 参考

["undefined reference to" 问题解决方法](http://blog.csdn.net/aiwoziji13/article/details/7330333)
