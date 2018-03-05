// Example 14. Using the callback function parameter and the software timer ID

#define mainONE_SHOT_TIMER_PERIOD		pdMS_TO_TICKS( 3333 )
#define mainAUTO_RELOAD_TIMER_PERIOD	pdMS_TO_TICKS( 500 )

int ulCallCount;

int main( void )
{
	TimerHandle_t	xAutoReloadTimer, xOneShotTimer;
	BaseType_t		xTimer1Started, xTimer2Started;

	xOneShotTimer = xTimerCreate("OneShot", mainONE_SHOT_TIMER_PERIOD, pdFALSE, 0, prvTimerCallback);
	xAutoReloadTimer = xTimerCreate("AutoReload", mainAUTO_RELOAD_TIMER_PERIOD, pdTRUE, 0, prvTimerCallback);

	if( ( xOneShotTimer != NULL ) && ( xAutoReloadTimer != NULL ) )
	{
		xTimer1Started = xTimerStart(xOneShotTimer, 0);
		xTimer2Started = xTimerStart(xAutoReloadTimer, 0);
		if( ( xTimer1Started == pdPASS ) && ( xTimer2Started == pdPASS ) )
		{
			vTaskStartScheduler();
		}
	}
	for( ;; );
}

static void prvTimerCallback( TimerHandle_t xTimer )
{
	TickType_t	xTimeNow;
	uint32_t	ulExecutionCount;

	ulExecutionCount = ( uint32_t ) pvTimerGetTimerID( xTimer );
	ulExecutionCount++;
	vTimerSetTimerID( xTimer, ( void * ) ulExecutionCount );

	xTimeNow = xTaskGetTickCount();

	if( xTimer == xOneShotTimer )
	{
		vPrintStringAndNumber( "One-shot timer callback executing", xTimeNow );
	}
	else
	{
		vPrintStringAndNumber( "Auto-reload timer callback executing", xTimeNow );
		if( ulExecutionCount == 5 )
		{
			xTimerStop( xTimer, 0 );
		}
	}
}



#if 0

// Listing 83. Using xTimerChangePeriod()

const TickType_t xHealthyTimerPeriod = pdMS_TO_TICKS( 3000 );
const TickType_t xErrorTimerPeriod   = pdMS_TO_TICKS( 200 );

static void prvCheckTimerCallbackFunction( TimerHandle_t xTimer )
{
	static BaseType_t xErrorDetected = pdFALSE;

	if( xErrorDetected == pdFALSE )
	{
		if( CheckTasksAreRunningWithoutError() == pdFAIL )
		{
			xTimerChangePeriod( xTimer, xErrorTimerPeriod, 0 );
		}
		xErrorDetected = pdTRUE;
	}
	ToggleLED();
}

#endif
