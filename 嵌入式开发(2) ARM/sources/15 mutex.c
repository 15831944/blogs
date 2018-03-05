int main( void )
{
	xMutex = xSemaphoreCreateMutex();	// 创建了一个互斥量类型的信号量
	srand( 567 );						// 给随机数发生器生成种子, 用于随机延迟时间
	if( xMutex != NULL )
	{
		xTaskCreate(prvPrintTask, "Print1", 1000, "Task 1 ******************************************\r\n", 1, NULL);
		xTaskCreate(prvPrintTask, "Print2", 1000, "Task 2 ------------------------------------------\r\n", 2, NULL);
		vTaskStartScheduler();
	}
	for( ;; );
}
