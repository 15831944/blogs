都是动态库

.ko   －－ kernel object，内核模块，可以在Linux内核起来之后动态的加载和卸载。
.so   －－ shared object，用户层的动态库 （于.a 对应），使用同一个.so的程序在运行时
只需要该.so的同一份拷贝。

关于.ko，上面有范例了。在Linux Device Driver 3rd那本书上也有说明。
至于.so，这里有例子：
http://blog.csdn.net/thinkerABC/archive/2006/03/11/621817.aspx

另外，如果你有 《C专家编程》这本书，也可以看看 “第五章 对链接的思考”

# 参考

[动态链接库.ko与.so的区别？？？怎么生成制作.ko文件 ？？？ ](http://bbs.csdn.net/topics/250037388)
