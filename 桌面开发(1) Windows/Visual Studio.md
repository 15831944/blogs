# MFC 的工具

1. Visual C++
2. AppWizard 用来生成初步的框架文件(代码和资源等)
3. ClassWizard 用来协助添加代码到框架文件
4. Resource Editor 用于帮助直观地设计用户接口

# MFC 项目文件

1. 工作区文件(.dsw, developer studio workspace)用来存放与该工作区相关的信息
2. 工程文件(.dsp, developer studio project)
3. 选择信息文件(.opt)

| tool          | resource file  | file type |
| ------------- | -------------- | --------- |
| Dialog Editor | .dlg           | text      |
| Image Editor  | .bmp .ico .cur | binary    |
| Font Editor   | .fon           | binary    |

| 编译器/链接器 | 文件类型                     | 组成                    |
| ----------- | --------------------------- | ---------------------- |
| C Compiler  | .c, .h -> .obj              | 程序代码                |
| RC Compiler | .rc, .h -> .res             | UI(user Interface) 资源 |
| Linker      | .obj .res .def .lib -> .exe | 可执行程序               |

1. \.rc 脚本文件用于描述上述资源文件
1. \.def 模块定义文件记录模块名称, 程序段和数据段的内存特性, 堆和栈的大小, CALLBACK 函数名称等

rc 文件描述的资源类型

| resource type | 说明 |
| ------------- | ---- |
| ICON          | 图标 |
| MENU          | 菜单(静态) |
| DIALOGEX      | 对话框 |
| CURSOR        | 光标 |
| BITMAP        | 位图 |
| FONT          | 字体 |
| ACCELERATORS  | 快捷键 |
| STRING        | 字符串 |
| VERSIONINFO   | 版本信息 |
| TOOLBAR       | 工具栏 |

# Makefile

| 工具       | 说明       |
| --------- | --------- |
| nmake.exe | Microsoft |
| make.exe  | Borland   |

# 函数调用约定 Calling convention

决定参数进入堆栈的次序, 处理堆栈的责任归属

| 调用习惯  | 宏定义    |
| -------- | -------- |
| _stdcall | CALLBACK |
| _pascall |  |
| _cdecl   |  |

# 快捷键

| keystroke | describe |
| --------- | ------- |
| ctrl-k-c  | 添加注释 |
| ctrl-k-u  | 删除注释 |

# 查看头文件路径
