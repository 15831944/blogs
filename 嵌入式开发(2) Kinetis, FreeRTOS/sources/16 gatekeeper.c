xQueueHandle xPrintQueue;

/* 定义任务和中断将会通过守护任务输出的字符串。 */
static char *pcStringsToPrint[] = {"Task 1\r\n", "Task 2\r\n", "tick hook interrupt\r\n"};

/*******************************************************************************
守护任务函数
这是唯一允许直接访问终端输出的任务。任何其它任务想要输出字符串，都不能直接访问终端，而是将要
输出的字符串发送到此任务。并且因为只有本任务才可以访问标准输出，所以本任务在实现上不需要考虑互斥
和串行化等问题。
*******************************************************************************/
static void prvStdioGatekeeperTask(void *pvParameters)
{
	char *pcMessageToPrint;

	for( ;; )
	{
		xQueueReceive( xPrintQueue, &pcMessageToPrint, portMAX_DELAY );
		printf( "%s", pcMessageToPrint );
		fflush( stdout );
	}
}

// 任务函数
static void prvPrintTask( void *pvParameters )
{
	int iIndexToString;
	iIndexToString = (int)pvParameters;
	for( ;; )
	{
		xQueueSendToBack(xPrintQueue, &(pcStringsToPrint[iIndexToString]), 0);
		vTaskDelay((rand() & 0x1FF));
	}
}

// 心跳钩子函数，每200 心跳周期就输出一个消息, 只能调用中断安全的函数
void vApplicationTickHook(void)
{
	static int		iCount = 0;
	portBASE_TYPE	xHigherPriorityTaskWoken = pdFALSE;

	if (++iCount >= 200)
	{
		xQueueSendToFrontFromISR(xPrintQueue, &(pcStringsToPrint[2]), &xHigherPriorityTaskWoken);	// 队首
		iCount = 0;
	}
}


int main( void )
{
	xPrintQueue = xQueueCreate(5, sizeof(char *));
	srand( 567 );					// 为伪随机数发生器产生种子
	if( xPrintQueue != NULL )
	{
		xTaskCreate(prvPrintTask, "Print1", 1000, (void *)0, 1, NULL);
		xTaskCreate(prvPrintTask, "Print2", 1000, (void *)1, 2, NULL);
		xTaskCreate(prvStdioGatekeeperTask, "Gatekeeper", 1000, NULL, 0, NULL);
		vTaskStartScheduler();
	}
	for( ;; );
}
