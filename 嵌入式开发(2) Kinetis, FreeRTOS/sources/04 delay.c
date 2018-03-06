void vTaskFunction( void *pvParameters )
{
	char *pcTaskName;


	pcTaskName = ( char * ) pvParameters;

	for( ;; )
	{
		vPrintString( pcTaskName );
		vTaskDelay( 250 / portTICK_RATE_MS );	// 定时事件
	}
}




static const char *pcTextForTask1 = “Task 1 is running\r\n”;
static const char *pcTextForTask2 = “Task 2 is running\t\n”;

int main( void )
{
	xTaskCreate( vTaskFunction, "Task 1", 1000, (void*)pcTextForTask1, 1, NULL );
	xTaskCreate( vTaskFunction, "Task 2", 1000, (void*)pcTextForTask2, 2, NULL );
	vTaskStartScheduler();
	return 0;
}
