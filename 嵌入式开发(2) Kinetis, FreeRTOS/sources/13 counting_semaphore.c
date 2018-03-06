// 例13 利用计数信号量对任务和中断进行同步

xSemaphoreHandle xCountingSemaphore;

// 周期性任务, 用于每隔 500 毫秒产生一个软件中断
static void vPeriodicTask( void *pvParameters )
{
	for( ;; )
	{
		vTaskDelay( 500 / portTICK_RATE_MS );	// 每500毫秒产生一个软件中断来”模拟”中断事件
		vPrintString("Periodic task - About to generate an interrupt.\r\n");
		__asm{ int 0x82 }		// 产生中断
		vPrintString("Periodic task - Interrupt generated.\r\n\r\n\r\n");
	}
}

// 延迟中断处理任务
static void vHandlerTask( void *pvParameters )
{
	for( ;; )
	{
		xSemaphoreTake( xCountingSemaphore, portMAX_DELAY );	// 无事件时阻塞
		vPrintString( "Handler task - Processing event.\r\n" );	// 事件已经发生
	}
}

// 中断服务例程
static void __interrupt __far vExampleInterruptHandler( void )
{
	static portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR(xCountingSemaphore, &xHigherPriorityTaskWoken);	// 使得延迟处理任务解除阻塞
	xSemaphoreGiveFromISR(xCountingSemaphore, &xHigherPriorityTaskWoken);	// 模拟处理器产生多个中断
	xSemaphoreGiveFromISR(xCountingSemaphore, &xHigherPriorityTaskWoken);
	if(xHigherPriorityTaskWoken == pdTRUE)
	{
		portSWITCH_CONTEXT();	// 强制进行一次任务切换，以确保中断直接返回到解除阻塞的任务(优选级更高)
	}
}

int main( void )
{
	xCountingSemaphore = xSemaphoreCreateCounting( 10, 0 );		// 创建计数信号量
	_dos_setvect( 0x82, vExampleInterruptHandler );	// 安装中断服务例程
	if(xCountingSemaphore != NULL)
	{
		xTaskCreate( vHandlerTask, "Handler", 1000, NULL, 3, NULL );	// 创建延迟中断处理任务, 使用较高优先级
		xTaskCreate( vPeriodicTask, "Periodic", 1000, NULL, 1, NULL );	// 创建一个任务用于周期性产生软件中断, 使用较低优先级
		vTaskStartScheduler();											// 启动调度器
	}
	for( ;; );
}
