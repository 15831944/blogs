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
3. 对象的地址是在对象装载(Load)时由系统分配的, 当系统卸载时(Unload)又释放给系统
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

教程

闻怡洋 Visual C++ 6.0 MFC 入门教程

博客

1. [文件描述符，文件句柄的区别？](http://bbs.csdn.net/topics/230035323)
2. [文件句柄是什么意思](http://zhidao.baidu.com/question/35001537.html)
