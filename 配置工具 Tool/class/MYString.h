// MYString.h: interface for the CMYString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSTRING_H__44E040A7_7070_4927_9E88_FB9752D4721B__INCLUDED_)
#define AFX_MYSTRING_H__44E040A7_7070_4927_9E88_FB9752D4721B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyString  : public CString
{
public:
	CMyString();
	virtual ~CMyString();

	void TrimSpace();
};

#endif // !defined(AFX_MYSTRING_H__44E040A7_7070_4927_9E88_FB9752D4721B__INCLUDED_)
