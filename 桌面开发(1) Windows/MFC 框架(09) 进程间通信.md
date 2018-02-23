# 多任务

GetMessage 函数

1. 协同式多任务(强制性多任务)
2. 抢先式多任务(非强制性多任务)

# 核心对象

| kernel object | 产生方法           | 用途 |
| ------------- | ----------------- | --- |
| event         | CreateEvent       | 线程同步 |
| mutex         | CreateMutex       | 线程同步 |
| semaphore     | CreateSemaphore   | 线程同步 |
| file          | CreateFile        |  |
| file-mapping  | CreateFileMapping | 内存映射文件(memory mapping file) |
| process       | CreateProcess     |  |
| thread        | CreateThread      |  |

1. 系统使用计数值(usage count)对核心对象进行管理
2. 核心对象产生后都会获得一个 handle 作为识别
3. 使用 CloseHandle 结束核心对象
4. 线程是 CPU 的调度单位，用来执行程序代码
5. process 对象是一个数据结构，用来管理线程

# 进程与线程

1. 进程不执行任何代码, 是线程的容器(执行环境), 线程负责执行包含在进程的地址空间中的代码
2. 线程可以访问进程的内核对象的所有句柄, 进程中的所有内存, 同一进程中所有其他线程的堆栈

进程的组成

1. 内核对象: 操作系统用来管理进程的数据结构, 存放关于进程的统计信息的地方
2. 地址空间: 包含所有可执行模块, DLL 模块的代码和数据, 还包含动态内存分配的空间(线程堆栈和堆分配空间)

线程的组成

1. 内核对象: 操作系统用来管理线程的数据结构, 存放关于线程的统计信息的地方
2. 线程堆栈: 用于维护在指定代码时需要的所有参数和局部变量

虚拟内存

1. 内核方式分区: 供内核代码, 设备驱动程序, 设备I/O高速缓冲, 非页面内存池的分配, 进行页面表
2. 用户方式分区: 进程的私有地址空间

1. 页文件 pagefile.sys
2. 页面大小: 页面是系统管理内存的单位, x86的CPU的页面大小是4KB

# 线程优先级 Priority

1. 范围: 0(最低) - 31(最高)

优先级等级 Priority Class

| Class    | CreateProcess 函数       |  |
| -------- | ----------------------- | --- |
| idle     | IDLE_PRIORITY_CLASS     | 4 |
| normal   | NORMAL_PRIORITY_CLASS   | 9(前台)/7(后台)|
| high     | HIGH_PRIORITY_CLASS     | 13 |
| realtime | REALTIME_PRIORITY_CLASS | 24 |

相对优先级

| SetThreadPriority 函数参数     | 调整幅度 |
| ----------------------------- | --- |
| THREAD_PRIORITY_LOWEST        | -2 |
| THREAD_PRIORITY_BELOW_NORMAL  | -1 |
| THREAD_PRIORITY_NORMAL        | 不变 |
| THREAD_PRIORITY_ABOVE_NORMAL  | 1 |
| THREAD_PRIORITY_HIGHEST       | 2 |
| THREAD_PRIORITY_IDLE          | realtime 等级则指定为16, 否则为1 |
| THREAD_PRIORITY_TIME_CRITICAL | realtime 等级则指定为31, 否则为15 |

# 线程同步

互斥对象

1. 互斥对象(mutex)属于内核对象, 能确保线程拥有对单个资源的互斥访问权
2. 互斥对象包含一个使用数量, 一个线程ID(拥有该对象的线程), 一个计数器(该线程拥有互斥对象的次数)

1. 有信号状态(signaled state), 已通知状态
2. 非信号状态, 未通知状态

1. 谁加锁, 就得由谁释放
2. 多次获取, 就得多次释放
3. 线程终止时, 会自动释放

# 参考

Platform SDK: DLLs, Process, and Threads
