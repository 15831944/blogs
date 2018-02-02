// MyStdioFile.h: interface for the CMyStdioFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSTDIOFILE_H__209D639C_CC92_430A_BA93_0F96E02872A0__INCLUDED_)
#define AFX_MYSTDIOFILE_H__209D639C_CC92_430A_BA93_0F96E02872A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyStdioFile : public CStdioFile
{
public:
	CMyStdioFile();
	virtual ~CMyStdioFile();

public:
	bool ReadLineWithout2SideSpace(CString *LineString);
};

#endif // !defined(AFX_MYSTDIOFILE_H__209D639C_CC92_430A_BA93_0F96E02872A0__INCLUDED_)
