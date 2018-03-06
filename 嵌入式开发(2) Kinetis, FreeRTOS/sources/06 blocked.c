// 持续处理任务
void vContinuousProcessingTask( void *pvParameters )
{
	char *pcTaskName;
	pcTaskName = ( char * ) pvParameters;
	for( ;; )
	{
		vPrintString( pcTaskName );
	}
}

// 周期任务
void vPeriodicTask( void *pvParameters )
{
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	for( ;; )
	{
		vPrintString( "Periodic task is running\r\n" );
		vTaskDelayUntil( &xLastWakeTime, ( 10 / portTICK_RATE_MS ) );
	}
}
