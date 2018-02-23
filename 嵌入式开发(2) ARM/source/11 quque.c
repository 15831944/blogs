/* 例 11. 写队列时阻塞 / 往队列发送结构体 */


/* 定义队列传递的结构类型。 */
typedef struct
{
	unsigned char ucValue;
	unsigned char ucSource;
} xData;

/* 声明两个xData类型的变量，通过队列进行传递。 */
static const xData xStructsToSend[ 2 ] =
{
	{ 100, mainSENDER_1 }, /* Used by Sender1. */
	{ 200, mainSENDER_2 } /* Used by Sender2. */
};

static void vReceiverTask( void *pvParameters )
{
	/* 声明结构体变量以保存从队列中读出的数据单元 */
	xData xReceivedStructure;
	portBASE_TYPE xStatus;
	/* This task is also defined within an infinite loop. */
	for( ;; )
	{
		/* 读队列任务的优先级最低，所以其只可能在写队列任务阻塞时得到执行。而写队列任务只会在队列写
		满时才会进入阻塞态，所以读队列任务执行时队列肯定已满。所以队列中数据单元的个数应当等于队列的
		深度 – 本例中队列深度为3 */
		if( uxQueueMessagesWaiting( xQueue ) != 3 )
		{
			vPrintString( "Queue should have been full!\r\n" );
		}
		/* Receive from the queue.
		第二个参数是存放接收数据的缓存空间。本例简单地采用一个具有足够空间大小的变量的地址。
		第三个参数是阻塞超时时间 – 本例不需要指定超时时间，因为读队列任会只会在队列满时才会得到执行，
		故而不会因队列空而阻塞 */
		xStatus = xQueueReceive( xQueue, &xReceivedStructure, 0 );
		if( xStatus == pdPASS )
		{
			/* 数据成功读出，打印输出数值及数据来源。 */
			if( xReceivedStructure.ucSource == mainSENDER_1 )
			{
				vPrintStringAndNumber( "From Sender 1 = ", xReceivedStructure.ucValue );
			}
			else
			{
				vPrintStringAndNumber( "From Sender 2 = ", xReceivedStructure.ucValue );
			}
		}
		else
		{
			/* 没有读到任何数据。这一定是发生了错误，因为此任务只支在队列满时才会得到执行 */
			vPrintString( "Could not receive from the queue.\r\n" );
		}
	}
}

int main( void )
{
	/* 创建队列用于保存最多3个xData类型的数据单元。 */
	xQueue = xQueueCreate( 3, sizeof( xData ) );
	if( xQueue != NULL )
	{
		/* 为写队列任务创建2个实例。 The
		任务入口参数用于传递发送到队列中的数据。因此其中一个任务往队列中一直写入
		xStructsToSend[0]，而另一个则往队列中一直写入xStructsToSend[1]。这两个任务的优先级都
		设为2，高于读队列任务的优先级 */
		xTaskCreate( vSenderTask, "Sender1", 1000, &( xStructsToSend[ 0 ] ), 2, NULL );
		xTaskCreate( vSenderTask, "Sender2", 1000, &( xStructsToSend[ 1 ] ), 2, NULL );
		/* 创建读队列任务。
		读队列任务优先级设为1，低于写队列任务的优先级。 */
		xTaskCreate( vReceiverTask, "Receiver", 1000, NULL, 1, NULL );
		/* 启动调度器，创建的任务得到执行。 */
		vTaskStartScheduler();
	}
	else
	{
		/* 创建队列失败。 */
	}
	/* 如果一切正常，main()函数不应该会执行到这里。但如果执行到这里，很可能是内存堆空间不足导致空闲
	任务无法创建。第五章将提供更多关于内存管理方面的信息 */
	for( ;; );
}
