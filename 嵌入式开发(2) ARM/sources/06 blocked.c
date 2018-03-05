// ������������
void vContinuousProcessingTask( void *pvParameters )
{
	char *pcTaskName;
	pcTaskName = ( char * ) pvParameters;
	for( ;; )
	{
		vPrintString( pcTaskName );
	}
}

// ��������
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
