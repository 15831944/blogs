// Example 22. Experimenting with event groups
// 注意函数名的的前缀 v 和 ul 隐含了函数的返回值类型

/* Definitions for the event bits in the event group. */
#define mainFIRST_TASK_BIT ( 1UL << 0UL )
#define mainSECOND_TASK_BIT ( 1UL << 1UL )
#define mainISR_BIT ( 1UL << 2UL )

// 任务函数, 定时事件, 置位事件组中的 bit0 和 bit1
static void vEventBitSettingTask( void *pvParameters )
{
	const TickType_t xDelay200ms = pdMS_TO_TICKS( 200UL ), xDontBlock = 0;
	for( ;; )
	{
		vTaskDelay( xDelay200ms );
		vPrintString( "Bit setting task -\t about to set bit 0.\r\n" );
		xEventGroupSetBits( xEventGroup, mainFIRST_TASK_BIT );

		vTaskDelay( xDelay200ms );
		vPrintString( "Bit setting task -\t about to set bit 1.\r\n" );
		xEventGroupSetBits( xEventGroup, mainSECOND_TASK_BIT );
	}
}

// 中断服务例程, 每500ms, 置位事件组中的 bit2
static uint32_t ulEventBitSettingISR( void )
{
	static const char *pcString = "Bit setting ISR -\t about to set bit 2.\r\n";
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	xTimerPendFunctionCallFromISR(vPrintStringFromDaemonTask, (void *)pcString, 0, &xHigherPriorityTaskWoken);	// 发送到  RTOS daemon task 执行打印输出
	xEventGroupSetBitsFromISR(xEventGroup, mainISR_BIT, &xHigherPriorityTaskWoken);		// 写入 timer command queue
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);		// 上下文切换
}

// 任务函数, 读取并在解锁条件满足时自动清除事件组
// 等待三个任务中的事件至少一个发生或全部发生后离开阻塞状态
static void vEventBitReadingTask( void *pvParameters )
{
	EventBits_t xEventGroupValue;
	const EventBits_t xBitsToWaitFor = ( mainFIRST_TASK_BIT | mainSECOND_TASK_BIT | mainISR_BIT );
	for( ;; )
	{
		xEventGroupValue = xEventGroupWaitBits(xEventGroup, xBitsToWaitFor, pdTRUE, pdFALSE/*pdTRUE*/, portMAX_DELAY );	// 阻塞等待事件组中的事件发生
		if ((xEventGroupValue & mainFIRST_TASK_BIT) != 0)
		{
			vPrintString( "Bit reading task -\t Event bit 0 was set\r\n" );
		}
		if ((xEventGroupValue & mainSECOND_TASK_BIT) != 0)
		{
			vPrintString( "Bit reading task -\t Event bit 1 was set\r\n" );
		}
		if ((xEventGroupValue & mainISR_BIT) != 0)
		{
			vPrintString( "Bit reading task -\t Event bit 2 was set\r\n" );
		}
	}
}

int main( void )
{
	xEventGroup = xEventGroupCreate();
	xTaskCreate(vEventBitSettingTask, "Bit Setter", 1000, NULL, 1, NULL);
	xTaskCreate(vEventBitReadingTask, "Bit Reader", 1000, NULL, 2, NULL);	// the reading task will pre-empt the writing task each time the reading task’s unblock condition is met.
	xTaskCreate(vInterruptGenerator, "Int Gen", 1000, NULL, 3, NULL);		// 用于产生软件中断
	vPortSetInterruptHandler(mainINTERRUPT_NUMBER, ulEventBitSettingISR);	// 安装中断服务例程
	vTaskStartScheduler();
	for( ;; );
	return 0;
}
