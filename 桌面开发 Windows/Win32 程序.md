# Win32 平台程序基础

| Type        | entry   | format | 特点                                      |
| ----------- | ------- | ------ | ----------------------------------------- |
| DOS         | main    | mz     | 可以调用 C Runtime 函数, 不可调用 Windows API |
| Console     | main    | exe    | 可以调用 GUI 无关部分的 windows API 和 MFC    |
| SDK         | WinMain | exe    | windows API                               |
| MFC         |         | exe    | MFC                                       |

1. mz (Mark Zbikowski)
2. exe (Portable Executable)
3. DOS 以外都属于 Win32 程序，可以在 Windows 下的 DOS Box 或 IDE 中编译
4. dumpbin 工具可以观察 PE 格式文件

# Windows SDK 程序开发流程

| tool          | resource file  | file type |
| ------------- | -------------- | --------- |
| Dialog Editor | .dlg           | text      |
| Image Editor  | .bmp .ico .cur | binary    |
| Font Editor   | .fon           | binary    |

.rc 脚本文件用于描述上述资源文件

| 编译器/链接器 | 文件类型                     | 组成                    |
| ----------- | --------------------------- | ---------------------- |
| C Compiler  | .c, .h -> .obj              | 程序代码                |
| RC Compiler | .rc, .h -> .res             | UI(user Interface) 资源 |
| Linker      | .obj .res .def .lib -> .exe | 可执行程序               |

.def 模块定义文件记录模块名称, 程序段和数据段的内存特性, 堆和栈的大小, CALLBACK 函数名称等

# 函数库

## C Runtimes

| C Runtimes | 说明 |
| ---------- | ----- |
| LIBC.LIB   | 静态库 |
| MSVCRT.LIB | MSVCRT40.DLL 的 import 函数库 |

| version                                          | name        | VC++ 编译器选项 |
| ------------------------------------------------ | ----------- | ---- |
| Single-Threaded (static)                         | libc.lib    | -ML  |
| Multithreaded (static)                           | libcmt.lib  | -MT  |
| Multithreaded DLL (dynamic import library)       | msvcrt.lib  | -MD  |
| Debug Single-Threaded (static)                   | libcd.lib   | -MLd |
| Debug Multithreaded (static)                     | libcmtd.lib | -MTd |
| Debug Multithreaded DLL (dynamic import library) | msvcrtd.lib | -MDd |

## Windows API

动态链接函数库

.exe .dll .fon .mod .drv .ocx

import 函数库的作用

1. 在链接阶段，链接器需要先为调用者准备一些适当的信息，以使执行阶段顺利跳转到 DLL 中执行
2. 若该 API 所属函数库尚未加载，系统以此得知先加载该函数库

| Windows API  | import 函数库 |
| ------------ | ------------ |
| GDI32.DLL    | GDI32.LIB    |
| USER32.DLL   | USER32.LIB   |
| KERNER32.DLL | KERNEL32.LIB |
| COMMDLG.DLL  | COMDLG32.LIB |
| TOOLHELP.DLL | TH32.LIB     |

前3个为 windosw 三大模块，由 WINDOWS.H 提供

# 消息为基础, 事件驱动

1. 应用程序等待事件输入, 输入由操作系统捕捉, 以消息形式进入程序中
2. 用户模块(User Module)负责各个外围的驱动程序, User Module -> SendMessage() -> Window procedure
3. 程序调用 GetMessage API 取得一个消息，程序的生命靠其推动
4. 窗口负责接收并处理消息, 每个窗口使用一个 窗口过程函数(window procedure) 负责处理消息

输入的分类

| 消息来源         | 消息传递 |
| --------------- | ------- |
| 硬件装置         | mouse driver, keyboard driver -> system message queue |
| 系统或其他应用程序 | PostMessage() -> application message queue |

# Makefile

| 工具       | 说明       |
| --------- | --------- |
| nmake.exe | Microsoft |
| make.exe  | Borland   |

# 函数调用方式

参数进入堆栈的次序

处理堆栈的责任归属

| 调用习惯  |   |
| -------- | - |
| _stdcall |  |
| _pascall |  |
| _cdecl   |  |

# 程序执行

加载器 -> C Startup Code -> WinMain

