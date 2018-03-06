
// 任务函数, 返回void, 参数void*, 实现为死循环, 不return
void vTask1(void *pvParameters)
{
	const char *pcTaskName = "Task 1 is running\r\n";
	volatile unsigned long ul;

	for( ;; )
	{
		vPrintString( pcTaskName );
		for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
		{
			;
		}
	}
}

void vTask2( void *pvParameters )
{
	const char *pcTaskName = "Task 2 is running\r\n";
	volatile unsigned long ul;

	for( ;; )
	{
		vPrintString( pcTaskName );
		for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
		{
			;
		}
	}
}

int main( void )
{
	xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, NULL);
	xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, NULL);
	vTaskStartScheduler();
	for( ;; );
}
