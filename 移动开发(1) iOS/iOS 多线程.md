1. NSThread 类创建多线程的程序
2. MSLock 类为彼此竞争的线程在访问进程资源时提供各种控制机制
3. NSTask 类可以分出一个子进程来执行其它工作或进行进度监控

# 进程

1. 进程: 进程是系统中正在运行的一个应用程序, 可以包含多个线程
2. 进程空间: 进程运行在其专有的空间内, 是受保护的, 一个进程不能访问另一个进程的专有空间, 或者说获得另一个进程的资源

进程的五态模型

1. 新建, 进程被创建但还未提交的状态, 新建态的进程无法运行, 因为需要操作系统给出进程管理信息: 建立资源表格, 分配资源, 加载程序, 建立地址空间表等等;
2. 就绪, 新建后具备所有进程管理信息, 一旦时间片轮转到, 即可运行
3. 运行, 运行态的进程数小于等于处理器的核心数, 当没有进程可运行时, 操作系统会指定系统空闲进程;
4. 阻塞, 等待或睡眠状态, 等待某事件发生(如 I/O 请求),  此时即使处理器分配给此进程也无法运行,
5. 终止, 操作系统要回收资源, 释放主存

# 线程

1. 线程: 线程是进程的基本执行单元, 用于指代一个独立执行的代码路径, 进程的所有任务都在线程中执行, 例如 Xcode 进程中, 编辑, 保存, 编译, 下载均是独立的线程
2. 主线程: 进程想要执行任务, 必须至少有一个线程, 这一线程称为主线程, 在 iOS 开发中称为 UI 线程, 应用程序在启动时, 在主线程中描绘用户界面, 处理触摸屏幕的事件等

多线程的应用

1. 网络请求, 客户端向服务器发起 HTTP 请求, 服务器的 API 返回结果, 客户端再进行 UI 的展示, 此过程由于网络原因, 可能需要几秒时间才能返回, 因此一般发异步请求, 即在不阻塞工作线程和 UI 线程(期间仍然可以操作 UI)的情况下发出请求, 完成相应任务, 保证客户端的流畅性
2. 图片加载, 读本地缓存, 请求网络图片, 再缓存到本地, 下次就可直接读缓存, 同样是一个异步操作的过程
3. 文件处理, 数据处理, 任务执行等都会放到异步线程中执行

任务执行方式

1. 同步(串行), 多个任务按照一定顺序执行, 总耗时等于各任务时间相加, 上一个任务执行的结果可用于下一个任务, 任务的执行会阻塞当前线程, 只存在一个线程也就是主线程
2. 异步(并行), 多个任务并发执行, 总耗时等于耗时最长的那个任务, 存在多个线程
3. 并行：多个任务在同一时刻发生, 多核 CPU 同时开启多条线程供多个任务同时执行, 互不干扰
4. 并发：多个任务在同一时间间隔内发生, 可以在线程之间进行多次上下文切换, 伪异步

线程状态

1. ready
2. cancelled
3. executing
4. finished
5. asynchronous

# 多线程

如果在主线程中执行耗时任务, 比如一些多请求的情况, 就会妨碍主线程中被称为 RunLoop 的主循环的执行, 导致不能更新用户界面, 应用程序的画面长时间停滞等问题, 使用了多线程编程, 在执行长时间的处理仍可保证用户界面的相应性能. 一般将网络请求等耗时任务放在独立的线程中, 将刷新 UI 的操作放在主线程中执行

1. 操作系统为每个线程分配时间片, 对每个线程按时间片轮转调度
2. 对于单核操作系统, 一个线程执行时, 其他线程阻塞或空闲, 宏观来看是并行, 实际为串行; 对于多核操作系统, 是真正的并行(并行的线程数小于核心数)
3. 多线程可以简化编程模型, 更加轻量级, 提高执行效率(一个任务多个人干), 提高资源利用率, 但增加程序复杂性(资源共享, 数据读写问题), 占用内存空间, 增加 CPU 调度开销
4. iOS 多线程实现技术方案包括: pThread(C 语言), NSThread, GCD(C 语言), NSOperation. 封装程度递增, 效率递减
5. 创建线程时应指定 selector

## pThread

基本用不到

```
pthread_t	pthread;
pthread_create(%pthread, NULL, childthread, NULL);
```

## NSThread

直观, 简单, 快捷, 但不能对线程进行详细配置, 不推荐使用

