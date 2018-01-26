# SDK 程序结构

1. 句柄(handle): 句柄是资源的标识号, 操作系统通过句柄来找到相应的资源进行管理和操作, 类似于UNIX中的文件描述符, 本质是指向指针的指针
2. 句柄的类型: 图标句柄(HICON), 光标句柄(HCURSOR), 窗口句柄(HWND, MSG 结构体的第一个成员, 消息接收者), 应用程序实例句柄(HINSTANCE)等, 本质是整型
3. 消息队列: 线程的消息队列是系统分配的一个 FIFO 缓冲区, 队列的元素是一个个 MSG 消息结构体, 使用 typedef 从变量的类型区分变量的用途, 程序员主要编写消息响应代码(窗口过程函数)

WinMain 函数参数(程序入口, 由操作系统在程序运行时调用)

1. 当前应用程序实例句柄: hInstance, 由操作系统分配和传入
2. 先前应用程序实例句柄: Win32 程序中总为空
3. 命令行参数: 指向字符串首地址的指针, 使用 Win+R 运行命令输入, 或在 VS 环境中配置
4. 窗口显示状态: 最大化, 最小化, 隐藏显示

设计并注册窗口类(WNDCLASS 结构体)

1. 窗口类的类型(Class styles): 位掩码, 水平重画, 垂直重画等
2. 窗口过程函数: 回调函数, 由用户定义和实现(消息响应代码)并赋值, 由操作系统在窗口收到消息时自动调用
3. 类附加内存, 窗口附加内存: 一般设置为0即可
4. 应用程序实例句柄(使用 WinMain 函数传入的句柄), 图标句柄(显示在窗口左上角, 调用 LoadIcon 函数获取), 光标句柄(LoadCursor 函数), 画刷句柄(窗口背景色, GetStockObject 函数)
5. 菜单名称(常量字符串), 窗口类名称

1. 定义窗口类结构体(WNDCLASS)并进行初始化
2. 调用 Register 函数注册窗口类, 传入设计好的窗口类结构体变量

创建显示和更新窗口(HWND)

1. 定义一个窗口句柄(HWND), 用于标识即将创建的窗口
2. 调用 CreateWindow 函数创建窗口(返回窗口句柄), 参数: 窗口类名称(传入已注册的窗口类), 窗口标题, 窗口类型(位掩码, 层叠, 标题栏等), 坐标, 宽高, 父窗口句柄, 菜单句柄, 实例句柄, WM_CREATE 消息的附加参数(多文档)
3. 调用 ShowWindow 函数, 显示窗口(最大化显示)
4. 调用 UpdateWindow 函数, 更新窗口, 最后做一次刷新

消息循环

1. 定义消息结构体(MSG), 存放取出的消息
2. 循环调用 GetMessage 函数, 接收发送给各个窗口的消息, 保证程序一直运行, 直到返回值为假
3. 调用 TranslateMessage 函数, 对消息对进行转换(产生新的消息加入消息队列), 例如将按键消息转换为字符消息(WM_CHAR)
4. 调用 DispatchMessage 函数, 将消息分配(路由)给窗口过程函数进行处理, 由操作系统调用
5. 实现窗口过程函数来响应消息, 函数名称可自定义, 参数固定不变: 窗口句柄, 消息标识符, 两个消息参数

消息响应

1. WM_CHAR 消息: 调用 MessageBox 函数, 弹出消息框
2. WM_LBUTTONDOWN 消息: 定义设备上下文句柄(HDC), 调用 GetDC 函数获取指定窗口的 DC 句柄(画布), 调用 TextOut 函数在指定的 DC 上输出文本, 调用 ReleaseDC 函数释放 DC 占用的资源
3. WM_PAINT 消息: 窗口从无到有, 尺寸发生便哈时重绘, 只能调用 BeginPaint 和 EndPaint 函数相应 WM_PAINT 消息
4. 缺省消息过程函数: DefWindowProc

程序终止

1. WM_CLOSE 消息: 调用 DestroyWindow 函数销毁指定窗口句柄标识的窗口(程序仍在运行), 发送 WM_DESTROY 消息
2. WM_DESTROY 消息: 调用 PostQuitMessage 函数, 发送 WM_QUIT 消息, GetMessage 收到此消息后返回0, 程序退出

# MFC 程序结构

