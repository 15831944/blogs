/*
例 10. 读队列时阻塞
本例示范创建一个队列，由多个任务往队列中写数据，以及从队列中把数据读出。
这个队列创建出来保存long 型数据单元。往队列中写数据的任务没有设定阻塞超时时
间，而读队列的任务设定了超时时间。
往队列中写数据的任务的优先级低于读队列任务的优先级。这意味着队列中永远不
会保持超过一个的数据单元。因为一旦有数据被写入队列，读队列任务立即解除阻塞，
抢占写队列任务，并从队列中接收数据，同时数据从队列中删除—队列再一次变为空队
列。
*/

/* 声明一个类型为 xQueueHandle 的变量. 其用于保存队列句柄，以便三个任务都可以引用此队列 */
xQueueHandle xQueue;

/* 写队列任务 参数被用来为每个实例传递各自的写入值 */
static void vSenderTask(void *pvParameters)
{
	long			lValueToSend;	// 数据单元
	portBASE_TYPE	xStatus;

	lValueToSend = (long)pvParameters;

	for( ;; )
	{
		// 不阻塞, 当队列满时，任务转入阻塞状态以等待队列空间有效。本例中没有设定超时时间，因为此队列决不会保持有超过一个数据单元的机会，所以也决不会满。
		xStatus = xQueueSendToBack( xQueue, &lValueToSend, 0 );
		if( xStatus != pdPASS )
		{
			vPrintString( "Could not send to the queue.\r\n" );
		}
		taskYIELD();	// 协作式调度, 允许其它发送任务执行, 通知调度器现在就切换到其它任务，而不必等到本任务的时间片耗尽
	}
}

/* 读队列任务 参数未使用 */
static void vReceiverTask( void *pvParameters )
{
	long				lReceivedValue;
	portBASE_TYPE		xStatus;
	const portTickType	xTicksToWait = 100 / portTICK_RATE_MS;	// 100 毫秒的阻塞超时时间

	for( ;; )
	{
		/* 此调用会发现队列一直为空，因为本任务将立即删除刚写入队列的数据单元。 */
		if( uxQueueMessagesWaiting( xQueue ) != 0 )
		{
			vPrintString( "Queue should have been empty!\r\n" );
		}
		// 阻塞, 当队列空时，任务转入阻塞状态以等待队列数据有效
		xStatus = xQueueReceive( xQueue, &lReceivedValue, xTicksToWait );
		if( xStatus == pdPASS )
		{
			/* 成功读出数据，打印出来。 */
			vPrintStringAndNumber( "Received = ", lReceivedValue );
		}
		else
		{
			/* 等待100ms也没有收到任何数据。
			必然存在错误，因为发送任务在不停地往队列中写入数据 */
			vPrintString( "Could not receive from the queue.\r\n" );
		}
	}
}

int main( void )
{
	/* 创建的队列用于保存最多5个值，每个数据单元都有足够的空间来存储一个long型变量 */
	xQueue = xQueueCreate( 5, sizeof( long ) );
	if( xQueue != NULL )
	{
		xTaskCreate(vSenderTask,   "Sender1",  1000, (void *)100, 1, NULL);
		xTaskCreate(vSenderTask,   "Sender2",  1000, (void *)200, 1, NULL);
		xTaskCreate(vReceiverTask, "Receiver", 1000, NULL,        2, NULL);	// 读队列任务优先级高
		vTaskStartScheduler();
	}
	for( ;; );
}
