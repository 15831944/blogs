# 资源管理 Resource Management

被多任务共享，或是被任务与中断共享的资源

1. 访问外设
2. 读改写操作
3. 变量的非原子访问
4. 函数重入: 如果一个函数除了访问自己栈空间上分配的数据或是内核寄存器中的数据外，不会访问其它任何数据，则这个函数就是可重入的, 可以安全地被多个任务调用，或是在任务与中断中均可调用

临界区 Critical Sections

```
taskENTER_CRITICAL()	把中断全部关掉，或是关掉优先级在configMAX_SYSCAL_INTERRUPT_PRIORITY 及以下的中断
taskEXIT_CRITICAL()		退出临界区
```

挂起(锁定)调度器 Suspending the Scheduler

1. 停止上下文切换而不用关中断

```
vTaskSuspendAll()
xTaskResumeAll()
```

互斥量 MUTEX, Mutual Exclusion

1. 互斥量是一种特殊的二值信号量，用于控制在两个或多个任务间访问共享资源
2. 优先级反转 Priority Inversion
3. 优先级继承 Priority Inheritance
4. 死锁 Deadlock

```
xSemaphoreCreateMutex();
xSemaphoreTake();
xSemaphoreGive();
```

守护任务 Gatekeeper Tasks

1. 守护任务是对某个资源具有唯一所有权的任务。只有守护任务才可以直接访问其守护的资源——其它任务要访问该资源只能间接地通过守护任务提供的服务。
2. 任务本身不访问资源, 而是将消息发送到守护任务间接访问