# 多任务

GetMessage 函数

协同式多任务(强制性多任务)

抢先式多任务(非强制性多任务)

# 窗口函数

窗口函数是 CALLBACK 函数, 即要被系统调用, 因为程序不关心的消息要由操作系统默认处理

# 消息映射 Msssage Map

# 对话框的运行

1. modal 对话框: 令其父窗口无效，直到对话框结束
2. modeless 对话框: 父窗口与对话框共同运行

对话框模板(dialog templete)

对话框函数(dialog procedure)

# rc 文件描述的资源类型

| resource type | 说明 |
| ------------- | ---- |
| ICON          | 图标 |
| MENU          | 菜单 |
| DIALOGEX      | 对话框 |
| SURSOR        |  |
| BITMAP        |  |
| FONT          |      |
| ACCELERATORS  | 快捷键 |
| STRING        |  |
| VERSIONINFO   |  |
| TOOLBAR       |  |

# 进程与线程

## 核心对象 kernel object

| 核心对象      | 产生方法            | 用途 |
| ------------ | ----------------- | - |
| event        | CreateEvent       | 线程同步 |
| mutex        | CreateMutex       | 线程同步 |
| semaphore    | CreateSemaphore   | 线程同步 |
| file         | CreateFile        |  |
| file-mapping | CreateFileMapping | 内存映射文件(memory mapping file) |
| process      | CreateProcess     |  |
| thread       | CreateThread      |  |

1. 系统使用计数值(usage count)对核心对象进行管理
2. 核心对象产生后都会获得一个 handle 作为识别
3. 使用 CloseHandle 结束核心对象
4. 线程是 CPU 的调度单位，用来执行程序代码
5. process 对象是一个数据结构，用来管理线程

## 线程优先级 Priority

范围: 0(最低) - 31(最高)

### 优先级等级 Priority Class

| Class    | CreateProcess 函数       |  |
| -------- | ----------------------- | --- |
| idle     | IDLE_PRIORITY_CLASS     | 4 |
| normal   | NORMAL_PRIORITY_CLASS   | 9(前台)/7(后台)|
| high     | HIGH_PRIORITY_CLASS     | 13 |
| realtime | REALTIME_PRIORITY_CLASS | 24 |

### 相对优先级

| SetThreadPriority 函数参数     | 调整幅度 |
| ----------------------------- | --- |
| THREAD_PRIORITY_LOWEST        | -2 |
| THREAD_PRIORITY_BELOW_NORMAL  | -1 |
| THREAD_PRIORITY_NORMAL        | 不变 |
| THREAD_PRIORITY_ABOVE_NORMAL  | 1 |
| THREAD_PRIORITY_HIGHEST       | 2 |
| THREAD_PRIORITY_IDLE          | realtime 等级则指定为16, 否则为1 |
| THREAD_PRIORITY_TIME_CRITICAL | realtime 等级则指定为31, 否则为15 |



# 应用程序框架 Application Framework

1. MFC, Microsoft Foundation Class
2. OWL, ObjectWindow Library
3. ATL
4. WPF

# DC (Device context)

1. 设备描述表或设备上下文, 相当于画布, 绘图环境, 要在哪里绘图, 包括: 显示器, 打印机, 存储器, 数据的索引等

# GDI 对象 (Graphics Device Interface)

1. GDI 是图形设备接口, 它的主要任务是负责系统与绘图程序之间的信息交换, 处理所有 Windows 程序的图形输出
2. 不允许程序直接访问物理显示硬件(显示器, 打印机等), 通过获得与特定窗口相关联设备环境的抽象接口间接访问显示硬件, 用户无需关心具体的物理设备类型, Windows 参考设备环境的数据结构完成数据的输出

有6种 GDI 对象可以用于 DC:

1. Region  区域(画布)
2. Pen     画笔
3. Palette 调色板(颜料盒)
4. Font    字体
5. Brush   刷子(用来刷大面积背景色的粗画笔)
6. Bitmap  位图

接口

1. SelectOBject 函数, 选择或更换画笔对象
2. GetStockObject 函数, 获取系统提供的缺省画笔
3. DeleteObject 函数, 清理画笔

# 文件句柄 file handle

