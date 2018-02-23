# 概念

1. 消息处理程序 message handler
2. 命令处理程序 command handler, 函数声明前有 afx_msg, 一般在视图类, 框架类中添加

1. 单文档 SDI, 只有一个文档类对象, 重复使用
2. 多文档 MDI

# 文档的串行化

1. 串行化(serialization): 使数据持久性(persistent)的过程叫做串行化

# CWinApp 类

定义: afxwin.h

```
CDocManager *m_pDocManager	// 文档管理器, 维护文档模板的指针链表
CWinApp::OnFileNew()		// 消息响应函数, 响应 ID_FILE_NEW 命令
CWinApp::OpenDocumentFile()
```

# CDocManager 类

```
CPtrList m_templateList;	// 文档模板的指针链表, 维护文档模板
CDocManager::OnFileNew()	// 虚函数
```

# CDocTemplate 类

CSingleDocTemplate 类

单文档应用程序只有一个文档模板类

```
CDocTemplate::GetDocString();			// 获取 String Table 中的 IDR_MAINFRAME 资源中字符串的7个子串
CDocTemplate::OpenDocumentFile();		// 纯虚函数

CDocTemplate::CreateNewDocument();		// 创建文档类对象
CDocTemplate::CreateNewFrame();			// 创建床架类对象(其中会创建视图类对象)

CSingleDocTemplate::OpenDocumentFile();
```

# CArchive 类

1. 没有基类, 将基本类型(primitive types)和 CObject 派生类对象保存在磁盘文件中, 可看作输入输出流, 构造 CArchive 归档对象时关联一个CFile文件对象
2. 可串行化的类通常都有一个 CObject::Serialize 成员函数, 使用 DECLARE_SERIAL 和 IMPLEMENT_SERIAL 宏, 由 CObject 类描述

```
// 构造函数参数: 文件对象指针(打开时指定访问权限), 读写模式(加载和存储需要相应的文件读和写权限), 文件缓冲区大小(字节), 用户指定的指向该缓冲区的指针(需要人工释放)
CArchive::CArchive(CFile* pFile, UINT nMode, int nBufSize = 4096, void* lpBuf = NULL);
```

# CDocument 类

定义: afxwin.h

```
CDocument::SetTitle();			// 设置文档标题
CDocument::OnNewDocument();		// 虚函数, 无实现, 作为文件/新建命令的一部分
CDocument::GetFirstViewPosition();	// 获取文档类关联的视图类集合的位置
CDocument::GetNextView();			// 迭代访问所有视图类对象
CDocument::DeleteContents
```

# 文档类

虚函数

```
CTestDoc::OnNewDocument();	// 新建
CTestDoc::Serialize();		// 打开和保存
```


# 执行流

窗口->文档管理器->文档模板->文档类

文件/新建命令
CWinApp::OnFileNew()					// 命令响应函数
CDocManager::OnFileNew()				// 调用虚函数
CSingleDocTemplate::OpenDocumentFile()	// 调用虚函数
CDocTemplate::CreateNewDocument()		// 调用虚函数
CDocTemplate::CreateNewFrame()			// 调用虚函数
CTestDoc::OnNewDocument()				// 调用子类的虚函数

文件/打开或保存命令
CWinApp::OnFileOpen()
CDocManager::OnFileOpen()
CDocManager::DoPromptFileName()	// 文件打开对话框
CWinApp::OpenDocumentFile()
CDocManager::OpenDocumentFile()
CSingleDocTemplate::OpenDocumentFile()
CDocument::OnOpenDocument()
CTestDoc::Serialize()

# 对象的串行化

1. 在自定义的类中实现 Serialize 函数, 使类支持串行化, 决定存储对象的哪些数据

生成可串行化的类的步骤

1. 将你的类派生自 CObject 类
2. 重写 Serialize 成员函数
3. 在类声明中使用 DECLARE_SERIAL 宏
4. 定义没有参数的构造函数
5. 在类的实现文件中使用 IMPLEMENT_SERIAL 宏

# 文档/视图结构

文档类负责管理数据, 提供保存和加载数据的功能
视图类负责显示数据, 给用户提供对数据的编辑和修改功能
文档/视图结构支持将应用程序所需要的数据处理与显示的函数空壳都设计好, 这些函数都是虚函数, 可以在派生类中重写这些函数
有关文件的读写操作在 CDocument 的 Serialize 函数中进行
有关数据和图形的显示操作在 CView 的 OnDraw 函数中进行
当按下"File/Open"时, Application Framework 会激活文件打开对话框, 由用户指定文件名, 然后自动调用 CGraphicDoc::Serialize 读取文件, 调用 CGraphicView::OnDraw, 传递一个显示 DC, 让你重新绘制窗口内容

文档/视图结构使程序把精力放在数据结构的设计和数据显示的操作上, 而不是对象或模块之间的通信上
一个文档对象可以和多个视图对象相关联, 可以调用 CDocument::GetFirstViewPosition, CDocument::GetNextView 迭代的获取
一个视图对象只能和一个文档对象相关联
