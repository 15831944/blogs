multitasking
multithreading
console programming



# 深入概念

Application Framework
	
	MFC(Microsoft Foundation Class Library)

Object Oriented

Runtime Type Information

Dynamic Creation

Persistence

Message Mapping

Command Routing

# windows 程序观念

# SDK 程序设计原理



# C++ 重要技术

类与对象

this 指针与继承

静态成员

虚函数与多态

模板类 template

异常处理 exception handling

# MFC 6大技术

## 简化仿真

Microsoft Visual C++提供工具

AppWizard 可以用来生成初步的框架文件（代码和资源等）；

资源编辑器用于帮助直观地设计用户接口；

ClassWizard 用来协助添加代码到框架文件；

工作区文件(.dsw)，用来存放与该工作区相关的信息；

工程文件(.dsp)

选择信息文件(.opt)

# 封装

构成MFC框架的是MFC类库。MFC类库是C++类库。

1. 对Win32应用程序编程接口的封装

用一个 C++ Object 来包装一个 Windows Object。例如：class CWnd是一个C++ window object，它把Windows window(HWND)和Windows window有关的API函数封装在C++ window object的成员函数内，后者的成员变量m_hWnd就是前者的窗口句柄。

（2）对应用程序概念的封装
使用SDK编写Windows应用程序时，总要定义窗口过程，登记Windows Class，创建窗口，等等。MFC把许多类似的处理封装起来，替程序员完成这些工作。另外，MFC提出了以文档-视图为中心的编程模式，MFC类库封装了对它的支持。文档是用户操作的数据对象，视图是数据操作的窗口，用户通过它处理、查看数据。
（3）对COM/OLE特性的封装
OLE建立在COM模型之上，由于支持OLE的应用程序必须实现一系列的接口（Interface），因而相当繁琐。MFC的OLE类封装了OLE API大量的复杂工作，这些类提供了实现OLE的更高级接口。
（4）对ODBC功能的封装
以少量的能提供与ODBC之间更高级接口的C++类，封装了ODBC API的大量的复杂的工作，提供了一种数据库编程模式。
