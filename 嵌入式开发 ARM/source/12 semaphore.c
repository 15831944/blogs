// 例12

// 周期性任务, 用于每隔 500 毫秒产生一个软件中断
static void vPeriodicTask( void *pvParameters )
{
	for( ;; )
	{
		/* 此任务通过每500毫秒产生一个软件中断来”模拟”中断事件 */
		vTaskDelay( 500 / portTICK_RATE_MS );
		/* 产生中断，并在产生之前和之后输出信息，以便在执行结果中直观直出执行流程 */
		vPrintString( "Periodic task - About to generate an interrupt.\r\n" );
		__asm{ int 0x82 } /* 这条语句产生中断 */
		vPrintString( "Periodic task - Interrupt generated.\r\n\r\n\r\n" );
	}
}

// 延迟处理任务, 通过使用二值信号量与软件中断进行同步
static void vHandlerTask( void *pvParameters )
{
	/* As per most tasks, this task is implemented within an infinite loop. */
	for( ;; )
	{
		/* 使用信号量等待一个事件。信号量在调度器启动之前，也即此任务执行之前就已被创建。任务被无超
		时阻塞，所以此函数调用也只会在成功获取信号量之后才会返回。此处也没有必要检测返回值 */
		xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );
		/* 程序运行到这里时，事件必然已经发生。本例的事件处理只是简单地打印输出一个信息 */
		vPrintString( "Handler task - Processing event.\r\n" );
	}
}

// 中断服务例程
static void __interrupt __far vExampleInterruptHandler( void )
{
	static portBASE_TYPE xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	/* 'Give' the semaphore to unblock the task. */
	xSemaphoreGiveFromISR( xBinarySemaphore, &xHigherPriorityTaskWoken );
	if( xHigherPriorityTaskWoken == pdTRUE )
	{
		/* 给出信号量以使得等待此信号量的任务解除阻塞。如果解出阻塞的任务的优先级高于当前任务的优先
		级 – 强制进行一次任务切换，以确保中断直接返回到解出阻塞的任务(优选级更高)。
		说明：在实际使用中，ISR中强制上下文切换的宏依赖于具体移植。此处调用的是基于Open Watcom DOS
		移植的宏。其它平台下的移植可能有不同的语法要求。对于实际使用的平台，请参如数对应移植自带的示
		例程序，以决定正确的语法和符号。
		*/
		portSWITCH_CONTEXT();
	}
}

// 创建二值信号量及任务，安装中断服务例程，然后启动调度器。
int main( void )
{
	/* 信号量在使用前都必须先创建。本例中创建了一个二值信号量 */
	vSemaphoreCreateBinary( xBinarySemaphore );
	/* 安装中断服务例程 */
	_dos_setvect( 0x82, vExampleInterruptHandler );
	/* 检查信号量是否成功创建 */
	if( xBinarySemaphore != NULL )
	{
		/* 创建延迟处理任务。此任务将与中断同步。延迟处理任务在创建时使用了一个较高的优先级，以保证
		中断退出后会被立即执行。在本例中，为延迟处理任务赋予优先级3 */
		xTaskCreate( vHandlerTask, "Handler", 1000, NULL, 3, NULL );
		/* 创建一个任务用于周期性产生软件中断。此任务的优先级低于延迟处理任务。每当延迟处理任务切出
		阻塞态，就会抢占周期任务*/
		xTaskCreate( vPeriodicTask, "Periodic", 1000, NULL, 1, NULL );
		/* Start the scheduler so the created tasks start executing. */
		vTaskStartScheduler();
	}
	/* 如果一切正常，main()函数不会执行到这里，因为调度器已经开始运行任务。但如果程序运行到了这里，
	很可能是由于系统内存不足而无法创建空闲任务。第五章会提供更多关于内存管理的信息 */
	for( ;; );
}
