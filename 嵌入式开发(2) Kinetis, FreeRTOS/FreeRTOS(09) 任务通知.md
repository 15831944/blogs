# 任务通知 Task Notifications

1. 中介对象(Intermediary Objects): 通过创建中介对象进行任务间的通信, 包括: 队列, 事件组, 信号量, 互斥锁, 任务间的事件和数据的收发都通过中介对象而不是直接通信
2. 任务通知(Task Notifications): 任务通知使任务可以直接作用于其他任务, 并且和ISR通信, 任务可以直接发送事件到另一个事件或ISR, 经常可被用于替换所有中介对象

任务的通知状态 Notification State

1. 挂起 Pending, 任务接收到通知, 任务可以处于阻塞状态等待通知状态变为挂起
2. 未挂起 Not-Pending, 任务读取它的通知值

任务的通知值 Notification Value, 32位无符号整数

优势 Benefits

1. 性能优势 Performance Benefits: 显著增加发送事件和数据到一个任务的速度
2. 内存优势 RAM Footprint Benefits: 中介对象必须先创建后使用, 而使用任务通知, 每个任务只需要8个字节的RAM的固定开销

限制 Limitations

1. 不能发送事件和数据到 ISR
2. 只有接收任务可以处理该通知
3. 接收任务的通知值一次只能保存一个值, 不能缓存
4. 只能发送给一个接收任务
5. 接收任务已经有通知挂起时(相当于队列满), 发送任务不能阻塞等待

```
xTaskNotify()		// 发送任务通知
xTaskNotifyWait()	// 接收任务通知

xTaskNotifyGive()			// 发送任务通知(更简单的版本), 接收任务的通知值加1, 通知状态变为挂起, 可代替信号量
vTaskNotifyGiveFromISR()	// 接收任务离开阻塞状态

ulTaskNotifyTake()			// 接收任务在阻塞状态等待通知值大于1, 并且在返回前使通知值减1或清0

```
