// Example 25. Using a task notification in place of a semaphore, method 2

static void vHandlerTask( void *pvParameters )
{
	/* xMaxExpectedBlockTime is set to be a little longer than the maximum expected time
	between events. */
	const TickType_t xMaxExpectedBlockTime = xInterruptFrequency + pdMS_TO_TICKS( 10 );
	/* As per most tasks, this task is implemented within an infinite loop. */
	for( ;; )
	{
		/* Wait to receive a notification sent directly to this task from the
		interrupt service routine. The xClearCountOnExit parameter is now pdFALSE,
		so the task's notification value will be decremented by ulTaskNotifyTake(),
		and not cleared to zero. */
		if( ulTaskNotifyTake( pdFALSE, xMaxExpectedBlockTime ) != 0 )
		{
			/* To get here an event must have occurred. Process the event (in this
			case just print out a message). */
			vPrintString( "Handler task - Processing event.\r\n" );
		}
		else
		{
			/* If this part of the function is reached then an interrupt did not
			arrive within the expected time, and (in a real application) it may be
			necessary to perform some error recovery operations. */
		}
	}
}

static uint32_t ulExampleInterruptHandler( void )
{
	BaseType_t xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	/* Send a notification to the handler task multiple times. The first ‘give’ will
	unblock the task, the following 'gives' are to demonstrate that the receiving
	task's notification value is being used to count (latch) events - allowing the
	task to process each event in turn. */
	vTaskNotifyGiveFromISR( xHandlerTask, &xHigherPriorityTaskWoken );
	vTaskNotifyGiveFromISR( xHandlerTask, &xHigherPriorityTaskWoken );
	vTaskNotifyGiveFromISR( xHandlerTask, &xHigherPriorityTaskWoken );
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
