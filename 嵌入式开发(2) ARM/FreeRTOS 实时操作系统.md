# 第1章 任务管理

小型多任务嵌入式系统

1. 软实时: 计算机对每一个输入的响应应当限定在一个恰当的时间范围
2. 硬实时: 任务必须在给定的时间限制内完成

任务

1. 调度器: 能够让任务切入切出的唯一实体, 任务函数相同的任务实例之间是独立运行的, 总是在所有就绪态任务中选择具有最高优先级的任务，并使其进入运行态。

1. 任务: 每个执行线程都被称为任务
2. 任务函数: 实现为死循环, 可以在一个任务函数中创建另一个任务, 效果和分别创建相同
3. 任务实例: 创建任务时产生任务实例
4. 顶层任务状态: 运行状态, 非运行状态
5. 任务转移: 非运行状态到运行状态, 切入(switched in), 切出(switched out)

1. 任务优先级: 任意数量的任务共享同一个优先级
2. 时间片: 心跳中断的频率的倒数
3. 时钟心跳(时钟滴答, tick):
4. 心跳中断(tick interrupt): 调度器在一个任务的时间片结束时通过心跳终端运行调度器(操作系统内核)自身, 调度器运行在心跳中断中, 心跳中断开始和完成即一个时间片的开始和结束
5. 心跳计数(tick count): 从调度器启动开始, 心跳中断总数
6. 饿死(starved): 如果高优先级的任务一直处于运行状态(不进入阻塞状态), 由于调度器总会选择高优先级任务, 低优先级任务的执行时间会被高优先级任务饿死

1. 持续处理(continuous processing)任务: 一直运行, 无阻塞
2. 周期任务(Periodic task)
1. 事件驱动任务: 高优先级任务由事件驱动, 没有事件发生则不能运行, 则调度器会选择优先级次之的能够进入运行状态的任务, 避免低优先级任务被饿死

1. 运行状态（running)
2. 阻塞状态(blocked): 任务正在等待时间发生
3. 挂起状态(suspended): 对调度器不可见
4. 就绪状态(ready):

1. 定时事件:
2. 同步事件: 队列, 二值信号量, 计数信号量, 互斥(递归)信号量, 互斥量, 都可以实现同步事件,

1. 等待超时时间: 同步事件等待超时则推出阻塞状态

空闲任务

1. 空闲任务: 拥有最低优先级0
2. 空闲任务钩子函数(或称回调，hook, or call-back)，可以直接在空闲任务中添加应用程序相关的功能。空闲任务钩子函数会被空闲任务每循环一次就自动调用一次。

1. 执行低优先级，后台或需要不停处理的功能代码。
2. 测试处系统处理裕量(空闲任务只会在所有其它任务都不运行时才有机会执行，所以测量出空闲任务占用的处理时间就可以清楚的知道系统有多少富余的处理时间)。
3. 将处理器配置到低功耗模式——提供一种自动省电方法，使得在没有任何应用功能需要处理的时候，系统自动进入省电模式。

1. 绝不能阻或挂起。空闲任务只会在其它任务都不运行时才会被执行(除非有应用任务共享空闲任务优先级)。以任何方式阻塞空闲任务都可能导致没有任务能够进入运行态！
2. 如果应用程序用到了 vTaskDelete() AP 函数，则空闲钩子函数必须能够尽快返回。因为在任务被删除后，空闲任务负责回收内核资源。如果空闲任务一直运行在钩子函数中，则无法进行回收工作。

调度算法

1. 抢占式调度(固定优先级): 高优先级抢占(pre_empted)低优先级任务
2. 协作式调度: 采用一个纯粹的协作式调度器，只可能在运行态任务进入阻塞态或是运行态任务显式调用taskYIELD()时，才会进行上下文切换。
3. 混合调度: 需要在中断服务例程中显式地进行上下文切换，从而允许同步事件产生抢占行为，但时间事件却不行。这样做的结果是得到了一个没有时间片机制的抢占式系统。

单调速率调度(Rate Monotonic Scheduling, RMS)是一种常用的优先级分配技术。
其根据任务周期性执行的速率来分配一个唯一的优先级。具有最高周期执行频率的任务
赋予高最优先级；具有最低周期执行频率的任务赋予最低优先级。这种优先级分配方式
被证明了可以最大化整个应用程序的可调度性(schedulability)

API

