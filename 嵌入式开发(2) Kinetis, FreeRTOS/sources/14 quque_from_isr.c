// 例14 利用队列在中断服务中发送或接收数据

QueueHandle_t xIntegerQueue;
QueueHandle_t xStringQueue;

// 周期任务, 向ISR发送数据, 产生软件中断
static void vIntegerGenerator( void *pvParameters )
{
	portTickType		xLastExecutionTime;
	unsigned portLONG	ulValueToSend = 0;
	int					i;

	xLastExecutionTime = xTaskGetTickCount();
	for( ;; )
	{
		vTaskDelayUntil( &xLastExecutionTime, 200 / portTICK_RATE_MS );		// 每200毫秒执行一次
		for (i = 0; i < 5; i++)
		{
			xQueueSendToBack(xIntegerQueue, &ulValueToSend, 0);		// 连续五次发送递增数值到队列, 无阻塞
			ulValueToSend++;
		}
		vPrintString("Generator task - About to generate an interrupt.\r\n");
		__asm{ int 0x82 }		// 产生中断，以让中断服务例程读取队列
		vPrintString("Generator task - Interrupt generated.\r\n\r\n\r\n");
	}
}

// 中断服务例程, 接收和发送队列数据
static void __interrupt __far vExampleInterruptHandler(void)
{
	static portBASE_TYPE	xHigherPriorityTaskWoken;
	static unsigned long	ulReceivedNumber;
	static const char *		pcStrings[] = {"String 0\r\n", "String 1\r\n", "String 2\r\n", "String 3\r\n"};

	xHigherPriorityTaskWoken = pdFALSE;
	/* 重复读队列，直到队列为空 */
	while(xQueueReceiveFromISR(xIntegerQueue, &ulReceivedNumber, &xHigherPriorityTaskWoken) != errQUEUE_EMPTY)
	{
		/* 截断收到的数据，保留低两位(数值范围0到3).然后将索引到的字符串指针发送到另一个队列 */
		ulReceivedNumber &= 0x03;
		xQueueSendToBackFromISR(xStringQueue, &pcStrings[ulReceivedNumber], &xHigherPriorityTaskWoken);
	}
	if(xHigherPriorityTaskWoken == pdTRUE)
	{
		portSWITCH_CONTEXT();
	}
}

// 周期任务, 接收来自ISR的数据, 中断处理任务
static void vStringPrinter(void *pvParameters)
{
	char *pcString;
	for( ;; )
	{
		xQueueReceive(xStringQueue, &pcString, portMAX_DELAY);	// 阻塞队列等待数据
		vPrintString(pcString);									// 打印接收到的数据
	}
}

int main( void )
{
	xIntegerQueue = xQueueCreate(10, sizeof(unsigned long));			// 创建整型队列
	xStringQueue = xQueueCreate(10, sizeof(char *));					// 创建字符串队列

	_dos_setvect(0x82, vExampleInterruptHandler);						// 安装中断服务例程
	xTaskCreate(vIntegerGenerator, "IntGen", 1000, NULL, 1, NULL);		// 创建任务用于往中断服务例程中发送数值。此任务优先级为1
	xTaskCreate(vStringPrinter,    "String", 1000, NULL, 2, NULL);		// 创建任务用于从中断服务例程中接收字符串，并打印输出。此任务优先级为2
	vTaskStartScheduler();
	for( ;; );
}
