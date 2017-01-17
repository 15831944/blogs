# 函数

1. print 函数参数可以使任意基本数据类型, 使用 separator: 定义打印的变量间的分隔符(默认为空格), 使用 terminator: 设置结束符(默认为回车)

# 内部参数名和外部参数名

# 闭包 closure

1. 闭包是词法闭包(Lexical Closure)的简称
2. 闭包是由函数和与其相关的引用环境组合而成的实体, 是一种包含环境成分和控制成分的实体
3. 闭包是引用了自由变量的函数, 这个被引用的自由变量将和这个函数一同存在, 即使已经离开了创造它的环境
4. 如果一个函数访问了它的外部变量(外部函数的参数和自动局部变量), 那么它就是一个闭包, 外部函数不是必需的, 通过访问外部变量, 一个闭包可以维持（keep alive）这些变量
5. 在内部函数和外部函数的例子中, 外部函数可以创建局部变量, 并且最终退出, 但是, 如果任何一个或多个内部函数在它退出后却没有退出, 那么内部函数就维持了外部函数的局部变量

# 参考

1. [什么是闭包，我的理解](http://www.cnblogs.com/xiaotie/archive/2011/08/03/2126145.html)
2. [闭包，懂不懂由你，反正我是懂了](http://www.cnblogs.com/frankfang/archive/2011/08/03/2125663.html)
3. [How do JavaScript closures work?](http://stackoverflow.com/questions/111102/how-do-javascript-closures-work)
