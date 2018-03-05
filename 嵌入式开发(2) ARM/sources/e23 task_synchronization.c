// Example 23. Synchronizing tasks

/* Definitions for the event bits in the event group. */
#define mainFIRST_TASK_BIT ( 1UL << 0UL )
#define mainSECOND_TASK_BIT( 1UL << 1UL )
#define mainTHIRD_TASK_BIT ( 1UL << 2UL )

EventGroupHandle_t xEventGroup;

// 任务函数, 各实例的事件位由参数传入
static void vSyncingTask( void *pvParameters )
{
	const TickType_t	xMaxDelay = pdMS_TO_TICKS( 4000UL );
	const TickType_t	xMinDelay = pdMS_TO_TICKS( 200UL );
	TickType_t			xDelayTime;
	EventBits_t			uxThisTasksSyncBit;
	const EventBits_t	uxAllSyncBits = ( mainFIRST_TASK_BIT | mainSECOND_TASK_BIT | mainTHIRD_TASK_BIT );

	uxThisTasksSyncBit = ( EventBits_t ) pvParameters;	// 当前任务实例使用的事件位, 置位以指示次任务到达同步点
	for( ;; )
	{
		xDelayTime = ( rand() % xMaxDelay ) + xMinDelay;	// 延迟随机的时间, 防止该任务的实例同时到达同步点, 便于观察
		vTaskDelay( xDelayTime );
		vPrintTwoStrings( pcTaskGetTaskName( NULL ), "reached sync point" );				// 不同时到达, 但几乎同时离开
		// 三个函数三次调用同一个函数, 但是使用的是同一个事件组的实体, 而事件位的测试和清除是一个原子操作, 因此三个任务会一同解锁, 然后事件位会一同被清除
		// 如果三个函数分别先后调用三次 xEventGroupWaitBits 函数, 即非原子操作, 则事件位被先后清除, 后调用的任务无法满足解锁条件
		xEventGroupSync( xEventGroup, uxThisTasksSyncBit, uxAllSyncBits, portMAX_DELAY );	// 置位自己, 等待所有任务到达其各自的同步点
		vPrintTwoStrings( pcTaskGetTaskName( NULL ), "exited sync point" );					// 所有任务都到达同步点后, 才会执行到这里
	}
}

int main( void )
{
	xEventGroup = xEventGroupCreate();
	xTaskCreate(vSyncingTask, "Task 1", 1000, mainFIRST_TASK_BIT,  1, NULL);
	xTaskCreate(vSyncingTask, "Task 2", 1000, mainSECOND_TASK_BIT, 1, NULL);
	xTaskCreate(vSyncingTask, "Task 3", 1000, mainTHIRD_TASK_BIT,  1, NULL);
	vTaskStartScheduler();
	for( ;; );
	return 0;
}

# if 0
// 任务同步, 两个任务共用一个套接字(UNIX 中服务器和客户端分别有各自的套接字?)

// 发送数据任务
void SocketTxTask( void *pvParameters )
{
	xSocket_t	xSocket;
	uint32_t	ulTxCount = 0UL;
	for( ;; )
	{
		xSocket = FreeRTOS_socket( ... );	// 创建套接字, 此任务向这个套接字发送数据, 另一个任务从这个套接字接收数据
		FreeRTOS_connect( xSocket, ... );	// 连接套接字
		xQueueSend( xSocketPassingQueue, &xSocket, portMAX_DELAY );	// 使用队列将套接字发送到接收数据的任务
		for( ulTxCount = 0; ulTxCount < 1000; ulTxCount++ )			// 向套接字发送消息
		{
			if( FreeRTOS_send( xSocket, ... ) < 0 )
			{
				break;
			}
		}
		TxTaskWantsToCloseSocket();			// 告诉接收任务, 发送任务想要关闭套接字
		xEventGroupSync( ... );				// 发送任务的同步点, 发送任务阻塞在这里等待接收任务到达其同步点, 接收任务在不再使用套接字时才会到达同步点, 这样套接字就可以安全的被关闭
		FreeRTOS_shutdown( xSocket, ... );	// 两个任务都不再使用套接字, 断开连接, 然后关闭套接字
		WaitForSocketToDisconnect();
		FreeRTOS_closesocket( xSocket );
	}
}

// 接收数据任务
void SocketRxTask( void *pvParameters )
{
	xSocket_t xSocket;
	for( ;; )
	{
		xQueueReceive( xSocketPassingQueue, &xSocket, portMAX_DELAY );	// 接收由发送任务创建和连接的套接字
		while( TxTaskWantsToCloseSocket() == pdFALSE )	// 持续从套接字接收数据, 直到发送任务想要关闭套接字
		{
			FreeRTOS_recv( xSocket, ... );	// 接收数据
			ProcessReceivedData();			// 处理数据
		}
		xEventGroupSync( ... );	// 接收任务的同步点, 不再使用套接字是执行到这里, 这样接收任务关闭套接字才是安全的
	}
}
#endif
