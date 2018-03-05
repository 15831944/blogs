# 软件计时器管理 Software Timer Management

1. 软件定时器用于安排函数在未来一段时间内或以固定的频率周期的执行
2. 软件定时器执行的这个函数叫做软件定时器的回调函数
3. 软件定时器由 FreeRTOS 内核实现并在其控制下, 不需要硬件支持, 与硬件定时器和硬件计数器无关

1. 软件定时器回调函数 Software Timer Callback Functions: 原型固定, 必须短小, 不可以(使调用任务)进入阻塞状态
2. 软件定时器的周期 Period of a Software Timer: 软件定时器开始到软件定时器回调函数执行的心跳中断(tick interrupt)数, 即回调函数延时执行

软件定时器的类型

1. One-shot timers: 只会执行一次回调函数, 可以手动重新执行, 执行完后进入休眠状态
2. Auto-reload timers: 每次过期(expire)后都会重新开始, 周期性地调用回调函数, 执行完后重新进入运行状态

软件定时器状态 Software Timer States

1. Dormant: 存在且可以被句柄引用但不运行
2. Running: 从进入运行状态或复位开始, 经过周期时间, 执行回调函数

守护任务 RTOS daemon task

1. 所有的软件定时回调函数执行在同一个守护守护任务上下文中(由守护任务调用), 回调函数阻塞会导致守护任务进入阻塞状态
2. 守护任务是一个标准的 FreeRTOS 任务, 在调度器启动时自动被创建
3. 曾经被叫做定时器服务(timer service)任务, 现在则有更多用途
4. 守护任务只会处理定时器命令和执行定时器回调函数

定时器命令队列 The Timer Command Queue

1. 软件定时器API函数通过称为定时器命令队列的队列从调用任务向守护任务发送命令
2. 定时器命令队列是一个标准的 FreeRTOS 队列, 在调度器启动时自动被创建

定时器ID: 多个软件定时器共用同一个回调函数时, 用于提供定时器具体的存储

```
FreeRTOS/Source/timers.c
void ATimerCallback( TimerHandle_t xTimer );

xTimerCreate()			// 创建后处于休眠状态, 可以在调度器运行前创建或在调度器开始后的任务中创建
xTimerCreateStatic()

xTimerStart()			// 启动休眠状态的定时器, 重新启动(复位)运行状态的定时器, 可以在调度器开始前调用, 但是定时器在调度器开始后才会真正的开始
xTimerStartFromISR()
xTimerReset()
xTimerResetFromISR()
xTimerChangePeriod()
xTimerChangePeriodFromISR()

vTimerSetTimerID()		// 直接访问软件定时器, 而不是发送命令到定时器命令队列
pvTimerGetTimerID()

xTimerStop()			// 停止运行状态的定时器, 相当于将定时器转移到休眠状态

xTimerDelete()	// 任意时刻均可删除
```
