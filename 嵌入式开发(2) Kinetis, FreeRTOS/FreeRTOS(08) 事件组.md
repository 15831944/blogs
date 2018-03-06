# 事件组 Event Groups

信号量和队列

1. 使任务处于阻塞状态等待事件发生
2. 事件发生时解锁优先级最高的任务

事件组

1. 使任务处于阻塞状态等待一组事件发生(置位)
2. 一组事件发生时解锁所有等待中的任务

1. 事件组用于同步多个任务, 将事件广播给多个任务, 使任务处于阻塞状态等待一组事件中的任意事件发生或等待多个操作完成
2. 事件组减少应用程序对RAM的使用, 使用一个事件组就可以代替多个二值信号量

event_groups.c

1. Event Flags: 用于指示事件是否发生的布尔值, 存储在 EventBits_t 类型的变量的一个位中, 因此也叫 Event Bits
2. Event Groups: 一组 Event Flags, 事件状态存储在 EventBits_t 类型的变量中, 32位宽, 一个事件组可配置8个或24个可用的事件位(configUSE_16_BIT_TICKS分别为1或0)

一个事件组可被多个任务置位和读取

# 事件管理 Event Management

1. 解锁条件 unblock condition: 调度器使用 unblock condition 决定任务是否会进入阻塞状态并何时离开阻塞状态
2. 任务调用 xEventGroupWaitBits 函数时, 如果 unblock condition 满足, 则该任务不会进入阻塞状态(没有需要等待的事件), 否则进入阻塞并等待事件组中的事件发生
3. 在 xEventGroupWaitBits 函数中 unblock condition 条件由以下2个参数的组合决定

uxBitsToWaitFor 参数指定测试事件组中的哪些位参与解锁判断
xWaitForAllBits 参数指定测试的这些位使用按位或还是按位与
xClearOnExit 参数在解锁条件满足(任务离开阻塞状态)后清除事件位(相当于执行 take 操作)

API 函数

```
EventGroupHandle_t
EventBits_t
BaseType_t pdPASS 和 pdFALSE
TickType_t

xEventGroupCreate()			// 返回事件组句柄(EventGroupHandle_t 类型)
xEventGroupCreateStatic()	// 在编译时静态分配内存

xEventGroupSetBits()		// 用于调用任务通知阻塞中的任务该位表示的事件已发生, 按位或操作(相当于 give 操作), 会使不确定数目的任务离开阻塞状态(二值信号量最多使一个任务离开阻塞状态)
EventGroupSetBitsFromISR()	// 事件组的置位操作属于非确定性操作 non-deterministic operations, 置位操作通过发送命令到 timer command queue 来推迟到 RTOS daemon task 中执行

xEventGroupWaitBits()		// 允许任务读取事件组的值, 并选择性地在阻塞状态等待其中一个或多个还未发生的事件, 事件位的测试和清除是一个原子操作
xEventGroupClearBits()		// 调用xEventGroupWaitBits函数的任务使用此函数清除事件位会导致竞争条件 race conditions, 不常用
```

# 任务同步 Task Synchronization

任务运行在各自的死循环，不同的执行流中，为了让各任务相互协调配合，有序（同步）的完成一个工作，就涉及到一个任务需要等待另一个任务，如果等待是单向的，则事件组的置位和清除放在不同的任务中，如果任务之间相互等待，等待任务清除被等待任务的事件组，则事件组的测试和清除需要成为一个原子操作。

1. 多个任务协同完成一个事件时, 则多个任务间需要同步, 例如两个任务共用一个 TCP socket, 一个向套接字发送数据, 另一个从该套接字接收数据, 一个任务想要关闭这个套接字必须先确保另一个任务不会再访问这个套接字
2. 事件组可以用于创建同步点, 每个任务对应事件组的一个位, 到达同步点时置位该位, 然后每个任务阻塞在事件组等待其他任务到达同步点(置位), 置位和测试操作必须合成一个不可中断的操作

同步点 synchronization point, 相当于事件发生, 事件位置位

事件管理中, 事件发生的任务和等待事件的任务是不同的任务
任务同步中, 到达同步点的任务彼此都是对等的, 任务之间互相等待, 例如A和B等待C, C等待ABC, A和B置位后等待C, C置位后清除A和B, A和B清除C, 由于C的置位和测试不是原子操作, C等待ABC就永远不会满足

一个任务能置位自己, 等待谁就清除谁

```
xEventGroupSync()			// 事件位的置位和测试是一个原子操作, 解锁条件满足后则清除该事件位
```
