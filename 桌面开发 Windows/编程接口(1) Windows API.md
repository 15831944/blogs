# initialization-file functions

They retrieve information from and copy information to a system- or application-defined initialization file. These functions are provided only for compatibility with 16-bit versions of Windows. New applications should use the registry.

```
GetPrivateProfileInt
GetPrivateProfileString
WritePrivateProfileString
WritePrivateProfileInt
```

# windows.h

GetCurrentDirectory
GetModuleFileName

# AfxGetApp( )

得到当前应用进程的指针, 访问到这个进程中的对象, 单一的 CWinApp 对象的指针(A pointer to the single CWinApp object for the application)

```
CWinApp *AFXAPI AfxGetApp()
```

# Ribbon 界面

# 参考

1. [MSDN Library](https://msdn.microsoft.com/zh-cn/library/ms310241)
2. [Registry Functions (Windows)](https://msdn.microsoft.com/en-us/library/windows/desktop/ms724875(v=vs.85).aspx)