1. 虚拟内存: 应用程序启动后, 组成这个程序的各对象是住留在内存的, Windows 是一个以虚拟内存为基础的操作系统, 内存管理器经常在内存中来回移动对象, 来满足各种应用程序的内存需要, 对象被移动意味着它的地址会发生变化
2. 句柄地址: Windows 为各应用程序腾出一些固定的内存储地址，专门用来登记各应用对象在内存中的地址变化, 保存对象被移动后的新地址, 通过这个句柄地址间接地知道对象具体在内存中的哪个位置
3. 内存分配: 对象的地址是在对象装载(Load)时由系统分配的, 当系统卸载时(Unload)又释放给系统
4. 描述符: 有一块内存区域保存了最终数据，而为了对这个数据进行操作，我们需要针对其构造一个描述结构体，这个结构体称为描述符
5. 文件句柄: windows 下的概念, 是指向具体对象(或数据块)的描述符的指针, 一个句柄就是你给一个文件, 设备, 管套(socket)或管道的一个名字, 以便帮助你记住你正处理的名字, 并隐藏缓存的复杂性, 其本质是一个指向指针的指针
6. 句柄是 HANDLE 类型, 例如, 创建文件 CreateFile 会返回一个 HANDLE 型的值
7. 句柄是一个系统内部数据结构的引用, 例如, 当你操作一个窗口(Delphi 窗体)时, 系统会返回一个该窗口的句柄, 系统会通知你: 你正在操作142号窗口, 应用程序就能要求系统对该窗口进行操作(移动, 改变大小, 最小化等)
8. 句柄是一种内部代码, 通过它能引用受系统控制的特殊元素(窗口, 位图, 图标, 内存块, 光标, 字体, 菜单等等)
9. Windows API 给这些项目分配确定的句柄，并将句柄返回给应用程序，然后通过句柄来进行操作, 而不是用物理地址来标识一个内存块，文件，任务或动态装入模块, 许多 Windows API 函数把句柄作为第一个参数(GDI 句柄, 菜单句柄, 实例句柄, 位图句柄等等)

# MFC 的工具

1. Visual C++
2. AppWizard 用来生成初步的框架文件(代码和资源等)
3. ClassWizard 用来协助添加代码到框架文件
4. Resource Editor 用于帮助直观地设计用户接口

# 项目文件

1. 工作区文件(.dsw, developer studio workspace)用来存放与该工作区相关的信息
2. 工程文件(.dsp, developer studio project)
3. 选择信息文件(.opt)

# MFC 的封装

MFC 框架(类库)是 C++ 类库

1. 对 Win32 应用程序编程接口的封装, 用一个 C++ Object 来包装一个 Windows Object, 例如: class CWnd 是一个 C++ window object, 它把 Windows window (HWND) 及相关 API 函数封装在 C++ window object 的成员函数内, C++ window object 的成员变量 m_hWnd 就是 Windows window 的窗口句柄
2. 对应用程序概念的封装, 使用 SDK 编写 Windows 应用程序时, 总要定义窗口过程, 登记 Windows Class, 创建窗口等等. MFC 把许多类似的处理封装起来, 替程序员完成这些工作. MFC 提出了以"文档-视图"为中心的编程模式, MFC 类库封装了对该编程模式的支持. 文档是用户操作的数据对象, 视图是数据操作的窗口, 用户通过视图处理和查看数据
3. 对 COM/OLE 特性的封装, OLE 建立在 COM 模型之上, 由于支持 OLE 的应用程序必须实现一系列的接口, 因而相当繁琐, MFC 的 OLE 类封装了 OLE API 大量复杂的工作, 这些类提供了实现 OLE 更高级的接口
4. 对 ODBC 功能的封装, 提供 ODBC 的更高级接口的 C++ 类, 封装了 ODBC API 大量复杂的工作, 提供了一种数据库编程模式

# 单文档界面(SingleDocumentInterface)

# 参考

书籍

1. 深入浅出.MFC

教程

1. 闻怡洋 Visual C++ 6.0 MFC 入门教程

博客

1. [文件描述符，文件句柄的区别？](http://bbs.csdn.net/topics/230035323)
2. [文件句柄是什么意思](http://zhidao.baidu.com/question/35001537.html)
