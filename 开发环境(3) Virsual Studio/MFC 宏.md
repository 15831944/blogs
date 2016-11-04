# \_MSC_VER

C/C++ 编译器版本号

| MS                 | VC++            | _MSC_VER |
| ------------------ | --------------- | -------- |
| Visual Studio 2005 | Visual C++ 8.0  | 1400     |
| Visual Studio 2015 | Visual C++ 14.0 | 1900     |

# \_T 和 TEXT

区分常量字符串是 ansi 还是 unicode

# LPCTSTR LPTSTR LPCWSTR

Long Pointer Const \_T String

1. LPCTSTR 用来表示你的字符是否使用 UNICODE, 如果你的程序定义了 UNICODE 或者其他相关的宏, 那么这个字符或者字符串将被作为 UNICODE 字符串, 否则就是标准的 ANSI 字符串
2. LPCTSTR 是 const char * 或者 const wchar_t *, 相当于 const TCHAR*

# TCHAR

1. ANSI, UNICODE, 自动, 分别使用 printf, wprintf, _tprintf 函数打印

```
THCAR	*p;
#ifdef UNICODE
	char const * format = "%ls";
#else
	char const * format = "%s";
#endif

printf(format, p);
```
