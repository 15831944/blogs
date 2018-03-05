// Example 24. Using a task notification in place of a semaphore, method 1

/* The rate at which the periodic task generates software interrupts. */
const TickType_t xInterruptFrequency = pdMS_TO_TICKS( 500UL );
static void vHandlerTask( void *pvParameters )
{
	/* xMaxExpectedBlockTime is set to be a little longer than the maximum expected time
	between events. */
	const TickType_t xMaxExpectedBlockTime = xInterruptFrequency + pdMS_TO_TICKS( 10 );
	uint32_t ulEventsToProcess;
	/* As per most tasks, this task is implemented within an infinite loop. */
	for( ;; )
	{
		/* Wait to receive a notification sent directly to this task from the
		interrupt service routine. */
		ulEventsToProcess = ulTaskNotifyTake( pdTRUE, xMaxExpectedBlockTime );
		if( ulEventsToProcess != 0 )
		{
			/* To get here at least one event must have occurred. Loop here until
			all the pending events have been processed (in this case, just print out
			a message for each event). */
			while( ulEventsToProcess > 0 )
			{
				vPrintString( "Handler task - Processing event.\r\n" );
				ulEventsToProcess--;
			}
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
	/* The xHigherPriorityTaskWoken parameter must be initialized to pdFALSE as
	it will get set to pdTRUE inside the interrupt safe API function if a
	context switch is required. */
	xHigherPriorityTaskWoken = pdFALSE;
	/* Send a notification directly to the task to which interrupt processing is
	being deferred. */
	vTaskNotifyGiveFromISR( /* The handle of the task to which the notification
	is being sent. The handle was saved when the task
	was created. */
	xHandlerTask,
	/* xHigherPriorityTaskWoken is used in the usual
	way. */
	&xHigherPriorityTaskWoken );
	/* Pass the xHigherPriorityTaskWoken value into portYIELD_FROM_ISR(). If
	xHigherPriorityTaskWoken was set to pdTRUE inside vTaskNotifyGiveFromISR()
	then calling portYIELD_FROM_ISR() will request a context switch. If
	xHigherPriorityTaskWoken is still pdFALSE then calling
	portYIELD_FROM_ISR() will have no effect. The implementation of
	portYIELD_FROM_ISR() used by the Windows port includes a return statement,
	which is why this function does not explicitly return a value. */
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
