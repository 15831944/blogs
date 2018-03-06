# 中断管理 Interrupt Management

事件 Events

1. 任务优先级: 软件优先级
2. 中断优先级: 由微控制器架构体系所定义, 是硬件控制的, 中断服务例程的执行会与之关联

1. 中断安全
2. 线程安全特性

延迟中断处理 Deferred Interrupt Processing

1. 中断服务例程(ISRs): 越短小越好
2. 延迟中断处理: 中断的发生和清除在 ISR 中记录, 而具体的中断处理则延迟在任务中实现, 称为延迟中断处理

二值信号量 Binary Semaphores

1. 二值信号量, 可用于实现应用任务和硬件中断同步, 实现延迟中断处理, 最多只可以锁存一个中断事件
2. 中断服务例程(ISR)中, 在事件发生后, 使用二值信号量解锁(give, V操作, 资源或事件加1)延迟中断处理任务(调用xSemaphoreGiveFromISR()函数)
3. 延迟处理任务(Handler Task)中, 被解锁后, 得以处理事件, 然后加锁(take, P操作, 资源或事件减1)以等待下一事件发生(调用xSemaphoreTake()函数)
4. 注意二值信号量的获取和释放不是由同一个任务完成的

计数信号量 Counting Semaphores

1. 事件计数, 初始化为0
2. 资源管理, 初始化为可用资源总数

在中断服务例程中使用队列 Using Queues within an ISR

1. 信号量用于事件通信。而队列不仅可以用于事件通信，还可以用来传递数据。

中断嵌套 Interrupt Nesting

```
configKERNEL_INTERRUPT_PRIORITY			设置系统心跳时钟的中断优先级。如果在移植中没有使用第二个常量，那么需要调用中断安全版本 FreeRTOS API 的中断都必须运行在此优先级上。
configMAX_SYSCALL_INTERRUPT_PRIORITY	设置中断安全版本 FreeRTOS API 可以运行的最高中断优先级。
```

Interrupt Safe API 函数

```
vSemaphoreCreateBinary();	// 创建二值信号量
xSemaphoreTake();			// 加锁, 获取信号量, 由延迟处理任务调用, 相当于读取队列, 队列为空则阻塞
xSemaphoreGiveFromISR();	// 解锁, 由中断服务例程调用

xSemaphoreCreateCounting();	// 创建计数信号量

xQueueSendToFrontFromISR();
xQueueSendToBackFromISR();
xQueueSendFromISR();
xQueueReceiveFromISR();
uxQueueMessagesWaitingFromISR();
```
