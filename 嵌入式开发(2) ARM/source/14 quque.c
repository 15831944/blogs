
// 例14

// 周期任务用于每 200 毫秒往队列中发送五个数值，五个数值都发送完后便产生一个软件中断
static void vIntegerGenerator( void *pvParameters )
{
	portTickType xLastExecutionTime;
	unsigned portLONG ulValueToSend = 0;
	int i;
	/* 初始化变量，用于调用 vTaskDelayUntil(). */
	xLastExecutionTime = xTaskGetTickCount();
	for( ;; )
	{
		/* 这是个周期性任务。进入阻塞态，直到该再次运行的时刻。此任务每200毫秒执行一次 */
		vTaskDelayUntil( &xLastExecutionTime, 200 / portTICK_RATE_MS );
		/* 连续五次发送递增数值到队列。这此数值将在中断服务例程中读出。中断服务例程会将队列读空，所
		以此任务可以确保将所有的数值都发送到队列。因此不需要指定阻塞超时时间 */
		for( i = 0; i < 5; i++ )
		{
			xQueueSendToBack( xIntegerQueue, &ulValueToSend, 0 );
			ulValueToSend++;
		}
		/* 产生中断，以让中断服务例程读取队列 */
		vPrintString( "Generator task - About to generate an interrupt.\r\n" );
		__asm{ int 0x82 } /* This line generates the interrupt. */
		vPrintString( "Generator task - Interrupt generated.\r\n\r\n\r\n" );
	}
}

/*
中断服务例程重复调用 xQueueReceiveFromISR()，直到被周期任务写到队列的数
值都被读出，以将队列读空。每个接收到的数值的低两位用于一个字符串数组的索引，
被索引到的字符串的指针将通过调用xQueueSendFromISR()发送到另一个队列中。
*/
static void __interrupt __far vExampleInterruptHandler( void )
{
	static portBASE_TYPE xHigherPriorityTaskWoken;
	static unsigned long ulReceivedNumber;
	/* 这些字符串被声明为static const，以保证它们不会被定位到ISR的栈空间中，即使ISR没有运行它们也是存
	在的 */
	static const char *pcStrings[] = {
	"String 0\r\n",
	"String 1\r\n",
	"String 2\r\n",
	"String 3\r\n"
	};
	xHigherPriorityTaskWoken = pdFALSE;
	/* 重复执行，直到队列为空 */
	while( xQueueReceiveFromISR( xIntegerQueue, &ulReceivedNumber, &xHigherPriorityTaskWoken ) != errQUEUE_EMPTY )
	{
		/* 截断收到的数据，保留低两位(数值范围0到3).然后将索引到的字符串指针发送到另一个队列 */
		ulReceivedNumber &= 0x03;
		xQueueSendToBackFromISR( xStringQueue,
		&pcStrings[ ulReceivedNumber ],
		&xHigherPriorityTaskWoken );
	}
	/* 被队列读写操作解除阻塞的任务，其优先级是否高于当前任务？如果是，则进行任务上下文切换 */
	if( xHigherPriorityTaskWoken == pdTRUE )
	{
		/* 说明：在实际使用中，ISR中强制上下文切换的宏依赖于具体移植。此处调用的是基于Open Watcom
		DOS移植的宏。其它平台下的移植可能有不同的语法要求。对于实际使用的平台，请参如数对应移植自带
		的示例程序，以决定正确的语法和符号。 */
		portSWITCH_CONTEXT();
	}
}

/* 另一个任务将接收从中断服务例程发出的字符串指针。此任务在读队列时被阻塞，
直到队列中有消息到来，并将接收到的字符串打印输出 */
static void vStringPrinter( void *pvParameters )
{
	char *pcString;
	for( ;; )
	{
		/* Block on the queue to wait for data to arrive. */
		xQueueReceive( xStringQueue, &pcString, portMAX_DELAY );
		/* Print out the string received. */
		vPrintString( pcString );
	}
}

int main( void )
{
	/* 队列使用前必须先创建。本例中创建了两个队列。一个队列用于保存类型为unsigned long的变量，另一
	个队列用于保存类型为char*的变量。两个队列的深度都为10。在实际应用中应当检测返回值以确保队列创建
	成功 */
	xIntegerQueue = xQueueCreate( 10, sizeof( unsigned long ) );
	xStringQueue = xQueueCreate( 10, sizeof( char * ) );
	/* 安装中断服务例程。 */
	_dos_setvect( 0x82, vExampleInterruptHandler );
	/* 创建任务用于往中断服务例程中发送数值。此任务优先级为1 */
	xTaskCreate( vIntegerGenerator, "IntGen", 1000, NULL, 1, NULL );
	/* 创建任务用于从中断服务例程中接收字符串，并打印输出。此任务优先级为2 */
	xTaskCreate( vStringPrinter, "String", 1000, NULL, 2, NULL );
	/* Start the scheduler so the created tasks start executing. */
	vTaskStartScheduler();
	/* 如果一切正常，main()函数不会执行到这里，因为调度器已经开始运行任务。但如果程序运行到了这里，
	很可能是由于系统内存不足而无法创建空闲任务。第五章会提供更多关于内存管理的信息 */
	for( ;; );
}
