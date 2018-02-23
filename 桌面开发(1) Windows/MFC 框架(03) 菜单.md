# 菜单 Menu

1. 使用 CMenu 类操作菜单资源

1. 静态菜单: 从资源文件加载
2. 动态菜单: 编写代码添加菜单项

1. 弹出菜单: Pop-up 属性被勾选, 不能进行命令相应, ID号不可更改
2. 对菜单项进行标记: CWnd::GetMenu CMenu::GetSubMneu CMenu::CheckMenuItem

1. 菜单栏 Menu 属于框架窗口
2. 子菜单 SubMenu 只能通过索引访问, 没有ID号, 例如文件, 编辑, 视图
3. 菜单项 MenuItem (可以通过索引和ID号访问)

2. 消息的响应顺序: 视图类, 文档类, 框架类, 应用程序类
3. 命令消息的路由: 先交给顶层的子窗口, 子窗口处理不了, 再交给应用程序类

消息类型

1. 标准消息: 以 WM_ 开头的消息. 由 CWnd 的派生类接收. CWnd 继承自 CCmdTarget, 因此窗口类也可以接收命令消息和通告消息.
2. 命令消息: WM_COMMAND 消息. 由 CCmdTarget 的派生类接收. 来自菜单, 加速键, 工具栏按钮的消息, 在 MFC 中通过 ID 来区分, 在 SDK 中通过 wParam 参数区分.
3. 通告消息: WM_COMMAND 消息. 由 CCmdTarget 的派生类接收. 由控件产生的消息(按钮单击, 列表框选择), 向其父窗口(通常是对话框)通知事件的发生.

事件处理程序

1. COMMAND
2. UPDATE_COMMAD_UI: 会传入 CCmdUI 对象

菜单项状态的命令更新机制(CN_UPDATE_COMMAND 消息)

在一个类的消息映射中添加 ON_UPDATE_COMMAND_UI 宏来捕获 CN_UPDATE_COMMAND_UI 消息, MFC 在该类中传递一个 CCmdUI 对象, 以对该菜单项进行操作

在后台, 操作系统发出 WM_INITMENUPOPUP 消息, 然后由 MFC 的基类如 CFrameWnd 接管, 后者创建一个 CCmdUI 对象, 并与第一个菜单项相关联, 调用对象的一个成员函数 DoUpdate(). 这个函数发出 CN_UPDATE_COMMAND_UI 消息, 消息带有指向 CCmdUI 对象的指针. 判断有没有响应该消息的宏, 进入我们编写的响应函数.

第一个菜单项更新完成后, 同一个 CCmdUI 对象就设置为与第二个菜单项相关联, 这样顺序进行, 直到完成所有菜单项

更新命令UI处理程序仅应用于弹出式菜单项上的项目, 不能应用于永久显示的顶级菜单项目

添加组件和控件, 例如, 右键弹出菜单: 工具箱 -> 右键 -> 选择项 ->

动态添加菜单项

lParam 和 wParam 是 Win16 系统遗留下来的产物，在 Win16 API 中 WndProc 有两个参数，一个 WORD 类型的 16 位整型变量，另一个是 LONG 类型的 32 位整型变量。根据匈牙利命名法(Hungarian notation)，16 位的变量就被命名为 wParam，而 32 位的变量就被命名为 lParam。
到了 Win32 API 中，原来的 16 位变量也被扩展为 32 位，因此 lParam 和 wParam 的大小完全相同。在 Win32 API 的早期，为了保证和 Win16 API 的代码兼容，MS 定义了 MPARAM 和 LPARAM 两个宏。保留 w 前缀的原因一方面是由于 WPARAM 宏也以 W 开头，另一方面是希望提醒程序员注意到可移植性。到了现在，Win16 早已退出历史舞台，但是这个前缀仍然约定俗成的沿用了下来。
