Example 15. Resetting a software timer

// 软件定时器回调函数, 关闭背光灯
static void prvBacklightTimerCallback( TimerHandle_t xTimer )
{
	TickType_t xTimeNow = xTaskGetTickCount();
	xSimulatedBacklightOn = pdFALSE;
	vPrintStringAndNumber("Timer expired, turning backlight OFF at time\t\t", xTimeNow);
}

// 按键轮询任务
static void vKeyHitTask( void *pvParameters )
{
	const TickType_t xShortDelay = pdMS_TO_TICKS( 50 );
	TickType_t xTimeNow;
	vPrintString( "Press a key to turn the backlight on.\r\n" );

	for( ;; )
	{
		if( _kbhit() != 0 )
		{
			xTimeNow = xTaskGetTickCount();
			if( xSimulatedBacklightOn == pdFALSE )
			{
				xSimulatedBacklightOn = pdTRUE;
				vPrintStringAndNumber("Key pressed, turning backlight ON at time\t\t", xTimeNow );
			}
			else
			{
				vPrintStringAndNumber("Key pressed, resetting software timer at time\t\t", xTimeNow );
			}
			xTimerReset( xBacklightTimer, xShortDelay );
			( void ) _getch();
		}
	}
}
