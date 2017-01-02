# 进程

1. 进程: 进程是系统中正在运行的一个应用程序
2. 进程空间: 进程运行在其专有的空间内, 是受保护的, 一个进程不能访问另一个进程的专有空间, 或者说获得另一个进程的资源

进程的五态模型

1. 新建, 进程被创建但还未提交的状态, 新建态的进程无法运行, 因为需要操作系统给出进程管理信息: 建立资源表格, 分配资源, 加载程序, 建立地址空间表等等;
2. 就绪, 新建后具备所有进程管理信息, 一旦时间片轮转到, 即可运行
3. 运行, 运行态的进程数小于等于处理器的核心数, 当没有进程可运行时, 操作系统会指定系统空闲进程;
4. 阻塞, 等待或睡眠状态, 等待某事件发生(如 I/O 请求),  此时即使处理器分配给此进程也无法运行,
5. 终止, 操作系统要回收资源, 释放主存

# 线程

1. 线程是进程的基本执行单元, 进程想要执行任务, 必须至少有一个线程, 这一线程称为主线程, 在 iOS 开发中称为 UI 线程
2. 进程的所有任务都在线程中执行, 例如 Xcode 进程中, 编辑, 保存, 编译, 下载均是独立的线程
3. 一般将网络请求等耗时任务放在独立的线程中, 将刷新 UI 的操作放在主线程中执行

多线程的应用

1. 网络请求, 客户端向服务器发起 HTTP 请求, 服务器的 API 返回结果, 客户端再进行 UI 的展示, 此过程由于网络原因, 可能需要几秒时间才能返回, 因此一般发异步请求, 即在不阻塞工作线程和 UI 线程(期间仍然可以操作 UI)的情况下发出请求, 完成相应任务, 保证客户端的流畅性
2. 图片加载, 读本地缓存, 请求网络图片, 再缓存到本地, 下次就可直接读缓存, 同样是一个异步操作的过程
3. 文件处理, 数据处理, 任务执行等都会放到异步线程中执行

任务执行方式

1. 同步, 等任务执行完, 才会执行后面的事情, 会阻塞当前线程
2. 异步, 
1. 串行, 多个任务按照一定顺序执行, 总耗时等于各任务时间相加(队列相关概念), 上一个任务执行的结果用于下一个任务时
2. 并行, 多个任务并发执行, 总耗时等于耗时最长的那个任务

# iOS 多线程

1. 操作系统为每个线程分配时间片, 对每个线程按时间片轮转调度
2. 对于单核操作系统, 一个线程执行时, 其他线程阻塞或空闲, 宏观来看是并行, 实际为串行; 对于多核操作系统, 是真正的并行(并行的线程数小于核心数)
3. 多线程可以简化编程模型, 更加轻量级, 提高执行效率(一个任务多个人干), 提高资源利用率, 但增加程序复杂性(资源共享, 数据读写问题), 占用内存空间, 增加 CPU 调度开销
4. iOS 多线程实现技术方案包括: pThread(C 语言), NSThread, GCD, NSOperation

## pThread

```
pthread_t	pthread;
pthread_create(%pthread, NULL, childthread, NULL);
```

## NSThread

```
// 使用 alloc init 方法和 start 方法创建并执行线程对象
NSThread *thread1 = [[NSThread alloc] initWithTarget:self selector:@selector(runThread1) object:nil];
[thread1 start];

// 使用 detachNewThreadSelector 静态方法创建并执行线程(省去创建线程对象)
[NSThread detachNewThreadSelector:@selector(runThread1) toTarget:self withObject:nil];

// 使用 performSelectorInBackground 方法创建线程
[self performSelectorInBackground:@selector(runThread1) withObject:nil];
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

1. 用于多核并行计算, 自动管理线程生命周期, C 语言

```
// 全局的, 并发的线程队列, 多个任务分别是线程
dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{ });
// 创建串行线程队列, 多个任务本质上是同一个线程
dispatch_queue_t queue = dispatch_queue_create("GCD queue", DISPATCH_QUEUE_SERIAL);
// 创建并行线程队列, 多个任务分别各自是一个线程
dispatch_queue_t queue = dispatch_queue_create("GCD queue", DISPATCH_QUEUE_CONCURRENT);
```

## NSOperation

1. NSInvocationOperation 系统提供的子类, 同步方式, 阻塞当前线程
2. NSBlockOperation
2. 自定义类, 继承 NSOperation
3. 线程池: NSOperationQueue 最大线程数

状态

1. ready
2. cancelled
3. executing
4. finished
5. asynchronous

依赖关系

addDependency

相互依赖会造成死锁

NSRunLoop

# 参考

1. [iOS多线程GCD](http://www.cnblogs.com/pure/archive/2013/03/31/2977420.html)
