# CString

afx.h

## 成员函数

```
Left(int nCount) const;				// 获取前 nCount 个字符  
Mid(int nFirst) const;				// 获取 nFirst 到后面所有的字符  
Mid(int nFirst, int nCount) const;	// 获取 nFirst 后面 nCount 个字符  
Right(int nCount) const;			// 获取后 nCount 个字符  
```

# CWinApp

CWinApp 为应用程序类
MFC 中的主应用程序类封装用于 Windows 操作系统的应用程序的初始化、运行和终止。
基于框架生成的应用程序必须有且仅有一个从 CWinApp 派生的类的对象。在创建窗口之前先构造该对象。
CWinApp 是从 CWinThread 派生的，后者表示可能具有一个或多个线程的应用程序的主执行线程。
在最新版本的 MFC 中，InitInstance、Run、ExitInstance 和 OnIdle 成员函数实际位于 CWinThread 类中。
此处将这些函数作为 CWinApp 成员来探讨，因为探讨所关心的是对象作为应用程序对象而不是主线程的角色。
注意
应用程序类构成应用程序的主执行线程。使用 Win32 API 函数还可以创建辅助执行线程。这些线程可以使用 MFC 库。有关更多信息，请参见多线程编程。
与用于 Windows 操作系统的任何程序一样，框架应用程序也具有 WinMain 函数。
但在框架应用程序中不必编写 WinMain。它由类库提供，并在应用程序启动时调用。
WinMain 执行注册窗口类等标准服务。然后它调用应用程序对象的成员函数来初始化和运行应用程序。（可通过重写由 WinMain 调用的 CWinApp 成员函数来自定义 WinMain。）
为初始化应用程序，WinMain 调用应用程序对象的 InitApplication 和 InitInstance 成员函数。
为运行应用程序的消息循环，WinMain 调用 Run 成员函数。
在终止时，WinMain 调用应用程序对象的 ExitInstance 成员函数。
