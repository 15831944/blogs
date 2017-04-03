# 异常 Exception

1. 异常的产生: 程序错误(例如向数组添加 nil 元素或数组溢出, 不推荐使用), 文件(读入文件不存在, 不推荐使用)或通信通道的输入输出, 没有内存可分配, 参数不正确
1. 异常处理机制 exception handling mechanism: 将异常处理流程和普通执行流程分开, 结构清晰
2. 异常句柄(exception handler): 用于捕获(catch)异常
3. 异常处理域(exception handling domain): 不能处理的异常会导致运行时错误, 程序将被终止
4. 异常对象: NSException 类的实例
5. 抛出异常: 向异常对象发送 raise 消息, 等同于异常发生, 此时还没有开始异常处理
6. 异常信息: 名称(在头文件中预定义为全局字符串常量或自定义新的异常), 原因, 用户字典
7. 未捕获异常句柄(uncaught exception handler): 异常处理域外部发生异常, 
8. 异常传播(propagation): 

```
@try {
	@throw object;	// 产生异常
	/*异常处理域*/
	/*正常处理过程*/
}
@catch (NSException *exception) {	// NSException 对象包含异常信息, 作为参数传递给`@catch` 块, 可以有零个或多个 catch 块, 
	/*异常句柄*/
	/*异常处理过程*/
}
@finally {						// 不写 catch 块时必须有 finally 块
	/*无论异常发送与否都会执行*/
}
```

# 断言 Assertion

1. 断言: 在程序中书写"程序必须满足的条件", 当条件被破坏时就触发异常的结构称为断言
2. 断言宏:

# 错误



# 参考

1. Exception Programming Topics
