# Component Development Environment (CDE)

1. main 函数调用处理器的初始化

```
Generated_Code\PE_low_level_init.h
Static_Code\System\PE_low_level_init.c
void PE_low_level_init(void)			// 硬件初始化, 操作系统初始化, 组件初始化
void PEX_components_init(void)
```

1. 所有任务主任务和其他任务都是在 Generated_Code 文件夹中创建, 在 Sources 文件夹中实现
2. main 函数调用操作系统, 操作系统模块调用主任务, 主任务再调用其他任务





# MODULE free_rtos

操作系统模块

```
Generated_Code\osa1.h
#define PEX_RTOS_INIT	OSA_Init
#define PEX_RTOS_START	OSA_Start

Generated_Code\free_rtos.h
#define PEX_RTOS_START()  {MainTask_Init(); OSA_Start();}	// 使用 free_rtos 控件后重新定义此宏
#define PEX_USE_RTOS
```





# MODULE MainTask

主任务创建模块

```
Generated_Code\MainTask.h
osa_status_t MainTask_Init(void)
```

# MODULE RFCommunication

第二个任务创建模块

# MODULE RTCConfig

第三个任务创建模块

# MODULE TimingConfig

第四个任务创建模块

# MODULE Task1

第五个任务创建模块

# MODULE Task3

第六个任务创建模块

查找 OSA_TaskCreate 函数看看项目中一个有多少个任务





# MODULE rtos_main_task

主任务实现, 创建所有的 事件组, 信号量, 队列, 任务

```
Sources\rtos_main_task.h
void main_task(os_task_param_t task_init_data)
```

# MODULE os_tasks

其他任务实现

定义所有的 事件组, 信号量, 队列

```
Sources\os_tasks.h
```
