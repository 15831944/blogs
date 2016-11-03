# 模板库

模板库用来实现一些比较常见的数据结构如 Array, List, Map

# CArray

afxtempl.h

1. C++ 不支持动态数组, MFC 提供了 CArray 类来实现动态数组的功能
2. CArray 继承自 CObject, 有两个模板参数，数组元素的数据类型, 函数调用时的参数类型

## 声明

```
CArray<Object, Object> Var1;
CArray<Object, Object&> Var2;
```

## 成员变量

```
TYPE*	m_pData;	// 数据保存地址的指针
int		m_nSize;	// 用户当前定义的数组的大小
int		m_nMaxSize;	// 当前实际分配的数组的大小
int		m_nGrowBy;	// 分配内存时增长的元素个数
```

## 构造函数

```
CArray<TYPE, ARG_TYPE>::CArray()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}
```

## 成员函数

```
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
