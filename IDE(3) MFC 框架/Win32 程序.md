# 1. Win32基本程序概念

| 种类 | 程序入口 | 格式 | 特点 |
| - | - | - | - |
| DOS 程序 | main| mz | 可以调用 C Runtime 函数, 不可调用 Windows API |
| Console 程序 | main | exe | 可以调用 GUI 无关部分的 windows API 和 MFC |
| SDK 程序 | WinMain | exe |windows API |
| MFC 程序 |  | exe | MFC |

mz (Mark Zbikowski)

exe (Portable Executable)

DOS 以外都属于 Win32 程序，可以在 Windows 下的 DOS Box 或 IDE 中编译

dumpbin 工具可以观察 PE 格式文件

# 2. windows SDK 程序开发流程

| 工具 | 资源文件 | 文件类型 |
| ------------- | -------------- | ------ |
| Dialog Editor | .dlg           | 文本文件 |
| Image Editor  | .bmp .ico .cur | 二进制文件 |
| Font Editor   | .fon           | 二进制文件 |

.rc 脚本文件用于描述上述资源文件

| 编译器/链接器 | 文件类型 | 组成 |
| ----------- | --------------- | -------|
| C Compiler  | .c, .h -> .obj  | 程序代码 |
| RC Compiler | .rc, .h -> .res | UI(user Interface) 资源 |
| Linker      | .obj .res .def .lib -> .exe | 可执行程序 |

.def 模块定义文件记录模块名称, 程序段和数据段的内存特性, 堆和栈的大小, CALLBACK 函数名称等

# 3. 函数库

## 1. C Runtimes

| C Runtimes | 说明 |
| ---------- | ----- |
| LIBC.LIB   | 静态库 |
| MSVCRT.LIB | MSVCRT40.DLL 的 import 函数库 |

| 版本 | 名称 | VC++ 编译器选项 |
| ----------------------------------------------- | ----------- | - |
| Single-Threaded(static)                         | libc.lib    | -ML |
| Multithreaded(static)                           | libcmt.lib  | -MT |
| Multithreaded DLL(dynamic import library)       | msvcrt.lib  | -MD |
| Debug Single-Threaded(static)                   | libcd.lib   | -MLd |
| Debug Multithreaded(static)                     | libcmtd.lib | -MTd |
| Debug Multithreaded DLL(dynamic import library) | msvcrtd.lib | -MDd |

## 2. Windows API

动态链接函数库

.exe .dll .fon .mod .drv .ocx

import 函数库的作用

1. 在链接阶段，链接器需要先为调用者准备一些适当的信息，以使执行阶段顺利跳转到 DLL 中执行

2. 若该 API 所属函数库尚未加载，系统以此得知先加载该函数库

| Windows API  | import 函数库 |
| ------------ | --------- |
| GDI32.DLL    | GDI32.LIB |
| USER32.DLL   | USER32.LIB |
| KERNER32.DLL | KERNEL32.LIB |
| COMMDLG.DLL  | COMDLG32.LIB |
| TOOLHELP.DLL | TH32.LIB |

# 4. 头文件

前3个为 windosw 三大模块，由 WINDOWS.H 提供

# 5. 消息为基础，事件驱动

应用程序等待事件输入，输入由操作系统捕捉，以消息形式进入程序中

USER 模块负责各个外围的驱动程序

## "输入"的分类

| 消息来源 | 消息传递 |
| ------- | ------- |
| 硬件装置 | mouse driver, keyboard driver -> system message queue |
| 系统或其他应用程序 | PostMessage() -> application message queue |

User Module -> SendMessage() -> Window procedure

程序调用 GetMessage API 取得一个消息，程序的生命靠其推动

窗口负责接收并处理消息

每个窗口使用一个 窗口函数(window procedure) 负责处理消息

# 6. Makefile

| 工具 | 说明 |
| - | - |
| nmake.exe | Microsoft |
| make.exe  | Borland |

# 7. 函数调用方式

参数进入堆栈的次序

处理堆栈的责任归属

| 调用习惯 |  |
| - | - |
| _stdcall |  |
| _pascall |  |
| _cdecl   |  |

# 8. 程序执行

加载器 -> C Startup Code -> WinMain

# 9. 多任务

GetMessage 函数

协同式多任务(强制性多任务)

抢先式多任务(非强制性多任务)

# 10. 窗口函数

窗口函数是 CALLBACK 函数，即要被系统调用，因为程序不关心的消息要由操作系统默认处理

# 11. 消息映射 Msssage Map

# 12. 对话框的运行

## 类型

modal 对话框： 令其父窗口无效，直到对话框结束

modeless 对话框: 父窗口与对话框共同运行

##对话框的运行

对话框模板(dialog templete)

对话框函数(dialog procedure)

# 13. rc文件描述的资源类型

| 资源类型 | 说明 |
| ------------ | ---- |
| ICON         | 图标 |
| MENU         | 菜单 |
| DIALOGEX     | 对话框 |
| SURSOR       |  |
| BITMAP       |  |
| FONT         |      |
| ACCELERATORS | 快捷键 |
| STRING       |  |
| VERSIONINFO  |  |
| TOOLBAR      |  |

# 14. 进程与线程

## 核心对象 kernel object

| 核心对象 | 产生方法 | 用途 |
| ------------ | ----------------- | - |
| event        | CreateEvent       | 线程同步 |
| mutex        | CreateMutex       | 线程同步 |
| semaphore    | CreateSemaphore   | 线程同步 |
| file         | CreateFile        |  |
| file-mapping | CreateFileMapping | 内存映射文件(memory mapping file) |
| process      | CreateProcess     |  |
| thread       | CreateThread      |  |

系统使用计数值(usage count)对核心对象进行管理

核心对象产生后都会获得一个 handle 作为识别

使用 CloseHandle 结束核心对象

线程是CPU的调度单位，用来执行程序代码

process 对象是一个数据结构，用来管理线程

## 线程优先级 Priority

范围: 0(最低) - 31(最高)

### 优先级等级 Priority Class

| Class | CreateProcess 函数 |  |
| -------- | ----------------------- | - |
| idle     | IDLE_PRIORITY_CLASS     | 4 |
| normal   | NORMAL_PRIORITY_CLASS   | 9(前台)/7(后台)|
| high     | HIGH_PRIORITY_CLASS     | 13 |
| realtime | REALTIME_PRIORITY_CLASS | 24 |

### 相对优先级

| SetThreadPriority 函数参数 | 调整幅度 |
| ----------------------------- | - |
| THREAD_PRIORITY_LOWEST        | -2 |
| THREAD_PRIORITY_BELOW_NORMAL  | -1 |
| THREAD_PRIORITY_NORMAL        | 不变 |
| THREAD_PRIORITY_ABOVE_NORMAL  | 1 |
| THREAD_PRIORITY_HIGHEST       | 2 |
| THREAD_PRIORITY_IDLE          | realtime 等级则指定为16, 否则为1 |
| THREAD_PRIORITY_TIME_CRITICAL | realtime 等级则指定为31, 否则为15 |

# 参考

深入浅出.MFC
