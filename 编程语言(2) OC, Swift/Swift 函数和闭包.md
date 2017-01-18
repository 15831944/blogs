# 函数

1. 默认情况下函数使用参数名(parameter names, 形参)作为调用时的参数(arguments, 实参)
2. 可在参数名(parameter name)前面写一个自定义的参数标签(argument label), 使用 "\_" 忽略参数标签
3. 使用元组类型的变量使得函数返回复合值
4. 使用 "..." 声明可变参数
5. 函数的嵌套: 在被嵌套的函数中可以直接访问在外层函数中声明的变量(不需要用参数传入)
6. Functions are a first-class type. This means that a function can return another function as its value.
7. 函数可以作为另一个函数的参数

# 闭包 closure

1. 闭包没有名称, 定义在 "({})" 内, 参数和返回值后接 in 以分隔函数体
2. 函数是闭包的一种特殊情况, 即函数是可以稍后再调用的代码块
3. 闭包中的代码可以访问闭包被创建的作用域中可用的变量和函数, 即使闭包执行完毕后处于一个不同的作用域, 例如嵌套的函数
4. 闭包的简写: 当闭包的类型已知时(such as the callback for a delegate)可忽略参数类型和返回类型
5. 可以使用数字代替名称, 这对于短小的闭包尤其有用

1. 闭包是词法闭包(Lexical Closure)的简称
2. 闭包是由函数和与其相关的引用环境组合而成的实体, 是一种包含环境成分和控制成分的实体
3. 闭包是引用了自由变量的函数, 这个被引用的自由变量将和这个函数一同存在, 即使已经离开了创造它的环境
4. 如果一个函数访问了它的外部变量(外部函数的参数和自动局部变量), 那么它就是一个闭包, 外部函数不是必需的, 通过访问外部变量, 一个闭包可以维持（keep alive）这些变量
5. 在内部函数和外部函数的例子中, 外部函数可以创建局部变量, 并且最终退出, 但是, 如果任何一个或多个内部函数在它退出后却没有退出, 那么内部函数就维持了外部函数的局部变量

# 参考

1. [什么是闭包，我的理解](http://www.cnblogs.com/xiaotie/archive/2011/08/03/2126145.html)
2. [闭包，懂不懂由你，反正我是懂了](http://www.cnblogs.com/frankfang/archive/2011/08/03/2125663.html)
3. [How do JavaScript closures work?](http://stackoverflow.com/questions/111102/how-do-javascript-closures-work)
