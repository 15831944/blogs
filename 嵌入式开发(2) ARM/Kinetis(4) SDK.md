# Kinetis SDK

# Task

OSA_TaskCreate		xTaskCreate
OSA_Start			vTaskStartScheduler
OSA_TimeDelay		vTaskDelay

# Event Group

函数

OSA_EventCreate		xEventGroupCreate		// 参数: 事件组句柄, 事件组清除模式
OSA_EventSet		xEventGroupSetBits
OSA_EventWait		xEventGroupWaitBits

宏

kEventAutoClear
kEventManualClear

# Semaphore

OSA_MutexCreate		xSemaphoreCreateMutex

# Queue

OSA_MsgQCreate		xQueueCreate
