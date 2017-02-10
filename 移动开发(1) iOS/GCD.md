## GCD, Grand Central Dispatch

概念

1. 工作单元: 将长期运行的任务拆分为多个工作单元, 并将这些单元添加到执行队列中, 系统将管理这些队列, 在多个线程上执行工作单元, 不需要启动和管理后台进程
2. 自动化后台进程(painless background processing):
3. 自动线程管理:
4. GCD 的实现是开源的
5. 队列(queue): 遵循先进先出(FIFO)原则,
6. 线程池: GCD 能够访问一个线程池, 该线程池可在应用整个生命周期内重用, 能自动利用更多的处理器核心, 即对于单核处理器意义不大
7. 代码块: C, C++, OC 中, 代码块可以像 C 的基本数据类型一样分配给一个变量, 以参数的形式传递给函数, 也可以执行, 可替代 OC 的委托模式或C中的回调函数
8. 代码块变量声明:
9. 代码块定义:
8. 闭包: Swift 中, GCD 使用闭包来封装代码并添加到队列中
1. 分派函数: async
1. 分派组(Dispatch Group):
2. 后台处理: 不是真正的多任务, 而是在受限方式下继续运行, 如播放音频, 请求位置, 拨打电话功能等

1. GCD (Grand Central Dispatch) 是 Apple 开发的一个多核编程的解决方法, 在 Mac OS X 10.6 雪豹中首次推出, 随后被引入 iOS4.0, 用于多核并行计算, 自动管理线程生命周期, C 语言
2. GCD 是一个替代诸如 NSThread, NSOperationQueue, NSInvocationOperation 等技术的很高效和强大的技术, 类似闭包(Closure), 但苹果把它叫做 blocks
3. 定义想执行的任务并追加到适当的 Dispatch Queue 中, Dispatch Queue 是执行处理的等待队列, 先进先出, 分为 Serial Dispatch Queue 串行调度队列 和 Concurrent Dispatch Queue 并发调度队列

Dispatch Queue

1. Main Dispatch Queue 在主线程中执行, 多个任务本质是同一个线程, 属于 Serial Dispatch Queue
2. Global Dispatch Queue, 是全局的, 多个任务各自分别是线程, 属于 Concurrent Dispatch Queue

```
dispatch_queue_t	mQueue = dispath_get_main_queue();
dispatch_queue_t	gQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0);
dispatch_queue_t	queue1 = dispatch_queue_create("queueName", DISPATCH_QUEUE_SERIAL);		// 创建串行线程队列
dispatch_queue_t	queue2 = dispatch_queue_create("queueName", DISPATCH_QUEUE_CONCURRENT);	// 创建并行线程队列
dispatch_time_t		time = dispatch_time(DISPATCH_TIME_NOW, 3ull * NSEC_PER_SEC);
dispatch_group_t	group = dispatch_group_creat();
static dispatch_once_	onceToken;

dispatch_async(gQueue, ^{ });	// 添加到线程队列
dispatch_release(queue);		// 释放
dispatch_retain(queue);			// 持有
dispatch_after(time ,dispatch_get_main_queue(),^{ });	// 在指定时间后, 追加到调度队列
dispatch_group_async(group, gQueue, ^{ });
dispatch_group_async(group, gQueue, ^{ });
dispatch_group_async(group, gQueue, ^{ });
dispatch_group_notify(group, dispatch_get_main_queue(), ^{ });
dispatch_group_wait(group, DISPATCH_TIME_FOREVER);
dispatch_group_enter(group);
dispatch_group_leave(group);
dispatch_apply(10, queue, ^( ){ });
dispatch_suspend(queue);
dispatch_resume(queue);
dispatch_once(&onceToken, ^{ });
dispatch_set_target_queue
dispatch_barrier_async
disapatch_sync
dispatch Semaphore
```

# 参考

博客

1. [iOS多线程GCD](http://www.cnblogs.com/pure/archive/2013/03/31/2977420.html)
2. [iOS多线程与GCD 你看我就够了](http://www.cocoachina.com/ios/20160804/17291.html)
