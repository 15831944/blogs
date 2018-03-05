// ����1�����ȼ�����, ����2������1��1, Ȼ���1, �ٵ�1, �������

xTaskHandle xTask2Handle;

void vTask1( void *pvParameters )
{
	unsigned portBASE_TYPE uxPriority;
	uxPriority = uxTaskPriorityGet( NULL );
	for( ;; )
	{
		vPrintString( "Task1 is running\r\n" );
		vPrintString( "About to raise the Task2 priority\r\n" );
		vTaskPrioritySet( xTask2Handle, ( uxPriority + 1 ) );
	}
}

void vTask2( void *pvParameters )
{
	unsigned portBASE_TYPE uxPriority;
	uxPriority = uxTaskPriorityGet( NULL );
	for( ;; )
	{
		vPrintString( "Task2 is running\r\n" );
		vPrintString( "About to lower the Task2 priority\r\n" );
		vTaskPrioritySet( NULL, ( uxPriority - 2 ) );
	}
}

int main( void )
{
	xTaskCreate( vTask1, "Task 1", 1000, NULL, 2, NULL );
	xTaskCreate( vTask2, "Task 2", 1000, NULL, 1, &xTask2Handle );
	vTaskStartScheduler();
	for( ;; );
}