```
// 宏
NS_DESIGNATED_INITIALIZER
NS_AVAILABLE
NS_DEPRECATED

@property double						threadPriority		// 小数形式的优先级属性
@property NSQualityOfService			qualityOfService	// 枚举类型的优先级属性, 线程启动后只读
@property (nullable, copy) NSString		*name				// 线程名字
@property NSUInteger					stackSize 			// 堆栈大小
@property (readonly) BOOL				isMainThread		// 是否是主线程
@property(readonly, getter=isExecuting)	BOOL executing;		// 线程是否正在执行
@property(readonly, getter=isFinished)	BOOL finished;		// 线程是否已经结束
@property(readonly, getter=isCancelled)	BOOL cancelled;		// 线程是否已经取消

+ (void)detachNewThreadSelector:(SEL)selector toTarget:(id)target withObject:(nullableid)argument;		// 创建并启动线程, 无须创建线程对象, 无须内存清理
+ (NSThread*)currentThread;												// 获取当前线程
+ (void)exit;															// 退出当前线程
+ (BOOL)isMultiThreaded;												// 判断是否为多线程
+ (BOOL)isMainThread;													// 当前线程是否为主线程
+ (NSThread*)mainThread;												// 获取主线程
+ (void)sleepUntilDate:(NSDate*)date;									// 设置线程阻塞时间
+ (void)sleepForTimeInterval:(NSTimeInterval)ti;						// 设置线程阻塞时间
+ (double)threadPriority;												// 获取线程优先级
+ (BOOL)setThreadPriority:(double)p;									// 设置线程优先级
+ (NSArray *)callStackReturnAddresses;									// 线程函数地址
+ (NSArray *)callStackSymbols;											// 查看方法被调用的 callstack
- (instancetype)initWithTarget:(id)target selector:(SEL)selector object:(nullableid)argument;			// 线程初始化(需要再调用 start 方法才能启动)
- (instancetype)init NS_DESIGNATED_INITIALIZER;							// 线程初始化
- (void)start															// 线程启动
- (void)cancel															// 线程取消
- (void)main															// 线程启动

performSelectorInBackground ?
```

NSThread 锁

```
// 使用 synchronized 将当前对象加锁
@synchronized (self) { };
// 使用 NSCondition 对象对代码块加锁
@property (nonatomic, strong) NSCondition *condition;
[self.condition lock];
[self.condition unlock];
// 使用 NSLock 对象加锁
```

## GCD, Grand Central Dispatch

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

## NSOperation

1. 子类: NSInvocationOperation(同步方式, 阻塞当前线程), NSBlockOperation
2. 自定义类, 继承 NSOperation
3. 线程池: NSOperationQueue 最大线程数

依赖关系

addDependency

相互依赖会造成死锁

NSRunLoop

```
typedef NS_ENUM (NSInteger, NSOperationQueuePriority) {//队列优先级
	NSOperationQueuePriorityVeryLow  = -8L,
	NSOperationQueuePriorityLow      = -4L,
	NSOperationQueuePriorityNormal   = 0,
	NSOperationQueuePriorityHigh     = 4,
	NSOperationQueuePriorityVeryHigh = 8
};
@property(readonly, getter=isCancelled)		BOOL cancelled;		// 是否已经取消
@property(readonly, getter=isExecuting)		BOOL executing;//是否正在执行
@property(readonly, getter=isFinished)		BOOL finished;//是否已经结束
@property(readonly, getter=isConcurrent)	BOOL concurrent;	// To be deprecated; use and override 'asynchronous' below//是否并发
@property(readonly, getter=isAsynchronous)	BOOL asynchronous NS_AVAILABLE(10_8,7_0);
@property(readonly, getter=isReady)			BOOL ready;
@property(readonly, copy)					NSArray *dependencies;	//获取所有依赖
@property NSOperationQueuePriority queuePriority;//优先级属性
@property double threadPriority NS_DEPRECATED(10_6,10_10,4_0,8_0);
@property NSQualityOfService qualityOfServiceNS_AVAILABLE(10_10,8_0);
@property(nullable,copy) NSString *name NS_AVAILABLE(10_10,8_0);
@property(nullable,copy) void(^completionBlock)(void);//执行结束block

- (void)start;									// 启动
- (void)main;									// 启动
- (void)cancel;									// 取消
- (void)addDependency:(NSOperation*)op;			// 添加依赖
- (void)removeDependency:(NSOperation*)op;		// 移除依赖
- (void)waitUntilFinished;
```

# 参考

1. [iOS多线程GCD](http://www.cnblogs.com/pure/archive/2013/03/31/2977420.html)

博客

1. [iOS多线程与GCD 你看我就够了](http://www.cocoachina.com/ios/20160804/17291.html)
2. [iOS系统库头文件中NS_AVAILABLE相关](http://www.jianshu.com/p/55adac99377b)
3. [小笨狼漫谈多线程：NSThread](http://www.cocoachina.com/ios/20160225/15421.html)
4. [NS_DESIGNATED_INITIALIZER宏 ](http://www.cocoachina.com/bbs/read.php?tid-282223.html)
