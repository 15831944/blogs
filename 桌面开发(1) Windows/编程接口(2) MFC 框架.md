# MFC 宏

## \_MSC_VER

C/C++ 编译器版本号

| MS                 | VC++            | _MSC_VER |
| ------------------ | --------------- | -------- |
| Visual Studio 2005 | Visual C++ 8.0  | 1400     |
| Visual Studio 2015 | Visual C++ 14.0 | 1900     |

## \_T 和 TEXT

区分常量字符串是 ansi 还是 unicode

## LPCTSTR LPTSTR LPCWSTR

Long Pointer Const \_T String

1. LPCTSTR 用来表示你的字符是否使用 UNICODE, 如果你的程序定义了 UNICODE 或者其他相关的宏, 那么这个字符串将被作为 UNICODE 字符串, 否则就是标准的 ANSI 字符串
2. LPCTSTR 是 const char * 或者 const wchar_t *, 相当于 const TCHAR*

## TCHAR

1. ANSI, UNICODE, 自动, 分别使用 printf, wprintf, \_tprintf 函数打印

```
THCAR	*p;
#ifdef UNICODE
	char const * format = "%ls";
#else
	char const * format = "%s";
#endif

printf(format, p);
```



# MFC 类库

## CString 字符串类

afx.h

```
Left(int nCount) const;				// 获取前 nCount 个字符  
Mid(int nFirst) const;				// 获取 nFirst 到后面所有的字符  
Mid(int nFirst, int nCount) const;	// 获取 nFirst 后面 nCount 个字符  
Right(int nCount) const;			// 获取后 nCount 个字符  
```

## CWinApp 主应用程序类

1. MFC 框架应用程序必须有且仅有一个 CWinApp 类的派生类的对象。在创建窗口之前先构造该对象。
2. CWinApp 类继承自 CWinThread 类，后者表示可能具有一个或多个线程的应用程序的主执行线程, 继承它的 InitInstance、Run、ExitInstance 和 OnIdle 等成员函数。
3. CWinApp 主应用程序类构成应用程序的主执行线程。使用 Win32 API 函数还可以创建辅助执行线程。这些线程可以使用 MFC 库。
4. MFC 框架应用程序的 WinMain 函数由类库提供，并在应用程序启动时调用。不必自行编写。用于执行注册窗口类等标准服务。
5. WinMain 函数调用 CWinApp 对象的成员函数来初始化(InitApplication 和 InitInstance)，运行应用程序的消息循环(Run)以及终止程序(ExitInstance)。
6. 通过重写由 WinMain 调用的 CWinApp 的成员函数来自定义 WinMain 函数。



# MFC 模板库

1. MSDN 建议使用基于模板的（template-based）数据收集类，数据收集类模板(MFC template-based Collection Classes)实现 lists, maps, arrays 等数据结构，包含在 afxtempl.h 头文件中

## CArray 数组

1. C++ 不支持动态数组, MFC 提供了 CArray 类来实现动态数组的功能，继承自 CObject 类

```
// 声明
CArray<Object, Object> Var1;
CArray<Object, Object&> Var2;

// 成员变量
TYPE*	m_pData;	// 数据保存地址的指针
int		m_nSize;	// 用户当前定义的数组的大小
int		m_nMaxSize;	// 当前实际分配的数组的大小
int		m_nGrowBy;	// 分配内存时增长的元素个数

// 构造函数
CArray<TYPE, ARG_TYPE>::CArray()	// 两个模板参数: 数组元素的数据类型, 函数调用时的参数类型
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

// 成员函数
CArray::GetSize
int GetSize( ) const;			// 取得当前数组元素个数

CArray::GetUpperBound
int GetUpperBound( ) const;		// 最大元素索引(数组元素个数-1)

CArray::SetSize
void SetSize( int nNewSize, int nGrowBy = -1 );	// 设置数组的大小
throw( CMemoryException );

CArray::FreeExtra
void FreeExtra( );				// 释放未使用的空间

CArray::RemoveAll
void RemoveAll( );				// 删除所有的元素

CArray::GetAt
TYPE GetAt( int nIndex ) const;		// 根据索引(参数)取得数组元素的值

CArray::SetAt
void SetAt( int nIndex, ARG_TYPE newElement );

CArray::ElementAt
TYPE& ElementAt( int nIndex );		// 取得第 nIndex 个元素的引用

CArray::GetData
const TYPE* GetData( ) const;		// 取得静态数组指针
TYPE* GetData( );

void SetAtGrow( int nIndex, ARG_TYPE newElement );	// 将第nIndex个元素设置成newElement,如果数组元素不够,会增加空间
throw( CMemoryException );

CArray::Add
int Add( ARG_TYPE newElement );		// 增加一个元素
throw( CMemoryException );

CArray::Append
int Append( const CArray& src );	// 追加另一个数组

void Copy( const CArray& src );		// 复制数组, 已经存在的内容将会被覆盖

CArray::InsertAt
void InsertAt( int nIndex, ARG_TYPE newElement, int nCount = 1 );	// 插入元素到数组
throw( CMemoryException );
void InsertAt( int nStartIndex, CArray* pNewArray );			// 插入一个数组到数组
throw( CMemoryException );

CArray::RemoveAt
void RemoveAt( int nIndex, int nCount = 1 );		// 删除另一个元素

CArray::operator [ ]					// 通过索引设置或取得另一个元素
TYPE& operator []( int nIndex );
TYPE operator []( int nIndex ) const;
```

# 参考

[MFC中CArray类原理及其应用](http://blog.csdn.net/whatday/article/details/8245963)
