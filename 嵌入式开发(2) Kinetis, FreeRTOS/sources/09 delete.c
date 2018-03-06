

void vTask1( void *pvParameters )
{
	const portTickType xDelay100ms = 100 / portTICK_RATE_MS;
	for( ;; )
	{
		vPrintString( "Task1 is running\r\n" );
		xTaskCreate( vTask2, "Task 2", 1000, NULL, 2, &xTask2Handle );
		vTaskDelay( xDelay100ms );
	}
}

void vTask2( void *pvParameters )
{
	vPrintString( "Task2 is running and about to delete itself\r\n" );
	vTaskDelete( xTask2Handle );
}


int main( void )
{
	xTaskCreate( vTask1, "Task 1", 1000, NULL, 1, NULL );
	vTaskStartScheduler();
	for( ;; );
}