1. 文件组织: 使用 MFC AppWizard 创建项目时, 系统为我们创建的五个类的定义和实现文件, VS 环境中还提供 MFC 类库文件和一些客户文件, 程序编译时将进行链接
2. 文件路径: `C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\atlmfc\src\mfc`

MFC 库的客户文件(执行流)

1. appmodul.cpp 文件: \_tWinMain 函数
2. winmain.cpp 文件: AfxWinMain 函数, 获取主应用程序对象, CWinApp::InitInstance, 调用 CWinApp::Run 函数? 调用 AfxEndDeferRegisterClass 函数注册窗口类
3. appcore.cpp 文件: 定义 AfxEndDeferRegisterClass 函数, 调用 AfxRegisterClass 函数注册窗口类, 调用 CFrameWnd::PreCreateWindow 函数
4. winfrm.cpp 文件: 调用 CreateEx 函数调用 CreateWindowEx 函数
5. thrdcore.cpp 文件: CWinThread::Run 函数进行消息循环, 消息映射

MFC 库的类的定义

1. CWnd 窗口类, m_hwnd 窗口句柄, CreateEx, DestroyWindow, PreCreateWindow 虚函数, ShowWindow, UpdateWindow 函数
2. CCmdTarget 类
3. CWinThread 类

1. CDialog 对话框类
2. CFrameWnd 框架窗口类, CFrameWnd::PreCreateWindow
3. CWinApp 应用程序类(afxwin.h, appcore.cpp), m_pMainWnd 数据成员, CWinApp::InitInstance 虚函数
4. CDocument 文档类
5. CView 视图类

MFC 项目生成的类实现文件

1. CAboutDlg 类: CDialog 类的派生类, 对话框类
2. CMainFrame 类: CFrameWnd 的派生类, 框架窗口(整个应用程序的窗口), 定义 PreCreateWindow 成员函数?
3. 应用程序类: CWinApp 的派生类, 只有一个 theApp 实例, 唯一的标识了该应用程序(Win32程序用实例号表示), 继承并实现 InitInstance 虚函数, 使用单文档模板来连接文档类, 框架类和视图类
4. 文档类: CDocument 的派生类, 文档类使数据和视图分开
5. 视图类: CView 的派生类, 子窗口

MFC 类继承图表

1. microsoft Foundation Class Library 提供了 Hierarchy Chart, 显示了所有类的组织结构图
2. CFrameWnd 类, CDialog 类和 CView 类均继承自 CWnd 窗口类, CWnd 类封装了与窗口操作相关的操作
3. CDocument 类继承自 CCmdTarget 类
4. CWinApp 类继承自 CWinThread 类

CWnd 对象与 Windows 窗口的关系

1. CWnd 对象是由 CWnd 构造函数和析构函数创建或销毁的, 窗口句柄 m_hWnd 这个数据成员, 保存了相关联的窗口的句柄 HWND, 对象销毁时应回收 Windows 窗口(不再显示)
2. Windows 窗口是系统内部的数据结构, 是一种资源, 由 Create 成员函数创建并由 CWnd 虚析构函数销毁
3. CWnd 对象本身不是 Windows 窗口, DestroyWindow 函数会销毁 Windows 窗口而不会销毁 CWnd 对象, 只是 m_hWnd 设为 NULL
4. 创建一个窗口时(例如 Button 控件窗口), 要先构建 CWnd 派生类对象, 再初始化相关的 Windows 窗口, 再显示窗口(在客户区域)
5. 子窗口对象可以作为父窗口对象的数据成员, 创建位置也是基于父窗口的

注意

1. 程序执行时, 先为全局变量和对象分配内存空间, 即先构造 CWinApp 应用程序类实例, 再执行 WinMain 函数
2. 类名以字母C开头表示Class
3. 父类的构造函数体中的 this, 在构造子类时, 指向的是子类对象
4. afx 前缀是 application framework 的缩写, 是一些应用程序框架类的全局函数的集合, 将各个类有机的组织在一起, 在每个类中都可以调用
5. 使用断点(break point)观察程序的执行流
6. 窗口类已经设计好了, 程序进行注册即可
7. Win32平台 SDK 和 MFC 函数库的函数名一般是相同的, 便于记忆
8. 在成员函数中, 如果成员函数名和想要调用的平台SDK函数名相同, 则在函数名前加域解析操作符而没有类名表示调用的是 Win32 平台全局函数

# 参考

教程

孙鑫VC++视频教程

MSDN

1. Platform SDK: Windows User Interface
2. Platform SDK: Windows GDI
