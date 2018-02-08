# C 标准库

1. 带缓冲的文件I/O
2. FILE 结构体, 流
3. 文件指针, 指向数据即将写入的位置

1. 二进制文件: 可执行程序, 声音, 位图
2. 文本文件: ASCII码

1. 按文本方式写入数据时, 换行会转换为回车换行, 读取数据时, 回车换行会转换为换行
2. 按二进制方式读取和写入数据时, 则会按数据在内存中的存储形式原样读取和写入回车换行

```
#include <stdio.h>
fopen
fwrite
fread
fseek
ftell
rewind
fflush
fclose

itoa
atoi
```

# C++ 标准库

ofstream 类
ifstream 类

```
ofstream::write
ofstream::close
ifstream::read
ifstream::close
```

# Windows API

1. Access Mode
2. Share Mode
3. Flags, FILE_FLAG_OVERLAPPED, 异步I/O方式

```
::CreateFile
::WriteFile
::ReadFile
::CloseHandle
```

# MFC

1. CFile 类, 无缓存, 二进制, 派生类支持文本文件和内存文件
2. CFileDialog 类, 文件对话框, 继承自 CCommonDialog : CDialog

```
CFile::CFile		// 文件名, 访问和共享模式
CFile::Write		// 写入内容, 写入长度
CFile::Read			// 读取内容, 读取长度
CFile::Seek			// 当前文件指针的位置
CFile::GetLength	// 返回文件长度
CFile::Close		// 关闭文件

CDialog::DoModal
CFileDialog::CFileDialog	// 打开或保存为对话框, 默认文件扩展名, 文件名编辑框的初始文件名, 对话框标志, 文件过滤器, 该文件对话框的父窗口
CFileDialog::GetFileName
CFileDialog::GetPathName
m_ofn.lpstrTitle			// 对话框标题
m_ofn.lpstrFilter			// 文件过滤器
m_ofn.lpstrDefExt			// 默认扩展名(只用于保存对话框)
```

# 配置文件

```
::WriteProfileString		// 写入 ini 文件, 用于16位的 Windows
::GetProfileString			// 读取 ini 文件

CWinApp::WriteProfileString	// 写入注册表, 用于32位的 Windows
CWinApp::GetProfileString	// 读取注册表, 返回读取到的字符串

::RegCreateKey				// 创建 HKEY 注册表项
::RegSetValue				// 设置指定表项的没有名字的值的数据
```