```
void ATaskFunction(void *pvParameters);
// 创建任务, 创建成功则返回 pdTRUE, 否则返回 errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY
portBASE_TYPE xTaskCreate(	pdTASK_CODE				pvTaskCode,			// 指向任务函数的指针
							const signed portCHAR	*const pcName,		// 描述性的任务名
							unsigned portSHORT		usStackDepth,		// 栈空间(字) = 栈宽度 * 栈深度, 最大 size_t
							void					*pvParameters,		// 任务函数参数
							unsigned portBASE_TYPE	uxPriority,			// 任务优先级
							xTaskHandle				*pxCreatedTask);	// 任务句柄

vTaskStartScheduler();		// 启动调度器开始执行已创建的任务
vTaskSuspend();				// 将任务挂起
vTaskResume();				// 唤醒挂起的任务
vTaskResumeFromISR();		// 唤醒挂起的任务
void	TaskPrioritySet(xTaskHandle pxTask, unsigned portBASE_TYPE uxNewPriority);	// 在任务启动后修改任务优先级
unsigned portBASE_TYPE	uxTaskPriorityGet( xTaskHandle pxTask );						// 查询任务优先级
void	vTaskDelay(portTickType xTicksToDelay);										// 使任务进入阻塞状态, 经过参数指定的心跳周期数后, 进入就绪状态
void	vTaskDelayUntil(portTickType *pxPreviousWakeTime, portTickType xTimeIncrement);// 调用此函数并进入阻塞后, 在绝对时刻进入就绪状态
void	vTaskDelete(xTaskHandle pxTaskToDelete);			// 删除指定任务, 参数为 NULL 则删除当前任务
void	vApplicationIdleHook(void);							// 定义钩子函数
```

宏定义

```
#include <FreeRTOSConfig.h>
config_MAX_TASK_NAME_LEN 最长任务名
configMINIMAL_STACK_SIZE 空闲任务栈空间大小
configMAX_PRIORITIES     最高优先级(需要减1)
configTICK_RATE_HZ       心跳中断频率
configUSE_IDLE_HOOK
portTICK_RATE_MS
mainDELAY_LOOP_COUNT
```

# 第2章 队列管理

1. 队列: 应用程序由一组独立的任务构成, 线程间所有的通信与同步机制都是基于队列实现的
队列可以保存的最大单元数目被称为队列的“深度”。
队列是具有自己独立权限的内核对象，并不属于或赋予任何任务。所有任务都可以向同一队列写入和读出。一个队列由多方写入是经常的事，但由多方读出倒是很少遇到。
队列读写阻塞
中断服务例程

```
xQueueHandle xQueueCreate( unsigned portBASE_TYPE uxQueueLength, unsigned portBASE_TYPE uxItemSize );	// 创建队列
portBASE_TYPE xQueueSendToFront( xQueueHandle xQueue, const void * pvItemToQueue, portTickType xTicksToWait );
portBASE_TYPE xQueueSendToBack( xQueueHandle xQueue, const void * pvItemToQueue, portTickType xTicksToWait );
portBASE_TYPE xQueueReceive( xQueueHandle xQueue, const void * pvBuffer, portTickType xTicksToWait )
portBASE_TYPE xQueuePeek( xQueueHandle xQueue, const void * pvBuffer, portTickType xTicksToWait );
unsigned portBASE_TYPE uxQueueMessagesWaiting( xQueueHandle xQueue );

xQueueSend();
xQueueSendFromISR();
xQueueSendToFrontFromISR()
xQueueSendToBackFromISR()
xQueueReceiveFromISR()
uxQueueMessagesWaitingFromISR()

portMAX_DELAY
INCLUDE_vTaskSuspend

```

# 第3章 中断管理

1. 二值信号量, 用于让任务和中断进行同步, 在锁存的事件还未被处理之前，如果还有中断事件发生，那么后续发生的中断事件将会丢失

1. 中断服务例程(ISR), 事件发生后, 使用信号量解锁(give, V操作, 资源或事件加1)中断处理任务
2. 延迟处理任务(Handler Task), 得以处理事件, 然后加锁(take, P操作, 资源或事件减1)以等待下一事件发生

```
void			vSemaphoreCreateBinary(xSemaphoreHandle xSemaphore);	// 创建信号量
portBASE_TYPE	xSemaphoreTake(xSemaphoreHandle xSemaphore, portTickType xTicksToWait);		// 加锁, 获取信号量, 由延迟处理任务调用, 相当于读取队列, 队列为空则阻塞
portBASE_TYPE	xSemaphoreGiveFromISR(xSemaphoreHandle xSemaphore, portBASE_TYPE *pxHigherPriorityTaskWoken);	// 解锁, 由中断服务例程调用
```

1. 计数信号量

1. 事件计数, 初始化为0
2. 资源管理, 初始化为可用资源总数

```
xSemaphoreHandle xSemaphoreCreateCounting(unsigned portBASE_TYPE uxMaxCount, unsigned portBASE_TYPE uxInitialCount);
```

1. 中断服务例程中使用队列

```
portBASE_TYPE xQueueSendToFrontFromISR(xQueueHandle xQueue, void *pvItemToQueue, portBASE_TYPE *pxHigherPriorityTaskWoken);
portBASE_TYPE xQueueSendToBackFromISR(xQueueHandle xQueue, void *pvItemToQueue, portBASE_TYPE *pxHigherPriorityTaskWoken);
```

中断嵌套

# 第4章 资源管理

互斥量

# 第5章 内存管理



# 第6章 错误排查

栈溢出

# 参考

《FreeRTOS 入门手册》
