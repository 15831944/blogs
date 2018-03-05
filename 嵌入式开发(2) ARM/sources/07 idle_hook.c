/* Declare a variable that will be incremented by the hook function. */
unsigned long ulIdleCycleCount = 0UL;
/* 空闲钩子函数必须命名为vApplicationIdleHook(),无参数也无返回值。 */
void vApplicationIdleHook( void )
{
	/* This hook function does nothing but increment a counter. */
	ulIdleCycleCount++;
}

void vTaskFunction( void *pvParameters )
{
	char *pcTaskName;
	pcTaskName = ( char * ) pvParameters;
	for( ;; )
	{
		vPrintStringAndNumber( pcTaskName, ulIdleCycleCount );
		vTaskDelay( 250 / portTICK_RATE_MS );
	}
}
