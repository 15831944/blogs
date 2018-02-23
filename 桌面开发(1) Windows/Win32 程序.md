# 应用程序框架 Application Framework

1. C Runtimes 函数库
2. Windows API, 开发 SDK 程序, 实现为 C 函数, 需要包含 Windows.h 头文件

1. MFC, Microsoft Foundation Class, 开发 MFC 程序, 实现为 C++ 类库和以 afx 开头的全局 C 函数
2. OWL, Object Window Library, C++
3. ATL, Active Template Library, C++
4. WPF, Windows Presentation Foundation, C#, 属于 .NET Framework 3.0

1. SDK 的 C 函数的第一个参数往往是句柄, 在 MFC 中则变成调用方法的对象

# Win32 平台程序基础

| Type        | entry   | format | 特点                                      |
| ----------- | ------- | ------ | ----------------------------------------- |
| DOS         | main    | mz     | 可以调用 C Runtime 函数, 不可调用 Windows API |
| Console     | main    | exe    | 可以调用 GUI 无关部分的 windows API 和 MFC    |
| SDK         | WinMain | exe    | windows API                               |
| MFC         | WinMain | exe    | MFC                                       |

1. mz (Mark Zbikowski)
2. exe (Portable Executable)
3. DOS 以外都属于 Win32 程序，可以在 Windows 下的 DOS Box 或 IDE 中编译
4. dumpbin 工具可以观察 PE 格式文件
5. 程序执行: 加载器 -> C Startup Code -> WinMain

文件句柄 file handle

1. 虚拟内存: 应用程序启动后, 组成这个程序的各对象是住留在内存的, Windows 是一个以虚拟内存为基础的操作系统, 内存管理器经常在内存中来回移动对象, 来满足各种应用程序的内存需要, 对象被移动意味着它的地址会发生变化
2. 句柄地址: Windows 为各应用程序腾出一些固定的内存储地址，专门用来登记各应用对象在内存中的地址变化, 保存对象被移动后的新地址, 通过这个句柄地址间接地知道对象具体在内存中的哪个位置
3. 内存分配: 对象的地址是在对象装载(Load)时由系统分配的, 当系统卸载时(Unload)又释放给系统
4. 描述符: 有一块内存区域保存了最终数据，而为了对这个数据进行操作，我们需要针对其构造一个描述结构体，这个结构体称为描述符
5. 文件句柄: windows 下的概念, 是指向具体对象(或数据块)的描述符的指针, 一个句柄就是你给一个文件, 设备, 管套(socket)或管道的一个名字, 以便帮助你记住你正处理的名字, 并隐藏缓存的复杂性, 其本质是一个指向指针的指针
6. 句柄是 HANDLE 类型, 例如, 创建文件 CreateFile 会返回一个 HANDLE 型的值
7. 句柄是一个系统内部数据结构的引用, 例如, 当你操作一个窗口(Delphi 窗体)时, 系统会返回一个该窗口的句柄, 系统会通知你: 你正在操作142号窗口, 应用程序就能要求系统对该窗口进行操作(移动, 改变大小, 最小化等)
8. 句柄是一种内部代码, 通过它能引用受系统控制的特殊元素(窗口, 位图, 图标, 内存块, 光标, 字体, 菜单等等)
9. Windows API 给这些项目分配确定的句柄，并将句柄返回给应用程序，然后通过句柄来进行操作, 而不是用物理地址来标识一个内存块，文件，任务或动态装入模块, 许多 Windows API 函数把句柄作为第一个参数(GDI 句柄, 菜单句柄, 实例句柄, 位图句柄等等)

# C Runtimes 函数库

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

# Windows API

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

前3个为 windosw 三大模块，由 windows.h 提供

# MFC 框架

MFC 框架(类库)是 C++ 类库

1. 对 Win32 应用程序编程接口的封装, 用 C++ 对象包装 Windows 对象, 例如: CWnd 类(C++ 窗口对象)把 Windows 窗口句柄(HWND)及相关 API 函数封装成 m_hWnd 数据成员和一些成员函数
2. 对应用程序概念的封装, 使用 SDK 编写 Windows 应用程序时, 总要定义窗口过程, 登记 Windows Class, 创建窗口等等. MFC 把许多类似的处理封装起来, 替程序员完成这些工作.
3. MFC 提出了以"文档-视图"为中心的编程模式, MFC 类库封装了对该编程模式的支持. 文档是用户操作的数据对象, 视图是数据操作的窗口, 用户通过视图处理和查看数据
4. 对 COM/OLE 特性的封装, OLE 建立在 COM 模型之上, 由于支持 OLE 的应用程序必须实现一系列的接口, 因而相当繁琐, MFC 的 OLE 类封装了 OLE API 大量复杂的工作, 这些类提供了实现 OLE 更高级的接口
5. 对 ODBC 功能的封装, 提供 ODBC 的更高级接口的 C++ 类, 封装了 ODBC API 大量复杂的工作, 提供了一种数据库编程模式

消息为基础, 事件驱动

1. 应用程序等待事件输入, 输入由操作系统捕捉, 以消息形式进入程序中
2. 用户模块(User Module)负责各个外围的驱动程序, User Module -> SendMessage() -> 窗口过程 Window procedure
3. 程序调用 GetMessage API 取得一个消息，程序的生命靠其推动
4. 窗口负责接收并处理消息, 每个窗口使用一个 窗口过程函数(window procedure) 负责处理消息
5. 窗口过程函数是 CALLBACK 函数, 即要被系统调用, 因为程序不关心的消息要由操作系统默认处理

输入的分类

| 消息来源         | 消息传递 |
| --------------- | ------- |
| 硬件装置         | mouse driver, keyboard driver -> system message queue |
| 系统或其他应用程序 | PostMessage() -> application message queue |

# 参考

书籍

1. 深入浅出MFC

教程

1. 闻怡洋 Visual C++ 6.0 MFC 入门教程

博客

1. [文件描述符，文件句柄的区别？](http://bbs.csdn.net/topics/230035323)
2. [文件句柄是什么意思](http://zhidao.baidu.com/question/35001537.html)
