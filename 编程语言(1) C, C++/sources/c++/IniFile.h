#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

class CIniFile : public CObject
{
	// 文件的每一行内容的类型, 可能是节名及注释, 键值对及注释, 纯注释
	enum SectionType
	{
		IsSection, IsItem, IsComment
	};

	// 文件的每一行可能包含的内容
	struct Section
	{
		SectionType	Type;
		CString		SectionName;	// 节名
		CString		Item;			// 键
		CString		Value;			// 值
		CString		Comment;		// 注释
	};

public:

	BOOL	Flush();
	BOOL	WriteValue(LPCTSTR szSection, LPCTSTR szItem, LPCTSTR szValue, LPCTSTR szComment = NULL);
	CString	Find(LPCTSTR szSection, LPCTSTR szItem);
	BOOL	Close();
	BOOL	Open(BOOL isReadOnly = FALSE);

	CIniFile(LPCTSTR szFileName);
	virtual ~CIniFile();

private:

	CString		 m_szFileName;	// 文件名, 在构造函数中获取, 在 open 成员函数中使用
	CString		 m_szContent;	// 文件全部内容, 在 open 成员函数中获取, 在 flush 成员函数中使用
	CFile		*m_pTxtFile;	// 文件对象指针
	BOOL		 m_bOpened;		// 文件打开状态
	BOOL		 m_bIsReadOnly;	// 由传入参数指定
	CArray<Section *, Section *>	m_arrayLine;	// 用于存储每行信息的数组

public:
	static bool		IsFileExist(CString szFileName);
	static void		CopyFileTo(CString szDestFileName, CString szSrcFileName);
	static CString	GetWinSysPath(void);
	static CString	GetAppPath(void);
	int				GetKeyVal(CString szSectionName, CString szKeyName, int ipDefault);
	CString			GetKeyVal(CString szSectionName, CString szKeyName, LPCTSTR szDefault);
};